/* 
 * Copyright 2007 Orad Hi-Tec Systems Ltd.
 * ALL RIGHTS RESERVED
 *
 * Filename: DvgAPIDefs.hpp
 */

#ifndef _DVG_A_P_I_DEFS_HPP
#define _DVG_A_P_I_DEFS_HPP

#include <assert.h>

#ifdef __cplusplus

namespace DvgAPIDefs
  {

#endif

  /// Common definition for 64 bits integer number used in API.
  typedef __int64 LongLong;
   
  /// Set of flags used in DVGBoardCapability structure.
  enum DVGBoardCapabilityFlags
    {
    /// Mean that board is initialized (has properly working firmware). If it is not set other fields of DVGBoardCapability are undefined.
    DVG_CAP_INITIALIZED  = 0x00000001,
    /// Mean that board has outputs and possibility to chain with other boards (compositor DVG board).
    DVG_CAP_CHAINING     = 0x00000002,
#ifndef DVGAPI_DISABLE_GRABBER
    /// Mean that board has capability to grab (grabber DVG board).
    DVG_CAP_GRABBING     = 0x00000004,
    /// Mean capability to combine two fields in one frame while grabbing (in hardware).
    DVG_CAP_FRAME_GRABBING = 0x00000008,
    /// Mean capability to grab selected part of field.
    DVG_CAP_PARTIAL_GRABBING = 0x00000010,
    /// Mean possibility to select physical input to grabbed stream.
    DVG_CAP_ROUTE_GRABBING = 0x00000020,
#endif //DVGAPI_DISABLE_GRABBER
    /// Mean that board is able to work as delay board.
    DVG_CAP_FDELAY_BOARD   = 0x00000040,
    /// Mean that board can read full frame from local GFX for each video field.
    DVG_CAP_FRAMERENDERING = 0x00000080,
    /// Mean that board can read full frame from local GFX for each two video fields.
    DVG_CAP_FRAMERENDERING2= 0x00000100,
    /// Mean that board can freeze video frame on input.
    DVG_CAP_FREEZE_GRABBING= 0x00000200,

    };

  /// Used in compositor API functions
  enum DVGAdditiveFunction
    {
    /// Standalone, pure local output.
    DVG_NOT_ADDITIVE = 0,
    /// Blending of GFX and chain signal based on chromakey produced from chain signal (only VRX).
    DVG_ADD_CHROMA_CHAIN,
    /// Blending of GFX and chain signal based on chromakey produced from local GFX signal (only VRX).
    DVG_ADD_CHROMA_GFX,
    /// Blending of GFX and chain signal as simple addition pixel by pixel (only VRX).
    DVG_ADD_BLEND,
    /// Blending of output signal and one of video inputs based on separate alpha from local output (no premultiplication).
    DVG_ADD_OVERLAY,
    /// Blending of output signal and one of video inputs based on chromakey produced from video input signal.
    DVG_ADD_SPORT_CHROMAKEY,
    /// Blending of output signal and one of video inputs based on separate alpha from local output (with premultiplication).
    DVG_ADD_OVERLAY_PREMULT,
    /// Internal value, used for controlling.
    DVG_ADD_FUN_COUNT,
    };

  /// Used in compositor API functions.
  enum DVGGenlockSource
    {
    /// No genlock used, freerun.
    DVG_GENLOCK_SOURCE_NONE         = 0,
    /// Analog blackburst or trilevel sync (on video boards), analog 3.3V TTL sync (on VRX).
    DVG_GENLOCK_SOURCE_ANALOG,
    /// Digital SDI sync (on video boards), DVI input sync (on VRX).
    DVG_GENLOCK_SOURCE_DIGITAL,
    /// Internal value, used for controlling.
    DVG_GENLOCK_SOURCE_COUNT,
    };

  /// Used in compositor and grabber API functions.
  enum DVGVideoStandard
    {
    /// Standard Definition video (HDVG).
    DVG_VIDEO_SD,
    /// High Definition video (HDVG).
    DVG_VIDEO_HD,
    /// RGB video out, variable resolutions (VRX).
    DVG_VIDEO_VGA,
    };

  /**
  Video formats
  1035i - 1920x1035 interlaced
  1080i - 1920x1080 interlaced
  1080p - 1920x1080 progressive scan
  720p - 1280x720 progressive scan
  */

  /// Used in compositor and grabber API functions.
  enum DVGGraphicsMode
    {
    /// Standard definition PAL, 720x576 interlaced, 25 Hz
    DVG_SD_PAL                  = 0,
    /// Standard definition NTSC, 720x486 interlaced, (30/1.001) Hz
    DVG_SD_NTSC                 = 1,
    /// Standard definition NTSC narrow blanking, 720x506 interlaced, (30/1.001) Hz
    DVG_SD_NTSC_NARROW          = 22,
    /// High Definition, 1920x1035 interlaced, 30Hz (A)
    DVG_HD_SMPTE260_30I         = 2,
    /// High Definition, 1920x1035 interlaced, (30/1.001) Hz (B)
    DVG_HD_SMPTE260_29I         = 3,
    /// High Definition, 1920x1080 interlaced, 25 Hz (C)
    DVG_HD_SMPTE295_25I         = 4,
    /// High Definition, 1920x1080 interlaced, 30 Hz (D)
    DVG_HD_SMPTE274_30I         = 5,
    /// High Definition, 1920x1080 interlaced, (30/1.001) Hz (E)
    DVG_HD_SMPTE274_29I         = 6,
    /// High Definition, 1920x1080 interlaced, 25 Hz (F)
    DVG_HD_SMPTE274_25I         = 7,
    /// High Definition, 1920x1080 progressive, 30 Hz (G)
    DVG_HD_SMPTE274_30P         = 8,
    /// High Definition, 1920x1080 progressive, (30/1.001) Hz (H)
    DVG_HD_SMPTE274_29P         = 9,
    /// High Definition, 1920x1080 progressive, 25 Hz (I)
    DVG_HD_SMPTE274_25P         = 10,
    /// High Definition, 1920x1080 progressive, 24 Hz (J)
    DVG_HD_SMPTE274_24P         = 11,
    /// High Definition, 1920x1080 progressive, (24/1.001) Hz (K)
    DVG_HD_SMPTE274_23P         = 12,
    /// High Definition, 1280x720 progressive, 60 Hz (L)
    DVG_HD_SMPTE296_60P         = 13,
    /// High Definition, 1280x720 progressive, (60/1.001) Hz (M)
    DVG_HD_SMPTE296_59P         = 14,
    /// High Definition, 1280x720 progressive, 50 Hz
    DVG_HD_SMPTE296_50P         = 15,
    /// High Definition, 1280x720 progressive, 30 Hz
    DVG_HD_SMPTE296_30P         = 16,
    /// High Definition, 1280x720 progressive, (30/1.001) Hz
    DVG_HD_SMPTE296_29P         = 17,
    /// High Definition, 1280x720 progressive, 25 Hz
    DVG_HD_SMPTE296_25          = 18,
    /// High Definition, 1280x720 progressive, 24 Hz
    DVG_HD_SMPTE296_24          = 19,
    /// High Definition, 1280x720 progressive, (24/1.001) Hz
    DVG_HD_SMPTE296_23          = 20,

    /// Variable resolution RGB VGA output used by VRX boards
    DVG_VR_CUSTOM               = 21,
    
    /// Internal value, used for controlling.
    DVG_GRAPHICS_MODE_COUNT = 23,

    /// Aliases for some HD modes.
    DVG_HD_1035I = DVG_HD_SMPTE260_29I,
    DVG_HD_1080I = DVG_HD_SMPTE274_29I,
    DVG_HD_1080P = DVG_HD_SMPTE274_29P,
    DVG_HD_1080P_25 = DVG_HD_SMPTE274_25P,
    DVG_HD_24P = DVG_HD_SMPTE274_23P,
    DVG_HD_720P = DVG_HD_SMPTE296_59P,
    DVG_HD_720P_50 = DVG_HD_SMPTE296_50P,
    DVG_HD_720P_30 = DVG_HD_SMPTE296_30P,
    DVG_HD_720P_29 = DVG_HD_SMPTE296_29P,
    DVG_HD_720P_25 = DVG_HD_SMPTE296_25,
    DVG_HD_720P_24 = DVG_HD_SMPTE296_24,
    DVG_HD_720P_23 = DVG_HD_SMPTE296_23,

    /// Binary flags with all High Definition modes set.
    DVG_HD_FORMATS_FLAGS = ((1 << DVG_VR_CUSTOM) - 1) & ~((1 << DVG_SD_PAL) | (1 << DVG_SD_NTSC)),
    /// Binary flags with all Standard Definition modes set.
    DVG_SD_FORMATS_FLAGS = ((1 << DVG_SD_PAL) | (1 << DVG_SD_NTSC) | (1 << DVG_SD_NTSC_NARROW)),
    /// Binary flags with all Progressive Video modes set.
    DVG_PROGRESSIVE_FORMATS_FLAGS = 0x003FFF00,
    /// Binary flags with all Progressive Video modes set, second part for use with 64 bits values.
    DVG_PROGRESSIVE_FORMATS_FLAGS2 = 0x00000000,
    };

  /// Used in Base API functions for write messages.
  enum DVGDebugCategory
    {
    /// Message category for critical events.
    DVG_DBG_CRITICAL        = 0,
    /// Message category for error events.
    DVG_DBG_ERROR,
    /// Message category for warnings.
    DVG_DBG_WARNING,
    /// Message category for user level informations.
    DVG_DBG_INFO,
    /// Message category for low level / debug informations.
    DVG_DBG_DEBUG,
    /// Value used for message filtering.
    DVG_DBG_OFF,
    /// Internal value, used for controlling.
    DVG_DBG_COUNT = DVG_DBG_OFF,
    };

#ifndef DVGAPI_DISABLE_GRABBER
  /// Used in DVGVideoInputCapability structure.
  enum DVGVideoInputCapabilityFlags
    {
    /// Mean that may be used as standalone color. If not set, can be used only as a slave in aggregation with other input.
    VIDIN_CAP_SINGLE_INPUT   = 0x00000001,
    /// Mean that may be configured to produce alpha from image color.
    VIDIN_CAP_CHROMA_KEY     = 0x00000002,
    };
#endif //DVGAPI_DISABLE_GRABBER

#ifndef DVGAPI_DISABLE_GRABBER
  /// Used in grabber API functions
  enum DVGPixelFormat
    {
    /// Special value used to reset pixel format of specified video input stream to global value.
    DVG_PIXEL_GLOBAL = -1,
    /// Lumination (Y) as 8 bit value per pixel. Used on specific hardware only.
    DVG_PIXEL_MONOCHROME = 0,
    /// RGB 32-bit per pixel, as in OGL GL_BGRA_EXT format. 8 bits per component. Order: 'B' 'G' 'R' 'A'. 'A' channel used only when activated.
    DVG_PIXEL_RGBA = 1,
    /// Alias name for compatibility.
    DVG_PIXEL_RGB = DVG_PIXEL_RGBA,
    /// YUV 32-bit per pixel. 8 bit per component. Order: 'Y' 'V' 'U' 'empty'.
    DVG_PIXEL_YUV32 = 4,
    /// The same as DVG_PIXEL_RGBA, but with Y from YUV input signal instead of 'A'.
    DVG_PIXEL_RGBY = 5,
    /// RGB 24-bit per pixel, as in OGL GL_BGR_EXT format. 8 bits per component. Order: 'B' 'G' 'R'. Used on specific hardware only.
    DVG_PIXEL_RGB24 = 6,
    };
#endif //DVGAPI_DISABLE_GRABBER

#ifndef DVGAPI_DISABLE_GRABBER
  /// Flags used into grabber API
  enum DVGImageCompressionFlags
    {
    /// Means that incoming video signal can be compressed using S3TC alorithm into the hardware.
    DVG_IMAGE_COMPRESSION_S3TC_FLAG            = 0x00000001,
    /// Alias flag for different name (DXT5) of the S3TC compresion
    DVG_IMAGE_COMPRESSION_DXT5_FLAG = DVG_IMAGE_COMPRESSION_S3TC_FLAG,
    /// Means that incoming video signal can be scaled by 2 in vertical direction into the hardware.
    DVG_IMAGE_COMPRESSION_HALF_VERTICAL_FLAG   = 0x00000002,
    /// Means that incoming video signal can be scaled by 2 in horizontal direction into the hardware.
    DVG_IMAGE_COMPRESSION_HALF_HORIZONTAL_FLAG = 0x00000004,
    };
#endif //DVGAPI_DISABLE_GRABBER

#ifndef DVGAPI_DISABLE_GRABBER
  /// Used in grabber API functions.
  enum DVGGrabbingState
    {
    /// Means that grabbing process is in progress.
    DVG_GRABBING_STARTED = 0,
    /// Means that grabbing process is not active (stopped).
    DVG_GRABBING_STOPPED,
    /// Means that grabbing process is not prepared (configured).
    DVG_GRABBING_NOT_INITIALIZED,
    };
#endif //DVGAPI_DISABLE_GRABBER

#ifndef DVGAPI_DISABLE_GRABBER
  /// Used in grabber API functions
  enum DVGFieldPolarity
    {
    /// Means that it is odd field into interlaced format.
    DVG_FIELD_ODD = 0,
    /// Means that it is even field into interlaced format.
    DVG_FIELD_EVEN = 1,
    /// Means that it is frame into progressive or sequential fields format (whole picture sampled in the same time).
    DVG_FRAME = 2,
    /// Means frame combined from two fields, odd first, then even.
    DVG_FRAME_ODD_EVEN = 3,
    /// Means frame combined from two fields, even first, then odd.
    DVG_FRAME_EVEN_ODD = 4,
    };
#endif //DVGAPI_DISABLE_GRABBER

  /// used in Output Control API functions
  enum DVGOutputSource
    {
    /// Physical input 0 connector.
    DVG_OUTPUT_INPUT_0      = 0,
    /// Physical input 1 connector.
    DVG_OUTPUT_INPUT_1      = 1,
    /// Physical input 2 connector.
    DVG_OUTPUT_INPUT_2      = 2,
    /// Physical input 3 connector.
    DVG_OUTPUT_INPUT_3      = 3,
    /// Physical input 4 connector.
    DVG_OUTPUT_INPUT_4      = 4,
    /// Physical input 5 connector.
    DVG_OUTPUT_INPUT_5      = 5,
    /// Physical input 6 connector.
    DVG_OUTPUT_INPUT_6      = 6,
    /// Physical input 7 connector.
    DVG_OUTPUT_INPUT_7      = 7,
    /// Internal frame delay output.
    DVG_OUTPUT_FDELAY       = 12,
    /// Internal test signal source.
    DVG_OUTPUT_TEST_SIGNAL  = 16,
    /// Output from internal mixer (usual final signal color).
    DVG_OUTPUT_MIXER         = 24,
    /// Output from internal mixer compound alpha (usual final signal alpha).
    DVG_OUTPUT_MIXER_ALPHA    = 25,
    /// Foreground color signal coming to internal mixer.
    DVG_OUTPUT_MIXER_FG       = 26,
    /// Chromakey alpha signal produced into mixer from foreground color.
    DVG_OUTPUT_MIXER_CHROMAKEY = 27,
    /// Background color signal coming to internal mixer (usually from GFX).
    DVG_OUTPUT_MIXER_BG       = 28,
    /// Background alpha signal coming to internal mixer (usually from GFX).
    DVG_OUTPUT_MIXER_BG_ALPHA = 29,
    /// Internal mixer test signal.
    DVG_OUTPUT_MIXER_TEST     = 30,
    /// Foreground alpha signal coming to internal mixer.
    DVG_OUTPUT_MIXER_FG_ALPHA = 31,
    };


  /// Used in DVGInputCapability structure.
  enum DVGInputType
    {
    /// RGB DVI signal input, in some hardware can be used also as digital genlock source.
    DVG_INPUT_TYPE_DVI = 0,
    /// HD or SD SDI video input.
    DVG_INPUT_TYPE_SDI,
    /// Analog composite video input.
    DVG_INPUT_TYPE_COMPOSITE,
    /// Analog video genlock input (blackburst, trilevel sync on HD).
    DVG_INPUT_TYPE_GENLOCK_ANALOG,
    /// Digital video genlock input.
    DVG_INPUT_TYPE_GENLOCK_DIGITAL,
    /// TTL 3.3 V input genlock used as 'analog' into VRX board.
    DVG_INPUT_TYPE_GENLOCK_TTL,
    };

  /// Used in DVGInputState structure and input control API functions.
  enum DVGInputStateFlags
    {
    /// Means that properly synchronized signal was recognized (not all inputs has capability to recognize).
    DVG_INPUT_STATE_INSYNC = 0x00000001,
    };

  /// Used in DVGBoardCapability struct.
  enum DVGChainMode
    {
    /// Antialiasing chain mode.
    DVG_CHAIN_AA  = 0,
    /// Interleaved Image Division chain mode.
    DVG_CHAIN_IID,
    /// Horizontal Screen Image Division chain mode.
    DVG_CHAIN_SIDH,
    /// Vertical Screen Image Division chain mode.
    DVG_CHAIN_SIDV,
    /// Time Division chain mode.
    DVG_CHAIN_TD,
    /// Eye Division chain mode (active stereo).
    DVG_CHAIN_ED,
    /// Added Image Division chain mode.
    DVG_CHAIN_AID,
    /// Reserved.
    DVG_CHAIN_SPARE_0,
    /// Reserved.
    DVG_CHAIN_SPARE_1,
    /// Reserved.
    DVG_CHAIN_SPARE_2,
    /// Internal value.
    DVG_CHAIN_MODE_COUNT,
    };

  /// Used in base API functions.
  struct DVGBoardCapability
    {
    /// Structure version. Below definition is up to version 2.
    int theVersion;
    /// Binary set of DVGBoardCapabilityFlags.
    unsigned int theCapabilityFlags;
    /// Array of each of defined DVGChainMode, define maximum length of give chain mode. If <= 1 means that mode is not supported.
    unsigned int theMaxChainLen[DVG_CHAIN_MODE_COUNT];
    /// Binary set of DVGAdditiveFunction flags, defines supported functions.
    unsigned int theAdditiveFunctionFlags;
    /// Binary set of DVGGraphicsMode flags, defines supported formats.
    LongLong theVideoFormatsFlags;
    /// Number of input connectors.
    unsigned int theNumOfInputConnectors;
#ifndef DVGAPI_DISABLE_GRABBER
    /// Number of video streams possible to grab concurrently.
    unsigned int theNumOfVideoInStreams;
    /// Binary set of DVGPixelFormat flags, defines supported grabber pixel formats.
    unsigned int thePixelFormatFlags;
    /// Binary set of DVGImageCompressionFlags, defines supported grabber compression formats.
    unsigned int theImageCompressionFlags;
#endif //DVGAPI_DISABLE_GRABBER
#ifdef DVGAPI_DISABLE_GRABBER
    /// Reserved.
    unsigned int pads1[3];
#endif //DVGAPI_DISABLE_GRABBER

    /// Number of output connectors, valid for theVersion >= 1.
    unsigned char theNumberOfOutputs;
    /// Number of supported delay units, valid for theVersion >= 1.
    unsigned char theDelayUnits;
    /// Reserved.
    unsigned char pads0[2];
    /// Binary set of DVGGenlockSource flags, defines supported sync sources, valid for theVersion >= 2.
    unsigned int theGenlockSourcesFlags;
    /// Reserved.
    unsigned int pads[4];

#ifdef __cplusplus
    /// Helper function, return true if board is working and all fields in this structure are properly filled.
    bool isInitialized(void) const
      { return (theCapabilityFlags & DVG_CAP_INITIALIZED) != 0; }
    /// Helper function, return true if board is a compositor (has outputs and eventually can be used in chain).
    bool isCompositor(void) const
      { return ((theCapabilityFlags & (DVG_CAP_INITIALIZED | DVG_CAP_CHAINING)) == (DVG_CAP_INITIALIZED | DVG_CAP_CHAINING)); };
#ifndef DVGAPI_DISABLE_GRABBER
    /// Helper function, return true if board is a grabber (can grab input to memory buffer).
    bool isGrabber(void) const
      { return ((theCapabilityFlags & (DVG_CAP_INITIALIZED | DVG_CAP_GRABBING)) == (DVG_CAP_INITIALIZED | DVG_CAP_GRABBING)); };
#endif //DVGAPI_DISABLE_GRABBER
    /// Helper function, return true if board support Standard Definition video modes (PAL/NTSC).
    bool isSD(void) const
      { return (isInitialized() && ((theVideoFormatsFlags & DVG_SD_FORMATS_FLAGS) != 0)); };
    /// Helper function, return true if board support High Definition video modes.
    bool isHD(void) const
      { return (isInitialized() && ((theVideoFormatsFlags & DVG_HD_FORMATS_FLAGS) != 0)); };
    /// Helper function, return true if board support variable resolution RGB, VGA output modes.
    bool isVR(void) const
      { return (isInitialized() && ((theVideoFormatsFlags & DVG_VR_CUSTOM) != 0)); };
#endif
    };

 
  /// Used in output control API functions
  struct DVGVideoOutputCapability
    {
    /// Structure version. Below definition is up to version 0.
    unsigned int theVersion;
    /// Size of structure in bytes, can depends of version.
    unsigned int theStructSize;
    /// Output capability flags, currently no flags defined.
    unsigned int theCapabilityFlags;
    /// Binary set of DVGOutputSource flags, defines supported sources for this output.
    unsigned int theSupportedSources;
    };

  
#ifndef DVGAPI_DISABLE_GRABBER
  /// Used in grabber API functions.
  struct DVGVideoInputCapability
    {
    /// Structure version. Below definition is up to version 1.
    int theVersion;
    /// if >= 0 dual link is possible to set with theAlphaChannel videoin
    int theAlphaChannelInputIndex;
    /// Binary set of DVGVideoInputCapabilityFlags.
    unsigned int theCapabilityFlags;
    /// Binary set of DVGPixelFormat flags, defines supported pixel formats possible to set per video input.
    unsigned int thePixelFormatFlags;
    /// Binary set of DVGImageCompressionFlags, defines compressions possible to set per video input.
    unsigned int theImageCompressionFlags;
    /// Reserved.
    unsigned int pads;
    /// Size of structure in bytes, can depends of version, valid for theVersion >= 1.
    unsigned int theStructSize;
    };
#endif //DVGAPI_DISABLE_GRABBER

#ifdef __cplusplus
  /// Used in input control API functions.
  struct DVGInputCapability
    {
    /// Structure version. Below definition is up to version 0.
    int theVersion;
    /// Size of structure in bytes, can depends of version.
    unsigned int theStructSize;
    /// Input capability flags, currently no flags defined.
    unsigned int theCapabilityFlags;
    /// Electrical type of input, as defined in DVGInputType.
    DVGInputType theType;
    };
#endif

  /// Used in input control API functions.
  struct DVGInputState
    {
    /// Structure version. Below definition is up to version 0.
    int theVersion;
    /// Size of structure in bytes, can depends of version.
    unsigned int theStructSize;
    // Binary set of DVGInputStateFlags, defines current state of given input.
    unsigned int theStateFlags;
    };

  /// Used in compositor API functions.
  enum DVGMultisaplingMode
    {
    /// No antialiasing, 1 sample per pixel.
    MS_1_SAMPLE = 1,
    /// Multisample antialiasing with 2 samples per pixel.
    MS_2_SAMPLES = 2,
    /// Multisample antialiasing using Quinqunx algorithm, supported only on some NV GFX from driver 5X.XX and up.
    MS_QUINQUNX = 3,
    /// Multisample antialiasing with 4 samples per pixel.
    MS_4_SAMPLES = 4,
    /// Mixed antialiasing made by 2x supersampling of 2 samples per pixel, supported only on some NV GFX and D3D only from driver 5X.XX and up.
    MS_4S_SAMPLES = 5,
    /// Multisample antialiasing with 6 samples per pixel (on ATI) or mixed mode by 1.5x2 supersampling of 2 samples per pixel (on some NV and D3D only from driver 5X.XX and up).
    MS_6_SAMPLES = 6,
    /// Mixed antialiasing made by 1.5x supersampling of 4 samples per pixel, supported only on some NV GFX and D3D only from driver 5X.XX and up.
    MS_6Q_SAMPLES = 7,
    /// Mixed antialiasing made by 2x2 supersampling of 2 samples per pixel, supported only on some NV GFX from driver 5X.XX and up.
    MS_8S_SAMPLES = 8,
    /// Mixed antialiasing made by 2x supersampling of 4 samples per pixel, supported only on some NV GFX from driver 5X.XX and up.
    MS_8Q_SAMPLES = 9,
    /// Multisample antialiasing using 9xTap algorithm (similar to 4 samples, but blurred), supported only on some NV GFX from driver 5X.XX and up.
    MS_4x9TAP_SAMPLES = 10,
    /// Mixed antialiasing made by 2x2 supersampling of 4 samples per pixel, supported only on some NV GFX from driver 5X.XX and up.
    MS_16S_SAMPLES = 16,
    };

  /// Used in base API functions.
  enum StatsCategories
    {
    /// Statistics category which measure rendering time (between releasing from swap to call of next waitForSwap() ).
    SC_RENDERING = 0,
    /// Statistics category which measure time application spend in wglSwapBuffers() function (works only when GL wrapper is used).
    SC_SWAP_BUFFERS,
    /// Statistics category which measure time application spend in glfinish() function (works only when GL wrapper is used).
    SC_GL_FINISH,
    /// Statistics category which measure time application spend in waitForSwap() function.
    SC_WAIT_FOR_SWAP,
    /// Statistics category which measure time application spend in swap barrier synchronisation (works only when swap barrier function is activated).
    SC_WAIT_FOR_SWAP_BARRIER,
    /// Statistics category which can be used by user application.
    SC_USER_0,
    /// Statistics category which can be used by user application.
    SC_USER_1,
    /// Statistics category which can be used by user application.
    SC_USER_2,
    /// Statistics category which can be used by user application.
    SC_USER_3,
    /// Statistics category which can be used by user application.
    SC_USER_4,
    /// Statistics category which can be used by user application.
    SC_USER_5,
    /// Statistics category which can be used by user application.
    SC_USER_6,
    /// Internal value, used for controlling. Not used as statistics category.
    MAX_STATS_CATEGORIES,
    };

  /// Used in ChromakeyColor structure.
  enum ColorSpace
    {
    /// Define RGB color space.
    COLOR_SPACE_RGB = 0,
    /// Define HSV color space.
    COLOR_SPACE_HSV,
    };

  /// Used in compositor API functions.
  enum ColorComponent
    {
    /// Define red component in RGB color space.
    COLOR_R = 0,
    /// Define green component in RGB color space.
    COLOR_G,
    /// Define blue component in RGB color space.
    COLOR_B,
    /// Define hue component in HSV color space.
    COLOR_H,
    /// Define saturation component in HSV color space.
    COLOR_S,
    /// Define value component in HSV color space.
    COLOR_V,
    };

#ifdef __cplusplus
  /// Used in compositor API functions.
  struct ChromakeyColor
    {
    /// Color space currently stored in below union.
    ColorSpace theColorSpace;
    
    union
      {
      /// Define RGB color, components are in range [0,64k).
      struct
        {
        unsigned short theR;
        unsigned short theG;
        unsigned short theB;
        } theRGB;
      /// Define HSV color, components are in range [0,64k).
      struct
        {
        unsigned short theH;
        unsigned short theS;
        unsigned short theV;
        } theHSV;
      };
    };

  /// Used in compositor API functions.
  struct ChromakeyTable
    {
    enum
      {
      CHROMAKEY_TABLE_SIZE = 512,
      CHROMAKEY_NUMBER_OF_POINTS = 32,
      };
    enum Type
      {
      POINTS = 0,
      TABLE,
      } theType;
    struct Point
      {
      unsigned short theIndex;
      ///values are in range [0;64k)
      unsigned short theValue;
      };
    union
      {
      ///values are in range [0;64k)
      unsigned short theTable[CHROMAKEY_TABLE_SIZE];
      Point thePoints[CHROMAKEY_NUMBER_OF_POINTS];
      };
    };
#endif

#ifdef __cplusplus
  }
#endif

#endif