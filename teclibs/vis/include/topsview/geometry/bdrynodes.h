// Boundary nodes geometry
// rodesp@tecgraf.puc-rio.br
// May 2008

#ifndef TPV_BDRY_NODES_GEOMETRY_H
#define TPV_BDRY_NODES_GEOMETRY_H

#include <tops/tops.h>
#include <topsview/defines.h>

#include "geometry.h"

#include <stdio.h>
#include <math.h>

class TpvPointSet;

/**
*/
class TPV_API TpvBdryNodesGeometry : public TpvGeometry
{
public:
  TpvBdryNodesGeometry ();
  
  virtual ~TpvBdryNodesGeometry ();

  TpvPointSet* GetPointSet ();

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
    TopElement el = m->GetElem(eu);
    TopElement adj0 = m->GetAdj(el, m->GetFacetUse(eu, 0).GetLocalId());
    TopElement adj1 = m->GetAdj(el, m->GetFacetUse(eu, 1).GetLocalId());
    if (!IsRezoned(m->GetId(el)) &&
        (m->IsCohesive(el) || m->GetDimension(el) == 2 || 
        !adj0.IsValid() || !IsElementActive(m->GetId(adj0)) || IsRezoned(m->GetId(adj0)) ||
        !adj1.IsValid() || !IsElementActive(m->GetId(adj1)) || IsRezoned(m->GetId(adj1))))
      return true;
    else
      return false;
  }

  bool IsBoundary(const TopVertexUse& vu) const
  {
    TopModel* m = GetModel();
    TopElement el = m->GetElem(vu);
    if (IsRezoned(m->GetId(el)))
      return false;
    else if (m->IsCohesive(el) || m->GetDimension(el) == 2)
      return true;
    else {
      int nf = m->GetNFacets(vu);
      for (int i = 0; i < nf; i++) {
        TopElement adj = m->GetAdj(el, m->GetFacetUse(vu, i).GetLocalId());
        if (!adj.IsValid() || !IsElementActive(m->GetId(adj)) || IsRezoned(m->GetId(adj)))
          return true;
      }
    }
    return false;
  }
   
private:
  TpvPointSet* m_pointset; 
};

#endif

