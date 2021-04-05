// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GraphFormatter/Private/FormatterSettings.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFormatterSettings() {}
// Cross Module References
	GRAPHFORMATTER_API UEnum* Z_Construct_UEnum_GraphFormatter_EGraphFormatterPositioningAlgorithm();
	UPackage* Z_Construct_UPackage__Script_GraphFormatter();
	GRAPHFORMATTER_API UClass* Z_Construct_UClass_UFormatterSettings_NoRegister();
	GRAPHFORMATTER_API UClass* Z_Construct_UClass_UFormatterSettings();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector2D();
// End Cross Module References
	static UEnum* EGraphFormatterPositioningAlgorithm_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_GraphFormatter_EGraphFormatterPositioningAlgorithm, Z_Construct_UPackage__Script_GraphFormatter(), TEXT("EGraphFormatterPositioningAlgorithm"));
		}
		return Singleton;
	}
	template<> GRAPHFORMATTER_API UEnum* StaticEnum<EGraphFormatterPositioningAlgorithm>()
	{
		return EGraphFormatterPositioningAlgorithm_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_EGraphFormatterPositioningAlgorithm(EGraphFormatterPositioningAlgorithm_StaticEnum, TEXT("/Script/GraphFormatter"), TEXT("EGraphFormatterPositioningAlgorithm"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_GraphFormatter_EGraphFormatterPositioningAlgorithm_Hash() { return 3292534336U; }
	UEnum* Z_Construct_UEnum_GraphFormatter_EGraphFormatterPositioningAlgorithm()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_GraphFormatter();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("EGraphFormatterPositioningAlgorithm"), 0, Get_Z_Construct_UEnum_GraphFormatter_EGraphFormatterPositioningAlgorithm_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "EGraphFormatterPositioningAlgorithm::EEvenlyInLayer", (int64)EGraphFormatterPositioningAlgorithm::EEvenlyInLayer },
				{ "EGraphFormatterPositioningAlgorithm::EFastAndSimpleMethodTop", (int64)EGraphFormatterPositioningAlgorithm::EFastAndSimpleMethodTop },
				{ "EGraphFormatterPositioningAlgorithm::EFastAndSimpleMethodMedian", (int64)EGraphFormatterPositioningAlgorithm::EFastAndSimpleMethodMedian },
				{ "EGraphFormatterPositioningAlgorithm::ELayerSweep", (int64)EGraphFormatterPositioningAlgorithm::ELayerSweep },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "EEvenlyInLayer.DisplayName", "Place node evenly in layer" },
				{ "EEvenlyInLayer.Name", "EGraphFormatterPositioningAlgorithm::EEvenlyInLayer" },
				{ "EFastAndSimpleMethodMedian.DisplayName", "FAS Median" },
				{ "EFastAndSimpleMethodMedian.Name", "EGraphFormatterPositioningAlgorithm::EFastAndSimpleMethodMedian" },
				{ "EFastAndSimpleMethodTop.DisplayName", "FAS Top" },
				{ "EFastAndSimpleMethodTop.Name", "EGraphFormatterPositioningAlgorithm::EFastAndSimpleMethodTop" },
				{ "ELayerSweep.DisplayName", "Layer sweep" },
				{ "ELayerSweep.Name", "EGraphFormatterPositioningAlgorithm::ELayerSweep" },
				{ "ModuleRelativePath", "Private/FormatterSettings.h" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_GraphFormatter,
				nullptr,
				"EGraphFormatterPositioningAlgorithm",
				"EGraphFormatterPositioningAlgorithm",
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
	void UFormatterSettings::StaticRegisterNativesUFormatterSettings()
	{
	}
	UClass* Z_Construct_UClass_UFormatterSettings_NoRegister()
	{
		return UFormatterSettings::StaticClass();
	}
	struct Z_Construct_UClass_UFormatterSettings_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_PositioningAlgorithm_Underlying;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_PositioningAlgorithm_MetaData[];
#endif
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_PositioningAlgorithm;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CommentBorder_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_CommentBorder;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_HorizontalSpacing_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_HorizontalSpacing;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_VerticalSpacing_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_VerticalSpacing;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MaxOrderingIterations_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_MaxOrderingIterations;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ForwardSplineTangentFromHorizontalDelta_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ForwardSplineTangentFromHorizontalDelta;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ForwardSplineTangentFromVerticalDelta_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ForwardSplineTangentFromVerticalDelta;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_BackwardSplineTangentFromHorizontalDelta_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_BackwardSplineTangentFromHorizontalDelta;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_BackwardSplineTangentFromVerticalDelta_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_BackwardSplineTangentFromVerticalDelta;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UFormatterSettings_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_GraphFormatter,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFormatterSettings_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "FormatterSettings.h" },
		{ "ModuleRelativePath", "Private/FormatterSettings.h" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_UFormatterSettings_Statics::NewProp_PositioningAlgorithm_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFormatterSettings_Statics::NewProp_PositioningAlgorithm_MetaData[] = {
		{ "Category", "Options" },
		{ "Comment", "/** Positioning algorithm*/" },
		{ "ModuleRelativePath", "Private/FormatterSettings.h" },
		{ "ToolTip", "Positioning algorithm" },
	};
#endif
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UFormatterSettings_Statics::NewProp_PositioningAlgorithm = { "PositioningAlgorithm", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFormatterSettings, PositioningAlgorithm), Z_Construct_UEnum_GraphFormatter_EGraphFormatterPositioningAlgorithm, METADATA_PARAMS(Z_Construct_UClass_UFormatterSettings_Statics::NewProp_PositioningAlgorithm_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFormatterSettings_Statics::NewProp_PositioningAlgorithm_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFormatterSettings_Statics::NewProp_CommentBorder_MetaData[] = {
		{ "Category", "Options" },
		{ "ClampMin", "45" },
		{ "Comment", "/** Border thickness */" },
		{ "ModuleRelativePath", "Private/FormatterSettings.h" },
		{ "ToolTip", "Border thickness" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UClass_UFormatterSettings_Statics::NewProp_CommentBorder = { "CommentBorder", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFormatterSettings, CommentBorder), METADATA_PARAMS(Z_Construct_UClass_UFormatterSettings_Statics::NewProp_CommentBorder_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFormatterSettings_Statics::NewProp_CommentBorder_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFormatterSettings_Statics::NewProp_HorizontalSpacing_MetaData[] = {
		{ "Category", "Options" },
		{ "ClampMin", "0" },
		{ "Comment", "/** Spacing between two layers */" },
		{ "ModuleRelativePath", "Private/FormatterSettings.h" },
		{ "ToolTip", "Spacing between two layers" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UClass_UFormatterSettings_Statics::NewProp_HorizontalSpacing = { "HorizontalSpacing", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFormatterSettings, HorizontalSpacing), METADATA_PARAMS(Z_Construct_UClass_UFormatterSettings_Statics::NewProp_HorizontalSpacing_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFormatterSettings_Statics::NewProp_HorizontalSpacing_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFormatterSettings_Statics::NewProp_VerticalSpacing_MetaData[] = {
		{ "Category", "Options" },
		{ "ClampMin", "0" },
		{ "Comment", "/** Spacing between two nodes */" },
		{ "ModuleRelativePath", "Private/FormatterSettings.h" },
		{ "ToolTip", "Spacing between two nodes" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UClass_UFormatterSettings_Statics::NewProp_VerticalSpacing = { "VerticalSpacing", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFormatterSettings, VerticalSpacing), METADATA_PARAMS(Z_Construct_UClass_UFormatterSettings_Statics::NewProp_VerticalSpacing_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFormatterSettings_Statics::NewProp_VerticalSpacing_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFormatterSettings_Statics::NewProp_MaxOrderingIterations_MetaData[] = {
		{ "Category", "Performance" },
		{ "ClampMax", "100" },
		{ "ClampMin", "0" },
		{ "Comment", "/** Vertex ordering max iterations */" },
		{ "ModuleRelativePath", "Private/FormatterSettings.h" },
		{ "ToolTip", "Vertex ordering max iterations" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UClass_UFormatterSettings_Statics::NewProp_MaxOrderingIterations = { "MaxOrderingIterations", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFormatterSettings, MaxOrderingIterations), METADATA_PARAMS(Z_Construct_UClass_UFormatterSettings_Statics::NewProp_MaxOrderingIterations_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFormatterSettings_Statics::NewProp_MaxOrderingIterations_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFormatterSettings_Statics::NewProp_ForwardSplineTangentFromHorizontalDelta_MetaData[] = {
		{ "Category", "Graph Formatter" },
		{ "Comment", "/** Straight connections old settings */" },
		{ "ModuleRelativePath", "Private/FormatterSettings.h" },
		{ "ToolTip", "Straight connections old settings" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_UFormatterSettings_Statics::NewProp_ForwardSplineTangentFromHorizontalDelta = { "ForwardSplineTangentFromHorizontalDelta", nullptr, (EPropertyFlags)0x0010000000004004, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFormatterSettings, ForwardSplineTangentFromHorizontalDelta), Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(Z_Construct_UClass_UFormatterSettings_Statics::NewProp_ForwardSplineTangentFromHorizontalDelta_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFormatterSettings_Statics::NewProp_ForwardSplineTangentFromHorizontalDelta_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFormatterSettings_Statics::NewProp_ForwardSplineTangentFromVerticalDelta_MetaData[] = {
		{ "Category", "Graph Formatter" },
		{ "ModuleRelativePath", "Private/FormatterSettings.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_UFormatterSettings_Statics::NewProp_ForwardSplineTangentFromVerticalDelta = { "ForwardSplineTangentFromVerticalDelta", nullptr, (EPropertyFlags)0x0010000000004004, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFormatterSettings, ForwardSplineTangentFromVerticalDelta), Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(Z_Construct_UClass_UFormatterSettings_Statics::NewProp_ForwardSplineTangentFromVerticalDelta_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFormatterSettings_Statics::NewProp_ForwardSplineTangentFromVerticalDelta_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFormatterSettings_Statics::NewProp_BackwardSplineTangentFromHorizontalDelta_MetaData[] = {
		{ "Category", "Graph Formatter" },
		{ "ModuleRelativePath", "Private/FormatterSettings.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_UFormatterSettings_Statics::NewProp_BackwardSplineTangentFromHorizontalDelta = { "BackwardSplineTangentFromHorizontalDelta", nullptr, (EPropertyFlags)0x0010000000004004, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFormatterSettings, BackwardSplineTangentFromHorizontalDelta), Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(Z_Construct_UClass_UFormatterSettings_Statics::NewProp_BackwardSplineTangentFromHorizontalDelta_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFormatterSettings_Statics::NewProp_BackwardSplineTangentFromHorizontalDelta_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFormatterSettings_Statics::NewProp_BackwardSplineTangentFromVerticalDelta_MetaData[] = {
		{ "Category", "Graph Formatter" },
		{ "ModuleRelativePath", "Private/FormatterSettings.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_UFormatterSettings_Statics::NewProp_BackwardSplineTangentFromVerticalDelta = { "BackwardSplineTangentFromVerticalDelta", nullptr, (EPropertyFlags)0x0010000000004004, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFormatterSettings, BackwardSplineTangentFromVerticalDelta), Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(Z_Construct_UClass_UFormatterSettings_Statics::NewProp_BackwardSplineTangentFromVerticalDelta_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFormatterSettings_Statics::NewProp_BackwardSplineTangentFromVerticalDelta_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UFormatterSettings_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFormatterSettings_Statics::NewProp_PositioningAlgorithm_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFormatterSettings_Statics::NewProp_PositioningAlgorithm,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFormatterSettings_Statics::NewProp_CommentBorder,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFormatterSettings_Statics::NewProp_HorizontalSpacing,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFormatterSettings_Statics::NewProp_VerticalSpacing,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFormatterSettings_Statics::NewProp_MaxOrderingIterations,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFormatterSettings_Statics::NewProp_ForwardSplineTangentFromHorizontalDelta,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFormatterSettings_Statics::NewProp_ForwardSplineTangentFromVerticalDelta,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFormatterSettings_Statics::NewProp_BackwardSplineTangentFromHorizontalDelta,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFormatterSettings_Statics::NewProp_BackwardSplineTangentFromVerticalDelta,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UFormatterSettings_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UFormatterSettings>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UFormatterSettings_Statics::ClassParams = {
		&UFormatterSettings::StaticClass,
		"Editor",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UFormatterSettings_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UFormatterSettings_Statics::PropPointers),
		0,
		0x001000A4u,
		METADATA_PARAMS(Z_Construct_UClass_UFormatterSettings_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UFormatterSettings_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UFormatterSettings()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UFormatterSettings_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UFormatterSettings, 186053786);
	template<> GRAPHFORMATTER_API UClass* StaticClass<UFormatterSettings>()
	{
		return UFormatterSettings::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UFormatterSettings(Z_Construct_UClass_UFormatterSettings, &UFormatterSettings::StaticClass, TEXT("/Script/GraphFormatter"), TEXT("UFormatterSettings"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UFormatterSettings);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
