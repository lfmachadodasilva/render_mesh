/**
* Modulo de definicao da classe TpvGeometry, para ser usado como geometria extraida para a TopsView
*/

#ifndef TPV_MATERIAL_OUTLINE_H
#define TPV_MATERIAL_OUTLINE_GEOMETRY_H

#include <tops/tops.h>
#include <topsview/defines.h>
#include "geometry.h"

#include <stdio.h>
#include <math.h>

class TpvLineSet;
class TpvProperty;

/**
*/
class TPV_API TpvMaterialOutlineGeometry : public TpvGeometry
{
public:
  TpvMaterialOutlineGeometry ();
  
  virtual ~TpvMaterialOutlineGeometry ();

  TpvLineSet* GetLineSet ();

  virtual void SetModel (TopModel* m);

  virtual bool SetActiveElements (const bool* active_elems);
  
  virtual void SetField (TpvProperty* p);
  
  virtual void SetFieldOutdated ();
   
  virtual void SetVBOEnabled (bool flag);
  
  virtual void SetBaseElemId (int id);

  virtual void SetDisplacement (float factor, TpvProperty* disp);  

  virtual void SetMaterialIds (TpvProperty* mats);
    
private:
  virtual void ExtractGeometry ();
   
  bool IsAdjElementActive(const TopElement& el, int i) const
  {
    TopModel* m = GetModel();
    TopElement adj = m->GetAdj(el, i);
    return adj.IsValid() && IsElementActive(m->GetId(adj)) && !IsRezoned(m->GetId(adj));
  }

  bool IsBoundary (const TopEdgeUse& eu) const
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

  bool IsOutline (const TopEdgeUse& eu);
   
private:
  TpvLineSet* m_lineset; 
  TpvProperty* m_material_prop;
};

#endif
