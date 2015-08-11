#ifndef GC_POLYGON_AREA_H
#define GC_POLYGON_AREA_H

#include "defines.h"

//-----------------------------------------//
// Includes and Forward Class Declarations //
//-----------------------------------------//

class gcVertex2D;

//---------//
// Defines //
//---------//

// Problem: Computing the area of a 2D polygon with n sides,
// or any measurement that can be weighted by triangle areas inside the polygon

// Solving Methods                                   Method Name                         Expected  Worst-Case

#define GC_POLYAREA_DECOMPOSITION   1   //   Centered Triangle Decomposition              O(n)      O(n)
#define GC_POLYAREA_NUM_METHODS     1

//------------------------//
// Direct Solving Methods //
//------------------------//

GC_API gcVertex2D gcTriangle2DCentroid (const gcVertex2D* Vertex1, const gcVertex2D* Vertex2, const gcVertex2D* Vertex3);
GC_API double     gcTriangle2DArea     (const gcVertex2D* Vertex1, const gcVertex2D* Vertex2, const gcVertex2D* Vertex3);

GC_API gcVertex2D gcPolygon2DCentroid  (gcVertex2D* Polygon[], int Size);
GC_API double     gcPolygon2DArea      (gcVertex2D* Polygon[], int Size);

#endif // GC_POLYGON_AREA_H
