// Cut geometry Iso-contour renderer (with layer separation)
// fabraham@tecgraf.puc-rio.br
// Feb 2008
#ifndef TPVRES_CONTOUR_CUT_RENDERER_H
#define TPVRES_CONTOUR_CUT_RENDERER_H

#include "contour.h"
#include <topsviewres/defines.h>

class TPVRES_API TpvResContourCutRenderer : public TpvResContourRenderer
{
public: 
  TpvResContourCutRenderer ();
  virtual ~TpvResContourCutRenderer ();
  /**
   * Specifies that the cut plane faces can be transparent (default=false).
   */
  void SetTransparent (bool f)
  {
    m_transparent = f;
  }

protected:
  void PreRender ();
  void PostRender ();

private:
  // virtual methods
  virtual void DoRender () = 0;
  virtual void DoRenderSelection () = 0;

private:
  bool m_transparent;
};

#endif

