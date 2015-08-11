//* completion.h
// A viewable reservoir completion.
// Tecgraf/PUC-Rio
// Jan 2004

#ifndef vis_completion_h
#define vis_completion_h

#include <ds/hash.h>
#include <gpos/common/util.h>
#include <gpos/model/geometry.h>
#include <gpos/defines.h>
#include <tops/model.h>

class ResModel;
class ResStep;
class ResWell;
class ResPosElementPropertyData;

class RES_API ResCompletionPosition
{
public:
  ResCompletionPosition (int grid_depth, const int* is, const int *js, const int *ks, bool base1=false)
  {
    SetPosition(grid_depth, is, js, ks, base1);
  }
  ResCompletionPosition (ResGeometry* geom, int cellindex)
  : m_pos(NULL)
  {
    SetPosition(geom, cellindex);
  }
  ResCompletionPosition (ResCompletionPosition* src)
  {
    m_grid_depth = src->m_grid_depth;
    m_pos = new int[3*m_grid_depth];
    memcpy(m_pos,src->m_pos,3*m_grid_depth*sizeof(int));
  }
  ~ResCompletionPosition ()
  {
    delete [] m_pos;
  }
  int GetGridDepth () const
  {
    return m_grid_depth;
  }
  void SetPosition (int depth, int i, int j, int k)
  {
    m_pos[3*depth  ] = i;
    m_pos[3*depth+1] = j;
    m_pos[3*depth+2] = k;
  }
  void SetPosition (ResGeometry* geom, int cellindex)
  {
    if (m_pos == NULL)
      delete m_pos;
    int grid_depth, *is, *js, *ks;
    geom->GetCompleteCellIndices(cellindex, &grid_depth, &is, &js, &ks);
    SetPosition(grid_depth, is, js, ks);
    delete [] is;
    delete [] js;
    delete [] ks;
  }
  void GetPosition (int depth, int *i, int *j, int *k) const
  {
    *i = m_pos[3*depth  ];
    *j = m_pos[3*depth+1];
    *k = m_pos[3*depth+2];
  }
private:
  void SetPosition (int grid_depth, const int* is, const int *js, const int *ks, bool base1=false)
  {
    m_grid_depth = grid_depth;
    m_pos = new int[3*grid_depth];
    int pos = 0;
    int base_correction = base1 ? -1 : 0;
    for (int l=0; l<grid_depth; ++l) {
      m_pos[pos++] = is[l] + base_correction;
      m_pos[pos++] = js[l] + base_correction;
      m_pos[pos++] = ks[l] + base_correction;
    }
  }
private:
  int m_grid_depth;
  int* m_pos;
};

//* 'ResCompletion' Class
// Represents a well completion suitable for viewing.
class RES_API ResCompletion
{
public:
  static TopElement GetCell (ResGeometry* geom, ResCompletionPosition* pos);
  static bool HasCell (ResGeometry* geom, ResCompletionPosition* pos)
  {
    return GetCell(geom,pos).IsValid();
  }
  void Release();
  /**
   * Specifies the completion cell coordinates.
   */
  void SetPosition (ResCompletionPosition* pos);
  /**
   * Obtains the completion cell coordinates.
   */
  ResCompletionPosition* GetPosition () const
  {
    return m_pos;
  }
  /**
   * Obtains the cell in which this completion lies.
   */
  TopElement GetCell ();
  /**
   * Obtains the completion's cell index.
   */
  int GetCellIndex ();
  /**
   * Obtains the root cell's position in the main grid.
   */
  void GetRootGridPosition (int *i, int *j, int *k)
  {
    m_pos->GetPosition(0, i, j, k);
  }
  /**
   * Specifies well trajectory information for this well.
   */
  void SetTrajectory (const AlgVector& entry,
                      const AlgVector& exit,
                      float perf_length);
  /**
   * Informs if completion has trajectory data.
   * Returns true if the information is available, false otherwise.
   */
  bool HasTrajectory () const
  {
    return m_trajectory != NULL;
  }
  /**
   * Obtains well trajectory information associated to this completion.
   * Returns false if the information is not available.
   */
  bool GetTrajectory (AlgVector* o_entry,
                      AlgVector* o_exit,
                      float* o_perf_length);
    //* Well query
    // Returns the well this completion belongs to.
  virtual ResWell * GetWell() = 0;

  virtual const char* GetName () 
  {
    int depth = m_pos->GetGridDepth();
    int i, j, k;
    m_pos->GetPosition(depth, &i, &j, &k);
    static char s[4096];
    s[0] = 0;
    sprintf(s,"%d:%d:%d",i, j, k);
    return s;
  }
  
    //* Property data load
    // Loads (if necessary) the data of the given property.
    // Returns the data loaded or NULL in case of an error.
  ResPosElementPropertyData * LoadPropertyData(const char *name);

    //* Property data unload
    // Unloads the data of the given property.
  void UnloadPropertyData(const char *name);

  /**
   * Informs if this completion has completion property 'name' recorded for at
   * least one time step.
   */
  virtual bool HasPropertyData (const char* name) = 0;

  /**
   * Informs which time steps are recorded for completion property 'name'.
   * Returns true if successful or false if failed fetching this data.
   */
  virtual bool PropHasRecordedSteps (const char* name, bool* has_recorded_steps) = 0;

		//* Reference count query
		// Returns the current number of references to the given property
	int GetRefCount(const char *name);

protected:
  /**
   * Constructor.
   * 'mdl' is the model of this completion.
   * 'pos' is the completion cell position.
   */
	ResCompletion (ResModel *mdl, ResCompletionPosition* pos);
  virtual ~ResCompletion();
  /**
   * Obtains the model associated with this completion.
   */
  ResModel* GetModel () const
  {
    return m_mdl;
  }
  // effectively load property data
  virtual ResPosElementPropertyData * doLoadPropertyData(const char *name) = 0;
  virtual void doUnloadPropertyData(const char *name) = 0;
private:
  void SaveCell ();
private:
  struct Trajectory
  {
    AlgVector entry;
    AlgVector exit;
    float perf_length;
  };
  DsHash<PSUtil::StringKey, int> m_refcount;
	ResModel *m_mdl;
  ResCompletionPosition* m_pos;
  Trajectory* m_trajectory;
  TopElement m_cell;
  bool m_cell_validated;
};

#endif

