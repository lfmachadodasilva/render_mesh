/**
  TopS - Topological data structure for mesh representation.
  
  TopS is a software developed by Tecgraf/PUC-Rio & UIUC.
  It is requested that the TopS users provide the appropriate
  credits and references to the work.
  
  References:
  1 - W. Celes, G.H. Paulino, R. Espinha, "A compact adjacency-based
  topological data structure for finite element mesh representation",
  IJNME, 2005 (in press)
  2 - W. Celes, G.H. Paulino, R. Espinha, "Efficient Handling of Implicit
  Entities in Reduced Mesh Representations", JCISE, Special Issue on
  Mesh-Based Geometric Data Processing, 2005 (in press)
  
  Aug 2005
*/

#ifndef _TOP_GRID_BUILDER_H
#define _TOP_GRID_BUILDER_H

class TopModel;
class TopMultiModel;

#include "../defines.h"

class TOPS_API TopGridBuilderOutput
{
public: 
  virtual ~TopGridBuilderOutput() {}

  virtual bool Start() { return true; }
  virtual bool Finish() { return true; }
  virtual void SetElemType(int type) {}
  virtual void SetNNodes(int nnodes) {}
  virtual void SetNElems(int nelems) {}
  virtual void SetJDirInvertedReservoir(bool jdir_inverted) {}
  virtual void SetKDirInvertedReservoir(bool kdir_inverted) {}

  virtual int InsertNode(double x = 0.0, double y = 0.0, double z = 0.0) = 0;
  virtual int InsertElem(int type, int* nids) = 0;  
};

class TOPS_API TopGridBuilderModelOutput : public TopGridBuilderOutput
{
public: 
  TopGridBuilderModelOutput(TopModel* model);
  virtual ~TopGridBuilderModelOutput();

  void SetModel(TopModel* model);
  virtual bool Start();
  virtual bool Finish();
  virtual void SetJDirInvertedReservoir(bool jdir_inverted);
  virtual void SetKDirInvertedReservoir(bool kdir_inverted);
  virtual int InsertNode(double x, double y, double z);
  virtual int InsertElem(int type, int* nids);     

  void SetUpdateAdj(bool flag);  

private:
  TopModel* m_model;
  bool m_update_adj;
};

class TOPS_API TopGridBuilderMultiModelOutput : public TopGridBuilderOutput
{
public: 
  TopGridBuilderMultiModelOutput(TopMultiModel* multimodel);
  virtual ~TopGridBuilderMultiModelOutput();
  virtual bool Start();
  virtual bool Finish();
  virtual void SetJDirInvertedReservoir(bool jdir_inverted);
  virtual void SetKDirInvertedReservoir(bool kdir_inverted);
  virtual int InsertNode(double x, double y, double z);
  virtual int InsertElem(int type, int* nids);

private:
  TopMultiModel* m_multimodel;
};


class TOPS_API TopGridBuilder
{
public:
  enum GridType {
    GRID_TYPE_RECTANGULAR = 0,
    GRID_TYPE_DISC
  };

  enum HexahedronTriang {
    HEXAHEDRON_TRIANG_SIX_TETRA = 0,
    HEXAHEDRON_TRIANG_PYRAMID_TETRA
  };

  /**
      Creates a square grid of the given element type into the given empty model.
      For Q4, Q8, HEX8, HEX20 and HEX8_RESERVOIR element types, a regular grid
    is created.
      For T3 and T6 element types, a 4-8 mesh is created.
      For TET4 and TET10 element types, a mesh of HEX elements each decomposed 
    into 6 TET elements is created.
      For two-dimensional elements, the z coordinate parameters are ignored.
      If the grid cannot be created, returns false.
  */
  /** deprecated */
  static bool BuildGrid(TopModel* m, 
                        int el_type, 
                        int nx, int ny, int nz, 
                        double xmin, double ymin, double zmin, 
                        double xmax, double ymax, double zmax,
                        bool update_adj = true);

  /** deprecated */
  static bool BuildGrid(TopGridBuilderOutput* m, 
                        int el_type, 
                        int nx, int ny, int nz,
                        double xmin, double ymin, double zmin, 
                        double xmax, double ymax, double zmax);

  TopGridBuilder();

  ~TopGridBuilder();

  /** default: GRID_TYPE_RECTANGULAR */
  void SetGridType(GridType gridtype) { m_gridtype = gridtype; }

  /** default: TopModel::ELEMENT_TET4 */
  void SetElemType(TopModel::ElemType elemtype) { m_elemtype = elemtype; }

  /** default: 1x1x1 */
  void SetDimensions(int nx, int ny, int nz) { m_nx = nx; m_ny = ny; m_nz = nz; }

  /** default: (0,0,0) x (1,1,1) */
  void SetBoundingBox(double xmin, double ymin, double zmin, 
                      double xmax, double ymax, double zmax);

  /** default: HEXAHEDRON_TRIANG_SIX_TETRA */
  void SetHexahedronTriangulation(HexahedronTriang v);

  /** default: false */
  void SetJDirInvertedReservoir (bool jdir_inverted);

  /** 
   * KDir inverted = KDIR_UP
   * Default: false 
   */
  void SetKDirInvertedReservoir (bool kdir_inverted);

  /**
    Sets the output stream to which the generated grid will be output.
  */
  void SetOutput(TopGridBuilderOutput* output);

  TopGridBuilderOutput* GetOutput() const
  {
    return m_output;
  }

  /**
    Build a grid defined by this builder's parameters and outputs to 
    the given output stream.
  */
  bool Build();

private:
   bool CreateGridT3(TopGridBuilderOutput* model, 
                     int nx, int ny, 
                     double xmin, double ymin, 
                     double xmax, double ymax);

   bool CreateGridT6(TopGridBuilderOutput* model, 
                     int nx, int ny, 
                     double xmin, double ymin, 
                     double xmax, double ymax);

   bool CreateGridQ4(TopGridBuilderOutput* model, 
                     int nx, int ny,
                     double xmin, double ymin, 
                     double xmax, double ymax);

   bool CreateGridQ8(TopGridBuilderOutput* model, 
                     int nx, int ny,
                     double xmin, double ymin, 
                     double xmax, double ymax);

   bool CreateGridHEX8(TopGridBuilderOutput* model, 
                       int nx, int ny, int nz,
                       double xmin, double ymin, double zmin, 
                       double xmax, double ymax, double zmax);

   bool CreateGridHEX8Reservoir(TopGridBuilderOutput* model, 
                                int nx, int ny, int nz,
                                double xmin, double ymin, double zmin, 
                                double xmax, double ymax, double zmax);

   bool CreateGridHEX20(TopGridBuilderOutput* model, 
                        int nx, int ny, int nz,
                        double xmin, double ymin, double zmin, 
                        double xmax, double ymax, double zmax);

   bool CreateGridTET4(TopGridBuilderOutput* model, 
                       int nx, int ny, int nz,
                       double xmin, double ymin, double zmin, 
                       double xmax, double ymax, double zmax);

   bool CreateGridTET10(TopGridBuilderOutput* model, 
                        int nx, int ny, int nz,
                        double xmin, double ymin, double zmin, 
                        double xmax, double ymax, double zmax);

   bool CreateGridPyramidTET4(TopGridBuilderOutput* model, 
                              int nx, int ny, int nz,
                              double xmin, double ymin, double zmin, 
                              double xmax, double ymax, double zmax);

   bool CreateGridDiscT3(TopGridBuilderOutput* model, 
                         int nx, int ny, 
                         double xmin, double ymin, 
                         double xmax, double ymax);

   bool CreateGridDiscT6(TopGridBuilderOutput* model, 
                         int nx, int ny, 
                         double xmin, double ymin, 
                         double xmax, double ymax);

   bool CreateGridDiscQ4(TopGridBuilderOutput* model, 
                         int nx, int ny,
                         double xmin, double ymin, 
                         double xmax, double ymax);

   bool CreateGridDiscQ8(TopGridBuilderOutput* model, 
                         int nx, int ny,
                         double xmin, double ymin, 
                         double xmax, double ymax);

   bool CreateGridDiscHEX8(TopGridBuilderOutput* model, 
                           int nx, int ny, int nz,
                           double xmin, double ymin, double zmin, 
                           double xmax, double ymax, double zmax);

   bool CreateGridDiscHEX20(TopGridBuilderOutput* model, 
                            int nx, int ny, int nz,
                            double xmin, double ymin, double zmin, 
                            double xmax, double ymax, double zmax);

   bool CreateGridDiscTET4(TopGridBuilderOutput* model, 
                           int nx, int ny, int nz,
                           double xmin, double ymin, double zmin, 
                           double xmax, double ymax, double zmax);

   bool CreateGridDiscTET10(TopGridBuilderOutput* model, 
                            int nx, int ny, int nz,
                            double xmin, double ymin, double zmin, 
                            double xmax, double ymax, double zmax);

private:
  GridType m_gridtype;
  TopModel::ElemType m_elemtype;
  HexahedronTriang m_hexahedron_triang;
  int m_nx, m_ny, m_nz;
  double m_xmin, m_xmax, m_ymin, m_ymax, m_zmin, m_zmax;
  bool m_jdir_inverted_reservoir;
  bool m_kdir_inverted_reservoir;
  TopGridBuilderOutput* m_output;
};

#endif
