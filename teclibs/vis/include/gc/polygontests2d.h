#ifndef GC_POLYGON_TESTS_H
#define GC_POLYGON_TESTS_H

//-----------------------------------------//
// Includes and Forward Class Declarations //
//-----------------------------------------//

#include "defines.h"
#include "constants.h"

class gcVertex2D;

//---------//
// Defines //
//---------//

//------------------------//
// Direct Solving Methods //
//------------------------//

GC_API int gcLocateAboutTriangle2D (const gcVertex2D* TestPoint, const gcVertex2D* Vertex1, const gcVertex2D* Vertex2, const gcVertex2D* Vertex3);

GC_API int gcLocateAboutPolygon2D  (const gcVertex2D* testPoint, gcVertex2D const * const polygon[], int size);

#endif // GC_POLYGON_TESTS_H
