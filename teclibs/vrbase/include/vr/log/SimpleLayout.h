/*
 * vrbase
 * Copyright 2007-2009 CENPES/Petrobras Tecgraf/PUC-Rio
 */

#ifndef _VR_LOG_SIMPLE_LAYOUT_H_
#define _VR_LOG_SIMPLE_LAYOUT_H_

#include "../Timer.h"
#include "Layout.h"

namespace vr {
namespace log {
/*!
    \addtogroup logging
    @{
 */

/*!
	Defines a basic layout in a "[%LineNumber] - [%TimeStamp] %Level %Message at %LineLocation" format
 */
class VRBASE_EXPORT SimpleLayout : public Layout
{
public:
	// Default constructor
	SimpleLayout();

	//! If true, add a line break to the end of the formatted string.
	void setPrintLineBreak( bool value );

	//! If true, print [main] to formatted string.
	void setPrintMain( bool value );

	//!Implement this method to create your own layout format.
	virtual void format( const LoggingEvent& event, String& output ) const;

private:
	bool _printLineBreak;
	bool _printMain;
	Timer _timer;
};

/*! @} */ // end of group logging

} // namespace log
} // namespace vr

#endif
