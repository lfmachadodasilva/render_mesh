#pragma once
#include <gpos/defines.h>
#include <gpos/model/loadernew.h>
#include <gpos/common/util.h>
#include <ds/array.h>
#include <ds/hash.h>
#include "common.h"

class ECLReader;

class CellData
{
public:
  CellData ()
    : m_i(-1),
      m_j(-1),
      m_k(-1),
      m_active(1),
      m_host_cell(-1),
      m_coarsening_group(-1)
  {
    m_corners = (float*) calloc(24, sizeof(float));
  }

  ~CellData ()
  {
    free(m_corners);
  }

  void SetPosition (int i, int j, int k)
  {
    m_i = i;
    m_j = j;
    m_k = k;
  }
  void SetActive (int active)
  {
    m_active = active;
  }
  void SetHostCellNumber (int num)
  {
    m_host_cell = num;
  }
  void SetCoarseningGroupNumber (int num)
  {
    m_coarsening_group = num;
  }
  void SetNumber (int icell)
  {
    m_icell = icell;
  }
  void SetCorners (const float values[24])
  {
    for(int i=0; i<24; i++)
      m_corners[i] = values[i];
  }
  void GetCorners (float values[24])
  {
    for(int i=0; i<24; i++)
      values[i] = m_corners[i];
  }
private:
  int m_i;
  int m_j;
  int m_k;
  int m_icell;
  int m_active;
  int m_host_cell;
  int m_coarsening_group;
  float *m_corners;
};

typedef DsArray<CellData*> CellDataArray;

class GridData
{
public:
  GridData ()
  : m_nx(-1),
    m_ny(-1),
    m_nz(-1),
    m_radial(false),
    m_mapunits(NULL),
    m_x_end_yaxis(-1),
    m_y_end_yaxis(-1),
    m_x_origin(-1),
    m_y_origin(-1),
    m_x_end_xaxis(-1),
    m_y_end_xaxis(-1),
    m_current_icell(-1)
  , m_num_active_cells(0)
  , m_num_active_cells_fracture(0)
  , m_active_cells(NULL)
  {
  }
  ~GridData ()
  {
    FREE_AND_SET_NULL(m_mapunits);
    FREE_AND_SET_NULL(m_active_cells);
    //FREE_AND_SET_NULL(m_active_cells_fracture);
  }
  void SetDimensions (int nx, int ny, int nz)
  {
    m_nx = nx;
    m_ny = ny;
    m_nz = nz;
    // initialize dimension arrays
    m_num_tot_cells = nx * ny * nz;
    m_num_active_cells = 0;
    m_num_active_cells_fracture = 0;
    m_cellarray.Resize(m_num_tot_cells);
    m_active_cells = (int*) calloc(m_num_tot_cells, sizeof(int));
    //m_active_cells_fracture = (int*) calloc(m_num_tot_cells, sizeof(int));
  }
  void SetRadial (bool radial)
  {
    m_radial = radial;
  }
  void GetDimensions (int *nx, int *ny, int *nz)
  {
    *nx = m_nx;
    *ny = m_ny;
    *nz = m_nz;
  }
  bool IsRadial ()
  {
    return m_radial;
  }
  void SetMapUnits (const char* s)
  {
    m_mapunits = PSUtil::StrDup(s);
  }
  void SetCoords (int i, int j, int k, int icell, int active)
  {
    m_current_icell = icell-1;
    CellData *cell = new CellData;
    cell->SetPosition(i, j, k);
    cell->SetNumber(icell);
    cell->SetActive(active);
    if (active == 1) {
      m_active_cells[m_num_active_cells++] = m_current_icell;
      //m_active_cells_fracture[m_num_active_cells_fracture++] = m_current_icell;
    }
    m_cellarray.Insert(cell, m_current_icell);
  }

  void SetCoords (int i, int j, int k, int icell, int active, 
                  int host_cell, int coarsening_group)
  {
    m_current_icell = icell-1;
    CellData *cell = new CellData;
    cell->SetPosition(i, j, k);
    cell->SetNumber(icell);
    cell->SetActive(active);
    cell->SetHostCellNumber(host_cell);
    cell->SetCoarseningGroupNumber(coarsening_group);
    if (active == 1) {
      m_active_cells[m_num_active_cells++] = m_current_icell;
      //m_active_cells_fracture[m_num_active_cells_fracture++] = m_current_icell;
    }
    m_cellarray.Insert(cell, m_current_icell);
    
  }

  void SetCorners (const float values[24])
  {
    CellData* c = m_cellarray.Get(m_current_icell);
    c->SetCorners(values);
  }
  void GetCorners (int index, float values[24])
  {
    CellData* c = m_cellarray.Get(index);
    c->GetCorners(values);
  }
  const char* GetMapUnits ()
  {
    return m_mapunits;
  }
  void SetMapAxes (float x_end_yaxis,
                   float y_end_yaxis,
                   float x_origin,
                   float y_origin,
                   float x_end_xaxis,
                   float y_end_xaxis)
  {
    m_x_end_yaxis = x_end_yaxis;
    m_y_end_yaxis = y_end_yaxis;
    m_x_origin = x_origin;
    m_y_origin = y_origin;
    m_x_end_xaxis = x_end_xaxis;
    m_y_end_xaxis = y_end_xaxis;
  }
  void GetMapAxes (float *x_end_yaxis,
                   float *y_end_yaxis,
                   float *x_origin,
                   float *y_origin,
                   float *x_end_xaxis,
                   float *y_end_xaxis)
  {
    *x_end_yaxis = m_x_end_yaxis;
    *y_end_yaxis = m_y_end_yaxis;
    *x_origin = m_x_origin;
    *y_origin = m_y_origin;
    *x_end_xaxis = m_x_end_xaxis;
    *y_end_xaxis = m_y_end_xaxis;
  }

  const int* GetActiveCells ()
  {
    return m_active_cells;
  }

  //int* GetActiveCellsFracture ()
  //{
    //return m_active_cells_fracture;
  //}

  int CountCells ()
  {
    return m_num_tot_cells;
  }

  int CountActiveCells ()
  {
    return m_num_active_cells;
  }

  int CountActiveCellsFracture ()
  {
    return 0;
  }
private:
  int m_nx;
  int m_ny;
  int m_nz;
  bool m_radial;
  char* m_mapunits;
  float m_x_end_yaxis;
  float m_y_end_yaxis;
  float m_x_origin;
  float m_y_origin;
  float m_x_end_xaxis;
  float m_y_end_xaxis;
  CellDataArray m_cellarray;
  int m_current_icell;
  int m_num_tot_cells;
  int m_num_active_cells;
  int m_num_active_cells_fracture;
  int* m_active_cells;
  //int* m_active_cells_fracture;
};

class LGRData: public GridData
{
public:
  LGRData (const char *name)
  : m_ipos_boxorig(-1),
    m_jpos_boxorig(-1),
    m_kpos_boxorig(-1),
    m_lower_i(-1),
    m_lower_j(-1),
    m_lower_k(-1),
    m_upper_i(-1),
    m_upper_j(-1),
    m_upper_k(-1),
    m_max_wells(-1),
    m_ntheta(0),
    m_parent(NULL)
  {
    m_name = PSUtil::StrDup(name);
  }
  ~LGRData ()
  {
    FREE_AND_SET_NULL(m_name);
    FREE_AND_SET_NULL(m_parent);
  }
  void SetBoxOrig (int i, int j, int k)
  {
    m_ipos_boxorig = i;
    m_jpos_boxorig = j;
    m_kpos_boxorig = k;
  }
  void GetBoxOrig (int *i, int *j, int *k)
  {
    *i = m_ipos_boxorig;
    *j = m_jpos_boxorig;
    *k = m_kpos_boxorig;
  }
  void SetParent (char* name)
  {
    m_parent = PSUtil::StrDup(name);
  }
  // Item 1 - NTHETA(=0 for non-radial, =1, 4 or 8 for radial LGR)
  // Items 2 to 7 define the LGR position in the host grid:
  // Item 2 - Lower I-index in host
  // Item 3 - Lower J-index in host
  // Item 4 - Lower K-index in host
  // Item 5 - Upper K-index in host
  // Item 6 - Upper J-index in host
  // Item 7 - Upper I-index in host
  // Item 8 - Max wells in LGR
  // Item 9 - NX for local grid
  // Item 10 - NY for local grid
  // Item 11 - NZ for local grid
  void SetParameters (int* values)
  {
    m_ntheta = values[0];
    m_lower_i = values[1];
    m_lower_j = values[2];
    m_lower_k = values[3];
    m_upper_i = values[4];
    m_upper_j = values[5];
    m_upper_k = values[6];
    m_max_wells = values[7];
    SetDimensions(values[8], values[9], values[10]); 
  }
private:
  char *m_name;
  int m_ipos_boxorig;
  int m_jpos_boxorig;
  int m_kpos_boxorig;
  char* m_parent;
  int m_lower_i;
  int m_lower_j;
  int m_lower_k;
  int m_upper_i;
  int m_upper_j;
  int m_upper_k;
  int m_max_wells;
  int m_ntheta;
};

class GRIDReader : public ECLGridReader
{
public:
  GRIDReader (const char* rootname, ResECLError *errors);
  ~GRIDReader();
  bool ReadKeywords (ResPosLoaderNew* loader);
  bool ValidateFiles(bool required);
  bool IsCornerPoints ();
  void GetRootDimensions(int* ni, int* nj, int* nk);
  bool FileExists ();
  void GetCellVertices(int index, float coords[24]);
  void GetRootActiveCells (int loader_index, DsArray<int>& active_cells);
  void GetRootActiveCellsFracture (DsArray<int>& active_cells);
  const char* GetCoordinatesUnit ();
  void BuildRefinementStructure (ECLRefinementArray* refinements);
  void GetActiveCells (int loader_index, DsArray<int>& active_cells);
  void GetActiveCellsFracture (DsArray<int>& active_cells);
  int CountTotalCells ();
  int CountActiveCells (int loader_index);
  int CountActiveCellsFracture ();
  int CountRootActiveCells ();
  int CountRootActiveCellsFracture ();
  bool IsLoaded ();
  char* GetCellRefinementData (int icell, int* index);
  bool IsRefinedModel ();
private:
  void ReadDIMENS (ECLReader *rd) throw (bool);
  void ReadRADIAL (ECLReader *rd) throw (bool);
  void ReadBOXORIG (ECLReader *rd) throw (bool);
  void ReadMAPUNITS (ECLReader* rd) throw (bool);
  void ReadMAPAXES (ECLReader* rd) throw (bool);
  void ReadGRIDUNIT (ECLReader *rd) throw (bool);
  void ReadCOORDSType4 (ECLReader* rd) throw (bool);
  void ReadCOORDSType5 (ECLReader* rd) throw (bool);
  void ReadCOORDSType7 (ECLReader* rd) throw (bool);
  void ReadCORNERS (ECLReader* rd) throw (bool);
  void ReadLGR (ECLReader* rd, int nelems) throw (bool);
  void ReadLGRILG (ECLReader* rd) throw (bool);
  bool LGRExists (const char* name);
  GridData* GetCurrentGrid () throw (bool);
  LGRData* GetCurrentRefinedGrid ();
private:
  ResECLError* m_errors;

  char* m_filename;          // GRID filename
  ECLReader *m_grid_rd;      // GRID Reader
  DsHash <DsStringKey, LGRData*> m_name_to_lgr;
  GridData* m_maingrid;
  char* m_current_lgr;
  int m_grid_type;
  int m_main_grid_icell;
  StringArray m_grid_array;
  bool m_file_exists;
  bool m_using_grid_coordinates;
  char* m_gridunit;
  bool m_loaded;
};

