#pragma once
#include <gpos/defines.h>
#include <gpos/model/loadernew.h>
#include <gpos/common/util.h>
#include <ds/array.h>
#include <ds/hash.h>
#include "common.h"

class ECLMapProperty;

class GroupRstData 
{
public:
  GroupRstData()
    : m_well_index(NULL)
    , m_num_children(0)
    , m_group_type(-1)
    , m_group_level(-1)
    , m_parent_index(-1)
    , m_name(NULL)
    , m_num(-1)
  {
  }
  ~GroupRstData()
  {
    FREE_AND_SET_NULL(m_well_index);
    FREE_AND_SET_NULL(m_name);
  }
  const char* GetName ()
  {
    return m_name;
  }
  void SetWellIndex (int nwgmax, int* data)
  {
    m_well_index = (int *)malloc(nwgmax*sizeof(int));
    memcpy(m_well_index, data, nwgmax);
  }
  void SetData (int num_children, int group_type, int group_level, int parent_index)
  {
    m_num_children = num_children;
    m_group_type = group_type;
    m_group_level = group_level;
    m_parent_index = parent_index;
  }
  void SetName (const char* name)
  {
    m_name = PSUtil::StrDup(name);
  }
  void SetNum (int n)
  {
    m_num = n;
  }
  int GetNum ()
  {
    return m_num;
  }
private:
  int *m_well_index;
  int m_num_children;
  int m_group_type;
  int m_group_level;
  int m_parent_index;
  char *m_name;
  int m_num;
};

typedef struct {
  int comp_number;
  int ipos;
  int jpos;
  int kpos;
  int status;
  int direction;
  int segment_number;
  bool is_fracture;
} CompRstData;

//* 'CompRstDataArray' Type
// Represents an array of CompRstData.
typedef DsArray<CompRstData*> CompRstDataArray;

class  WellRstData
{
public:
  WellRstData ()
  : m_i(-1),
    m_j(-1),
    m_k(-1),
    m_num_comp(-1),
    m_group_index(-1), 
    m_well_type(-1),
    m_well_status(-1),
    m_lgr_index(-1),
    m_friction_well_flag(-1),
    m_segmented_well_number(-1),
    m_name(NULL)
  {
    m_comp_fracture = new CompRstDataArray;
    m_comp_matrix = new CompRstDataArray;
    m_completions = new CompRstDataArray;
  }
  ~WellRstData ()
  {
    int n;
    FREE_AND_SET_NULL(m_name);
    n = m_comp_fracture->Size();
    for (int i=0; i<n; i++)
      delete(m_comp_fracture->Get(i));
    DELETE_AND_SET_NULL(m_comp_fracture);

    n = m_comp_matrix->Size();
    for (int i=0; i<n; i++)
      delete(m_comp_matrix->Get(i));
    DELETE_AND_SET_NULL(m_comp_matrix);

    n = m_completions->Size();
    for (int i=0; i<n; i++)
      delete(m_completions->Get(i));
    DELETE_AND_SET_NULL(m_completions);
  }

  int CountCompletions ()
  {
    return m_completions->Size();
  }

  int CountFractureCompletions ()
  {
    return m_comp_fracture->Size();
  }

  int CountMatrixCompletions ()
  {
    return m_comp_matrix->Size();
  }

  void FractureCompletionPosition (int ic, int *i, int *j, int *k)
  {
    int n = m_comp_fracture->Size();
    for(int ii=0; ii<n; ii++) {
      CompRstData* c = m_comp_fracture->Get(ii);
      
      if (m_fracture_compnum_to_comp.Get(c->comp_number) == ic+1) {
        *i = c->ipos;
        *j = c->jpos;
        *k = c->kpos;
        return;
      }
    }
    assert(false);
  }
  
  void MatrixCompletionPosition (int ic, int *i, int *j, int *k)
  {
    int n = m_comp_matrix->Size();
    for(int ii=0; ii<n; ii++) {
      CompRstData* c = m_comp_matrix->Get(ii);
      if (m_matrix_compnum_to_comp.Get(c->comp_number) == ic+1) {
        *i = c->ipos;
        *j = c->jpos;
        *k = c->kpos;
        return;
      }
    }
    assert(false);
  }
  void CompletionPosition (int ic, int *i, int *j, int *k)
  {
    int n = m_completions->Size();
    for(int ii=0; ii<n; ii++) {
      CompRstData* c = m_completions->Get(ii);
      if (m_compnum_to_comp.Get(c->comp_number) == ic+1) {
        *i = c->ipos;
        *j = c->jpos;
        *k = c->kpos;
        return;
      }
    }
    assert(false);
  }
  const char* Name ()
  {
    return m_name;
  }
  const int WellType ()
  {
    return m_well_type;
  }
  void SetData (int i, int j, int k,
                int ncomp, int ig, int wtype, 
                int wstatus, int ilgr, 
                int fwell, int swell)
  {
    m_i = i;
    m_j = j;
    m_k = k;
    m_num_comp = ncomp;
    m_group_index = ig;
    m_well_type = wtype;
    m_well_status = wstatus;
    if (ilgr == 0)
      m_lgr_index = -1;
    else
      m_lgr_index = ilgr;
    m_friction_well_flag = fwell;
    m_segmented_well_number = swell;
  }
  void SetName (const char* name)
  {
    m_name = PSUtil::StrDup(name);
  }

  void AddCompletion (int cnum, int i, int j, int k, int status,
                            int dir, int snum)
  {
    //printf("AddMatrixCompletion: cnum=%d i=%d j=%d k=%d\n",cnum,i,j,k);
    CompRstData *c = new CompRstData;
    c->comp_number = cnum;
    c->ipos = i-1;
    c->jpos = j-1;
    c->kpos = k-1;
    c->status = status;
    c->direction = dir;
    c->segment_number = snum;
    c->is_fracture = false;
    m_completions->Append(c);
    m_compnum_to_comp.Set(cnum,m_completions->Size()); 
  }
  
  void AddMatrixCompletion (int cnum, int i, int j, int k, int status,
                            int dir, int snum)
  {
    //printf("AddMatrixCompletion: cnum=%d i=%d j=%d k=%d\n",cnum,i,j,k);
    CompRstData *c = new CompRstData;
    c->comp_number = cnum;
    c->ipos = i-1;
    c->jpos = j-1;
    c->kpos = k-1;
    c->status = status;
    c->direction = dir;
    c->segment_number = snum;
    c->is_fracture = false;
    m_comp_matrix->Append(c);
    m_matrix_compnum_to_comp.Set(cnum,m_comp_matrix->Size()); 
  }

  void AddFractureCompletion (int cnum, int i, int j, int k, int status,
                              int dir, int snum)
  {
    CompRstData *c = new CompRstData;
    c->comp_number = cnum;
    c->ipos = i-1;
    c->jpos = j-1;
    c->kpos = k-1;
    c->status = status;
    c->direction = dir;
    c->segment_number = snum;
    c->is_fracture = true;
    m_comp_fracture->Append(c);
    m_fracture_compnum_to_comp.Set(cnum,m_comp_fracture->Size()); 
  }

  bool IsRefined ()
  {
    if (m_lgr_index == -1)
      return false;
    return true;
  }
  int LGRIndex ()
  {
    return m_lgr_index-1;  // base 0
  }
  int GetParent ()
  {
    return m_group_index;
  }
private:
  int m_i;                      // Grid cell I-coordinate for wellhead
  int m_j;                      // Grid cell J-coordinate for wellhead
  int m_k;                      // Grid cell K-coordinate for wellhead
  int m_num_comp;               // Number of completion connections
  int m_group_index;            // Group parent index
  int m_well_type;              // Well type
  int m_well_status;            // Well status
  int m_lgr_index;              // LGR index for a well with local completions
  int m_friction_well_flag;     // Friction well flag
  int m_segmented_well_number;  // Segmented well number
  char *m_name;                 // Well name
  CompRstDataArray* m_comp_fracture;     // Fracture Completion data array
  CompRstDataArray* m_comp_matrix;       // Matrix Completion data array
  CompRstDataArray* m_completions;       // Matrix+Fracture Completion data array
  DsHash<int, int> m_matrix_compnum_to_comp;
  DsHash<int, int> m_fracture_compnum_to_comp;
  DsHash<int, int> m_compnum_to_comp;
};

//* 'GroupRstDataArray' Type
// Represents an array of GroupRstData.
typedef DsArray<GroupRstData*> GroupRstDataArray;

//* 'WellRstDataArray' Type
// Represents an array of WellRstData.
typedef DsArray<WellRstData*> WellRstDataArray;


class RstData
{
public:
  RstData ()
    : m_day(-1),
      m_month(-1),
      m_year(-1),
      m_ndays(-1),
      m_num_matrix_wells(0),
      m_num_fracture_wells(0)
  {
  }
  ~RstData ()
  {
    int nwells = m_wells.Size();
    for (int j=0; j<nwells; j++) {
      WellRstData* w = m_wells[j];
      DELETE_AND_SET_NULL(w);
    }

    int ngroups = m_groups.Size();
    for (int j=0; j<ngroups; j++) {
      GroupRstData *g = m_groups[j];
      DELETE_AND_SET_NULL(g);
    }
  }
  WellRstData* GetWell (int iw)
  {
    if (!m_wells.ValidIndex(iw))
      return NULL;
    return m_wells[iw];
  }
  GroupRstData* GetGroup (int ig)
  {
    if (!m_groups.ValidIndex(ig))
      return NULL;
    return m_groups[ig];
  }

  void AddFractureWell (const char* name)
  {
    for(int i=0; i<m_fracture_wells.Size(); i++) {
      if (m_fracture_wells.Get(i) == name)
        return;
    }
    //printf("AddFractureWell %s\n", name);
    m_fracture_wells.Append(name);
  }

  void AddMatrixWell (const char* name)
  {
    for(int i=0; i<m_matrix_wells.Size(); i++) {
      if (m_matrix_wells.Get(i) == name)
        return;
    }
    //printf("AddMatrixWell %s\n", name);
    m_matrix_wells.Append(name);
  }

  bool IsFractureWell (int iw)
  {
    const char* wellname = m_wells.Get(iw)->Name();
    for(int i=0; i<m_fracture_wells.Size(); i++) {
      if (PSUtil::StrEq(m_fracture_wells.Get(i), wellname))
        return true;
    }
    return false;
  }

  const char* WellName (int iw)
  {
    WellRstData* w = m_wells.Get(iw);
    return w->Name();
  }

  const char* MatrixWellName (int iw)
  {
    assert(m_matrix_wells.ValidIndex(iw));
    return m_matrix_wells.Get(iw);
  }

  const char* FractureWellName (int iw)
  {
    assert(m_fracture_wells.ValidIndex(iw));
    return m_fracture_wells.Get(iw);
  }
  void AddGroup (GroupRstData* g)
  {
    int idx = m_groups.Size();
    g->SetNum(idx);
    m_groups.Append(g);
    if (g->GetName()) {
      m_groupname_to_index.Set(g->GetName(), idx);
      m_index_to_groupname.Set(idx, g->GetName());
    }
  }
  void AddWell (int i, int j, int k,
                int ncomp, int ig, int wtype, 
                int wstatus, int ilgr, 
                int fwell, int swell)
  {
    WellRstData* w = new WellRstData;
    w->SetData(i, j, k, ncomp, ig, wtype, 
               wstatus, ilgr, 
               fwell, swell);
    m_wells.Append(w);
  }

  void SetWellName (int iw, const char* name)
  {
    WellRstData *w;
    if (m_wells.ValidIndex(iw))
      w = m_wells[iw];
    else {
      m_wells.Resize(iw+1);
      w = new WellRstData;
      m_wells[iw] = w;
    }
    w->SetName(name);
  }
  void SetGroupName (int ig, const char* name)
  {
    GroupRstData *g;
    if (m_groups.ValidIndex(ig))
      g = m_groups[ig];
    else {
      m_groups.Resize(ig+1);
      g = new GroupRstData;
      m_groups[ig] = g;
    }
    g->SetName(name);
  }
 
  int CountWells ()
  {
    return m_wells.Size();
  }
  
  int CountMatrixWells ()
  {
    return m_matrix_wells.Size();
  }

  int CountFractureWells ()
  {
    return m_fracture_wells.Size();
  }

  bool IsRefinedWell (int iw)
  {
    return m_wells.Get(iw)->IsRefined();
  }
  void AddTimeStep (int dd, int mm, int yy, float days)
  {
    m_ndays = days;
    m_day = (float)dd;
    m_month = (float)mm;
    m_year = (float)yy;
  }
  void GetTimeStep (int* dd, int* mm, int* yy, float* days)
  {
    *dd = (int)m_day;
    *mm = (int)m_month;
    *yy = (int)m_year;
    *days = m_ndays;
  }
  int WellIndex (const char* wellname)
  {
    if (!m_wellname_to_index.Find(wellname))
      return -1;
    return m_wellname_to_index.Get(wellname);
  }
  void SetWellIndex (const char* wellname, int idx)
  {
    m_wellname_to_index.Set(wellname, idx);
  }
  GroupRstData* GetGroup (const char* name)
  {
    if (!m_groupname_to_index.Find(name))
      return NULL;
    return m_groups.Get(m_groupname_to_index.Get(name));
  }
  void SetGroupIndex (const char* groupname, int idx)
  {
    if (m_index_to_groupname.Find(idx)) {
      //assert(PSUtil::StrEq(m_index_to_groupname.Get(idx),groupname));
      return;
    }
    m_index_to_groupname.Set(idx, groupname);
  }
  const char* GetGroupName (int i)
  {
    if (!m_index_to_groupname.Find(i))
      return NULL;
    const char* parent = m_index_to_groupname.Get(i);
    return parent;
  }
private:
  DsArray<const char*> m_fracture_wells;
  DsArray<const char*> m_matrix_wells;
  WellRstDataArray m_wells;
  GroupRstDataArray m_groups;
  float m_day;
  float m_month;
  float m_year;
  float m_ndays;
  DsHash<DsStringKey, int> m_wellname_to_index;
  DsHash<DsStringKey, int> m_groupname_to_index;
  DsHash<int, DsStringKey> m_index_to_groupname;
  int m_num_fracture_wells;
  int m_num_matrix_wells;
};

//* 'RstDataArray' Type
// Represents an array of RstData
typedef DsArray<RstData*> RstDataArray;

class RstGridData 
{
public:
  RstGridData (const char* name)
  : m_nx(-1)
  , m_ny(-1)
  , m_nz(-1)
  , m_unit(NULL)
  , m_nact(-1)
  , m_num_matrix_wells(0)
  , m_num_fracture_wells(0)
  {
    m_gridname = PSUtil::StrDup(name);
    m_rstdata = new RstDataArray;
    m_props.Clear();
    m_props_to_index.Clear();
  }
  ~RstGridData ()
  {
    FREE_AND_SET_NULL(m_gridname);
    FREE_AND_SET_NULL(m_unit);
    int n = m_rstdata->Size();
    for (int i=0; i<n; i++) {
      RstData* r = m_rstdata->Get(i);
      DELETE_AND_SET_NULL(r);
    }
    DELETE_AND_SET_NULL(m_rstdata);
    n = m_props.Size();
    for(int i=0; i<n; i++)
      delete(m_props.Get(i));
    m_props_to_index.Clear();
    int k;
    if (m_index_to_groupname.First(&k)) {
      do
        free(m_index_to_groupname.Get(k));
      while (m_index_to_groupname.Next(&k));
    }
  }
  int RestartDataCount ()
  {
    return m_rstdata->Size();
  }
  void SetGridDimensions (int nx, int ny, int nz)
  {
    m_nx = nx;
    m_ny = ny;
    m_nz = nz;
  }
  void GridDimensions (int* nx, int* ny, int* nz)
  {
    *nx = m_nx;
    *ny = m_ny;
    *nz = m_nz;
  }
  RstData* GetRestartData (int time)
  {
    if (m_rstdata->ValidIndex(time)) 
      return m_rstdata->Get(time);
    return NULL;
  }
  RstData* NewRestartData (int time)
  {
    m_rstdata->Resize(time+1);
    RstData* r = new RstData;
    m_rstdata->Set(time, r);
    return r;
  }
  int CountTimeSteps ()
  {
    return m_rstdata->Size();
  }
  RstData* LastRestartData ()
  {
    int n = m_rstdata->Size();
    if (n > 0)
      return m_rstdata->Get(n-1);
    return NULL;
  }
  void SetUnit (const char* u)
  {
    if (!m_unit) 
      m_unit = PSUtil::StrDup(u);
  }
  void SetNumActiveCells (int nact)
  {
    m_nact = nact;
  }
  int ActiveCellsCount ()
  {
    return m_nact;
  }
  int NumTotalCells ()
  {
    return m_nx * m_ny * m_nz;
  }
  void AddProperty (const char* name, ECLMapProperty *p)
  {
    int index = m_props.Size();
    m_props.Append(p);
    m_props_to_index.Set(name, index);
  }
  ECLMapProperty* GetProperty (const char *name)
  {
    if (!m_props_to_index.Find(name))
      return NULL;
    int index = m_props_to_index.Get(name);
    assert(m_props.ValidIndex(index));
    return m_props.Get(index);
  }
  ECLMapProperty* GetProperty (int index)
  {
    assert(m_props.ValidIndex(index));
    return m_props.Get(index);
  }
  int GetNumProperties ()
  {
    return m_props.Size();
  }
  bool PropertyExists (const char* name)
  {
    if (!m_props_to_index.Find(name)) 
      return false;
    int index = m_props_to_index.Get(name);
    if (!m_props.ValidIndex(index))
      return false;
    return true;
  }
  void SetNumWells (int nwells)
  {
    m_num_wells = nwells;
  }
  int GetNumWells ()
  {
    return m_num_wells;
  }
private:
  int m_nx;
  int m_ny;
  int m_nz;
  char* m_gridname;
  char* m_unit;
  int m_nact;
  int m_num_wells;                          // NWELL = number of wells
  RstDataArray* m_rstdata;
  DsArray<ECLMapProperty*> m_props;
  DsHash<DsStringKey, int> m_props_to_index;
  DsHash<int, char*> m_index_to_groupname;
  int m_num_matrix_wells;
  int m_num_fracture_wells;
  DsHash<DsStringKey, int> m_matrix_wells;
  DsHash<DsStringKey, int> m_fracture_wells;
};

class ECLReader;
class SMSPECReader;

class UNRSTReader : public ECLFormatReader
{
public:
  UNRSTReader (const char* rootname, 
               ResECLError *errors, 
               float nullvalue);
  ~UNRSTReader();
  bool ReadKeywords (ResPosLoaderNew* loader);
  bool ValidateFiles (bool required);
  //bool ReadWellKeywords (ResPosLoaderNew* loader);
  bool FileExists ();
  int CountWells ();
  int CountWells (const char* lgrname);
  int CountCompletions (const char* lgrname, const char* wellname);
  int CountCompletions (const char* wellname);
  bool CompletionPosition(const char* lgrname, const char* wellname, int ic, int* i, int* j, int* k);
  bool CompletionPosition(const char* wellname, int ic, int* i, int* j, int* k);
  const char* WellName (int iw);
  const char* MatrixWellName (int iw);
  const char* FractureWellName (int iw);
  int CountGrids ();
  int WellIndex (const char* name);
  int WellIndex (const char* lgrname, const char* wellname);
  const char* WellLGR (int iw);
  void GridDimensions (int* nx, int* ny, int* nz);
  void GridDimensions (const char* grid, int* nx, int* ny, int* nz);
  int CountLGRActiveCells(const char* grid);
  void SetInitialDate(const char* date);
  int CountProperties();
  ECLMapProperty* GetProperty (int index);
  bool IsDualPorosity ();
  bool LoadProperty (int loader_index, const char* symbol, int ts, DsHash<DsStringKey, float*>& prop_by_grid, bool is_complete_prop, int propsize);
  int CountMapTimeSteps ();
  void GetMapTimeStep (int ts, int* dd, int* mm, int* yy, float* days);
  bool PropertyExists (const char* symbol);
  bool PropertyExists (const char* symbol, const char* lgrname);
  int GetWellType(const char* wellname, const int day, const int month, const int year);
  bool IsLoaded ();
  int CountRootActiveCells ();
  const char* GetWellParent(int wellid, int stepindex);
  int CountMatrixWells ();
  int CountMatrixWells (const char* lgrname);
  int CountFractureWells ();
  int CountFractureWells (const char* lgrname);
  int CountMatrixCompletions (const char* wellname);
  int CountFractureCompletions (const char* wellname);
  int CountMatrixCompletions (const char* lgrname, const char* wellname);
  int CountFractureCompletions (const char* lgrname, const char* wellname);
  bool MatrixCompletionPosition(const char* wellname, 
                                int ic, int* i, int* j, int* k);
  bool FractureCompletionPosition(const char* wellname, 
                                  int ic, int* i, int* j, int* k);
  bool MatrixCompletionPosition(const char* lgrname, 
                                           const char* wellname, 
                                          int ic, int* i, int* j, int* k);
  bool FractureCompletionPosition(const char* lgrname, 
                                             const char* wellname, 
                                             int ic, int* i, int* j, int* k);
  bool IsFractureWell(const char* lgrname, const char* wellname);
  bool IsFractureWell(const char* wellname);
private:
  void ReadSEQNUM (ECLReader *rd) throw (bool);
  void ReadINTEHEAD (ECLReader *rd, int nelems) throw (bool);
  void ReadLOGIHEAD (ECLReader *rd, int nelems) throw (bool);
  void ReadDOUBHEAD (ECLReader *rd, int nelems) throw (bool);
  void ReadIGRP (ECLReader *rd, int nelems) throw (bool);
  void ReadISEG (ECLReader *rd, int nelems) throw (bool);
  void ReadIWEL (ECLReader *rd, int nelems) throw (bool);
  void ReadZWEL (ECLReader *rd, int nelems) throw (bool);
  void ReadICON (ECLReader *rd, int nelems) throw (bool);
  void ReadZGRP (ECLReader *rd, int nelems) throw (bool);
  void ReadLGR (ECLReader *rd) throw (bool);
  void ReadENDLGR (ECLReader *rd) throw (bool);
  void ReadLGRNAMES (ECLReader *rd, int nbytes) throw (bool);
  void ReadSolutionProperty(ECLReader *rd, 
                            const char* keyword, 
                            int nelems, 
                            const char* dtype,
                            RstGridData* grid,
                            bool is_complete);
  void SetCurrentGrid (const char* name);
  RstData* GetRestartData (const char*grid, int time);
  RstData* GetLastRestartData (const char*grid);
  RstGridData* GetGridData ();
  void AddTimeStep (int ts, int dd, int mm, int yy);
  bool ReadPropertyValue(ECLMapProperty* prop,
                         double factor_mult,
                         double factor_add,
                         int ts,
                         float*& value,
                         size_t propsize,
                         size_t offset_to_skip);
  float GetNullValue ()
  {
    return m_nullvalue;
  }
  DsHash<DsStringKey,int>* BuildSolutionPropsToEnum ();
  void GetPropertyUnitFactors(const char* unit, 
                              double* factor_mult, 
                              double* factor_add);
  void SetNoValues (RstGridData* grid, bool is_complete_prop, float*& values);
  bool ReadingFracture ();
private:
  char *m_filename;
  ResECLError* m_errors;

  char *m_restart;              // UNRST filename
  ECLReader *m_unrst_rd;      // UNRST Reader
  int m_rst_index_time;
  DsHash<DsStringKey, RstGridData*>* m_grid_to_rstdata;
  bool m_lgr_rst;
  int m_unit;                  // units type: 1 - METRIC, 2 - FIELD, 3 - LAB
  int m_nigrpz;
  int m_ngmaxz;
  int m_nwgmax;
  int m_nswlmx;      // NSWLMX = maximum number of segmented wells
  int m_nsegmx;      // NSEGMX = maximum number of segments per well
  int m_nisegz;      // NISEGZ = number of entries per segment in ISEG array
  int m_niwel;                // NIWEL = no of data elements per well in IWEL
                              //         array (default 97 for ECLIPSE, 94 for ECLIPSE 300)
  int m_nzwel;                // NZWEL = no of 8-character words per well in
                              //         ZWEL array (= 3)
  int m_ncwma;                // NCWMA = maximum number of completions per well
  int m_iphs;                 // IPHS = phase indicator
  int m_iprog;
  int m_nicon;                // NICON = no of data elements per completion in
                              //         ICON array (default 19)
  char m_simtitle[4096];
  bool m_radial_model;
  bool m_dual_porosity_model;
  char* m_current_grid;
  int m_current_step;
  StringArray* m_lgrnames;
  int m_ini_day;
  int m_ini_month;
  int m_ini_year;
  bool m_startsol;
  float m_nullvalue;
  bool m_loaded;
  DsHash<DsStringKey, int> m_date_to_ts;
  DsArray<DsStringKey> m_grid_list;
  bool m_reading_fracture;
};
