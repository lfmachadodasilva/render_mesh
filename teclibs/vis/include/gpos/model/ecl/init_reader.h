#pragma once
#include <gpos/defines.h>
#include <gpos/model/loadernew.h>
#include <gpos/common/util.h>
#include <ds/array.h>
#include <ds/hash.h>
#include "common.h"

class ECLReader;
class ECLMapProperty;

class ECLInitProperty : public ECLProperty
{
private:
  bool m_is_complete;
  ResValueType m_dtype;
  size_t m_size;
public:
  ECLInitProperty (bool is_complete, int nelems)
  {
    m_is_complete = is_complete;
    m_size = (size_t) nelems;
  }
  ~ECLInitProperty ()
  {
  }
  bool IsCompletProperty ()
  {
    return m_is_complete;
  }

  void SetType (ResValueType dtype)
  {
    m_dtype = dtype;
  }

  ResValueType GetType ()
  {
    return m_dtype;
  }
  size_t GetSize ()
  {
    return m_size;
  }
};

class InitGridData 
{
public:
  InitGridData (const char* name)
  : m_nx(-1)
  , m_ny(-1)
  , m_nz(-1)
  , m_unit(NULL)
  , m_nact(-1)
  {
    m_gridname = PSUtil::StrDup(name);
    m_props = new DsArray<ECLInitProperty*>;
    m_props_to_index = new DsHash<DsStringKey, int>;
  }
  ~InitGridData ()
  {
    FREE_AND_SET_NULL(m_gridname);
    FREE_AND_SET_NULL(m_unit);
    int n = m_props->Size();
    for(int i=0; i<n; i++) {
      ECLInitProperty* prop = m_props->Get(i);
      DELETE_AND_SET_NULL(prop);
    }
    DELETE_AND_SET_NULL(m_props);
    DELETE_AND_SET_NULL(m_props_to_index);
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
  void AddProperty (const char* name, ECLInitProperty *p)
  {
    int index = m_props->Size();
    m_props->Append(p);
    m_props_to_index->Set(name, index);
  }
  ECLInitProperty* GetProperty (const char *name)
  {
    if (!m_props_to_index->Find(name))
      return NULL;
    int index = m_props_to_index->Get(name);
    assert(m_props->ValidIndex(index));
    return m_props->Get(index);
  }
  ECLInitProperty* GetProperty (int index)
  {
    assert(m_props->ValidIndex(index));
    return m_props->Get(index);
  }
  int GetNumProperties ()
  {
    return m_props->Size();
  }
  bool PropertyExists (const char* name)
  {
    if (!m_props_to_index->Find(name)) 
      return false;
    int index = m_props_to_index->Get(name);
    if (!m_props->ValidIndex(index))
      return false;
    return true;
  }
private:
  int m_nx;
  int m_ny;
  int m_nz;
  char* m_gridname;
  char* m_unit;
  int m_nact;
  DsArray<ECLInitProperty*>* m_props;
  DsHash<DsStringKey, int>* m_props_to_index;
};

class INITReader : public ECLFormatReader
{
public:
  INITReader (const char* rootname, 
               ResECLError *errors, 
               //const char* inidate,
               float nullvalue);
  ~INITReader();
  bool ReadKeywords (ResPosLoaderNew* loader);
  bool ValidateFiles (bool required);
  int CountProperties();
  ECLMapProperty* GetProperty (int index);
  bool LoadProperty (int loader_index,
                     const char* symbol, 
                     int ts, 
                     DsHash<DsStringKey, float*>& prop_by_grid, 
                     bool is_complete_prop,
                     size_t propsize);
  bool FileExists ();
  void GridDimensions (int* nx, int* ny, int* nz);
  int CountRootActiveCells ();
  int CountActiveCells ();
  bool IsDualPorosity ();
  void GetInitDate (int* day, int* month, int* year);
  char* GetInitialDate ();
  bool IsLoaded ();
private:
  void ReadINTEHEAD (ECLReader *rd, int nelems) throw (bool);
  void ReadLOGIHEAD (ECLReader *rd, int nelems) throw (bool);
  void ReadDOUBHEAD (ECLReader *rd, int nelems) throw (bool);
  void ReadPORV (ECLReader* rd, int nelems) throw (bool);
  void ReadLGR (ECLReader *rd) throw (bool);
  void ReadENDLGR (ECLReader *rd) throw (bool);
  void SetCurrentGrid (const char* name);
  void ReadInitialProperty (ECLReader *rd, const char* keyword, int nelems, const char* dtype);
  InitGridData* GetGridData ();
  float GetNullValue ()
  {
    return m_nullvalue;
  }
  bool ReadPropertyValue(ECLMapProperty* prop,
                         double factor_mult,
                         double factor_add,
                         float*& values,
                         size_t propsize,
                         size_t offset_to_skip);
private:
  ResECLError* m_errors;
  char *m_filename;                // INIT filename
  ECLReader *m_init_rd;        // INIT Reader
  float m_nullvalue;
  int m_iprog;
  DsHash<DsStringKey, InitGridData*>* m_grid_to_initdata;
  bool m_lgr_init;
  char* m_current_grid;
  bool m_radial_model;
  bool m_dual_porosity_model;
  StringArray* m_grid_list;
  int m_init_day;
  int m_init_month;
  int m_init_year;
  bool m_loaded;
};

