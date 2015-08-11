/* 
 * Copyright 2002,2003 Orad Hi-Tec Systems Ltd.
 * ALL RIGHTS RESERVED
 *
 * Filename: dvgAPI.hpp
 */

#ifndef DVG_API_HPP
#define DVG_API_HPP

#include "dvgAPICommon.hpp"
#include "DvgAPIDefs.hpp"

/**
Class delivered API for DVG driver
*/

//struct DVGChainConfiguration;
//struct DVGProjectionConfiguration;
struct DVGRenderingGroup;
struct DVGOutputFormat;
struct DvgCapability;
struct DVGSwapCounter;
class dvgInternalOutput;
namespace dvgMemStruct
  {
  struct APIData;
  struct ServiceData;
  }

class DVGAPI_SHARED_SYMBOL dvgAPI
  {
public:

  enum StatusCodes
    {
    SUCCESS = 0,
    UNSUPPORTED_CAPABILITY = -500,
    ERROR_PARAMETER_VALUE,
    DRIVER_NOT_STARTED,
    DRIVER_FAILURE,
    DRIVER_CLOSE_FAILURE,
    CREATE_OVERLAPED_EVENT_FAILURE,
    CREATE_SWAP_EVENT_FAILURE,
    SWAP_EVENT_NOT_SET,
    CREATE_INTERRUPT_EVENT_FAILURE,
    INTERRUPT_EVENT_NOT_SET,
    SWAP_COUNTER_NOT_SET,
    CHANGES_NOTIFICATION_NOT_SET,
    DRIVER_IO_ERROR,
    SWAP_TIMEOUT,
    WAITING_TIMEOUTED = SWAP_TIMEOUT,
    SWAP_FAILED,
    WAITING_FAILED = SWAP_FAILED,
    CREATE_COMMUNICATION_FAILURE,
    API_NOT_OPEN,
    DRIVER_FW_NOT_LOADED,
    CREATE_SWAP_BARRIER_READY_EVENT_FAILURE,
    CREATE_SWAP_BARRIER_WAIT_EVENT_FAILURE,
    MESSAGES_SERVICE_FAILURE,
    END_OF_STATUS_CODES
    };

  ///
  enum AspectCorrections
    {
    /// No aspect correction.
    AC_NONE = 0,
    /// Field of view will be increased.
    AC_INCREASE_FOV,
    /// Field of view will be decreased.
    AC_DECREASE_FOV
    };

  ///
  enum GfxBoardVendor
    {
    /// Venodr not recognized
    GFX_VENDOR_UNKNOWN = 0,
    /// Vendor NVidia Corp.
    GFX_VENDOR_NV,
    /// Vendor ATI Corp.
    GFX_VENDOR_ATI
    };

  /** 
  Default constructor.
  It initialize all the internal struct.
  Pleas use getStatus() method to check that initialization finish succesfuly.
  */
  dvgAPI(void);

  /** 
  Destructor.
  It close connection to the driver and release all resources.
  It do not unload (stop) the driver.
  */
  ~dvgAPI(void);

  /**
  This method return last status code (like last called method return).
  See StatusCodes definition.
  */
  int getStatus() const;

  /**
  This method return string description for given status code 
  (returned by any called method) or NULL if the value is out of the range.
  If called without parameters, return description about last status 
  (like returned by getStatus() method.
  */
  const char *getStatusString(const StatusCodes aStatusCode = END_OF_STATUS_CODES) const;

  /**
  This method return last system error code generated by called method.
  It is set only if called method return error status code
  and can be read to get more information about the problem.
  See windows GetLastError() function for meaning of the codes.
  */
  int getSystemErrorCode() const;

  /**
  This method try to open connection to the driver.
  Must be executed before use on any methods below.
  Can be call more than one time
  (next call first call close() method, then reopen all connection).
  It returns StatusCodes error code.
  */
  int open(void);

  /**
  This close connection to the driver.
  It is executed into destructor automatically.
  It return StatusCodes error code.
  */
  int close(void);

  /**
  This method return true if last open() execute succeed and close() was not call after.
  */
  bool isOpen(void) const
    { return theIsOpen; };

  /**
  This function return and reset subset of binary flags selected by aFlag parameter
  ("1" into the mask mean that value of this flag is returned and flag is reset to "0").
  Description of the flags you can find into ...................
  */
  unsigned int getChangesFlags(const unsigned int aFlag);

  /**
  This function return version of the used API library.
  @param aMajor      - a major version number.
  @param aMinor      - a minor version number.
  @param aRevision   - a revision number.
  @return  - a StatusCodes error code.
  */
  int getVersion(unsigned &aMajor, unsigned &aMinor, unsigned &aRevision);

  /**
  This function return version of DVG service working on this machine.
  @param aMajor      - a major version number.
  @param aMinor      - a minor version number.
  @param aRevision   - a revision number.
  @return  - a StatusCodes error code.
  */
  int getServiceVersion(unsigned &aMajor, unsigned &aMinor, unsigned &aRevision);

  /**
  This function return version of DVG driver working on this machine.
  @param aMajor      - a major version number.
  @param aMinor      - a minor version number.
  @param aRevision   - a revision number.
  @return  - a StatusCodes error code.
  */
  int getDriverVersion(unsigned &aMajor, unsigned &aMinor, unsigned &aRevision);
 
  /**
  This function return version of DVG firmware installed on the DVG board.
  @param aVersion    - a version of DVG board number.
  @param aRevision   - a Revision of DVG board number.
  @param aPatchLevel - a patch level for given revision version.
  @return  - a StatusCodes error code.
  */
  int getFirmwareVersion(unsigned &aVersion, unsigned &aRevision, unsigned &aPatchLevel);


  /**
  This function return vendor of the installed GFX board (NV, ATI etc.)
  @param aVendor    - a GFX board vendor ID.
  @return  - a StatusCodes error code.
  */
  int getGfxBoardVendor(GfxBoardVendor &aVendor);

  /**
  This function return currently displayed GFX parameters (on the output of the chain).
  aVrate is in Hz, rest parameters in pixels.
  @param aVrate      - a frame rate frequency in Hz of the output video signal.
  @param aHActive    - a number of displayed horizontal pixels.
  @param aHSyncStart - a number of pixel where horizontal synchronisation pulse start.
  @param aHSyncEnd   - a number of pixel wher horizontal synchronisation pulse end.
  @param aHTotal     - a total number of horizontal pixels (including active pixels, sync pulse, front porch and back porch).
  @param aVActive    - a number of displayed pixel rows.
  @param aVSyncStart - a number of row where vertical synchronisation pulse start.
  @param aVSyncEnd   - a number of row where vertical synchronisation pulse end.
  @param aVTotal     - a total number of rows (including active rows, sync pulse, front porch and back porch).
  @return  - a StatusCodes error code.
  */
  int getVRGraphicsMode(float &aVrate, unsigned &aHActive,
                        unsigned &aHSyncStart, unsigned &aHSyncEnd, 
                        unsigned &aHTotal, unsigned &aVActive,
                        unsigned &aVSyncStart, unsigned &aVSyncEnd,
                        unsigned &aVTotal);

  /**
  This function return viewport size in pixels.
  In chain modes sometimes rendering application must open window
  which do not cover all the screen. This function return size of the rendering area.
  Left upper corner of the area is on (0,0) position.
  It return StatusCodes error code.
  */
  int getBaseViewportSize(unsigned int &aBaseWidth, unsigned int &aBaseHeight);

  /**
  This function return number of antialasing samples to be generated by GFX adapter hardware.
  API and driver try to force GFX driver to use such number of samples, but application can try set it anyway.
  1 sample means no GFX antialiasing. 
  It return StatusCodes error code.
  */
  int getGFXMultiSampling(DvgAPIDefs::DVGMultisaplingMode &aSamples);

  int getGFXMultiSampling(unsigned int &aSamples)
    {
    return getGFXMultiSampling(*(DvgAPIDefs::DVGMultisaplingMode*)&aSamples);
    }

  /**
  This function return additive function of the chain.
  If additive function is activated, content from chain (previous nodes) 
  is composited with current nodes content using one of methods below:
  aAdditiveFunction can be:
     - DVG_NOT_ADDITIVE - which mean additive functionality is off
     - DVG_ADD_CHROMA_CHAIN - which mean that mixing is based on chromakey from chain (previous nodes) color. 
     - DVG_ADD_CHROMA_GFX  - which mean that mixing is based on chromakey from local GFX color.
     - DVG_ADD_BLEND  - which mean that mixing is based on additive blending.
  It return StatusCodes error code.
  */
  int getAdditiveFunction(DvgAPIDefs::DVGAdditiveFunction &aAdditiveFunction);
  
  /**
  This function return number of time divided antialasing samples to be generated by DVG hardware.
  1 sample means no TDAA antialiasing.
  It return StatusCodes error code.
  */
  int getTDAA(unsigned int &aSamples);

  /**
  This function return parameters of current antialiasing chain.
  aAALen explain how many samples are generated into chain. 1 means that AA chain is off.
  aAAPos explain which AA sample is generate this renderer. It can have values in range (0, aAALen - 1).
  It return StatusCodes error code.
  */
  int getAAChain(unsigned int &aAAPos, unsigned int &aAALen);  
  
  /**
  This function return parameters of current Time Division chain.
  aTDLen explain how many time slots are generated into chain. 1 means that time division is off.
  aTDPos explain which time division slot (phase) is generated on this renderer. 
  It can have values in range (0, aTDLen - 1).
  It return StatusCodes error code.
  */
  int getTDChain(unsigned int &aTDPos, unsigned int &aTDLen);

  /**
  This function return parameters of current Added Image Division chain.
  aAIDLen explain how many added parts are generated into chain. 1 means that  added image division is off.
  aAIDPos explain which part is generated on this renderer. It can have values in range (0, aAIDLen - 1).
  It return StatusCodes error code.
  */
  int getAIDChain(unsigned int &aAIDPos, unsigned int &aAIDLen);  

  /**
  This function was removed.
  Please use getAIDChain() and getAAChain() functions, which are now independent.
  */
  // int getUseAAToSSD(bool &aUseAAToSSD);

  /**
  This function return parameters of current Screen Image Division chain.
  aVLen explain how many vertical parts are generated into chain. 1 means that vertical division is off.
  aHLen explain how many horizontal parts are generated into chain. 1 means that horizontal division is off.
  aVPos explain which vertical part is generated on this renderer ( 0 to aVLen - 1).
  aHPos explain which horizontal part is generated on this renderer ( 0 to aHLen - 1).
  It return StatusCodes error code.
  */
  int getSIDChain(unsigned int &aHPos, unsigned int &aVPos, unsigned int &aHLen, unsigned int &aVLen);

  /**
  This function return parameters of current Interleaved Image Division chain.
  aIIDLen explain how many vertically interleaved parts are generated into chain. 1 means that interleaved division is off.
  aIIDPos explain which vertical part is generated on this renderer ( 0 to aIIDLen - 1).
  It return StatusCodes error code.
  */
  int getIIDChain(unsigned int &aIIDPos, unsigned int &aIIDLen);

  /**
  This function return parameters needed to construct SID projection.
  use getBaseViewportSize() method to get size of the rendering window to be open.
  aTotalWidth and aTotalHeight return size of the whole picture generated into chain.
  aHOffset and aVOffset return offset of the left upper corner from the whole picture to the
  subwindow which is generated by this renderer.
  If SID chain is not active, it return base viewport size into aTotalWidth and aTotalHeight,
  and 0,0 in aHOffset and aVOffset.
  It return StatusCodes error code.
  */
  int getSIDViewportSize(unsigned int &aTotalWidth, unsigned int &aTotalHeight,
                         unsigned int &aHOffset, unsigned int &aVOffset);

  /**
  This function return parameters of current stereo mode.
  Two stereo modes are supported: active and passive.
  In passive mode each chain generate picture just for one eye. 
  Then passive mode just change camera and projection parameters.
  Active stereo mode generate altered pictures for both eyes.
  In active mode special VESA connector on the rear of DVG is activated 
  (to connect active glasses).
  In active mode each renderer woroks with the half chian frame frequency.
  Then if chain is set to 1024x768 120 Hz, each renderer work in 1024x768 60 Hz.
  Meaning of parameters:
  aIsStereo - return true if active or passive stereo is on.
  aIsActiveStereo - return true if active stereo is on.
  aIsLeftEye - return true if this renderer must render for left eye, otherwise right eye must be generated.
  aUseArrangeMatrices - return true if arrangeProjectionMatrix() method arrange projection using stereo parameters.
   (the same flag is returned by isProjectionStereoApplied() method).
  aEyeSeparation - it is distance between eyes in meters, usually about 0.1 to .15.
  aEyeFocalLen - it is distance between eyes and projection plane in meters, ussually about 8 times eyeSeparation.
  It return StatusCodes error code.
  */
  int getStereoStatus(bool &aIsStereo, bool &aIsActiveStereo, 
                      bool &aIsLeftEye, bool &aUseArrangeMatrices,
                      float &aEyeSeparation, float &aEyeFocalLen);

  /**
  This method return true if arrangeProjectionMatrix() method use AA chain parameters to adjust projection.
  */
  bool isProjectionAAApplied(void);

  /**
  This method return true if arrangeProjectionMatrix() method use SID chain parameters to adjust projection.
  */
  bool isProjectionSIDApplied(void);

  /**
  This method return true if arrangeProjectionMatrix() method use IID chain parameters to adjust projection.
  */
  bool isProjectionIIDApplied(void);

  /**
  This method return true if arrangeProjectionMatrix() method use stereo chain parameters to adjust projection.
  WARNING ! Only projection can be adjusted for stereo. Rendering program must adjust camera position itself,
  based on current stereo parameters.
  */
  bool isProjectionStereoApplied(void);

  /**
  This method return true if arrangeProjectionMatrix() method use tiling group parameters to adjust projection.
  */
  bool isProjectionTilingApplied(void);

  /**
  This function return parameters of the channel tiling.
  @param aIsTiled           - return true if tiling is activated.
  @param aAspectCorrection  - return type of aspect correction to be done.
  @param aHorizontalTiles   - return number of columns on tiles. 1 means no tiling horizontally.
  @param aVerticalTiles     - return number of rows on tiles. 1 means no tiling vertically.
  @param aHorizontalPos     - return column number to be display by this renderer. It is counted from 0.
  @param aVerticalPos       - return row number to be display by this renderer. It is counted from 0.
  @param aHorizontalMargin  - return overlaped margin counted in the screen diameter. 
                              1.0 means 100 % overlaped, 0.0 means no overlaped.
                              negative values means gap between tiles. Possible range [-1.0, 1.0]
  @param aVerticalMargin    - return overlaped margin counted in the screen diameter. 
                              1.0 means 100 % overlaped, 0.0 means no overlaped.
                              negative values means gap between tiles. Possible range [-1.0, 1.0]
  @return  - a StatusCodes error code.
  */
  int getTileStatus(bool &aIsTiled, AspectCorrections &aAspectCorrection, unsigned &aHorizontalTiles,
                            unsigned &aVerticalTiles, unsigned &aHorizontalPos,
                            unsigned &aVerticalPos, float &aHorizontalMargin,
                            float &aVerticalMargin);

    
  /**
  This method return current rendering group parameters.
  aLength return length of the rendering group 
  (remember that rendering chain length can be shorter, if such configuration is set)
  aMyPosition return position into the group, from 0 to aLength - 1.
  This position is related to the phisical connection.
  aMasterIp return IP address of the "master" host of this grup. used only for information purposes.
  aSyncIp return IP address of the "synchronisation" host of this grup. used only for information purposes.
  */
  int getRenderingGroup(unsigned int &aMyPosition, 
                        unsigned int &aLength,
                        unsigned int &aMasterIp,
                        unsigned int &aSyncIp);

  /**
  This function return number of the computers used in current chain mode.
  @param aLength   - return number of the renderers used (1 to the length of rendering group).
  @return  - a StatusCodes error code.
  */
  int getChainLength(unsigned int &aLength);
 
  
  /**
  This method modify the projection matrix. It does this in-place. 
  The 16 floats of the matrix are in the same arrangement as returned by 
  glGetFloatv(GL_PROJECTION_MATRIX).
  This matrix is always adjusted due to antialiasing subpixel shift (based on current AA configuration,
  including all AA chain, TDAA and GFX hardware samples).
  Adjsuting due to stereo, SID and IID can be switched on/off from chain configuration.
  Use methods: isProjectionSIDApplied(), isProjectionIIDApplied(), isProjectionStereoApplied() to get current state.
  It return StatusCodes error code.
  */
  int arrangeProjectionMatrix(float aMatrix[16]);

  /**
  This method return current frame rate divider factor.
  1 means that it is off.
  Higher values means that swap events frequency on each renderer are divided by this factor.
  It is used in situation when rendering is too heavt to be render in each frame.
  Then it is possible to set some constant, maximum frequency (which is below full framerate frequency).
  It helps to synchronize all renderers in such situation.
  It return StatusCodes error code.
  */
  int getFramerateDivider(unsigned int &aFrameRateDivider);

  /*
  This methods wait for the next swap on the renderer.
  It returns the common chain-adjusted swapcounter (in aCount). 
  If in time divided chaining, it waits for the correct phase. 
  If framerate divider is active, it waits for given number of frames also.
  That is - it does not necessarily return after the next 
  50/60hz vsync, but after the one 'assigned' to it (according to its 
  time division chain position and framerate divider).
  aTimeOut parameters can be set with timeout in miliseconds, default is infinite.
  It return StatusCodes error code.
  */
  int waitForSwap(unsigned int &aCount, 
                  const unsigned int aTimeOut = INFINITE_TIMEOUT);

  /**
  This function wait for the next sync IRQ on this renderer.
  It returns the common swapcounter (in aCount). 
  It waits for the real next vsync, and doesn't adjust to the chain. 
  aTimeOut parameters can be set with timeout in miliseconds, default is infinite.
  It return StatusCodes error code.
  */
  int waitForRealSwap(unsigned int &aCount, 
                      const unsigned int aTimeOut = INFINITE_TIMEOUT);
    
  
  /*
  This methods wait for the right moment to start rendering.
  In chains others than TD it just returns (does nothing). In TD chain if
  TD DFR is activated, it waits for the right moment to start rendering. 
  If TD DFR activated it _must_ be called just after "swap buffers".
  It returns the common chain-adjusted swapcounter (in aCount). 
  aTimeOut parameters can be set with timeout in miliseconds, default is infinite.
  It return StatusCodes error code.
  */
  int waitForRender(unsigned int &aCount, 
                    const unsigned int aTimeOut = INFINITE_TIMEOUT);
  

  /**
  This method return a group-adjusted swap counter, related to all
  the chain patrameters (like last waitForSwap() methods return).
  It return StatusCodes error code.
  */
  int getSwapCounter(unsigned int &aCount);
  
  /**
  This method return a absolute swap counter 
  (like last waitForRealSwap() methods return).
  It return StatusCodes error code.
  */
  int getRealSwapCounter(unsigned int &aCount);
  
  /** 
  Get both group-adjusted and/or real (absolute) swap counters.
  Each parameter can be NULL if given counter is not needed.
  It return StatusCodes error code.
  */
  int getSwapCounters(unsigned int *aCount, unsigned int *aRealCount);

  /**
  This method return time in microseconds from the last swap IRQ.
  It return StatusCodes error code.
  */
  int getTimeFromSwap(unsigned int &aTime);

  /**
  This method return time in microseconds to the next swap IRQ.
  It return StatusCodes error code.
  */
  int getTimeToSwap(unsigned int &aTime);

  /**
  This method starts measurement of specific statistics category.
  It return StatusCodes error code.
  */
  int startMeasure(const int aStatsCategory);

  /**
  This method ends measurement of specific statistics category.
  It return StatusCodes error code.
  */
  int endMeasure(const int aStatsCategory);

  /**
  This method returns statistics of specific category.
  It return StatusCodes error code.
  */
  int getStats(const int aStatsCategory, unsigned long &aMinTime, unsigned long &aMaxTime, unsigned long &aSumTime, unsigned long &aCount);

  /**
  This method returns last measurement of specific statistics category.
  It return StatusCodes error code.
  */
  int getLastTime(const int aStatsCategory, unsigned long &aLastTime);

  /**
  This method returns measurement's counter of specific statistics category.
  It return StatusCodes error code.
  */
  int getStatsCounter(const int aStatsCategory, unsigned long &aCounter);

  /**
  This method returns user debug flags in aFlags parameter.
  It return StatusCodes error code.
  */
  int getUserDebugFlags(unsigned int &aFlags);

  /**
  This method is used to write user message in given category to remote message viewer
  Then it can be displayed and/or logged into management GUI or received by DVGServiceAPI
  aCategory parameter defines one of categories from DVGDebugCategory enum.
  aMessage point to null-terminated string with message to write. 
  It returns StatusCodes error code.
  */
  int writeUserMessage(const DvgAPIDefs::DVGDebugCategory aCategory, const char* aMessage);

  /**
  This method is used to write user message in given category to remote message viewer
  Then it can be displayed and/or logged into management GUI or received by DVGServiceAPI
  aCategory parameter define one of categories from DVGDebugCategory enum.
  aFormat point to a string defining format in printf()-like form.
  Rest parameters are variable, as defined in aFormat. 
  It returns StatusCodes error code.
  */
  int writeUserMessageEx(const DvgAPIDefs::DVGDebugCategory aCategory, const char* aFormat, ...);

  /**
  This method is used to write user message in given category to remote message viewer
  Then it can be displayed and/or logged into management GUI or received by DVGServiceAPI
  aCategory parameter define one of categories from DVGDebugCategory enum.
  aFormat point to a string defining format in printf()-like form.
  aArags defines list of arguments - like in vsprintf() call. 
  It returns StatusCodes error code.
  */
  int writeUserMessageEx(const DvgAPIDefs::DVGDebugCategory aCategory, const char* aFormat, va_list aArgs);

  int waitForSwapBarrier(unsigned int &aCount, 
                         const unsigned int aTimeOut = INFINITE_TIMEOUT);

  void setIsRendering(const bool aIsRendering)
    { theIsRendering = aIsRendering; };

  bool getIsRendering(void)
    { return theIsRendering; };
 
  enum 
    {
    INFINITE_TIMEOUT = 0xFFFFFFFF,
    };

protected:

  HANDLE theDriver;
  ///handles to 
  HANDLE theSwapEvent;
  HANDLE theInterruptEvent; 
  volatile DVGSwapCounter *theSwapCounters;
  volatile unsigned int *theChangesFlags;

  int theErrorCode;
  int theStatus;

  OVERLAPPED theOverlappedStruct;

  bool checkOverlappedResult(OVERLAPPED &aOverlappedStruct, const bool aWait = true);
  unsigned int checkChanges(const unsigned int aFlag, const bool aInternal = true);

  int updateProjectionStatus(void);
  int updateChainInfo(void);
  int updateGraphicsMode(void);
  int updateBaseViewportSize(void);

  bool openAPIData(void);
  bool openServiceData(const bool aReadOnly);
  void closeAPIData(void);
  void closeServiceData(void);

  inline unsigned getTimeDiff(const __int64 aStart, const __int64 aStop)
    {
    return (unsigned int)((aStop - aStart) * 1000000 / timerResolution);
    }

  inline void getTimestamp(__int64 &aStamp)
    {
    QueryPerformanceCounter((LARGE_INTEGER *)&aStamp);
    }

  enum
    {
    MAX_STATUS_CODES = (END_OF_STATUS_CODES - UNSUPPORTED_CAPABILITY) + 1
    };

  static const int theMagic[32][32];
  DvgAPIDefs::DVGMultisaplingMode theGFXSamples;
  DvgAPIDefs::DVGChainConfiguration *theChain;
  unsigned theBaseViewport[2];
  unsigned int theTDAA;
  unsigned int theFramerateDivider;
  unsigned int theProjectionFlags;
  DvgAPIDefs::DVGProjectionConfiguration *theProjectionConfig;
  DVGRenderingGroup *theGroup;
  DVGOutputFormat *theFormat;

  unsigned int theInternalChangesFlags;
  unsigned int theExternalChangesFlags;
  volatile dvgMemStruct::APIData *theAPIData;
  HANDLE theAPIDataHandle;
  bool theServiceDataReadOnly;
  volatile dvgMemStruct::ServiceData *theServiceData;
  dvgInternalOutput* theInternalOutput;
  HANDLE theServiceDataHandle;
  DvgCapability *theCapability;
  __int64 theSwapFinish;
  bool theIsRendering;
  bool theIsOK;
  GfxBoardVendor theGfxVendor;
  bool theGFXReal4Samples;

  static const char *theStatusStrings[MAX_STATUS_CODES];

  HANDLE theSwapBarrierReadyEvent;
  HANDLE theSwapBarrierWaitEvent;
  __int64 timerResolution;
  __int64 currentTimeStamp;
  bool theIsOpen;
private:
  /// do not use copy constructor
  dvgAPI(const dvgAPI &aOther);

  /// do not use '=' operator
  dvgAPI &operator=(const dvgAPI &aOther);
  };

#endif

