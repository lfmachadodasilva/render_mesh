#include <GL/glew.h>

#include "geometryutil.h"
#include "tetrageometry3.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <assert.h>
#include <time.h>

#define MAX_EL_N 20

MODEL_CLASS_TEMPLATE
float TpvTetraGeometry3<MODELCLASS>::Dist(float* p0, float* p1)
{
  return (float) sqrt((p0[0]-p1[0])*(p0[0]-p1[0]) + (p0[1]-p1[1])*(p0[1]-p1[1]) + (p0[2]-p1[2])*(p0[2]-p1[2]));
}

MODEL_CLASS_TEMPLATE
void TpvTetraGeometry3<MODELCLASS>::InitGeometry()
{
  if (m_auto_max_edge_length)
    m_max_edge_length = 0.0f;
  m_tetra = new TpvTetrahedronSet();
}

MODEL_CLASS_TEMPLATE
void TpvTetraGeometry3<MODELCLASS>::ClearGeometry()
{
  delete m_tetra;
}

MODEL_CLASS_TEMPLATE
void TpvTetraGeometry3<MODELCLASS>::ClearField()
{
  m_tetra->GetField()->Resize(0);
}

MODEL_CLASS_TEMPLATE
void TpvTetraGeometry3<MODELCLASS>::ClearDisp()
{
  m_tetra->SetSize(0);
  m_tetra->GetAdjacencies()->Resize(0);
  m_tetra->GetPositions()->Resize(0);
  m_tetra->GetNormals()->Resize(0);
  m_tetra->GetPointSupports()->Resize(0);
}

MODEL_CLASS_TEMPLATE
void TpvTetraGeometry3<MODELCLASS>::GetTetField(int ti, float* s)
{
  TopModel* model = SuperClass::GetModel();
  assert(model != NULL);

  TpvSupport* psup = &(m_tetra->GetPointSupports()->GetArray()[4*ti]);
  if (m_field) {
    int ft = m_field->GetType();
    if (ft == TpvProperty::PROP_ELEMENT_NODE) {
      int elid = model->GetId(model->GetElem(psup[0].GetVertexUse()));
      for (int i = 0; i < 4; i++) {
        int nid = model->GetNodeLocalId(psup[i].GetVertexUse());
        if (m_normalize_field)
          s[i] = m_field->NormalizeScalar(m_field->GetValue(elid, nid)[0]);
        else
          s[i] = m_field->GetValue(elid, nid)[0];
      }
    } else if (ft == TpvProperty::PROP_ELEMENT) {
      int elid = model->GetId(model->GetElem(psup[0].GetVertexUse()));
      for (int i = 0; i < 4; i++) {
        if (m_normalize_field)
          s[i] = m_field->NormalizeScalar(m_field->GetValue(elid)[0]);
        else
          s[i] = m_field->GetValue(elid)[0];
      }
    } else if (ft == TpvProperty::PROP_NODE) {
      for (int i = 0; i < 4; i++) {
        int nid = model->GetId(model->GetNode(psup[i].GetVertexUse()));
        if (m_normalize_field)
          s[i] = m_field->NormalizeScalar(m_field->GetValue(nid)[0]);
        else
          s[i] = m_field->GetValue(nid)[0];
      }
    }
  } else {
    for (int i = 0; i < 4; i++)
      s[i] = 0.0f;
  }
}

//Only for TET cells!!!
MODEL_CLASS_TEMPLATE
void TpvTetraGeometry3<MODELCLASS>::AddTet(const TopElement& el)
{
  TopModel* model = SuperClass::GetModel();
  assert(model != NULL);

  int tet_size = m_tetra->GetSize();
  TpvFloatArray* tet_pos = m_tetra->GetPositions();
  TpvFloatArray* tet_normal = m_tetra->GetNormals();
  TpvSupportArray* tet_psup = m_tetra->GetPointSupports();
  TpvIntArray* tet_adj = m_tetra->GetAdjacencies();

  float pos[4][3];
  // Compute node positions.
  for (int i = 0; i < 4; i++) {
    TopNode n = model->GetVertexNode(el, i);
    TpvGeometryUtil::GetNodePosition(model, n, m_disp, m_disp_factor, pos[i]);
    tet_pos->Append(3, pos[i]);
  }
  // Compute node supports.
  for (int i = 0; i < 4; i++) {
    TopVertexUse vu = model->GetVertexUse(el, i);
    tet_psup->Append(TpvSupport(TpvSupport::VERTEX_USE, vu.GetHandle()));
  }
  // Compute face normals and adjacencies.
  for (int fi = 0; fi < 4; fi++) {
    int fp[4][3] = {{1,2,3}, {0,3,2}, {0,1,3}, {0,2,1}};
    // Normal
    float normal[3];
    TpvGeometryUtil::ComputeTriNormal(pos[fp[fi][0]], pos[fp[fi][1]], pos[fp[fi][2]], normal);
    tet_normal->Append(3, normal);
    // Adjacency
    TopElement adj = model->GetAdj(el, fi);
    int adj_type = model->GetType(adj);
    if (adj.IsValid() && 
      (adj_type == TopModel::ELEMENT_TET4 || adj_type == TopModel::ELEMENT_TET10)) {
//TODO: 1-indexed ids.
      tet_adj->Append(model->GetId(adj));   
    } else
      tet_adj->Append(0);
  }
  // Compute max edge length.
  if (m_auto_max_edge_length) {
    for (int i = 0; i < 4; i++) {
      for (int j = i+1; j < 4; j++) {
        float d = Dist(&pos[i][0], &pos[j][0]);
        if (d > m_max_edge_length) m_max_edge_length = d;
      }
    }
  }
  m_tetra->SetSize(tet_size + 1);
}

MODEL_CLASS_TEMPLATE
void TpvTetraGeometry3<MODELCLASS>::ExtractGeometry()
{
  TopModel* model = SuperClass::GetModel();
  assert(model != NULL);

  if (m_auto_max_edge_length)
    m_max_edge_length = 0.0f;
  m_visited.Clear();
  m_visited.ResizeAndSetConst(model->GetNElem(), 0);

  for (unsigned type = 0; type < TopModel::ELEMENT_MAX; type++) {
    const TopElementClass* el_class = model->GetElemClass(type);
    unsigned nelem = model->GetNElemOfType(type);
    if (el_class->GetDimension() == 3 &&         
        //!el_class->IsInfinite() && !el_class->IsCohesive()) {
        !el_class->IsCohesive())
    {
      for (unsigned i = 0; i < nelem; i++) {
        TopElement el = model->GetElem(type, i);
//TODO: 1-indexed ids.
        if (!m_visited.Get(model->GetId(el)-1)) {
          switch (type) {
            case TopModel::ELEMENT_TET4:
            case TopModel::ELEMENT_TET10:
              AddTet(el);
              break;
/*
            case TopModel::ELEMENT_HEX8:
            case TopModel::ELEMENT_HEX20:
              AddHex(el);
              break;
*/
            default:
//TODO
              printf("Unsupported element type: %d\n", type);
          }
        }
      }
    }
  }
}

MODEL_CLASS_TEMPLATE
void TpvTetraGeometry3<MODELCLASS>::ExtractField()
{
  int tet_size = m_tetra->GetSize();
  TpvFloatArray* tet_field = m_tetra->GetField();
  tet_field->Resize(4*tet_size);
  float* fp = tet_field->GetArray();
  for (int i = 0; i < tet_size; i++, fp += 4)
    GetTetField(i, fp);
}

/*****************
 public
******************/
//constructor
MODEL_CLASS_TEMPLATE
TpvTetraGeometry3<MODELCLASS>::TpvTetraGeometry3() :
  m_field(NULL), m_disp(NULL), m_disp_factor(1.0f),
  m_normalize_field(true),
  m_update_geom(true), m_update_field(true), m_update_disp(true),
  m_auto_max_edge_length(true), m_max_edge_length(0.0f)
{
  TpvGeometryUtil::Init();
  InitGeometry();
}

MODEL_CLASS_TEMPLATE
TpvTetraGeometry3<MODELCLASS>::~TpvTetraGeometry3()
{
}

MODEL_CLASS_TEMPLATE
void TpvTetraGeometry3<MODELCLASS>::SetBaseId(int id)
{
  SuperClass::SetBaseId(id);
  SetGeometryOutdated();
}

MODEL_CLASS_TEMPLATE
void TpvTetraGeometry3<MODELCLASS>::SetNormalizeField(bool f)
{
  m_normalize_field = f;
  m_update_field = true;
}

MODEL_CLASS_TEMPLATE
void TpvTetraGeometry3<MODELCLASS>::SetField(TpvProperty* f)
{
  m_field = f;
  m_update_field = true;
}

MODEL_CLASS_TEMPLATE
TpvProperty* TpvTetraGeometry3<MODELCLASS>::GetField()
{
  return m_field;
}

MODEL_CLASS_TEMPLATE
void TpvTetraGeometry3<MODELCLASS>::SetDisp(TpvProperty* d)
{
  m_disp = d;
  m_update_disp = true;
}

MODEL_CLASS_TEMPLATE
TpvProperty* TpvTetraGeometry3<MODELCLASS>::GetDisp()
{
  return m_disp;
}

MODEL_CLASS_TEMPLATE
void TpvTetraGeometry3<MODELCLASS>::SetDispFactor(float f)
{
  m_disp_factor = f;
  m_update_disp = true;
}

MODEL_CLASS_TEMPLATE
float TpvTetraGeometry3<MODELCLASS>::GetDispFactor()
{
  return m_disp_factor;
}

MODEL_CLASS_TEMPLATE
void TpvTetraGeometry3<MODELCLASS>::Update()
{ 
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
TpvTetrahedronSet* TpvTetraGeometry3<MODELCLASS>::GetTetrahedra(int step_id)
{
  Update();
  return m_tetra;
}

