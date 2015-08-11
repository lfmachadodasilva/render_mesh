/* 
 * Copyright 2007 Orad Hi-Tec Systems Ltd.
 * ALL RIGHTS RESERVED
 *
 * Filename: dvgGrabberControlAPI.hpp
 */

#ifndef _DVG_GRABBER_CONTROL_A_P_I_HPP
#define _DVG_GRABBER_CONTROL_A_P_I_HPP


#include "dvgAPIBase.hpp"


/**
Class allows to control parameters of grabbing.

There are methods to change video format, downconvertion, dual-link and
other parameters. There is possibility to route physical input to input stream.

Most of functions faile if board is currently used (some API locked board
or started grabbing).

Number of video input stream is not changing for board and it is maximum number.
Because of limitation of board, number of active video steams may change.
Number of active video streams depends on video format (e.g. DVG64 board
support 4 SD video input streams, but only one if some HD format is set).

*/


class DVGAPI_SHARED_SYMBOL dvgGrabberControlAPI : public dvgAPIBase
  {
public:

  class DVGAPI_SHARED_SYMBOL VideoInputStream
    {
  public:

    /**
    This method returns index of the stream.
    Streams are indexed from 0 to getNumberOfVideoInputStreams() - 1.
    */
    inline unsigned int getIndex(void) const
      { return theIndex; }

    /**
    This method return last status code (which was returned by last method call).
    See dvgAPIBase::StatusCodes definition.
    */
    dvgAPIBase::StatusCodes getStatus() const
      {
      return theStatus;
      }

    /**
    Video input stream may be inactive if current video format limit number of streams.
    */
    dvgAPIBase::StatusCodes  isActive(bool& aActive);

    ///
    dvgAPIBase::StatusCodes  getCapability(const DvgAPIDefs::DVGVideoInputCapability*&);

    ///It disables chromakey, if aAlphaChannel != -1
    dvgAPIBase::StatusCodes  setAlphaChannel(int aAlphaChannel);
    ///
    dvgAPIBase::StatusCodes  getAlphaChannel(int& aAlphaChannel);

    ///It disables alpha channel, if enabled
    dvgAPIBase::StatusCodes  enableChromaKey(bool aEnable = true);
    ///
    dvgAPIBase::StatusCodes  isChromaKey(bool& aEnabled);

    ///make sense only for interlaced video format, no action for progressive formats
    dvgAPIBase::StatusCodes  enableFrameGrabbing(bool aEnable = true);
    ///
    dvgAPIBase::StatusCodes  isFrameGrabbing(bool& aEnabled);

    /**
    It sets pixelformat for video input stream. It is overwritten by setGlobalPixelFormat().
    Set DvgAPIDef::DVG_PIXEL_GLOBAL if you want to return to global pixelformat.
    */
    dvgAPIBase::StatusCodes  setPixelFormat(const DvgAPIDefs::DVGPixelFormat);
    ///
    dvgAPIBase::StatusCodes  getPixelFormat(DvgAPIDefs::DVGPixelFormat&);

    ///set of DvgAPIDefs::DVGImageCompressionFlags
    dvgAPIBase::StatusCodes  setImageCompression(unsigned int aCompressionSet);
    ///
    dvgAPIBase::StatusCodes  getImageCompression(unsigned int& aCompressionSet);

    /**
    Returns height of field.
    Value is function of video format and downconvertion.
    */
    dvgAPIBase::StatusCodes  getFieldHeight(unsigned int& aHeight);

    /**
    Accepts values from [1, <field height>].
    aHeight is internally converted to normalzed value.
    */
    dvgAPIBase::StatusCodes  setGrabbingHeight(unsigned int aHeight);

    /**
    Returns value calculated from normalized value.
    It means that it may change after changing video format or
    applying downconvertion.
    */
    dvgAPIBase::StatusCodes  getGrabbingHeight(unsigned int& aHeight);

    /**
    Accepts normalized value [0.0;1.0].
    Normalized height means: (<grabbing height> - 1)/(<field height> - 1)
    */
    dvgAPIBase::StatusCodes  setGrabbingHeight(float aHeight);

    ///returns normalized height
    dvgAPIBase::StatusCodes  getGrabbingHeight(float& aHeight);

    /**
    Sets grabbing start line. It accepts values from [0,<field height> - <grabbing height>].
    aStartLine is internally converted to normalized value [0.0;1.0].
    */
    dvgAPIBase::StatusCodes  setGrabbingStartLine(unsigned int aStartLine);

    /**
    Returns value calculated from normalized start line.
    It means that it may change after changing video format or
    applying downconvertion.
    */
    dvgAPIBase::StatusCodes  getGrabbingStartLine(unsigned int& aStartLine);

    /**
    It acccepts normalized values [0.0;1.0].
    Normalized start line means: <start line>/(<field height> - <grabbing height>)
    */
    dvgAPIBase::StatusCodes  setGrabbingStartLine(float aStartLine);

    ///returns normalized start line
    dvgAPIBase::StatusCodes  getGrabbingStartLine(float& aStartLine);

    /**
    It supposes to route in runtime particular physical video input to video input stream.
    It is connected 1 to 1 at startup.
    */
    dvgAPIBase::StatusCodes  attachPhysicalInput(int aPhysicalInput);

    /**
    Returns -1 if no input is attached.
    */
    dvgAPIBase::StatusCodes  getPhysicalInput(int& aPhysicalInput);

    ///returns number of blocks in video buffer
    dvgAPIBase::StatusCodes  getBufferLength(unsigned int& aLength);

    /**
    Sets delay performed on video buffer. aDelay must not exceeds length of video buffer.
    Functions from dvgGrabberAPI for CURRENT_FIELD_ID returns parameters of delayed field.
    */
    dvgAPIBase::StatusCodes  setDelay(unsigned int aDelay);
    ///
    dvgAPIBase::StatusCodes  getDelay(unsigned int& aDelay);

  private:

    VideoInputStream(void);
    VideoInputStream(VideoInputStream& aOther);
    VideoInputStream(dvgGrabberControlAPI* aAPI, unsigned int aIndex);
    ~VideoInputStream(void);

    friend dvgGrabberControlAPI;
    dvgGrabberControlAPI *theBoard;
    unsigned int theIndex;
    dvgAPIBase::StatusCodes  theStatus;

    bool theCapabilityInitialized;
    DvgAPIDefs::DVGVideoInputCapability theCapability;
    };

  /// Default constructor.
  dvgGrabberControlAPI(void);

  /// Destructor.
  virtual ~dvgGrabberControlAPI(void);

  ///
  dvgAPIBase::StatusCodes  isBoardLocked(bool& aLocked);

  /**
  Reallocates internal buffer. Board has to be unlocked.
  */
  dvgAPIBase::StatusCodes  resizeInternalBuffer(size_t aSize);

  /**
  It returns size of internal buffer
  */
  dvgAPIBase::StatusCodes  getInternalBufferSize(size_t& aSize);

  ///Returns size of field in internal buffer
  dvgAPIBase::StatusCodes  getBaseFieldSize(unsigned int& aFieldSize);

  ///
  dvgAPIBase::StatusCodes  getVideoStandard(DvgAPIDefs::DVGVideoStandard& aStandard);

  ///
  dvgAPIBase::StatusCodes  setVideoStandard(const DvgAPIDefs::DVGVideoStandard aStandard);

  ///Board has to be unlocked.
  dvgAPIBase::StatusCodes  setVideoFormat(const DvgAPIDefs::DVGGraphicsMode aFormat);

  ///
  dvgAPIBase::StatusCodes  getVideoFormat(DvgAPIDefs::DVGGraphicsMode& aFormat);

  /**
  Sets global compression (global because it is per board).
  aCompressionFlags - set of compression flags, some of combination may be mutual exclusive
  */
  dvgAPIBase::StatusCodes  setGlobalCompression(unsigned int aCompressionFlags);
  
  ///
  dvgAPIBase::StatusCodes  getGlobalCompression(unsigned int& aCompressionFlags);

  /**
  Sets global pixel format (global means one for all streams of board).
  This settings overwrite pixel formats for all streams.
  This setting may be overwritten for particular stream (VideoInput::setPixelFormat()).
  Possible pixel formats you may check in board capability (getBoardCapability()).
  thePixelFormatFlags & (1 << aPixelFormat) <=> supported
  */
  dvgAPIBase::StatusCodes  setGlobalPixelFormat(DvgAPIDefs::DVGPixelFormat aPixelFormat);

  ///
  dvgAPIBase::StatusCodes  getGlobalPixelFormat(DvgAPIDefs::DVGPixelFormat &aPixelFormat);

  /**
  Freezes video input.
  */
  dvgAPIBase::StatusCodes  freezeVideo(bool aFreeze = true);

  /**
  Chekcs state of freezing video.
  */
  dvgAPIBase::StatusCodes  isVideoFrozen(bool& aFreeze);

  ///Number of connectors, it may be retrieved from DVGBoardCapability struct, too
  dvgAPIBase::StatusCodes  getNumberOfVideoInConnectors(unsigned int& aNum);

  ///
  dvgAPIBase::StatusCodes  getNumberOfVideoInputStreams(unsigned int& aNum);

  ///
  dvgAPIBase::StatusCodes  attachPhysicalInput(unsigned int aNumberOfStreams, const unsigned int* aPhysicalInputs);

  ///
  dvgAPIBase::StatusCodes  getPhysicalInput(unsigned int aNumberOfStreams, unsigned int* aPhysicalInputs);

  /**
  Returns aIndex'th VideoInputStream.
  It may returns NULL if index exceeds limit or api is not opened.
  */
  VideoInputStream* getVideoInputStream(unsigned int aVideoIndex);

protected:

  dvgAPIBase::StatusCodes  setPixelFormat(int aIndex, const DvgAPIDefs::DVGPixelFormat aFormat);
  dvgAPIBase::StatusCodes  getPixelFormat(int aIndex, DvgAPIDefs::DVGPixelFormat& aFormat);
  virtual dvgAPIBase::StatusCodes  opening();
  virtual dvgAPIBase::StatusCodes  closing();

private:

  enum Consts
    {
    MAX_NUM_VIDINS = 16,
    };

  friend VideoInputStream;

  VideoInputStream* theInput[MAX_NUM_VIDINS];

  /// Copy constructor.
  dvgGrabberControlAPI(const dvgGrabberControlAPI &aOther);
  /** Assignment operator.
  @param aOther object to be assigned.
  @return dvgGrabberControlAPI& after assigned state
  */
  dvgGrabberControlAPI &operator=(const dvgGrabberControlAPI &aOther);

  };

#endif

