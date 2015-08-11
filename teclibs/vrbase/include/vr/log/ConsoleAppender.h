/*
 * vrbase
 * Copyright 2007-2009 CENPES/Petrobras Tecgraf/PUC-Rio
 */

#ifndef _VR_LOG_CONSOLE_APPENDER_H_
#define _VR_LOG_CONSOLE_APPENDER_H_

#include "Appender.h"

namespace vr {
namespace log {
/*!
    \addtogroup logging
    @{
 */

/*!
	Appends log events to stdout using a layout specified by the user. 
 */
class VRBASE_EXPORT ConsoleAppender : public Appender
{
public:
    //! Constructor that receives the Appender Layout (\see Layout).
    ConsoleAppender( const Layout* layout );
	
	// Does nothing
	virtual void close();

	//! Prints on the console the specified event.
    virtual void doAppend( const LoggingEvent& event );
};

/*! @} */ // end of group logging

} // namespace log
} // namespace vr

#endif
