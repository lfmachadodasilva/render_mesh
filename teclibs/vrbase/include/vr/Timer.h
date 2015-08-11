#ifndef _VR_TIMER_H
#define _VR_TIMER_H

#include "Common.h"

namespace vr {

/*!
	Measures a time interval.
 
	The implementation prioritizes performance and resolution,
	but will probably run out-of-sync with real-world clocks.
 */
class VRBASE_EXPORT Timer
{
public:
	typedef int64 Stamp;

public:
	//! Creates a Timer and initializes its 'start time' to the current time.
	Timer();

	//! Returns a Stamp for the current time using a low-level OS function.
	Stamp computeCurrentStamp() const;

	//! Returns the timer's reference time in seconds.
	inline double getStartTime() const { return ( _startStamp * _stampToSeconds );	}

	//! Returns the timer's reference timestamp.
	inline Stamp getStartStamp() const { return _startStamp; }

	//! Sets the timer's reference timestamp.
	inline void setStartStamp( Stamp stamp ) { _startStamp = stamp; }

	//! Returns the multiplier that converts a Stamp to clock time in seconds.
	inline double getStampToSeconds() const { return _stampToSeconds; }

	//! Returns elapsed time (in seconds) since last restart.
	inline double elapsed() const
	{
		return ( ( computeCurrentStamp() - _startStamp ) * _stampToSeconds );
	}

	//! Returns elapsed time (in seconds) from this timer's reference Stamp up to the specified Stamp.
	inline double elapsed( Stamp stamp ) const
	{
		return ( ( stamp - _startStamp ) * _stampToSeconds );
	}

	//! Restarts the timer and returns elapsed time (in seconds) since last restart.
	inline double restart()
	{
		Stamp previousStamp = _startStamp;
		_startStamp = computeCurrentStamp();
		return ( ( _startStamp - previousStamp ) * _stampToSeconds );
	}

private:
	Stamp _startStamp;
	double _stampToSeconds;
};

} // namespace vr

#endif
