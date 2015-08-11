/*
 * vrbase
 * Copyright 2007-2009 CENPES/Petrobras Tecgraf/PUC-Rio
 */

#ifndef _VR_LOG_APPENDER_H_
#define _VR_LOG_APPENDER_H_

#include "../RefCounting.h"
#include "Layout.h"
#include "Manager.h"
#include <vector>

namespace vr {
namespace log {
/*!
    \addtogroup logging
    @{
 */

/*!
	Interface class that makes it possible for you to implement your 
	own strategies for outputting log statements.
*/
class VRBASE_EXPORT Appender : public RefCounted
{
public:	
	// Destructor
    virtual ~Appender()
    {;}

    //! Returns this appenders layout.
    inline const Layout* getLayout() const { return _layout.get(); }

    //! Set the Layout for this appender.
    inline void setLayout( const Layout* layout ) { _layout = layout; }

	//! Log in Appender specific way.
    virtual void doAppend( const LoggingEvent& event ) = 0;

    //! Release any resources allocated within the appender such as file handles, network connections, etc.
    virtual void close()
    {;}

protected:
    Appender( const Layout* layout ) : _layout( layout )
    {;}

private:
    vr::ref_ptr<const Layout> _layout;
};

/*! @} */ // end of group logging

} // namespace log
} // namespace vr

#endif
