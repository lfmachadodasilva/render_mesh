// Boundary faces geometry
// rodesp@tecgraf.puc-rio.br
// Apr 2010

#ifndef TPV_BDRY_FACES_BILINEAR_H
#define TPV_BDRY_FACES_BILINEAR_H

#include <tops/tops.h>
#include <topsview/defines.h>

#include "bilinear.h"

#include <stdio.h>
#include <math.h>

class TpvTriangleSet;
class TpvFemTriangulator;
class TpvElemQ4BilinearTriangulator;
class TpvElemQ8BilinearTriangulator;

/**  
*/
class TPV_API TpvBdryFacesBilinearGeometry : public TpvBilinearGeometry
{
public:
  TpvBdryFacesBilinearGeometry ();
  
  virtual ~TpvBdryFacesBilinearGeometry ();

  TpvTriangleSet* GetTriangleSet ();

  TpvTriangleSet* GetTriangleSetQ4 ();

  TpvTriangleSet* GetTriangleSetQ8 ();

  virtual void SetModel (TopModel* m);

  virtual bool SetActiveElements (const bool* active_elems);
  
  virtual void SetField (TpvProperty* p);
  
  virtual void SetFieldOutdated ();
   
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
  TpvTriangleSet* m_triset_q4;
  TpvTriangleSet* m_triset_q8;
  TpvFemTriangulator* m_triangulator;
  TpvElemQ4BilinearTriangulator* m_triangulator_q4;
  TpvElemQ8BilinearTriangulator* m_triangulator_q8;
  int m_attrib_q4;
  int m_attrib_q8;
};

#endif