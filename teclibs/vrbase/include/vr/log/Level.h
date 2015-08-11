/*
 * vrbase
 * Copyright 2007-2009 CENPES/Petrobras Tecgraf/PUC-Rio
 */

#ifndef _VR_LOG_LEVEL_H_
#define _VR_LOG_LEVEL_H_

#include "../String.h"
#include "../RefCounting.h"

namespace vr {
namespace log {
/*!
    \addtogroup logging
    @{
 */

/*!
    Defines a set of standard logging levels that can be used to control logging output.
    Clients should normally use the predefined level constants such as LogLevel::fatal().
 */
class VRBASE_EXPORT Level : public RefCounted
{
public:

	//! Available Level Values
	enum
	{
		OffValue = INT32_MAX,
		FatalValue = 50000,
		ErrorValue = 40000,
		WarnValue = 30000,
		InfoValue = 20000,
		DebugValue = 10000,
		TraceValue = 5000,
		AllValue = INT32_MIN
	};

    static Level* off();
	static Level* fatal();
	static Level* error();
	static Level* warn();
	static Level* info();
	static Level* debug();
	static Level* trace();
	static Level* all();

public:
	// Constructor
	Level( int level, const String& name );

	//! Get the name of the level.
	inline const String& getName() const { return _name; }

	//! Returns the integer representation of this level.
	inline int getLevel() const { return _level; }

    // Equals operator
    inline bool operator==( const Level& other ) const { return ( this->_level == other._level ); }

private:
	int _level;
	String _name;
};

/*! @} */ // end of group logging

} // namespace log
} // namespace vr

#endif
