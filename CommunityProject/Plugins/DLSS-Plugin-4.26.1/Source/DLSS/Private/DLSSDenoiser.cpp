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

#include "DLSSDenoiser.h"
#include "DLSSUpscaler.h"
#include "PostProcess/TemporalAA.h"
#include "SceneTextureParameters.h"
#include "ScenePrivate.h"


static TAutoConsoleVariable<int32> CVarNGXDLSSReflectionsTemporalAA(
	TEXT("r.NGX.DLSS.Reflections.TemporalAA"),
	1,
	TEXT("Apply a temporal AA pass on the denoised reflections"),
	ECVF_RenderThreadSafe
);

static TAutoConsoleVariable<int32> CVarNGXDLSSWaterReflectionsTemporalAA(
	TEXT("r.NGX.DLSS.WaterReflections.TemporalAA"),
	1,
	TEXT("Apply a temporal AA pass on the denoised water reflections"),
	ECVF_RenderThreadSafe
);


FDLSSDenoiser::FDLSSDenoiser(const IScreenSpaceDenoiser* InWrappedDenoiser, const FDLSSUpscaler* InUpscaler)
	: WrappedDenoiser(InWrappedDenoiser)
	, Upscaler(InUpscaler)
{
	check(Upscaler);
	check(WrappedDenoiser);
}

const TCHAR* FDLSSDenoiser::GetDebugName() const
{
	if (Upscaler->IsDLSSActive())
	{
		return TEXT("FDLSSDenoiserWrapper(Active)");
	}
	else
	{
		return TEXT("FDLSSDenoiserWrapper(Inactive)");
	}
}

IScreenSpaceDenoiser::EShadowRequirements FDLSSDenoiser::GetShadowRequirements(const FViewInfo& View, const FLightSceneInfo& LightSceneInfo, const FShadowRayTracingConfig& RayTracingConfig) const
{
	return WrappedDenoiser->GetShadowRequirements(View, LightSceneInfo, RayTracingConfig);
}

void FDLSSDenoiser::DenoiseShadowVisibilityMasks(FRDGBuilder& GraphBuilder, const FViewInfo& View, FPreviousViewInfo* PreviousViewInfos, const FSceneTextureParameters& SceneTextures, const TStaticArray<FShadowVisibilityParameters, IScreenSpaceDenoiser::kMaxBatchSize>& InputParameters, const int32 InputParameterCount, TStaticArray<FShadowVisibilityOutputs, IScreenSpaceDenoiser::kMaxBatchSize>& Outputs) const
{
	WrappedDenoiser->DenoiseShadowVisibilityMasks(GraphBuilder, View, PreviousViewInfos, SceneTextures, InputParameters, InputParameterCount, Outputs);
}

IScreenSpaceDenoiser::FPolychromaticPenumbraOutputs FDLSSDenoiser::DenoisePolychromaticPenumbraHarmonics(FRDGBuilder& GraphBuilder, const FViewInfo& View, FPreviousViewInfo* PreviousViewInfos, const FSceneTextureParameters& SceneTextures, const FPolychromaticPenumbraHarmonics& Inputs) const
{
	return WrappedDenoiser->DenoisePolychromaticPenumbraHarmonics(GraphBuilder, View, PreviousViewInfos, SceneTextures, Inputs);
}

IScreenSpaceDenoiser::FReflectionsOutputs FDLSSDenoiser::DenoiseReflections(FRDGBuilder& GraphBuilder, const FViewInfo& View, FPreviousViewInfo* PreviousViewInfos, const FSceneTextureParameters& SceneTextures, const FReflectionsInputs& Inputs, const FReflectionsRayTracingConfig Config) const
{ 
	FReflectionsOutputs Outputs = WrappedDenoiser->DenoiseReflections(GraphBuilder, View, PreviousViewInfos, SceneTextures, Inputs, Config);
	const bool bIsDLSSActive = Upscaler->IsDLSSActive() && View.Family && Upscaler->IsValidUpscalerInstance(View.Family->GetTemporalUpscalerInterface());
	const bool bApplyTemporalAA = bIsDLSSActive && CVarNGXDLSSReflectionsTemporalAA.GetValueOnRenderThread() && View.ViewState && View.AntiAliasingMethod == AAM_TemporalAA;
	if(bApplyTemporalAA)
	{
		check(View.ViewState);

		FTAAPassParameters TAASettings(View);
		TAASettings.Pass = ETAAPassConfig::ScreenSpaceReflections;
		TAASettings.SceneDepthTexture = SceneTextures.SceneDepthTexture;
		TAASettings.SceneVelocityTexture = SceneTextures.GBufferVelocityTexture;
		TAASettings.SceneColorInput = Outputs.Color;
		TAASettings.bOutputRenderTargetable = true;

		FTAAOutputs TAAOutputs = AddTemporalAAPass(
			GraphBuilder,
			View,
			TAASettings,
			View.PrevViewInfo.SSRHistory,
			&View.ViewState->PrevFrameViewInfo.SSRHistory);

		Outputs.Color = TAAOutputs.SceneColor;
	}

	return Outputs;
}

IScreenSpaceDenoiser::FReflectionsOutputs FDLSSDenoiser::DenoiseWaterReflections(FRDGBuilder& GraphBuilder, const FViewInfo& View, FPreviousViewInfo* PreviousViewInfos, const FSceneTextureParameters& SceneTextures, const FReflectionsInputs& Inputs, const FReflectionsRayTracingConfig Config) const
{
	FReflectionsOutputs Outputs = WrappedDenoiser->DenoiseWaterReflections(GraphBuilder, View, PreviousViewInfos, SceneTextures, Inputs, Config);
	const bool bIsDLSSActive = Upscaler->IsDLSSActive() && View.Family && Upscaler->IsValidUpscalerInstance(View.Family->GetTemporalUpscalerInterface());
	const bool bApplyTemporalAA = bIsDLSSActive && Upscaler->IsDLSSActive() && CVarNGXDLSSWaterReflectionsTemporalAA.GetValueOnRenderThread() && View.ViewState && View.AntiAliasingMethod == AAM_TemporalAA;
	if (bApplyTemporalAA)
	{
		check(View.ViewState);

		FTAAPassParameters TAASettings(View);
		TAASettings.Pass = ETAAPassConfig::ScreenSpaceReflections;
		TAASettings.SceneDepthTexture = SceneTextures.SceneDepthTexture;
		TAASettings.SceneVelocityTexture = SceneTextures.GBufferVelocityTexture;
		TAASettings.SceneColorInput = Outputs.Color;
		TAASettings.bOutputRenderTargetable = true;

		FTAAOutputs TAAOutputs = AddTemporalAAPass(
			GraphBuilder,
			View,
			TAASettings,
			View.PrevViewInfo.WaterSSRHistory,
			&View.ViewState->PrevFrameViewInfo.WaterSSRHistory);

		Outputs.Color = TAAOutputs.SceneColor;
	}

	return Outputs;
}

IScreenSpaceDenoiser::FAmbientOcclusionOutputs FDLSSDenoiser::DenoiseAmbientOcclusion(FRDGBuilder& GraphBuilder, const FViewInfo& View, FPreviousViewInfo* PreviousViewInfos, const FSceneTextureParameters& SceneTextures, const FAmbientOcclusionInputs& Inputs, const FAmbientOcclusionRayTracingConfig Config) const
{
	return WrappedDenoiser->DenoiseAmbientOcclusion(GraphBuilder, View, PreviousViewInfos, SceneTextures, Inputs, Config);
}

IScreenSpaceDenoiser::FDiffuseIndirectOutputs FDLSSDenoiser::DenoiseDiffuseIndirect(FRDGBuilder& GraphBuilder, const FViewInfo& View, FPreviousViewInfo* PreviousViewInfos, const FSceneTextureParameters& SceneTextures, const FDiffuseIndirectInputs& Inputs, const FAmbientOcclusionRayTracingConfig Config) const
{
	return WrappedDenoiser->DenoiseDiffuseIndirect(GraphBuilder, View, PreviousViewInfos, SceneTextures, Inputs, Config);
}

IScreenSpaceDenoiser::FDiffuseIndirectOutputs FDLSSDenoiser::DenoiseSkyLight(FRDGBuilder& GraphBuilder, const FViewInfo& View, FPreviousViewInfo* PreviousViewInfos, const FSceneTextureParameters& SceneTextures, const FDiffuseIndirectInputs& Inputs, const FAmbientOcclusionRayTracingConfig Config) const
{
	return WrappedDenoiser->DenoiseSkyLight(GraphBuilder, View, PreviousViewInfos, SceneTextures, Inputs, Config);
}

IScreenSpaceDenoiser::FDiffuseIndirectOutputs FDLSSDenoiser::DenoiseReflectedSkyLight(FRDGBuilder& GraphBuilder, const FViewInfo& View, FPreviousViewInfo* PreviousViewInfos, const FSceneTextureParameters& SceneTextures, const FDiffuseIndirectInputs& Inputs, const FAmbientOcclusionRayTracingConfig Config) const
{
	return WrappedDenoiser->DenoiseReflectedSkyLight(GraphBuilder, View, PreviousViewInfos, SceneTextures, Inputs, Config);
}

IScreenSpaceDenoiser::FDiffuseIndirectHarmonic FDLSSDenoiser::DenoiseDiffuseIndirectHarmonic(FRDGBuilder& GraphBuilder, const FViewInfo& View, FPreviousViewInfo* PreviousViewInfos, const FSceneTextureParameters& SceneTextures, const FDiffuseIndirectHarmonic& Inputs, const FAmbientOcclusionRayTracingConfig Config) const
{
	return WrappedDenoiser->DenoiseDiffuseIndirectHarmonic(GraphBuilder, View, PreviousViewInfos, SceneTextures, Inputs, Config);
}

bool FDLSSDenoiser::SupportsScreenSpaceDiffuseIndirectDenoiser(EShaderPlatform Platform) const
{
	return WrappedDenoiser->SupportsScreenSpaceDiffuseIndirectDenoiser(Platform);
}

IScreenSpaceDenoiser::FDiffuseIndirectOutputs FDLSSDenoiser::DenoiseScreenSpaceDiffuseIndirect(FRDGBuilder& GraphBuilder, const FViewInfo& View, FPreviousViewInfo* PreviousViewInfos, const FSceneTextureParameters& SceneTextures, const FDiffuseIndirectInputs& Inputs, const FAmbientOcclusionRayTracingConfig Config) const
{
	return WrappedDenoiser->DenoiseScreenSpaceDiffuseIndirect(GraphBuilder, View, PreviousViewInfos, SceneTextures, Inputs, Config);
}

const IScreenSpaceDenoiser* FDLSSDenoiser::GetWrappedDenoiser() const
{
	return WrappedDenoiser;
}
