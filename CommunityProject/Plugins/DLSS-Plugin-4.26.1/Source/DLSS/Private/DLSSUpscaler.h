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

#pragma once

#include "CoreMinimal.h"
#include "RendererInterface.h"
#include "PostProcess/TemporalAA.h"
#include "ScreenPass.h"
#include "NGXRHI.h"

#include "CustomStaticScreenPercentage.h"
#include "CustomResourcePool.h"

class FSceneTextureParameters;

struct FTemporalAAHistory;

class FRHITexture;
class NGXRHI;
struct FDLSSOptimalSettings;
struct FDLSSPassParameters
{
	FIntRect InputViewRect;
	FIntRect OutputViewRect;
	bool bHighResolutionMotionVectors = false;

	FRDGTexture* SceneColorInput = nullptr;
	FRDGTexture* SceneVelocityInput = nullptr;
	FRDGTexture* SceneDepthInput = nullptr;

	FRDGTexture* EyeAdaptationInput = nullptr;

	FDLSSPassParameters(const FViewInfo& View)
		: InputViewRect(View.ViewRect)
		, OutputViewRect(FIntPoint::ZeroValue, View.GetSecondaryViewRectSize())
	{
	}

	/** Returns the texture resolution that will be output. */
	FIntPoint GetOutputExtent() const;

	/** Validate the settings of TAA, to make sure there is no issue. */
	bool Validate() const;
};

struct FDLSSOutputs
{
	FRDGTexture* SceneColor = nullptr;
};

enum class EDLSSQualityMode
{
	MinValue = -2,
	UltraPerformance = -2,
	Performance = -1,
	Balanced = 0,
	Quality = 1,
	UltraQuality = 2,
	MaxValue = UltraQuality,
	NumValues = 5
};

class DLSS_API FDLSSUpscaler final : public ITemporalUpscaler, public ICustomStaticScreenPercentage, public ICustomResourcePool
{

	friend class FDLSSModule;
public:


	FDLSSUpscaler(const FDLSSUpscaler* InUpscaler, EDLSSQualityMode InQualityMode);
	virtual ~FDLSSUpscaler();
	// Inherited via ITemporalUpscaler
	virtual const TCHAR* GetDebugName() const final;

	virtual void AddPasses(
		FRDGBuilder& GraphBuilder,
		const FViewInfo& View,
		const FPassInputs& PassInputs,
		FRDGTextureRef* OutSceneColorTexture,
		FIntRect* OutSceneColorViewRect,
		FRDGTextureRef* OutSceneColorHalfResTexture,	
		FIntRect* OutSceneColorHalfResViewRect) const final;


	// Inherited via ICustomStaticScreenPercentage
	virtual void SetupMainGameViewFamily(FSceneViewFamily& ViewFamily) final;
	virtual float GetMinUpsampleResolutionFraction() const final;
	virtual float GetMaxUpsampleResolutionFraction() const final;

	float GetOptimalResolutionFractionForQuality(EDLSSQualityMode Quality) const;
	float GetOptimalSharpnessForQuality(EDLSSQualityMode Quality) const;
	float GetMinResolutionFractionForQuality(EDLSSQualityMode Quality) const;
	float GetMaxResolutionFractionForQuality(EDLSSQualityMode Quality) const;
	bool IsFixedResolutionFraction(EDLSSQualityMode Quality) const;
	
	const NGXRHI* GetNGXRHI() const
	{
		return NGXRHIExtensions;
	}

	// Inherited via ICustomResourcePool
	virtual void Tick(FRHICommandListImmediate& RHICmdList) override;

	bool IsQualityModeSupported(EDLSSQualityMode InQualityMode) const;
	uint32 GetNumRuntimeQualityModes() const
	{
		return NumRuntimeQualityModes;
	}

	bool IsDLSSActive() const;

	static FDLSSUpscaler* GetUpscalerInstanceForViewFamily(const FDLSSUpscaler* InUpscaler, EDLSSQualityMode InQualityMode);
	static bool IsValidUpscalerInstance(const ITemporalUpscaler* InUpscaler);

	static void ReleaseStaticResources();

private:
	FDLSSUpscaler(NGXRHI* InNGXRHIExtensions);
	FDLSSUpscaler(const FDLSSUpscaler&) = default;
	

	EDLSSQualityMode GetSupportedQualityModeFromCVarValue(int32 InCVarValue) const
	{
		check(NumRuntimeQualityModes );
		static_assert(int32(EDLSSQualityMode::NumValues) == 5, "please update this code to handle the new enum values");
		for (auto QualityMode : { EDLSSQualityMode::UltraPerformance,  EDLSSQualityMode::Performance , EDLSSQualityMode::Balanced, EDLSSQualityMode::Quality,  EDLSSQualityMode::UltraQuality })
		{
			if (InCVarValue == static_cast<int32>(QualityMode) && IsQualityModeSupported(QualityMode))
			{
				return QualityMode;
			}
		}
		return EDLSSQualityMode::Balanced;
	}

	bool IsResolutionFractionSupported(float InResolutionFraction) const;
	
	bool EnableDLSSInPlayInEditorViewports() const;
	FDLSSOutputs AddDLSSPass(
		FRDGBuilder& GraphBuilder,
		const FViewInfo& View,
		const FDLSSPassParameters& Inputs,
		const FTemporalAAHistory& InputHistory,
		FTemporalAAHistory* OutputHistory,
		const TRefCountPtr<ICustomTemporalAAHistory> InputCustomHistoryInterface,
		TRefCountPtr<ICustomTemporalAAHistory>* OutputCustomHistoryInterface
	) const;


	
	EDLSSQualityMode DLSSQualityMode = EDLSSQualityMode::NumValues;

	// The FDLSSUpscaler(NGXRHI*) will update those once
	static NGXRHI* NGXRHIExtensions;
	static float MinResolutionFraction;
	static float MaxResolutionFraction;	

	static uint32 NumRuntimeQualityModes;
	static TArray<FDLSSOptimalSettings> ResolutionSettings;

	static TStaticArray <TSharedPtr<FDLSSUpscaler>, uint32(EDLSSQualityMode::NumValues)> DLSSUpscalerInstancesPerViewFamily;
};
