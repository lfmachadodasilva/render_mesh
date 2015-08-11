/*
 * vrbase
 * Copyright 2007-2009 CENPES/Petrobras Tecgraf/PUC-Rio
 */

#ifndef _VR_ALGEBRATYPES_H_
#define _VR_ALGEBRATYPES_H_

//! \file AlgebraTypes.h Includes all basic linear algebra classes.

#include <vr/Vec2.h>
#include <vr/Vec3.h>
#include <vr/Vec4.h>
#include <vr/Mat4.h>
#include <vr/Quat.h>

/*! \addtogroup algebra Basic Linear Algebra Classes
	@{
 */

/*!
	Imports all basic linear algebra classes into the current namespace.
	This is useful if you want to write <tt>Vec3f</tt>, <tt>Mat4d</tt>, etc. in your
	program but don't want to fully import the vr namespace.
 */
#define USING_VR_ALGEBRA_TYPES	\
	using vr::Vec2f;	\
	using vr::Vec2d;	\
	using vr::Vec3f;	\
	using vr::Vec3d;	\
	using vr::Mat4f;	\
	using vr::Mat4d;	\
	using vr::Quatf;	\
	using vr::Quatd;

/*! @} */ // end of group algebra

#endif // _VR_ALGEBRATYPES_H_
