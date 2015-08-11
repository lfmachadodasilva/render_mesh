#ifndef GEOMS_GRAHAM_H
#define GEOMS_GRAHAM_H

#include "../defines.h"

typedef struct
{
	float x;
	float y;
  void* data;
} POINT2D;

GEOMS_API int convexHull2dGraham( POINT2D* orgPoint, int nPoints, POINT2D* hull);

#endif // GEOMS_GRAHAM_H
