// Cohesive element nodes geometry
// rodesp@tecgraf.puc-rio.br
// May 2008

#ifndef TPV_COH_NODES_GEOMETRY_H
#define TPV_COH_NODES_GEOMETRY_H

#include <tops/tops.h>
#include <topsview/defines.h>

#include "geometry.h"

#include <stdio.h>
#include <math.h>

class TpvPointSet;

/**
*/
class TPV_API TpvCohNodesGeometry : public TpvGeometry
{
public:
  TpvCohNodesGeometry ();
  
  virtual ~TpvCohNodesGeometry ();

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
   
private:
  TpvPointSet* m_pointset; 
};

#endif

