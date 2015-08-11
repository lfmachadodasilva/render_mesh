// Cut geometry Iso-contour renderer (with layer separation)
// fabraham@tecgraf.puc-rio.br
// Feb 2008
// cpalomo@tecgraf.puc-rio.br
// May 2010
#ifndef TPVRES_CONTOUR_CUT_SEP_RENDERER_H
#define TPVRES_CONTOUR_CUT_SEP_RENDERER_H

#include "contourcut.h"
#include <topsviewres/defines.h>

class TpvResCutSepGeometry;

class TPVRES_API TpvResContourCutSepRenderer : public TpvResContourCutRenderer
{
public: 
  TpvResContourCutSepRenderer ();
  virtual ~TpvResContourCutSepRenderer ();
  void SetGeometry (TpvResCutSepGeometry* g);
  void SetSeparations (const float* separations);
private:
  // virtual methods
  void DoRender ();
  void DoRenderSelection ();
private:
  TpvResCutSepGeometry* m_geometry;
  float *m_separations;
};

#endif  // TPVRES_CONTOUR_CUT_SEP_RENDERER_H
