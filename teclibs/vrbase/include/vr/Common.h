/*
 * vrbase
 * Copyright 2007-2009 CENPES/Petrobras Tecgraf/PUC-Rio
 */

#ifndef _VR_COMMON_H_
#define _VR_COMMON_H_

#ifndef __cplusplus
#	error The vr base library requires a C++ compiler.
#endif

//! \file Common.h Includes the most basic macros and platform definitions.

#include "Platform.h"

/*!
    \addtogroup utilityfunc Utility Macros and Functions
    @{
 */

/*!
	\def VR_STATIC_CHECK( const_expr, id_msg )
    Evaluates a constant expression and, if the result is false, aborts the
	compilation with an error message.

	\param const_expr is a compile-time integral or pointer expression.
	\param id_msg is a C++ identifier that describes the error (it does not
		need to be defined). Something like 'invalid_element_size'.
 */
#define VR_STATIC_CHECK( const_expr, id_msg ) \
	{ vr::CompileTimeError<( (const_expr) != 0 )> ERROR_##id_msg; (void)ERROR_##id_msg; }

/*!
	\def VR_ARRAY_LENGTH( array )
	Returns the number of elements in a static array.

	\param array the name of a statically allocated array.
 */
#define VR_ARRAY_LENGTH( array )	(sizeof(array)/sizeof(array[0]))

/*! @} */ // end of group utilityfunc

//! Main namespace of this library.
namespace vr {

// Template trick to yield compile time errors:
template<int> struct CompileTimeError;
template<> struct CompileTimeError<true> {};

} // namespace vr

#endif // _VR_COMMON_H_
