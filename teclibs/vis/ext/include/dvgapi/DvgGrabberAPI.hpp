/* 
 * Copyright 2007 Orad Hi-Tec Systems Ltd.
 * ALL RIGHTS RESERVED
 *
 * Filename: dvgGrabberAPI.hpp
 */

#ifndef DVG_GRABBER_API_HPP
#define DVG_GRABBER_API_HPP

#include "dvgAPIBase.hpp"

/**
Class covers grabbing functionality of DVG board.

Class is dedicated to deliver grabbed image. 
Configuration is performed by other class dvgGrabberControlAPI.

Grabbing may be performed to internal buffer (managed by driver) or to buffer
supplied by user. 
Number of VideoInputStreams is constant, but video streams may be inactive 
if function of board is changed (e.g. SD grabber HD Grabber).

There are methods to get parameters of image, like resolution and pixel format,
necessary for render or process image.

Buffer allocated by user may be used only by process which owns buffer.
If internal buffer is used, it is possible that VideoInputStream cannot be configured
to handle transfer, because of limited size of internal buffer.

Video input stream has to be active and attached to some physical input in
order to grab. It is part of configuration and it is covered by separate class
dvgGraberControlAPI. There are only methods to detect if VideoInputStream is
working (it means is active and connected to physical input).
Additionally, VideoInputStream has to be enabled for grabbing.

There is mechanizm to notify user about begin and end of transfer.

Most of methods has to or should be called after locking board in order to
prevent changing critical parameters, i.e. field resolution, from other place (process).
*/

struct DVGBufferHeader;

class  DVGAPI_SHARED_SYMBOL dvgGrabberAPI : public dvgAPIBase
  {
public:
 
  /// Helper constant values used in this class
  enum Consts
    {
    /// Special filed ID value which always means last grabbed field.
    CURRENT_FIELD_ID = -1,
    };

  /// Helper class which define element of FieldBuffer.
  class DVGAPI_SHARED_SYMBOL FieldItem
    {
    public:

    /// Destructor.
    virtual ~FieldItem(void);

    /**
    This method return offset in bytes into field buffer to begin of this field data item.
    Use getBufferPtr() from parent FieldBuffer class to get base pointer value.
    */
    size_t getDataOffset(void);

    /**
    This method returns pointer to the field data buffer.
    */
    void* getData(void);

    /**
    This method returns polarit of field stored in this item.
    For progressive video format it always return DVG_FRAME value.
    If framegrabbing is activated for interlaced video formats,
    it returns DVG_FRAME_ODD_EVEN or DVG_FRAME_EVEN_ODD
    depends which field in combained first in final frame.
    */
    DvgAPIDefs::DVGFieldPolarity getFieldPolarity(void);

    protected:

    /// Default counstructor. Do not use directly.
    FieldItem(void);
    /// Copy counstructor. Do not use directly.
    FieldItem(const FieldItem&);
    /// = operator. Do not use directly.
    FieldItem& operator=(const FieldItem& aOther);
    /// Main counstructor. Do not use directly.
    FieldItem(void* aBufferPtr, struct DVGFieldHeader* aHeader);

    void* theData;
    struct DVGFieldHeader* theHeader;
    };

  /// Helper class which define field buffer to store grabbed frames.
  class DVGAPI_SHARED_SYMBOL FieldBuffer
    {
  public:
    /// This method returns size of buffer in bytes.
    size_t getSize(void);

    /// This method returns total number of blocks (fields/frames) into the buffer.
    unsigned int getLength(void);

    /// This method returns number of valid (filled) blocks (fields/frames) into the buffer.
    unsigned int getValidLength(void);

    /**
    This method returns OGL pixel format which define organization of block.
    (GL_BGRA_EXT, GL_BGR_EXT etc.).
    */
    int getGLPixelFormat(void);

    /**
    This method returns DX pixel format which define organization of block.
    Currently not implemented.
    */
    int getDXPixelFormat(void);

    /**
    This method returns field/frame item resolution/geometry.
    It should be called after locking the board, when parameters will not change.
    aWidth, aHeight - size in pixels, aDepth - bytes per pixel.
    */
    void getFieldSize(unsigned int& aWidth, unsigned int& aHeight, unsigned int& aDepth);

    /**
    This method returns base buffer memory pointer.
    Use offset returned by FieldItem::getData() to get field/frame item data pointer.
    */
    unsigned char* getBufferPtr(void);

    /**
    This method returns pointer for field/frame item.
    If aTimeShift is 0, returns pointer for lastly created/grabbed FieldItem. 
    If aTimeShift is > 0, returns FieldItem shifted by aTimeShift fields/frames in past.
    Returns valid pointer for aTimeShift in range [0; getLength()),
    but fields outside of range [0; getValidLength()) does not contain 
    valid data.
    */
    FieldItem* getFieldByTime(unsigned int aTimeShift);
    
    protected:
    
    /// Default counstructor. Do not use directly.
    FieldBuffer(void);
    /// Copy counstructor. Do not use directly.
    FieldBuffer(const FieldBuffer&);
    /// Destructor. Do not use directly.
    virtual ~FieldBuffer(void);
    /// = operator. Do not use directly.
    FieldBuffer& operator=(const FieldBuffer&);

    void construct(void* aBuffer, DVGBufferHeader* aBufferHeader, DVGFieldHeader* aFieldHeaders);
    
    unsigned int theBufferId;
    void* theBuffer;
    volatile DVGBufferHeader *theBufferHeader;
    unsigned int theNumItems;
    FieldItem **theFieldItems;
    };

  /// Helper class which define video input stream and methods to use it.
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
    dvgAPIBase::StatusCodes getStatus();

    /**
    This method return status of stream.
    Returns true if video input stream is configured/activated and has attached some physical input.
    Configuration of stream is done using dvgGrabberControlAPI class.
    Not working streams (returning false) cannot be enabled.
    */
    dvgAPIBase::StatusCodes isWorking(bool& aWorking);

    /**
    This method enable or disable usage of video stream.
    If called with true, enable usage. If called with false, disable usage.
    Grabbing will be performed when stream is enabled and grabbing is started ( see startGrabbing() ).
    Enabling is possible only on working streams (see isWorking() ).
    Usually steps are first enabling used streams, then start grabbing on the board.
    It is also possible to first start grabbing (with part of streams enabled), then
    enable additional stream. 
    Enabling or disabling stream when grabbing is started can cause temporary malfunction on other enabled streams.
    */
    dvgAPIBase::StatusCodes enable(bool aEnable = true);

    /**
    Helper function to disable stream. See enable() description.
    */
    dvgAPIBase::StatusCodes disable(void)
      {
      return enable(false);
      };
    
    /**
    This method return true if video stream is enabled. See enable() description.
    */
    dvgAPIBase::StatusCodes isEnabled(bool& aEnabled);

    /**
    Sets user buffer for input stream.
    It releases internal buffer if it was assigned. It failes if grabbing is started.
    */
    dvgAPIBase::StatusCodes assignUserBuffer(const void* aBufferPtr, size_t aSize);

    ///returns NULL in aBufferPtr if internal buffer is used
    dvgAPIBase::StatusCodes getUserBuffer(void*& aBufferPtr, size_t& aSize);

    /**
    Connfigures input stream to use aLength or less blocks (including 0) from internal buffer.
    It failes if grabbing is started. It stops usage of user buffer if it was assigned.
    It returns error if less then requested blocks is assigned.
    Assigned length may be retrieved in aResultLength.
    */
    dvgAPIBase::StatusCodes assignInternalBuffer(unsigned int aLength = 2, unsigned int *aResultLength = NULL);

    ///It may returns 0 even user buffer is not assigned.
    dvgAPIBase::StatusCodes getInternalBuffer(unsigned int &aLength);

    /*
    Returns buffer configuration.
    aBufferPtr is not NULL if user buffer is assigned. aLength make sense only if internal buffer
    is assigned.
    */
    dvgAPIBase::StatusCodes getBufferConfiguration(void** aBufferPtr, size_t* aSize, unsigned int* aLength);

    ///
    dvgAPIBase::StatusCodes getGLPixelFormat(int&);

    ///
    dvgAPIBase::StatusCodes getDXPixelFormat(int&);

    /**
    Retrieve field resolution. It should be called after locking board, in order to prevent changing.
    aDepth - bytes per pixel.
    */
    dvgAPIBase::StatusCodes getFieldSize(unsigned int& aWidth, unsigned int& aHeight, unsigned int& aDepth);

    /**
    Returns base pointer to buffer.
    Use offset returned by getFieldOffset() to get field data.
    unsigned char* bufferPtr;
    getBufferPtr(bufferPtr);
    ...
    getFieldOffset(fieldId, fieldOffset);
    fieldData = bufferPtr + fieldOffset;
    As alternative you may use getField()
    */
    dvgAPIBase::StatusCodes getBufferPtr(unsigned char*& aPtr);

    /**
    Locks one field in buffer. If delay is not specifed last field is locked and
    delayed field in other case.
    It prevents from grabbing to this part of buffer.
    If next grabbing is going to be performed to locked part of buffer,
    driver pauses grabbing of this video input stream to time buffer is released.
    It is possible to call this function without calling releaseField().
    In this case previously locked field is released and aFieldId field is locked.
    aFieldId - retrieve id of locked field 
    */
    dvgAPIBase::StatusCodes lockField(int& aFieldId);

    ///
    dvgAPIBase::StatusCodes releaseField();

    /**
    Offset in bytes to field (aFieldId) in buffer.
    Use getBufferPtr() to get base pointer.
    As aFieldId use value retrieved from lockField() or CURRENT_FIELD_ID if you are interested
    in current field, but not necessary in locking field.
    */
    dvgAPIBase::StatusCodes getFieldOffset(int aFieldId, size_t& aOffset);

    /**
    Gets field data for field aFieldId.
    aFieldId - use value retrieved from lockField() or CURRENT_FIELD_ID if you are interested
    in current field, but not necessary in locking field.
    */
    dvgAPIBase::StatusCodes getField(int aFieldId, void*& aFieldData);

    /**
    It make sense only for interlaced video formats,
    in other cases it does not fail but returns always the same value (DVG_FRAME).
    */
    dvgAPIBase::StatusCodes getFieldPolarity(int aFieldId, DvgAPIDefs::DVGFieldPolarity& aPolarity);

    ///
    dvgAPIBase::StatusCodes waitForTransferStart(const unsigned int aTimeout);

    /// wait for end of transfer
    dvgAPIBase::StatusCodes waitForTransferFinish(const unsigned int aTimeout);

    /**
    Layer 2 buffer is intended to hold long history of video images.
    It is limited only by available memory. It is filled in background by service.
    CPU is utilized to copy images from internal buffer to layer 2 buffer.
    If buffer with aId is currently assigned to input stream,
    it reaturns dvgAPIBase::L2BUFFER_ALREADY_EXISTS. In such case to check size of
    buffer call getL2Buffer()->getSize().
    */
    dvgAPIBase::StatusCodes createL2Buffer(size_t aSize, int aId = 0);

    ///
    dvgAPIBase::StatusCodes closeL2Buffer(void);

    /**
    */
    FieldBuffer* getL2Buffer(void);

    ///
    dvgAPIBase::StatusCodes startUpdatingL2Buffer(void);

    ///
    dvgAPIBase::StatusCodes stopUpdatingL2Buffer(void);

  protected:

    virtual dvgAPIBase::StatusCodes open();
    virtual dvgAPIBase::StatusCodes close();
    dvgAPIBase::StatusCodes createL2Buffer(size_t aSize, int aId, DVGBufferHeader* aHeader);
    dvgAPIBase::StatusCodes closeL2BufferEx(void);
    friend dvgGrabberAPI;

    VideoInputStream(void);
    
    VideoInputStream(VideoInputStream& aOther);
    
    virtual ~VideoInputStream(void);

    dvgGrabberAPI* theBoard;
    unsigned int theIndex;
    dvgAPIBase::StatusCodes theStatus;
    bool theIsOpen;
    HANDLE theStartEvent;
    HANDLE theFinishEvent;
    unsigned int theBufferId;
    unsigned char* theGrabbingBuffer;
    volatile DVGBufferHeader *theGrabbingBufferHeader;
    FieldBuffer *theL2Buffer;
    };

   /// Default constructor.
  dvgGrabberAPI(void);

  /// Destructor.
  virtual ~dvgGrabberAPI(void);

  /**
  It returns total numbers of fields which can hold internal buffer.
  It may change if video mode or some global compression/downconversion are changed,
  so it is recomended to lock access to board before calling this method.
  */
  dvgAPIBase::StatusCodes getInternalBufferLength(unsigned int& aFieldsNum);

  ///
  dvgAPIBase::StatusCodes getNumberOfVideoInputStreams(unsigned int& aNum);

  /**
  Returns aIndex'th VideoInputStream.
  It may returns NULL if index exceeds limit or api is not opened.
  */
  VideoInputStream* getVideoInputStream(unsigned int aStreamIndex);

  /**
  It ensures that current configuration does not change during grabbing.
  It prevents from changing any critical parameters.
  */
  dvgAPIBase::StatusCodes lockBoard(void);

  /**
  It removes lock. If grabbing is started it stops grabbing, too.
  It disables any VideoBuffers enabled by this instance of API,
  if thay were not disabled manually.
  */
  dvgAPIBase::StatusCodes unlockBoard(void);

  ///if no videoin is enabled, mathod does nothing and returns SUCCESS
  dvgAPIBase::StatusCodes startGrabbing(void);

  ///
  dvgAPIBase::StatusCodes stopGrabbing(void);

  ///
  dvgAPIBase::StatusCodes getGrabbingState(DvgAPIDefs::DVGGrabbingState&);

  ///
  dvgAPIBase::StatusCodes waitForInputSync(const unsigned int aTimeout);

  /// wait for end of transfer from grabber
  dvgAPIBase::StatusCodes waitForTransferFinish(const unsigned int aTimeout);

  protected:

  virtual dvgAPIBase::StatusCodes opening();
  virtual dvgAPIBase::StatusCodes closing();

  HANDLE theDMAStartEvent;
  HANDLE theDMAFinishEvent;

  private:
  
  enum
    {
    MAX_NUM_VIDINS = 16,
    };

  friend dvgGrabberAPI::VideoInputStream;

  //it is internal buffer
  struct DVGFieldHeader* theFieldHeaderArena;

  DVGBufferHeader *theGrabbingBufferHeaderArena;
  VideoInputStream* theInput[MAX_NUM_VIDINS];

  /// Copy constructor.
  dvgGrabberAPI(const dvgGrabberAPI &aOther);

  dvgGrabberAPI &operator=(const dvgGrabberAPI &aOther);

  };

#endif