#pragma once

#include <gpos/defines.h>
#include <gpos/model/loadernew.h>
#include <gpos/model/modelnew.h>
#include <gpos/common/util.h>
#include <ds/array.h>
#include <ds/hash.h>
#include "common.h"
#include "smspec_reader.h"
#include "unsmry_reader.h"
#include "unrst_reader.h"
#include "init_reader.h"

/*
// *****************************************************************************
// 
// *****************************************************************************
*/
//static const char* props_desc[] = {
//};

static const char* special_props_desc[] = {
  "Simulated time (days)",
  "Simulated time (years)",
  "Calendar day from DATE keyword",
  "Calendar month from DATE keyword",
  "Calendar year from DATE keyword",
  "Elapsed run time (seconds)",
  "Maximum pressure change per timestep",
  "Maximum oil saturation change per timestep",
  "Maximum gas saturation change per timestep",
  "Maximum water saturation change per timestep",
  "Newton iterations per timestep",
  "Average number of linear iterations per Newton iteration for each timestep",
  "Reasons for selecting timestep length",
  "Current CPU usage (seconds)",
  "CPU usage per timestep (seconds)",
  "CPU usage per simulated day (seconds) or per hour in lab units",
  "Elapsed time per timestep (seconds)",
  "Elapsed time per simulated day (seconds) or per hour in lab units",
  "Timestep length"
};

static const char* special_props_symbol[] = {
  "TIME",
  "YEARS", 
  "DAY", 
  "MONTH", 
  "YEAR", 
  "ELAPSED", 
  "MAXDPR", 
  "MAXDSO", 
  "MAXDSG", 
  "MAXDSW", 
  "NEWTON", 
  "NLINEARS", 
  "STEPTYPE",  
  "TCPU", 
  "TCPUTS", 
  "TCPUDAY", 
  "TELAPTS",
  "TELAPDAY", 
  "TIMESTEP"
};

typedef enum { 
  TIME,
  YEARS, 
  DAY, 
  MONTH, 
  YEAR, 
  ELAPSED, 
  MAXDPR, 
  MAXDSO, 
  MAXDSG, 
  MAXDSW, 
  NEWTON, 
  NLINEARS, 
  STEPTYPE,  
  TCPU, 
  TCPUTS, 
  TCPUDAY, 
  TELAPTS,
  TELAPDAY, 
  TIMESTEP,
  NUM_SPECIAL_KEYS
} SpecialKeywords;

class ECLReader;

class ECLElemData 
{
private:
  int  m_num;
  char *m_name;
  DsArray<ECLProperty*> m_props;
  DsHash<DsStringKey, int> m_props_to_index;
public:
  ECLElemData ()
  : m_num(-1)
  , m_name(NULL)
  {
    m_props.Clear();
    m_props_to_index.Clear();
  }
  ~ECLElemData ()
  {
    int n = m_props.Size();
    for(int i=0; i<n; i++)
      delete(m_props.Get(i));
    FREE_AND_SET_NULL(m_name);
  }
  void SetNumber(int cnum)
  {
    m_num = cnum;
  }
  int GetNumber()
  {
    return m_num;
  }
  void SetName (const char* wellname)
  {
    m_name = PSUtil::StrDup(wellname);
  }
  const char* GetName ()
  {
    return m_name;
  }
  void AddProperty (const char* name, ECLProperty *p)
  {
    int index = m_props.Size();
    m_props.Append(p);
    m_props_to_index.Set(name, index);
  }
  ECLProperty* GetProperty (const char *name)
  {
    if (!m_props_to_index.Find(name))
      return NULL;
    int index = m_props_to_index.Get(name);
    assert(m_props.ValidIndex(index));
    return m_props.Get(index);
  }
  ECLProperty* GetProperty (int index)
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
};

class ECLExtraData : public ECLElemData
{};

class ECLCompletionData: public ECLElemData
{
private:
  IntArray m_i;
  IntArray m_j;
  IntArray m_k;
  char *m_wellname;
  char *m_lgrname;
  int m_cellindex;
  //char *connect_to;
public:
  ECLCompletionData()
  : m_cellindex(-1)
  , m_wellname(NULL)
  , m_lgrname(NULL)
  {
  }
  ~ECLCompletionData() 
  {
    FREE_AND_SET_NULL(m_wellname);
  }
  
  void SetPosition(int depth, int ipos,int jpos,int kpos)
  {
    if (!m_i.ValidIndex(depth)) {
      m_i.Resize(depth+1);
      m_j.Resize(depth+1);
      m_k.Resize(depth+1);
    }
    m_i[depth] = ipos;
    m_j[depth] = jpos;
    m_k[depth] = kpos;
  }
  void SetParent(const char *name)
  {
    m_wellname = PSUtil::StrDup(name);
  }
  void SetCellIndex (int cellindex)
  {
    m_cellindex = cellindex;
  }
  const char* GetParent ()
  {
    return m_wellname;
  }
  //void SetConnectTo(const char *connect)
  //{
  //  connect_to = PSUtil::StrDup(connect);
  //}
  //char *GetConnectTo(void)
  //{
  //  return connect_to;
  //}
  //char *GetName();
  int GetGridDepth () const
  {
    return m_i.Size();
  }
  void GetPosition(int grid,int *ipos,int *jpos,int *kpos)
  {
    if (m_i.ValidIndex(grid)) {
      *ipos = m_i[grid];
      *jpos = m_j[grid];
      *kpos = m_k[grid];
    }
    else {
      *ipos = -1;
      *jpos = -1;
      *kpos = -1;
    }
  }
  int GetCellIndex ()
  {
    return m_cellindex;
  }
};

typedef DsArray<ECLCompletionData*> ECLCompletionDataArray;

class ECLWellData : public ECLElemData
{
private:
  char *m_lgrname;
  ECLCompletionDataArray *m_completions;              // list of layers;
public:
  ECLWellData ()
  : m_completions(NULL),
    m_lgrname(NULL)
  {
    m_completions = new ECLCompletionDataArray;
    m_completions->Clear();
  }
  ~ECLWellData ()
  {
    int n = m_completions->Size();
    for (int i=0; i<n; i++) {
      ECLCompletionData *c = m_completions->Get(i);
      DELETE_AND_SET_NULL(c);
    }
    DELETE_AND_SET_NULL(m_completions);
    FREE_AND_SET_NULL(m_lgrname);
  }
  void SetCompletion (ECLCompletionData *l)
  {
    m_completions->Append(l);
  }
  int GetNumComp ()
  {
    return m_completions->Size();
  }
  ECLCompletionData* GetCompletion (int idx)
  {
    //for (int i=0; i<m_completions->Size(); i++) {
    //  ECLCompletionData* l = m_completions->Get(i);
    //  if (l->GetNumber() == idx)
    //    return l;
    //}
    if (m_completions->ValidIndex(idx))
      return m_completions->Get(idx);
    return NULL;
  }
  ECLCompletionData* FindCompletion(int grid, int ipos, int jpos, int kpos)
  {
    for (int n=0; n<m_completions->Size(); n++) {
      if (m_completions->ValidIndex(n)) {
        ECLCompletionData* l = m_completions->Get(n);
        int i = -1;
        int j = -1;
        int k = -1;
        l->GetPosition(grid, &i, &j, &k);
        if (i == ipos && j == jpos && k == kpos)
          return l;
      }
    }
    return NULL;
  }

  void SetLGRName (const char* lgrname)
  {
    m_lgrname = PSUtil::StrDup(lgrname);
  }
  const char* GetLGRName ()
  {
    return m_lgrname;
  }
  bool IsRefined ()
  {
    return (m_lgrname != NULL);
  }
};

class ECLFieldData : public ECLElemData
{};

class ECLGroupData : public ECLElemData
{};

class ECLRegionData : public ECLElemData
{};

//* 'ECLWellDataArray' Type
// Represents an array of ECLWellData.
typedef DsArray<ECLWellData*> ECLWellDataArray;

//* 'ECLGroupDataArray' Type
// Represents an array of ECLGroupData.
typedef DsArray<ECLGroupData*> ECLGroupDataArray;

//* 'ECLFieldDataArray' Type
// Represents an array of ECLFieldData.
typedef DsArray<ECLFieldData*> ECLFieldDataArray;

//* 'ECLRegionDataArray' Type
// Represents an array of ECLRegionData.
typedef DsArray<ECLRegionData*> ECLRegionDataArray;

//* 'ECLExtraDataArray' Type
// Represents an array of ECLExtraData
typedef DsArray<ECLExtraData*> ECLExtraDataArray;

//* 'ECLElemDataHash' Type
// Represents an hash of ECLElemData
typedef DsHash<DsStringKey, ECLElemData*> ECLElemDataHash;

//* 'ECLPropertyHash' Type
// Represents an hash of ECLProperty
typedef DsHash<DsStringKey, ECLProperty*> ECLPropertyHash;

class ResECLWellResultLoader : public ResPosWellResultLoader
{
public:
  ResECLWellResultLoader (UNRSTReader** unrst_reader, 
                          SMSPECReader** smspec_reader,
                          INITReader** init_reader);
  ~ResECLWellResultLoader ();
  // virtual methods
  /**
   * This method is called with an empty reservoir model and the root of its
   * filename.
   *
   * Returns true if all expected files were correctly loaded and
   * false otherwise.
   */
  const char* GetRootFileName () const;
  bool AreGridFilesNewer (const char* filename);
  bool LoadHeader (const char* src, int* model_count, char*** suffixes);
  bool Load(const char *src, ResPosModelNew* mdl);
  bool GetWellType (ResPosModelNew* mdl, int well_id, ResWellType* wtype);
  const char* GetWellParent (int well_id, int stepindex);
  bool GetWellPropRecordedSteps (ResPosModelNew* mdl, int prop_id, int well_id, bool* has_recorded_steps);
  bool GetCompletionPropRecordedSteps (ResPosModelNew* mdl, int prop_id, int well_id, int comp_index, bool* has_recorded_steps);
  bool GetGroupPropRecordedSteps (ResPosModelNew* mdl, int prop_id, int group_id, bool* has_recorded_steps);
  bool GetRegionPropRecordedSteps (ResPosModelNew* mdl, int prop_id, int region_id, bool* has_recorded_steps);
  bool GetFieldPropRecordedSteps (ResPosModelNew* mdl, int prop_id, bool* has_recorded_steps);
  bool GetExtraPropRecordedSteps (ResPosModelNew* mdl, int prop_id, bool* has_recorded_steps);
  bool LoadFieldProperty (ResPosModelNew* mdl, int prop_id, float* data);
  bool LoadGroupProperty (ResPosModelNew* mdl, int prop_id, int group_id, float* data);
  bool LoadRegionProperty (ResPosModelNew* mdl, int prop_id, int region_id, float* data);
  bool LoadWellProperty (ResPosModelNew* mdl, int prop_id, int well_id, float* data);
  bool LoadWellProperty (ResPosModelNew* mdl, const char* symbol, int well_id, float* data);
  bool LoadCompletionProperty (ResPosModelNew* mdl, int prop_id, int well_id, int comp_index, float* data);
  bool LoadExtraProperty (ResPosModelNew* mdl, int prop_id, float* data);
  const char* GetLoadError () const;
  const char* GetLoadErrorDetails () const;
  const char* GetLoadWarnings () const; 
  char* GetCompletionName (ResPosModelNew* mdl, int well_id, int comp_index);
private:
  void SetWellGroups (ResPosModelNew* mdl);
  bool PropertyExists (ECLPropertyArray* prop_array, const char* symbol);
  float GetNullValue () const
  {
    return RES_NULL_VALUE;
  }  
  bool StoreWellTypes (ResPosModelNew* mdl);
  bool GetRecordedSteps (ECLElemData *e, ECLProperty* prop, bool* has_recorded_steps);
  bool LoadProperty (ECLElemData *e, ECLProperty* prop, float* data);
  bool ReadSMSPEC ();
  bool ReadSUMMARY ();
  // Misc functions
  ECLExtraData* AddExtra (const char* name, const char* desc);
  ECLWellData* AddWell (int idx, const char* name);
  ECLGroupData* AddGroup (const char* name);
  //void AddRegion (ECLRegionData *r, int index);
  ECLRegionData* AddRegion(int num, const char* name);
  bool WellExists (const char *name);
  bool GroupExists(const char *name);
  bool CreateProperties (bool has_unrst);
  ECLProperty* CreateProperty (const char* symbol, const char* unit, int pos);
  bool StoreWellProperty (const char* symbol,const char* desc,const char* unit);
  bool StoreGroupProperty (const char* symbol,const char* desc,const char* unit);
  bool StoreRegionProperty (const char* symbol,const char* desc,const char* unit);
  bool StoreFieldProperty (const char* symbol,const char* desc,const char* unit);
  bool StoreCompletionProperty (const char* symbol,const char* desc,const char* unit);
  bool HasElemPropertyValue (ECLProperty* prop, int ts);
  bool ReadElemPropertyValue(ECLProperty* prop,
                             double factor_mult,
                             double factor_add,
                             int ts,
                             float *value);
  bool StoreProperty(ECLPropertyArray*& prop_array,
                     const char* symbol,
                     const char* desc,
                     const char* unit);
  
  bool RegionExists(const char *name);
  void SetPropertyUnit (ECLProperty* p, const char *unit);
  bool IsExtraProperty (const char* propname);
  void AddRegionProperty (ECLRegionData* r, 
                          const char* symbol, 
                          const char* unit,
                          int pos);
  void AddFieldProperty (ECLFieldData* f, 
                         const char* symbol, 
                         const char* unit,
                         int pos);
  void BuildSpecialKeysToEnum (DsHash<DsStringKey,int>*& keys)
  {
    for(int i=1;i<NUM_SPECIAL_KEYS;i++)
      keys->Set(special_props_symbol[i], i);  // first key is 1
  }
  void AddWellProperty (ECLWellData* w, 
                        const char* symbol, 
                        const char* unit,
                        int pos,
                        bool refined_prop);
  void AddGroupProperty (ECLGroupData* g, 
                         const char* symbol, 
                         const char* unit,
                         int pos);
  ECLCompletionData* AddCompletion (int idx, const char* wellname, int cellindex);
  ECLCompletionData* AddCompletion (int idx, const char* wellname, int ipos, int jpos,int kpos);
  ECLCompletionData* AddCompletion (int idx, const char* wellname, 
                      int depth, int ipos, int jpos, int kpos,
                      const char* lgrname);
  ECLCompletionData* GetCompletionData (const char* wellname,
                                        int cellindex);
  ECLCompletionData* GetCompletionData (const char* wellname,
                                        const char* lgrname,
                                        int depth,
                                        int ipos,
                                        int jpos,
                                        int kpos);
  ECLCompletionData* GetCompletionData (const char* wellname,
                                        int ipos,
                                        int jpos,
                                        int kpos);
  void AddCompletionProperty (ECLCompletionData* g, 
                              const char* symbol, 
                              const char* unit,
                              int pos);
  void ReleaseElemHash (DsHash<DsStringKey,ECLElemData*>& h);
  void ReleaseIntHash(DsHash<DsStringKey, int>& h);
  //void CompleteElements ();
  bool CreateElements ();
  bool CreateWells ();
  ECLWellData* GetWellData(const char* wellname);
  void SetWellData(const char* wellname, ECLWellData* w);
  bool GetCompletionsFromRestart(ECLWellData* w);
  int CreateWell (const char* wellname);
private:
  ResPosModelNew* m_modelnew;
  char *m_rootname;
  ResECLError *m_errors;
  int m_index_time;            // indicates the current time
  ECLElemDataHash m_name_to_group;
  ECLElemDataHash m_name_to_well;
  ECLElemDataHash m_name_to_region;
  ECLElemDataHash m_name_to_extra;
  ECLWellDataArray* m_wells;
  ECLGroupDataArray* m_groups;
  ECLFieldDataArray* m_field;
  ECLRegionDataArray* m_regions;
  ECLExtraDataArray* m_extras;
  ECLPropertyArray* m_well_props;
  ECLPropertyArray* m_group_props;
  ECLPropertyArray* m_region_props;
  ECLPropertyArray* m_field_props;
  ECLPropertyArray* m_comp_props;
  int m_rst_index_time;
  int m_summary_index;
  ECLPropertyHash m_symbol_to_field_prop;
  ECLPropertyHash m_symbol_to_group_prop;
  ECLPropertyHash m_symbol_to_region_prop;
  ECLPropertyHash m_symbol_to_well_prop;
  ECLPropertyHash m_symbol_to_comp_prop;
  ECLPropertyHash m_index_to_wellprop;
  DsHash<DsStringKey,char*>* m_units_table;
  SMSPECReader* m_smspec_reader;
  SMSPECReader** m_smspec_pt;
  UNSMRYReader* m_unsmry_reader;
  UNRSTReader*  m_unrst_reader;
  UNRSTReader**  m_unrst_pt;
  INITReader* m_init_reader;
  INITReader** m_init_pt;
  char m_simtitle[4096];
  DsHash<DsStringKey,int>* m_special_props;
  // Grid dimensions
  int m_nx;          
  int m_ny;
  int m_nz;
  bool m_is_dualpor;
};
