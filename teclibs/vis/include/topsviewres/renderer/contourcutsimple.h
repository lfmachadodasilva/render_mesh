// Cut geometry Iso-contour renderer (without layer separation)
// fabraham@tecgraf.puc-rio.br
// Feb 2008
// cpalomo@tecgraf.puc-rio.br
// May 2010
#ifndef TPVRES_CONTOUR_CUT_SIMPLE_RENDERER_H
#define TPVRES_CONTOUR_CUT_SIMPLE_RENDERER_H

#include "contourcut.h"
#include <topsviewres/defines.h>

class TpvResCutSimpleGeometry;

class TPVRES_API TpvResContourCutSimpleRenderer : public TpvResContourCutRenderer
{
public: 
  TpvResContourCutSimpleRenderer ();
  virtual ~TpvResContourCutSimpleRenderer ();
  void SetGeometry (TpvResCutSimpleGeometry* g);
private:
  // virtual methods
  void DoRender ();
  void DoRenderSelection ();
private:
  TpvResCutSimpleGeometry* m_geometry;
};

#endif
