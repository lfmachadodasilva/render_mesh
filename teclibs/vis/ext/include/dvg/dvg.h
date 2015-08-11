#ifndef __DVG_H
#define __DVG_H

#ifdef __cplusplus
extern "C" {
#endif

#define DVG_VID_PAL                      1
#define DVG_VID_NTSC                     0

#define DVG_HD_NONE                      0
#define DVG_HD_1080I                     5 /*E*/
#define DVG_HD_SMPTE274_29I              5 /*E*/
#define DVG_HD_1035I                     2 /*B*/
#define DVG_HD_SMPTE260_29I              2 /*B*/
#define DVG_HD_720P                     13 /*M*/
#define DVG_HD_SMPTE296_59P             13 /*M*/
#define DVG_HD_24P                      11 /*K*/
#define DVG_HD_SMPTE274_23P             11 /*K*/
#define DVG_HD_SMPTE260_30I              1 /*A*/
#define DVG_HD_SMPTE295_25I              3 /*C*/
#define DVG_HD_SMPTE274_30I              4 /*D*/
#define DVG_HD_SMPTE274_25I              6 /*F*/
#define DVG_HD_SMPTE274_24P             10 /*J*/
#define DVG_HD_SMPTE274_30P              7 /*G*/
#define DVG_HD_SMPTE274_29P              8 /*H*/
#define DVG_HD_1080P                     8 /*H*/
#define DVG_HD_SMPTE274_25P              9 /*I*/
#define DVG_HD_1080P_25                  9 /*I*/
#define DVG_HD_SMPTE296_60P             12 /*L*/


#define DVG_HD_HFILT_NONE                0
#define DVG_HD_HFILT_MED                 1
#define DVG_HD_HFILT_LOW                 2


#define DVG_VIDIN_MODE_IGNORE            0
#define DVG_VIDIN_MODE_OVERLAY           1
#define DVG_VIDIN_MODE_UNDERLAY          2
#define DVG_VIDIN_MODE_CHAIN_AA          3
#define DVG_VIDIN_MODE_CHAIN_Z16         4
#define DVG_VIDIN_MODE_CHAIN_AA_AND_MIX  5

#define DVG_CHAIN_AA_MODE_FIRST          0
#define DVG_CHAIN_AA_MODE_MIDDLE         1
#define DVG_CHAIN_AA_MODE_LAST_OF_2      2
#define DVG_CHAIN_AA_MODE_LAST_OF_3      3
#define DVG_CHAIN_AA_MODE_LAST_OF_4      4

#define DVG_CHAIN_AA_NOMS                (1<<8)

#define DVG_GENLOCK_SOURCE_NONE          0
#define DVG_GENLOCK_SOURCE_ANALOG        1
#define DVG_GENLOCK_SOURCE_DIGITAL       2
#define DVG_GENLOCK_SOURCE_DIGITAL_2     3

#define DVG_MULTIAA_DUAL                 0
#define DVG_MULTIAA_DUAL_FILT            1
#define DVG_MULTIAA_TRIPLE               8
#define DVG_MULTIAA_TRIPLE_FILT          9

#define DVG_COLORFILTER_NONE             0
#define DVG_COLORFILTER_2TAP             1
#define DVG_COLORFILTER_3TAP             2

#define DVG_SRC_GFX_COLOR                0
#define DVG_SRC_GFX_ALPHA                1
#define DVG_SRC_MIX_OUTPUT               2
#define DVG_SRC_INPUT_1                  3
#define DVG_SRC_INPUT_2                  4
#define DVG_SRC_CKEY_PROC_FG             5
#define DVG_SRC_CKEY_ALPHA               6
#define DVG_SRC_CKEY_GFX_ALPHA           7

#define DVG_VIDIN_PIXELFORMAT_RGB        1
#define DVG_VIDIN_PIXELFORMAT_RGBA       2
#define DVG_VIDIN_PIXELFORMAT_I          3
#define DVG_VIDIN_PIXELFORMAT_IA         4
#define DVG_VIDIN_PIXELFORMAT_UYVY       5
#define DVG_VIDIN_PIXELFORMAT_UYAVYA     6

#define DVG_VIDIN_UNIT_ANALOG            1
#define DVG_VIDIN_UNIT_DIGITAL_MAIN      2
#define DVG_VIDIN_UNIT_DIGITAL_GRABONLY  3
#define DVG_VIDIN_UNIT_AGRAB             4


#define DVG_VGA_NON_COMPOSITE_SYNC       (1<<6)
#define DVG_DVI_OUT                      (1<<5)
#define DVG_VGA_VSYNC_ACTIVE_LOW         (1<<4)
#define DVG_VGA_HSYNC_ACTIVE_LOW         (1<<3)
#define DVG_VGA_SYNC_ON_GREEN            (1<<2)
#define DVG_VGA_TEST_PATTERN             (1<<1)
#define DVG_VGA_RESERVED0                (1<<0)

#define DVG_IMAGE_SPLIT                  0
#define DVG_IMAGE_INTERLEAVED            1

#define DVG_STEREO_RIGHT                 0
#define DVG_STEREO_LEFT                  1

#define DVG_PROC_MODE_ALPHA_BLEND        0
#define DVG_PROC_MODE_ALPHA_BLEND_FULL   1
#define DVG_PROC_MODE_MAX                2

#define DVG_ERR_NO_ERROR                 0
#define DVG_ERR_ILLEGAL_OBJECT           1
#define DVG_ERR_RANGE                    2
#define DVG_ERR_CAPABILITY               3
#define DVG_ERR_BROKEN                   4
#define DVG_ERR_IN_USE                   5

#define DVG_OK                           DVG_ERR_NO_ERROR

#define DVG_ON                           1
#define DVG_OFF                          0
#define DVG_AUTO                         9998

typedef void *DVG;


// ========================================================================   Vidin Structures =

// ------------------------------------------------------------------------ DvgVidinUnitConfig -

typedef struct {
    int         id;                      // id of this config
    int         numDigitalColorInputs;   // number of digital (D1) color input paths.
                                         // Color meaning RGB without alpha.
                                         // Each such input requires 1 connector
    int         numDigitalDualInputs;    // number of digital (D1) dual input paths.
                                         // Meaning "4:2:2:4" and RGBA in memory.
                                         // This takes up two physical BNC input connectors. 
    int         numAnalogRGBInputs;      // Number of analog component RGB inputs
    int         numAnalogCompositeInputs;// Number of analog component RGB inputs
    int         prohibitsMixing;         // If set to 1, it means that using this config
                                         // will make mixing operation impossible.
                                         // Of course, this applies only to the "main DVG board"
                                         // VidinUnit. 
    int         prohibitsChaining;       // If set to 1, it means that using this config
                                         // will make chaining operation impossible.
                                         // Of course, this applies only to the "main DVG board"
                                         // VidinUnit.  
    char        *verbalDescription;      // A human-readable description of this config
    int         numDigitalCKeyInputs;    // channels with their chromakey alpha attached
    int         numAnalogMonochromeInputs;
    char        reservedForFutureUse[120];  // future additions shouldn't break old code
    } DvgVidinUnitConfig;


// ----------------------------------------------------------------- DvgVidinUnitInputParams -

typedef struct {
    int         width, height;          // width and height of image in memory.
                                        // This means hardware scaling.
    int         pixelFormat;            // Previously known to VL users as pixel packing.
                                        // One of DVG_VIDIN_PIXELFORMAT_ constants.
    int         withMipmap;             // The hardware will compute mipmap levels for
                                        // tri-linear filtered video-to-texture.
    int         mipmapLevels;           // The number of mipmap levels.
                                        // This will probably be more of a returned value
                                        // then a requested value.  
    int         interlaced;             // The h/w will provide interlaced video
    int         compressed;             // The h/w will compress in S3TC (DXT5) format
    char        reservedForFutureUse[124];  // future additions shouldn't break old code
    }  DvgVidinUnitInputParams;

typedef struct {
    unsigned long long dma_start_tick;
    unsigned long long dma_end_tick;
    unsigned long dma_count;
    int boardIdentifier;
    } DvgInputFieldExtendedInfo ;
// ===========================================================================   Prototypes =

void dvgPerror(char *msg,int ec) ;
int dvgSetBasicVideoMode(DVG _dvg, int mode) ;
int dvgSetVideoInputMode(DVG _dvg, int mode) ;
int dvgSetHighDefMode(DVG _dvg, int mode) ;
int dvgSetOutputFormat(DVG _dvg, float framerate,
        int hactive, int hsync_start, int hsync_end, int htotal,
        int vactive, int vsync_start, int vsync_end, int vtotal,   int flags);
int dvgSetOutputTestPattern(DVG _dvg, int number);
int dvgSetNarrowBlanking(DVG _dvg, int mode) ;
int dvgSetFrameRendering(DVG _dvg, int mode) ;
int dvgSetAntiFlickerFilter(DVG _dvg, int mode) ;
int dvgSetAntiAliasFilter(DVG _dvg, int mode) ;
int dvgSetAntiAlias2Filter(DVG _dvg, int mode) ;
int dvgSetAntiAliasMultiFilter(DVG _dvg, int mode, int type) ;
int dvgSetStabilizeFilter(DVG _dvg, int mode) ;
int dvgSetKeyGenerateMask(DVG _dvg, int mode) ;
int dvgSetGraphicsAlpha(DVG _dvg, int mode);
int dvgSetMixerNegateKey(DVG _dvg, int mode) ;
int dvgSetAAChainLengthAndPos(DVG _dvg, int len, int pos) ;
int dvgSetMultiplexChainLengthAndPos(DVG _dvg, int len, int pos);
int dvgSetImageChainLengthAndPos(DVG _dvg, int len,int pos, int type,int x,int y);
int dvgSetStereoChainPos(DVG _dvg,int pos);
int dvgSetProcessingChainTypeAndPosAndLen(DVG _dvg, int type,int pos,int len);
int dvgSetChannelNumber(DVG _dvg, int pos);
int dvgSetChainLength(DVG _dvg, int len);
int dvgSetVSyncOutput(DVG _dvg, int mode);

int dvgSetGenlockSource(DVG _dvg, int src) ;
int dvgSetHDHfilt(DVG _dvg, int mode) ;
int dvgSetKeyGenerateMaskCenter(DVG _dvg, unsigned char *color) ;
int dvgSetKeyGenerateMaskRange(DVG _dvg, unsigned char *color) ;
int dvgSetKeyGenerateMaskFalloff(DVG _dvg, unsigned char *color) ;
int dvgSetColorSubsampleFilter(DVG _dvg, int type);
int dvgSetPreMultipliedMix(DVG _dvg, int mode);
int dvgSetOutputSelection(DVG _dvg, int out1, int out2);
int dvgSetEarlyInterrupt(DVG _dvg, float preTime);
int dvgSetNVmultisamplingHint(DVG _dvg, int samples);
int dvgGetVDI(DVG _dvg, int *in1, int *in2, unsigned int *vitc);
int dvgSetWatchDog(DVG _dvg, int mode, int fields);
int dvgSetFramedelay(DVG _dvg, int swControl, int numFrames);

int dvgGetWindowSize(DVG _dvg, int *w,int *h) ;
int dvgGetColorWindowPosition(DVG _dvg, int *x,int *y);
int dvgGetMaskWindowPosition(DVG _dvg, int *x,int *y);

int dvgGetGeometry(DVG _dvg, int *totalWidth,int *totalHeight,int *positionX,int *positionY,
        int *basicWidth,int *basicHeight,
        int *numColorViewports, int *numMaskViewports,
        int (*viewportGeom)[4]);

int dvgGetStatus(DVG _dvg, int *boardType, int *version, int *frameLocked,
        int *digital_1_present,
        int *analogGenlockPresent,
        int *digital_2_present);

int dvgGetHWstring(DVG _dvg, char **str);

char *dvgGetLibraryVersionString(DVG _dvg);
int dvgGetGraphicsDetails(DVG _dvg,int *vendor,int *device,int *subVendor,int *subDevice, int *glVersion);

int dvgArrangeProjectionMatrix(DVG _dvg, float m_[16],int field,int viewport);

int dvgGetFramelockState(DVG _dvg,int *locked_,int *dir_);
int dvgGetFramelockState2(DVG _dvg,int *locked_,int *dir_);
int dvgGetFieldPolarity(DVG _dvg, int *polarity);
int dvgHelpFramelock(DVG _dvg);

int dvgSetSwapBarrier(DVG _dvg, int mode);
int dvgWaitForSwap(DVG _dvg, unsigned int *count);
int dvgWaitForRealSwap(DVG _dvg, unsigned int *count);

int dvgSetRenderingGroup(DVG _dvg, int myPosition, int num, char *names[],int *phase);
int dvgSynchronizeWithGroup(DVG _dvg);

int dvgSetFramerateDivider(DVG _dvg, int divider);
int dvgSetTimeDivisionAntiAliasing(DVG _dvg, int multiplier);
int dvgSetGenlockPhase(DVG _dvg, int hphase,int vphase);

int dvgSetCKeyParams(DVG _dvg,char *Hlut,char *Slut,char *Vlut,int board);
int dvgSetCKeyTables(DVG _dvg,char *Hlut,char *Slut,char *Vlut,int board);
int dvgSetCKeyTablesZone(DVG _dvg,char *Hlut,char *Slut,char *Vlut,int zoneID,int board);
int dvgSetCKey(DVG _dvg, int mode);
int dvgSetCKeyZoned(DVG _dvg, int mode);
int dvgSetZoneCompositing(DVG _dvg, int ckeyOrLinear, int preMultiplied, int negate,
        int composite,
        int futureReserveIdontKnowWhatYet1,
        int futureReserveIdontKnowWhatYet2,
        int futureReserveIdontKnowWhatYet3,
        int futureReserveFlags,
        void *futureReservePointer,
        int zoneID);

typedef struct {
    char *name;
    float val;
} CKeyParameterValuePair;

int dvgSetCKeyParameters(DVG _dvg,CKeyParameterValuePair *plist,int board);
int dvgSetCKeyParametersZone(DVG _dvg,CKeyParameterValuePair *plist,int zoneID, int board);


// Old style video grabbing --------------------------------------------------------   Vidin -

int dvgGetNumVidinPaths(DVG _dvg);
int dvgGetVidinAttributes(DVG _dvg,int w,int *width,int *height,int *depth, int *glFormat);
int dvgStartVidinPath(DVG _dvg,int w);
int dvgGetVidinField(DVG _dvg,int w,int *polarity, unsigned char **pixels);
int dvgStopVidinPath(DVG _dvg,int w);



// New style video grabbing --------------------------------------------------------   Vidin -

int dvgGetNumVidinUnits(DVG _dvg);
int dvgGetVidinUnitConfigs(DVG _dvg, int whichUnit, DvgVidinUnitConfig ** configs, int *numConfigs);
int dvgGetVidinUnitType(DVG _dvg, int whichUnit, int *type, char **verbalDescription);
int dvgSetVidinUnitConfig(DVG _dvg, int whichUnit, int configID);
int dvgSetVidinUnitInputParams(DVG _dvg, int whichUnit, int whichInput, DvgVidinUnitInputParams *param);
int dvgGetVidinUnitInputAttributes(DVG _dvg,int whichUnit, int whichInput,int *width,int *height,int *depth, int *glFormat);
int dvgStartVidinUnitPaths(DVG _dvg, int whichUnit);
int dvgGetVidinUnitField(DVG _dvg, int whichUnit, int whichInput, int *polarity, unsigned char **pixels);
int dvgGetVidinUnitFieldExtended(DVG _dvg, int whichUnit, int whichInput, int *polarity, unsigned char **pixels,DvgInputFieldExtendedInfo *xinfo);
// int dvgChooseVidinUnitConfig(.....)
int dvgStopVidinUnitPaths(DVG _dvg, int whichUnit);
int dvgStopAllVidinUnitPaths(DVG _dvg);
int dvgStartVidinUnitPaths(DVG _dvg, int whichUnit);
int dvgStartAllVidinUnitPaths(DVG _dvg);


DVG dvgOpen(void) ;
int dvgActivate(DVG _dvg) ;
int dvgTestSetup(DVG _dvg) ;
int dvgClose(DVG _dvg) ;
int dvgIsOpened(void);
DVG dvgGetOpenedHandle(void);

int  __dvg_set_jtag(DVG _dvg, int w,int enable, int tck, int tdi, int tms);
int  __dvg_get_jtag(DVG _dvg, int w);

#ifdef __cplusplus
}
#endif

#endif
