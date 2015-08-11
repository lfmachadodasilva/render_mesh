
#ifndef TOP_MULTI_MODEL_RES_REFINEMENT_H
#define TOP_MULTI_MODEL_RES_REFINEMENT_H

#include "../multimodel.h"

/**
*/
class TOPS_API TopMultiReservoirRefinement
{
public:

  TopMultiReservoirRefinement (TopMultiModel* multimodel = NULL);

  ~TopMultiReservoirRefinement ();

  void SetMultiModel (TopMultiModel* multimodel);

  /**
    Refines an element of a reservoir grid into (nx x ny x nz) child elements 
    placed at the underneath level (i+1). If the parent element is at the last
    level, a new level is created.
    This method will work correctly only for reservoir grids (structured meshes
    of HE8_RESERVOIR elements).
  */
  bool RefineElem (TopElement elem, int nx, int ny, int nz);

  /**
   * Returns the coordinates of a trilinear interpolation of element coordinates
   * at 'nodepos', given interpolation parameters 'r', 's' and 't'.
   */
  void InterpolatePoint (int topology, 
                         const float* nodepos, 
                         float r, float s, float t, 
                         float* x, float* y, float* z);
private:

  int FindRefinedNodeParent (int topology, 
                             int i, int j, int k, 
                             int nx, int ny, int nz);

  void CreateRefinedElems (TopElement elem, 
                           int nx, int ny, int nz, 
                           const TopRawArray<TopNode>& childnodes, 
                           bool update_adj);

  void CreateRefinedNodes (TopElement elem, 
                           int nx, int ny, int nz, 
                           TopRawArray<TopNode>& o_childnodes);

  void ReuseRefinedNodesOfAdjFaces (TopElement elem, 
                                    int nx, int ny, int nz,
                                    TopRawArray<TopNode>& o_childnodes);

  void ReuseRefinedNodesOfAdjEdges (TopElement elem, 
                                    int nx, int ny, int nz,
                                    TopRawArray<TopNode>& o_childnodes);

  void ReuseRefinedNodesOfAdjVertices (TopElement elem, 
                                       int nx, int ny, int nz,
                                       TopRawArray<TopNode>& o_childnodes);

  void DetermineNodesOfElemInGrid (int topology, 
                                   int nx, int ny, int nz, 
                                   int i, int j, int k, 
                                   const TopNode* nodes, 
                                   TopNode* o_elem_nodes);

  TopModel* GetChildModel (TopModel* model);

  int GetChildNodeGridSize (TopElement elem, int nx, int ny, int nz);

  void GetChildNodeGridDimensions (TopElement elem, 
                                   int nx, int ny, int nz,
                                   int* o_node_nx, 
                                   int* o_node_ny, 
                                   int* o_node_nz);

  int GetNodeIndexInGrid (int nx, int ny, int nz, 
                          int i, int j, int k);

  void GetElemNodePositionInGrid (TopElement elem, int node_lid,
                                  int* o_i, int* o_j, int* o_k);

  void ComputeRefinedNodePositionsAndParents (
      TopElement elem, int nx, int ny, int nz, 
      TopRawArray<float>& opos, TopRawArray<TopNode>& oparent);

  TopFaceUse FindAdjFaceUseWithMatchingRefinement (
      int topology, int nx, int ny, int nz,
      TopModel* model, TopFaceUse fu);

  bool MatchRefinedFaces (int topology, int nx, int ny, int nz, 
                          TopModel* model, TopFaceUse fu, TopFaceUse adj_fu);

  void GetRefinedNodes (TopModel* model, TopFaceUse fu, 
                        TopRawArray<TopNode>& o_child_nodes);

  void GetRefinedNodeIndicesInGrid (int topology, int nx, int ny, int nz,
                                    TopModel* model, TopFaceUse fu, 
                                    TopRawArray<int>& o_indices);

  TopEdgeUse FindAdjEdgeUseWithMatchingRefinement (
      int topology, int nx, int ny, int nz,
      TopModel* model, TopEdgeUse eu, bool non_manifold);

  bool MatchRefinedEdges (int topology, int nx, int ny, int nz, 
                          TopModel* model, TopEdgeUse eu, TopEdgeUse adj_eu);

  void GetRefinedNodes (TopModel* model, TopEdgeUse eu, 
                        TopRawArray<TopNode>& o_child_nodes);

  void GetRefinedNodeIndicesInGrid (int topology, int nx, int ny, int nz,
                                    TopModel* model, TopEdgeUse eu, 
                                    TopRawArray<int>& o_indices);

  TopVertexUse FindAdjVertexUseWithMatchingRefinement (
      int topology, int nx, int ny, int nz,
      TopModel* model, TopVertexUse vu, bool non_manifold);

  bool MatchRefinedVertices (int topology, int nx, int ny, int nz, 
                             TopModel* model, 
                             TopVertexUse vu, TopVertexUse adj_vu);

  TopNode GetRefinedNode (TopModel* model, TopVertexUse vu);

  int GetRefinedNodeIndexInGrid (int topology, int nx, int ny, int nz, 
                                 TopVertexUse vu);

  void GetNodePositionInRefinedGrid (int topology, 
                                     int nx, int ny, int nz, 
                                     TopVertexUse vu,
                                     int* o_child_node_i, 
                                     int* o_child_node_j, 
                                     int* o_child_node_k);

  void GetFaceRefinement (int topology, int nx, int ny, int nz, 
                          int face_lid, int* o_nr, int* o_ns);

  int GetEdgeRefinement (int topology, int nx, int ny, int nz, int edge_lid);

  void NodePositionInFaceRefinementToGrid (int topology, 
                                           int nx, int ny, int nz,
                                           int face_lid, int face_i, int face_j, 
                                           int* o_i, int* o_j, int* o_k);

  bool NodePositionInGridToFaceRefinement (int topology, int nx, int ny, int nz,
                                           int node_i, int node_j, int node_k, 
                                           int face_lid, int* o_i, int* o_j);

  int GetNodeIndexInFaceRefinement (int topology, int nx, int ny, int nz,
                                    int face_lid, int i, int j);

  void NodePositionInEdgeRefinementToGrid (int topology, int nx, int ny, int nz,
                                           int edge_lid, int edge_i, 
                                           int* o_i, int* o_j, int* o_k);

  bool NodePositionInGridToEdgeRefinement (int topology, int nx, int ny, int nz, 
                                           int node_i, int node_j, int node_k, 
                                           int edge_lid, int* o_i);

  TopNode InsertChildNode (TopModel* model,
                           float x, float y, float z,
                           TopNode parent);

  TopElement InsertChildElem (TopModel* model,
                              const TopNode* nodes,
                              TopElement parent,
                              int index_in_parent,
                              TopElement prev_sibling,
                              bool update_adj);

  bool IsJDirInvertedReservoir () const
  {
    TopModel* rootmodel = m_multimodel->GetRootModel();
    return rootmodel->IsReservoir() && rootmodel->IsJDirInvertedReservoir();
  }

  bool IsKDirInvertedReservoir () const
  {
    TopModel* rootmodel = m_multimodel->GetRootModel();
    return rootmodel->IsReservoir() && rootmodel->GetKDirReservoir() == TopModel::K_DIR_UP;
  }

  void GetRefinedNodeNatCoords(int ni, int nj, int nk,
                               int i, int j, int k,
                               float* o_r, 
                               float* o_s, 
                               float* o_t);

private:
  TopMultiModel* m_multimodel;
};

#endif

