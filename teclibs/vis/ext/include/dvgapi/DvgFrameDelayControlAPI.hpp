/* 
 * Copyright 2007 Orad Hi-Tec Systems Ltd.
 * ALL RIGHTS RESERVED
 *
 * Filename: dvgFrameDelayControlAPI.hpp
 */

#ifndef DVG_FRAME_DELAY_CONTROL_A_P_I_HPP
#define DVG_FRAME_DELAY_CONTROL_A_P_I_HPP

#include "dvgAPIBase.hpp"


/**
Class to control frame delay functionality of DVG board.
If board has ability to work as frame delay board, 
DVG_CAP_FDELAY_BOARD flag is set in DVGBoardCapability structure.
*/

class DVGAPI_SHARED_SYMBOL dvgFrameDelayControlAPI : public dvgAPIBase
  {
public:

  /// Default constructor.
  dvgFrameDelayControlAPI(void);

  /// Destructor.
  virtual ~dvgFrameDelayControlAPI(void);

  /**
  This method returns number of logical delay units supported on this board.
  It returns 0 if delay functionality is not supported into the HW.
  */
  dvgAPIBase::StatusCodes getNumberOfDelayUnits(unsigned int &aNumber);

  /**
  This method returns maximum delay in frames which can be set on this board.
  */
  dvgAPIBase::StatusCodes getMaxDelay(unsigned int &aMaxDelay);

  /**
  This method sets delay in frames for first delay unit.
  aDelay value must be between 0 and maxDelay returned by getMaxDelay().
  */
  dvgAPIBase::StatusCodes setDelay(const unsigned int aDelay)
    {
    return setDelay(0, aDelay);
    }

  /**
  This method sets delay in frames for given delay unit.
  aDelayUnit value is in range 0 to (aNumber_of_units - 1). 
  Number of units can be read using getNumberOfDelayUnits().
  aDelay value must be between 0 and maxDelay returned by getMaxDelay().
  */
  dvgAPIBase::StatusCodes setDelay(const unsigned int aDelayUnit, const unsigned int aDelay);

  /**
  This method return delay value in frames for first delay unit.
  */
  dvgAPIBase::StatusCodes getDelay(unsigned int &aDelay)
    {
    return getDelay(0, aDelay);
    }


  /**
  This method return delay value in frames for given delay unit.
  aDelayUnit value is in range 0 to (aNumber_of_units - 1). 
  Number of units can be read using getNumberOfDelayUnits().
  */
  dvgAPIBase::StatusCodes getDelay(const unsigned int aDelayUnit, unsigned int &aDelay);

protected:

  virtual dvgAPIBase::StatusCodes opening();
  virtual dvgAPIBase::StatusCodes closing();

private:

  /// Do not use copy constructor.
  dvgFrameDelayControlAPI(const dvgFrameDelayControlAPI &aOther);
  /// Do not use = operator.
  dvgFrameDelayControlAPI &operator=(const dvgFrameDelayControlAPI &aOther);


  };

#endif
