/**
 *	Class for storing a point in 2D.
 *	author: Cesar Palomo <cpalomo@tecgraf.puc-rio.br>
 *	date:   09-Apr-2010
 */
#ifndef GEOMS_POINT2D_H
#define GEOMS_POINT2D_H

#include "defines.h"
#include <alg/vector.h>

namespace geoms {

class GEOMS_API Point2D
{
public:
  Point2D () : x(0.f), y(0.f)
  {
  }

  Point2D (float _x, float _y) : x(_x), y(_y)
  {
  }

  void Set (Point2D& p)
  {
    x = p.x;
    y = p.y;
  }

  float x;
  float y;
};

} // namespace geoms

#endif // GEOMS_POINT2D_H
