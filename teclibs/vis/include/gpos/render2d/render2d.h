//* render.h
// Reservoir rendering routines (Map and Section).
// Tecgraf/PUC-Rio
// Jan 2004

#ifndef RES_RENDER_MAPSEC_H
#define RES_RENDER_MAPSEC_H

#include <gpos/model/render.h>
#include <gpos/model/geometry.h>
#include <gpos/defines.h>
#include <well/well2d.h>
#include <ds/list.h>
#include <lic/image.h>
#include <ugl/texture.h>

#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/glew.h>
#include <GL/glu.h>

// Enables old code API

// Enables completion drawings using images
#define RES_USE_COMPLETION_SYMBOL_IMAGES

// Enables a different well height for each well,
// where its height depends on the reservoir relief.
#define USE_RELIEF_WELL_HEIGHT

// Enables flow map
#define USE_FLOW_MAP

class TpvResContourMapSecRenderer;
class ResMapSecRenderingContext;
class ResMapSecRenderData;
class ResMapSecModelRenderer;
class ResMapSecWellRenderer;

class RESRENDERAPI ResMapSecCellRenderer : public ResCellRenderer
{
public:
  ResMapSecCellRenderer(SciColorScale *color_scale)
  : ResCellRenderer(color_scale)
  , m_mdlr(NULL)
  , m_render_ts(-1)
  , m_render_lic_ts(-1)
  , m_render_lic3_ts(-1)
  {
  }
  virtual ~ResMapSecCellRenderer()
  {
  }
  /**
   * Specifies the reservoir renderer being used along with this renderer.
   * This specification is mandatory for the renderer to work.
   */
  void SetModelRenderer(ResMapSecModelRenderer *mdlr)
  {
    assert(mdlr);
    m_mdlr = mdlr;
  }
  virtual ResModelRenderer* GetModelRenderer() const;
  virtual void RenderBegin ();
  virtual void RenderEnd ();
  virtual void Render ();
  AlgMatrix GetCellsTransformation();
  /**
   * If data_ts is NULL, assumes vector field info has changed.
   */
  void RefreshVectorField (bool useAutofill, int* data_ts = NULL);
private:
  void RenderLic ();
  void RenderLic3 (); // Triphase Lic
  virtual bool MustUsePerElemColor () const;
private:
  ResMapSecModelRenderer *m_mdlr;
  int m_render_ts;
  int m_render_lic_ts;
  int m_render_lic3_ts;
};

class RESRENDERAPI ResMapSecCompletionRenderer : public ResCompletionRenderer
{
public:
  ResMapSecCompletionRenderer();
  virtual ~ResMapSecCompletionRenderer();
  /**
   * Specifies the reservoir renderer being used along with this renderer.
   * This specification is mandatory for the renderer to work.
   */
  void SetModelRenderer(ResMapSecModelRenderer *mdlr)
  {
    assert(mdlr);
    m_mdlr = mdlr;
  }
  /**
   * Specifies the well renderer being used along with this renderer.
   * This specification is mandatory for the renderer to work.
   */
  void SetWellRenderer(ResMapSecWellRenderer *wr)
  {
    assert(wr);
    m_wr = wr;
  }
  void Render (int well, int comp);
  void RenderBubble (int well, int comp, float r, bool innerCircle);
  void RenderBegin();
  void RenderEnd();
  /**
   * Computes the given well completion's center and radius.
   * This method projects the completion onto the current section.
   */
  void CalcCenterAndRadius (int well,
                            int comp,
                            ResMapSecRenderingContext *ctx,
                            AlgVector *center,
                            float *radius);
protected:
  /**
   * Obtains the reservoir renderer being used along with this renderer.
   */
  ResMapSecModelRenderer* GetModelRenderer() const
  {
    return m_mdlr;
  }
private:
  float d_radius;
  GLUquadricObj *d_quadric;
  ResMapSecModelRenderer *m_mdlr;
  ResMapSecWellRenderer *m_wr;
};

class RESRENDERAPI ResMapSecWellRenderer : public ResWellRenderer
{
public:
  enum WellPropType
  {
    NULL_PROP = 5,
    FLOW_PROP = 6,
  };
  struct Completion
  {
    int well;
    int comp;
    Completion ()
    : well(-1)
    , comp(-1)
    {
    }
    Completion (int well, int comp)
    : well(well)
    , comp(comp)
    {
    }
    bool WasInitialized () const
    {
      return well != -1 && comp != -1;
    }
  };
  typedef DsList<Completion> CompletionList;
  ResMapSecWellRenderer (ResCompletionRenderer *compr, SciColorScale *cs) :
    ResWellRenderer(compr, cs),
    m_mdlr(NULL)
    , m_numCompletions(0)
    , m_tex_quad_disp_list(0)
    , m_renderers()
    , m_render_ts(-1)
    , m_prod_at_section_tex(NULL)     
    , m_prod_before_section_tex(NULL)
    , m_prod_after_section_tex(NULL)
    , m_inj_at_section_tex(NULL)     
    , m_inj_before_section_tex(NULL)
    , m_inj_after_section_tex(NULL)
    , m_flow_tex(NULL)   
  {
  }
  virtual ~ResMapSecWellRenderer()
  {
    DsStringKey k;
    if (m_renderers.First(&k)) {
      do
        delete m_renderers.Get(k);
      while (m_renderers.Next(&k));
    }
    // delete textures 
    delete m_prod_at_section_tex;     
    delete m_prod_before_section_tex;
    delete m_prod_after_section_tex;
    delete m_inj_at_section_tex;     
    delete m_inj_before_section_tex;
    delete m_inj_after_section_tex;
    delete m_flow_tex;               
    if (m_tex_quad_disp_list)
      W2dWellSet::DestroyTexturedQuadDisplayList(m_tex_quad_disp_list);
  }
  /**
   * Specifies the reservoir renderer being used along with this renderer.
   * This specification is mandatory for the renderer to work.
   */
  void SetModelRenderer(ResMapSecModelRenderer *mdlr)
  {
    assert(mdlr);
    m_mdlr = mdlr;
  }
  void Render (int element);
  void RenderBubble (int well);
  void RenderBegin();
  void RenderEnd();
  /**
   * Name rendering functions.
   * Assumes that RenderBegin was called.
   */
  void RenderName (int element);
  void RenderNameBegin();
  void RenderNameEnd();
  void CalcPointWithScale (AlgVector &dest) const
  {
    dest.x = m_cx + (dest.x - m_cx)*m_sx;
    dest.y = m_cy + (dest.y - m_cy)*m_sy;
    dest.z = m_cz + (dest.z - m_cz)*m_sz;
  }
  void CalcPointWithScale (AlgVector &dest, AlgVector &p) const
  {
    dest.x = m_cx + (p.x - m_cx)*m_sx;
    dest.y = m_cy + (p.y - m_cy)*m_sy;
    dest.z = m_cz + (p.z - m_cz)*m_sz;
  }
  void CalcPointWithScale (AlgVector &dest, float x, float y, float z) const
  {
    dest.x = m_cx + (x - m_cx)*m_sx;
    dest.y = m_cy + (y - m_cy)*m_sy;
    dest.z = m_cz + (z - m_cz)*m_sz;
  }
  float CalcPointWithScaleZ (float z) const
  {
    return m_cz + (z - m_cz)*m_sz;
  }
  AlgVector GetWellTopCoordinates (int well) const;
  /**
   * Collects the list of completions for the well 'well'.
   * If ctx->CompletionVisibilityMode() specifies that only completions lying in the current
   * section must be rendered (ResMapSecRenderingContext::SECTION), only
   * the completions lying on the current section and in active cells will be collected.
   * Else, collects all completions that, when projected to the current section,
   * will lie on active cells (ResMapSecRenderingContext::ALL).
   * If 'indiceslist' is specified, then for every completion added to the list,
   * it inserts the completion position in the well (0-based).
   */
  bool CollectCompletions (CompletionList *complist,
                           int well,
                           ResMapSecRenderingContext *ctx);
  /**
   * Does the same as above method, except it returns a list of all completions indicating
   * which ones are at section.
   */
  bool CollectAllCompletions (CompletionList *complist,
                              DsArray<bool> *compvisible,
                              int well,
                              ResMapSecRenderingContext *ctx);

protected:
  /**
   * Obtains the reservoir renderer being used along with this renderer.
   */
  ResMapSecModelRenderer* GetModelRenderer() const
  {
    return m_mdlr;
  }
private:
  W2dWell* BuildRenderer (int well);
  /**
   * Reads flow and completion image files.
   */
  void LoadRendererImageSymbols ();
  void SetRendererImageSymbols (W2dWell* renderer, int well);
  void SetCompletionSymbols (W2dWell* renderer);
  // Returns completions coordinates, ids, if completions are visible (if 'AT_SECTION' mode), and size.
  int GetCompletionsAttr(int well, AlgVector** compCoords, bool** compVisible);
  bool GetLastCompletion (int well, AlgVector* compCoord, int* compID);
  void InitRenderer (W2dWell* renderer, int well);
  /**
   * Update completions positions and visibility.
   */
  void UpdateCompletion (W2dWell* renderer, int well, int comp);
  /**
   * Updates well renderer in case there is a change in section.
   */
  void UpdateRenderer (W2dWell* renderer, int well);
  // comp_id refers to the completion stored by ResMapSecWellRenderer,
  // comp_index refers to completion index referenced in W2dWell renderer.
  void SetCompletionAttr (W2dWell* renderer, int well, int comp_id);
  // Updates pick ids
  void SetWellProperties (W2dWell* renderer, int well, int comp_id);
  // Comp refers to completion index stored in W2dWell renderer.
  void SetBubbleProperties (W2dWell* renderer, int well);
  /**
   * Sets a flow map in which wells are drawn in circles with radius determined 
   * by the maximum sum of all wells flow properties in all timesteps. Color 
   * is determined by linear interpolation considering gas, oil and water flow
   * value weights.
   */
  void SetFlowMapProperties (W2dWell* renderer, int well);
private:
  ResMapSecModelRenderer *m_mdlr;
  CompletionList m_complist;
  float m_cx, m_cy, m_cz, m_sx, m_sy, m_sz;
  int m_numCompletions;
  float m_wellwidth;
  GLuint m_tex_quad_disp_list;
  DsHash<int, float> m_flowRadius;
  DsHash<DsStringKey,W2dWell*> m_renderers;
  DsHash<int, int> m_prevsec;  // used to identify the previous map section before changing sections
  int m_render_ts;
  bool m_cs_old_modulate;
  // completion and flow textures
  UGLTexture* m_prod_at_section_tex;     // producers and undefined wells
  UGLTexture* m_prod_before_section_tex;
  UGLTexture* m_prod_after_section_tex;
  UGLTexture* m_inj_at_section_tex;     // injector wells
  UGLTexture* m_inj_before_section_tex;
  UGLTexture* m_inj_after_section_tex;
  UGLTexture* m_flow_tex;               // flow map image

};

class RESRENDERAPI ResMapSecModelRenderer : public ResModelRenderer
{
public:
  ResMapSecModelRenderer(
    ResCellRenderer *cellr,
    ResWellRenderer *wellr,
    ResCompletionRenderer *compr,
    SciColorScale *color_scale) :
      ResModelRenderer(cellr, wellr, compr, color_scale),
      m_pickbuffer(NULL),
      m_pickbuffersize(0)
  , m_render_cells_ts(-1)
  , m_render_cells_with_prop_ts(-1)
  {
  }
  virtual ~ResMapSecModelRenderer()
  {
  }
  void RenderBegin ();
  void Render ();
  void RenderEnd ();
  void LoadCellsTransformation();
  AlgMatrix GetCellsTransformation();
  PickHit* DoPick (float x, float y);
  /**
   * Performs selection on the model.
   * 'x' and 'y' are the normalized coordinates of the point being selected.
   *
   * Returns the index of the selected cell if any cell was hit.
   * Returns a negative number otherwise.
   */
  int CellSelection (float x, float y);
  /**
   * Obtains the bonding box of what is drawn according to 'ctx'.
   * xmin,xmax,ymin,ymax,zmin,zmax will be calculated if the pointers are
   * supplied (!= NULL).
   */
  bool GetDrawBoundingBox (ResMapSecRenderingContext *ctx,
                           float *xmin,
                           float *xmax,
                           float *ymin,
                           float *ymax,
                           float *zmin,
                           float *zmax);
protected:
  ResMapSecRenderData* GetRenderData ();
private:
  void RenderCells ();
  bool PrepareVisibleCells (int whichsec, int sec, int& data_ts);
  void CreateTopsView ();
  void DestroyTopsView (ResMapSecRenderData* renderData);
  void ColorScaleChanged (int& data_ts);
  void SmoothnessChanged ();
  void ModelChanged ();
  virtual TpvResContourMapSecRenderer* BuildResRenderer ();
  virtual void PropertyChanged (ResProperty *prop);
  /**
   * Informs that the current cell selection changed.
   */
  virtual void CellSelectionChanged (ResProperty *prop)
  {
  }

private:
  DsHash<ResModelNew*,ResMapSecRenderData*> m_renderdata;
  GLuint *m_pickbuffer;
  int m_pickbuffersize;
  int m_render_cells_ts;
  int m_render_cells_with_prop_ts;
private:
  friend class ResMapSecCellRenderer;
};

class RESRENDERAPI ResMapSecRenderingContext : public ResRenderingContext
{
public:
  enum WireframeMode {
    NORMAL,
    ACTIVECELLS,
    UNDER,
    OFF
  };
  enum CompVisMode {
    ALL,
    SECTION,
    NONE
  };
  enum WellMode 
  {
    PLAIN_MAP,    // Drawing well map with completions and links
    BUBBLE_MAP,   // Drawing map in bubble mode
    FLOW_MAP,     // Drawing map in flow mode
  };
  
  ResMapSecRenderingContext(ResModel *mdl);
  virtual ~ResMapSecRenderingContext();
  void SetDrawRefined (bool f)
  {
    m_draw_refined = f;
  }
  bool DrawRefined () const
  {
    return m_draw_refined;
  }
  void SetSecI (int i);
  void SetSecJ (int j);
  void SetSecK (int k);
  int SecI () const
  {
    return m_seci;
  }
  int SecJ () const
  {
    return m_secj;
  }
  int SecK () const
  {
    return m_seck;
  }
  void SetMapCameraInverted (bool f)
  {
    m_invk = f;
  }
  bool MapCameraInverted () const
  {
    return m_invk;
  }
  void SetCompletionVisibilityMode (CompVisMode m)
  {
    if (m_compvis == m)
      return;
    m_compvis = m;
    SetChanged(ResRenderingContext::COMPVISIBILITYMODE);
    SetAllWellsChanged(ResRenderingContext::COMPVISIBILITYMODE, true);
  }
  CompVisMode CompletionVisibilityMode () const
  {
    return m_compvis;
  }
  void SetCompletionScale (float s)
  {
    if (m_compscale == s)
      return;
    m_compscale = s;
    SetChanged(ResRenderingContext::COMPRADIUS);
    SetAllWellsChanged(ResRenderingContext::COMPRADIUS, true);
  }
  float CompletionScale () const
  {
    return m_compscale;
  }
  void SetWireframeMode (WireframeMode m)
  {
    m_wireframe = m;
  }
  WireframeMode GetWireframeMode () const
  {
    return m_wireframe;
  }
  void SetWellMode (WellMode m);
  WellMode GetWellMode () const
  {
    return m_wellmapmode;
  }
  void SetGapVisible (bool f)
  {
    m_viewgap = f;
  }
  bool GapVisible () const
  {
    return m_viewgap;
  }
  void SetGapColor (float r, float g, float b)
  {
    m_gr = r;
    m_gg = g;
    m_gb = b;
  }
  void GapColor (float *r, float *g, float *b)
  {
    *r = m_gr;
    *g = m_gg;
    *b = m_gb;
  }
  void SetGapThickness (int w)
  {
    m_gthickness = w;
  }
  int GapThickness () const
  {
    return m_gthickness;
  }
  void SetFillInactive (bool f)
  {
    m_fill_inactive = f;
  }
  bool FillInactive () const
  {
    return m_fill_inactive;
  }
  void SetBubbleStep (int mapStepIndex);
  int BubbleStep() const
  {
    return m_bubble_elem_step;
  }
  /**
  * Sets a property name.
  * 'prop' cannot be higher than 4.
  */
  void SetBubblePropertyName (int prop, const char* name);
  const char* BubblePropertyName (int prop) const
  {
    return m_bubble_prop_name[prop];
  }
  /**
  * Sets a property color.
  * 'prop' cannot be higher than 4.
  * 'color' is the property color in format rgb.
  */
  void SetBubblePropertyColor (int prop, unsigned char color[3]);
  void BubblePropertyColor (int prop, unsigned char color[3]) const
  {
    color[0] = m_bubble_prop_color[3*prop+0];
    color[1] = m_bubble_prop_color[3*prop+1];
    color[2] = m_bubble_prop_color[3*prop+2];
  }
  int BubbleNumberOfProperties () const
  {
    return m_bubble_num_props;
  }
  void SetBubbleNumberOfProperties (int p)
  {
    if (m_bubble_num_props == p)
      return;
    assert(p >= 0 && p <= 4);
    m_bubble_num_props = p;
    SetChanged(ResRenderingContext::BUBBLE);
    SetAllWellsChanged(ResRenderingContext::BUBBLE, true);
  }
  void SetWellWidthFactor (float f);
  /**
  *  For internal use
  */
  float GetWellWidthFactor () const
  {
    return m_well_width_factor;
  }
  /**
   * Defines a scale factor for smaller completions (image symbols).
   */
  void SetCompScaleFactor (float s)
  {
    m_comp_scale = s;
  }
  /**
   * Obtains the scale factor for smaller completions (image symbols).
   */
  float GetCompScaleFactor () const
  {
    return m_comp_scale;
  }
  /**
  * Computes the max value of the ith property.
  */
  void FillBubblePropertyMaxValue (int i);
  float BubbleMaxPropertiesValues (int prop) const
  {
    return m_bubble_prop_max[prop];
  }
  void SetFlowPropertyName (const char* fo, const char* fg, const char* fw);
  /**
   * Computes the maximum flow property for all wells.
   */
  void FillFlowPropertyMaxValue (const char* fo, const char* fg, const char* fw); 
  /**
   * Gets the maximum flow property (oil + gas + water) for all wells.
   **/
  float GetFlowMaxValue () const
  {
    return m_flow_prop_max;
  }
  float GetFlowGasWeight () const
  {
    return m_flow_gas_weight;
  }
  /**
   * Gets the minimum flow property (oil + gas + water) for all wells.
   **/
  float GetFlowMinValue () const
  {
    return m_flow_prop_min;
  }
  const char* GetFlowPropName (int flowtype) const
  {
    return m_flow_prop_name[flowtype];
  }
  bool IsFlowMapEnabled () const
  {
    return (m_wellmapmode == FLOW_MAP &&
            SecK() != -1);
  }
  void GetResFlowMapColor (float* color) const
  {
    color[0] = m_flow_map_color[0];
    color[1] = m_flow_map_color[1];
    color[2] = m_flow_map_color[2];
  }
  void SetResFlowMapColor (float r, float g, float b);
private:
  void SetWillRenderAnyCell (bool flag)
  {
    m_will_render_any_cell = flag;
  }
  bool WillRenderAnyCell () const
  {
    return m_will_render_any_cell;
  }
  
private:
  bool m_will_render_any_cell; // whether any cell should be rendered
  bool m_draw_refined;
  int m_seci, m_secj, m_seck;     // sections to perform
                            // a value of -1 indicates that sectioning shouldn't be performed at the
                            // given axis
                            // it is always assumed that one and only one section is different from -1
  bool m_invk;                // true if the y of the camera is inverted in map view.
  CompVisMode m_compvis;      // completions visibility setting
  float m_compscale;          // completion radius scale factor
  WireframeMode m_wireframe;  // wireframe mode
  WellMode m_wellmapmode;
//  unsigned char m_cr, m_cg, m_cb; // contour color
//  float m_cthickness;         // contour thickness
  bool m_viewgap;         // gap highlight toggle
  float m_gr, m_gg, m_gb; // gap color
  int m_gthickness;       // gap thickness
  bool m_fill_inactive;   // fill inactive cells values?
  int m_bubble_num_props; // number of properties on a bubble (max = 4)
  char* m_bubble_prop_name[4];
  float m_bubble_prop_max[4];
  unsigned char m_bubble_prop_color[12];
  int m_bubble_elem_step;
  char* m_flow_prop_name[3];    // name of maximum flow properties for oil, gas, water, respectively.
  float m_flow_prop_max;        // maxiumum flow value (foil + fgas + fwater)
  float m_flow_prop_min;        // minumum flow value (foil + fgas + fwater)
  float m_flow_gas_weight;      // sclae value applied to flow gas since its measures is 10e6 greater than other flows
  float m_flow_map_color[3];    // reservoir cells color when in flow map
  float m_well_width_factor;       // default is 1 (f < 1 shrinks and f > 1 enlarges well width)
  float m_comp_scale;  // defines a scale factor for smaller completions (image symbols).
  
private:
  friend class ResMapSecModelRenderer;
  friend class ResMapSecCellRenderer;
};

#endif

