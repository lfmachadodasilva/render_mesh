// Cohesive facets bilinear geometry
// rodesp@tecgraf.puc-rio.br
// Apr 2010

#ifndef TPV_COH_FACETS_BILINEAR_H
#define TPV_COH_FACETS_BILINEAR_H

#include <tops/tops.h>
#include <topsview/defines.h>

#include "bilinear.h"

#include <stdio.h>
#include <math.h>

class TpvTriangleSet;
class TpvLineSet;
class TpvFemTriangulator;
class TpvElemQ4BilinearTriangulator;
class TpvElemQ8BilinearTriangulator;

/**  
*/
class TPV_API TpvCohFacetsBilinearGeometry : public TpvBilinearGeometry
{
public:
  TpvCohFacetsBilinearGeometry ();
  
  virtual ~TpvCohFacetsBilinearGeometry ();

  TpvTriangleSet* GetTriangleSet ();

  TpvTriangleSet* GetTriangleSetQ4 ();

  TpvTriangleSet* GetTriangleSetQ8 ();

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
   
private:
  TpvTriangleSet* m_triset; 
  TpvTriangleSet* m_triset_q4;
  TpvTriangleSet* m_triset_q8;
  TpvLineSet* m_lineset;
  TpvFemTriangulator* m_triangulator;
  TpvElemQ4BilinearTriangulator* m_triangulator_q4;
  TpvElemQ8BilinearTriangulator* m_triangulator_q8;
  int m_attrib_q4;
  int m_attrib_q8;
};

#endif