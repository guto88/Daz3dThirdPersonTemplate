// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
enum class UDLSSMode : uint8;
enum class UDLSSSupport : uint8;
#ifdef DLSSBLUEPRINT_DLSSLibrary_generated_h
#error "DLSSLibrary.generated.h already included, missing '#pragma once' in DLSSLibrary.h"
#endif
#define DLSSBLUEPRINT_DLSSLibrary_generated_h

#define HostProject_Plugins_DLSS_Source_DLSSBlueprint_Public_DLSSLibrary_h_64_SPARSE_DATA
#define HostProject_Plugins_DLSS_Source_DLSSBlueprint_Public_DLSSLibrary_h_64_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execGetDLSSSharpness); \
	DECLARE_FUNCTION(execSetDLSSSharpness); \
	DECLARE_FUNCTION(execGetDLSSMode); \
	DECLARE_FUNCTION(execSetDLSSMode); \
	DECLARE_FUNCTION(execGetDLSSScreenPercentageRange); \
	DECLARE_FUNCTION(execGetDLSSModeInformation); \
	DECLARE_FUNCTION(execGetSupportedDLSSModes); \
	DECLARE_FUNCTION(execIsDLSSModeSupported); \
	DECLARE_FUNCTION(execGetDLSSMinimumDriverVersion); \
	DECLARE_FUNCTION(execQueryDLSSSupport); \
	DECLARE_FUNCTION(execIsDLSSSupported);


#define HostProject_Plugins_DLSS_Source_DLSSBlueprint_Public_DLSSLibrary_h_64_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execGetDLSSSharpness); \
	DECLARE_FUNCTION(execSetDLSSSharpness); \
	DECLARE_FUNCTION(execGetDLSSMode); \
	DECLARE_FUNCTION(execSetDLSSMode); \
	DECLARE_FUNCTION(execGetDLSSScreenPercentageRange); \
	DECLARE_FUNCTION(execGetDLSSModeInformation); \
	DECLARE_FUNCTION(execGetSupportedDLSSModes); \
	DECLARE_FUNCTION(execIsDLSSModeSupported); \
	DECLARE_FUNCTION(execGetDLSSMinimumDriverVersion); \
	DECLARE_FUNCTION(execQueryDLSSSupport); \
	DECLARE_FUNCTION(execIsDLSSSupported);


#define HostProject_Plugins_DLSS_Source_DLSSBlueprint_Public_DLSSLibrary_h_64_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUDLSSLibrary(); \
	friend struct Z_Construct_UClass_UDLSSLibrary_Statics; \
public: \
	DECLARE_CLASS(UDLSSLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/DLSSBlueprint"), DLSSBLUEPRINT_API) \
	DECLARE_SERIALIZER(UDLSSLibrary)


#define HostProject_Plugins_DLSS_Source_DLSSBlueprint_Public_DLSSLibrary_h_64_INCLASS \
private: \
	static void StaticRegisterNativesUDLSSLibrary(); \
	friend struct Z_Construct_UClass_UDLSSLibrary_Statics; \
public: \
	DECLARE_CLASS(UDLSSLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/DLSSBlueprint"), DLSSBLUEPRINT_API) \
	DECLARE_SERIALIZER(UDLSSLibrary)


#define HostProject_Plugins_DLSS_Source_DLSSBlueprint_Public_DLSSLibrary_h_64_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	DLSSBLUEPRINT_API UDLSSLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UDLSSLibrary) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(DLSSBLUEPRINT_API, UDLSSLibrary); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UDLSSLibrary); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	DLSSBLUEPRINT_API UDLSSLibrary(UDLSSLibrary&&); \
	DLSSBLUEPRINT_API UDLSSLibrary(const UDLSSLibrary&); \
public:


#define HostProject_Plugins_DLSS_Source_DLSSBlueprint_Public_DLSSLibrary_h_64_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	DLSSBLUEPRINT_API UDLSSLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	DLSSBLUEPRINT_API UDLSSLibrary(UDLSSLibrary&&); \
	DLSSBLUEPRINT_API UDLSSLibrary(const UDLSSLibrary&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(DLSSBLUEPRINT_API, UDLSSLibrary); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UDLSSLibrary); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UDLSSLibrary)


#define HostProject_Plugins_DLSS_Source_DLSSBlueprint_Public_DLSSLibrary_h_64_PRIVATE_PROPERTY_OFFSET
#define HostProject_Plugins_DLSS_Source_DLSSBlueprint_Public_DLSSLibrary_h_60_PROLOG
#define HostProject_Plugins_DLSS_Source_DLSSBlueprint_Public_DLSSLibrary_h_64_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	HostProject_Plugins_DLSS_Source_DLSSBlueprint_Public_DLSSLibrary_h_64_PRIVATE_PROPERTY_OFFSET \
	HostProject_Plugins_DLSS_Source_DLSSBlueprint_Public_DLSSLibrary_h_64_SPARSE_DATA \
	HostProject_Plugins_DLSS_Source_DLSSBlueprint_Public_DLSSLibrary_h_64_RPC_WRAPPERS \
	HostProject_Plugins_DLSS_Source_DLSSBlueprint_Public_DLSSLibrary_h_64_INCLASS \
	HostProject_Plugins_DLSS_Source_DLSSBlueprint_Public_DLSSLibrary_h_64_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define HostProject_Plugins_DLSS_Source_DLSSBlueprint_Public_DLSSLibrary_h_64_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	HostProject_Plugins_DLSS_Source_DLSSBlueprint_Public_DLSSLibrary_h_64_PRIVATE_PROPERTY_OFFSET \
	HostProject_Plugins_DLSS_Source_DLSSBlueprint_Public_DLSSLibrary_h_64_SPARSE_DATA \
	HostProject_Plugins_DLSS_Source_DLSSBlueprint_Public_DLSSLibrary_h_64_RPC_WRAPPERS_NO_PURE_DECLS \
	HostProject_Plugins_DLSS_Source_DLSSBlueprint_Public_DLSSLibrary_h_64_INCLASS_NO_PURE_DECLS \
	HostProject_Plugins_DLSS_Source_DLSSBlueprint_Public_DLSSLibrary_h_64_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> DLSSBLUEPRINT_API UClass* StaticClass<class UDLSSLibrary>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID HostProject_Plugins_DLSS_Source_DLSSBlueprint_Public_DLSSLibrary_h


#define FOREACH_ENUM_UDLSSMODE(op) \
	op(UDLSSMode::Off) \
	op(UDLSSMode::UltraPerformance) \
	op(UDLSSMode::Performance) \
	op(UDLSSMode::Balanced) \
	op(UDLSSMode::Quality) \
	op(UDLSSMode::UltraQuality) 

enum class UDLSSMode : uint8;
template<> DLSSBLUEPRINT_API UEnum* StaticEnum<UDLSSMode>();

#define FOREACH_ENUM_UDLSSSUPPORT(op) \
	op(UDLSSSupport::Supported) \
	op(UDLSSSupport::NotSupported) \
	op(UDLSSSupport::NotSupportedIncompatibleHardware) \
	op(UDLSSSupport::NotSupportedDriverOutOfDate) \
	op(UDLSSSupport::NotSupportedOperatingSystemOutOfDate) 

enum class UDLSSSupport : uint8;
template<> DLSSBLUEPRINT_API UEnum* StaticEnum<UDLSSSupport>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
