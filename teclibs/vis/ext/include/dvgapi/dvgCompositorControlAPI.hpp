/* 
 * Copyright 2007 Orad Hi-Tec Systems Ltd.
 * ALL RIGHTS RESERVED
 *
 * Filename: dvgCompositorControlAPI.hpp
 */

#ifndef _DVG_COMPOSITOR_CONTROL_A_P_I_HPP
#define _DVG_COMPOSITOR_CONTROL_A_P_I_HPP

#include "dvgAPIBase.hpp"
#include "dvgCompositorConfig.hpp"


/**
Class allows to control DVG compositor board functionality and change parameters / configuration.
*/

class DVGAPI_SHARED_SYMBOL dvgCompositorControlAPI : public dvgAPIBase
  {
public:

  /// Default constructor.
  dvgCompositorControlAPI(void);

  /// Destructor.
  virtual ~dvgCompositorControlAPI(void);

  /**
  This method return video standard which is active on this DVG board.
  */
  dvgAPIBase::StatusCodes getVideoStandard(DvgAPIDefs::DVGVideoStandard& aStandard);

  /**
  This method set video standard active for this DVG board.
  If video standard change is possible, it can take long time to activate
  and can change several other parameters (for example video mode).
  */
  dvgAPIBase::StatusCodes setVideoStandard(const DvgAPIDefs::DVGVideoStandard aStandard);

  /**
  This method returns pointer to class which store set of current parameters.
  See definition of dvgCompositorConfig.
  */
  dvgAPIBase::StatusCodes getCompositorConfig(dvgCompositorConfig &aConfig);

  /**
  This method allows to apply several settings at once.
  Any subset of parameters which can be stored in dvgCompositorConfig class can be set.
  See definition of dvgCompositorConfig.
  */
  dvgAPIBase::StatusCodes setCompositorConfig(dvgCompositorConfig &aConfig);

  /**
  This method return video format which is active on this DVG board.
  */
  dvgAPIBase::StatusCodes getVideoFormat(DvgAPIDefs::DVGGraphicsMode& aFormat);

  /**
  Returns set of binary flags with supported video formats.
  In order to check if video format is supported check "((1 << format) & aSupportedFormats) != 0".
  Possible formats are defined in DVGGraphicsMode enum.
  */
  dvgAPIBase::StatusCodes getVideoFormatsFlags(DvgAPIDefs::LongLong& aSupportedFormats);

  /**
  Helper method. Return true if given video format is supported.
  */
  bool isVideoFormatSupported(const DvgAPIDefs::DVGGraphicsMode aFormat)
    {
    DvgAPIDefs::LongLong flags;
    if ((getVideoFormatsFlags(flags) == SUCCESS) && (((DvgAPIDefs::LongLong)1 << aFormat) & flags))
      return true;
    return false;
    }

  /**
  This method set video format for this DVG board.
  To check supported formats use getVideoFormatsFlags().
  */
  dvgAPIBase::StatusCodes setVideoFormat(const DvgAPIDefs::DVGGraphicsMode aFormat);

  /**
  This method return true into aFrameRendering parameter when GFX must render full frame,
  and no interlacing is used (output video format can still be interlaced, but no local).
  It is always true for progressive video formats.
  */
  dvgAPIBase::StatusCodes isFrameRendering(bool& aFrameRendering);

  /**
  This method set frame rendering parameter.
  If set as true, GFX must render full frame and no interlacing is used 
  (output video format can still be interlaced, but no local).
  It make sense only for interlaced (not pregressive) video formats,
  as for progressive it is always true and cannot be changed to false.
  Set frame rendering to true automatically set flicker filter on.
  */
  dvgAPIBase::StatusCodes setFrameRendering(const bool aFrameRendering);

  /**
  This method return true into aAlphaViewPort when alpha viewports are used.
  It means that both color and alpha viewports are created on GFX display and
  alpha channel can be outputed.
  */
  dvgAPIBase::StatusCodes isAlphaViewPort(bool& aAlphaViewPort);

  /**
  This method set use of alpha viewports.
  If set as true it means that both color and alpha viewports are created 
  on GFX display and alpha channel can be outputed.
  */
  dvgAPIBase::StatusCodes setAlphaViewPort(const bool aAlphaViewPort);

  /**
  This method return true in aOn parameter if flicker filter is activated.
  This filter is used only if output video format is interlaced (in fields)
  while local rendering is progressive (frame rendering).
  Set this filter "on" for other situation does not change anything,
  but value is remembered and remain, then this function can return
  true also if filter does not really work.
  */
  dvgAPIBase::StatusCodes isAntiFlickerFilter(bool& aOn);

  /**
  This method set use of anti flicker filter.
  This filter is used only if output video format is interlaced (in fields)
  while local rendering is progressive (frame rendering).
  Set this filter on for other situation does not change anything,
  but value will be remembered and remain when other parameters 
  (video format or frame rendering) will change.
  If frame rendering is set to on (using setFrameRendering() ), 
  it automatically set filter to on (but do not chanage strenth of filter).
  */
  dvgAPIBase::StatusCodes setAntiFlickerFilter(const bool aOn);

  /**
  This method return strength of flicker filter.
  Possible minimum and maximum value can be read by getAntiFlickerFilterStrengthRanges().
  Check isAntiFlickerFilter() to know if filter is activated.
  Deactivating filter by setAntiFlickerFilter() does not change strength value.
  */
  dvgAPIBase::StatusCodes getAntiFlickerFilterStrength(float& aStrenght);

  /**
  This method return minimum and maximum value of flicker fliter strength
  which can be set using setAntiFlickerFilterStrength().
  */
  dvgAPIBase::StatusCodes getAntiFlickerFilterStrengthRanges(float& aMin, float& aMax);

  /**
  This method set flicker filter strength.
  Possible minimum and maximum value can be read by getAntiFlickerFilterStrengthRanges().
  Check isAntiFlickerFilter() to know if filter is activated.
  Deactivating filter by setAntiFlickerFilter() does not change strength value.
  */
  dvgAPIBase::StatusCodes setAntiFlickerFilterStrength(const float aStrength);

  /**
  This method return currently used genlock source for this DVG board.
  See DVGGenlockSource for description.
  Not all sources are possible on each hardware.
  To check which sources are possible to use, check getGenlockSourceFlags().
  */
  dvgAPIBase::StatusCodes getGenlockSource(DvgAPIDefs::DVGGenlockSource& aSource);

  /**
  This method returns in aSourcesFlags binary set of supported genlock sources flags.
  In order to check if source is supported: check that ((1 << source) & aSourcesFlags) != 0.
  See DVGGenlockSource for description of sources.
  */
  dvgAPIBase::StatusCodes getGenlockSourceFlags(unsigned int& aSourcesFlags);

  /**
  This method set genlock source for this DVG board.
  See DVGGenlockSource for description of sources.
  Not all sources are possible on each hardware.
  To check which sources are possible to set, use getGenlockSourceFlags().
  */
  dvgAPIBase::StatusCodes setGenlockSource(const DvgAPIDefs::DVGGenlockSource aSource);

  /**
  This function return additive function of the chain.
  If additive function is activated, content from chain (previous nodes) or video input
  is composited with local node content using selected method.
  See definition of DVGAdditiveFunction.
  Not all methods are supported on each hardware.
  To check which methods are possible to set, use getAdditveFunctionFlags().
  */
  dvgAPIBase::StatusCodes getAdditiveFunction(DvgAPIDefs::DVGAdditiveFunction &aMixingType);

  /**
  This method returns in aSupportedMixings binary set of supported additive functions flags.
  In order to check if function is supported: check that ((1 << function) & aSupportedMixings) != 0.
  See DVGAdditiveFunction for description of functions.
  */
  dvgAPIBase::StatusCodes getAdditiveFunctionFlags(unsigned int& aSupportedMixings);

  /**
  This method set additive function for this DVG board.
  See DVGAdditiveFunction for description of functions.
  Not all functions are possible on each hardware.
  To check which functions are possible to set, use getAdditveFunctionFlags().
  */
  dvgAPIBase::StatusCodes setAdditiveFunction(const DvgAPIDefs::DVGAdditiveFunction aMixingType);

  /**
  This method get horizontal and vertical extension margins for local GFX resolution.
  By default display resolution for local GFX is set to the resolution of used video format (frame or field).
  If cropping extension is set, GFX display resolution is enlarged by given number of pixels.
  Active output area (which have resolution of selected video frame/field) is cropped from whole display.
  Offsets for output area can be read using getCroppingOffset().
  By default cropping extension is set to 0.
  */
  dvgAPIBase::StatusCodes getCroppingExtension(unsigned short& aHExtension, unsigned short& aVExtension);

  /**
  This method set horizontal and vertical extension margins for local GFX resolution.
  By default display resolution for local GFX is set to the resolution of used video format (frame or field).
  If cropping extension is set, GFX display resolution is enlarged by given number of pixels.
  Active output area (which have resolution of selected video frame/field) is cropped from whole display.
  Offsets for output area are set using setCroppingOffset().
  By default cropping extension is set to 0.
  */
  dvgAPIBase::StatusCodes setCroppingExtension(const unsigned short aHExtension, const unsigned short aVExtension);

  /**
  This method read offsets in pixels between upper left corner of local GFX display and active output area.
  Offset can have value in range 0 to <extension value> (which was set into setCroppingExtension() function).
  Offsets are stored internally as normalized value [0,1], then if extension value was changed, also offset value 
  in pixels will change proportionally.
  By default offsets are set to 0, which mean output area from left upper corner of GFX display.
  */
  dvgAPIBase::StatusCodes getCroppingOffset(unsigned short& aHOffset, unsigned short& aVOffset);

  /**
  This method read normalized offset values between upper left corner of local GFX display and active output area.
  Offset can have value in range 0.0 to 1.0. Value 1.0 means that output area is moved to maximal right/down position. 
  Offsets are stored internally as normalized value [0,1], then if extension value (in pixels) was changed,  
  normalized offset value will not change.
  By default offsets are set to 0, which mean output area from left upper corner of GFX display.
  */
  dvgAPIBase::StatusCodes getCroppingOffset(float& aHOffset, float& aVOffset);

  /**
  This method set offset in pixels between upper left corner of local GFX display and active output area.
  Offset can be set only in range 0 to <extension value> (which was set into setCroppingExtension() function).
  Offsets are stored internally as normalized value [0,1], then if extension value was changed, also offset value 
  in pixels will change proportionally.
  By default offsets are set to 0, which mean output area from left upper corner of GFX display.
  */
  dvgAPIBase::StatusCodes setCroppingOffset(const unsigned short aHOffset, const unsigned short aVOffset);

  /**
  This method set normalized offset value between upper left corner of local GFX display and active output area.
  Offset can be set in range 0.0 to 1.0. Value 1.0 means that output area is moved to maximal right/down position. 
  Offsets are stored internally as normalized value [0,1], then if extension value (in pixels) was changed,  
  normalized offset value will not change.
  By default offsets are set to 0, which mean output area from left upper corner of GFX display.
  */
  dvgAPIBase::StatusCodes setCroppingOffset(const float aHOffset, const float aVOffset);

  /**
  This method return Chromakey base color set for this compositor (see ChromakeyColor definition).
  Check using getAdditiveFunctionFlags() if chromakeying is posisble for this HW.
  Chromakey will be used only if set by proper additive function (check using getAdditiveFunction() ).
  */
  dvgAPIBase::StatusCodes getChromakeyColor(DvgAPIDefs::ChromakeyColor& aColor);

  /**
  This method set Chromakey base color for this compositor (see ChromakeyColor definition).
  Check using getAdditiveFunctionFlags() if chromakeying is posisble for this HW.
  Chromakey will be used only if set by proper additive function (check using getAdditiveFunction() ).
  */
  dvgAPIBase::StatusCodes setChromakeyColor(const DvgAPIDefs::ChromakeyColor& aColor);

  /**
  This method return chromakey color table for given component.
  See definition of ChromakeyTable for more information.
  All used components (RGB or HSV) must have the same type (POINTS or TABLE).
  Check using getAdditiveFunctionFlags() if chromakeying is posisble for this HW.
  Chromakey will be used only if set by proper additive function (check using getAdditiveFunction() ).
  */
  dvgAPIBase::StatusCodes getChromakeyTable(const DvgAPIDefs::ColorComponent aComponent, DvgAPIDefs::ChromakeyTable& aTable);

  /**
  This method set chromakey color table for given component.
  See definition of ChromakeyTable for more information.
  All used components (RGB or HSV) must have the same type (POINTS or TABLE).
  Check using getAdditiveFunctionFlags() if chromakeying is posisble for this HW.
  Chromakey will be used only if set by proper additive function (check using getAdditiveFunction() ).
  */
  dvgAPIBase::StatusCodes setChromakeyTable(const DvgAPIDefs::ColorComponent aComponent, const DvgAPIDefs::ChromakeyTable& aTable);

protected:

  virtual dvgAPIBase::StatusCodes opening();
  virtual dvgAPIBase::StatusCodes closing();

private:

  /// Do not use copy constructor.
  dvgCompositorControlAPI(const dvgCompositorControlAPI &aOther);
  /// Do not use = operator.
  dvgCompositorControlAPI &operator=(const dvgCompositorControlAPI &aOther);

  };

#endif
