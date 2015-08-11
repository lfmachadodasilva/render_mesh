#ifndef GC_POLYGON_INTERSECTION_H
#define GC_POLYGON_INTERSECTION_H

#include "defines.h"

//-----------------------------------------//
// Includes and Forward Class Declarations //
//-----------------------------------------//

class gcVertex2D;

//---------//
// Defines //
//---------//

// Problem: Computing the intersection points of two 2D polygons of m and n sides each

// Solving Methods                              Method Name              Expected    Worst-Case

#define GC_POLYINTERSECT_BRUTE           1  // Brute Force              O(n*m)      O(n*m)
#define GC_POLYINTERSECT_NUM_METHODS     1

//------------------------//
// Direct Solving Methods //
//------------------------//

GC_API int gcPolygonIntersect2DConvex (gcVertex2D* Polygon1[], int Poly1Size, gcVertex2D* Polygon2[], int Poly2Size, gcVertex2D** Intersection[], int method = GC_POLYINTERSECT_BRUTE);
GC_API int gcPolygonIntersect2D       (gcVertex2D* Polygon1[], int Poly1Size, gcVertex2D* Polygon2[], int Poly2Size, gcVertex2D** Intersection[], int method = GC_POLYINTERSECT_BRUTE);

//---------------------------//
// Method-Specific Functions //
//---------------------------//

GC_API int gcPolygonIntersect2DBrute (gcVertex2D* Polygon1[], int Poly1Size, gcVertex2D* Polygon2[], int Poly2Size, gcVertex2D** Intersection[]);

#endif // GC_POLYGON_INTERSECTION_H
