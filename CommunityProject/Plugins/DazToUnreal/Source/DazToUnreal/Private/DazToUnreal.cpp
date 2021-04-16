#include "DazToUnreal.h"
#include "DazToUnrealSettings.h"
#include "DazToUnrealStyle.h"
#include "DazToUnrealCommands.h"
#include "DazToUnrealMaterials.h"
#include "DazToUnrealUtils.h"
#include "DazToUnrealFbx.h"
#include "DazToUnrealEnvironment.h"
#include "DazToUnrealPoses.h"

#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "Misc/Paths.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "HAL/PlatformFilemanager.h"
#include "Misc/FileHelper.h"
#include "Materials/MaterialInstance.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Factories/MaterialInstanceConstantFactoryNew.h"
#include "Engine/ObjectLibrary.h"
#include "Factories/TextureFactory.h"
#include "ObjectTools.h"
#include "Engine/Texture2D.h"
#include "Utils.h"
#include "AssetToolsModule.h"
#include "AssetRegistryModule.h"
#include "EditorAssetLibrary.h"
#include "PackageTools.h"
#include "ObjectTools.h"
#include "Factories/FbxFactory.h"
#include "Factories/FbxImportUI.h"
#include "FbxImporter.h"
#include "AssetImportTask.h"
#include "Factories/MaterialImportHelpers.h"
#include "Factories/FbxTextureImportData.h"
#include "Factories/FbxSkeletalMeshImportData.h"
#include "Interfaces/IPluginManager.h"
#include "ContentBrowserModule.h"
#include "IContentBrowserSingleton.h"
#include "Misc/MessageDialog.h"
#include "EditorAssetLibrary.h"
#include "Misc/EngineVersion.h"
#include "Engine/SkeletalMesh.h"
#include "Animation/AnimInstance.h"
#include "Misc/ScopedSlowTask.h"
#include "Serialization/JsonReader.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonSerializer.h"
//#include "ISkeletonEditorModule.h"
//#include "IEditableSkeleton.h"

// NOTE: This FBX include code was copied from FbxImporter.h
// Temporarily disable a few warnings due to virtual function abuse in FBX source files
#pragma warning( push )

#pragma warning( disable : 4263 ) // 'function' : member function does not override any base class virtual member function
#pragma warning( disable : 4264 ) // 'virtual_function' : no override available for virtual member function from base 'class'; function is hidden

// Include the fbx sdk header
// temp undef/redef of _O_RDONLY because kfbxcache.h (included by fbxsdk.h) does
// a weird use of these identifiers inside an enum.
#ifdef _O_RDONLY
#define TMP_UNFBX_BACKUP_O_RDONLY _O_RDONLY
#define TMP_UNFBX_BACKUP_O_WRONLY _O_WRONLY
#undef _O_RDONLY
#undef _O_WRONLY
#endif

//Robert G. : Packing was only set for the 64bits platform, but we also need it for 32bits.
//This was found while trying to trace a loop that iterate through all character links.
//The memory didn't match what the debugger displayed, obviously since the packing was not right.
#pragma pack(push,8)

#if PLATFORM_WINDOWS
// _CRT_SECURE_NO_DEPRECATE is defined but is not enough to suppress the deprecation
// warning for vsprintf and stricmp in VS2010.  Since FBX is able to properly handle the non-deprecated
// versions on the appropriate platforms, _CRT_SECURE_NO_DEPRECATE is temporarily undefined before
// including the FBX headers

// The following is a hack to make the FBX header files compile correctly under Visual Studio 2012 and Visual Studio 2013
#if _MSC_VER >= 1700
#define FBX_DLL_MSC_VER 1600
#endif


#endif // PLATFORM_WINDOWS

// FBX casts null pointer to a reference
THIRD_PARTY_INCLUDES_START
#include <fbxsdk.h>
THIRD_PARTY_INCLUDES_END

#pragma pack(pop)

#ifdef TMP_UNFBX_BACKUP_O_RDONLY
#define _O_RDONLY TMP_FBX_BACKUP_O_RDONLY
#define _O_WRONLY TMP_FBX_BACKUP_O_WRONLY
#undef TMP_UNFBX_BACKUP_O_RDONLY
#undef TMP_UNFBX_BACKUP_O_WRONLY
#endif

#pragma warning( pop )
// end of fbx include

//static const FName DazToUnrealTabName("DazToUnreal");

#define LOCTEXT_NAMESPACE "FDazToUnrealModule"

void FDazToUnrealModule::StartupModule()
{
	 // This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	 FDazToUnrealStyle::Initialize();
	 FDazToUnrealStyle::ReloadTextures();

	 FDazToUnrealCommands::Register();

	 PluginCommands = MakeShareable(new FUICommandList);

	 /*PluginCommands->MapAction(
		 FDazToUnrealCommands::Get().OpenPluginWindow,
		 FExecuteAction::CreateRaw(this, &FDazToUnrealModule::PluginButtonClicked),
		 FCanExecuteAction());*/

	 PluginCommands->MapAction(
		  FDazToUnrealCommands::Get().InstallDazStudioPlugin,
		  FExecuteAction::CreateRaw(this, &FDazToUnrealModule::InstallDazStudioPlugin),
		  FCanExecuteAction());

	 /*PluginCommands->MapAction(
		 FDazToUnrealCommands::Get().InstallSkeletonAssets,
		 FExecuteAction::CreateRaw(this, &FDazToUnrealModule::InstallSkeletonAssetsToProject),
		 FCanExecuteAction());*/

		 /*PluginCommands->MapAction(
			 FDazToUnrealCommands::Get().InstallMaterialAssets,
			 FExecuteAction::CreateRaw(this, &FDazToUnrealModule::InstallMaterialAssetsToProject),
			 FCanExecuteAction());*/

	 FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

	 {
		  TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		  MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FDazToUnrealModule::AddMenuExtension));

		  LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	 }

	 {
		  TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		  ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FDazToUnrealModule::AddToolbarExtension));


		  FString InstallerPath = IPluginManager::Get().FindPlugin("DazToUnreal")->GetBaseDir() / TEXT("Resources") / TEXT("DazToUnrealSetup.exe");
		  FString InstallerAbsolutePath = IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead(*InstallerPath);

		  FString DazStudioPluginPath = IPluginManager::Get().FindPlugin("DazToUnreal")->GetBaseDir() / TEXT("Resources") / TEXT("dzunrealbridge.dll");
		  FString DazStudioPluginAbsolutePath = IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead(*InstallerPath);

		  if (FPaths::FileExists(InstallerAbsolutePath)
			  && FPaths::FileExists(DazStudioPluginAbsolutePath))
		  {
			  LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
		  }
	 }

	 /*FGlobalTabmanager::Get()->RegisterNomadTabSpawner(DazToUnrealTabName, FOnSpawnTab::CreateRaw(this, &FDazToUnrealModule::OnSpawnPluginTab))
		 .SetDisplayName(LOCTEXT("FDazToUnrealTabTitle", "DazToUnreal"))
		 .SetMenuType(ETabSpawnerMenuType::Hidden);*/

	 StartupUDPListener();
}

void FDazToUnrealModule::ShutdownModule()
{
	 // This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	 // we call this function before unloading the module.
	 FDazToUnrealStyle::Shutdown();

	 FDazToUnrealCommands::Unregister();

	 //FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(DazToUnrealTabName);
}

/*TSharedRef<SDockTab> FDazToUnrealModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FDazToUnrealModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("DazToUnreal.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
}*/

//void FDazToUnrealModule::PluginButtonClicked()
//{
	//FGlobalTabmanager::Get()->InvokeTab(DazToUnrealTabName);
//}

void FDazToUnrealModule::AddMenuExtension(FMenuBuilder& Builder)
{
	 Builder.AddMenuEntry(FDazToUnrealCommands::Get().OpenPluginWindow);
}

void FDazToUnrealModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	 //Builder.AddToolBarButton(FDazToUnrealCommands::Get().OpenPluginWindow);
	 Builder.AddComboButton(
		  FUIAction(),
		  FOnGetContent::CreateRaw(this, &FDazToUnrealModule::MakeDazToUnrealToolbarMenu, PluginCommands),
		  LOCTEXT("DazToUnrealCombo", "DazToUnreal"),
		  LOCTEXT("DazToUnrealCombo_ToolTip", "Actions for DazToUnreal"),
		  FSlateIcon(FDazToUnrealStyle::GetStyleSetName(), "DazToUnreal.ToolBar"),
		  false,
		  "LevelToolbarQuickSettings"
	 );
}

TSharedRef<SWidget> FDazToUnrealModule::MakeDazToUnrealToolbarMenu(TSharedPtr<FUICommandList> DazToUnrealCommandList)
{
	 FMenuBuilder MenuBuilder(true, DazToUnrealCommandList);

	 MenuBuilder.AddMenuEntry(FDazToUnrealCommands::Get().InstallDazStudioPlugin);
	 //MenuBuilder.AddMenuEntry(FDazToUnrealCommands::Get().InstallSkeletonAssets);
	 //MenuBuilder.AddMenuEntry(FDazToUnrealCommands::Get().InstallMaterialAssets);

	 return MenuBuilder.MakeWidget();
}

void FDazToUnrealModule::StartupUDPListener()
{
	 const UDazToUnrealSettings* CachedSettings = GetDefault<UDazToUnrealSettings>();

	 FIPv4Endpoint Endpoint(FIPv4Address::InternalLoopback, CachedSettings->Port);
	 ServerSocket = FUdpSocketBuilder(TEXT("DazToUnrealServerSocket"))
		  .AsNonBlocking()
		  .AsReusable()
		  .BoundToEndpoint(Endpoint);

	 TickDelegate = FTickerDelegate::CreateRaw(this, &FDazToUnrealModule::Tick);
	 TickDelegateHandle = FTicker::GetCoreTicker().AddTicker(TickDelegate, 1.0f);
}
void FDazToUnrealModule::ShutdownUDPListener()
{
	 if (ServerSocket != nullptr)
	 {
		  ServerSocket->Close();
		  ServerSocket = nullptr;
	 }
}

bool FDazToUnrealModule::Tick(float DeltaTime)
{
	 // Check from messages from the Daz Studio plugin
	 uint32 BytesPending = 0;
	 if (ServerSocket->HasPendingData(BytesPending))
	 {
		  uint8 Data[2048];
		  ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get();
		  TSharedRef<FInternetAddr> Sender = SocketSubsystem->CreateInternetAddr();

		  // Parse the message
		  int32 BytesRead = 0;
		  if (ServerSocket->RecvFrom(Data, sizeof(Data), BytesRead, *Sender))
		  {
				char CharData[2048];
				memcpy(CharData, Data, BytesRead);
				CharData[BytesRead] = 0;

				FString FileName = ANSI_TO_TCHAR(CharData);
				if (FPaths::FileExists(FileName))
				{
					 FString Json;
					 FFileHelper::LoadFileToString(Json, *FileName);
					 TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(Json);
					 TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
					 if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
					 {
						  ImportFromDaz(JsonObject);
					 }
				}
		  }
	 }
	 return true;
}

bool FDazToUnrealModule::MakeDirectoryAndCheck(FString& Directory)
{
	 IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	 if (!FPaths::DirectoryExists(Directory))
	 {
		  PlatformFile.CreateDirectory(*Directory);
		  if (!FPaths::DirectoryExists(Directory))
		  {
				return false;
		  }
	 }
	 return true;
}

UObject* FDazToUnrealModule::ImportFromDaz(TSharedPtr<FJsonObject> JsonObject)
{
	 TMap<FString, TArray<FDUFTextureProperty>> MaterialProperties;

	 FString FBXPath = JsonObject->GetStringField(TEXT("FBX File"));
	 FString AssetName = FDazToUnrealUtils::SanitizeName(JsonObject->GetStringField(TEXT("Asset Name")));
	 FString ImportFolder = JsonObject->GetStringField(TEXT("Import Folder"));
	 DazAssetType AssetType = DazAssetType::StaticMesh;
	 if (JsonObject->GetStringField(TEXT("Asset Type")) == TEXT("SkeletalMesh"))
		  AssetType = DazAssetType::SkeletalMesh;
	 else if (JsonObject->GetStringField(TEXT("Asset Type")) == TEXT("Animation"))
		  AssetType = DazAssetType::Animation;
	 else if (JsonObject->GetStringField(TEXT("Asset Type")) == TEXT("Environment"))
		 AssetType = DazAssetType::Environment;
	 else if (JsonObject->GetStringField(TEXT("Asset Type")) == TEXT("Pose"))
		 AssetType = DazAssetType::Pose;

	 // Set up the folder paths
	 FString ImportDirectory = FPaths::ProjectDir() / TEXT("Import");
	 if (!ImportFolder.IsEmpty())
	 {
		  ImportDirectory = ImportFolder;
	 }

	 FString ImportCharacterFolder = FPaths::GetPath(FBXPath);
	 FString ImportCharacterTexturesFolder = FPaths::GetPath(FBXPath) / TEXT("Textures");
	 FString ImportCharacterMaterialFolder = FPaths::GetPath(FBXPath) / TEXT("Materials");
	 FString FBXFile = FBXPath;

	 const UDazToUnrealSettings* CachedSettings = GetDefault<UDazToUnrealSettings>();

	 FString DAZImportFolder = CachedSettings->ImportDirectory.Path;
	 FString DAZAnimationImportFolder = CachedSettings->AnimationImportDirectory.Path;
	 FString CharacterFolder = DAZImportFolder / AssetName;
	 FString CharacterTexturesFolder = CharacterFolder / TEXT("Textures");
	 FString CharacterMaterialFolder = CharacterFolder / TEXT("Materials");

	 IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	 FString ContentDirectory = FPaths::ProjectContentDir();

	 FString LocalDAZImportFolder = DAZImportFolder.Replace(TEXT("/Game/"), *ContentDirectory);
	 FString LocalDAZAnimationImportFolder = DAZAnimationImportFolder.Replace(TEXT("/Game/"), *ContentDirectory);
	 FString LocalCharacterFolder = CharacterFolder.Replace(TEXT("/Game/"), *ContentDirectory);
	 FString LocalCharacterTexturesFolder = CharacterTexturesFolder.Replace(TEXT("/Game/"), *ContentDirectory);
	 FString LocalCharacterMaterialFolder = CharacterMaterialFolder.Replace(TEXT("/Game/"), *ContentDirectory);

	 // Make any needed folders.  If any of these fail, don't continue
	 if (!FDazToUnrealUtils::MakeDirectoryAndCheck(ImportDirectory)) return false;
	 if (!FDazToUnrealUtils::MakeDirectoryAndCheck(ImportCharacterFolder)) return false;
	 if (!FDazToUnrealUtils::MakeDirectoryAndCheck(ImportCharacterTexturesFolder)) return false;
	 if (!FDazToUnrealUtils::MakeDirectoryAndCheck(LocalDAZImportFolder)) return false;
	 if (!FDazToUnrealUtils::MakeDirectoryAndCheck(LocalDAZAnimationImportFolder)) return false;
	 if (!FDazToUnrealUtils::MakeDirectoryAndCheck(LocalCharacterFolder)) return false;
	 if (!FDazToUnrealUtils::MakeDirectoryAndCheck(LocalCharacterTexturesFolder)) return false;
	 if (!FDazToUnrealUtils::MakeDirectoryAndCheck(LocalCharacterMaterialFolder)) return false;

	 if (AssetType == DazAssetType::Environment)
	 {
		 FDazToUnrealEnvironment::ImportEnvironment(JsonObject);
		 return nullptr;
	 }

	 // If there isn't an FBX file, stop
	 if (!FPaths::FileExists(FBXFile))
	 {
		  return false;
	 }

	 // Load subdivision info
	 TMap<FString, int> SubdivisionLevels;
	 TArray<TSharedPtr<FJsonValue>> sdList = JsonObject->GetArrayField(TEXT("Subdivisions"));
	 for (int32 i = 0; i < sdList.Num(); i++)
	 {
		  TSharedPtr<FJsonObject> subdivision = sdList[i]->AsObject();
		  SubdivisionLevels.Add(subdivision->GetStringField(TEXT("Asset Name")), subdivision->GetIntegerField(TEXT("Value")));
	 }

	 // Use the maps file to find the textures to load
	 TMap<FString, FString> TextureFileSourceToTarget;
	 TArray<FString> IntermediateMaterials;

	 TArray<TSharedPtr<FJsonValue>> matList = JsonObject->GetArrayField(TEXT("Materials"));
	 for (int32 i = 0; i < matList.Num(); i++)
	 {
		  TSharedPtr<FJsonObject> material = matList[i]->AsObject();
		  int32 Version = material->GetIntegerField(TEXT("Version"));

		  // Version 1 "Version, Material, Type, Color, Opacity, File"
		  if (Version == 1)
		  {
				FString MaterialName = AssetName + TEXT("_") + material->GetStringField(TEXT("Material Name"));
				MaterialName = FDazToUnrealUtils::SanitizeName(MaterialName);
				FString TexturePath = material->GetStringField(TEXT("Texture"));
				FString TextureName = FDazToUnrealUtils::SanitizeName(FPaths::GetBaseFilename(TexturePath));

				if (!MaterialProperties.Contains(MaterialName))
				{
					 MaterialProperties.Add(MaterialName, TArray<FDUFTextureProperty>());
				}
				FDUFTextureProperty Property;
				Property.Name = material->GetStringField(TEXT("Name"));
				Property.Type = material->GetStringField(TEXT("Data Type"));
				Property.Value = material->GetStringField(TEXT("Value"));
				if (Property.Type == TEXT("Texture"))
				{
					 Property.Type = TEXT("Color");
				}

				MaterialProperties[MaterialName].Add(Property);
				if (!TextureName.IsEmpty())
				{
					 // If a texture is attached add a texture property
					 FDUFTextureProperty TextureProperty;
					 TextureProperty.Name = material->GetStringField(TEXT("Name")) + TEXT(" Texture");
					 TextureProperty.Type = TEXT("Texture");

					 if (!TextureFileSourceToTarget.Contains(TexturePath))
					 {
						  int32 TextureCount = 0;
						  FString NewTextureName = FString::Printf(TEXT("%s_%02d_%s"), *TextureName, TextureCount, *AssetName);
						  while (TextureFileSourceToTarget.FindKey(NewTextureName) != nullptr)
						  {
								TextureCount++;
								NewTextureName = FString::Printf(TEXT("%s_%02d_%s"), *TextureName, TextureCount, *AssetName);
						  }
						  TextureFileSourceToTarget.Add(TexturePath, NewTextureName);
					 }

					 TextureProperty.Value = TextureFileSourceToTarget[TexturePath];
					 MaterialProperties[MaterialName].Add(TextureProperty);
					 //TextureFiles.AddUnique(TexturePath);

					 // and a switch property for things like Specular that could come from different channels
					 FDUFTextureProperty SwitchProperty;
					 SwitchProperty.Name = material->GetStringField(TEXT("Name")) + TEXT(" Texture Active");
					 SwitchProperty.Type = TEXT("Switch");
					 SwitchProperty.Value = TEXT("true");
					 MaterialProperties[MaterialName].Add(SwitchProperty);
				}
		  }

		  // Version 2 "Version, ObjectName, Material, Type, Color, Opacity, File"
		  if (Version == 2)
		  {
				FString ObjectName = material->GetStringField(TEXT("Asset Name"));
				ObjectName = FDazToUnrealUtils::SanitizeName(ObjectName);
				IntermediateMaterials.AddUnique(ObjectName + TEXT("_BaseMat"));
				FString ShaderName = material->GetStringField(TEXT("Material Type"));
				FString MaterialName = AssetName + TEXT("_") + material->GetStringField(TEXT("Material Name"));
				MaterialName = FDazToUnrealUtils::SanitizeName(MaterialName);
				FString TexturePath = material->GetStringField(TEXT("Texture"));
				FString TextureName = FDazToUnrealUtils::SanitizeName(FPaths::GetBaseFilename(TexturePath));

				if (!MaterialProperties.Contains(MaterialName))
				{
					 MaterialProperties.Add(MaterialName, TArray<FDUFTextureProperty>());
				}
				FDUFTextureProperty Property;
				Property.Name = material->GetStringField(TEXT("Name"));
				Property.Type = material->GetStringField(TEXT("Data Type"));
				Property.Value = material->GetStringField(TEXT("Value"));
				Property.ObjectName = ObjectName;
				Property.ShaderName = ShaderName;
				if (Property.Type == TEXT("Texture"))
				{
					 Property.Type = TEXT("Color");
				}
				
				// Properties that end with Enabled are switches for functionality
				if (Property.Name.EndsWith(TEXT(" Enable")))
				{
					Property.Type = TEXT("Switch");
					if (Property.Value == TEXT("0"))
					{
						Property.Value = TEXT("false");
					}
					else
					{
						Property.Value = TEXT("true");
					}
				}

				MaterialProperties[MaterialName].Add(Property);
				if (!TextureName.IsEmpty())
				{
					 // If a texture is attached add a texture property
					 FDUFTextureProperty TextureProperty;
					 TextureProperty.Name = material->GetStringField(TEXT("Name")) + TEXT(" Texture");
					 TextureProperty.Type = TEXT("Texture");
					 TextureProperty.ObjectName = ObjectName;
					 TextureProperty.ShaderName = ShaderName;

					 if (!TextureFileSourceToTarget.Contains(TexturePath))
					 {
						  int32 TextureCount = 0;
						  FString NewTextureName = FString::Printf(TEXT("%s_%02d_%s"), *TextureName, TextureCount, *AssetName);
						  while (TextureFileSourceToTarget.FindKey(NewTextureName) != nullptr)
						  {
								TextureCount++;
								NewTextureName = FString::Printf(TEXT("%s_%02d_%s"), *TextureName, TextureCount, *AssetName);
						  }
						  TextureFileSourceToTarget.Add(TexturePath, NewTextureName);
					 }

					 TextureProperty.Value = TextureFileSourceToTarget[TexturePath];
					 MaterialProperties[MaterialName].Add(TextureProperty);
					 //TextureFiles.AddUnique(TexturePath);

					 // and a switch property for things like Specular that could come from different channels
					 FDUFTextureProperty SwitchProperty;
					 SwitchProperty.Name = material->GetStringField(TEXT("Name")) + TEXT(" Texture Active");
					 SwitchProperty.Type = TEXT("Switch");
					 SwitchProperty.Value = TEXT("true");
					 SwitchProperty.ObjectName = ObjectName;
					 SwitchProperty.ShaderName = ShaderName;
					 MaterialProperties[MaterialName].Add(SwitchProperty);
				}
		  }
	 }

	 // Load the FBX file
	 FbxManager* SdkManager = FbxManager::Create();

	 // create an IOSettings object
	 FbxIOSettings* ios = FbxIOSettings::Create(SdkManager, IOSROOT);
	 SdkManager->SetIOSettings(ios);

	 // Create the geometry converter
	 FbxGeometryConverter* GeometryConverter = new FbxGeometryConverter(SdkManager);

	 FbxImporter* Importer = FbxImporter::Create(SdkManager, "");
	 const bool bImportStatus = Importer->Initialize(TCHAR_TO_UTF8(*FBXFile));
	 FbxScene* Scene = FbxScene::Create(SdkManager, "");
	 Importer->Import(Scene);

	 FbxNode* RootNode = Scene->GetRootNode();

	 // Find the root bone.  There should only be one bone off the scene root
	 FbxNode* RootBone = nullptr;
	 FString RootBoneName = TEXT("");
	 for (int ChildIndex = 0; ChildIndex < RootNode->GetChildCount(); ++ChildIndex)
	 {
		  FbxNode* ChildNode = RootNode->GetChild(ChildIndex);
		  FbxNodeAttribute* Attr = ChildNode->GetNodeAttribute();
		  if (Attr && Attr->GetAttributeType() == FbxNodeAttribute::eSkeleton)
		  {
				RootBone = ChildNode;
				RootBoneName = UTF8_TO_TCHAR(RootBone->GetName());
				RootBone->SetName(TCHAR_TO_UTF8(TEXT("root")));
				Attr->SetName(TCHAR_TO_UTF8(TEXT("root")));
				break;
		  }
	 }

	 // Daz Studio puts the base bone rotations in a different place than Unreal expects them.
	 if (CachedSettings->FixBoneRotationsOnImport && AssetType == DazAssetType::SkeletalMesh && RootBone)
	 {
		FDazToUnrealFbx::FixClusterTranformLinks(Scene, RootBone);
	 }

	 // If this is a skeleton mesh, but a root bone wasn't found, it may be a scene under a group node or something similar
	 // So create a root node.
	 if (AssetType == DazAssetType::SkeletalMesh && RootBone == nullptr)
	 {
		  RootBoneName = AssetName;

		  FbxSkeleton* NewRootNodeAttribute = FbxSkeleton::Create(Scene, TCHAR_TO_UTF8(TEXT("root")));
		  NewRootNodeAttribute->SetSkeletonType(FbxSkeleton::eRoot);
		  NewRootNodeAttribute->Size.Set(1.0);
		  RootBone = FbxNode::Create(Scene, TCHAR_TO_UTF8(TEXT("root")));
		  RootBone->SetNodeAttribute(NewRootNodeAttribute);
		  RootBone->LclTranslation.Set(FbxVector4(0.0, 00.0, 0.0));


		  for (int ChildIndex = RootNode->GetChildCount() - 1; ChildIndex >= 0; --ChildIndex)
		  {
				FbxNode* ChildNode = RootNode->GetChild(ChildIndex);
				RootBone->AddChild(ChildNode);
				if (FbxSkeleton* ChildSkeleton = ChildNode->GetSkeleton())
				{
					 if (ChildSkeleton->GetSkeletonType() == FbxSkeleton::eRoot)
					 {
						  ChildSkeleton->SetSkeletonType(FbxSkeleton::eLimb);
					 }
				}
		  }

		  RootNode->AddChild(RootBone);
	 }

	 FDazToUnrealFbx::RenameDuplicateBones(RootBone);

	 struct local
	 {
		  static void GetWeights(FbxNode* SceneNode, TMap<int, TArray<int>>& VertexPolygons, TMap<int, double>& ClusterWeights, FbxMatrix TargetMatrix, int SearchFromVertex, TArray<int>& TouchedPolygons, TArray<int>& TouchedVertices, double& WeightsOut, double& DistancesOut, int32 Depth)
		  {
				FbxVector4 TargetPosition;
				FbxQuaternion TargetNormal;
				FbxVector4 TargetShearing;
				FbxVector4 TargetScale;
				double Sign;
				TargetMatrix.GetElements(TargetPosition, TargetNormal, TargetShearing, TargetScale, Sign);

				FbxVector4* VertexLocations = SceneNode->GetMesh()->GetControlPoints();
				for (int PolygonIndex : VertexPolygons[SearchFromVertex])
				{
					 if (TouchedPolygons.Contains(PolygonIndex)) continue;
					 TouchedPolygons.Add(PolygonIndex);
					 FbxVector4 NeedWeightVertexNormal;
					 /*for (int VertexIndex = 0; VertexIndex < SceneNode->GetMesh()->GetPolygonSize(PolygonIndex); ++VertexIndex)
					 {
						 int Vertex = SceneNode->GetMesh()->GetPolygonVertex(PolygonIndex, VertexIndex);
						 if (Vertex == SearchFromVertex)
						 {
							 SceneNode->GetMesh()->GetPolygonVertexNormal(PolygonIndex, VertexIndex, NeedWeightVertexNormal);
						 }
					 }*/
					 // Set the vertices with no weight, to be the average of the ones with weight.
					 for (int VertexIndex = 0; VertexIndex < SceneNode->GetMesh()->GetPolygonSize(PolygonIndex); ++VertexIndex)
					 {
						  int Vertex = SceneNode->GetMesh()->GetPolygonVertex(PolygonIndex, VertexIndex);
						  if (TouchedVertices.Contains(Vertex)) continue;
						  TouchedVertices.Add(Vertex);
						  if (ClusterWeights.Contains(Vertex))
						  {
								FbxVector4 CompareVertexNormal;
								SceneNode->GetMesh()->GetPolygonVertexNormal(PolygonIndex, VertexIndex, CompareVertexNormal);
								//double DotProduct = CompareVertexNormal.DotProduct(NeedWeightVertexNormal);
								FbxVector4 CompareLocation = VertexLocations[Vertex];
								FbxVector4 CompareScale = FbxVector4(1.0f, 1.0f, 1.0f);
								FbxMatrix CompareMatrix = FbxMatrix(CompareLocation, CompareVertexNormal, CompareScale);
								//CompareLocation.
								FbxMatrix AdjustedMatrix = CompareMatrix * TargetMatrix.Inverse();

								FbxVector4 AdjustedComparePosition;
								FbxQuaternion AdjustedCompareNormal;
								FbxVector4 AdjustedCompareShearing;
								FbxVector4 AdjustedCompareScale;
								double AdjustedCompareSign;
								AdjustedMatrix.GetElements(AdjustedComparePosition, AdjustedCompareNormal, AdjustedCompareShearing, AdjustedCompareScale, AdjustedCompareSign);

								double InverseDotProduct = 1 - AdjustedCompareNormal.DotProduct(TargetNormal);
								double AngleAdjustment = InverseDotProduct * 3.14;
								//AdjustedComparePosition[2] = 0.0;
								//FbxVector4 Test = TargetPosition.;
								//double VertexDistance = AdjustedComparePosition.Length();//AdjustedComparePosition.Distance(TargetPosition);
								double VertexDistance = CompareLocation.Distance(TargetPosition) * AngleAdjustment;
								//VertexDistance = VertexDistance * VertexDistance* VertexDistance* VertexDistance* VertexDistance* VertexDistance* VertexDistance* VertexDistance;
								/*if (DotProduct > 0.0)
								{
									VertexDistance = VertexDistance * DotProduct;
								}*/

								//double AdditionalWeightCount = FurthestDistance / VertexDistance;
								//double AdditionalWeight = AdditionalWeightCount * ClusterWeights[Vertex];
								double AdditionalWeightCount = 1 / VertexDistance;
								double AdditionalWeight = ClusterWeights[Vertex] / VertexDistance;

								WeightsOut += AdditionalWeight;
								DistancesOut += AdditionalWeightCount;
						  }

						  if (Depth > 1)
						  {
								GetWeights(SceneNode, VertexPolygons, ClusterWeights, TargetMatrix, Vertex, TouchedPolygons, TouchedVertices, WeightsOut, DistancesOut, Depth - 1);
						  }
					 }
				}
		  }

		  static void FindVertexNeedingWeight(int SearchFromVertex, FbxNode* SceneNode, TArray<int>& NeedWeights, TMap<int, TArray<int>>& VertexPolygons, TArray<int>& NoWeights, int32 Depth)
		  {
				for (int PolygonIndex : VertexPolygons[SearchFromVertex])
				{
					 for (int VertexIndex = 0; VertexIndex < SceneNode->GetMesh()->GetPolygonSize(PolygonIndex); ++VertexIndex)
					 {
						  int Vertex = SceneNode->GetMesh()->GetPolygonVertex(PolygonIndex, VertexIndex);
						  if (NoWeights.Contains(Vertex))
						  {
								NeedWeights.AddUnique(Vertex);
						  }

						  if (Depth > 1)
						  {
								FindVertexNeedingWeight(Vertex, SceneNode, NeedWeights, VertexPolygons, NoWeights, Depth - 1);
						  }
					 }
				}
		  }
	 };

	 // Detach geometry from the skeleton
	 for (int NodeIndex = 0; NodeIndex < Scene->GetNodeCount(); ++NodeIndex)
	 {
		  FbxNode* SceneNode = Scene->GetNode(NodeIndex);
		  if (SceneNode == nullptr)
		  {
				continue;
		  }
		  FbxGeometry* NodeGeometry = static_cast<FbxGeometry*>(SceneNode->GetMesh());
		  if (NodeGeometry)
		  {
				if (SceneNode->GetParent() &&
					 SceneNode->GetParent()->GetNodeAttribute() &&
					 SceneNode->GetParent()->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eSkeleton)
				{
					 SceneNode->GetParent()->RemoveChild(SceneNode);
					 RootNode->AddChild(SceneNode);
				}
		  }
#if 1
		  if (SubdivisionLevels.Num() > 0)
		  {
				// Create missing weights
				if (NodeGeometry)
				{
					 FString GeometryName = UTF8_TO_TCHAR(SceneNode->GetName());
					 if (!SubdivisionLevels.Contains(GeometryName)) continue;
					 if (SubdivisionLevels[GeometryName] == 0) continue;

					 for (int DeformerIndex = 0; DeformerIndex < NodeGeometry->GetDeformerCount(); ++DeformerIndex)
					 {
						  FbxSkin* Skin = static_cast<FbxSkin*>(NodeGeometry->GetDeformer(DeformerIndex));
						  if (Skin)
						  {

								FbxVector4* VertexLocations = SceneNode->GetMesh()->GetControlPoints();
								TArray<int> NoWeights;
								TArray<int> HasWeights;
								TMap<int, TArray<int>> VertexPolygons;
								TMap<int, FbxVector4> VertexNormals;
								// iterate the polygons
								for (int PolygonIndex = 0; PolygonIndex < SceneNode->GetMesh()->GetPolygonCount(); ++PolygonIndex)
								{

									 for (int VertexIndex = 0; VertexIndex < SceneNode->GetMesh()->GetPolygonSize(PolygonIndex); ++VertexIndex)
									 {
										  int Vertex = SceneNode->GetMesh()->GetPolygonVertex(PolygonIndex, VertexIndex);
										  if (!VertexPolygons.Contains(Vertex))
										  {
												TArray<int> PolygonList;
												VertexPolygons.Add(Vertex, PolygonList);
										  }
										  VertexPolygons[Vertex].Add(PolygonIndex);
										  if (HasWeights.Contains(Vertex)) continue;
										  if (NoWeights.Contains(Vertex)) continue;

										  FbxVector4 VertexNormal;
										  Vertex, SceneNode->GetMesh()->GetPolygonVertexNormal(PolygonIndex, VertexIndex, VertexNormal);
										  VertexNormals.Add(Vertex, VertexNormal);

										  NoWeights.AddUnique(Vertex);
									 }
								}

								for (int ClusterIndex = 0; ClusterIndex < Skin->GetClusterCount(); ++ClusterIndex)
								{
									 FbxCluster* Cluster = Skin->GetCluster(ClusterIndex);

									 for (int ClusterVertexIndex = 0; ClusterVertexIndex < Cluster->GetControlPointIndicesCount(); ++ClusterVertexIndex)
									 {
										  int Vertex = Cluster->GetControlPointIndices()[ClusterVertexIndex];
										  //if (Cluster->GetControlPointIndices()[ClusterVertexIndex] == Vertex)
										  {
												NoWeights.Remove(Vertex);
												HasWeights.AddUnique(Vertex);
										  }
									 }

								}

								if (HasWeights.Num() > 0 && NoWeights.Num() > 0)
								{
									 //for (int NoWeightVertex : NoWeights)
									 {
										  FScopedSlowTask SubdivisionTask(Skin->GetClusterCount(), LOCTEXT("DazToUnrealSudAutoWeightTask", "Creating Subdivision Weights for Cluster:"));

										  for (int ClusterIndex = 0; ClusterIndex < Skin->GetClusterCount(); ++ClusterIndex)
										  {
												SubdivisionTask.EnterProgressFrame();
												FbxCluster* Cluster = Skin->GetCluster(ClusterIndex);
												int ClusterVertexCount = Cluster->GetControlPointIndicesCount();

												//Make a map of all the weights for the cluster
												TMap<int, double> ClusterWeights;
												//TMap<int, double> ClusterVertex;
												for (int ClusterVertexIndex = 0; ClusterVertexIndex < ClusterVertexCount; ++ClusterVertexIndex)
												{
													 int WeightVertex = Cluster->GetControlPointIndices()[ClusterVertexIndex];
													 double Weight = Cluster->GetControlPointWeights()[ClusterVertexIndex];
													 ClusterWeights.Add(WeightVertex, Weight);
													 //ClusterVertex.Add(ClusterVertexIndex, WeightVertex);
												}

												TMap<int, double> WeightsToAdd;
												for (int ClusterVertexIndex = 0; ClusterVertexIndex < ClusterVertexCount; ++ClusterVertexIndex)
												{
													 int WeightVertex = Cluster->GetControlPointIndices()[ClusterVertexIndex];
													 //if(NoWeights.Contains(NoWeightVertex))
													 {
														  TArray<int> NeedWeights;
														  local::FindVertexNeedingWeight(WeightVertex, SceneNode, NeedWeights, VertexPolygons, NoWeights, 1);
														  /*for (int PolygonIndex : VertexPolygons[WeightVertex])
														  {
															  for (int VertexIndex = 0; VertexIndex < SceneNode->GetMesh()->GetPolygonSize(PolygonIndex); ++VertexIndex)
															  {
																  int Vertex = SceneNode->GetMesh()->GetPolygonVertex(PolygonIndex, VertexIndex);
																  if (NoWeights.Contains(Vertex))
																  {
																	  NeedWeights.AddUnique(Vertex);
																  }
															  }
														  }*/

														  for (int NeedWeightVertex : NeedWeights)
														  {
																double WeightCount = 0.0f;
																double Weight = 0.0f;

																FbxVector4 NeedWeightVertexLocation = VertexLocations[NeedWeightVertex];
																TArray<int> TouchedPolygons;
																TArray<int> TouchedVertices;
																FbxVector4 ScaleVector = FbxVector4(1.0, 1.0, 1.0);
																FbxMatrix VertexMatrix = FbxMatrix(NeedWeightVertexLocation, VertexNormals[NeedWeightVertex], ScaleVector);
																local::GetWeights(SceneNode, VertexPolygons, ClusterWeights, VertexMatrix, NeedWeightVertex, TouchedPolygons, TouchedVertices, Weight, WeightCount, 1);



																/*for (int PolygonIndex : VertexPolygons[NeedWeightVertex])
																{
																	FbxVector4 NeedWeightVertexNormal;
																	for (int VertexIndex = 0; VertexIndex < SceneNode->GetMesh()->GetPolygonSize(PolygonIndex); ++VertexIndex)
																	{
																		int Vertex = SceneNode->GetMesh()->GetPolygonVertex(PolygonIndex, VertexIndex);
																		if (Vertex == NeedWeightVertex)
																		{
																			SceneNode->GetMesh()->GetPolygonVertexNormal(PolygonIndex, VertexIndex, NeedWeightVertexNormal);
																		}
																	}
																	// Set the vertices with no weight, to be the average of the ones with weight.
																	for (int VertexIndex = 0; VertexIndex < SceneNode->GetMesh()->GetPolygonSize(PolygonIndex); ++VertexIndex)
																	{
																		int Vertex = SceneNode->GetMesh()->GetPolygonVertex(PolygonIndex, VertexIndex);
																		if (ClusterWeights.Contains(Vertex))
																		{
																			FbxVector4 CompareVertexNormal;
																			SceneNode->GetMesh()->GetPolygonVertexNormal(PolygonIndex, VertexIndex, CompareVertexNormal);
																			double DotProduct = CompareVertexNormal.DotProduct(NeedWeightVertexNormal);
																			FbxVector4 CompareLocation = VertexLocations[Vertex];
																			double VertexDistance = NeedWeightVertexLocation.Distance(CompareLocation);
																			if (DotProduct > 0.0)
																			{
																				VertexDistance = VertexDistance * DotProduct;
																			}

																			//double AdditionalWeightCount = FurthestDistance / VertexDistance;
																			//double AdditionalWeight = AdditionalWeightCount * ClusterWeights[Vertex];
																			double AdditionalWeightCount = 1 / VertexDistance;
																			double AdditionalWeight = ClusterWeights[Vertex] /  VertexDistance;

																			Weight += AdditionalWeight;
																			WeightCount += AdditionalWeightCount;
																		}
																	}
																}*/
																if (WeightCount > 0)
																{
																	 WeightsToAdd.Add(NeedWeightVertex, Weight / (double)WeightCount);
																	 //Cluster->AddControlPointIndex(NeedWeightVertex, Weight / (double)WeightCount);
																}
														  }
													 }
												}

												for (auto WeightToAdd : WeightsToAdd)
												{
													 Cluster->AddControlPointIndex(WeightToAdd.Key, WeightToAdd.Value);
												}
										  }
									 }
								}
						  }
					 }
				}
		  }
#endif
	 }

	 // Add IK bones
	 if (RootBone)
	 {
		  // ik_foot_root
		  FbxNode* IKRootNode = Scene->FindNodeByName(TCHAR_TO_UTF8(TEXT("ik_foot_root")));
		  if (!IKRootNode)
		  {
				// Create IK Root 
				FbxSkeleton* IKRootNodeAttribute = FbxSkeleton::Create(Scene, TCHAR_TO_UTF8(TEXT("ik_foot_root")));
				IKRootNodeAttribute->SetSkeletonType(FbxSkeleton::eLimbNode);
				IKRootNodeAttribute->Size.Set(1.0);
				IKRootNode = FbxNode::Create(Scene, TCHAR_TO_UTF8(TEXT("ik_foot_root")));
				IKRootNode->SetNodeAttribute(IKRootNodeAttribute);
				IKRootNode->LclTranslation.Set(FbxVector4(0.0, 00.0, 0.0));
				RootBone->AddChild(IKRootNode);
		  }

		  // ik_foot_l
		  FbxNode* IKFootLNode = Scene->FindNodeByName(TCHAR_TO_UTF8(TEXT("ik_foot_l")));
		  FbxNode* FootLNode = Scene->FindNodeByName(TCHAR_TO_UTF8(TEXT("lFoot")));
		  if (!IKFootLNode && FootLNode)
		  {
				// Create IK Root 
				FbxSkeleton* IKFootLNodeAttribute = FbxSkeleton::Create(Scene, TCHAR_TO_UTF8(TEXT("ik_foot_l")));
				IKFootLNodeAttribute->SetSkeletonType(FbxSkeleton::eLimbNode);
				IKFootLNodeAttribute->Size.Set(1.0);
				IKFootLNode = FbxNode::Create(Scene, TCHAR_TO_UTF8(TEXT("ik_foot_l")));
				IKFootLNode->SetNodeAttribute(IKFootLNodeAttribute);
				FbxVector4 FootLocation = FootLNode->EvaluateGlobalTransform().GetT();
				IKFootLNode->LclTranslation.Set(FootLocation);
				IKRootNode->AddChild(IKFootLNode);
		  }

		  // ik_foot_r
		  FbxNode* IKFootRNode = Scene->FindNodeByName(TCHAR_TO_UTF8(TEXT("ik_foot_r")));
		  FbxNode* FootRNode = Scene->FindNodeByName(TCHAR_TO_UTF8(TEXT("rFoot")));
		  if (!IKFootRNode && FootRNode)
		  {
				// Create IK Root 
				FbxSkeleton* IKFootRNodeAttribute = FbxSkeleton::Create(Scene, TCHAR_TO_UTF8(TEXT("ik_foot_r")));
				IKFootRNodeAttribute->SetSkeletonType(FbxSkeleton::eLimbNode);
				IKFootRNodeAttribute->Size.Set(1.0);
				IKFootRNode = FbxNode::Create(Scene, TCHAR_TO_UTF8(TEXT("ik_foot_r")));
				IKFootRNode->SetNodeAttribute(IKFootRNodeAttribute);
				FbxVector4 FootLocation = FootRNode->EvaluateGlobalTransform().GetT();
				IKFootRNode->LclTranslation.Set(FootLocation);
				IKRootNode->AddChild(IKFootRNode);
		  }

		  // ik_hand_root
		  FbxNode* IKHandRootNode = Scene->FindNodeByName(TCHAR_TO_UTF8(TEXT("ik_hand_root")));
		  if (!IKHandRootNode)
		  {
				// Create IK Root 
				FbxSkeleton* IKHandRootNodeAttribute = FbxSkeleton::Create(Scene, TCHAR_TO_UTF8(TEXT("ik_hand_root")));
				IKHandRootNodeAttribute->SetSkeletonType(FbxSkeleton::eLimbNode);
				IKHandRootNodeAttribute->Size.Set(1.0);
				IKHandRootNode = FbxNode::Create(Scene, TCHAR_TO_UTF8(TEXT("ik_hand_root")));
				IKHandRootNode->SetNodeAttribute(IKHandRootNodeAttribute);
				IKHandRootNode->LclTranslation.Set(FbxVector4(0.0, 00.0, 0.0));
				RootBone->AddChild(IKHandRootNode);
		  }

		  // ik_hand_gun
		  FbxNode* IKHandGunNode = Scene->FindNodeByName(TCHAR_TO_UTF8(TEXT("ik_hand_gun")));
		  FbxNode* HandRNode = Scene->FindNodeByName(TCHAR_TO_UTF8(TEXT("rHand")));
		  if (!IKHandGunNode && HandRNode)
		  {
				// Create IK Root 
				FbxSkeleton* IKHandGunNodeAttribute = FbxSkeleton::Create(Scene, TCHAR_TO_UTF8(TEXT("ik_hand_gun")));
				IKHandGunNodeAttribute->SetSkeletonType(FbxSkeleton::eLimbNode);
				IKHandGunNodeAttribute->Size.Set(1.0);
				IKHandGunNode = FbxNode::Create(Scene, TCHAR_TO_UTF8(TEXT("ik_hand_gun")));
				IKHandGunNode->SetNodeAttribute(IKHandGunNodeAttribute);
				FbxVector4 HandLocation = HandRNode->EvaluateGlobalTransform().GetT();
				IKHandGunNode->LclTranslation.Set(HandLocation);
				IKHandRootNode->AddChild(IKHandGunNode);
		  }

		  // ik_hand_r
		  FbxNode* IKHandRNode = Scene->FindNodeByName(TCHAR_TO_UTF8(TEXT("ik_hand_r")));
		  //FbxNode* HandRNode = Scene->FindNodeByName(TCHAR_TO_UTF8(TEXT("rHand")));
		  //FbxNode* IKHandGunNode = Scene->FindNodeByName(TCHAR_TO_UTF8(TEXT("ik_hand_gun")));
		  if (!IKHandRNode && HandRNode && IKHandGunNode)
		  {
				// Create IK Root 
				FbxSkeleton* IKHandRNodeAttribute = FbxSkeleton::Create(Scene, TCHAR_TO_UTF8(TEXT("ik_hand_r")));
				IKHandRNodeAttribute->SetSkeletonType(FbxSkeleton::eLimbNode);
				IKHandRNodeAttribute->Size.Set(1.0);
				IKHandRNode = FbxNode::Create(Scene, TCHAR_TO_UTF8(TEXT("ik_hand_r")));
				IKHandRNode->SetNodeAttribute(IKHandRNodeAttribute);
				IKHandRNode->LclTranslation.Set(FbxVector4(0.0, 00.0, 0.0));
				IKHandGunNode->AddChild(IKHandRNode);
		  }

		  // ik_hand_l
		  FbxNode* IKHandLNode = Scene->FindNodeByName(TCHAR_TO_UTF8(TEXT("ik_hand_l")));
		  FbxNode* HandLNode = Scene->FindNodeByName(TCHAR_TO_UTF8(TEXT("lHand")));
		  //FbxNode* IKHandGunNode = Scene->FindNodeByName(TCHAR_TO_UTF8(TEXT("ik_hand_gun")));
		  if (!IKHandLNode && HandLNode && IKHandGunNode)
		  {
				// Create IK Root 
				FbxSkeleton* IKHandRNodeAttribute = FbxSkeleton::Create(Scene, TCHAR_TO_UTF8(TEXT("ik_hand_l")));
				IKHandRNodeAttribute->SetSkeletonType(FbxSkeleton::eLimbNode);
				IKHandRNodeAttribute->Size.Set(1.0);
				IKHandLNode = FbxNode::Create(Scene, TCHAR_TO_UTF8(TEXT("ik_hand_l")));
				IKHandLNode->SetNodeAttribute(IKHandRNodeAttribute);
				FbxVector4 HandLocation = HandLNode->EvaluateGlobalTransform().GetT();
				FbxVector4 ParentLocation = IKHandGunNode->EvaluateGlobalTransform().GetT();
				IKHandLNode->LclTranslation.Set(HandLocation - ParentLocation);
				IKHandGunNode->AddChild(IKHandLNode);
		  }
	 }

	 // Get a list of morph name mappings
	 TMap<FString, FString> MorphMappings;
	 TArray<TSharedPtr<FJsonValue>> morphList = JsonObject->GetArrayField(TEXT("Morphs"));
	 for (int32 i = 0; i < morphList.Num(); i++)
	 {
		  TSharedPtr<FJsonObject> morph = morphList[i]->AsObject();
		  FString MorphName = morph->GetStringField(TEXT("Name"));
		  FString MorphLabel = morph->GetStringField(TEXT("Label"));

		  // Daz Studio seems to strip the part of the name before a period when exporting the morph to FBX
		  if (MorphName.Contains(TEXT(".")))
		  {
			  FString Left;
			  MorphName.Split(TEXT("."), &Left, &MorphName);
		  }

		  if (CachedSettings->UseInternalMorphName)
		  {
			  MorphMappings.Add(MorphName, MorphName);
		  }
		  else
		  {
			  MorphMappings.Add(MorphName, MorphLabel);
		  }
	 }

	 // Get a list of morph name mappings
	 TArray<FString> PoseNameList;
	 const TArray<TSharedPtr<FJsonValue>>* PoseList;
	 if (JsonObject->TryGetArrayField(TEXT("Poses"), PoseList))
	 {
		 PoseNameList.Add(TEXT("ReferencePose"));
		 for (int32 i = 0; i < PoseList->Num(); i++)
		 {
			 TSharedPtr<FJsonObject> Pose = (*PoseList)[i]->AsObject();
			 FString PoseName = Pose->GetStringField(TEXT("Name"));
			 FString PoseLabel = Pose->GetStringField(TEXT("Label"));

			 PoseNameList.Add(PoseLabel);
		 }
	 }

	 // Combine clothing and body morphs
	 for (int NodeIndex = 0; NodeIndex < Scene->GetNodeCount(); ++NodeIndex)
	 {
		  FbxNode* SceneNode = Scene->GetNode(NodeIndex);
		  if (SceneNode == nullptr)
		  {
				continue;
		  }
		  FbxGeometry* NodeGeometry = static_cast<FbxGeometry*>(SceneNode->GetMesh());
		  if (NodeGeometry)
		  {

				const int32 BlendShapeDeformerCount = NodeGeometry->GetDeformerCount(FbxDeformer::eBlendShape);
				for (int32 BlendShapeIndex = 0; BlendShapeIndex < BlendShapeDeformerCount; ++BlendShapeIndex)
				{
					 FbxBlendShape* BlendShape = (FbxBlendShape*)NodeGeometry->GetDeformer(BlendShapeIndex, FbxDeformer::eBlendShape);
					 const int32 BlendShapeChannelCount = BlendShape->GetBlendShapeChannelCount();

					 TArray<FbxBlendShapeChannel*> ChannelsToRemove;
					 for (int32 ChannelIndex = 0; ChannelIndex < BlendShapeChannelCount; ++ChannelIndex)
					 {
						  FbxBlendShapeChannel* Channel = BlendShape->GetBlendShapeChannel(ChannelIndex);
						  if (Channel)
						  {
								FString ChannelName = UTF8_TO_TCHAR(Channel->GetNameOnly());
								FString NewChannelName, Extra;
								ChannelName.Split(TEXT("__"), &Extra, &NewChannelName);
								if (MorphMappings.Contains(NewChannelName))
								{
									 NewChannelName = MorphMappings[NewChannelName];
									 Channel->SetName(TCHAR_TO_UTF8(*NewChannelName));
								}
								else
								{
									 ChannelsToRemove.AddUnique(Channel);
								}
						  }
					 }
					 for (FbxBlendShapeChannel* Channel : ChannelsToRemove)
					 {
						  BlendShape->RemoveBlendShapeChannel(Channel);
					 }
				}
		  }
	 }

	 // Get a list of Materials with name collisions
	 /*TArray<FString> UniqueMaterialNames;
	 TArray<FString> DuplicateMaterialNames;
	 for (int32 MaterialIndex = Scene->GetMaterialCount() - 1; MaterialIndex >= 0; --MaterialIndex)
	 {
		 //MaterialProperties.Add(MaterialName
		 FbxSurfaceMaterial *Material = Scene->GetMaterial(MaterialIndex);
		 FString OriginalMaterialName = UTF8_TO_TCHAR(Material->GetName());
		 if (UniqueMaterialNames.Contains(OriginalMaterialName))
		 {
			 DuplciateMaterialNames.Add(OriginalMaterialName);
		 }
		 UniqueMaterialNames.AddUnique(OriginalMaterialName);
	 }

	 // Rename any duplicates adding their shape name
	 for (int32 MeshIndex = Scene->GetGeometryCount() - 1; MeshIndex >= 0; --MeshIndex)
	 {
		 FbxGeometry* Geometry = Scene->GetGeometry(MeshIndex);
		 FbxNode* GeometryNode = Geometry->GetNode();
		 for (int32 MaterialIndex = GeometryNode->GetMaterialCount() - 1; MaterialIndex >= 0; --MaterialIndex)
		 {
			 FbxSurfaceMaterial *Material = GeometryNode->GetMaterial(MaterialIndex);
			 FString OriginalMaterialName = UTF8_TO_TCHAR(Material->GetName());
			 if (DuplciateMaterialNames.Contains(OriginalMaterialName))
			 {
				 FString NewMaterialName = GeometryNode
			 }
		 }
	 }*/

	 // Rename Materials
	 FbxArray<FbxSurfaceMaterial*> MaterialArray;
	 Scene->FillMaterialArray(MaterialArray);
	 TArray<FString> MaterialNames;
	 for (int32 MaterialIndex = MaterialArray.Size() - 1; MaterialIndex >= 0; --MaterialIndex)
	 {
		  //MaterialProperties.Add(MaterialName
		  FbxSurfaceMaterial* Material = MaterialArray[MaterialIndex];
		  FString OriginalMaterialName = UTF8_TO_TCHAR(Material->GetName());
		  FString NewMaterialName = AssetName + TEXT("_") + OriginalMaterialName;
		  NewMaterialName = FDazToUnrealUtils::SanitizeName(NewMaterialName);
		  Material->SetName(TCHAR_TO_UTF8(*NewMaterialName));
		  if (MaterialProperties.Contains(NewMaterialName))
		  {
				MaterialNames.Add(NewMaterialName);
		  }
		  else
		  {
				for (int32 MeshIndex = Scene->GetGeometryCount() - 1; MeshIndex >= 0; --MeshIndex)
				{
					 FbxGeometry* Geometry = Scene->GetGeometry(MeshIndex);
					 FbxNode* GeometryNode = Geometry->GetNode();
					 if (GeometryNode->GetMaterialIndex(TCHAR_TO_UTF8(*NewMaterialName)) != -1)
					 {
						  Scene->RemoveGeometry(Geometry);
					 }
				}
				Scene->RemoveMaterial(Material);
		  }

	 }

	 // Create an exporter.
	 FbxExporter* Exporter = FbxExporter::Create(SdkManager, "");
	 int32 FileFormat = -1;

	 // set file format
	 FileFormat = SdkManager->GetIOPluginRegistry()->FindWriterIDByDescription("FBX ascii (*.fbx)");

	 // Make folders for saving the updated FBX file
	 FString UpdatedFBXFolder = FPaths::GetPath(FBXFile) / TEXT("UpdatedFBX");
	 FString UpdatedFBXFile = FPaths::GetPath(FBXFile) / TEXT("UpdatedFBX") / FPaths::GetCleanFilename(FBXPath);
	 if (!MakeDirectoryAndCheck(UpdatedFBXFolder)) return false;

	 // Initialize the exporter by providing a filename.
	 if (!Exporter->Initialize(TCHAR_TO_UTF8(*UpdatedFBXFile), FileFormat, SdkManager->GetIOSettings()))
	 {
		  return false;
	 }

	 // Export the scene.
	 bool Status = Exporter->Export(Scene);

	 // Destroy the exporter.
	 Exporter->Destroy();

	 // If this is a character, determine the type.
	 DazCharacterType CharacterType = DazCharacterType::Unknown;
	 FString CharacterTypeName = RootBoneName.Replace(TEXT("\0"), TEXT(""));
	 if (RootBoneName == TEXT("Genesis3Male"))
	 {
		  CharacterType = DazCharacterType::Genesis3Male;
	 }
	 else if (RootBoneName == TEXT("Genesis3Female"))
	 {
		  CharacterType = DazCharacterType::Genesis3Female;
	 }
	 else if (RootBoneName == TEXT("Genesis8Male"))
	 {
		  CharacterType = DazCharacterType::Genesis8Male;
	 }
	 else if (RootBoneName == TEXT("Genesis8Female"))
	 {
		  CharacterType = DazCharacterType::Genesis8Female;
	 }
	 else if (RootBoneName == TEXT("Genesis"))
	 {
		  CharacterType = DazCharacterType::Genesis1;
	 }

	 // Import Textures
	 if (AssetType == DazAssetType::SkeletalMesh || AssetType == DazAssetType::StaticMesh)
	 {
		  TArray<FString> TexturesFilesToImport;
		  for (auto TexturePair : TextureFileSourceToTarget)
		  {
				FString SourceFileName = TexturePair.Key;
				FString TargetFileName = ImportCharacterTexturesFolder / TexturePair.Value + FPaths::GetExtension(SourceFileName, true);
				PlatformFile.CopyFile(*TargetFileName, *SourceFileName);
				TexturesFilesToImport.Add(TargetFileName);
		  }
		  ImportTextureAssets(TexturesFilesToImport, CharacterTexturesFolder);
	 }

	 // Create Intermediate Materials
	 if (AssetType == DazAssetType::SkeletalMesh || AssetType == DazAssetType::StaticMesh)
	 {
		 // Create a default Master Subsurface Profile if needed
		 USubsurfaceProfile* MasterSubsurfaceProfile = FDazToUnrealMaterials::CreateSubsurfaceBaseProfileForCharacter(CharacterMaterialFolder, MaterialProperties);

		  for (FString IntermediateMaterialName : IntermediateMaterials)
		  {
				TArray<FString> ChildMaterials;
				FString ChildMaterialFolder = CharacterMaterialFolder;
				for (FString ChildMaterialName : MaterialNames)
				{
					 if (MaterialProperties.Contains(ChildMaterialName))
					 {
						  for (FDUFTextureProperty ChildProperty : MaterialProperties[ChildMaterialName])
						  {
								if ((ChildProperty.ObjectName + TEXT("_BaseMat")) == IntermediateMaterialName)
								{
									 ChildMaterialFolder = CharacterMaterialFolder / ChildProperty.ObjectName;
									 ChildMaterials.AddUnique(ChildMaterialName);
								}
						  }
					 }
				}

				if (ChildMaterials.Num() > 1)
				{


					 // Copy Material Properties
					 TArray<FDUFTextureProperty> MostCommonProperties = FDazToUnrealMaterials::GetMostCommonProperties(ChildMaterials, MaterialProperties);
					 MaterialProperties.Add(IntermediateMaterialName, MostCommonProperties);
					 //MaterialProperties[IntermediateMaterialName] = MaterialProperties[ChildMaterials[0]];


					 // Create Material
					 FSoftObjectPath BaseMaterialPath = FDazToUnrealMaterials::GetMostCommonBaseMaterial(ChildMaterials, MaterialProperties);//FDazToUnrealMaterials::GetBaseMaterial(ChildMaterials[0], MaterialProperties[IntermediateMaterialName]);
					 UObject* BaseMaterial = BaseMaterialPath.TryLoad();
					 UMaterialInstanceConstant* UnrealMaterialConstant = FDazToUnrealMaterials::CreateMaterial(CharacterMaterialFolder, CharacterTexturesFolder, IntermediateMaterialName, MaterialProperties, CharacterType, nullptr, MasterSubsurfaceProfile);
					 UnrealMaterialConstant->SetParentEditorOnly((UMaterial*)BaseMaterial);
					 for (FString MaterialName : ChildMaterials)
					 {
						USubsurfaceProfile* SubsurfaceProfile = MasterSubsurfaceProfile;
						if (!FDazToUnrealMaterials::SubsurfaceProfilesWouldBeIdentical(MasterSubsurfaceProfile, MaterialProperties[MaterialName]))
						{
							SubsurfaceProfile = FDazToUnrealMaterials::CreateSubsurfaceProfileForMaterial(MaterialName, ChildMaterialFolder, MaterialProperties[MaterialName]);
						}

						if (FDazToUnrealMaterials::GetBaseMaterial(MaterialName, MaterialProperties[MaterialName]) == BaseMaterialPath)
						{

							int32 Length = MaterialProperties[MaterialName].Num();
							for (int32 Index = Length - 1; Index >= 0; Index--)
							{
								FDUFTextureProperty ChildPropertyForRemoval = MaterialProperties[MaterialName][Index];
								if (ChildPropertyForRemoval.Name == TEXT("Asset Type")) continue;
								for (FDUFTextureProperty ParentProperty : MaterialProperties[IntermediateMaterialName])
								{
									if (ParentProperty.Name == ChildPropertyForRemoval.Name && ParentProperty.Value == ChildPropertyForRemoval.Value)
									{
											MaterialProperties[MaterialName].RemoveAt(Index);
											break;
									}
								}
							}

							FDazToUnrealMaterials::CreateMaterial(ChildMaterialFolder, CharacterTexturesFolder, MaterialName, MaterialProperties, CharacterType, UnrealMaterialConstant, SubsurfaceProfile);
						}
						else
						{
							FDazToUnrealMaterials::CreateMaterial(ChildMaterialFolder, CharacterTexturesFolder, MaterialName, MaterialProperties, CharacterType, nullptr, SubsurfaceProfile);
						}
					 }
				}
				else if (ChildMaterials.Num() == 1)
				{
					USubsurfaceProfile* SubsurfaceProfile = FDazToUnrealMaterials::CreateSubsurfaceProfileForMaterial(ChildMaterials[0], CharacterMaterialFolder / ChildMaterials[0], MaterialProperties[ChildMaterials[0]]);
					FDazToUnrealMaterials::CreateMaterial(CharacterMaterialFolder / IntermediateMaterialName, CharacterTexturesFolder, ChildMaterials[0], MaterialProperties, CharacterType, nullptr, SubsurfaceProfile);
				}

		  }
	 }

	 // Import FBX
	 UObject* NewObject = ImportFBXAsset(UpdatedFBXFile, CharacterFolder, AssetType, CharacterType, CharacterTypeName);

	 // If this is a Pose transfer, an AnimSequence was created.  Make a PoseAsset from it.
	 if (AssetType == DazAssetType::Pose)
	 {
		 if (UAnimSequence* AnimSequence = Cast<UAnimSequence>(NewObject))
		 {
			 UPoseAsset* NewPoseAsset = FDazToUnrealPoses::CreatePoseAsset(AnimSequence, PoseNameList);

			 FContentBrowserModule& ContentBrowserModule = FModuleManager::Get().LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
			 TArray<UObject*> AssetsToSelect;
			 AssetsToSelect.Add((UObject*)NewPoseAsset);
			 ContentBrowserModule.Get().SyncBrowserToAssets(AssetsToSelect);
		 }
	 }

	 return NewObject;
}



/*bool FDazToUnrealModule::CreateMaterials(const FString CharacterMaterialFolder, const FString CharacterTexturesFolder, const TArray<FString>& MaterialNames, TMap<FString, TArray<FDUFTextureProperty>> MaterialProperties, const DazCharacterType CharacterType)
{
	 const UDazToUnrealSettings* CachedSettings = GetDefault<UDazToUnrealSettings>();

	 // Update Material Names
	 for (FString MaterialName : MaterialNames)
	 {
		  FDazToUnrealMaterials::CreateMaterial(CharacterMaterialFolder, CharacterTexturesFolder, MaterialName, MaterialProperties, CharacterType, nullptr);
	 }


	 return true;
}*/


// Modified from the FColor::FromHex function
FLinearColor FDazToUnrealModule::FromHex(const FString& HexString)
{
	 int32 StartIndex = (!HexString.IsEmpty() && HexString[0] == TCHAR('#')) ? 1 : 0;

	 if (HexString.Len() == 3 + StartIndex)
	 {
		  const int32 R = FParse::HexDigit(HexString[StartIndex++]);
		  const int32 G = FParse::HexDigit(HexString[StartIndex++]);
		  const int32 B = FParse::HexDigit(HexString[StartIndex]);

		  return FLinearColor(((R << 4) + R) / 255.0, ((G << 4) + G) / 355.0, ((B << 4) + B) / 255.0, 1.0);
	 }

	 if (HexString.Len() == 6 + StartIndex)
	 {
		  FLinearColor Result;

		  Result.R = ((FParse::HexDigit(HexString[StartIndex + 0]) << 4) + FParse::HexDigit(HexString[StartIndex + 1])) / 255.0;
		  Result.G = ((FParse::HexDigit(HexString[StartIndex + 2]) << 4) + FParse::HexDigit(HexString[StartIndex + 3])) / 255.0;
		  Result.B = ((FParse::HexDigit(HexString[StartIndex + 4]) << 4) + FParse::HexDigit(HexString[StartIndex + 5])) / 255.0;
		  Result.A = 1.0f;

		  return Result;
	 }

	 if (HexString.Len() == 8 + StartIndex)
	 {
		  FLinearColor Result;

		  Result.R = ((FParse::HexDigit(HexString[StartIndex + 0]) << 4) + FParse::HexDigit(HexString[StartIndex + 1])) / 255.0;
		  Result.G = ((FParse::HexDigit(HexString[StartIndex + 2]) << 4) + FParse::HexDigit(HexString[StartIndex + 3])) / 255.0;
		  Result.B = ((FParse::HexDigit(HexString[StartIndex + 4]) << 4) + FParse::HexDigit(HexString[StartIndex + 5])) / 255.0;
		  Result.A = ((FParse::HexDigit(HexString[StartIndex + 6]) << 4) + FParse::HexDigit(HexString[StartIndex + 7])) / 255.0;

		  return Result;
	 }

	 return FLinearColor(ForceInitToZero);
}

void FDazToUnrealModule::SetMaterialProperty(const FString& MaterialName, const FString& PropertyName, const FString& PropertyType, const FString& PropertyValue, TMap<FString, TArray<FDUFTextureProperty>>& MaterialProperties)
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

bool FDazToUnrealModule::ImportTextureAssets(TArray<FString>& SourcePaths, FString& ImportLocation)
{
	 FAssetToolsModule& AssetToolsModule = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools");
	 TArray<UObject*> ImportedAssets = AssetToolsModule.Get().ImportAssets(SourcePaths, ImportLocation);
	 if (ImportedAssets.Num() > 0)
	 {
		  return true;
	 }
	 return false;
}

UObject* FDazToUnrealModule::ImportFBXAsset(const FString& SourcePath, const FString& ImportLocation, const DazAssetType& AssetType, const DazCharacterType& CharacterType, const FString& CharacterTypeName)
{
	 FAssetToolsModule& AssetToolsModule = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools");
	 UDazToUnrealSettings* CachedSettings = GetMutableDefault<UDazToUnrealSettings>();

	 FString NewFBXPath = SourcePath;
	 TArray<FString> FileNames;
	 FileNames.Add(NewFBXPath);

	 UFbxFactory* FbxFactory = NewObject<UFbxFactory>(UFbxFactory::StaticClass());
	 FbxFactory->AddToRoot();

	 USkeleton* Skeleton = nullptr;
	 FSoftObjectPath SkeletonPath;
	 if (CharacterType == DazCharacterType::Genesis1)
	 {
		  Skeleton = (USkeleton*)CachedSettings->Genesis1Skeleton.TryLoad();
		  SkeletonPath = CachedSettings->Genesis1Skeleton;
	 }
	 if (CharacterType == DazCharacterType::Genesis3Male || CharacterType == DazCharacterType::Genesis3Female)
	 {
		  Skeleton = (USkeleton*)CachedSettings->Genesis3Skeleton.TryLoad();
		  SkeletonPath = CachedSettings->Genesis3Skeleton;
	 }
	 if (CharacterType == DazCharacterType::Genesis8Male || CharacterType == DazCharacterType::Genesis8Female)
	 {
		  Skeleton = (USkeleton*)CachedSettings->Genesis8Skeleton.TryLoad();
		  SkeletonPath = CachedSettings->Genesis8Skeleton;
	 }
	 if (CharacterType == DazCharacterType::Unknown && CachedSettings->OtherSkeletons.Contains(CharacterTypeName))
	 {
		  Skeleton = (USkeleton*)CachedSettings->OtherSkeletons[CharacterTypeName].TryLoad();
		  SkeletonPath = CachedSettings->OtherSkeletons[CharacterTypeName];
	 }

	 UFbxImportUI* ImportUI = NewObject<UFbxImportUI>();
	 FbxFactory->SetDetectImportTypeOnImport(false);
	 FbxFactory->ImportUI->TextureImportData->MaterialSearchLocation = EMaterialSearchLocation::UnderRoot;
	 FbxFactory->ImportUI->bImportMaterials = false;
	 FbxFactory->ImportUI->bImportTextures = false;

	 if (AssetType == DazAssetType::SkeletalMesh)
	 {
		  FbxFactory->ImportUI->bImportAsSkeletal = true;
		  FbxFactory->ImportUI->Skeleton = Skeleton;
		  FbxFactory->ImportUI->SkeletalMeshImportData->bImportMorphTargets = true;
		  FbxFactory->ImportUI->bImportAnimations = true;
		  FbxFactory->ImportUI->SkeletalMeshImportData->bUseT0AsRefPose = CachedSettings->FrameZeroIsReferencePose;
		  FbxFactory->ImportUI->SkeletalMeshImportData->bConvertScene = true;
		  FbxFactory->ImportUI->SkeletalMeshImportData->bForceFrontXAxis = CachedSettings->ZeroRootRotationOnImport;
		  FbxFactory->ImportUI->MeshTypeToImport = FBXIT_SkeletalMesh;
	 }
	 if (AssetType == DazAssetType::StaticMesh)
	 {
		  FbxFactory->ImportUI->bImportAsSkeletal = false;
		  FbxFactory->ImportUI->bImportMaterials = true;
		  FbxFactory->ImportUI->MeshTypeToImport = FBXIT_StaticMesh;
	 }
	 if (AssetType == DazAssetType::Animation || AssetType == DazAssetType::Pose)
	 {
		  FbxFactory->ImportUI->bImportAsSkeletal = true;
		  FbxFactory->ImportUI->Skeleton = Skeleton;
		  FbxFactory->ImportUI->bImportMesh = false;
		  FbxFactory->ImportUI->bImportMaterials = false;
		  FbxFactory->ImportUI->bImportTextures = false;
		  FbxFactory->ImportUI->bImportAnimations = true;
		  FbxFactory->ImportUI->MeshTypeToImport = FBXIT_Animation;
	 }
	 //UFbxFactory::EnableShowOption();
	 UAutomatedAssetImportData* ImportData = NewObject<UAutomatedAssetImportData>(UAutomatedAssetImportData::StaticClass());
	 ImportData->FactoryName = TEXT("FbxFactory");
	 ImportData->Factory = FbxFactory;
	 ImportData->Filenames = FileNames;
	 ImportData->DestinationPath = ImportLocation;
	 ImportData->bReplaceExisting = true;
	 if (AssetType == DazAssetType::Animation || AssetType == DazAssetType::Pose)
	 {
		  ImportData->DestinationPath = CachedSettings->AnimationImportDirectory.Path;
	 }

	 TArray<UObject*> ImportedAssets;
	 if (CachedSettings->ShowFBXImportDialog)
	 {
		  UAssetImportTask* AssetImportTask = NewObject<UAssetImportTask>();
		  AssetImportTask->Filename = ImportData->Filenames[0];
		  AssetImportTask->DestinationPath = ImportData->DestinationPath;
		  AssetImportTask->Options = FbxFactory->ImportUI;
		  AssetImportTask->Factory = FbxFactory;
		  TArray< UAssetImportTask* > ImportTasks;
		  ImportTasks.Add(AssetImportTask);
		  AssetToolsModule.Get().ImportAssetTasks(ImportTasks);
		  for (FString ImportedPath : AssetImportTask->ImportedObjectPaths)
		  {
				FSoftObjectPath SoftObjectPath(ImportedPath);
				ImportedAssets.Add(SoftObjectPath.TryLoad());
		  }
	 }
	 else
	 {
		  ImportedAssets = AssetToolsModule.Get().ImportAssetsAutomated(ImportData);
	 }

	 FContentBrowserModule& ContentBrowserModule = FModuleManager::Get().LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
	 ContentBrowserModule.Get().SyncBrowserToAssets(ImportedAssets);

	 for (UObject* ImportedAsset : ImportedAssets)
	 {
		  if (USkeletalMesh* SkeletalMesh = Cast<USkeletalMesh>(ImportedAsset))
		  {
				if (CachedSettings->SkeletonPostProcessAnimation.Contains(SkeletonPath))
				{
					SkeletalMesh->PostProcessAnimBlueprint = CachedSettings->SkeletonPostProcessAnimation[SkeletonPath].TryLoadClass<UAnimInstance>();
				}

				//Get the new skeleton
				if (!Skeleton)
				{
					 Skeleton = SkeletalMesh->Skeleton;
					 int32 BoneIndex = Skeleton->GetReferenceSkeleton().FindBoneIndex(FName(TEXT("pelvis")));
					 if (BoneIndex == -1)
					 {
						  BoneIndex = Skeleton->GetReferenceSkeleton().FindBoneIndex(FName(TEXT("hip")));
					 }
					 if (BoneIndex != -1)
					 {
						  Skeleton->SetBoneTranslationRetargetingMode(BoneIndex, EBoneTranslationRetargetingMode::Skeleton, true);
					 }
					 //ISkeletonEditorModule& SkeletonEditorModule = FModuleManager::LoadModuleChecked<ISkeletonEditorModule>("SkeletonEditor");
					 //TSharedPtr<IEditableSkeleton> EditableSkeleton = SkeletonEditorModule.CreateEditableSkeleton(Skeleton);
					 //EditableSkeleton->Set

					 CachedSettings->OtherSkeletons.Add(CharacterTypeName, Skeleton);
					 CachedSettings->SaveConfig(CPF_Config, *CachedSettings->GetDefaultConfigFilename());
				}
		  }
	 }

	 if (ImportedAssets.Num() > 0)
	 {
		  return ImportedAssets[0];
	 }
	 return nullptr;
}

void FDazToUnrealModule::InstallDazStudioPlugin()
{
	 FString InstallerPath = IPluginManager::Get().FindPlugin("DazToUnreal")->GetBaseDir() / TEXT("Resources") / TEXT("DazToUnrealSetup.exe");
	 FString InstallerAbsolutePath = IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead(*InstallerPath);
	 FPlatformProcess::LaunchFileInDefaultExternalApplication(*InstallerAbsolutePath, NULL, ELaunchVerb::Open);
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FDazToUnrealModule, DazToUnreal)