#pragma once

#include <gpos/model/loadernew.h>
#include <gpos/common/util.h>
#include <ds/array.h>
#include <ds/hash.h>
#include "common.h"

typedef struct {
  float x_offset;     // x-coordinate grid offset from the origin of the reservoir
  float y_offset;     // y-coordinate grid offset from the origin of the reservoir
  float rotation;     // the rotation of the grid relative to the X axis of the 
                      // reservoir
  int   axes_directions[3]; // x,y,z axes relative to the axes directions as defined
                            // by the k direction. The x,y,z values are either plus
                            // or minus 1 indicating conformance with or reversal
                            // from the normal directions specified by the k
                            // direction.
  int nblocks_complete_storage; // number of blocks is complete storage
  int nblocks_package_storage;  // number of blocks is package storage
  int nblocks_spatial_storage;  // number of blocks is spatial  storage
  int ninterblock_connections;  // number of interblock connections (eg 
                                // transmissibility)
  int ngrids;         // number of grids in total (fundamental grid 
                      // plus subgrids)
} GridData;

class CMGBinReader;
class CMGTextReader;
class CMGDictionary;

class ResCMGGeometryLoader : public ResPosGeometryLoader
{
public:
  ResCMGGeometryLoader (CMGDictionary *d);
  ~ResCMGGeometryLoader ();
  float GetVersion () const
  {
    // version 0.0: initial version (until 17/01/2010)
    // version 0.1: implemented GRID-AXES-DIRECTIONS keyword.
    return 0.1f;
  }
  void SetKRange (int kmin, int kmax);
  // virtual methods
  /**
   * This method is called with an empty reservoir model and the root of its
   * filename.
   *
   * Returns true if all expected files were correctly loaded and
   * false otherwise.
   */
  //const char* GetRootFileName () const;
  //bool AreGridFilesNewer (const char* filename);
  bool Load (const char* src, ResPosModelNew* mdl);
  bool HasMeshInformation ()
  {
    return false;
  }
  const char* GetLoadError () const;
  const char* GetLoadErrorDetails () const;
  void GetCellVertices (int index, float coords[24]);
  void GetFilenames (const char *src, int *numfiles, char ***filenames);
private:
  int GetTotalNumCells ();
  bool GetActiveCells (ResPosModelNew* mdl,
                       DsArray<int>& cs_to_res_index,
                       DsArray<int>& active_cells,
                       DsArray<int>& packed2complete);
  void GetRootDimensions (int* ni, int* nj, int* nk);
  char* GetCoordinatesUnit ();
  bool SkipRecord (const char* propname, bool is_element_record);
  void BadFileErrorMsg (const char *format, ...);
  void UnsupportedFileErrorMsg (const char *format, ...);
  void SystemErrorMsg (const char *format, ...);
  void StoreErrorDetails (const char *format, va_list ap);
  bool CheckIfHasCorners () throw(bool);
  bool LoadBasicInfo (ResPosModelNew* mdl) throw(bool);
  bool HasTime() {
    if (m_index_time == -1) return false;
    return true;
  }    
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

  int MakeRecurrentData (int ts);
  int ReadGridProperty (char* propname);
  int ReadDimension (int* var);

  int CreateIniProperties ();
  int SetMapTimeStep (void);

  void SetKdir (const char* dir);
  CMGProperty* CreateProperty (char* propname);

  bool IsFloat () const
  {
    return m_float_length == 4;
  }
  bool IsXDR () const
  {
    return m_xdr;
  }
  unsigned long long LoadGridProperty (const char *propname,
                                       void **buffer,
                                       const char* progressname = NULL);
  int ReadCorners();
  int ReadDimensionMaps(ResPosModelNew* mdl);
  bool LoadProperties ();
  int Index (int i, int j, int k) const
  {
    return (m_nj[0]*k + j)*m_ni[0] + i;
  }
  int GetUsedNK () const;
  void DetectDualPorosity () throw(CMGError);
private:
  char* m_rootname;
  float m_null;
  char* m_mrf;                 // Main Data File (*.mrf)
  char* m_rrf;                 // Rewindable Restart File (*.rrf)
  CMGBinReader* m_mrf_rd;      // reader to Main Data File (*.mrf)
  CMGBinReader* m_rrf_rd;      // reader to Rewindable Restart File (*.rrf)
  bool m_is_corner_points;

  // temporary variables
  float *m_x;
  float *m_y;

  int   m_index_time;           // indicates the current time
  int   m_max_rec_len;          // maximum physical record length for associated binary 
                                // mrf file.
  int   m_file;
  
  int m_kdir;               // k direction for the grid ("UP" or "DOWN")
  int m_kini;
  int m_kend;
  int m_kinc;

  bool m_skip_restart;        // The presence of this record indicates that a reading program
                              // should skip reading RESTART records because the data is for
                              // simulator restart only
  GridData m_grid;            // grid geometry parameters
  
  int m_num_rstspec_rec[4096];      // number of rstspec properties data 
  
  int m_num_complete_storage;  
  int m_num_packed_storage;
  int  *m_nact;

  DsArray<char*> m_group_rec;
  DsArray<char*> m_well_rec;
  DsArray<char*> m_layer_rec;
  DsArray<char*> m_sector_rec;

  float *m_faultarray;
  DsArray<float*> m_corners; // 24 values for each grid block
  float *m_ef_porosity;    // Effective porosity at reference conditions (corrected 
                           // by the net-to-gross ratio)
  
  // Initial Property Maps
  int* m_active_cells;      // array with active cells indexes
  float** m_blksize;    
  int m_blksizesize;
  float *m_blkdep;          // Grid block depths at the center of cell 
  
  int* m_gn_nextcs;
  
  bool m_fracture;
  bool m_matrix;
  bool m_is_fractured;
  bool m_is_comp;
  bool m_is_term;
  bool m_is_lgr;
  int  m_nactive;
  
  CMGDictionary *m_dict;   // Data dictionary
  
  double m_uctime;
  
  // Time variables
  double m_rtimet;
  int m_idate;
  char m_initial_date[16];
  double m_rtime;
  int m_nspchs;                // Number of spec variables readed from SPHIST-NAMES
  /* Dimensioning variables */
  int m_num_sectors;          // Number of sectors (NSECT1)
  int m_num_sectors4;         // Number of sectors (NSECT1) * 4
  int m_num_grids;            // Number of grids (NPTGN)
  int m_num_grids1;           // Number of grids (NPTGN1) + 1
  int m_num_grid_groups;      // Number of grid groups defined (NPTGG)
  int m_num_connections;      // Total number of connections (NPTCN)
  int m_sector_length;        // Sector geometry length
  
  /* Index variables */
  int* m_igntza;              // Grid number to local Z direction (IGNTZA)
  int* m_igntfr;              // Grid number to first fracture CS index (IGNTFR)
  int* m_igntnc;              // Grid number to last block CS index (IGNTNC)
  //int* m_grid_type;           // Grid type for each grid (IGNTGT)
  int* m_igntns;              // Grid number to last block SS index (IGNTNS)
  int* m_ni;                  // Number of cells at I direction for each grid (IGNTID)
  int* m_nj;                  // Number of cells at J direction for each grid (IGNTJD)
  int* m_nk;                  // Number of cells at K direction for each grid (IGNTKD)
  int* m_cs_block_type;       // Complete storage to block type (ICSTBC)
  int* m_cs_child_grid;       // Complete storage to child grid (ICSTCG)
  int* m_cs_grid_number;      // Complete storage to grid number (ICSTGN)
  int* m_cs_package_storage;  // Complete storage to packed storage (ICSTPS)
  int* m_ps_block_type;       // Packed storage to block type (IPSTBT)
  int* m_ps_active;           // Packed storage to active status (IPSTAC)
  int* m_igntwn;              // Grid number to well number (IGNTWN)
  int* m_igntgg;              // Grid number to grid group (IGNTGG)
  int* m_ictps1;              // Connection to lower packed storage (ICTPS1)
  int* m_ictps2;              // Connection to upper packed storage (ICTPS2)
  DsArray<int> m_maingrid_cs; // main grid cells to complete storage
  double *m_wellradius;       // Radius of wellbore in centre of grid
  
  int m_nextlayer[4096];  
  int m_ipos_layer[4096];
  int m_jpos_layer[4096];
  int m_kpos_layer[4096];
  
  int m_nvlay;  // number of layer informations per mrf register
  int m_nvgrp;  // number of group informations per mrf register
  int m_nvwel;  // number of well informations per mrf register 
  int m_nvsec;  // number of sector informations per mrf register 
  
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
  unsigned int m_float_length; // number of bytes of data written in the mrf file
  bool m_rewind;               // indicates that the rrf file has been rewound

  int m_numx;                  // Number of liquid condensible components
  int m_numy;                  // Number of fluid components
  int m_numw;                  // Number of aqueous components
  int m_numo;                  // Number of oleic components
  int m_nsold;                 // Number of solid components + 1
  int m_ncomp;                 // Total number of components

  char** m_comp_name;          // component name array
  bool** m_comp_phases;        // specifies in which phase each component may be
                          // found. 0=water,1=oil,2=gas,3=solid

  DsArray<CMGProperty*> m_grid_props;
  DsHash<DsStringKey,CMGProperty*> m_symbol_to_grid_prop;
  DsHash<DsStringKey,int>* m_irfkeys;
  DsHash<DsStringKey,bool>* m_noreset_props; // list of properties that cannot be redefined
  DsHash<DsStringKey,int> m_dimension_props;
  DsArray<char*> m_internal_units;
  DsArray<char*> m_output_units;
  int m_kmin;
  int m_kmax;
  int m_kminoffset;
  int m_kmaxoffset;
  char  m_load_error[4096];         // error while loading, if any
  char  m_load_error_details[4096]; // details on error while loading, if any

  bool m_grid_defined;
  bool m_has_grid;
  DsArray<char*> m_lease_rec;
  DsArray<char*> m_separator_rec;
  DsArray<char*> m_comp_rec;
  DsHash<DsStringKey,DsArray<char*>*> m_rstspec_rec;
  DsHash<DsStringKey,size_t> m_rec_sizes;
  DsArray<int> m_cell_model_index;
  bool m_dual_porosity;
};

