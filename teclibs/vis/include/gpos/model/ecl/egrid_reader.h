#pragma once
#include <gpos/defines.h>
#include <gpos/model/loadernew.h>
#include <gpos/common/util.h>
#include <ds/array.h>
#include <ds/hash.h>
#include <alg/matrix.h>
#include "common.h"

class ECLReader;

typedef struct {
  DsArray<int> indirection;
  DsArray<int> activecells;
  char* refinement_name;
  int num_act;
  int index;
} RefinedCellData;

typedef struct {
  int index;
  char* refinement_name;
} IndirectionCellData;

typedef struct {
  int lower_k;
  int upper_k;
} ReservoirData;

typedef DsArray<ReservoirData*> ReservoirDataArray;

class EGridData 
{
public:
  EGridData (int index, const char* name, int ni, int nj, int nk,
             int lower_i_host, int lower_j_host, int lower_k_host,
             int upper_i_host, int upper_j_host, int upper_k_host)
    : m_numres(1)
    , m_coord(NULL)
    , m_zcorn(NULL)
    , m_name(NULL)
    , m_numseg(0)
    , m_is_radial(false)
    , m_ix_orig(-1)
    , m_iy_orig(-1)
    , m_iz_orig(-1)
    , m_hostcell(NULL)
    , m_num_active_cells(0)
    , m_num_active_cells_fracture(0)
    , m_lgrparent(NULL)
    , m_lgrsgrid(NULL)
    , m_num_root_cells(0)
    , m_num_total_cells(0)
  {
    m_active.Clear();
    m_active_fracture.Clear();
    m_name = PSUtil::StrDup(name);
    if (index == 0) {                 // root grid
      m_nx = ni;
      m_ny = nj;
      m_nz = nk;
      m_num_root_cells = ni * nj * nk;
      m_lower_i_host = lower_i_host; 
      m_lower_j_host = lower_j_host; 
      m_lower_k_host = lower_k_host; 
      m_upper_i_host = upper_i_host; 
      m_upper_j_host = upper_j_host; 
      m_upper_k_host = upper_k_host;
    }
    else {
      // positions are 0 based
      m_lower_i_host = lower_i_host - 1; 
      m_lower_j_host = lower_j_host - 1; 
      m_lower_k_host = lower_k_host - 1; 
      m_upper_i_host = upper_i_host - 1; 
      m_upper_j_host = upper_j_host - 1; 
      m_upper_k_host = upper_k_host - 1;
      //
      int ncells_i = m_upper_i_host-m_lower_i_host+1;
      int ncells_j = m_upper_j_host-m_lower_j_host+1;
      int ncells_k = m_upper_k_host-m_lower_k_host+1;
      m_num_root_cells = ncells_i * ncells_j * ncells_k;
      m_nri = ni / ncells_i;
      m_nrj = nj / ncells_j;
      m_nrk = nk / ncells_k;
    }
    m_nx = ni;
    m_ny = nj;
    m_nz = nk;
    m_num_total_cells = ni * nj * nk;
  }
  ~EGridData ()
  {
    PSUtil::Free(m_name);
    FREE_AND_SET_NULL(m_coord);
    FREE_AND_SET_NULL(m_zcorn);
    FREE_AND_SET_NULL(m_hostcell);
    FREE_AND_SET_NULL(m_lgrparent);
    FREE_AND_SET_NULL(m_lgrsgrid);
  }
  const char* GetName()
  {
    return m_name;
  }
  int CountTotalCells ()
  {
    return m_num_total_cells;
  }
  void GetDimensions (int* nx, int* ny, int* nz)
  {
    *nx = m_nx;
    *ny = m_ny;
    *nz = m_nz;
  }
  void GetRefinementDimensions(int* nri, int* nrj, int* nrk)
  {
    *nri = m_nri;
    *nrj = m_nrj;
    *nrk = m_nrk;
  }
  void SetCoordValues (const float* values, int n)
  {
    m_coord = (float*) malloc(n*sizeof(float));
    memcpy(m_coord, values, n*sizeof(float));
    m_coord_size = n;
  }
  void SetZcornValues (const float* values, int n)
  {
    m_zcorn = (float*) malloc(n*sizeof(float));
    memcpy(m_zcorn, values, n*sizeof(float));
    m_zcorn_size = n;
  }
  void SetActiveCells (const int* values, int n, bool is_dualpor)
  {
    // values[i] can be:
    // 0 - inactive
    // 1 - active (or active matrix for dual porosity runs)
    // 2 - active fracture (for dual porosity runs)
    // 3 - active matrix and fracture (for dual porosity runs)
    m_active.Clear();
    m_active_fracture.Clear();
    m_num_active_cells = 0;
    m_num_active_cells_fracture = 0;
    
    if (is_dualpor) {
      for (int i=0; i<n; i++) {
        // fill matrix active cells
        if (values[i] == 1 || values[i] == 3) {
          m_active.Append(1);
          m_num_active_cells++;
        }
        else
          m_active.Append(0);
        // fill fracture active cells
        if (values[i] == 2 || values[i] == 3) {
          m_active_fracture.Append(1);
          m_num_active_cells_fracture++;
        }
        else
          m_active_fracture.Append(0);
      }
    }
    else {
      for (int i=0; i<n; i++) {
        if (values[i] == 1) {
          m_active.Append(1);
          m_num_active_cells++;
        }
        else
          m_active.Append(0);
      }
    }
  }
  int CountActiveCells ()
  {
    return m_num_active_cells;
  }
  int CountActiveCellsFracture ()
  {
    return m_num_active_cells_fracture;
  }
  void SetHostCellNumbers (const int* values, int n)
  {
    m_hostcell = (int*) malloc(n*sizeof(int));
    memcpy(m_hostcell, values, n*sizeof(int));
  }
  void GetCoord (const int i, const int j, const int k, const int ipos, const int jpos, 
                 AlgMatrix* map_axes_transf,
                 float* x1, float* y1, float* z1, float* x2, float* y2, float* z2)
  {
    int pos = (j*(m_nx+1) + i)*6;
    pos = pos + 6*ipos + 6*(m_nx+1)*jpos;
    assert(pos+5 < m_coord_size);
    *x1 = m_coord[pos++];
    *y1 = m_coord[pos++];
    *z1 = m_coord[pos++];
    *x2 = m_coord[pos++];
    *y2 = m_coord[pos++];
    *z2 = m_coord[pos++];
    if (map_axes_transf != NULL) {
      map_axes_transf->Transform(x1, y1, z1);
      map_axes_transf->Transform(x2, y2, z2);
    }
  }
  void GetCoordMultReser (const int i, const int j, const int k, const int ipos, const int jpos,
                          AlgMatrix* map_axes_transf,
                          int numres,
                          float* x1, float* y1, float* z1, float* x2, float* y2, float* z2)
  {
    int pos = (j*(m_nx+1) + i)*6;
    pos = pos + 6*ipos + 6*(m_nx+1)*jpos;
    pos = pos + numres*(6*(m_nx+1)*(m_ny+1));
    assert(pos+5 < m_coord_size);
    *x1 = m_coord[pos++];
    *y1 = m_coord[pos++];
    *z1 = m_coord[pos++];
    *x2 = m_coord[pos++];
    *y2 = m_coord[pos++];
    *z2 = m_coord[pos++];
    if (map_axes_transf != NULL) {
      map_axes_transf->Transform(x1, y1, z1);
      map_axes_transf->Transform(x2, y2, z2);
    }
  }
  float GetZcorn(const int i, const int j, const int k,
                 const int ipos, const int jpos, const int kpos)
  {
    int nxny = m_nx * m_ny;
    int nxny4 = 4 * nxny;
    int nx2 = 2 * m_nx;
    int pos = k*2*nxny4 + 2*j*nx2 + 2*i;
    pos = pos + ipos + jpos*nx2 + kpos*nxny4;
    assert(pos < m_zcorn_size);
    return m_zcorn[pos];
  }
  int GetActiveCells (DsArray<int>& activecells)
  {
    int n = m_active.Size();
    int nact = 0;
    for (int i=0; i<n; i++) {
      if (m_active[i] == 1) {
        activecells.Append(i);
        nact++;
      }
    }
    return nact;
  }
  int GetActiveCells (int pos, DsArray<int>& activecells)
  {
    int n = m_nx * m_ny * m_nz;
    int nact = 0;
    int k = pos * n;
    for (int i=0; i<n; i++) {
      if (m_active[i] == 1) {
        activecells.Append(k+i);
        nact++;
      }
    }
    return nact;
  }
  int GetActiveCellsFracture (DsArray<int>& activecells)
  {
    int n = m_active_fracture.Size();
    int nact = 0;
    for (int i=0; i<n; i++) {
      if (m_active_fracture[i] == 1) {
        activecells.Append(i);
        nact++;
      }
    }
    return nact;
  }
  int GetActiveCellsFracture (int pos, DsArray<int>& activecells)
  {
    int n = m_nx * m_ny * m_nz;
    int nact = 0;
    int k = pos * n;
    for (int i=0; i<n; i++) {
      if (m_active_fracture[i] == 1) {
        activecells.Append(k+i);
        nact++;
      }
    }
    return nact;
  }
  void SetNumReservoirs (int nres)
  {
    m_numres = nres;
  }
  void SetNumSegments (int nseg)
  {
    m_numseg = nseg;
  }
  void SetRadial (bool is_radial)
  {
    m_is_radial = is_radial;
  }
  void GetHostCoords (int* i0, int* j0, int* k0, int* i1, int* j1, int* k1)
  {
    *i0 = m_lower_i_host;
    *j0 = m_lower_j_host;
    *k0 = m_lower_k_host;
    *i1 = m_upper_i_host;
    *j1 = m_upper_j_host;
    *k1 = m_upper_k_host;
  }

  void SetBoxOrig (int ix, int iy, int iz)
  {
    m_ix_orig = ix;
    m_iy_orig = iy;
    m_iz_orig = iz;
  }
  int GetNumReservoirs ()
  {
    return m_numres;
  }
  int FindReservoir (int layer)
  {
   for (int i=0; i < m_numres; i++) {
      ReservoirData* r = m_reser.Get(i);
      if (layer >= r->lower_k && layer <= r->upper_k)
        return i;
    }
    assert(false);
    return -1;
  }
  void SetReservoirLimits (int numres, int lower_k, int upper_k)
  {
    ReservoirData* r = new ReservoirData;
    r->lower_k = lower_k;
    r->upper_k = upper_k;
    m_reser.Insert(r, numres);
  }
  const ReservoirData* GetReservoirData (int nres)
  {
    return m_reser.Get(nres);
  }
  void SetLGRParent (const char* name)
  {
    m_lgrparent = PSUtil::StrDup(name);
  }
  const char* GetLGRParent ()
  {
    return m_lgrparent;
  }

  void SetLGRSgrid (const char* name)
  {
    m_lgrsgrid = PSUtil::StrDup(name);
  }
private:
  int m_nx;
  int m_ny;
  int m_nz;
  float* m_coord;
  float* m_zcorn;
  char* m_name;
  int m_numres;
  int m_numseg;
  bool m_is_radial;
  int m_lower_i_host; 
  int m_lower_j_host; 
  int m_lower_k_host;
  int m_upper_i_host; 
  int m_upper_j_host; 
  int m_upper_k_host;
  int m_ix_orig;
  int m_iy_orig;
  int m_iz_orig;
  DsArray<int> m_active;
  DsArray<int> m_active_fracture;
  int* m_hostcell;
  int m_num_active_cells;
  int m_num_active_cells_fracture;
  int m_coord_size;
  int m_zcorn_size;
  char* m_lgrparent;
  char* m_lgrsgrid;
  ReservoirDataArray m_reser;
  int m_num_total_cells;
  int m_num_root_cells;
  int m_nri;
  int m_nrj;
  int m_nrk;
};

typedef DsArray<EGridData*> EGridDataArray;

class EGRIDReader : public ECLGridReader
{
public:
  EGRIDReader (const char* rootname, ResECLError *errors);
  ~EGRIDReader();
public:
  bool ReadKeywords (ResPosLoaderNew* loader);
  bool ValidateFiles(bool required);
  bool IsCornerPoints ();
  void GetRootDimensions(int* ni, int* nj, int* nk);
  bool FileExists ();
  void GetCellVertices(int index, float coords[24]);
  void GetRootActiveCells (int loader_index, DsArray<int>& active_cells);
  const char* GetCoordinatesUnit ();
  void BuildRefinementStructure (ECLRefinementArray* refinements);
  void GetActiveCells (int loader_index, DsArray<int>& active_cells);
  void GetActiveCellsFracture (DsArray<int>& active_cells);
  int CountTotalCells ();
  int CountActiveCells (int loader_index);
  int CountRootActiveCells ();
  bool IsLoaded ();
  char* GetCellRefinementData (int icell, int* index);
  bool IsRefinedModel ();
private:
  void ReadFILEHEAD (ECLReader *rd, int nelems) throw (bool);
  void ReadMAPUNITS (ECLReader *rd) throw (bool);
  void ReadMAPAXES (ECLReader *rd) throw (bool);
  void ReadGRIDHEAD (ECLReader *rd, int nelems) throw (bool);
  void ReadGRIDUNIT (ECLReader *rd) throw (bool);
  void ReadBOXORIG (ECLReader *rd) throw (bool);
  void ReadCOORD (ECLReader *rd) throw (bool);
  void ReadCOORDSYS (ECLReader *rd, int nelems) throw (bool);
  void ReadZCORN (ECLReader *rd) throw (bool);
  void ReadACTNUM (ECLReader* rd) throw (bool);
  void ReadCORSNUM (ECLReader* rd, int nelems) throw (bool);
  void ReadHOSTNUM (ECLReader* rd, int nelems) throw (bool);
  void ReadENDGRID ();
  void ReadLGR (ECLReader* rd, int nelems) throw (bool);
  void ReadLGRPARNT (ECLReader* rd) throw (bool);
  void ReadLGRSGRID (ECLReader* rd) throw (bool);
  void ReadENDLGR (ECLReader* rd) throw (bool);
  EGridData* GetGridData ();
  EGridData* GetGridData (int index);
  void BuildRefinedCells ();
  bool IsDualPorosity ()
  {
    return m_dual_por || m_dual_perm;
  }
private:
  char *m_rootname;
  ResECLError* m_errors;
  char* m_filename;              // EGRID filename
  ECLReader *m_egrid_rd;         // EGRID Reader
  //
  int m_grid_type;               // Grid type:
                                 //  0 - Corner point
                                 //  1 - Unstructured
                                 //  2 - Hybrid (Corner point / Unstructured)
  bool m_dual_por;               
  bool m_dual_perm;
  char* m_mapunits;
  float m_x_end_y_axis;
  float m_y_end_y_axis;
  float m_x_origin;
  float m_y_origin;
  float m_x_end_x_axis;
  float m_y_end_x_axis;
  char* m_gridunit;
  bool m_using_grid_coordinates;
  bool m_file_exists;
  EGridDataArray m_grid_array;
  char* m_current_grid;
  DsHash<DsStringKey,int> m_grid_to_index;
  bool m_is_corner_points;
  AlgMatrix* m_map_axes_transf;
  DsHash<int, EGridData*> m_cellindex_to_griddata;
  DsHash<int, RefinedCellData*> m_cellindex_to_refineddata;
  DsHash<int, IndirectionCellData*> m_indirection_to_refinement;
  DsHash<int, int> m_cellindex_to_gridpos;
  DsArray<int> m_refined_cells;
  bool m_loaded;
};

