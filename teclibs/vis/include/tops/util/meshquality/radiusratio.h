#ifndef TOP_RADIUS_RATIO_MESH_QUALITY_H
#define TOP_RADIUS_RATIO_MESH_QUALITY_H

#include "../meshquality.h"

/**
  Radius ratio element shape quality measure.

  Ref:
    Mitrinovic DS, et al. (1989) "Recent Advances in Geometric Inequalities",
    Kluwer Academic Dordrecht, The Netherlands.

    Lo SH (1997) "Optimization of tetrahedral meshes based on element shape
    measures", Computers & Structures 63(5), pp. 951-961.

  The radius ration (rho) is the ratio of inradius (r) to circumradius (R) 
  scaled by 2, for triangles (rho = 2 * r / R), or by 3, for tetrahedra (rho = 3 * r / R)

  Higher values mean better quality triangles. Equilateral triangles have
  rho = 1. The value rho = 0 corresponds to A, B and C being co-linear. 
  0 <= rho <= 1.  

  - Planar T3 and T6, with vertices A, B, C:

    rho = 2 * inradius / circumradius = 2 * r / R
    r = (1/2) * sqrt((b + c - a) * (c + a - b) * (a + b - c) / (a + b + c))
    R = a * b * c / sqrt((a + b + c)(b + c - a) * (c + a - b) * (a + b - c))

    or equivalently,

    rho = ((b + c - a) * (c + a - b) * (a + b - c)) / (a * b * c)

    a, b, c = lengths of the opposite edges do the vertices A,B,C.

  - TET4 and TET10

    rho = 3 * inradius / circumradius = 3 * r / R
    r = 3 * v / (s1 + s2 + s3 + s4), 
      where v = volume of T and s1, s2, s3, s4 are the areas of the 4 faces of T
    R = sqrt((a + b + c) * (a + b - c) * (a + c - b) * (b + c - a)) / (24 * v)
      
    or equivalently,

    rho = (216 * volume^2) / 
      (sum[i=0,3](area(i)) * 
        sqrt((a + b + c) * (a + b - c) * (a + c - b) * (b + c - a)))

    a, b, c = products of the lengths of the opposite edges do the vertices A,B,C.
*/
class TOPS_API TopRadiusRatioMeshQuality : public TopMeshQuality
{
public:
  TopRadiusRatioMeshQuality(TopModel* m);

  virtual ~TopRadiusRatioMeshQuality();

  virtual double GetElemQuality(const TopElement& el);

  virtual void GetMetricLimits(double* minval, double* maxval);
};

#endif

