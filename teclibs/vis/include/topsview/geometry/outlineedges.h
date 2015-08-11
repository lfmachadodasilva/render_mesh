/**
* Modulo de definicao da classe TpvGeometry, para ser usado como geometria extraida para a TopsView
*/

#ifndef TPV_OUTLINE_EDGES_GEOMETRY_H
#define TPV_OUTLINE_EDGES_GEOMETRY_H

#include <tops/tops.h>
#include <topsview/defines.h>
#include "geometry.h"

#include <stdio.h>
#include <math.h>

class TpvLineSet;

/**
 * Extracts a set of lines corresponding to the outline of a mesh.
 */
class TPV_API TpvOutlineEdgesGeometry : public TpvGeometry
{
public:
  TpvOutlineEdgesGeometry ();
  
  virtual ~TpvOutlineEdgesGeometry ();

  TpvLineSet* GetLineSet ();

  virtual void SetModel (TopModel* m);

  // Element activity is ignored.
  virtual bool SetActiveElements (const bool* active_elems);
  
  virtual void SetField (TpvProperty* p);
  
  virtual void SetFieldOutdated ();
   
  virtual void SetVBOEnabled (bool flag);
  
  virtual void SetBaseElemId (int id);

  virtual void SetDisplacement (float factor, TpvProperty* disp);  
    
private:
  virtual void ExtractGeometry ();
   
  bool IsOutline (const TopEdge& edge);

  bool IsBoundary (const TopFacetUse& facetuse)
  {
    TopModel* m = GetModel();
    TopElement elem = m->GetElem(facetuse);
    TopElement adj_elem = m->GetAdj(elem, facetuse.GetLocalId());
    return !adj_elem.IsValid() || m->IsCohesive(adj_elem);
  }

  bool IsBoundary (const TopFaceUse& faceuse)
  {
    TopModel* m = GetModel();
    TopElement elem = m->GetElem(faceuse);
    TopElement adj_elem = m->GetAdj(elem, faceuse.GetLocalId());
    return !adj_elem.IsValid() || m->IsCohesive(adj_elem);
  }
   
private:
  TpvLineSet* m_lineset; 
};

#endif
