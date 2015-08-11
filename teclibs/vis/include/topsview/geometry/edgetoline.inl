
#include "edgetoline.h"
#include "geometryutil.h"
#include "triangulator.h"

MODEL_CLASS_TEMPLATE
void TpvEdgeToLineGeometry<MODELCLASS>::InitGeometry()
{
  int nsteps, *rezone;
  m_edge_geom->GetRezone(&nsteps, &rezone);
  SuperClass::SetRezone(nsteps, rezone);
  m_lines = new TpvLineSet2[nsteps+1];
}

MODEL_CLASS_TEMPLATE
void TpvEdgeToLineGeometry<MODELCLASS>::ClearGeometry()
{
  delete[] m_lines;
}

MODEL_CLASS_TEMPLATE
void TpvEdgeToLineGeometry<MODELCLASS>::ClearField()
{
  int nsteps = SuperClass::GetRezoneNumSteps();
  for (int i = 0; i < nsteps+1; i++)
    m_lines[i].GetField()->Resize(0);
}

MODEL_CLASS_TEMPLATE
void TpvEdgeToLineGeometry<MODELCLASS>::ClearDisp()
{
  int nsteps = SuperClass::GetRezoneNumSteps();
  for (int i = 0; i < nsteps+1; i++) {
    m_lines[i].SetSize(0);
    m_lines[i].GetPositions()->Resize(0);
  }
}

MODEL_CLASS_TEMPLATE
void TpvEdgeToLineGeometry<MODELCLASS>::ExtractGeometry()
{
  int nsteps = SuperClass::GetRezoneNumSteps();
  for (int step_id = SuperClass::GetBaseId() + nsteps; step_id >= SuperClass::GetBaseId(); step_id--) {
    int resid = SuperClass::GetStepRezoneId(step_id);
    int lin_size = m_lines[resid].GetSize();
    TpvFloatArray* lin_pos = m_lines[resid].GetPositions();
    TpvSupportArray* lin_support = m_lines[resid].GetSupports();
    int nedges = m_edge_geom->GetNumOfEdges(step_id);
    TopEdgeUse* edges = m_edge_geom->GetEdges(step_id);
    for (int eui = 0; eui < nedges; eui++) {
      TopEdgeUse eu = edges[eui];
      TopModel* model = SuperClass::GetElemModel(TopModel::GetElem(eu));
      int el_type = model->GetElemType(eu);
      int eu_lid = model->GetLocalId(eu);
      float pos[3*TOP_MAX_NUM_E_N];
      TpvGeometryUtil::GetEdgePositions(model, eu, m_disp, m_disp_factor, pos);     
      int nlin = TpvTriangulator::GetEdgeNumOfLines(el_type, eu_lid);
      lin_pos->Resize(6*(lin_size + nlin));
      TpvTriangulator::TriangulateEdgeGeometry(model, eu, pos,
          &(lin_pos->GetArray()[6*lin_size]));
      // Extracts line support.
      TpvSupport support(TpvSupport::EDGE_USE, eu.GetHandle());
      for (int i = 0; i < nlin; i++)
        lin_support->Append(support);
      lin_size += nlin;
    }
    m_lines[resid].SetSize(lin_size);
  }
}

MODEL_CLASS_TEMPLATE
void TpvEdgeToLineGeometry<MODELCLASS>::ExtractField()
{
  int nsteps = SuperClass::GetRezoneNumSteps();
  for (int step_id = SuperClass::GetBaseId() + nsteps; step_id >= SuperClass::GetBaseId(); step_id--) {
    int resid = SuperClass::GetStepRezoneId(step_id);
    TpvFloatArray* lin_field = m_lines[resid].GetField();
    int lin_field_size = lin_field->Size();
    int nedges = m_edge_geom->GetNumOfEdges(step_id);
    TopEdgeUse* edges = m_edge_geom->GetEdges(step_id);
    for (int eui = 0; eui < nedges; eui++) {
      TopEdgeUse eu = edges[eui];
      TopModel* model = SuperClass::GetElemModel(TopModel::GetElem(eu));
      int el_type = model->GetElemType(eu);
      int eu_lid = model->GetLocalId(eu);
      int nlin = TpvTriangulator::GetEdgeNumOfLines(el_type, eu_lid);
      float s[TOP_MAX_NUM_F_N];
      TpvGeometryUtil::GetEdgeField(model, eu, m_field, s);
      lin_field->Resize(lin_field_size + 2*nlin);
      TpvTriangulator::TriangulateEdgeField(model, eu, s, 
          &(lin_field->GetArray()[lin_field_size])); 
      lin_field_size += 2*nlin;
    }
  }
}

/*************
public
**************/
//constructor
MODEL_CLASS_TEMPLATE
TpvEdgeToLineGeometry<MODELCLASS>::TpvEdgeToLineGeometry(TpvEdgeGeometry<MODELCLASS>* g) : 
  m_edge_geom(g),
  m_field(NULL), m_disp(NULL), m_disp_factor(1.0f),
  m_update_geom(true), m_update_disp(true), m_update_field(true)
{
  TpvGeometryUtil::Init();
  TpvTriangulator::Init();
  InitGeometry();
}

MODEL_CLASS_TEMPLATE
TpvEdgeToLineGeometry<MODELCLASS>::~TpvEdgeToLineGeometry() 
{
  ClearGeometry();
}

MODEL_CLASS_TEMPLATE
void TpvEdgeToLineGeometry<MODELCLASS>::SetEdgeGeometry(TpvEdgeGeometry<MODELCLASS>* g)
{
  m_edge_geom = g;
  m_update_geom = true;
}

MODEL_CLASS_TEMPLATE
TpvEdgeGeometry<MODELCLASS>* TpvEdgeToLineGeometry<MODELCLASS>::GetEdgeGeometry()
{
  return m_edge_geom;
}

MODEL_CLASS_TEMPLATE
void TpvEdgeToLineGeometry<MODELCLASS>::SetModel(TopModel* m)
{
  SuperClass::SetModel(m);
  m_update_geom = true;
}

MODEL_CLASS_TEMPLATE
void TpvEdgeToLineGeometry<MODELCLASS>::SetModel(TopMultiModel* m)
{
  SuperClass::SetModel(m);
  m_update_geom = true;
}

MODEL_CLASS_TEMPLATE
void TpvEdgeToLineGeometry<MODELCLASS>::SetBaseId(int id)
{
  SuperClass::SetBaseId(id);
  m_update_geom = true;
}

MODEL_CLASS_TEMPLATE
void TpvEdgeToLineGeometry<MODELCLASS>::SetField(TpvProperty* f)
{
  m_field = f;
  m_update_field = true;
}

MODEL_CLASS_TEMPLATE
TpvProperty* TpvEdgeToLineGeometry<MODELCLASS>::GetField()
{
  return m_field;
}

MODEL_CLASS_TEMPLATE
void TpvEdgeToLineGeometry<MODELCLASS>::SetDisp(TpvProperty* d)
{
  m_disp = d;
  m_update_disp = true;
}

MODEL_CLASS_TEMPLATE
TpvProperty* TpvEdgeToLineGeometry<MODELCLASS>::GetDisp()
{
  return m_disp;
}

MODEL_CLASS_TEMPLATE
void TpvEdgeToLineGeometry<MODELCLASS>::SetDispFactor(float f)
{
  m_disp_factor = f;
  m_update_disp = true;
}

MODEL_CLASS_TEMPLATE
float TpvEdgeToLineGeometry<MODELCLASS>::GetDispFactor()
{
  return m_disp_factor;
}

MODEL_CLASS_TEMPLATE
void TpvEdgeToLineGeometry<MODELCLASS>::Update()
{ 
  m_edge_geom->Update();

  bool geom_changed = false;
  bool field_changed = false;
  if (m_update_geom) {
    ClearGeometry();
    InitGeometry();
    ExtractGeometry();
    // Displacement is updated in UpdateGeometry().
    m_update_disp = false;
    m_update_field = true;
    geom_changed = true;
  }
  if (m_update_disp) {
    ClearDisp();
    ExtractGeometry();
    geom_changed = true;
  }
  if (m_update_field) {
    ClearField();
    ExtractField();
    field_changed = true;
  }
  m_update_geom = false;
  m_update_disp = false;
  m_update_field = false;
  if (geom_changed)
    SuperClass::NotifyGeometryChanged();
  if (field_changed)
    SuperClass::NotifyFieldChanged();
}

MODEL_CLASS_TEMPLATE
TpvLineSet2* TpvEdgeToLineGeometry<MODELCLASS>::GetLines(int step_id)
{
  return &m_lines[SuperClass::GetStepRezoneId(step_id)];
}

