// Projeto GereSim
// Grupo de Visualizacao
//
// fabraham@tecgraf.puc-rio.br
// celes@tecgraf.puc-rio.br
//
// Tecgraf/PUC-Rio
#ifndef RES_POS_MODEL_NEW_H
#define RES_POS_MODEL_NEW_H

#include "modelnew.h"

class ResPosModel;

class ResPosModelNew : public ResModelNew
{
public:
  ResPosModel* GetPosModel () const
  {
    return (ResPosModel*)GetModel();
  }
  // methods that should be called by any loaders 
  /**
   * Specifies the simulation title. Can be called more than once: only first call will apply.
   */
  void SetSimulationTitle (const char *title);
  /** Specifies the initial date.
   *
   */
  void SetInitialDate (const char* date);
  // methods that should be called by well result loaders 
  /**
   * Specifies the value to be associated to an undefined grid value.
   */
  void SetWellNullValue (float v)
  {
    ResModelNew::SetWellNullValue(v);
  }
  void CreateWellTimeStep (double ndays, int day, int month, int year);
  void CreateField ();
  void CreateGroup (const char* name);
  void CreateRegion (const char* name);
  int CreateWell (const char* name);
  void SetWellGroup (int well, int ts, const char* group);
  void SetWellLGRName (int well, const char* lgrname);
  void SetWellType (int well, ResWellType type, int ts);
  int AddWellComp (int well,
                   int depth,
                   const int* is,
                   const int* js,
                   const int* ks);
  void SetCompTrajectory (int well,
                          int comp, 
                          const AlgVector& entry,
                          const AlgVector& exit,
                          float perf_length);
  void CreateWellProperty (const char* name,
                           const char* desc,
                           ResValueType vtype,
                           const char* unit);
  void CreateCompProperty (const char* name,
                           const char* desc,
                           ResValueType vtype,
                           const char* unit);
  void CreateGroupProperty (const char* name,
                            const char* desc,
                            ResValueType vtype,
                            const char* unit);
  void CreateRegionProperty (const char* name,
                             const char* desc,
                             ResValueType vtype,
                             const char* unit);
  void CreateFieldProperty (const char* name,
                            const char* desc,
                            ResValueType vtype,
                            const char* unit);
  /**
   * Informs that well 'well' has well property 'prop' recorded for at least
   * one time step.
   */
  void SetWellHasProperty (int well, const char* prop);
  /**
   * Informs that the completion 'comp' of well 'well' has completion property
   * 'prop' recorded for at least one time step.
   */
  void SetCompHasProperty (int well, int comp, const char* prop);
  /**
   * Informs that group 'group' has group property 'prop' recorded for at least
   * one time step.
   */
  void SetGroupHasProperty (int group, const char* prop);
  /**
   * Informs that region 'region' has region property 'prop' recorded for at least
   * one time step.
   */
  void SetRegionHasProperty (int region, const char* prop);
  // methods that should be called by map result loaders 
  /**
   * Specifies the value to be associated to an undefined grid value.
   */
  void SetGridNullValue (float v)
  {
    ResModelNew::SetGridNullValue(v);
  }
  void SetGridCompleteDimension (int d)
  {
    ResModelNew::SetGridCompleteDimension(d);
  }
  void SetGridPackedDimension (int d)
  {
    ResModelNew::SetGridPackedDimension(d);
  }
  void CreateGridTimeStep (double ndays, int day, int month, int year);
  void CreateGridIniProp (const char* symbol,
                          const char* desc,
                          ResValueType dtype,
                          const char* unit,
                          bool iscomplete);
  void CreateGridRecProp (const char* symbol,
                          const char* desc,
                          ResValueType dtype,
                          const char* unit);
  // methods that should be called by geometry loaders 
  /**
   * Informs that the geometry is radial. Coordinates will be assumed to be cylindric parametric
   * coords: 'x' + radial_rw is the radius, 'y' is the theta angle (in degrees) and 'z' is 'z'.
   */
  void SetGridRadial (float radial_rw);
  /**
   * Specifies the grid data.
   * 'ni, nj, nk':       root grid dimensions
   * 'active_cells':     array with 'num_active' grid cell indices 'c', according to the
   *                     convention used by the res library. Indices must be ordered,
   *                     e.g. if i < j, then active_cells[i] < active_cells[j].
   * 'indirection':      array with 'num_active' indices, where if, indirection[p] = c,
   *                     then non-complete properties loaded with LoadIniProperty/LoadRecProperty
   *                     will have data[p] corresponding to the grid cell with index 'c',
   *                     'c' being the index according to the convention of the res library.
   * 'is_corner_points': informs if the geometry is defined by its corner points or if it is a
   *                     block-centered geometry.
   * 'are_inactive_z_correct': informs if the z coordinates of inactive cells are defined.
   * 'zdirdown':               informs if the grid is zdir=DOWN (true) or zdir=UP (false).
   * 'kdirdown':               informs if the grid is kdir=DOWN (true) or kdir=UP (false).
   * 'coords_unit':            specifies the unit of the used coordinate system.
   *                           'NULL' is accepted if this unit is unknown.
   */
  void SetGridData (int ni,
                    int nj,
                    int nk,
                    const int* active_cells,
                    const int* indirection,
                    bool is_corner_points,
                    bool are_inactive_z_correct,
                    bool zdirdown,
                    bool kdirdown,
                    const char* coords_unit);
  /**
   * Refines a cell.
   *
   * 'depth': refinement depth 1 if the cell belongs to the main grid, 2 if on
   *          the first refinement level and so on.
   * 'i, j, k': 'i', 'j' and 'k' coordinates of the cell to be refined: i[l], j[l]
   *            and k[l] are the i, j, k coordinates of the cell on the refinement
   *            level 'l-1' where l ranges from 0 (main grid) until 'depth-1'.
   * 'refinement_indices': refinement_indices[l] is the index of the refinement
   *                       containing the cell coordinates i[l], j[l] and k[l].
   * nri, nrj, nrk:        number of parts in the 'i', 'j' and 'k' directions
   *                       to split the specified cell.
   */
  void AddGridCellRefinement (int depth,
                              const int* i,
                              const int* j,
                              const int* k,
                              const int* refinement_indices,
                              int nri,
                              int nrj,
                              int nrk);
  /**
   * Refines a range of cells in the main grid.
   *
   * rootistart, rootiend: range of cells to be refined in the 'i' direction, inclusive.
   * rootjstart, rootjend: range of cells to be refined in the 'j' direction, inclusive.
   * rootkstart, rootkend: range of cells to be refined in the 'k' direction, inclusive.
   * nri, nrj, nrk:        number of parts in the 'i', 'j' and 'k' directions
   *                       to split each cell.
   */
  void AddGridRangeRefinement (int rootistart,
                               int rootiend,
                               int rootjstart,
                               int rootjend,
                               int rootkstart,
                               int rootkend,
                               int nri,
                               int nrj,
                               int nrk);
  // utility methods
  /**
   * Specifies that all wells have well property 'prop' recorded for at
   * least one time step.
   */
  void SetPropertyPresentOnAllWells (const char* prop);
  /**
   * Informs that all completions of all wells have completion property
   * 'prop' recorded for at least one time step.
   */
  void SetPropertyPresentOnAllCompletions (const char* prop);
  /**
   * Specifies that all groups have group property 'prop' recorded for at
   * least one time step.
   */
  void SetPropertyPresentOnAllGroups (const char* prop);
  /**
   * Specifies that all regions have region property 'prop' recorded for at
   * least one time step.
   */
  void SetPropertyPresentOnAllRegions (const char* prop);
  /**
   * Obtains the index of this model in the loader's list (see ResPosLoaderNew::LoadHeader).
   */
  int GetLoaderIndex () const;
private:
  /**
   * Constructs the new API object.
   * For now, receives the ResPosModel pointer.
   */
  ResPosModelNew (ResPosModel* mdl);
private:
  friend class ResPosModel;
};

#endif

