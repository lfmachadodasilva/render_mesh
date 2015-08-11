//* render.h
// Reservoir rendering routines (3D).
// Tecgraf/PUC-Rio
// Jan 2004
#ifndef RES_RENDER_3D_H
#define RES_RENDER_3D_H

#include <gpos/model/render.h>
#include <gpos/defines.h>
#include <sciutils/colorscale.h>
#include <vgl/frustum.h>
#include <topsview/colorscale/colorscale.h>
#include <topsviewres/geometry/bdryfacesopaque.h>
#include <ds/array.h>
#include <ds/hash.h>
#ifdef _WIN32
# include <windows.h>
#endif
#include <GL/glew.h>
#include <GL/glu.h>

#define MODE_STATIC  1
#define MODE_DYNAMIC 2

#include "lic/slicgeom.h"

// Enables a different well height for each well,
// where its height depends on the reservoir relief.
#define USE_RELIEF_WELL_HEIGHT

class FenceData;
class ResModel;
class ResModelNew;
class TpvColorScale;
class Res3DWellRenderer;
class Res3DRenderingContext;
class Res3DRenderData;
class ResFaultData;
class ResFaultRenderer;
class TpvVflVectorIntegrator;
class TpvVflAdvector;
class VflFieldLineRenderer;
class TpvResGeometry;
class W3dWell;
struct UGLCylinder;

class RESRENDERAPI Res3DCompletionRenderer : public ResCompletionRenderer
{
public:
  Res3DCompletionRenderer();
  virtual ~Res3DCompletionRenderer();
  void Render (int well, int comp);
  void RenderBegin();
  void RenderEnd();
  void SetWellRenderer (Res3DWellRenderer *wr)
  {
    m_wr = wr;
  }
private:
  void DrawCompletionHighlight (float wellradius);
private:
  Res3DWellRenderer *m_wr;
  GLUquadric *d_quadric;
};

class RESRENDERAPI Res3DWellRenderer : public ResWellRenderer
{
public:
  Res3DWellRenderer (ResCompletionRenderer *renderer, SciColorScale *cs);
  virtual ~Res3DWellRenderer();
  void Render (int element);
  void RenderBegin();
  void RenderEnd();
  void RenderName (int element);
  void RenderNameBegin();
  void RenderNameEnd();
protected:
  void CalcPointWithScale (AlgVector &p) const
  {
    p.x = m_cx + (p.x - m_cx)*m_sx;
    p.y = m_cy + (p.y - m_cy)*m_sy;
    p.z = m_cz + (p.z - m_cz)*m_sz;
  }
private:
  void CalcPointWithScale (AlgVector &dest, AlgVector &p) const
  {
    dest.x = m_cx + (p.x - m_cx)*m_sx;
    dest.y = m_cy + (p.y - m_cy)*m_sy;
    dest.z = m_cz + (p.z - m_cz)*m_sz;
  }
  void CalcPointWithScale (AlgVector &dest, AlgVector p) const
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
  * Given a height and a radius, must a cylinder be drawn or a line will
  * suffice?
  * Returns true if the cylinder must be drawn, false otherwise.
  */
  bool MustDrawCylinder (float height, float radius);
  float* GetCompletionsCoords (int element, int* size);
  /**
  * Obtain entry and exit coordinates for each well that has trajectory.
  * returns 'true' is well has entry and exit points, and 'false' otherwise.
  */
  bool GetCompletionsEntryAndExitCoords (int element, int* size, float** entryCoords, int** cellIds);
  W3dWell* BuildRenderer (int element, float wellradius);                  // builds well
  void BuildTrajGeometry (W3dWell* renderer, float* coords, int numcoords);// builds well geometry with real trajecotry
  void SetTrajGeometry (W3dWell* renderer, float* coords, int numcoords);  // updates well geometry with real trajecotry
  W3dWell* BuildTrajRenderer (int element, float wellradius);              // builds well with cruved path, if any
private:
  float m_cx, m_cy, m_cz, m_sx, m_sy, m_sz;
  double m_proj[16];
  GLUquadric *d_quadric;
  UGLCylinder *d_cylinder_detailed;
  UGLCylinder *d_cylinder_coarse;
  DsHash<DsStringKey,W3dWell*> m_renderers;  // well renderers for wells connected by completions at the center of each completed cell
  DsHash<DsStringKey,W3dWell*> m_trenderers; // well renderers for curved paths (LAYERXYZ in cmg simulators, for example).
  DsHash<DsStringKey,bool> m_has_well_traj;  // indicates if well has entry and exit points data
  float m_completionradius;
  float m_wellradius;
  int m_render_w_prop_ts;
  int m_render_c_prop_ts;
  friend class Res3DCompletionRenderer;
  VglFrustum* m_frustum;
};

class RESRENDERAPI Res3DModelRenderer : public ResModelRenderer
{
public:
  enum PrimType {
    QUADS,
    UNKNOWN,
  };
public:
  Res3DModelRenderer (
    ResCellRenderer *cellr,
    ResWellRenderer *wellr,
    ResCompletionRenderer *compr,
    SciColorScale* cells_color_scale,
    SciColorScale* fault_color_scale);
  virtual ~Res3DModelRenderer ();
  /**
   * Specify whether hierarchy with only active elements should be used.
   */
  void SetUseOnlyActElemHierarchy (bool flag);
  /**
   * Fetch whether hierarchy with only active elements is used.
   */
  bool UseOnlyActElemHierarchy () const;
  /**
   * Enable/disable faces extraction for geomset with active elements.
   */
  void SetActiveGeomSetEnabled (bool flag);
  /**
   * Enable/disable faces extraction for geomset with inactive elements.
   */
  void SetInactiveGeomSetEnabled (bool flag);
  /**
   * Get whether faces extraction is enabled for geomset with inactive elements.
   */
  bool IsInactiveGeomSetEnabled ();
  /**
   * Enable/disable wireframe mode for geomset with active elements.
   */
  void SetActiveGeomSetWireframeEnabled (bool flag);
  /**
   * Enable/disable wireframe mode for geomset with inactive elements.
   */
  void SetInactiveGeomSetWireframeEnabled (bool flag);
  /**
  * Enable/disable drawing of grid lines for geomset with active elements.
   */
  void SetActiveGeomSetGridlinesEnabled (bool flag);
  /**
   * Enable/disable drawing of grid lines for geomset with inactive elements.
   */
  void SetInactiveGeomSetGridlinesEnabled (bool flag);
  void setClippingPlane (float a, float b, float c, float d);
  void setClippingPlane (const float vetPlane[4]);
  /**
   * m_cut3d plane
   */
  void setGLClippingPlane (double a, double b, double c, double d);
  /**
   * m_cut3d plane
   */
  void setGLClippingPlane( double vetPlane[4] );
  /**
   * General cutting planes
   */
  void SetGLClippingPlane (int plane, double a, double b, double c, double d);
  void SetGLClippingPlane (int plane, double equation[4]);
  void SetGLClippingPlaneEnabled (int plane, bool enabled);
  void setCut3dBoundingBox(
    float xmin, float xmax,
    float ymin, float ymax,
    float zmin, float zmax);
  void setNumPlanes (int num_planes);
  void setPlaneLimits (int planeID, float x1, float y1, float z1, float x2, float y2, float z2);
  void setPlaneLimits (float x, float y, float z, float w);
  void SetPlaneEquation (int plane_id, float x, float y, float z, float w);
  void enableCut ();
  void disableCut ();
  void setCut3d (bool flag) {m_cut3d = flag;}
  void SetPlaneEnabled (int plane_i, bool flag);
  void getCutZLimits (float* zmin, float* zmax);
  void RenderBegin ();
  void RenderBeginCells (void);
  void Render ();
  void RenderEndCells (void);
  void RenderEnd ();
  void SetFaultData (const ResFaultData* fault_data);
  const char* GetFaultsActivePropertyName () const;
  const char* GetFaultsActivePropertyUnit () const;

  /**
  * Which is a safe size for a selection buffer ?
  */
  int GetPickBufferSize ();
  PickHit* DoPick (float x, float y);
  PickHit* ProcessPick (int hit_count, 
                        float x, 
                        float y,
                        bool check_cell = true,
                        bool check_well = true,
                        bool check_comp = true,
                        bool get_coords = false);
  /**
   * Performs selection on the model.
   * 'x' and 'y' are the normalized coordinates of the point being selected.
   *
   * Returns the index of the selected cell if any cell was hit.
   * Returns a negative number otherwise.
   */
  int CellSelection (float x, float y);
  bool CellSelection (float x, float y, AlgVector* coords);
  bool FenceSelection (float x, float y, GLuint* id);
  void SetSelectionMode (bool sel);
  /**
   * Lights configuration
   *
   * Sets attributes for the light of index 'i'.
   * Direction 'dx', 'dy' and 'dz' must be given in world coordinates.
   */
  void SetLight (
    int i,
    bool active,
    int oglid,
    float dx,
    float dy,
    float dz,
    float diffr,
    float diffg,
    float diffb,
    float spr,
    float spg,
    float spb);
  virtual bool MustRefine () const;
  /**
   * Get the render mode used by this renderer to draw well names
   */
  virtual UFontMessage::RenderMode GetWellNameRenderMode ()
  {
    return UFontMessage::TEXTURE_FONT;
  }
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
  /**
   * Accumulates the transformation required to take from
   * the global space to the space in which the cells are
   * rendered.
   */
  void LoadCellsTransformation ();
  AlgMatrix GetCellsTransformation ();
  /**
   * Vector Field Line Methods
   */
  TpvVflVectorIntegrator* GetFieldLineIntegrator ();
  TpvVflAdvector* GetFieldLineAdvector ();
  VflFieldLineRenderer* GetFieldLineRenderer ();
  void ResetFieldLineWells (bool restoreBackup = false);
  void SetFieldLineColorScale (float minR, float minG, float minB, float midR, float midG, float midB, float maxR, float maxG, float maxB);
  void GetFieldLineColorScale (float*minR, float*minG, float*minB, float*midR, float*midG, float*midB, float*maxR, float*maxG, float*maxB);
  void GetFieldLineProperty (int *property);
  void GetFieldLineWellCount (int *count);
  void GetFieldLineWell (int which, int *id);
  //void CreateFieldLines (int whichProperty, int whichStep);
  void CreateFieldLines (int whichProperty, int whichWell, int whichStep);
  bool SaveFieldLines (const char* filename);
  bool LoadFieldLines (const char* filename, bool ignoreMissingFile = false);
  PrimType GetCellsPrimitiveType ();
  DsArray<float>* GetCellsVertexArray ();
  DsArray<unsigned int>* GetCellsIndices ();
  /**
   * Obtains total number of primitives in the last render call (without any culling).
   */
  int GetTotalNumberOfPrimitives () const
  {
    return m_num_primitives;
  }
  /**
   * Obtains the number of primitives used in the last render call.
   */
  int GetNumberOfPrimitivesUsed () const
  {
    return m_last_num_primitives_used;
  }
  /**
   * SLic Methods
   * If data_ts is NULL, assumes vector field info has changed.
   */
  void RefreshVectorField(bool useAutofill, int* data_ts = NULL);

protected:
  /**
   * Return a properly configured ufonttext instance.
   */
  virtual UFontText* CreateText ();

  virtual Res3DRenderData* GetRenderData ();
  /**
   * Enable/disable faces extraction for a given geomset type.
   */
  void SetGeomSetEnabled (TpvResBdryFacesOpaqueGeometry::GeomSetType type,
                          bool flag);
  /**
   * Get whether faces extraction is enabled for a given geomset type.
   */
  bool IsGeomSetEnabled (TpvResBdryFacesOpaqueGeometry::GeomSetType type);
  /**
   * Enable/disable wireframe mode for a given geomset type.
   */
  void 
  SetGeomSetWireframeEnabled (TpvResBdryFacesOpaqueGeometry::GeomSetType type,
                              bool flag);
  /**
   * Enable/disable drawing of grid lines for a given geomset type.
   */
  void 
  SetGeomSetGridlinesEnabled (TpvResBdryFacesOpaqueGeometry::GeomSetType type,
                              bool flag);
  float GetReservoirTranslation ();
  static float* AllocSeparationsArray (Res3DRenderingContext *ctx, ResModelNew* mdl);
  TpvColorScale* GetColorScale () const
  {
    return m_color_scale;
  }
  void CreateColorScale (int numcolors);
  ResPosModelNew* GetPosModel () const;
  bool MustSeparateLayers ();
  bool HasSection ();
private:
  virtual void CreateTopsView (Res3DRenderData *renderData);
  // creates topsview for volume rendering
  void CreateVVTopsView ();
  void RenderFault (Res3DRenderingContext* ctx);
  void RenderFence (Res3DRenderingContext* ctx);
  void RenderWells (Res3DRenderingContext *ctx, bool disable_depth_test);
  /**
   * Calculate intersection between wells and fence diagram.
   */
  void IntersectFenceAndWells ();
  void RenderWellsNames (Res3DRenderingContext *ctx);
  void PreparePickBuffer ();
  int SelectionRender (float x, float y);
  virtual bool EnableCutPlane (
    Res3DRenderData* renderData,
    bool drawing_section,
    bool separating_layers
  );
  /**
   * Renders the reservoir cut plane.
   *
   * Used in the 3D window (cut3d) and in the Cut window (map -> cutwindow).
   */
  void RenderCutPlane (
    Res3DRenderData* renderData,
    bool drawing_section,
    bool separating_layers,
    bool renderOpaque);

  /**
   * Renders the reservoir with transparent cells.
   */
  void RenderTransparentIsoContour (
    Res3DRenderData* renderData,
    const AlgVector& obspos,
    bool drawing_section,
    bool separating_layers);
  /**
   * Renders the reservoir without transparent cells.
   */
  void RenderOpaqueIsoContour (
    Res3DRenderData* renderData,
    const AlgVector& obspos,
    bool drawing_section,
    bool separating_layers);
  virtual void ColorScaleChanged (int& data_ts);
  virtual void PropertyChanged (ResProperty *prop);
  /**
   * Informs that the current cell selection changed.
   */
  virtual void CellSelectionChanged (ResProperty *prop)
  {
  }
  virtual bool MustUsePerElemColor () const;
  void ReloadVVColorScale (int& data_ts);
  void ReloadVVProperties (ResProperty *prop);
  virtual void SmoothnessChanged ();
  virtual void ModelChanged ();
  void RenderReservoirIsoContour (
    Res3DRenderData* renderData, ResProperty* prop);
  void RenderReservoirVolumetric (
    Res3DRenderData* renderData, ResProperty* prop);
  void RenderReservoirFieldlines (int timeStepIndex);
  void RenderSLic();
  void RenderSLic3();
  TpvResBdryFacesOpaqueGeometry* GetUpdatedOpaqueIsoContourTopsViewGeometry (const AlgVector* obspos);
private:
  void SetGeometryActiveElems (Res3DRenderingContext* ctx,
                               Res3DRenderData* renderData,
                               TpvResGeometry* geom);
protected:
  Res3DRenderData* m_renderingData;
  int m_nplanes;
  float* m_planelimits;
private:
  TpvColorScale* m_color_scale;
  struct light
  {
    int id;
    float direction[4];
    float diffuse[4];
    float specular[4];
    bool active;
  };
  // array of lights to be used (8 max)
  light m_lights[8];
  int m_allocatedPlanes;
  float m_clipping_plane[4];
  struct ClippingPlane
  {
    bool enabled;
    double equation[4];
  };
  ClippingPlane m_model_clipping_plane[6];
  double m_gl_clipping_plane[6];
  double m_cut3d_box[6];
  ResFaultRenderer* m_fault_renderer;
  SciColorScale* m_fault_cs;
  // pick buffer data
  GLuint *m_pickbuffer;
  int m_pickbuffersize;
  int m_num_primitives;
  int m_last_num_primitives_used;
  // exclusive font cache
  UFontCache* m_font_cache;
  // whether 3D cut is enabled
  bool m_cut3d;
  int m_render_ts;
  int m_render_lic_ts;
  int m_render_lic3_ts;
  int m_render_res_isoc_ts;
  int m_render_res_vol_ts;
  int m_render_res_dl_ts;
  // whether this class is used in the cut window
  bool m_cut;
  bool m_use_only_act_hierarchy;
  bool m_cuda_support; // whether CUDA is supported by the graphics card
};

class RESRENDERAPI Res3DRenderingContext : public ResRenderingContext
{
public:
  Res3DRenderingContext(int nlayers, ResModel *mdl);
  virtual ~Res3DRenderingContext();
  enum RenderMode
  {
    RENDER_ISOCONTOUR = 0,
    RENDER_VOLUMETRIC
  };
  /**
   * Specifies the point around which the scale is performed.
   * The default is the active cells bounding box center.
   */
  void SetScaleCenter (float x, float y, float z);
  /**
   * Obtains the x coordinate of the point around which the scale
   * is performed. The default is (ActXMax()+ActXMin())/2.
   */
  float ScaleCenterX () const;
  /**
   * Obtains the x coordinate of the point around which the scale
   * is performed. The default is (ActYMax()+ActYMin())/2.
   */
  float ScaleCenterY () const;
  /**
   * Obtains the x coordinate of the point around which the scale
   * is performed. The default is (ActZMax()+ActZMin())/2.
   */
  float ScaleCenterZ () const;
  /**
   * Specifies layer 'l' separation as 'd'.
   */
  void SetLayerDistance(int l, float d);
  float GetLayerDistance(int l) const
  {
    assert((l>=0)&&(l<m_nl));
    return m_ldists[l];
  }
  /**
   * Returns GetLayerDistance(l) multiplied by the global separation factor.
   */
  float GetFinalLayerDistance (int l) const;
  /**
   * Specifies layer 'l' as visible if 'vis' is true and as invisible otherwise.
   */
  void SetLayerVis(int l, bool vis)
  {
    assert(l>=0 && l<m_nl);
    m_lvis[l] = vis;
  }
  bool GetLayerVis(int l)
  {
    assert((l>=0)&&(l<m_nl));
    return m_lvis[l];
  }
  void DisableSectors ()
  {
    free(m_sectors);
    m_sectors = NULL;
    m_numsectors = 0;
    m_enable_sector = false;
  }
  void SetSectors(int num_sectors,int* psector)
  {
    m_sectors = (int*)realloc(m_sectors,sizeof(int)*num_sectors);
    memcpy(m_sectors,psector,sizeof(int)*num_sectors);
    m_numsectors = num_sectors;
    m_enable_sector = true;
  }
  bool HasSectors () const
  {
    return m_enable_sector;
  }
  int GetNumSectors () const
  {
    return m_numsectors;
  }
  const int* GetSectors () const
  {
    return m_sectors;
  }
  /**
   * Sets current render mode, defined by enum RenderMode
   */
  void SetRenderMode (RenderMode mode);
  RenderMode GetRenderMode () const
  {
    return m_render_mode;
  }
  void SetVVProbeBoxEnabled (bool f)
  {
    m_vv_probe_enabled = f;
  }
  bool VVProbeBoxEnabled () const
  {
    return m_vv_probe_enabled;
  }
  void SetVVProbeBox (float xmin, float xmax, float ymin, float ymax, float zmin, float zmax)
  {
    m_vv_probe_min.Set(xmin, ymin, zmin);
    m_vv_probe_max.Set(xmax, ymax, zmax);
  }
  const AlgVector& GetVVProbeBoxMin () const
  {
    return m_vv_probe_min;
  }
  const AlgVector& GetVVProbeBoxMax () const
  {
    return m_vv_probe_max;
  }
  int GetUpdateMode() const
  {
    return m_update_mode;
  }
  /**
   * Hints the renderer:
   *
   * - MODE_STATIC signals that the rendering process will not change in the
   *   following frames (enables some optimizations).
   * - MODE_DYNAMIC signals that the rendering process will change, like in
   *   property/step animations.
   */
  void SetUpdateMode(int mode);
  /**
   * Specifies if only the top faces of the cells must be drawn.
   */
  void SetTopFaces (bool flag);
  bool HasTopFaces () const
  {
    return m_topfaces;
  }
  /**
   * Specifies a global layer separation of value 'dk'.
   */
  void SetGlobalLayerSeparation (float dk);
  float GetGlobalLayerSeparation () const
  {
    return m_dk;
  }
  /**
   * Specifies the 'i' section filter.
   */
  void SetSecI (int i)
  {
    m_seci = i;
  }
  /**
   * Specifies the 'j' section filter.
   */
  void SetSecJ (int j)
  {
    m_secj = j;
  }
  /**
   * Specifies the 'k' section filter.
   */
  void SetSecK (int k)
  {
    m_seck = k;
  }
  int GetSecI () const
  {
    return m_seci;
  }
  int GetSecJ () const
  {
    return m_secj;
  }
  int GetSecK () const
  {
    return m_seck;
  }
  /**
   * Speficies that only cells belonging to this ijk range (inclusive)
   * will be rendered.
   * Option cannot be used along with layer separation or section i, j and k.
   */
  void EnableSubGrid (int imin,
                      int imax,
                      int jmin,
                      int jmax,
                      int kmin,
                      int kmax);
  /**
   * Speficies that only cells belonging to this ijk range (inclusive)
   * will be rendered.
   * Option cannot be used along with layer separation or section i, j and k.
   */
  void DisableSubGrid ();
  bool IsSubGridEnabled () const
  {
    return m_subgrid_enabled;
  }
  int GetSubGridIMin () const
  {
    return m_subgrid_imin;
  }
  int GetSubGridIMax () const
  {
    return m_subgrid_imax;
  }
  int GetSubGridJMin () const
  {
    return m_subgrid_jmin;
  }
  int GetSubGridJMax () const
  {
    return m_subgrid_jmax;
  }
  int GetSubGridKMin () const
  {
    return m_subgrid_kmin;
  }
  int GetSubGridKMax () const
  {
    return m_subgrid_kmax;
  }
  /**
   * Specifies if completions must be rendered.
   */
  void SetCompletionsVisible(bool f)
  {
    m_compvis = f;
  }
  bool CompletionsVisible() const
  {
    return m_compvis;
  }
  bool WellsTrajectoryVisible () const
  {
    // real well trajectory will only be active if layers are not separated.
    return ResRenderingContext::WellsTrajectoryVisible() && 
           (GetGlobalLayerSeparation() == 0.0f);
  }
  const bool* GetLayerVisibility () const
  {
    return m_lvis;
  }
  /**
   * Specifies if the wireframe mode is on: only gridlines are drawn,
   * internal faces (quads) are not.
   * NOTE: when set to true, calls to SetGridLinesEnabled have no effect:
   * when wireframeenabled, gridlines are ALWAYS drawn.
   */
  void SetWireframeEnabled (bool f)
  {
    SetWireframeEnabled(TpvResBdryFacesOpaqueGeometry::TYPE_1, f);
  }
  void 
  SetWireframeEnabled (TpvResBdryFacesOpaqueGeometry::GeomSetType type, bool f)
  {
    m_wireframe[type] = f;
  }
  bool IsWireframeEnabled () const
  {
    return IsWireframeEnabled(TpvResBdryFacesOpaqueGeometry::TYPE_1);
  }
  bool 
  IsWireframeEnabled (TpvResBdryFacesOpaqueGeometry::GeomSetType type) const
  {
    return m_wireframe[type];
  }
  /**
   * Specifies if the grid lines must be rendered.
   * NOTE: calls to SetGridLinesEnabled have no effect when in Wireframe mode.
   * @see SetWireframeEnabled(bool)
   */
  void SetGridLinesEnabled (bool f)
  {
    SetGridLinesEnabled(TpvResBdryFacesOpaqueGeometry::TYPE_1, f);
  }
  void 
  SetGridLinesEnabled (TpvResBdryFacesOpaqueGeometry::GeomSetType type, bool f)
  {
    m_draw_grid[type] = f;
  }
  bool GetGridLinesEnabled () const
  {
    return GetGridLinesEnabled(TpvResBdryFacesOpaqueGeometry::TYPE_1);
  }
  bool GetGridLinesEnabled (TpvResBdryFacesOpaqueGeometry::GeomSetType type) const
  {
    return m_draw_grid[type];
  }
  /**
   * Specifies if field lines must be rendered.
   */
  void SetFieldLines (bool f)
  {
    m_fieldlines = f;
  }
  bool HasFieldLines () const
  {
    return m_fieldlines;
  }
  /**
   * Specifies a global alpha multiplier 'a',
   * where 'smax' is considered the maximum possible scale.
   */
  void SetScaleAlpha (float a, float smax)
  {
    m_scalealpha = a;
    m_scalealphamax = smax;
  }
  float GetScaleAlpha () const
  {
    return m_scalealpha;
  }
  float GetNormalizedAlphaScale () const
  {
    return m_scalealpha / m_scalealphamax;
  }
  /**
   * Specifies which refined grid must be rendered (from 0 to numgrids-1).
   */
  void SetRefinedGrid (int index);
  int GetRefinedGrid () const
  {
    return m_refinement;
  }
  /**
   * For internal use
   */
  void SetCellsDispList (int id)
  {
    m_cellsdisplist = id;
  }
  /**
   * For internal use
   */
  int GetCellsDispList () const
  {
    return m_cellsdisplist;
  }
  /**
   * For internal use
   */
  bool MustUseCellsDisplayList() const;
  /**
   * For internal use
   */
  void ReleaseDisplayList();
  /**
   * For internal use
   */
  void ReleaseCellsDisplayList();
  /**
   * For internal use
   */
  void SetOptimizeCells(bool flag)
  {
    m_optimize_cells = flag;
  }
  /**
   * For internal use
   */
  void SetWillRender(bool flag)
  {
    if (!flag)
      ReleaseDisplayList();
  }
  /**
   * For internal use
   */
  bool IsOptimizingCells() const
  {
    return m_optimize_cells;
  }
  /**
   * Get limits in Z for 3d rendering, taking into account model scale, layers
   * separations and well head height. Defines Z coordinates for model's bounding
   * volume.
   * @param zmin return minimum Z value.
   * @param zmax return maximum Z value.
   */
  void GetZLimits (float* zmin, float* zmax);
  void SetCompletionRadiusFactor (float r);
  /**
  *  For internal use
  */
  float GetCompletionRadiusFactor () const
  {
    return m_completion_radius_factor;
  }
  void SetWellRadiusFactor (float r);
  /**
  *  For internal use
  */
  float GetWellRadiusFactor () const
  {
    return m_well_radius_factor;
  }
  void SetFenceData (FenceData* fence_data)
  {
    m_fence_data = fence_data;
  }
  FenceData* GetFenceData () const
  {
    return m_fence_data;
  }
  void SetFaultsRenderingEnabled (bool f)
  {
    m_fault_rendering_enabled = f;
  }
  bool IsFaultsRenderingEnabled () const
  {
    return m_fault_rendering_enabled;
  }
  bool LoadFaultDataFromFile (const char* fn);
  const ResFaultData* GetFaultData () const
  {
    return m_fault_data;
  }
  const bool HasFaultData () const
  {
    return m_fault_data != NULL;
  }
  /**
   * Access array of wells cut by fence diagram.
   */
  const DsArray<int>& GetFenceCutWells () const
  {
    return m_fence_wells;
  }
  /**
   * Clear array of wells cut by fence diagram.
   */
  void ClearFenceCutWells ()
  {
    m_fence_wells.Clear();
  }
  /**
   * Store well cut by fence diagram.
   * @param well_i well index.
   */
  void AddFenceCutWell (int well_i)
  {
    m_fence_wells.Append(well_i);
  }
  /**
   * Set distance tolerance factor to use when calculating
   * intersections between wells and reservoir.
   */
  void SetFenceWellDistanceFactor (float factor)
  {
    if (m_fence_wells_distance_factor == factor)
      return;
    m_fence_wells_distance_factor = factor;
    SetFenceCutWellsNeedsUpdate(true);
  }
  /**
   * Get distance tolerance factor to use when calculating
   * intersections between wells and reservoir.
   */
  float GetWellDistanceFactor () const
  {
    return m_fence_wells_distance_factor;
  }
  /**
   * Set fence posts width factor based on wells radius.
   * @param factor.
   */
  void SetFencePostWidthFactor (float factor)
  {
    m_fence_post_width_factor = factor;
  }
  /**
   * Get fence posts width factor based on wells radius.
   */
  float GetFencePostWidthFactor () const
  {
    return m_fence_post_width_factor;
  }
  /**
   * Set fence diagram opacity.
   */
  void SetFenceOpacity (float alpha)
  {
    m_fence_opacity = alpha;
  }
  /**
   * Get fence diagram opacity.
   */
  float GetFenceOpacity () const
  {
    return m_fence_opacity;
  }
  /**
   * Get whether intersections between wells and reservoir
   * must be tested.
   * Assumes SetFenceData has been called previously.
   */
  void SetFenceCutWellsNeedsUpdate (bool flag)
  {
    m_fence_wells_needs_update = flag;
    // reset wells cut by fence
    if (flag)
      ClearFenceCutWells();
  }
  /**
  * Intersections between wells and reservoir must be tested?
   */
  bool IsFenceCutWellsNeedsUpdate () const
  {
    return m_fence_wells_needs_update;
  }
  /**
   * Enables/disables fence diagram rendering.
   * Assumes SetFenceData has been called previously.
   */
  void SetCutFenceEnabled (bool flag);
  /**
   * Should render fence diagram?
   */
  bool IsCutFenceEnabled () const
  {
    return m_cut_fence;
  }
  // virtual methods
  float GetReservoirTranslation () const;
private:
  int m_update_mode;
  bool m_optimize_cells;
  bool m_topfaces;            // true to render only cells' top faces, false renders all cells' faces
  int m_nl;
  float m_dk;                 // global layer separation factor, 'k' axis
  float *m_ldists;            // array of layers distances
                              // each layer has its z distance to the top of the reservoir
  bool *m_lvis;               // array of layers visibility
                              // each layer has its visiblity toggle
                              // true if the layer is visible, false otherwise
  bool* m_wireframe;          // wireframe toggle
  bool* m_draw_grid;          // draw grid lines toggle.
  int m_seci, m_secj, m_seck; // sections to perform
                              // a value of -1 indicates that sectioning shouldn't be performed at the
                              // given axis
  bool m_subgrid_enabled;     // sub grid enabled?
  int m_subgrid_imin;         // sub grid range (inclusive), if enabled
  int m_subgrid_imax;
  int m_subgrid_jmin;
  int m_subgrid_jmax;
  int m_subgrid_kmin;
  int m_subgrid_kmax;
  bool m_compvis;        // completions visibility toggle
  bool m_fieldlines;     // fieldlines visibility toggle
  int* m_sectors;        // sector id to view,NULL views all sectors
  int m_numsectors;      // number of active sectors
  bool m_enable_sector;  // active sectors control.
  RenderMode m_render_mode;     // current render mode.
  float m_scalealpha;    // current scale of the alpha value.
  float m_scalealphamax; // maximum possible value of the alpha scale.
  int m_cellsdisplist;   // cells display list identifier
  int m_refinement;      // index of the refined grid being rendered
  bool m_vv_probe_enabled;
  AlgVector m_vv_probe_min;
  AlgVector m_vv_probe_max;
  float m_completion_radius_factor;    // default is 1 (f < 1 shrinks and f > 1 enlarges cylinder)
  float m_well_radius_factor;          // default is 1 (f < 1 shrinks and f > 1 enlarges cylinder)
  FenceData* m_fence_data; // fence diagram data
  const ResFaultData* m_fault_data; // faults data
  bool m_fault_rendering_enabled;   // flag for faults rendering
  bool m_cut_fence; // whether fence cut is enabled
  DsArray<int> m_fence_wells; // wells that passed the intersection test against fence
  bool m_fence_wells_needs_update;  // indicates whether intersection against well is necessary
  float m_fence_wells_distance_factor;
  float m_fence_opacity;
  float m_fence_post_width_factor;
  float m_scx, m_scy, m_scz;  // global scale center (default is active cells bounding box center)
};

#endif

