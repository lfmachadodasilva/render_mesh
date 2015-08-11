// Transparent Iso-contour renderer
// fabraham@tecgraf.puc-rio.br
// Feb 2008
#ifndef TPVRES_CONTOUR_TRANSP_RENDERER_H
#define TPVRES_CONTOUR_TRANSP_RENDERER_H

#include "contour.h"
#include <topsviewres/defines.h>

class TpvResTranspGeometry;

class TPVRES_API TpvResContourTranspRenderer : public TpvResContourRenderer
{
public:
  TpvResContourTranspRenderer();
  virtual ~TpvResContourTranspRenderer();
  void SetGeometry(TpvResTranspGeometry* g)
  {
    m_geometry = g;
  }
  virtual TpvResTranspGeometry* GetGeometry() const
  {
    return m_geometry;
  }
protected:
  virtual void RenderBegin ();
  virtual void DoRender ();
  virtual void RenderEnd ();
private:
  virtual void RenderOpaque();
  virtual void RenderTransp();
private:
  TpvResTranspGeometry *m_geometry;
};

#endif

