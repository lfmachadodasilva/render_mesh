/*
 * shadowmapinterface.h
 * Author:  Vitor Barata Ribeiro Blanco Barroso (vbarata@tecgraf.puc-rio.br)
 * Updated: Mar 2009
 */

#ifndef SM_SHADOW_MAP_INTERFACE_H
#define SM_SHADOW_MAP_INTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "defines.h"

/********************/
/* Shadow Map Types */
/********************/

#define SHADOWMAP_NOWARP              0 /* No Warp                                                  */
#define SHADOWMAP_FIT_WORLD_ALIGNED   1 /* Fit the map to  a bounding volume, but keep it aligned   */
#define SHADOWMAP_FIT_VIEW_ALIGNED    2 /* Fit the map to the viewing volume, allowing rotation     */
#define SHADOWMAP_FIT_WORLD_ORIENTED  3 /* Fit the map to  a bounding volume, but keep it aligned   */
#define SHADOWMAP_FIT_VIEW_ORIENTED   4 /* Fit the map to the viewing volume, allowing rotation     */
#define SHADOWMAP_WARP_INF            5 /* Apply TSM warp with n' = infinity                        */
#define SHADOWMAP_WARP_TSM            6 /* Apply TSM warp with n' = n'[TSM]                         */
#define SHADOWMAP_WARP_PSM            7 /* Apply TSM warp with n' = n'[PSM]      = n                */
#define SHADOWMAP_WARP_LISPSM         8 /* Apply TSM warp with n' = n'[LISPSM]   = n + sqrt(n*f)    */
#define SHADOWMAP_WARP_GLISPSM        9 /* Apply TSM warp with n' = n'[GLISMSPM]                    */

/*******************/
/* Other constants */
/*******************/

#define SHADOWMAP_TRUE  1    /* Boolean value True  */
#define SHADOWMAP_FALSE 0    /* Boolean value False */
#define SHADOWMAP_OK    1    /* Returned by smInit() if initialization succeeds */
#define SHADOWMAP_FAIL  0    /* Returned by smInit() if initialization fails    */

/********************/
/* Type Definitions */
/********************/

typedef int smMap;
typedef int smMapper;

/***************************/
/* Mapper and Map Creation */
/***************************/

SM_API smMapper smCreateShadowMapper ();
SM_API smMap    smCreateShadowMap    ();

SM_API bool smInitShadowMapper (smMapper mapperHandle);
SM_API bool smInitShadowMap    (smMap mapHandle, unsigned int mapWidth, unsigned int mapHeight);

/*****************************************************/
/* Mapper and Map Destruction, and Complete Clean Up */
/*****************************************************/

SM_API void     smCleanShadowMapper   (smMapper mapperHandle); /* Call before destroying */
SM_API void     smCleanShadowMap      (smMap mapHandle);       /* Call before destroying */
SM_API void     smDestroyShadowMapper (smMapper mapperHandle);
SM_API void     smDestroyShadowMap    (smMap mapHandle);
SM_API void     smCleanUp             (void);                  /* Call when terminating a program */

/************************/
/* Mapper configuration */
/************************/

/* Parameters */

SM_API void smSetColorTexture (smMapper mapperHandle, int state);
SM_API void smSetCombiner     (smMapper mapperHandle, int state);
SM_API void smSetFakeShadows  (smMapper mapperHandle, int state);
SM_API void smSetFake4Mode    (smMapper mapperHandle, int state);
SM_API bool smSetWindowSize   (smMapper mapperHandle, unsigned int width, unsigned int height);
SM_API void smSetCamera       (smMapper mapperHandle, const float* viewTransform, const float* projTransform, float znear = 0.0f, float zfar = 0.0f, float fovy = 0.0f, float aspect = 0.0f);
SM_API void smSetWorldBBox    (smMapper mapperHandle, unsigned int vertexCount, float* vertices);

SM_API void smSetTextureUnitColor  (smMapper mapperHandle, unsigned int unit);
SM_API void smSetTextureUnitShadow (smMapper mapperHandle, unsigned int unit);
SM_API void smSetTextureUnitClip   (smMapper mapperHandle, unsigned int unit);
SM_API void smSetTextureUnitJitter (smMapper mapperHandle, unsigned int unit);

SM_API int  smGetFakeShadows  (smMapper mapperHandle);
SM_API int  smGetFake4Mode    (smMapper mapperHandle);

/* Dummy Textures */

SM_API void smLoadDummyTextures   (smMapper mapperHandle, unsigned int number);
SM_API void smUnloadDummyTextures (smMapper mapperHandle);

/* Visualization */

SM_API void smDrawTSMDebug     (smMapper mapperHandle, smMap mapHandle);
SM_API void smDrawWorldFrustum (smMapper mapperHandle);

/* For custom texture units to work, the user's OpenGL implementation must       */
/* support GLSL predefined-array indexing through uniform variables.             */

/* For units to work with the NOSHADER mode, "separate specular color" must      */
/* be turned OFF and the shadow texture unit must be 1 less than the clip unit.  */
/* Ideally, it works perfectly only for the default texture units.               */

/*********************/
/* Map Configuration */
/*********************/

/* Parameter Setters */

SM_API void smSetAllowShaders       (smMap mapHandle, int state);
SM_API void smSetClipTexture        (smMap mapHandle, int state);
SM_API void smSetLitBorders         (smMap mapHandle, int state);
SM_API void smSetCulling            (smMap mapHandle, int state);
SM_API void smSetCullFrontFace      (smMap mapHandle, int state);
SM_API void smSetPolyOffsetEnabled  (smMap mapHandle, int state);
SM_API void smSetPolyOffset         (smMap mapHandle, float factor, float units);
SM_API void smSetFragOffsetConst    (smMap mapHandle, float offset);
SM_API void smSetFragOffsetRange    (smMap mapHandle, float minBias, float maxBias);
SM_API void smSetGaussBlurSize      (smMap mapHandle, int size);
SM_API void smSetDualDepth          (smMap mapHandle, int state);
SM_API void smSetDualDepthClamp     (smMap mapHandle, int state);
SM_API void smSetPCF                (smMap mapHandle, int state);
SM_API void smSetPCFJitter          (smMap mapHandle, int state);
SM_API void smSetPCFCircular        (smMap mapHandle, int state);
SM_API void smSetPCFTexelSpace      (smMap mapHandle, int state);
SM_API void smSetPCFCamMultiSample  (smMap mapHandle, int state);
SM_API void smSetPCFCamAlignSample  (smMap mapHandle, int state);
SM_API void smSetPCFAdaptive        (smMap mapHandle, int state);
SM_API void smSetPCFKernelScale     (smMap mapHandle, float scale);
SM_API void smSetPCFKernelSize      (smMap mapHandle, int size);
SM_API void smSetPCFJitterSize      (smMap mapHandle, int size);
SM_API void smSetTSMFocusDistance   (smMap mapHandle, float value);
SM_API void smSetTSMFocusZDistance  (smMap mapHandle, float value);
SM_API void smSetTSMFocusPercentage (smMap mapHandle, float value);
SM_API void smSetPartitionZ         (smMap mapHandle, int state);
SM_API void smSetForceKeepZ         (smMap mapHandle, int state);
SM_API void smSetShadowMapWarp      (smMap mapHandle, int warp);
SM_API void smSetVarianceMap        (smMap mapHandle, int state);
SM_API void smSetVarianceBias       (smMap mapHandle, float value);
SM_API void smSetVarianceGround     (smMap mapHandle, float value);
SM_API void smSetFakeAttenuation    (smMap mapHandle, float value);
SM_API void smSetFakeShadowColor    (smMap mapHandle, float r, float g, float b);

/* Parameter Getters */

SM_API int   smGetWidth              (smMap mapHandle);
SM_API int   smGetHeight             (smMap mapHandle);
SM_API int   smGetAllowShaders       (smMap mapHandle);
SM_API int   smGetClipTexture        (smMap mapHandle);
SM_API int   smGetLitBorders         (smMap mapHandle);
SM_API int   smGetCulling            (smMap mapHandle);
SM_API int   smGetCullFrontFace      (smMap mapHandle);
SM_API int   smGetPolyOffsetEnabled  (smMap mapHandle);
SM_API void  smGetPolyOffset         (smMap mapHandle, float &factor, float &units);
SM_API float smGetFragOffsetConst    (smMap mapHandle);
SM_API void  smGetFragOffsetRange    (smMap mapHandle, float &minBias, float &maxBias);
SM_API int   smGetGaussBlurSize      (smMap mapHandle);
SM_API int   smGetDualDepth          (smMap mapHandle);
SM_API int   smGetDualDepthClamp     (smMap mapHandle);
SM_API int   smGetPCF                (smMap mapHandle);
SM_API int   smGetPCFJitter          (smMap mapHandle);
SM_API int   smGetPCFCircular        (smMap mapHandle);
SM_API int   smGetPCFTexKernel       (smMap mapHandle);
SM_API int   smGetPCFTexelSpace      (smMap mapHandle);
SM_API int   smGetPCFCamMultiSample  (smMap mapHandle);
SM_API int   smGetPCFCamAlignSample  (smMap mapHandle);
SM_API int   smGetPCFAdaptive        (smMap mapHandle);
SM_API float smGetPCFKernelScale     (smMap mapHandle);
SM_API int   smGetPCFKernelSize      (smMap mapHandle);
SM_API int   smGetPCFJitterSize      (smMap mapHandle);
SM_API float smGetTSMFocusDistance   (smMap mapHandle);
SM_API float smGetTSMFocusZDistance  (smMap mapHandle);
SM_API float smGetTSMFocusPercentage (smMap mapHandle);
SM_API int   smGetPartitionZ         (smMap mapHandle);
SM_API int   smGetForceKeepZ         (smMap mapHandle);
SM_API int   smGetShadowMapWarp      (smMap mapHandle);
SM_API int   smGetUseSimpleFit       (smMap mapHandle);
SM_API int   smGetUseTSMTransform    (smMap mapHandle);
SM_API int   smGetViewDependant      (smMap mapHandle);
SM_API int   smGetVarianceMap        (smMap mapHandle);
SM_API float smGetVarianceBias       (smMap mapHandle);
SM_API float smGetVarianceGround     (smMap mapHandle);
SM_API float smGetFakeAttenuation    (smMap mapHandle);
SM_API void  smGetFakeShadowColor    (smMap mapHandle, float &r, float &g, float &b);

/* Light Setters */

SM_API void smSetLightLookAt        (smMap mapHandle, float eyeX, float eyeY, float eyeZ, float targetX, float targetY, float targetZ, float upX, float upY, float upZ);
SM_API void smSetLightLookTo        (smMap mapHandle, float eyeX, float eyeY, float eyeZ, float viewX,   float viewY,   float viewZ,   float upX, float upY, float upZ);

SM_API void smSetLightPerspective   (smMap mapHandle, float fovy, float aspect, float znear,  float zfar);
SM_API void smSetLightPFrustum      (smMap mapHandle, float left, float right,  float bottom, float top, float znear, float zfar);

SM_API void smSetLightOrtho         (smMap mapHandle, float width, float height, float znear,  float zfar);
SM_API void smSetLightOFrustum      (smMap mapHandle, float left,  float right,  float bottom, float top, float znear, float zfar);

SM_API void smSetLightViewTransform (smMap mapHandle, float* matrix, bool isAffine = false);
SM_API void smSetLightProjTransform (smMap mapHandle, float* matrix, bool isAffine = false);

/* Light Getters */

SM_API void smGetLightViewTransform (smMap mapHandle, float* matrix);
SM_API void smGetLightProjTransform (smMap mapHandle, float* matrix);
SM_API void smGetLightWarpTransform (smMap mapHandle, float* matrix);
SM_API void smGetLightViewInverse   (smMap mapHandle, float* matrix);
SM_API void smGetLightProjInverse   (smMap mapHandle, float* matrix);
SM_API void smGetLightPosition      (smMap mapHandle, float* vec3d);

/* Camera Moved Flag */

SM_API void smSetCameraMovedFlag (smMap mapHandle);

/* Visualization */

SM_API void smDrawShadowMapTexture (smMap mapHandle, smMapper mapperHandle, float left = -1.0f, float bottom = -1.0f, float right = 1.0f, float top = 1.0f, int option = 0);
SM_API void smDrawLightFrustum     (smMap mapHandle);

/*******************/
/* Combiner Passes */
/*******************/

SM_API void smBeginCombinerColorPass   (smMapper mapperHandle, bool isOpaquePass = true, float alphaTest = 1.0f);
SM_API void smEndCombinerColorPass     (void);

SM_API void smBeginCombinerAmbientPass (smMapper mapperHandle, bool isOpaquePass = true, float alphaTest = 1.0f);
SM_API void smEndCombinerAmbientPass   (void);

SM_API void smBeginCombinerLightPasses (smMapper mapperHandle, bool isOpaquePass = true, bool useBlend = true, float alphaTest = 1.0f);
SM_API void smEndCombinerLightPasses   (void);

SM_API void smDoCombinerFinalPass      (smMapper mapperHandle, bool isOpaquePass = true, float alphaTest = 1.0f);

/**************/
/* Map Update */
/**************/

SM_API void smBeginMapsUpdate       (smMapper mapperHandle);

SM_API void smBeginUpdate           (smMap mapHandle);
SM_API void smEndUpdate             (void);

SM_API void smBeginDualUpdateFirst  (smMap mapHandle);
SM_API void smEndDualUpdateFirst    (void);

SM_API void smBeginDualUpdateSecond (smMap mapHandle);
SM_API void smEndDualUpdateSecond   (void);

SM_API void smSwitchPartitionUpdatePass (void);

SM_API void smEndMapsUpdate         (void);

/**************/
/* Map Render */
/**************/

SM_API void smBeginUnshadowedPass (smMapper mapperHandle, bool isOpaquePass = true, float alphaTest = 1.0f);
SM_API void smEndUnshadowedPass   (void);

SM_API void smBeginMapsRender (smMapper mapperHandle, bool isOpaquePass = true, bool useBlend = true, float alphaTest = 1.0f);
SM_API void smBeginRender     (smMap mapHandle);
SM_API void smEndRender       (void);
SM_API void smEndMapsRender   (void);

SM_API void smBeginFake4MapsRender (smMapper mapperHandle, float alphaTest = 1.0f);
SM_API void smBeginFake4Render     (smMap mapHandle, unsigned int texunit);          // In this case, 4 consecutive Begin()'s should be called,
SM_API void smEndFake4Render       (void);                                           // and after rendering, 4 consecutive End()'s.
SM_API void smEndFake4MapsRender   (void);

/* Important note: when smBeginRender or smBeginCombiner*Pass is called, */
/* the currently loaded OpenGL ModelView matrix must correspond to the   */
/* viewing matrix of the camera (as produced by gluLookAt())!            */

#ifdef __cplusplus
}
#endif

#endif /* SM_SHADOW_MAP_INTERFACE_H */

/*
TODO:

- Interpolate Shadow Map values in PCF instead of using tangent plane (may be expensive in texture accesses) (DO NOT DO)
- Midpoint/Dual-Depth Shadow Map (MAYBE DO)
- MORE TECHNIQUES!!!

*/
