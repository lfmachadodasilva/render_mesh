/*
 * vrbase
 * Copyright 2007-2009 CENPES/Petrobras Tecgraf/PUC-Rio
 */

#ifndef _VR_ROOTSOLVER_H_
#define _VR_ROOTSOLVER_H_

#include "Common.h"

namespace vr {

/*!
	\defgroup root_solving Basic root solving algorithms
	@{
*/

/*!
	All code based on Graphics Gems I
	http://tog.acm.org/GraphicsGems/gems/Roots3And4.c
*/

/*!
	Ax^2 + Bx + C = 0
	Receives 3 polynomial coeffs and finds at most 2 roots.
	Return number of roots found.
*/
int VRBASE_EXPORT solveQuadric( double coeffs[3], double roots[2] );

/*!
	Ax^3 + Bx^2 + Cx + D = 0
	Receives 4 polynomial coeffs and finds at most 3 roots.
	Return number of roots found.
*/
int VRBASE_EXPORT solveCubic( double coeffs[4], double roots[3] );

/*!
	Ax^4 + Bx^3 + Cx^2 + Dx + E = 0
	Receives 5 polynomial coeffs and finds at most 4 roots.
	Return number of roots found.
*/
int VRBASE_EXPORT solveQuartic( double coeffs[5], double roots[4] );

/*! @} */ // end of group root_solving

} // namespace vr

#endif // _VR_ROOTSOLVER_H_
