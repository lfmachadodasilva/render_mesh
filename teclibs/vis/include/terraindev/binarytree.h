#ifndef TERRAIN_LINEAR_BINARY_TREE_H
#define TERRAIN_LINEAR_BINARY_TREE_H

// ** Linear Binary Tree index structure:
//
//                               00                                - level 0
//               01                              02                - level 1
//       03              04              05              06        - level 2
//   07      08      09      10      11      12      13      14    - level 3
// 15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  - level 4
// 
// ** Size calculations
//
// level_size(level) =  2^level    =  1<<level     // number of nodes of level "level"
// tree_size(depth)  = (2^depth)-1 = (1<<depth)-1  // number of nodes of a tree with "depth" levels
//
// ** Indexing calculations
//
// parent(i) = floor((i-1)/2) = (i-1)>>1
// children(i) = (2*i)+k = (i<<1)+k, k = 1..2
//
// ** Coordinate calculations
//
// level(i) = floor(log2(i+1))         // precision problems, calcutated iteratively in the code
// coord(i) = i - tree_size(level(i))  // local coordinate of the node inside its level in the binary tree

//-----------------------------------//
// Includes and Forward Declarations //
//-----------------------------------//

#include "baseclass.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

//------------------//
// Static Constants //
//------------------//

static const long BINARYTREE_LEFT  = 1L;
static const long BINARYTREE_RIGHT = 2L;

static const int  BINARYTREE_MAX_DEPTH = 8*sizeof(long)-1;
static const long BINARYTREE_MAX_INDEX = LONG_MAX;

//------------------//
// Class Definition //
//------------------//

template <class TYPE>
class TERRAINAPI TrnLinearBinaryTree : public TrnBaseClass
{
public:

  // Class Name

  static const char* CLASSNAME () {return "TrnLinearBinaryTree";}
  virtual const char* ClassName () const {return CLASSNAME();}

  // Constructor and Destructor

  TrnLinearBinaryTree ()
  : m_depth(0)
  , m_tree_size(0)
  , m_first_leaf(0)
  , m_used_leaves(0)
  , m_nodes(NULL)
  {
  }

  ~TrnLinearBinaryTree ()
  {
    Clear();
  }

  // Structural Methods

  bool AddLeaf ();
  bool RemLeaf ();
  void Clear ();

  // Other Methods

  inline int GetDepth () const
  {
    return m_depth;
  }

  inline long GetSize () const
  {
    return m_tree_size;
  }

  inline bool IsValid (long i) const
  {
    return (i >= 0L && i < m_tree_size);
  }

  inline bool IsLeaf (long i) const
  {
    return (i >= m_first_leaf);
  }

  inline long GetParent (long i) const
  {
    return i > 0L ? (i - 1L) >> 1 : -1L;
  }

  inline int GetLevel (long i) const
  { 
    i += 1L;
    int level = 0;
    while (i > 1L)
    {
      i >>= 1;
      ++level;
    }
    return level;
  }

  inline long GetLevelSize (int level) const
  {
    return (1L << level);
  }

  inline long GetNumNodes (int depth) const
  {
    return ((1L << depth) - 1L);
  }

  inline long GetNumLeaves () const
  {
    return (m_tree_size - m_first_leaf);
  }

  inline long GetUsedLeaves () const
  {
    return (m_used_leaves);
  }

  inline long GetFirstLeaf () const
  {
    return m_first_leaf;
  }

  inline long GetLeftChild (long i) const
  {
    return IsLeaf(i) ? -1 : (i << 1) + BINARYTREE_LEFT;
  }

  inline q_index GetRightChild (long i) const
  {
    return IsLeaf(i) ? -1 : (i << 1) + BINARYTREE_RIGHT;
  }

  inline void SetData (long i, TYPE const& data)
  {
    m_nodes[i] = data;
  }

  inline TYPE const& GetDataRef (long i) const
  {
    return m_nodes[i];
  }

  inline TYPE& GetDataRef (long i)
  {
    return m_nodes[i];
  }

  inline TYPE GetData (long i) const
  {
    return m_nodes[i];
  }

private:

  int m_depth;
  long m_tree_size;
  long m_first_leaf;
  long m_used_leaves;
  TYPE* m_nodes;
};

//--------------------//
// Structural Methods //
//--------------------//

template <class TYPE>
bool TrnLinearBinaryTree<TYPE>::AddLeaf ()
{
  // If needed, double the tree capacity by creating a whole sister tree sharing a common new root
  long new_used_leaves = m_used_leaves + 1;
  if (new_used_leaves > GetNumLeaves())
  {
    // Allocate a new tree
    long num_levels = GetDepth() + 1;
    long num_nodes = (GetSize() << 1) + 1;
    TYPE* new_nodes = (TYPE*)malloc(num_nodes*sizeof(TYPE));
    if (!new_nodes)
      return false;

    // Call constructor for new root
    new(&new_nodes[0]) TYPE;

    // Copy the existing elements from the old tree and call constructor for new elements on the new tree
    TYPE* src_ptr = m_nodes;
    TYPE* dst_ptr = new_nodes+1;
    long level = 0; // of the new (largest) tree
    long elem_count = 1;
    while (++level < num_levels)
    {
      memcpy(dst_ptr, src_ptr, elem_count * sizeof(TYPE));
      src_ptr += elem_count;
      dst_ptr += elem_count;
      for (int i = 0; i < elem_count; ++i)
        new(dst_ptr++) TYPE;
      elem_count <<= 1;
    }

    // Free old tree and update state
    free(m_nodes);
    m_nodes = new_nodes;
    m_depth = num_levels;
    m_tree_size = num_nodes;
    m_first_leaf = num_nodes >> 1;
  }
  m_used_leaves = new_used_leaves;
  return true;
}

template <class TYPE>
bool TrnLinearBinaryTree<TYPE>::RemLeaf ()
{
  if (m_used_leaves <= 0)
    return false;

  // If needed, cut the tree capacity in half by deleting the root and the whole sister tree
  long new_used_leaves = m_used_leaves - 1;
  if (new_used_leaves <= GetNumLeaves() >> 1)
  {
    // Allocate a new tree
    long num_levels = GetDepth() - 1;
    long num_nodes = GetSize() >> 1;
    TYPE* new_nodes = NULL;
    if (num_nodes > 0)
    {
      new_nodes = (TYPE*)malloc(num_nodes*sizeof(TYPE));
      if (!new_nodes)
        return false;
    }

    // Call destructor for the old root
    m_nodes[0].~TYPE();

    // Copy old elements to the new tree and call destructor for discarded elements on the old tree
    TYPE* src_ptr = m_nodes+1;
    TYPE* dst_ptr = new_nodes;
    long level = 0; // of the old (largest) tree
    long elem_count = 1;
    while (++level <= num_levels)
    {
      memcpy(dst_ptr, src_ptr, elem_count * sizeof(TYPE));
      src_ptr += elem_count;
      dst_ptr += elem_count;
      for (int i = 0; i < elem_count; ++i)
        (*src_ptr++).~TYPE();
      elem_count <<= 1;
    }

    // Free old tree and update state
    free(m_nodes);
    m_nodes = new_nodes;
    m_depth = num_levels;
    m_tree_size = num_nodes;
    m_first_leaf = num_nodes >> 1;
  }
  m_used_leaves = new_used_leaves;
  return true;
}

template <class TYPE>
void TrnLinearBinaryTree<TYPE>::Clear ()
{
  for (int i = 0; i < m_tree_size; ++i)
    m_nodes[i].~TYPE();
  free(m_nodes);
  m_nodes = NULL;
  m_used_leaves = 0;
  m_first_leaf = 0;
  m_tree_size = 0;
  m_depth = 0;
}


#endif // TERRAIN_LINEAR_BINARY_TREE_H
