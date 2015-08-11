#pragma once

#include <gpos/model/loadernew.h>
#include <gpos/model/unit.h>
#include <gpos/common/util.h>
#include <gpos/defines.h>
#include <ds/array.h>
#include <ds/hash.h>
#include "reader.h"

#define FREE_AND_SET_NULL(p) { PSUtil::Free(p); p = NULL;}
#define DELETE_AND_SET_NULL(p) { if (p) {delete p; p = NULL;} }

#define STRING_SIZE  8
#define STRINGS_PER_BLOCK  105
#define INTEGERS_PER_BLOCK  1000

#define MAIN_GRID "main"

//#define REFINED_GRID 0

class ECLReader;

struct ECLRefinement
{
  int nri;
  int nrj;
  int nrk;
  int i0;
  int j0;
  int k0;
  int i1;
  int j1;
  int k1;
};

typedef DsArray<ECLRefinement*> ECLRefinementArray;

#define ECLIPSE100 100
#define ECLIPSE300 300
#define ECLIPSE300_THERMAL 500

static const char *MapPropertiesDesc[] = {
  "Pressão",
  "Saturação de Óleo",
  "Saturação de água",
  "Saturação de gás",
  "Grau API inicial do óleo",
  "Razão de solubilidade",
  "Óleo in-place",
  "Água in-place",
  "Gás in-place",
  "Volume poroso",
  "Tamanho da célula na direção X",
  "Tamanho da célula na direção Y",
  "Tamanho da célula na direção Z",
  "Permeabilidada na direção X",
  "Permeabilidade na direção Y",
  "Permeabilidade na direção Z",
  "Multiplicador de transmissibilidade na direção X",
  "Multiplicador de transmissibilidade na direção Y",
  "Multiplicador de transmissibilidade na direção Z",
  "Porosidade",
  "Razão NET to GROS",
  "Profundidade do topo da célula",
  "Profundidade do centro da célula",
  "Transmissibilidade na direção X",
  "Transmissibilidade na direção Y",
  "Transmissibilidade na direção Z",
  "Volume poroso mínimo",
  "Multiplicador de volume poroso",
  "Multiplicador de transmissibilidade (direção X-)",
  "Multiplicador de transmissibilidade (direção Y-)",
  "Multiplicador de transmissibilidade (direção Z-)",
  "Critical oil-in-water saturation"
};

//* 'IntArray' Type
// Represents an array of int.
typedef DsArray<int> IntArray;

//* 'DoubleArray' Type
// Represents an array of double.
typedef DsArray<double> DoubleArray;

//* 'StringArray' Type
// Represents an array of char*.
typedef DsArray<char*> StringArray;

typedef enum {
} SMSPECExtraKeys;

typedef enum {
  RESTART=1,
  DIMENS,
  KEYWORDS,
  WGNAMES,
  NAMES,
  NUMS,
  LGRS,
  NUMLX,
  NUMLY,
  NUMLZ,
  LENGTHS,
  LENUNITS,
  UNITS,
  STARTDAT,
  LGRNAMES,
  LGRVEC,
  LGRTIMES,
  RUNTIMEI,
  RUNTIMED,
  STEPRESN,
  NUM_SMSPEC_KEYS
} SMSPECKeywords;

typedef enum {
  SEQHDR = 1,
  MINISTEP,
  PARAMS,
  NUM_SUMMARY_KEYS
} SUMMARYKeywords;

typedef enum {
  GRID_DIMENS = 1,
  GRID_RADIAL,
  GRID_BOXORIG,
  GRID_MAPUNITS,
  GRID_MAPAXES,
  GRID_GRIDUNIT,
  GRID_COORDS,
  GRID_CORNERS,
  GRID_LGR,
  GRID_LGRILG,
  GRID_NNCHEAD,
  GRID_NNC1,
  GRID_NNC2,
  GRID_NNCL,
  GRID_NNCG,
  GRID_NNCHEADA,
  GRID_NNA1,
  GRID_NNA2,
  NUM_GRID_KEYS
} GRIDKeywords;

typedef enum {
  RST_SEQNUM = 1,
  RST_INTEHEAD,
  RST_LOGIHEAD,
  RST_DOUBHEAD,
  RST_IGRP,
  RST_ISEG,
  RST_IWEL,
  RST_ZWEL,
  RST_ICON,
  RST_HIDDEN,
  RST_ZTRACER,
  RST_DRAINAGE,
  RST_LGRNAMES,
  RST_LGR,
  RST_LGRHEADI,
  RST_LGRHEADQ,
  RST_LGRHEADD,
  RST_LGRJOIN,
  RST_ENDLGR,
  RST_ZGRP,
  RST_STARTSOL,
  RST_ENDSOL,
  NUM_RESTART_KEYS
} RESTARTKeywords;

typedef enum {
  EGRID_FILEHEAD = 1,
  EGRID_MAPUNITS,
  EGRID_MAPAXES,
  EGRID_GRIDUNIT,
  EGRID_GRIDHEAD,
  EGRID_ENDGRID,
  EGRID_LGR,
  EGRID_LGRPARNT,
  EGRID_LGRSGRID,
  EGRID_ENDLGR,
  EGRID_BOXORIG,
  EGRID_COORD,
  EGRID_COORDSYS,
  EGRID_ZCORN,
  EGRID_ACTNUM,
  EGRID_CORSNUM,
  EGRID_HOSTNUM,
  NUM_EGRID_KEYS
} EGRIDKeywords;

typedef enum {
  INIT_SEQNUM = 1,
  INIT_INTEHEAD,
  INIT_LOGIHEAD,
  INIT_DOUBHEAD,
  INIT_PORV,
  INIT_LGR,
  INIT_LGRHEADI,
  INIT_LGRHEADQ,
  INIT_LGRHEADD,
  INIT_LGRSGONE,
  INIT_TABDIMS,
  INIT_TAB,
  INIT_CON,
  INIT_TRANNNC,
  INIT_DIFFNNC,
  INIT_HEATNNC,
  INIT_TRANGL,
  INIT_LGRJOIN,
  INIT_TRANLL,
  NUM_INIT_KEYS
} INITKeywords;

typedef enum {
  KDIR_UP,
  KDIR_DOWN
} KDirection;

ResValueType ResECLGetDataType (const char *s);

void ResECLBuildSMSPECKeyToEnum (DsHash<DsStringKey,int>*& keys);

void ResECLBuildSUMMARYKeyToEnum (DsHash<DsStringKey,int>*& keys);

void ResECLBuildRESTARTKeyToEnum (DsHash<DsStringKey,int>*& keys);

void ResECLBuildGRIDKeyToEnum (DsHash<DsStringKey,int>*& keys);

void ResECLBuildEGRIDKeyToEnum (DsHash<DsStringKey,int>*& keys);

void ResECLBuildINITKeyToEnum (DsHash<DsStringKey,int>*& keys);

void ResECLFreeArray (DsArray<char*>* var);

void ResECLReadStringList (ECLReader *rd, char** list, int nlist) throw (bool);
void ResECLReadStringArray (ECLReader *rd, StringArray* list, int nlist) throw (bool);
void ResECLReadIntegerList (ECLReader *rd, int*& list, size_t nlist) throw (bool);

void ResECLReadRealList (ECLReader *rd, float*& list, size_t nlist) throw (bool);
void ResECLReadRealList (ECLReader *rd, 
                         float*& list, 
                         size_t nlist,
                         double factor_mult,
                         double factor_add ) throw (bool);
void ResECLReadDoubleList (ECLReader *rd, double* list, int nlist) throw (bool);
void ResECLReadReal (ECLReader *rd, float *values, int n) throw (bool);

void ResECLSkipInfo (ECLReader *rd, size_t nelems, const char *dtype) throw (bool);
void ResECLSkipReal (ECLReader *rd, int nelems) throw (bool);
void ResECLSkipString (ECLReader *rd, int nelems) throw (bool);
void ResECLSkipInt (ECLReader *rd, int nelems) throw (bool);
void ResECLSkipDouble (ECLReader *rd, int nelems) throw (bool);

void ResECLBuildDefaultUnitsTable (DsHash<DsStringKey,char*>*& unit_table);
void ResECLReleaseDefaultUnitsTable (DsHash<DsStringKey,char*>*& unit_table);

size_t ResECLFloatValueOffset (int pos, int nlist);
char* ResECLReadString (ECLReader *rd) throw (bool);

const char* ResECLGetPropertyDesc (const char* symbol);
const char* ResECLGetPropertyUnit (const char* symbol);

void ResECLReleaseFloatHash (DsHash<DsStringKey, float*>&);
//~ typedef enum {
  //~ KDIR_UP,
  //~ KDIR_DOWN
//~ } KDirection;

typedef struct {
  int   ts;
  double time;
  int day;
  int month;
  int year;
  char *time_str;
  char *date_str;
  bool maptime;
  bool welltime;
  bool grouptime;
  bool comptime;
  bool sectortime;
  bool fieldtime;
} TimeData;

class ECLProperty 
{
private:
  char* m_symbol;
  char* m_desc;
  char* m_unit;
  double m_factor_mult;
  double m_factor_add;
  int m_pos;
  DsArray<size_t>* m_offset;
  bool complete;
public:
  ECLProperty()
  : m_symbol(NULL)
  , m_desc(NULL)
  , m_unit(NULL)
  , m_factor_mult(1)
  , m_factor_add(0)
  {
    m_offset = new DsArray<size_t>;
  }

  ~ECLProperty()
  {
    FREE_AND_SET_NULL(m_symbol);
    FREE_AND_SET_NULL(m_desc);
    FREE_AND_SET_NULL(m_unit);
    DELETE_AND_SET_NULL(m_offset);
  }

  void SetSymbol (const char *s)
  {
    m_symbol = PSUtil::StrDup(s);
  }

  void SetDesc (const char *s)
  {
    m_desc = PSUtil::StrDup(s);
  }

  void SetUnit (const char *u, double fmult, double fadd)
  {
    m_unit = PSUtil::StrDup(u);
    m_factor_mult = fmult;
    m_factor_add = fadd;
  }

  void SetPosition (int position)
  {
    m_pos = position;
  }

  const char* GetSymbol ()
  {
    return m_symbol;
  }

  const char* GetDesc ()
  {
    return m_desc;
  }

  const char* GetUnit ()
  {
    return m_unit;
  }

  void GetUnitFactors (double* fmult, double* fadd)
  {
    *fmult = m_factor_mult;
    *fadd = m_factor_add;
  }

  int GetPosition ()
  {
    return m_pos;
  }

  void AddOffset(size_t offset)
  {
    m_offset->Append(offset);
  }
   
  void AddOffset (size_t offset, int ts)
  {
    m_offset->ResizeAndSetConst(ts, -1);
    m_offset->Insert(offset, ts);
  }
  
  bool GetOffset (int i, size_t* ret) const
  {
    int n = m_offset->Size();
    if (i >= n)
      return false;
    *ret = m_offset->Get(i);
    return true;
  }

  size_t GetOffset (int i) const
  {
    int n = m_offset->Size();
    size_t ret = -1;
    if (i < n)
      ret = m_offset->Get(i);
    if (ret != (size_t)-1)
      return ret;
    // Property was not written in this ts
    // find an earlier ts with valid offset
    int taux = i-1;
    while (taux >= n) taux--;
    while (taux >= 0 && (ret = m_offset->Get(taux)) == (size_t)-1) taux--;
    if (taux < 0)
      return -1;
    return ret;
  }
}; 

typedef DsArray<ECLProperty*> ECLPropertyArray;

class ResECLError 
{
  public:
    ResECLError();
    ~ResECLError();
    void BadFileErrorMsg (const char *format, ...);
    void StoreErrorDetails (const char *format, va_list va);
    void UnsupportedFileErrorMsg (const char *format, ...);
    void SystemErrorMsg (const char *format, ...);
    const char* GetLoadError () const;
    const char* GetLoadErrorDetails () const;
    const char* GetLoadWarnings () const;
  private: 
    char  m_load_error[10000000];         // error while loading, if any
    char  m_load_error_details[10000000]; // details on error while loading, if any
    char  m_load_warnings[10000000];      // warnings while loading, if any
};

void ResECLReleasePropHash (DsHash<DsStringKey,ECLProperty*>& h);

void ResECLGetPropertyUnitFactors(const char* keyword,
                                  const char* u, 
                                  double* factor_mult, 
                                  double* factor_add);

void ResECLReleaseRefinement (ECLRefinementArray* refinement);
void ResECLReleaseStringArray (StringArray* s);

class ECLMapProperty : public ECLProperty
{
private:
  bool m_is_complete;
  ResValueType m_dtype;
  size_t m_size;
public:
  ECLMapProperty (bool is_complete, int nelems)
  {
    m_is_complete = is_complete;
    m_size = (size_t) nelems;
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

class ECLFormatReader
{
public:
  ECLFormatReader ()
  : m_refcount(1)
  {
  }
  void IncRef ()
  {
    m_refcount++;
  }
  void DecRef ()
  {
    if ((--m_refcount) == 0)
      delete this;
  }
protected:
  virtual ~ECLFormatReader ()
  {
  }
private:
  int m_refcount;
};

class ECLGridReader : public ECLFormatReader
{
public:
  ECLGridReader ()
  {
  }
  virtual bool ReadKeywords (ResPosLoaderNew* loader) = 0;
  virtual bool ValidateFiles(bool required) = 0;
  virtual bool IsCornerPoints () = 0;
  virtual void GetRootDimensions(int* ni, int* nj, int* nk) = 0;
  virtual bool FileExists () = 0;
  virtual void GetCellVertices(int index, float coords[24]) = 0;
  virtual void GetRootActiveCells (int loader_index, DsArray<int>& active_cells) = 0;
  virtual const char* GetCoordinatesUnit () = 0;
  virtual void BuildRefinementStructure (ECLRefinementArray* refinements) = 0;
  virtual void GetActiveCells (int loader_index, DsArray<int>& active_cells) = 0;
  virtual int CountTotalCells () = 0;
  virtual int CountActiveCells (int loader_index) = 0;
  virtual int CountRootActiveCells () = 0;
  virtual bool IsLoaded () = 0;
  virtual char* GetCellRefinementData (int icell, int* index) = 0;
  virtual bool IsRefinedModel () = 0;
protected:
  ~ECLGridReader()
  {
  }
private:
};

void ResECLReleasePropertyArray(ECLPropertyArray*& a);

size_t ResECLNumBytes (size_t nelems, const char *dtype);
