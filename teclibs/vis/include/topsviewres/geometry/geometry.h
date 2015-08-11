// Geometry extractor abstract class
// fabraham@tecgraf.puc-rio.br
// Feb 2008
#ifndef TPVRES_GEOMETRY_H
#define TPVRES_GEOMETRY_H

#include <topsviewres/defines.h>
#include <tops/multimodel.h>

class TpvProperty;
class TpvGeometrySet;
class TpvQuadSet;

class TPVRES_API TpvResGeometry
{
public:
  TpvResGeometry ();
  virtual ~TpvResGeometry ();
  virtual void SetModel (TopMultiModel* m, bool is_radial, float radial_rw);
  TopMultiModel* GetModel() const
  {
    return m_model;
  }
  bool IsModelRadial () const
  {
    return m_is_radial;
  }
  float GetRadialRW () const
  {
    return m_radial_rw;
  }
  /**
   * Informs the extractor that the active elements array has changed.
   * Will force the geometry re-extraction.
   */
  void SetActiveElementsChanged ()
  {
    SetGeometryOutdated();
  }
  /**
   * Informs the extractor that the model has changed.
   * Will force the geometry re-extraction.
   */
  void SetModelChanged ()
  {
    SetGeometryOutdated();
  }
  void Update ();
  /**
   * Specifies a per-element scalar field. Must have dimension equal to 1.
   */
  virtual void SetPerElemField (TpvProperty* p) = 0;
  /**
   * Specifies per-element colors. Must have dimension equal to 3.
   */
  virtual void SetPerElemColors (TpvProperty* p) = 0;
  /**
   * Signals a change in the per-element scalar field.
   */
  virtual void SetFieldOutdated () = 0;
  /**
   * Signals a change in the per-element colors.
   */
  virtual void SetPerElemColorsOutdated () = 0;
  /**
   * Specifies the activity status of the model elements (true=active, false=inactive).
   * Array dimension must be model->GetNElem().
   * Returns true if the active elements status changed, false if not.
   */
  virtual bool SetActiveElements (const bool* active_elems);
  virtual void SetGeometryOutdated ()
  {
    m_update_geom = true;
  }
protected:
  virtual const bool* GetActiveElementsArray () const
  {
    return m_active_elems;
  }
  virtual bool IsElementActive(int index) const
  {
    return m_active_elems[index];
  }
  bool IsElementActive (TopElement element) const
  {
    return IsElementActive(GetElemPosition(element));
  }
  bool IsElementActive (TopElement element, TopModel* elem_model) const
  {
    return IsElementActive(GetElemPosition(element, elem_model));
  }
  int GetElemPosition (TopElement element) const
  {
    return GetElemPosition(element, GetModel()->GetElemModel(element));
  }
  int GetElemPosition (TopElement element, TopModel* elem_model) const
  {
    return elem_model->GetId(element);
  }
  /**
   * Adds face 'fui' of element 'element' originated from 'elem_model' to
   * geometry set 'set'.
   */
  static void AddFaceTo (TpvGeometrySet* set,
                         TopModel* elem_model,
                         TopElement element,
                         int fui);
private:
  virtual void BeforeExtractFaces ()
  {
  }
  virtual void ExtractFaces () = 0;
private:
  TopMultiModel* m_model;
  const bool* m_active_elems;
  bool m_update_geom;
  bool m_is_radial;
  float m_radial_rw;
};

#endif

