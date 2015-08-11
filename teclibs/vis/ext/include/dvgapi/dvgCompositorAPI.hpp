/* 
 * Copyright 2007 Orad Hi-Tec Systems Ltd.
 * ALL RIGHTS RESERVED
 *
 * Filename: dvgCompositorAPI.hpp
 */

#ifndef DVG_COMPOSITOR_A_P_I_HPP
#define DVG_COMPOSITOR_A_P_I_HPP

#include "dvgAPIBase.hpp"

/**
Class delivered API for DVG compositor functionality of board.
Use isCompositor() function from base API to check if board has compositor capabilities.
Check base class dvgAPIBase for more information.
This class just read current configuration, state and parameters and is not used for 
control and configuration (see dvgCompositorControlAPI for that).
*/


namespace DvgAPIDefs
  {
  struct DVGChainConfiguration;
  struct DVGProjectionConfiguration;
  };
struct DVGRenderingGroup;
struct DVGSolution;
struct DVGSwapCounter;
struct DVGBufferHeader;


class DVGAPI_SHARED_SYMBOL dvgCompositorAPI: public dvgAPIBase
  {
public:

  enum 
    {
    /// Default timeout value for some wait methods.
    INFINITE_TIMEOUT = 0xFFFFFFFF,
    };

  /// Define vendor of GFX board.
  enum GfxBoardVendor
    {
    /// Vendor not recognized.
    GFX_VENDOR_UNKNOWN = 0,
    /// Vendor NVidia Corp.
    GFX_VENDOR_NV,
    /// Vendor ATI Corp.
    GFX_VENDOR_ATI,
    };

  /// Define aspect correction when some tiling is used.
  enum AspectCorrections
    {
    /// No aspect correction.
    AC_NONE = 0,
    /// Field of view will be increased.
    AC_INCREASE_FOV,
    /// Field of view will be decreased.
    AC_DECREASE_FOV
    };

  /// Define type of viewport.
  enum ViewPortType
    {
    /// Viewport used for RGB color rendering.
    VIEWPORT_COLOR = 0,
    /// Viewport used for alpha rendering (as white color).
    VIEWPORT_ALPHA,
    };

  /** 
  Default constructor.
  It initialize all the internal struct.
  Pleas use getStatus() method to check that initialization finish succesfuly.
  */
  dvgCompositorAPI(void);

  /** 
  Destructor.
  It close connection to the board and release all resources.
  It do not stop the board.
  */
  ~dvgCompositorAPI(void);

  /**
  This function return vendor of the GFX board (NV, ATI etc.) connected to DVG board.
  @param aVendor    - a GFX board vendor ID.
  @return  - a StatusCodes error code.
  */
  dvgAPIBase::StatusCodes getGfxBoardVendor(GfxBoardVendor &aVendor);

  /**
  This function return video standard which is active on this DVG board.
  */
  dvgAPIBase::StatusCodes getVideoStandard(DvgAPIDefs::DVGVideoStandard& aStandard);

  /**
  This function return video format which is active on this DVG board.
  */
  dvgAPIBase::StatusCodes getVideoFormat(DvgAPIDefs::DVGGraphicsMode& aFormat);

  /**
  This function returns detailed parameters of chain video format when it is DvgAPIDefs::DVG_VR_CUSTOM.
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
  dvgAPIBase::StatusCodes getVRGraphicsMode(float &aVrate, unsigned &aHActive,
                        unsigned &aHSyncStart, unsigned &aHSyncEnd, 
                        unsigned &aHTotal, unsigned &aVActive,
                        unsigned &aVSyncStart, unsigned &aVSyncEnd,
                        unsigned &aVTotal);

  /**
  Returns name of display reported by Windows, associated with DVG board.
  It return StatusCodes error code.
  */
  dvgAPIBase::StatusCodes getDisplayName(const char* &aName);

  /**
  This function returns Windows desktop position of rendering area.
  All viewports are inside this area.
  It is one common Windows desktop, but it can be divided for several displays.
  It return StatusCodes error code.
  */
  dvgAPIBase::StatusCodes getRenderingAreaDesktopPos(long int& aX, long int& aY);

  /**
  This function returns display position of rendering area.
  All viewports are inside this area.
  To check which display is used, see getDisplayName().
  It return StatusCodes error code.
  */
  dvgAPIBase::StatusCodes getRenderingAreaDisplayPos(long int& aX, long int& aY);

  /**
  This function returns size of rendering area, usually it is whole Windows display size.
  All viewports are inside this area.
  It return StatusCodes error code.
  */
  dvgAPIBase::StatusCodes getRenderingAreaSize(unsigned int& aWidth, unsigned int& aHeight);

  /**
  Returns number of outputs currently produced by DVG board.
  Usually it is one output.
  Outputs are counted from 0.
  It return StatusCodes error code.
  */
  dvgAPIBase::StatusCodes getNumberOfOutputs(unsigned int& aNumber);

  /**
  Returns number of viewports of specified type for specified output.
  Outputs are indexed from 0.
  It return StatusCodes error code.
  */
  dvgAPIBase::StatusCodes getNumberOfViewports(unsigned int& aNumber, const ViewPortType aType, const unsigned int aOutput = 0);

  /**
  Returns offsets related to left upper corner of rendering area.
  Outputs are indexed from 0.
  aIndex - index of viewport for specified type and output.
  Outputs are indexed from 0.
  Viewports are indexed from 0.
  It return StatusCodes error code.
  */
  dvgAPIBase::StatusCodes getViewportOffsets(unsigned int& aXOffset, unsigned int& aYOffset, const ViewPortType aType, 
                                 const unsigned int aIndex = 0, const unsigned int aOutput = 0);

  /**
  Returns desktop position of viewport.
  It is one common Windows desktop, but it can be divided for several displays.
  aIndex - index of viewport for specified type and output.
  Outputs are indexed from 0.
  Viewports are indexed from 0.
  It return StatusCodes error code.
  */
  dvgAPIBase::StatusCodes getViewportDesktopPos(long int& aX, long int& aY, const ViewPortType aType, const unsigned int aIndex = 0, const unsigned int aOutput = 0);

  /**
  Returns display position of viewport.
  To check which display is used, see getDisplayName().
  aIndex - index of viewport for specified type and output.
  Outputs are indexed from 0.
  Viewports are indexed from 0.
  It return StatusCodes error code.
  */
  dvgAPIBase::StatusCodes getViewportDisplayPos(long int& aX, long int& aY, const ViewPortType aType, const unsigned int aIndex = 0, const unsigned int aOutput = 0);

  /**
  This function returns viewport size.
  aIndex - index of viewport for specified type and output.
  Outputs are indexed from 0.
  Viewports are indexed from 0.
  It return StatusCodes error code.
  */
  dvgAPIBase::StatusCodes getViewportSize(unsigned int& aWidth, unsigned int& aHeight, const ViewPortType aType, const unsigned int aIndex = 0, const unsigned int aOutput = 0);


  /**
  This function initiate functionality of alpha plane copying between viewports.
  It is only for Open GL applications and must be call after proper OGL window and context is opened.
  Size of opened window must be get from getRenderingAreaSize()
  Initialization is separate for each output (usually it is only one output number 0)
  aOutput - number of output.
  Outputs are indexed from 0.
  It return StatusCodes error code.
  */
  dvgAPIBase::StatusCodes initAlphaCopy(const unsigned int aOutput = 0);

  /**
  This fumction copy alpha plane from Color viewport indexed by aSourceIndex to the Alpha viewport indexed by aDestinationIndex.
  Alpha plane from color viewport is transformed to white color (the same RGB values) into alpha viewport.
  initAlphaCopy() for given output must be call before.
  This function is normally called just before swap.
  aSourceIndex - index of Color viewport from which alpha will be copied.
  aDestinationIndex - index of Alpha viewport to which alpha will be copied.
  aOutput - number of DVG board output, usually 0.
  Outputs are indexed from 0.
  Viewports are indexed from 0.
  It return StatusCodes error code.
  */
  dvgAPIBase::StatusCodes copyAlpha(const unsigned int aSourceIndex, const unsigned int aDestinationIndex, const unsigned int aOutput = 0);

  /**
  This function copy alpha to all Alpha viewports defined for given output.
  Alpha is copied from color viewport with the same index (e.g. 0 to 0, 1 to 1 up to all viewports).
  Alpha plane from color viewport is transformed to white color (the same RGB values) into alpha viewport.
  initAlphaCopy() for given output must be call before.
  This function is normally called just before swap.
  aOutput - number of DVG board output, usually 0.
  Outputs are indexed from 0.
  It return StatusCodes error code.
  */
  dvgAPIBase::StatusCodes copyAlpha(const unsigned int aOutput = 0);
  
  /**
  This function return antialasing mode generated by GFX adapter hardware.
  API try to force GFX driver to use such antialiasing, but application can try set it anyway.
  It return StatusCodes error code.
  */
  dvgAPIBase::StatusCodes getGFXMultiSampling(DvgAPIDefs::DVGMultisaplingMode &aSamples);
  
  /**
  This function return additive function of the chain.
  If additive function is activated, content from chain (previous nodes) or video input
  is composited with local node content using selected method.
  See definition of DVGAdditiveFunction.
  It return StatusCodes error code.
  */
  dvgAPIBase::StatusCodes getAdditiveFunction(DvgAPIDefs::DVGAdditiveFunction &aAdditiveFunction);
  
  /**
  This function return number of time divided antialasing samples to be generated by DVG hardware.
  1 sample means no TDAA antialiasing. Used on VRX only.
  It return StatusCodes error code.
  */
  dvgAPIBase::StatusCodes getTDAA(unsigned int &aSamples);

  /**
  This function return parameters of current antialiasing chain.
  aAALen explain how many samples are generated into chain. 1 means that AA chain is off.
  aAAPos explain which AA sample is generate this renderer. It can have values in range (0, aAALen - 1).
  Total number of samples can be calculated as multiplication of aAALen and number of samples generated by GFX.
  It return StatusCodes error code.
  */
  dvgAPIBase::StatusCodes getAAChain(unsigned int &aAAPos, unsigned int &aAALen);  
  
  /**
  This function return parameters of current Time Division chain.
  aTDLen explain how many time slots are generated into chain. 1 means that time division is off.
  aTDPos explain which time division slot (phase) is generated on this renderer. 
  It can have values in range (0, aTDLen - 1).
  It return StatusCodes error code.
  */
  dvgAPIBase::StatusCodes getTDChain(unsigned int &aTDPos, unsigned int &aTDLen);

  /**
  This function return parameters of current Added Image Division chain.
  aAIDLen explain how many added parts are generated into chain. 1 means that  added image division is off.
  aAIDPos explain which part is generated on this renderer. It can have values in range (0, aAIDLen - 1).
  It return StatusCodes error code.
  */
  dvgAPIBase::StatusCodes getAIDChain(unsigned int &aAIDPos, unsigned int &aAIDLen);  

  /**
  This function return parameters of current Screen Image Division chain.
  aVLen explain how many vertical parts are generated into chain. 1 means that vertical division is off.
  aHLen explain how many horizontal parts are generated into chain. 1 means that horizontal division is off.
  aVPos explain which vertical part is generated on this renderer ( 0 to aVLen - 1).
  aHPos explain which horizontal part is generated on this renderer ( 0 to aHLen - 1).
  It return StatusCodes error code.
  */
  dvgAPIBase::StatusCodes getSIDChain(unsigned int &aHPos, unsigned int &aVPos, unsigned int &aHLen, unsigned int &aVLen);

  /**
  This function return parameters of current Interleaved Image Division chain.
  aIIDLen explain how many vertically interleaved parts are generated into chain. 1 means that interleaved division is off.
  aIIDPos explain which vertical part is generated on this renderer ( 0 to aIIDLen - 1).
  It return StatusCodes error code.
  */
  dvgAPIBase::StatusCodes getIIDChain(unsigned int &aIIDPos, unsigned int &aIIDLen);

  /**
  This function return parameters needed to construct SID projection.
  use getViewportSize() method to get size of the rendering window to be open.
  aTotalWidth and aTotalHeight return size of the whole picture generated into chain.
  aHOffset and aVOffset return offset of the left upper corner from the whole picture to the
  subwindow which is generated by this renderer (as a part of SID chain).
  If SID chain is not active, it return just color viewport size into aTotalWidth and aTotalHeight,
  and 0,0 in aHOffset and aVOffset.
  It return StatusCodes error code.
  */
  dvgAPIBase::StatusCodes getSIDViewportSize(unsigned int &aTotalWidth, unsigned int &aTotalHeight,
                         unsigned int &aHOffset, unsigned int &aVOffset);

  /**
  This function return parameters of current stereo mode (Eye Division mode).
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
  dvgAPIBase::StatusCodes getStereoStatus(bool &aIsStereo, bool &aIsActiveStereo, 
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
  Tiling is used in situation when several separate monitors (projections) make common flat screen.
  Then geometry of tling can be defined into control GUI and application can read those parameters and
  display propert part of picture (tile).
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
  dvgAPIBase::StatusCodes getTileStatus(bool &aIsTiled, AspectCorrections &aAspectCorrection, unsigned &aHorizontalTiles,
                            unsigned &aVerticalTiles, unsigned &aHorizontalPos,
                            unsigned &aVerticalPos, float &aHorizontalMargin,
                            float &aVerticalMargin);

    
  /**
  This method return current rendering group parameters.
  aLength return length of the rendering group 
  (rendering group can be divided for several "chain" channels, check hetChainLength() for your channel info)
  aMyPosition return position into the group, from 0 to aLength - 1.
  This position is related to the physical connections.
  aMasterIp return IP address of the "master" host of this grup. used only for information purposes.
  aSyncIp return IP address of the "synchronisation" host of this grup. used only for information purposes.
  */
  dvgAPIBase::StatusCodes getRenderingGroup(unsigned int &aMyPosition, 
                        unsigned int &aLength,
                        unsigned int &aMasterIp,
                        unsigned int &aSyncIp);

  /**
  This function return number of the computers used in current "chain" channel.
  @param aLength   - return number of the renderers used (1 to the length of rendering group).
  @return  - a StatusCodes error code.
  */
  dvgAPIBase::StatusCodes getChainLength(unsigned int &aLength);
 
  
  /**
  This method modify the projection matrix. It does it in-place. 
  The 16 floats of the matrix are in the same arrangement as returned by 
  glGetFloatv(GL_PROJECTION_MATRIX).
  This matrix can be adjusted  due to antialiasing subpixel shift (based on current AA configuration,
  including all AA chain, TDAA and GFX hardware samples, can be switched on/off from configuration).
  Adjusting due to stereo, SID and IID can be switched on/off from chain configuration.
  Use methods: isProjectionAAApplied(),  isProjectionSIDApplied(), isProjectionIIDApplied(), isProjectionStereoApplied() to get current state.
  It return StatusCodes error code.
  */
  dvgAPIBase::StatusCodes arrangeProjectionMatrix(float aMatrix[16]);

  /**
  This method return current frame rate divider factor.
  1 means that dividing is off.
  Higher values means that swap events frequency on each renderer are divided by this factor.
  It is used in situation when rendering is too heavy to be render in each frame but no additional swap synchornization is used.
  Then it is possible to set some constant, maximum frequency (which is below full framerate frequency).
  It helps to synchronize all renderers in such situation and to have constant framerate, which can be "nicer" in visibility.
  It return StatusCodes error code.
  */
  dvgAPIBase::StatusCodes getFramerateDivider(unsigned int &aFrameRateDivider);

  /**
  This method return true into aFrameRendering parameter when GFX must render full frame,
  and no interlacing is used (output video format can still be interlaced, but no local).
  It is always true for progressive video formats.
  */
  dvgAPIBase::StatusCodes isFrameRendering(bool& aFrameRendering);

  /*
  This methods wait for the next swap on the renderer.
  It returns the common swapcounter for rendering group (in aCount).
  If there is fieldrendering aCounter is also adjusted to polarity of output signal (odd/even value for odd/even field).
  If in time divided chaining, it waits for the correct phase to. 
  If framerate divider is active, it waits for given number of frames also.
  That is - it does not necessarily return after the next 
  50/60 Hz (or other) vsync, but after the one 'assigned' to it (according to its 
  time division chain position and framerate divider).
  aTimeOut parameters can be set with timeout in milliseconds, default is infinite.
  It return StatusCodes error code.
  */
  dvgAPIBase::StatusCodes waitForSwap(unsigned int &aCount, 
                  const unsigned int aTimeOut = INFINITE_TIMEOUT);

  /**
  This function wait for the next sync IRQ on this renderer.
  It returns the common swapcounter rendering group (in aCount). 
  It waits for the real next vsync (50/60 Hz etc.) and doesn't adjust to the chain modes.
  aTimeOut parameters can be set with timeout in miliseconds, default is infinite.
  It return StatusCodes error code.
  */
  dvgAPIBase::StatusCodes waitForRealSwap(unsigned int &aCount, 
                      const unsigned int aTimeOut = INFINITE_TIMEOUT);
    
  
  /*
  This methods wait for the right moment to start rendering.
  In TimeDivision chain mode is not active, it just returns (does nothing).
  In TD chain if TD DFR is activated, it waits for the right moment to start rendering.
  If TD DFR is activated, it MUST be called just after "swap buffers" to have proper behavior.
  Then for all applications which are designated to run with Time division it is recommended to call it
  just before start new frame rendering.
  It returns the common adjusted swapcounter (in aCount).
  aTimeOut parameters can be set with timeout in milliseconds, default is infinite.
  It return StatusCodes error code.
  */
  dvgAPIBase::StatusCodes waitForRender(unsigned int &aCount, 
                    const unsigned int aTimeOut = INFINITE_TIMEOUT);
  

  /**
  This method return current group-adjusted frame counter, related to all
  the chain patrameters (like last waitForSwap() methods return).
  It return StatusCodes error code.
  */
  dvgAPIBase::StatusCodes getSwapCounter(unsigned int &aCount);
  
  /**
  This method return current common absolute swap counter 
  (like last waitForRealSwap() methods return).
  It return StatusCodes error code.
  */
  dvgAPIBase::StatusCodes getRealSwapCounter(unsigned int &aCount);
  
  /** 
  Get both current group-adjusted and/or real (absolute) swap counters.
  Each parameter can be NULL if given counter is not needed.
  It return StatusCodes error code.
  */
  dvgAPIBase::StatusCodes getSwapCounters(unsigned int *aCount, unsigned int *aRealCount);

  /**
  This method return time in microseconds from the last swap IRQ.
  It return StatusCodes error code.
  */
  dvgAPIBase::StatusCodes getTimeFromSwap(unsigned int &aTime);

  /**
  This method return time in microseconds to the next swap IRQ.
  It return StatusCodes error code.
  */
  dvgAPIBase::StatusCodes getTimeToSwap(unsigned int &aTime);

  /**
  This method is used to set compositor API entity, which is used 
  into process (application) which do real rendering and call waitForSwap() periodically.
  For proper working statistics and swap barrier (swap lock) between nodes,
  only one process (per node) can set true here.
  When no chaining and time statistics are used, this settings does not matter.
  By default, after creation of object state is false.
  */
  void setIsRendering(const bool aIsRendering)
    { theIsRendering = aIsRendering; };

  /**
  This method check state of rendering flag, as set into setIsRendering() method.
  */
  bool getIsRendering(void)
    { return theIsRendering; };
 
protected:
 
  virtual dvgAPIBase::StatusCodes opening();
  virtual dvgAPIBase::StatusCodes closing();

  HANDLE theSwapEvent;
  HANDLE theInterruptEvent; 
  volatile DVGSwapCounter *theSwapCounters;

  dvgAPIBase::StatusCodes updateProjectionStatus(void);
  dvgAPIBase::StatusCodes updateChainInfo(void);
  dvgAPIBase::StatusCodes updateSolution(void);
  dvgAPIBase::StatusCodes updateBaseViewportSize(void);
  dvgAPIBase::StatusCodes waitForSwapBarrier(unsigned int &aCount, 
                         const unsigned int aTimeOut = INFINITE_TIMEOUT);

  static const int theMagic[32][32];
  DvgAPIDefs::DVGMultisaplingMode theGFXSamples;
  DvgAPIDefs::DVGChainConfiguration *theChain;
  unsigned theBaseViewport[2];
  unsigned int theTDAA;
  unsigned int theFramerateDivider;
  unsigned int theProjectionFlags;
  DvgAPIDefs::DVGProjectionConfiguration *theProjectionConfig;
  DVGRenderingGroup *theGroup;
  DVGSolution *theFormat;

  __int64 theSwapFinish;
  bool theIsRendering;
  GfxBoardVendor theGfxVendor;
  bool theGFXReal4Samples;

  HANDLE theSwapBarrierReadyEvent;
  HANDLE theSwapBarrierWaitEvent;
  long int theDesktopOffsets[2];
  bool theDesktopOffsetsUpdated;
  class AlphaCopyStruct;
  AlphaCopyStruct *theAlphaCopy;

private:

  /// Do not use copy constructor.
  dvgCompositorAPI(const dvgCompositorAPI &aOther);
  /// Do not use '=' operator.
  dvgCompositorAPI &operator=(const dvgCompositorAPI &aOther);

  };

#endif


