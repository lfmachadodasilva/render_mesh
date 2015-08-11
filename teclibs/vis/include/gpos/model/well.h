//* well.h
// A viewable reservoir well.
// Tecgraf/PUC-Rio
// Jan 2004

#ifndef vis_well_h
#define vis_well_h

#include <ds/hash.h>
#include <gpos/common/util.h>
#include <gpos/model/model.h>
#include <gpos/defines.h>

class ResModel;
class ResCompletion;
class ResStep;
class ResPosElementPropertyData;

//* 'ResWell' Class
// Represents a reservoir well suitable for viewing.
class RES_API ResWell
{
public:
private:
  DsHash<PSUtil::StringKey, int> m_refcount;
protected:
	ResModel *m_mdl;
  ResWell(ResModel *mdl);
  virtual ~ResWell();
public:
    //* Reference counting routines

    // Releases the element, unloading all properties that
    // are still referenced
	void Release();

  /**
   * Returns the position of this well in the root model,
   * so that model->GetWellAt(position) returns this well.
   * Returns -1 in case this well is not found in the model.
   */
  int GetPositionInRootModel();

    //* Name query
    // Returns the well name.
  virtual const char * GetName () const = 0;

    //* LGRName query
    //  Returns name of well lgr
  virtual const char * GetLGRName () const 
  {
    return "";
  }
  /**
   * Obtains the name of the parent group of the well
   * at the time step of index 'stepindex'.
   * If returns NULL, assumes the default group.
   */
  virtual const char* GetGroup (int stepindex) const
  {
    return NULL;
  }
  /**
   * Obtains the well type (see ResWellType) on the time step of index 'ts'.
   */
  ResWellType GetType (int ts) const
  {
    if (m_type.ValidIndex(ts))
      return m_type[ts];
    else
      return RES_WELL_UNDEFINED;
  }
    //* Name config
    // Sets the name of the well
  virtual void SetName(const char * name) = 0;

    //* Amount of completions query
    // Returns the number of completions.
  virtual int GetNumberOfCompletions() const = 0;

    //* Completion query
    // Returns the ith completion.
  virtual ResCompletion * GetCompletion(int i) = 0;

    //* Well radius query
    // Returns the radius of the well in world units, along each axis.
  void GetRadius(float *i, float *j, float *k)
  {
    return m_mdl->GetWellsRadius(i,j,k);
  }

  /**
   * Informs if this well has well property 'name' recorded for at least one
   * time step.
   */
  virtual bool HasPropertyData (const char* name) = 0;

  /**
   * Informs which time steps are recorded for well property 'name'.
   * Returns true if successful or false if failed fetching this data.
   */
  virtual bool PropHasRecordedSteps (const char* name, bool* has_recorded_steps) = 0;

    //* Property data load
    // Loads (if necessary) the data of the given property.
    // Returns the data loaded or NULL in case of an error.
  ResPosElementPropertyData * LoadPropertyData(const char *name);

    //* Property data unload
    // Unloads the data of the given property.
  void UnloadPropertyData(const char *name);

		//* Reference count query
		// Returns the current number of references to the given property
	int GetRefCount(const char *name);
  /**
   * Sets the well type (see ResWellType) for the time step of index 'ts'.
   */
  void SetType (int ts, ResWellType type)
  {
    if (!m_type.ValidIndex(ts))
      m_type.ResizeAndSetConst(ts+1, RES_WELL_UNDEFINED);
    m_type[ts] = type;
  }
  /**
   * Invert completions order
   */
  virtual void InvertCompletionOrder() = 0;

  /**
   * Get well's completions for a given link.
   * A link is only considered between valid completions.
   * @param link_id link id.
   * @param c1 index of the completion at one link extremity (return value).
   * @param c2 index of the completion at the other link extremity (return value).
   * @return whether link id is valid (inside range of valid completions).
   * NOTE: c1 and c2 not changed when returning false.
   */
  bool GetLink (int link_id, int* c1, int* c2);

  /**
  * Get well segments for a given link of its real trajectory.
  * A segment is only considered belonging to an active completion or in between
  * these segments.
  * @param comp_from first completion
  * @param comp_to second completion
  * @param coord_from list of first coordinates belonging to the segment.
  * @param coord_to list of second coordinates belonging to the segment.
  * @param seg_factors indicates a portion of the link each segment occupies [0.0, 1.0].
  * @param cellIds only for segments that are inside cells with defined completions.
  * @param n number of segments.
  * @return whether segment id is valid (inside range of valid completions).
  * NOTE: coord_from and coord_to not changed when returning false.
  */
  bool GetTrajLinkSegments (int comp_from, 
                            int comp_to, 
                            AlgVector** coord_from, 
                            AlgVector** coord_to, 
                            float** seg_factors,
                            int** cellIds,
                            int* n);

  /**
   * Calculates intersections between the well link 'link_id' and the reservoir
   * active cells.
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
  int GetCrossedCells (int link_id, 
                       const float** tmin, 
                       const float** tmax, 
                       const int** cells_ids,
                       bool force = false);

  /**
  * Calculates intersections between the well with a real trajectory geometry 
  * segment 'segment_id' and the reservoir active cells.
  * Intersection values are returned through parameters 'tmin[i]' and
  * 'tmax[i]' (0 <= i < cell_count), assuming 0.0 is at the position of active
  * completion 'link_id' and 1.0 is at the position of the next segment of the
  * trajectory 'segment_id+1'.
  * 'tmin' and 'tmax' are in ascending order: 'tmin[i]'<'tmin[i+1]' and
  * 'tmax[i]'<'tmax[i+1]'.
  * Note that not necessarily 'tmax[i]' equals 'tmin[i+1]', since intersection
  * is calculated exclusively with active cells and there can be holes in the
  * interior of the reservoir.
  * cells_id[i] indicates the intersected cell's id at tmin[i] and tmax[i].
  * @return number of intersections.
  */
  int GetCrossedCellsTraj (int link_id,
                           const float** tmin,
                           const float** tmax,
                           const int** cells_ids,
                           bool force);

  /**
   * Calculates intersections between the well's first completion and the reservoir
   * top (active cells bounding box zmin).
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
   * res_z_top the top Z coordinate for reservoir
   * @return number of intersections.
   */
  int GetToTopCrossedCells (const float** tmin, 
                            const float** tmax, 
                            const int** cells_ids,
                            float res_z_top,
                            bool force = false);

  /**
   * Update well's z-top coordinate.
   */
  void SetZTop (float z)
  {
    m_z_top = z;
  }
  /**
   * Fetch well's z-top coordinate.
   */
  float GetZTop () const
  {
    return m_z_top;
  }
  /**
  * Fetch first layer id in which well top
  * coordinate belongs to.
  */
  int GetCellIdTop () const
  {
    if (m_cell_id_top < 0) {
      printf("RES: GetCellIdTop called without SetCellIdTop being called.\n");
      return 0;
    }
    return m_cell_id_top;
  }

protected:
  // effectively load property data
  virtual ResPosElementPropertyData * doLoadPropertyData(const char *name) = 0;
  virtual void doUnloadPropertyData(const char *name) = 0;
private:
  /**
   * Update first layer id in which well top
   * coordinate belongs to.
   */
  void SetCellIdTop (int id) 
  {
    assert(id >= 0);
    m_cell_id_top = id;
  }
private:
  struct IntersectResult
  {
    float* tmin;
    float* tmax;
    int* cells_ids;
    int n;
  };
private:
  DsArray<IntersectResult*> m_link_intersections;
  DsArray<IntersectResult*> m_segment_intersections;
  IntersectResult* m_to_top_intersections;
  DsArray<ResWellType> m_type;
  float m_z_top;
  int m_cell_id_top;
};

#endif

