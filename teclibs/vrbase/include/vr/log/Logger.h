/*
 * vrbase
 * Copyright 2007-2009 CENPES/Petrobras Tecgraf/PUC-Rio
 */

#ifndef _VR_LOG_LOGGER_H_
#define _VR_LOG_LOGGER_H_

#include "../String.h"
#include "../Exception.h"
#include "../RefCounting.h"
#include "Appender.h"
#include "Manager.h"
#include "LoggingEvent.h"
#include <vector>

namespace vr {
namespace log {

/*!
    \addtogroup logging Logging framework for C++ patterned after Apache's log4cxx.
    @{
 */

/*!
    This is the only kind of exception raised by the logging subsystem.
    \see Logger
 */
class Exception : public vr::Exception
{
public:
    Exception( const String& message ) : vr::Exception( message )
    {;}
};

/*!
    This is the central class in the logging system.
    Most logging operations, except configuration, are done through this class.
 */
class VRBASE_EXPORT Logger
{
	friend class Manager;

public:
	//! Retrieve a logger by name in current encoding. 
	static Logger* getLogger( const String& name );

public:
    //! Destructor
    ~Logger();

	//! Returns the logger's local name (e.g. ClassName). 
	inline const String& getName() const { return _name; }

    //! Returns the logger's full name (e.g. module.submodule.ClassName).
    inline const String& getFullName() const { return _fullName; }

	//! Returns the parent of this logger.
	inline Logger* getParent() const { return _parent; }

	//! Returns the assigned Level, if any, for this Logger. 
	inline const Level* getLevel() const { return _level.get(); }

	//! Set the level of this Logger. 
	void setLevel( const Level* level );

    /*!
        Set the additivity flag for this Logger instance.
        Additivity is set to true by default, that is children inherit
        the appenders of their ancestors by default. If this variable is
        set to false then the appenders found in the
        ancestors of this logger are not used. However, the children
        of this logger will inherit its appenders, unless the children
        have their additivity flag set to false too. See
        the user manual for more details. 
     */
    inline void setAditivity( bool value ) { _additive = value; }

    //! Returns whether this logger instance is additive.
    inline bool isAditive() { return _additive; }
	
	//! Returns the number of appenders in this logger.
	inline int getNumAppenders() const { return _appenders.size(); }
	
	//!	Get an appender in this logger by its index. \see getNumAppenders()
    inline const Appender* getAppender( int index ) const { return _appenders[index].get(); }

	//! Add a new appender to this logger. 
	void addAppender( Appender* appender );

	//! Remove the appender passed as parameter from the list of appenders. 
	void removeAppender( Appender* appender );

	//! Starting from this logger, search the logger hierarchy for a non-null level and return it. 
	const Level* getEffectiveLevel() const;

	//! This is the most generic printing method. It is intended to be invoked by wrapper classes.
	void log( const Level* level, const String& message, const LocationInfo& location ) const;

	//! Checks whether this logger is enabled for a given Level passed as parameter
	bool isEnabledFor( const Level* level ) const;

 	//! Close all attached appenders.
	void closeAppenders();

	//! Gets or creates a logger named 'name' as a direct child of this logger.
	Logger* getOrCreateChild( const char* name );

private:
	// Verifies if the logging subsystem has been initialized.
	// If not, raises an exception.
    void checkState() const;

	// Defines the _fullName parameter with the logger's complete name.
    void buildFullName( Logger* logger );

protected:
    // Constructor
    Logger( const String& name, Logger* parent );
    
private:
	// Call all appenders in the Log hierarchy starting at this Logger. 
	void callAppenders( const LoggingEvent& event ) const;

private:
    String _name;       // 'local' name, e.g. MyClass
    String _fullName;   // e.g. module.submodule.MyClass
	Logger* _parent;
	ref_ptr<const Level> _level;
	bool _additive;
	
	typedef std::vector<Logger*> LoggerList;
	LoggerList _children;
	
	typedef std::vector< ref_ptr<Appender> > AppenderList;
    AppenderList _appenders;
};

/*! @} */ // end of group logging

} // namespace log
} // namespace vr

/*!
    \addtogroup logging
    @{
 */

/*!
    Defines a <em>getter</em> function that returns a cached vr::log::Logger.
 */
#define VR_DEFINE_LOGGER( loggerName, getterName ) \
    static vr::log::Logger* getterName() { \
        static vr::log::Logger* s_logger = 0; \
        if( s_logger == 0 ) \
            s_logger = vr::log::Logger::getLogger( loggerName ); \
        return s_logger; \
    }

#ifndef VR_DISABLE_LOGGING
    //! Logs a message to a specified logger with a specified level. 
    #define VR_LOG( logger, level, message ) { \
        if( logger->isEnabledFor( level ) ) { \
            logger->log( level, message, VR_LOG_LOCATION ); } }

    //! Logs a message to a specified logger with the TRACE level.
    #define VR_LOG_TRACE( logger, message ) { \
        if( logger->isEnabledFor( vr::log::Level::trace() ) ) { \
            logger->log( vr::log::Level::trace(), message, VR_LOG_LOCATION ); } }

    //! Logs a message to a specified logger with the DEBUG level.
    #define VR_LOG_DEBUG( logger, message ) { \
        if( logger->isEnabledFor( vr::log::Level::debug() ) ) { \
            logger->log( vr::log::Level::debug(), message, VR_LOG_LOCATION ); } }

    //! Logs a message to a specified logger with the INFO level.
    #define VR_LOG_INFO( logger, message ) { \
        if( logger->isEnabledFor( vr::log::Level::info() ) ) { \
            logger->log( vr::log::Level::info(), message, VR_LOG_LOCATION ); } }

    //! Logs a message to a specified logger with the WARN level.
    #define VR_LOG_WARN( logger, message ) { \
        if( logger->isEnabledFor( vr::log::Level::warn() ) ) { \
            logger->log( vr::log::Level::warn(), message, VR_LOG_LOCATION ); } }

    //! Logs a message to a specified logger with the ERROR level. 
    #define VR_LOG_ERROR( logger, message ) { \
        if( logger->isEnabledFor( vr::log::Level::error() ) ) { \
            logger->log( vr::log::Level::error(), message, VR_LOG_LOCATION ); } }

    //! Logs a message to a specified logger with the FATAL level. 
    #define VR_LOG_FATAL( logger, message ) { \
        if( logger->isEnabledFor( vr::log::Level::fatal() ) ) { \
            logger->log( vr::log::Level::fatal(), message, VR_LOG_LOCATION ); } }

    //! Logs an error if the condition is not true.
    #define VR_LOG_ASSERT( logger, condition, message ) { \
        if( !(condition) && logger->isEnabledFor( vr::log::Level::error() ) ) { \
            logger->log( vr::log::Level::error(), message, VR_LOG_LOCATION ); } }
#else
    #define VR_LOG( logger, level, message ) 
    #define VR_LOG_TRACE( logger, message )
    #define VR_LOG_DEBUG( logger, message )
    #define VR_LOG_INFO( logger, message )
    #define VR_LOG_WARN( logger, message )
    #define VR_LOG_ERROR( logger, message )
    #define VR_LOG_FATAL( logger, message )
    #define VR_LOG_ASSERT( logger, condition, message )
#endif

/*! @} */ // end of group logging

#endif
