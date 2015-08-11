
#ifndef TPV_POLY_WIREFRAME_RENDERER_3_H
#define TPV_POLY_WIREFRAME_RENDERER_3_H

#include <ds/list.h>

#include "../geometry/linegeometry.h"
#include "renderer3.h"
#include <topsview/defines.h>

/**
    Polygonal contour mapper. Maps triangle, line and 
  scalars to colors.
*/
MODEL_CLASS_TEMPLATE
class TPV_API TpvPolyWireframeRenderer3 : public TpvRenderer3
{
private:
  typedef DsList<TpvLineGeometry3<MODELCLASS>*> LineList;
  LineList m_line_geoms;
  int m_base_id;
  int m_nsteps;
  int m_curr_step;

  bool m_update_geometry;

  float m_clip_plane[4];
  bool  m_clip_plane_enabled;
  float m_poly_offset_factor;
  float m_poly_offset_units;
  bool  m_poly_offset_enabled;

  float m_line_color[4];
  float m_line_width; 

  bool m_render_triangles;
  bool m_render_lines;
 
  void DrawArray(int n, int dim, 
      float* pos, float* normal, float* scalar);
  void RenderLines();

public: 
  TpvPolyWireframeRenderer3();
  virtual ~TpvPolyWireframeRenderer3();

  void AddLineGeometry(TpvLineGeometry3<MODELCLASS>* g);
  void ClearLineGeometries();
  void ClearGeometries()
  {
    ClearLineGeometries();
  }

  virtual void SetBaseId(int id);
  virtual int GetBaseId();

  virtual void SetNumOfSteps(int n);
  virtual void SetCurrentStep(int step_id);

  virtual void SetClippingPlane(float a, float b, float c, float d);
  virtual void SetClippingPlaneEnabled(bool flag);

  virtual void SetPolygonOffset(float factor, float units);
  virtual void SetPolygonOffsetEnabled(bool flag);

  void SetLineColor(float r, float g, float b, float a)
  {
    m_line_color[0] = r; m_line_color[1] = g; m_line_color[2] = b; m_line_color[3] = a;
  }
  
  void GetLineColor(float* r, float* g, float* b, float* a) const
  {
    *r = m_line_color[0]; *g = m_line_color[1]; *b = m_line_color[2]; *a = m_line_color[3];
  }

  void SetLineWidth(float w)
  {
    m_line_width = w;
  }

  float GetLineWidth()
  {
    return m_line_width;
  }

  void SetRenderLines(bool flag);

  virtual bool Update();
  virtual void Render();
private:
  static int InitExtensions ();
};

#include "polywireframe3.inl"

#endif
