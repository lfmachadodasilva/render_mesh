#pragma once

#include <gpos/model/loadernew.h>
#include <gpos/common/util.h>
#include <gpos/defines.h>
#include <ds/array.h>
#include <ds/hash.h>
#include "common.h"
#include "binreader.h"
#include "textreader.h"

class ResCMGMapResultLoader : public ResPosMapResultLoader
{
public:
  ResCMGMapResultLoader (CMGDictionary *d);
  ~ResCMGMapResultLoader ();
  void SetKRange (int kmin, int kmax);
  const char* GetRootFileName () const;
  bool AreGridFilesNewer (const char* filename);
  // virtual methods
  bool LoadHeader (const char* src, int* model_count, char*** suffixes);
  bool Load (const char* src, ResPosModelNew* mdl);
  const char* GetLoadError () const;
  const char* GetLoadErrorDetails () const;
  bool LoadIniProperty (ResPosModelNew* mdl, int prop_id, float* data);
  bool LoadRecProperty (ResPosModelNew* mdl, int prop_id, int ts, float* data);
private:
  int GetCompleteDimension ();
  int ComputePackedDimension (ResPosModelNew* mdl);
  float GetNullValue () const
  {
    return RES_NULL_VALUE;
  }
  bool HasTime () const
  {
    return m_index_time != -1;
  }
  int AddIniProperty (char* propname);
  int AddRecProperty (char* propname);
  int ReadIRF (CMGTextReader& rd);
  int ReadTitle(CMGTextReader& rd,char *label);
  int ReadParent (CMGTextReader& rd);
  int ReadGroupName (CMGTextReader& rd);
  int ReadWellName (CMGTextReader& rd);
  int ReadLayerName (CMGTextReader& rd);
  int ReadTime (CMGTextReader& rd);
  int ReadGrid (CMGTextReader& rd);
  int ReadSimulName (CMGTextReader& rd);
  int ReadVersion (CMGTextReader& rd);
  int ReadRunDate (CMGTextReader& rd);
  int ReadCaseId (CMGTextReader& rd);
  int ReadIndexed (CMGTextReader& rd,
                   char* label);
  int ReadXDR (CMGTextReader& rd);
  int ReadFloatLength (CMGTextReader& rd);
  int ReadFile (CMGTextReader& rd);
  int ReadRewind (CMGTextReader& rd);
  int ReadNComp (CMGTextReader& rd);
  int ReadCompName (CMGTextReader& rd);
  int ReadCompPhaseTemplate (CMGTextReader& rd);
  int ReadKDIR (CMGTextReader& rd);
  int ReadInternalUnitTable (CMGTextReader& rd);
  int ReadOutputUnitTable (CMGTextReader& rd);
  int ReadPvtTable (CMGTextReader& rd);
  int ReadGOPermTable (CMGTextReader& rd);
  int ReadWOPermTable (CMGTextReader& rd);
  int ReadSectorName (CMGTextReader& rd);
  int ReadLeaseName (CMGTextReader& rd);
  int ReadSphistNames (CMGTextReader& rd);

  int ReadGroupRec (CMGTextReader& rd);
  int ReadWellRec (CMGTextReader& rd);
  int ReadLayerRec (CMGTextReader& rd);
  int ReadSectorRec (CMGTextReader& rd);
  int ReadLeaseRec (CMGTextReader& rd);
  int ReadSeparatorRec (CMGTextReader& rd);
  int ReadRstSpecRec (CMGTextReader& rd, const char* label);
  int ReadCompPropRec (CMGTextReader& rd);

  int ReadTimeChr (CMGTextReader& rd);
  int ReadGridXOffset (CMGTextReader& rd);
  int ReadGridYOffset (CMGTextReader& rd);
  int ReadGridRotation (CMGTextReader& rd);
  int ReadGridAxesDirections (CMGTextReader& rd);
  int ReadGridDim (CMGTextReader& rd);

  int ReadRestart (CMGTextReader& rd);
  int ReadWMRestart (CMGTextReader& rd);
  int ReadSpecHistory (CMGTextReader& rd);
  int ReadGridValue (CMGTextReader& rd);

  int ReadGroup (CMGTextReader& rd,
                 char* label);
  int ReadWell (CMGTextReader& rd,
                char* label);
  int ReadLayer (CMGTextReader& rd,
                 char* label);
  int ReadSector (CMGTextReader& rd,
                  char* label);
  int ReadLease (CMGTextReader& rd,
                 char* label);
  int ReadSeparator (CMGTextReader& rd,
                     char* label);
  int ReadCompProp (CMGTextReader& rd,
                    char* label);
  int ReadRstSpec (CMGTextReader& rd,
                   char* label);

  int ReadRestartControl (CMGTextReader& rd,
                          char* label);
  int ReadWMRestartControl (CMGTextReader& rd,
                            char* label);

  void MakeRecurrentData (ResPosModelNew* mdl, int ts);
  int ReadGridProperty (char* propname);
  int ReadDimension (int* var);

  //int CreateGeometryMaps ();
  int CreateIniProperties (ResPosModelNew* mdl);
  int SetMapTimeStep (void);

  void SetKdir (int dir);
  int PrepareKRangeRead ();
  CMGProperty* CreateProperty (char* propname, bool compute_unit);
  bool ComputeGridUnits ();
  bool ComputeUnit (const char *propname, DsArray<int>* unit);

  bool IsFloat () const
  {
    return m_float_length == 4;
  }
  bool IsXDR () const
  {
    return m_xdr;
  }

  unsigned long long LoadGridProperty (const char* propname, void** buffer);
  int ReadDimensionMaps ();
private:
  void DetectDualPorosity () throw(CMGError);
  void BadFileErrorMsg (const char *format, ...);
  void UnsupportedFileErrorMsg (const char *format, ...);
  void SystemErrorMsg (const char *format, ...);
  void StoreErrorDetails (const char *format, va_list ap);
  void StoreExtraIniProperty (const char* symbol,
                              const char* desc,
                              ResValueType dtype,
                              bool iscomplete);
  const double* ReadDouble (int nelems,
                            size_t offset);
  const int* ReadInt (int nelems,
                      size_t offset);

  int GetUsedNK () const;
  int MainGridToPacked (int i) const
  {
    assert(m_maingrid_ps != NULL);
    return m_maingrid_ps[i];
  }
  bool GetNextPackedPos (int& p, int &pps);
  void FillArrayWithCompletePropDouble (ResPosModelNew* mdl, float* data, const double* src, double factor_mult, double factor_add);
  void FillArrayWithCompletePropInt (ResPosModelNew* mdl, float* data, const int* src, double factor_mult, double factor_add);
  void FillArrayWithPackedPropDouble (ResPosModelNew* mdl, float* data, const double* src, double factor_mult, double factor_add);
  void FillArrayWithPackedPropInt (ResPosModelNew* mdl, float* data, const int* src, double factor_mult, double factor_add);
  bool SkipRecord (const char* propname, bool is_element_record);
  bool IsValidGridProperty (const char *propname);
  void FillArrayWithNullValue (ResPosModelNew* mdl, float* data, bool is_complete);
  int GetActiveCellCount () const;
private:
  struct UnitData
  {
    ResUnit* u;
    double factor_add;
    double factor_mult;
    UnitData (ResUnit* u, double factor_mult, double factor_add)
    : u(u)
    , factor_add(factor_add)
    , factor_mult(factor_mult)
    {
    }
    ~UnitData ()
    {
      if (u != NULL)
        delete u;
    }
  };
  struct IniProperty
  {
    CMGProperty* p;
    char* desc;
    bool iscomplete;
    bool get_data_from_dict;

    IniProperty (CMGProperty* p)
    : p(p)
    , desc(NULL)
    , get_data_from_dict(true)
    {
    }
    IniProperty (CMGProperty* p, const char* desc, bool iscomplete)
    : p(p)
    , desc(strdup(desc))
    , iscomplete(iscomplete)
    , get_data_from_dict(false)
    {
    }
    ~IniProperty ()
    {
      free(desc);
    }
  };
private:
  char* m_rootname;
  char* m_mrf;                 // Main Data File (*.mrf)
  char* m_rrf;                 // Rewindable Restart File (*.rrf)
  CMGBinReader* m_mrf_rd;      // reader to Main Data File (*.mrf)
  CMGBinReader* m_rrf_rd;      // reader to Rewindable Restart File (*.rrf)
  bool m_is_corner_points;
  int m_index_time;            // indicates the current time
  int m_map_index_time;
  int m_max_rec_len;           // maximum physical record length for associated
                            // binary mrf file.
  DsArray<TimeData> m_time;    // stores time data
  char  m_load_error[4096];         // error while loading, if any
  char  m_load_error_details[4096]; // details on error while loading, if any
  int m_file;

  int m_kdir;                  // k direction for the grid ("UP" or "DOWN")
  int m_kini;
  int m_kend;
  int m_kinc;

  bool m_skip_restart;        // The presence of this record indicates that a reading program
                              // should skip reading RESTART records because the data is for
                              // simulator restart only

  int m_num_rstspec_rec[4096]; // number of rstspec properties data
  int m_main_grid_num_act_cells;
  int m_num_complete_storage;
  int m_num_packed_storage;
  int* m_nact;

  DsArray<char*> m_group_rec;
  DsArray<char*> m_well_rec;
  DsArray<char*> m_layer_rec;
  DsArray<char*> m_sector_rec;

#if 0
  // Grid geometry maps
  float* m_dx;
  float* m_dy;
  float* m_h;
  float* m_top;
  float* m_bottom;
  float* m_zmed;
#endif
  double* m_blkpvl;            // Pore volume for active grid blocks only
  
//  float *m_faultarray;
//  // Initial Property Maps
//  int* m_active_cells;      // array with active cells indexes
  CMGDictionary* m_dict;       // Data dictionary
  // Time variables
  double m_rtimet;
  char m_initial_date[16];
  double m_rtime;
  /* Dimensioning variables */
  int m_num_grids;             // Number of grids (NPTGN)
  /* Index variables */
  int* m_ni;                   // Number of cells at I direction for each grid (IGNTID)
  int* m_nj;                   // Number of cells at J direction for each grid (IGNTJD)
  int* m_nk;                   // Number of cells at K direction for each grid (IGNTKD)
  int* m_cs_block_type;        // Complete storage to block type (ICSTBC)
  int* m_cs_child_grid;        // Complete storage to child grid (ICSTCG)
  int* m_cs_package_storage;   // Complete storage to packed storage (ICSTPS)
  int* m_ps_complete_storage;  // Packed storage to complete storage (IPSTCS)
  int* m_ps_block_type;        // Packed storage to block type (IPSTBT)
  int* m_ps_active;            // Packed storage to active status (IPSTAC)
  int* m_igntwn;               // Grid number to well number (IGNTWN)
  int* m_igntgg;               // Grid number to grid group (IGNTGG)
  int* m_ictps1;               // Connection to lower packed storage (ICTPS1)
  int* m_ictps2;               // Connection to upper packed storage (ICTPS2)
  int* m_maingrid_ps;          // main grid cells to package storage
  bool m_initime;
  /*
   * Type 1 keywords
   */
  char* m_simname;             // simulator name. The value of string is either
                          // IMEX,GEM,STARS or CMGPROP
  char* m_version;             // version number. Typically of the form yy.rr
                          // where yy is the last two digits of the year
                          // and rr is a release number within year
  char* m_rundate;             // the date the simulator was run to produce the
                          // data file. Is an string of the form yyyymmdd
  char* m_title1;              // title 1
  char* m_title2;              // title 2
  char* m_title3;              // title 3
  char* m_full_title;          // full title
  char* m_caseid;              // caseid string
  char* m_parent;              // indicates the irf file is a continuation from
                          // the file specified (restart run)
  bool m_indexed_mrf;          // indicates that mrf file is indexed
  bool m_xdr;                  // indicates that mrf file is in XDR format
  int m_float_length;          // number of bytes of data written in the mrf file
  bool m_rewind;               // indicates that the rrf file has been rewound

  DsHash<DsStringKey, IniProperty*> m_symbol_to_ini_prop;
  DsHash<DsStringKey, CMGProperty*> m_symbol_to_rec_prop;
  DsHash<DsStringKey, CMGProperty*> m_symbol_to_grid_prop;
  DsArray<double> m_load_temp_d;
  DsArray<int> m_load_temp_i;
  DsHash<DsStringKey, int>* m_irfkeys;
  DsHash<DsStringKey, bool>* m_noreset_props; // list of properties that cannot be redefined
  DsHash<DsStringKey, int> m_dimension_props;
  DsHash<DsStringKey, int> m_inimap_props;
  DsHash<DsStringKey, UnitData*> m_prop_units;
  int m_kmin;
  int m_kmax;
  int m_kminoffset;
  int m_kmaxoffset;
  int m_krange_num_act;
  DsArray<int> m_main_grid_packed_to_complete;
  DsArray<char*> m_internal_units;
  DsArray<char*> m_output_units;
  bool m_grid_defined;
  bool m_has_grid;
  DsArray<char*> m_lease_rec;
  DsArray<char*> m_separator_rec;
  DsArray<char*> m_comp_rec;
  DsHash<DsStringKey,DsArray<char *>*> m_rstspec_rec;
  DsHash<DsStringKey,size_t> m_rec_sizes;
  DsArray<int> m_cell_model_index;
  bool m_dual_porosity;
};

