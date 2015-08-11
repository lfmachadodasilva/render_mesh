#pragma once

#include <gpos/defines.h>
#include <gpos/model/loadernew.h>
#include <gpos/model/modelnew.h>
#include <gpos/common/util.h>
#include <ds/array.h>
#include <ds/hash.h>
#include "common.h"
#include "grid_reader.h"
#include "unrst_reader.h"
#include "init_reader.h"

class ResECLMapResultLoader : public ResPosMapResultLoader
{
public:
  ResECLMapResultLoader (UNRSTReader** unrst_reader, 
                         ECLGridReader** grid_reader,
                         SMSPECReader** smspec_reader,
                         INITReader** init_reader);
  ~ResECLMapResultLoader ();
  void SetKRange (int kmin, int kmax);
  // Virtual Methods
  bool LoadHeader (const char* src, int* model_count, char*** suffixes);
  bool Load (const char* src, ResPosModelNew* mdl);
  const char* GetLoadError () const;
  const char* GetLoadErrorDetails () const;
  const char* GetLoadWarnings () const;
  bool LoadIniProperty (ResPosModelNew* mdl, int prop_id, float* data);
  bool LoadRecProperty (ResPosModelNew* mdl, int prop_id, int ts, float* data);
private:
  void SetKdir (const char* dir);
  bool ValidateFiles ();
  bool LoadBasicInfo (ResPosModelNew* mdl);
  int GetCompleteDimension ();
  int GetUsedNK () const;
  int GetPackedDimension (int loader_index);
  bool IsDualPorosity ();
  int CreateIniProperties (ResPosModelNew* mdl);
  void PrepareKRangeRead ();
private:
  char* m_rootname;
  ECLGridReader* m_grid_reader;   
  ECLGridReader** m_grid_pt;   
  UNRSTReader** m_unrst_pt;
  UNRSTReader* m_unrst_reader;
  INITReader* m_init_reader;
  INITReader** m_init_pt;
  SMSPECReader* m_smspec_reader;
  SMSPECReader** m_smspec_pt;
  ResECLError *m_errors;
  ResPosModelNew* m_modelnew;
  int m_kmin;
  int m_kmax;
  int m_krange_num_act;
  int m_kini;
  int m_kend;
  int m_kinc;
  int m_kdir;
  bool m_has_unrst;
  bool m_has_init;
  int m_ni;
  int m_nj;
  int m_nk;
  bool m_is_dualpor;
};

