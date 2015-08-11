#pragma once

#include <alg/matrix.h>
#include <alg/vector.h>
#include <gpos/io/open.h>
#include <ds/array.h>

#ifndef RESVIEW_DLL
# ifndef TEC_DLL
#  define RESVIEW_API
# else
#  define RESVIEW_API __declspec(dllimport)
# endif
#else
# define RESVIEW_API __declspec(dllexport)
#endif

class ResModelNew;
class ResPosLoader;
class ResModelRenderer;
class ResRenderingContext;
class Res3DRenderingContext;
class Res3DModelRenderer;
class ResMapSecRenderingContext;
class ResMapSecModelRenderer;
class SciColorScale;
class SciActiveElementColorScale;
class SciActiveElementCompass;
class SciActiveElementAxis;
class SciTip;
class UFontText;

namespace resview {

enum PropMode
{
  PERCELL,
  PERNODE,
};

enum RenderMode3D
{
  RENDER_ISOCONTOUR,
  RENDER_VOLUMETRIC
};

enum WellRenderMode
{
  RENDER_COLORS = 0,    // colors configured by SetWellAttr
  RENDER_WELL_PROP,     // each well with its property value
  RENDER_COMP_PROP,     // each completion with its property value
  RENDER_CROSSED_CELLS, // colors of crossed cells
};

enum MapSecWireframeMode
{
  NORMAL = 0,
  ACTIVECELLS,
  UNDER,
  OFF,
  WIREFRAME_MODE_COUNT
};

enum MapSecCompVisMode
{
  ALL,
  SECTION,
  NONE
};

enum PrimType
{
  QUADS,
  UNKNOWN,
};

class RESVIEW_API IResView
{
public:
  virtual ~IResView()
  {
  }
  virtual void ClearLoadOptions () = 0;
  virtual void SetLoadOption (const char* optionname, void* optionvalue) = 0;
  /**
   * Specifies that the reservoir coordinates must be centered at the origin.
   * This method should be called before LoadModel().
   */
  virtual void SetCenterModel (bool f) = 0;
  /**
   * Loads model stored in file name 'filename' (geresim format).
   * Returns true if successful, false otherwise.
   */
  virtual bool LoadModel (const char* filename) = 0;
  /**
   * Specifies the use of a model that was loaded externally.
   */
  virtual void SetModel (ResModelNew* mdl) = 0;
  /**
   * Obtains the model bounding box.
   */
  virtual void GetModelBoundingBox (float &xmin, float &xmax, float &ymin, float &ymax, float &zmin, float &zmax, bool only_act = true) = 0;
  /**
   * Obtains model root grid dimensions.
   */
  virtual void GetRootDimensions (int* ni, int *nj, int* nk) = 0;
  /**
   * Obtains a good initial value for the reservoir z scale.
   */
  virtual float GetInitialZScale () = 0;
  /**
   * Obtains the number of map time steps.
   */
  virtual int GetNumberOfMapSteps () = 0;
  virtual void SetColorScaleNumberOfIntervals (int n) = 0;
  virtual void SetColorScaleIntervalColor (int index, unsigned char r, unsigned char g, unsigned char b, unsigned char a=255) = 0;
  virtual void SetColorScaleFont (const char* name, int size, bool bold, bool italic) = 0;
  virtual void SetColorScaleRange (float vmin, float vmax) = 0;
  virtual void GetColorScaleRange (float *vmin, float *vmax) = 0;
  virtual void SetColorScaleBackground (float r, float g, float b, float a) = 0;
  virtual int GetNumberOfProperties () = 0;
  virtual const char* GetPropertyName (int index) = 0;
  virtual float GetPropertyMinValue (int index) = 0;
  virtual float GetPropertyMaxValue (int index) = 0;
  virtual int GetWellPropertyCount () = 0;
  virtual const char* GetWellPropertyName (int index) = 0;
  virtual int GetCompPropertyCount () = 0;
  virtual const char* GetCompPropertyName (int index) = 0;
  /**
   * Specifies the current viewed property.
   * If prop_index == -1, assumes no property will be used.
   * step_index == -1 is only allowed for initial properties (where step doesn't matter).
   */
  virtual void SetProperty (int prop_index, int step_index) = 0;
  /**
   * Obtains currently viewed property, returns -1 in case no property was set.
   */
  virtual int GetProperty () = 0;
  /**
   * Obtains currently viewed property step index, returns -1 in case no property was set or an initial property is being viewed.
   */
  virtual int GetPropertyStep () = 0;
  virtual void SetWellHighlightColor(unsigned char r, unsigned char g, unsigned char b) = 0;
  virtual void ClearHighlightedWells() = 0;
  virtual void AddHighlightedWell(int well) = 0;
  virtual void SetDrawOnlyHighlightedWells(bool flag) = 0;
  virtual void SetWellAttr(const char* name, bool visible, int r, int g, int b, int nr, int ng, int nb) = 0;
  virtual void SetWellCompAttr(const char* name, int r, int g, int b) = 0;
  virtual void SetWellNameAttr(const char* font, int size, bool bold, bool italic) = 0;
  virtual void SetReservoirVisible (bool f) = 0;
  virtual void SetWellsVisible (bool f) = 0;
  virtual void SetWellNamesVisible (bool f) = 0;
  virtual void SetScale (float x, float y, float z) = 0;
  virtual float ScaleX () = 0;
  virtual float ScaleY () = 0;
  virtual float ScaleZ () = 0;
  virtual void SetDrawOutOfRangeCells (bool f) = 0;
  virtual void SetOutOfRangeCellsColor (unsigned char r, unsigned char g, unsigned char b, unsigned char a) = 0;
  virtual void SetPropMode (PropMode mode) = 0;
  virtual PropMode GetPropMode () = 0;
  virtual void SetWireframeThickness (float w) = 0;
  virtual void SetWireframeColor (float r, float g, float b) = 0;
  /**
   * Enables/disables wireframe intensity attenuation according to observer
   * distance.
   */
  virtual void SetWireframeIntensityAttenuation (bool flag) = 0;
  virtual bool GetWireframeIntensityAttenuation () const = 0;
  virtual void SetModelSmooth (bool f) = 0;
  virtual void SetDraw2DElements (bool f) = 0;
  virtual void SetContour (bool f) = 0;
  virtual void SetUseVBO (bool f) = 0;
  virtual void SetRenderCompassEnabled (bool enabled) = 0;
  virtual void SetRenderAxesEnabled (bool enabled) = 0;
  /**
   * Specifies if the drawing of the I axis (when SetRenderAxesEnabled(true)) must be inverted.
   * This is useful when the reservoir original coordinates have been inverted.
   */
  virtual void SetIAxisInverted (bool f) = 0;
  /**
   * Specifies if the drawing of the J axis (when SetRenderAxesEnabled(true)) must be inverted.
   * This is useful when the reservoir original coordinates have been inverted.
   */
  virtual void SetJAxisInverted (bool f) = 0;
  /**
   * Specifies if the drawing of the K axis (when SetRenderAxesEnabled(true)) must be inverted.
   * This is useful when the reservoir original coordinates have been inverted.
   */
  virtual void SetKAxisInverted (bool f) = 0;
  virtual void SetRenderColorScaleEnabled (bool enabled) = 0;
  /**
   * Specifies a color for the reservoir. If SetFlatColorsEnabled(true) is called,
   * this color is used instead of a colored property.
   */
  virtual void SetFlatColor (float r, float g, float b) = 0;
  /**
   * Enables/disables the use of a single color for the reservoir.
   */
  virtual void SetFlatColorEnabled (bool flag) = 0;
  /**
   * Return transform matrix leading to the coordinate system
   * in which the reservoir is drawn.
   */
  virtual AlgMatrix GetReservoirTransformation () = 0;
  /**
   * Specifies if the FPS rate must be shown on the top of the screen (default=false).
   */
  virtual void SetDebugFPS (bool f) = 0;
  /**
   * Is showing FPS rate?
   */
  virtual bool DebugFPS () = 0;
  virtual void SetOcclusionEnabled (bool f) = 0;
  virtual bool IsOcclusionEnabled () = 0;
  virtual void SetOcclusionBlockSize (int ni, int nj, int nk) = 0;
  virtual void SetBackfaceCullingEnabled (bool f) = 0;
  virtual bool IsBackfaceCullingEnabled () = 0;
  virtual void ToggleBackfaceCullingConeDraw (int c) = 0;
  virtual void SetBackfaceCullingDebugQuadset (int q) = 0;
  virtual void SetFrustumEnabled (bool f) = 0;
  virtual bool IsFrustumEnabled () = 0;
  virtual void SetCullingPaused (bool f) = 0;
  virtual bool IsCullingPaused () = 0;
  virtual void SetDebuggingBoundingBoxes (bool f) = 0;
  virtual bool IsDebuggingBoundingBoxes () = 0;
  virtual void SetUpdateAllBeforeRendering (bool f) = 0;
  virtual bool GetUpdateAllBeforeRendering () = 0;
  virtual void SetBlockSize (int ni, int nj, int nk) = 0;
  virtual void SetWellRenderMode (WellRenderMode mode) = 0;
  virtual WellRenderMode GetWellRenderMode () = 0;
  /**
   * Specifies well property for WellRenderMode=RENDER_WELL_PROP.
   */
  virtual void SetWellProperty (const char* name) = 0;
  /**
   * Specifies completion property for WellRenderMode=RENDER_COMP_PROP.
   */
  virtual void SetCompProperty (const char* name) = 0;
  /**
   * Specifies if associated data must be freed whenever
   * visualization mode switches between normal visualization,
   * visualization with separation and visualization with sections.
   */
  virtual void SetFreeMemoryOnModeSwitchEnabled (bool f) = 0;
  /**
   * Obtains the flag that signals if associated data must be freed
   * whenever visualization mode switches between normal visualization,
   * visualization with separation and visualization with sections.
   */
  virtual bool IsFreeMemoryOnModeSwitchEnabled () = 0;
  virtual void SetTipEnabled (bool enabled) = 0;
  virtual bool IsTipEnabled () = 0;
  virtual void ResetTip () = 0;
  virtual void SetTitle (const char* txt) = 0;
  virtual void SetTitleColor (float red, float green, float blue) = 0;
  virtual void SetTitlePosition (const float pos[3]) = 0;
  virtual void SetTitlePosition (float x, float y, float z) = 0;
  virtual const AlgVector& GetTitlePosition () const = 0;
  virtual bool SetTitleFont (const char* ff, int size, bool bold = false, bool italic = false, bool utf8 = false) = 0;
  virtual void SetTitleEnabled (bool flag) = 0;
  virtual void SetNativeRedraw (bool f) = 0;
  /**
   * Renders the reservoir using the given options.
   */
  virtual void Render () = 0;
  virtual void EndRender () = 0;
  virtual void Pick (float x, float y) = 0;
};

class RESVIEW_API IResView3D : public IResView
{
public:
  virtual ~IResView3D ()
  {
  }
  /**
   * Specifies the point around which the scale is performed.
   * The default is the active cells bounding box center.
   */
  virtual void SetScaleCenter (float x, float y, float z) = 0;
  /**
   * Obtains the x coordinate of the point around which the scale
   * is performed. The default is (ActXMax()+ActXMin())/2.
   */
  virtual float ScaleCenterX () = 0;
  /**
   * Obtains the x coordinate of the point around which the scale
   * is performed. The default is (ActYMax()+ActYMin())/2.
   */
  virtual float ScaleCenterY () = 0;
  /**
   * Obtains the x coordinate of the point around which the scale
   * is performed. The default is (ActZMax()+ActZMin())/2.
   */
  virtual float ScaleCenterZ () = 0;
  /**
   * Specifies layer 'l' separation as 'd'.
   */
  virtual void SetLayerDistance(int l, float d) = 0;
  /**
   * Specifies layer 'l' as visible if 'vis' is true and as invisible otherwise.
   */
  virtual void SetLayerVis(int l, bool vis) = 0;
  /**
   * Sets current render mode, defined by enum RenderMode.
   */
  virtual void SetRenderMode (RenderMode3D mode) = 0;
  /**
   * Obtains current render mode, defined by enum RenderMode.
   */
  virtual RenderMode3D GetRenderMode () = 0;
  /**
   * Specifies if only the top faces of the cells must be drawn.
   */
  virtual void SetTopFaces (bool flag) = 0;
  /**
   * Specifies a global layer separation of value 'dk'.
   */
  virtual void SetGlobalLayerSeparation (float dk) = 0;
  /**
   * Obtains the global layer separation 'dk'.
   */
  virtual float GetGlobalLayerSeparation () = 0;
  /**
   * Specifies the 'i' section filter.
   */
  virtual void SetSecI (int i) = 0;
  /**
   * Specifies the 'j' section filter.
   */
  virtual void SetSecJ (int j) = 0;
  /**
   * Specifies the 'k' section filter.
   */
  virtual void SetSecK (int k) = 0;
  /**
   * Specifies if completions must be rendered.
   */
  virtual void SetCompletionsVisible(bool f) = 0;
  /**
   * Specifies completion and well attributes
   */
  virtual void SetCompletionRadiusFactor (float r) = 0;
  virtual float GetCompletionRadiusFactor () = 0;
  virtual void SetWellRadiusFactor (float r) = 0;
  virtual float GetWellRadiusFactor () = 0;
  virtual void SetWellHeadCylinderHeightFactor (float f) = 0;
  virtual float GetWellHeadCylinderHeightFactor () = 0;
  /**
   * Specifies if the grid wireframe must be rendered.
   */
  virtual void SetGridLinesEnabled (bool f) = 0;
  virtual bool GetGridLinesEnabled () = 0;
  /**
   * Specifies if field lines must be rendered.
   */
  virtual void SetFieldLines (bool f) = 0;
  /**
   * Specifies a global alpha multiplier 'a',
   * where 'smax' is considered the maximum possible scale.
   */
  virtual void SetScaleAlpha (float a, float smax) = 0;
  /**
   * Specify whether hierarchy with only active elements should be used.
   */
  virtual void SetUseOnlyActElemHierarchy (bool flag) = 0;
  /**
   * Fetch whether hierarchy with only active elements is used.
   */
  virtual bool UseOnlyActElemHierarchy () const = 0;
  /**
   * Enable/disable faces extraction for geomset with active elements.
   */
  virtual void SetActiveGeomSetEnabled (bool flag) = 0;
  /**
   * Enable/disable faces extraction for geomset with inactive elements.
   */
  virtual void SetInactiveGeomSetEnabled (bool flag) = 0;
  /**
   * Enable/disable wireframe mode for geomset with active elements.
   */
  virtual void SetActiveGeomSetWireframeEnabled (bool flag) = 0;
  /**
   * Enable/disable wireframe mode for geomset with inactive elements.
   */
  virtual void SetInactiveGeomSetWireframeEnabled (bool flag) = 0;

  /**
   * Enable/disable drawing of grid lines for geomset with active elements.
   */
  virtual void SetActiveGeomSetGridlinesEnabled (bool flag) = 0;
  /**
   * Enable/disable drawing of grid lines for geomset with inactive elements.
   */
  virtual void SetInactiveGeomSetGridlinesEnabled (bool flag) = 0;
  /**
   * Specifies which refined grid must be rendered (from 0 to numgrids-1).
   */
  virtual void SetRefinedGrid (int index) = 0;
  /**
   * Enables or disables the clipping plane of index 'index'.
   */
  virtual void SetClippingPlaneEnabled (int index, bool enabled) = 0;
  /**
   * Specifies the equation of the clipping plane of index 'index'.
   */
  virtual void SetClippingPlane (int index, float a, float b, float c, float d) = 0;
  /**
   * Obtains total number of primitives in the last render call (without any culling).
   */
  virtual int GetTotalNumberOfPrimitives () = 0;
  /**
   * Obtains the number of primitives used in the last render call.
   */
  virtual int GetNumberOfPrimitivesUsed () = 0;
  virtual void SetModel (ResModelNew* mdl) = 0;
};

class RESVIEW_API IResViewMap : public IResView
{
public:
  virtual ~IResViewMap ()
  {
  }
  virtual void SetCompletionScale (float s) = 0;
  virtual void SetWireframeMode (MapSecWireframeMode m) = 0;
  virtual MapSecWireframeMode GetWireframeMode () = 0;
  /**
   * Specifies the current 'i' section.
   */
  virtual void SetSecI (int i) = 0;
  /**
   * Specifies the current 'j' section.
   */
  virtual void SetSecJ (int j) = 0;
  /**
   * Specifies the current 'k' section.
   */
  virtual void SetSecK (int k) = 0;
  /**
   * Specifies if faults must be rendered with a different thickness.
   * Default: true
   */
  virtual void SetGapVisible (bool f) = 0;
  /**
   * Specifies fault rendering color.
   * Default: black
   */
  virtual void SetGapColor (float r, float g, float b) = 0;
  /**
   * Specifies fault rendering line thickness.
   * Default: 2 pixels
   */
  virtual void SetGapThickness (int w) = 0;
};

class RESVIEW_API ResView
{
public:
  ResView (const char* datapath, bool ever_use_2d_elements=true);
  virtual ~ResView ();
  void SetCenterModel (bool f)
  {
    m_center_model = f;
  }
  void ClearLoadOptions ();
  void SetLoadOption (const char* optionname, void* optionvalue);
  virtual bool LoadModel (const char* filename);
  /**
   * Loads model using a C# loader.
   * Returns true if successful, false otherwise.
   */
  //virtual bool LoadModel (ResPosLoader* loader);
  void GetRootDimensions (int* ni, int *nj, int* nk);
  /**
   * Obtains the original model bounding box (before model was centered).
   */
  void GetOriginalModelBoundingBox (float &xmin, float &xmax, float &ymin, float &ymax, float &zmin, float &zmax);
  float GetInitialZScale ();
  int GetNumberOfMapSteps ();
  void SetColorScaleNumberOfIntervals (int n);
  void SetColorScaleIntervalColor (int index, unsigned char r, unsigned char g, unsigned char b, unsigned char a=255);
  void SetColorScaleFont (const char* name, int size, bool bold, bool italic);
  void SetColorScaleRange (float vmin, float vmax);
  void GetColorScaleRange (float *vmin, float *vmax);
  void SetColorScaleBackground (float r, float g, float b, float a);

  int GetNumberOfProperties ();
  const char* GetPropertyName (int index);
  float GetPropertyMinValue (int index);
  float GetPropertyMaxValue (int index);
  int GetWellPropertyCount ();
  const char* GetWellPropertyName (int index);
  int GetCompPropertyCount ();
  const char* GetCompPropertyName (int index);
  void SetProperty (int prop_index, int step_index);
  int GetProperty ();
  int GetPropertyStep ();
  void SetWellHighlightColor(unsigned char r, unsigned char g, unsigned char b);
  void ClearHighlightedWells();
  void AddHighlightedWell(int well);
  void SetDrawOnlyHighlightedWells(bool flag);
  void SetWellAttr(const char* name, bool visible, int r, int g, int b, int nr, int ng, int nb);
  void SetWellCompAttr(const char* name, int r, int g, int b);
  void SetWellNameAttr(const char* font, int size, bool bold, bool italic);
  void SetReservoirVisible (bool f);
  void SetWellsVisible (bool f);
  void SetWellNamesVisible (bool f);
  void SetScale (float x, float y, float z);
  float ScaleX ();
  float ScaleY ();
  float ScaleZ ();
  void SetDrawOutOfRangeCells (bool f);
  void SetOutOfRangeCellsColor (unsigned char r, unsigned char g, unsigned char b, unsigned char a);
  void SetPropMode (PropMode mode);
  PropMode GetPropMode ();
  void SetWireframeThickness (float w);
  void SetWireframeColor (float r, float g, float b);
  void SetWireframeIntensityAttenuation (bool flag);
  bool GetWireframeIntensityAttenuation () const;
  void SetModelSmooth (bool f);
  void SetDraw2DElements (bool f);
  virtual void SetContour (bool f);
  void SetUseVBO (bool f);
  void SetDebugFPS (bool f);
  bool DebugFPS ()
  {
    return m_show_fps;
  }
  void SetOcclusionEnabled (bool f);
  bool IsOcclusionEnabled ();
  void SetOcclusionBlockSize (int ni, int nj, int nk);
  void SetBackfaceCullingEnabled (bool f);
  bool IsBackfaceCullingEnabled ();
  void ToggleBackfaceCullingConeDraw (int c);
  void SetBackfaceCullingDebugQuadset (int q);
  void SetFrustumEnabled (bool f);
  bool IsFrustumEnabled ();
  void SetCullingPaused (bool f);
  bool IsCullingPaused ();
  void SetDebuggingBoundingBoxes (bool f);
  bool IsDebuggingBoundingBoxes ();
  void SetUpdateAllBeforeRendering (bool f);
  bool GetUpdateAllBeforeRendering ();
  void SetBlockSize (int ni, int nj, int nk);
  void SetFreeMemoryOnModeSwitchEnabled (bool f);
  bool IsFreeMemoryOnModeSwitchEnabled ();
  void SetRenderCompassEnabled (bool enabled);
  void SetRenderAxesEnabled (bool enabled);
  void SetIAxisInverted (bool f);
  void SetJAxisInverted (bool f);
  void SetKAxisInverted (bool f);
  void SetRenderColorScaleEnabled (bool enabled);
  void SetTipEnabled (bool enabled);
  bool IsTipEnabled ();
  void ResetTip ();
  void SetTitle (const char* txt);
  void SetTitleColor (float red, float green, float blue);
  void SetTitlePosition (const float pos[3]);
  void SetTitlePosition (float x, float y, float z);
  const AlgVector& GetTitlePosition () const;
  bool SetTitleFont (const char* ff, 
                     int size, 
                     bool bold = false, 
                     bool italic = false, 
                     bool utf8 = false);
  void SetTitleEnabled (bool flag);
  bool IsTitleEnabled () const;
  void SetNativeRedraw (bool f);
  void SetWellRenderMode (WellRenderMode mode);
  WellRenderMode GetWellRenderMode ();
  void SetWellProperty (const char* name);
  void SetCompProperty (const char* name);
  void SetFlatColor (float r, float g, float b);
  void SetFlatColorEnabled (bool flag);
  AlgMatrix GetReservoirTransformation ();
  virtual void Render ();
  virtual void EndRender ();
  void Pick (float x, float y);
  void SetModel (ResModelNew* mdl);
  double GetFPS () const
  {
    return m_fps;
  }
protected:
  ResModelNew* GetModel()
  {
    return m_model;
  }
  SciColorScale* GetCellsColorScale()
  {
    return m_cells_cs;
  }
  SciActiveElementColorScale* GetColorScaleActElem()
  {
    return m_acolorscale;
  }
  virtual ResModelRenderer* GetModelRenderer() = 0;
  virtual ResRenderingContext* GetRenderingContext() const = 0;
  const char* GetDataPath ()
  {
    return m_datapath;
  }
  ResOpenOptions* GetLoadOptions ()
  {
    return &m_options;
  }
  SciColorScale* GetWellsColorScale ()
  {
    return m_wells_cs;
  }
private:
  void LoadModelCommon ();
  void Initialize ();
  void SetColorScaleChanged ();
private:
  ResModelNew *m_model;
  ResOpenOptions m_options;
  SciActiveElementCompass* m_compass;
  SciActiveElementAxis* m_axes;
  SciTip* m_query_tip;
  SciColorScale* m_cells_cs;
  SciColorScale* m_wells_cs;
  SciActiveElementColorScale* m_acolorscale;
  bool m_title_enabled;
  UFontText* m_title;
  char* m_title_text;
  AlgVector m_title_pos;
  AlgVector m_title_color;
  char* m_datapath;
  // fps data
  int m_averagenumframes;
  int m_nframes;
  double m_fps;
  double m_t0;
  // flags
  bool m_show_fps;
  bool m_show_2d_elements;
  bool m_initialized;
  bool m_center_model;
  bool m_loaded_mdl;
  bool m_render_compass;
  bool m_render_axes;
  bool m_render_color_scale;
};

class RESVIEW_API ResView3D : public IResView3D, private ResView
{
public:
  ResView3D(const char* datapath, bool ever_use_2d_elements=true);
  ~ResView3D();
  void SetCenterModel (bool f)
  {
    ResView::SetCenterModel(f);
  }
  void SetModel (ResModelNew* mdl)
  {
    ResView::SetModel(mdl);
    LoadModelCommon();
  }
  void ClearLoadOptions ()
  {
    ResView::ClearLoadOptions();
  }
  void SetLoadOption (const char* optionname, void* optionvalue)
  {
    ResView::SetLoadOption(optionname, optionvalue);
  }
  void SetRenderCompassEnabled (bool enabled)
  {
    ResView::SetRenderCompassEnabled(enabled);
  }
  void SetRenderAxesEnabled (bool enabled)
  {
    ResView::SetRenderAxesEnabled(enabled);
  }
  void SetIAxisInverted (bool f)
  {
    ResView::SetIAxisInverted(f);
  }
  void SetJAxisInverted (bool f)
  {
    ResView::SetJAxisInverted(f);
  }
  void SetKAxisInverted (bool f)
  {
    ResView::SetKAxisInverted(f);
  }
  void SetRenderColorScaleEnabled (bool enabled)
  {
    ResView::SetRenderColorScaleEnabled(enabled);
  }
  void SetFlatColor (float r, float g, float b)
  { 
    ResView::SetFlatColor(r, g, b);
  } 
  void SetFlatColorEnabled (bool flag)
  {
    ResView::SetFlatColorEnabled(flag);
  }
  AlgMatrix GetReservoirTransformation ()
  {
    return ResView::GetReservoirTransformation();
  }
  virtual bool LoadModel (const char* filename);
  //virtual bool LoadModel (ResPosLoader* loader);
  void SetLayerDistance(int l, float d);
  void SetLayerVis(int l, bool vis);
  void SetRenderMode (RenderMode3D mode);
  RenderMode3D GetRenderMode ();
  void SetTopFaces (bool flag);
  void SetGlobalLayerSeparation (float dk);
  float GetGlobalLayerSeparation ();
  void SetScaleCenter (float x, float y, float z);
  float ScaleCenterX ();
  float ScaleCenterY ();
  float ScaleCenterZ ();
  void SetSecI (int i);
  void SetSecJ (int j);
  void SetSecK (int k);
  void SetCompletionsVisible(bool f);
  void SetCompletionRadiusFactor (float r);
  float GetCompletionRadiusFactor ();
  void SetWellRadiusFactor (float r);
  float GetWellRadiusFactor ();
  void SetWellHeadCylinderHeightFactor (float f);
  float GetWellHeadCylinderHeightFactor ();
  void SetGridLinesEnabled (bool f);
  bool GetGridLinesEnabled ();
  void SetFieldLines (bool f);
  void SetScaleAlpha (float a, float smax);
  void SetUseOnlyActElemHierarchy (bool flag);
  bool UseOnlyActElemHierarchy () const;
  void SetActiveGeomSetEnabled (bool flag);
  void SetInactiveGeomSetEnabled (bool flag);
  void SetActiveGeomSetWireframeEnabled (bool flag);
  void SetInactiveGeomSetWireframeEnabled (bool flag);
  void SetActiveGeomSetGridlinesEnabled (bool flag);
  void SetInactiveGeomSetGridlinesEnabled (bool flag);
  /**
   * Specifies which refined grid must be rendered (from 0 to numgrids-1).
   */
  void SetRefinedGrid (int index);
  void SetClippingPlaneEnabled (int index, bool enabled);
  void SetClippingPlane (int index, float a, float b, float c, float d);
  void GetModelBoundingBox (float &xmin, float &xmax, float &ymin, float &ymax, float &zmin, float &zmax, bool only_act = true);
  void GetRootDimensions (int* ni, int *nj, int* nk)
  {
    ResView::GetRootDimensions(ni, nj, nk);
  }
  float GetInitialZScale ()
  {
    return ResView::GetInitialZScale ();
  }
  int GetNumberOfMapSteps ()
  {
    return ResView::GetNumberOfMapSteps();
  }
  void SetColorScaleNumberOfIntervals (int n)
  {
    ResView::SetColorScaleNumberOfIntervals(n);
  }
  void SetColorScaleIntervalColor (int index, unsigned char r, unsigned char g, unsigned char b, unsigned char a=255)
  {
    ResView::SetColorScaleIntervalColor(index, r, g, b, a);
  }
  void SetColorScaleFont (const char* name, int size, bool bold, bool italic)
  {
    ResView::SetColorScaleFont(name, size, bold, italic);
  }
  void SetColorScaleRange (float vmin, float vmax)
  {
    ResView::SetColorScaleRange(vmin, vmax);
  }
  void GetColorScaleRange (float *vmin, float *vmax)
  {
    ResView::GetColorScaleRange(vmin, vmax);
  }
  void SetColorScaleBackground (float r, float g, float b, float a)
  {
    ResView::SetColorScaleBackground(r, g, b, a);
  }
  int GetNumberOfProperties ()
  {
    return ResView::GetNumberOfProperties();
  }
  const char* GetPropertyName (int index)
  {
    return ResView::GetPropertyName(index);
  }
  float GetPropertyMinValue (int index)
  {
    return ResView::GetPropertyMinValue(index);
  }
  float GetPropertyMaxValue (int index)
  {
    return ResView::GetPropertyMaxValue(index);
  }
  int GetWellPropertyCount ()
  {
    return ResView::GetWellPropertyCount();
  }
  const char* GetWellPropertyName (int index)
  {
    return ResView::GetWellPropertyName(index);
  }
  int GetCompPropertyCount ()
  {
    return ResView::GetCompPropertyCount();
  }
  const char* GetCompPropertyName (int index)
  {
    return ResView::GetCompPropertyName(index);
  }
  WellRenderMode GetWellRenderMode ()
  {
    return ResView::GetWellRenderMode();
  }
  void SetProperty (int prop_index, int step_index)
  {
    ResView::SetProperty(prop_index, step_index);
  }
  int GetProperty ()
  {
    return ResView::GetProperty();
  }
  int GetPropertyStep ()
  {
    return ResView::GetPropertyStep();
  }
  void SetWellHighlightColor (unsigned char r, unsigned char g, unsigned char b)
  {
    ResView::SetWellHighlightColor(r, g, b);
  }
  void ClearHighlightedWells ()
  {
    ResView::ClearHighlightedWells();
  }
  void AddHighlightedWell (int well)
  {
    ResView::AddHighlightedWell(well);
  }
  void SetDrawOnlyHighlightedWells (bool flag)
  {
    ResView::SetDrawOnlyHighlightedWells(flag);
  }
  void SetWellAttr (const char* name, bool visible, int r, int g, int b, int nr, int ng, int nb)
  {
    ResView::SetWellAttr(name, visible, r, g, b, nr, ng, nb);
  }
  void SetWellCompAttr (const char* name, int r, int g, int b)
  {
    ResView::SetWellCompAttr(name, r, g, b);
  }
  void SetWellNameAttr (const char* font, int size, bool bold, bool italic)
  {
    ResView::SetWellNameAttr(font, size, bold, italic);
  }
  void SetReservoirVisible (bool f)
  {
    ResView::SetReservoirVisible(f);
  }
  void SetWellsVisible (bool f)
  {
    ResView::SetWellsVisible(f);
  }
  void SetWellNamesVisible (bool f)
  {
    ResView::SetWellNamesVisible(f);
  }
  void SetScale (float x, float y, float z)
  {
    ResView::SetScale(x, y, z);
  }
  float ScaleX ()
  {
    return ResView::ScaleX();
  }
  float ScaleY ()
  {
    return ResView::ScaleY();
  }
  float ScaleZ ()
  {
    return ResView::ScaleZ();
  }
  void SetDrawOutOfRangeCells (bool f)
  {
    ResView::SetDrawOutOfRangeCells(f);
  }
  void SetOutOfRangeCellsColor (unsigned char r, unsigned char g, unsigned char b, unsigned char a)
  {
    ResView::SetOutOfRangeCellsColor(r, g, b, a);
  }
  void SetPropMode (PropMode mode)
  {
    ResView::SetPropMode(mode);
  }
  PropMode GetPropMode ()
  {
    return ResView::GetPropMode();
  }
  void SetWireframeThickness (float w)
  {
    ResView::SetWireframeThickness(w);
  }
  void SetWireframeColor (float r, float g, float b)
  {
    ResView::SetWireframeColor(r, g, b);
  }
  void SetWireframeIntensityAttenuation (bool flag)
  {
    ResView::SetWireframeIntensityAttenuation(flag);
  }
  bool GetWireframeIntensityAttenuation () const
  {
    return ResView::GetWireframeIntensityAttenuation();
  }
  void SetModelSmooth (bool f)
  {
    ResView::SetModelSmooth(f);
  }
  void SetDraw2DElements (bool f)
  {
    ResView::SetDraw2DElements(f);
  }
  void SetUseVBO (bool f)
  {
    ResView::SetUseVBO(f);
  }
  void SetDebugFPS (bool f)
  {
    ResView::SetDebugFPS(f);
  }
  bool DebugFPS ()
  {
    return ResView::DebugFPS();
  }
  void SetOcclusionEnabled (bool f)
  {
    ResView::SetOcclusionEnabled(f);
  }
  bool IsOcclusionEnabled ()
  {
    return ResView::IsOcclusionEnabled();
  }
  void SetOcclusionBlockSize (int ni, int nj, int nk)
  {
    return ResView::SetOcclusionBlockSize(ni, nj, nk);
  }
  void SetBackfaceCullingEnabled (bool f)
  {
    ResView::SetBackfaceCullingEnabled(f);
  }
  bool IsBackfaceCullingEnabled ()
  {
    return ResView::IsBackfaceCullingEnabled();
  }
  void ToggleBackfaceCullingConeDraw (int c)
  {
    ResView::ToggleBackfaceCullingConeDraw(c);
  }
  void SetBackfaceCullingDebugQuadset (int q)
  {
    ResView::SetBackfaceCullingDebugQuadset(q);
  }
  void SetFrustumEnabled (bool f)
  {
    ResView::SetFrustumEnabled(f);
  }
  bool IsFrustumEnabled ()
  {
    return ResView::IsFrustumEnabled();
  }
  void SetCullingPaused (bool f)
  {
    ResView::SetCullingPaused(f);
  }
  bool IsCullingPaused ()
  {
    return ResView::IsCullingPaused();
  }
  void SetDebuggingBoundingBoxes (bool f)
  {
    ResView::SetDebuggingBoundingBoxes(f);
  }
  bool IsDebuggingBoundingBoxes ()
  {
    return ResView::IsDebuggingBoundingBoxes();
  }
  void SetUpdateAllBeforeRendering (bool f)
  {
    ResView::SetUpdateAllBeforeRendering(f);
  }
  bool GetUpdateAllBeforeRendering ()
  {
    return ResView::GetUpdateAllBeforeRendering();
  }
  void SetBlockSize (int ni, int nj, int nk)
  {
    ResView::SetBlockSize(ni, nj, nk);
  }
  void SetFreeMemoryOnModeSwitchEnabled (bool f)
  {
    ResView::SetFreeMemoryOnModeSwitchEnabled(f);
  }
  bool IsFreeMemoryOnModeSwitchEnabled ()
  {
    return ResView::IsFreeMemoryOnModeSwitchEnabled();
  }
  void SetTipEnabled (bool enabled)
  {
    ResView::SetTipEnabled(enabled);
  }
  bool IsTipEnabled ()
  {
    return ResView::IsTipEnabled();
  }
  void ResetTip ()
  {
    ResView::ResetTip();
  }
  void SetTitle (const char* txt)
  {
    ResView::SetTitle(txt);
  }
  void SetTitleColor (float red, float green, float blue)
  {
    ResView::SetTitleColor(red, green, blue);
  }
  void SetTitlePosition (const float pos[3])
  {
    ResView::SetTitlePosition(pos);
  }
  void SetTitlePosition (float x, float y, float z)
  {
    ResView::SetTitlePosition(x, y, z);
  }
  const AlgVector& GetTitlePosition () const
  {
    return ResView::GetTitlePosition();
  }
  bool SetTitleFont (const char* ff, 
                     int size, 
                     bool bold = false, 
                     bool italic = false, 
                     bool utf8 = false)
  {
    return ResView::SetTitleFont(ff, size, bold, italic, utf8);
  }
  void SetTitleEnabled (bool flag)
  {
    ResView::SetTitleEnabled(flag);
  }
  bool IsTitleEnabled (bool flag)
  {
    return ResView::IsTitleEnabled();
  }
  void SetNativeRedraw (bool f)
  {
    ResView::SetNativeRedraw(f);
  }
  void SetWellRenderMode (WellRenderMode mode)
  {
    ResView::SetWellRenderMode(mode);
  }
  void SetWellProperty (const char* name)
  {
    ResView::SetWellProperty(name);
  }
  void SetCompProperty (const char* name)
  {
    ResView::SetCompProperty(name);
  }
  void Pick (float x, float y)
  {
    ResView::Pick(x, y);
  }
  // virtual methods
  void SetContour (bool f);
  void Render ();
  void EndRender ();
  /**
   * Obtains the current reservoir's geometry primitive type.
   */
  PrimType GetPrimitiveType ();
  /**
   * Obtains the current reservoir's geometry vertex array.
   * The array should be deleted by the caller.
   * This method should not be called at every frame.
   */
  DsArray<float>* GetVertexArray ();
  /**
   * Obtains the indices of the reservoir's geometry primitives.
   * If NULL is returned, it is assumed that they are sequential indices
   * (vertex0 vertex1 vertex2 ...)
   * This method should not be called at every frame.
   */
  DsArray<unsigned int>* GetIndices ();
  int GetTotalNumberOfPrimitives ();
  int GetNumberOfPrimitivesUsed ();
protected:
  // virtual methods
  ResModelRenderer* GetModelRenderer();
  ResRenderingContext* GetRenderingContext() const;
private:
  void LoadModelCommon ();
private:
  Res3DRenderingContext* m_context;
  Res3DModelRenderer* m_model_renderer;
};

class RESVIEW_API ResViewMapSec : public IResViewMap, public ResView
{
public:
  ResViewMapSec(const char* datapath);
  ~ResViewMapSec();
  void SetCenterModel (bool f)
  {
    ResView::SetCenterModel(f);
  }
  void SetModel (ResModelNew* mdl)
  {
    ResView::SetModel(mdl);
    LoadModelCommon();
  }
  virtual bool LoadModel (const char* filename);
  //virtual bool LoadModel (ResPosLoader* loader);
  void SetDrawRefined (bool f);
  void SetSecI (int i);
  void SetSecJ (int j);
  void SetSecK (int k);
  void SetMapCameraInverted (bool f);
  void SetCompletionVisibilityMode (MapSecCompVisMode m);
  void SetCompletionScale (float s);
  void SetWellHeadCylinderHeightFactor (float f);
  float GetWellHeadCylinderHeightFactor ();
  void SetWellWidthFactor (float f);
  float GetWellWidthFactor ();
  void SetWireframeMode (MapSecWireframeMode m);
  MapSecWireframeMode GetWireframeMode ();
  void SetGapVisible (bool f);
  void SetGapColor (float r, float g, float b);
  void SetGapThickness (int w);
  void SetFillInactive (bool f);
  void ClearLoadOptions ()
  {
    ResView::ClearLoadOptions();
  }
  void SetLoadOption (const char* optionname, void* optionvalue)
  {
    ResView::SetLoadOption(optionname, optionvalue);
  }
  void SetRenderCompassEnabled (bool enabled)
  {
    ResView::SetRenderCompassEnabled(enabled);
  }
  void SetRenderAxesEnabled (bool enabled)
  {
    ResView::SetRenderAxesEnabled(enabled);
  }
  void SetIAxisInverted (bool f)
  {
    ResView::SetIAxisInverted(f);
  }
  void SetJAxisInverted (bool f)
  {
    ResView::SetJAxisInverted(f);
  }
  void SetKAxisInverted (bool f)
  {
    ResView::SetKAxisInverted(f);
  }
  void SetRenderColorScaleEnabled (bool enabled)
  {
    ResView::SetRenderColorScaleEnabled(enabled);
  }
  void SetFlatColor (float r, float g, float b)
  { 
    ResView::SetFlatColor(r, g, b);
  } 
  void SetFlatColorEnabled (bool flag)
  {
    ResView::SetFlatColorEnabled(flag);
  }
  AlgMatrix GetReservoirTransformation ()
  {
    return ResView::GetReservoirTransformation();
  }
  void SetColorScaleBackground (float r, float g, float b, float a)
  {
    ResView::SetColorScaleBackground(r, g, b, a);
  }
  void GetRootDimensions (int* ni, int *nj, int* nk)
  {
    ResView::GetRootDimensions(ni, nj, nk);
  }
  float GetInitialZScale ()
  {
    return ResView::GetInitialZScale ();
  }
  int GetNumberOfMapSteps ()
  {
    return ResView::GetNumberOfMapSteps();
  }
  void SetColorScaleNumberOfIntervals (int n)
  {
    ResView::SetColorScaleNumberOfIntervals(n);
  }
  void SetColorScaleIntervalColor (int index, unsigned char r, unsigned char g, unsigned char b, unsigned char a=255)
  {
    ResView::SetColorScaleIntervalColor(index, r, g, b, a);
  }
  void SetColorScaleFont (const char* name, int size, bool bold, bool italic)
  {
    ResView::SetColorScaleFont(name, size, bold, italic);
  }
  void SetColorScaleRange (float vmin, float vmax)
  {
    ResView::SetColorScaleRange(vmin, vmax);
  }
  void GetColorScaleRange (float *vmin, float *vmax)
  {
    ResView::GetColorScaleRange(vmin, vmax);
  }
  int GetNumberOfProperties ()
  {
    return ResView::GetNumberOfProperties();
  }
  const char* GetPropertyName (int index)
  {
    return ResView::GetPropertyName(index);
  }
  float GetPropertyMinValue (int index)
  {
    return ResView::GetPropertyMinValue(index);
  }
  float GetPropertyMaxValue (int index)
  {
    return ResView::GetPropertyMaxValue(index);
  }
  int GetWellPropertyCount ()
  {
    return ResView::GetWellPropertyCount();
  }
  const char* GetWellPropertyName (int index)
  {
    return ResView::GetWellPropertyName(index);
  }
  int GetCompPropertyCount ()
  {
    return ResView::GetCompPropertyCount();
  }
  const char* GetCompPropertyName (int index)
  {
    return ResView::GetCompPropertyName(index);
  }
  WellRenderMode GetWellRenderMode ()
  {
    return ResView::GetWellRenderMode();
  }
  void SetProperty (int prop_index, int step_index)
  {
    ResView::SetProperty(prop_index, step_index);
  }
  int GetProperty ()
  {
    return ResView::GetProperty();
  }
  int GetPropertyStep ()
  {
    return ResView::GetPropertyStep();
  }
  void SetWellHighlightColor (unsigned char r, unsigned char g, unsigned char b)
  {
    ResView::SetWellHighlightColor(r, g, b);
  }
  void ClearHighlightedWells ()
  {
    ResView::ClearHighlightedWells();
  }
  void AddHighlightedWell (int well)
  {
    ResView::AddHighlightedWell(well);
  }
  void SetDrawOnlyHighlightedWells (bool flag)
  {
    ResView::SetDrawOnlyHighlightedWells(flag);
  }
  void SetWellAttr (const char* name, bool visible, int r, int g, int b, int nr, int ng, int nb)
  {
    ResView::SetWellAttr(name, visible, r, g, b, nr, ng, nb);
  }
  void SetWellCompAttr (const char* name, int r, int g, int b)
  {
    ResView::SetWellCompAttr(name, r, g, b);
  }
  void SetWellNameAttr (const char* font, int size, bool bold, bool italic)
  {
    ResView::SetWellNameAttr(font, size, bold, italic);
  }
  void SetReservoirVisible (bool f)
  {
    ResView::SetReservoirVisible(f);
  }
  void SetWellsVisible (bool f)
  {
    ResView::SetWellsVisible(f);
  }
  void SetWellNamesVisible (bool f)
  {
    ResView::SetWellNamesVisible(f);
  }
  void SetScale (float x, float y, float z)
  {
    ResView::SetScale(x, y, z);
  }
  float ScaleX ()
  {
    return ResView::ScaleX();
  }
  float ScaleY ()
  {
    return ResView::ScaleY();
  }
  float ScaleZ ()
  {
    return ResView::ScaleZ();
  }
  void SetDrawOutOfRangeCells (bool f)
  {
    ResView::SetDrawOutOfRangeCells(f);
  }
  void SetOutOfRangeCellsColor (unsigned char r, unsigned char g, unsigned char b, unsigned char a)
  {
    ResView::SetOutOfRangeCellsColor(r, g, b, a);
  }
  void SetPropMode (PropMode mode)
  {
    ResView::SetPropMode(mode);
  }
  PropMode GetPropMode ()
  {
    return ResView::GetPropMode();
  }
  void SetWireframeThickness (float w)
  {
    ResView::SetWireframeThickness(w);
  }
  void SetWireframeColor (float r, float g, float b)
  {
    ResView::SetWireframeColor(r, g, b);
  }
  void SetWireframeIntensityAttenuation (bool flag)
  {
    ResView::SetWireframeIntensityAttenuation(flag);
  }
  bool GetWireframeIntensityAttenuation () const
  {
    return ResView::GetWireframeIntensityAttenuation();
  }
  void SetModelSmooth (bool f)
  {
    ResView::SetModelSmooth(f);
  }
  void SetDraw2DElements (bool f)
  {
    ResView::SetDraw2DElements(f);
  }
  void SetUseVBO (bool f)
  {
    ResView::SetUseVBO(f);
  }
  void SetDebugFPS (bool f)
  {
    ResView::SetDebugFPS(f);
  }
  bool DebugFPS ()
  {
    return ResView::DebugFPS();
  }
  void SetOcclusionEnabled (bool f)
  {
    ResView::SetOcclusionEnabled(f);
  }
  bool IsOcclusionEnabled ()
  {
    return ResView::IsOcclusionEnabled();
  }
  void SetOcclusionBlockSize (int ni, int nj, int nk)
  {
    return ResView::SetOcclusionBlockSize(ni, nj, nk);
  }
  void SetBackfaceCullingEnabled (bool f)
  {
    ResView::SetBackfaceCullingEnabled(f);
  }
  bool IsBackfaceCullingEnabled ()
  {
    return ResView::IsBackfaceCullingEnabled();
  }
  void ToggleBackfaceCullingConeDraw (int c)
  {
    ResView::ToggleBackfaceCullingConeDraw(c);
  }
  void SetBackfaceCullingDebugQuadset (int q)
  {
    ResView::SetBackfaceCullingDebugQuadset(q);
  }
  void SetFrustumEnabled (bool f)
  {
    ResView::SetFrustumEnabled(f);
  }
  bool IsFrustumEnabled ()
  {
    return ResView::IsFrustumEnabled();
  }
  void SetCullingPaused (bool f)
  {
    ResView::SetCullingPaused(f);
  }
  bool IsCullingPaused ()
  {
    return ResView::IsCullingPaused();
  }
  void SetDebuggingBoundingBoxes (bool f)
  {
    ResView::SetDebuggingBoundingBoxes(f);
  }
  bool IsDebuggingBoundingBoxes ()
  {
    return ResView::IsDebuggingBoundingBoxes();
  }
  void SetUpdateAllBeforeRendering (bool f)
  {
    ResView::SetUpdateAllBeforeRendering(f);
  }
  bool GetUpdateAllBeforeRendering ()
  {
    return ResView::GetUpdateAllBeforeRendering();
  }
  void SetBlockSize (int ni, int nj, int nk)
  {
    ResView::SetBlockSize(ni, nj, nk);
  }
  void SetFreeMemoryOnModeSwitchEnabled (bool f)
  {
    ResView::SetFreeMemoryOnModeSwitchEnabled(f);
  }
  bool IsFreeMemoryOnModeSwitchEnabled ()
  {
    return ResView::IsFreeMemoryOnModeSwitchEnabled();
  }
  void SetTipEnabled (bool enabled)
  {
    ResView::SetTipEnabled(enabled);
  }
  bool IsTipEnabled ()
  {
    return ResView::IsTipEnabled();
  }
  void ResetTip ()
  {
    ResView::ResetTip();
  }
  void SetTitle (const char* txt)
  {
    ResView::SetTitle(txt);
  }
  void SetTitleColor (float red, float green, float blue)
  {
    ResView::SetTitleColor(red, green, blue);
  }
  void SetTitlePosition (const float pos[3])
  {
    ResView::SetTitlePosition(pos);
  }
  void SetTitlePosition (float x, float y, float z)
  {
    ResView::SetTitlePosition(x, y, z);
  }
  const AlgVector& GetTitlePosition () const
  {
    return ResView::GetTitlePosition();
  }
  bool SetTitleFont (const char* ff, 
                     int size, 
                     bool bold = false, 
                     bool italic = false, 
                     bool utf8 = false)
  {
    return ResView::SetTitleFont(ff, size, bold, italic, utf8);
  }
  void SetTitleEnabled (bool flag)
  {
    ResView::SetTitleEnabled(flag);
  }
  bool IsTitleEnabled (bool flag)
  {
    return ResView::IsTitleEnabled();
  }
  void SetNativeRedraw (bool f)
  {
    ResView::SetNativeRedraw(f);
  }
  void SetWellRenderMode (WellRenderMode mode)
  {
    ResView::SetWellRenderMode(mode);
  }
  void SetWellProperty (const char* name)
  {
    ResView::SetWellProperty(name);
  }
  void SetCompProperty (const char* name)
  {
    ResView::SetCompProperty(name);
  }
  void Pick (float x, float y)
  {
    ResView::Pick(x, y);
  }
  void GetModelBoundingBox (float &xmin, float &xmax, float &ymin, float &ymax, float &zmin, float &zmax, bool only_act = true);
  void SetContour (bool f);
  void Render ();
  void EndRender ();
protected:
  // virtual methods
  ResModelRenderer* GetModelRenderer();
  ResRenderingContext* GetRenderingContext() const;
private:
  void LoadModelCommon ();
private:
  ResMapSecRenderingContext* m_context;
  ResMapSecModelRenderer* m_model_renderer;
};

/**
 * Initializes the resview component.
 * Returns true in case of success, false otherwise.
 */
RESVIEW_API bool Init ();
/**
 * At application end, this function must be called.
 * Guarantees all resources are freed and all auxiliary threads finish.
 */
RESVIEW_API void Shutdown ();

}

