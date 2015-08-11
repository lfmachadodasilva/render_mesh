/**
*	A generic oriented box, can be used as AABB or OBB.
*	author: Paulo Ivson <psantos@tecgraf.puc-rio.br>
*	author: Vitor Barata <vbarata@tecgraf.puc-rio.br>
*	date:   3-Mar-2008
*/
#ifndef VRBV_BOX_H
#define VRBV_BOX_H

#include <vr/Mat4.h>
#include <vr/Vec3.h>
#include "defines.h"

namespace vrbv {

class VRBV_API Box
{
public:
	vr::Vec3f center;  // Center point
	vr::Vec3f axis[3]; // Orthonormal basis
	vr::Vec3f extents; // Half-lengths along each basis' axis

	/**
	*  Input is a vr::vec3 array of size 8.
	*  Vertices are computed as follows:
	*     7+------+6
	*     /|     /|
	*    / |    / |
	*   / 3+---/--+2
	* 4+------+5 /    y  z
	*  | /    | /     | /
	*  |/     |/      |/
	* 0+------+1      *---x
	*/
	void computeVertices( vr::Vec3f* vertices ) const;
	/**
	*  Input is a float array of size 24 (3 coordinates per vertex).
	*  Vertices are computed as follows:
	*     7+------+6
	*     /|     /|
	*    / |    / |
	*   / 3+---/--+2
	* 4+------+5 /    y  z
	*  | /    | /     | /
	*  |/     |/      |/
	* 0+------+1      *---x
	*/
	void computeVerticesArray( float vertices[24] ) const;

	/**
	 * Convenience method to get the axis that has the greatest extents
	 */
	const vr::Vec3f& getLongestAxis() const;
	vr::Vec3f getLongestAxis( vr::Mat4<float> modelMatrix ) const;

	/**
	 * Method to get the surface area
	 */
	float getSurfaceArea();
};

} // namespace vrbv

#endif // VRBV_BOX_H
