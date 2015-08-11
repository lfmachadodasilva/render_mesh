/**
*	Convenience class for storing a plane in 3D.
*	author: Paulo Ivson <psantos@tecgraf.puc-rio.br>
*	date:   5-Mar-2008
*/
#ifndef VRBV_PLANE_H
#define VRBV_PLANE_H

#include <vr/Vec3.h>
#include "defines.h"

namespace vrbv {

class VRBV_API Plane
{
public:
	// normal   = ( a, b, c )
	// position = d
	void set( float a, float b, float c, float d );

	/**
	*	Sets plane in Hessian Normal Form
	*	n = normalized plane normal
	*	p = point on plane
	*	Then plane is defined as: 
	*		n*p = -d
	*	and d is the distance of the plane from the origin.
	*  Here, the sign of d determines the side of the plane on which the origin is located. 
	*  If d > 0, it is in the half-space determined by the direction of the normal.
	*  If d < 0, it is in the opposite half-space.
	*/ 
	void set( const vr::Vec3f& _normal, const vr::Vec3f& pointOnPlane );

	// Correctly update position according to normalization.
	// Attention: will crash if normal length is sufficiently close to zero!
	void normalize();

	vr::Vec3f normal;
	float position;
};

} // namespace vrbv

#endif // VRBV_PLANE_H
