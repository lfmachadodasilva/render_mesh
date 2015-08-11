#pragma once

#include <gpos/model/loadernew.h>
#include "mapresultloader.h"

class PPOSPReader;

class ResPPOSPGeometryLoader : public ResPosGeometryLoader
{
public:
  ResPPOSPGeometryLoader (ResPPOSPMapResultLoader* map_loader);
  virtual ~ResPPOSPGeometryLoader ();
  // virtual methods
  virtual float GetVersion () const
  {
    // version 0.0: initial version (until 14/01/2010)
    // version 0.1: corrected geometry coordinates unit.
    return 0.1f;
  }
  bool Load (const char *src, ResPosModelNew* mdl);
  bool HasMeshInformation ()
  {
    return false;
  }
  const char* GetLoadError () const
  {
    return "Arquivos de modelo .DAM, .DAP ou .PPOSP inválidos ou inexistentes";
  }
  void GetCellVertices(int index, float coords[24]);
  void GetFilenames (const char *src, int *numfiles, char ***filenames);
private:
  bool SetActiveCells (ResPosModelNew* mdl);
  bool LoadActiveCells ();
  bool LoadProperties (ResPosModelNew* mdl);
  void FindIfIsCornerPoints (ResPosModelNew* mdl);
  int Index (int i, int j, int k) const
  {
    return (m_nj*k + j)*m_ni + i;
  }
  bool LoadTopoAndBase (ResPosModelNew* mdl);
  bool LoadIniMapProperty (ResPosModelNew* mdl, const char* symbol, float* data);
private:
  ResPPOSPMapResultLoader* m_map_loader;
  char *m_rootname;
  bool m_is_corner_points;
  bool m_inactive_correct;
  // temporary variables
  DsArray<float> m_x;
  DsArray<float> m_y;
  DsArray<float> m_cpx[8];
  DsArray<float> m_cpy[8];
  DsArray<float> m_cpz[8];
  DsArray<float> m_zmin;
  DsArray<float> m_zmax;
  int m_ni, m_nj, m_nk, m_ninj;
};

