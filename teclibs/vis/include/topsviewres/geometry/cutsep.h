// Cut planes geometry extractor (with sections and layer separation)
// fabraham@tecgraf.puc-rio.br
// Feb 2008
// cpalomo@tecgraf.puc-rio.br
// May 2010
#ifndef TPVRES_CUT_SEP_H
#define TPVRES_CUT_SEP_H

#include <geoms/intersect.h>
#include <topsgeoms/polyhedramodel.h>
#include <topsviewres/defines.h>
#include "cut.h"

class TPVRES_API TpvResCutSepGeometry: public TpvResCutGeometry
{
public:
  TpvResCutSepGeometry (int num_layers);
  ~TpvResCutSepGeometry ();
  /**
   * Specifies the layer separations for each layer (separation[k]).
   * This class will be responsible for freeing the 'separations' array.
   */
  void SetSeparations (const float* separations);
  void SetSection (int i, int j, int k);
  bool HasSection () const
  {
    return
      m_section_i != -1 ||
      m_section_j != -1 ||
      m_section_k != -1;
  }
  bool IsOnSection (int i, int j, int k) const
  {
    return
      (m_section_i == -1 || m_section_i == i) &&
      (m_section_j == -1 || m_section_j == j) &&
      (m_section_k == -1 || m_section_k == k);
  }
  int GetNumLayers () const
  {
    return m_num_layers;
  }
  void SetIntersect (TOP_INTERSECT* intersect,
                     topsgeoms::PolyhedraModelRes* poly_model,
                     int k);
  TpvTriangleSet* GetTriangleSet (int plane_i, int layer);

private:
  void UpdatePlaneEquation (float plane_eq[4], 
                            float orig_plane_eq[4], 
                            int layer);
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
  DsArray<TpvTriangleSet**> m_geomset;
  float *m_separations;
  int m_num_layers;
  int m_section_i;
  int m_section_j;
  int m_section_k;
  DsArray<TOP_INTERSECT*> m_intersect;
  DsArray<topsgeoms::PolyhedraModelRes*> m_poly_model;
};

#endif  // TPVRES_CUT_SEP_H
