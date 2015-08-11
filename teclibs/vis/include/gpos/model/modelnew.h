// Projeto GereSim
// Grupo de Visualizacao
//
// fabraham@tecgraf.puc-rio.br
// celes@tecgraf.puc-rio.br
//
// Tecgraf/PUC-Rio
#ifndef RES_MODEL_NEW_H
#define RES_MODEL_NEW_H

#include <gpos/defines.h>
#include <gpos/io/open.h>
#include <alg/vector.h>

class ResModel;
class TopModel;
class TopElement;

class ResModelNew
{
public:
  /**
   * At program exit function.
   * Guarantees all resources are freed and all auxiliary threads end.
   */
  static void AtExit ();
  /**
   * Increases model reference counter.
   */
  void IncRef ();
  /**
   * Decreases model reference counter. When 0 is reached, object is deleted.
   */
  void DecRef ();
  // general methods
  const char* GetName () const;
  // simulation methods
  /**
   * Obtains the result's simulation title.
   */
  const char* GetSimulationTitle () const;
  /**
   * Obtains the result's initial date.
   */
  const char* GetInitialDate ();
  /**
   * Does model have recorded grid data?
   */
  bool HasGridData () const;
  /**
   * Does model have recorded well data?
   */
  bool HasWellData () const;
  /**
   * Returns the grid coordinates unit.
   */
  const char* GetGridCoordsUnit () const;
  /**
   * Returns the number of recorded grid time steps.
   */
  int GetGridTimeStepCount ();
  /**
   * Obtains information about the grid time step of index 'index',
   * returning them in the following pointers:\n
   * *ndays: number of days passed since the first time step.\n
   * *day:   day number.\n
   * *month: month number.\n
   * *year:  year number.\n
   *
   * Requisites:
   * - 0 <= index < GetTimeStepCount()
   */
  void GetGridTimeStep (int index,
                        double* ndays,
                        int* day,
                        int* month,
                        int* year);
  /**
   * Returns the number of recorded well time steps.
   */
  int GetWellTimeStepCount ();
  /**
   * Obtains information about the well time step of index 'index',
   * returning them in the following pointers:\n
   * *ndays: number of days passed since the first time step.\n
   * *day:   day number.\n
   * *month: month number.\n
   * *year:  year number.\n
   *
   * Requisites:
   * - 0 <= index < GetTimeStepCount()
   */
  void GetWellTimeStep (int index,
                        double* ndays,
                        int* day,
                        int* month,
                        int* year);
  int GetWellClosestTimeStep (int mapts);
  /**
   * Obtains the value associated to an undefined grid value.
   */
  float GetGridNullValue () const;
  /**
   * Obtains the value associated to an undefined well value.
   */
  float GetWellNullValue () const;
  // Grid methods
  int GetGridCompleteDimension () const
  {
    assert(m_grid_comp_dim >= 0);
    return m_grid_comp_dim;
  }
  int GetGridPackedDimension () const
  {
    assert(m_grid_packed_dim >= 0);
    return m_grid_packed_dim;
  }
  // Grid property methods
  int GetGridPropCount () const;
  const char* GetGridPropName (int prop) const;
  const char* GetGridPropDesc (int prop) const;
  /**
   * Obtains a string identifying the unit of property 'prop'.
   * Returns NULL if no string is associated with property.
   */
  const char* GetGridPropUnit (int prop) const;
  int GetGridPropByName (const char* name) const;
  bool IsGridPropSingle (int prop) const;
  bool IsGridPropComplete (int prop) const;
  /**
   * Obtains the minimum value of property 'prop' in all time steps.
   */
  float GetGridPropMin (int prop) const;
  /**
   * Obtains the maximum value of property 'prop' in all time steps.
   */
  float GetGridPropMax (int prop) const;
  bool LoadGridIniProp (int prop_id, float* data);
  bool LoadGridRecProp (int prop_id, int ts, float* data);
  float GetGridInitialZScale () const;
  /**
   * Transforms a coordinate from local model coordinates to original model coordinates.
   */
  void GridTransformToOriginalCoords (double* x, double* y, double* z) const;
  /**
   * Transforms a coordinate from original model coordinates to local model coordinates.
   */
  void GridTransformToLocalCoords (double* x, double* y, double* z) const;
  /**
   * Is the model grid corner points (true)? Or block centered (false) ?
   */
  bool IsGridCornerPoints () const;
  bool IsGridZDown () const;
  bool IsGridKDown () const;
  bool SetGridSmooth (bool f);
  float GetGridXmin () const
  {
    return m_bb_xmin;
  }
  float GetGridXmax () const
  {
    return m_bb_xmax;
  }
  float GetGridYmin () const
  {
    return m_bb_ymin;
  }
  float GetGridYmax () const
  {
    return m_bb_ymax;
  }
  float GetGridZmin () const
  {
    return m_bb_zmin;
  }
  float GetGridZmax () const
  {
    return m_bb_zmax;
  }
  float GetGridActXmin () const
  {
    return m_act_bb_xmin;
  }
  float GetGridActXmax () const
  {
    return m_act_bb_xmax;
  }
  float GetGridActYmin () const
  {
    return m_act_bb_ymin;
  }
  float GetGridActYmax () const
  {
    return m_act_bb_ymax;
  }
  float GetGridActZmin () const
  {
    return m_act_bb_zmin;
  }
  float GetGridActZmax () const
  {
    return m_act_bb_zmax;
  }
  float GetGridOrigXmin () const
  {
    return m_orig_bb_xmin;
  }
  float GetGridOrigXmax () const
  {
    return m_orig_bb_xmax;
  }
  float GetGridOrigYmin () const
  {
    return m_orig_bb_ymin;
  }
  float GetGridOrigYmax () const
  {
    return m_orig_bb_ymax;
  }
  float GetGridOrigZmin () const
  {
    return m_orig_bb_zmin;
  }
  float GetGridOrigZmax () const
  {
    return m_orig_act_bb_zmax;
  }
  float GetGridOrigActXmin () const
  {
    return m_orig_act_bb_xmin;
  }
  float GetGridOrigActXmax () const
  {
    return m_orig_act_bb_xmax;
  }
  float GetGridOrigActYmin () const
  {
    return m_orig_act_bb_ymin;
  }
  float GetGridOrigActYmax () const
  {
    return m_orig_act_bb_ymax;
  }
  float GetGridOrigActZmin () const
  {
    return m_orig_act_bb_zmin;
  }
  float GetGridOrigActZmax () const
  {
    return m_orig_act_bb_zmax;
  }
  int GetGridRootNi () const;
  int GetGridRootNj () const;
  int GetGridRootNk () const;
  float GetGridRootAvgCellWidth ();
  int GetGridRootCellIndex (int i, int j, int k);
  bool WasGridZInverted () const;
  bool IsGridInactiveZCorrect () const;
  bool IsGridRadial () const;
  float GetGridRW () const;
  void GetGridCellCompleteIndices (int cell, int* level_count, int** i, int** j, int** k);
  /**
   * Obtains the indices 'i', 'j' and 'k' of the root cell of a cell.
   */
  void GetGridCellRootIndices (int cell, int* i, int *j, int *k);
  int GetGridCellCount () const;
  int GetGridActiveCellCount () const;
  /**
   * Obtains the activity status of grid cells.
   * active[c] = true  means the cell with index 'c' is active.
   * active[c] = false means the cell with index 'c' is inactive.
   */
  const bool* GetGridCellActivity () const;
  /**
   * Obtains the packed indices of grid cells.
   * indices[c] = p means 'p' is the packed index for the cell with index 'c'.
   * indices[c] = -1 means 'c' is an inactive cell.
   */
  const int* GetGridCellPackedIndices () const;
  bool IsGridCellActive (int cell) const;
  void GetGridCellCoords (int cell, AlgVector coords[8]);
  AlgVector GetGridCellCenterPoint (int cell, int face = -1);
  AlgVector GetGridCellDiagonal (int cell);
  /**
   * Obtains the total number of vertices (nodes) in the model.
   */
  int GetGridVertexCount ();
  /**
   * Obtains the index of the 'vi'th vertex of cell 'cell'.
   */
  int GetGridCellVertex (int cell, int vi);
  /**
   * Obtains the coordinates of the vertex with index 'vertex'.
   */
  AlgVector GetGridVertexPosition (int vertex);
  /**
   * Obtains, in case the cell 'cell' has an adjacent cell through the face 'fi',
   * the index of the adjacent cell. Returns -1 if there is no adjacent cell.
   * 
   * The following assertion is valid:
   *
   * static int face_index_on_adj_elem[6] = { 1, 0, 3, 2, 5, 4 };
   * for all c:
   *   for (int fi=0; fi<6; ++fi) {
   *     int adj = GetGridNeighborCell(c, fi);
   *     assert(adj == GetGridNeighborCell(adj, face_index_on_adj_elem[fi]));
   *   }
   */
  int GetGridNeighborCell (int cell, int fi);
  // Well methods
  /**
   * Obtains the number of wells in this result.
   */
  int GetWellCount () const;
  const char* GetWellName (int well) const;
  int GetWellByName (const char* name) const;
  /**
   * Obtains the type of well 'well' at the time step of index 'ts'.
   */
  ResWellType GetWellType (int well, int ts) const;
  /**
   * Obtains the name of the parent group of the well 'well'
   * at the time step of index 'stepindex'.
   * If returns NULL, assumes the default group.
   */
  const char* GetWellGroup (int well, int stepindex) const;
  /**
   * Obtains a good value to use as well radius in 3D windows.
   */
  float GetWellsRadius () const;

  /**
   * Get well's completions for a given link.
   * A link is only considered between valid completions.
   * @param well well identifier.
   * @param link_id link id.
   * @param c1 completion at one link extremity (return value).
   * @param c2 completion at the other link extremity (return value).
   * @return whether link id is valid (inside range of valid completions).
   * NOTE: c1 and c2 not changed when returning false.
   */
  bool GetWellLink (int well, 
                    int link_id, 
                    int* c1, 
                    int* c2);

  /**
   * Calculates intersections between the link 'link_id' of well 'well' and the
   * reservoir active cells.
   * Intersection values are returned through parameters 'tmin[i]' and
   * 'tmax[i]' (0 <= i < cell_count), assuming 0.0 is at the position of active
   * completion 'link_id' and 1.0 is at the position of active completion
   * 'link_id+1'.
   * 'tmin' and 'tmax' are in ascending order: 'tmin[i]'<'tmin[i+1]' and
   * 'tmax[i]'<'tmax[i+1]'.
   * Note that not necessarily 'tmax[i]' equals 'tmin[i+1]', since intersection
   * is calculated exclusively with active cells and there can be holes in the
   * interior of the reservoir.
   * cells_id[i] indicates the intersected cell's id at tmin[i] and tmax[i].
   * @return number of intersections.
   */
  int GetWellLinkCrossedCells (int well, 
                               int link_id, 
                               const float** tmin, 
                               const float** tmax, 
                               const int** cell_ids,
                               bool force = false) const;

  /**
  * Calculates intersections between the link 'link_id' of well 'well' with
  * a real trajectory and the reservoir active cells.
  * Intersection values are returned through parameters 'tmin[i]' and
  * 'tmax[i]' (0 <= i < cell_count), assuming 0.0 is at the position of entry 
  * point in cell and 1.0 is at the exit point of the cell.
  * 'tmin' and 'tmax' are in ascending order: 'tmin[i]'<'tmin[i+1]' and
  * 'tmax[i]'<'tmax[i+1]'.
  * Note that not necessarily 'tmax[i]' equals 'tmin[i+1]', since intersection
  * is calculated exclusively with active cells and there can be holes in the
  * interior of the reservoir.
  * cells_id[i] indicates the intersected cell's id at tmin[i] and tmax[i].
  * @return number of intersections.
  */
  int GetWellTrajSegmentCrossedCells (int well, 
                                      int link_id, 
                                      const float** tmin, 
                                      const float** tmax, 
                                      const int** cell_ids,
                                      bool force) const;
  /**
   * Calculates intersections between the reservoir active cells and the
   * segment linking the first completion of well 'well_name' and the top
   * of the reservoir bounding box.
   * Intersection values are returned through parameters 'tmin[i]' and
   * 'tmax[i]' (0 <= i < cell_count), assuming 0.0 is at the position of active
   * completion 'link_id' and 1.0 is at the position of active completion
   * 'link_id+1'.
   * 'tmin' and 'tmax' are in ascending order: 'tmin[i]'<'tmin[i+1]' and
   * 'tmax[i]'<'tmax[i+1]'.
   * Note that not necessarily 'tmax[i]' equals 'tmin[i+1]', since intersection
   * is calculated exclusively with active cells and there can be holes in the
   * interior of the reservoir.
   * cells_id[i] indicates the intersected cell's id at tmin[i] and tmax[i].
   * @return number of intersections.
   */
  int GetWellToTopCrossedCells (int well, 
                                const float** tmin, 
                                const float** tmax, 
                                const int** cell_ids,
                                bool force = false) const;

  struct CrossedCells
  {
    int interval_count;
    const float* tmin;
    const float* tmax;
    const int* cell_ids;
    float* cell_props;
    ~CrossedCells ()
    {
      free(cell_props);
    }
  };
  struct NumCoreData
  {
    int comp_count;      /**< Completions count.                               */
    float* comp;         /**< Completion position along well (0..1).           */
    int inters_count;    /**< intersections count.                             */
    int* cell_ids;       /**< array with inters_count cell ids.                */
    float* start;        /**< array with inters_count intersect. start (0..1). */
    float* lengths;      /**< array with inters_count lengths.                 */
    int steps_count;     /**< time steps count.                                */
    float** props;       /**< steps_count arrays with inters_count prop values.*/
    ~NumCoreData ()
    {
      free(comp);
      free(cell_ids);
      free(lengths);
      free(start);
      for (int t = 0; t < steps_count; t++)
        free(props[t]);
      free(props);
    }
  };
  /**
   * Calculates intersections between the reservoir active cells and the
   * segment linking the first completion of well 'well_name' and the top
   * of the reservoir bounding box, storing the property values at a given
   * time step.
   *
   * If any intersections were found, the return is not NULL and holds the
   * following information:
   * 
   * 'interval_count' intersections are returned through parameters 'tmin[i]'
   * and 'tmax[i]' (0 <= i < interval_count), assuming 0.0 is at the position
   * of active completion 'link_id' and 1.0 is at the position of active
   * completion 'link_id+1'.
   * 'tmin' and 'tmax' are in ascending order: 'tmin[i]'<'tmin[i+1]' and
   * 'tmax[i]'<'tmax[i+1]'.
   * Note that not necessarily 'tmax[i]' equals 'tmin[i+1]', since intersection
   * is calculated exclusively with active cells and there can be holes in the
   * interior of the reservoir.
   * cells_id[i] indicates the intersected cell's id at tmin[i] and tmax[i].
   * cell_props[i] indicates the value of the given property at the intersected
   * cell.
   */
  CrossedCells* GetWellToTopIntersections (const char* well_name, 
                                           const char* grid_prop, 
                                           int step_index);
  /**
   * Same as above, but receives the well index rather than the well name.
   */
  CrossedCells* GetWellToTopIntersections (int well, 
                                           const char* grid_prop, 
                                           int step_index);
  /**
   * Calculates intersections between the links of well 'well_name' and the reservoir
   * active cells, storing the property values at a given time step.
   *
   * An array with size 'link_count' is returned. For each link, if any intersections were found,
   * ret[link_index] is different than NULL and holds the following information:
   * 
   * 'interval_count' intersections are returned through parameters 'tmin[i]' and
   * 'tmax[i]' (0 <= i < interval_count), assuming 0.0 is at the position of active
   * completion 'link_id' and 1.0 is at the position of active completion
   * 'link_id+1'.
   * 'tmin' and 'tmax' are in ascending order: 'tmin[i]'<'tmin[i+1]' and
   * 'tmax[i]'<'tmax[i+1]'.
   * Note that not necessarily 'tmax[i]' equals 'tmin[i+1]', since intersection
   * is calculated exclusively with active cells and there can be holes in the
   * interior of the reservoir.
   * cells_id[i] indicates the intersected cell's id at tmin[i] and tmax[i].
   * cell_props[i] indicates the value of the given property at the intersected cell.
   */
  DsArray<CrossedCells*>* GetWellLinksIntersections (const char* well_name, 
                                                     const char* grid_prop, 
                                                     int step_index);
  /**
   * Same as above, but receives the well index rather than the well name.
   */
  DsArray<CrossedCells*>* GetWellLinksIntersections (int well, 
                                                     const char* grid_prop, 
                                                     int step_index);

  /**
  * Calculates intersections between the segments of well 'well_name' with real trajectory
  * and the reservoir active cells, storing the property values at a given time step.
  *
  * An array with size 'segment_count' is returned. For each link, if any intersections were found,
  * ret[link_index] is different than NULL and holds the following information:
  * 
  * 'interval_count' intersections are returned through parameters 'tmin[i]' and
  * 'tmax[i]' (0 <= i < interval_count), assuming 0.0 is at the position of entry point
  * for active completion cell and 1.0 is at the position of exit point for active completion
  * cell.
  * 'tmin' and 'tmax' are in ascending order: 'tmin[i]'<'tmin[i+1]' and
  * 'tmax[i]'<'tmax[i+1]'.
  * Note that not necessarily 'tmax[i]' equals 'tmin[i+1]', since intersection
  * is calculated exclusively with active cells and there can be holes in the
  * interior of the reservoir.
  * cells_id[i] indicates the intersected cell's id at tmin[i] and tmax[i].
  * cell_props[i] indicates the value of the given property at the intersected cell.
  */
  DsArray<ResModelNew::CrossedCells*>* GetWellTrajSegmentIntersections (const char* well_name, 
                                                                        const char* grid_prop, 
                                                                        int step_index);

  /**
  * Same as above, but receives the well index rather than the well name.
  */
  DsArray<ResModelNew::CrossedCells*>* GetWellTrajSegmentIntersections (int well, 
                                                                        const char* grid_prop, 
                                                                        int step_index);
  /**
   * Calculates intersections between the links of well 'well_name' and the reservoir
   * active cells, storing the property 'grid_prop' values at a given time step.
   *
   * 'inters_count' intersections are returned through parameter 'length[i]'
   * (0 <= i < inters_count), assuming 0.0 is at the position of the first 
   * active completion and 1.0 is at the position of the last active completion.
   * 'lengths' is in ascending order: 'length[i]'<'length[i+1]'.
   * cells_id[i] indicates the intersected cell's id at length[i].
   * props is a pointer with step_indices.Size() positions;
   * props[t] is an array to inters_count values of the given property
   * at the intersection.
   * NOTE an inactive cell will have property value = RES_NULL_VALUE.
   * NOTE grid_prop must be a recurrent property (not initial/single)
   */
  NumCoreData* GetNumCoreData (const char* well_name, 
                               const char* grid_prop, 
                               DsArray<int>& step_indices);
  /**
   * Same as above, but receives a single time step.
   */
  NumCoreData* GetNumCoreData (const char* well_name, 
                               const char* grid_prop, 
                               int step_index);
  /**
   * Same as above, but receives the well index rather than the well name.
   */
  NumCoreData* GetNumCoreData (int well, 
                               const char* grid_prop, 
                               DsArray<int>& step_indices);
  /**
   * Same as above, but receives a single time step.
   */
  NumCoreData* GetNumCoreData (int well, 
                               const char* grid_prop, 
                               int step_index);
  float GetWellTopZDisplacement () const;
  /**
   * Fetch well's z-top coordinate.
   */
  float GetWellZTop (int well) const;
  /**
  * Fetch first layer id in which well top
  * coordinate belongs to.
  */
  int GetWellCellIdTop (int well) const;
  AlgVector ProjectToBBTop (const AlgVector& point) const;
  int GetCompCount (int well);
  /**
   * Obtains the completion flow to index:
   * 'well': well identifier.
   * 'comp': comp on the well's completion list.
   *
   * Returns the comp of the completion into which the fluid flows.
   *
   * Requisites:
   * - 0 <= comp < GetCompletionCount(well)
   */
  //TODO: not yet implemented
  //int GetCompFlowToIndex (int well, int comp);
  void GetCompRootGridPosition (int well, int comp, int* pi, int* pj, int* pk);
  int GetCompGridCell (int well, int comp);
  AlgVector GetCompPosition (int well, int comp);
  /**
   * Obtains well trajectory data: entry and exit points and perforation length.
   * Returns true if this data is available, false otherwise.
   */
  bool GetCompTrajectory (int well,
                          int comp,
                          AlgVector* o_entry,
                          AlgVector* o_exit,
                          float* o_perf_length);
  /**
   * Informs if completion has trajectory data.
   * Returns true if this data is available, false otherwise.
   */
  bool HasCompTrajectory (int well, int comp) const;
  const char* GetCompName (int well, int comp) const;
  // Group methods
  int GetGroupCount () const;
  const char* GetGroupName (int group) const;
  int GetGroupByName (const char* name) const;
  // Region methods
  int GetRegionCount () const;
  const char* GetRegionName (int region) const;
  int GetRegionByName (const char* name) const;
  // Well Property methods
  int GetWellPropCount () const;
  const char* GetWellPropName (int prop) const;
  int GetWellPropByName (const char* name) const;
  /**
   * Informs if well 'well' has well property 'prop' recorded for at least
   * one time step.
   */
  bool HasWellProp (int prop, int well);
  /**
   * Informs which time steps are recorded for well property 'prop', well 'well'.
   * Returns true if successful or false if failed fetching this data.
   */
  bool GetWellPropRecordedSteps (int prop, int well, bool* has_recorded_steps);
  bool LoadWellProp (int prop, int well);
  float GetWellPropMin (int prop, int well);
  float GetWellPropMax (int prop, int well);
  float GetWellPropValue (int prop, int well, int t);
  void UnloadWellProp (int prop, int well);
  // Completion property methods
  int GetCompPropCount () const;
  const char* GetCompPropName (int prop) const;
  const char* GetCompPropDesc (int prop) const;
  int GetCompPropByName (const char* name) const;
  /**
   * Informs if the completion 'comp' of well 'well' has completion property
   * 'prop' recorded for at least one time step.
   */
  bool HasCompProp (int prop, int well, int comp);
  /**
   * Informs which time steps are recorded for completion property 'prop', well 'well'
   * and completion index 'comp_index'.
   * Returns true if successful or false if failed fetching this data.
   */
  bool GetCompPropRecordedSteps (int prop, int well, int comp_index, bool* has_recorded_steps);
  bool LoadCompProp (int prop, int well, int comp);
  float GetCompPropMin (int prop, int well, int comp);
  float GetCompPropMax (int prop, int well, int comp);
  float GetCompPropValue (int prop, int well, int comp, int t);
  void UnloadCompProp (int prop, int well, int comp);
  // Group property methods
  int GetGroupPropCount () const;
  const char* GetGroupPropName (int prop) const;
  const char* GetGroupPropDesc (int prop) const;
  int GetGroupPropByName (const char* name) const;
  /**
   * Informs if group 'group' has group property 'prop' recorded for at least
   * one time step.
   */
  bool HasGroupProp (int prop, int group);
  /**
   * Informs which time steps are recorded for group property 'prop', group 'group'.
   * Returns true if successful or false if failed fetching this data.
   */
  bool GetGroupPropRecordedSteps (int prop, int group, bool* has_recorded_steps);
  bool LoadGroupProp (int prop, int group);
  float GetGroupPropMin (int prop, int group);
  float GetGroupPropMax (int prop, int group);
  float GetGroupPropValue (int prop, int group, int t);
  void UnloadGroupProp (int prop, int group);
  // Region property methods
  int GetRegionPropCount () const;
  const char* GetRegionPropName (int prop) const;
  const char* GetRegionPropDesc (int prop) const;
  int GetRegionPropByName (const char* name) const;
  /**
   * Informs that region 'region' has region property 'prop' recorded for at least
   * one time step.
   */
  bool HasRegionProp (int prop, int region);
  /**
   * Informs which time steps are recorded for region property 'prop', region 'region'.
   * Returns true if successful or false if failed fetching this data.
   */
  bool GetRegionPropRecordedSteps (int prop, int region, bool* has_recorded_steps);
  bool LoadRegionProp (int prop, int region);
  float GetRegionPropMin (int prop, int region);
  float GetRegionPropMax (int prop, int region);
  float GetRegionPropValue (int prop, int region, int t);
  void UnloadRegionProp (int prop, int region);
  // Field property methods
  int GetFieldPropCount () const;
  const char* GetFieldPropName (int prop) const;
  const char* GetFieldPropDesc (int prop) const;
  int GetFieldPropByName (const char* name) const;
  /**
   * Informs which time steps are recorded for field property 'prop'.
   * Returns true if successful or false if failed fetching this data.
   */
  bool GetFieldPropRecordedSteps (int prop, bool* has_recorded_steps);
  bool LoadFieldProp (int prop);
  float GetFieldPropMin (int prop);
  float GetFieldPropMax (int prop);
  float GetFieldPropValue (int prop, int t);
  void UnloadFieldProp (int prop);
  // System methods
  void AfterLoad (ResOpenOptions* options);
  ResModel* GetModel () const
  {
    return m_mdl;
  }
  void SetGridCompleteDimension (int d)
  {
    m_grid_comp_dim = d;
  }
  void SetGridPackedDimension (int d)
  {
    m_grid_packed_dim = d;
  }
  /**
   * Specifies the value to be associated to an undefined grid value.
   */
  void SetWellNullValue (float v);
  /**
   * Specifies the value to be associated to an undefined well value.
   */
  void SetGridNullValue (float v);
protected:
  virtual ~ResModelNew ();
private:
  /**
   * Constructs the new API object.
   * For now, receives the ResModel pointer.
   */
  ResModelNew (ResModel* mdl);
  void GetElementAndModel (int cell,
                           TopElement* element,
                           TopModel** model);
private:
  ResModel* m_mdl;
  float m_bb_xmin;
  float m_bb_xmax;
  float m_bb_ymin;
  float m_bb_ymax;
  float m_bb_zmin;
  float m_bb_zmax;
  float m_act_bb_xmin;
  float m_act_bb_xmax;
  float m_act_bb_ymin;
  float m_act_bb_ymax;
  float m_act_bb_zmin;
  float m_act_bb_zmax;
  float m_orig_bb_xmin;
  float m_orig_bb_xmax;
  float m_orig_bb_ymin;
  float m_orig_bb_ymax;
  float m_orig_bb_zmin;
  float m_orig_bb_zmax;
  float m_orig_act_bb_xmin;
  float m_orig_act_bb_xmax;
  float m_orig_act_bb_ymin;
  float m_orig_act_bb_ymax;
  float m_orig_act_bb_zmin;
  float m_orig_act_bb_zmax;
  int m_grid_comp_dim;
  int m_grid_packed_dim;
private:
  friend class ResModel;
  friend class ResPosModelNew;
};

#endif

