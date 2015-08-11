#include <ugl/ugl.h>

//#define VERBOSE

MODEL_CLASS_TEMPLATE
int TpvPolyWireframeRenderer3<MODELCLASS>::InitExtensions ()
{
  static bool initialized = false;
  if (initialized)
    return 1;
  initialized = true;
  return 1;
}

MODEL_CLASS_TEMPLATE
void TpvPolyWireframeRenderer3<MODELCLASS>::DrawArray(int n, int dim, 
                                       float* pos, float* normal, float* scalar)
{
  glPushClientAttrib(GL_CLIENT_VERTEX_ARRAY_BIT);
  if (pos) {
    glVertexPointer(3, GL_FLOAT, 0, pos);
    glEnableClientState(GL_VERTEX_ARRAY);
  }
  if (normal) {
    glNormalPointer(GL_FLOAT, 0, normal);
    glEnableClientState(GL_NORMAL_ARRAY);
  }
  if (scalar) {
    glTexCoordPointer(1, GL_FLOAT, 0, scalar);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  }
  if (dim == 0) // points
    glDrawArrays(GL_POINTS, 0, n);
  else if (dim == 1) // lines
    glDrawArrays(GL_LINES, 0, 2*n);
  glPopClientAttrib();
}

MODEL_CLASS_TEMPLATE
void TpvPolyWireframeRenderer3<MODELCLASS>::RenderLines()
{
  for (typename LineList::Iterator it = m_line_geoms.Begin(); it.Valid(); ++it) {
    TpvLineGeometry3<MODELCLASS>* g = it.Self();
    for (int step_id = m_base_id + m_nsteps; step_id > m_curr_step; step_id--) {
      TpvLineSet2* lin = g->GetLines(step_id);
      int n = lin->GetSize();
      float* pos = lin->GetPositions()->GetArray();
      DrawArray(n, 1, pos, NULL, NULL); 
    }
  }
}


MODEL_CLASS_TEMPLATE
bool TpvPolyWireframeRenderer3<MODELCLASS>::Update()
{
  for (typename LineList::Iterator it = m_line_geoms.Begin(); it.Valid(); ++it)
    it.Self()->Update();
  m_update_geometry = false;
  return true;
}

/*************
public
**************/
//constructor
MODEL_CLASS_TEMPLATE
TpvPolyWireframeRenderer3<MODELCLASS>::TpvPolyWireframeRenderer3()
  : m_base_id(1), m_nsteps(1), m_curr_step(1),
  m_update_geometry(true),
  m_clip_plane_enabled(false),
  m_poly_offset_factor(0), m_poly_offset_units(0), m_poly_offset_enabled(false),
  m_render_lines(true)
{
  InitExtensions();
  m_clip_plane[0] = 0.0f;
  m_clip_plane[1] = 0.0f;
  m_clip_plane[2] = 1.0f;
  m_clip_plane[3] = 0.0f;
  m_line_color[0] = m_line_color[1] = m_line_color[2] = 0; m_line_color[3] = 1;
  m_line_width = 1;
}

MODEL_CLASS_TEMPLATE
TpvPolyWireframeRenderer3<MODELCLASS>::~TpvPolyWireframeRenderer3()
{
}

MODEL_CLASS_TEMPLATE
void TpvPolyWireframeRenderer3<MODELCLASS>::AddLineGeometry(TpvLineGeometry3<MODELCLASS>* g)
{
  if (g) {
    m_line_geoms.Append(g);
    m_update_geometry = true;
  }
}

MODEL_CLASS_TEMPLATE
void TpvPolyWireframeRenderer3<MODELCLASS>::ClearLineGeometries()
{
  m_line_geoms.Clear();
  m_update_geometry = true;
}

MODEL_CLASS_TEMPLATE
void TpvPolyWireframeRenderer3<MODELCLASS>::SetBaseId(int id)
{
  m_base_id = id;
}

MODEL_CLASS_TEMPLATE
int TpvPolyWireframeRenderer3<MODELCLASS>::GetBaseId()
{
  return m_base_id;
}

MODEL_CLASS_TEMPLATE
void TpvPolyWireframeRenderer3<MODELCLASS>::SetNumOfSteps(int n)
{
  m_nsteps = n;
}

MODEL_CLASS_TEMPLATE
void TpvPolyWireframeRenderer3<MODELCLASS>::SetCurrentStep(int step_id)
{
  m_curr_step = step_id;
}

MODEL_CLASS_TEMPLATE
void TpvPolyWireframeRenderer3<MODELCLASS>::SetClippingPlane(float a, float b, float c, float d)
{
  m_clip_plane[0] = a; m_clip_plane[1] = b; m_clip_plane[2] = c; m_clip_plane[3] = d;
}

MODEL_CLASS_TEMPLATE
void TpvPolyWireframeRenderer3<MODELCLASS>::SetClippingPlaneEnabled(bool flag)
{
  m_clip_plane_enabled = flag;
}

MODEL_CLASS_TEMPLATE
void TpvPolyWireframeRenderer3<MODELCLASS>::SetPolygonOffset(float factor, float units)
{
  m_poly_offset_factor = factor;
  m_poly_offset_units = units;
}

MODEL_CLASS_TEMPLATE
void TpvPolyWireframeRenderer3<MODELCLASS>::SetPolygonOffsetEnabled(bool flag)
{
  m_poly_offset_enabled = flag;
}

MODEL_CLASS_TEMPLATE
void TpvPolyWireframeRenderer3<MODELCLASS>::SetRenderLines(bool flag)
{
  m_render_lines = flag;
}


MODEL_CLASS_TEMPLATE
void TpvPolyWireframeRenderer3<MODELCLASS>::Render()
{
  Update();

  glPushAttrib(GL_ENABLE_BIT | GL_TRANSFORM_BIT |  // clip plane
    GL_CURRENT_BIT | GL_LIGHTING_BIT | 
    GL_POLYGON_BIT | GL_LINE_BIT | GL_POINT_BIT | GL_DEPTH_BUFFER_BIT);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glDisable(GL_LIGHTING);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  
  if (m_clip_plane_enabled) {
    double plane[4] = {m_clip_plane[0], m_clip_plane[1], m_clip_plane[2], m_clip_plane[3]};
    glClipPlane(GL_CLIP_PLANE0, plane);
    glEnable(GL_CLIP_PLANE0);
  }

  bool render_lines = m_render_lines && m_line_geoms.Size() > 0;
  if (render_lines) {
    if (m_poly_offset_enabled) {
      glPolygonOffset(m_poly_offset_factor, m_poly_offset_units);
      glEnable(GL_POLYGON_OFFSET_LINE);
    }
    glColor4fv(m_line_color);
    glLineWidth(m_line_width);
    RenderLines();
  }

  glPopAttrib();
}

