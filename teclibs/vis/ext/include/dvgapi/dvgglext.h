/************************************/
/** Orad DVG GL Wrapper extensions **/
/**         Version 1.2.4          **/
/************************************/

#ifndef __dvgglext_h_
#define __dvgglext_h_

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_WIN32) && !defined(GLAPIENTRY) && !defined(__CYGWIN__)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif
#include <windows.h>
#endif

#ifdef _WIN32
  #ifndef GLAPIENTRY
    #define GLAPIENTRY __stdcall
  #endif

  /* Texture compression methods. */
  #define DVGGL_TEXCOMP_DXT1 1
  #define DVGGL_TEXCOMP_DXT3 3
  #define DVGGL_TEXCOMP_DXT5 5

  /* Windows status codes. */
  #define DVGGL_SUCCESS                                    0
  #define DVGGL_FAILED                                    -1
  #define DVGGL_UNSUPPORTED_CAPABILITY                  -500
  #define DVGGL_ERROR_PARAMETER_VALUE                   -499
  #define DVGGL_DRIVER_NOT_STARTED                      -498
  #define DVGGL_DRIVER_FAILURE                          -497
  #define DVGGL_DRIVER_CLOSE_FAILURE                    -496
  #define DVGGL_CREATE_OVERLAPED_EVENT_FAILURE          -495
  #define DVGGL_CREATE_SWAP_EVENT_FAILURE               -494
  #define DVGGL_SWAP_EVENT_NOT_SET                      -493
  #define DVGGL_CREATE_INTERRUPT_EVENT_FAILURE          -492
  #define DVGGL_INTERRUPT_EVENT_NOT_SET                 -491
  #define DVGGL_SWAP_COUNTER_NOT_SET                    -490
  #define DVGGL_CHANGES_NOTIFICATION_NOT_SET            -489
  #define DVGGL_DRIVER_IO_ERROR                         -488
  #define DVGGL_SWAP_TIMEOUT                            -487
  #define DVGGL_SWAP_FAILED                             -486
  #define DVGGL_CREATE_COMMUNICATION_FAILURE            -485
  #define DVGGL_API_NOT_OPEN                            -484
  #define DVGGL_DRIVER_FW_NOT_LOADED                    -483
  #define DVGGL_CREATE_SWAP_BARRIER_READY_EVENT_FAILURE -482
  #define DVGGL_CREATE_SWAP_BARRIER_WAIT_EVENT_FAILURE  -481
  #define DVGGL_MESSAGES_SERVICE_FAILURE                -480
#else
  #define GLAPIENTRY

  /* Infinite timeout. */
  #define INFINITE 0xFFFFFFFF

  /* Linux status codes. */
  #define DVGGL_SUCCESS   0
  #define DVGGL_FAILED   -1
#endif

/* Statistics catefories */
#define DVGGL_MAX_STATS_CATEGORIES    12

#define DVGGL_SC_RENDERING             0
#define DVGGL_SC_SWAP_BUFFERS          1
#define DVGGL_SC_GL_FINISH             2
#define DVGGL_SC_WAIT_FOR_SWAP         3
#define DVGGL_SC_WAIT_FOR_SWAP_BARRIER 4
#define DVGGL_SC_USER_FIRST            5
#define DVGGL_SC_USER_LAST DVGGL_MAX_STATS_CATEGORIES - 1

/* Debug categories */
#define DVGGL_DBG_CRITICAL 0
#define DVGGL_DBG_ERROR    1
#define DVGGL_DBG_WARNING  2
#define DVGGL_DBG_INFO     3
#define DVGGL_DBG_DEBUG    4
#define DVGGL_DBG_OFF      5

/* Wrapper configuration structure */
struct DvgGLWrapperConfig 
  {
  int theConfigVersion;
  int theConfigSize;

#ifdef _WIN32
  int theWaitOnSwapBuffers;
  
  int theDebugOutputCalls; 
  int theDebugMultisampling;
  int theReserved2;
#else
  int thePassThroughEnabled;
#endif

#ifdef _WIN32
  int theForceMultisampling;

  int theForceAnisotropicFiltering;
  int theAnisotropicFilteringLevel;
  
  int theForceRGBTextureCompression;
  int theRGBTextureCompression;
  
  int theForceRGBATextureCompression;
  int theRGBATextureCompression;

  int theMeasureRenderingTime;
  int theMeasureWaitForSwap;
  int theMeasureSwapBuffers;
  int theReportDrops;
  int theMeasureDetails;

  int theBusySwap;
  int theReserved1;

#ifdef SWAP_BARRIER
  int theSwapBarrier;
  int theSwapMargin;
  int theSwapLenght;
  int theSwapPos;

  int theReserved[40];
#else
  int theReserved[44];
#endif
#else
  int theReserved[61];
#endif
  };


#define DVG_GL_GET_SWAP_COUNTER_EXT "glGetSwapCounterDVG"
typedef int (GLAPIENTRY *glGetSwapCounterDVG)(unsigned int* aCurrent, unsigned int* aAbsolute);

#define DVG_GL_GET_FLOATV_EXT "glGetFloatvDVG"
typedef void (GLAPIENTRY *glGetFloatvDVG)(unsigned int aType, float* aParams);

#define DVG_GL_GET_DOUBLEV_EXT "glGetDoublevDVG"
typedef void (GLAPIENTRY *glGetDoublevDVG)(unsigned int aType, double* aParams);

#define DVG_GL_WAIT_FOR_SWAP_EXT "glWaitForSwapDVG"
typedef int (GLAPIENTRY *glWaitForSwapDVG)(unsigned int *aCount, const unsigned int aTimeOut);

#define DVG_GL_GET_WRAPPER_CONFIG_EXT "glGetWrapperConfigDVG"
typedef int (GLAPIENTRY *glGetWrapperConfigDVG)(struct DvgGLWrapperConfig *aConfig);

#define DVG_GL_SET_WRAPPER_CONFIG_EXT "glSetWrapperConfigDVG"
typedef int (GLAPIENTRY *glSetWrapperConfigDVG)(const struct DvgGLWrapperConfig *aConfig);

#define DVG_GL_GET_GFX_MULTISAMPLING_EXT "glGetGFXMultiSamplingDVG"
typedef int (GLAPIENTRY *glGetGFXMultiSamplingDVG)(unsigned int *aSamples);

#define DVG_GL_GET_VR_GRAPHICS_MODE_EXT "glGetVRGraphicsModeDVG"
typedef int (GLAPIENTRY *glGetVRGraphicsModeDVG)(float *aVrate, unsigned *aHActive,
                      unsigned *aHSyncStart, unsigned *aHSyncEnd, 
                      unsigned *aHTotal, unsigned *aVActive,
                      unsigned *aVSyncStart, unsigned *aVSyncEnd,
                      unsigned *aVTotal);

#define DVG_GL_GET_VIEWPORT_COUNT_EXT "glGetViewportCountDVG"
typedef int (GLAPIENTRY *glGetViewportCountDVG)(unsigned int *aColorViewports, unsigned int *aMaskViewports);

#define DVG_GL_GET_VIEWPORT_POS_AND_SIZE_EXT "glGetViewportPosAndSizeDVG"
typedef int (GLAPIENTRY *glGetViewportPosAndSizeDVG)
  (
  unsigned int aViewportId, 
  unsigned int *aPosX, 
  unsigned int *aPosY,
  unsigned int *aWidth, 
  unsigned int *aHeight
  );

#define DVG_GL_GET_BASE_VIEWPORT_SIZE_EXT "glGetBaseViewportSizeDVG"
typedef int (GLAPIENTRY *glGetBaseViewportSizeDVG)(unsigned int *aBaseWidth, unsigned int *aBaseHeight);

#define DVG_GL_GET_TDAA_EXT "glGetTDAADVG"
typedef int (GLAPIENTRY *glGetTDAADVG)(unsigned int *aSamples);

#define DVG_GL_GET_AA_CHAIN_EXT "glGetAAChainDVG"
typedef int (GLAPIENTRY *glGetAAChainDVG)(unsigned int *aAAPos, unsigned int *aAALen);  

#define DVG_GL_GET_TD_CHAIN_EXT "glGetTDChainDVG"
typedef int (GLAPIENTRY *glGetTDChainDVG)(unsigned int *aTDPos, unsigned int *aTDLen);

#define DVG_GL_GET_AID_CHAIN_EXT "glGetAIDChainDVG"
typedef int (GLAPIENTRY *glGetAIDChainDVG)(unsigned int *aAIDPos, unsigned int *aAIDLen);

// glGetUseAAToSSDDVG extension is obsolete. Please use glGetAIDChainDVG instead.
#define DVG_GL_GET_USE_AA_TO_SSD_EXT "glGetUseAAToSSDDVG"
typedef int (GLAPIENTRY *glGetUseAAToSSDDVG)(int *aUseAAToSSD);

#define DVG_GL_GET_SID_CHAIN_EXT "glGetSIDChainDVG"
typedef int (GLAPIENTRY *glGetSIDChainDVG)(unsigned int *aHPos, unsigned int *aVPos, unsigned int *aHLen, unsigned int *aVLen);

#define DVG_GL_GET_IID_CHAIN_EXT "glGetIIDChainDVG"
typedef int (GLAPIENTRY *glGetIIDChainDVG)(unsigned int *aIIDPos, unsigned int *aIIDLen);

#define DVG_GL_GET_SID_VIEWPORT_SIZE_EXT "glGetSIDViewportSizeDVG"
typedef int (GLAPIENTRY *glGetSIDViewportSizeDVG)(unsigned int *aTotalWidth, unsigned int *aTotalHeight,
                       unsigned int *aHOffset, unsigned int *aVOffset);

#define DVG_GL_GET_STEREO_STATUS_EXT "glGetStereoStatusDVG"
typedef int (GLAPIENTRY *glGetStereoStatusDVG)(int *aIsStereo, int *aIsActiveStereo, 
                    int *aIsLeftEye, int *aUseArrangeMatrices,
                    float *aEyeSeparation, float *aEyeFocalLen);

#define DVG_GL_IS_PROJECTION_SID_APPLIED_EXT "glIsProjectionSIDAppliedDVG"
typedef int (GLAPIENTRY *glIsProjectionSIDAppliedDVG)(void);

#define DVG_GL_IS_PROJECTION_IID_APPLIED_EXT "glIsProjectionIIDAppliedDVG"
typedef int (GLAPIENTRY *glIsProjectionIIDAppliedDVG)(void);

#define DVG_GL_IS_PROJECTION_STEREO_APPLIED_EXT "glIsProjectionStereoAppliedDVG"
typedef int (GLAPIENTRY *glIsProjectionStereoAppliedDVG)(void);

#define DVG_GL_IS_PROJECTION_TILING_APPLIED_EXT "glIsProjectionTilingAppliedDVG"
typedef int (GLAPIENTRY *glIsProjectionTilingAppliedDVG)(void);

#define DVG_GL_GET_TILE_STATUS_EXT "glGetTileStatusDVG"
typedef int (GLAPIENTRY *glGetTileStatusDVG)(int *aIsTiled, 
                          unsigned *aHorizontalTiles, unsigned *aVerticalTiles,
                          unsigned *aHorizontalPos, unsigned *aVerticalPos, 
                          float *aHorizontalMargin, float *aVerticalMargin, 
                          int *aIncFov, int *aDecFov);

#define DVG_GL_GET_RENDERING_GROUP_EXT "glGetRenderingGroupDVG"
typedef int (GLAPIENTRY *glGetRenderingGroupDVG)(unsigned int *aMyPosition, 
                      unsigned int *aLength,
                      unsigned int *aMasterIp,
                      unsigned int *aSyncIp);

#define DVG_GL_GET_CHAIN_LENGTH_EXT "glGetChainLengthDVG"
typedef int (GLAPIENTRY *glGetChainLengthDVG)(unsigned int *aLength);

#define DVG_GL_ARRANGE_PROJECTION_MATRIX_EXT "glArrangeProjectionMatrixDVG"
typedef int (GLAPIENTRY *glArrangeProjectionMatrixDVG)(float aMatrix[16]);

#define DVG_GL_GET_FRAMERATE_DIVIDER_EXT "glGetFramerateDividerDVG"
typedef int (GLAPIENTRY *glGetFramerateDividerDVG)(unsigned int *aFrameRateDivider);

#define DVG_GL_WAIT_FOR_REAL_SWAP_EXT "glWaitForRealSwapDVG"
typedef int (GLAPIENTRY *glWaitForRealSwapDVG)(unsigned int *aCount, 
                    const unsigned int aTimeOut);
  
#ifdef _WIN32
#define DVG_GL_GET_TIME_FROM_SWAP_EXT "glGetTimeFromSwapDVG"
typedef int (GLAPIENTRY *glGetTimeFromSwapDVG)(unsigned int *aTime);

#define DVG_GL_GET_TIME_TO_SWAP_EXT "glGetTimeToSwapDVG"
typedef int (GLAPIENTRY *glGetTimeToSwapDVG)(unsigned int *aTime);
#endif

#define DVG_GL_GET_VERSION_EXT "glGetVersionDVG"
typedef int (GLAPIENTRY *glGetVersionDVG)(unsigned *aMajor, unsigned *aMinor, unsigned *aRevision);

#define DVG_GL_GET_SERVICE_VERSION_EXT "glGetServiceVersionDVG"
typedef int (GLAPIENTRY *glGetServiceVersionDVG)(unsigned *aMajor, unsigned *aMinor, unsigned *aRevision);

#define DVG_GL_GET_DRIVER_VERSION_EXT "glGetDriverVersionDVG"
typedef int (GLAPIENTRY *glGetDriverVersionDVG)(unsigned *aMajor, unsigned *aMinor, unsigned *aRevision);
 
#define DVG_GL_GET_FIRMWARE_VERSION_EXT "glGetFirmwareVersionDVG"
typedef int (GLAPIENTRY *glGetFirmwareVersionDVG)(unsigned *aVersion, unsigned *aRevision, unsigned *aPatchLevel);

#define DVG_GL_GET_WRAPPER_VERSION_EXT "glGetWrapperVersionDVG"
typedef int (GLAPIENTRY *glGetWrapperVersionDVG)(unsigned *aMajor, unsigned *aMinor, unsigned *aRevision);

#define DVG_GL_IS_CONFIG_CHANGED_EXT "glIsConfigChangedDVG"
typedef int (GLAPIENTRY *glIsConfigChangedDVG)(void);

#define DVG_GL_START_MEASURE_EXT "glStartMeasureDVG"
typedef int (GLAPIENTRY *glStartMeasureDVG)(const int aStatsCategory);

#define DVG_GL_END_MEASURE_EXT "glEndMeasureDVG"
typedef int (GLAPIENTRY *glEndMeasureDVG)(const int aStatsCategory);

#define DVG_GL_GET_STATS_EXT "glGetStatsDVG"
typedef int (GLAPIENTRY *glGetStatsDVG)(const int aStatsCategory, unsigned long *aMinTime, unsigned long *aMaxTime, unsigned long *aSumTime, unsigned long *aCount);

#define DVG_GL_GET_LAST_TIME_EXT "glGetLastTimeDVG"
typedef int (GLAPIENTRY *glGetLastTimeDVG)(const int aStatsCategory, unsigned long *aLastTime);

#define DVG_GL_GET_STATS_COUNTER_EXT "glGetStatsCounterDVG"
typedef int (GLAPIENTRY *glGetStatsCounterDVG)(const int aStatsCategory, unsigned long *aCounter);

#define DVG_GL_WRITE_USER_MESSAGE_EXT "glWriteUserMessageDVG"
typedef int (GLAPIENTRY *glWriteUserMessageDVG)(const int aDebugCategory, const char* aMessage);


#ifdef __cplusplus
}
#endif

#endif
