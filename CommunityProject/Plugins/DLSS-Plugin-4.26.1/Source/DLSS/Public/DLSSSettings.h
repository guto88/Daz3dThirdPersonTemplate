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

#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "Engine/DeveloperSettings.h"

#include "DLSSSettings.generated.h"

UENUM()
enum class EDLSSSettingOverride : uint8
{
	Enabled UMETA(DisplayName = "True"),
	Disabled UMETA(DisplayName = "False"),
	UseProjectSettings UMETA(DisplayName = "Use project settings"),
};

UCLASS(Config = Engine, ProjectUserConfig)
class DLSS_API UDLSSOverrideSettings : public UObject
{
public:

	GENERATED_BODY()
	
	/** This enables DLSS in editor viewports. Saved to local user config only.*/
	UPROPERTY(Config, EditAnywhere, Category = "Level Editor - Viewport (Local)", DisplayName = "Enable DLSS to be turned on in Editor viewports")
	EDLSSSettingOverride EnableDLSSInEditorViewportsOverride = EDLSSSettingOverride::UseProjectSettings;

	/** This setting enables adjusting the screenpercentage directly in the editor, outside of the optimized DLSS quality modes. Saved to local user config only.*/
	UPROPERTY(Config, EditAnywhere, Category = "Level Editor - Viewport (Local)", DisplayName = "Enable Screenpercentage Manipulation in DLSS Editor Viewports")
	EDLSSSettingOverride EnableScreenpercentageManipulationInDLSSEditorViewportsOverride = EDLSSSettingOverride::UseProjectSettings;

	/** This enables DLSS in play in editor viewports. Saved to local user config only. */
	UPROPERTY(Config, EditAnywhere, Category = "Level Editor - Viewport (Local)", DisplayName = "Enable DLSS in Play In Editor viewports")
	EDLSSSettingOverride EnableDLSSInPlayInEditorViewportsOverride = EDLSSSettingOverride::UseProjectSettings;

	/** This enables warnings about plugins & tools that are incompatible with DLSS in the editor. Saved to local user config only. */
	UPROPERTY(Config, EditAnywhere, Category = "Editor (Local)", DisplayName = "Warn about incompatible plugins and tools")
	bool bShowDLSSIncompatiblePluginsToolsWarnings = true;

	/** This enables on screen warnings and errors about DLSS  */
	UPROPERTY(Config, EditAnywhere, Category = "Editor (Local)", DisplayName = "Show various DLSS on screen debug messages")
	EDLSSSettingOverride ShowDLSSSDebugOnScreenMessages = EDLSSSettingOverride::UseProjectSettings;

};

UCLASS(Config = Engine, DefaultConfig, DisplayName="NVIDIA DLSS")
class DLSS_API UDLSSSettings: public UObject
{
	GENERATED_BODY()

private:

public:

	/** Enable DLSS for D3D12, if the driver supports it at runtime */
	UPROPERTY(Config, EditAnywhere, Category = "Platforms", DisplayName = "Enable DLSS for the D3D12RHI")
		bool bEnableDLSSD3D12 = PLATFORM_WINDOWS;

	/** Enable DLSS for D3D11, if the driver supports it at runtime */
	UPROPERTY(Config, EditAnywhere, Category = "Platforms", DisplayName = "Enable DLSS for the D3D11RHI")
		bool bEnableDLSSD3D11 = PLATFORM_WINDOWS;

	/** Enable DLSS for Vulkan, if the driver supports it at runtime */
	UPROPERTY(Config, EditAnywhere, Category = "Platforms", DisplayName = "Enable DLSS for the VulkanRHI")
		bool bEnableDLSSVulkan = PLATFORM_WINDOWS;

	/** This enables DLSS in editor viewports. This project wide setting can be locally overridden in the NVIDIA DLSS (Local) settings.*/
	UPROPERTY(Config, EditAnywhere, Category = "Level Editor - Viewport", DisplayName = "Enable DLSS to be turned on in Editor viewports")
		bool bEnableDLSSInEditorViewports = true;

	/** This setting enables adjusting the screenpercentage directly in the editor, outside of the optimized DLSS quality modes. This project wide setting can be locally overridden in the NVIDIA DLSS (Local) settings.*/
	UPROPERTY(Config = Editor, EditAnywhere, Category = "Level Editor - Viewport", DisplayName = "Enable Screenpercentage Manipulation in DLSS Editor Viewports")
		bool bEnableScreenpercentageManipulationInDLSSEditorViewports = false;

	/** This enables DLSS in play in editor viewports. This project wide setting can be locally overridden in in the NVIDIA DLSS (Local) settings.*/
	UPROPERTY(Config, EditAnywhere, Category = "Level Editor - Viewport", DisplayName = "Enable DLSS in Play In Editor viewports")
		bool bEnableDLSSInPlayInEditorViewports = true;

	/** This enables on screen warnings and errors about DLSS. This project wide setting can be locally overridden in the NVIDIA DLSS (Local) settings. */
	UPROPERTY(Config, EditAnywhere, Category = "Level Editor - Viewport", DisplayName = "Show various DLSS on screen debug messages")
		bool bShowDLSSSDebugOnScreenMessages = true;

	/** This is part of the DLSS plugin and used by most projects*/
	UPROPERTY(VisibleAnywhere, Config, Category = "General Settings", DisplayName = "Generic DLSS Binary Path")
		FString GenericDLSSBinaryPath;

	UPROPERTY(VisibleAnywhere, Config, Category = "General Settings", DisplayName = "Exists")
		bool bGenericDLSSBinaryExists;

	/** By default the DLSS plugin uses the UE4 Project ID to initalize DLSS. In some cases NVIDIA might provide a separate NVIDIA Application ID, which should be put here. Please refer to https://developer.nvidia.com/dlss for details*/
	UPROPERTY(Config, EditAnywhere, Category = "General Settings", DisplayName = "NVIDIA NGX Application ID", AdvancedDisplay)
		uint32 NVIDIANGXApplicationId;

	/** In some cases NVIDIA might provide a project specific DLSS binary for your project. Please refer to https://developer.nvidia.com/dlss for details*/
	UPROPERTY(VisibleAnywhere, Config, Category = "General Settings", DisplayName = "Custom DLSS Binary Path", AdvancedDisplay)
		FString CustomDLSSBinaryPath;
	UPROPERTY(VisibleAnywhere, Config, Category = "General Settings", DisplayName = "Exists", AdvancedDisplay)
		bool bCustomDLSSBinaryExists;
};
