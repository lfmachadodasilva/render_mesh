#include "geometry3.h"

/**************
 protected
***************/
MODEL_CLASS_TEMPLATE
void TpvGeometry3<MODELCLASS>::NotifyGeometryChanged()
{
  for (typename ListenerList::Iterator it = GetListeners().Begin(); it.Valid(); ++it)
    it->GeometryChanged(this);
}

MODEL_CLASS_TEMPLATE
void TpvGeometry3<MODELCLASS>::NotifyFieldChanged()
{
  for (typename ListenerList::Iterator it = GetListeners().Begin(); it.Valid(); ++it)
    it->FieldChanged(this);
}

//constructor
MODEL_CLASS_TEMPLATE
TpvGeometry3<MODELCLASS>::TpvGeometry3() :
  m_elem_vis(NULL), m_nsteps(0), m_rezone(NULL), m_base_id(1)
{
  for (int i = 0; i < TopModel::ELEMENT_MAX; i++)
    m_elem_type_vis[i] = true;
}

/**************
 public
***************/
MODEL_CLASS_TEMPLATE
void TpvGeometry3<MODELCLASS>::AddListener(TpvGeometryListener<MODELCLASS>* l) 
{ 
  m_listeners.Append(l); 
}

MODEL_CLASS_TEMPLATE
void TpvGeometry3<MODELCLASS>::RemListener(TpvGeometryListener<MODELCLASS>* l) 
{ 
  m_listeners.Remove(l); 
}

MODEL_CLASS_TEMPLATE
typename TpvGeometry3<MODELCLASS>::ListenerList& TpvGeometry3<MODELCLASS>::GetListeners() 
{ 
  return m_listeners; 
}

MODEL_CLASS_TEMPLATE
void TpvGeometry3<MODELCLASS>::ClearListeners() 
{ 
  m_listeners.Clear(); 
}
