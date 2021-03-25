// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DLSS/Public/DLSSSettings.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeDLSSSettings() {}
// Cross Module References
	DLSS_API UEnum* Z_Construct_UEnum_DLSS_EDLSSSettingOverride();
	UPackage* Z_Construct_UPackage__Script_DLSS();
	DLSS_API UClass* Z_Construct_UClass_UDLSSOverrideSettings_NoRegister();
	DLSS_API UClass* Z_Construct_UClass_UDLSSOverrideSettings();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	DLSS_API UClass* Z_Construct_UClass_UDLSSSettings_NoRegister();
	DLSS_API UClass* Z_Construct_UClass_UDLSSSettings();
// End Cross Module References
	static UEnum* EDLSSSettingOverride_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_DLSS_EDLSSSettingOverride, Z_Construct_UPackage__Script_DLSS(), TEXT("EDLSSSettingOverride"));
		}
		return Singleton;
	}
	template<> DLSS_API UEnum* StaticEnum<EDLSSSettingOverride>()
	{
		return EDLSSSettingOverride_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_EDLSSSettingOverride(EDLSSSettingOverride_StaticEnum, TEXT("/Script/DLSS"), TEXT("EDLSSSettingOverride"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_DLSS_EDLSSSettingOverride_Hash() { return 3522351107U; }
	UEnum* Z_Construct_UEnum_DLSS_EDLSSSettingOverride()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_DLSS();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("EDLSSSettingOverride"), 0, Get_Z_Construct_UEnum_DLSS_EDLSSSettingOverride_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "EDLSSSettingOverride::Enabled", (int64)EDLSSSettingOverride::Enabled },
				{ "EDLSSSettingOverride::Disabled", (int64)EDLSSSettingOverride::Disabled },
				{ "EDLSSSettingOverride::UseProjectSettings", (int64)EDLSSSettingOverride::UseProjectSettings },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "Disabled.DisplayName", "False" },
				{ "Disabled.Name", "EDLSSSettingOverride::Disabled" },
				{ "Enabled.DisplayName", "True" },
				{ "Enabled.Name", "EDLSSSettingOverride::Enabled" },
				{ "ModuleRelativePath", "Public/DLSSSettings.h" },
				{ "UseProjectSettings.DisplayName", "Use project settings" },
				{ "UseProjectSettings.Name", "EDLSSSettingOverride::UseProjectSettings" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_DLSS,
				nullptr,
				"EDLSSSettingOverride",
				"EDLSSSettingOverride",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				EEnumFlags::None,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::EnumClass,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
	void UDLSSOverrideSettings::StaticRegisterNativesUDLSSOverrideSettings()
	{
	}
	UClass* Z_Construct_UClass_UDLSSOverrideSettings_NoRegister()
	{
		return UDLSSOverrideSettings::StaticClass();
	}
	struct Z_Construct_UClass_UDLSSOverrideSettings_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_EnableDLSSInEditorViewportsOverride_Underlying;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_EnableDLSSInEditorViewportsOverride_MetaData[];
#endif
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_EnableDLSSInEditorViewportsOverride;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_EnableScreenpercentageManipulationInDLSSEditorViewportsOverride_Underlying;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_EnableScreenpercentageManipulationInDLSSEditorViewportsOverride_MetaData[];
#endif
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_EnableScreenpercentageManipulationInDLSSEditorViewportsOverride;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_EnableDLSSInPlayInEditorViewportsOverride_Underlying;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_EnableDLSSInPlayInEditorViewportsOverride_MetaData[];
#endif
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_EnableDLSSInPlayInEditorViewportsOverride;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bShowDLSSIncompatiblePluginsToolsWarnings_MetaData[];
#endif
		static void NewProp_bShowDLSSIncompatiblePluginsToolsWarnings_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bShowDLSSIncompatiblePluginsToolsWarnings;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_ShowDLSSSDebugOnScreenMessages_Underlying;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ShowDLSSSDebugOnScreenMessages_MetaData[];
#endif
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_ShowDLSSSDebugOnScreenMessages;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UDLSSOverrideSettings_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_DLSS,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UDLSSOverrideSettings_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "DLSSSettings.h" },
		{ "ModuleRelativePath", "Public/DLSSSettings.h" },
	};
#endif
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_UDLSSOverrideSettings_Statics::NewProp_EnableDLSSInEditorViewportsOverride_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UDLSSOverrideSettings_Statics::NewProp_EnableDLSSInEditorViewportsOverride_MetaData[] = {
		{ "Category", "Level Editor - Viewport (Local)" },
		{ "Comment", "/** This enables DLSS in editor viewports. Saved to local user config only.*/" },
		{ "DisplayName", "Enable DLSS to be turned on in Editor viewports" },
		{ "ModuleRelativePath", "Public/DLSSSettings.h" },
		{ "ToolTip", "This enables DLSS in editor viewports. Saved to local user config only." },
	};
#endif
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UDLSSOverrideSettings_Statics::NewProp_EnableDLSSInEditorViewportsOverride = { "EnableDLSSInEditorViewportsOverride", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UDLSSOverrideSettings, EnableDLSSInEditorViewportsOverride), Z_Construct_UEnum_DLSS_EDLSSSettingOverride, METADATA_PARAMS(Z_Construct_UClass_UDLSSOverrideSettings_Statics::NewProp_EnableDLSSInEditorViewportsOverride_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UDLSSOverrideSettings_Statics::NewProp_EnableDLSSInEditorViewportsOverride_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_UDLSSOverrideSettings_Statics::NewProp_EnableScreenpercentageManipulationInDLSSEditorViewportsOverride_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UDLSSOverrideSettings_Statics::NewProp_EnableScreenpercentageManipulationInDLSSEditorViewportsOverride_MetaData[] = {
		{ "Category", "Level Editor - Viewport (Local)" },
		{ "Comment", "/** This setting enables adjusting the screenpercentage directly in the editor, outside of the optimized DLSS quality modes. Saved to local user config only.*/" },
		{ "DisplayName", "Enable Screenpercentage Manipulation in DLSS Editor Viewports" },
		{ "ModuleRelativePath", "Public/DLSSSettings.h" },
		{ "ToolTip", "This setting enables adjusting the screenpercentage directly in the editor, outside of the optimized DLSS quality modes. Saved to local user config only." },
	};
#endif
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UDLSSOverrideSettings_Statics::NewProp_EnableScreenpercentageManipulationInDLSSEditorViewportsOverride = { "EnableScreenpercentageManipulationInDLSSEditorViewportsOverride", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UDLSSOverrideSettings, EnableScreenpercentageManipulationInDLSSEditorViewportsOverride), Z_Construct_UEnum_DLSS_EDLSSSettingOverride, METADATA_PARAMS(Z_Construct_UClass_UDLSSOverrideSettings_Statics::NewProp_EnableScreenpercentageManipulationInDLSSEditorViewportsOverride_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UDLSSOverrideSettings_Statics::NewProp_EnableScreenpercentageManipulationInDLSSEditorViewportsOverride_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_UDLSSOverrideSettings_Statics::NewProp_EnableDLSSInPlayInEditorViewportsOverride_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UDLSSOverrideSettings_Statics::NewProp_EnableDLSSInPlayInEditorViewportsOverride_MetaData[] = {
		{ "Category", "Level Editor - Viewport (Local)" },
		{ "Comment", "/** This enables DLSS in play in editor viewports. Saved to local user config only. */" },
		{ "DisplayName", "Enable DLSS in Play In Editor viewports" },
		{ "ModuleRelativePath", "Public/DLSSSettings.h" },
		{ "ToolTip", "This enables DLSS in play in editor viewports. Saved to local user config only." },
	};
#endif
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UDLSSOverrideSettings_Statics::NewProp_EnableDLSSInPlayInEditorViewportsOverride = { "EnableDLSSInPlayInEditorViewportsOverride", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UDLSSOverrideSettings, EnableDLSSInPlayInEditorViewportsOverride), Z_Construct_UEnum_DLSS_EDLSSSettingOverride, METADATA_PARAMS(Z_Construct_UClass_UDLSSOverrideSettings_Statics::NewProp_EnableDLSSInPlayInEditorViewportsOverride_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UDLSSOverrideSettings_Statics::NewProp_EnableDLSSInPlayInEditorViewportsOverride_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UDLSSOverrideSettings_Statics::NewProp_bShowDLSSIncompatiblePluginsToolsWarnings_MetaData[] = {
		{ "Category", "Editor (Local)" },
		{ "Comment", "/** This enables warnings about plugins & tools that are incompatible with DLSS in the editor. Saved to local user config only. */" },
		{ "DisplayName", "Warn about incompatible plugins and tools" },
		{ "ModuleRelativePath", "Public/DLSSSettings.h" },
		{ "ToolTip", "This enables warnings about plugins & tools that are incompatible with DLSS in the editor. Saved to local user config only." },
	};
#endif
	void Z_Construct_UClass_UDLSSOverrideSettings_Statics::NewProp_bShowDLSSIncompatiblePluginsToolsWarnings_SetBit(void* Obj)
	{
		((UDLSSOverrideSettings*)Obj)->bShowDLSSIncompatiblePluginsToolsWarnings = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UDLSSOverrideSettings_Statics::NewProp_bShowDLSSIncompatiblePluginsToolsWarnings = { "bShowDLSSIncompatiblePluginsToolsWarnings", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UDLSSOverrideSettings), &Z_Construct_UClass_UDLSSOverrideSettings_Statics::NewProp_bShowDLSSIncompatiblePluginsToolsWarnings_SetBit, METADATA_PARAMS(Z_Construct_UClass_UDLSSOverrideSettings_Statics::NewProp_bShowDLSSIncompatiblePluginsToolsWarnings_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UDLSSOverrideSettings_Statics::NewProp_bShowDLSSIncompatiblePluginsToolsWarnings_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_UDLSSOverrideSettings_Statics::NewProp_ShowDLSSSDebugOnScreenMessages_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UDLSSOverrideSettings_Statics::NewProp_ShowDLSSSDebugOnScreenMessages_MetaData[] = {
		{ "Category", "Editor (Local)" },
		{ "Comment", "/** This enables on screen warnings and errors about DLSS  */" },
		{ "DisplayName", "Show various DLSS on screen debug messages" },
		{ "ModuleRelativePath", "Public/DLSSSettings.h" },
		{ "ToolTip", "This enables on screen warnings and errors about DLSS" },
	};
#endif
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UDLSSOverrideSettings_Statics::NewProp_ShowDLSSSDebugOnScreenMessages = { "ShowDLSSSDebugOnScreenMessages", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UDLSSOverrideSettings, ShowDLSSSDebugOnScreenMessages), Z_Construct_UEnum_DLSS_EDLSSSettingOverride, METADATA_PARAMS(Z_Construct_UClass_UDLSSOverrideSettings_Statics::NewProp_ShowDLSSSDebugOnScreenMessages_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UDLSSOverrideSettings_Statics::NewProp_ShowDLSSSDebugOnScreenMessages_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UDLSSOverrideSettings_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDLSSOverrideSettings_Statics::NewProp_EnableDLSSInEditorViewportsOverride_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDLSSOverrideSettings_Statics::NewProp_EnableDLSSInEditorViewportsOverride,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDLSSOverrideSettings_Statics::NewProp_EnableScreenpercentageManipulationInDLSSEditorViewportsOverride_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDLSSOverrideSettings_Statics::NewProp_EnableScreenpercentageManipulationInDLSSEditorViewportsOverride,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDLSSOverrideSettings_Statics::NewProp_EnableDLSSInPlayInEditorViewportsOverride_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDLSSOverrideSettings_Statics::NewProp_EnableDLSSInPlayInEditorViewportsOverride,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDLSSOverrideSettings_Statics::NewProp_bShowDLSSIncompatiblePluginsToolsWarnings,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDLSSOverrideSettings_Statics::NewProp_ShowDLSSSDebugOnScreenMessages_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDLSSOverrideSettings_Statics::NewProp_ShowDLSSSDebugOnScreenMessages,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UDLSSOverrideSettings_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDLSSOverrideSettings>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UDLSSOverrideSettings_Statics::ClassParams = {
		&UDLSSOverrideSettings::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UDLSSOverrideSettings_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UDLSSOverrideSettings_Statics::PropPointers),
		0,
		0x001000E4u,
		METADATA_PARAMS(Z_Construct_UClass_UDLSSOverrideSettings_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UDLSSOverrideSettings_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UDLSSOverrideSettings()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UDLSSOverrideSettings_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UDLSSOverrideSettings, 2893090765);
	template<> DLSS_API UClass* StaticClass<UDLSSOverrideSettings>()
	{
		return UDLSSOverrideSettings::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UDLSSOverrideSettings(Z_Construct_UClass_UDLSSOverrideSettings, &UDLSSOverrideSettings::StaticClass, TEXT("/Script/DLSS"), TEXT("UDLSSOverrideSettings"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UDLSSOverrideSettings);
	void UDLSSSettings::StaticRegisterNativesUDLSSSettings()
	{
	}
	UClass* Z_Construct_UClass_UDLSSSettings_NoRegister()
	{
		return UDLSSSettings::StaticClass();
	}
	struct Z_Construct_UClass_UDLSSSettings_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bEnableDLSSD3D12_MetaData[];
#endif
		static void NewProp_bEnableDLSSD3D12_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bEnableDLSSD3D12;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bEnableDLSSD3D11_MetaData[];
#endif
		static void NewProp_bEnableDLSSD3D11_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bEnableDLSSD3D11;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bEnableDLSSVulkan_MetaData[];
#endif
		static void NewProp_bEnableDLSSVulkan_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bEnableDLSSVulkan;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bEnableDLSSInEditorViewports_MetaData[];
#endif
		static void NewProp_bEnableDLSSInEditorViewports_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bEnableDLSSInEditorViewports;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bEnableScreenpercentageManipulationInDLSSEditorViewports_MetaData[];
#endif
		static void NewProp_bEnableScreenpercentageManipulationInDLSSEditorViewports_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bEnableScreenpercentageManipulationInDLSSEditorViewports;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bEnableDLSSInPlayInEditorViewports_MetaData[];
#endif
		static void NewProp_bEnableDLSSInPlayInEditorViewports_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bEnableDLSSInPlayInEditorViewports;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bShowDLSSSDebugOnScreenMessages_MetaData[];
#endif
		static void NewProp_bShowDLSSSDebugOnScreenMessages_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bShowDLSSSDebugOnScreenMessages;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_GenericDLSSBinaryPath_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_GenericDLSSBinaryPath;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bGenericDLSSBinaryExists_MetaData[];
#endif
		static void NewProp_bGenericDLSSBinaryExists_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bGenericDLSSBinaryExists;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_NVIDIANGXApplicationId_MetaData[];
#endif
		static const UE4CodeGen_Private::FUInt32PropertyParams NewProp_NVIDIANGXApplicationId;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CustomDLSSBinaryPath_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_CustomDLSSBinaryPath;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bCustomDLSSBinaryExists_MetaData[];
#endif
		static void NewProp_bCustomDLSSBinaryExists_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bCustomDLSSBinaryExists;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UDLSSSettings_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_DLSS,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UDLSSSettings_Statics::Class_MetaDataParams[] = {
		{ "DisplayName", "NVIDIA DLSS" },
		{ "IncludePath", "DLSSSettings.h" },
		{ "ModuleRelativePath", "Public/DLSSSettings.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bEnableDLSSD3D12_MetaData[] = {
		{ "Category", "Platforms" },
		{ "Comment", "/** Enable DLSS for D3D12, if the driver supports it at runtime */" },
		{ "DisplayName", "Enable DLSS for the D3D12RHI" },
		{ "ModuleRelativePath", "Public/DLSSSettings.h" },
		{ "ToolTip", "Enable DLSS for D3D12, if the driver supports it at runtime" },
	};
#endif
	void Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bEnableDLSSD3D12_SetBit(void* Obj)
	{
		((UDLSSSettings*)Obj)->bEnableDLSSD3D12 = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bEnableDLSSD3D12 = { "bEnableDLSSD3D12", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UDLSSSettings), &Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bEnableDLSSD3D12_SetBit, METADATA_PARAMS(Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bEnableDLSSD3D12_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bEnableDLSSD3D12_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bEnableDLSSD3D11_MetaData[] = {
		{ "Category", "Platforms" },
		{ "Comment", "/** Enable DLSS for D3D11, if the driver supports it at runtime */" },
		{ "DisplayName", "Enable DLSS for the D3D11RHI" },
		{ "ModuleRelativePath", "Public/DLSSSettings.h" },
		{ "ToolTip", "Enable DLSS for D3D11, if the driver supports it at runtime" },
	};
#endif
	void Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bEnableDLSSD3D11_SetBit(void* Obj)
	{
		((UDLSSSettings*)Obj)->bEnableDLSSD3D11 = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bEnableDLSSD3D11 = { "bEnableDLSSD3D11", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UDLSSSettings), &Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bEnableDLSSD3D11_SetBit, METADATA_PARAMS(Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bEnableDLSSD3D11_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bEnableDLSSD3D11_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bEnableDLSSVulkan_MetaData[] = {
		{ "Category", "Platforms" },
		{ "Comment", "/** Enable DLSS for Vulkan, if the driver supports it at runtime */" },
		{ "DisplayName", "Enable DLSS for the VulkanRHI" },
		{ "ModuleRelativePath", "Public/DLSSSettings.h" },
		{ "ToolTip", "Enable DLSS for Vulkan, if the driver supports it at runtime" },
	};
#endif
	void Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bEnableDLSSVulkan_SetBit(void* Obj)
	{
		((UDLSSSettings*)Obj)->bEnableDLSSVulkan = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bEnableDLSSVulkan = { "bEnableDLSSVulkan", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UDLSSSettings), &Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bEnableDLSSVulkan_SetBit, METADATA_PARAMS(Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bEnableDLSSVulkan_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bEnableDLSSVulkan_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bEnableDLSSInEditorViewports_MetaData[] = {
		{ "Category", "Level Editor - Viewport" },
		{ "Comment", "/** This enables DLSS in editor viewports. This project wide setting can be locally overridden in the NVIDIA DLSS (Local) settings.*/" },
		{ "DisplayName", "Enable DLSS to be turned on in Editor viewports" },
		{ "ModuleRelativePath", "Public/DLSSSettings.h" },
		{ "ToolTip", "This enables DLSS in editor viewports. This project wide setting can be locally overridden in the NVIDIA DLSS (Local) settings." },
	};
#endif
	void Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bEnableDLSSInEditorViewports_SetBit(void* Obj)
	{
		((UDLSSSettings*)Obj)->bEnableDLSSInEditorViewports = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bEnableDLSSInEditorViewports = { "bEnableDLSSInEditorViewports", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UDLSSSettings), &Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bEnableDLSSInEditorViewports_SetBit, METADATA_PARAMS(Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bEnableDLSSInEditorViewports_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bEnableDLSSInEditorViewports_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bEnableScreenpercentageManipulationInDLSSEditorViewports_MetaData[] = {
		{ "Category", "Level Editor - Viewport" },
		{ "Comment", "/** This setting enables adjusting the screenpercentage directly in the editor, outside of the optimized DLSS quality modes. This project wide setting can be locally overridden in the NVIDIA DLSS (Local) settings.*/" },
		{ "DisplayName", "Enable Screenpercentage Manipulation in DLSS Editor Viewports" },
		{ "ModuleRelativePath", "Public/DLSSSettings.h" },
		{ "ToolTip", "This setting enables adjusting the screenpercentage directly in the editor, outside of the optimized DLSS quality modes. This project wide setting can be locally overridden in the NVIDIA DLSS (Local) settings." },
	};
#endif
	void Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bEnableScreenpercentageManipulationInDLSSEditorViewports_SetBit(void* Obj)
	{
		((UDLSSSettings*)Obj)->bEnableScreenpercentageManipulationInDLSSEditorViewports = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bEnableScreenpercentageManipulationInDLSSEditorViewports = { "bEnableScreenpercentageManipulationInDLSSEditorViewports", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UDLSSSettings), &Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bEnableScreenpercentageManipulationInDLSSEditorViewports_SetBit, METADATA_PARAMS(Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bEnableScreenpercentageManipulationInDLSSEditorViewports_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bEnableScreenpercentageManipulationInDLSSEditorViewports_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bEnableDLSSInPlayInEditorViewports_MetaData[] = {
		{ "Category", "Level Editor - Viewport" },
		{ "Comment", "/** This enables DLSS in play in editor viewports. This project wide setting can be locally overridden in in the NVIDIA DLSS (Local) settings.*/" },
		{ "DisplayName", "Enable DLSS in Play In Editor viewports" },
		{ "ModuleRelativePath", "Public/DLSSSettings.h" },
		{ "ToolTip", "This enables DLSS in play in editor viewports. This project wide setting can be locally overridden in in the NVIDIA DLSS (Local) settings." },
	};
#endif
	void Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bEnableDLSSInPlayInEditorViewports_SetBit(void* Obj)
	{
		((UDLSSSettings*)Obj)->bEnableDLSSInPlayInEditorViewports = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bEnableDLSSInPlayInEditorViewports = { "bEnableDLSSInPlayInEditorViewports", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UDLSSSettings), &Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bEnableDLSSInPlayInEditorViewports_SetBit, METADATA_PARAMS(Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bEnableDLSSInPlayInEditorViewports_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bEnableDLSSInPlayInEditorViewports_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bShowDLSSSDebugOnScreenMessages_MetaData[] = {
		{ "Category", "Level Editor - Viewport" },
		{ "Comment", "/** This enables on screen warnings and errors about DLSS. This project wide setting can be locally overridden in the NVIDIA DLSS (Local) settings. */" },
		{ "DisplayName", "Show various DLSS on screen debug messages" },
		{ "ModuleRelativePath", "Public/DLSSSettings.h" },
		{ "ToolTip", "This enables on screen warnings and errors about DLSS. This project wide setting can be locally overridden in the NVIDIA DLSS (Local) settings." },
	};
#endif
	void Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bShowDLSSSDebugOnScreenMessages_SetBit(void* Obj)
	{
		((UDLSSSettings*)Obj)->bShowDLSSSDebugOnScreenMessages = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bShowDLSSSDebugOnScreenMessages = { "bShowDLSSSDebugOnScreenMessages", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UDLSSSettings), &Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bShowDLSSSDebugOnScreenMessages_SetBit, METADATA_PARAMS(Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bShowDLSSSDebugOnScreenMessages_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bShowDLSSSDebugOnScreenMessages_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UDLSSSettings_Statics::NewProp_GenericDLSSBinaryPath_MetaData[] = {
		{ "Category", "General Settings" },
		{ "Comment", "/** This is part of the DLSS plugin and used by most projects*/" },
		{ "DisplayName", "Generic DLSS Binary Path" },
		{ "ModuleRelativePath", "Public/DLSSSettings.h" },
		{ "ToolTip", "This is part of the DLSS plugin and used by most projects" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UDLSSSettings_Statics::NewProp_GenericDLSSBinaryPath = { "GenericDLSSBinaryPath", nullptr, (EPropertyFlags)0x0010000000024001, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UDLSSSettings, GenericDLSSBinaryPath), METADATA_PARAMS(Z_Construct_UClass_UDLSSSettings_Statics::NewProp_GenericDLSSBinaryPath_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UDLSSSettings_Statics::NewProp_GenericDLSSBinaryPath_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bGenericDLSSBinaryExists_MetaData[] = {
		{ "Category", "General Settings" },
		{ "DisplayName", "Exists" },
		{ "ModuleRelativePath", "Public/DLSSSettings.h" },
	};
#endif
	void Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bGenericDLSSBinaryExists_SetBit(void* Obj)
	{
		((UDLSSSettings*)Obj)->bGenericDLSSBinaryExists = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bGenericDLSSBinaryExists = { "bGenericDLSSBinaryExists", nullptr, (EPropertyFlags)0x0010000000024001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UDLSSSettings), &Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bGenericDLSSBinaryExists_SetBit, METADATA_PARAMS(Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bGenericDLSSBinaryExists_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bGenericDLSSBinaryExists_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UDLSSSettings_Statics::NewProp_NVIDIANGXApplicationId_MetaData[] = {
		{ "Category", "General Settings" },
		{ "Comment", "/** By default the DLSS plugin uses the UE4 Project ID to initalize DLSS. In some cases NVIDIA might provide a separate NVIDIA Application ID, which should be put here. Please refer to https://developer.nvidia.com/dlss for details*/" },
		{ "DisplayName", "NVIDIA NGX Application ID" },
		{ "ModuleRelativePath", "Public/DLSSSettings.h" },
		{ "ToolTip", "By default the DLSS plugin uses the UE4 Project ID to initalize DLSS. In some cases NVIDIA might provide a separate NVIDIA Application ID, which should be put here. Please refer to https://developer.nvidia.com/dlss for details" },
	};
#endif
	const UE4CodeGen_Private::FUInt32PropertyParams Z_Construct_UClass_UDLSSSettings_Statics::NewProp_NVIDIANGXApplicationId = { "NVIDIANGXApplicationId", nullptr, (EPropertyFlags)0x0010040000004001, UE4CodeGen_Private::EPropertyGenFlags::UInt32, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UDLSSSettings, NVIDIANGXApplicationId), METADATA_PARAMS(Z_Construct_UClass_UDLSSSettings_Statics::NewProp_NVIDIANGXApplicationId_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UDLSSSettings_Statics::NewProp_NVIDIANGXApplicationId_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UDLSSSettings_Statics::NewProp_CustomDLSSBinaryPath_MetaData[] = {
		{ "Category", "General Settings" },
		{ "Comment", "/** In some cases NVIDIA might provide a project specific DLSS binary for your project. Please refer to https://developer.nvidia.com/dlss for details*/" },
		{ "DisplayName", "Custom DLSS Binary Path" },
		{ "ModuleRelativePath", "Public/DLSSSettings.h" },
		{ "ToolTip", "In some cases NVIDIA might provide a project specific DLSS binary for your project. Please refer to https://developer.nvidia.com/dlss for details" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UDLSSSettings_Statics::NewProp_CustomDLSSBinaryPath = { "CustomDLSSBinaryPath", nullptr, (EPropertyFlags)0x0010040000024001, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UDLSSSettings, CustomDLSSBinaryPath), METADATA_PARAMS(Z_Construct_UClass_UDLSSSettings_Statics::NewProp_CustomDLSSBinaryPath_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UDLSSSettings_Statics::NewProp_CustomDLSSBinaryPath_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bCustomDLSSBinaryExists_MetaData[] = {
		{ "Category", "General Settings" },
		{ "DisplayName", "Exists" },
		{ "ModuleRelativePath", "Public/DLSSSettings.h" },
	};
#endif
	void Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bCustomDLSSBinaryExists_SetBit(void* Obj)
	{
		((UDLSSSettings*)Obj)->bCustomDLSSBinaryExists = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bCustomDLSSBinaryExists = { "bCustomDLSSBinaryExists", nullptr, (EPropertyFlags)0x0010040000024001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UDLSSSettings), &Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bCustomDLSSBinaryExists_SetBit, METADATA_PARAMS(Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bCustomDLSSBinaryExists_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bCustomDLSSBinaryExists_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UDLSSSettings_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bEnableDLSSD3D12,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bEnableDLSSD3D11,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bEnableDLSSVulkan,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bEnableDLSSInEditorViewports,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bEnableScreenpercentageManipulationInDLSSEditorViewports,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bEnableDLSSInPlayInEditorViewports,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bShowDLSSSDebugOnScreenMessages,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDLSSSettings_Statics::NewProp_GenericDLSSBinaryPath,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bGenericDLSSBinaryExists,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDLSSSettings_Statics::NewProp_NVIDIANGXApplicationId,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDLSSSettings_Statics::NewProp_CustomDLSSBinaryPath,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDLSSSettings_Statics::NewProp_bCustomDLSSBinaryExists,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UDLSSSettings_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDLSSSettings>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UDLSSSettings_Statics::ClassParams = {
		&UDLSSSettings::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UDLSSSettings_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UDLSSSettings_Statics::PropPointers),
		0,
		0x001000A6u,
		METADATA_PARAMS(Z_Construct_UClass_UDLSSSettings_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UDLSSSettings_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UDLSSSettings()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UDLSSSettings_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UDLSSSettings, 3892250485);
	template<> DLSS_API UClass* StaticClass<UDLSSSettings>()
	{
		return UDLSSSettings::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UDLSSSettings(Z_Construct_UClass_UDLSSSettings, &UDLSSSettings::StaticClass, TEXT("/Script/DLSS"), TEXT("UDLSSSettings"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UDLSSSettings);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
