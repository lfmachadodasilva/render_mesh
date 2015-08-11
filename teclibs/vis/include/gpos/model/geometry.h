//* geometry.h 
// The grid geometry.
// Tecgraf/PUC-Rio
// Jan 2004

#ifndef grd_geometry_h
#define grd_geometry_h

#include <alg/vector.h>
#include <ds/array.h>
#include <ds/mtvar.h>
#include <geoms/intersect.h>
#include <gpos/common/util.h>
#include <gpos/defines.h>
#include <gpos/model/model.h>
#include <gpos/io/open.h>
#include <tops/multimodel.h>
#include <topsgeoms/polyhedramodel.h>

#include <math.h> // fabs
#include <stdio.h> // sprintf
#include <assert.h>

#define cTOPO 0
#define cBASE 1
#define cMAX_NMB_NEIGHBORS 4 /// Maximum number of cells at the same layer that can share the same vertex

#ifndef TOP_USE_MULTILEVEL
#error "The define TOP_USE_MULTILEVEL must be turned on in tops/defines.h"
#endif

class ResGeometry;
class ResGrid;
class IOStream;
class IOCompBinFileStream;

//* Geometric tolerance
static const float GRD_TOL = 1e-7F;
static const float GRD_BIG = 1e20F;

//* 'ResInterpolationMode' enumeration
// Enumerates the interpolation mode.
enum ResInterpolationMode {
  GRD_NORMAL, /// original mesh
  GRD_INTERPOLATED, /// interpolated mesh. If it's corner point, the mesh remains untouched.
  GRD_LAST
};

//* 'ResGeometry' Class
// Represents the grid geometry.
class RES_API ResGeometry
{
public:
  typedef void (*ProgressCB)(const char* sectionname, float progress, void *data);
  typedef void (*LoadProgressFunc)(float progress, void* data);
  typedef void (*AfterComputedFunc) (ResModel* model, ResOpenOptions* options, void* data);
private:
  class HierarchiesSet
  {
  public:
    HierarchiesSet ();
    ~HierarchiesSet ();
    void Reset ();
  public:
    TOP_INTERSECT* w_act_cells;
    TOP_INTERSECT* w_all_cells;
    DsArray<TOP_INTERSECT*> w_act_cells_level;
    DsArray<TOP_INTERSECT*> w_all_cells_level;
  };
private:
  TopMultiModel* m_top_model; // current adjacency model (original or smoothed)
  TopMultiModel m_n_top_model; // original adjacency model
  TopMultiModel m_i_top_model; // smoothed adjacency model
  HierarchiesSet* m_n_hierarchy;
  HierarchiesSet* m_i_hierarchy;
protected:
  ResModel* d_model;  // the model this geometry belongs to
  int m_ni;       // number of cells in the i direction
  int m_nj;       // number of cells in the j direction
  int m_nk;       // number of cells in the k direction
  int d_nact;     // number of active cells

  typedef struct {
    AlgVector min;
    AlgVector max;
  } BB;

private:
  BB d_bb;            // bounding box
  BB d_act_bb;        // active cells bounding box
  static DsMTVar<float> s_max_z_scale;  // maximum z scale value
  float m_ini_z_scale;                  // initial z scale value
protected:
  float d_tx, d_ty;   // bounding box translation: UTM coordinates are too big.
                      // translate to local coords so as to work with floats.

  ResInterpolationMode d_imode;    // current interpolation mode
  double d_fault;    // mininum size of a crack to be considered a fault (negative values mean infinite)
  bool d_z_inverted; // was the Z coordinate of all points inverted?
  bool d_inactive_correct; // are the inactive cells Z correct?
  bool d_smooth_computed; // has smooth mode been computed before?

  // OBS: a fault is given by a gap defined in reservoir world coordinates. Today, this gap is 30cm.

  void ComputeFaultMap(TopModel* m, float tolerance, bool* fault_map_i, bool* fault_map_j);
  TopElement InsertSmoothBlockCenteredCell(int i, int j, int k, 
      const float* vertex_list, const bool* fault_map_i, const bool* fault_map_j, bool collapse_k);
protected:
  /*
   * 'refinements_must_be_removable' specifies if eventual geometry refinements must be removable.
   */
  ResGeometry (ResModel* model, int nx, int ny, int nz, int ncells, int nact, bool refinements_must_be_removable);
public:
  /**
   * Function that must be called at program exit to guarantee
   * all resources are freed and all auxiliary threads finish.
   */
  static void AtExit ();
  virtual ~ResGeometry ();
  static IOStream* BeginGeometryFileLoad (const char* filename,
                                          float loader_version,
                                          LoadProgressFunc progressfunc,
                                          void* progressdata);
  static bool LoadInstantiationParameters (IOStream* stream,
                                           bool* is_corner_points,
                                           int* nx,
                                           int* ny,
                                           int* nz,
                                           int* nact,
                                           int* numcells,
                                           bool* is_inactive_correct);
  bool FinishGeometryFileLoad (IOStream* stream, int finalnumcells);
  /** Split model's elements in a spatial hierarchy. */
  void BuildHierarchy (UpdateSectionProgressCB progresscb,
                       void* progresscbdata);
  void BuildOriginalModelHierarchy (UpdateSectionProgressCB progresscb,
                                    void* progresscbdata);
  /**
   * Counts the number of main grid cells on each reservoir layer.
   * If 'active_only' is true, only active cells are counted.
   */
  void CountLayersCellCount (DsArray<int>* layers_cell_count, bool active_only);
  /** 
   * Return model's elements spatial hierarchy.
   * @param only_act if true, returns the hierarchy of active cells, else returns the hierarchy of all cells.
   * @param k hierarchy including all layers if 'k' == ALL_LAYERS, else returns the hierarchy of a specific layer. Default is ALL_LAYERS.
   */
  geoms::Hierarchy* GetHierarchy (bool only_act, int k = ALL_LAYERS);
  topsgeoms::PolyhedraModelRes* GetPolyModel (bool only_act, int k = ALL_LAYERS);
  TOP_INTERSECT* GetIntersect (bool only_act, int k = ALL_LAYERS);
#if DEBUG_TESTED_ELEMS
  void SaveTestedElementsProperty (const char* filename,
                                   DsHash<int, bool>* tested_elems);
#endif
  /**
   * Sets the geometry as valid or invalid.
   */
  void SetValid (bool valid)
  {
    m_valid = valid;
  }
  /**
   * Is the geometry valid?
   */
  bool IsValid () const
  {
    return m_valid;
  }
  /**
   * Inform if the inactive cells geometry's Z coordinate is correct
   * (old PPOSP driver was not specifying the inactive cells geometry's Z).
   */
  void SetInactiveCorrect (bool f)
  {
    d_inactive_correct = f;
  }
  bool IsInactiveCorrect ()
  {
    return d_inactive_correct;
  }
  /**
   * Specifies the z dir (if zdirdown=true, the z coordinates rise along with gravity).
   */
  void SetZDirDown (bool f)
  {
    m_zdir_down = f;
  }
  /**
   * Obtains the z dir (if the Z coordinates rise along with gravity).
   */
  bool IsZDown () const
  {
    return m_zdir_down;
  }
  /**
   * Specifies the k dir (if kdir=DOWN, the k coordinates rise along with gravity).
   */
  void SetKDir (TopModel::KDir kdir)
  {
    m_n_top_model.SetKDir(kdir);
    m_i_top_model.SetKDir(kdir);
  }
  /**
   * Informs if reservoir elements are adjacent through switched faces in the J direction,
   * considering the original element template.
   */
  void SetJDirInverted (bool f)
  {
    m_n_top_model.SetJDirInvertedReservoir(f);
    m_i_top_model.SetJDirInvertedReservoir(f);
  }
  /**
   * Obtains the k dir (if the K coordinates rise along with gravity).
   */
  bool IsKDown () const
  {
    return m_n_top_model.GetKDirReservoir() == TopModel::K_DIR_DOWN;
  }
  TopMultiModel* GetOriginalModel(){ return &m_n_top_model; }
  TopMultiModel* GetSmoothModel(){ return &m_i_top_model; }
  TopMultiModel* GetModel(){ return m_top_model; }
  const bool* GetVisibleCells() const
  {
    return m_active_cells.GetArrayConst();
  }
  void SetCellActive (int index, bool a)
  {
    m_active_cells.Set(index, a);
  }
  /**
   * Specifies all cells activity status at once.
   */
  void SetCellsActive (int numcells, const bool* a)
  {
    assert(numcells == m_active_cells.Size());
    memcpy(m_active_cells.GetArray(), a, numcells*sizeof(bool));
  }
  bool IsActiveCell (int index) const
  {
    return m_active_cells.Get(index);
  }
  ResModel* GetResModel() const { return d_model; }
  /**
   * Releases memory allocated for temporaries.
   */
  void ReleaseMemory ();

  void GetBoundingBoxTranslation (float* x, float* y) const
  {
    *x = d_tx;
    *y = d_ty;
  }
  /**
   * Transforms a coordinate from local model coordinates to original model coordinates.
   */
  void TransformToOriginalCoords (double* x, double* y, double* z) const;
  /**
   * Transforms a coordinate from original model coordinates to local model coordinates.
   */
  void TransformToLocalCoords (double* x, double* y, double* z) const;
    //* Grid dimensions query
    // Returns the number of cells in the i direction
  int Ni () const { return m_ni; }
    // Returns the number of cells in the j direction
  int Nj () const { return m_nj; }
    // Returns the number of cells in the k direction
  int Nk () const { return m_nk; }

    //* Amount of active cells query
    // Returns the number of active cells
  int Nact () const { return d_nact; }
    //* Amount of cells query
    // Returns the number of cells
  int Ncells () const
  { 
    return m_active_cells.Size();
  }
  /**
   * Returns the original number of cells in the root grid.
   */
  int GetMainGridNumCells () const
  {
    return m_num_cells_root;
  }

  void SetInd(int i, int v)
  {
    assert(m_prop_ind.ValidIndex(i));
    m_prop_ind.Set(i, v);
  }
  /**
   * Obtains the property indirection of the cell of id 'i'.
   */
  int GetInd (int i) const
  {
    return m_prop_ind.Get(i);
  }
    //* Active cell minima query
    // Returns the active cells bounding box's minimum X
  float ActXmin () const { return d_act_bb.min.x; }
    // Returns the active cells bounding box's minimum Y
  float ActYmin () const { return d_act_bb.min.y; }
    // Returns the active cells bounding box's minimum Z
  float ActZmin () const { return d_act_bb.min.z; }

    //* Active cell maxima query
    // Returns the active cells bounding box's maximum X
  float ActXmax () const { return d_act_bb.max.x; }
    // Returns the active cells bounding box's maximum Y
  float ActYmax () const { return d_act_bb.max.y; }
    // Returns the active cells bounding box's maximum Z
  float ActZmax () const { return d_act_bb.max.z; }

    //* Global minima query
    // Returns the bounding box's minimum X
  float Xmin () { return d_bb.min.x; }
    // Returns the bounding box's minimum Y
  float Ymin () { return d_bb.min.y; }
    // Returns the bounding box's minimum Z
  float Zmin () { return d_bb.min.z; }

    //* Global maxima query
    // Returns the bounding box's maximum X
  float Xmax () { return d_bb.max.x; }
    // Returns the bounding box's maximum Y
  float Ymax () { return d_bb.max.y; }
    // Returns the bounding box's maximum Z
  float Zmax () { return d_bb.max.z; }

  /**
   * Adjusts the model bounding boxes to cartesian coordinates
   */
  void ConvertBBsToCartesian ();

    //* Linear index computation
    // Computes the cell index given it's position in the grid.
  int Index (int i, int j, int k) const
  {
#ifdef _DEBUG
    if ((i>=Ni())||(j>=Nj())||(k>=Nk())||
        (i<0)||(j<0)||(k<0))
    {
      char msg[128];
      sprintf(msg, "Invalid IJK requested: %d %d %d   Bounds are: %d %d %d", i,j,k,Ni(),Nj(),Nk());
      //PSUtil::Error(msg);
      PSUtil::WarningOld(msg);
      assert(0);
      return 0;
    }
#endif
    return RES_LINEAR_INDEX(i,j,k,Ni(),Nj(),Nk());
  }

    //* Reverse linear index computation
    // Computes the cell position in the grid given it's linear index.
  void ReverseIndex (int index, int *i, int *j, int *k)
  {
    ResReverseIndex (index, Ni(), Nj(), Nk(), i, j, k);
  }
  /**
   * Informs if the main grid cell of index 'origindex' is present in the model.
   */
  bool HasCell (int origindex) const
  {
    return m_n_top_model.GetRootModel()->GetElem(TopModel::ELEMENT_HEX8_RESERVOIR,(unsigned int)origindex).IsValid();
  }
  /**
   * Informs if the main grid cell of indices 'i', 'j' and 'k' is present in the model.
   */
  bool HasCell (int i, int j, int k) const
  {
    return HasCell(Index(i,j,k));
  }
  /**
   * AfterMainGridComputed
   *
   * Calculates the model's bounding box, corrects the model orientation and
   * centers the model's coordinates and bounding box.
   */
  void AfterMainGridComputed ();

    //* Geometry mode adjust
    // Change the geometry interpolation mode.
    // Returns true if normals had to be recomputed, false otherwise.
  bool SetGeometryMode (int                     mode,
                        double                  fault = -1,
                        UpdateSectionProgressCB progressfunc = NULL,
                        void*                   progressfuncdata = NULL);

  bool SetVerticalGap (double                  gap,
                       UpdateSectionProgressCB progressfunc = NULL,
                       void*                   progressfuncdata = NULL);

  inline double VerticalGap (void) {return d_fault; }

  virtual bool IsCornerPoints () = 0;

  /**
  * Metodos para retornar informacoes topologicas da TopsView
  */
  //* Center coordinate computation
  // Computes the center of the whole cell or of a given face
  AlgVector centerPoint (int i,int j,int k, int face = -1);
  AlgVector centerPoint (int index, int face = -1)
  {
    return centerPoint(GetCell(index), face);
  }
  AlgVector centerPoint (TopElement cell, int face = -1);

  //* Diagonal vector computation
  // Computes the diagonal vector of the cell
  AlgVector computeDiag (TopElement cell);

  //* Returns a vertex (x,y,z) reference of a given cell (i,j,k) , and given vertex number,
  AlgVector GetCellVertex (int index, int v)
  {
    return GetCellVertex(GetCell(index), v);
  }
  AlgVector GetCellVertex (TopElement cell, int v);
  //* Returns a vertex (x,y,z) reference of a given cell (i,j,k), and a vertex number in a given face index.
  AlgVector GetCellFaceVertex (int index, int fi, int vi)
  {
    return GetCellFaceVertex(GetCell(index), fi, vi);
  }
  AlgVector GetCellFaceVertex (TopElement cell, int fi, int vi);
  /**
   * Obtains the cell's TOP, BASE, H and ZMED values.
   *
   * 'index' is the index of the cell on the grid.
   *
   * TOP is the average of the Z values of the 4 vertices of the top of the element.
   * BASE is the average of the Z values of the 4 vertices of the bottom of the element.
   * H is TOP - BASE.
   * ZMED is (TOP + BASE)/2.
   * DX is XMAX-XMIN.
   * DY is YMAX-YMIN.
   */
  void GetCellGeomProperties (int index,
                              float* top,
                              float* base,
                              float* h,
                              float* zmed,
                              float* xmin,
                              float* xmax,
                              float* ymin,
                              float* ymax,
                              float* zmin,
                              float* zmax,
                              float* dx,
                              float* dy);
  class AxisInvertedCB
  {
  public:
    virtual int GetTotalCellCount () = 0;
    virtual bool GetActiveCellVertices (int act_index, AlgVector vertices[5]) = 0;
  };
  class TopAxisInvertedCB : public AxisInvertedCB
  {
  public:
    virtual bool GetActiveCellAndAdjVertices (int act_index,
                                              int axis,
                                              AlgVector vertices[5],
                                              AlgVector adj_vertices[5],
                                              bool* skip_to_next_active_cell) = 0;
  };
  static bool AreElemAxesInverted (int j, int axis, AxisInvertedCB* cb);
  static bool IsTopAxisInverted (int j, int axis, TopAxisInvertedCB* cb);
  /**
  * Given the parent grid, builds refined geometry.
  */
  ResGrid* Refine (int nir,
                   int njr,
                   int nkr,
                   int starti,
                   int endi,
                   int startj,
                   int endj,
                   int startk,
                   int endk,
                   ResGrid* parent_grid,
                   bool refine_smooth_model,
                   bool cell_activity_already_set);
  /**
   * Removes the given refined grid.
   * Main grid is not allowed.
   */
  void RemoveRefinement (ResGrid* grid);
  /**
  * Were Z coordinates inverted?
  */
  bool WasZInverted ()
  {
    return d_z_inverted;
  }
  void ChildGeometryInserted();
  bool SetModelSmoothness(int mode);
  bool SaveGeometryFile (const char* filename,
                         float loader_version,
                         bool waitforcompletion);
  /**
   * Centraliza o modelo. Util para o modelo não possuir coordenadas
   * muito grandes (menos problemas de imprecisão de ponto flutuante).
   */
  void CenterModel ();
  static float GetSerializationVersion ();
  /**
   * Returns the index of the cell 'cell'.
   */
  int GetCellIndex (TopElement cell);
  /**
   * Obtains the indices 'i', 'j' and 'k' of a cell on its parent cell.
   */
  void GetCellIndices (int index, int* i, int *j, int *k) const;
  /**
   * Obtains the indices 'i', 'j' and 'k' of the root cell of a cell.
   */
  void GetRootGridCellIndices (int index, int* i, int *j, int *k) const;
  /**
   * Obtains the complete indices 'i', 'j' and 'k' of a cell.
   * 'levels' will contain the cell depth.
   * 'i', 'j' and 'k' will be sized '*levels', allocated with new[]. Their memory must
   * be released by the caller.
   */
  void GetCompleteCellIndices (int index, int* levels, int** i, int **j, int **k) const;
  /**
   * Obtains the cell at the given id.
   */
  TopElement GetCell (int id) const
  {
    return GetCell(m_top_model, id);
  }
  /**
   * Obtains the minimum and maximum coordinates of the cell of index 'i' of the main grid.
   * xmin, xmax, ymin, ... can be NULL (limits will be ignored).
   * The input values of *xmin, *xmax and so on are used in the comparisons.
   */
  void GetCellCoordsMinMax (unsigned int i,
                            float* xmin,
                            float* xmax,
                            float* ymin,
                            float* ymax,
                            float* zmin,
                            float* zmax);
  /**
   * Obtains the 8 coordinates of the cell with index 'index'.
   */
  void GetCellCoords (int index, AlgVector coords[8]);
  /**
   * Obtains, given the specified active cells, the default indirection for
   * properties, such that ind[allcellsindex] = activecellsindex if 'allcellsindex'
   * is active and ind[allcellsindex] = -1 if 'allcellsindex' is inactive.
   */
  const int* GetDefaultPropIndirection () const
  {
    return m_prop_ind.GetArrayConst();
  }
  /**
   * Returns true if the geometry is left-hand oriented.
   */
  bool IsLeftHandOriented () const
  {
    return m_left_hand;
  }
  /**
   * Obtains the root grid (parent=NULL).
   */
  ResGrid* GetRootGrid () const
  {
    return m_rootgrid;
  }
  /**
   * Returns a good initial z scale.
   */
  float GetInitialZScale () const
  {
    return m_ini_z_scale;
  }
  /**
   * Returns the maximum allowed z scale.
   */
  static float GetMaxZScale ()
  {
    return s_max_z_scale.Get();
  }
  /**
   * Specifies the number of expected refinement levels, where 1 = main grid only,
   * 2 = refinements of the main grid, 3 = refinements of refinements on the main grid,
   * and so on.
   */
  void SetNumberOfRefinementLevels (int numlevels)
  {
    m_refined_level_finished_original.Clear();
    m_refined_level_finished_smooth.Clear();
    m_refined_level_finished_original.ResizeAndSetConst(numlevels, false);
    m_refined_level_finished_smooth.ResizeAndSetConst(numlevels, false);
  }
  /**
   * Obtains the specified number of expected refinement levels, where 1 = main grid only,
   * 2 = refinements of the main grid, 3 = refinements of refinements on the main grid,
   * and so on.
   */
  int GetNumberOfRefinementLevels () const
  {
    return m_refined_level_finished_original.Size();
  }
  /**
   * Obtains the current maximum number of refinement levels supported (includes
   * level 0).
   */
  static int GetMaxNumberOfRefinementLevels ()
  {
    return 1 << TOP_ENTITY_LEVEL_BITS;
  }
  /**
   * Called after building a refinement level.
   *
   * 'smoothmodel' specifies if the smooth model must be updated if 'true', or the original
   * model if 'false'.
   *
   * 'func' is a progress monitoring callback that will be called if != NULL. 'data' will
   * be passed to it.
   */
  void FinishedBuildingLevel (bool                    smoothmodel,
                              int                     level,
                              UpdateSectionProgressCB func = NULL,
                              void*                   data = NULL);
  /**
   * Returns the unit of the used coordinate system.
   * Returns NULL if this unit is unknown.
   */
  const char* GetCoordinatesUnit () const
  {
    return m_coord_unit;
  }
  /**
   * Specifies the unit of the used coordinate system.
   * Specify NULL (or do not call) if unknown.
   */
  void SetCoordinatesUnit (const char* unit)
  {
    free(m_coord_unit);
    m_coord_unit = PSUtil::StrDup(unit);
  }
  /**
   * Prints useful statistics on memory consumption.
   */
  void PrintMemoryUsage ();
  /**
   * For internal use.
   */
  void AfterComputed (ResOpenOptions* options);
  DS_DEPRECATED int Nx () const { return Ni(); }
  DS_DEPRECATED int Ny () const { return Nj(); }
  DS_DEPRECATED int Nz () const { return Nk(); }
protected:
  void CorrectModelAxes (TopAxisInvertedCB* cb);
  /**
   * Inverts Z coordinates of all points.
   */
  void InvertZ ();
  /**
   * Obtains the index of vertex 'v' in the source geometry description (data source).
   */
  int GetOrigElemIncidence (int v) const
  {
    return m_orig_elem_inc[v];
  }
  /**
   * Insere um novo elemento ao modelo. Dado o i,j,k do elemento a ser inserido, e as coordenadas
   * dos oito vertices da celula e uma constante de toleracia, descobre se alguma celula vizinha (se existir)
   * possui algum vertice (no / node) dentro da tolerancia. Se existir, entao faz o colapso dos vertices e 
   * cria as incidencias de forma correta.
   */
  virtual bool InsertElem (TopMultiModel* model, int i, int j, int k, const float orig_vertex_list[24], float tolerance);
  /**
   * Inserts a new vertex in the model at internal position 'index'.
   * Returns true if successful (there was enough memory for the operation).
   */
  virtual bool InsertVertex (TopMultiModel* model, int index, float x, float y, float z);
  /**
   * Inserts the cell with indices 'i', 'j' and 'k', using previously inserted vertices of indices
   * 'vertex_indices[n]'.
   * Returns true if successful (there was enough memory for the operation).
   */
  virtual bool InsertCell (TopMultiModel* model, int i, int j, int k, const int orig_vertex_indices[8]);
  /**
   * Adiciona um ponto de celula aos volume envolventes do modelo.
   * Especifica se o ponto vem de celula ativa ou inativa.
   */
  void UpdateBoundingBoxes (float x, float y, float z, bool fromactivecell);
  void SetModel (bool smooth);
  void SetIds (UpdateSectionProgressCB func, void* data);
  void SetAdjacenciesOutdated (bool smoothmodel, int level)
  {
    if (smoothmodel)
      m_refined_level_finished_smooth.SetConst(level, false);
    else
      m_refined_level_finished_original.SetConst(level, false);
  }
private:
  /**
   * Build hierarchy for provided multi_model at specified layer.
   * @param multi_model model
   * @param only_act if true, only active cells are added.
   * @param layer if different from ALL_LAYERS, only cells on a given layer are added. Default is ALL_LAYERS.
   */
  TOP_INTERSECT* 
  BuildHierarchy (TopMultiModel* multi_model,
                  bool only_act = true,
                  int layer = ALL_LAYERS);
  void BuildSmoothModelHierarchy (UpdateSectionProgressCB progresscb,
                                  void* progresscbdata);
  void BuildModelHierarchy (TopMultiModel* model,
                            HierarchiesSet* h,
                            const char* progresscb_string,
                            UpdateSectionProgressCB progresscb,
                            void* progresscbdata);
  void ComputeInitialZScale ();
  int CountNumberOfRefinementLevels () const;
  void ReconstructSmoothRefinements (UpdateSectionProgressCB progressfunc,
                                     void*                   progressfuncdata);
  void SetElementIds (int nummodels, TopMultiModel** models);
  void SetNodeIds (int nummodels, TopMultiModel** models);
  TopElement GetCell (TopMultiModel* m, int id) const;
  /**
   * Obtains, given a multimodel and a cell id,
   * the associated TopElement and TopModel.
   * Returns true if cell was found, false otherwise.
   */
  bool GetElementAndModel (TopMultiModel* m,
                           int id,
                           TopElement* element,
                           TopModel** model) const;
  /**
   * Atribui ids (indexados a partir de 0) aos elementos e no's do modelo,
   * usando TopModel::SetId().
   */
  void SetIds (int nummodels, TopMultiModel** models);
  /**
   * Atribui ids (indexados a partir de 0) aos elementos e no's do modelo,
   * usando TopModel::SetId(). 'func', se diferente de NULL,
   * eh chamada para atualizar o progresso da operacao. 'data' eh passado
   * para 'func'.
   */
  void SetIds (int                     nummodels,
               TopMultiModel**         models,
               UpdateSectionProgressCB func,
               void*                   data);
private:
  struct ProgressData {
    float start;
    float multiplier;
    const char* section;
    UpdateSectionProgressCB origfunc;
    void* origdata;
  };
private:
  void SetElementIds (int nummodels, TopModel** models);
  void SetNodeIds (int nummodels, TopModel** models);
  bool IsLeftHandSystem(int j);
  bool AreElemAxesInverted (int j, int axis);
  bool SerializeGridHierarchy ();
  bool DeserializeGridHierarchy (IOStream* stream);
  bool SerializeBVsHierarchy ();
  bool DeserializeBVsHierarchy (IOStream* stream);
  bool SerializeModelHierarchy (HierarchiesSet* h);
  bool DeserializeModelHierarchy (IOStream* stream,
                                  TopMultiModel* model,
                                  HierarchiesSet* h);
  bool SerializeIntersect (TOP_INTERSECT* inter);
  bool DeserializeIntersect (TOP_INTERSECT** inter,
                             IOStream* stream, 
                             TopMultiModel* model);
  bool SerializeDefaultPropertyIndirection ();
  bool DeserializeDefaultPropertyIndirection (IOStream* stream);
  static void ProgressFunction (const char* section, float progress, void* data);
private:
  ResGrid* m_rootgrid;
  DsArray<bool> m_active_cells;
  DsArray<int> m_prop_ind;
  DsArray<int> m_refined_level_finished_original;
  DsArray<int> m_refined_level_finished_smooth;
  IOCompBinFileStream* m_write_stream;
  char* m_coord_unit;
  int m_num_cells_root;
  int m_orig_elem_inc[8];
  bool m_left_hand;
  bool m_valid;
  bool m_refinements_must_be_removable;
  bool m_zdir_down;
private:
  friend class ResModelNew;
};

#endif
