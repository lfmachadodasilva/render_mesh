// Iso-contour renderer
// fabraham@tecgraf.puc-rio.br
// rodesp@tecgraf.puc-rio.br
// Feb 2008
#ifndef TPV_CONTOUR_RENDERER_H
#define TPV_CONTOUR_RENDERER_H

#include "renderer.h"
#include <topsview/defines.h>

class UGLGridTex;
class TpvGeometrySet;
class TpvLineSet;
class TpvPointSet;

class TPV_API TpvContourRenderer : public TpvRenderer
{
public: 
  TpvContourRenderer ();
  
  virtual ~TpvContourRenderer ();
  
  /**
   * Enables gridlines drawing.
   */
  void SetGridLinesEnabled (bool flag)
  {
    m_draw_grid = flag;
  }
  
  /**
   * Returns whether gridlines drawing is enabled.
   */
  bool GetGridLinesEnabled () const
  {
    return m_draw_grid;
  }

  /**
   * Set gridlines color.
   */
  void SetGridLinesColor (float r, float g, float b);
  
  /**
   * Get gridlines color.
   */
  void GetGridLinesColor (float *r, float *g, float *b);
  
  /**
   * Set gridlines thickness.
   */
  void SetGridLinesThickness (float t);

  /**
   * Get gridlines thickness.
   */
  float GetGridLinesThickness ();

  /**
   * Enables gridlines intensity attenuation according to distance to observer.
   */
  void SetGridLinesIntensityAttenuation (bool flag);

  /**
   * Get whether gridlines intensity attenuation according to
   * distance to observer is enabled.
   */
  bool GetGridLinesIntensityAttenuation () const;
  
  /**
   * Configures the use of opaque gridlines even when
   * transparency on cell faces is enabled.
   */
  void SetGridLinesOpaqueOnTransparency (bool flag);
  
  /**
   * Configures the use of contour on the wireframe mesh.
   * When it is enabled, polygon filling will be disabled 
   * and lighting will affect the contour lines.
   * Default: false.
   */
  void SetWireframeContourEnabled (bool flag);
  
  /**
   * When wireframe mode is true, cells faces are drawn
   * as transparent, i.e., only polygon lines are drawn.
   */
  void SetWireframeModeCells (bool flag);

  /**
   * Configures the use of geometry field colors (specified through geometry->SetPerElemField).
   */
  void SetFieldEnabled (bool flag)
  {
    m_field_enabled = flag;
  }
  
  /**
   * Configures the use of per elem geometry colors (specified through geometry->SetPerElemColor).
   */
  void SetUsePerElemColor (bool flag)
  {
    m_per_elem_color = flag;
  }
  
  /** 
   * Enable/disable backface culling.
   */
  void SetCullFace (bool flag)
  {
    m_cull_face = flag;
  }
  
  /** 
   * Enable/disable depth test.
   */
  void SetDepthTest (bool flag)
  {
    m_depth_test = flag;
  }

  /**
   * Sets whether lighting is enabled for line rendering.
   * If true, the global lighting settings (see SetLighTingEnabled())
   * will be used. Else, no lighting will be used.
   * Default: true
   */
  void SetLineLightingEnabled (bool flag)
  {
    m_line_lighting_enabled = flag;
  }

  /**
   * Sets whether lighting is enabled for point rendering.
   * If true, the global lighting settings (see SetLightingEnabled())
   * will be used. Else, no lighting will be used.
   * Default: true
   */
  void SetPointLightingEnabled (bool flag)
  {
    m_point_lighting_enabled = flag;
  }

  /**
   * Sets whether line smoothing is enabled.
   * If true, line antialiasing will be switched on. Else, default settings 
   * will be used.
   * Note: line smoothing only takes effect when supported by current
   * OpenGL implementation.
  */
  void SetLineSmoothEnabled (bool flag)
  {
    m_line_smooth_enabled = flag;
  }

  /**
   * Sets whether point smoothing is enabled.
   * If true, rounded points will be drawn instead of square points. Else, 
   * default settings will be used.
   * Note: point smoothing only takes effect when supported by current
   * OpenGL implementation.
   * Default: false
  */
  void SetPointSmoothEnabled (bool flag)
  {
    m_point_smooth_enabled = flag;
  }
  
protected:
  void PrepareSetForRender (TpvGeometrySet *set);
  void PrepareSetForRenderSelection (TpvGeometrySet *set);
  void RenderSet (TpvGeometrySet *set);
  void RenderSet (TpvLineSet *set);
  void RenderSet (TpvPointSet *set);

  void RenderSetSelection (TpvGeometrySet *set);
  void RenderSetSelection (TpvLineSet *set);
  void RenderSetSelection (TpvPointSet *set);
  /**
   * Are per elem colors enabled?
   */
  bool MustUsePerElemColor () const
  {
    return m_per_elem_color;
  }
  /**
   * Is geometry field enabled?
   */
  bool IsFieldEnabled () const
  {
    return m_field_enabled;
  }
  virtual void RenderBegin ();
  virtual void RenderEnd ();
private:
  UGLGridTex *m_gridtex;
  bool m_draw_grid;
  bool m_depth_test;
  bool m_cull_face;
  bool m_field_enabled;
  bool m_per_elem_color;
  bool m_line_lighting_enabled;
  bool m_point_lighting_enabled;
  bool m_line_smooth_enabled;
  bool m_point_smooth_enabled;
  bool m_wireframe_cells_enabled;
};

#endif

