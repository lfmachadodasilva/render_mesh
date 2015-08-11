// Map and section geometry extractor
// fabraham@tecgraf.puc-rio.br
// Feb 2008
#ifndef TPVRES_MAP_SEC_H
#define TPVRES_MAP_SEC_H

#include "geometry.h"
#include <geoms/intersect.h>
#include <tops/model.h>
#include <topsviewres/defines.h>

namespace topsgeoms {
  class PolyhedraModelRes;
};
class TpvQuadSet;
class TpvResQuadSetOcclusion;
class TpvResLineSet;
class TpvResRadialTriangulator;

class TPVRES_API TpvResMapSecGeometry : public TpvResGeometry
{
public:
  typedef enum
  {
    SECTION_I,
    SECTION_J,
    SECTION_K,
  } SectionType;
  TpvResMapSecGeometry ();
  virtual ~TpvResMapSecGeometry ();
  TpvGeometrySet* GetQuadSetActive ();
  TpvGeometrySet* GetQuadSetInactive ();
  TpvResLineSet* GetQuadSetGap ();
  void SetSectionType (SectionType type);
  /**
   * Specifies if must show inactive cells property values.
   */
  void SetFillInactive (bool flag);
  /**
   * Must show inactive cells property values?
   */
  bool MustFillInactive () const
  {
    return m_fill_inactive;
  }
  /**
   * Set elements hierarchy.
   */
  void SetHierarchy (geoms::Hierarchy* hierarchy, 
                     topsgeoms::PolyhedraModelRes* poly_model);
  virtual void SetModel (TopMultiModel* m, bool is_radial, float radial_rw);
  virtual bool SetActiveElements (const bool* active_elems);
  virtual bool SetVisibleElements (const bool* visible_elems);
  virtual void SetVisibleElementsChanged ();
  virtual void SetPerElemField (TpvProperty* p);
  virtual void SetPerElemColors (TpvProperty* p);
  virtual void SetFieldOutdated ();
  virtual void SetPerElemColorsOutdated ();
  virtual void SetVBOEnabled (bool flag);
protected:
  bool IsElementVisible (int index) const
  {
    return m_visible_elems == NULL || m_visible_elems[index];
  }
private:
  void CheckGap (
    TopModel *model,
    TopElement element,
    TopElement adj_element,
    int fi,
    int edge_index);
  TopElement GetAdjacentElementIfActive (TopElement el,
                                         TopElement parent_el,
                                         TopModel* elem_model,
                                         int ci,
                                         int cj,
                                         int ck);
  virtual void ExtractFaces ();
private:
  TpvResRadialTriangulator* m_radial_triangulator;
  TpvGeometrySet* m_geom_set_active;
  TpvGeometrySet* m_geom_set_inactive;
  TpvResQuadSetOcclusion* m_geom_occ_set_active;
  TpvResQuadSetOcclusion* m_geom_occ_set_inactive;
  TpvResLineSet *m_geom_set_gap;
  const bool *m_visible_elems;
  SectionType m_section;
  bool m_fill_inactive;
};

#endif

