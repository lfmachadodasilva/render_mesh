/*
 * vrbase
 * Copyright 2007-2009 CENPES/Petrobras Tecgraf/PUC-Rio
 */

#ifndef _VR_LOG_LOGGING_EVENT_H_
#define _VR_LOG_LOGGING_EVENT_H_

#include "../Timer.h"
#include "../String.h"
#include "../RefCounting.h"
#include "Level.h"

namespace vr {
namespace log {

class Logger;

/*!
    \addtogroup logging
    @{
 */

/*!
	This class represents the location (and its properties, such as class, 
	method, line, file) of a logging statement.
 */
class VRBASE_EXPORT LocationInfo
{
public:
    static const char* CLASS_UNAVAILABLE;
    static const char* METHOD_UNAVAILABLE;

	//! Constructor.
	//! @param fileName       The full path of the source file. This can be obtained with the macro __FILE__.
	//! @param fullMethodName The fully-qualified name of the function/method, e.g.:
	//!                         "int vr::Foo::bar(const vr::String&, void*)"
	//!                       This can be obtained with the macro __VR_LOG_FUNC__.
	//! @param methodName     The name of the method, stripped of its argument list, e.g.:
	//!                         "vr::Foo::bar" (on Visual Studio)
	//!                         "bar" (on GCC)
	//!                       This can be obtained with the macro __VR_LOG_STRIP_FUNC__
	//! @param lineNumber     This can be obtained with the macro __LINE__.
	LocationInfo( const char* const fileName, const char* const fullMethodName, const char* methodName, int lineNumber );

	//! Return the class name of the call site.
    inline const String& getClassName() const { return _className; }

    //! Returns the method name of the caller.
    inline const char* getMethodName() const { return _bareMethodName; }

    //! Retrieves the full method name (e.g. int Class::method())
    inline const char* getFullMethodName() const { return _fullMethodName; }

	//! Return the file name of the caller.
    inline const char* getFileName() const { return _fileName; }

	//! Returns the line number of the caller.
    inline int getLineNumber() const { return _lineNumber; }

private:
    int _lineNumber;                // caller's line number.
    const char* _fileName;          // caller's file name.
    const char* _fullMethodName;    // caller's fully-qualified method name.
    const char* _bareMethodName;    // caller's stripped-down method name, without the namespace/class/arguments
    String _className;
};

// platform-dependent definition for VR_LOG_LOCATION
#ifndef VR_LOG_LOCATION
    #ifdef _MSC_VER
        #if _MSC_VER >= 1300
            #define __VR_LOG_FUNC__ __FUNCSIG__
        #endif
        #define __VR_LOG_STRIP_FUNC__ __FUNCTION__
    #elif defined( __GNUC__ )
        #define __VR_LOG_FUNC__ __PRETTY_FUNCTION__
        #define __VR_LOG_STRIP_FUNC__ __FUNCTION__
    #endif
    #ifndef __VR_LOG_FUNC__
        #define __VR_LOG_FUNC__ ""
    #endif
    #ifndef __VR_LOG_STRIP_FUNC__
        #define __VR_LOG_STRIP_FUNC__ ""
    #endif
    //! Expands to a vr::log::LocationInfo with info about the line and function where this macro was called.
    #define VR_LOG_LOCATION vr::log::LocationInfo( __FILE__, __VR_LOG_FUNC__, __VR_LOG_STRIP_FUNC__, __LINE__ )
#endif


/*!
	LoggingEvent is the internal representation of logging events.
	When an affirmative decision is made to log then a LoggingEvent instance is created.
	This instance is passed around to the different vr::Log components.
 */
class VRBASE_EXPORT LoggingEvent
{
public:
	//! Returns the time when the application started, in seconds elapsed since 01.01.1970.
    static Timer::Stamp getStartTime();

public:
	//! Constructor
	LoggingEvent( const Logger* logger, const Level* level, const String& message, const LocationInfo& location )
        : _logger( logger ), _level( level ), _message( message ), _locationInfo( location )
    {;}

    //! Returns the logger that generated the event.
    inline const Logger* getLogger() const { return _logger; }

	//! Return the level of this event.
    inline const Level* getLevel() const { return _level.get(); }

	//! Return the message for this logging event. 
    inline const String getMessage() const { return _message; }

    //! Returns info about the location in the source code where the log was generated.
    inline const LocationInfo& getLocationInfo() const { return _locationInfo; }

private:
    const Logger* _logger;
    vr::ref_ptr<const Level> _level;
    String _message;
	LocationInfo _locationInfo;
};

/*! @} */ // end of group logging

} // namespace log
} // namespace vr

#endif
