/* 
 * Copyright 2007 Orad Hi-Tec Systems Ltd.
 * ALL RIGHTS RESERVED
 *
 * Filename: dvgOutputControlAPI.hpp
 */

#ifndef DVG_OUTPUT_CONTROL_A_P_I_HPP
#define DVG_OUTPUT_CONTROL_A_P_I_HPP

#include "dvgAPIBase.hpp"


/**
Control of output signals of DVG board.
*/

class  DVGAPI_SHARED_SYMBOL dvgOutputControlAPI : public dvgAPIBase
  {
public:

  /// Default constructor.
  dvgOutputControlAPI(void);

  /// Destructor.
  virtual ~dvgOutputControlAPI(void);

  ///
  dvgAPIBase::StatusCodes  getNumberOfOutputs(unsigned int &aNumberOfOutputs);

  ///
  dvgAPIBase::StatusCodes  getOutputCapability(unsigned int aOutput, DvgAPIDefs::DVGVideoOutputCapability* &aCapability);

  ///SDI/analog/VR/stereo/
  dvgAPIBase::StatusCodes  getOutputType(unsigned int aOutput, unsigned int &aType);

  ///
  dvgAPIBase::StatusCodes  isInternallyUsed(unsigned int aOutput, bool &aUsed);

  /**
  Sets downconversion HD to SD.
  HD signal will be downconverted to analog SD format.
  It is applied when output is not internally used.
  */
  dvgAPIBase::StatusCodes  activateHD2SDDownconversion(unsigned int aOutput, bool aActivate);

  ///
  dvgAPIBase::StatusCodes  isHD2SDDownconversionActivated(unsigned int aOutput, bool &aActivate);

  /**
  Activates DVI Output.
  It is applied when output is not internally used.
  */
  dvgAPIBase::StatusCodes  activateDVIOutput(unsigned int aOutput, bool aActivate);

  ///
  dvgAPIBase::StatusCodes  isDVIOutputActivated(unsigned int aOutput, bool &aActivate);

  ///aSourcesFlags - flags of supported DVGOutputSource
  dvgAPIBase::StatusCodes  getSupportedSources(unsigned int aOutput, unsigned int &aSourcesFlags);

  /**
  It sets source for outputr
  */
  dvgAPIBase::StatusCodes  setSource(unsigned int aOutput, DvgAPIDefs::DVGOutputSource aSource);

  ///
  dvgAPIBase::StatusCodes  getSource(unsigned int aOutput, DvgAPIDefs::DVGOutputSource &aSource);

protected:

  virtual dvgAPIBase::StatusCodes  opening(void);
  virtual dvgAPIBase::StatusCodes  closing(void);

  private:

  /// Copy constructor.
  dvgOutputControlAPI(const dvgOutputControlAPI &aOther);

  /** Assignment operator.
  @param aOther object to be assigned.
  @return dvgOutputControlAPI& after assigned state
  */
  dvgOutputControlAPI &operator=(const dvgOutputControlAPI &aOther);

  };

#endif
