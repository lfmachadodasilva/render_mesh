/**
* Modulo de definicao da classe TpvGeometry, para ser usado como geometria extraida para a TopsView
*/

#ifndef TPV_EDGE_TO_LINE_GEOMETRY_H
#define TPV_EDGE_TO_LINE_GEOMETRY_H

#include <tops/tops.h>
#include <topsview/defines.h>

#include "edgegeometry.h"
#include "linegeometry.h"

#include <stdio.h>
#include <math.h>

/**  
*/
MODEL_CLASS_TEMPLATE class TPVH_API TpvEdgeToLineGeometry : public TpvLineGeometry3<MODELCLASS>
{
private:
  TpvEdgeGeometry<MODELCLASS>* m_edge_geom;
  TpvProperty* m_field;
  TpvProperty* m_disp;
  float m_disp_factor;
  bool m_update_geom;
  bool m_update_disp;
  bool m_update_field;

  TpvLineSet2* m_lines;

  void InitGeometry();
  void ClearGeometry();
  void ClearField();
  void ClearDisp();
  void ExtractGeometry();
  void ExtractField();

public:
  typedef TpvLineGeometry3<MODELCLASS> SuperClass;

  TpvEdgeToLineGeometry(TpvEdgeGeometry<MODELCLASS>* g = NULL);
  virtual ~TpvEdgeToLineGeometry();

  virtual void SetEdgeGeometry(TpvEdgeGeometry<MODELCLASS>* g);
  virtual TpvEdgeGeometry<MODELCLASS>* GetEdgeGeometry();

  virtual void SetModel(TopModel* m);

  virtual void SetModel(TopMultiModel* m);

  virtual void SetBaseId(int id);

  virtual void SetField(TpvProperty* f);
  virtual TpvProperty* GetField();

  virtual void SetDisp(TpvProperty* d);
  virtual TpvProperty* GetDisp();

  virtual void SetDispFactor(float f);
  virtual float GetDispFactor();

  /**
      Updates geometry data.
      After any modifications, geometry must be updated before it can
    be used again.
  */
  virtual void Update();

  virtual TpvLineSet2* GetLines(int step_id = TpvGeometry3<MODELCLASS>::NO_REZONE_STEP_ID);
};

#include "edgetoline.inl"

#endif
