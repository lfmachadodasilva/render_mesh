// 3d triangulation of generic finite element meshes.
// rodesp@tecgraf.puc-rio.br
// Nov 2008

#ifndef TPV_FEM_TETRA_GEOMETRY_3_H
#define TPV_FEM_TETRA_GEOMETRY_3_H

#include "tetrageometry3.h"
#include "tetrahedronset.h"
#include <topsview/defines.h>
#include <ds/hash.h>

#define TPV_FEM_TETRA_GEOMETRY_3_USE_TEMPLATE
#define TPV_FEM_TETRA_GEOMETRY_3_USE_OPTIMIZED_TEMPLATE

class TetraModel;

class TPV_API TpvFemTetraGeometry3 : public TpvTetraGeometry3<TpvFemGeometryModel>
{
public:
  typedef TpvTetraGeometry3<TpvFemGeometryModel> SuperClass;
  typedef TpvTetrahedronSet Tetrahedra;

  TpvFemTetraGeometry3();
  virtual ~TpvFemTetraGeometry3();

  /** Sets the model associated to this geometry. */
  virtual void SetModel (TopModel* m);
  TopModel* GetModel() const
  {
    return m_model;
  }
  virtual TpvTetrahedronSet* GetTetrahedra(int step_id = TpvGeometry3<TpvFemGeometryModel>::NO_REZONE_STEP_ID);

  void SetExtractTetrahedronVertexIncidences (bool flag);

protected:
  virtual void InitGeometry();
  virtual void ClearGeometry();
  virtual void ClearField();
  virtual void ClearDisp();
  virtual void ExtractGeometry();
  virtual void ExtractField();

private:
  class TetraTemplate {
  public:
    TetraTemplate (bool isvalid = false) : m_isvalid(isvalid), m_ntetras(0) {}
    ~TetraTemplate () {}
    bool IsValid () const { return m_isvalid; }
    void AddTetra (int nodes[4]) 
    {
      assert(m_ntetras < 32);
      int* v = &m_nodes[4*m_ntetras];
      for (int i = 0; i < 4; i++) 
        v[i] = nodes[i];
      m_ntetras++;
    }
    int GetNumTetras () const
    {
      return m_ntetras;
    }
    const int* GetNodes (int tetra) const
    {
      return &m_nodes[4*tetra];
    }
  private:
    bool m_isvalid;
    int m_ntetras;
    int m_nodes[4*32]; // MAX_NUM_TETRA = 32
  };

  bool IsVisible(const TopElement& el) const
  {
    //return !m_model->IsInfinite(el) &&
    return IsElemTypeVisible(m_model, el) &&
           IsElemVisible(m_model, el);
  }

  void InitNatCoords ();
  const float* GetNatCoords (int elemtype) const
  {
    return m_natcoords[elemtype];
  }
  void Triangulate (TetraModel& tetmodel, TopElement elem, const int* nodeids);

  void TriangulateTET10(
    const TopElement& elem, const int* nodeids, TetraModel& tetmodel);

  void TriangulateSplitQuadraticHEX20 (
    const TopElement& elem, const int* nodeids, int base_elemid, 
    TpvProperty* disp, float disp_factor, int extra_nodeid0,
    int* extra_nodeids, int* nextra_nodes, TetraModel& tetmodel);

  void TriangulateSplitQuadraticWEDGE15 (
    const TopElement& elem, const int* nodeids, int base_elemid, 
    TpvProperty* disp, float disp_factor, int extra_nodeid0,
    int* extra_nodeids, int* nextra_nodes, TetraModel& tetmodel);

  void TriangulateSplitQuadraticTET10 (
    const TopElement& elem, const int* nodeids, int base_elemid, 
    TpvProperty* disp, float disp_factor, int extra_nodeid0,
    int* extra_nodeids, int* nextra_nodes, TetraModel& tetmodel);

  // Debug
  bool SavePosFile (TetraModel& tetmodel, const char* filename);
  int GetElemRezoneId (const TopElement& el) const
  {
    return GetStepRezoneId(m_rezone ? m_rezone[GetModel()->GetId(el) - GetBaseId()] : -1);
  }
private:
  TopModel* m_model;
  TpvFemGeometryModel m_elem_model;
  float* m_natcoords[TopModel::ELEMENT_MAX];
  TpvTetrahedronSet* m_tetra;
  DsHash<unsigned long int, TetraTemplate> m_templates[TopModel::ELEMENT_MAX];
  bool m_extract_vertex_incidences;
};

#endif

