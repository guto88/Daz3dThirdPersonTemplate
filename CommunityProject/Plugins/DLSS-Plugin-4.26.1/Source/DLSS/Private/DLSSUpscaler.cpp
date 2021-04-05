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

#include "DLSSUpscaler.h"


#include "DLSSUpscalerPrivate.h"
#include "DLSSUpscalerHistory.h"
#include "DLSSSettings.h"

#include "VelocityCombinePass.h"

#include "PostProcess/SceneRenderTargets.h"
#include "PostProcess/PostProcessing.h"

#include "ScreenPass.h"

#include "PostProcess/PostProcessInput.h"
#include "CompositionLighting/PostProcessPassThrough.h"
#include "RayTracing/RaytracingOptions.h"

#include "LegacyScreenPercentageDriver.h"



#define LOCTEXT_NAMESPACE "FDLSSModule"


static TAutoConsoleVariable<int32> CVarNGXDLSSEnable(
	TEXT("r.NGX.DLSS.Enable"), 1,
	TEXT("Enable/Disable DLSS entirely."),
	ECVF_RenderThreadSafe);

static TAutoConsoleVariable<int32> CVarNGXDLSSAutomationTesting(
	TEXT("r.NGX.DLSS.AutomationTesting"), 0,
	TEXT("Whether the NGX library should be loaded when GIsAutomationTesting is true.(default is false)\n")
	TEXT("Must be set to true before startup. This can be enabled for cases where running automation testing with DLSS desired"),
	ECVF_ReadOnly);

static TAutoConsoleVariable<int32> CVarNGXDLSSPerfQualitySetting(
	TEXT("r.NGX.DLSS.Quality"),
	-1,
	TEXT("DLSS Performance/Quality setting. Not all modes might be supported at runtime, in this case Balanced mode is used as a fallback\n")
	TEXT(" -2: Ultra Performance\n")
	TEXT(" -1: Performance (default)\n")
	TEXT("  0: Balanced\n")
	TEXT("  1: Quality\n")
	TEXT("  2: Ultra Quality\n"),
	ECVF_RenderThreadSafe);

static TAutoConsoleVariable<float> CVarNGXDLSSSharpness(
	TEXT("r.NGX.DLSS.Sharpness"),
	0.0f,
	TEXT("0.0 to 1.0: Sharpening to apply to the DLSS pass (default: 0.0f)"),
	ECVF_RenderThreadSafe);

static TAutoConsoleVariable<int32> CVarNGXDLSSDilateMotionVectors(
	TEXT("r.NGX.DLSS.DilateMotionVectors"),
	1,
	TEXT(" 0: pass low resolution motion vectors into DLSS\n")
	TEXT(" 1: pass dilated high resolution motion vectors into DLSS. This can help with improving image quality of thin details. (default)"),
	ECVF_RenderThreadSafe);

DECLARE_GPU_STAT(DLSS)

BEGIN_SHADER_PARAMETER_STRUCT(FDLSSShaderParameters, )

// Input images
SHADER_PARAMETER_RDG_TEXTURE(Texture2D, SceneColorInput)
SHADER_PARAMETER_RDG_TEXTURE(Texture2D, SceneDepthInput)
SHADER_PARAMETER_RDG_TEXTURE(Texture2D, EyeAdaptation)
SHADER_PARAMETER_RDG_TEXTURE(Texture2D, SceneVelocityInput)


// Output images
RDG_TEXTURE_ACCESS(SceneColorOutput, ERHIAccess::UAVCompute)

END_SHADER_PARAMETER_STRUCT()


FIntPoint FDLSSPassParameters::GetOutputExtent() const
{
	check(Validate());
	check(SceneColorInput);

	FIntPoint InputExtent = SceneColorInput->Desc.Extent;

	FIntPoint QuantizedPrimaryUpscaleViewSize;
	QuantizeSceneBufferSize(OutputViewRect.Size(), QuantizedPrimaryUpscaleViewSize);

	return FIntPoint(
		FMath::Max(InputExtent.X, QuantizedPrimaryUpscaleViewSize.X),
		FMath::Max(InputExtent.Y, QuantizedPrimaryUpscaleViewSize.Y));
}

bool FDLSSPassParameters::Validate() const
{
	check(OutputViewRect.Min == FIntPoint::ZeroValue);
	return true;
}

const TCHAR* FDLSSUpscaler::GetDebugName() const
{
	return TEXT("FDLSSUpscaler");
}


static NVSDK_NGX_PerfQuality_Value ToNGXQuality(EDLSSQualityMode Quality)
{
	static_assert(int32(EDLSSQualityMode::NumValues) == 5,"please update this code to handle the new enum values" );
	switch (Quality)
	{
		case EDLSSQualityMode::UltraPerformance:
			return NVSDK_NGX_PerfQuality_Value_UltraPerformance;

		default:
			checkf(false, TEXT("EDLSSQualityMode out of range"));
		case EDLSSQualityMode::Performance:
			return NVSDK_NGX_PerfQuality_Value_MaxPerf;

		case EDLSSQualityMode::Balanced:
			return NVSDK_NGX_PerfQuality_Value_Balanced;

		case EDLSSQualityMode::Quality:
			return NVSDK_NGX_PerfQuality_Value_MaxQuality;
		
		case EDLSSQualityMode::UltraQuality:
			return NVSDK_NGX_PerfQuality_Value_UltraQuality;
	}
}

NGXRHI* FDLSSUpscaler::NGXRHIExtensions;
TStaticArray <TSharedPtr<FDLSSUpscaler>, uint32(EDLSSQualityMode::NumValues)> FDLSSUpscaler::DLSSUpscalerInstancesPerViewFamily;
float FDLSSUpscaler::MinResolutionFraction = TNumericLimits <float>::Max();
float FDLSSUpscaler::MaxResolutionFraction = TNumericLimits <float>::Min();


uint32 FDLSSUpscaler::NumRuntimeQualityModes = 0;
TArray<FDLSSOptimalSettings> FDLSSUpscaler::ResolutionSettings;


FDLSSUpscaler* FDLSSUpscaler::GetUpscalerInstanceForViewFamily(const FDLSSUpscaler* InUpscaler, EDLSSQualityMode InQualityMode)
{
	uint32 ArrayIndex = (int32)ToNGXQuality(InQualityMode);
	if (!DLSSUpscalerInstancesPerViewFamily[ArrayIndex])
	{
		DLSSUpscalerInstancesPerViewFamily[ArrayIndex] = MakeShared<FDLSSUpscaler>(InUpscaler, InQualityMode);

	}                                                  
	return DLSSUpscalerInstancesPerViewFamily[ArrayIndex].Get();
}

bool FDLSSUpscaler::IsValidUpscalerInstance(const ITemporalUpscaler* InUpscaler)
{
	for (auto UpscalerInstance : DLSSUpscalerInstancesPerViewFamily)
	{
		if (UpscalerInstance.Get() == InUpscaler)
		{
			return true;
		}
	}
	return false;
}

// make copy & assign quality mode
FDLSSUpscaler::FDLSSUpscaler(const FDLSSUpscaler* InUpscaler, EDLSSQualityMode InQualityMode)
	: FDLSSUpscaler(*InUpscaler)
{
	DLSSQualityMode = InQualityMode;
	check(NGXRHIExtensions);
}


FDLSSUpscaler::FDLSSUpscaler(NGXRHI* InNGXRHIExtensions)
	
{
	UE_LOG(LogDLSS, Log, TEXT("%s Enter"), __FUNCTIONW__);
	
	
	checkf(!NGXRHIExtensions, TEXT("static member NGXRHIExtensions should only be assigned once by this ctor when called during module startup") );
	NGXRHIExtensions = InNGXRHIExtensions;

	ResolutionSettings.Init(FDLSSOptimalSettings(), int32(EDLSSQualityMode::NumValues));

	static_assert(int32(EDLSSQualityMode::NumValues) == 5, "please update this code to handle the new enum values");
	for (auto QualityMode : { EDLSSQualityMode::UltraPerformance,  EDLSSQualityMode::Performance , EDLSSQualityMode::Balanced, EDLSSQualityMode::Quality,  EDLSSQualityMode::UltraQuality })
	{
		check(ToNGXQuality(QualityMode) < ResolutionSettings.Num());
		check(ToNGXQuality(QualityMode) >= 0);

		FDLSSOptimalSettings OptimalSettings = NGXRHIExtensions->GetDLSSOptimalSettings(ToNGXQuality(QualityMode));
		
		ResolutionSettings[ToNGXQuality(QualityMode)] = OptimalSettings;

		// we only consider non-fixed resolutions for the overall min / max resolution fraction
		if (OptimalSettings.bIsSupported && !OptimalSettings.IsFixedResolution())
		{
			// We use OptimalSettings.OptimalResolutionFraction to avoid getting to "floating point close" to OptimalSettings.{MinMax}ResolutionFraction) 
			MinResolutionFraction = FMath::Min(MinResolutionFraction, OptimalSettings.OptimalResolutionFraction);
			MaxResolutionFraction = FMath::Max(MaxResolutionFraction, OptimalSettings.OptimalResolutionFraction);
			++NumRuntimeQualityModes;
		}

		UE_LOG(LogDLSS, Log, TEXT("QualityMode %d: bSupported = %u, ResolutionFraction = %.4f. MinResolutionFraction=%.4f,  MaxResolutionFraction %.4f"),
			QualityMode, OptimalSettings.bIsSupported, OptimalSettings.OptimalResolutionFraction, OptimalSettings.MinResolutionFraction, OptimalSettings.MaxResolutionFraction);
	}

	// the DLSS module will report DLSS as not supported if there are no supported quality modes at runtime
	UE_LOG(LogDLSS, Log, TEXT("NumRuntimeQualityModes=%u, MinResolutionFraction=%.4f,  MaxResolutionFraction=%.4f"), NumRuntimeQualityModes, MinResolutionFraction, MaxResolutionFraction);

	// Higher levels of the code (e.g. UI) should check whether each mode is actually supported
	// But for now verify early that the DLSS 2.0 modes are supported. Those checks could be removed in the future
	check(IsQualityModeSupported(EDLSSQualityMode::Performance));
	check(IsQualityModeSupported(EDLSSQualityMode::Balanced));
	check(IsQualityModeSupported(EDLSSQualityMode::Quality));


	UE_LOG(LogDLSS, Log, TEXT("%s Leave"), __FUNCTIONW__);
}

FDLSSUpscaler::~FDLSSUpscaler()
{
	UE_LOG(LogDLSS, Log, TEXT("%s Enter"), __FUNCTIONW__);

	UE_LOG(LogDLSS, Log, TEXT("%s Leave"), __FUNCTIONW__);
}

// this gets explicitly called during module shutdown
void FDLSSUpscaler::ReleaseStaticResources()
{
	UE_LOG(LogDLSS, Log, TEXT("%s Enter"), __FUNCTIONW__);
	ResolutionSettings.Empty();
	for (auto& UpscalerInstance : DLSSUpscalerInstancesPerViewFamily)
	{
		UpscalerInstance.Reset();
	}
	
	UE_LOG(LogDLSS, Log, TEXT("%s Leave"), __FUNCTIONW__);
}

void FDLSSUpscaler::AddPasses(
	FRDGBuilder& GraphBuilder,
	const FViewInfo& View,
	const FPassInputs& PassInputs,
	FRDGTextureRef* OutSceneColorTexture,
	FIntRect* OutSceneColorViewRect,
	FRDGTextureRef* OutSceneColorHalfResTexture,
	FIntRect* OutSceneColorHalfResViewRect) const
{
	check(!PassInputs.bAllowDownsampleSceneColor);


	checkf(View.PrimaryScreenPercentageMethod == EPrimaryScreenPercentageMethod::TemporalUpscale, TEXT("DLSS requires TemporalUpscale. If you hit this assert, please set r.TemporalAA.Upscale=1"));


	

	const FTemporalAAHistory& InputHistory = View.PrevViewInfo.TemporalAAHistory;
	const TRefCountPtr<ICustomTemporalAAHistory> InputCustomHistory = View.PrevViewInfo.CustomTemporalAAHistory;

	FTemporalAAHistory* OutputHistory = View.ViewState ? &(View.ViewState->PrevFrameViewInfo.TemporalAAHistory) : nullptr;
	TRefCountPtr < ICustomTemporalAAHistory >* OutputCustomHistory = View.ViewState ? &(View.ViewState->PrevFrameViewInfo.CustomTemporalAAHistory) : nullptr;

	
	FDLSSPassParameters DLSSParameters(View);
	const FIntRect SecondaryViewRect = DLSSParameters.OutputViewRect;
	{
		RDG_GPU_STAT_SCOPE(GraphBuilder, DLSS);
		RDG_EVENT_SCOPE(GraphBuilder, "DLSS");

		const bool bDilateMotionVectors = CVarNGXDLSSDilateMotionVectors.GetValueOnRenderThread() != 0;

		FRDGTextureRef CombinedVelocityTexture = AddVelocityCombinePass(GraphBuilder, View, PassInputs.SceneDepthTexture, PassInputs.SceneVelocityTexture, bDilateMotionVectors);

		DLSSParameters.SceneColorInput = PassInputs.SceneColorTexture;
		DLSSParameters.EyeAdaptationInput = PassInputs.EyeAdaptationTexture;
		DLSSParameters.SceneVelocityInput = CombinedVelocityTexture;
		DLSSParameters.SceneDepthInput = PassInputs.SceneDepthTexture;
		DLSSParameters.bHighResolutionMotionVectors = bDilateMotionVectors;
		const FDLSSOutputs DLSSOutputs = AddDLSSPass(
			GraphBuilder,
			View,
			DLSSParameters,
			InputHistory,
			OutputHistory,
			InputCustomHistory,
			OutputCustomHistory
		);

		FRDGTextureRef SceneColorTexture = DLSSOutputs.SceneColor;

		*OutSceneColorTexture = SceneColorTexture;
		*OutSceneColorViewRect = SecondaryViewRect;

		*OutSceneColorHalfResTexture = nullptr;
		*OutSceneColorHalfResViewRect = FIntRect(FIntPoint::ZeroValue, FIntPoint::ZeroValue);
	}
}

FDLSSOutputs FDLSSUpscaler::AddDLSSPass(
	FRDGBuilder& GraphBuilder,
	const FViewInfo& View,
	const FDLSSPassParameters& Inputs,
	const FTemporalAAHistory& InputHistory,
	FTemporalAAHistory* OutputHistory,
	const TRefCountPtr<ICustomTemporalAAHistory> InputCustomHistoryInterface,
	TRefCountPtr<ICustomTemporalAAHistory>* OutputCustomHistoryInterface
) const
{
	check(IsValidUpscalerInstance(this));
	check(IsDLSSActive());
	const FDLSSUpscalerHistory* InputCustomHistory = static_cast<const FDLSSUpscalerHistory*>(InputCustomHistoryInterface.GetReference());

	const bool bCameraCut = !InputHistory.IsValid() || View.bCameraCut || !OutputHistory;
	const FIntPoint OutputExtent = Inputs.GetOutputExtent();

	const FIntRect SrcRect = Inputs.InputViewRect;
	const FIntRect DestRect = Inputs.OutputViewRect;

	const float ScaleX = float(SrcRect.Width()) / float(DestRect.Width());
	const float ScaleY = float(SrcRect.Height()) / float(DestRect.Height());

	// FDLSSUpscaler::SetupMainGameViewFamily or FDLSSUpscalerEditor::SetupEditorViewFamily 
	// set DLSSQualityMode by setting an FDLSSUpscaler on the ViewFamily (from the pool in DLSSUpscalerInstancesPerViewFamily)
	
	check(DLSSQualityMode != EDLSSQualityMode::NumValues);
	check(IsQualityModeSupported(DLSSQualityMode));

	check(GetMinResolutionFractionForQuality(DLSSQualityMode) - 0.01f <= ScaleX && ScaleX <= GetMaxResolutionFractionForQuality(DLSSQualityMode) + 0.01f);
	check(GetMinResolutionFractionForQuality(DLSSQualityMode) - 0.01f <= ScaleY && ScaleY <= GetMaxResolutionFractionForQuality(DLSSQualityMode) + 0.01f );

	const TCHAR* PassName = TEXT("MainUpsampling");

	// Create outputs
	FDLSSOutputs Outputs;
	{
		FRDGTextureDesc SceneColorDesc = FRDGTextureDesc::Create2D(
			OutputExtent,
			PF_FloatRGBA,
			FClearValueBinding::Black,
			TexCreate_ShaderResource | TexCreate_UAV);

		const TCHAR* OutputName = TEXT("DLSSOutputSceneColor");

		Outputs.SceneColor = GraphBuilder.CreateTexture(
			SceneColorDesc,
			OutputName);
	}

	FDLSSStateRef DLSSState = (InputCustomHistory && InputCustomHistory->DLSSState) ? InputCustomHistory->DLSSState : MakeShared<FDLSSState, ESPMode::ThreadSafe>();
	{
		FDLSSShaderParameters* PassParameters = GraphBuilder.AllocParameters<FDLSSShaderParameters>();

		// Set up common shader parameters
		const FIntPoint InputExtent = Inputs.SceneColorInput->Desc.Extent;
		const FIntRect InputViewRect = Inputs.InputViewRect;
		const FIntRect OutputViewRect = Inputs.OutputViewRect;

		// Input buffer shader parameters
		{
			PassParameters->SceneColorInput = Inputs.SceneColorInput;
			PassParameters->SceneDepthInput = Inputs.SceneDepthInput;
			PassParameters->SceneVelocityInput = Inputs.SceneVelocityInput;
			PassParameters->EyeAdaptation = Inputs.EyeAdaptationInput;
		}

		// Outputs 
		{
			PassParameters->SceneColorOutput = Outputs.SceneColor;
		}

		const FVector2D JitterOffset = View.TemporalJitterPixels;
		const float DeltaWorldTime = View.Family->DeltaWorldTime;

		const float PreExposure = View.PreExposure;

		const float Sharpness = FMath::Clamp(CVarNGXDLSSSharpness.GetValueOnRenderThread(), 0.0f, 1.0f);
		NGXRHI* LocalNGXRHIExtensions = this->NGXRHIExtensions;
		const int32 NGXPerfQuality = ToNGXQuality(DLSSQualityMode);
		GraphBuilder.AddPass(
			RDG_EVENT_NAME("DLSS %s%s %dx%d -> %dx%d",
				PassName,
				Sharpness != 0.0f ? TEXT(" Sharpen") : TEXT(""),
				SrcRect.Width(), SrcRect.Height(),
				DestRect.Width(), DestRect.Height()),
			PassParameters,
			ERDGPassFlags::Compute | ERDGPassFlags::Raster | ERDGPassFlags::SkipRenderPass,
			[LocalNGXRHIExtensions, PassParameters, Inputs, bCameraCut, JitterOffset, DeltaWorldTime, PreExposure, Sharpness, NGXPerfQuality, DLSSState](FRHICommandListImmediate& RHICmdList)
		{
			FRHIDLSSArguments DLSSArguments;
			FMemory::Memzero(&DLSSArguments, sizeof(DLSSArguments));

			// input parameters
			DLSSArguments.SrcRect = Inputs.InputViewRect;
			DLSSArguments.DestRect = Inputs.OutputViewRect;

			DLSSArguments.Sharpness = Sharpness;
			DLSSArguments.bReset = bCameraCut;
			DLSSArguments.JitterOffset = JitterOffset;

			DLSSArguments.MotionVectorScale = FVector2D(1.0f, 1.0f);
			DLSSArguments.bHighResolutionMotionVectors = Inputs.bHighResolutionMotionVectors;
			DLSSArguments.DeltaTime = DeltaWorldTime;

			DLSSArguments.PerfQuality = NGXPerfQuality;

			check(PassParameters->SceneColorInput);
			PassParameters->SceneColorInput->MarkResourceAsUsed();
			DLSSArguments.InputColor = PassParameters->SceneColorInput->GetRHI();
					

			check(PassParameters->SceneVelocityInput);
			PassParameters->SceneVelocityInput->MarkResourceAsUsed();
			DLSSArguments.InputMotionVectors = PassParameters->SceneVelocityInput->GetRHI();

			check(PassParameters->SceneDepthInput);
			PassParameters->SceneDepthInput->MarkResourceAsUsed();
			DLSSArguments.InputDepth = PassParameters->SceneDepthInput->GetRHI();

			check(PassParameters->EyeAdaptation);
			PassParameters->EyeAdaptation->MarkResourceAsUsed();
			DLSSArguments.InputExposure = PassParameters->EyeAdaptation->GetRHI();
			DLSSArguments.PreExposure = PreExposure;
			

			// output images
			check(PassParameters->SceneColorOutput);
			PassParameters->SceneColorOutput->MarkResourceAsUsed();
			DLSSArguments.OutputColor = PassParameters->SceneColorOutput->GetRHI();


			RHICmdList.EnqueueLambda(
				[LocalNGXRHIExtensions, DLSSArguments, DLSSState](FRHICommandListImmediate& Cmd)
			{
				LocalNGXRHIExtensions->ExecuteDLSS(Cmd, DLSSArguments, DLSSState);
			});
		});
	}

	if (!View.bStatePrevViewInfoIsReadOnly && OutputHistory)
	{
		OutputHistory->SafeRelease();

		GraphBuilder.QueueTextureExtraction(Outputs.SceneColor, &OutputHistory->RT[0]);

		OutputHistory->ViewportRect = DestRect;
		OutputHistory->ReferenceBufferSize = OutputExtent;
	}


	if (!View.bStatePrevViewInfoIsReadOnly && OutputCustomHistoryInterface)
	{
		if (!OutputCustomHistoryInterface->GetReference())
		{
			(*OutputCustomHistoryInterface) = new FDLSSUpscalerHistory(DLSSState);
		}
	}
	return Outputs;
}

void FDLSSUpscaler::Tick(FRHICommandListImmediate& RHICmdList)
{
	check(NGXRHIExtensions);
	check(IsInRenderingThread());
	// Pass it over to the RHI thread which handles the lifetime of the NGX DLSS resources
	RHICmdList.EnqueueLambda(
		[this](FRHICommandListImmediate& Cmd)
	{
		NGXRHIExtensions->TickPoolElements();
	});
}

bool FDLSSUpscaler::IsQualityModeSupported(EDLSSQualityMode InQualityMode) const
{
	return ResolutionSettings[ToNGXQuality(InQualityMode)].bIsSupported;
}

bool FDLSSUpscaler::IsDLSSActive() const
{
	static const auto CVarTemporalAAUpscaler = IConsoleManager::Get().FindConsoleVariable(TEXT("r.TemporalAA.Upscaler"));
	const bool bDLSSActive = ( (GTemporalUpscaler == this) || IsValidUpscalerInstance(this)) && CVarTemporalAAUpscaler && (CVarTemporalAAUpscaler->GetInt() != 0) && (CVarNGXDLSSEnable.GetValueOnAnyThread() != 0);
	return bDLSSActive;
}

void FDLSSUpscaler::SetupMainGameViewFamily(FSceneViewFamily& ViewFamily)
{
	const bool bDLSSActiveWithAutomation = !GIsAutomationTesting || (GIsAutomationTesting && (CVarNGXDLSSAutomationTesting.GetValueOnAnyThread() != 0));
	if (IsDLSSActive() && bDLSSActiveWithAutomation)
	{
		check(GTemporalUpscaler == this);
		check(GCustomStaticScreenPercentage == this);

		if (!GIsEditor || (GIsEditor && GIsPlayInEditorWorld && EnableDLSSInPlayInEditorViewports()))
		{
			EDLSSQualityMode DLSSQuality = GetSupportedQualityModeFromCVarValue(CVarNGXDLSSPerfQualitySetting.GetValueOnGameThread());
			ViewFamily.SetTemporalUpscalerInterface(GetUpscalerInstanceForViewFamily(this, DLSSQuality));

			if (ViewFamily.EngineShowFlags.ScreenPercentage && !ViewFamily.GetScreenPercentageInterface())
			{

				const float ResolutionFraction = GetOptimalResolutionFractionForQuality(DLSSQuality);
				ViewFamily.SetScreenPercentageInterface(new FLegacyScreenPercentageDriver(
					ViewFamily, ResolutionFraction,
					/* AllowPostProcessSettingsScreenPercentage = */  false));
			}
		}
	}
}


bool  FDLSSUpscaler::EnableDLSSInPlayInEditorViewports() const
{
	if (GetDefault<UDLSSOverrideSettings>()->EnableDLSSInPlayInEditorViewportsOverride == EDLSSSettingOverride::UseProjectSettings)
	{
		return GetDefault<UDLSSSettings>()->bEnableDLSSInPlayInEditorViewports;
	}
	else
	{
		return GetDefault<UDLSSOverrideSettings>()->EnableDLSSInPlayInEditorViewportsOverride == EDLSSSettingOverride::Enabled;
	}
}

float FDLSSUpscaler::GetMinUpsampleResolutionFraction() const
{
	return MinResolutionFraction;
}

float FDLSSUpscaler::GetMaxUpsampleResolutionFraction() const
{
	return MaxResolutionFraction;
}

float FDLSSUpscaler::GetOptimalResolutionFractionForQuality(EDLSSQualityMode Quality) const
{
	check(IsQualityModeSupported(Quality));
	return ResolutionSettings[ToNGXQuality(Quality)].OptimalResolutionFraction;
}

float  FDLSSUpscaler::GetOptimalSharpnessForQuality(EDLSSQualityMode Quality) const
{
	check(IsQualityModeSupported(Quality));
	return ResolutionSettings[ToNGXQuality(Quality)].Sharpness;
}

float FDLSSUpscaler::GetMinResolutionFractionForQuality(EDLSSQualityMode Quality) const
{
	check(IsQualityModeSupported(Quality));
	return ResolutionSettings[ToNGXQuality(Quality)].MinResolutionFraction;
}

float FDLSSUpscaler::GetMaxResolutionFractionForQuality(EDLSSQualityMode Quality) const
{
	check(IsQualityModeSupported(Quality));
	return ResolutionSettings[ToNGXQuality(Quality)].MaxResolutionFraction;
}

bool FDLSSUpscaler::IsFixedResolutionFraction(EDLSSQualityMode Quality) const
{
	check(IsQualityModeSupported(Quality));
	return ResolutionSettings[ToNGXQuality(Quality)].IsFixedResolution();
}

bool FDLSSUpscaler::IsResolutionFractionSupported(float InResolutionFraction) const
{
	for (auto ResolutionSetting : ResolutionSettings)
	{
		if ((ResolutionSetting.MinResolutionFraction - 0.01f) <= InResolutionFraction && InResolutionFraction <= (ResolutionSetting.MaxResolutionFraction + 0.01f))
		{
			return true;
		}
	}
	return false;
}

#undef LOCTEXT_NAMESPACE
