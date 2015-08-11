
#ifndef TOPSVIEWRES_TETRA_TEMPLATE_H
#define TOPSVIEWRES_TETRA_TEMPLATE_H

/**
 * Local template definition of the tetrahedral decomposition
 * of a reservoir cell (TopModel::ELEMENT_HEX8_RESERVOIR).
 */
class TpvResCellTetrahedralTemplate
{
private:
  enum { 
    NUM_TETRA_PER_CELL = 6
  };

public:
  TpvResCellTetrahedralTemplate ()
  {
  }

  static int NumTetrahedra ()
  {
    return NUM_TETRA_PER_CELL;
  }

  /**
   * Returns the index of the cell node corresponding to the tetrahedron node,
   * or -1 otherwise.
   */
  static int CellNode (int tetrai, int nodei)
  {
    return CELL_NODES[tetrai][nodei];
  }

  /**
   * Returns the index of the cell face which the tetrahedron face is on,
   * or -1 otherwise.
   */
  static int CellFace (int tetrai, int facei)
  {
    return CELL_FACES[tetrai][facei];
  }

  static bool IsTetrahedronFaceOnCellFace (int tetrai, int facei)
  {
    return CellFace(tetrai, facei) != -1;
  }

  /** 
   * Returns the index of the tetrahedron node corresponding to the 
   * tetrahedron face node. 
   */
  static int TetrahedronNodeInFace (int facei, int nodei)
  {
    return FACE_NODES[facei][nodei];
  }

  /**
   * Returns the index of the tetrahedron adjacent to the given face.
   * The tetrahedron index may be associated to a cell other than 
   * the original one.
   */
  static int AdjacentTetrahedron (int tetrai, int facei)
  {
    return TETRA_NEIGHBORS[tetrai][facei];
  }

private:
  enum { 
    NUM_FACES_PER_TETRA = 4,
    NUM_NODES_PER_TETRA = 4,
    NUM_NODES_PER_FACE = 3
  };

  static const int CELL_NODES[NUM_TETRA_PER_CELL][NUM_NODES_PER_TETRA];
  static const int FACE_NODES[NUM_FACES_PER_TETRA][NUM_NODES_PER_FACE];
  static const int CELL_FACES[NUM_TETRA_PER_CELL][NUM_FACES_PER_TETRA];
  static const int TETRA_NEIGHBORS[NUM_TETRA_PER_CELL][NUM_FACES_PER_TETRA];
};

#endif