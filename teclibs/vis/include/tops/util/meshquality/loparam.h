#ifndef TOP_LO_PARAM_MESH_QUALITY_H
#define TOP_LO_PARAM_MESH_QUALITY_H

#include "../meshquality.h"

/**
  Lo´s quality criterion.

  - Triangles (planar T3 and T6, with vertices {A, B, C}):
    Ref: 
       Lo SH (1989) "Delaunay triangulation of non-convex planar domains", 
       Int. J. numer. Meth. Engng 28, pp. 2695-2707

       Lo SH (1992) "Generation of high-quality gradation finite element mesh",
       Engineering Fracture Mechanics 41(2), pp. 191-202

    alpha(ABC) = 2 * sqrt(3) * length(cross(AB, BC)) / 
       (length(AB)^2 + length(BC)^2 + length(CA)^2)

    or, equivalently, 

    alpha(ABC) = 4 * sqrt(3) * area / sum[i=1,3](edge_length(i)^2)

    Higher values mean better quality triangles. Equilateral triangles have
    alpha = 1. alpha = 0 corresponds to A, B and C being co-linear.

  - Tetrahedra (TET4 and TET10, with vertices {J1,J3,J2,X}) = "gamma coefficient"
    Ref:
      Lo SH (1990) "Volume discretization into tetrahedra -- II. 3D triangulation
      by advancing front approach", Computers & Structures 39(5), pp. 501-511

    gamma = 72 * sqrt(3) * volume_of_tetrahedron / (sum_of_squares_of_edges ^ 1.5),

    or, equivalently,

    gamma = 12 * sqrt(3) * dot(cross_product(J1J3, J1J2), J1X) /
      (length(J1J3)^2 + length(J3J2)^2 + length(J2J1)^2 + length(J1X)^2 + 
        length(J2X)^2 + length(J2X)^2 + length(J3X)^2)^1.5

    Higher values mean better tetrahedra. J1, J2, J3 are the nodes of 
    triangular facet i and 72 * sqrt(3) is a normalizing factor. Gamma is in 
    the interval [0, 1]. Equilateral tetrahedra have a maximum value of one.
    
    A minimum arbitrary value of gamma can be chosen to accept triangles: 
    gamma > gamma_min. It can be, for example, 0.5*alpha, where alpha is the
    Lo's metric of the facet i.
*/
class TOPS_API TopLoParamMeshQuality : public TopMeshQuality
{
public:
  TopLoParamMeshQuality(TopModel* m);

  virtual ~TopLoParamMeshQuality();

  virtual double GetElemQuality(const TopElement& el);

  virtual void GetMetricLimits(double* minval, double* maxval);
};

#endif

