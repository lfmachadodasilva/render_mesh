/**
 * BVs hierarchy.
 * author: Cesar Palomo <cpalomo@tecgraf.puc-rio.br>
 * date:   1-Dec-2009
 */
#ifndef GEOMS_HIERARCHY_H
#define GEOMS_HIERARCHY_H

#include "defines.h"
#include "ray.h"
#include "sphere.h"
#include "triangle.h"
#include <alg/matrix.h>
#include <ds/array.h>
#include <vrbv/boxfactory.h>
#include <vrbv/scenedata.h>
#include <vrbv/treebuilder.h>

// forward declarations
class IOStream;

namespace geoms {

class GEOMS_API Hierarchy
{
private:
  class BinTreeNode
  {
  public:
    BinTreeNode ()
    {
    }
    BinTreeNode (vrbv::Node* n, int i)
    {
      node = n;
      index = i;
    }
    vrbv::Node* node;
    int index;
  };
public:
  Hierarchy ();
  virtual ~Hierarchy ();
  bool Serialize (IOStream* s);
  bool Deserialize (IOStream* s);
  static float GetSerializationVersion ();
  void Reset ();
  void SetMaxLeafVertexCount (int n)
  {
    m_max_leaf_vert_count = n;
  }
  vrbv::Node* GetTreeRoot ()
  {
    return m_tree_root;
  }
  vrbv::TreeBuilder::Statistics* GetTreeBuilderStats ()
  {
    return &m_tree_statistics;
  }
  void BuildTree (vrbv::SceneData& scene_data);
  bool HasAddedBlocks ()
  {
    return m_num_added_blocks > 0;
  }
  int GetNumAddedBlocks ()
  {
    return m_num_added_blocks;
  }
  float GetAverageZ ()
  {
    return m_average_z;
  }
  AlgVector& GetScale ()
  {
    return m_scale;
  }
  AlgVector& GetScaleCenter ()
  {
    return m_scale_center;
  }
  void SetNumAddedBlocks (int n)
  {
    m_num_added_blocks = n;
  }
  void SetAverageZ (float z)
  {
    m_average_z = z;
  }
  void SetScale (AlgVector& scale)
  {
    m_scale.Set(scale);
  }
  void SetScaleCenter (AlgVector& center)
  {
    m_scale_center.Set(center);
  }
private:
  bool SerializeNode (IOStream* s, vrbv::Node* node);
  bool SerializeBBox (IOStream* s, vrbv::Box* bbox);
  bool DeserializeNode (IOStream* s, vrbv::Node** node);
  bool DeserializeBBox (IOStream* s, vrbv::Box* bbox);
private:
  int m_num_added_blocks;
  float m_average_z;
  vrbv::Node* m_tree_root;
  AlgVector m_scale;
  AlgVector m_scale_center;
  int m_max_leaf_vert_count;
  vrbv::TreeBuilder::Statistics m_tree_statistics;
};

} // namespace geoms

#endif // GEOMS_HIERARCHY_H
