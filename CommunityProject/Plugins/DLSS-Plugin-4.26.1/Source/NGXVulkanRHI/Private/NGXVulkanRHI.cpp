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

#include "NGXVulkanRHI.h"

#include "VulkanRHIPrivate.h"
#include "VulkanPendingState.h"
#include "VulkanRHIBridge.h"
#include "VulkanContext.h"

#include "nvsdk_ngx_vk.h"
#include "nvsdk_ngx_helpers_vk.h"

#include "GenericPlatform/GenericPlatformFile.h"

DEFINE_LOG_CATEGORY_STATIC(LogDLSSNGXVulkanRHI, Log, All);

#define LOCTEXT_NAMESPACE "FNGXVulkanRHIModule"

class FVulkanNGXDLSSFeature final : public NGXDLSSFeature
{

public:
	using NGXDLSSFeature::NGXDLSSFeature;

	virtual ~FVulkanNGXDLSSFeature()
	{
		check(!IsRunningRHIInSeparateThread() || IsInRHIThread());
		check(NGXRHI::NGXInitialized());
		NVSDK_NGX_Result Result;
		Result = NVSDK_NGX_VULKAN_ReleaseFeature(Feature);
		UE_LOG(LogDLSSNGXVulkanRHI, Log, TEXT("NVSDK_NGX_VULKAN_ReleaseFeature -> (%u %s)"), Result, GetNGXResultAsString(Result));

		if (NGXRHI::SupportsAllocateParameters())
		{
			Result = NVSDK_NGX_VULKAN_DestroyParameters(Parameter);
			UE_LOG(LogDLSSNGXVulkanRHI, Log, TEXT("NVSDK_NGX_VULKAN_DestroyParameters -> (%u %s)"), Result, GetNGXResultAsString(Result));
		}
	}
};


class FNGXVulkanRHI final : public NGXRHI
{
	// DLSS_TODO MGPU
	const int VisibilityNodeMask = 1;
	const int CreationNodeMask = 1;
	const int AdapterId = 0;

public:
	FNGXVulkanRHI(const FNGXRHICreateArguments& Arguments);
	virtual void ExecuteDLSS(FRHICommandList& CmdList, const FRHIDLSSArguments& InArguments, FDLSSStateRef InDLSSState) final;
	virtual ~FNGXVulkanRHI();
private:

	FVulkanDynamicRHI* VulkanRHI = nullptr;
	FVulkanDevice* VulkanDevice = nullptr;

	NVSDK_NGX_Result Init_NGX_VK(const FNGXRHICreateArguments& InArguments, const wchar_t* InApplicationDataPath, VkInstance InInstance, VkPhysicalDevice InPD, VkDevice InDevice, const NVSDK_NGX_FeatureCommonInfo* InFeatureInfo);
	static bool IsIncompatibleAPICaptureToolActive();
};


bool FNGXVulkanRHI::IsIncompatibleAPICaptureToolActive()
{
	// TODO figure out whether the renderdoc layer is active, either here or in the PreInit module
	return false;
}

NVSDK_NGX_Result FNGXVulkanRHI::Init_NGX_VK(const FNGXRHICreateArguments& InArguments, const wchar_t* InApplicationDataPath, VkInstance InInstance, VkPhysicalDevice InPD, VkDevice InDevice, const NVSDK_NGX_FeatureCommonInfo* InFeatureInfo)
{
	NVSDK_NGX_Result Result = NVSDK_NGX_Result_Fail;
	int32 APIVersion = NVSDK_NGX_VERSION_API_MACRO;
	do 
	{
		if (InArguments.InitializeNGXWithNGXApplicationID())
		{
			Result = NVSDK_NGX_VULKAN_Init(InArguments.NGXAppId, InApplicationDataPath, InInstance, InPD, InDevice, InFeatureInfo, static_cast<NVSDK_NGX_Version>(APIVersion));
			UE_LOG(LogDLSSNGXVulkanRHI, Log, TEXT("NVSDK_NGX_VULKAN_Init(AppID= %u, APIVersion = 0x%x) -> (%u %s)"), InArguments.NGXAppId, APIVersion, Result, GetNGXResultAsString(Result));
		}
		else
		{
			Result = NVSDK_NGX_VULKAN_Init_with_ProjectID(TCHAR_TO_UTF8(*InArguments.UnrealProjectID), NVSDK_NGX_ENGINE_TYPE_UNREAL, TCHAR_TO_UTF8(*InArguments.UnrealEngineVersion), InApplicationDataPath, InInstance, InPD, InDevice, InFeatureInfo, static_cast<NVSDK_NGX_Version>(APIVersion));
			UE_LOG(LogDLSSNGXVulkanRHI, Log, TEXT("NVSDK_NGX_VULKAN_Init(ProjectID = %s, EngineVersion=%s, APIVersion = 0x%x) -> (%u %s)"), *InArguments.UnrealProjectID, *InArguments.UnrealEngineVersion, APIVersion, Result, GetNGXResultAsString(Result));
		}

		if (NVSDK_NGX_FAILED(Result))
		{
			NVSDK_NGX_VULKAN_Shutdown();
		}

		--APIVersion;
	} while (NVSDK_NGX_FAILED(Result) && APIVersion >= NVSDK_NGX_VERSION_API_MACRO_BASE_LINE);

	if (NVSDK_NGX_SUCCEED(Result) && (APIVersion + 1 < NVSDK_NGX_VERSION_API_MACRO_WITH_LOGGING))
	{
		UE_LOG(LogDLSSNGXVulkanRHI, Log, TEXT("Warning: NVSDK_NGX_VULKAN_Init succeeded, but the driver installed on this system is too old the support the NGX logging API. The console variables r.NGX.LogLevel and r.NGX.DisableOtherLoggingSinks will have no effect and NGX logs will only show up in their own log files, and not in UE4's log files."));
	}

	return Result;
}


FNGXVulkanRHI::FNGXVulkanRHI(const FNGXRHICreateArguments& Arguments)
	: NGXRHI(Arguments)
	, VulkanRHI(static_cast<FVulkanDynamicRHI*>(Arguments.DynamicRHI))
	, VulkanDevice(VulkanRHIBridge::GetDevice(VulkanRHI)
)
{
	ensure(VulkanRHI);

	const FString NGXLogDir = GetNGXLogDirectory();
	IPlatformFile::GetPlatformPhysical().CreateDirectoryTree(*NGXLogDir);

	bIsIncompatibleAPICaptureToolActive = IsIncompatibleAPICaptureToolActive();

	VkInstance VulkanInstance = reinterpret_cast<VkInstance>(VulkanRHIBridge::GetInstance(VulkanRHI));
	VkPhysicalDevice VulkanPhysicalDevice = reinterpret_cast<VkPhysicalDevice>(VulkanRHIBridge::GetPhysicalDevice(VulkanDevice));
	VkDevice VulkanLogicalDevice = reinterpret_cast<VkDevice>(VulkanRHIBridge::GetLogicalDevice(VulkanDevice));

	NVSDK_NGX_Result ResultInit = Init_NGX_VK(Arguments, *NGXLogDir, VulkanInstance, VulkanPhysicalDevice, VulkanLogicalDevice, CommonFeatureInfo());
	UE_LOG(LogDLSSNGXVulkanRHI, Log, TEXT("NVSDK_NGX_VULKAN_Init (Log %s) -> (%u %s)"), *NGXLogDir, ResultInit, GetNGXResultAsString(ResultInit));
	
	// store for the higher level code interpret
	DLSSQueryFeature.DLSSInitResult = ResultInit;

	if (NVSDK_NGX_Result_FAIL_OutOfDate == ResultInit)
	{
		DLSSQueryFeature.DriverRequirements.DriverUpdateRequired = true;
	}
	else if (NVSDK_NGX_Result_Success == ResultInit)
	{
		bNGXInitialized = true;

		NVSDK_NGX_Result ResultGetParameters = NVSDK_NGX_VULKAN_GetCapabilityParameters(&DLSSQueryFeature.CapabilityParameters);
		UE_LOG(LogDLSSNGXVulkanRHI, Log, TEXT("NVSDK_NGX_VULKAN_GetCapabilityParameters -> (%u %s)"), ResultGetParameters, GetNGXResultAsString(ResultGetParameters));

		if (NVSDK_NGX_Result_FAIL_OutOfDate == ResultGetParameters)
		{
			DLSSQueryFeature.DriverRequirements.DriverUpdateRequired = true;
		}

		if (NVSDK_NGX_FAILED(ResultGetParameters))
		{
			ResultGetParameters = NVSDK_NGX_VULKAN_GetParameters(&DLSSQueryFeature.CapabilityParameters);
			UE_LOG(LogDLSSNGXVulkanRHI, Log, TEXT("NVSDK_NGX_VULKAN_GetParameters -> (%u %s)"), ResultGetParameters, GetNGXResultAsString(ResultGetParameters));
			
			bSupportsAllocateParameters = false;
		}

		if (NVSDK_NGX_Result_Success == ResultGetParameters)
		{
			DLSSQueryFeature.QueryDLSSSupport();
		}
	}
}

FNGXVulkanRHI::~FNGXVulkanRHI()
{
	UE_LOG(LogDLSSNGXVulkanRHI, Log, TEXT("%s Enter"), __FUNCTIONW__);
	if (bNGXInitialized)
	{
		// Destroy the parameters and features before we call NVSDK_NGX_D3D11_Shutdown
		ReleaseAllocatedFeatures();
		
		NVSDK_NGX_Result Result;
		if (bSupportsAllocateParameters && DLSSQueryFeature.CapabilityParameters)
		{
			Result = NVSDK_NGX_VULKAN_DestroyParameters(DLSSQueryFeature.CapabilityParameters);
			UE_LOG(LogDLSSNGXVulkanRHI, Log, TEXT("NVSDK_NGX_VULKAN_DestroyParameters -> (%u %s)"), Result, GetNGXResultAsString(Result));
		}
		Result = NVSDK_NGX_VULKAN_Shutdown();
		UE_LOG(LogDLSSNGXVulkanRHI, Log, TEXT("NVSDK_NGX_VULKAN_Shutdown -> (%u %s)"), Result, GetNGXResultAsString(Result));
		bNGXInitialized = false;
	}
	UE_LOG(LogDLSSNGXVulkanRHI, Log, TEXT("%s Leave"), __FUNCTIONW__);
}

void FNGXVulkanRHI::ExecuteDLSS(FRHICommandList& CmdList, const FRHIDLSSArguments& InArguments, FDLSSStateRef InDLSSState)
{
	check(!IsRunningRHIInSeparateThread() || IsInRHIThread());
	check(IsDLSSAvailable());
	if (!IsDLSSAvailable()) return;

	InArguments.Validate();

	FVulkanCommandListContextImmediate& ImmediateContext = VulkanDevice->GetImmediateContext();
	VkCommandBuffer VulkanCommandBuffer = ImmediateContext.GetCommandBufferManager()->GetActiveCmdBuffer()->GetHandle();
	
	if (InDLSSState->RequiresFeatureRecreation(InArguments))
	{
		check(!InDLSSState->DLSSFeature || InDLSSState->DLSSFeature && InDLSSState->DLSSFeature->Feature && InDLSSState->DLSSFeature->Parameter);
		InDLSSState->DLSSFeature = nullptr;
	}

	if (InArguments.bReset)
	{
		check(!InDLSSState->DLSSFeature);
		InDLSSState->DLSSFeature = FindFreeFeature(InArguments);
	}

	if (!InDLSSState->DLSSFeature)
	{
		NVSDK_NGX_Parameter* NewNGXParameterHandle = nullptr;
		if (NGXRHI::SupportsAllocateParameters())
		{
			NVSDK_NGX_Result Result = NVSDK_NGX_VULKAN_AllocateParameters(&NewNGXParameterHandle);
			checkf(Result == NVSDK_NGX_Result_Success, TEXT("NVSDK_NGX_VULKAN_AllocateParameters failed! (%u %s)"), Result, GetNGXResultAsString(Result));
		}
		else
		{
			NVSDK_NGX_Result Result = NVSDK_NGX_VULKAN_GetParameters(&NewNGXParameterHandle);
			checkf(Result == NVSDK_NGX_Result_Success, TEXT("NVSDK_NGX_VULKAN_GetParameters failed! (%u %s)"), Result, GetNGXResultAsString(Result));
		}

		NVSDK_NGX_DLSS_Create_Params DlssCreateParams = InArguments.GetNGXDLSSCreateParams();
		NVSDK_NGX_Handle* NewNGXHandle = nullptr;

		NVSDK_NGX_Result ResultCreate = NGX_VULKAN_CREATE_DLSS_EXT(
			VulkanCommandBuffer,
			CreationNodeMask,
			VisibilityNodeMask,
			&NewNGXHandle,
			NewNGXParameterHandle,
			&DlssCreateParams);

		checkf(ResultCreate == NVSDK_NGX_Result_Success, TEXT("NGX_VULKAN_CREATE_DLSS failed! (%u %s)"), ResultCreate, GetNGXResultAsString(ResultCreate));

		InDLSSState->DLSSFeature = MakeShared<FVulkanNGXDLSSFeature>(NewNGXHandle, NewNGXParameterHandle, InArguments.GetFeatureDesc(), FrameCounter);
		RegisterFeature(InDLSSState->DLSSFeature);
	}
	
	check(InDLSSState->DLSSFeature);

	// execute
	NVSDK_NGX_VK_DLSS_Eval_Params DlssEvalParams;
	FMemory::Memzero(DlssEvalParams);
	auto NGXVulkanResourceFromRHITexture = [](FRHITexture* InRHITexture)
	{
		check(InRHITexture);
		if (FRHITextureReference* TexRef = InRHITexture->GetTextureReference())
		{
			InRHITexture = TexRef->GetReferencedTexture();
			check(InRHITexture);
		}

		FVulkanTextureBase* VulkanTexture = static_cast<FVulkanTextureBase*>(InRHITexture->GetTextureBaseRHI());

		NVSDK_NGX_Resource_VK NGXTexture;
		FMemory::Memzero(NGXTexture);

		NGXTexture.Type = NVSDK_NGX_RESOURCE_VK_TYPE_VK_IMAGEVIEW;

		// Check for VK_IMAGE_USAGE_STORAGE_BIT. Those are not directly stored but FVulkanSurface::GenerateImageCreateInfo sets the VK flag based on those UEFlags
		NGXTexture.ReadWrite = (VulkanTexture->Surface.UEFlags & TexCreate_Presentable) || (VulkanTexture->Surface.UEFlags & TexCreate_UAV);

		NGXTexture.Resource.ImageViewInfo.ImageView = VulkanTexture->DefaultView.View;
		NGXTexture.Resource.ImageViewInfo.Image = VulkanTexture->DefaultView.Image;
		NGXTexture.Resource.ImageViewInfo.Format = VulkanTexture->Surface.ViewFormat;

		NGXTexture.Resource.ImageViewInfo.Width = VulkanTexture->Surface.Width;
		NGXTexture.Resource.ImageViewInfo.Height = VulkanTexture->Surface.Height;
		check(VulkanTexture->Surface.Depth == 1);

		NGXTexture.Resource.ImageViewInfo.SubresourceRange.aspectMask = VulkanTexture->Surface.GetFullAspectMask();

		NGXTexture.Resource.ImageViewInfo.SubresourceRange.layerCount = VulkanTexture->Surface.GetNumberOfArrayLevels();
		NGXTexture.Resource.ImageViewInfo.SubresourceRange.levelCount = VulkanTexture->Surface.GetNumMips();

		// DLSS_TODO Figure out where to get those from if the textures are arrayed or mipped.
		check(VulkanTexture->Surface.GetNumberOfArrayLevels() == 1);
		check(VulkanTexture->Surface.GetNumMips() == 1);
		NGXTexture.Resource.ImageViewInfo.SubresourceRange.baseMipLevel = 0;
		NGXTexture.Resource.ImageViewInfo.SubresourceRange.baseArrayLayer = 0;

		return NGXTexture;
	};

	NVSDK_NGX_Resource_VK InOutput = NGXVulkanResourceFromRHITexture(InArguments.OutputColor);
	DlssEvalParams.Feature.pInOutput = &InOutput;
	check(InArguments.OutputColor->GetFlags() & ( TexCreate_UAV | TexCreate_Presentable));
	check(InOutput.ReadWrite == true);
	DlssEvalParams.InOutputSubrectBase.X = InArguments.DestRect.Min.X;
	DlssEvalParams.InOutputSubrectBase.Y = InArguments.DestRect.Min.Y;

	DlssEvalParams.InRenderSubrectDimensions.Width = InArguments.SrcRect.Width();
	DlssEvalParams.InRenderSubrectDimensions.Height = InArguments.SrcRect.Height();

	NVSDK_NGX_Resource_VK InColor = NGXVulkanResourceFromRHITexture(InArguments.InputColor);
	DlssEvalParams.Feature.pInColor = &InColor;
	DlssEvalParams.InColorSubrectBase.X = InArguments.SrcRect.Min.X;
	DlssEvalParams.InColorSubrectBase.Y = InArguments.SrcRect.Min.Y;

	NVSDK_NGX_Resource_VK InDepth = NGXVulkanResourceFromRHITexture(InArguments.InputDepth);
	DlssEvalParams.pInDepth = &InDepth;
	DlssEvalParams.InDepthSubrectBase.X = InArguments.SrcRect.Min.X;
	DlssEvalParams.InDepthSubrectBase.Y = InArguments.SrcRect.Min.Y;

	NVSDK_NGX_Resource_VK InMotionVectors = NGXVulkanResourceFromRHITexture(InArguments.InputMotionVectors);
	DlssEvalParams.pInMotionVectors = &InMotionVectors;
	// The VelocityCombine pass puts the motion vectors into the top left corner
	DlssEvalParams.InMVSubrectBase.X = 0;
	DlssEvalParams.InMVSubrectBase.Y = 0;

	NVSDK_NGX_Resource_VK InExposureTexture = NGXVulkanResourceFromRHITexture(InArguments.InputExposure);
	DlssEvalParams.pInExposureTexture = &InExposureTexture;
	DlssEvalParams.InPreExposure = InArguments.PreExposure;

	DlssEvalParams.Feature.InSharpness = InArguments.Sharpness;
	DlssEvalParams.InJitterOffsetX = InArguments.JitterOffset.X;
	DlssEvalParams.InJitterOffsetY = InArguments.JitterOffset.Y;

	DlssEvalParams.InMVScaleX = InArguments.MotionVectorScale.X;
	DlssEvalParams.InMVScaleY = InArguments.MotionVectorScale.Y;
	DlssEvalParams.InReset = InArguments.bReset;


	DlssEvalParams.InFrameTimeDeltaInMsec = InArguments.DeltaTime;

	NVSDK_NGX_Result Result = NGX_VULKAN_EVALUATE_DLSS_EXT(
		VulkanCommandBuffer,
		InDLSSState->DLSSFeature->Feature,
		InDLSSState->DLSSFeature->Parameter,
		&DlssEvalParams
	);
	checkf(Result == NVSDK_NGX_Result_Success, TEXT("NGX_Vulkan_EVALUATE_DLSS_EXT failed! (%u %s)"), Result, GetNGXResultAsString(Result));

	InDLSSState->DLSSFeature->Tick(FrameCounter);

	if (FVulkanPlatform::RegisterGPUWork() && ImmediateContext.IsImmediate())
	{
		ImmediateContext.GetGPUProfiler().RegisterGPUWork(1);
	}

	

	ImmediateContext.GetPendingComputeState()->Reset();
	ImmediateContext.GetPendingGfxState()->Reset();
}


/** IModuleInterface implementation */

void FNGXVulkanRHIModule::StartupModule()
{
}

void FNGXVulkanRHIModule::ShutdownModule()
{
}

TUniquePtr<NGXRHI> FNGXVulkanRHIModule::CreateNGXRHI(const FNGXRHICreateArguments& Arguments)
{
	TUniquePtr<NGXRHI> Result(new FNGXVulkanRHI(Arguments));
	return Result;
}

IMPLEMENT_MODULE(FNGXVulkanRHIModule, NGXVulkanRHI)

#undef LOCTEXT_NAMESPACE


