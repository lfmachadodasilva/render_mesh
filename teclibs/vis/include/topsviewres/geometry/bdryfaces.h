// Boundary faces geometry extractor
// fabraham@tecgraf.puc-rio.br
// Feb 2008
#ifndef TPVRES_BDRY_FACES_H
#define TPVRES_BDRY_FACES_H

#include "geometry.h"
#include <tops/multimodel.h>
#include <topsviewres/defines.h>
#include <ds/array.h>
#include <assert.h>

class TpvGeometrySet;

class TPVRES_API TpvResBdryFacesGeometry : public TpvResGeometry
{
public:
  TpvResBdryFacesGeometry ();
  virtual ~TpvResBdryFacesGeometry ();
  /**
   * Specifies if only top faces must be rendered.
   * If so, kdirdown=true informs if the top face has local index 0 and
   * kdirdown=false informs that the top face has local index 1.
   */
  void SetOnlyTopFaces (bool f, bool kdirdown);
  void SetLayerVisibility (const bool* lvis);
  /**
   * Specifies the use of vertex buffer objects on geometry sets.
   */
  virtual void SetVBOEnabled (bool flag) = 0;
  virtual void SetGeometryOutdated ();
  /**
   * Releases all associated vertex array data from CPU and VBOs.
   */
  virtual void Release ();
protected:
  bool MustOnlyExtractTopFaces () const
  {
    return m_top_faces;
  }
  int GetTopFaceLocalIndex() const
  {
    return m_top_face_index;
  }
  void AddElem (TopElement element,
                TpvGeometrySet *destset,
                int num_no_test_adj_fu,
                const int *no_test_adj_fu,
                int num_test_adj_fu,
                const int *test_adj_fu);
  const bool* GetActiveElementsArray () const
  {
    return m_elem_active_and_in_visible_layer.GetArrayConst();
  }
  bool IsElementActive (int index) const
  {
    assert(0 <= index && index < m_elem_active_and_in_visible_layer.Size());
    return m_elem_active_and_in_visible_layer.Get(index);
  }
  bool IsElementActive (TopElement element) const
  {
    return IsElementActive(GetElemPosition(element));
  }
  bool IsElementActive (TopElement element, TopModel* elem_model) const
  {
    return IsElementActive(GetElemPosition(element, elem_model));
  }
  virtual bool MustDrawAdjFace (TopElement element, TopModel* elem_model, int fui)
  {
    //return true; descomentar para desabilitar a otimizacao 'hull' que fazemos com a tops.
    if (!elem_model->HasAdj(element,fui))
      return true;
    TopElement adj = elem_model->GetAdj(element,fui);
    return !IsElementActive(adj, elem_model);
  }
  bool IsActiveElemsUpdated () const
  {
    return m_active_elems_updated;
  }
  void SetActiveElemsUpdated ()
  {
    m_active_elems_updated = true;
  }
  bool IsElementLayerVisible (TopElement element) const
  {
    if (m_layer_vis == NULL)
      return true;

    int k = GetModel()->GetRootElemReverseIdK(element);
    return m_layer_vis[k];
  }

private:
  // virtual methods
  virtual void BeforeExtractFaces ();
private:
  bool *m_layer_vis;
  DsArray<bool> m_elem_active_and_in_visible_layer;
  int m_top_face_index;
  bool m_top_faces;
  bool m_active_elems_updated;
};

#endif

