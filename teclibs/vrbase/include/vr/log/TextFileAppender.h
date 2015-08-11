/*
 * vrbase
 * Copyright 2007-2009 CENPES/Petrobras Tecgraf/PUC-Rio
 */

#ifndef _VR_LOG_TEXT_FILE_APPENDER_H_
#define _VR_LOG_TEXT_FILE_APPENDER_H_

#include "Appender.h"

namespace vr {
namespace log {
/*!
    \addtogroup logging
    @{
 */

/*!
	Defines a LogAppender that sends the output of a Log to a Text File.
 */
class VRBASE_EXPORT TextFileAppender : public Appender
{
public:
    //! Constructor that receives the File Name and Appender Layout (\see Layout).
    TextFileAppender( const String& filename, const Layout* layout );

    virtual ~TextFileAppender();

	//! Closes the current file handler.
	virtual void close();

	//! Prints on the current file the specified event.
	//! If the file or the layout are not valid, does nothing.s
    virtual void doAppend( const LoggingEvent& event );

protected:
	FILE* _fileHandler;	
};

/*! @} */ // end of group logging

} // namespace log
} // namespace vr

#endif
