// Transparent Iso-contour renderer (with separation)
// fabraham@tecgraf.puc-rio.br
// Feb 2008
#ifndef TPVRES_CONTOUR_TRANSP_SEP_RENDERER_H
#define TPVRES_CONTOUR_TRANSP_SEP_RENDERER_H

#include "contourtransp.h"
#include <topsviewres/defines.h>

class TpvResTranspSepGeometry;

class TPVRES_API TpvResContourTranspSepRenderer : public TpvResContourTranspRenderer
{
public:
  TpvResContourTranspSepRenderer();
  virtual ~TpvResContourTranspSepRenderer();
  void SetGeometry(TpvResTranspSepGeometry* g)
  {
    m_geometry = g;
  }
  virtual TpvResTranspGeometry* GetGeometry() const;
private:
  // virtual methods
  void RenderOpaque();
private:
  TpvResTranspSepGeometry *m_geometry;
};

#endif
