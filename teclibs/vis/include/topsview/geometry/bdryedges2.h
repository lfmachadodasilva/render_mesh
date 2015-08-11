/**
* Modulo de definicao da classe TpvGeometry, para ser usado como geometria extraida para a TopsView
*/

#ifndef TPV_BDRY_EDGES_GEOMETRY2_H
#define TPV_BDRY_EDGES_GEOMETRY2_H

#include <tops/tops.h>
#include <topsview/defines.h>

#include "edgegeometry.h"

#include <stdio.h>
#include <math.h>

/**  
*/
MODEL_CLASS_TEMPLATE
class TPVH_API TpvBdryEdgesGeometry2 : public TpvEdgeGeometry<MODELCLASS>
{
private:
  bool m_update_geom;

  int m_nsteps_alloc;
  TpvEdgeUseArray** m_edges;

  bool IsVisible(const TopElement& el)
  {
    TopModel* model = SuperClass::GetElemModel(el);
    //return !model->IsInfinite(el) &&
    return SuperClass::IsElemTypeVisible(model, el) &&
           SuperClass::IsElemVisible(model, el);
  }

  bool IsBoundary(const TopEdgeUse& eu)
  {
    TopElement el = TopModel::GetElem(eu);
    if (IsVisible(el)) {
      TopModel* model = SuperClass::GetElemModel(el);
      TopElement adj0 = model->GetAdj(el, model->GetFacetUse(eu, 0).GetLocalId());
      TopElement adj1 = model->GetAdj(el, model->GetFacetUse(eu, 1).GetLocalId());
      int resid = SuperClass::GetElemRezoneId(el);
      if (model->IsCohesive(el) || model->GetDimension(el) == 2 ||
          !adj0.IsValid() || !IsVisible(adj0) || resid != SuperClass::GetElemRezoneId(adj0) ||
          !adj1.IsValid() || !IsVisible(adj1) || resid != SuperClass::GetElemRezoneId(adj1))
        return true;
    } 
    return false;
  }

  void InitEdges();
  void ClearEdges();
  void ExtractEdges();

public:
  typedef TpvEdgeGeometry<MODELCLASS> SuperClass;

  TpvBdryEdgesGeometry2();
  virtual ~TpvBdryEdgesGeometry2();

  virtual void SetModel(TopModel* m);

  virtual void SetModel(TopMultiModel* m);

  virtual void SetElemTypeVis(int type, bool isvisible);

  virtual void SetElemVis(const bool* vis);

  virtual void SetRezone(int nsteps, int* rezone);

  virtual void SetBaseId(int id);

  virtual void Update();

  virtual int GetNumOfEdges(int step_id = TpvGeometry3<MODELCLASS>::NO_REZONE_STEP_ID);
  virtual TopEdgeUse* GetEdges(int step_id = TpvGeometry3<MODELCLASS>::NO_REZONE_STEP_ID);
};

#include "bdryedges2.inl"

#endif
