/**
*	Algorithms to compute euclidean distance between geometric entities.
*	author: Paulo Ivson <psantos@tecgraf.puc-rio.br>
*	date:   5-Mar-2008
*/
#ifndef VRBV_DISTANCE_H
#define VRBV_DISTANCE_H

#include "common.h"
#include "defines.h"
#include <vr/Vec3.h>

namespace vrbv {

class VRBV_API Distance
{
public:
	// Plane must be in Hessian Normal Form
	static float between( const vr::Vec3f& point, const Plane& plane );

	// Precise distance from point to box
	static float between( const vr::Vec3f& point, const Box& box );
};

} // namespace vrbv

#endif // VRBV_DISTANCE_H
