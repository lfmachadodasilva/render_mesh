// Cut planes geometry extractor (without sections or layer separation)
// cpalomo@tecgraf.puc-rio.br
// May 2010
#ifndef TPVRES_CUT_SIMPLE_H
#define TPVRES_CUT_SIMPLE_H

#include <geoms/intersect.h>
#include <topsgeoms/polyhedramodel.h>
#include <topsviewres/defines.h>
#include "cut.h"

class TPVRES_API TpvResCutSimpleGeometry : public TpvResCutGeometry
{
public:
  TpvResCutSimpleGeometry ();
  ~TpvResCutSimpleGeometry ();

  TpvTriangleSet* GetTriangleSet (int plane_i);
  void SetIntersect (TOP_INTERSECT* intersect,
                     topsgeoms::PolyhedraModelRes* poly_model);

private:
  // virtual methods
  int GetGeomCount ();
  TpvTriangleSet* GetGeom (int i);
  TpvTriangleSet** AllocPlaneGeoms (int plane_i, int* count);
  TpvTriangleSet** GetPlaneGeoms (int plane_i, int* count);
  bool SkipFaceExtraction (int si, int sj, int sk);
  void AddFace (int plane_i, 
                int k, 
                DsArray<AlgVector>& polygon, 
                TopElement el);
  void ResetGeomsets (int plane_i);
  int GetIntersectCount ();
  TOP_INTERSECT* GetIntersect (int i);
  TOP_INTERSECT* GetIntersectByEl (TopElement el);
  topsgeoms::PolyhedraModelRes* GetPolyModel (int i);
  bool CheckIntersection (TopElement el, 
                          float planeLimits[6],
                          float planeEquation[4],
                          const float direction[3],
                          bool isInfinitePlane);
  int CalculateIntersection (float* planeLimits,
                             float* planeEquation, 
                             const float direction[3], 
                             bool isInfinitePlane);

private:
  DsArray<TpvTriangleSet*> m_geomset;
  TOP_INTERSECT* m_intersect;
  topsgeoms::PolyhedraModelRes* m_poly_model;
};

#endif  // TPVRES_CUT_SIMPLE_H

