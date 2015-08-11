// Projeto GereSim
// Grupo de Visualizacao
//
// cpalomo@tecgraf.puc-rio.br
// @date 02/02/2011
//
// Tecgraf/PUC-Rio
//
// Centralizes methods for calculation and processing of intersections
// between well and reservoir.

#ifndef RES_WELL_INTERSECTION_H
#define RES_WELL_INTERSECTION_H

#include <ds/array.h>
#include <gpos/defines.h>
#include "modelnew.h"

class WellIntersection
{
public:
  /**
   * Calculates intersections between the reservoir active cells and the
   * segment linking the first completion of a well and the top
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
  static ResModelNew::CrossedCells*
    GetWellToTopIntersections (ResModelNew* mdlnew,
                               int well, 
                               const char* grid_prop, 
                               int step_index);

  /**
   * Calculates intersections between the links of a well and the reservoir
   * active cells, storing the property values at a given time step.
   *
   * An array with size 'link_count' is returned. For each link, if any 
   * intersections were found, ret[link_index] is different than NULL and 
   * holds the following information:
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
  static DsArray<ResModelNew::CrossedCells*>*
    GetWellLinksIntersections (ResModelNew* mdlnew, 
                               int well,
                               const char* grid_prop, 
                               int step_index);

  /**
  * Calculates intersections between the segments of well with real
  * trajectory and the reservoir active cells, storing the property 
  * values at a given time step.
  *
  * An array with size 'segment_count' is returned. For each segment, if any 
  * intersections were found, ret[segment_index] is different than NULL and 
  * holds the following information:
  * 
  * 'interval_count' intersections are returned through parameters 'tmin[i]'
  * and 'tmax[i]' (0 <= i < interval_count), assuming 0.0 is at first entry
  * of active completion cell and 1.0 is at the position of exit of active
  * completion cell.
  * 'tmin' and 'tmax' are in ascending order: 'tmin[i]'<'tmin[i+1]' and
  * 'tmax[i]'<'tmax[i+1]'.
  * Note that not necessarily 'tmax[i]' equals 'tmin[i+1]', since intersection
  * is calculated exclusively with active cells and there can be holes in the
  * interior of the reservoir.
  * cells_id[i] indicates the intersected cell's id at tmin[i] and tmax[i].
  * cell_props[i] indicates the value of the given property at the intersected
  * cell.
  */
  static DsArray<ResModelNew::CrossedCells*>*
    GetWellTrajSegmentIntersections (ResModelNew* mdl,
                                     int well, 
                                     const char* grid_prop, 
                                     int step_index);
  
  /**
   * Calculates intersections between the links of a well and the reservoir
   * active cells, storing the property 'grid_prop' values at given time steps.
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
  static ResModelNew::NumCoreData*
    GetNumCoreData (ResModelNew* mdlnew,
                    int well, 
                    const char* grid_prop, 
                    DsArray<int>& step_indices);
};

#endif  // RES_WELL_INTERSECTION_H

