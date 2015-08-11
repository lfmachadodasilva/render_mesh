#ifndef RES_RENDER_CUT_H
#define RES_RENDER_CUT_H

#include <gpos/model/completion.h>
#include <gpos/model/well.h>
#include <gpos/model/render.h>
#include <gpos/defines.h>
#include <gpos/render3d/render3d.h>
#include <ds/list.h>

class ResCutModelRenderer;
class TpvResCutGeometry;

class RESRENDERAPI ResCutWellRenderer : public ResWellRenderer
{
  typedef DsList<int> CompletionIndicesList;
public:
  ResCutWellRenderer (ResCompletionRenderer *renderer, SciColorScale* cs)
  : ResWellRenderer(renderer, cs)
  , m_mdlRenderer(NULL)
  {
  }
  bool CompletionIntersects (int well, int comp, float* centroid = NULL);
  int GetCompletionKInRootModel (int well, int comp);
  void Render (int element);
  void RenderBegin();
  void RenderEnd();
  void RenderName (int element);
  void RenderNameBegin();
  void RenderNameEnd();
  void SetModelRenderer(ResCutModelRenderer *mdlrenderer)
  {
    m_mdlRenderer = mdlrenderer;
  }
  bool CollectCompletions (int well,
                           Res3DRenderingContext *ctx,
                           CompletionIndicesList *indiceslist);
  void CalcPointWithScale (AlgVector &dest)
  {
    dest.x = m_cx + (dest.x - m_cx)*m_sx;
    dest.y = m_cy + (dest.y - m_cy)*m_sy;
    dest.z = m_cz + (dest.z - m_cz)*m_sz;
  }
  void CalcPointWithScale (AlgVector &dest, float x, float y, float z)
  {
    dest.x = m_cx + (x - m_cx)*m_sx;
    dest.y = m_cy + (y - m_cy)*m_sy;
    dest.z = m_cz + (z - m_cz)*m_sz;
  }
  float CalcPointWithScaleZ (float z)
  {
    return m_cz + (z - m_cz)*m_sz;
  }
private:
  ResCutModelRenderer* m_mdlRenderer;
  CompletionIndicesList m_compindiceslist;
  float m_cx, m_cy, m_cz, m_sx, m_sy, m_sz, m_trans;
};

class RESRENDERAPI ResCutCompletionRenderer : public ResCompletionRenderer
{
public:
  ResCutCompletionRenderer();
  void SetModelRenderer(ResCutModelRenderer *mdlrenderer)
  {
    m_mdlRenderer = mdlrenderer;
  }
  bool CalcCenterAndRadius (int well, int comp, ResRenderingContext *ctx, AlgVector *center, float *radius);
  void Render (int well, int comp);
  void RenderBegin();
  void RenderEnd();
  void SetWellRenderer (ResCutWellRenderer *wr)
  {
    m_wr = wr;
  }
private:
  ResCutWellRenderer *m_wr;
  ResCutModelRenderer* m_mdlRenderer;
  GLUquadricObj *d_quadric;
};

class RESRENDERAPI ResCutModelRenderer : public Res3DModelRenderer
{
public:
  ResCutModelRenderer(
    ResCellRenderer *cellr,
    ResWellRenderer *wellr,
    ResCompletionRenderer *compr,
    SciColorScale *color_scale) :
  Res3DModelRenderer(cellr, wellr, compr, color_scale, NULL)
  {
  }
  virtual ~ResCutModelRenderer(){}
  // reimplemented virtual methods
  /**
   * Get the render mode used by this renderer to draw well names
   */
  virtual UFontMessage::RenderMode GetWellNameRenderMode ()
  {
    return ResModelRenderer::GetWellNameRenderMode();
  }
  virtual void DrawWellName (int well,
                             float r,
                             float g,
                             float b,
                             float x,
                             float y,
                             float z,
                             float sdx,
                             float sdy,
                             float sdz)
  {
    // call original renderer (not 3d renderer)
    ResModelRenderer::DrawWellName(well, r, g, b, x, y, z, sdx, sdy, sdz);
  }
  bool MustRefine() const;
  void RenderBegin();
  void RenderEnd();
  TpvResCutGeometry* GetResCut();
private:
  virtual void CreateTopsView (Res3DRenderData *renderData);
  virtual void SmoothnessChanged ();
  virtual void ModelChanged ();
  virtual void ColorScaleChanged (int& data_ts);
  virtual void PropertyChanged (ResProperty *prop);
  // virtual methods
  bool EnableCutPlane(
    Res3DRenderData* renderData,
    bool drawing_section,
    bool separating_layers);
private:
};

class RESRENDERAPI ResCutRenderingContext : public Res3DRenderingContext
{
public:
  ResCutRenderingContext(int nlayers, ResModel *mdl) : Res3DRenderingContext(nlayers,mdl),m_mustRefine(true)
  {
  }
  void SetMustRefine( bool r )
  {
    m_mustRefine = r;
  }
  bool GetMustRefine() const
  {
    return m_mustRefine;
  }
private:
  bool m_mustRefine;
};

#endif

