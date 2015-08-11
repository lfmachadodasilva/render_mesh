/**
* Modulo de definicao da classe TpvGeometry, para ser usado como geometria extraida para a TopsView
*/

#ifndef TPV_GEOMETRY3_H
#define TPV_GEOMETRY3_H

#include <ds/list.h>
#include <tops/tops.h>
#include <topsview/defines.h>

#include "../property/property.h"
#include "array.h"

#include <stdio.h>
#include <math.h>

#define MODEL_CLASS_TEMPLATE template <class MODELCLASS>

MODEL_CLASS_TEMPLATE class TpvGeometry3;

/**
  class TpvGeometryListener

    Geometry change listener. 
*/
MODEL_CLASS_TEMPLATE
class TPVH_API TpvGeometryListener
{
public:
  virtual ~TpvGeometryListener() {}
  virtual void GeometryChanged(TpvGeometry3<MODELCLASS>* source) {}
  virtual void FieldChanged(TpvGeometry3<MODELCLASS>* source) {}
};

/**
 * Model class for FEM geometries (they use TopModel*)
 */
class TPVH_API TpvFemGeometryModel
{
public:
  TpvFemGeometryModel ()
  : m_model(NULL)
  {
  }
  void SetModel (TopModel* m)
  {
    m_model = m;
  }
  void SetModel (TopMultiModel* m)
  {
  }
  TopModel* GetModel () const
  {
    return m_model;
  }
  TopMultiModel* GetMultiModel () const
  {
    return NULL;
  }
  TopModel* GetElemModel (const TopElement& elem) const
  {
    return m_model;
  }
  int GetNumLevels () const
  {
    return 1;
  }
  TopModel* GetLevelModel (int index) const
  {
    assert(index == 0);
    return m_model;
  }
private:
  TopModel* m_model;
};

/**
 * Model class for reservoir geometries (they use TopMultiModel*)
 */
class TPV_API TpvResGeometryModel
{
public:
  TpvResGeometryModel ()
  : m_model(NULL)
  {
  }
  void SetModel (TopModel* m)
  {
  }
  void SetModel (TopMultiModel* m)
  {
    m_model = m;
  }
  TopModel* GetElemModel (const TopElement& elem) const
  {
    return m_model->GetModel(elem.GetLevel());
  }
  TopModel* GetModel () const
  {
    return NULL;
  }
  TopMultiModel* GetMultiModel () const
  {
    return m_model;
  }
  int GetNumLevels () const
  {
    return m_model->GetNLevels();
  }
  TopModel* GetLevelModel (int index) const
  {
    return m_model->GetModel(index);
  }
private:
  TopMultiModel* m_model;
};

/**  
  class TpvGeometry3

    Represents a geometry extracted from a model.
  It contains polygonal and/or topological data from TopS.
*/

template <class MODELCLASS>
class TPV_API TpvGeometry3
{
public:
  typedef DsPList<TpvGeometryListener<MODELCLASS> > ListenerList;

private:
  ListenerList m_listeners;

protected:
  bool m_elem_type_vis[TopModel::ELEMENT_MAX];
  const bool* m_elem_vis;
  int m_nsteps;
  int* m_rezone;
  int m_base_id;

  int GetStepRezoneId(int step_id) const
  {
    if (m_rezone) {
      int id = step_id - m_base_id;
      if (id >= 0 && id < m_nsteps)
        return id + 1;
      else
        return 0;
    } else {
      return 0;
    }
  }

  int GetElemRezoneId (const TopElement& el) const
  {
    int step_id;
    if (m_rezone != NULL) {
      TopModel* model = GetElemModel(el);
      step_id = m_rezone[model->GetId(el) - m_base_id];
    }
    else
      step_id = -1;
    return GetStepRezoneId(step_id);
  }

  void NotifyGeometryChanged();
  void NotifyFieldChanged();

  TpvGeometry3();

public:
  enum {
    NO_REZONE_STEP_ID = -1,
  };

  virtual ~TpvGeometry3() {}

  /** Sets the model associated to this geometry. */
  virtual void SetModel (TopModel* m)
  {
    m_model.SetModel(m);
  }
  virtual void SetModel (TopMultiModel* m)
  {
    m_model.SetModel(m);
  }
  TopModel* GetModel() const
  {
    return m_model.GetModel();
  }
  TopMultiModel* GetMultiModel() const
  {
    return m_model.GetMultiModel();
  }

  /** Sets the visibility of a given element type. */
  virtual void SetElemTypeVis(int type, bool isvisible) 
  { 
    m_elem_type_vis[type] = isvisible;
  }

  bool GetElemTypeVis(int type) 
  { 
    return m_elem_type_vis[type];
  }

  bool IsElemTypeVisible (TopModel* model, TopElement el) const
  {
    return m_elem_type_vis == NULL ||
           m_elem_type_vis[model->GetType(el)];
  }

  /**
      Sets a reference to element visibility array.
    vis[elemid-1] = [true false]
  */
  virtual void SetElemVis(const bool* vis) { m_elem_vis = vis;}
  virtual const bool* GetElemVis() { return m_elem_vis; }

  bool IsElemVisible (TopModel* model, TopElement el) const
  {
    return m_elem_vis == NULL ||
           m_elem_vis[model->GetId(el) - GetBaseId()];
  }

  /** 
      Sets the ids of the time-steps in which the elements are rezoned.
  */
  virtual void SetRezone(int nsteps, int* rezone) 
  {
    m_nsteps = nsteps;
    m_rezone = rezone;
  }

  void GetRezone(int* nsteps, int** rezone) 
  { 
    *nsteps = m_nsteps;
    *rezone = m_rezone;
  }

  int GetRezoneNumSteps () const
  { 
    return m_nsteps;
  }

  /**
      Sets the base id.
    Default base id is 1, what means that ids are 1-indexed.
  */
  virtual void SetBaseId(int id) { m_base_id = id; }
  int GetBaseId() const
  {
    return m_base_id;
  }

  /** Sets property field associated to this geometry. */
  virtual void SetField(TpvProperty* f) {}
  virtual TpvProperty* GetField() { return NULL; }

  /** Sets nodal displacement data array. */
  virtual void SetDisp(TpvProperty* d) {}
  virtual TpvProperty* GetDisp() { return NULL; }

  /** Sets displacement factor. */
  virtual void SetDispFactor(float f) {}
  virtual float GetDispFactor() { return 1.0; }

  /**
      Updates geometry data.
      After any modifications, geometry must be updated before it can
    be used again.
  */
  virtual void Update() {}

  virtual void Print() {}

  /**
      Adds a listener to geometry modification events.
  */
  void AddListener(TpvGeometryListener<MODELCLASS>* l); 
  void RemListener(TpvGeometryListener<MODELCLASS>* l);
  ListenerList& GetListeners();
  void ClearListeners();
protected:
  TopModel* GetElemModel (const TopElement& elem) const
  {
    return m_model.GetElemModel(elem);
  }
  int GetNumLevels () const
  {
    return m_model.GetNumLevels();
  }
  TopModel* GetLevelModel (int index) const
  {
    return m_model.GetLevelModel(index);
  }
private:
  MODELCLASS m_model;
};

#include "geometry3.inl"

#endif
