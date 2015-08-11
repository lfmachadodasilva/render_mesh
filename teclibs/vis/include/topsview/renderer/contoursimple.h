// Simple Iso-contour renderer
// fabraham@tecgraf.puc-rio.br
// rodesp@tecgraf.puc-rio.br
// Feb 2008
#ifndef TPV_CONTOUR_SIMPLE_RENDERER_H
#define TPV_CONTOUR_SIMPLE_RENDERER_H

#include <topsview/defines.h>
#include "contour.h"
#include "../geometry/geometry.h"

class TPV_API TpvContourSimpleRenderer : public TpvContourRenderer
{
public: 
  TpvContourSimpleRenderer ();
  
  virtual ~TpvContourSimpleRenderer ();
  
  void SetGeometry (TpvGeometry* g);

  /**
    Sets whether support for transparent faces is enabled.
    Default: false
  */
  void SetTransparencyEnabled (bool flag);
  
private:
  virtual void DoRender ();
  virtual void DoRenderSelection ();
  
private:
  TpvGeometry* m_geometry;
  bool m_transp_enabled;
};

#endif

