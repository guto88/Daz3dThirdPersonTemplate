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

#include "NGXD3D12RHI.h"

#include "nvsdk_ngx.h"
#include "nvsdk_ngx_helpers.h"

#include "D3D12RHIPrivate.h"
#include "D3D12Util.h"
#include "D3D12State.h"
#include "D3D12Resources.h"
#include "D3D12Viewport.h"
#include "D3D12ConstantBuffer.h"

#include "RHIValidationCommon.h"
#include "GenericPlatform/GenericPlatformFile.h"


DEFINE_LOG_CATEGORY_STATIC(LogDLSSNGXD3D12RHI, Log, All);

#define LOCTEXT_NAMESPACE "FNGXD3D12RHIModule"

class FD3D12NGXDLSSFeature final : public NGXDLSSFeature
{

public:
	using NGXDLSSFeature::NGXDLSSFeature;

	virtual ~FD3D12NGXDLSSFeature()
	{
		check(!IsRunningRHIInSeparateThread() || IsInRHIThread());
		check(NGXRHI::NGXInitialized());
		NVSDK_NGX_Result Result;
		Result = NVSDK_NGX_D3D12_ReleaseFeature(Feature);
		UE_LOG(LogDLSSNGXD3D12RHI, Log, TEXT("NVSDK_NGX_D3D12_ReleaseFeature -> (%u %s)"), Result, GetNGXResultAsString(Result));

		if (NGXRHI::SupportsAllocateParameters())
		{
			Result = NVSDK_NGX_D3D12_DestroyParameters(Parameter);
			UE_LOG(LogDLSSNGXD3D12RHI, Log, TEXT("NVSDK_NGX_D3D12_DestroyParameters -> (%u %s)"), Result, GetNGXResultAsString(Result));
		}
	}
};

class FNGXD3D12RHI final : public NGXRHI
{
	// DLSS_TODO MGPU
	const int VisibilityNodeMask = 1;
	const int CreationNodeMask = 1;
	const int AdapterId = 0;

public:
	FNGXD3D12RHI(const FNGXRHICreateArguments& Arguments);
	virtual void ExecuteDLSS(FRHICommandList& CmdList, const FRHIDLSSArguments& InArguments, FDLSSStateRef InDLSSState) final;
	virtual ~FNGXD3D12RHI();
private:
	NVSDK_NGX_Result Init_NGX_D3D12(const FNGXRHICreateArguments& InArguments, const wchar_t* InApplicationDataPath, ID3D12Device* InHandle, const NVSDK_NGX_FeatureCommonInfo* InFeatureInfo);
	static bool IsIncompatibleAPICaptureToolActive(ID3D12Device* InDirect3DDevice);

	FD3D12DynamicRHI* D3D12RHI = nullptr;

	ID3D12Device* Direct3DDevice = nullptr;
};

bool FNGXD3D12RHI::IsIncompatibleAPICaptureToolActive(ID3D12Device* InDirect3DDevice)
{
	// RenderDoc
	{
		IID RenderDocID;
		if (SUCCEEDED(IIDFromString(L"{A7AA6116-9C8D-4BBA-9083-B4D816B71B78}", &RenderDocID)))
		{
			TRefCountPtr<IUnknown> RenderDoc;
			if (SUCCEEDED(InDirect3DDevice->QueryInterface(RenderDocID, (void**)RenderDoc.GetInitReference())))
			{
				return true;
			}
		}
	}
	return false;
}

NVSDK_NGX_Result FNGXD3D12RHI::Init_NGX_D3D12(const FNGXRHICreateArguments& InArguments, const wchar_t* InApplicationDataPath, ID3D12Device* InHandle, const NVSDK_NGX_FeatureCommonInfo* InFeatureInfo)
{
	NVSDK_NGX_Result Result = NVSDK_NGX_Result_Fail;
	int32 APIVersion = NVSDK_NGX_VERSION_API_MACRO;
	do 
	{
		if (InArguments.InitializeNGXWithNGXApplicationID())
		{
			Result = NVSDK_NGX_D3D12_Init(InArguments.NGXAppId, InApplicationDataPath, InHandle, InFeatureInfo, static_cast<NVSDK_NGX_Version>(APIVersion));
			UE_LOG(LogDLSSNGXD3D12RHI, Log, TEXT("NVSDK_NGX_D3D12_Init(AppID= %u, APIVersion = 0x%x) -> (%u %s)"), InArguments.NGXAppId, APIVersion, Result, GetNGXResultAsString(Result));
		}
		else
		{
			Result = NVSDK_NGX_D3D12_Init_with_ProjectID(TCHAR_TO_UTF8(*InArguments.UnrealProjectID), NVSDK_NGX_ENGINE_TYPE_UNREAL, TCHAR_TO_UTF8(*InArguments.UnrealEngineVersion), InApplicationDataPath, InHandle, InFeatureInfo, static_cast<NVSDK_NGX_Version>(APIVersion));
			UE_LOG(LogDLSSNGXD3D12RHI, Log, TEXT("NVSDK_NGX_D3D12_Init_with_ProjectID(ProjectID = %s, EngineVersion=%s, APIVersion = 0x%x) -> (%u %s)"), *InArguments.UnrealProjectID, *InArguments.UnrealEngineVersion, APIVersion, Result, GetNGXResultAsString(Result));
		}

		if (NVSDK_NGX_FAILED(Result))
		{
			NVSDK_NGX_D3D12_Shutdown();
		}
		
		--APIVersion;
	} while (NVSDK_NGX_FAILED(Result) && APIVersion >= NVSDK_NGX_VERSION_API_MACRO_BASE_LINE);

	if (NVSDK_NGX_SUCCEED(Result) && (APIVersion + 1 < NVSDK_NGX_VERSION_API_MACRO_WITH_LOGGING))
	{
		UE_LOG(LogDLSSNGXD3D12RHI, Log, TEXT("Warning: NVSDK_NGX_D3D12_Init succeeded, but the driver installed on this system is too old the support the NGX logging API. The console variables r.NGX.LogLevel and r.NGX.DisableOtherLoggingSinks will have no effect and NGX logs will only show up in their own log files, and not in UE4's log files."));
	}

	return Result;
}



FNGXD3D12RHI::FNGXD3D12RHI(const FNGXRHICreateArguments& Arguments)
	: NGXRHI(Arguments)
	, D3D12RHI(static_cast<FD3D12DynamicRHI*>(Arguments.DynamicRHI))
	, Direct3DDevice(D3D12RHI->GetAdapter(AdapterId).GetD3DDevice())
	
{
	ensure(D3D12RHI);
	ensure(Direct3DDevice);
	bIsIncompatibleAPICaptureToolActive = IsIncompatibleAPICaptureToolActive(Direct3DDevice);

	const FString NGXLogDir = GetNGXLogDirectory();
	IPlatformFile::GetPlatformPhysical().CreateDirectoryTree(*NGXLogDir);

	NVSDK_NGX_Result ResultInit = Init_NGX_D3D12(Arguments, *NGXLogDir, Direct3DDevice, CommonFeatureInfo());
	UE_LOG(LogDLSSNGXD3D12RHI, Log, TEXT("NVSDK_NGX_D3D12_Init (Log %s) -> (%u %s)"), *NGXLogDir, ResultInit, GetNGXResultAsString(ResultInit));
	
	// store for the higher level code interpret
	DLSSQueryFeature.DLSSInitResult = ResultInit;

	if (NVSDK_NGX_Result_FAIL_OutOfDate == ResultInit)
	{
		DLSSQueryFeature.DriverRequirements.DriverUpdateRequired = true;
	}
	else if (NVSDK_NGX_Result_Success == ResultInit)
	{
		bNGXInitialized = true;

		NVSDK_NGX_Result ResultGetParameters = NVSDK_NGX_D3D12_GetCapabilityParameters(&DLSSQueryFeature.CapabilityParameters);

		UE_LOG(LogDLSSNGXD3D12RHI, Log, TEXT("NVSDK_NGX_D3D12_GetCapabilityParameters -> (%u %s)"), ResultGetParameters, GetNGXResultAsString(ResultGetParameters));

		if (NVSDK_NGX_Result_FAIL_OutOfDate == ResultGetParameters)
		{
			DLSSQueryFeature.DriverRequirements.DriverUpdateRequired = true;
		}

		if (NVSDK_NGX_FAILED(ResultGetParameters))
		{
			ResultGetParameters = NVSDK_NGX_D3D12_GetParameters(&DLSSQueryFeature.CapabilityParameters);
			UE_LOG(LogDLSSNGXD3D12RHI, Log, TEXT("NVSDK_NGX_D3D12_GetParameters -> (%u %s)"), ResultGetParameters, GetNGXResultAsString(ResultGetParameters));

			bSupportsAllocateParameters = false;
		}

		if (NVSDK_NGX_Result_Success == ResultGetParameters)
		{
			DLSSQueryFeature.QueryDLSSSupport();
		}
	}
}

FNGXD3D12RHI::~FNGXD3D12RHI()
{
	UE_LOG(LogDLSSNGXD3D12RHI, Log, TEXT("%s Enter"), __FUNCTIONW__);
	if (bNGXInitialized)
	{
		// Destroy the parameters and features before we call NVSDK_NGX_D3D11_Shutdown
		ReleaseAllocatedFeatures();
		
		NVSDK_NGX_Result Result;
		if (bSupportsAllocateParameters && DLSSQueryFeature.CapabilityParameters)
		{
			Result = NVSDK_NGX_D3D12_DestroyParameters(DLSSQueryFeature.CapabilityParameters);
			UE_LOG(LogDLSSNGXD3D12RHI, Log, TEXT("NVSDK_NGX_D3D12_DestroyParameters -> (%u %s)"), Result, GetNGXResultAsString(Result));
		}
		Result = NVSDK_NGX_D3D12_Shutdown();
		UE_LOG(LogDLSSNGXD3D12RHI, Log, TEXT("NVSDK_NGX_D3D12_Shutdown -> (%u %s)"), Result, GetNGXResultAsString(Result));
		bNGXInitialized = false;
	}
	UE_LOG(LogDLSSNGXD3D12RHI, Log, TEXT("%s Leave"), __FUNCTIONW__);
}

void FNGXD3D12RHI::ExecuteDLSS(FRHICommandList& CmdList, const FRHIDLSSArguments& InArguments, FDLSSStateRef InDLSSState)
{
	check(!IsRunningRHIInSeparateThread() || IsInRHIThread());
	check(IsDLSSAvailable());
	if (!IsDLSSAvailable()) return;

	InArguments.Validate();

	FD3D12Device* Device = GetD3D12TextureFromRHITexture(InArguments.InputColor)->GetParentDevice();
	ID3D12GraphicsCommandList* D3DGraphicsCommandList = Device->GetCommandContext().CommandListHandle.GraphicsCommandList();
	
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
			NVSDK_NGX_Result Result = NVSDK_NGX_D3D12_AllocateParameters(&NewNGXParameterHandle);
			checkf(Result == NVSDK_NGX_Result_Success, TEXT("NVSDK_NGX_D3D12_AllocateParameters failed! (%u %s)"), Result, GetNGXResultAsString(Result));
		}
		else
		{
			NVSDK_NGX_Result Result = NVSDK_NGX_D3D12_GetParameters(&NewNGXParameterHandle);
			checkf(Result == NVSDK_NGX_Result_Success, TEXT("NVSDK_NGX_D3D12_GetParameters failed! (%u %s)"), Result, GetNGXResultAsString(Result));
		}

		NVSDK_NGX_DLSS_Create_Params DlssCreateParams = InArguments.GetNGXDLSSCreateParams();
		NVSDK_NGX_Handle* NewNGXFeatureHandle = nullptr;

		NVSDK_NGX_Result ResultCreate = NGX_D3D12_CREATE_DLSS_EXT(
			D3DGraphicsCommandList,
			CreationNodeMask,
			VisibilityNodeMask,
			&NewNGXFeatureHandle,
			NewNGXParameterHandle,
			&DlssCreateParams
		);
		InDLSSState->DLSSFeature = MakeShared<FD3D12NGXDLSSFeature>(NewNGXFeatureHandle, NewNGXParameterHandle, InArguments.GetFeatureDesc(), FrameCounter);
		RegisterFeature(InDLSSState->DLSSFeature);
	}

	check(InDLSSState->DLSSFeature);

	// execute
	if (Device->GetCommandContext().IsDefaultContext())
	{
		Device->RegisterGPUWork(1);
	}

	NVSDK_NGX_D3D12_DLSS_Eval_Params DlssEvalParams;
	FMemory::Memzero(DlssEvalParams);

	DlssEvalParams.Feature.pInOutput = GetD3D12TextureFromRHITexture(InArguments.OutputColor)->GetResource()->GetResource();
	DlssEvalParams.InOutputSubrectBase.X = InArguments.DestRect.Min.X;
	DlssEvalParams.InOutputSubrectBase.Y = InArguments.DestRect.Min.Y;

	DlssEvalParams.InRenderSubrectDimensions.Width = InArguments.SrcRect.Width();
	DlssEvalParams.InRenderSubrectDimensions.Height = InArguments.SrcRect.Height();

	DlssEvalParams.Feature.pInColor = GetD3D12TextureFromRHITexture(InArguments.InputColor)->GetResource()->GetResource();
	DlssEvalParams.InColorSubrectBase.X = InArguments.SrcRect.Min.X;
	DlssEvalParams.InColorSubrectBase.Y = InArguments.SrcRect.Min.Y;

	DlssEvalParams.pInDepth = GetD3D12TextureFromRHITexture(InArguments.InputDepth)->GetResource()->GetResource();
	DlssEvalParams.InDepthSubrectBase.X = InArguments.SrcRect.Min.X;
	DlssEvalParams.InDepthSubrectBase.Y = InArguments.SrcRect.Min.Y;

	DlssEvalParams.pInMotionVectors = GetD3D12TextureFromRHITexture(InArguments.InputMotionVectors)->GetResource()->GetResource();
	// The VelocityCombine pass puts the motion vectors into the top left corner
	DlssEvalParams.InMVSubrectBase.X = 0;
	DlssEvalParams.InMVSubrectBase.Y = 0;

	DlssEvalParams.pInExposureTexture = GetD3D12TextureFromRHITexture(InArguments.InputExposure)->GetResource()->GetResource();
	DlssEvalParams.InPreExposure = InArguments.PreExposure;

	DlssEvalParams.Feature.InSharpness = InArguments.Sharpness;
	DlssEvalParams.InJitterOffsetX = InArguments.JitterOffset.X;
	DlssEvalParams.InJitterOffsetY = InArguments.JitterOffset.Y;

	DlssEvalParams.InMVScaleX = InArguments.MotionVectorScale.X;
	DlssEvalParams.InMVScaleY = InArguments.MotionVectorScale.Y;
	DlssEvalParams.InReset = InArguments.bReset;

	DlssEvalParams.InFrameTimeDeltaInMsec = InArguments.DeltaTime;

	NVSDK_NGX_Result ResultEvaluate = NGX_D3D12_EVALUATE_DLSS_EXT(
		D3DGraphicsCommandList,
		InDLSSState->DLSSFeature->Feature,
		InDLSSState->DLSSFeature->Parameter,
		&DlssEvalParams
	);
	checkf(ResultEvaluate == NVSDK_NGX_Result_Success, TEXT("NGX_D3D12_EVALUATE_DLSS_EXT failed! (%u %s)"), ResultEvaluate, GetNGXResultAsString(ResultEvaluate));
	
	InDLSSState->DLSSFeature->Tick(FrameCounter);

	Device->GetCommandContext().StateCache.ForceSetComputeRootSignature();
	Device->GetCommandContext().StateCache.GetDescriptorCache()->SetCurrentCommandList(Device->GetCommandContext().CommandListHandle);
	
}

/** IModuleInterface implementation */

void FNGXD3D12RHIModule::StartupModule()
{
}

void FNGXD3D12RHIModule::ShutdownModule()
{
}

TUniquePtr<NGXRHI> FNGXD3D12RHIModule::CreateNGXRHI(const FNGXRHICreateArguments& Arguments)
{
	TUniquePtr<NGXRHI> Result(new FNGXD3D12RHI(Arguments));
	return Result;
}

IMPLEMENT_MODULE(FNGXD3D12RHIModule, NGXD3D12RHI)

#undef LOCTEXT_NAMESPACE




