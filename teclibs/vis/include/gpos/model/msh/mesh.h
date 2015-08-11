// mesh.h
// GERESIM
// Tecgraf/PUC-Rio
// Jun 2004

#ifndef ps_mesh_h
#define ps_mesh_h

extern "C" {
#include <lua.h>
#include <lauxlib.h>
}

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <gpos/model/model.h>
#include <gpos/model/modelnew.h>
#include <gpos/model/property.h>
#include <gpos/model/well.h>
#include <gpos/model/completion.h>
#include <gpos/model/step.h>
#include <gpos/model/geometry.h>
#include <ds/hash.h>

#define RES_MSH_NULL_VALUE 97654321.0f

class MshGrid;
class MshGeometry;
class MshArray;
class MshProperty;
class ResMshModel;
struct LuaProgressCallback;

typedef int lua_Object;

///////////////////////////////////////////////////// MshModel
class MshModel
{
private:
  lua_State* m_L;
  DsArray<MshGrid*> m_grid;
  int m_refcount;
public:
  MshModel ();
  ~MshModel ();
  MshGrid* GetGrid (int i=0)
  {
    assert(m_grid.ValidIndex(i));
    return m_grid.Get(i);
  }
  void AddGrid (MshGrid* grid, int at=-1)
  {
    m_grid.Insert(grid, at);
  }
  bool RemoveGrid (MshGrid* grid);
  int GetNumberOfGrids () const
  {
    return m_grid.Size();
  }
  void AddRef()
  {
    m_refcount++;
  }
  void Release();
private:
  void Resize (int n)
  {
    m_grid.Resize(n);
  }
};

///////////////////////////////////////////////////// MshGrid
class MshGrid
{
  lua_State *m_L;
  lua_Object m_ref;
  int m_ni, m_nj, m_nk;
  int m_nir, m_njr, m_nkr;
  DsArray<MshProperty*> m_prop;
  MshGeometry* m_geom;

  int m_range[6]; // range of refinement: [0] = start i,[1] = start j,[2] = start k
                  //                      [3] = End i,  [4] = End j,  [5] = End k
public:
  MshGrid (lua_State *L, lua_Object lo);
  ~MshGrid ();
  lua_State* GetLuaState () const
  {
    return m_L;
  }
  void PushTable () const
  {
    lua_getref(m_L, m_ref);
  }
  void SetGeometry (MshGeometry* geom);
  void AddProperty (MshProperty* prop);
  MshProperty* RemoveProperty (const DsStringKey& name);
  MshProperty* RemoveProperty (const char* name)
  {
    DsStringKey n(name);
    return RemoveProperty(n);
  }
  void SetParent (MshGrid* grid)
  {
    m_parent = grid;
  }
  MshGrid* GetParent () const
  {
    return m_parent;
  }
  bool HasParent () const
  {
    return m_parent != NULL;
  }
  int GetDepth () const;
  void SetResGrid (ResGrid* grid)
  {
    m_resgrid = grid;
  }
  ResGrid* GetResGrid () const
  {
    return m_resgrid;
  }
  int GetNumberOfProperties() const { return m_prop.Size(); }
  int GetNi () const {  return m_ni; }
  int GetNj () const {  return m_nj; }
  int GetNk () const {  return m_nk; }
  int GetNumCells () const
  {
    return GetNi() * GetNj() * GetNk();
  }
  int GetNir () const {  return m_nir; }
  int GetNjr () const {  return m_njr; }
  int GetNkr () const {  return m_nkr; }
  void GetRange (int& starti,
                 int& startj,
                 int& startk,
                 int& endi,
                 int& endj,
                 int& endk) const
  {
    starti = m_range[0];
    endi = m_range[1];
    startj = m_range[2];
    endj = m_range[3];
    startk = m_range[4];
    endk = m_range[5];
  }
  MshGeometry* GetGeometry ();
  MshProperty* GetProperty (int i);
  MshProperty* GetProperty (const DsStringKey& name);
  MshProperty* GetProperty (const char* name)
  {
    DsStringKey n(name);
    return GetProperty(n);
  }
  int Index (int i, int j, int k) const
  {
    return RES_LINEAR_INDEX(i, j, k, m_ni, m_nj, m_nk);
  }
  void ReverseIndex (int index, int* i, int* j, int* k) const
  {
    ResReverseIndex(index, m_ni, m_nj, m_nk, i, j, k);
  }
  void SetOffset (int offset)
  {
    m_offset = offset;
  }
  int GetOffset () const
  {
    return m_offset;
  }
  /**
   * Returns the cell's index in the entire model (including all grids).
   */
  int GetCellIndex (int i, int j, int k) const
  {
    return GetCellIndex(Index(i,j,k));
  }
  int GetCellIndex (int index) const
  {
    return GetOffset() + index;
  }
  int GetLocalIndex (int cellindex) const
  {
    return cellindex - m_offset;
  }
  /**
   * Is the cell with index 'cellindex' on the entire model on this grid?
   */
  bool IsCellOnGrid (int cellindex) const
  {
    cellindex = GetLocalIndex(cellindex);
    return 0 <= cellindex && cellindex < m_ni*m_nj*m_nk;
  }
  void GetGridCellIndices (int cellindex, int* i, int* j, int* k) const
  {
    int gi, gj, gk;
    int index = GetLocalIndex(cellindex);
    ReverseIndex(index, &gi, &gj, &gk);
    *i = gi % m_nir;
    *j = gj % m_njr;
    *k = gk % m_nkr;
  }
  void GetParentCellIndices (int i, int j, int k, int* pi, int* pj, int* pk) const
  {
    *pi = (i / m_nir) + m_range[0];
    *pj = (j / m_njr) + m_range[2];
    *pk = (k / m_nkr) + m_range[4];
  }
private:
  void Resize (int n);
private:
  DsHash<DsStringKey, int> m_prop_indices;
  MshGrid* m_parent;
  ResGrid* m_resgrid;
  int m_offset;
};

///////////////////////////////////////////////////// MshGeometry
class MshGeometry
{
protected:
  MshGrid* m_grid;
  bool m_kdown;
  bool m_iscornerpoints;
  MshGeometry (MshGrid* grid, bool kdown, bool iscornerpoints);
public:
  bool IsCornerPoints ()
  {
    return m_iscornerpoints;
  }
  bool IskDown ()
  {
    return m_kdown;
  }
  virtual ~MshGeometry ();
  virtual void GetCoord (int i, int j, int k, float x[8], float y[8], float z[8]) = 0;
};

///////////////////////////////////////////////////// MshBlockCenter
class MshBlockCentered : public MshGeometry
{
protected:
  MshArray* m_di;
  MshArray* m_dj;
  MshArray* m_dk;

public:
  MshBlockCentered (MshGrid* grid, MshArray* di, MshArray* dj, MshArray* dk, bool kdown, bool accumd = true);
  ~MshBlockCentered ();
};


///////////////////////////////////////////////////// MshBlockCenteredDTop
class MshBlockCenteredDTop : public MshBlockCentered
{
  MshArray *m_dtop;
public:
  MshBlockCenteredDTop(MshGrid* grid, MshArray* di, MshArray* dj, MshArray* dk, MshArray* dtop, bool kdown);

  ~MshBlockCenteredDTop();

  void GetCoord (int i, int j, int k, float x[8], float y[8], float z[8]);
};


///////////////////////////////////////////////////// MshBlockCenteredPayDepth
class MshBlockCenteredPayDepth : public MshBlockCentered
{
  MshArray *m_paydepth;
public:
  MshBlockCenteredPayDepth(MshGrid* grid, MshArray* di, MshArray* dj, MshArray* dk, MshArray* paydepth, bool kdown);

  ~MshBlockCenteredPayDepth();

  void GetCoord (int i, int j, int k, float x[8], float y[8], float z[8]);
};

///////////////////////////////////////////////////// MshBlockCenteredDepth
class MshBlockCenteredDepth : public MshBlockCentered
{
  int m_refi, m_refj, m_refk;
  bool m_refcenter;
  float m_depth;
public:
  MshBlockCenteredDepth(MshGrid* grid, MshArray* di, MshArray* dj, MshArray* dk, int i, int j, int k, bool refcenter, float depth, bool kdown);

  ~MshBlockCenteredDepth();

  void GetCoord (int i, int j, int k, float x[8], float y[8], float z[8]);
};

///////////////////////////////////////////////////// MshCornerPoints
class MshCornerPoints : public MshGeometry
{
  const char *m_filenameerror;
  bool m_fileexists;
  int m_nread;
  int m_nexpected;
protected:
  void SetErrorFilename (const char *filename, bool fileexists=true, int nread=0, int nexpected=0)
  {
    m_filenameerror = filename;
    m_fileexists = fileexists;
    m_nread = nread;
    m_nexpected = nexpected;
  }
  MshCornerPoints (MshGrid* grid, bool kdown, bool iscornerpoints) :
    MshGeometry(grid,kdown,iscornerpoints),
    m_filenameerror(NULL)
  {
  }
public:
  virtual ~MshCornerPoints()
  {
  }
  const char *ErrorFilename (bool *fileexists=NULL, int *nread=NULL, int *nexpected=NULL) const
  {
    if (m_filenameerror)
    {
      if (fileexists)
        *fileexists = m_fileexists;
      if (nread)
        *nread = m_nread;
      if (nexpected)
        *nexpected = m_nexpected;
    }
    return m_filenameerror;
  }
};

///////////////////////////////////////////////////// MshCornerPointsZCorn
class MshCornerPointsZCorn : public MshCornerPoints
{
  float *m_coord;
  float *m_zcorn;
public:
  MshCornerPointsZCorn(MshGrid* grid, const char *coord, const char *zcorn, bool kdown, int progressfunction=-1);
  virtual ~MshCornerPointsZCorn();

  void GetCoord (int i, int j, int k, float x[8], float y[8], float z[8]);
};

///////////////////////////////////////////////////// MshCornerPointsDIDJZCorn
class MshCornerPointsDIDJZCorn : public MshCornerPoints
{
  MshArray* m_di;
  MshArray* m_dj;
  float *m_zcorn;
public:
  MshCornerPointsDIDJZCorn(MshGrid* grid, MshArray *di, MshArray *dj, const char *zcorn, bool kdown, int progressfunction=-1);
  virtual ~MshCornerPointsDIDJZCorn();

  void GetCoord (int i, int j, int k, float x[8], float y[8], float z[8]);
};

///////////////////////////////////////////////////// MshCornerPointsCorners
class MshCornerPointsCorners : public MshCornerPoints
{
  float *m_corners;
public:
  MshCornerPointsCorners(MshGrid* grid, const char *corners, bool kdown, int progressfunction=-1);
  virtual ~MshCornerPointsCorners();

  void GetCoord (int i, int j, int k, float x[8], float y[8], float z[8]);
};

///////////////////////////////////////////////////// MshArray
class MshArray
{
protected:
  lua_State    * m_L;
  MshGrid      * m_grid;
  DsArray<float> m_value;
  int            m_ref;
  float          m_min;
  float          m_max;

  void update_minmax();

public:
  MshArray          ( MshGrid* grid, lua_Object lo );
  virtual ~MshArray ();
  bool Load ();
  void Unload ();
  bool IsLoaded () const;
  float GetValue (int i, int j, int k) const
  {
    return GetValue(m_grid->Index( i, j, k ));
  }

  float GetValue (int index) const
  {
    assert(m_value.ValidIndex(index));
    return m_value.Get(index);
  }

 float GetMin() { return m_min; }
 float GetMax() { return m_max; }

 MshGrid * GetGrid() { return m_grid; }

 void ApplyModifiers();

 void AccumulateX();
 void AccumulateY();
 void AccumulateZ();
  bool IsConstant (float* pconstantvalue);
  virtual bool SaveINC (const char *filename);
private:
  virtual int LoadValues () = 0;
};

///////////////////////////////////////////////////// MshArrayConst
class MshArrayConst : public MshArray
{
public:
  MshArrayConst (MshGrid* grid, lua_Object lo)
    : MshArray(grid, lo)
  {
  }

  ~MshArrayConst() { }

private:
  int LoadValues();
};

///////////////////////////////////////////////////// MshArrayAll
class MshArrayAll : public MshArray
{
public:
  MshArrayAll(MshGrid* grid, lua_Object lo)
    : MshArray(grid, lo)
  {
  }

  ~MshArrayAll() { }

private:
  bool SaveINC (const char *filename);
  int LoadValues();
};

///////////////////////////////////////////////////// MshArrayIVar
class MshArrayIVar : public MshArray
{
public:
  MshArrayIVar(MshGrid *grid, lua_Object lo)
    : MshArray(grid, lo)
  {
  }

  ~MshArrayIVar() { };

private:
  int LoadValues();
};

///////////////////////////////////////////////////// MshArrayJVar
class MshArrayJVar : public MshArray
{
public:
  MshArrayJVar(MshGrid *grid, lua_Object lo)
    : MshArray(grid, lo)
  {
  }

  ~MshArrayJVar() { };

private:
  int LoadValues();
};

///////////////////////////////////////////////////// MshArrayKVar
class MshArrayKVar : public MshArray
{
public:
  MshArrayKVar(MshGrid *grid, lua_Object lo)
    : MshArray(grid, lo)
  {
  }

  ~MshArrayKVar() { };

private:
  int LoadValues();
};

///////////////////////////////////////////////////// MshArrayIJK
class MshArrayIJK : public MshArray
{
  float m_defvalue;
public:
  MshArrayIJK(MshGrid *grid, lua_Object lo, float defvalue = 0.0f)
    : MshArray(grid, lo), m_defvalue(defvalue)
  {
  }

  ~MshArrayIJK() { };

private:
  int LoadValues();
};

///////////////////////////////////////////////////// MshArrayIJVar
class MshArrayIJVar : public MshArray
{
public:
  MshArrayIJVar(MshGrid *grid, lua_Object lo)
    : MshArray(grid, lo)
  {
  }

  ~MshArrayIJVar() { };

private:
  int LoadValues();
};

// A MshArray that is a proxy to a ResProperty.
class MshProxyArray : public MshArray
{
public:
  MshProxyArray (ResProperty* prop, MshGrid* grid, lua_Object lo)
  : MshArray(grid, lo)
  , m_prop(prop)
  {
  }
  ~MshProxyArray ()
  {
  }
private:
  int LoadValues ();
private:
  ResProperty* m_prop;
};

// A MshArray that is a proxy to a ResProperty.
class MshInheritArray : public MshArray
{
public:
  MshInheritArray (MshGrid* grid, const char* propname, lua_Object lo)
  : MshArray(grid, lo)
  , m_propname(propname)
  {
  }
  ~MshInheritArray ()
  {
  }
private:
  int LoadValues ();
private:
  DsStringKey m_propname;
};

///////////////////////////////////////////////////// MshProperty
class MshProperty
{
  char *m_name;
  MshArray *m_array;
public:
  MshProperty (const char *name, MshArray *array)
  : m_array(array)
  {
    m_name = strdup(name);
  }
  ~MshProperty()
  {
    free(m_name);
    delete m_array;
  }
  bool Load()
  {
    return m_array->Load();
  }
  void Unload()
  {
    m_array->Unload();
  }
  MshArray * GetArray() { return m_array; }
  const char *GetName() { return m_name; }
  float GetValue(int i, int j, int k)
  {
    return m_array->GetValue(i,j,k);
  }
  float GetValue(int index)
  {
    return m_array->GetValue(index);
  }
  bool IsLoaded () const
  {
    return m_array->IsLoaded();
  }
  bool IsConstant (float* pconstantvalue)
  {
    return m_array->IsConstant(pconstantvalue);
  }
  bool SaveINC (const char *filename)
  {
    return m_array->SaveINC(filename);
  }
};

/////////////////////// Wrapper classes for the 'ResModel' architecture

class ResMshStep : public ResStep
{
public:
  ResMshStep()
  {
    SetNumber(0);
  }
  double GetNumberOfDays() const { return 0.0; }
  int GetDay() const { return 1; }
  int GetMonth() const { return 1; }
  int GetYear() const { return 1980; }
};

class ResMshProperty : public ResProperty
{
  ResMshModel *m_mdl;
public:
  ResMshProperty (ResMshModel *mdl, const char* name);
  void GridHierarchyChanged ()
  {
    ForceReloadIfNeeded();
  }
  void PropertyModifierListChanged ()
  {
    ForceReloadIfNeeded();
  }
  bool IsInitial() { return true; }
  bool IsComplete () const
  {
    return true;
  }
  const char * GetSymbol() const
  {
    return m_name;
  }
  const char * GetUnit() const { return ""; }
  const char * GetDescription() const { return "MSH PROPERTY"; }

  float GetMinValue();
  float GetMaxValue();

  float GetNull() const { return RES_MSH_NULL_VALUE; } // TODO: what should I place here?
  
  int GetNumberOfStepsLoaded() { return 1; }

  float GetValue (int index);

  void GetValues (float *buf, int bufsize[], int slice[]);
protected:
  ~ResMshProperty ();
  int doLoad (const ResStep *t)
  {
    return DoLoad();
  }
  int doUnLoad (const ResStep *t)
  {
    return DoUnload();
  }
  bool UpdateMinMax ();
private:
  bool DoLoad ();
  bool DoUnload ();
  void ForceReloadIfNeeded ();
private:
  DsStringKey m_name;
  float m_min;
  float m_max;
  float* m_values;
};

class ResMshGeometry : public ResGeometry
{
  void CorrectModelAxes (MshGeometry* geom);
  /**
  * Carrega o modelo se for cornerpoint
  */
  void LoadCornerPoints(MshGeometry* geom);

  /**
  * Carrega o modelo se for bloco centrado
  */
  void LoadBlockCenter(MshGeometry* geom);

public:
  ResMshGeometry(ResModel *model, int nx, int ny, int nz, bool isCornerPoint)
  : ResGeometry(model, nx, ny, nz, nx*ny*nz, nx*ny*nz, true)
  , m_isCornerPoint(isCornerPoint)
  , m_initial_fault(-1)
  , m_kdown(false)
  {
    d_imode = GRD_INTERPOLATED;
    SetInactiveCorrect(true);
  }
  ~ResMshGeometry() {};
  void SetNact(int nact) { d_nact = nact; }
  void SetProgressCB (ProgressCB progresscb, void *progresscbdata)
  {
    d_progresscb = progresscb;
    d_progresscbdata = progresscbdata;
  }
  void UpdateProgress(const char *sectionname, float progress)
  {
    if (d_progresscb)
      d_progresscb(sectionname,progress,d_progresscbdata);
  }
  void FinishedBuildingLevel (bool smoothmodel, int level)
  {
    ResGeometry::FinishedBuildingLevel(smoothmodel,
                                       level,
                                       d_progresscb,
                                       d_progresscbdata);
  }
  void AfterChange (double fault=-1.0);
  void UpdateIndirection ();
  virtual bool IsCornerPoints ()
  {
    return m_isCornerPoint;
  }
  int ComputeMainGridCells (MshGeometry* geom);
  void SetVerticalGap (double fault);
  virtual bool IsKDown () const
  {
    return m_kdown;
  }
protected:
private:
  static void UpdateProgressCB (const char *sectionname, float progress, void* data)
  {
    ResMshGeometry* geom = (ResMshGeometry*)data;
    geom->UpdateProgress(sectionname, progress);
  }
private:
  bool m_isCornerPoint;
  float m_initial_fault;
  void (*d_progresscb)(const char*,float,void*);
  void *d_progresscbdata;
  bool m_kdown;
};

class ResMshCompletion : public ResCompletion
{
  ResWell *m_well;
public:
  ResMshCompletion(ResModel *mdl, ResWell *well, ResCompletionPosition *pos);
  virtual ~ResMshCompletion()
  {
  }
    //* Well query
    // Returns the well this completion belongs to.
  ResWell * GetWell() { return m_well; }
protected:
  // virtual methods
  ResPosElementPropertyData * doLoadPropertyData(const char *name) { return 0; }
  void doUnloadPropertyData(const char *name) {};
  bool HasPropertyData (const char* name)
  {
    return false;
  }
  bool PropHasRecordedSteps (const char* name, bool* has_recorded_steps)
  {
    return false;
  }
};

class ResMshWell : public ResWell
{
  PSArray<ResMshCompletion*> m_comps;
  char *m_name;

public:
  ResMshWell(ResModel *mdl, const char *name);

  ~ResMshWell();

  void AddCompletion(ResMshCompletion *comp, int at=-1) { m_comps.insert(comp, at); }

  // removes ith completion from its current position and reinserts it at dst
  // shifting remaining completions ahead
  void MoveCompletion(int i, int dst);

  void RemoveCompletion(int i);

  void SetName(const char *name);

  const char * GetName() const { return m_name; }

  int GetNumberOfCompletions() const { return m_comps.size(); }

  ResCompletion * GetCompletion(int i) { return m_comps[i]; }

  void InvertCompletionOrder();

  bool SwapCompletionsOrder(int compidx_1, int compidx_2);
  // virtual methods
  bool HasPropertyData (const char* name)
  {
    return false;
  }
  bool PropHasRecordedSteps (const char* name, bool* has_recorded_steps)
  {
    return false;
  }
protected:
  // effectively load property data
  ResPosElementPropertyData * doLoadPropertyData(const char *name) { return 0; }
  void doUnloadPropertyData(const char *name) {};

};

class ResMshActivenessInfo
{
public:
  ResMshActivenessInfo(ResModel *mdl) : m_mdl(mdl), m_act(NULL)
  {
  }
  ~ResMshActivenessInfo();
  /**
   * Obtains the number of properties that influence cell activeness.
   */
  static int GetNumberOfPropertiesThatInfluenceCellActiveness();
  /**
   * Obtains the property that influences cell activeness of index 'index'.
   * (0 <= index < GetNumberOfPropertiesThatInfluenceCellActiveness())
   */
  static const char* GetPropertyThatInfluencesCellActiveness(int index);
  /**
   * Informs if the property named 'name' has influence on each
   * cell's activeness status.
   */
  static bool HasInfluenceOnCellActiveness (const char *name);
  /**
   * Prepares for the storage of 'numcells' cell activeness info.
   */
  void SetNumCells (int numcells);
  /**
   * Returns the number of cells
   */
  int GetNumCells () const
  {
    return m_numcells;
  }
  /**
   * Updates the cells' activeness status.
   * Returns the number of active cells found.
   */
  int UpdateActiveStatus ();
  /**
   * Updates cell 'index' activity status.
   */
  void SetCellActive (int index, bool active)
  {
    m_act[index] = active;
  }
  /**
   * Is cell 'index' active?
   */
  bool IsCellActive (int index)
  {
    return m_act[index];
  }
  /**
   * Obtains the active cells array.
   */
  const bool* GetActiveCells () const
  {
    return m_act;
  }
  void CopyFrom (ResModel* mdl);
protected:
  ResModel* GetModel() const
  {
    return m_mdl;
  }
private:
  ResModel *m_mdl;
  int m_numcells;
  bool *m_act;
};

class ResMshModel : public ResModel
{
  char *m_name;
  char *m_title;
  char *m_unit_id;
  MshModel *m_mdl;
  DsArray<MshGrid*> m_grids;
  ResMshGeometry *m_geom;
  DsArray<ResMshProperty*> m_props;
  ResMshStep *m_step;

  struct Area {
    int i1, j1, k1, i2, j2, k2;
    Area(int ii1, int jj1, int kk1, int ii2, int jj2, int kk2)
      : i1(ii1), j1(jj1), k1(kk1), i2(ii2), j2(jj2), k2(kk2)
    {
    }
  };

  struct Sector {
    char *m_name;
    PSArray<Area*> m_areas;
    Sector(const char *name);
    ~Sector();
    void AddArea(int i1, int j1, int k1, int i2, int j2, int k2)
    {
      m_areas.insert(new Area(i1, j1, k1, i2, j2, k2));
    }
  };

  PSArray<ResMshWell*> m_wells;
  PSArray<Sector*> m_sectors;

public:
  ResMshModel (lua_State *L,
               MshModel *mdl,
               const char *name,
               const char *title,
               int progresslo=0,
               const char *unit_id=NULL,
               ResOpenOptions* options = NULL);
  ~ResMshModel();
  void AfterLoad ();
  void CreateRefinement (MshGrid *grid, bool during_load=false);
  void RemoveRefinement (int grid_index);
  void ReinsertRefinement (MshGrid* grid, int grid_index);
  MshModel* GetModel()
  {
    return m_mdl;
  }
  int AddMapProperty (ResProperty *p);
  ResProperty* RemoveProperty (const char *symbol);
  void MoveCompletionTo (ResCompletion* comp, int i, int j, int k);
  void GetCellGridAndIndices (int cellindex, int* oi, int *oj, int* ok, int* ogrid_index);
  void GetCellIndices (int cellindex, int* oi, int *oj, int* ok)
  {
    GetCellGridAndIndices(cellindex, oi, oj, ok, NULL);
  }
  bool HasCellData() { return GetNumberOfProperties() > 0; }
  bool HasWellData() { return false; }
  int GetNumberOfSectors() { return m_sectors.size(); }
  int GetNumberOfAreas(int s) { return m_sectors[s]->m_areas.size(); }
  const char * GetSectorName(int s) { return m_sectors[s]->m_name; }
  void GetAreaBoundaries(int s, int a, int *i1, int *j1, int *k1, int *i2, int *j2, int *k2)
  {
    Sector *sec = m_sectors[s];
    Area *area = sec->m_areas[a];
    *i1 = area->i1;
    *j1 = area->j1;
    *k1 = area->k1;
    *i2 = area->i2;
    *j2 = area->j2;
    *k2 = area->k2;
  }

  void AddSector(const char *name)
  {
    m_sectors.insert(new Sector(name));
  }

  void AddArea(int s, int i1, int j1, int k1, int i2, int j2, int k2)
  {
    m_sectors[s]->m_areas.insert(new Area(i1, j1, k1, i2, j2, k2));
  }
  const char * GetSimIniDate() { return "01/01/1980"; }
  void AddWell (ResMshWell *well, bool updatewellsradius=true);
  bool RemoveWell (const char *name);
  void RemoveAllWells ();
  const char * GetName() { return m_name; }
  const char * GetSimTitle() { return m_title; }
  const char * GetSimDistanceUnit();
  const char * GetUnit() { return m_unit_id; }
  ResMshGeometry* GetResMshGeometry(int i = 0) { return m_geom; }
  ResGeometry* GetGeometry(int i = 0) const { return m_geom; }
  int Load(const char *rootname) { return 0; }
  int GetNumberOfIniProperties() { return m_props.Size(); }
  int GetNumberOfRecProperties() { return 0; }
  ResWell * GetWellAt(int i)
  { 
    return m_wells[i];
  }
  ResWell * GetWell(const char *name);
  int GetNumberOfWells() 
  {
    return m_wells.size();
  }

  ResPosGroup * GetGroupAt(int i) { return 0; }
  ResPosGroup * GetGroup(const char *name) { return 0; }
  int GetNumberOfGroups() { return 0; }

  ResPosRegion * GetRegionAt(int i) { return 0; }
  ResPosRegion * GetRegion(const char *name) { return 0; }
  int GetNumberOfRegions() { return 0; }

  ResPosField * GetField() { return 0; }

  ResStep * GetStep(int i) { return m_step; }

  ResStep * GetElementStep(int i) { return 0; }

  int GetNumberOfSteps() { return 1; }

  int GetNumberOfElementSteps() { return 0; }
  /**
   * Updates the cells' activeness status.
   */
  void UpdateActiveStatus ();

  int GetNumberOfGrids () const
  {
    return m_grids.Size();
  }
  MshGrid* GetGrid (int index) const
  {
    return m_grids.Get(index);
  }
  MshGrid* GetGridOfCell (int cellindex) const
  {
    return GetGrid(GetGridIndexOfCell(cellindex));
  }
  int GetGridIndexOfCell (int cellindex) const
  {
    assert(m_cell_to_grid_index.ValidIndex(cellindex));
    return m_cell_to_grid_index.Get(cellindex);
  }
  void GetCompleteCellGridIndices (int cellindex, int* depth, int** oi, int** oj, int** ok) const;
  int GetCellIndexFromGridIndices (int depth, int* gi, int* gj, int* gk) const
  {
    return GetCellIndexFromGridIndices(GetGrid(0), depth, gi, gj, gk);
  }
  void PropertyAddedToGrid ();
protected: 
  ResProperty * GetIniProperty(int i) { return m_props.Get(i); }
  ResProperty * GetIniProperty(const char *name);
  ResProperty * GetRecProperty(int i) { return 0; }
  ResProperty * GetRecProperty(const char *name) { return 0; }
  
  ResPosElementProperty * GetWellProp(int i) { return 0; }
  ResPosElementProperty * GetWellProp(const char *name) { return 0; }
  int GetNumberOfWellProps() { return 0; }
  ResPosElementProperty * GetCompProp(int i) { return 0; }
  ResPosElementProperty * GetCompProp(const char *name) { return 0; }
  int GetNumberOfCompProps() { return 0; }
  ResPosElementProperty * GetGroupProp(int i) { return 0; }
  ResPosElementProperty * GetGroupProp(const char *name) { return 0; }
  int GetNumberOfGroupProps() { return 0; }
  ResPosElementProperty * GetRegionProp(int i) { return 0; }
  ResPosElementProperty * GetRegionProp(const char *name) { return 0; }
  int GetNumberOfRegionProps() { return 0; }
  ResPosElementProperty * GetFieldProp(int i) { return 0; }
  ResPosElementProperty * GetFieldProp(const char *name) { return 0; }
  int GetNumberOfFieldProps() { return 0; }
private:
  void ComputeMainGridCells ();
  int CountNumberOfRefinementLevels ();
  void AfterGridHierarchyChange (double faultvalue, bool during_load);
  void SortGridsByLevel ();
  int ComputeGridIndexing (int numgrids);
  int GetCellIndexFromGridIndices (MshGrid* grid, int depth, int* gi, int* gj, int* gk) const;
  void Refine (MshGrid *grid, int grid_level, bool during_load);
private:
  ResMshActivenessInfo m_activeinfo;
  DsArray<int> m_cell_to_grid_index;
};

#endif

