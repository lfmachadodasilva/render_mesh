#ifndef GC_TYPES_H
#define GC_TYPES_H

#include "array.h"
#include "clist.h"

class gcVertex2D;
class gcHalfEdge2D;
class gcTriangle2D;

//----------//
// Typedefs //
//----------//

typedef gcCList<gcVertex2D*>      gcVertex2DCList;
typedef gcVertex2DCList::Iterator gcVertex2DCIterator;

typedef gcCList<gcHalfEdge2D*>      gcHalfEdge2DCList;
typedef gcHalfEdge2DCList::Iterator gcHalfEdge2DCIterator;

typedef gcCList<gcTriangle2D*>      gcTriangle2DCList;
typedef gcTriangle2DCList::Iterator gcTriangle2DCIterator;

typedef gcCList<int>         gcIntCList;
typedef gcIntCList::Iterator gcIntCIterator;
typedef gcArray<gcVertex2D*> gcVertex2DArray;

typedef gcArray<int> gcIntArray;

#endif // GC_TYPES_H
