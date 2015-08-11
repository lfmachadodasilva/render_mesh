/**
 *	Triangle representation. TODO r(t) = orig + t*dir
 *	author: Cesar Palomo <cpalomo@tecgraf.puc-rio.br>
 *	date:   10-Dec-2009
 */
#ifndef GEOMS_TRIANGLE_H
#define GEOMS_TRIANGLE_H

#include <alg/vector.h>
#include "point2d.h"
#include "defines.h"

namespace geoms {

class GEOMS_API Triangle
{
public:
	AlgVector v1, v2, v3; // Vertices
};

class Triangle2D
{
public:
  Triangle2D ()
  {
  }

  Triangle2D (const Point2D& v1, const Point2D& v2, const Point2D& v3)
  : v1(v1), v2(v2), v3(v3)
  {
  }


  /**
   * Returns the barycentric coordinates of a point with respect to
   * this triangle.
   * Returns false if coordinates cannot be computed (e.g.
   * degenerated triangle).
   */
  bool GetBarycentricCoordinates (const Point2D& p,
                                  float* t1,
                                  float* t2,
                                  float* t3)
  {
    float a[2] = {v1.x, v1.y}; 
    float b[2] = {v2.x, v2.y}; 
    float c[2] = {v3.x, v3.y}; 
    float area_total, area_a, area_b, area_c;
    AlgVector vec1, vec2, res;

    // Compute areas (barycentic coordinates)
    // Results at z coordinate
    vec1 = AlgVector(b[0]-a[0], b[1]-a[1], 0);  //b-a
    vec2 = AlgVector(c[0]-a[0], c[1]-a[1], 0);  //c-a
    res.Cross(vec1, vec2);
    area_total = 0.5f * res.z;

    vec1 = AlgVector(p.x - c[0], p.y - c[1], 0);  //p-c
    vec2 = AlgVector(b[0] - c[0], b[1] - c[1], 0);  //b-c
    res.Cross(vec1, vec2);
    area_a = 0.5f * res.z;

    vec1 = AlgVector(a[0] - c[0], a[1] - c[1], 0);  //a-c
    vec2 = AlgVector(p.x - c[0], p.y - c[1], 0);  //p-c 
    res.Cross(vec1, vec2);
    area_b = 0.5f * res.z;

    area_c = area_total - (area_a + area_b);

    if (fabs(area_total) > 0.0f) {
      *t1 = area_a / area_total;  //alpha
      *t2 = area_b / area_total;  //beta
      *t3 = area_c / area_total;  //gama
      return true;
    } else
      return false;
  }

  /**
   * Checks whether a point lies inside a triangle.
   */
  static bool CheckIntersection (const Triangle2D& t,
                                 const Point2D& p)
  {
    float dv0[2] = {t.v2.x - t.v1.x, t.v2.y - t.v1.y};
    float dv1[2] = {t.v3.x - t.v2.x, t.v3.y - t.v2.y};
    float dv2[2] = {t.v1.x - t.v3.x, t.v1.y - t.v3.y};
    if ((dv0[0] == dv1[0] && dv0[1] == dv1[1]) || (dv1[0] == dv2[0] && dv1[1] == dv2[1]))
      return false;

    float dp0[2] = {p.x - t.v1.x, p.y - t.v1.y};
    float dp1[2] = {p.x - t.v2.x, p.y - t.v2.y};
    float dp2[2] = {p.x - t.v3.x, p.y - t.v3.y};

    bool ccw0 = dv0[0]*dp0[1] - dv0[1]*dp0[0] >= 0.0f;
    bool ccw1 = dv1[0]*dp1[1] - dv1[1]*dp1[0] >= 0.0f;
    bool ccw2 = dv2[0]*dp2[1] - dv2[1]*dp2[0] >= 0.0f;
    return ccw0 == ccw1 && ccw1 == ccw2;
  }

  Point2D v1, v2, v3;
};

} // namespace geoms

#endif // GEOMS_TRIANGLE_H
