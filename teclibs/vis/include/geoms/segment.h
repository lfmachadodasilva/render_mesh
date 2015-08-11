/**
 *	Line segment representation.
 *	author: Cesar Palomo <cpalomo@tecgraf.puc-rio.br>
 *	date:   26-Jan-2009
 */
#ifndef GEOMS_SEGMENT_H
#define GEOMS_SEGMENT_H

#include <alg/vector.h>
#include "defines.h"
#include "ray.h"

namespace geoms {

class GEOMS_API Segment
{
public:
  Segment ()
  {
    p1.Set(0.0f, 0.0f, 0.0f);
    p2.Set(0.0f, 0.0f, 0.0f);
  }
  Segment (const float v[6])
  {
    p1.Set(v[0], v[1], v[2]);
    p2.Set(v[3], v[4], v[5]);
  }
  Segment (const float vec1[3], const float vec2[3])
  {
    p1.Set(vec1);
    p2.Set(vec2);
  }
  Segment (const Ray& r)
  {
    p1.Set(r.o);
    if (r.IsLimited())
      p2.Set(r.o + r.d*r.l);
    else
      p2.Set(r.o + r.d);
  }

public:
	AlgVector p1; // vertex 1
	AlgVector p2; // vertex 2
};

} // namespace geoms

#endif // GEOMS_SEGMENT_H

