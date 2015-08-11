/**
 *	A polyhedron model for a reservoir.
 *	author: Cesar Palomo <cpalomo@tecgraf.puc-rio.br>
 *	date:   2-Dec-2009
 */

#ifndef vis_tops_geoms_polyhedra_model_h
#define vis_tops_geoms_polyhedra_model_h

#include <ds/array.h>
#include <ds/mtvar.h>
#include <geoms/block.h>
#include <tops/handles.h>
#include <tops/multimodel.h>

namespace topsgeoms {

#define ALL_LAYERS -1

//* 'PolyhedraModelRes' Class
//Represents a polyhedron model for a reservoir.
class PolyhedraModelRes
{
public:
  /**
   * @param multi_model reservoir model
   * @param active_poly array of booleans for active polyhedrons
   */
  PolyhedraModelRes (TopMultiModel* multi_model, 
                     const bool* active_poly);
  /**
   * @param multi_model reservoir model
   * @param active_cells array of booleans for active cells
   * @param only_act if true, only active cells are added.
   * @param layer if different from ALL_LAYERS, only cells on a given layer are added. Default is ALL_LAYERS.
   */
  PolyhedraModelRes (TopMultiModel* multi_model, 
                     const bool* active_cells,
                     bool only_act,
                     int layer);
  PolyhedraModelRes (const PolyhedraModelRes& poly_model);
	~PolyhedraModelRes ();
  bool Serialize (IOStream* s);
  bool Deserialize (IOStream* s);
  static float GetSerializationVersion ();
  // TODO remove methods from here...
  const geoms::Block& GetBlock (int block_index) const
  {
    return m_block.GetRef(block_index);
  }
  const DsArray<geoms::Block>& GetBlocks () const
  {
    return m_block;
  }
  const DsArray<int>& GetBlockPolys () const
  {
    return m_block_polys;
  }
  // hierarchy setup
  int GetNumBlocks () const
  {
    return m_num_blocks;
  }
  void GetMinIJK (int* min_i, int* min_j, int* min_k) const
  {
    *min_i = m_min_i;
    *min_j = m_min_j;
    *min_k = m_min_k;
  }
  void GetNumBlocksIJK (int* num_blocks_i, 
                        int* num_blocks_j, 
                        int* num_blocks_k) const
  {
    *num_blocks_i = m_num_blocks_i;
    *num_blocks_j = m_num_blocks_j;
    *num_blocks_k = m_num_blocks_k;
  }
  TopElement GetPoly (int poly_index) const
  {
    return m_poly_array.Get(poly_index);
  }
  int GetPolyID (int poly_index) const
  {
    TopElement elem = GetElem(poly_index);
    return GetModel(elem)->GetId(elem);
  }
  int Index (int poly_index) const;
  int Index (TopElement elem) const;
  // TODO ...until here
  void Setup ();
  // polys info
  int GetPolyCount () const
  {
    return m_poly_array.Size();
  }
  // edges info
  int GetEdgeCount (int poly_index) const
  {
    return 12;
  }
  void GetEdgeCoords (float* coords, int poly_index, int edge_index) const;
  // faces info
  int GetFaceCount (int poly_index) const
  {
    return 6;
  }
  int GetFaceVertexCount (int poly_index, int face_index) const
  {
    return 4;
  }
  void GetFaceCoords (float* coords, int poly_index, int face_index) const;
  // vertices info
  int GetVertexCount (int poly_index) const
  {
    return 8;
  }
  void GetVertexCoords (int* vertex_count, float* coords, int poly_index) const
  {
    assert(m_poly_array.ValidIndex(poly_index));

    *vertex_count = GetVertexCount(poly_index);

    TopElement elem = GetElem(poly_index);
    TopModel* model = GetModel(elem);
    for (int v = 0; v < *vertex_count; v++) { 
      TopNode node = model->GetNode(elem, v);
      model->GetPositionFloat(node, coords, coords+1, coords+2);
      coords += 3;
    }
  }
  TopMultiModel* GetTopMultiModel () const
  {
    return m_multi_model;
  }
  bool IsOnlyActive () const
  {
    return m_only_act;
  }
  int GetActiveLayer () const
  {
    return m_active_layer;
  }
  TopElement GetElem (int poly_index) const
  {
    return GetPoly(poly_index);
  }
  static void SetBlockSize (int ni, int nj, int nk);
  static void GetDefaultBlockSize (int* ni, int* nj, int* nk)
  {
    *ni = s_block_size_i.Get();
    *nj = s_block_size_j.Get();
    *nk = s_block_size_k.Get();
  }
  void GetUsedBlockSize (int* ni, int* nj, int* nk) const
  {
    *ni = m_block_size_i;
    *nj = m_block_size_j;
    *nk = m_block_size_k;
  }
private:
  void InitPolyArray ();
  void InitBlocks ();
  int Index (int i, int j, int k) const;
  void GetRootIndices (int poly_index, 
                       int* i, 
                       int* j, 
                       int* k) const;
  void GetRootIndices (TopElement elem, 
                       int* i, 
                       int* j, 
                       int* k) const;
  TopModel* GetModel (TopElement elem) const
  {
    return m_multi_model->GetElemModel(elem);
  }
  int GetLayer (int poly_index) const 
  {
    TopElement el = GetElem(poly_index);
    return m_multi_model->GetRootElemReverseIdK(el);
  }
private:
  TopMultiModel* m_multi_model;
  // TODO remove these members
  DsArray<geoms::Block> m_block;   // blocks info
  DsArray<int> m_block_polys;      // array of blocks polys
  int m_min_i, m_min_j, m_min_k;
  int m_num_blocks_i, m_num_blocks_j, m_num_blocks_k, m_num_blocks;
  DsArray<TopElement> m_poly_array;
  bool m_only_act;
  int m_active_layer;
  const bool* m_active_poly;
private:
  static DsMTVar<int> s_block_size_i;
  static DsMTVar<int> s_block_size_j;
  static DsMTVar<int> s_block_size_k;
  int m_block_size_i;
  int m_block_size_j;
  int m_block_size_k;
};

#define TOP_INTERSECT geoms::Intersect<topsgeoms::PolyhedraModelRes>

}; // namespace topsgeoms

#endif // vis_tops_geoms_polyhedra_model_h
