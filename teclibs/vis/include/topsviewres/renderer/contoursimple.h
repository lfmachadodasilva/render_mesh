// Simple Iso-contour renderer
// fabraham@tecgraf.puc-rio.br
// Feb 2008
#ifndef TPVRES_CONTOUR_SIMPLE_RENDERER_H
#define TPVRES_CONTOUR_SIMPLE_RENDERER_H

#include "contour.h"
#include <topsviewres/defines.h>

class TpvResBdryFacesSimpleGeometry;

class TPVRES_API TpvResContourSimpleRenderer : public TpvResContourRenderer
{
public: 
  TpvResContourSimpleRenderer ();
  virtual ~TpvResContourSimpleRenderer ();
  void SetGeometry(TpvResBdryFacesSimpleGeometry* g);
private:
  virtual void DoRender ();
  virtual void DoRenderSelection ();
private:
  TpvResBdryFacesSimpleGeometry* m_geometry;
};

#endif

