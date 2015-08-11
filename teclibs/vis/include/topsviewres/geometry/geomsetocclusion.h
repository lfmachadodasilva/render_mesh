// Primitive sets for reservoirs (with occlusion culling)
// fabraham@tecgraf.puc-rio.br
// Feb 2008
#ifndef TPVRES_GEOM_SET_OCCLUSION_H
#define TPVRES_GEOM_SET_OCCLUSION_H

#include <ds/array.h>
#include <ds/hash.h>
#include <ds/hashset.h>
#include <topsview/geometry/geomset.h>
#include <topsview/geometry/geomsetbase.h>
#include <topsviewres/defines.h>
#include <vdlib/frustumculler.h>
#include <vdlib/occlusionculler.h>

typedef DsHashSet<int> BlockSet;
typedef DsHash<vrbv::Node*, BlockSet*> BlockSetsPerNode;
typedef DsHashSet<int>::Iterator BlockSetIterator;

// forward declarations
namespace geoms {
  class Hierarchy;
};
namespace topsgeoms {
  class PolyhedraModelRes;
};

class TPVRES_API TpvResGeometrySetOcclusion : public TpvGeometrySet, public vdlib::IOcclusionCallback, public vdlib::IFrustumCallback
{
public:
  virtual ~TpvResGeometrySetOcclusion ();
  float GetAverageZ ();
  // tpvgeometryset
  void SetModel (TopMultiModel *m);
  void SetHierarchy (geoms::Hierarchy* hierarchy, 
                     topsgeoms::PolyhedraModelRes* poly_model);
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
  void SetObserverPosition (const AlgVector& obspos);
  void SetScale (float x, float y, float z);
  void SetScaleCenter (float x, float y, float z);
  void Update ();
  void FreeFromCPU ();
  void Draw ();
  void DrawSelection ();
  DsArray<float>* GetVertexArrayCopy ();
  int Size ()
  {
    return m_total_prim_count;
  }
  int DrawnSize ()
  {
    return m_drawn_prim_count;
  }
  // static methods
  static void SetOcclusionEnabled (bool f);
  static bool IsOcclusionEnabled ();
  static bool IsOcclusionSupported ();
  static void SetFrustumEnabled (bool f);
  static bool IsFrustumEnabled ();
  static void SetDrawBoundingBoxes (bool f);
  static bool GetDrawBoundingBoxes ();
  static void SetPauseCulling (bool f);
  static bool GetPauseCulling ();
  static void SetUpdateAllBeforeRendering (bool f);
  static bool GetUpdateAllBeforeRendering ();
protected:
  /**
   * Constructor.
   *
   * 'verts_per_prim' must be 3 for triangle sets and 4 for quad sets.
   * 'disable_occlusion_culling': disables occlusion culling regardless of the
   *                              TpvResGeometrySetOcclusion::SetOcclusionEnabled() call.
   * 'disable_backface_culling':  disables backface culling regardless of the
   *                              TpvResQuadSetSplitHex::SetCullingEnabled() call.
   */
  TpvResGeometrySetOcclusion (int verts_per_prim,
                              bool disable_occlusion_culling,
                              bool disable_backface_culling);
  bool OcclusionCullingDisabled () const
  {
    return m_occ_culling_disabled;
  }
  bool BackfaceCullingDisabled () const
  {
    return m_bf_culling_disabled;
  }
  virtual TpvGeometrySet* CreateGeometrySet () const = 0;
  // vdlib::IFrustumCallback
  bool inside (vrbv::Node* node);
  // vdlib::IOcclusionCallback
  void draw (vrbv::Node* node);
  bool isValid (vrbv::Node* node);
  bool isDrawable (vrbv::Node* node);
private:
  void UpdateCullerHierarchy ();
  void UpdateCullerViewerParams ();
  void GetFaceIJK (TopFaceUse fu, int* i, int *j, int *k);
  /**
   * Create geometry sets for every hierarchy node.
   */
  void CreateGeomSetsForNodes ();
  /**
   * Setup a newly created geometry set.
   */
  void SetupGeometrySet (TpvGeometrySet* geomset);
  /**
   * Iterate tree from node n and return at map every node below n (including n)
   * and a corresponding set with block ids for geometries in each node.
   */
  void BuildBlockIdsLists (BlockSetsPerNode& map, vrbv::Node* n);
  void DrawWithoutCulling ();
private:
  typedef struct DrawnSet {
    TpvGeometrySet* set;
    vrbv::Node* node;
    DrawnSet ()
    {
      this->set = NULL;
      this->node = NULL;
    }
    DrawnSet (TpvGeometrySet* set, vrbv::Node* node)
    {
      this->set = set;
      this->node = node;
    }
  } DrawnSet;
  DsHash<vrbv::Node*, TpvGeometrySet*> m_node_geomset_map;
  DsArray<TpvGeometrySet*> m_geomsets;
  DsArray<TopFaceUse>* m_faces_per_block;
  DsArray<DrawnSet> m_drawn_last_frame;
  vdlib::OcclusionCuller m_occlusion_culler;
  vdlib::FrustumCuller m_frustum_culler;
  vrbv::Node* m_occlusion_root;
  int m_total_prim_count;
  int m_drawn_prim_count;
  AlgVector m_obspos;
  AlgVector m_scale;
  AlgVector m_scale_center;
  bool m_updated;
  bool m_draw_selection;
  geoms::Hierarchy* m_hierarchy;
  topsgeoms::PolyhedraModelRes* m_poly_model;
  bool m_occ_culling_disabled;
  bool m_bf_culling_disabled;
  bool m_any_added_face;
};

#endif
