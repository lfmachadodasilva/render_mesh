// Geometry extractor abstract class
// rodesp@tecgraf.puc-rio.br
// May 2008
#ifndef TPV_GEOMETRY_H
#define TPV_GEOMETRY_H

#include <topsview/defines.h>
#include <stdlib.h>

class TopModel;
class TpvProperty;
class TpvQuadSet;
class TpvTriangleSet;
class TpvLineSet;
class TpvPointSet;

class TPV_API TpvGeometry
{
public:
  TpvGeometry ();
  
  virtual ~TpvGeometry ();
  
  virtual void SetModel (TopModel* m);
  
  TopModel* GetModel() const
  {
    return m_model;
  }
  
  virtual void SetBaseElemId (int id);
  
  int GetBaseElemId () const
  {
    return m_base_elem_id;
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
  
  /**
   * Specifies a scalar field. Must have dimension equal to 1.
   */
  virtual void SetField (TpvProperty* p) = 0;
  
  /**
   * Signals a change in the scalar field.
   */
  virtual void SetFieldOutdated () = 0;
  
  /**
   * Specifies the activity status of the model elements (true=active, false=inactive).
   * Array dimension must be model->GetNElem().
   * Returns true if the active elements status changed, false if not.
   */
  virtual bool SetActiveElements (const bool* active_elems);

//TODO mover para FemGeometry
  virtual void SetRezoneBaseId (int id);

  virtual void SetRezone (int nsteps, const int* rezone_elems);

  virtual void SetRezoneStep (int step);

  
  virtual void SetGeometryOutdated ()
  {
    m_update_geom = true;
  }

  bool IsGeometryOutdated ()
  {
    return m_update_geom;
  }

  /**
   * Requests immediate update of this geometry.
   */
  void Update ();
  
  virtual TpvQuadSet* GetQuadSet () 
  {
    return NULL;
  }

  virtual TpvTriangleSet* GetTriangleSet ()
  {
    return NULL;
  }

  virtual TpvLineSet* GetLineSet ()
  {
    return NULL;
  }

  virtual TpvPointSet* GetPointSet ()
  {
    return NULL;
  }

protected:
  bool IsElementActive (int id) const
  {
    return m_active_elems == NULL || m_active_elems[id - m_base_elem_id];
  }

//TODO mover para FemGeometry
  int GetRezoneId (int elemid) const
  {
    if (m_rezone_elems)
      return m_rezone_elems[elemid - GetBaseElemId()];
    else
      return m_rezone_base_id - 1;
  }    

  bool IsRezoned (int elemid) const
  {
    int rezoneid = GetRezoneId(elemid);
    return rezoneid >= m_rezone_base_id && m_rezone_step >= m_rezone_base_id &&
      rezoneid <= m_rezone_step;
  }
  
private:
  virtual void ExtractGeometry () = 0;
  
private:
  TopModel* m_model;
  const bool* m_active_elems;
  bool m_update_geom;
  int m_base_elem_id;
//TODO mover para FemGeometry
  const int* m_rezone_elems;
  int m_rezone_nsteps;
  int m_rezone_step;
  int m_rezone_base_id;
};

#endif


