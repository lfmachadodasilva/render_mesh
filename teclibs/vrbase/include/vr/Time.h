/*
 * vrbase
 * Copyright 2007-2009 CENPES/Petrobras Tecgraf/PUC-Rio
 */

#ifndef _VR_TIME_H_
#define _VR_TIME_H_

#include <iostream>

#include "Common.h"
#include "String.h"

//! Main namespace of this library.
namespace vr {

/*!
	\brief The Time class provides clock time functions.

	A Time object contains a clock time, i.e. the number of hours, minutes, seconds and milliseconds since midnight. 
	It can read the current time from the system clock. It provides functions for comparing
	times and for manipulating a time.

	Time uses the 24-hour clock format; it has no concept of AM/PM. Unlike DateTime, Time knows nothing about time zones or 
	daylight savings time (DST).

	A Time object is typically created either by giving the number of hours, minutes, seconds and milliseconds, or
	by using the static function getCurrentTime(), which creates a Time object that contains the system's local time. 
 */
class VRBASE_EXPORT Time
{
public:
	/*!
		Returns the current time as reported by the system clock.
	 */
	static Time currentTime();

	/*!
		Returns the difference in days of the normalized time????
	*/
	static int normalized( int& msec );

public:
	/*!
		Constructs a null, invalid time object. 
		\see isNull().
	 */
	Time();

	/*!
		Constructs a time with the total of milliseconds ms.
	 */
	Time( int ms );

	/*!
		Constructs a time with hour h, minute m, seconds s and milliseconds ms.
	 */
	Time( int h, int m, int s = 0, int ms = 0 );

	/*!
		Returns a Time object containing a time ms milliseconds later than the time of this object 
		(or earlier if ms is negative).
		Note that the time will wrap if it passes midnight. \see addSecs() for an example.
		\see addSecs() and getMSecsTo().
	*/
	inline Time addMSecs( int ms ) const { return Time( _msecs + ms ); }

	/*!
		Returns a Time object containing a time s seconds later than the time of this object 
		(or earlier if s is negative).
		Note that the time will wrap if it passes midnight.
		\see also addMSecs(), secsTo(), and DateTime::addSecs().
	*/
	inline Time addSecs( int s ) const { return Time( _msecs + ( s * 1000 ) ); }

	/*!
		Returns the millisecond part (0 to 999) of the time.
		\see getSecond(), getMinute() and getHour().	
	 */
	int getMSec() const;

	/*!
		Returns the second part (0 to 59) of the time.
		\see getMSec(), getHour() and getMinute().
	 */
	int getSecond() const;

	/*! 
		Returns the minute part (0 to 59) of the time.
		\see also getMSec(), getHour() and getSecond().
	 */
	int getMinute() const;

	/*!
		Returns the hour part (0 to 23) of the time.
		\see getMSec(), getMinute() and getSecond().
	 */
	int getHour() const;

	/*!
		Sets the time to hour h, minute m, seconds s and milliseconds ms.
		h must be in the range 0 to 23, m and s must be in the range 0 to 59 and ms must be in the range 0 to 999.
	 */
	void setTime( int h, int m, int s = 0, int ms = 0 );

	/*!
		Returns the number of milliseconds from this time to t. If t is earlier than this time, the number of 
		milliseconds returned is negative. Because Time measures time within a day and there are 86400 seconds 
		in a day, the result is always between -86400000 and 86400000 ms.
		\see also secsTo().		
	 */
	int getMSecsTo( const Time& t ) const;

	/*!
		Returns the number of seconds from this time to t. If t is earlier than this time, the number of seconds 
		returned is negative. Because Time measures time within a day and there are 86400 seconds in a day, the 
		result is always between -86400 and 86400.
		\see also addSecs() and DateTime::getSecsTo().
	 */
	int getSecsTo( const Time& t ) const;

	/*!
		?????????????
	 */
	int getTotalMSecs() const;

	/*!
		Returns true if the time is null (i.e., the Time object was not initialized); 
		otherwise returns false.
	 */
	bool isNull() const;

	/*!
		Returns the DateTime as a string, always in the form hh::mm::ss.
	 */
	String toString() const;
		
	// Operators:

	// Adds two times.
	Time operator+( const Time& t ) const;

	// Subtracts one time from another.
	Time operator-( const Time& t ) const;

	/*!
		Returns a Time object containing a time t later than the time of this object (or earlier if t is negative).
		Note that the time will wrap if it passes midnight.

		Examples:
		 Time n(14,  0,  0, 0);             // n == 14:00:00.000
		 Time t( 0, 30, 15, 200);			// t == 00:30:15.200
		 n += t;							// n == 14:30:15.200

		 Time n( 14,  0,  0, 0);            // n ==  14:00:00.000
		 Time t(-20, 30, 15, 000);  		// t == -20:30:15.000
		 n += t;							// n ==  17:29:45.000
		 \see getSecsTo().
	 */
	const Time& operator+=( const Time& t );

	/*!
		Returns a Time object containing a time t sooner than the time of this object (or later if t is negative).
		Note that the time will wrap if it passes midnight.
		 \see getSecsTo() and operator+=.
	 */
	const Time& operator-=( const Time& t );

	// Returns true if this time is different from t; otherwise returns false.
	inline bool operator!=( const Time& t ) const;

	//! Returns true if this time is earlier than t; otherwise returns false.
	inline bool operator<( const Time& t ) const;

	//! Returns true if this time is earlier than or equal to t; otherwise returns false.
	inline bool operator<=( const Time& t ) const;

	//! Returns true if this time is equal to t; otherwise returns false.
	inline bool operator==( const Time& t ) const;
	
	//! Returns true if this time is later than t; otherwise returns false.
	inline bool operator>( const Time& t ) const;

	//! Returns true if this time is later than or equal to t; otherwise returns false.
	inline bool operator>=( const Time& t ) const;

private:
	void normalize();

	int32 _msecs;
};

inline std::ostream& operator<<( std::ostream& stream, const Time& time )
{
	return stream << time.toString().data();
}

bool Time::operator!=( const Time & t ) const
{
	return !( _msecs == t._msecs );
}

bool Time::operator<( const Time& t ) const
{
	return ( _msecs < t._msecs );
}

bool Time::operator<=( const Time& t ) const
{
	return ( _msecs < t._msecs ) || ( _msecs == t._msecs );
}

bool Time::operator==( const Time& t ) const
{
	return ( _msecs == t._msecs );
}

bool Time::operator>( const Time& t ) const
{
	return ( _msecs > t._msecs );
}

bool Time::operator>=( const Time& t ) const
{
	return ( _msecs > t._msecs ) || ( _msecs == t._msecs );
}

} // namespace vr

#endif

