/**
*	General intersection algorithms.
*	author: Paulo Ivson <psantos@tecgraf.puc-rio.br>
*	date:   7-Mar-2008
*/
#ifndef VRBV_INTERSECTION_H
#define VRBV_INTERSECTION_H

#include "common.h"
#include "defines.h"

namespace vrbv {

class VRBV_API Intersection
{
public:
	/**
	 *	Return code:
	 *		Totally inside:  +1
	 *		Totally outside: -1
	 *		Intersected:      0
	 *
	 *	Plane must be in Hessian Normal Form.
	 */
	static int between( const Plane& plane, const Box& box );
};

} // namespace vrbv

#endif // VRBV_INTERSECTION_H
