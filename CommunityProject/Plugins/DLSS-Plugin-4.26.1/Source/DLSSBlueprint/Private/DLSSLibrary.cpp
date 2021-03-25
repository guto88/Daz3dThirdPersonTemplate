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

#include "DLSSLibrary.h"
#include "DLSS.h"
#include "DLSSSettings.h"
#include "DLSSUpscaler.h"
#include "NGXRHI.h"

#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"
#include "ShaderCore.h"

#define LOCTEXT_NAMESPACE "FDLSSBlueprintModule"
DEFINE_LOG_CATEGORY_STATIC(LogDLSSBlueprint, Log, All);


FDLSSUpscaler* UDLSSLibrary::DLSSUpscaler = nullptr;
UDLSSSupport UDLSSLibrary::DLSSSupport = UDLSSSupport::NotSupported;

static bool ShowDLSSSDebugOnScreenMessages()
{
	if (GetDefault<UDLSSOverrideSettings>()->ShowDLSSSDebugOnScreenMessages == EDLSSSettingOverride::UseProjectSettings)
	{
		return GetDefault<UDLSSSettings>()->bShowDLSSSDebugOnScreenMessages;
	}
	else
	{
		return GetDefault<UDLSSOverrideSettings>()->ShowDLSSSDebugOnScreenMessages == EDLSSSettingOverride::Enabled;
	}
}


#if !UE_BUILD_SHIPPING

UDLSSLibrary::FDLSSErrorState UDLSSLibrary::DLSSErrorState;
FDelegateHandle UDLSSLibrary::DLSSOnScreenMessagesDelegateHandle;
void UDLSSLibrary::GetDLSSOnScreenMessages(TMultiMap<FCoreDelegates::EOnScreenMessageSeverity, FText>& OutMessages)
{
	check(IsInGameThread());

	if(ShowDLSSSDebugOnScreenMessages())
	{
		if (DLSSErrorState.bIsDLSSModeInvalid)
		{
			const FTextFormat Format(LOCTEXT("DLSSOnScreenDebugSetModeInvalidDLSSMode",
				"DLSS Error: The DLSS mode \"{0}\" is not supported. This error can be avoided by calling SetDLSSMode({0}) only if IsDLSSModeSupported({0}) returns true."));
			const FText Message = FText::Format(Format, StaticEnum<UDLSSMode>()->GetDisplayNameTextByValue(int64(DLSSErrorState.InvalidDLSSMode)));
			OutMessages.Add(FCoreDelegates::EOnScreenMessageSeverity::Error, Message);
		}

		// Checking for "contains" in case virtualization is changing the GPU string
		const bool bIsNVIDIA =  FWindowsPlatformMisc::GetPrimaryGPUBrand().Contains(TEXT("NVIDIA"));
	
		if (bIsNVIDIA && (UDLSSSupport::Supported != QueryDLSSSupport()))
		{
			const FTextFormat Format(LOCTEXT("DLSSOnScreenDebugDLSSNotSupported",
				"DLSS Information: DLSS is not supported due to {0}. Please see the various LogDLSS* categories in the Developer Tools -> Output Log for further detail."));
			const FText Message = FText::Format(Format, StaticEnum<UDLSSSupport>()->GetDisplayNameTextByValue(int64(QueryDLSSSupport())));
			OutMessages.Add(FCoreDelegates::EOnScreenMessageSeverity::Warning, Message);
		}
	}
}
#endif


static EDLSSQualityMode ToEDLSSQualityMode(UDLSSMode InDLSSQualityMode)
{
	static_assert(int32(EDLSSQualityMode::NumValues) == 5, "please update this code to handle the new enum values");

	switch (InDLSSQualityMode)
	{

	case UDLSSMode::UltraPerformance: 
		return EDLSSQualityMode::UltraPerformance;
	
	// the higher level code should catch this...
	case UDLSSMode::Off:
		checkf(false, TEXT("should not be called with UDLSSMode::Off "));
	default:
		checkf(false, TEXT("UDLSSMode out of range"));
	
	case UDLSSMode::Performance:
		return EDLSSQualityMode::Performance;
	
	case UDLSSMode::Balanced:
		return EDLSSQualityMode::Balanced;
	
	case UDLSSMode::Quality:
		return EDLSSQualityMode::Quality;
	
	case UDLSSMode::UltraQuality:
		return EDLSSQualityMode::UltraQuality;
	}
}

static int32 ToDLSSQualityCVarValue(UDLSSMode DLSSMode)
{
	return static_cast<int32>(ToEDLSSQualityMode(DLSSMode));
}

bool UDLSSLibrary::IsDLSSModeSupported(UDLSSMode DLSSMode)
{
	if (DLSSMode == UDLSSMode::Off)
	{
		return true;
	}
	else if (!IsDLSSSupported())
	{
		return false;
	}
	else
	{
		return DLSSUpscaler->IsQualityModeSupported(ToEDLSSQualityMode(DLSSMode));
	}
}

void UDLSSLibrary::GetDLSSModeInformation(UDLSSMode DLSSMode, bool& bIsSupported, float& OptimalScreenPercentage, bool& bIsFixedScreenPercentage, float& MinScreenPercentage, float& MaxScreenPercentage, float& OptimalSharpness)
{
	// fall back to TAA for unsupported or DLSS off
	OptimalScreenPercentage = 100.0f;
	OptimalScreenPercentage = 0.0f;
	bIsFixedScreenPercentage = false;
	MinScreenPercentage = 100.0f * ITemporalUpscaler::GetDefaultTemporalUpscaler()->GetMinUpsampleResolutionFraction();
	MaxScreenPercentage = 100.0f * ITemporalUpscaler::GetDefaultTemporalUpscaler()->GetMaxUpsampleResolutionFraction();
	OptimalSharpness = 0.0f;
	bIsSupported = IsDLSSModeSupported(DLSSMode);

	if ((DLSSMode != UDLSSMode::Off) && bIsSupported)
	{
		bIsFixedScreenPercentage = DLSSUpscaler->IsFixedResolutionFraction(ToEDLSSQualityMode(DLSSMode));

		OptimalScreenPercentage = 100.0f * DLSSUpscaler->GetOptimalResolutionFractionForQuality(ToEDLSSQualityMode(DLSSMode));
		MinScreenPercentage = 100.0f * DLSSUpscaler->GetMinResolutionFractionForQuality(ToEDLSSQualityMode(DLSSMode));
		MaxScreenPercentage = 100.0f * DLSSUpscaler->GetMaxResolutionFractionForQuality(ToEDLSSQualityMode(DLSSMode));

		OptimalSharpness = DLSSUpscaler->GetOptimalSharpnessForQuality(ToEDLSSQualityMode(DLSSMode));
	}
	
}

void UDLSSLibrary::GetDLSSScreenPercentageRange(float& MinScreenPercentage, float& MaxScreenPercentage)
{
	if (IsDLSSSupported())
	{
		MinScreenPercentage = 100.0f * DLSSUpscaler->GetMinUpsampleResolutionFraction();
		MaxScreenPercentage = 100.0f * DLSSUpscaler->GetMaxUpsampleResolutionFraction();
	}
	else
	{
		MinScreenPercentage = 100.0f;
		MaxScreenPercentage = 100.0f;
	}
}

TArray<UDLSSMode> UDLSSLibrary::GetSupportedDLSSModes()
{
	TArray<UDLSSMode> SupportedQualityModes;

	// always supported :)
	SupportedQualityModes.Add(UDLSSMode::Off);

	UEnum* Enum = StaticEnum<UDLSSMode>();

	int32 NumEnums = Enum->NumEnums();
	

	checkf(StaticEnum<UDLSSMode>()->NumEnums() == (6 + 1) /* + 1 is for _MAX */, TEXT("please update this code to handle the new enum values"));
	for (auto QualityMode : { UDLSSMode::UltraPerformance, UDLSSMode::Performance , UDLSSMode::Balanced,
	                          UDLSSMode::Quality,  UDLSSMode::UltraQuality })
	{
		if (IsDLSSModeSupported(QualityMode))
		{
			SupportedQualityModes.Add(QualityMode);
		}
	}

	return SupportedQualityModes;
}

bool UDLSSLibrary::IsDLSSSupported()
{
	return QueryDLSSSupport() == UDLSSSupport::Supported;
}

UDLSSSupport UDLSSLibrary::QueryDLSSSupport()
{
	return DLSSSupport;
}

void  UDLSSLibrary::GetDLSSMinimumDriverVersion(int32& MinDriverVersionMajor, int32& MinDriverVersionMinor)
{
	const NGXRHI* NGXRHIExtensions = DLSSUpscaler ? DLSSUpscaler->GetNGXRHI() : nullptr;

	FNGXDriverRequirements DriverRequirements = NGXRHIExtensions ? NGXRHIExtensions->GetDLSSDriverRequirements() : FNGXDriverRequirements();

	MinDriverVersionMajor = DriverRequirements.MinDriverVersionMajor;
	MinDriverVersionMinor = DriverRequirements.MinDriverVersionMinor;
}


void UDLSSLibrary::SetDLSSMode( UDLSSMode DLSSMode)
{
	static const auto CVarNGXEnable = IConsoleManager::Get().FindConsoleVariable(TEXT("r.NGX.Enable"));
	bool bNGXEnabled = CVarNGXEnable && CVarNGXEnable->GetInt();

	static auto CVarDLSSEnable = IConsoleManager::Get().FindConsoleVariable(TEXT("r.NGX.DLSS.Enable"));
	if (CVarDLSSEnable)
	{
		// r.NGX.Enable might be set to 0 via hotfix so set r.NGX.DLSS.Enable to 0 too (in case it might come from saved settings)
		bool bDLSSEnabled = bNGXEnabled && (DLSSMode != UDLSSMode::Off);
		CVarDLSSEnable->Set(bDLSSEnabled ? 1 : 0, ECVF_SetByCommandline);

#if !UE_BUILD_SHIPPING
		check(IsInGameThread());
		DLSSErrorState.bIsDLSSModeInvalid = !IsDLSSModeSupported(DLSSMode);
		DLSSErrorState.InvalidDLSSMode = DLSSMode;
#endif 
	}

	static auto CVarDLSSQuality = IConsoleManager::Get().FindConsoleVariable(TEXT("r.NGX.DLSS.Quality"));
	if (CVarDLSSQuality && (DLSSMode != UDLSSMode::Off))
	{
		CVarDLSSQuality->Set(ToDLSSQualityCVarValue(DLSSMode), ECVF_SetByCommandline);
	}
}

UDLSSMode UDLSSLibrary::GetDLSSMode()
{
	static const auto CVarNGXEnable = IConsoleManager::Get().FindConsoleVariable(TEXT("r.NGX.Enable"));
	bool bNGXEnabled = CVarNGXEnable && CVarNGXEnable->GetInt();

	static auto CVarDLSSEnable = IConsoleManager::Get().FindConsoleVariable(TEXT("r.NGX.DLSS.Enable"));
	bool DLSSEnabled = CVarDLSSEnable && CVarDLSSEnable->GetInt();

	static auto CVarDLSSQuality = IConsoleManager::Get().FindConsoleVariable(TEXT("r.NGX.DLSS.Quality"));
	int32 DLSSQuality = CVarDLSSQuality ? CVarDLSSQuality->GetInt() : 0;

	if (bNGXEnabled && DLSSEnabled && CVarDLSSQuality)
	{
		static_assert(int32(EDLSSQualityMode::NumValues) == 5, "please update this code to handle the new enum values");

		switch (EDLSSQualityMode(DLSSQuality))
		{
			case EDLSSQualityMode::UltraPerformance:
				return UDLSSMode::UltraPerformance;

			default:
				UE_LOG(LogDLSSBlueprint , Log, TEXT("r.NGX.DLSS.Quality is set to %d, which is outside of the valid range [%d, %d])"), DLSSQuality, EDLSSQualityMode::MinValue, EDLSSQualityMode::MaxValue);

			case EDLSSQualityMode::Performance:
				return UDLSSMode::Performance;

			case EDLSSQualityMode::Balanced:
				return UDLSSMode::Balanced;

			case EDLSSQualityMode::Quality:
				return UDLSSMode::Quality;

			case EDLSSQualityMode::UltraQuality:
				return UDLSSMode::UltraQuality;
		};
	}

	return UDLSSMode::Off;
}

void UDLSSLibrary::SetDLSSSharpness(float Sharpness)
{
	static const auto CVarNGXDLSSharpness = IConsoleManager::Get().FindConsoleVariable(TEXT("r.NGX.DLSS.Sharpness"));
	
	if (CVarNGXDLSSharpness)
	{
		CVarNGXDLSSharpness->Set(Sharpness, ECVF_SetByCommandline);
	}
}

float UDLSSLibrary::GetDLSSSharpness()
{
	static const auto CVarNGXDLSSharpness = IConsoleManager::Get().FindConsoleVariable(TEXT("r.NGX.DLSS.Sharpness"));
	
	if (CVarNGXDLSSharpness)
	{
		return CVarNGXDLSSharpness->GetFloat();
	}

	return 0.0f;
}

static UDLSSSupport ToUDLSSSupport(EDLSSSupport InDLSSSupport)
{
	switch (InDLSSSupport)
	{

		case EDLSSSupport::Supported:
			return UDLSSSupport::Supported;

		// this should be resolved at development time
		default:
			checkf(false, TEXT("please update this code to handle the new EDLSSSupport values"));
		case EDLSSSupport::NotSupported:
			return UDLSSSupport::NotSupported;

		case EDLSSSupport::NotSupportedIncompatibleHardware:
			return UDLSSSupport::NotSupportedIncompatibleHardware;


		case EDLSSSupport::NotSupportedDriverOutOfDate:
			return UDLSSSupport::NotSupportedDriverOutOfDate;

		case EDLSSSupport::NotSupportedOperatingSystemOutOfDate:
			return UDLSSSupport::NotSupportedOperatingSystemOutOfDate;
	}
}

void FDLSSBlueprintModule::StartupModule()
{
	IDLSSModuleInterface* DLSSModule = &FModuleManager::LoadModuleChecked<IDLSSModuleInterface>(TEXT("DLSS"));

	check(DLSSModule);

	UDLSSLibrary::DLSSUpscaler = DLSSModule->GetDLSSUpscaler();
	UDLSSLibrary::DLSSSupport = ToUDLSSSupport(DLSSModule->QueryDLSSSupport());

#if !UE_BUILD_SHIPPING
	UDLSSLibrary::DLSSOnScreenMessagesDelegateHandle = FCoreDelegates::OnGetOnScreenMessages.AddStatic(&UDLSSLibrary::GetDLSSOnScreenMessages);
#endif

	check((DLSSModule->GetDLSSUpscaler() != nullptr) || (DLSSModule->QueryDLSSSupport() != EDLSSSupport::Supported));
}

void FDLSSBlueprintModule::ShutdownModule()
{
#if !UE_BUILD_SHIPPING
	if (UDLSSLibrary::DLSSOnScreenMessagesDelegateHandle.IsValid())
	{
		FCoreDelegates::OnGetOnScreenMessages.Remove(UDLSSLibrary::DLSSOnScreenMessagesDelegateHandle);
		UDLSSLibrary::DLSSOnScreenMessagesDelegateHandle.Reset();
	}
#endif
}


#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FDLSSBlueprintModule, DLSSBlueprint)

