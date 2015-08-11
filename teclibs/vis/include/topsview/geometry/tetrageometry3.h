
#ifndef TPV_TETRA_GEOMETRY_3_H
#define TPV_TETRA_GEOMETRY_3_H

#include "geometry3.h"
#include "tetrahedronset.h"
#include <topsview/defines.h>

MODEL_CLASS_TEMPLATE
class TPVH_API TpvTetraGeometry3 : public TpvGeometry3<MODELCLASS>
{
private:
  TpvProperty* m_field;
  TpvProperty* m_disp;
  float m_disp_factor;

  TpvTetrahedronSet* m_tetra;

  TpvIntArray  m_visited;

  bool  m_normalize_field;

  bool m_update_geom;
  bool m_update_field;
  bool m_update_disp;

  void GetTetField(int ti, float* s);
  void AddTet(const TopElement& el);

protected:
  bool  m_auto_max_edge_length;
  float m_max_edge_length;

  virtual void InitGeometry();
  virtual void ClearGeometry();
  virtual void ClearField();
  virtual void ClearDisp();
  virtual void ExtractGeometry();
  virtual void ExtractField();

  void SetFieldOutdated() { m_update_field = true; }
  void SetGeometryOutdated ()
  {
    m_update_geom = true;
  }
public:
  typedef TpvGeometry3<MODELCLASS> SuperClass;
  typedef TpvTetrahedronSet Tetrahedra;

  TpvTetraGeometry3();
  virtual ~TpvTetraGeometry3();

  virtual void SetBaseId(int id);

  /**
  * Sets whether the extracted field values will be normalized.
  * Default: true (to keep compatibility).
  */
  virtual void SetNormalizeField(bool f);
  bool GetNormalizeField() const { return m_normalize_field; }

  virtual void SetField(TpvProperty* f);
  virtual TpvProperty* GetField();

  virtual void SetDisp(TpvProperty* d);
  virtual TpvProperty* GetDisp();

  virtual void SetDispFactor(float f);
  virtual float GetDispFactor();

  virtual void Update();

  virtual TpvTetrahedronSet* GetTetrahedra(int step_id = TpvGeometry3<MODELCLASS>::NO_REZONE_STEP_ID);

  /**
      Sets whether the maximum edge length of the model will be automatically
    computed. If not, the user must specify the edge length.
      Default: true
  */
  void SetAutoMaxEdgeLength(bool flag)
  {
    m_auto_max_edge_length = flag;
  }

  void SetMaxEdgeLength(float l)
  {
    m_max_edge_length = l;
  }

  float GetMaxEdgeLength()
  {
    return m_max_edge_length;
  }
protected:
  static float Dist(float* p0, float* p1);
private:
};

#include "tetrageometry3.inl"

#endif

