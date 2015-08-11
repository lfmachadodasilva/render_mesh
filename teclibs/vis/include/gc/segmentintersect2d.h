#include "vertex2d.h"
#include "defines.h"

//---------------------------//
// Interseção de 2 segmentos //
//---------------------------//

GC_API bool gcSegmentsIntersect2D        (const gcVertex2D *SegStart1,  const gcVertex2D *SegEnd1,  const gcVertex2D *SegStart2,  const gcVertex2D *SegEnd2);
GC_API int  gcLocateSegments2D           (const gcVertex2D *SegStart1,  const gcVertex2D *SegEnd1,  const gcVertex2D *SegStart2,  const gcVertex2D *SegEnd2);
GC_API bool gcFindLinesIntersect2D       (const gcVertex2D *LineStart1, const gcVertex2D *LineEnd1, const gcVertex2D *LineStart2, const gcVertex2D *LineEnd2, gcVertex2D &Intersection);
GC_API bool gcFindSegmentsIntersect2D    (const gcVertex2D *SegStart1,  const gcVertex2D *SegEnd1,  const gcVertex2D *SegStart2,  const gcVertex2D *SegEnd2,  gcVertex2D &Intersection);
GC_API bool gcFindSegmentLineIntersect2D (const gcVertex2D *SegStart,  const gcVertex2D *SegEnd,  const gcVertex2D *LineStart,  const gcVertex2D *LineEnd,  gcVertex2D &Intersection);
