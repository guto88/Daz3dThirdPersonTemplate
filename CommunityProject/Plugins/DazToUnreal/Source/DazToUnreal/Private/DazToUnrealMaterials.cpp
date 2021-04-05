#include "DazToUnrealMaterials.h"
#include "DazToUnrealSettings.h"
#include "DazToUnrealTextures.h"

#include "Materials/MaterialInstanceConstant.h"
#include "Factories/MaterialInstanceConstantFactoryNew.h"
#include "Factories/SubsurfaceProfileFactory.h"
#include "Engine/SubsurfaceProfile.h"
#include "AssetRegistryModule.h"
#include "AssetToolsModule.h"

FSoftObjectPath FDazToUnrealMaterials::GetBaseMaterialForShader(FString ShaderName)
{
	const UDazToUnrealSettings* CachedSettings = GetDefault<UDazToUnrealSettings>();
	FSoftObjectPath BaseMaterialAssetPath = CachedSettings->BaseMaterial;
	if (CachedSettings->BaseShaderMaterials.Contains(ShaderName))
	{
		BaseMaterialAssetPath = CachedSettings->BaseShaderMaterials[ShaderName];
	}
	return BaseMaterialAssetPath;
}
FSoftObjectPath FDazToUnrealMaterials::GetSkinMaterialForShader(FString ShaderName)
{
	const UDazToUnrealSettings* CachedSettings = GetDefault<UDazToUnrealSettings>();
	FSoftObjectPath BaseMaterialAssetPath = CachedSettings->BaseSkinMaterial;
	if (CachedSettings->SkinShaderMaterials.Contains(ShaderName))
	{
		BaseMaterialAssetPath = CachedSettings->SkinShaderMaterials[ShaderName];
	}
	return BaseMaterialAssetPath;
}

FSoftObjectPath FDazToUnrealMaterials::GetBaseMaterial(FString MaterialName, TArray<FDUFTextureProperty > MaterialProperties)
{
	const UDazToUnrealSettings* CachedSettings = GetDefault<UDazToUnrealSettings>();

	// Find the proper Base Material
	FSoftObjectPath BaseMaterialAssetPath = CachedSettings->BaseMaterial;

	FString AssetType = "";
	FString ShaderName = "";
	TArray<FDUFTextureProperty> Properties = MaterialProperties;
	for (FDUFTextureProperty Property : Properties)
	{
		if (Property.Name == TEXT("Asset Type"))
		{
			AssetType = Property.Value;
			ShaderName = Property.ShaderName;
		}
	}

	// Set the default material type
	if (CachedSettings->BaseShaderMaterials.Contains(ShaderName))
	{
		BaseMaterialAssetPath = CachedSettings->BaseShaderMaterials[ShaderName];
		//return BaseMaterialAssetPath;
	}
	
	if (AssetType == TEXT("Follower/Hair"))
	{
		BaseMaterialAssetPath = CachedSettings->BaseHairMaterial;
		if (MaterialName.EndsWith(TEXT("_scalp")))
		{
			BaseMaterialAssetPath = CachedSettings->BaseScalpMaterial;
		}
	}
	else if (AssetType == TEXT("Follower/Attachment/Head/Face/Eyelashes"))
	{
		if (MaterialName.Contains(TEXT("_EyeMoisture")))
		{
			BaseMaterialAssetPath = CachedSettings->BaseEyeMoistureMaterial;
		}
		else
		{
			BaseMaterialAssetPath = CachedSettings->BaseAlphaMaterial;
		}
	}
	else if (AssetType == TEXT("Follower/Attachment/Lower-Body/Hip/Front") &&
		MaterialName.Contains(TEXT("_Genitalia")))
	{
		BaseMaterialAssetPath = GetSkinMaterialForShader(ShaderName);
	}
	else if (AssetType == TEXT("Actor/Character"))
	{
		// Check for skin materials
		if (MaterialName.EndsWith(TEXT("_Face")) ||
			MaterialName.EndsWith(TEXT("_Head")) ||
			MaterialName.EndsWith(TEXT("_Lips")) ||
			MaterialName.EndsWith(TEXT("_Legs")) ||
			MaterialName.EndsWith(TEXT("_Hips")) ||
			MaterialName.EndsWith(TEXT("_Feet")) ||
			MaterialName.EndsWith(TEXT("_Torso")) ||
			MaterialName.EndsWith(TEXT("_Body")) ||
			MaterialName.EndsWith(TEXT("_Neck")) ||
			MaterialName.EndsWith(TEXT("_Shoulders")) ||
			MaterialName.EndsWith(TEXT("_Arms")) ||
			MaterialName.EndsWith(TEXT("_Forearms")) ||
			MaterialName.EndsWith(TEXT("_Hands")) ||
			MaterialName.EndsWith(TEXT("_EyeSocket")) ||
			MaterialName.EndsWith(TEXT("_Ears")) ||
			MaterialName.EndsWith(TEXT("_Fingernails")) ||
			MaterialName.EndsWith(TEXT("_Toenails")) ||
			MaterialName.EndsWith(TEXT("_Nipples")) ||
			MaterialName.EndsWith(TEXT("_Genitalia")))
		{
			BaseMaterialAssetPath = GetSkinMaterialForShader(ShaderName);
		}
		else if (MaterialName.Contains(TEXT("_EyeMoisture")))
		{
			BaseMaterialAssetPath = CachedSettings->BaseEyeMoistureMaterial;
		}
		else if (MaterialName.Contains(TEXT("_EyeReflection")))
		{
			BaseMaterialAssetPath = CachedSettings->BaseEyeMoistureMaterial;
		}
		else if (MaterialName.Contains(TEXT("_Tear")))
		{
			BaseMaterialAssetPath = CachedSettings->BaseEyeMoistureMaterial;
		}
		else if (MaterialName.EndsWith(TEXT("_EyeLashes")))
		{
			BaseMaterialAssetPath = CachedSettings->BaseAlphaMaterial;
		}
		else if (MaterialName.EndsWith(TEXT("_Eyelashes")))
		{
			BaseMaterialAssetPath = CachedSettings->BaseAlphaMaterial;
		}
		else if (MaterialName.EndsWith(TEXT("_Eyelash")))
		{
			BaseMaterialAssetPath = CachedSettings->BaseAlphaMaterial;
		}
		else if (MaterialName.EndsWith(TEXT("_cornea")))
		{
			BaseMaterialAssetPath = CachedSettings->BaseCorneaMaterial;
		}
		/*else if (MaterialName.EndsWith(TEXT("_sclera")))
		{
			BaseMaterialAssetPath = CachedSettings->BaseMaterial;
		}
		else if (MaterialName.EndsWith(TEXT("_irises")))
		{
			BaseMaterialAssetPath = CachedSettings->BaseMaterial;
		}
		else if (MaterialName.EndsWith(TEXT("_pupils")))
		{
			BaseMaterialAssetPath = CachedSettings->BaseMaterial;
		}*/
		else
		{
			//BaseMaterialAssetPath = CachedSettings->BaseMaterial;

			for (FDUFTextureProperty Property : Properties)
			{
				if (Property.Name == TEXT("Cutout Opacity Texture"))
				{
					BaseMaterialAssetPath = CachedSettings->BaseAlphaMaterial;
				}
			}
			
		}
	}
	else if (MaterialName.Contains(TEXT("_EyeMoisture")))
	{
		BaseMaterialAssetPath = CachedSettings->BaseEyeMoistureMaterial;
	}
	else
	{
		//BaseMaterialAssetPath = CachedSettings->BaseMaterial;

		for (FDUFTextureProperty Property : Properties)
		{
			if (Property.Name == TEXT("Cutout Opacity Texture"))
			{
				BaseMaterialAssetPath = CachedSettings->BaseAlphaMaterial;
			}
			if (Property.Name == TEXT("Opacity Strength") && Property.Value != TEXT("1"))
			{
				BaseMaterialAssetPath = CachedSettings->BaseAlphaMaterial;
			}
		}
		
	}
	if (MaterialName.EndsWith(TEXT("_NoDraw")))
	{
		BaseMaterialAssetPath = CachedSettings->NoDrawMaterial;
	}
	return BaseMaterialAssetPath;
}

UMaterialInstanceConstant* FDazToUnrealMaterials::CreateMaterial(const FString CharacterMaterialFolder, const FString CharacterTexturesFolder, FString& MaterialName, TMap<FString, TArray<FDUFTextureProperty>> MaterialProperties, const DazCharacterType CharacterType, UMaterialInstanceConstant* ParentMaterial, USubsurfaceProfile* SubsurfaceProfile)
{
	const UDazToUnrealSettings* CachedSettings = GetDefault<UDazToUnrealSettings>();

	FSoftObjectPath BaseMaterialAssetPath = CachedSettings->BaseMaterial;
	// Prepare the material Properties
	if (MaterialProperties.Contains(MaterialName))
	{
		BaseMaterialAssetPath = GetBaseMaterial(MaterialName, MaterialProperties[MaterialName]);
	}
	
	FString ShaderName = "";
	FString AssetType = "";
	if (MaterialProperties.Contains(MaterialName))
	{
		TArray<FDUFTextureProperty> Properties = MaterialProperties[MaterialName];
		for (FDUFTextureProperty Property : Properties)
		{
			if (Property.Name == TEXT("Asset Type"))
			{
				AssetType = Property.Value;
				ShaderName = Property.ShaderName;
			}
		}
	}

	if (AssetType == TEXT("Follower/Attachment/Head/Face/Eyelashes") ||
		AssetType == TEXT("Follower/Attachment/Head/Face/Eyes") ||
		AssetType == TEXT("Follower/Attachment/Head/Face/Eyes/Tear") ||
		AssetType == TEXT("Follower/Attachment/Head/Face/Tears"))
	{
		if (MaterialName.Contains(TEXT("_EyeMoisture")) || MaterialName.EndsWith(TEXT("_EyeReflection")))
		{
			//BaseMaterialAssetPath = CachedSettings->BaseEyeMoistureMaterial;
			SetMaterialProperty(MaterialName, TEXT("Metallic Weight"), TEXT("Double"), TEXT("1"), MaterialProperties);
			SetMaterialProperty(MaterialName, TEXT("Opacity Strength"), TEXT("Double"), FString::SanitizeFloat(CachedSettings->DefaultEyeMoistureOpacity), MaterialProperties);
			SetMaterialProperty(MaterialName, TEXT("Diffuse Color"), TEXT("Color"), TEXT("#bababa"), MaterialProperties);
			SetMaterialProperty(MaterialName, TEXT("Index of Refraction"), TEXT("Double"), TEXT("1.0"), MaterialProperties);
		}
		else if (MaterialName.EndsWith(TEXT("_Tear")) || MaterialName.EndsWith(TEXT("_Tears")))
		{
			//BaseMaterialAssetPath = CachedSettings->BaseCorneaMaterial;
			SetMaterialProperty(MaterialName, TEXT("Metallic Weight"), TEXT("Double"), TEXT("1"), MaterialProperties);
			SetMaterialProperty(MaterialName, TEXT("Opacity Strength"), TEXT("Double"), FString::SanitizeFloat(CachedSettings->DefaultEyeMoistureOpacity), MaterialProperties);
			SetMaterialProperty(MaterialName, TEXT("Index of Refraction"), TEXT("Double"), TEXT("1.0"), MaterialProperties);
		}
		else
		{
			//BaseMaterialAssetPath = CachedSettings->BaseAlphaMaterial;
			SetMaterialProperty(MaterialName, TEXT("Metallic Weight"), TEXT("Double"), TEXT("0"), MaterialProperties);
			SetMaterialProperty(MaterialName, TEXT("Glossy Layered Weight"), TEXT("Double"), TEXT("0"), MaterialProperties);
		}
	}
	else if (AssetType == TEXT("Follower/Attachment/Lower-Body/Hip/Front") &&
		MaterialName.Contains(TEXT("_Genitalia")))
	{
		//BaseMaterialAssetPath = CachedSettings->BaseSkinMaterial;
		SetMaterialProperty(MaterialName, TEXT("Subsurface Alpha Texture"), TEXT("Texture"), FDazToUnrealTextures::GetSubSurfaceAlphaTexture(CharacterType, MaterialName), MaterialProperties);
	}
	else if (AssetType == TEXT("Actor/Character"))
	{
		// Check for skin materials
		if (MaterialName.EndsWith(TEXT("_Face")) ||
			MaterialName.EndsWith(TEXT("_Head")) ||
			MaterialName.EndsWith(TEXT("_Lips")) ||
			MaterialName.EndsWith(TEXT("_Legs")) ||
			MaterialName.EndsWith(TEXT("_Torso")) ||
			MaterialName.EndsWith(TEXT("_Body")) ||
			MaterialName.EndsWith(TEXT("_Arms")) ||
			MaterialName.EndsWith(TEXT("_EyeSocket")) ||
			MaterialName.EndsWith(TEXT("_Ears")) ||
			MaterialName.EndsWith(TEXT("_Fingernails")) ||
			MaterialName.EndsWith(TEXT("_Toenails")) ||
			MaterialName.EndsWith(TEXT("_Genitalia")))
		{
			//BaseMaterialAssetPath = CachedSettings->BaseSkinMaterial;
			SetMaterialProperty(MaterialName, TEXT("Diffuse Subsurface Color Weight"), TEXT("Double"), FString::SanitizeFloat(CachedSettings->DefaultSkinDiffuseSubsurfaceColorWeight), MaterialProperties);
			SetMaterialProperty(MaterialName, TEXT("Subsurface Alpha Texture"), TEXT("Texture"), FDazToUnrealTextures::GetSubSurfaceAlphaTexture(CharacterType, MaterialName), MaterialProperties);
		}
		else if (MaterialName.Contains(TEXT("_EyeMoisture")))
		{
			//BaseMaterialAssetPath = CachedSettings->BaseEyeMoistureMaterial;
			SetMaterialProperty(MaterialName, TEXT("Metallic Weight"), TEXT("Double"), TEXT("1"), MaterialProperties);
			SetMaterialProperty(MaterialName, TEXT("Opacity Strength"), TEXT("Double"), FString::SanitizeFloat(CachedSettings->DefaultEyeMoistureOpacity), MaterialProperties);
			SetMaterialProperty(MaterialName, TEXT("Index of Refraction"), TEXT("Double"), TEXT("1.0"), MaterialProperties);
		}
		else if (MaterialName.EndsWith(TEXT("_EyeReflection")) || MaterialName.EndsWith(TEXT("_Tear")) || MaterialName.EndsWith(TEXT("_Tears")))
		{
			//BaseMaterialAssetPath = CachedSettings->BaseEyeMoistureMaterial;
			SetMaterialProperty(MaterialName, TEXT("Metallic Weight"), TEXT("Double"), TEXT("1"), MaterialProperties);
			SetMaterialProperty(MaterialName, TEXT("Opacity Strength"), TEXT("Double"), FString::SanitizeFloat(CachedSettings->DefaultEyeMoistureOpacity), MaterialProperties);
			SetMaterialProperty(MaterialName, TEXT("Index of Refraction"), TEXT("Double"), TEXT("1.0"), MaterialProperties);
		}
		else if (MaterialName.EndsWith(TEXT("_EyeLashes")) || MaterialName.EndsWith(TEXT("_Eyelashes")))
		{
			//BaseMaterialAssetPath = CachedSettings->BaseAlphaMaterial;
			SetMaterialProperty(MaterialName, TEXT("Metallic Weight"), TEXT("Double"), TEXT("0"), MaterialProperties);
			SetMaterialProperty(MaterialName, TEXT("Glossy Layered Weight"), TEXT("Double"), TEXT("0"), MaterialProperties);
			SetMaterialProperty(MaterialName, TEXT("Index of Refraction"), TEXT("Double"), TEXT("1.0"), MaterialProperties);
		}
		else if (MaterialName.EndsWith(TEXT("_cornea")))
		{
			//BaseMaterialAssetPath = CachedSettings->BaseCorneaMaterial;
			SetMaterialProperty(MaterialName, TEXT("Metallic Weight"), TEXT("Double"), TEXT("1"), MaterialProperties);
			SetMaterialProperty(MaterialName, TEXT("Opacity Strength"), TEXT("Double"), FString::SanitizeFloat(CachedSettings->DefaultEyeMoistureOpacity), MaterialProperties);
			SetMaterialProperty(MaterialName, TEXT("Index of Refraction"), TEXT("Double"), TEXT("1.0"), MaterialProperties);
		}
		else if (MaterialName.EndsWith(TEXT("_sclera")))
		{
			//BaseMaterialAssetPath = CachedSettings->BaseMaterial;
		}
		else if (MaterialName.EndsWith(TEXT("_irises")))
		{
			SetMaterialProperty(MaterialName, TEXT("Pixel Depth Offset"), TEXT("Double"), TEXT("0.1"), MaterialProperties);
			//BaseMaterialAssetPath = CachedSettings->BaseMaterial;
		}
		else if (MaterialName.EndsWith(TEXT("_pupils")))
		{
			SetMaterialProperty(MaterialName, TEXT("Pixel Depth Offset"), TEXT("Double"), TEXT("0.1"), MaterialProperties);
			//BaseMaterialAssetPath = CachedSettings->BaseMaterial;
		}
		else
		{
			//BaseMaterialAssetPath = CachedSettings->BaseMaterial;
			if (MaterialProperties.Contains(MaterialName))
			{
				TArray<FDUFTextureProperty> Properties = MaterialProperties[MaterialName];
				for (FDUFTextureProperty Property : Properties)
				{
					if (Property.Name == TEXT("Cutout Opacity Texture"))
					{
						//BaseMaterialAssetPath = CachedSettings->BaseAlphaMaterial;
					}
				}
			}
		}
	}
	else if (MaterialName.Contains(TEXT("_EyeMoisture")))
	{
		//BaseMaterialAssetPath = CachedSettings->BaseEyeMoistureMaterial;
		SetMaterialProperty(MaterialName, TEXT("Metallic Weight"), TEXT("Double"), TEXT("1"), MaterialProperties);
		SetMaterialProperty(MaterialName, TEXT("Opacity Strength"), TEXT("Double"), FString::SanitizeFloat(CachedSettings->DefaultEyeMoistureOpacity), MaterialProperties);
		SetMaterialProperty(MaterialName, TEXT("Index of Refraction"), TEXT("Double"), TEXT("1.0"), MaterialProperties);
	}
	else
	{
		//BaseMaterialAssetPath = CachedSettings->BaseMaterial;
		if (MaterialProperties.Contains(MaterialName))
		{
			TArray<FDUFTextureProperty> Properties = MaterialProperties[MaterialName];
			for (FDUFTextureProperty Property : Properties)
			{
				if (Property.Name == TEXT("Cutout Opacity Texture"))
				{
					//BaseMaterialAssetPath = CachedSettings->BaseAlphaMaterial;
				}
				if (Property.Name == TEXT("Opacity Strength") && Property.Value != TEXT("1"))
				{
					//BaseMaterialAssetPath = CachedSettings->BaseAlphaMaterial;
				}
			}
		}
	}
	if (MaterialName.EndsWith(TEXT("_NoDraw")))
	{
		//BaseMaterialAssetPath = CachedSettings->NoDrawMaterial;
	}

	// Create the Material Instance
	auto MaterialInstanceFactory = NewObject<UMaterialInstanceConstantFactoryNew>();

	UPackage* Package = CreatePackage(nullptr, *(CharacterMaterialFolder / MaterialName));
	UMaterialInstanceConstant* UnrealMaterialConstant = (UMaterialInstanceConstant*)MaterialInstanceFactory->FactoryCreateNew(UMaterialInstanceConstant::StaticClass(), Package, *MaterialName, RF_Standalone | RF_Public, NULL, GWarn);


	if (UnrealMaterialConstant != NULL)
	{
		// Notify the asset registry
		FAssetRegistryModule::AssetCreated(UnrealMaterialConstant);

		// Set the dirty flag so this package will get saved later
		Package->SetDirtyFlag(true);

		UObject* BaseMaterial = BaseMaterialAssetPath.TryLoad();
		if (ParentMaterial && ParentMaterial->Parent == BaseMaterial)
		{
			UnrealMaterialConstant->SetParentEditorOnly((UMaterial*)ParentMaterial);
		}
		else
		{
			UnrealMaterialConstant->SetParentEditorOnly((UMaterial*)BaseMaterial);
		}

		if (SubsurfaceProfile)
		{
			if (!ParentMaterial || ParentMaterial->SubsurfaceProfile != SubsurfaceProfile)
			{
				UnrealMaterialConstant->bOverrideSubsurfaceProfile = 1;
				UnrealMaterialConstant->SubsurfaceProfile = SubsurfaceProfile;
			}
			else
			{
				UnrealMaterialConstant->bOverrideSubsurfaceProfile = 0;
			}
		}

		// Set the MaterialInstance properties
		if (MaterialProperties.Contains(MaterialName))
		{

			// Rename properties based on the settings
			TArray<FDUFTextureProperty> MaterialInstanceProperties;
			for (FDUFTextureProperty MaterialProperty : MaterialProperties[MaterialName])
			{
				if (CachedSettings->MaterialPropertyMapping.Contains(MaterialProperty.Name))
				{
					MaterialProperty.Name = CachedSettings->MaterialPropertyMapping[MaterialProperty.Name];
				}
				MaterialInstanceProperties.Add(MaterialProperty);
			}

			// Apply the properties
			for (FDUFTextureProperty MaterialProperty : MaterialInstanceProperties)
			{
				if (MaterialProperty.Type == TEXT("Texture"))
				{
					FStringAssetReference TextureAssetPath(CharacterTexturesFolder / MaterialProperty.Value);
					UObject* TextureAsset = TextureAssetPath.TryLoad();
					if (TextureAsset == nullptr)
					{
						FStringAssetReference TextureAssetPathFull(MaterialProperty.Value);
						TextureAsset = TextureAssetPathFull.TryLoad();
					}
					FMaterialParameterInfo ParameterInfo(*MaterialProperty.Name);
					UnrealMaterialConstant->SetTextureParameterValueEditorOnly(ParameterInfo, (UTexture*)TextureAsset);
				}
				if (MaterialProperty.Type == TEXT("Double"))
				{
					float Value = FCString::Atof(*MaterialProperty.Value);
					FMaterialParameterInfo ParameterInfo(*MaterialProperty.Name);
					UnrealMaterialConstant->SetScalarParameterValueEditorOnly(ParameterInfo, Value);
				}
				if (MaterialProperty.Type == TEXT("Color"))
				{
					//FLinearColor Value = FDazToUnrealModule::FromHex(MaterialProperty.Value);
					//FColor Color = Value.ToFColor(true);
					FColor Color = FColor::FromHex(MaterialProperty.Value);
					FMaterialParameterInfo ParameterInfo(*MaterialProperty.Name);
					UnrealMaterialConstant->SetVectorParameterValueEditorOnly(ParameterInfo, Color);
				}
				if (MaterialProperty.Type == TEXT("Switch"))
				{
					FStaticParameterSet StaticParameters;
					UnrealMaterialConstant->GetStaticParameterValues(StaticParameters);

					for (int32 ParameterIdx = 0; ParameterIdx < StaticParameters.StaticSwitchParameters.Num(); ParameterIdx++)
					{
						for (int32 SwitchParamIdx = 0; SwitchParamIdx < StaticParameters.StaticSwitchParameters.Num(); SwitchParamIdx++)
						{
							FStaticSwitchParameter& StaticSwitchParam = StaticParameters.StaticSwitchParameters[SwitchParamIdx];

							if (StaticSwitchParam.ParameterInfo.Name.ToString() == MaterialProperty.Name)
							{
								StaticSwitchParam.bOverride = true;
								StaticSwitchParam.Value = MaterialProperty.Value.ToLower() == TEXT("true");
							}
						}
					}
					UnrealMaterialConstant->UpdateStaticPermutation(StaticParameters);
				}
			}
		}
	}


	return UnrealMaterialConstant;
}

void FDazToUnrealMaterials::SetMaterialProperty(const FString& MaterialName, const FString& PropertyName, const FString& PropertyType, const FString& PropertyValue, TMap<FString, TArray<FDUFTextureProperty>>& MaterialProperties)
{
	if (!MaterialProperties.Contains(MaterialName))
	{
		MaterialProperties.Add(MaterialName, TArray<FDUFTextureProperty>());
	}
	TArray<FDUFTextureProperty>& Properties = MaterialProperties[MaterialName];
	for (FDUFTextureProperty& Property : Properties)
	{
		if (Property.Name == PropertyName)
		{
			Property.Value = PropertyValue;
			return;
		}
	}
	FDUFTextureProperty TextureProperty;
	TextureProperty.Name = PropertyName;
	TextureProperty.Type = PropertyType;
	TextureProperty.Value = PropertyValue;
	MaterialProperties[MaterialName].Add(TextureProperty);

}

FSoftObjectPath FDazToUnrealMaterials::GetMostCommonBaseMaterial(TArray<FString> MaterialNames, TMap<FString, TArray<FDUFTextureProperty>> MaterialProperties)
{
	TArray<FSoftObjectPath> BaseMaterials;
	for (FString MaterialName : MaterialNames)
	{
		BaseMaterials.Add(GetBaseMaterial(MaterialName, MaterialProperties[MaterialName]));
	}

	FSoftObjectPath MostCommonPath;
	int32 MostCommonCount = 0;
	for (FSoftObjectPath BaseMaterial : BaseMaterials)
	{
		int32 Count = 0;
		for (FSoftObjectPath BaseMaterialMatch : BaseMaterials)
		{
			if (BaseMaterialMatch == BaseMaterial)
			{
				Count++;
			}
		}
		if (Count > MostCommonCount)
		{
			MostCommonCount = Count;
			MostCommonPath = BaseMaterial;
		}
	}
	return MostCommonPath;
}

TArray<FDUFTextureProperty> FDazToUnrealMaterials::GetMostCommonProperties(TArray<FString> MaterialNames, TMap<FString, TArray<FDUFTextureProperty>> MaterialProperties)
{
	// Get a list of property names
	TArray<FString> PossibleProperties;
	for (FString MaterialName : MaterialNames)
	{
		for (FDUFTextureProperty Property : MaterialProperties[MaterialName])
		{
			if (Property.Name != TEXT("Asset Type"))
			{
				PossibleProperties.AddUnique(Property.Name);
			}
		}
	}

	TArray<FDUFTextureProperty> MostCommonProperties;
	for (FString PossibleProperty : PossibleProperties)
	{
		FDUFTextureProperty MostCommonProperty = GetMostCommonProperty(PossibleProperty, MaterialNames, MaterialProperties);
		if (MostCommonProperty.Name != TEXT(""))
		{
			MostCommonProperties.Add(MostCommonProperty);
		}
	}

	return MostCommonProperties;
}

FDUFTextureProperty FDazToUnrealMaterials::GetMostCommonProperty(FString PropertyName, TArray<FString> MaterialNames, TMap<FString, TArray<FDUFTextureProperty>> MaterialProperties)
{
	TArray<FDUFTextureProperty> PossibleProperties;

	// Only include properties that exist on all the child materials
	int32 PropertyCount = 0;
	for (FString MaterialName : MaterialNames)
	{
		// Gather all the options
		for (FDUFTextureProperty Property : MaterialProperties[MaterialName])
		{
			if (Property.Name == PropertyName)
			{
				PropertyCount++;
				PossibleProperties.Add(Property);
			}
		}
	}


	FDUFTextureProperty MostCommonProperty;
	int32 MostCommonCount = 0;
	if (PropertyCount == MaterialNames.Num())
	{
		for (FDUFTextureProperty PropertyToCount : PossibleProperties)
		{
			int32 Count = 0;
			for (FDUFTextureProperty PropertyToMatch : PossibleProperties)
			{
				if (PropertyToMatch == PropertyToCount)
				{
					Count++;
				}
			}
			if (Count > MostCommonCount)
			{
				MostCommonCount = Count;
				MostCommonProperty = PropertyToCount;
			}
		}
	}

	if (MostCommonCount <= 1)
	{
		MostCommonProperty.Name = TEXT("");
	}
	return MostCommonProperty;
}

bool FDazToUnrealMaterials::HasMaterialProperty(const FString& PropertyName, const  TArray<FDUFTextureProperty>& MaterialProperties)
{
	for (FDUFTextureProperty MaterialProperty : MaterialProperties)
	{
		if (MaterialProperty.Name == PropertyName)
		{
			return true;
		}
	}
	return false;
}
FString FDazToUnrealMaterials::GetMaterialProperty(const FString& PropertyName, const TArray<FDUFTextureProperty>& MaterialProperties)
{
	for (FDUFTextureProperty MaterialProperty : MaterialProperties)
	{
		if (MaterialProperty.Name == PropertyName)
		{
			return MaterialProperty.Value;
		}
	}
	return FString();
}

USubsurfaceProfile* FDazToUnrealMaterials::CreateSubsurfaceBaseProfileForCharacter(const FString CharacterMaterialFolder, TMap<FString, TArray<FDUFTextureProperty>>& MaterialProperties)
{
	// Find the torso material.
	for (TPair<FString, TArray<FDUFTextureProperty>> Pair : MaterialProperties)
	{
		FString AssetType;
		for (FDUFTextureProperty Property : Pair.Value)
		{
			if (Property.Name == TEXT("Asset Type"))
			{
				AssetType = Property.Value;
			}
		}

		if (AssetType == TEXT("Actor/Character"))
		{
			if (Pair.Key.EndsWith(TEXT("_Torso")) || Pair.Key.EndsWith(TEXT("_Body")))
			{
				return CreateSubsurfaceProfileForMaterial(Pair.Key, CharacterMaterialFolder, Pair.Value);
			}

		}
	}
	return nullptr;
}

USubsurfaceProfile* FDazToUnrealMaterials::CreateSubsurfaceProfileForMaterial(const FString MaterialName, const FString CharacterMaterialFolder, const TArray<FDUFTextureProperty > MaterialProperties)
{
	// Create the Material Instance
	//auto SubsurfaceProfileFactory = NewObject<USubsurfaceProfileFactory>();

	//Only create for the PBRSkin base material
	FString ShaderName;
	for (FDUFTextureProperty Property : MaterialProperties)
	{
		if (Property.Name == TEXT("Asset Type"))
		{
			ShaderName = Property.ShaderName;
		}
	}
	if (ShaderName != TEXT("PBRSkin"))
	{
		return nullptr;
	}

	FString SubsurfaceProfileName = MaterialName + TEXT("_Profile");
	UPackage* Package = CreatePackage(nullptr, *(CharacterMaterialFolder / MaterialName));
	//USubsurfaceProfile* SubsurfaceProfile = (USubsurfaceProfile*)SubsurfaceProfileFactory->FactoryCreateNew(USubsurfaceProfile::StaticClass(), Package, *MaterialName, RF_Standalone | RF_Public, NULL, GWarn);
	FAssetToolsModule& AssetToolsModule = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools");
	USubsurfaceProfile* SubsurfaceProfile = Cast<USubsurfaceProfile>(AssetToolsModule.Get().CreateAsset(SubsurfaceProfileName, FPackageName::GetLongPackagePath(*(CharacterMaterialFolder / MaterialName)), USubsurfaceProfile::StaticClass(), NULL));
	if (HasMaterialProperty(TEXT("Specular Lobe 1 Roughness"), MaterialProperties))
	{
		SubsurfaceProfile->Settings.Roughness0 = FCString::Atof(*GetMaterialProperty(TEXT("Specular Lobe 1 Roughness"), MaterialProperties));
	}
	if (HasMaterialProperty(TEXT("Specular Lobe 2 Roughness Mult"), MaterialProperties))
	{
		SubsurfaceProfile->Settings.Roughness1 = FCString::Atof(*GetMaterialProperty(TEXT("Specular Lobe 2 Roughness Mult"), MaterialProperties));
	}
	if (HasMaterialProperty(TEXT("Dual Lobe Specular Ratio"), MaterialProperties))
	{
		SubsurfaceProfile->Settings.LobeMix = FCString::Atof(*GetMaterialProperty(TEXT("Dual Lobe Specular Ratio"), MaterialProperties));
	}
	if (HasMaterialProperty(TEXT("SSS Color"), MaterialProperties))
	{
		SubsurfaceProfile->Settings.SubsurfaceColor = FColor::FromHex(*GetMaterialProperty(TEXT("SSS Color"), MaterialProperties));
	}
	if (HasMaterialProperty(TEXT("SSS Color"), MaterialProperties))
	{
		SubsurfaceProfile->Settings.SubsurfaceColor = FColor::FromHex(*GetMaterialProperty(TEXT("SSS Color"), MaterialProperties));
	}
	if (HasMaterialProperty(TEXT("Transmitted Color"), MaterialProperties))
	{
		SubsurfaceProfile->Settings.FalloffColor = FColor::FromHex(*GetMaterialProperty(TEXT("Transmitted Color"), MaterialProperties));
	}
	return SubsurfaceProfile;
}

bool FDazToUnrealMaterials::SubsurfaceProfilesAreIdentical(USubsurfaceProfile* A, USubsurfaceProfile* B)
{
	if (A == nullptr || B == nullptr) return false;
	if (A->Settings.Roughness0 != B->Settings.Roughness0) return false;
	if (A->Settings.Roughness1 != B->Settings.Roughness1) return false;
	if (A->Settings.LobeMix != B->Settings.LobeMix) return false;
	if (A->Settings.SubsurfaceColor != B->Settings.SubsurfaceColor) return false;
	if (A->Settings.FalloffColor != B->Settings.FalloffColor) return false;
	return true;
}

bool FDazToUnrealMaterials::SubsurfaceProfilesWouldBeIdentical(USubsurfaceProfile* ExistingSubsurfaceProfile, const TArray<FDUFTextureProperty > MaterialProperties)
{
	if (ExistingSubsurfaceProfile == nullptr) return false;
	if (ExistingSubsurfaceProfile->Settings.Roughness0 != FCString::Atof(*GetMaterialProperty(TEXT("Specular Lobe 1 Roughness"), MaterialProperties))) return false;
	if (ExistingSubsurfaceProfile->Settings.Roughness1 != FCString::Atof(*GetMaterialProperty(TEXT("Specular Lobe 2 Roughness Mult"), MaterialProperties))) return false;
	if (ExistingSubsurfaceProfile->Settings.LobeMix != FCString::Atof(*GetMaterialProperty(TEXT("Dual Lobe Specular Ratio"), MaterialProperties))) return false;
	if (ExistingSubsurfaceProfile->Settings.SubsurfaceColor != FColor::FromHex(*GetMaterialProperty(TEXT("SSS Color"), MaterialProperties))) return false;
	if (ExistingSubsurfaceProfile->Settings.FalloffColor != FColor::FromHex(*GetMaterialProperty(TEXT("Transmitted Color"), MaterialProperties))) return false;
	return true;
}