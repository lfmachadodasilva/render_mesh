#pragma once

#include <gpos/defines.h>
#include <gpos/model/loadernew.h>
#include <gpos/model/modelnew.h>
#include <gpos/common/util.h>
#include <ds/array.h>
#include <ds/hash.h>
#include "common.h"
#include "grid_reader.h"
#include "egrid_reader.h"
#include "smspec_reader.h"

class ResECLGeometryLoader : public ResPosGeometryLoader
{
public:
  ResECLGeometryLoader (ECLGridReader** grid_reader, SMSPECReader** smspec_reader);
  ~ResECLGeometryLoader ();
  float GetVersion () const
  {
    // version 0.0: initial version (until 17/01/2010)
    // version 0.1: implemented MAPAXES rotation part
    // version 0.2: merger with branch geresim_v2_8 (just to be sure)
    // version 0.3: fixed indirection for refined models
    // version 0.4: disabled refined grids temporarily (properties are wrong)
    // version 0.5: treating negative UTM northing coordinates (generated by ptrell)
    return 0.5f;
  }
  bool Load (const char *src, ResPosModelNew* mdl);
  bool HasMeshInformation ()
  {
    return false;
  }
  void SetKRange (int kmin, int kmax);
  void GetCellVertices (int index, float coords[24]);
  void GetFilenames (const char *src, int *numfiles, char  ***filenames);
private:
  bool ValidateFiles (bool required);
  bool LoadBasicInfo ();
  void SetGridInfo ();
  int GetUsedNK (int nk) const;
  void GetActiveCells (int loader_index,
                       DsArray<int>& active_cells, 
                       DsArray<int>& indirection);
private:
  char* m_rootname;
  char *m_grid;
  ResECLError *m_errors;
  ResPosModelNew* m_modelnew;
  int m_kmin;
  int m_kmax;
  bool m_egrid_exists;
  ECLGridReader* m_grid_reader;
  ECLGridReader** m_grid_pt;
};

