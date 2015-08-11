#pragma once

#include <gpos/model/loadernew.h>
#include <gpos/model/unit.h>
#include <gpos/common/util.h>
#include <gpos/defines.h>
#include <ds/array.h>
#include <ds/hash.h>

#define UNKNOWN_KEYWORD_FORMAT "Palavra-chave '%s' desconhecida.\nA versão do simulador usado é mais nova do que a versão do dicionário de dados.\nEntre em contato com o suporte do Geresim (suporte-geresim@tecgraf.puc-rio.br)"

/*
 * GRID TYPE PARAMETERS
 *
 * Usage:  Grid type for grid number IGN is IGNTGT(IGN).
 * Example:  IGNTGT(IGN) .EQ. IGTHYB is true only for hybrid grid.
 *    IGTCAR  - Fundamental Cartesian
 *    IGTCYL  - Fundamental Cylindrical
 *    IGTCVF  - Fundamental CVFE (Control-Volume Finite Element)
 *    IGTCOR  - Fundamental Corner Point Grid
 *    IGTREF  - Cartesian refined in Cartesian parent
 *    IGTRCY  - Cylindrically refined in Cylindrical parent
 *    IGTHYB  - Cylindrically refined in Cartesian parent
 *    IGTWBO  - Wellbore
 *    IGTWEL  - Well equation
 *    IGTMNC  - MINC refinement
 *    IGTSUB  - Subdomain refinement
 *    IGTTUB  - Tubing in a circulating well
 */
typedef enum {
  IGTCAR =  1, 
  IGTCYL =  2, 
  IGTREF =  3, 
  IGTHYB =  4,
  IGTWBO =  5, 
  IGTWEL =  6, 
  IGTMNC =  7, 
  IGTSUB =  8,
  IGTTUB =  9, 
  IGTRCY =  10, 
  IGTCVF =  11, 
  IGTCOR =  12
} GridTypes;

typedef enum {
  AREAL = 0,          // Fundamental Cartesian
  RADIAL,             // Fundamental Cylindrical
  CVFE,               // Fundamental CVFE (Control-Volume Finite Element)
  CORNER,             // Fundamental Corner Point Grid
  CARFIN              // Cartesian refined in Cartesian parent
} SimulationTypes;

/*
 * BLOCK TYPE PARAMETERS
 *    Usage:  Block type for block number IPS is IPSTBT(IPS).
 *    Example:  IPSTBT(IPS) .EQ. IBTWBO is true only for a
 *              discretized wellbore block.
 *    Note:  IBTNUL and IBTPNC are negative, as IPSTBT is also used to
 *           store fault numbers (as positive integers).
 *
 *    IBTNUL  - null block
 *    IBTPNC  - pinch out block (special type of null)
 *    IBTSP   - reservoir block in single porosity system
 *    IBTFR   - fracture block in dual porosity grid
 *    IBTMA   - matrix block in dual porosity grid
 *    IBTMNC  - matrix MINC block
 *    IBTSUB  - matrix subdomain block
 *    IBTWEL  - "block" for well equation(s)
 *    IBTWBO  - wellbore "block"
 *    IBTTUB  - tubing "block"
 *    IBTZP   - zero porosity block (thermal model)
 */
typedef enum {
  IBTNUL = -1, 
  IBTPNC = -2, 
  IBTFR  =  1, 
  IBTMA  =  2,
  IBTWEL =  3, 
  IBTWBO =  4, 
  IBTZP  =  5, 
  IBTTUB =  6,
  IBTMNC =  7, 
  IBTSUB =  8, 
  IBTSP  =  9
} BlockTypes;

typedef enum {
  SIMNAME=1,
  VERSION,
  RUNDATE,
  TITLE1,
  TITLE2,
  TITLE3,
  CASEID,
  PARENT,
  INDEXED,
  INDEX64,
  XDR,
  FLOATLENGTH,
  KFILE,
  REWIND,
  NCOMP,
  COMPNAME,
  COMPPHASETEMPLATE,
  KDIR,
  INTERNALUNITTABLE,
  OUTPUTUNITTABLE,
  MAXRECLEN,
  SKIPRESTART,
  GROUPNAME,
  WELLNAME,
  LAYERNAME,
  SECTORNAME,
  LEASENAME,
  SPHISTNAMES,
  TIME,
  STOP,
  TIMCHR,
  GRIDXOFFSET,
  GRIDYOFFSET,
  GRIDROTATION,
  GRIDAXESDIRECTIONS,
  GRIDDIM,
  SIMULATORDONE,
  GRID,
  RESTART,
  WMRESTART,
  SPECHISTORY,
  GRIDVALUE,
  GROUPREC,
  WELLREC,
  LAYERREC,
  SEPARATORREC,
  SECTORREC,
  LEASEREC,
  COMPPROPREC,
  RSTSPEC,
  GROUP,
  WELL,
  LAYER,
  SECTOR,
  LEASE,
  SEPARATOR,
  COMPPROP,
  RESTARTCONTROL,
  WMRESTARTCONTROL,
  PVTTABLE,
  WOPERMTABLE,
  GOPERMTABLE,
  NUM_IRF_KEYS
} IRFKeywords;

typedef enum {
  KDIR_UP,
  KDIR_DOWN
} KDirection;

typedef struct {
  int   ts;
  float time;
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

class CMGBinReader;
class CMGTextReader;
class CMGDictionary;

ResValueType ResCMGGetDataType (const char *s);

class CMGProperty 
{
public:
  CMGProperty();
  virtual ~CMGProperty();

  void SetType (ResValueType dtype)
  {
    m_dtype = dtype;
  }
  
  ResValueType GetType()
  {
    return m_dtype;
  }
  
  void AddOffset(size_t offset)
  {
    m_offset.Append(offset);
  }

  void AddOffset (size_t offset, int ts)
  {
    if (ts == -1)
      ts=0;
    int dim = m_offset.Size();
    if (ts >= dim) {
      m_offset.Resize(ts+1);
      size_t dummy = -1;
      for (int i=dim;i<ts;i++) 
        m_offset.Set(i,dummy);
    }  
    m_offset.Set(ts,offset);
  }
  
  bool GetOffset (int i, size_t* ret) const
  {
    int n = m_offset.Size();
    if (i >= n)
      return false;
    *ret = m_offset.Get(i);
    return true;
  }

  size_t GetOffset (int i) const
  {
    int n = m_offset.Size();
    size_t ret = -1;
    if (i < n)
      ret = m_offset.Get(i);
    if (ret != (size_t)-1)
      return ret;
    // Property was not written in this ts
    // find an earlier ts with valid offset
    int taux = i-1;
    while (taux >= n) taux--;
    while (taux >= 0 && (ret = m_offset.Get(taux)) == (size_t)-1) taux--;
    if (taux < 0)
      return -1;
    return ret;
  }
private:
  ResValueType m_dtype;
  DsArray<size_t> m_offset;
};

typedef enum {
  U_TIME = 1,
  U_TEMPERATURE,
  U_PRESSURE,
  U_LENGTH,
  U_PROPERTY_VOLUME,
  U_PERMEABILITY,
  U_MASS,
  U_MOLAR_MASS,
  U_VISCOSITY,
  U_ENERGY,
  U_WELL_LIQUID_VOLUME,
  U_WELL_GAS_VOLUME,
  U_WELL_RATE_TIME,
  U_INTERFACIAL_TENSION,
  NUM_UNIT_TYPES
} UnitTypes;

typedef enum {
  WAT_PHASE = 1,
  OIL_PHASE = 2,
  GAS_PHASE = 3,
  POL_PHASE = 4,
  SOL_PHASE = 5,
  COIL_PHASE = 6,
  CGAS_PHASE = 7,
  NO_PHASE  = 99
} PhaseType;

typedef enum {
  FT_NONE = 0,
  FT_MIL,
  FT_MM,
  FT_RATE,
  FT_FRAC
} FactorType;

typedef struct {
  const char* pposp_name;
  double factor;
  PhaseType phase;
  const char *desc;
  FactorType factor_type;
} PropConvEntry;

typedef struct {
  const char *irf_name;
  int numdata;
  PropConvEntry data[10];
} PropConv;

struct CMGRefinement
{
  DsArray<int> cell_i;
  DsArray<int> cell_j;
  DsArray<int> cell_k;
  DsArray<int> refinement_indices;
  int nri;
  int nrj;
  int nrk;
};

struct CMGError
{
public:
  enum Type
  {
    BAD_FILE,
    UNSUPPORTED_FILE,
    SYSTEM,
  };
  Type type;
  char msg[2048];
public:
  CMGError (Type type, const char* format, ...);
};

//* 'PropConvData' type
// Represents an array of PropConv data
typedef DsHash<DsStringKey,const PropConv*> PropConvData;

DsHash<DsStringKey,int>* ResCMGBuildIRFKeyToEnum ();
DsHash<DsStringKey,bool>* ResCMGBuildNonResetableDimProps ();
/**
 * Removes the component name from a property name: Ex: Z(1) -> Z.
 * The returned value must be freed by the caller.
 */
int ResCMGGetComponent (const char *symbol);
int ResCMGPropertyLength (DsHash<DsStringKey, int>* dimension_props,
                          const char*               ssize);
unsigned int ResCMGPropertySize (ResValueType dtype,
                                 int          float_length,
                                 bool         fixed_component_size);
// Gets the number of data items for a given packing type
// The packing types are:
//	" " - this keyword is not associated with a grid array
//	"s" - this keyword is associated with a spatial storage grid array
//	"p" - this keyword is associated with a packed storage grid array
//	"c" - this keyword is associated with a complete storage grid array
//     The default value is " ".
size_t ResCMGPropertyNumData (DsHash<DsStringKey, int>* dimension_props,
                              const char*               packing);
size_t ResCMGGetNumBytes (DsHash<DsStringKey, int>* dimension_props,
                          const char*               packing,
                          const char*               size,
                          ResValueType              dtype,
                          int                       float_length,
                          bool                      fixed_component_size)
                          throw(const char*);
size_t ResCMGComputeRecordOffset (const char*                 recname,
                                  const char*                 simname,
                                  CMGDictionary*              dict,
                                  DsHash<DsStringKey, int>*   dimension_props,
                                  int                         float_length,
                                  bool                        is_element_record,
                                  DsHash<DsStringKey,size_t>* rec_sizes,
                                  DsHash<DsStringKey,bool>*   invalid_dimensions)
                                  throw(const char*);
size_t ResCMGComputeRecordOffset (const char*                 recname,
                                  const char*                 simname,
                                  CMGDictionary*              dict,
                                  DsHash<DsStringKey, int>*   dimension_props,
                                  int                         float_length,
                                  bool                        is_element_record,
                                  DsHash<DsStringKey,size_t>* rec_sizes)
                                  throw(const char*);

int ResCMGSkipTableType1 (CMGTextReader* irfrd);
int ResCMGSkipTableType2 (CMGTextReader* irfrd, CMGBinReader* mrfrd, bool isxdr);
int ResCMGSkipTableType2 (CMGTextReader*              irfrd,
                          CMGBinReader*               mrfrd,
                          const char*                 simname,
                          CMGDictionary*              dict,
                          DsHash<DsStringKey, int>*   dimension_props,
                          int                         float_length,
                          bool                        isxdr,
                          DsHash<DsStringKey,size_t>* rec_sizes)
                          throw(const char*);
int ResCMGSkipTableType3 (CMGTextReader* irfrd);
int ResCMGSkipTableType4 (CMGTextReader* irfrd, CMGBinReader* mrfrd, bool isxdr);
int ResCMGSkipTableType4 (CMGTextReader*              irfrd,
                          CMGBinReader*               mrfrd,
                          const char*                 simname,
                          CMGDictionary*              dict,
                          DsHash<DsStringKey, int>*   dimension_props,
                          const DsArray<char*>*       recnames,
                          int                         float_length,
                          bool                        isxdr,
                          DsHash<DsStringKey,size_t>* rec_sizes)
                          throw(const char*);
int ResCMGSkipTableType4 (CMGTextReader* irfrd,
                          CMGBinReader* mrfrd,
                          int        numrecprops,
                          int        float_length,
                          bool       isxdr)
                          throw(const char*);
int ResCMGSkipTableType4 (CMGTextReader* irfrd,
                          CMGBinReader* mrfrd,
                          size_t     offsettoskip,
                          bool       isxdr)
                          throw(const char*);
bool ResCMGSkipTableType5 (CMGTextReader* irfrd, 
                           CMGBinReader* mrfrd, 
                           int float_length,
                           bool isxdr);
bool ResCMGSkipTableType5 (CMGTextReader* irfrd, 
                           CMGBinReader* mrfrd, 
                           bool isxdr);
bool ResCMGSkipTableType6 (CMGTextReader* irfrd,
                           CMGBinReader* mrfrd, 
                           int float_length,
                           bool isxdr);
void ResCMGReleasePropArray (DsArray<CMGProperty*>& a);
void ResCMGReleasePropHash (DsHash<DsStringKey,CMGProperty*>& h);
bool ResCMGComputeUnitAndFactor (const DsArray<int>* prop_unit,
                                 DsArray<char*>* internal_units,
                                 DsArray<char*>* output_units,
                                 ResUnit** o_unit,
                                 double* o_factor_mult,
                                 double* o_factor_add);
char* ResCMGGetPropName(const char *symbol);
void ResCMGFreeArray (DsArray<char*>* var);
/**
 * Reads and stores a dimensioning property on hash 'dimension_props'.
 * Throws an error string in case of errors.
 */
bool ResCMGReadDimension (const char*               propname,
                          CMGBinReader*             mrfrd,
                          bool                      isxdr,
                          DsHash<DsStringKey,int>*  dimension_props,
                          DsHash<DsStringKey,bool>* noresetable_props)
                          throw(const char*);
/**
 * Skips a given grid property, storing its dimensions.
 * Throws a BadFileError string in case of errors (see ResCMGGetBadFileError).
 */
void ResCMGSkipGridProperty (const char*                 name,
                             CMGBinReader*               mrfrd,
                             const char*                 simname,
                             CMGDictionary*              dict,
                             DsHash<DsStringKey, int>*   dimension_props,
                             int                         float_length,
                             DsHash<DsStringKey,size_t>* rec_sizes,
                             bool                        isxdr,
                             DsHash<DsStringKey, bool>*  noresetable_props,
                             DsHash<DsStringKey, bool>*  invalid_dimensions)
                             throw(char*);
/**
 * Skips a given grid property, storing its dimensions.
 * Throws a BadFileError string in case of errors (see ResCMGGetBadFileError).
 */
void ResCMGSkipRecord (const char*                 propname,
                       CMGBinReader*               mrfrd,
                       const char*                 simname,
                       CMGDictionary*              dict,
                       DsHash<DsStringKey, int>*   dimension_props,
                       int                         float_length,
                       DsHash<DsStringKey,size_t>* rec_sizes,
                       bool                        isxdr,
                       DsHash<DsStringKey,bool>*   invalid_dimensions)
                       throw(char*);
/**
 * Reads a grid property entry (table type 2) and skip all properties on it.
 *
 * Throws a BadFileError string in case of errors (see ResCMGGetBadFileError).
 */
void ResCMGSkipGridRecords (const char*                 methodname,
                            CMGTextReader*              irfrd,
                            CMGBinReader*               mrfrd,
                            const char*                 simname,
                            CMGDictionary*              dict,
                            DsHash<DsStringKey, int>*   dimension_props,
                            int                         float_length,
                            DsHash<DsStringKey,size_t>* rec_sizes,
                            bool                        isxdr,
                            DsHash<DsStringKey, bool>*  noresetable_props)
                            throw(char*);
/**
 * Constructs, given the model grid dimensioning variables, the refinement
 * structure and the mapping between the irf/mrf file indexing (cs) and
 * the 'res' library indexing.
 *
 * 'refinements', 'cs_to_res_index' and 'res_to_cs_index' can be NULL if not
 * necessary for the caller.
 *
 * Refinements added to 'refinements' must be deleted by the caller.
 */
void ResCMGBuildRefinementStructure (int num_grids,
                                     int model_index, // if 0, is matrix, else, is fracture (1)
                                     bool is_dual_porosity,
                                     const DsArray<int>& cell_model_index,
                                     int num_complete_storage,
                                     const int* nig,
                                     const int* njg,
                                     const int* nkg,
                                     const int* cs_grid_number,
                                     const int* cs_to_parent_block,
                                     DsArray<CMGRefinement*>* refinements,
                                     DsArray<int>* cs_to_res_index);
/**
 * Detects if model is dual porosity or not.
 * Throws a boolean value in case of loading problems.
 *
 * Returns *o_is_dual_porosity equal to true if dual porosity, false otherwise.
 * Fill o_cell_model_index, where o_cell_model_index[c] = model index of cell with complete
 * storage index 'c'.
 */
void ResCMGDetectDualPorosity (unsigned long long nfr,   // igntfr array size
                               unsigned long long nnc,   // igntnc array size
                               int complete_storage,     // complete storage (as read from model)
                               const int* ni,            // ni array
                               const int* nj,            // nj array
                               const int* nk,            // nk array
                               const int* igntfr,        // igntfr array
                               const int* igntnc,        // igntnc array
                               bool* o_is_dual_porosity,
                               DsArray<int>* o_cell_model_index) throw(CMGError);
/**
 * Formats and throws an error string signaling a bad file.
 * To obtain the error string, call ResCMGGetBadFileError on the thrown value.
 * The thrown value must be freed by the catcher.
 */
void ResCMGThrowBadFileError (const char *format, ...) throw(char*);
/**
 * Obtain the error string from a ResCMGThrowBadFileError call.
 */
const char* ResCMGGetBadFileError (const char* error);
/**
 * Keep rstspecrec properties for later skipping.
 * Throws a bad file error in case of reading errors (see ResCMGGetBadFileError).
 */
void ResCMGKeepRstSpecProps (CMGTextReader* irfrd, 
                             const char* label, 
                             DsHash<DsStringKey,DsArray<char*>*>* rstspec_rec)
                             throw(char*);
