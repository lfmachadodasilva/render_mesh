/*
 * vrbase
 * Copyright 2007-2009 CENPES/Petrobras Tecgraf/PUC-Rio
 */

#ifndef _VR_LOG_LAYOUT_H_
#define _VR_LOG_LAYOUT_H_

#include "../String.h"
#include "../RefCounting.h"
#include "LoggingEvent.h"

namespace vr {
namespace log {
/*!
    \addtogroup logging
    @{
 */

/*!
	Abstract class that makes it possible for you to extend 
	and create your own log layout format.
*/
class VRBASE_EXPORT Layout : public RefCounted
{
public:
    // Destructor
    virtual ~Layout()
    {;}

    //! Implement this method to create your own layout format.
    virtual void format( const LoggingEvent& event, String& output ) const = 0;

    //! Returns the content type output by this layout. Default content type is "text/plain".
    virtual String getContentType() const { return String( "text/plain" ); }

    //! Append the header for the layout format. Default header is empty;
    virtual void appendHeader( String& ) {;}

    //! Append the footer for the layout format. Default footer is empty;
    virtual void appendFooter( String& ) {;}
};

/*! @} */ // end of group logging

} // namespace log
} // namespace vr

#endif
