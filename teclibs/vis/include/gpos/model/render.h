//* render.h
// Reservoir rendering routines.
// Tecgraf/PUC-Rio
// Jan 2004

#ifndef vis_render_h
#define vis_render_h

#include <GL/glew.h>
#include <stdio.h>
#include <assert.h>
#include <ds/array.h>
#include <sciutils/colorscale.h>
#include <ds/hash.h>
#include <alg/matrix.h>
#include <alg/vector.h>
#include <ufont/text.h>

#ifndef GPOSRENDER_DLL
# ifndef TEC_DLL
#  define RESRENDERAPI
# else
#  define RESRENDERAPI __declspec(dllimport)
# endif
#else
# define RESRENDERAPI __declspec(dllexport)
#endif

class ResModel;
class ResModelNew;
class ResPosModelNew;
class ResWell;
class ResCompletion;
class ResGeometry;
class ResProperty;
class ResStep;
class ResRenderingContext;
class ResModelRenderer;
class ResRenderData;
class SciColorScale;
class WWell;

enum ResPickType
{
  CELL = 0,
  WELL,
  COMP,
};

//* 'ResCellRenderer' Class
// Represents an entity capable of rendering cells.
class RESRENDERAPI ResCellRenderer
{
protected:
  ResModelNew *d_mdl;
  ResRenderingContext *d_ctx;
  SciColorScale* d_cs;
  ResCellRenderer()
  : m_model_renderer(NULL)
  {
  }
public:
  ResCellRenderer(SciColorScale *color_scale)
    : d_mdl(0), d_ctx(0), d_cs(color_scale)
  {
  }
  virtual ~ResCellRenderer()
  {
  }
  void SetModel(ResModelNew *mdl)
  {
    d_mdl = mdl;
  }
  void SetContext(ResRenderingContext *ctx)
  {
    d_ctx = ctx;
  }
  void SetModelRenderer(ResModelRenderer* renderer)
  {
    m_model_renderer = renderer;
  }
  virtual ResModelRenderer* GetModelRenderer() const
  {
    return m_model_renderer;
  }
  virtual void Render() = 0;
    //* Cell Render Begin
    // Signals that cell rendering is about to begin.
  virtual void RenderBegin() = 0;
    //* Cell Render End
    // Signals that cell rendering has ended.
  virtual void RenderEnd() = 0;
  void LoadCellsTransformation();
  /**
   * Loads the transformation needed to take from the global space to the
   * cells coordinate system.
   *
   * Usually involves loading a scale and a translation.
   */
  virtual AlgMatrix GetCellsTransformation() = 0;
private:
  ResModelRenderer* m_model_renderer;
};

//* 'ResCompletionRenderer' Class
// Represents an entity capable of rendering completions.
class RESRENDERAPI ResCompletionRenderer
{
protected:
  typedef struct {
    int well;
    int comp;
  } CompletionRecord;
  ResModelNew *d_mdl;
  ResRenderingContext *d_ctx;
  DsArray<CompletionRecord> d_completionindices;
public:
  ResCompletionRenderer()
  : d_mdl(NULL)
  , m_model_renderer(NULL)
  {
  }
  virtual ~ResCompletionRenderer()
  {
  }
  void SetModel(ResModelNew *mdl)
  {
    d_mdl = mdl;
  }
  void SetContext(ResRenderingContext *ctx)
  {
    d_ctx = ctx;
  }
  void SetModelRenderer(ResModelRenderer* renderer)
  {
    m_model_renderer = renderer;
  }
  ResModelRenderer* GetModelRenderer () const
  {
    return m_model_renderer;
  }
  void ClearCompletionRecords ()
  {
    d_completionindices.Resize(0);
  }
  int GetCompletionRecordsSize () const
  {
    return d_completionindices.Size();
  }
  unsigned int StoreCompletion (int well, int comp)
  {
    unsigned int pos = d_completionindices.Size();
    CompletionRecord r;
    r.well = well;
    r.comp = comp;
    d_completionindices.Append(r);
    return pos;
  }
  void GetCompletion (unsigned int id, const char **wellname, int *comp);
    //* Completion render
    // Renders the given completion of the given well.
  virtual void Render (int well, int comp) = 0;
    //* Completion Render Begin
    // Signals that completion rendering is about to begin.
  virtual void RenderBegin() = 0;
    //* Completion Render End
    // Signals that completion rendering has ended.
  virtual void RenderEnd() = 0;
private:
  ResModelRenderer* m_model_renderer;
};

//* 'ResWellRenderer'
// Represents an entity capable of rendering wells.
class RESRENDERAPI ResWellRenderer
{
  DsHash<int, float> m_rasterpos;
protected:
  ResModelNew *d_mdl;
  ResRenderingContext *d_ctx;
  ResCompletionRenderer *d_cr;
  bool m_use_scissor;
  DsArray<int> m_whead_crossed_cells_link_id; // crossed cells link id belonging to well head (if it exists)
  GLint m_vp[4];
  /*
   * Obtains, given root cell coordinates, a raster pos y coordinate for
   * rendering.
   * The returned value will be incremented by an offset in subsequent
   * calls with the same index. This is used to position well names
   * that lie in the same position, so that they don't overlap.
   */
  float GetNameRasterY (int i, int j, int k);
  /*
   * Obtains, given an index, a raster pos y coordinate for rendering.
   * The returned value will be incremented by an offset in subsequent
   * calls with the same index. This is used to position well names
   * that lie in the same position, so that they don't overlap.
   */
  float GetNameRasterY (int index)
  {
    float namey;
    // calc the name y on this completion
    if (m_rasterpos.Find(index))
      namey = m_rasterpos.Get(index) + 0.05f;
    else
      namey = 0.0f;
    m_rasterpos.Set(index,namey);
    return namey;
  }
  /**
   * Sets well renderer property value associated to that well.
   */
  void BuildWellProp (int well, WWell* renderer);
  /**
   * Builds and loads well renderer property values associated to each 
   * completion of that well.
   */
  void BuildCompProp (int well, WWell* renderer);
  /**
  * Gets property values associated to each well
  * from the already loaded properties (previously loaded by the color scale).
  */
  void SetWellProp (int well, WWell* renderer);
  /**
  * Gets well renderer property values associated to each 
  * completion of that well from the already loaded properties.
  * (previously loaded by the color scale)
  */
  void SetCompProp (int well, WWell* renderer);
  /**
   * Set property values for intersections between well and resevoir cells.
   */
  void SetIntersectionsPropValues (int well, WWell* renderer);
  void SetTrajIntersectionsPropValues (int well, WWell* renderer); // used for wells with real trajectory
  void CrossWellsHead (int well, WWell* renderer);
  void CrossCells (int well, WWell* renderer);
  void CrossCellsTraj (int well, WWell* renderer);
  virtual AlgVector GetWellTopCoordinates (int well) const;
  void SetupColorScaleForWellProp (const char* well_prop);
  void SetupColorScaleForCompProp (const char* comp_prop);
  void GetWellHeadData (int well, float* len, AlgVector* top);
public:
  ResWellRenderer (ResCompletionRenderer *renderer, SciColorScale *cs)
  : d_mdl(NULL)
  , d_ctx(NULL)
  , d_cr(renderer)
  , m_use_scissor(false)
  , m_whead_crossed_cells_link_id()
  , m_model_renderer(NULL)
  , m_cs(cs)
  {
  }
  virtual ~ResWellRenderer();
  void SetModel(ResModelNew *mdl)
  {
    d_mdl = mdl;
  }
  void SetContext(ResRenderingContext *ctx)
  {
    d_ctx = ctx;
  }
  void SetModelRenderer(ResModelRenderer* renderer)
  {
    m_model_renderer = renderer;
  }
  ResModelRenderer* GetModelRenderer () const
  {
    return m_model_renderer;
  }
  void SetScissorEnabled (bool f)
  {
    m_use_scissor = f;
  }
  bool GetWellColor(int well, float *owr, float *owg, float *owb);
  void GetCompletionColor (int well, int comp, unsigned char *ocr, unsigned char *ocg, unsigned char *ocb);
  // Renders the given well.
  virtual void Render(int well) = 0;
  // Signals that well rendering is about to begin.
  virtual void RenderBegin();
  // Signals that well rendering has ended.
  virtual void RenderEnd();
  virtual void RenderName(int well) {}
  virtual void RenderNameBegin();
  virtual void RenderNameEnd();
protected:
  SciColorScale* GetColorScale () const
  {
    return m_cs;
  }
  float GetCurrWellProp (int well);
  float GetCurrCompProp (int well, int comp);
private:
  ResModelRenderer* m_model_renderer;
  // For wells with no real trajectories
  DsHash<int, bool> m_cells_crossed_with_well;
  DsHash<int, bool> m_cells_crossed_with_well_head;
  // For wells with real trajectories
  DsHash<int, bool> m_cells_crossed_with_well_traj;
  // current properties for each well and each well completion
  DsArray<float> m_well_properties;
  DsArray<DsArray<float>*> m_completion_properties;
  SciColorScale *m_cs;
protected:
  SciColorScale::Mode m_cs_mode;
#define TEST_LINE_INTER_PERF 0
#if TEST_LINE_INTER_PERF
public:
  float m_inter_wells_time;
  float m_inter_wells_head_time;
#endif
};

//* 'ResModelRenderer' Class
// Renders a reservoir. It uses specialized renderers for each task.
class RESRENDERAPI ResModelRenderer
{
protected:
  ResModelNew *d_mdl;
  ResRenderingContext *d_ctx;
  ResCellRenderer *d_cellr;
  ResWellRenderer *d_wellr;
  ResCompletionRenderer *d_compr;
  SciColorScale *d_cs;
  DsHash<DsStringKey, UFontText*> d_welllabel;
public:
  struct PickHit 
  {
    PickHit ()
    : bubble_prop_index(-1)
    , well_cell_id(-1)
    {
    }
    int type;
    int id;
    ResModel* mdl;
    int bubble_prop_index;
    int well_cell_id;
    AlgVector coords;
  };

  ResModelRenderer (ResCellRenderer *cellr,
                    ResWellRenderer *wellr,
                    ResCompletionRenderer *compr,
                    SciColorScale *color_scale)
  : d_mdl(NULL)
  , d_ctx(NULL)
  , d_cellr(cellr)
  , d_wellr(wellr)
  , d_compr(compr)
  , d_cs(color_scale)
  , m_data_path(NULL)
  {
  }
  virtual ~ResModelRenderer()
  {
    DsStringKey wellname;
    for (bool hasNext = d_welllabel.First(&wellname);
         hasNext;
         hasNext = d_welllabel.Next(&wellname))
    {
      delete d_welllabel.Get(wellname);
    }
    free(m_data_path);
  }
  ResCellRenderer * GetCellRenderer()
  {
    return d_cellr;
  }
  ResWellRenderer * GetWellRenderer()
  {
    return d_wellr;
  }
  ResCompletionRenderer * GetCompletionRenderer()
  {
    return d_compr;
  }
  SciColorScale* GetColorScale() const
  {
    return d_cs;
  }
    //* Model set
    // Sets the current model for rendering
  void SetModel (ResModel *mdl);
    //* Context set
    // Sets the current rendering context
  void SetContext(ResRenderingContext *ctx)
  {
    d_ctx = ctx;
    if(d_cellr)
    d_cellr->SetContext(ctx);
    d_wellr->SetContext(ctx);
    d_compr->SetContext(ctx);
  }
  /**
   * Specifies the directory used to look for data needed during the rendering process
   * (e.g. shaders, etc.)
   */
  void SetDataPath (const char* path);
  /**
   * Obtains the data path.
   */
  const char* GetDataPath () const
  {
    return m_data_path;
  }
  /**
   * Get the render mode used by this renderer to draw well names
   */
  virtual UFontMessage::RenderMode GetWellNameRenderMode ()
  {
    return UFontMessage::PIXMAP_FONT;
  }
  /**
   * Stores font information for well 'well'.
   */
  void SetupWellNameRenderer (int well,
                              const char *name_font,
                              int name_font_size,
                              bool name_font_bold,
                              bool name_font_italic);
  /**
   * Renders the well name with 'r', 'g', 'b' color, on raster pos 'x', 'y' and 'z' with
   * displacements 'sdx', 'sdy' and 'sdz' on the clipping space.
   * Assumes 'SetupWellNameRenderer' was previously called for this well.
   */
  virtual void DrawWellName (int well,
                             float r,
                             float g,
                             float b,
                             float x,
                             float y,
                             float z,
                             float sdx,
                             float sdy,
                             float sdz);
    //* Reservoir Render Begin
    // Signals that reservoir rendering is about to begin.
  virtual void RenderBegin();
    //* Reservoir Render
    // Renders the current model, using the given property.
  virtual void Render () = 0;
    //* Reservoir Render End
    // Signals that reservoir rendering has ended.
  virtual void RenderEnd() = 0;
  virtual PickHit* DoPick (float x, float y) = 0;
  bool Pick (float x,
             float y,
             int* type = NULL,
             int* id = NULL,
             ResModel** pickedMdl = NULL,
             int* p_bubble_prop_index = NULL,
             int* well_cell_id = NULL);

  /**
   * Returns property ids for the triphase values associated 
   * to the current property.
   */
  void GetLic3Properties(ResRenderingContext * ctx, int * propG, int * propO, int * propW);

  /**
   * Loads the transformation needed to take from the global space to the
   * cells coordinate system.
   *
   * Usually involves loading a scale and a translation.
   */
  virtual void LoadCellsTransformation() = 0;
  virtual AlgMatrix GetCellsTransformation() = 0;
  /**
   * Returns the number of registered vector field properties.
   */
  static int GetVectorFieldPropertyCount ();
  /**
   * Returns the X component of the vector field property with index 'which_prop'.
   * (0 <= which_prop && which_prop < GetVectorFieldPropertyCount)
   */
  static const char* GetVectorFieldPropX (int which_prop);
  /**
   * Returns the Y component of the vector field property with index 'which_prop'.
   * (0 <= which_prop && which_prop < GetVectorFieldPropertyCount)
   */
  static const char* GetVectorFieldPropY (int which_prop);
  /**
   * Returns the Z component of the vector field property with index 'which_prop'.
   * (0 <= which_prop && which_prop < GetVectorFieldPropertyCount)
   */
  static const char* GetVectorFieldPropZ (int which_prop);
  /**
   * Returns the description of the vector field property with index 'which_prop'.
   * (0 <= which_prop && which_prop < GetVectorFieldPropertyCount)
   */
  static const char* GetVectorFieldPropDesc (int which_prop);
  /**
   * Returns a short name for the vector field property with index 'which_prop'.
   * (0 <= which_prop && which_prop < GetVectorFieldPropertyCount)
   */
  static const char* GetVectorFieldPropShortName (int which_prop);
protected:
  /**
   * Return a properly configured ufonttext instance.
   */
  virtual UFontText* CreateText ();

  ResModelNew* GetModel() const
  {
    return d_mdl;
  }
  /**
   * GetRenderedProperty
   *
   * Obtains the rendered property.
   *
   * Returns true if successful, false otherwise.
   */
  bool GetRenderedProperty (ResProperty **prop);
  /**
   * Informs that the current property changed or must be recomputed.
   * Returns true if 'fill_inactive' is true and this property has values for inactive cells,
   * false otherwise.
   */
  bool PropertyChanged (ResRenderData *renderdata, ResProperty *prop, bool fill_inactive);
  void ModelChanged (ResRenderData *renderdata);
  /**
   * Sets the vibility flag of out-of-range cells.
   * Returns if any cell changed activity status.
   */
  bool BuildOutOfRangeCellActivity (ResRenderData* renderData,
                                    int num_cells,
                                    const bool* active_cells,
                                    int& data_ts);
  void CreateTopsView (ResRenderData* renderData);
private:
  char* m_data_path;
};

//* 'ResRenderingContext' Class
// Defines a set of rendering attributes suitable for any type of reservoir rendering.
class RESRENDERAPI ResRenderingContext
{
public:
  enum
  {
    COLOR_SCALE            = 1<<0,
    SECTOR                 = 1<<1,
    OUTRANGECELLSCOLORS    = 1<<2,
    TOPFACES               = 1<<3,
    STEP                   = 1<<4,
    PROPERTY               = 1<<5,
    SMOOTHNESS             = 1<<6,
    SECTION                = 1<<7,
    RENDERMODE             = 1<<8,
    ACTIVECELLS            = 1<<9,
    SCALE                  = 1<<10, // geometric scale
    CELLSELECTION          = 1<<11,
    REFINEMENTS            = 1<<12,
    LAYERSEPARATION        = 1<<13,
    WELLRENDERMODE         = 1<<14,
    WELLPROP               = 1<<15,
    COMPPROP               = 1<<16,
    COMPRADIUS             = 1<<17,
    COMPVISIBILITYMODE     = 1<<18,
    WELLRADIUS             = 1<<19,
    WELLHEADCYLINDERHEIGHT = 1<<20,
    BUBBLE                 = 1<<21,
    FLOW                   = 1<<22,
    WELLMODE               = 1<<23,
    VECTOR_FIELD           = 1<<24,
    COMPPOSITION           = 1<<25,
    LAST                   = 1<<25,
    LAST_SHIFT             = 25,
    ANY = 0xFFFFFFFF,
    ALL = (
      COLOR_SCALE            |
      SECTOR                 |
      OUTRANGECELLSCOLORS    |
      TOPFACES               |
      STEP                   |
      PROPERTY               |
      SMOOTHNESS             |
      SECTION                |
      RENDERMODE             |
      ACTIVECELLS            |
      SCALE                  |
      CELLSELECTION          |
      REFINEMENTS            |
      LAYERSEPARATION        |
      WELLRENDERMODE         |
      WELLPROP               |
      COMPPROP               |
      COMPRADIUS             |
      COMPVISIBILITYMODE     |
      WELLRADIUS             |
      WELLHEADCYLINDERHEIGHT |
      BUBBLE                 |
      FLOW                   |
      WELLMODE               |
      VECTOR_FIELD           |
      COMPPOSITION
    ),
  };
  // property visibility setting
  enum PropMode {
    PERCELL,
    PERNODE,
  };
  enum WellRenderMode
  {
    RENDER_COLORS,        // colors configured by SetWellAttr
    RENDER_WELL_PROP,     // each well with its property value
    RENDER_COMP_PROP,     // each completion with its property value
    RENDER_CROSSED_CELLS, // colors of crossed cells
  };
  enum FieldColorMode
  {
    NO_MAP,        // No Coloring
    MAGNITUDE_MAP, // Colors Magnitude
    Z_MAP,         // Colors Z Scale
    PALETTE_MAP,   // Colors both Magnitude and Z
    TRIPHASE_MAP,  // Shows Oil/Gas/Water simultaneously
  };

  ResRenderingContext(ResModel *mdl);
  virtual ~ResRenderingContext();
  void InitCompChanged ();
  void SetProperty (const char *name, int step_index);
  const char* GetPropertyName () const
  {
    return m_propname;
  }
  int GetStepIndex () const
  {
    return m_step_index;
  }
  void SetWellHighlightColor(unsigned char r, unsigned char g, unsigned char b);
  int GetWellHighlightColor () const
  {
    return m_hlwellcolor;
  }
  void ClearHighlightedWells()
  {
    m_hlwells.Clear();
  }
  void AddHighlightedWell (int well);
  /**
   * Is the well 'well' highlighted?
   * Always returns false if any completion is highlighted and completions
   * can be highlighted (see HasCompletionHighlight).
   */
  bool IsWellHighlighted (int well);
  bool HasHighlightedWells()
  {
    return m_hlwells.GetNumberOfKeys() != 0;
  }
  void SetDrawOnlyHighlightedWells(bool flag)
  {
    m_drawonlyhighlightedwells = flag;
  }
  bool MustDrawOnlyHighlightedWells()
  {
    return m_drawonlyhighlightedwells && HasHighlightedWells();
  }
  /**
   * Specifies that completions can be highlighted.
   * In this case, if any completions are highlighted, the well is not highlighted.
   */
  void SetCompletionHighlight(bool flag)
  {
    m_has_completion_highlight = flag;
  }
  /**
   * Can completions be highlighted ?
   * In this case, if any completions are highlighted, the well is not highlighted.
   */
  bool HasCompletionHighlight() const
  {
    return m_has_completion_highlight;
  }
  /**
   * Clears the highlighted completions list.
   */
  void ClearHighlightedCompletions();
  /**
   * Adds a highlighted completion. Assumed to be the completion of
   * a highlighted well.
   */
  void AddHighlightedCompletion (int well, int comp);
  /**
   * Is the completion 'comp' of well 'well' highlighted?
   */
  bool IsCompletionHighlighted (int well, int comp);
  /**
   * Is any completion highlighted?
   */
  bool HasHighlightedCompletions() const
  {
    return m_has_highlighted_completions;
  }
  void AddWell(const char *name);
  void RemoveWell(const char *name);
  void RenameWell(const char *oldname, const char *newname);
  /**
   * Removes the context data of all wells.
   */
  void RemoveAllWells();
  void SetWellAttr(const char *name, int vis, int r, int g, int b, int nr, int ng, int nb);
  void GetWellAttr(int well, int *vis, int *r, int *g, int *b, int *nr, int *ng, int *nb);
  void SetWellCompAttr(const char *name, int r, int g, int b);
  void GetWellCompAttr(int well, int *r, int *g, int *b);
  void SetWellNameAttr(const char *font, int size, bool bold, bool italic);
  void GetWellNameAttr(const char **font, int *size, bool *bold, bool *italic);
  void SetReservoirVisible (bool f)
  {
    m_resvis = f;
  }
  bool ReservoirVisible () const
  {
    return m_resvis;
  }
  void SetWellsVisible (bool f)
  {
    m_wellvis = f;
  }
  void SetWellsTrajectoryVisible (bool f)
  {
    if (m_well_trajectory_vis == f)
      return;
    m_well_trajectory_vis = f;
    SetAllWellsChanged(ResRenderingContext::WELLMODE, true, true);
  }
  virtual bool WellsTrajectoryVisible () const
  {
    return m_well_trajectory_vis;
  }
  /**
   * For internal use
   */
  void SetHasWellTrajectory (bool f)
  {
    m_model_has_trajectory = f;
  }
  bool HasWellTrajectory () const
  {
    return m_model_has_trajectory;
  }
  bool WellsVisible () const
  {
    return m_wellvis;
  }
  void SetWellNamesVisible (bool f)
  {
    m_wellnvis = f;
  }
  bool WellNamesVisible () const
  {
    return m_wellnvis;
  }
  void SetScale (float x, float y, float z);
  float ScaleX () const
  {
    return m_sx;
  }
  float ScaleY () const
  {
    return m_sy;
  }
  float ScaleZ () const
  {
    return m_sz;
  }
  void SetDrawOutOfRangeCells (bool f);
  bool DrawOutOfRangeCells () const
  {
    return m_outrangecells;
  }
  void SetOutOfRangeCellsColor (unsigned char r, unsigned char g, unsigned char b, unsigned char a);
  void GetOutOfRangeCellsColor (unsigned char *r, unsigned char *g, unsigned char *b, unsigned char *a) const
  {
    *r = m_outrangecellsr;
    *g = m_outrangecellsg;
    *b = m_outrangecellsb;
    *a = m_outrangecellsa;
  }
  void SetPropMode (PropMode mode)
  {
    m_property_mode = mode;
  }
  PropMode GetPropMode () const
  {
    return m_property_mode;
  }
  bool OnSelection () const
  {
    return m_pick;
  }
  void SetOnSelection (bool f)
  {
    m_pick = f;
  }
  void SetWireframeThickness (float w)
  {
    m_wthickness = w;
  }
  float WireframeThickness () const
  {
    return m_wthickness;
  }
  void SetWireframeColor (float r, float g, float b)
  {
    m_wr = r;
    m_wg = g;
    m_wb = b;
  }
  void WireframeColor (float *r, float *g, float *b)
  {
    *r = m_wr;
    *g = m_wg;
    *b = m_wb;
  }
  /**
   * Enables/disables wireframe intensity attenuation according to observer
   * distance.
   */
  void SetWireframeIntensityAttenuation (bool flag)
  {
    m_intensity_att = flag;
  }
  bool GetWireframeIntensityAttenuation () const
  {
    return m_intensity_att;
  }
  void SetWellHeight (float h)
  {
    m_wellheight = h;
  }
  float WellHeight () const
  {
    return m_wellheight;
  }
  void SetWellHeadCylinderHeightFactor (float f);
  /**
  *  For internal use
  */
  float GetWellHeadCylinderHeightFactor () const
  {
    return m_well_head_height_factor;
  }
  void SetContour (bool f)
  {
    m_contour = f;
  }
  bool Contour () const
  {
    return m_contour;
  }
  void SetUseVBO (bool flag)
  {
    m_use_vbo = flag;
  }
  bool UseVBO () const
  {
    return m_use_vbo;
  }
  /**
   * Specifies the use of a single color (through SetCellsSingleColor)
   * for the entire reservoir (disables property drawing).
   */
  void SetUseSingleColor (bool flag)
  {
    m_use_single_color = flag;
  }
  /**
   * Is using a single color for the entire reservoir?
   */
  bool UseSingleColor () const
  {
    return m_use_single_color;
  }
  /**
   * Set color to be used when drawing cells.
   * NOTE: has effect only when UseSingleColor().
   * @see SetUseSingleColor
   * @see UseSingleColor
   */
  void SetCellsSingleColor (const AlgVector& color)
  {
    m_single_color = color;
  }
  /**
   * Get color to be used when drawing cells.
   * @see SetUseSingleColor
   * @see UseSingleColor
   */
  const AlgVector& GetCellsSingleColor () const
  {
    return m_single_color;
  }
  /**
   * For internal use
   */
  ResProperty* GetProperty () const;
  /**
   * For internal use
   */
  int GetWellAttrPacked(int well);
  /**
   * For internal use
   */
  int GetWellCompAttrPacked(int well);
  /**
   * For internal use
   */
  int GetWellNameAttrPacked(int well);
  /**
   * For internal use
   */
  void DebugChanged (const char *label);
  /**
   * For internal use
   */
  void AtRenderEnd ();
  /**
   * For internal use
   */
  void SetChanged (unsigned int which);
  /**
   * For internal use
   */
  bool IsChanged (unsigned int which, int data_ts) const;
  /**
   * For internal use
   */
  void DataUpdated (int& ts);
  /**
  * For internal use
  */
  void SetWellChanged (int well, unsigned int which, bool changed);
  /**
  * For internal use
  */
  void SetAllWellsChanged (unsigned int which, bool changed);
  /**
   * For internal use
   * 'both' refers changing both common wells and trajectory wells
   */
  void SetWellChanged (int well, unsigned int which, bool changed, bool both);
  /**
   * For internal use
   * 'both' refers changing both common wells and trajectory wells
   */
  void SetAllWellsChanged (unsigned int which, bool changed, bool both);
  bool IsWellChanged (int well, unsigned int which);
  /**
   * For internal use
   */
  virtual void SetWillRender(bool flag)
  {
  }
  /**
   * For internal use
   */
  bool IsPerCellColor () const
  {
    return m_per_cell_prop != NULL;
  }
  /**
   * For internal use.
   * @return true when cells must be colored using color scale.
   * @see IsPerCellColor
   * @see UseSingleColor
   */
  bool ColorCellsWithCS () const
  {
    return !IsPerCellColor() && !UseSingleColor();
  }
  /**
   * For internal use
   */
  ResProperty* GetPerCellProp () const
  {
    return m_per_cell_prop;
  }
  /**
   * For internal use
   */
  void SetPerCellProp (ResProperty* prop)
  {
    m_per_cell_prop = prop;
  }
  /**
   * For internal use
   */
  void SetUsedProperty (ResProperty* prop);
  /**
   * For internal use
   */
  void SaveMatrices ();
  /**
   * For internal use
   */
  const double* GetModelView () const
  {
    return m_mm;
  }
  /**
   * For internal use
   */
  int GetVPX () const
  {
    return m_vp[0];
  }
  /**
   * For internal use
   */
  int GetVPY () const
  {
    return m_vp[1];
  }
  /**
   * For internal use
   */
  int GetVPW () const
  {
    return m_vp[2];
  }
  /**
   * For internal use
   */
  int GetVPH () const
  {
    return m_vp[3];
  }
  /**
   * For internal use
   */
  virtual float GetReservoirTranslation () const
  {
    return 0.0f;
  }
  ResModelNew* GetModel () const
  {
    return m_mdl;
  }
  /**
   * Specifies well render mode (see above definition of 'WellRenderMode').
   */
  void SetWellRenderMode (WellRenderMode mode);
  WellRenderMode GetWellRenderMode () const
  {
    return m_well_render_mode;
  }
  /**
   * Specifies well property for WellRenderMode=RENDER_WELL_PROP.
   * Assumes SetWellRenderMode(RENDER_WELL_PROP) has been called.
   */
  void SetWellProperty (const char* name);
  const char* GetWellProperty () const
  {
    return m_well_property_name;
  }
  /**
   * Specifies completion property for WellRenderMode=RENDER_COMP_PROP.
   * Assumes SetWellRenderMode(RENDER_COMP_PROP) has been called.
   */
  void SetCompProperty (const char* name);
  const char* GetCompProperty () const
  {
    return m_comp_property_name;
  }
  // LIC Methods
  // Sets Field XYZ Properties from Name
  void SetVectorField (const char* propx, const char* propy, const char* propz);
  // Enable/Disable field animation
  void SetVectorFieldAnimated (bool f);
  // Adjusts LIC quality (i in [0,1])
  void SetVectorFieldQuality (float i);
  // Adjusts animation speed (i in [0,1])
  void SetVectorFieldAnimSpeed (float i);
  // Changes Coloring Mode
  void SetVectorFieldColorMode (FieldColorMode mode);
  // Fix Noise Image to Model (to avoid flickering)
  void SetVectorFieldFixed(bool f)
  {
    SetChanged(VECTOR_FIELD);
    m_vf_fixed = f;
  }
  // Enable Field Visualization
  void EnableVectorField(bool e)
  {
    m_vf_enabled = e;
  }
  // Returns true if field visualization is enabled
  bool IsVectorFieldEnabled()
  {
    return m_vf_enabled;
  }
  // Returns the start value in the magnitude scale
  float GetVectorFieldMinMagnitude ()
  {
    return m_vf_scaleMin;
  }
  // Returns the end value in the magnitude scale
  float GetVectorFieldMaxMagnitude ()
  {
    return m_vf_scaleMax;
  }
  // Returns the property name representing the X component
  const char* GetVectorFieldPropertyX () const
  {
    return m_vf_prop_x;
  }
  // Returns the property name representing the Y component
  const char* GetVectorFieldPropertyY () const
  {
    return m_vf_prop_y;
  }
  // Returns the property name representing the Z component
  const char* GetVectorFieldPropertyZ () const
  {
    return m_vf_prop_z;
  }
  // Returns Image Quality (value in [0,1])
  float GetVectorFieldQuality () const
  {
    return m_vf_L;
  }
  // Returns animation speed (value in [0,1])
  float GetVectorFieldAnimSpeed () const
  {
    return m_vf_B;
  }
  // Return Current Coloring Mode
  FieldColorMode GetVectorFieldColorMode () const
  {
	return m_vf_colorMode;
  }
  // Indicates if the noise image is fixed to the model
  bool IsVectorFieldFixed () const
  {
    return m_vf_fixed;
  }
  // Indicates if the field is being animated
  bool IsVectorFieldAnimated () const
  {
    return m_vf_animated;
  }
  // Adjusts the scale limits
  void SetVectorFieldValueLimits(float min, float max)
  {
    if (min > max) return;
    m_vf_scaleMin = min;
    m_vf_scaleMax = max;
  }

  void SetCompletionChanged (int well, int comp);
  void ResetWellCompletionsChanged (int well);
  bool WasCompletionChanged (int well, int comp) const
  {
    return m_comp_changed.Get(well)->Get(comp);
  }

private:
  bool HasModelTrajData ();
private:
  typedef struct
  {
    int wattr; // well attributes
               // attributes coded in an integer:
               //   0x0VRRGGBB
               //    where R,G,B are color values in the range [0,255]
               //          V is one if well is visible, zero otherwise
    int nattr; // well name attributes
               // attributes coded in an integer:
               //   0x00RRGGBB
               //    where R,G,B are color values in the range [0,255]
    int cattr; // well completion color
               // attibutes coded in an integer:
               //   0x00RRGGBB
               //   where R,G,B are color values in the range [0,255]
  } WellAttribute;
  ResModelNew* m_mdl;
  char* m_propname; // holds the current property name
  int m_step_index;
  // the matrices of the current frame, along with the viewport
  double m_mm[16];
  double m_pm[16];
  GLint m_vp[4];
  float m_sx, m_sy, m_sz;      // global scale
  bool m_resvis;               // reservoir visibility toggle
  bool m_wellvis;              // wells visibility toggle
  bool m_well_trajectory_vis;  // well curved trajectory toggle
  bool m_model_has_trajectory; // indicates if model has any well with trajectory data
  bool m_wellnvis;             // well names visibility toggle
  int m_hlwellcolor;           // the color to use when highlighting a well
                               // this information is coded in an integer:
                               //   0x00RRGGBB
                               //    where R,G,B are color values in the range [0,255]
  float m_wthickness;          // wireframe thickness
  float m_wr, m_wg, m_wb;      // wireframe color
  bool m_pick;                    // true if picking is enabled, false otherwise
  bool m_outrangecells;           // out of range cells display
  unsigned char m_outrangecellsr;
  unsigned char m_outrangecellsg;
  unsigned char m_outrangecellsb;
  unsigned char m_outrangecellsa;  // the color of these cells
  PropMode m_property_mode;        // property mode (PERCELL or PERNODE)
  float m_wellheight;              // well height
  float m_well_head_height_factor; // default is 1 (f < 1 shrinks and f > 1 enlarges cylinder)
  bool m_contour;                  // contour toggle
  ResProperty* m_per_cell_prop;    // holds the current property if it's a cell color provider, null otherwise
  bool m_use_single_color;         // reservoir must be drawn using a single color
  AlgVector m_single_color;        // reservoir single color (RGB, 0..1)
  char *m_font_family_name;
  int m_font_size;
  bool m_font_bold;
  bool m_font_italic;
  int m_changed_ts[LAST_SHIFT+1];
  DsHash<int, unsigned int> m_well_changed;
  DsHash<int, unsigned int> m_well_traj_changed;
  int m_defattr;
  int m_attrsize;
  DsHash<DsStringKey,bool> m_hlwells;
  DsHash<int,bool> m_hlcomps;
  DsHash<DsStringKey,WellAttribute*> m_wattrs;
  bool m_drawonlyhighlightedwells;
  bool m_has_completion_highlight;
  bool m_has_highlighted_completions;
  bool m_intensity_att;
  bool m_use_vbo;
  WellRenderMode m_well_render_mode; // changes well rendering mode
  char* m_well_property_name;  
  char* m_comp_property_name;

  char* m_vf_prop_x;
  char* m_vf_prop_y;
  char* m_vf_prop_z;
  bool m_vf_enabled;
  bool m_vf_animated;
  bool m_vf_fixed;
  FieldColorMode m_vf_colorMode;
  float m_vf_L;
  float m_vf_B;
  float m_vf_scaleMin;
  float m_vf_scaleMax;

  DsArray<DsArray<int>*> m_comp_changed; // ids of completions that were modified
  int m_num_max_comp;                    // maximum number of completions for all wells
  int m_debug_changed_ts;                // debug changed time stamp
  int m_current_ts;                      // current render time stamp
};

RESRENDERAPI void gposrender_init ();
RESRENDERAPI void gposrender_setocclusionenabled (bool f);
RESRENDERAPI bool gposrender_isocclusionenabled ();
RESRENDERAPI bool gposrender_isocclusionsupported ();
RESRENDERAPI void gposrender_setfrustumenabled (bool f);
RESRENDERAPI bool gposrender_isfrustumenabled ();
RESRENDERAPI void gposrender_setcullingpaused (bool f);
RESRENDERAPI bool gposrender_iscullingpaused ();
RESRENDERAPI void gposrender_setbackfacecullingenabled (bool f);
RESRENDERAPI bool gposrender_isbackfacecullingenabled ();
RESRENDERAPI void gposrender_toggleconedraw (int c);
RESRENDERAPI void gposrender_setbackfacecullingdebugquadset (int q);
RESRENDERAPI void gposrender_setdebuggingboundingboxes (bool f);
RESRENDERAPI bool gposrender_isdebuggingboundingboxes ();
RESRENDERAPI void gposrender_setupdateallbeforerendering (bool f);
RESRENDERAPI bool gposrender_getupdateallbeforerendering ();
RESRENDERAPI void gposrender_setocclusionblocksize (int ni, int nj, int nk);
RESRENDERAPI void gposrender_setreleaseonmodeswitch (bool f);
RESRENDERAPI bool gposrender_willreleaseonmodeswitch ();

#endif

