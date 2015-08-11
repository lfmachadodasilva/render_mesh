// Boundary faces geometry
// rodesp@tecgraf.puc-rio.br
// May 2008

#ifndef TPV_BDRY_FACES_GEOMETRY_H
#define TPV_BDRY_FACES_GEOMETRY_H

#include <tops/tops.h>
#include <topsview/defines.h>

#include "geometry.h"

#include <stdio.h>
#include <math.h>

class TpvTriangleSet;
class TpvFemTriangulator;

/**  
*/
class TPV_API TpvBdryFacesGeometry : public TpvGeometry
{
public:
  TpvBdryFacesGeometry ();
  
  virtual ~TpvBdryFacesGeometry ();

  TpvTriangleSet* GetTriangleSet ();

  virtual void SetModel (TopModel* m);

  virtual bool SetActiveElements (const bool* active_elems);
  
  virtual void SetField (TpvProperty* p);
  
  virtual void SetFieldOutdated ();

  virtual void SetPerElemColors (TpvProperty* p);

  virtual void SetPerElemColorsOutdated ();
   
  virtual void SetVBOEnabled (bool flag);
  
  virtual void SetBaseElemId (int id);

  virtual void SetDisplacement (float factor, TpvProperty* disp);  
  
private:
  virtual void ExtractGeometry ();
  
  bool IsBoundary(const TopElement& el, int facei) const
  {
    TopModel* m = GetModel();
    TopElement adj = m->GetAdj(el, facei);
    if (!m->IsCohesive(el) && 
        !IsRezoned(m->GetId(el)) &&
        (m->GetDimension(el) < 3 || 
          !adj.IsValid() || 
          !IsElementActive(m->GetId(adj)) ||
          IsRezoned(m->GetId(adj))))
      return true;  
    else
      return false;
  }  
   
private:
  TpvTriangleSet* m_triset; 
  TpvFemTriangulator* m_triangulator;
};

#endif
