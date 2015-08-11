#pragma once
#include <gpos/defines.h>
#include <gpos/model/loadernew.h>
#include <gpos/common/util.h>
#include <ds/array.h>
#include <ds/hash.h>
#include "common.h"

class ECLReader;

class SMSPECReader : public ECLFormatReader
{
public:
  SMSPECReader (const char* rootname, ResECLError *errors);
  ~SMSPECReader();
  bool ReadKeywords (ResPosLoaderNew* loader);
  bool ReadMapKeywords ();
  bool ValidateFiles();
  int KeywordsCount ();
  void PropertyValues (int i, char*& propname, char*& unit, int* num, char*& name);
  int ParametersCount ();
  int Nx ();
  int Ny ();
  int Nz ();
  int KeywordPosition (const char* key);
  char* GetInitialDate (int* iday, int* imonth, int* iyear);
  void LGRData (int pos, char* lgrname, int* ix, int* iy, int* iz);
private:
  // SMSPEC file keywords
  void ReadRESTART (ECLReader *rd) throw (bool);
  void ReadDIMENS (ECLReader *rd) throw (bool);
  void ReadKEYWORDS (ECLReader *rd) throw (bool);
  void ReadWGNAMES (ECLReader *rd) throw (bool);
  void ReadNAMES (ECLReader *rd) throw (bool);
  void ReadNUMS (ECLReader *rd) throw (bool);
  void ReadLGRS (ECLReader *rd) throw (bool);
  void ReadNUMLX (ECLReader *rd) throw (bool);
  void ReadNUMLY (ECLReader *rd) throw (bool);
  void ReadNUMLZ (ECLReader *rd) throw (bool);
  void ReadLENGTHS (ECLReader *rd) throw (bool);
  void ReadUNITS (ECLReader *rd) throw (bool);
  void ReadSTARTDAT (ECLReader *rd) throw (bool);
  void ReadLENUNITS (ECLReader *rd) throw (bool);
  void ReadLGRNAMES (ECLReader *rd, int nelems) throw (bool);
  void ReadLGRVEC (ECLReader *rd) throw (bool);
  void ReadLGRTIMES (ECLReader *rd) throw (bool);
  void ReadRUNTIMEI (ECLReader *rd, int nelems) throw (bool);
  void ReadRUNTIMED (ECLReader *rd, int nelems) throw (bool);
  void ReadSTEPRESN (ECLReader *rd, int nelems) throw (bool);
private:
  ResECLError* m_errors;

  char *m_filename;            // SMSPEC filename
  ECLReader *m_smspec_rd;      // SMSPEC Reader
  char *m_restart_name;        // name of restart file, if any
  StringArray* m_keywords;     // mnemonic keyword associated with each data vector
  StringArray* m_wgnames;      // well or group name associated with each data vector
  StringArray* m_names;        // alternative to WGNAMES for models where the standard
                               // short naming convention is not used (e.g. multiple
                               // reservoirs connected together by a network)
  int* m_nums;                 // integer cell or region number associated with each
                               // data vector
  StringArray* m_lgrs;               // The LGR name associated with each data vector
  int* m_numlx;                // For local block or completion data vectors, the I-position
                               // in the local grid.
  int* m_numly;                // For local block or completion data vectors, the Jposition
                               // in the local grid.
  int* m_numlz;                // For local block or completion data vectors, the Kposition
                               // in the local grid.
  float* m_lengths;            // For horizontal well data, the length along the well
                               // associated with each summary item (i.e. distance from
                               // bottom- hole reference point to completion)
  char *m_lenunits;            // The unit used for horizontal well lengths
  StringArray* m_units;        // Units associated with each vector
  StringArray* m_lgrnames;     // The names of the local grids defined for this run, if any.
  int* m_lgrvec;               // The number of summary vectors associated with each LGR
  int* m_lgrtimes;             // Total number of local ministeps associated with each LGR
  int* m_runtimei;             // Integer data used for run-time monitoring
  double* m_runtimed;          // Double precision data used for run-time monitoring
  StringArray* m_stepresn;     // Character mnemonics describing the reasons for
                               // selecting timestep lengths in the simulation run
  char *m_rundate;             // The date of the run start
//
  int m_nlgr;                  // local grids counter
  int m_num_stepresn;
  //
  int m_nlist;                 // number of data vector parameters stored at each timestep
  int m_nx;                    // number of cells in X-direction at global grid
  int m_ny;                    // number of cells in Y-direction at global grid
  int m_nz;                    // number of cells in Z-direction at global grid
  int m_istar;                 // report step number of restart file used to
                               // start this run, if any, or -1, if not
  int m_day_pos;
  int m_month_pos;
  int m_year_pos;
  int m_time_pos;

  int m_start_day;             // The date of the run start
  int m_start_month;
  int m_start_year;
  //
  DsHash<DsStringKey,int> m_keyword_to_position;
};

