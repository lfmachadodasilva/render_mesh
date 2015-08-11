// Iso-contour renderer (with layer separation)
// fabraham@tecgraf.puc-rio.br
// Feb 2008
#ifndef TPVRES_CONTOUR_SEP_RENDERER_H
#define TPVRES_CONTOUR_SEP_RENDERER_H

#include "contour.h"
#include <topsviewres/defines.h>

class TpvResBdryFacesSepGeometry;
class AlgVector;

class TPVRES_API TpvResContourSepRenderer : public TpvResContourRenderer
{
public: 
  TpvResContourSepRenderer ();
  virtual ~TpvResContourSepRenderer ();
  void SetGeometry (TpvResBdryFacesSepGeometry* g);
  void SetSeparations (const float* separations);
  void SetObserverPosition (const AlgVector* obspos)
  {
    m_obspos = obspos;
  }
private:
  // virtual methods
  void DoRender ();
  void DoRenderSelection ();
  int* DetermineBestLayerOrdering ();
private:
  TpvResBdryFacesSepGeometry* m_geometry;
  float *m_separations;
  const AlgVector* m_obspos;
};

#endif

