#pragma once

#include <gpos/model/loadernew.h>
#include <gpos/defines.h>
#include <ds/array.h>
#include <ds/hash.h>

class PPOSPReader;

class ResPPOSPMapResultLoader : public ResPosMapResultLoader
{
public:
  ResPPOSPMapResultLoader ();
  virtual ~ResPPOSPMapResultLoader ();
  void GetRootGridDimensions (int* ni, int* nj, int* nk);
  bool IsInactiveZCorrect () const
  {
    return m_inactive_correct;
  }
  // virtual methods
  bool LoadHeader (const char* src, int* model_count, char*** suffixes);
  bool Load (const char* src, ResPosModelNew* mdl);
  const char* GetLoadError () const
  {
    return "Arquivos de modelo .DAM, .DAP ou .PPOSP inválidos ou inexistentes";
  }
  bool LoadIniProperty (ResPosModelNew* mdl, int prop_id, float* data);
  bool LoadRecProperty (ResPosModelNew* mdl, int prop_id, int ts, float* data);
private:
  int GetRecPropertyCount ();
  const char* GetRootFileName () const;
  bool AreGridFilesNewer (const char* filename);
  bool LoadBasicInfo (ResPosModelNew* mdl);
  char* MapFileName () const
  {
    return m_dam_file;
  }
  int ReadBaseFile (ResPosModelNew* mdl, PPOSPReader& rd);
  int ReadINFBASIC (ResPosModelNew* mdl, PPOSPReader& rd);
  int ReadTITSIMUL (ResPosModelNew* mdl, PPOSPReader& rd);
  int ReadINFGERAL (PPOSPReader& rd);
  bool ReadPropDesc(PPOSPReader & rd,
                    char symbol[5],
                    char desc[81],
                    ResValueType *dtype,
                    int* unit);
  bool ReadPROPMAPI (ResPosModelNew* mdl, PPOSPReader& rd, int* numiniprops, int* numcompletemaps);
  bool ReadPROPMAPS (ResPosModelNew* mdl, PPOSPReader& rd, int numiniprops, int numcompletemaps);
  bool ReadPROPMAP  (PPOSPReader& rd, char type);
  int ReadTIMEMAPA (ResPosModelNew* mdl, PPOSPReader& rd);
  int ReadUNIDPROP (PPOSPReader& rd);
  int ReadPROPCOMP (PPOSPReader& rd);
  int ReadPROPPOCO (PPOSPReader& rd);
  int ReadDEFPOCOS (PPOSPReader& rd);
  int ReadTIMEPOCO (PPOSPReader& rd);
  int ReadPROPGRUP (PPOSPReader& rd);
  int ReadDEFGRUPO (PPOSPReader& rd);
  int ReadPROPBLOC (PPOSPReader& rd);
  int ReadDEFBLOCO (PPOSPReader& rd);
  int ReadPROPCAMP (PPOSPReader& rd);
  int ReadDEFCAMPO (PPOSPReader& rd);
  int LoadHeader (
    PPOSPReader& rd,
    const char* keyword,
    const char* symbol,
    ResValueType type,
    float* pnullreal
  );
  int CheckHeader (PPOSPReader& rd,
                   const char* keyword)
  {
    return LoadHeader(rd, keyword, NULL, RES_TYPE_REAL, NULL);
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
  struct IniProperty : public Property
  {
    bool complete;
  };
  struct RecProperty : public Property
  {
  };
private:
  void StoreIniProperty (ResPosModelNew* mdl, IniProperty* p);
  void StoreRecProperty (ResPosModelNew* mdl, RecProperty* p);
  IniProperty* GetIniPropertyData (ResPosModelNew* mdl, int prop_id);
  RecProperty* GetRecPropertyData (ResPosModelNew* mdl, int prop_id);
  int GetDimension (ResPosModelNew* mdl, IniProperty* p);
  bool FindOutNullReal (ResPosModelNew* mdl, PPOSPReader& rd);
  bool GetNullRealFromFile (ResPosModelNew* mdl, PPOSPReader& rd, Property* p, const char* keyword);
  bool SkipWellPropDefinitions (PPOSPReader& rd);
  bool ReadAndConvertIntArray (PPOSPReader& rd, int numvalues, float* data);
  const char* GetUnitSymbol (int unit_index);
private:
  char* m_rootname;
  int m_nullint;    // value that corresponds to a null value.
  float m_nullreal;
  char* m_dam_file; // map data file
  DsArray<IniProperty*> m_ini_props;
  DsArray<RecProperty*> m_rec_props;
  DsHash<DsStringKey,IniProperty*> m_ini_props_n;
  DsHash<DsStringKey,RecProperty*> m_rec_props_n;
  DsArray<int> m_temp_int;
  int m_nx, m_ny, m_nz;
  DsArray<ResUnit*> m_units;
  int m_simulator_unit;
  int m_max_unit_found;
  bool m_is_intel;
  bool m_inactive_correct;
};

