// geometryloader.h
// fabraham@tecgraf.puc-rio.br
// Dec 2010
#ifndef RES_TOPS_GEOMETRY_LOADER_H
#define RES_TOPS_GEOMETRY_LOADER_H

#include <gpos/model/loadernew.h>
#include <alg/matrix.h>
#include <ds/array.h>

class TopModel;

/**
 * This class implements a geometry loader from an already built
 * TopS structure.
 *
 * Assumes the structure represents a corner points geometry without grid refinements.
 * Also assumes all cells are active.
 */
class ResTopsGeometryLoader : public ResPosGeometryLoader
{
public:
  /**
   * Constructor. Receives the TopS model.
   * 'coords_unit' specifies the unit of coordinates in 'rootmodel'.
   * Assumes the structure represents a corner points geometry without grid refinements.
   * Also assumes all cells are active.
   */
  ResTopsGeometryLoader (TopModel* rootmodel, const char* coords_unit);
  ~ResTopsGeometryLoader ();
  /**
   * Specifies an optional transformation matrix for the input model
   * vertices.
   */
  void SetCoordinatesTransformation (const AlgMatrix& t);
  /**
   * Specifies an optional array with active cells ids.
   */
  void SetActiveCells (const DsArray<int>* act_cells);

  /**
   * Specifies an optional array with, for each active cell set by SetActiveCells,
   * the id in the complete cells array.
   */
  void SetPackedToComplete (const DsArray<int>* packed_to_complete);

private:
  float GetVersion () const
  {
    // version 0.0: until 19/01/2011
    // version 0.1: included coordinates unit from the original model
    return 0.1f;
  }
  bool Load (const char* src, ResPosModelNew* mdl);
  bool HasMeshInformation ()
  {
    return true;
  }
  int GetVertexCount ();
  void GetVertexCoords (int vertex_index, float v[3]);
  void GetCellVertices (int cell_index, int vertices[8]);
  void GetFilenames (const char *src,
                     int        *numfiles,
                     char     ***filenames);
  void GetCellVertices (int index, float coords[24])
  {
    GetCellVerticesCoordsFromMesh(index, coords);
  }
private:
  TopModel* m_root_model;
  AlgMatrix* m_coords_transf;
  char* m_coords_unit;
  int m_act_cells_count;
  int* m_act_cells;
  int* m_packed_to_complete;
};

#endif

