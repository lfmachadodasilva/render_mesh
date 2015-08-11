/*
 * vrbase
 * Copyright 2007-2009 CENPES/Petrobras Tecgraf/PUC-Rio
 */

#ifndef _VR_PLATFORM_H_
#define _VR_PLATFORM_H_

//! \file Platform.h Platform Info and Portable Types

#include "Config.h"

// Define NULL pointer value
#ifndef NULL
	#ifdef __cplusplus
		#define NULL	0
	#else
		#define NULL	((void *)0)
	#endif
#endif

// Recognized operating systems (VR_OS_x):
#if defined(__APPLE__) && (defined(__GNUC__) || defined(__xlC__) || defined(__xlc__))
    #define VR_OS_MAC
    #define VR_OS_BSD4
    #ifdef __LP64__
        #define VR_OS_MAC64
    #else
        #define VR_OS_MAC32
    #endif
#elif defined(__CYGWIN__)
    #define VR_OS_CYGWIN
#elif defined(MSDOS) || defined(_MSDOS)
    #define VR_OS_MSDOS
#elif !defined(SAG_COM) && (defined(WIN64) || defined(_WIN64) || defined(__WIN64__))
    #define VR_OS_WIN32
    #define VR_OS_WIN64
#elif !defined(SAG_COM) && (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))
    #define VR_OS_WIN32
#elif defined(__linux__) || defined(__linux)
    #define VR_OS_LINUX
#elif defined(__FreeBSD__) || defined(__DragonFly__)
    #define VR_OS_FREEBSD
    #define VR_OS_BSD4
#elif defined(__NetBSD__)
    #define VR_OS_NETBSD
    #define VR_OS_BSD4
#elif defined(__OpenBSD__)
    #define VR_OS_OPENBSD
    #define VR_OS_BSD4
#elif defined(__sgi)
    #define VR_OS_IRIX
#else
    #error Operating system unknown or unsupported by vrbase.
#endif

#if defined(VR_OS_WIN32) || defined(VR_OS_WIN64)
    #define VR_OS_WIN
#endif

#if defined(VR_OS_MSDOS) || defined(VR_OS_WIN)
    #undef VR_OS_UNIX
#elif !defined(VR_OS_UNIX)
    #define VR_OS_UNIX
#endif

// Recognized compilers (VR_CC_x)
#if defined(_MSC_VER)
    #define VR_CC_MSVC
    #if defined(__INTEL_COMPILER)
        #define VR_CC_INTEL
    #endif
#elif defined(__GNUC__)
    #define VR_CC_GNU
    #if defined(__MINGW32__)
        #define VR_CC_MINGW
    #endif
    #if defined(__INTEL_COMPILER)
        #define VR_CC_INTEL
    #endif
#endif

// Portable macro to 'force' inlining of a function
#if defined(_MSC_VER)
	#define VR_FORCEINLINE	__forceinline
#elif defined(__GNUG__)
	#define VR_FORCEINLINE	inline __attribute__((always_inline))
#else
	#error Oops! The VR_FORCEINLINE macro was not defined for this compiler!
#endif

#if defined(__GNUG__)
	#include <sys/types.h>
#endif

// Portable shared-library interface attributes:
#if defined(VR_OS_WIN)
    #if defined(vrbase_EXPORTS)
        #define VRBASE_EXPORT __declspec(dllexport)
        #define VRBASE_HEXPORT __declspec(dllexport)
    #elif defined(VRBASE_STATIC)
        #define VRBASE_EXPORT
        #define VRBASE_HEXPORT
    #else
        #define VRBASE_EXPORT __declspec(dllimport)
        #define VRBASE_HEXPORT __declspec(dllexport)
    #endif
#else
    #define VRBASE_EXPORT
    #define VRBASE_HEXPORT
#endif

//! Wraps the signed 64-bit integer literal in a platform-independent way.
#if defined(VR_OS_WIN) && !defined(VR_CC_GNU)
    #define VR_INT64_C( c ) c ## i64
    #define VR_UINT64_C( c ) c ## ui64
#elif VR_POINTER_SIZE == 8 && !defined(VR_OS_MAC)
    #define VR_INT64_C( c ) c ## L
    #define VR_UINT64_C( c ) c ## UL
#else
    #define VR_INT64_C( c ) c ## LL
    #define VR_UINT64_C( c ) c ## ULL
#endif

namespace vr {

// Portable Integer Types.
#if defined(VR_CC_MSVC)
	typedef __int8				int8;
	typedef __int16				int16;
	typedef __int32				int32;
	typedef __int64				int64;
	typedef unsigned __int8		uint8;
	typedef unsigned __int16	uint16;
	typedef unsigned __int32	uint32;
	typedef unsigned __int64	uint64;
#elif defined(VR_CC_GNU)
	typedef int8_t				int8;
	typedef int16_t				int16;
	typedef int32_t				int32;
	typedef int64_t				int64;
	typedef u_int8_t			uint8;
	typedef u_int16_t			uint16;
	typedef u_int32_t			uint32;
	typedef u_int64_t			uint64;
#else
	#error Oops! The portable integer types were not defined for this compiler!
#endif

// Limits for the portable integer types.
// (current definitions are only valid for x86 platforms)
#ifdef VR_OS_MAC
	#undef INT8_MIN
	#undef INT8_MAX
	#undef UINT8_MAX

	#undef INT16_MIN
	#undef INT16_MAX
	#undef UINT16_MAX

	#undef INT32_MIN
	#undef INT32_MAX
	#undef UINT32_MAX

	#undef INT64_MIN
	#undef INT64_MAX
	#undef UINT64_MAX
#endif

const int8		INT8_MIN	= -127 - 1;
const int8		INT8_MAX	=  127;
const uint8		UINT8_MAX	=  0xFF;

const int16		INT16_MIN	= -32767 - 1;
const int16		INT16_MAX	=  32767;
const uint16	UINT16_MAX	= 0xFFFF;

const int32		INT32_MIN	= -2147483647 - 1;
const int32		INT32_MAX	=  2147483647;
const uint32	UINT32_MAX	=  0xFFFFFFFF;

#if defined(VR_CC_MSVC)
const int64		INT64_MAX	= 0x7FFFFFFFFFFFFFFF;
const uint64	UINT64_MAX	= 0xFFFFFFFFFFFFFFFF;
#else
const int64		INT64_MAX	= 0x7FFFFFFFFFFFFFFFLL;
const uint64	UINT64_MAX	= 0xFFFFFFFFFFFFFFFFULL;
#endif
const int64		INT64_MIN	= -INT64_MAX - 1;

} // namespace vr

/*!
	Imports all portable integer types into the current namespace.
	This is useful if you want to write <tt>uint8</tt>, <tt>int32</tt>, etc. in your
	program but don't want to fully import the vr namespace.
 */
#define USING_VR_INTEGER_TYPES	\
	using vr::int8;		\
	using vr::int16;	\
	using vr::int32;	\
	using vr::int64;	\
	using vr::uint8;	\
	using vr::uint16;	\
	using vr::uint32;	\
	using vr::uint64;

#endif
