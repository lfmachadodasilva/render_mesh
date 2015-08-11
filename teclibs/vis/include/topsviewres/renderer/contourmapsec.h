// Map and Section Iso-contour renderer
// fabraham@tecgraf.puc-rio.br
// Feb 2008
#ifndef TPVRES_MAP_SEC_RENDERER_H
#define TPVRES_MAP_SEC_RENDERER_H

#include "contour.h"
#include <topsviewres/defines.h>

class TpvResMapSecGeometry;
class SciColorScaleTex;
class TpvQuadSet;

class TPVRES_API TpvResContourMapSecRenderer : public TpvResContourRenderer
{
public:
  typedef enum
  {
    NORMAL,
    ACTIVE_CELLS,
    UNDER,
    NONE,
  } WireframeMode;
  TpvResContourMapSecRenderer ();
  virtual ~TpvResContourMapSecRenderer ();
  void SetGeometry (TpvResMapSecGeometry* g);
  void SetColorScaleTex (SciColorScaleTex *tex)
  {
    m_texture = tex;
  }
  void SetWireframeMode (WireframeMode mode)
  {
    m_wireframe_mode = mode;
  }
  void SetGapEnabled (bool f)
  {
    m_gap_enabled = f;
  }
  bool IsGapEnabled () const
  {
    return m_gap_enabled;
  }
  void SetGapColor (float r, float g, float b)
  {
    m_gap_color[0] = r;
    m_gap_color[1] = g;
    m_gap_color[2] = b;
  }
  void SetGapThickness (float thickness)
  {
    m_gap_thickness = thickness;
  }
  // Draws Wireframe and Gaps over a reservoir image
  void RenderOverlay ();
protected:
  void DoRenderFill (TpvGeometrySet* set);
  void DoRenderGap ();
  WireframeMode GetWireframeMode () const
  {
    return m_wireframe_mode;
  }
  TpvResMapSecGeometry* GetGeometry () const
  {
    return m_geometry;
  }
private:
  void DoRenderActive ();
  void DoRenderInactiveFill ();
  void DoRenderInactiveNoFill ();
  virtual void DoRender ();
  virtual void DoRenderSelection ();
private:
  TpvResMapSecGeometry* m_geometry;
  SciColorScaleTex* m_texture;
  WireframeMode m_wireframe_mode;
  float m_gap_color[3];
  float m_gap_thickness;
  bool m_gap_enabled;
};

#endif

