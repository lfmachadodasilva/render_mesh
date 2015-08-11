/**
*	Debug defines and functions
*	author: Vitor Barata <vbarata@tecgraf.puc-rio.br>
*	date:   1-Out-2010
*/
#ifndef VDLIB_DEBUG_H_
#define VDLIB_DEBUG_H_

#include <vdlib/common.h>

//#define DEBUG_QUERY_POOL
//#define DEBUG_QUERY_QUEUE
//#define DEBUG_QUERY_COUNTERS
//#define DEBUG_CULLER_ALGORITHM
//#define DEBUG_CULLER_MULTIQUERY
//#define DEBUG_CULLER_TIGHTBBOX
//#define DEBUG_CULLER_COUNTERS

namespace vdlib {

#ifdef DEBUG_QUERY_POOL
	void debugQueryPool ( const char* format, ... );
#else
	inline void debugQueryPool ( const char* format, ... ) {}
#endif

#ifdef DEBUG_QUERY_QUEUE
	void debugQueryQueue ( const char* format, ... );
#else
	inline void debugQueryQueue ( const char* format, ... ) {}
#endif

#ifdef DEBUG_CULLER_ALGORITHM
	void debugAlgorithm ( const char* format, ... );
#else
	inline void debugAlgorithm ( const char* format, ... ) {}
#endif

#ifdef DEBUG_CULLER_MULTIQUERY
	void debugMultiQuery ( const char* format, ... );
#else
	inline void debugMultiQuery ( const char* format, ... ) {}
#endif

#ifdef DEBUG_CULLER_TIGHTBBOX
	void debugTightBBox ( const char* format, ... );
#else
	inline void debugTightBBox ( const char* format, ... ) {}
#endif

} // namespace vdlib

#endif // VDLIB_DEBUG_H_
