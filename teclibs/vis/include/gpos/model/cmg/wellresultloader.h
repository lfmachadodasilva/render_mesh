#pragma once

#include <gpos/defines.h>
#include <gpos/model/loadernew.h>
#include <gpos/common/util.h>
#include <ds/array.h>
#include <ds/hash.h>
#include <utl/utlstring.h>
#include "common.h"
#include "binreader.h"
#include "textreader.h"
#include <algorithm>

#define FREE_AND_SET_NULL(p) { PSUtil::Free(p); p = NULL;}
#define DELETE_AND_SET_NULL(p) { if (p) {delete p; p = NULL;} }

typedef struct {
  float x_entry;
  float y_entry;
  float z_entry;
  float x_exit;
  float y_exit;
  float z_exit;
  float perf_length;
} LayerXYZData;

//* 'TimeDataArray' Type
// Represents an array of times.
typedef DsArray<TimeData> TimeDataArray;
typedef DsArray<int> IntArray;

class CMGBinReader;
class CMGTextReader;
class CMGDictionary;

class CMGRecData 
{
public:
  CMGRecData();
  virtual ~CMGRecData();
  /**
   * Signals that this property was recorded in a time step.
   */
  void SetRecordedInTimeStep ()
  {
    m_recorded_in_any_time_step = true;
  }
  /**
   * Was this property record recorded in any time step?
   */
  bool WasRecordedInAnyTimeStep () const
  {
    return m_recorded_in_any_time_step;
  }
  void SetType (ResValueType type)
  {
    m_type = type;
  }
  void SetSymbol(const char *s)
  {
    m_symbol = s;
  }
  const DsStringKey& Symbol ()
  {
    return m_symbol;
  }
  ResValueType Type () const
  {
    return m_type;
  }
private:
  DsStringKey m_symbol;
  ResValueType m_type;
  bool m_recorded_in_any_time_step;
};

class CMGWellRecData : public CMGRecData
{
public:
  ~CMGWellRecData ()
  {
    int size = m_well_props.Size();
    for (int i=0; i<size; ++i)
      delete m_well_props[i];
  }
  void SetWellProp (int well, int well_count, CMGProperty* prop)
  {
    if (!m_well_props.ValidIndex(well))
      m_well_props.ResizeAndSetConst(well_count, NULL);
    m_well_props[well] = prop;
  }
  CMGProperty* GetWellProp (int well)
  {
    if (m_well_props.ValidIndex(well))
      return m_well_props[well];
    else
      return NULL;
  }
private:
  DsArray<CMGProperty*> m_well_props;
};

class CMGGroupRecData : public CMGRecData
{
public:
  ~CMGGroupRecData ()
  {
    int size = m_group_props.Size();
    for (int i=0; i<size; ++i)
      delete m_group_props[i];
  }
  void SetGroupProp (int group, int group_count, CMGProperty* prop)
  {
    if (!m_group_props.ValidIndex(group))
      m_group_props.ResizeAndSetConst(group_count, NULL);
    m_group_props[group] = prop;
  }
  CMGProperty* GetGroupProp (int group)
  {
    if (m_group_props.ValidIndex(group))
      return m_group_props[group];
    else
      return NULL;
  }
private:
  DsArray<CMGProperty*> m_group_props;
};

class CMGLayerRecData : public CMGRecData
{
public:
  ~CMGLayerRecData ()
  {
    int size = m_layer_props.Size();
    for (int i=0; i<size; ++i)
      delete m_layer_props[i];
  }
  void SetLayerProp (int layer, int layer_count, CMGProperty* prop)
  {
    if (!m_layer_props.ValidIndex(layer))
      m_layer_props.ResizeAndSetConst(layer_count, NULL);
    m_layer_props[layer] = prop;
  }
  CMGProperty* GetLayerProp (int layer)
  {
    if (m_layer_props.ValidIndex(layer))
      return m_layer_props[layer];
    else
      return NULL;
  }
private:
  DsArray<CMGProperty*> m_layer_props;
};

class WellDefData {
public:
  char *parent;
  float fraction;
public:
  WellDefData ()
  : parent(NULL)
  {
  }
  ~WellDefData ()
  {
    FREE_AND_SET_NULL(parent);
  }
};

class WellData {
public:
  char *name;
  DsHash<int, WellDefData*> defdata;
  DsArray<int> layers;
public:
  WellData (int index)
  : name(NULL)
  , m_index(index)
  {
  }
  ~WellData ()
  {
    FREE_AND_SET_NULL(name);

    int k;
    if (defdata.First(&k)) {
      do
        delete defdata.Get(k);
      while (defdata.Next(&k));
      defdata.Clear();
    }
  }
  int GetIndex () const
  {
    return m_index;
  }
private:
  int m_index;
};

class GroupData {
public:
  char *name;
  char *parent;
public:
  GroupData ()
  : name(NULL)
  , parent(NULL)
  , m_index(-1)
  {
  }
  GroupData (const char* name, const char* parent, int index)
  : name(NULL)
  , parent(NULL)
  , m_index(index)
  {
    utlStringCopy(this->name, name);
    utlStringCopy(this->parent, parent);
  }
  ~GroupData ()
  {
    FREE_AND_SET_NULL(name);
    FREE_AND_SET_NULL(parent);
  }
  int GetIndex () const
  {
    return m_index;
  }
private:
  int m_index;
};

class CMGLayer
{
public:
  CMGLayer();
  virtual ~CMGLayer();
  
  void SetIndex (int index)
  {
    m_index = index;
  }
  
  int GetIndex () const
  {
    return m_index;
  }
  
  void AddPosition(int i,int j,int k)
  {
    m_i.Append(i);
    m_j.Append(j);
    m_k.Append(k);
  }
  void FinishedPosition ()
  {
    m_i.Pack();
    m_j.Pack();
    m_k.Pack();
  }
  
  void SetParent(const char *name)
  {
    m_wellname = PSUtil::StrDup(name);
  }
  
  void SetConnectTo(const char *connect)
  {
    m_connect_to = PSUtil::StrDup(connect);
  }
  
  const char *GetConnectTo(void)
  {
    return m_connect_to;
  }
  
  void SetPerf(bool perf)
  {
    m_true_perf = perf;
  }
  
  void SetLayerXYZ(float xi,float yi,float zi,float xo,float yo,float zo,float length)
  {
    m_layerxyz = new LayerXYZData;
    m_layerxyz->x_entry = xi;
    m_layerxyz->y_entry = yi;
    m_layerxyz->z_entry = zi;
    m_layerxyz->x_exit = xo;
    m_layerxyz->y_exit = yo;
    m_layerxyz->z_exit = zo;
    m_layerxyz->perf_length = length;
  }
  bool GetTrajectory (AlgVector* o_entry,
                      AlgVector* o_exit,
                      float* o_perf_length)
  {
    if (m_layerxyz == NULL)
      return false;
    o_entry->Set(m_layerxyz->x_entry, m_layerxyz->y_entry, m_layerxyz->z_entry);
    o_exit ->Set(m_layerxyz->x_exit,  m_layerxyz->y_exit,  m_layerxyz->z_exit);
    *o_perf_length = m_layerxyz->perf_length;
    return true;
  }
  
  const char *GetParent(void)
  {
    return m_wellname;
  }
  
  bool GetPerf(void)
  {
    return m_true_perf;
  }
  
  const char *GetName();
  
  int GetGridDepth () const
  {
    return m_i.Size();
  }
  
  void GetPosition(int grid,int *i,int *j,int *k)
  {
    *i = m_i.Get(grid);
    *j = m_j.Get(grid);
    *k = m_k.Get(grid);
  }
private:
  int m_index;
  IntArray m_i;
  IntArray m_j;
  IntArray m_k;
  char* m_wellname;
  char* m_connect_to;
  bool m_true_perf;
  LayerXYZData* m_layerxyz;
};

class SectorData {
public:
  char *name;
  int num;
  DsHash<DsStringKey,CMGProperty*> props;
public:
  SectorData ()
  : name(NULL)
  {
  }
  ~SectorData ();
};

class FieldData {
public:
  char *name;
  int num;
  DsHash<DsStringKey,CMGProperty*> props;
public:
  FieldData ()
  : name(NULL)
  {
  }
  ~FieldData ();
};

typedef DsHash<DsStringKey,WellData *> WellDataArray;
typedef DsHash<int,WellData *> WellNoDataArray;

typedef DsHash<DsStringKey,GroupData *> GroupDataArray;
typedef DsHash<int,GroupData *> GroupNoDataArray;

typedef DsHash<DsStringKey,SectorData *> SectorDataArray;
typedef DsHash<int,SectorData *> SectorNoDataArray;

class ResCMGWellResultLoader : public ResPosWellResultLoader
{
public:
  ResCMGWellResultLoader(CMGDictionary *d);
  ~ResCMGWellResultLoader();
  // virtual methods
  char* GetCompletionName (ResPosModelNew* mdl, 
                           int well_id,
                           int comp_index);
  const char* GetRootFileName () const;
  bool AreGridFilesNewer (const char* filename);
  bool LoadHeader (const char* src, int* model_count, char*** suffixes);
  bool Load(const char *src, ResPosModelNew* mdl);
  const char* GetLoadError () const;
  const char* GetLoadErrorDetails () const;
  const char* GetLoadWarnings () const;
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
  bool LoadCompletionProperty (ResPosModelNew* mdl, int prop_id, int well_id, int comp_index, float* data);
  bool LoadExtraProperty (ResPosModelNew* mdl, int prop_id, float* data);
private:
  bool StoreWellTypes (ResPosModelNew* mdl);
  float GetNullValue () const
  {
    return RES_NULL_VALUE;
  }
  typedef enum {
    WELL_TYPE = 1,
    GROUP_TYPE,
    LAYER_TYPE,
    SECTOR_TYPE,
    FIELD_TYPE
  } ElemType;
  struct UnitData
  {
    UnitData (ResUnit* unit,
              const char* propsymbol,
              PropConvData* convdata);
    ~UnitData ()
    {
      free(m_symbol);
    }
    const char* GetSymbol ()
    {
      return m_symbol;
    }
  private:
    char* m_symbol;
  };
private:
  void WarningMsg (const char *format, ...);
  void BadFileErrorMsg (const char *format, ...);
  void UnsupportedFileErrorMsg (const char *format, ...);
  void SystemErrorMsg (const char *format, ...);
  void StoreErrorDetails (const char *format, va_list ap);
  void StoreWarningDetails (const char *format, va_list ap);
  char* WellFileName () const
  {
    return m_mrf;
  }
  bool LoadBasicInfo(ResPosModelNew* mdl);
  void CreateGroups (ResPosModelNew* mdl);
  bool HasTime () const
  {
    return m_index_time != -1;
  }
  bool WellExists(const char *name);
  bool GroupExists(const char *name);
  WellData* GetWell(const char *name);
  GroupData *GetGroup(const char *name);
  SectorData* GetSector(const char *name);
  
  bool AddWellProperty(CMGWellRecData *recdata, int well_index);
  bool AddGroupProperty (CMGGroupRecData *recdata, int group_index);
  bool AddLayerProperty (CMGLayerRecData *recdata, int layer_index);
  bool AddSectorProperty(CMGRecData *recdata,SectorData *s);
  bool AddElemProperty(CMGRecData *recdata,CMGProperty *p)
  {
    size_t offset = m_mrf_rd->GetCurrentOffset();
    p->AddOffset(offset);
    return m_mrf_rd->Skip(m_float_length); // skip 1 element data
  }
  bool AddFieldProperty(CMGRecData *recdata,FieldData *s);
  
  int ReadIRF (CMGTextReader& rd);
  int ReadTitle(CMGTextReader& rd,char *label);
  int ReadParent(CMGTextReader& rd);
  int ReadGroupName(CMGTextReader& rd);
  int ReadWellName(CMGTextReader& rd);
  int ReadLayerName(CMGTextReader& rd);
  int ReadTime(CMGTextReader& rd);
  int ReadGrid(CMGTextReader& rd);
  int ReadSimulName(CMGTextReader& rd);
  int ReadVersion(CMGTextReader& rd);
  int ReadRunDate(CMGTextReader& rd);
  int ReadCaseId(CMGTextReader& rd);
  int ReadIndexed(CMGTextReader& rd,char *label);
  int ReadXDR(CMGTextReader& rd);
  int ReadFloatLength(CMGTextReader& rd);
  int ReadFile(CMGTextReader& rd);
  int ReadRewind(CMGTextReader& rd);
  int ReadNComp(CMGTextReader& rd);
  int ReadCompName(CMGTextReader& rd);
  int ReadCompPhaseTemplate(CMGTextReader& rd);
  int ReadKDIR(CMGTextReader& rd);
  int ReadInternalUnitTable(CMGTextReader& rd);
  int ReadOutputUnitTable(CMGTextReader& rd);
  int ReadPvtTable(CMGTextReader& rd);
  int ReadGOPermTable(CMGTextReader& rd);
  int ReadWOPermTable(CMGTextReader& rd);
  int ReadSectorName(CMGTextReader& rd);
  int ReadLeaseName(CMGTextReader& rd);
  int ReadSphistNames(CMGTextReader& rd);
  
  int ReadGroupRec(CMGTextReader&rd);
  int ReadWellRec(CMGTextReader&rd);
  int ReadLayerRec(CMGTextReader&rd);
  int ReadSectorRec(CMGTextReader&rd);
  int ReadLeaseRec(CMGTextReader&rd);
  int ReadSeparatorRec(CMGTextReader&rd);
  int ReadRstSpecRec(CMGTextReader&rd, const char* label);
  int ReadCompPropRec(CMGTextReader&rd);
  
  int ReadTimeChr(CMGTextReader& rd);
  int ReadGridXOffset(CMGTextReader& rd);
  int ReadGridYOffset(CMGTextReader& rd);
  int ReadGridRotation(CMGTextReader& rd);
  int ReadGridAxesDirections(CMGTextReader& rd);
  int ReadGridDim(CMGTextReader& rd);
  
  bool ReadRestart(CMGTextReader& rd);
  bool ReadWMRestart(CMGTextReader& rd);
  bool ReadSpecHistory(CMGTextReader& rd);
  bool ReadGridValue(CMGTextReader& rd);
  
  int ReadGroup(CMGTextReader& rd,char *label);
  int ReadWell(CMGTextReader& rd,char *label);
  int ReadLayer(CMGTextReader& rd,char *label);
  int ReadSector(CMGTextReader& rd,char *label);
  int ReadLease(CMGTextReader& rd,char *label);
  int ReadSeparator(CMGTextReader& rd,char *label);
  int ReadCompProp(CMGTextReader& rd,char *label);
  int ReadRstSpec(CMGTextReader& rd,char *label);
  
  int ReadRestartControl(CMGTextReader& rd,char *label);
  int ReadWMRestartControl(CMGTextReader& rd,char *label);
  
  int MakeRecurrentData(ResPosModelNew* mdl, int ts);
  void TimeStepAdded (int ts);
  int InitializeData();

  //int ReadProperty(const char *propname,void **buffer);
  
  int CreateIniProperties();
  int CreateRecProperties();

  int SetWellTimeStep();
  int SetGroupTimeStep();
  int SetCompTimeStep();
  int SetSectorTimeStep();
  int SetFieldTimeStep();
  
  int CreateCornerMaps();
  
  size_t GetNumBytes (const char *packing,
                      ResValueType type,
                      const char *size,
                      bool fixed_component_size)
                      throw(const char*)
  {
    return ResCMGGetNumBytes(&m_dimension_props,
                             packing,
                             size,
                             type,
                             m_float_length,
                             fixed_component_size);
  }
  void AddLayersToWells (ResPosModelNew* mdl);
  void SetWellGroups (ResPosModelNew* mdl);
  int CreateElementPropertyLists(ResPosModelNew* mdl);
  int CreateWellProperties(ResPosModelNew* mdl);
  int CreateGroupProperties(ResPosModelNew* mdl);
  int CreateLayerProperties(ResPosModelNew* mdl);
  int CreateSectorProperties(ResPosModelNew* mdl);
  int CreateFieldProperties(ResPosModelNew* mdl);
  int CreateAdittionalProperties(ResPosModelNew* mdl, ElemType elem,bool has_oil,bool has_water,bool has_gas);
  int CreateAdittionalProperty(ResPosModelNew* mdl, ElemType elem,const char *symbol,
    const char *desc,DsArray<int>* unit);
  bool GetRatePropRecordedTimes (ResPosModelNew* mdl,
                                 const CMGProperty* prop,
                                 const bool* whichsteps,
                                 bool* has_recorded_steps);
  int ReadRateProperty (ResPosModelNew* mdl,
                        const CMGProperty* prop,
                        const bool* whichsteps,
                        double factor_mult,
                        double factor_add,
                        float* data);
  bool GetElemPropRecordedTimes (ResPosModelNew* mdl,
                                 const CMGProperty* prop,
                                 const bool* whichsteps,
                                 bool* has_recorded_steps);
  bool ReadElemProperty (ResPosModelNew* mdl,
                         const CMGProperty* prop,
                         const bool* whichsteps,
                         double factor_mult,
                         double factor_add,
                         float* data);
  bool GetMonthlyRatePropRecordedTimes (ResPosModelNew* mdl,
                                        const CMGProperty* prop,
                                        const bool* whichsteps,
                                        bool* has_recorded_steps);
  bool ReadRateMonthly(ResPosModelNew* mdl, const CMGProperty* prop_o,const bool* whichsteps,float *data);
  bool GetYearlyRatePropRecordedTimes (ResPosModelNew* mdl,
                                       const CMGProperty* prop,
                                       const bool* whichsteps,
                                       bool* has_recorded_steps);
  bool ReadRateYearly(ResPosModelNew* mdl, const CMGProperty* prop_o,const bool* whichsteps,float *data);
  bool GetQLIQRecordedTimes (ResPosModelNew* mdl,
                             const CMGProperty* prop_o,
                             const CMGProperty* prop_w,
                             const bool* whichsteps,
                             bool* has_recorded_steps);
  bool ReadQLIQ(ResPosModelNew* mdl, const CMGProperty* prop_o,const CMGProperty* prop_w,const bool* whichsteps,float *data);
  bool GetRAORecordedTimes (ResPosModelNew* mdl,
                            const CMGProperty* prop_o,
                            const CMGProperty* prop_w,
                            const bool* whichsteps,
                            bool* has_recorded_steps);
  bool ReadRAO(ResPosModelNew* mdl, const CMGProperty* prop_o,const CMGProperty* prop_w,const bool* whichsteps,float *data);
  bool GetWCUTRecordedTimes (ResPosModelNew* mdl,
                             const CMGProperty* prop_o,
                             const CMGProperty* prop_w,
                             const bool* whichsteps,
                             bool* has_recorded_steps);
  bool ReadWCUT(ResPosModelNew* mdl, const CMGProperty* prop_o,const CMGProperty* prop_w,const bool* whichsteps,float *data);
  bool GetRGORecordedTimes (ResPosModelNew* mdl,
                            const CMGProperty* prop_o,
                            const CMGProperty* prop_g,
                            const bool* whichsteps,
                            bool* has_recorded_steps);
  bool ReadRGO(ResPosModelNew* mdl, const CMGProperty* prop_o,const CMGProperty* prop_g,const bool* whichsteps,float *data);
  bool GetRGLRecordedTimes (ResPosModelNew* mdl,
                            const CMGProperty* prop_o,
                            const CMGProperty* prop_w,
                            const CMGProperty* prop_g,
                            const bool* whichsteps,
                            bool* has_recorded_steps);
  bool ReadRGL(ResPosModelNew* mdl, const CMGProperty* prop_o,const CMGProperty* prop_w,const CMGProperty* prop_g,const bool* whichsteps,float *data);
  bool ReadElemPropertyValue(const CMGProperty* prop,
                             double factor_mult,
                             double factor_add,
                             int ts,
                             float *value);
  void AddWell (WellData *w, int index);
  void AddGroup (GroupData *g, int index);
  void AddLayer(CMGLayer *l);
  void AddSector(SectorData *s);

  void MakeConversionData();
  bool ConvertWellProperty(ResPosModelNew* mdl,const DsStringKey& propname,char *desc,int *phase, DsArray<int>* unit);
  bool ConvertLayerProperty(ResPosModelNew* mdl,const DsStringKey& propname,char *desc,int *phase, DsArray<int>* unit);
  bool ConvertGroupProperty(ResPosModelNew* mdl,const DsStringKey& propname,char *desc,int *phase, DsArray<int>* unit);
  bool ConvertFieldProperty(ResPosModelNew* mdl,const DsStringKey& propname,char *desc,int *phase,DsArray<int>* unit);
  bool ConvertRegionProperty(ResPosModelNew* mdl,const DsStringKey& propname,char *desc,int *phase,DsArray<int>* unit);

  bool StoreComponentProperty(ResPosModelNew* mdl, ElemType elem,const char *propname,int compnum,const char *desc,DsArray<int>* unit);
  bool StoreComponentProperties(ResPosModelNew* mdl, ElemType elem,const char *propname,int compnum,const char *desc,int *phase,DsArray<int>* unit);

  char *GetComponentPropName (const char *symbol);

  bool IsFloat(void)
  {
    return (m_float_length == 4);
  }
  bool IsXDR(void)
  {
    return m_xdr;
  }
  bool StoreWellProperty (ResPosModelNew* mdl,
                          const char* symbol,
                          const char* desc,
                          const DsArray<int>* unit);
  bool StoreGroupProperty (ResPosModelNew* mdl,
                           const char* symbol,
                           const char* desc,
                           const DsArray<int>* unit);
  bool StoreRegionProperty (ResPosModelNew* mdl,
                            const char* symbol,
                            const char* desc,
                            const DsArray<int>* unit);
  bool StoreCompletionProperty (ResPosModelNew* mdl,
                                const char* symbol,
                                const char* desc,
                                const DsArray<int>* unit);
  bool StoreFieldProperty (ResPosModelNew* mdl,
                           const char* symbol,
                           const char* desc,
                           const DsArray<int>* unit);
  CMGLayer* GetLayer (int well_id, int index);
  bool SkipRecord (const char* propname, bool is_element_record);
  void FillArrayWithNullValues (ResPosModelNew* mdl, float* data);
  /**
   * Tries to obtain a given group property from a group.
   * Throws an error in case the property is not found.
   */
  const CMGProperty* GetGroupProp (GroupData* g, const char* name) throw(bool);
  const CMGProperty* GetGroupPropNoThrow (GroupData* g, const char* irf_prop);
  const CMGProperty* GetWellProp (WellData* w, const char* irf_prop);
  const CMGProperty* GetLayerProp (CMGLayer* layer, const char* irf_prop);
  const CMGProperty* GetComponentProp (WellData* w, const char* pname);
  const CMGProperty* GetComponentProp (GroupData* g, const char* pname);
  const CMGProperty* GetComponentProp (CMGLayer* layer, const char* pname);
  static const CMGProperty* GetComponentProp (DsHash<DsStringKey,CMGProperty*>& props, const char* pname);
private:
  struct Property
  {
    char* symbol;
    char* desc;
    UnitData* unit;
    double factor_mult;
    double factor_add;
    Property()
    : symbol(NULL)
    , desc(NULL)
    , unit(NULL)
    {
    }
    ~Property()
    {
      free(symbol);
      free(desc);
      if (unit != NULL)
        delete unit;
    }
  };
private:
  char *m_rootname;
  char *m_mrf;              // Main Data File (*.mrf)
  char *m_rrf;              // Rewindable Restart File (*.rrf)
  CMGBinReader *m_mrf_rd;   // reader to Main Data File (*.mrf) 
  CMGBinReader *m_rrf_rd;   // reader to Rewindable Restart File (*.rrf)

  int m_index_time;           // indicates the current time
  int m_max_rec_len;          // maximum physical record length for associated binary 
                                // mrf file.
  TimeDataArray m_time;         // stores time data
  char  m_load_error[4096];         // error while loading, if any
  char  m_load_error_details[4096]; // details on error while loading, if any
  char  m_load_warning_details[4096]; // details on warnings while loading, if any
  int   m_file;
  
  bool m_skip_restart;        // The presence of this record indicates that a reading program
                              // should skip reading RESTART records because the data is for
                              // simulator restart only

  DsArray<CMGGroupRecData*> m_group_rec;    // current group data written for each group
  DsArray<CMGWellRecData*> m_well_rec;      // current well data written for each well
  DsArray<CMGLayerRecData*> m_layer_rec;    // current layer data written for each layer
  DsArray<CMGRecData*> m_sector_rec;        // current sector data written for each sector
  DsArray<CMGRecData*> m_field_rec;
  DsHash<DsStringKey,CMGLayerRecData*> m_prop_name_to_layer_rec;
  DsHash<DsStringKey,CMGWellRecData*> m_prop_name_to_well_rec;
  DsHash<DsStringKey,CMGGroupRecData*> m_prop_name_to_group_rec;
  DsHash<DsStringKey,WellData *> m_name_to_well;
  DsHash<int, char*> m_wellid_to_name;
  DsHash<DsStringKey, int> m_name_to_wellid;
  DsHash<DsStringKey,GroupData *> m_name_to_group;
  DsArray<CMGLayer*> m_layers; // list of layers
  DsHash<DsStringKey,SectorData*> m_name_to_sector;
  DsHash<DsStringKey,FieldData*> m_name_to_field;
  int m_num_complete_storage;  
  CMGDictionary *m_dict;   // Data dictionary
  
  // Time variables
  double m_rtimet;
  char m_initial_date[16];
  double m_rtime;
  /* Dimensioning variables */
  int m_num_sectors;          // Number of sectors (NSECT1)
  int m_num_grids;            // Number of grids (NPTGN)
  int* m_cs_block_type;       // Complete storage to block type (ICSTBC)
  int* m_cs_child_grid;       // Complete storage to child grid (ICSTCG)
  int* m_cs_grid_number;      // Complete storage to grid number (ICSTGN)
  int* m_cs_package_storage;  // Complete storage to packed storage (ICSTPS)
  int* m_cs_parent_block;     // Complete storage to parent block (ICSTPB)
  int* m_ps_complete_storage; // Packed storage to complete storage (IPSTCS)
  int* m_ps_block_type;       // Packed storage to block type (IPSTBT)
  int* m_ps_active;           // Packed storage to active status (IPSTAC)
  bool m_initime;
  /* 
   * Type 1 keywords
   */
  char *m_simname;        // simulator name. The value of string is either 
                          // IMEX,GEM,STARS or CMGPROP
  char *m_version;        // version number. Typically of the form yy.rr 
                          // where yy is the last two digits of the year 
                          // and rr is a release number within year
  char *m_rundate;        // the date the simulator was run to produce the 
                          // data file. Is an string of the form yyyymmdd 
  char *m_title1;         // title 1
  char *m_title2;         // title 2
  char *m_title3;         // title 3
  char* m_full_title;     // full title
  char *m_caseid;         // caseid string
  char *m_parent;         // indicates the irf file is a continuation from 
                          // the file specified (restart run)
  bool  m_indexed_mrf;    // indicates that mrf file is indexed
  bool  m_xdr;            // indicates that mrf file is in XDR format
  int   m_float_length;   // number of bytes of data written in the mrf file 
  bool  m_rewind;         // indicates that the rrf file has been rewound
  
  int m_numx;             // Number of liquid condensible components
  int m_numy;             // Number of fluid components
  int m_numw;             // Number of aqueous components
  int m_numo;             // Number of oleic components
  int m_nsold;            // Number of solid components + 1
  int m_ncomp;            // Total number of components  
  
  char **m_comp_name;     // component name array
  DsArray<bool*> m_comp_phases; // specifies in which phase each component may be
                                // found. 0=water,1=oil,2=gas,3=solid
                          
  DsArray<WellData*> m_wells;
  DsArray<GroupData*> m_groups;
  DsArray<SectorData*> m_sectors;
  FieldData* m_field;

  DsArray<char*> m_lease_rec;
  DsArray<char*> m_separator_rec;
  DsArray<char*> m_comp_rec;
  DsHash<DsStringKey,DsArray<char*>*> m_rstspec_rec;
  DsHash<DsStringKey,Property*> m_symbol_to_well_prop;
  DsHash<DsStringKey,Property*> m_symbol_to_comp_prop;
  DsHash<DsStringKey,Property*> m_symbol_to_group_prop;
  DsHash<DsStringKey,Property*> m_symbol_to_region_prop;
  DsHash<DsStringKey,Property*> m_symbol_to_field_prop;
  DsArray<int> m_ts_to_timedata;
  PropConvData m_wellirf2posp, m_wellposp2irf;
  PropConvData m_regionirf2posp, m_regionposp2irf;
  PropConvData m_groupirf2posp, m_groupposp2irf;

  DsHash<DsStringKey,int>* m_irfkeys;
  DsHash<DsStringKey,bool>* m_noreset_props; // list of properties that cannot be redefined
  DsHash<DsStringKey,int> m_dimension_props;
  DsArray<char*> m_internal_units;
  DsArray<char*> m_output_units;
  char* m_sim_title;
  int m_field_index;
  bool m_has_well;
  bool m_has_group;
  bool m_has_comp;
  bool m_has_sector;
  bool m_has_field;
  bool m_grid_defined;

  bool m_has_field_data;
  bool m_has_well_data;
  bool m_has_group_data;
  bool m_has_sector_data;
  bool m_has_layer_data;

  bool m_any_well_on_def_field_inj; // if any well was attached to Default-Field-INJ
  bool m_any_well_on_def_field_pro; // if any well was attached to Default-Field-PRO
  bool m_any_well_on_def_group_inj; // if any well was attached to Default-Group-INJ
  bool m_any_well_on_def_group_pro; // if any well was attached to Default-Group-PRO

  DsHash<DsStringKey,size_t> m_rec_sizes;
};

