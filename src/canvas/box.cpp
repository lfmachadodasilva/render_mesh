// -------------------------------------------------------------------------------------------------
// Anflex Project -- Tecgraf/PUC-Rio
// www.tecgraf.puc-rio.br
//
// $HeadURL: https://subversion.tecgraf.puc-rio.br/svn/anflex-interface/trunk/src/box.cpp $
// $Revision: 316 $
// $Date: 2010-07-14 20:07:43 -0300 (qua, 14 jul 2010) $
//
// $Author: gstiebler $
// -------------------------------------------------------------------------------------------------

#include <limits.h>
#include "box.h"
#include <iostream>
#include <algorithm>
using namespace std;

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
sBox::sBox( float xmin, float xmax, float ymin, 
            float ymax, float zmin, float zmax)
{
  min.x = xmin;
  max.x = xmax;
  min.y = ymin;
  max.y = ymax;
  min.z = zmin;
  max.z = zmax;
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void sBox::reset(void)
{
  float limit = std::numeric_limits<float>::max();

  min.x =  limit;
  min.y =  limit;
  min.z =  limit;
  max.x = -limit;
  max.y = -limit;
  max.z = -limit;
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
sBox operator+(const sBox &box, AlgVector &pt)
{
  sBox new_box(box);

  new_box.min.x = std::min(new_box.min.x, pt.x);
  new_box.min.y = std::min(new_box.min.y, pt.y);
  new_box.min.z = std::min(new_box.min.z, pt.z);

  new_box.max.x = std::max(new_box.max.x, pt.x);
  new_box.max.y = std::max(new_box.max.y, pt.y);
  new_box.max.z = std::max(new_box.max.z, pt.z);

  return new_box;
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void sBox::add(const sBox &box)
{
  min.x = std::min(min.x, box.min.x);
  min.y = std::min(min.y, box.min.y);
  min.z = std::min(min.z, box.min.z);

  max.x = std::max(max.x, box.max.x);
  max.y = std::max(max.y, box.max.y);
  max.z = std::max(max.z, box.max.z);
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
bool BoxIntersection(const sBox& b1, const sBox& b2)
{
  return (b1.min.x <= b2.max.x && b1.max.x >= b2.min.x) &&
    (b1.min.y <= b2.max.y && b1.max.y >= b2.min.y) &&
    (b1.min.z <= b2.max.z && b1.max.z >= b2.min.z);
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
//void BoxBoundQuads(sBox* b, dCoord (**quads)[4], int nquads, double tol)
//{
// int i;
//
// b->reset();
//
// while(nquads--) 
// {
//  for(i = 0; i < 4; i++) 
//  {
//   b->min.x = Min(b->min.x, ((dCoord*)(*quads))[i].x);
//   b->min.y = Min(b->min.y, ((dCoord*)(*quads))[i].y);
//   b->min.z = Min(b->min.z, ((dCoord*)(*quads))[i].z);
//   b->max.x = Max(b->max.x, ((dCoord*)(*quads))[i].x);
//   b->max.y = Max(b->max.y, ((dCoord*)(*quads))[i].y);
//   b->max.z = Max(b->max.z, ((dCoord*)(*quads))[i].z);
//  }
//  quads++;
// }
// b->min.x -= tol;
// b->min.y -= tol;
// b->min.z -= tol;
// b->max.x += tol;
// b->max.y += tol;
// b->max.z += tol;
//}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void BoxTransform(sBox* res, sBox* orig, float M[9], float T[3])
{
  int i, j, k;
  float res_min[3], res_max[3], orig_min[3], orig_max[3], a, b;

  orig_min[0] = orig->min.x; orig_max[0] = orig->max.x;
  orig_min[1] = orig->min.y; orig_max[1] = orig->max.y;
  orig_min[2] = orig->min.z; orig_max[2] = orig->max.z;

  res_min[0] = res_max[0] = T[0];
  res_min[1] = res_max[1] = T[1];
  res_min[2] = res_max[2] = T[2];

  for(i = 0, k = 0; i < 7; i+=3, k++)
  {
    for (j = 0; j < 3; j++)
    {
      a = M[i+j]*orig_min[j];
      b = M[i+j]*orig_max[j];
      if(a < b) 
      {
        res_min[k] += a;
        res_max[k] += b;
      } 
      else 
      {
        res_min[k] += b;
        res_max[k] += a;
      }
    }
  }

  res->min.x = res_min[0]; res->max.x = res_max[0];
  res->min.y = res_min[1]; res->max.y = res_max[1];
  res->min.z = res_min[2]; res->max.z = res_max[2];
}