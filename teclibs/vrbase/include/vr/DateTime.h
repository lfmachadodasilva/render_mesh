/*
 * vrbase
 * Copyright 2007-2009 CENPES/Petrobras Tecgraf/PUC-Rio
 */

#ifndef _VR_DATE_TIME_H_
#define _VR_DATE_TIME_H_

#include "Common.h"
#include "String.h"
#include "Date.h"
#include "Time.h"

//! Main namespace of this library.
namespace vr {

/*!
	\brief The DateTime class provides date and time functions.

	A DateTime object contains a calendar date and a clock time (a "datetime"). 
	It is a combination of the Date and Time classes. It can read the current datetime 
	from the system clock. It provides functions for comparing datetimes and for manipulating 
	a DateTime by adding a number of seconds, days, months, or years.
 */
class VRBASE_EXPORT DateTime
{
public:
	
	/*! 
		Returns the current DateTime, as reported by the system clock, in the local time zone.
		See also Date::getCurrentDate(), Time::getCurrentTime().
	*/	
	static DateTime currentDateTime();

public:
	/*!
		Constructs a null DateTime (i.e. null date and null time). A null DateTime is invalid, since the date is invalid.
		\see isValid().
	 */
	DateTime();

	/*!
		Constructs a DateTime with the given date, a valid time (00:00:00.000).
	 */
	DateTime( const Date& date );

	/*!
		Constructs a DateTime with the given std::time_t DateTime.
	 */
	DateTime( time_t sysTime );

	/*!
		Constructs a DateTime with the given date and time, using the time specification 
		defined by spec. If date is valid and time is not, the time will be set to midnight.
	 */
	DateTime( const Date& date, const Time& time );

	/*!
		Returns a DateTime object containing a DateTime msecs milliseconds later than the 
		DateTime of this object (or earlier if msecs is negative).
		Note that the time will wrap if it passes midnight. \see addSecs() for an example.
		\see addSecs(), secsTo(), addDays(), addMonths(), addYears().
	*/
	DateTime addMSecs( int msecs ) const;

	/*!
		Returns a DateTime object containing a DateTime secs seconds later than the DateTime 
		of this object (or earlier if secs is negative).
	 */
	DateTime addSecs( int secs ) const;

	/*!
		Returns a DateTime object containing a DateTime ndays days later than the DateTime 
		of this object (or earlier if ndays is negative).		
	 */
	DateTime addDays( int ndays ) const;
	
	/*!
		Returns a DateTime object containing a DateTime nmonths months later than the 
		DateTime of this object (or earlier if nmonths is negative).
	 */
	DateTime addMonths( int nmonths ) const;

	/*!
		Returns a DateTime object containing a DateTime nyears years later than the 
		DateTime of this object (or earlier if nyears is negative).
	 */
	DateTime addYears( int nyears ) const;

	/*!
		Sets the date part of this DateTime to date. If no time is set, it is set to midnight.
		\see getDate, setTime.
	 */
	void setDate( const Date& date );

	/*!
		Returns the date part of the DateTime.
		\see setDate, getTime.
	 */
	Date getDate() const;

	 /*!
		Sets the time part of this DateTime to time.
		\see getTime, setDate.
	  */
	void setTime( const Time& time );

	/*!
		Returns the time part of the DateTime.
		\see setTime, getDate.
	 */
	Time getTime() const;

	/*!
		Returns the number of seconds from this DateTime to the other DateTime. If the other DateTime is earlier 
		than this DateTime, the value returned is negative. 
	 */
	int getSecsTo( const DateTime& other ) const;

	/*!
		Returns the number of days from this DateTime to the other DateTime. 
		If the other DateTime is earlier than this DateTime, the value returned is negative.
	 */
	int getDaysTo( const DateTime& other ) const;

	/*!
		Returns true if both the date and the time are null; otherwise returns false. A null DateTime is invalid.
		\see Date::isNull(), Time::isNull().
	 */
	bool isNull() const;

	/*!
		Returns the DateTime as a string. The format parameter determines the format of the result string.
		The format string is defined in the same way as the strftime function uses it.

		Example:
			DateTime( Date( 2009, 2, 28 ), Time( 14, 0, 3 ) ) -> "2009-02-28 14:00:03"
	 */
	String toString() const;

	//!	Returns the date and time as a time_t value corresponding to time since the Epoch 
	//! (00:00:00 UTC, January 1, 1970), measured in seconds. \see DateTime( time_t ).
	time_t toSystemTime();

	// Comparison Operators:

	//!	Returns true if this date is different from d; otherwise returns false.
	bool operator!=( const DateTime& dt ) const;

	//!	Returns true if this date is earlier than d; otherwise returns false.
	bool operator<( const DateTime& dt ) const;

	//! Returns true if this date is earlier than or equal to d; otherwise returns false.
	bool operator<=( const DateTime& dt ) const;

	//!	Returns true if this date is equal to d; otherwise returns false.
	bool operator==( const DateTime& dt ) const;

	//!	Returns true if this date is later than d; otherwise returns false.
	bool operator>( const DateTime& dt ) const;

	//!	Returns true if this date is later than or equal to d; otherwise returns false.
	bool operator>=( const DateTime& dt ) const;

private:
	Time _time;
	Date _date;
};

} // namespace vr

#endif

