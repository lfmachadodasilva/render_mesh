/**
 *	Class for storing a polygon in 2D (convex or not).
 *	author: Cesar Palomo <cpalomo@tecgraf.puc-rio.br>
 *	date:   09-Apr-2010
 */
#ifndef GEOMS_POLYGON2D_H
#define GEOMS_POLYGON2D_H

#include "defines.h"
#include <alg/vector.h>

namespace geoms {

class GEOMS_API Polygon2D
{
public:
  /**
   *  Add vertex to polygon. Vertices order used to determine edges (0..n-1).
   */ 
  void AddVertex (const float x, const float y)
  {
    vertices.Append(Point2D(x, y));
  }
  void AddVertex (const Point2D& v)
  {
    vertices.Append(v);
  }

  /**
   *  Get vertex i, with 0 <= i < vertex count.
   */ 
  void GetVertex (int i, float& x, float& y) const
  {
    Point2D& v = vertices.GetRef(i);
    x = v.x;
    y = v.y;
  }
  const Point2D* GetVertex (int i) const
  {
    return vertices.GetAddressConst(i);
  }

  /**
   *  Get total number of vertices.
   */ 
  int GetVertexCount () const
  {
    return vertices.Size();
  }

public:
  DsArray<Point2D> vertices;
};

} // namespace geoms

#endif // GEOMS_POLYGON2D_H
