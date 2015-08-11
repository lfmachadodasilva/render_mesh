/**
 *	Convenience class for storing a plane in 3D (Hessian form).
 *	author: Cesar Palomo <cpalomo@tecgraf.puc-rio.br>
 *	date:   30-Mar-2010
 */
#ifndef GEOMS_PLANE_H
#define GEOMS_PLANE_H

#include <alg/vector.h>
#include <ds/defines.h>
#include "defines.h"

#define GEOMS_NORM_EPSILON_ZERO 1.0e-5

namespace geoms {

class GEOMS_API Plane
{
public:
  Plane () 
  : degenerate(false)
  {
  }

  /**
   *  Set plane in Hessian Normal Form
   *  n = normalized plane normal
   *  p = point on plane
   *  Then plane is defined as: 
   *    n*p = -d
   *  and d is the distance of the plane from the origin.
   *  Here, the sign of d determines the side of the plane on which the origin is located. 
   *  If d > 0, it is in the half-space determined by the direction of the normal.
   *  If d < 0, it is in the opposite half-space.
   */ 
  DS_FORCE_INLINE void Set (const AlgVector& n, const AlgVector& point_on_plane)
  {
    normal = n;
    d = -(n.Dot(point_on_plane));
  }

  /**
   * Set plane with 3 given points laying on plane.
   * Points assumed to be non-colinear.
   */
  void Set (const float v0[3], const float v1[3], const float v2[3]);

  /**
   * Set plane with 3 given points laying on plane.
   * Points assumed to be non-colinear.
   */
  void Set (const float v[9])
  {
    Set(&v[0], &v[3], &v[6]);
  }

  /**
   * Return distance from point p to plane.
   * If p is in the half-space determined by the direction of normal, then return > 0.
   * If it is in the other half-space, then return < 0;
   */
  DS_FORCE_INLINE float Distance (const AlgVector& p) const
  {
    return normal.Dot(p) + d;
  }


  // Correctly update position according to normalization: 
  // ensures plane is in Hessian form.
  // Attention: will crash if normal length is sufficiently close to zero!
  void Normalize ();

  /**
   * Set a plane as degenerate.
   */
  DS_FORCE_INLINE void SetDegenerate ()
  {
    normal.Set(0, 0, 0);
    d = 0.f;
    degenerate = true;
  }

  /**
   * Return whether plane is degenerate.
   */
  bool IsDegenerate () const
  {
    return degenerate;
  }

  AlgVector normal;
  float d;
  bool degenerate;
};

} // namespace geoms

#endif // GEOMS_PLANE_H
