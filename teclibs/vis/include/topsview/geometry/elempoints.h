// Element points geometry
// rodesp@tecgraf.puc-rio.br
// May 2008

#ifndef TPV_ELEM_POINTS_GEOMETRY_H
#define TPV_ELEM_POINTS_GEOMETRY_H

#include <tops/tops.h>
#include <topsview/defines.h>

#include "geometry.h"

class TpvTriangleSet;
class TpvPointExtractor;

/**  
 * Defines a geometry which extracts a set of points from mesh elements.
 */
class TPV_API TpvElemPointsGeometry : public TpvGeometry
{
public:
  TpvElemPointsGeometry ();
  
  virtual ~TpvElemPointsGeometry ();

  TpvPointSet* GetPointSet ();

  virtual void SetModel (TopModel* m);

  virtual bool SetActiveElements (const bool* active_elems);

  virtual void SetBaseElemId (int id);
  
  virtual void SetField (TpvProperty* p);
  
  virtual void SetFieldOutdated ();

  virtual void SetDisplacement (float factor, TpvProperty* disp);  
  
  virtual void SetVBOEnabled (bool flag);

  /**
   * Signals a change in element positions.
   */
  void SetPositionsOutdated ();
 
  void SetPointExtractor (TpvPointExtractor* extractor);

private:
  virtual void ExtractGeometry ();
  void ExtractNodeGeometry ();
  void ExtractElementGeometry ();
    
private:
  TpvProperty* m_field;
  TpvPointSet* m_pointset; 
};

#endif
