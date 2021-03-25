/*
* Copyright (c) 2018 NVIDIA CORPORATION.  All rights reserved.
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

#ifndef NVSDK_NGX_HELPERS_H
#define NVSDK_NGX_HELPERS_H
#pragma once

#include "nvsdk_ngx.h"
#include "nvsdk_ngx_defs.h"

typedef NVSDK_NGX_Result(NVSDK_CONV *PFN_NVSDK_NGX_DLSS_GetStatsCallback)(NVSDK_NGX_Parameter *InParams);

static inline NVSDK_NGX_Result NGX_DLSS_GET_STATS(
    NVSDK_NGX_Parameter *pInParams,
    unsigned long long *pVRAMAllocatedBytes)
{
    void *Callback = NULL;
    NVSDK_NGX_Parameter_GetVoidPointer(pInParams, NVSDK_NGX_Parameter_DLSSGetStatsCallback, &Callback);
    if (!Callback)
    {
        // Possible reasons for this:
        // - Installed DLSS is out of date and does not support the feature we need
        // - You used NVSDK_NGX_AllocateParameters() for creating InParams. Try using NVSDK_NGX_GetCapabilityParameters() instead
        return NVSDK_NGX_Result_FAIL_OutOfDate;
    }

    NVSDK_NGX_Result Res = NVSDK_NGX_Result_Success;
    PFN_NVSDK_NGX_DLSS_GetStatsCallback PFNCallback = (PFN_NVSDK_NGX_DLSS_GetStatsCallback)Callback;
    Res = PFNCallback(pInParams);
    if (NVSDK_NGX_FAILED(Res))
    {
        return Res;
    }
    NVSDK_NGX_Parameter_GetULL(pInParams, NVSDK_NGX_Parameter_SizeInBytes, pVRAMAllocatedBytes);
    return Res;
}

typedef NVSDK_NGX_Result(NVSDK_CONV *PFN_NVSDK_NGX_DLSS_GetOptimalSettingsCallback)(NVSDK_NGX_Parameter *InParams);

static inline NVSDK_NGX_Result NGX_DLSS_GET_OPTIMAL_SETTINGS(
    NVSDK_NGX_Parameter *pInParams,
    unsigned int InUserSelectedWidth,
    unsigned int InUserSelectedHeight,
    NVSDK_NGX_PerfQuality_Value InPerfQualityValue,
    unsigned int *pOutRenderOptimalWidth,
    unsigned int *pOutRenderOptimalHeight,
    unsigned int *pOutRenderMaxWidth,
    unsigned int *pOutRenderMaxHeight,
    unsigned int *pOutRenderMinWidth,
    unsigned int *pOutRenderMinHeight,
    float *pOutSharpness)
{
    void *Callback = NULL;
    NVSDK_NGX_Parameter_GetVoidPointer(pInParams, NVSDK_NGX_Parameter_DLSSOptimalSettingsCallback, &Callback);
    if (!Callback)
    {
        // Possible reasons for this:
        // - Installed DLSS is out of date and does not support the feature we need
        // - You used NVSDK_NGX_AllocateParameters() for creating InParams. Try using NVSDK_NGX_GetCapabilityParameters() instead
        return NVSDK_NGX_Result_FAIL_OutOfDate;
    }

    // These are selections made by user in UI
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_Width, InUserSelectedWidth);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_Height, InUserSelectedHeight);
    NVSDK_NGX_Parameter_SetI(pInParams, NVSDK_NGX_Parameter_PerfQualityValue, InPerfQualityValue);
    NVSDK_NGX_Parameter_SetI(pInParams, NVSDK_NGX_Parameter_RTXValue, false); // Some older DLSS dlls still expect this value to be set

    NVSDK_NGX_Result Res = NVSDK_NGX_Result_Success;
    PFN_NVSDK_NGX_DLSS_GetOptimalSettingsCallback PFNCallback = (PFN_NVSDK_NGX_DLSS_GetOptimalSettingsCallback)Callback;
    Res = PFNCallback(pInParams);
    if (NVSDK_NGX_FAILED(Res))
    {
        return Res;
    }
    NVSDK_NGX_Parameter_GetUI(pInParams, NVSDK_NGX_Parameter_OutWidth, pOutRenderOptimalWidth);
    NVSDK_NGX_Parameter_GetUI(pInParams, NVSDK_NGX_Parameter_OutHeight, pOutRenderOptimalHeight);
    // If we have an older DLSS Dll those might need to be set to the optimal dimensions instead
    *pOutRenderMaxWidth  = *pOutRenderOptimalWidth;
    *pOutRenderMaxHeight = *pOutRenderOptimalHeight;
    *pOutRenderMinWidth  = *pOutRenderOptimalWidth;
    *pOutRenderMinHeight = *pOutRenderOptimalHeight;
    NVSDK_NGX_Parameter_GetUI(pInParams, NVSDK_NGX_Parameter_DLSS_Get_Dynamic_Max_Render_Width,  pOutRenderMaxWidth);
    NVSDK_NGX_Parameter_GetUI(pInParams, NVSDK_NGX_Parameter_DLSS_Get_Dynamic_Max_Render_Height, pOutRenderMaxHeight);
    NVSDK_NGX_Parameter_GetUI(pInParams, NVSDK_NGX_Parameter_DLSS_Get_Dynamic_Min_Render_Width,  pOutRenderMinWidth);
    NVSDK_NGX_Parameter_GetUI(pInParams, NVSDK_NGX_Parameter_DLSS_Get_Dynamic_Min_Render_Height, pOutRenderMinHeight);
    NVSDK_NGX_Parameter_GetF(pInParams, NVSDK_NGX_Parameter_Sharpness, pOutSharpness);
    return Res;
}

/*** D3D11 ***/
typedef struct NVSDK_NGX_D3D11_Feature_Eval_Params
{
    ID3D11Resource*  pInColor;
    ID3D11Resource*  pInOutput;
    /*** OPTIONAL for DLSS ***/
    float       InSharpness;
} NVSDK_NGX_D3D11_Feature_Eval_Params;

typedef struct NVSDK_NGX_CUDA_Feature_Eval_Params
{
    CUtexObject* pInColor;
    CUtexObject* pInOutput;
    /*** OPTIONAL for DLSS ***/
    float       InSharpness;
} NVSDK_NGX_CUDA_Feature_Eval_Params;

typedef struct NVSDK_NGX_D3D11_GBuffer
{
    ID3D11Resource* pInAttrib[NVSDK_NGX_GBUFFERTYPE_NUM];
} NVSDK_NGX_D3D11_GBuffer;

typedef struct NVSDK_NGX_D3D11_DLSS_Eval_Params
{
    NVSDK_NGX_D3D11_Feature_Eval_Params Feature;
    ID3D11Resource*                     pInDepth;
    ID3D11Resource*                     pInMotionVectors;
    float                               InJitterOffsetX;
    float                               InJitterOffsetY;
    NVSDK_NGX_Dimensions                InRenderSubrectDimensions;
    /*** OPTIONAL ***/
    int                                 InReset;
    float                               InMVScaleX;
    float                               InMVScaleY;
    ID3D11Resource*                     pInTransparencyMask; /* per pixel mask identifying alpha-blended objects like particles etc. */
    ID3D11Resource*                     pInExposureTexture;
    ID3D11Resource*                     pInBiasCurrentColorMask;
    NVSDK_NGX_Coordinates               InColorSubrectBase;
    NVSDK_NGX_Coordinates               InDepthSubrectBase;
    NVSDK_NGX_Coordinates               InMVSubrectBase;
    NVSDK_NGX_Coordinates               InTranslucencySubrectBase;
    NVSDK_NGX_Coordinates               InBiasCurrentColorSubrectBase;
    NVSDK_NGX_Coordinates               InOutputSubrectBase;
    float                               InPreExposure;
    int                                 InIndicatorInvertXAxis;
    int                                 InIndicatorInvertYAxis;
    /*** OPTIONAL - only for research purposes ***/
    NVSDK_NGX_D3D11_GBuffer             GBufferSurface;
    NVSDK_NGX_ToneMapperType            InToneMapperType;
    ID3D11Resource*                     pInMotionVectors3D;
    ID3D11Resource*                     pInIsParticleMask; /* to identify which pixels contains particles, essentially that are not drawn as part of base pass */
    ID3D11Resource*                     pInAnimatedTextureMask; /* a binary mask covering pixels occupied by animated textures */
    ID3D11Resource*                     pInDepthHighRes;
    ID3D11Resource*                     pInPositionViewSpace;
    float                               InFrameTimeDeltaInMsec; /* helps in determining the amount to denoise or anti-alias based on the speed of the object from motion vector magnitudes and fps as determined by this delta */
    ID3D11Resource*                     pInRayTracingHitDistance; /* for each effect - approximation to the amount of noise in a ray-traced color */
    ID3D11Resource*                     pInMotionVectorsReflections; /* motion vectors of reflected objects like for mirrored surfaces */
} NVSDK_NGX_D3D11_DLSS_Eval_Params;

typedef struct NVSDK_NGX_D3D11_DLISP_Eval_Params
{
    NVSDK_NGX_D3D11_Feature_Eval_Params Feature;
    /*** OPTIONAL ***/
    unsigned int                    InRectX;
    unsigned int                    InRectY;
    unsigned int                    InRectW;
    unsigned int                    InRectH;
    float                           InDenoise;
} NVSDK_NGX_D3D11_DLISP_Eval_Params;

typedef struct NVSDK_NGX_CUDA_DLISP_Eval_Params
{
    NVSDK_NGX_CUDA_Feature_Eval_Params Feature;
    /*** OPTIONAL ***/
    unsigned int                    InRectX;
    unsigned int                    InRectY;
    unsigned int                    InRectW;
    unsigned int                    InRectH;
    float                           InDenoise;
} NVSDK_NGX_CUDA_DLISP_Eval_Params;

static inline NVSDK_NGX_Result NGX_D3D11_CREATE_DLSS_EXT(
    ID3D11DeviceContext *pInCtx,
    NVSDK_NGX_Handle **ppOutHandle,
    NVSDK_NGX_Parameter *pInParams,
    NVSDK_NGX_DLSS_Create_Params *pInDlssCreateParams)
{
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_Width, pInDlssCreateParams->Feature.InWidth);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_Height, pInDlssCreateParams->Feature.InHeight);
    // Should be the same as Width/Height unless engine supports upscaled AA (e.g. TAAU)
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_OutWidth, pInDlssCreateParams->Feature.InTargetWidth);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_OutHeight, pInDlssCreateParams->Feature.InTargetHeight);
    NVSDK_NGX_Parameter_SetI(pInParams, NVSDK_NGX_Parameter_PerfQualityValue, pInDlssCreateParams->Feature.InPerfQualityValue);
    NVSDK_NGX_Parameter_SetI(pInParams, NVSDK_NGX_Parameter_DLSS_Feature_Create_Flags, pInDlssCreateParams->InFeatureCreateFlags);
    NVSDK_NGX_Parameter_SetI(pInParams, NVSDK_NGX_Parameter_DLSS_Enable_Output_Subrects, pInDlssCreateParams->InEnableOutputSubrects ? 1 : 0);

    return NVSDK_NGX_D3D11_CreateFeature(pInCtx, NVSDK_NGX_Feature_SuperSampling, pInParams, ppOutHandle);
}

static inline NVSDK_NGX_Result NGX_D3D11_EVALUATE_DLSS_EXT(
    ID3D11DeviceContext *pInCtx,
    NVSDK_NGX_Handle *pInHandle,
    NVSDK_NGX_Parameter *pInParams,
    NVSDK_NGX_D3D11_DLSS_Eval_Params *pInDlssEvalParams)
{
    NVSDK_NGX_Parameter_SetD3d11Resource(pInParams, NVSDK_NGX_Parameter_Color, pInDlssEvalParams->Feature.pInColor);
    NVSDK_NGX_Parameter_SetD3d11Resource(pInParams, NVSDK_NGX_Parameter_Output, pInDlssEvalParams->Feature.pInOutput);
    NVSDK_NGX_Parameter_SetD3d11Resource(pInParams, NVSDK_NGX_Parameter_Depth, pInDlssEvalParams->pInDepth);
    NVSDK_NGX_Parameter_SetD3d11Resource(pInParams, NVSDK_NGX_Parameter_MotionVectors, pInDlssEvalParams->pInMotionVectors);
    // Jitter offset must be in pixel space
    NVSDK_NGX_Parameter_SetF(pInParams, NVSDK_NGX_Parameter_Jitter_Offset_X, pInDlssEvalParams->InJitterOffsetX);
    NVSDK_NGX_Parameter_SetF(pInParams, NVSDK_NGX_Parameter_Jitter_Offset_Y, pInDlssEvalParams->InJitterOffsetY);
    NVSDK_NGX_Parameter_SetF(pInParams, NVSDK_NGX_Parameter_Sharpness, pInDlssEvalParams->Feature.InSharpness);
    // Set to 1 when scene changes completely (new level etc)
    NVSDK_NGX_Parameter_SetI(pInParams, NVSDK_NGX_Parameter_Reset, pInDlssEvalParams->InReset);
    // If MVs need custom scaling to convert to pixel space
    NVSDK_NGX_Parameter_SetF(pInParams, NVSDK_NGX_Parameter_MV_Scale_X, pInDlssEvalParams->InMVScaleX);
    NVSDK_NGX_Parameter_SetF(pInParams, NVSDK_NGX_Parameter_MV_Scale_Y, pInDlssEvalParams->InMVScaleY);
    NVSDK_NGX_Parameter_SetD3d11Resource(pInParams, NVSDK_NGX_Parameter_TransparencyMask, pInDlssEvalParams->pInTransparencyMask);
    NVSDK_NGX_Parameter_SetD3d11Resource(pInParams, NVSDK_NGX_Parameter_ExposureTexture, pInDlssEvalParams->pInExposureTexture);
    NVSDK_NGX_Parameter_SetD3d11Resource(pInParams, NVSDK_NGX_Parameter_DLSS_Input_Bias_Current_Color_Mask, pInDlssEvalParams->pInBiasCurrentColorMask);
    NVSDK_NGX_Parameter_SetD3d11Resource(pInParams, NVSDK_NGX_Parameter_GBuffer_Albedo, pInDlssEvalParams->GBufferSurface.pInAttrib[NVSDK_NGX_GBUFFER_ALBEDO]);
    NVSDK_NGX_Parameter_SetD3d11Resource(pInParams, NVSDK_NGX_Parameter_GBuffer_Roughness, pInDlssEvalParams->GBufferSurface.pInAttrib[NVSDK_NGX_GBUFFER_ROUGHNESS]);
    NVSDK_NGX_Parameter_SetD3d11Resource(pInParams, NVSDK_NGX_Parameter_GBuffer_Metallic, pInDlssEvalParams->GBufferSurface.pInAttrib[NVSDK_NGX_GBUFFER_METALLIC]);
    NVSDK_NGX_Parameter_SetD3d11Resource(pInParams, NVSDK_NGX_Parameter_GBuffer_Specular, pInDlssEvalParams->GBufferSurface.pInAttrib[NVSDK_NGX_GBUFFER_SPECULAR]);
    NVSDK_NGX_Parameter_SetD3d11Resource(pInParams, NVSDK_NGX_Parameter_GBuffer_Subsurface, pInDlssEvalParams->GBufferSurface.pInAttrib[NVSDK_NGX_GBUFFER_SUBSURFACE]);
    NVSDK_NGX_Parameter_SetD3d11Resource(pInParams, NVSDK_NGX_Parameter_GBuffer_Normals, pInDlssEvalParams->GBufferSurface.pInAttrib[NVSDK_NGX_GBUFFER_NORMALS]);
    NVSDK_NGX_Parameter_SetD3d11Resource(pInParams, NVSDK_NGX_Parameter_GBuffer_ShadingModelId, pInDlssEvalParams->GBufferSurface.pInAttrib[NVSDK_NGX_GBUFFER_SHADINGMODELID]);
    NVSDK_NGX_Parameter_SetD3d11Resource(pInParams, NVSDK_NGX_Parameter_GBuffer_MaterialId, pInDlssEvalParams->GBufferSurface.pInAttrib[NVSDK_NGX_GBUFFER_MATERIALID]);
    NVSDK_NGX_Parameter_SetD3d11Resource(pInParams, NVSDK_NGX_Parameter_GBuffer_Atrrib_8, pInDlssEvalParams->GBufferSurface.pInAttrib[8]);
    NVSDK_NGX_Parameter_SetD3d11Resource(pInParams, NVSDK_NGX_Parameter_GBuffer_Atrrib_9, pInDlssEvalParams->GBufferSurface.pInAttrib[9]);
    NVSDK_NGX_Parameter_SetD3d11Resource(pInParams, NVSDK_NGX_Parameter_GBuffer_Atrrib_10, pInDlssEvalParams->GBufferSurface.pInAttrib[10]);
    NVSDK_NGX_Parameter_SetD3d11Resource(pInParams, NVSDK_NGX_Parameter_GBuffer_Atrrib_11, pInDlssEvalParams->GBufferSurface.pInAttrib[11]);
    NVSDK_NGX_Parameter_SetD3d11Resource(pInParams, NVSDK_NGX_Parameter_GBuffer_Atrrib_12, pInDlssEvalParams->GBufferSurface.pInAttrib[12]);
    NVSDK_NGX_Parameter_SetD3d11Resource(pInParams, NVSDK_NGX_Parameter_GBuffer_Atrrib_13, pInDlssEvalParams->GBufferSurface.pInAttrib[13]);
    NVSDK_NGX_Parameter_SetD3d11Resource(pInParams, NVSDK_NGX_Parameter_GBuffer_Atrrib_14, pInDlssEvalParams->GBufferSurface.pInAttrib[14]);
    NVSDK_NGX_Parameter_SetD3d11Resource(pInParams, NVSDK_NGX_Parameter_GBuffer_Atrrib_15, pInDlssEvalParams->GBufferSurface.pInAttrib[15]);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_TonemapperType, pInDlssEvalParams->InToneMapperType);
    NVSDK_NGX_Parameter_SetD3d11Resource(pInParams, NVSDK_NGX_Parameter_MotionVectors3D, pInDlssEvalParams->pInMotionVectors3D);
    NVSDK_NGX_Parameter_SetD3d11Resource(pInParams, NVSDK_NGX_Parameter_IsParticleMask, pInDlssEvalParams->pInIsParticleMask);
    NVSDK_NGX_Parameter_SetD3d11Resource(pInParams, NVSDK_NGX_Parameter_AnimatedTextureMask, pInDlssEvalParams->pInAnimatedTextureMask);
    NVSDK_NGX_Parameter_SetD3d11Resource(pInParams, NVSDK_NGX_Parameter_DepthHighRes, pInDlssEvalParams->pInDepthHighRes);
    NVSDK_NGX_Parameter_SetD3d11Resource(pInParams, NVSDK_NGX_Parameter_Position_ViewSpace, pInDlssEvalParams->pInPositionViewSpace);
    NVSDK_NGX_Parameter_SetF(pInParams, NVSDK_NGX_Parameter_FrameTimeDeltaInMsec, pInDlssEvalParams->InFrameTimeDeltaInMsec);
    NVSDK_NGX_Parameter_SetD3d11Resource(pInParams, NVSDK_NGX_Parameter_RayTracingHitDistance, pInDlssEvalParams->pInRayTracingHitDistance);
    NVSDK_NGX_Parameter_SetD3d11Resource(pInParams, NVSDK_NGX_Parameter_MotionVectorsReflection, pInDlssEvalParams->pInMotionVectorsReflections);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_DLSS_Input_Color_Subrect_Base_X, pInDlssEvalParams->InColorSubrectBase.X);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_DLSS_Input_Color_Subrect_Base_Y, pInDlssEvalParams->InColorSubrectBase.Y);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_DLSS_Input_Depth_Subrect_Base_X, pInDlssEvalParams->InDepthSubrectBase.X);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_DLSS_Input_Depth_Subrect_Base_Y, pInDlssEvalParams->InDepthSubrectBase.Y);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_DLSS_Input_MV_SubrectBase_X, pInDlssEvalParams->InMVSubrectBase.X);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_DLSS_Input_MV_SubrectBase_Y, pInDlssEvalParams->InMVSubrectBase.Y);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_DLSS_Input_Translucency_SubrectBase_X, pInDlssEvalParams->InTranslucencySubrectBase.X);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_DLSS_Input_Translucency_SubrectBase_Y, pInDlssEvalParams->InTranslucencySubrectBase.Y);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_DLSS_Input_Bias_Current_Color_SubrectBase_X, pInDlssEvalParams->InBiasCurrentColorSubrectBase.X);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_DLSS_Input_Bias_Current_Color_SubrectBase_Y, pInDlssEvalParams->InBiasCurrentColorSubrectBase.Y);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_DLSS_Output_Subrect_Base_X, pInDlssEvalParams->InOutputSubrectBase.X);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_DLSS_Output_Subrect_Base_Y, pInDlssEvalParams->InOutputSubrectBase.Y);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_DLSS_Render_Subrect_Dimensions_Width , pInDlssEvalParams->InRenderSubrectDimensions.Width);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_DLSS_Render_Subrect_Dimensions_Height, pInDlssEvalParams->InRenderSubrectDimensions.Height);
    NVSDK_NGX_Parameter_SetF(pInParams, NGSDK_NGX_Parameter_DLSS_Pre_Exposure, pInDlssEvalParams->InPreExposure == 0.0f ? 1.0f : pInDlssEvalParams->InPreExposure);
    NVSDK_NGX_Parameter_SetI(pInParams, NVSDK_NGX_Parameter_DLSS_Indicator_Invert_X_Axis, pInDlssEvalParams->InIndicatorInvertXAxis);
    NVSDK_NGX_Parameter_SetI(pInParams, NVSDK_NGX_Parameter_DLSS_Indicator_Invert_Y_Axis, pInDlssEvalParams->InIndicatorInvertYAxis);

    return NVSDK_NGX_D3D11_EvaluateFeature_C(pInCtx, pInHandle, pInParams, NULL);
}


static inline NVSDK_NGX_Result NGX_D3D11_CREATE_DLISP_EXT(
    ID3D11DeviceContext *pInCtx,
    NVSDK_NGX_Handle **ppOutHandle,
    NVSDK_NGX_Parameter *pInParams,
    NVSDK_NGX_Feature_Create_Params *pDlispCreateParams)
{
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_Width, pDlispCreateParams->InWidth);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_Height, pDlispCreateParams->InHeight);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_OutWidth, pDlispCreateParams->InTargetWidth);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_OutHeight, pDlispCreateParams->InTargetHeight);

    return NVSDK_NGX_D3D11_CreateFeature(pInCtx, NVSDK_NGX_Feature_ImageSignalProcessing, pInParams, ppOutHandle);
}

static inline NVSDK_NGX_Result NGX_CUDA_CREATE_DLISP_EXT(
    NVSDK_NGX_Handle** ppOutHandle,
    NVSDK_NGX_Parameter* pInParams,
    NVSDK_NGX_Feature_Create_Params* pDlispCreateParams)
{
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_Width, pDlispCreateParams->InWidth);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_Height, pDlispCreateParams->InHeight);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_OutWidth, pDlispCreateParams->InTargetWidth);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_OutHeight, pDlispCreateParams->InTargetHeight);

    return NVSDK_NGX_CUDA_CreateFeature(NVSDK_NGX_Feature_ImageSignalProcessing, pInParams, ppOutHandle);
}

static inline NVSDK_NGX_Result NGX_D3D11_EVALUATE_DLISP_EXT(
    ID3D11DeviceContext *pInCtx,
    NVSDK_NGX_Handle *pInHandle,
    NVSDK_NGX_Parameter *pInParams,
    NVSDK_NGX_D3D11_DLISP_Eval_Params *pDlispEvalParams)
{
    if (pDlispEvalParams->Feature.InSharpness < 0.0f || pDlispEvalParams->Feature.InSharpness > 1.0f || pDlispEvalParams->InDenoise < 0.0f || pDlispEvalParams->InDenoise > 1.0f)
    {
        return NVSDK_NGX_Result_FAIL_InvalidParameter;
    }
    NVSDK_NGX_Parameter_SetD3d11Resource(pInParams, NVSDK_NGX_Parameter_Color, pDlispEvalParams->Feature.pInColor);
    NVSDK_NGX_Parameter_SetD3d11Resource(pInParams, NVSDK_NGX_Parameter_Output, pDlispEvalParams->Feature.pInOutput);
    // Both sharpness and denoise in range [0.0f,1.0f]
    NVSDK_NGX_Parameter_SetF(pInParams, NVSDK_NGX_Parameter_Sharpness, pDlispEvalParams->Feature.InSharpness);
    NVSDK_NGX_Parameter_SetF(pInParams, NVSDK_NGX_Parameter_Denoise, pDlispEvalParams->InDenoise);
    // If input is atlas - use RECT to upscale only the required area
    if (pDlispEvalParams->InRectW)
    {
        NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_Rect_X, pDlispEvalParams->InRectX);
        NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_Rect_Y, pDlispEvalParams->InRectY);
        NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_Rect_W, pDlispEvalParams->InRectW);
        NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_Rect_H, pDlispEvalParams->InRectH);
    }

    return NVSDK_NGX_D3D11_EvaluateFeature_C(pInCtx, pInHandle, pInParams, NULL);
}

static inline NVSDK_NGX_Result NGX_CUDA_EVALUATE_DLISP_EXT(
    NVSDK_NGX_Handle *pInHandle,
    NVSDK_NGX_Parameter *pInParams,
    NVSDK_NGX_CUDA_DLISP_Eval_Params *pDlispEvalParams)
{
    if (pDlispEvalParams->Feature.InSharpness < 0.0f || pDlispEvalParams->Feature.InSharpness > 1.0f || pDlispEvalParams->InDenoise < 0.0f || pDlispEvalParams->InDenoise > 1.0f)
    {
        return NVSDK_NGX_Result_FAIL_InvalidParameter;
    }
    NVSDK_NGX_Parameter_SetVoidPointer(pInParams, NVSDK_NGX_Parameter_Color, pDlispEvalParams->Feature.pInColor);
    NVSDK_NGX_Parameter_SetVoidPointer(pInParams, NVSDK_NGX_Parameter_Output, pDlispEvalParams->Feature.pInOutput);
    // Both sharpness and denoise in range [0.0f,1.0f]
    NVSDK_NGX_Parameter_SetF(pInParams, NVSDK_NGX_Parameter_Sharpness, pDlispEvalParams->Feature.InSharpness);
    NVSDK_NGX_Parameter_SetF(pInParams, NVSDK_NGX_Parameter_Denoise, pDlispEvalParams->InDenoise);
    // If input is atlas - use RECT to upscale only the required area
    if (pDlispEvalParams->InRectW)
    {
        NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_Rect_X, pDlispEvalParams->InRectX);
        NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_Rect_Y, pDlispEvalParams->InRectY);
        NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_Rect_W, pDlispEvalParams->InRectW);
        NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_Rect_H, pDlispEvalParams->InRectH);
    }

    return NVSDK_NGX_CUDA_EvaluateFeature_C(pInHandle, pInParams, NULL);
}

static inline NVSDK_NGX_Result NGX_D3D11_CREATE_DLRESOLVE_EXT(
    ID3D11DeviceContext *pInCtx,
    NVSDK_NGX_Handle **ppOutHandle,
    NVSDK_NGX_Parameter *pInParams,
    NVSDK_NGX_Feature_Create_Params *pDlresolveCreateParams)
{
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_Width, pDlresolveCreateParams->InWidth);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_Height, pDlresolveCreateParams->InHeight);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_OutWidth, pDlresolveCreateParams->InTargetWidth);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_OutHeight, pDlresolveCreateParams->InTargetHeight);

    return NVSDK_NGX_D3D11_CreateFeature(pInCtx, NVSDK_NGX_Feature_DeepResolve, pInParams, ppOutHandle);
}

static inline NVSDK_NGX_Result NGX_D3D11_EVALUATE_DLRESOLVE_EXT(
    ID3D11DeviceContext *pInCtx,
    NVSDK_NGX_Handle *InHandle,
    NVSDK_NGX_Parameter *pInParams,
    NVSDK_NGX_D3D11_Feature_Eval_Params *pDlresolveEvalParams)
{
    NVSDK_NGX_Parameter_SetD3d11Resource(pInParams, NVSDK_NGX_Parameter_Color, pDlresolveEvalParams->pInColor);
    NVSDK_NGX_Parameter_SetD3d11Resource(pInParams, NVSDK_NGX_Parameter_Output, pDlresolveEvalParams->pInOutput);
    NVSDK_NGX_Parameter_SetF(pInParams, NVSDK_NGX_Parameter_Sharpness, pDlresolveEvalParams->InSharpness);

    return NVSDK_NGX_D3D11_EvaluateFeature_C(pInCtx, InHandle, pInParams, NULL);
}


/*** D3D12 ***/
typedef struct NVSDK_NGX_D3D12_Feature_Eval_Params
{
    ID3D12Resource*  pInColor;
    ID3D12Resource*  pInOutput;
    /*** OPTIONAL for DLSS ***/
    float       InSharpness;
} NVSDK_NGX_D3D12_Feature_Eval_Params;

typedef struct NVSDK_NGX_D3D12_GBuffer
{
    ID3D12Resource* pInAttrib[NVSDK_NGX_GBUFFERTYPE_NUM];
} NVSDK_NGX_D3D12_GBuffer;

typedef struct NVSDK_NGX_D3D12_DLSS_Eval_Params
{
    NVSDK_NGX_D3D12_Feature_Eval_Params Feature;
    ID3D12Resource*                     pInDepth;
    ID3D12Resource*                     pInMotionVectors;
    float                               InJitterOffsetX;
    float                               InJitterOffsetY;
    NVSDK_NGX_Dimensions                InRenderSubrectDimensions;
    /*** OPTIONAL ***/
    int                                 InReset;
    float                               InMVScaleX;
    float                               InMVScaleY;
    ID3D12Resource*                     pInTransparencyMask; /* per pixel mask identifying alpha-blended objects like particles etc. */
    ID3D12Resource*                     pInExposureTexture;
    ID3D12Resource*                     pInBiasCurrentColorMask;
    NVSDK_NGX_Coordinates               InColorSubrectBase;
    NVSDK_NGX_Coordinates               InDepthSubrectBase;
    NVSDK_NGX_Coordinates               InMVSubrectBase;
    NVSDK_NGX_Coordinates               InTranslucencySubrectBase;
    NVSDK_NGX_Coordinates               InBiasCurrentColorSubrectBase;
    NVSDK_NGX_Coordinates               InOutputSubrectBase;
    float                               InPreExposure;
    int                                 InIndicatorInvertXAxis;
    int                                 InIndicatorInvertYAxis;
    /*** OPTIONAL - only for research purposes ***/
    NVSDK_NGX_D3D12_GBuffer             GBufferSurface;
    NVSDK_NGX_ToneMapperType            InToneMapperType;
    ID3D12Resource*                     pInMotionVectors3D;
    ID3D12Resource*                     pInIsParticleMask; /* to identify which pixels contains particles, essentially that are not drawn as part of base pass */
    ID3D12Resource*                     pInAnimatedTextureMask; /* a binary mask covering pixels occupied by animated textures */
    ID3D12Resource*                     pInDepthHighRes;
    ID3D12Resource*                     pInPositionViewSpace;
    float                               InFrameTimeDeltaInMsec; /* helps in determining the amount to denoise or anti-alias based on the speed of the object from motion vector magnitudes and fps as determined by this delta */
    ID3D12Resource*                     pInRayTracingHitDistance; /* for each effect - approximation to the amount of noise in a ray-traced color */
    ID3D12Resource*                     pInMotionVectorsReflections; /* motion vectors of reflected objects like for mirrored surfaces */
} NVSDK_NGX_D3D12_DLSS_Eval_Params;

typedef struct NVSDK_NGX_D3D12_DLISP_Eval_Params
{
    NVSDK_NGX_D3D12_Feature_Eval_Params Feature;
    /*** OPTIONAL ***/
    unsigned int                        InRectX;
    unsigned int                        InRectY;
    unsigned int                        InRectW;
    unsigned int                        InRectH;
    float                               InDenoise;
} NVSDK_NGX_D3D12_DLISP_Eval_Params;


static inline NVSDK_NGX_Result NGX_D3D12_CREATE_DLSS_EXT(
    ID3D12GraphicsCommandList *pInCmdList,
    unsigned int InCreationNodeMask,
    unsigned int InVisibilityNodeMask,
    NVSDK_NGX_Handle **ppOutHandle,
    NVSDK_NGX_Parameter *pInParams,
    NVSDK_NGX_DLSS_Create_Params *pInDlssCreateParams)
{
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_CreationNodeMask, InCreationNodeMask);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_VisibilityNodeMask, InVisibilityNodeMask);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_Width, pInDlssCreateParams->Feature.InWidth);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_Height, pInDlssCreateParams->Feature.InHeight);
    // Should be the same as Width/Height unless engine supports upscaled AA (e.g. TAAU)
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_OutWidth, pInDlssCreateParams->Feature.InTargetWidth);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_OutHeight, pInDlssCreateParams->Feature.InTargetHeight);
    NVSDK_NGX_Parameter_SetI(pInParams, NVSDK_NGX_Parameter_PerfQualityValue, pInDlssCreateParams->Feature.InPerfQualityValue);
    NVSDK_NGX_Parameter_SetI(pInParams, NVSDK_NGX_Parameter_DLSS_Feature_Create_Flags, pInDlssCreateParams->InFeatureCreateFlags);
    NVSDK_NGX_Parameter_SetI(pInParams, NVSDK_NGX_Parameter_DLSS_Enable_Output_Subrects, pInDlssCreateParams->InEnableOutputSubrects ? 1 : 0);

    return NVSDK_NGX_D3D12_CreateFeature(pInCmdList, NVSDK_NGX_Feature_SuperSampling, pInParams, ppOutHandle);
}

static inline NVSDK_NGX_Result NGX_D3D12_EVALUATE_DLSS_EXT(
    ID3D12GraphicsCommandList *pInCmdList,
    NVSDK_NGX_Handle *pInHandle,
    NVSDK_NGX_Parameter *pInParams,
    NVSDK_NGX_D3D12_DLSS_Eval_Params *pInDlssEvalParams)
{
    NVSDK_NGX_Parameter_SetD3d12Resource(pInParams, NVSDK_NGX_Parameter_Color, pInDlssEvalParams->Feature.pInColor);
    NVSDK_NGX_Parameter_SetD3d12Resource(pInParams, NVSDK_NGX_Parameter_Output, pInDlssEvalParams->Feature.pInOutput);
    NVSDK_NGX_Parameter_SetD3d12Resource(pInParams, NVSDK_NGX_Parameter_Depth, pInDlssEvalParams->pInDepth);
    NVSDK_NGX_Parameter_SetD3d12Resource(pInParams, NVSDK_NGX_Parameter_MotionVectors, pInDlssEvalParams->pInMotionVectors);
    // Jitter offset must be in pixel space
    NVSDK_NGX_Parameter_SetF(pInParams, NVSDK_NGX_Parameter_Jitter_Offset_X, pInDlssEvalParams->InJitterOffsetX);
    NVSDK_NGX_Parameter_SetF(pInParams, NVSDK_NGX_Parameter_Jitter_Offset_Y, pInDlssEvalParams->InJitterOffsetY);
    NVSDK_NGX_Parameter_SetF(pInParams, NVSDK_NGX_Parameter_Sharpness, pInDlssEvalParams->Feature.InSharpness);
    // Set to 1 when scene changes completely (new level etc)
    NVSDK_NGX_Parameter_SetI(pInParams, NVSDK_NGX_Parameter_Reset, pInDlssEvalParams->InReset);
    // If MVs need custom scaling to convert to pixel space
    NVSDK_NGX_Parameter_SetF(pInParams, NVSDK_NGX_Parameter_MV_Scale_X, pInDlssEvalParams->InMVScaleX);
    NVSDK_NGX_Parameter_SetF(pInParams, NVSDK_NGX_Parameter_MV_Scale_Y, pInDlssEvalParams->InMVScaleY);
    NVSDK_NGX_Parameter_SetD3d12Resource(pInParams, NVSDK_NGX_Parameter_TransparencyMask, pInDlssEvalParams->pInTransparencyMask);
    NVSDK_NGX_Parameter_SetD3d12Resource(pInParams, NVSDK_NGX_Parameter_ExposureTexture, pInDlssEvalParams->pInExposureTexture);
    NVSDK_NGX_Parameter_SetD3d12Resource(pInParams, NVSDK_NGX_Parameter_DLSS_Input_Bias_Current_Color_Mask, pInDlssEvalParams->pInBiasCurrentColorMask);
    NVSDK_NGX_Parameter_SetD3d12Resource(pInParams, NVSDK_NGX_Parameter_GBuffer_Albedo, pInDlssEvalParams->GBufferSurface.pInAttrib[NVSDK_NGX_GBUFFER_ALBEDO]);
    NVSDK_NGX_Parameter_SetD3d12Resource(pInParams, NVSDK_NGX_Parameter_GBuffer_Roughness, pInDlssEvalParams->GBufferSurface.pInAttrib[NVSDK_NGX_GBUFFER_ROUGHNESS]);
    NVSDK_NGX_Parameter_SetD3d12Resource(pInParams, NVSDK_NGX_Parameter_GBuffer_Metallic, pInDlssEvalParams->GBufferSurface.pInAttrib[NVSDK_NGX_GBUFFER_METALLIC]);
    NVSDK_NGX_Parameter_SetD3d12Resource(pInParams, NVSDK_NGX_Parameter_GBuffer_Specular, pInDlssEvalParams->GBufferSurface.pInAttrib[NVSDK_NGX_GBUFFER_SPECULAR]);
    NVSDK_NGX_Parameter_SetD3d12Resource(pInParams, NVSDK_NGX_Parameter_GBuffer_Subsurface, pInDlssEvalParams->GBufferSurface.pInAttrib[NVSDK_NGX_GBUFFER_SUBSURFACE]);
    NVSDK_NGX_Parameter_SetD3d12Resource(pInParams, NVSDK_NGX_Parameter_GBuffer_Normals, pInDlssEvalParams->GBufferSurface.pInAttrib[NVSDK_NGX_GBUFFER_NORMALS]);
    NVSDK_NGX_Parameter_SetD3d12Resource(pInParams, NVSDK_NGX_Parameter_GBuffer_ShadingModelId, pInDlssEvalParams->GBufferSurface.pInAttrib[NVSDK_NGX_GBUFFER_SHADINGMODELID]);
    NVSDK_NGX_Parameter_SetD3d12Resource(pInParams, NVSDK_NGX_Parameter_GBuffer_MaterialId, pInDlssEvalParams->GBufferSurface.pInAttrib[NVSDK_NGX_GBUFFER_MATERIALID]);
    NVSDK_NGX_Parameter_SetD3d12Resource(pInParams, NVSDK_NGX_Parameter_GBuffer_Atrrib_8, pInDlssEvalParams->GBufferSurface.pInAttrib[8]);
    NVSDK_NGX_Parameter_SetD3d12Resource(pInParams, NVSDK_NGX_Parameter_GBuffer_Atrrib_9, pInDlssEvalParams->GBufferSurface.pInAttrib[9]);
    NVSDK_NGX_Parameter_SetD3d12Resource(pInParams, NVSDK_NGX_Parameter_GBuffer_Atrrib_10, pInDlssEvalParams->GBufferSurface.pInAttrib[10]);
    NVSDK_NGX_Parameter_SetD3d12Resource(pInParams, NVSDK_NGX_Parameter_GBuffer_Atrrib_11, pInDlssEvalParams->GBufferSurface.pInAttrib[11]);
    NVSDK_NGX_Parameter_SetD3d12Resource(pInParams, NVSDK_NGX_Parameter_GBuffer_Atrrib_12, pInDlssEvalParams->GBufferSurface.pInAttrib[12]);
    NVSDK_NGX_Parameter_SetD3d12Resource(pInParams, NVSDK_NGX_Parameter_GBuffer_Atrrib_13, pInDlssEvalParams->GBufferSurface.pInAttrib[13]);
    NVSDK_NGX_Parameter_SetD3d12Resource(pInParams, NVSDK_NGX_Parameter_GBuffer_Atrrib_14, pInDlssEvalParams->GBufferSurface.pInAttrib[14]);
    NVSDK_NGX_Parameter_SetD3d12Resource(pInParams, NVSDK_NGX_Parameter_GBuffer_Atrrib_15, pInDlssEvalParams->GBufferSurface.pInAttrib[15]);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_TonemapperType, pInDlssEvalParams->InToneMapperType);
    NVSDK_NGX_Parameter_SetD3d12Resource(pInParams, NVSDK_NGX_Parameter_MotionVectors3D, pInDlssEvalParams->pInMotionVectors3D);
    NVSDK_NGX_Parameter_SetD3d12Resource(pInParams, NVSDK_NGX_Parameter_IsParticleMask, pInDlssEvalParams->pInIsParticleMask);
    NVSDK_NGX_Parameter_SetD3d12Resource(pInParams, NVSDK_NGX_Parameter_AnimatedTextureMask, pInDlssEvalParams->pInAnimatedTextureMask);
    NVSDK_NGX_Parameter_SetD3d12Resource(pInParams, NVSDK_NGX_Parameter_DepthHighRes, pInDlssEvalParams->pInDepthHighRes);
    NVSDK_NGX_Parameter_SetD3d12Resource(pInParams, NVSDK_NGX_Parameter_Position_ViewSpace, pInDlssEvalParams->pInPositionViewSpace);
    NVSDK_NGX_Parameter_SetF(pInParams, NVSDK_NGX_Parameter_FrameTimeDeltaInMsec, pInDlssEvalParams->InFrameTimeDeltaInMsec);
    NVSDK_NGX_Parameter_SetD3d12Resource(pInParams, NVSDK_NGX_Parameter_RayTracingHitDistance, pInDlssEvalParams->pInRayTracingHitDistance);
    NVSDK_NGX_Parameter_SetD3d12Resource(pInParams, NVSDK_NGX_Parameter_MotionVectorsReflection, pInDlssEvalParams->pInMotionVectorsReflections);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_DLSS_Input_Color_Subrect_Base_X, pInDlssEvalParams->InColorSubrectBase.X);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_DLSS_Input_Color_Subrect_Base_Y, pInDlssEvalParams->InColorSubrectBase.Y);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_DLSS_Input_Depth_Subrect_Base_X, pInDlssEvalParams->InDepthSubrectBase.X);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_DLSS_Input_Depth_Subrect_Base_Y, pInDlssEvalParams->InDepthSubrectBase.Y);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_DLSS_Input_MV_SubrectBase_X, pInDlssEvalParams->InMVSubrectBase.X);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_DLSS_Input_MV_SubrectBase_Y, pInDlssEvalParams->InMVSubrectBase.Y);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_DLSS_Input_Translucency_SubrectBase_X, pInDlssEvalParams->InTranslucencySubrectBase.X);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_DLSS_Input_Translucency_SubrectBase_Y, pInDlssEvalParams->InTranslucencySubrectBase.Y);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_DLSS_Input_Bias_Current_Color_SubrectBase_X, pInDlssEvalParams->InBiasCurrentColorSubrectBase.X);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_DLSS_Input_Bias_Current_Color_SubrectBase_Y, pInDlssEvalParams->InBiasCurrentColorSubrectBase.Y);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_DLSS_Output_Subrect_Base_X, pInDlssEvalParams->InOutputSubrectBase.X);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_DLSS_Output_Subrect_Base_Y, pInDlssEvalParams->InOutputSubrectBase.Y);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_DLSS_Render_Subrect_Dimensions_Width , pInDlssEvalParams->InRenderSubrectDimensions.Width);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_DLSS_Render_Subrect_Dimensions_Height, pInDlssEvalParams->InRenderSubrectDimensions.Height);
    NVSDK_NGX_Parameter_SetF(pInParams, NGSDK_NGX_Parameter_DLSS_Pre_Exposure, pInDlssEvalParams->InPreExposure == 0.0f ? 1.0f : pInDlssEvalParams->InPreExposure);
    NVSDK_NGX_Parameter_SetI(pInParams, NVSDK_NGX_Parameter_DLSS_Indicator_Invert_X_Axis, pInDlssEvalParams->InIndicatorInvertXAxis);
    NVSDK_NGX_Parameter_SetI(pInParams, NVSDK_NGX_Parameter_DLSS_Indicator_Invert_Y_Axis, pInDlssEvalParams->InIndicatorInvertYAxis);

    return NVSDK_NGX_D3D12_EvaluateFeature_C(pInCmdList, pInHandle, pInParams, NULL);
}


static inline NVSDK_NGX_Result NGX_D3D12_CREATE_DLISP_EXT(
    ID3D12GraphicsCommandList *InCmdList,
    unsigned int InCreationNodeMask,
    unsigned int InVisibilityNodeMask,
    NVSDK_NGX_Handle **ppOutHandle,
    NVSDK_NGX_Parameter *pInParams,
    NVSDK_NGX_Feature_Create_Params *pDlispCreateParams)
{
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_CreationNodeMask, InCreationNodeMask);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_VisibilityNodeMask, InVisibilityNodeMask);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_Width, pDlispCreateParams->InWidth);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_Height, pDlispCreateParams->InHeight);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_OutWidth, pDlispCreateParams->InTargetWidth);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_OutHeight, pDlispCreateParams->InTargetHeight);
    NVSDK_NGX_Parameter_SetI(pInParams, NVSDK_NGX_Parameter_PerfQualityValue, pDlispCreateParams->InPerfQualityValue);

    return NVSDK_NGX_D3D12_CreateFeature(InCmdList, NVSDK_NGX_Feature_ImageSignalProcessing, pInParams, ppOutHandle);
}

static inline NVSDK_NGX_Result NGX_D3D12_EVALUATE_DLISP_EXT(
    ID3D12GraphicsCommandList *pInCmdList,
    NVSDK_NGX_Handle *pInHandle,
    NVSDK_NGX_Parameter *pInParams,
    NVSDK_NGX_D3D12_DLISP_Eval_Params *pDlispEvalParams)
{
    if (pDlispEvalParams->Feature.InSharpness < 0.0f || pDlispEvalParams->Feature.InSharpness > 1.0f || pDlispEvalParams->InDenoise < 0.0f || pDlispEvalParams->InDenoise > 1.0f)
    {
        return NVSDK_NGX_Result_FAIL_InvalidParameter;
    }
    NVSDK_NGX_Parameter_SetD3d12Resource(pInParams, NVSDK_NGX_Parameter_Color, pDlispEvalParams->Feature.pInColor);
    NVSDK_NGX_Parameter_SetD3d12Resource(pInParams, NVSDK_NGX_Parameter_Output, pDlispEvalParams->Feature.pInOutput);
    // Both sharpness and denoise in range [0.0f,1.0f]
    NVSDK_NGX_Parameter_SetF(pInParams, NVSDK_NGX_Parameter_Sharpness, pDlispEvalParams->Feature.InSharpness);
    NVSDK_NGX_Parameter_SetF(pInParams, NVSDK_NGX_Parameter_Denoise, pDlispEvalParams->InDenoise);
    // If input is atlas - use RECT to upscale only the required area
    if (pDlispEvalParams->InRectW)
    {
        NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_Rect_X, pDlispEvalParams->InRectX);
        NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_Rect_Y, pDlispEvalParams->InRectY);
        NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_Rect_W, pDlispEvalParams->InRectW);
        NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_Rect_H, pDlispEvalParams->InRectH);
    }
    return NVSDK_NGX_D3D12_EvaluateFeature_C(pInCmdList, pInHandle, pInParams, NULL);
}


static inline NVSDK_NGX_Result NGX_D3D12_CREATE_DLRESOLVE_EXT(
    ID3D12GraphicsCommandList *pInCmdList,
    unsigned int InCreationNodeMask,
    unsigned int InVisibilityNodeMask,
    NVSDK_NGX_Handle **ppOutHandle,
    NVSDK_NGX_Parameter *pInParams,
    NVSDK_NGX_Feature_Create_Params *pDlresolveCreateParams)
{
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_CreationNodeMask, InCreationNodeMask);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_VisibilityNodeMask, InVisibilityNodeMask);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_Width, pDlresolveCreateParams->InWidth);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_Height, pDlresolveCreateParams->InHeight);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_OutWidth, pDlresolveCreateParams->InTargetWidth);
    NVSDK_NGX_Parameter_SetUI(pInParams, NVSDK_NGX_Parameter_OutHeight, pDlresolveCreateParams->InTargetHeight);

    return NVSDK_NGX_D3D12_CreateFeature(pInCmdList, NVSDK_NGX_Feature_DeepResolve, pInParams, ppOutHandle);
}

static inline NVSDK_NGX_Result NGX_D3D12_EVALUATE_DLRESOLVE_EXT(
    ID3D12GraphicsCommandList *pInCmdList,
    NVSDK_NGX_Handle *pInHandle,
    NVSDK_NGX_Parameter *pInParams,
    NVSDK_NGX_D3D12_Feature_Eval_Params *pDlresolveEvalParams)
{
    // This call to NVSDK_NGX_Parameter_SetXXX() is equivalent to the Params->Set below functionally
    // but to work around the lack of virtual functions and polymorphism in a C only project
    // we introduced this new way to set params.
    // The test should enforce that both paths work.
    NVSDK_NGX_Parameter_SetD3d12Resource(pInParams, NVSDK_NGX_Parameter_Color, pDlresolveEvalParams->pInColor);
    NVSDK_NGX_Parameter_SetD3d12Resource(pInParams, NVSDK_NGX_Parameter_Output, pDlresolveEvalParams->pInOutput);
    NVSDK_NGX_Parameter_SetF(pInParams, NVSDK_NGX_Parameter_Sharpness, pDlresolveEvalParams->InSharpness);

    return NVSDK_NGX_D3D12_EvaluateFeature_C(pInCmdList, pInHandle, pInParams, NULL);
}


// Following legacy helpers presently in use will be deprecated in the near future in favor of the ones defined above using parameter structures.
// Hence, the use of parameter-structure-based helpers defined above is highly encouraged.

/******************* DEPRECATED *********************/

static inline NVSDK_NGX_Result NGX_D3D11_CREATE_DLSS(
    NVSDK_NGX_Handle **OutHandle,
    NVSDK_NGX_Parameter *InParams,
    ID3D11DeviceContext *InCtx,
    unsigned int InWidth,
    unsigned int InHeight,
    unsigned int InTargetWidth,
    unsigned int InTargetHeight,
    NVSDK_NGX_PerfQuality_Value InPerfQualityValue,
    int          InFeatureCreateFlags)
{
    NVSDK_NGX_Parameter_SetUI(InParams, NVSDK_NGX_Parameter_Width, InWidth);
    NVSDK_NGX_Parameter_SetUI(InParams, NVSDK_NGX_Parameter_Height, InHeight);
    // Should be the same as Width/Height unless engine supports upscaled AA (e.g. TAAU)
    NVSDK_NGX_Parameter_SetUI(InParams, NVSDK_NGX_Parameter_OutWidth, InTargetWidth);
    NVSDK_NGX_Parameter_SetUI(InParams, NVSDK_NGX_Parameter_OutHeight, InTargetHeight);
    NVSDK_NGX_Parameter_SetI(InParams, NVSDK_NGX_Parameter_PerfQualityValue, InPerfQualityValue);
    NVSDK_NGX_Parameter_SetI(InParams, NVSDK_NGX_Parameter_DLSS_Feature_Create_Flags, InFeatureCreateFlags);
    return NVSDK_NGX_D3D11_CreateFeature(InCtx, NVSDK_NGX_Feature_SuperSampling, InParams, OutHandle);
}

static inline NVSDK_NGX_Result NGX_D3D11_EVALUATE_DLSS(
    NVSDK_NGX_Handle *InHandle,
    NVSDK_NGX_Parameter *InParams,
    ID3D11DeviceContext *InCtx,
    ID3D11Resource *InColor,
    ID3D11Resource *InMotionVectors,
    ID3D11Resource *InOutput,
    ID3D11Resource *InDepth,
    ID3D11Resource *InTransparencyMask, // per pixel mask identifying alpha-blended objects like particles etc.
    ID3D11Resource *InExposureTexture,
    int Reset,
    float InSharpness,
    float InMVScaleX,
    float InMVScaleY,
    float InJitterOffsetX,
    float InJitterOffsetY)
{
    NVSDK_NGX_Parameter_SetD3d11Resource(InParams, NVSDK_NGX_Parameter_Color, InColor);
    NVSDK_NGX_Parameter_SetD3d11Resource(InParams, NVSDK_NGX_Parameter_MotionVectors, InMotionVectors);
    NVSDK_NGX_Parameter_SetD3d11Resource(InParams, NVSDK_NGX_Parameter_Output, InOutput);
    NVSDK_NGX_Parameter_SetD3d11Resource(InParams, NVSDK_NGX_Parameter_ExposureTexture, InExposureTexture);
    // Set to 1 when scene changes completely (new level etc)
    NVSDK_NGX_Parameter_SetI(InParams, NVSDK_NGX_Parameter_Reset, Reset);
    // If MVs need custom scaling to convert to pixel space
    NVSDK_NGX_Parameter_SetF(InParams, NVSDK_NGX_Parameter_MV_Scale_X, InMVScaleX);
    NVSDK_NGX_Parameter_SetF(InParams, NVSDK_NGX_Parameter_MV_Scale_Y, InMVScaleY);
    // Jitter offset must be in pixel space
    NVSDK_NGX_Parameter_SetF(InParams, NVSDK_NGX_Parameter_Jitter_Offset_X, InJitterOffsetX);
    NVSDK_NGX_Parameter_SetF(InParams, NVSDK_NGX_Parameter_Jitter_Offset_Y, InJitterOffsetY);
    NVSDK_NGX_Parameter_SetF(InParams, NVSDK_NGX_Parameter_Sharpness, InSharpness);
    NVSDK_NGX_Parameter_SetD3d11Resource(InParams, NVSDK_NGX_Parameter_Depth, InDepth);
    NVSDK_NGX_Parameter_SetD3d11Resource(InParams, NVSDK_NGX_Parameter_TransparencyMask, InTransparencyMask);
    return NVSDK_NGX_D3D11_EvaluateFeature_C(InCtx, InHandle, InParams, NULL);
}


static inline NVSDK_NGX_Result NGX_D3D11_CREATE_DLISP(
    NVSDK_NGX_Handle **OutHandle,
    NVSDK_NGX_Parameter *InParams,
    ID3D11DeviceContext *InCtx,
    unsigned int InWidth,
    unsigned int InHeight,
    unsigned int InTargetWidth,
    unsigned int InTargetHeight)
{
    NVSDK_NGX_Parameter_SetUI(InParams, NVSDK_NGX_Parameter_Width, InWidth);
    NVSDK_NGX_Parameter_SetUI(InParams, NVSDK_NGX_Parameter_Height, InHeight);
    NVSDK_NGX_Parameter_SetUI(InParams, NVSDK_NGX_Parameter_OutWidth, InTargetWidth);
    NVSDK_NGX_Parameter_SetUI(InParams, NVSDK_NGX_Parameter_OutHeight, InTargetHeight);
    return NVSDK_NGX_D3D11_CreateFeature(InCtx, NVSDK_NGX_Feature_ImageSignalProcessing, InParams, OutHandle);
}

static inline NVSDK_NGX_Result NGX_CUDA_CREATE_DLISP(
    NVSDK_NGX_Handle **OutHandle,
    NVSDK_NGX_Parameter *InParams,
    unsigned int InWidth,
    unsigned int InHeight,
    unsigned int InTargetWidth,
    unsigned int InTargetHeight)
{
    NVSDK_NGX_Parameter_SetUI(InParams, NVSDK_NGX_Parameter_Width, InWidth);
    NVSDK_NGX_Parameter_SetUI(InParams, NVSDK_NGX_Parameter_Height, InHeight);
    NVSDK_NGX_Parameter_SetUI(InParams, NVSDK_NGX_Parameter_OutWidth, InTargetWidth);
    NVSDK_NGX_Parameter_SetUI(InParams, NVSDK_NGX_Parameter_OutHeight, InTargetHeight);
    return NVSDK_NGX_CUDA_CreateFeature(NVSDK_NGX_Feature_ImageSignalProcessing, InParams, OutHandle);
}

static inline NVSDK_NGX_Result NGX_D3D11_EVALUATE_DLISP(
    NVSDK_NGX_Handle *InHandle,
    NVSDK_NGX_Parameter *InParams,
    ID3D11DeviceContext *InCtx,
    ID3D11Resource *InColor,
    ID3D11Resource *InOutput,
    float InSharpness,
    float InDenoise,
    unsigned int InRectX,
    unsigned int InRectY,
    unsigned int InRectW,
    unsigned int InRectH)
{
    if (InSharpness < 0.0f || InSharpness > 1.0f || InDenoise < 0.0f || InDenoise > 1.0f)
    {
        return NVSDK_NGX_Result_FAIL_InvalidParameter;
    }
    NVSDK_NGX_Parameter_SetD3d11Resource(InParams, NVSDK_NGX_Parameter_Color, InColor);
    NVSDK_NGX_Parameter_SetD3d11Resource(InParams, NVSDK_NGX_Parameter_Output, InOutput);
    // Both sharpness and denoise in range [0.0f,1.0f]
    NVSDK_NGX_Parameter_SetF(InParams, NVSDK_NGX_Parameter_Sharpness, InSharpness);
    NVSDK_NGX_Parameter_SetF(InParams, NVSDK_NGX_Parameter_Denoise, InDenoise);
    // If input is atlas - use RECT to upscale only the required area
    if (InRectW)
    {
        NVSDK_NGX_Parameter_SetUI(InParams, NVSDK_NGX_Parameter_Rect_X, InRectX);
        NVSDK_NGX_Parameter_SetUI(InParams, NVSDK_NGX_Parameter_Rect_Y, InRectY);
        NVSDK_NGX_Parameter_SetUI(InParams, NVSDK_NGX_Parameter_Rect_W, InRectW);
        NVSDK_NGX_Parameter_SetUI(InParams, NVSDK_NGX_Parameter_Rect_H, InRectH);
    }
    return NVSDK_NGX_D3D11_EvaluateFeature_C(InCtx, InHandle, InParams, NULL);
}


static inline NVSDK_NGX_Result NGX_D3D11_CREATE_DLRESOLVE(
    NVSDK_NGX_Handle **OutHandle,
    NVSDK_NGX_Parameter *InParams,
    ID3D11DeviceContext *InCtx,
    unsigned int InWidth,
    unsigned int InHeight,
    unsigned int InTargetWidth,
    unsigned int InTargetHeight)
{
    NVSDK_NGX_Parameter_SetUI(InParams, NVSDK_NGX_Parameter_Width, InWidth);
    NVSDK_NGX_Parameter_SetUI(InParams, NVSDK_NGX_Parameter_Height, InHeight);
    NVSDK_NGX_Parameter_SetUI(InParams, NVSDK_NGX_Parameter_OutWidth, InTargetWidth);
    NVSDK_NGX_Parameter_SetUI(InParams, NVSDK_NGX_Parameter_OutHeight, InTargetHeight);

    return NVSDK_NGX_D3D11_CreateFeature(InCtx, NVSDK_NGX_Feature_DeepResolve, InParams, OutHandle);
}

static inline NVSDK_NGX_Result NGX_D3D11_EVALUATE_DLRESOLVE(
    NVSDK_NGX_Handle *InHandle,
    NVSDK_NGX_Parameter *InParams,
    ID3D11DeviceContext *InCtx,
    ID3D11Resource *InColor,
    ID3D11Resource *InOutput,
    float InSharpness)
{
    NVSDK_NGX_Parameter_SetD3d11Resource(InParams, NVSDK_NGX_Parameter_Color, InColor);
    NVSDK_NGX_Parameter_SetD3d11Resource(InParams, NVSDK_NGX_Parameter_Output, InOutput);
    NVSDK_NGX_Parameter_SetF(InParams, NVSDK_NGX_Parameter_Sharpness, InSharpness);

    return NVSDK_NGX_D3D11_EvaluateFeature_C(InCtx, InHandle, InParams, NULL);
}


static inline NVSDK_NGX_Result NGX_D3D12_CREATE_DLSS(
    NVSDK_NGX_Handle **OutHandle,
    NVSDK_NGX_Parameter *InParams,
    ID3D12GraphicsCommandList *InCmdList,
    unsigned int InWidth,
    unsigned int InHeight,
    unsigned int InTargetWidth,
    unsigned int InTargetHeight,
    NVSDK_NGX_PerfQuality_Value InPerfQualityValue,
    int          InFeatureCreateFlags,
    unsigned int InCreationNodeMask,
    unsigned int InVisibilityNodeMask)
{
    NVSDK_NGX_Parameter_SetUI(InParams, NVSDK_NGX_Parameter_CreationNodeMask, InCreationNodeMask);
    NVSDK_NGX_Parameter_SetUI(InParams, NVSDK_NGX_Parameter_VisibilityNodeMask, InVisibilityNodeMask);
    NVSDK_NGX_Parameter_SetUI(InParams, NVSDK_NGX_Parameter_Width, InWidth);
    NVSDK_NGX_Parameter_SetUI(InParams, NVSDK_NGX_Parameter_Height, InHeight);
    // Should be the same as Width/Height unless engine supports upscaled AA (e.g. TAAU)
    NVSDK_NGX_Parameter_SetUI(InParams, NVSDK_NGX_Parameter_OutWidth, InTargetWidth);
    NVSDK_NGX_Parameter_SetUI(InParams, NVSDK_NGX_Parameter_OutHeight, InTargetHeight);
    NVSDK_NGX_Parameter_SetI(InParams, NVSDK_NGX_Parameter_PerfQualityValue, InPerfQualityValue);
    NVSDK_NGX_Parameter_SetI(InParams, NVSDK_NGX_Parameter_DLSS_Feature_Create_Flags, InFeatureCreateFlags);
    return NVSDK_NGX_D3D12_CreateFeature(InCmdList, NVSDK_NGX_Feature_SuperSampling, InParams, OutHandle);
}

static inline NVSDK_NGX_Result NGX_D3D12_EVALUATE_DLSS(
    NVSDK_NGX_Handle *InHandle,
    NVSDK_NGX_Parameter *InParams,
    ID3D12GraphicsCommandList *InCmdList,
    ID3D12Resource *InColor,
    ID3D12Resource *InMotionVectors,
    ID3D12Resource *InOutput,
    ID3D12Resource *InDepth,
    ID3D12Resource *InTransparencyMask, // per pixel mask identifying alpha-blended objects like particles etc.
    ID3D12Resource *InExposureTexture,
    int Reset,
    float InSharpness,
    float InMVScaleX,
    float InMVScaleY,
    float InJitterOffsetX,
    float InJitterOffsetY)
{
    NVSDK_NGX_Parameter_SetD3d12Resource(InParams, NVSDK_NGX_Parameter_Color, InColor);
    NVSDK_NGX_Parameter_SetD3d12Resource(InParams, NVSDK_NGX_Parameter_MotionVectors, InMotionVectors);
    NVSDK_NGX_Parameter_SetD3d12Resource(InParams, NVSDK_NGX_Parameter_Output, InOutput);
    NVSDK_NGX_Parameter_SetD3d12Resource(InParams, NVSDK_NGX_Parameter_TransparencyMask, InTransparencyMask);
    NVSDK_NGX_Parameter_SetD3d12Resource(InParams, NVSDK_NGX_Parameter_ExposureTexture, InExposureTexture);
    // Set to 1 when scene changes completely (new level etc)
    NVSDK_NGX_Parameter_SetI(InParams, NVSDK_NGX_Parameter_Reset, Reset);
    // If MVs need custom scaling to convert to pixel space
    NVSDK_NGX_Parameter_SetF(InParams, NVSDK_NGX_Parameter_MV_Scale_X, InMVScaleX);
    NVSDK_NGX_Parameter_SetF(InParams, NVSDK_NGX_Parameter_MV_Scale_Y, InMVScaleY);
    // Jitter offset must be in pixel space
    NVSDK_NGX_Parameter_SetF(InParams, NVSDK_NGX_Parameter_Jitter_Offset_X, InJitterOffsetX);
    NVSDK_NGX_Parameter_SetF(InParams, NVSDK_NGX_Parameter_Jitter_Offset_Y, InJitterOffsetY);
    NVSDK_NGX_Parameter_SetF(InParams, NVSDK_NGX_Parameter_Sharpness, InSharpness);
    NVSDK_NGX_Parameter_SetD3d12Resource(InParams, NVSDK_NGX_Parameter_Depth, InDepth);
    return NVSDK_NGX_D3D12_EvaluateFeature_C(InCmdList, InHandle, InParams, NULL);
}


static inline NVSDK_NGX_Result NGX_D3D12_CREATE_DLISP(
    NVSDK_NGX_Handle **OutHandle,
    NVSDK_NGX_Parameter *InParams,
    ID3D12GraphicsCommandList *InCmdList,
    unsigned int InWidth,
    unsigned int InHeight,
    unsigned int InTargetWidth,
    unsigned int InTargetHeight,
    unsigned int InCreationNodeMask,
    unsigned int InVisibilityNodeMask)
{
    NVSDK_NGX_Parameter_SetUI(InParams, NVSDK_NGX_Parameter_CreationNodeMask, InCreationNodeMask);
    NVSDK_NGX_Parameter_SetUI(InParams, NVSDK_NGX_Parameter_VisibilityNodeMask, InVisibilityNodeMask);
    NVSDK_NGX_Parameter_SetUI(InParams, NVSDK_NGX_Parameter_Width, InWidth);
    NVSDK_NGX_Parameter_SetUI(InParams, NVSDK_NGX_Parameter_Height, InHeight);
    NVSDK_NGX_Parameter_SetUI(InParams, NVSDK_NGX_Parameter_OutWidth, InTargetWidth);
    NVSDK_NGX_Parameter_SetUI(InParams, NVSDK_NGX_Parameter_OutHeight, InTargetHeight);
    return NVSDK_NGX_D3D12_CreateFeature(InCmdList, NVSDK_NGX_Feature_ImageSignalProcessing, InParams, OutHandle);
}

static inline NVSDK_NGX_Result NGX_D3D12_EVALUATE_DLISP(
    NVSDK_NGX_Handle *InHandle,
    NVSDK_NGX_Parameter *InParams,
    ID3D12GraphicsCommandList *InCmdList,
    ID3D12Resource *InColor,
    ID3D12Resource *InOutput,
    float InSharpness,
    float InDenoise,
    unsigned int InRectX,
    unsigned int InRectY,
    unsigned int InRectW,
    unsigned int InRectH)
{
    if (InSharpness < 0.0f || InSharpness > 1.0f || InDenoise < 0.0f || InDenoise > 1.0f)
    {
        return NVSDK_NGX_Result_FAIL_InvalidParameter;
    }
    NVSDK_NGX_Parameter_SetD3d12Resource(InParams, NVSDK_NGX_Parameter_Color, InColor);
    NVSDK_NGX_Parameter_SetD3d12Resource(InParams, NVSDK_NGX_Parameter_Output, InOutput);
    // Both sharpness and denoise in range [0.0f,1.0f]
    NVSDK_NGX_Parameter_SetF(InParams, NVSDK_NGX_Parameter_Sharpness, InSharpness);
    NVSDK_NGX_Parameter_SetF(InParams, NVSDK_NGX_Parameter_Denoise, InDenoise);
    // If input is atlas - use RECT to upscale only the required area
    if (InRectW)
    {
        NVSDK_NGX_Parameter_SetUI(InParams, NVSDK_NGX_Parameter_Rect_X, InRectX);
        NVSDK_NGX_Parameter_SetUI(InParams, NVSDK_NGX_Parameter_Rect_Y, InRectY);
        NVSDK_NGX_Parameter_SetUI(InParams, NVSDK_NGX_Parameter_Rect_W, InRectW);
        NVSDK_NGX_Parameter_SetUI(InParams, NVSDK_NGX_Parameter_Rect_H, InRectH);
    }
    return NVSDK_NGX_D3D12_EvaluateFeature_C(InCmdList, InHandle, InParams, NULL);
}

static inline NVSDK_NGX_Result NGX_CUDA_EVALUATE_DLISP(
    NVSDK_NGX_Handle* InHandle,
    NVSDK_NGX_Parameter* InParams,
    void* InColor,
    void* InOutput,
    float InSharpness,
    float InDenoise,
    unsigned int InRectX,
    unsigned int InRectY,
    unsigned int InRectW,
    unsigned int InRectH)
{
    if (InSharpness < 0.0f || InSharpness > 1.0f || InDenoise < 0.0f || InDenoise > 1.0f)
    {
        return NVSDK_NGX_Result_FAIL_InvalidParameter;
    }
    NVSDK_NGX_Parameter_SetVoidPointer(InParams, NVSDK_NGX_Parameter_Color, InColor);
    NVSDK_NGX_Parameter_SetVoidPointer(InParams, NVSDK_NGX_Parameter_Output, InOutput);
    // Both sharpness and denoise in range [0.0f,1.0f]
    NVSDK_NGX_Parameter_SetF(InParams, NVSDK_NGX_Parameter_Sharpness, InSharpness);
    NVSDK_NGX_Parameter_SetF(InParams, NVSDK_NGX_Parameter_Denoise, InDenoise);
    // If input is atlas - use RECT to upscale only the required area
    if (InRectW)
    {
        NVSDK_NGX_Parameter_SetUI(InParams, NVSDK_NGX_Parameter_Rect_X, InRectX);
        NVSDK_NGX_Parameter_SetUI(InParams, NVSDK_NGX_Parameter_Rect_Y, InRectY);
        NVSDK_NGX_Parameter_SetUI(InParams, NVSDK_NGX_Parameter_Rect_W, InRectW);
        NVSDK_NGX_Parameter_SetUI(InParams, NVSDK_NGX_Parameter_Rect_H, InRectH);
    }
    return NVSDK_NGX_CUDA_EvaluateFeature_C(InHandle, InParams, NULL);
}

static inline NVSDK_NGX_Result NGX_D3D12_CREATE_DLRESOLVE(
    NVSDK_NGX_Handle **OutHandle,
    NVSDK_NGX_Parameter *InParams,
    ID3D12GraphicsCommandList *InCmdList,
    unsigned int InWidth,
    unsigned int InHeight,
    unsigned int InTargetWidth,
    unsigned int InTargetHeight,
    unsigned int InCreationNodeMask,
    unsigned int InVisibilityNodeMask)
{
    NVSDK_NGX_Parameter_SetUI(InParams, NVSDK_NGX_Parameter_CreationNodeMask, InCreationNodeMask);
    NVSDK_NGX_Parameter_SetUI(InParams, NVSDK_NGX_Parameter_VisibilityNodeMask, InVisibilityNodeMask);
    NVSDK_NGX_Parameter_SetUI(InParams, NVSDK_NGX_Parameter_Width, InWidth);
    NVSDK_NGX_Parameter_SetUI(InParams, NVSDK_NGX_Parameter_Height, InHeight);
    NVSDK_NGX_Parameter_SetUI(InParams, NVSDK_NGX_Parameter_OutWidth, InTargetWidth);
    NVSDK_NGX_Parameter_SetUI(InParams, NVSDK_NGX_Parameter_OutHeight, InTargetHeight);

    return NVSDK_NGX_D3D12_CreateFeature(InCmdList, NVSDK_NGX_Feature_DeepResolve, InParams, OutHandle);
}

static inline NVSDK_NGX_Result NGX_D3D12_EVALUATE_DLRESOLVE(
    NVSDK_NGX_Handle *InHandle,
    NVSDK_NGX_Parameter *InParams,
    ID3D12GraphicsCommandList *InCmdList,
    ID3D12Resource *InColor,
    ID3D12Resource *InOutput,
    float InSharpness)
{
    // This call to NVSDK_NGX_Parameter_SetXXX() is equivalent to the Params->Set below functionally
    // but to work around the lack of virtual functions and polymorphism in a C only project
    // we introduced this new way to set params.
    // The test should enforce that both paths work.
    NVSDK_NGX_Parameter_SetD3d12Resource(InParams, NVSDK_NGX_Parameter_Color, InColor);
    NVSDK_NGX_Parameter_SetD3d12Resource(InParams, NVSDK_NGX_Parameter_Output, InOutput);
    NVSDK_NGX_Parameter_SetF(InParams, NVSDK_NGX_Parameter_Sharpness, InSharpness);

    return NVSDK_NGX_D3D12_EvaluateFeature_C(InCmdList, InHandle, InParams, NULL);
}

#endif
