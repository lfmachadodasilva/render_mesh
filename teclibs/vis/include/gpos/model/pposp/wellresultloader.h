#pragma once

#include <gpos/model/loadernew.h>
#include <gpos/defines.h>
#include <ds/array.h>
#include <ds/hash.h>
#include <stdio.h>

class PPOSPReader;

class ResPPOSPWellResultLoader : public ResPosWellResultLoader
{
public:
  ResPPOSPWellResultLoader ();
  ~ResPPOSPWellResultLoader ();
  // implemented virtual methods
  bool LoadHeader (const char* src, int* model_count, char*** suffixes);
  bool Load (const char *src, ResPosModelNew* mdl);
  const char* GetLoadError () const
  {
    return "Arquivos de modelo .DAM, .DAP ou .PPOSP inválidos ou inexistentes";
  }
  bool GetWellPropRecordedSteps (ResPosModelNew* mdl, int prop_id, int well_id, bool* has_recorded_steps);
  bool GetCompletionPropRecordedSteps (ResPosModelNew* mdl, int prop_id, int well_id, int comp_index, bool* has_recorded_steps);
  bool GetGroupPropRecordedSteps (ResPosModelNew* mdl, int prop_id, int group_id, bool* has_recorded_steps);
  bool GetRegionPropRecordedSteps (ResPosModelNew* mdl, int prop_id, int region_id, bool* has_recorded_steps);
  bool GetFieldPropRecordedSteps (ResPosModelNew* mdl, int prop_id, bool* has_recorded_steps);
  bool GetExtraPropRecordedSteps (ResPosModelNew* mdl, int prop_id, bool* has_recorded_steps);
  bool LoadWellProperty (ResPosModelNew* mdl, int prop_id, int well_id, float* data);
  bool LoadCompletionProperty (ResPosModelNew* mdl,
                               int prop_id,
                               int well_id,
                               int comp_index,
                               float* data);
  bool LoadGroupProperty (ResPosModelNew* mdl, int prop_id, int group_id, float* data);
  bool LoadRegionProperty (ResPosModelNew* mdl, int prop_id, int region_id, float* data);
  bool LoadFieldProperty (ResPosModelNew* mdl, int prop_id, float* data);
  bool LoadExtraProperty (ResPosModelNew* mdl, int prop_id, float* data);
private:
  float GetNullValue () const
  {
    return 97654320.0;
  }
  char* WellFileName () const
  {
    return m_dam_file;
  }
  bool LoadBasicInfo (ResPosModelNew* mdl);
  int  ReadBaseFile (ResPosModelNew* mdl, PPOSPReader& rd);
  int  ReadINFBASIC (ResPosModelNew* mdl, PPOSPReader& rd);
  int  ReadTITSIMUL (ResPosModelNew* mdl, PPOSPReader& rd);
  int  ReadINFGERAL (ResPosModelNew* mdl, PPOSPReader& rd);
  bool SkipMapPropDesc (PPOSPReader& rd);
  bool SkipPROPMAPI (ResPosModelNew* mdl, PPOSPReader& rd);
  bool SkipPROPMAPS (ResPosModelNew* mdl, PPOSPReader& rd);
  bool ReadPROPMAP  (ResPosModelNew* mdl, PPOSPReader& rd, char type, int nx, int ny, int nz, int nact);
  int  SkipTIMEMAPA (ResPosModelNew* mdl, PPOSPReader& rd);
  int  ReadUNIDPROP (ResPosModelNew* mdl, PPOSPReader& rd);
  int  ReadPROPCOMP (ResPosModelNew* mdl, PPOSPReader& rd);
  int  ReadPROPPOCO (ResPosModelNew* mdl, PPOSPReader& rd);
  int  ReadDEFPOCOS (ResPosModelNew* mdl, PPOSPReader& rd);
  int  ReadTIMEPOCO (ResPosModelNew* mdl, PPOSPReader& rd);
  int  ReadPROPGRUP (ResPosModelNew* mdl, PPOSPReader& rd);
  int  ReadDEFGRUPO (ResPosModelNew* mdl, PPOSPReader& rd);
  int  ReadPROPBLOC (ResPosModelNew* mdl, PPOSPReader& rd);
  int  ReadDEFBLOCO (ResPosModelNew* mdl, PPOSPReader& rd);
  int  ReadPROPCAMP (ResPosModelNew* mdl, PPOSPReader& rd);
  int  ReadDEFCAMPO (ResPosModelNew* mdl, PPOSPReader& rd);
  int LoadHeader (
    PPOSPReader     &rd,
    const char      *keyword,
    const char      *symbol,
    ResValueType  type,
    float           *pnullreal
  );
  int CheckHeader (PPOSPReader &rd, const char *keyword)
  {
    return LoadHeader (rd,keyword,NULL,RES_TYPE_REAL,NULL);
  }
private:
  struct Property
  {
    char* symbol;
    char* desc;
    ResValueType vtype;
    int unit;
    int offset;
    Property()
    : symbol(NULL)
    , desc(NULL)
    {
    }
    ~Property()
    {
      free(symbol);
      free(desc);
    }
  };
  struct TimeStep
  {
    double ndays;
    int day;
    int month;
    int year;
  };
  struct Completion
  {
    int i;
    int j;
    int k;
    int offset;
  };
  struct Well
  {
    char* name;
    DsArray<Completion> completions;
    int offset;
    Well()
    : name(NULL)
    {
    }
    ~Well()
    {
      free(name);
    }
  };
  struct Group
  {
    char* name;
    int offset;
    Group()
    : name(NULL)
    {
    }
    ~Group()
    {
      free(name);
    }
  };
  struct Region
  {
    char* name;
    int offset;
    Region()
    : name(NULL)
    {
    }
    ~Region()
    {
      free(name);
    }
  };
private:
  void PrepareFieldPropertyOffsets (ResPosModelNew* mdl);
  void PrepareGroupPropertyOffsets (ResPosModelNew* mdl);
  void PrepareRegionPropertyOffsets (ResPosModelNew* mdl);
  void PrepareWellPropertyOffsets (ResPosModelNew* mdl);
  void PrepareCompletionPropertyOffsets (ResPosModelNew* mdl);
  void StoreWellProperty (Property* p);
  void StoreCompletionProperty (Property* p);
  void StoreGroupProperty (Property* p);
  void StoreRegionProperty (Property* p);
  void StoreFieldProperty (Property* p);
  Property* GetCompletionProperty (const char* symbol);
  Property* GetGroupProperty (const char* symbol);
  Property* GetRegionProperty (const char* symbol);
  Property* GetFieldProperty (const char* symbol);
  Property* GetWellPropertyData (ResPosModelNew* mdl, int prop_id);
  Property* GetCompletionPropertyData (ResPosModelNew* mdl, int prop_id);
  Property* GetGroupPropertyData (ResPosModelNew* mdl, int prop_id);
  Property* GetRegionPropertyData (ResPosModelNew* mdl, int prop_id);
  Property* GetFieldPropertyData (ResPosModelNew* mdl, int prop_id);
  Well* GetWellData (int well_id);
  Group* GetGroupData (int group_id);
  Region* GetRegionData (int region_id);
  bool ReadAndConvertIntArray (int numvalues, float* data);
  const char* GetUnitSymbol (int unit_index);
  void StoreWellTypes (ResPosModelNew* mdl);
private:
  char *m_rootname;
  int m_nullint;    // value that corresponds to a null value.
  char *m_dam_file; // well data file
  DsArray<Property*> m_well_props;
  DsArray<Property*> m_comp_props;
  DsArray<Property*> m_group_props;
  DsArray<Property*> m_region_props;
  DsArray<Property*> m_field_props;
  DsHash<DsStringKey,Property*> m_well_props_n;
  DsHash<DsStringKey,Property*> m_comp_props_n;
  DsHash<DsStringKey,Property*> m_group_props_n;
  DsHash<DsStringKey,Property*> m_region_props_n;
  DsHash<DsStringKey,Property*> m_field_props_n;
  DsArray<Well*> m_wells;
  DsArray<Group*> m_groups;
  DsArray<Region*> m_regions;
  DsArray<int> m_temp_int;
  PPOSPReader* m_reader; // reader to the binary element data file
  DsArray<ResUnit*> m_units;
  int m_simulator_unit;
  int m_max_unit_found;
  int m_field_offset;
  bool m_is_intel;
};

