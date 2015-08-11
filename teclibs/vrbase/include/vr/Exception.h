/*
 * vrbase
 * Copyright 2007-2009 CENPES/Petrobras Tecgraf/PUC-Rio
 */

#ifndef _VR_EXCEPTION_H_
#define _VR_EXCEPTION_H_

#include "Common.h"
#include "String.h"
#include <exception>

namespace vr {

/*!
    Base Exception class. All exceptions thrown within the vr namespace must inherit from this class.
 */
class VRBASE_EXPORT Exception : public std::exception
{
public:
	//! Constructs an Exception with the specified message.
	Exception( const String& message ) : _message( message )
	{;}

	//! Constructs a copy of an Exception.
	Exception( const Exception& other ) : std::exception()
	{
		_message = other._message;
	}

	//! Destructor
	virtual ~Exception() throw();

	//! Returns the exception message.
	const String& getMessage() const
	{
		return _message;
	}

	//! Updates the exception message.
	void setMessage( const String& message )
	{
		_message = message;
	}

	//! Returns the exception message.
	virtual const char* what() const throw();

private:
	// forbid copies
    Exception& operator=( const Exception& )
    {
        return *this;
    }

private:
	String _message;
};

/*!
    This is the only kind of exception raised by Date methods.
    \see Date
 */
class DateException : public Exception
{
public:
    DateException( const String& message ) : Exception( message )
    {;}
};

/*!
    Raised from methods when an object is at an invalid state.
 */
class InvalidStateException : public Exception
{
public:
    InvalidStateException( const String& message ) : Exception( message )
    {;}
};

/*!
    This exception is raised whenever an IO operation fails.    
 */
class IOException : public Exception
{
public:
    IOException( const String& message ) : Exception( message )
    {;}
};

/*!
    This is the only kind of exception raised by String methods.
    \see String StringList StringInputStream
 */
class StringException : public Exception
{
public:
    StringException( const String& message ) : Exception( message )
    {;}
};

} // namespace vr

#endif
