// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DLSSBlueprint/Public/DLSSLibrary.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeDLSSLibrary() {}
// Cross Module References
	DLSSBLUEPRINT_API UEnum* Z_Construct_UEnum_DLSSBlueprint_UDLSSMode();
	UPackage* Z_Construct_UPackage__Script_DLSSBlueprint();
	DLSSBLUEPRINT_API UEnum* Z_Construct_UEnum_DLSSBlueprint_UDLSSSupport();
	DLSSBLUEPRINT_API UClass* Z_Construct_UClass_UDLSSLibrary_NoRegister();
	DLSSBLUEPRINT_API UClass* Z_Construct_UClass_UDLSSLibrary();
	ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
// End Cross Module References
	static UEnum* UDLSSMode_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_DLSSBlueprint_UDLSSMode, Z_Construct_UPackage__Script_DLSSBlueprint(), TEXT("UDLSSMode"));
		}
		return Singleton;
	}
	template<> DLSSBLUEPRINT_API UEnum* StaticEnum<UDLSSMode>()
	{
		return UDLSSMode_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_UDLSSMode(UDLSSMode_StaticEnum, TEXT("/Script/DLSSBlueprint"), TEXT("UDLSSMode"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_DLSSBlueprint_UDLSSMode_Hash() { return 3219273498U; }
	UEnum* Z_Construct_UEnum_DLSSBlueprint_UDLSSMode()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_DLSSBlueprint();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("UDLSSMode"), 0, Get_Z_Construct_UEnum_DLSSBlueprint_UDLSSMode_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "UDLSSMode::Off", (int64)UDLSSMode::Off },
				{ "UDLSSMode::UltraPerformance", (int64)UDLSSMode::UltraPerformance },
				{ "UDLSSMode::Performance", (int64)UDLSSMode::Performance },
				{ "UDLSSMode::Balanced", (int64)UDLSSMode::Balanced },
				{ "UDLSSMode::Quality", (int64)UDLSSMode::Quality },
				{ "UDLSSMode::UltraQuality", (int64)UDLSSMode::UltraQuality },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "Balanced.DisplayName", "Balanced" },
				{ "Balanced.Name", "UDLSSMode::Balanced" },
				{ "BlueprintType", "true" },
				{ "ModuleRelativePath", "Public/DLSSLibrary.h" },
				{ "Off.DisplayName", "Off" },
				{ "Off.Name", "UDLSSMode::Off" },
				{ "Performance.DisplayName", "Performance" },
				{ "Performance.Name", "UDLSSMode::Performance" },
				{ "Quality.DisplayName", "Quality" },
				{ "Quality.Name", "UDLSSMode::Quality" },
				{ "UltraPerformance.DisplayName", "Ultra Performance" },
				{ "UltraPerformance.Name", "UDLSSMode::UltraPerformance" },
				{ "UltraQuality.DisplayName", "Ultra Quality" },
				{ "UltraQuality.Name", "UDLSSMode::UltraQuality" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_DLSSBlueprint,
				nullptr,
				"UDLSSMode",
				"UDLSSMode",
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
	static UEnum* UDLSSSupport_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_DLSSBlueprint_UDLSSSupport, Z_Construct_UPackage__Script_DLSSBlueprint(), TEXT("UDLSSSupport"));
		}
		return Singleton;
	}
	template<> DLSSBLUEPRINT_API UEnum* StaticEnum<UDLSSSupport>()
	{
		return UDLSSSupport_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_UDLSSSupport(UDLSSSupport_StaticEnum, TEXT("/Script/DLSSBlueprint"), TEXT("UDLSSSupport"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_DLSSBlueprint_UDLSSSupport_Hash() { return 708259637U; }
	UEnum* Z_Construct_UEnum_DLSSBlueprint_UDLSSSupport()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_DLSSBlueprint();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("UDLSSSupport"), 0, Get_Z_Construct_UEnum_DLSSBlueprint_UDLSSSupport_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "UDLSSSupport::Supported", (int64)UDLSSSupport::Supported },
				{ "UDLSSSupport::NotSupported", (int64)UDLSSSupport::NotSupported },
				{ "UDLSSSupport::NotSupportedIncompatibleHardware", (int64)UDLSSSupport::NotSupportedIncompatibleHardware },
				{ "UDLSSSupport::NotSupportedDriverOutOfDate", (int64)UDLSSSupport::NotSupportedDriverOutOfDate },
				{ "UDLSSSupport::NotSupportedOperatingSystemOutOfDate", (int64)UDLSSSupport::NotSupportedOperatingSystemOutOfDate },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "BlueprintType", "true" },
				{ "ModuleRelativePath", "Public/DLSSLibrary.h" },
				{ "NotSupported.DisplayName", "Not Supported" },
				{ "NotSupported.Name", "UDLSSSupport::NotSupported" },
				{ "NotSupportedDriverOutOfDate.DisplayName", "Driver Out of Date" },
				{ "NotSupportedDriverOutOfDate.Name", "UDLSSSupport::NotSupportedDriverOutOfDate" },
				{ "NotSupportedDriverOutOfDate.ToolTip", "The driver is outdated. Also see GetDLSSMinimumDriverVersion" },
				{ "NotSupportedIncompatibleHardware.DisplayName", "Incompatible Hardware" },
				{ "NotSupportedIncompatibleHardware.Name", "UDLSSSupport::NotSupportedIncompatibleHardware" },
				{ "NotSupportedIncompatibleHardware.ToolTip", "DLSS requires an NVIDIA RTX GPU" },
				{ "NotSupportedOperatingSystemOutOfDate.DisplayName", "Operating System Out of Date" },
				{ "NotSupportedOperatingSystemOutOfDate.Name", "UDLSSSupport::NotSupportedOperatingSystemOutOfDate" },
				{ "NotSupportedOperatingSystemOutOfDate.ToolTip", "DLSS requires at least Windows 10 Fall 2017 Creators Update 64-bit, (v1709, build 16299)" },
				{ "Supported.DisplayName", "Supported" },
				{ "Supported.Name", "UDLSSSupport::Supported" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_DLSSBlueprint,
				nullptr,
				"UDLSSSupport",
				"UDLSSSupport",
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
	DEFINE_FUNCTION(UDLSSLibrary::execGetDLSSSharpness)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(float*)Z_Param__Result=UDLSSLibrary::GetDLSSSharpness();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UDLSSLibrary::execSetDLSSSharpness)
	{
		P_GET_PROPERTY(FFloatProperty,Z_Param_Sharpness);
		P_FINISH;
		P_NATIVE_BEGIN;
		UDLSSLibrary::SetDLSSSharpness(Z_Param_Sharpness);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UDLSSLibrary::execGetDLSSMode)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(UDLSSMode*)Z_Param__Result=UDLSSLibrary::GetDLSSMode();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UDLSSLibrary::execSetDLSSMode)
	{
		P_GET_ENUM(UDLSSMode,Z_Param_DLSSMode);
		P_FINISH;
		P_NATIVE_BEGIN;
		UDLSSLibrary::SetDLSSMode(UDLSSMode(Z_Param_DLSSMode));
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UDLSSLibrary::execGetDLSSScreenPercentageRange)
	{
		P_GET_PROPERTY_REF(FFloatProperty,Z_Param_Out_MinScreenPercentage);
		P_GET_PROPERTY_REF(FFloatProperty,Z_Param_Out_MaxScreenPercentage);
		P_FINISH;
		P_NATIVE_BEGIN;
		UDLSSLibrary::GetDLSSScreenPercentageRange(Z_Param_Out_MinScreenPercentage,Z_Param_Out_MaxScreenPercentage);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UDLSSLibrary::execGetDLSSModeInformation)
	{
		P_GET_ENUM(UDLSSMode,Z_Param_DLSSMode);
		P_GET_UBOOL_REF(Z_Param_Out_bIsSupported);
		P_GET_PROPERTY_REF(FFloatProperty,Z_Param_Out_OptimalScreenPercentage);
		P_GET_UBOOL_REF(Z_Param_Out_bIsFixedScreenPercentage);
		P_GET_PROPERTY_REF(FFloatProperty,Z_Param_Out_MinScreenPercentage);
		P_GET_PROPERTY_REF(FFloatProperty,Z_Param_Out_MaxScreenPercentage);
		P_GET_PROPERTY_REF(FFloatProperty,Z_Param_Out_OptimalSharpness);
		P_FINISH;
		P_NATIVE_BEGIN;
		UDLSSLibrary::GetDLSSModeInformation(UDLSSMode(Z_Param_DLSSMode),Z_Param_Out_bIsSupported,Z_Param_Out_OptimalScreenPercentage,Z_Param_Out_bIsFixedScreenPercentage,Z_Param_Out_MinScreenPercentage,Z_Param_Out_MaxScreenPercentage,Z_Param_Out_OptimalSharpness);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UDLSSLibrary::execGetSupportedDLSSModes)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<UDLSSMode>*)Z_Param__Result=UDLSSLibrary::GetSupportedDLSSModes();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UDLSSLibrary::execIsDLSSModeSupported)
	{
		P_GET_ENUM(UDLSSMode,Z_Param_DLSSMode);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=UDLSSLibrary::IsDLSSModeSupported(UDLSSMode(Z_Param_DLSSMode));
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UDLSSLibrary::execGetDLSSMinimumDriverVersion)
	{
		P_GET_PROPERTY_REF(FIntProperty,Z_Param_Out_MinDriverVersionMajor);
		P_GET_PROPERTY_REF(FIntProperty,Z_Param_Out_MinDriverVersionMinor);
		P_FINISH;
		P_NATIVE_BEGIN;
		UDLSSLibrary::GetDLSSMinimumDriverVersion(Z_Param_Out_MinDriverVersionMajor,Z_Param_Out_MinDriverVersionMinor);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UDLSSLibrary::execQueryDLSSSupport)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(UDLSSSupport*)Z_Param__Result=UDLSSLibrary::QueryDLSSSupport();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UDLSSLibrary::execIsDLSSSupported)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=UDLSSLibrary::IsDLSSSupported();
		P_NATIVE_END;
	}
	void UDLSSLibrary::StaticRegisterNativesUDLSSLibrary()
	{
		UClass* Class = UDLSSLibrary::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "GetDLSSMinimumDriverVersion", &UDLSSLibrary::execGetDLSSMinimumDriverVersion },
			{ "GetDLSSMode", &UDLSSLibrary::execGetDLSSMode },
			{ "GetDLSSModeInformation", &UDLSSLibrary::execGetDLSSModeInformation },
			{ "GetDLSSScreenPercentageRange", &UDLSSLibrary::execGetDLSSScreenPercentageRange },
			{ "GetDLSSSharpness", &UDLSSLibrary::execGetDLSSSharpness },
			{ "GetSupportedDLSSModes", &UDLSSLibrary::execGetSupportedDLSSModes },
			{ "IsDLSSModeSupported", &UDLSSLibrary::execIsDLSSModeSupported },
			{ "IsDLSSSupported", &UDLSSLibrary::execIsDLSSSupported },
			{ "QueryDLSSSupport", &UDLSSLibrary::execQueryDLSSSupport },
			{ "SetDLSSMode", &UDLSSLibrary::execSetDLSSMode },
			{ "SetDLSSSharpness", &UDLSSLibrary::execSetDLSSSharpness },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UDLSSLibrary_GetDLSSMinimumDriverVersion_Statics
	{
		struct DLSSLibrary_eventGetDLSSMinimumDriverVersion_Parms
		{
			int32 MinDriverVersionMajor;
			int32 MinDriverVersionMinor;
		};
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_MinDriverVersionMajor;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_MinDriverVersionMinor;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UDLSSLibrary_GetDLSSMinimumDriverVersion_Statics::NewProp_MinDriverVersionMajor = { "MinDriverVersionMajor", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(DLSSLibrary_eventGetDLSSMinimumDriverVersion_Parms, MinDriverVersionMajor), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UDLSSLibrary_GetDLSSMinimumDriverVersion_Statics::NewProp_MinDriverVersionMinor = { "MinDriverVersionMinor", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(DLSSLibrary_eventGetDLSSMinimumDriverVersion_Parms, MinDriverVersionMinor), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UDLSSLibrary_GetDLSSMinimumDriverVersion_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UDLSSLibrary_GetDLSSMinimumDriverVersion_Statics::NewProp_MinDriverVersionMajor,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UDLSSLibrary_GetDLSSMinimumDriverVersion_Statics::NewProp_MinDriverVersionMinor,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UDLSSLibrary_GetDLSSMinimumDriverVersion_Statics::Function_MetaDataParams[] = {
		{ "Category", "DLSS" },
		{ "Comment", "/** If QueryDLSSSupport returns \"NotSupportedDriverOutOfDate\", then MinDriverVersionMajor and MinDriverVersionMinor contains the required driver version.*/" },
		{ "DisplayName", "Get DLSS Minimum DriverVersion" },
		{ "ModuleRelativePath", "Public/DLSSLibrary.h" },
		{ "ToolTip", "If QueryDLSSSupport returns \"NotSupportedDriverOutOfDate\", then MinDriverVersionMajor and MinDriverVersionMinor contains the required driver version." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UDLSSLibrary_GetDLSSMinimumDriverVersion_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UDLSSLibrary, nullptr, "GetDLSSMinimumDriverVersion", nullptr, nullptr, sizeof(DLSSLibrary_eventGetDLSSMinimumDriverVersion_Parms), Z_Construct_UFunction_UDLSSLibrary_GetDLSSMinimumDriverVersion_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UDLSSLibrary_GetDLSSMinimumDriverVersion_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422403, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UDLSSLibrary_GetDLSSMinimumDriverVersion_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UDLSSLibrary_GetDLSSMinimumDriverVersion_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UDLSSLibrary_GetDLSSMinimumDriverVersion()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UDLSSLibrary_GetDLSSMinimumDriverVersion_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UDLSSLibrary_GetDLSSMode_Statics
	{
		struct DLSSLibrary_eventGetDLSSMode_Parms
		{
			UDLSSMode ReturnValue;
		};
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_ReturnValue_Underlying;
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UDLSSLibrary_GetDLSSMode_Statics::NewProp_ReturnValue_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UDLSSLibrary_GetDLSSMode_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(DLSSLibrary_eventGetDLSSMode_Parms, ReturnValue), Z_Construct_UEnum_DLSSBlueprint_UDLSSMode, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UDLSSLibrary_GetDLSSMode_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UDLSSLibrary_GetDLSSMode_Statics::NewProp_ReturnValue_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UDLSSLibrary_GetDLSSMode_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UDLSSLibrary_GetDLSSMode_Statics::Function_MetaDataParams[] = {
		{ "Category", "DLSS" },
		{ "Comment", "/* Reads the console variables to infer the current DLSS mode (r.NGX.DLSS.Enable, r.NGX.DLSS.Quality)*/" },
		{ "DisplayName", "Get DLSS Mode" },
		{ "ModuleRelativePath", "Public/DLSSLibrary.h" },
		{ "ToolTip", "Reads the console variables to infer the current DLSS mode (r.NGX.DLSS.Enable, r.NGX.DLSS.Quality)" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UDLSSLibrary_GetDLSSMode_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UDLSSLibrary, nullptr, "GetDLSSMode", nullptr, nullptr, sizeof(DLSSLibrary_eventGetDLSSMode_Parms), Z_Construct_UFunction_UDLSSLibrary_GetDLSSMode_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UDLSSLibrary_GetDLSSMode_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022403, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UDLSSLibrary_GetDLSSMode_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UDLSSLibrary_GetDLSSMode_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UDLSSLibrary_GetDLSSMode()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UDLSSLibrary_GetDLSSMode_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UDLSSLibrary_GetDLSSModeInformation_Statics
	{
		struct DLSSLibrary_eventGetDLSSModeInformation_Parms
		{
			UDLSSMode DLSSMode;
			bool bIsSupported;
			float OptimalScreenPercentage;
			bool bIsFixedScreenPercentage;
			float MinScreenPercentage;
			float MaxScreenPercentage;
			float OptimalSharpness;
		};
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_DLSSMode_Underlying;
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_DLSSMode;
		static void NewProp_bIsSupported_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bIsSupported;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_OptimalScreenPercentage;
		static void NewProp_bIsFixedScreenPercentage_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bIsFixedScreenPercentage;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_MinScreenPercentage;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_MaxScreenPercentage;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_OptimalSharpness;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UDLSSLibrary_GetDLSSModeInformation_Statics::NewProp_DLSSMode_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UDLSSLibrary_GetDLSSModeInformation_Statics::NewProp_DLSSMode = { "DLSSMode", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(DLSSLibrary_eventGetDLSSModeInformation_Parms, DLSSMode), Z_Construct_UEnum_DLSSBlueprint_UDLSSMode, METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_UDLSSLibrary_GetDLSSModeInformation_Statics::NewProp_bIsSupported_SetBit(void* Obj)
	{
		((DLSSLibrary_eventGetDLSSModeInformation_Parms*)Obj)->bIsSupported = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UDLSSLibrary_GetDLSSModeInformation_Statics::NewProp_bIsSupported = { "bIsSupported", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(DLSSLibrary_eventGetDLSSModeInformation_Parms), &Z_Construct_UFunction_UDLSSLibrary_GetDLSSModeInformation_Statics::NewProp_bIsSupported_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UDLSSLibrary_GetDLSSModeInformation_Statics::NewProp_OptimalScreenPercentage = { "OptimalScreenPercentage", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(DLSSLibrary_eventGetDLSSModeInformation_Parms, OptimalScreenPercentage), METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_UDLSSLibrary_GetDLSSModeInformation_Statics::NewProp_bIsFixedScreenPercentage_SetBit(void* Obj)
	{
		((DLSSLibrary_eventGetDLSSModeInformation_Parms*)Obj)->bIsFixedScreenPercentage = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UDLSSLibrary_GetDLSSModeInformation_Statics::NewProp_bIsFixedScreenPercentage = { "bIsFixedScreenPercentage", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(DLSSLibrary_eventGetDLSSModeInformation_Parms), &Z_Construct_UFunction_UDLSSLibrary_GetDLSSModeInformation_Statics::NewProp_bIsFixedScreenPercentage_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UDLSSLibrary_GetDLSSModeInformation_Statics::NewProp_MinScreenPercentage = { "MinScreenPercentage", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(DLSSLibrary_eventGetDLSSModeInformation_Parms, MinScreenPercentage), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UDLSSLibrary_GetDLSSModeInformation_Statics::NewProp_MaxScreenPercentage = { "MaxScreenPercentage", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(DLSSLibrary_eventGetDLSSModeInformation_Parms, MaxScreenPercentage), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UDLSSLibrary_GetDLSSModeInformation_Statics::NewProp_OptimalSharpness = { "OptimalSharpness", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(DLSSLibrary_eventGetDLSSModeInformation_Parms, OptimalSharpness), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UDLSSLibrary_GetDLSSModeInformation_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UDLSSLibrary_GetDLSSModeInformation_Statics::NewProp_DLSSMode_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UDLSSLibrary_GetDLSSModeInformation_Statics::NewProp_DLSSMode,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UDLSSLibrary_GetDLSSModeInformation_Statics::NewProp_bIsSupported,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UDLSSLibrary_GetDLSSModeInformation_Statics::NewProp_OptimalScreenPercentage,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UDLSSLibrary_GetDLSSModeInformation_Statics::NewProp_bIsFixedScreenPercentage,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UDLSSLibrary_GetDLSSModeInformation_Statics::NewProp_MinScreenPercentage,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UDLSSLibrary_GetDLSSModeInformation_Statics::NewProp_MaxScreenPercentage,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UDLSSLibrary_GetDLSSModeInformation_Statics::NewProp_OptimalSharpness,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UDLSSLibrary_GetDLSSModeInformation_Statics::Function_MetaDataParams[] = {
		{ "Category", "DLSS" },
		{ "Comment", "/** Provides additional details (such as screen percentage ranges) about a DLSS mode*/" },
		{ "DisplayName", "Get DLSS Mode Information" },
		{ "ModuleRelativePath", "Public/DLSSLibrary.h" },
		{ "ToolTip", "Provides additional details (such as screen percentage ranges) about a DLSS mode" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UDLSSLibrary_GetDLSSModeInformation_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UDLSSLibrary, nullptr, "GetDLSSModeInformation", nullptr, nullptr, sizeof(DLSSLibrary_eventGetDLSSModeInformation_Parms), Z_Construct_UFunction_UDLSSLibrary_GetDLSSModeInformation_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UDLSSLibrary_GetDLSSModeInformation_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422403, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UDLSSLibrary_GetDLSSModeInformation_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UDLSSLibrary_GetDLSSModeInformation_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UDLSSLibrary_GetDLSSModeInformation()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UDLSSLibrary_GetDLSSModeInformation_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UDLSSLibrary_GetDLSSScreenPercentageRange_Statics
	{
		struct DLSSLibrary_eventGetDLSSScreenPercentageRange_Parms
		{
			float MinScreenPercentage;
			float MaxScreenPercentage;
		};
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_MinScreenPercentage;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_MaxScreenPercentage;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UDLSSLibrary_GetDLSSScreenPercentageRange_Statics::NewProp_MinScreenPercentage = { "MinScreenPercentage", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(DLSSLibrary_eventGetDLSSScreenPercentageRange_Parms, MinScreenPercentage), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UDLSSLibrary_GetDLSSScreenPercentageRange_Statics::NewProp_MaxScreenPercentage = { "MaxScreenPercentage", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(DLSSLibrary_eventGetDLSSScreenPercentageRange_Parms, MaxScreenPercentage), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UDLSSLibrary_GetDLSSScreenPercentageRange_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UDLSSLibrary_GetDLSSScreenPercentageRange_Statics::NewProp_MinScreenPercentage,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UDLSSLibrary_GetDLSSScreenPercentageRange_Statics::NewProp_MaxScreenPercentage,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UDLSSLibrary_GetDLSSScreenPercentageRange_Statics::Function_MetaDataParams[] = {
		{ "Category", "DLSS" },
		{ "Comment", "/** The global screen percentage range that DLSS supports. Excludes DLSS modes with fixed screen percentage. Also see GetDLSSModeInformation*/" },
		{ "DisplayName", "Get DLSS Screenpercentage Range" },
		{ "ModuleRelativePath", "Public/DLSSLibrary.h" },
		{ "ToolTip", "The global screen percentage range that DLSS supports. Excludes DLSS modes with fixed screen percentage. Also see GetDLSSModeInformation" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UDLSSLibrary_GetDLSSScreenPercentageRange_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UDLSSLibrary, nullptr, "GetDLSSScreenPercentageRange", nullptr, nullptr, sizeof(DLSSLibrary_eventGetDLSSScreenPercentageRange_Parms), Z_Construct_UFunction_UDLSSLibrary_GetDLSSScreenPercentageRange_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UDLSSLibrary_GetDLSSScreenPercentageRange_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422403, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UDLSSLibrary_GetDLSSScreenPercentageRange_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UDLSSLibrary_GetDLSSScreenPercentageRange_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UDLSSLibrary_GetDLSSScreenPercentageRange()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UDLSSLibrary_GetDLSSScreenPercentageRange_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UDLSSLibrary_GetDLSSSharpness_Statics
	{
		struct DLSSLibrary_eventGetDLSSSharpness_Parms
		{
			float ReturnValue;
		};
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UDLSSLibrary_GetDLSSSharpness_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(DLSSLibrary_eventGetDLSSSharpness_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UDLSSLibrary_GetDLSSSharpness_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UDLSSLibrary_GetDLSSSharpness_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UDLSSLibrary_GetDLSSSharpness_Statics::Function_MetaDataParams[] = {
		{ "Category", "DLSS" },
		{ "Comment", "/*Reads the console variables to infer the current DLSS sharpness (r.NGX.DLSS.Sharpness) */" },
		{ "DisplayName", "Get DLSS Sharpness" },
		{ "ModuleRelativePath", "Public/DLSSLibrary.h" },
		{ "ToolTip", "Reads the console variables to infer the current DLSS sharpness (r.NGX.DLSS.Sharpness)" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UDLSSLibrary_GetDLSSSharpness_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UDLSSLibrary, nullptr, "GetDLSSSharpness", nullptr, nullptr, sizeof(DLSSLibrary_eventGetDLSSSharpness_Parms), Z_Construct_UFunction_UDLSSLibrary_GetDLSSSharpness_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UDLSSLibrary_GetDLSSSharpness_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022403, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UDLSSLibrary_GetDLSSSharpness_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UDLSSLibrary_GetDLSSSharpness_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UDLSSLibrary_GetDLSSSharpness()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UDLSSLibrary_GetDLSSSharpness_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UDLSSLibrary_GetSupportedDLSSModes_Statics
	{
		struct DLSSLibrary_eventGetSupportedDLSSModes_Parms
		{
			TArray<UDLSSMode> ReturnValue;
		};
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_ReturnValue_Inner_Underlying;
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_ReturnValue_Inner;
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UDLSSLibrary_GetSupportedDLSSModes_Statics::NewProp_ReturnValue_Inner_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UDLSSLibrary_GetSupportedDLSSModes_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UEnum_DLSSBlueprint_UDLSSMode, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UDLSSLibrary_GetSupportedDLSSModes_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(DLSSLibrary_eventGetSupportedDLSSModes_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UDLSSLibrary_GetSupportedDLSSModes_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UDLSSLibrary_GetSupportedDLSSModes_Statics::NewProp_ReturnValue_Inner_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UDLSSLibrary_GetSupportedDLSSModes_Statics::NewProp_ReturnValue_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UDLSSLibrary_GetSupportedDLSSModes_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UDLSSLibrary_GetSupportedDLSSModes_Statics::Function_MetaDataParams[] = {
		{ "Category", "DLSS" },
		{ "Comment", "/** Retrieves all supported DLSS modes. Can be used to populate UI */" },
		{ "DisplayName", "Get Supported DLSS Modes" },
		{ "ModuleRelativePath", "Public/DLSSLibrary.h" },
		{ "ToolTip", "Retrieves all supported DLSS modes. Can be used to populate UI" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UDLSSLibrary_GetSupportedDLSSModes_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UDLSSLibrary, nullptr, "GetSupportedDLSSModes", nullptr, nullptr, sizeof(DLSSLibrary_eventGetSupportedDLSSModes_Parms), Z_Construct_UFunction_UDLSSLibrary_GetSupportedDLSSModes_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UDLSSLibrary_GetSupportedDLSSModes_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022403, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UDLSSLibrary_GetSupportedDLSSModes_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UDLSSLibrary_GetSupportedDLSSModes_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UDLSSLibrary_GetSupportedDLSSModes()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UDLSSLibrary_GetSupportedDLSSModes_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UDLSSLibrary_IsDLSSModeSupported_Statics
	{
		struct DLSSLibrary_eventIsDLSSModeSupported_Parms
		{
			UDLSSMode DLSSMode;
			bool ReturnValue;
		};
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_DLSSMode_Underlying;
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_DLSSMode;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UDLSSLibrary_IsDLSSModeSupported_Statics::NewProp_DLSSMode_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UDLSSLibrary_IsDLSSModeSupported_Statics::NewProp_DLSSMode = { "DLSSMode", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(DLSSLibrary_eventIsDLSSModeSupported_Parms, DLSSMode), Z_Construct_UEnum_DLSSBlueprint_UDLSSMode, METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_UDLSSLibrary_IsDLSSModeSupported_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DLSSLibrary_eventIsDLSSModeSupported_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UDLSSLibrary_IsDLSSModeSupported_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(DLSSLibrary_eventIsDLSSModeSupported_Parms), &Z_Construct_UFunction_UDLSSLibrary_IsDLSSModeSupported_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UDLSSLibrary_IsDLSSModeSupported_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UDLSSLibrary_IsDLSSModeSupported_Statics::NewProp_DLSSMode_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UDLSSLibrary_IsDLSSModeSupported_Statics::NewProp_DLSSMode,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UDLSSLibrary_IsDLSSModeSupported_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UDLSSLibrary_IsDLSSModeSupported_Statics::Function_MetaDataParams[] = {
		{ "Category", "DLSS" },
		{ "Comment", "/** Checks whether a DLSS mode is supported */" },
		{ "DisplayName", "Is DLSS Mode Supported" },
		{ "ModuleRelativePath", "Public/DLSSLibrary.h" },
		{ "ToolTip", "Checks whether a DLSS mode is supported" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UDLSSLibrary_IsDLSSModeSupported_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UDLSSLibrary, nullptr, "IsDLSSModeSupported", nullptr, nullptr, sizeof(DLSSLibrary_eventIsDLSSModeSupported_Parms), Z_Construct_UFunction_UDLSSLibrary_IsDLSSModeSupported_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UDLSSLibrary_IsDLSSModeSupported_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022403, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UDLSSLibrary_IsDLSSModeSupported_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UDLSSLibrary_IsDLSSModeSupported_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UDLSSLibrary_IsDLSSModeSupported()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UDLSSLibrary_IsDLSSModeSupported_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UDLSSLibrary_IsDLSSSupported_Statics
	{
		struct DLSSLibrary_eventIsDLSSSupported_Parms
		{
			bool ReturnValue;
		};
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UFunction_UDLSSLibrary_IsDLSSSupported_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DLSSLibrary_eventIsDLSSSupported_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UDLSSLibrary_IsDLSSSupported_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(DLSSLibrary_eventIsDLSSSupported_Parms), &Z_Construct_UFunction_UDLSSLibrary_IsDLSSSupported_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UDLSSLibrary_IsDLSSSupported_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UDLSSLibrary_IsDLSSSupported_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UDLSSLibrary_IsDLSSSupported_Statics::Function_MetaDataParams[] = {
		{ "Category", "DLSS" },
		{ "Comment", "/** Checks whether DLSS is supported by the current GPU. Further details can be retrieved via QueryDLSSSupport*/" },
		{ "DisplayName", "Is NVIDIA DLSS Supported" },
		{ "ModuleRelativePath", "Public/DLSSLibrary.h" },
		{ "ToolTip", "Checks whether DLSS is supported by the current GPU. Further details can be retrieved via QueryDLSSSupport" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UDLSSLibrary_IsDLSSSupported_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UDLSSLibrary, nullptr, "IsDLSSSupported", nullptr, nullptr, sizeof(DLSSLibrary_eventIsDLSSSupported_Parms), Z_Construct_UFunction_UDLSSLibrary_IsDLSSSupported_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UDLSSLibrary_IsDLSSSupported_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022403, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UDLSSLibrary_IsDLSSSupported_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UDLSSLibrary_IsDLSSSupported_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UDLSSLibrary_IsDLSSSupported()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UDLSSLibrary_IsDLSSSupported_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UDLSSLibrary_QueryDLSSSupport_Statics
	{
		struct DLSSLibrary_eventQueryDLSSSupport_Parms
		{
			UDLSSSupport ReturnValue;
		};
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_ReturnValue_Underlying;
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UDLSSLibrary_QueryDLSSSupport_Statics::NewProp_ReturnValue_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UDLSSLibrary_QueryDLSSSupport_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(DLSSLibrary_eventQueryDLSSSupport_Parms, ReturnValue), Z_Construct_UEnum_DLSSBlueprint_UDLSSSupport, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UDLSSLibrary_QueryDLSSSupport_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UDLSSLibrary_QueryDLSSSupport_Statics::NewProp_ReturnValue_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UDLSSLibrary_QueryDLSSSupport_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UDLSSLibrary_QueryDLSSSupport_Statics::Function_MetaDataParams[] = {
		{ "Category", "DLSS" },
		{ "Comment", "/** Checks whether DLSS is supported by the current GPU\x09*/" },
		{ "DisplayName", "Query NVIDIA DLSS Support" },
		{ "ModuleRelativePath", "Public/DLSSLibrary.h" },
		{ "ToolTip", "Checks whether DLSS is supported by the current GPU" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UDLSSLibrary_QueryDLSSSupport_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UDLSSLibrary, nullptr, "QueryDLSSSupport", nullptr, nullptr, sizeof(DLSSLibrary_eventQueryDLSSSupport_Parms), Z_Construct_UFunction_UDLSSLibrary_QueryDLSSSupport_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UDLSSLibrary_QueryDLSSSupport_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022403, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UDLSSLibrary_QueryDLSSSupport_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UDLSSLibrary_QueryDLSSSupport_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UDLSSLibrary_QueryDLSSSupport()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UDLSSLibrary_QueryDLSSSupport_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UDLSSLibrary_SetDLSSMode_Statics
	{
		struct DLSSLibrary_eventSetDLSSMode_Parms
		{
			UDLSSMode DLSSMode;
		};
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_DLSSMode_Underlying;
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_DLSSMode;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UDLSSLibrary_SetDLSSMode_Statics::NewProp_DLSSMode_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UDLSSLibrary_SetDLSSMode_Statics::NewProp_DLSSMode = { "DLSSMode", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(DLSSLibrary_eventSetDLSSMode_Parms, DLSSMode), Z_Construct_UEnum_DLSSBlueprint_UDLSSMode, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UDLSSLibrary_SetDLSSMode_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UDLSSLibrary_SetDLSSMode_Statics::NewProp_DLSSMode_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UDLSSLibrary_SetDLSSMode_Statics::NewProp_DLSSMode,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UDLSSLibrary_SetDLSSMode_Statics::Function_MetaDataParams[] = {
		{ "Category", "DLSS" },
		{ "Comment", "/** Sets the console variables to enable/disable DLSS (r.NGX.DLSS.Enable, r.NGX.DLSS.Quality)*/" },
		{ "DisplayName", "Set DLSS Mode" },
		{ "ModuleRelativePath", "Public/DLSSLibrary.h" },
		{ "ToolTip", "Sets the console variables to enable/disable DLSS (r.NGX.DLSS.Enable, r.NGX.DLSS.Quality)" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UDLSSLibrary_SetDLSSMode_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UDLSSLibrary, nullptr, "SetDLSSMode", nullptr, nullptr, sizeof(DLSSLibrary_eventSetDLSSMode_Parms), Z_Construct_UFunction_UDLSSLibrary_SetDLSSMode_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UDLSSLibrary_SetDLSSMode_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022403, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UDLSSLibrary_SetDLSSMode_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UDLSSLibrary_SetDLSSMode_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UDLSSLibrary_SetDLSSMode()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UDLSSLibrary_SetDLSSMode_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UDLSSLibrary_SetDLSSSharpness_Statics
	{
		struct DLSSLibrary_eventSetDLSSSharpness_Parms
		{
			float Sharpness;
		};
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Sharpness;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UDLSSLibrary_SetDLSSSharpness_Statics::NewProp_Sharpness = { "Sharpness", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(DLSSLibrary_eventSetDLSSSharpness_Parms, Sharpness), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UDLSSLibrary_SetDLSSSharpness_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UDLSSLibrary_SetDLSSSharpness_Statics::NewProp_Sharpness,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UDLSSLibrary_SetDLSSSharpness_Statics::Function_MetaDataParams[] = {
		{ "Category", "DLSS" },
		{ "Comment", "/* Sets the console variables to enable additional DLSS sharpening. Set to 0 to disable (r.NGX.DLSS.Sharpness) */" },
		{ "DisplayName", "Set DLSS Sharpness" },
		{ "ModuleRelativePath", "Public/DLSSLibrary.h" },
		{ "ToolTip", "Sets the console variables to enable additional DLSS sharpening. Set to 0 to disable (r.NGX.DLSS.Sharpness)" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UDLSSLibrary_SetDLSSSharpness_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UDLSSLibrary, nullptr, "SetDLSSSharpness", nullptr, nullptr, sizeof(DLSSLibrary_eventSetDLSSSharpness_Parms), Z_Construct_UFunction_UDLSSLibrary_SetDLSSSharpness_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UDLSSLibrary_SetDLSSSharpness_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022403, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UDLSSLibrary_SetDLSSSharpness_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UDLSSLibrary_SetDLSSSharpness_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UDLSSLibrary_SetDLSSSharpness()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UDLSSLibrary_SetDLSSSharpness_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UDLSSLibrary_NoRegister()
	{
		return UDLSSLibrary::StaticClass();
	}
	struct Z_Construct_UClass_UDLSSLibrary_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UDLSSLibrary_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
		(UObject* (*)())Z_Construct_UPackage__Script_DLSSBlueprint,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UDLSSLibrary_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UDLSSLibrary_GetDLSSMinimumDriverVersion, "GetDLSSMinimumDriverVersion" }, // 1556264258
		{ &Z_Construct_UFunction_UDLSSLibrary_GetDLSSMode, "GetDLSSMode" }, // 333876543
		{ &Z_Construct_UFunction_UDLSSLibrary_GetDLSSModeInformation, "GetDLSSModeInformation" }, // 1247008882
		{ &Z_Construct_UFunction_UDLSSLibrary_GetDLSSScreenPercentageRange, "GetDLSSScreenPercentageRange" }, // 1690551544
		{ &Z_Construct_UFunction_UDLSSLibrary_GetDLSSSharpness, "GetDLSSSharpness" }, // 637941015
		{ &Z_Construct_UFunction_UDLSSLibrary_GetSupportedDLSSModes, "GetSupportedDLSSModes" }, // 42367125
		{ &Z_Construct_UFunction_UDLSSLibrary_IsDLSSModeSupported, "IsDLSSModeSupported" }, // 1538485074
		{ &Z_Construct_UFunction_UDLSSLibrary_IsDLSSSupported, "IsDLSSSupported" }, // 2370480275
		{ &Z_Construct_UFunction_UDLSSLibrary_QueryDLSSSupport, "QueryDLSSSupport" }, // 3230415657
		{ &Z_Construct_UFunction_UDLSSLibrary_SetDLSSMode, "SetDLSSMode" }, // 820694163
		{ &Z_Construct_UFunction_UDLSSLibrary_SetDLSSSharpness, "SetDLSSSharpness" }, // 1286679746
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UDLSSLibrary_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "DLSSLibrary.h" },
		{ "ModuleRelativePath", "Public/DLSSLibrary.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UDLSSLibrary_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDLSSLibrary>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UDLSSLibrary_Statics::ClassParams = {
		&UDLSSLibrary::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		0,
		0,
		0x000800A0u,
		METADATA_PARAMS(Z_Construct_UClass_UDLSSLibrary_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UDLSSLibrary_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UDLSSLibrary()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UDLSSLibrary_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UDLSSLibrary, 2896839407);
	template<> DLSSBLUEPRINT_API UClass* StaticClass<UDLSSLibrary>()
	{
		return UDLSSLibrary::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UDLSSLibrary(Z_Construct_UClass_UDLSSLibrary, &UDLSSLibrary::StaticClass, TEXT("/Script/DLSSBlueprint"), TEXT("UDLSSLibrary"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UDLSSLibrary);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
