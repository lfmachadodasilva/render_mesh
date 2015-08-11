/*
 * vrbase
 * Copyright 2007-2009 CENPES/Petrobras Tecgraf/PUC-Rio
 */

#ifndef _VR_LOG_MANAGER_H_
#define _VR_LOG_MANAGER_H_

#include "../Common.h"
#include <map>

namespace vr {

class String;

namespace log {

class Logger;
class Appender;

/*!
    \addtogroup logging
    @{
 */

/*!
    \brief Class that manages Logger instances.

    Before the logging module can be used one of the initialize() overloads must be called.
	Use the Manager class to retrieve Logger instances. 
 */
class VRBASE_EXPORT Manager
{
public:
    //! Configures the root logger to use the ConsoleAppender appender.
    static bool initialize();

    //! Configures the root logger to use the specified appender.
    static bool initialize( Appender* appender );
	
	//! Shuts down the logging subsystem, destroying the root logger.
	//! Only call this at program termination, for cleanup.
	static void shutdown();

    //! Retrieves or creates a logger using the specified name.
    static Logger* getLogger( const String& name );

    /*!
        Retrieves the root logger.
        The root logger resides at the top of the logger hierarchy. It is exceptional in two ways:
          -# it always exists,
          -# it cannot be retrieved by name.
     */
    static Logger* getRootLogger();

private:
    static Logger* sm_rootLogger;
	static bool sm_wasInitialized;
};

/*! @} */ // end of group logging

} // namespace log
} // namespace vr

#endif
