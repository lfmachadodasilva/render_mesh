#ifndef GC_CONVEX_HULL_2D_H
#define GC_CONVEX_HULL_2D_H

//-----------------------------------------//
// Includes and Forward Class Declarations //
//-----------------------------------------//

class gcVertex2D;

#include "defines.h"
#include "types.h"

//---------//
// Defines //
//---------//

// Solving Methods              Method Name              Expected    Worst-Case    Best-Case   Worst-Case  1Mp-Tri 1Mp-Crc 1Mp-Brd

enum GCConvexHull2DMethod
{
  GC_HULL_JARVIS_MARCH  = 1,  // Jarvis March             O(n*h)      O(n^2)        Tiny Hull   Full Hull    0.23s   23s     >1m
  GC_HULL_GRAHAM_SCAN   = 2,  // Graham Scan              O(n*log(n)) O(n*log(n))   Full Hull   Tiny Hull    2.45s   2.45s   2.25s
  GC_HULL_INCREMENTAL   = 3,  // Incremental Scan         O(n*log(n)) O(n*log(n))   -           -            1.12s   1.12s   1.13s
  GC_HULL_INC2PASS      = 4,  // 2-pass incremental Scan  O(n*log(n)) O(n*log(n))   -           -            1.69s   1.72s   1.66s
  GC_HULL_MERGE_DEPTH   = 5,  // Merge Hull (Depth)       O(n*log(n)) O(n*log(n))   -           -            0.93s   0.93s   0.84s
  GC_HULL_MERGE_BREADTH = 6,  // Merge Hull (Breadth)     O(n*log(n)) O(n*log(n))   -           -            1.14s   1.14s   1.03s
  GC_HULL_NUM_METHODS   = 6,
  GC_HULL_QUICK         = 7,  // Quick Hull               O(n*log(n)) O(n^2)        Uniform     Full Hull    -       -       -
};

//------------------------//
// Direct Solving Methods //
//------------------------//

// Copying hull vertices to a new array

GC_API int gcConvexHull2D (gcVertex2D* Points[], int Size, gcVertex2D** Hull[], GCConvexHull2DMethod method = GC_HULL_JARVIS_MARCH, bool preDiscardInterior = true);
GC_API int gcConvexHull2D (gcVertex2D* Points[], int FirstIndex, int LastIndex, gcVertex2D** Hull[], GCConvexHull2DMethod method = GC_HULL_JARVIS_MARCH, bool preDiscardInterior = true);

// Rearranging input array with convex hull on first positions

GC_API int gcConvexHull2D (gcVertex2D* Points[], int Size, GCConvexHull2DMethod method = GC_HULL_JARVIS_MARCH, bool preDiscardInterior = true);
GC_API int gcConvexHull2D (gcVertex2D* Points[], int FirstIndex, int LastIndex, GCConvexHull2DMethod method = GC_HULL_JARVIS_MARCH, bool preDiscardInterior = true);

// Step-by-step convex hull calculation

GC_API void gcConvexHull2DStartStep (gcVertex2D* Points[], int Size, GCConvexHull2DMethod method = GC_HULL_JARVIS_MARCH);
GC_API void gcConvexHull2DStartStep (gcVertex2D* Points[], int FirstIndex, int LastIndex, GCConvexHull2DMethod method = GC_HULL_JARVIS_MARCH);
GC_API bool gcConvexHull2DContinue  (int &outputHullSize);
GC_API int  gcConvexHull2DGetStepSubSize ();
GC_API int* gcConvexHull2DGetStepSubOutputSizes ();

//---------------------------//
// Method-Specific Functions //
//---------------------------//

GC_API int  gcConvexHull2DJarvisCompare    (const gcVertex2D *Point, const gcVertex2D *ComparedPoint, const gcVertex2D *ReferencePoint, bool PreferClosest = false);
GC_API int  gcConvexHull2DJarvisSelectNext (gcVertex2D* Points[], int FirstIndex, int LastIndex, int  RefIndex, bool PreferClosest = false);
GC_API bool gcConvexHull2DJarvisStep       (gcVertex2D* Points[], int FirstIndex, int LastIndex, int &CurHullSize, bool PreferClosest = false);
GC_API int  gcConvexHull2DJarvis           (gcVertex2D* Points[], int FirstIndex, int LastIndex, bool PreferClosest = false);

GC_API int  gcConvexHull2DGrahamColinears  (gcVertex2D* Points[], int FirstIndex, int LastIndex);
GC_API bool gcConvexHull2DGrahamStep       (gcVertex2D* Points[], int FirstIndex, int LastIndex, int &CurHullSize, int &NextIndex);
GC_API int  gcConvexHull2DGraham           (gcVertex2D* Points[], int FirstIndex, int LastIndex);

GC_API bool gcConvexHull2DIncrementalStep  (gcVertex2D* Points[], int FirstIndex, int LastIndex, int &NextIndex, gcIntCList &HullList, gcIntCIterator &RightPoint);
GC_API int  gcConvexHull2DIncremental      (gcVertex2D* Points[], int FirstIndex, int LastIndex);

GC_API bool gcConvexHull2DInc2PassStep     (gcVertex2D* Points[], int FirstIndex, int LastIndex, int PassFirstIndex, bool Backwards, int &HullSize, int &NextIndex);
GC_API int  gcConvexHull2DInc2Pass         (gcVertex2D* Points[], int FirstIndex, int LastIndex);

GC_API void gcConvexHull2DMergeMerge       (gcVertex2D* Points[], gcVertex2D* AuxPoints[], int FirstIndexA, int LastIndexA, int HullSizeA, int LeftIndexA, int RightIndexA, int FirstIndexB, int LastIndexB, int HullSizeB, int LeftIndexB, int RightIndexB, int &HullSize, int &LeftIndex, int &RightIndex);
GC_API void gcConvexHull2DMergeStepBreadth (gcVertex2D* Points[], gcVertex2D* AuxPoints[], int FirstIndex, int LastIndex, int HalfSize, int HullSizes[], int LeftIndices[], int RightIndices[]);
GC_API void gcConvexHull2DMergeStepDepth   (gcVertex2D* Points[], gcVertex2D* AuxPoints[], int FirstIndex, int LastIndex, int &HullSize, int &LeftIndex, int &RightIndex);
GC_API int  gcConvexHull2DMergeBreadth     (gcVertex2D* Points[], int FirstIndex, int LastIndex);
GC_API int  gcConvexHull2DMergeDepth       (gcVertex2D* Points[], int FirstIndex, int LastIndex);

GC_API int  gcDiscardInterior              (gcVertex2D* Points[], int FirstIndex, int LastIndex);
GC_API int  gcDiscardInterior              (gcVertex2D* Points[], int FirstIndex, int LastIndex, gcVertex2D* ConvexPolygon[], int PolygonStart, int PolygonEnd);

GC_API int  gcDiscardExterior              (gcVertex2D* Points[], int FirstIndex, int LastIndex);
GC_API int  gcDiscardExterior              (gcVertex2D* Points[], int FirstIndex, int LastIndex, gcVertex2D* ConvexPolygon[], int PolygonStart, int PolygonEnd);

#endif // GC_CONVEX_HULL_2D_H
