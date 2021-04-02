// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef GRAPHFORMATTER_FormatterSettings_generated_h
#error "FormatterSettings.generated.h already included, missing '#pragma once' in FormatterSettings.h"
#endif
#define GRAPHFORMATTER_FormatterSettings_generated_h

#define HostProject_Plugins_GraphFormatter_Source_GraphFormatter_Private_FormatterSettings_h_24_SPARSE_DATA
#define HostProject_Plugins_GraphFormatter_Source_GraphFormatter_Private_FormatterSettings_h_24_RPC_WRAPPERS
#define HostProject_Plugins_GraphFormatter_Source_GraphFormatter_Private_FormatterSettings_h_24_RPC_WRAPPERS_NO_PURE_DECLS
#define HostProject_Plugins_GraphFormatter_Source_GraphFormatter_Private_FormatterSettings_h_24_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUFormatterSettings(); \
	friend struct Z_Construct_UClass_UFormatterSettings_Statics; \
public: \
	DECLARE_CLASS(UFormatterSettings, UObject, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/GraphFormatter"), NO_API) \
	DECLARE_SERIALIZER(UFormatterSettings) \
	static const TCHAR* StaticConfigName() {return TEXT("Editor");} \



#define HostProject_Plugins_GraphFormatter_Source_GraphFormatter_Private_FormatterSettings_h_24_INCLASS \
private: \
	static void StaticRegisterNativesUFormatterSettings(); \
	friend struct Z_Construct_UClass_UFormatterSettings_Statics; \
public: \
	DECLARE_CLASS(UFormatterSettings, UObject, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/GraphFormatter"), NO_API) \
	DECLARE_SERIALIZER(UFormatterSettings) \
	static const TCHAR* StaticConfigName() {return TEXT("Editor");} \



#define HostProject_Plugins_GraphFormatter_Source_GraphFormatter_Private_FormatterSettings_h_24_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UFormatterSettings(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UFormatterSettings) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UFormatterSettings); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UFormatterSettings); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UFormatterSettings(UFormatterSettings&&); \
	NO_API UFormatterSettings(const UFormatterSettings&); \
public:


#define HostProject_Plugins_GraphFormatter_Source_GraphFormatter_Private_FormatterSettings_h_24_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UFormatterSettings(UFormatterSettings&&); \
	NO_API UFormatterSettings(const UFormatterSettings&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UFormatterSettings); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UFormatterSettings); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UFormatterSettings)


#define HostProject_Plugins_GraphFormatter_Source_GraphFormatter_Private_FormatterSettings_h_24_PRIVATE_PROPERTY_OFFSET
#define HostProject_Plugins_GraphFormatter_Source_GraphFormatter_Private_FormatterSettings_h_20_PROLOG
#define HostProject_Plugins_GraphFormatter_Source_GraphFormatter_Private_FormatterSettings_h_24_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	HostProject_Plugins_GraphFormatter_Source_GraphFormatter_Private_FormatterSettings_h_24_PRIVATE_PROPERTY_OFFSET \
	HostProject_Plugins_GraphFormatter_Source_GraphFormatter_Private_FormatterSettings_h_24_SPARSE_DATA \
	HostProject_Plugins_GraphFormatter_Source_GraphFormatter_Private_FormatterSettings_h_24_RPC_WRAPPERS \
	HostProject_Plugins_GraphFormatter_Source_GraphFormatter_Private_FormatterSettings_h_24_INCLASS \
	HostProject_Plugins_GraphFormatter_Source_GraphFormatter_Private_FormatterSettings_h_24_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define HostProject_Plugins_GraphFormatter_Source_GraphFormatter_Private_FormatterSettings_h_24_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	HostProject_Plugins_GraphFormatter_Source_GraphFormatter_Private_FormatterSettings_h_24_PRIVATE_PROPERTY_OFFSET \
	HostProject_Plugins_GraphFormatter_Source_GraphFormatter_Private_FormatterSettings_h_24_SPARSE_DATA \
	HostProject_Plugins_GraphFormatter_Source_GraphFormatter_Private_FormatterSettings_h_24_RPC_WRAPPERS_NO_PURE_DECLS \
	HostProject_Plugins_GraphFormatter_Source_GraphFormatter_Private_FormatterSettings_h_24_INCLASS_NO_PURE_DECLS \
	HostProject_Plugins_GraphFormatter_Source_GraphFormatter_Private_FormatterSettings_h_24_ENHANCED_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> GRAPHFORMATTER_API UClass* StaticClass<class UFormatterSettings>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID HostProject_Plugins_GraphFormatter_Source_GraphFormatter_Private_FormatterSettings_h


#define FOREACH_ENUM_EGRAPHFORMATTERPOSITIONINGALGORITHM(op) \
	op(EGraphFormatterPositioningAlgorithm::EEvenlyInLayer) \
	op(EGraphFormatterPositioningAlgorithm::EFastAndSimpleMethodTop) \
	op(EGraphFormatterPositioningAlgorithm::EFastAndSimpleMethodMedian) \
	op(EGraphFormatterPositioningAlgorithm::ELayerSweep) 

enum class EGraphFormatterPositioningAlgorithm;
template<> GRAPHFORMATTER_API UEnum* StaticEnum<EGraphFormatterPositioningAlgorithm>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
