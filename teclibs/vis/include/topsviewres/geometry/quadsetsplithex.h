// Quad sets for reservoirs, grouping top, bottom and side faces in separate geometry sets.
// fabraham@tecgraf.puc-rio.br
// Aug 2009
#ifndef TPV_QUAD_SET_SPLIT_HEX_H
#define TPV_QUAD_SET_SPLIT_HEX_H

#include <topsview/geometry/geomset.h>
#include <topsview/geometry/quadset.h>
#include <topsviewres/defines.h>
#include <alg/normalcone.h>
#include <alg/vector.h>
#include <alg/matrix.h>

class TPVRES_API TpvResQuadSetSplitHex : public TpvGeometrySet
{
public:
  TpvResQuadSetSplitHex ();
  // tpvgeometryset
  void SetModel (TopMultiModel *m);
  void SetTriangulator (TpvTriangulator* triangulator);
  void SetMustComputeNormals (bool flag);
  void SetSupportType (SupportType type);
  void SetActiveElements (const bool* active_elems);
  void Reset ();
  void AddFace (TopFaceUse fu);
  void SetField (TpvProperty *prop);
  void SetPerElemColors (TpvProperty *prop);
  void SetFieldOutdated ();
  void SetPerElemColorsOutdated ();
  void SetNormalsType (TpvGeometrySet::PropType type);
  void SetFieldType (TpvGeometrySet::PropType type);
  void SetUsePerElemColor (bool flag);
  void SetWireframe (bool flag);
  void SetVBOEnabled (bool flag);
  void Release ();
  void SetObserverPosition (const AlgVector& obspos)
  {
    m_obspos = obspos;
  }
  void SetScale (float x, float y, float z);
  void SetScaleCenter (float x, float y, float z);
  void Update ();
  void FreeFromCPU ();
  void Draw ();
  void DrawSelection ();
  DsArray<float>* GetVertexArrayCopy ();
  int Size ();
  int DrawnSize ();
  static void SetCullingEnabled (bool f);
  static bool IsCullingEnabled ();
  static void SetPauseCulling (bool f);
  static bool GetPauseCulling ();
  static void ToggleConeDraw (int c);
  static void SetDebugQuadset (int q);
  static void DebugBegin ();
private:
  bool WasGeomSetUpdated (int index)
  {
    return m_geomsets[index].IsUserDataOutdated(m_last_update_ts[index]);
  }
private:
  TpvQuadSet m_geomsets[3];
  AlgNormalCone m_normalcones[2];
  bool m_culled_cluster[2];
  int m_last_update_ts[3];
  AlgVector m_obspos;
  AlgVector m_lastobspos;
  AlgVector m_scale;
  AlgVector m_scale_center;
  AlgMatrix m_scale_matrix;
  bool m_scale_changed;
};

#endif

