// Boundary edges geometry
// rodesp@tecgraf.puc-rio.br
// May 2008

#ifndef TPV_BDRY_EDGES_GEOMETRY_H
#define TPV_BDRY_EDGES_GEOMETRY_H

#include <tops/tops.h>
#include <topsview/defines.h>

#include "geometry.h"

#include <stdio.h>
#include <math.h>

class TpvLineSet;

/**
*/
class TPV_API TpvBdryEdgesGeometry : public TpvGeometry
{
public:
  TpvBdryEdgesGeometry ();
  
  virtual ~TpvBdryEdgesGeometry ();

  TpvLineSet* GetLineSet ();

  virtual void SetModel (TopModel* m);

  virtual bool SetActiveElements (const bool* active_elems);
  
  virtual void SetField (TpvProperty* p);
  
  virtual void SetFieldOutdated ();
   
  virtual void SetVBOEnabled (bool flag);
  
  virtual void SetBaseElemId (int id);

  virtual void SetDisplacement (float factor, TpvProperty* disp);  
    
private:
  virtual void ExtractGeometry ();
   
  bool IsBoundary(const TopEdgeUse& eu) const
  {
    TopModel* m = GetModel();
    TopElement el = TopModel::GetElem(eu);
    TopElement adj0 = m->GetAdj(el, m->GetFacetUse(eu, 0).GetLocalId());
    TopElement adj1 = m->GetAdj(el, m->GetFacetUse(eu, 1).GetLocalId());
    //int resid = GetElemRezoneId(el);
    if (!IsRezoned(m->GetId(el)) &&
        (m->IsCohesive(el) || m->GetDimension(el) == 2 || 
        !adj0.IsValid() || !IsElementActive(m->GetId(adj0)) || IsRezoned(m->GetId(adj0)) ||
        !adj1.IsValid() || !IsElementActive(m->GetId(adj1)) || IsRezoned(m->GetId(adj1))))
      return true;
    else
      return false;
  }
   
private:
  TpvLineSet* m_lineset; 
};

#endif
