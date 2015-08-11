/**
 *	Ray representation. r(t) = orig + t*dir
 *	author: Cesar Palomo <cpalomo@tecgraf.puc-rio.br>
 *	date:   27-Nov-2009
 */
#ifndef GEOMS_RAY_H
#define GEOMS_RAY_H

#include "defines.h"
#include <alg/vector.h>

namespace geoms {

class GEOMS_API Ray
{
public:
  Ray () 
    : l(NO_LIMIT)
    , inv_l(1.f)
  {
    o.Set(0.f, 0.f, 0.f);
    d.Set(0.f, 0.f, 0.f);
  }

  Ray (const float origin[3], const float direction[3], bool limited)
  {
    o.Set(origin[0], origin[1], origin[2]);
    d.Set(direction[0], direction[1], direction[2]);
    // when direction already normalized, could avoid this step
    float d_norm = d.Normalize();
    if (limited) {
      l = d_norm;
      inv_l = 1.f / l;
    }
  }

  bool IsLimited () const
  {
    return l != NO_LIMIT;
  }

public:
  AlgVector o;  // Origin
  AlgVector d;  // Direction (normalized)
  float l;      // limit: used for limiting intersection tests' range
  float inv_l;  // 1 / limit (for speed up)

private:
  static const float NO_LIMIT;
};

} // namespace geoms

#endif // GEOMS_RAY_H

