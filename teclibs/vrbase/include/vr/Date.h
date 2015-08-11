/*
 * vrbase
 * Copyright 2007-2009 CENPES/Petrobras Tecgraf/PUC-Rio
 */

#ifndef _VR_DATE_H_
#define _VR_DATE_H_

#include <iostream>

#include "Common.h"
#include "String.h"

//! Main namespace of this library.
namespace vr {

/*!
	\brief The Date class provides date functions.
	
	A Data class that represent dates accurately over a very wide range, running from 4713BC 
	to 9999AD, and handling the various calendar corrections, primarily the Julian/Gregorian 
	changeover.
 */
class VRBASE_EXPORT Date
{
public:
	/*!
		Returns the current date, as reported by the system clock.
		See also Time::getCurrentTime() and DateTime::getCurrentDateTime().
	 */
	static Date currentDate();

	//! Returns true if the given year is a leap year.
	static bool isLeapYear( int year );

	//! Performs a physical conversion from YMD form to Julian day number.
	static int32 ymdToJulianDay( int year, int month, int day );

	//! Performs a physical conversion from a Julian day number to YMD values.
    static void julianDayToYmd( int32 julianDay, int &year, int &month, int &day );

public:
	/*!
	 	Default constructor that initializes the object to January 1, 4713BC.
	 */
    Date();

	//! Constructs a date from time_t time since the Epoch (00:00:00 UTC, January 1, 1970), 
	//! measured in seconds.
	Date( time_t time );

	/*!
		Constructs a date with year y, month m and day d.
		Ex: 
			Date d( 2005, 2, 23 ); // day 23 of February
	 */
	Date( int y, int m, int d );

	//! Destroys the date.
	~Date();

	/*!
		Returns a Date object containing a date ndays later than the date of this object 
		(or earlier if ndays is negative). \see addMonths(), addYears(), and getDaysTo().
	 */
	Date addDays( int ndays ) const;

	/*!		
		Returns a Date object containing a date nmonths later than the date of this object 
		(or earlier if nmonths is negative). \see addDays() and addYears().	
	 */
	Date addMonths( int nmonths ) const;

	/*!
		Returns a Date object containing a date nyears later than the date of this object 
		(or earlier if nyears is negative).
		\see addDays() and addMonths().
	 */
	Date addYears( int nyears ) const;

	//! Returns the day of the month (1 to 31) of this date. \see getYear(), getMonth(), and getDayOfWeek().
	int getDay() const;

	/*!
		Returns the number corresponding to the month of this date, using the following convention:

		1 = "January"
		2 = "February"
		3 = "March"
		4 = "April"
		5 = "May"
		6 = "June"
		7 = "July"
		8 = "August"
		9 = "September"
		10 = "October"
		11 = "November"
		12 = "December"

		\see getYear() and getDay().
	 */
	int getMonth() const;

	//! Returns the year of this date. \see getMonth() and getDay().
	int getYear() const;

	/*!
		Returns true if the date is null (i.e., the Date object was not initialized); 
		otherwise returns false.
	 */
	bool isNull() const;

	//!	Set the date to the given year, month and day.
	inline void setYMD( int year, int month, int day );

	//! Retrieve the year, month and day, respectively, that represents this date.
	inline void getYMD( int &year, int &month, int &day );

	/*!
		Returns the number of days from this date to d (which is negative if d is earlier than this
		date). 
		Example:

		Date d1(1995, 5, 17);  // May 17, 1995
		Date d2(1995, 5, 20);  // May 20, 1995
		d1.daysTo(d2);          // returns 3
		d2.daysTo(d1);          // returns -3
		\see addDays().
	 */
	int getDaysTo( const Date& d ) const;

	/*!
		Returns the day of week for this date, using the following convention:
		
		Monday		=  1,
		Tuesday	 	=  2,
		Wednesday	=  3,
		Thursday	=  4,
		Friday		=  5,
		Saturday	=  6,
		Sunday		=  7

		\see getDay().
	*/
	int getDayOfWeek() const;

	//! Returns whether the current year is leap.
	bool isLeapYear();

	//! Returns this date in ascii in the form "YYYY-MM-DD".
	String toString() const;

	//!	Returns the date as a time_t value corresponding to time since the Epoch 
	//! (00:00:00 UTC, January 1, 1970), measured in seconds. \see Date( time_t ).
	time_t toSystemTime();

	// Operators:

    // Arithmetic:
	inline Date operator+( int32 ndays ) const;
	inline Date operator-( int32 ndays ) const;

	// Arithmetic updates:
	inline Date& operator+=( int32 ndays );
	inline Date& operator-=( int32 ndays );

	// Comparison:

	//!	Returns true if this date is different from d; otherwise returns false.
	inline bool operator!=( const Date& d ) const;

	//!	Returns true if this date is earlier than d; otherwise returns false.
	inline bool operator<( const Date& d ) const;

	//! Returns true if this date is earlier than or equal to d; otherwise returns false.
	inline bool operator<=( const Date& d ) const;

	//!	Returns true if this date is equal to d; otherwise returns false.
	inline bool operator==( const Date& d ) const;

	//!	Returns true if this date is later than d; otherwise returns false.
	inline bool operator>( const Date& d ) const;
	
	//!	Returns true if this date is later than or equal to d; otherwise returns false.
	inline bool operator>=( const Date& d ) const;

private:
	//! Auxiliary constructor used by operators for efficiency sake.
	inline Date( int32 julianDay ) : _julianDay( julianDay )
	{;}

	//! Checks if the date isn't null. Otherwise, throws an DateException.
	void checkDate() const;

private:
	int32 _julianDay;
};

inline std::ostream& operator<<( std::ostream& stream, const Date& date )
{
	return stream << date.toString().data();
}

void Date::setYMD( int year, int month, int day )
{
	_julianDay = ymdToJulianDay( year, month, day );
}

void Date::getYMD( int &y, int &m, int &d )
{
	julianDayToYmd( _julianDay, y, m, d );
}

Date Date::operator+( int32 ndays ) const
{
	return Date( _julianDay + ndays );
}

Date Date::operator-( int32 ndays ) const
{
	return Date( _julianDay - ndays );	
}

Date& Date::operator+=( int32 ndays )
{
	_julianDay += ndays;
	return *this;
}

Date& Date::operator-=( int32 ndays )
{
	_julianDay -= ndays;
	return *this;
}

bool Date::operator!=( const Date& d ) const
{
	return _julianDay != d._julianDay;
}

bool Date::operator<( const Date& d ) const
{
	return _julianDay < d._julianDay;
}

bool Date::operator<=( const Date& d ) const
{
	return _julianDay <= d._julianDay;
}

bool Date::operator==( const Date& d ) const
{
	return _julianDay == d._julianDay;
}

bool Date::operator>( const Date& d ) const
{
	return _julianDay > d._julianDay;
}

bool Date::operator>=( const Date& d ) const
{
	return _julianDay >= d._julianDay;
}

} // namespace vr

#endif

