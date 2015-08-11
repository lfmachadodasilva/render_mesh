#include "bdryedges2.h"

MODEL_CLASS_TEMPLATE
void TpvBdryEdgesGeometry2<MODELCLASS>::InitEdges()
{
  m_nsteps_alloc = SuperClass::GetRezoneNumSteps() + 1;
  m_edges = (TpvEdgeUseArray**) calloc(m_nsteps_alloc, sizeof(TpvEdgeUseArray*));
  for (int i = 0; i < m_nsteps_alloc; i++)
    m_edges[i] = new TpvEdgeUseArray();
}

MODEL_CLASS_TEMPLATE
void TpvBdryEdgesGeometry2<MODELCLASS>::ClearEdges()
{
  for (int i = 0; i < m_nsteps_alloc; i++) 
    if (m_edges[i])
      delete m_edges[i];
  free(m_edges);
}

MODEL_CLASS_TEMPLATE
void TpvBdryEdgesGeometry2<MODELCLASS>::ExtractEdges()
{
  // Initializes step visibility array.
  TopEdgeUse* stepvis = new TopEdgeUse[SuperClass::GetRezoneNumSteps()+1];
  int numlevels = SuperClass::GetNumLevels();
  for (int l=0; l<numlevels; ++l) {
    TopModel* model = SuperClass::GetLevelModel(l);
    for (TopModel::EdgeItr itr(model); itr.IsValid(); itr.Next()) {
      TopEdge e = itr.GetCurr();
      TopEdgeUse eeu = model->GetEdgeUse(e);
      for (TopModel::EdgeUseItr euitr(model, e); euitr.IsValid(); euitr.Next()) {
        TopEdgeUse eu = euitr.GetCurr();
        if (IsBoundary(eu)) {
          int resid = SuperClass::GetElemRezoneId(TopModel::GetElem(eu));
          if (eeu != stepvis[resid]) {
            m_edges[resid]->Append(eu);
            stepvis[resid] = eeu;
          }        
        }
      }
    }
  }
  delete[] stepvis;
}

/*************
public
**************/
//constructor
MODEL_CLASS_TEMPLATE
TpvBdryEdgesGeometry2<MODELCLASS>::TpvBdryEdgesGeometry2() : 
  m_update_geom(true),
  m_nsteps_alloc(0)
{
  InitEdges();
}

MODEL_CLASS_TEMPLATE
TpvBdryEdgesGeometry2<MODELCLASS>::~TpvBdryEdgesGeometry2() 
{
  ClearEdges();
}

MODEL_CLASS_TEMPLATE
void TpvBdryEdgesGeometry2<MODELCLASS>::SetModel(TopModel* m)
{
  SuperClass::SetModel(m);
  m_update_geom = true;
}

MODEL_CLASS_TEMPLATE
void TpvBdryEdgesGeometry2<MODELCLASS>::SetModel(TopMultiModel* m)
{
  SuperClass::SetModel(m);
  m_update_geom = true;
}

MODEL_CLASS_TEMPLATE
void TpvBdryEdgesGeometry2<MODELCLASS>::SetElemTypeVis(int type, bool isvisible)
{
  SuperClass::SetElemTypeVis(type, isvisible);
  m_update_geom = true;
}

MODEL_CLASS_TEMPLATE
void TpvBdryEdgesGeometry2<MODELCLASS>::SetElemVis(const bool* vis)
{
  SuperClass::SetElemVis(vis);
  m_update_geom = true;
}

MODEL_CLASS_TEMPLATE
void TpvBdryEdgesGeometry2<MODELCLASS>::SetRezone(int nsteps, int* rezone)
{
  SuperClass::SetRezone(nsteps, rezone);
  m_update_geom = true;
}

MODEL_CLASS_TEMPLATE
void TpvBdryEdgesGeometry2<MODELCLASS>::SetBaseId(int id)
{
  SuperClass::SetBaseId(id);
  m_update_geom = true;
}

MODEL_CLASS_TEMPLATE
void TpvBdryEdgesGeometry2<MODELCLASS>::Update()
{ 
  bool geom_changed = false;
  if (m_update_geom) {
    ClearEdges();
    InitEdges();
    ExtractEdges();
    geom_changed = true;
  }
  m_update_geom = false;
  if (geom_changed)
    SuperClass::NotifyGeometryChanged();
}

MODEL_CLASS_TEMPLATE
int TpvBdryEdgesGeometry2<MODELCLASS>::GetNumOfEdges(int step_id)
{
  return m_edges[SuperClass::GetStepRezoneId(step_id)]->Size();
}

MODEL_CLASS_TEMPLATE
TopEdgeUse* TpvBdryEdgesGeometry2<MODELCLASS>::GetEdges(int step_id)
{
  return m_edges[SuperClass::GetStepRezoneId(step_id)]->GetArray();
}

