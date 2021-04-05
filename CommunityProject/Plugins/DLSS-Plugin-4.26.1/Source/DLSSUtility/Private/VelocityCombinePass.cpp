/*
* Copyright (c) 2020 NVIDIA CORPORATION.  All rights reserved.
*
* NVIDIA Corporation and its licensors retain all intellectual property and proprietary
* rights in and to this software, related documentation and any modifications thereto.
* Any use, reproduction, disclosure or distribution of this software and related
* documentation without an express license agreement from NVIDIA Corporation is strictly
* prohibited.
*
* TO THE MAXIMUM EXTENT PERMITTED BY APPLICABLE LAW, THIS SOFTWARE IS PROVIDED *AS IS*
* AND NVIDIA AND ITS SUPPLIERS DISCLAIM ALL WARRANTIES, EITHER EXPRESS OR IMPLIED,
* INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE.  IN NO EVENT SHALL NVIDIA OR ITS SUPPLIERS BE LIABLE FOR ANY
* SPECIAL, INCIDENTAL, INDIRECT, OR CONSEQUENTIAL DAMAGES WHATSOEVER (INCLUDING, WITHOUT
* LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION, LOSS OF
* BUSINESS INFORMATION, OR ANY OTHER PECUNIARY LOSS) ARISING OUT OF THE USE OF OR
* INABILITY TO USE THIS SOFTWARE, EVEN IF NVIDIA HAS BEEN ADVISED OF THE POSSIBILITY OF
* SUCH DAMAGES.
*/

#include "VelocityCombinePass.h"


const int32 kVelocityCombineComputeTileSizeX = FComputeShaderUtils::kGolden2DGroupSize;
const int32 kVelocityCombineComputeTileSizeY = FComputeShaderUtils::kGolden2DGroupSize;


class FDilateMotionVectorsDim : SHADER_PERMUTATION_BOOL("DILATE_MOTION_VECTORS");

class FVelocityCombineCS : public FGlobalShader
{
public:
	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		// Only cook for the platforms/RHIs where DLSS is supported, which is DX11,DX12 and Vulkan [on Win64]
		return 	IsFeatureLevelSupported(Parameters.Platform, ERHIFeatureLevel::SM5) &&
				IsPCPlatform(Parameters.Platform) && (IsD3DPlatform(Parameters.Platform, false) || IsVulkanSM5Platform(Parameters.Platform));
	}

	static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)
	{
		FGlobalShader::ModifyCompilationEnvironment(Parameters, OutEnvironment);
		OutEnvironment.SetDefine(TEXT("THREADGROUP_SIZEX"), kVelocityCombineComputeTileSizeX);
		OutEnvironment.SetDefine(TEXT("THREADGROUP_SIZEY"), kVelocityCombineComputeTileSizeY);
	}
	using FPermutationDomain = TShaderPermutationDomain<FDilateMotionVectorsDim>;

	DECLARE_GLOBAL_SHADER(FVelocityCombineCS);
	SHADER_USE_PARAMETER_STRUCT(FVelocityCombineCS, FGlobalShader);

	BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
		// Input images
		SHADER_PARAMETER_RDG_TEXTURE(Texture2D, VelocityTexture)
		SHADER_PARAMETER_SAMPLER(SamplerState, VelocityTextureSampler)
		SHADER_PARAMETER_STRUCT(FScreenPassTextureViewportParameters, Velocity)

		SHADER_PARAMETER_RDG_TEXTURE(Texture2D, DepthTexture)
		SHADER_PARAMETER_SAMPLER(SamplerState, DepthTextureSampler)

		SHADER_PARAMETER(FVector2D, TemporalJitterPixels)

		SHADER_PARAMETER_STRUCT_REF(FViewUniformShaderParameters, View)
		
		// Output images
		SHADER_PARAMETER_RDG_TEXTURE_UAV(Texture2D, OutVelocityCombinedTexture)
		SHADER_PARAMETER_STRUCT(FScreenPassTextureViewportParameters, CombinedVelocity)

	END_SHADER_PARAMETER_STRUCT()
};


IMPLEMENT_GLOBAL_SHADER(FVelocityCombineCS, "/Plugin/DLSS/Private/VelocityCombine.usf", "VelocityCombineMain", SF_Compute);

FRDGTextureRef AddVelocityCombinePass(
	FRDGBuilder& GraphBuilder,
	const FViewInfo& View,
	FRDGTextureRef InSceneDepthTexture,
	FRDGTextureRef InVelocityTexture,
	bool bDilateMotionVectors
)
{
	const FIntRect InputViewRect = View.ViewRect;
	const FIntRect OutputViewRect = FIntRect( FIntPoint::ZeroValue, bDilateMotionVectors ? View.GetSecondaryViewRectSize() : View.ViewRect.Size());

	FRDGTextureDesc CombinedVelocityDesc = FRDGTextureDesc::Create2D(
		OutputViewRect.Size(),
		PF_G16R16F,
		FClearValueBinding::Black,
		TexCreate_ShaderResource | TexCreate_UAV);
	const TCHAR* OutputName = TEXT("DLSSCombinedVelocity");

	FRDGTextureRef CombinedVelocityTexture = GraphBuilder.CreateTexture(
		CombinedVelocityDesc,
		OutputName);

	FVelocityCombineCS::FParameters* PassParameters = GraphBuilder.AllocParameters<FVelocityCombineCS::FParameters>();

	// input velocity
	{
		PassParameters->VelocityTexture = InVelocityTexture;
		PassParameters->VelocityTextureSampler = TStaticSamplerState<SF_Point>::GetRHI();

		// we use InSceneDepthTexture here and not InVelocityTexture since the latter can be a 1x1 black texture
		check(InVelocityTexture->Desc.Extent == FIntPoint(1, 1) || InVelocityTexture->Desc.Extent == InSceneDepthTexture->Desc.Extent);
		FScreenPassTextureViewport velocityViewport(InSceneDepthTexture, InputViewRect);
		FScreenPassTextureViewportParameters velocityViewportParameters = GetScreenPassTextureViewportParameters(velocityViewport);
		PassParameters->Velocity = velocityViewportParameters;
	}
	// input depth
	{
		PassParameters->DepthTexture = InSceneDepthTexture;
		PassParameters->DepthTextureSampler = TStaticSamplerState<SF_Point>::GetRHI();
	}
	// output combined velocity
	{
		PassParameters->OutVelocityCombinedTexture = GraphBuilder.CreateUAV(CombinedVelocityTexture);

		FScreenPassTextureViewport CombinedVelocityViewport(CombinedVelocityTexture, OutputViewRect);
		FScreenPassTextureViewportParameters CombinedVelocityViewportParameters = GetScreenPassTextureViewportParameters(CombinedVelocityViewport);
		PassParameters->CombinedVelocity = CombinedVelocityViewportParameters;
	}

	// various state
	{
		PassParameters->TemporalJitterPixels = View.TemporalJitterPixels;
		PassParameters->View = View.ViewUniformBuffer;
	}

	FVelocityCombineCS::FPermutationDomain PermutationVector;
	PermutationVector.Set<FDilateMotionVectorsDim>(bDilateMotionVectors);

	TShaderMapRef<FVelocityCombineCS> ComputeShader(View.ShaderMap, PermutationVector);

	FComputeShaderUtils::AddPass(
		GraphBuilder,
		RDG_EVENT_NAME("Velocity Combine%s (%dx%d -> %dx%d)", 
			bDilateMotionVectors ? TEXT(" Dilate") : TEXT(""),
			InputViewRect.Width(), InputViewRect.Height(),
			OutputViewRect.Width(), OutputViewRect.Height()
		),
		ComputeShader,
		PassParameters,
		FComputeShaderUtils::GetGroupCount(OutputViewRect.Size(), FComputeShaderUtils::kGolden2DGroupSize));
		
	return CombinedVelocityTexture;
}