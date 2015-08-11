// Boundary faces geometry
// rodesp@tecgraf.puc-rio.br
// May 2008

#ifndef TPV_COH_FACETS_GEOMETRY_H
#define TPV_COH_FACETS_GEOMETRY_H

#include <tops/tops.h>
#include <topsview/defines.h>

#include "geometry.h"

#include <stdio.h>
#include <math.h>

class TpvTriangleSet;
class TpvLineSet;
class TpvFemTriangulator;

/**  
*/
class TPV_API TpvCohFacetsGeometry : public TpvGeometry
{
public:
  TpvCohFacetsGeometry ();
  
  virtual ~TpvCohFacetsGeometry ();

  TpvTriangleSet* GetTriangleSet ();

  TpvLineSet* GetLineSet ();

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
     
private:
  TpvTriangleSet* m_triset; 
  TpvLineSet* m_lineset; 
  TpvFemTriangulator* m_triangulator;
};

#endif
