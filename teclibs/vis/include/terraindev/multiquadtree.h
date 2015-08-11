#ifndef TERRAIN_QUADTREE_LINEAR_MULTI_H
#define TERRAIN_QUADTREE_LINEAR_MULTI_H

#include "baseclass.h"
#include "quadtreedefines.h"

#include <mthread/atomicpointer.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// ** QuadTree branch structure:
//
// (matricial indices)                     (flipped indices)
//
// - level 0                               - level 0
// 
// 0                                       0
// 
// - level 1                               - level 1
// 
// 1  2                                    1  2
// 3  4                                    3  4
// 
// - level 2                               - level 2
// 
// 05 06 07  8                             05 06 09 10
// 09 10 11 12                             07 08 11 12
// 13 14 15 16                             13 14 17 18
// 17 18 19 20                             15 16 19 20
// 
// - level 3                               - level 3
// 
// 21 22 23 24 25 26 27 28                 21 22 25 26 37 38 41 42
// 29 30 31 32 33 34 35 36                 23 24 27 28 39 40 43 44
// 37 38 39 40 41 42 43 44                 29 30 33 34 45 46 49 50
// 45 46 47 48 49 50 51 52                 31 32 35 36 47 48 51 52
// 53 54 55 56 57 58 59 60                 53 54 57 58 69 70 73 74
// 61 62 63 64 65 66 67 68                 55 56 59 60 71 72 75 76
// 69 70 71 72 73 74 75 76                 61 62 65 66 77 78 81 82
// 77 78 79 80 81 82 83 84                 63 64 67 68 79 80 83 84
// 
// - level 4
// 
// 085 086 087 088 089 090 091 092 093 094 095 096 097 098 099 100     085 086 089 090 101 102 105 106 149 150 153 154 165 166 169 170
// 101 102 103 104 105 106 107 108 109 110 111 112 113 114 115 116     087 088 091 092 103 104 107 108 151 152 155 156 167 168 171 172
// 117 118 119 120 121 122 123 124 125 126 127 128 129 130 131 132     093 094 097 098 109 110 113 114 157 158 161 162 173 174 177 178
// 133 134 135 136 137 138 139 140 141 142 143 144 145 146 147 148     095 096 099 100 111 112 115 116 159 160 163 164 175 176 179 180
// 149 150 151 152 153 154 155 156 157 158 159 160 161 162 163 164     117 118 121 122 133 134 137 138 181 182 185 186 197 198 201 202
// 165 166 167 168 169 170 171 172 173 174 175 176 177 178 179 180     119 120 123 124 135 136 139 140 183 184 187 188 199 200 203 204
// 181 182 183 184 185 186 187 188 189 190 191 192 193 194 195 196     125 126 129 130 141 142 145 146 189 190 193 194 205 206 209 210
// 197 198 199 200 201 202 203 204 205 206 207 208 209 210 211 212     127 128 131 132 143 144 147 148 191 192 195 196 207 208 211 212
// 213 214 215 216 217 218 219 220 221 222 223 224 225 226 227 228     213 214 217 218 229 230 233 234 277 278 281 282 293 294 297 298
// 229 230 231 232 233 234 235 236 237 238 239 240 241 242 243 244     215 216 219 220 231 232 235 236 279 280 283 284 295 296 299 300
// 245 246 247 248 249 250 251 252 253 254 255 256 257 258 259 260     221 222 225 226 237 238 241 242 285 286 289 290 301 302 305 306
// 261 262 263 264 265 266 267 268 269 270 271 272 273 274 275 276     223 224 227 228 239 240 243 244 287 288 291 292 303 304 307 308
// 277 278 279 280 281 282 283 284 285 286 287 288 289 290 291 292     245 246 249 250 261 262 265 266 309 310 313 314 325 326 329 330
// 293 294 295 296 297 298 299 300 301 302 303 304 305 306 307 308     247 248 251 252 263 264 267 268 311 312 315 316 327 328 331 332
// 309 310 311 312 313 314 315 316 317 318 319 320 321 322 323 324     253 254 257 258 269 270 273 274 317 318 321 322 333 334 337 338
// 325 326 327 328 329 330 331 332 333 334 335 336 337 338 339 340     255 256 259 260 271 272 275 276 319 320 323 324 335 336 339 340
// 
// ** Size calculations
//
// level_size(level) = 2^level                        // size of each coordinate i,j in level "level"
// level_nnodes(level) = (2^level)*(2^level)
// branch_nnodes(depth) = ((4^depth)-1)/3
// tree_nnodes(depth) = branches*branch_nnodes(depth) // total nodes in a tree with "depth" levels
//
// ** Indexing calculations (flipped indices) (inside a branch)
//
// father(findex) = floor((findex-1)/4)
// children(findex) = 4*findex+i, i = 1..4
// level(findex) = floor(log4(3*findex+1))      // precision problems, calcutated iteratively in the code
//
// ** Calculating coordinates (matricial indices) (inside a branch)
// 
// size = level_size(level)
// nnodes = tree_nnodes(level)
// lindex = mindex - nnodes    // local matricial index of the node inside its level in the quadtree
// j = lindex / size           // local j (from 0 to size-1) in level "level" for global matricial index "mindex"
// i = lindex % size           // local i (from 0 to size-1) in level "level" for global matricial index "mindex"
// 
// ** Calculating children (matricial indices) (inside a branch)
//
// size = level_size(level+1)
// first = tree_nnodes(level+1)
// Child_NW = first + 2*(j*size + i)
// Child_NE = first + 2*(j*size + i) + 1
// Child_SW = first + 2*(j*size + i) + size
// Child_SE = first + 2*(j*size + i) + 1 + size

#define QUADTREE_NW 1
#define QUADTREE_NE 2
#define QUADTREE_SW 3
#define QUADTREE_SE 4

class TERRAINAPI TrnQuadtreeIndexMap : public TrnBaseClass
{
public:
  
  // Class Name

  static const char* CLASSNAME () {return "TrnQuadtreeIndexMap";}
  virtual const char* ClassName () const {return CLASSNAME();}

  // Constructor and Destructor

  TrnQuadtreeIndexMap ()
  : m_matrix_to_flipped(0)
  , m_flipped_to_matrix(0)
  , m_maxnodes(0)
  , m_firstleaf(0)
  , m_maxdepth(0)
  {
  }

  ~TrnQuadtreeIndexMap ()
  {
    CleanUp();
  }

  inline bool Init (int maxdepth)
  {
    assert(maxdepth > 0 && maxdepth <= QUADTREE_MAX_LEVELS);
    if (maxdepth == m_maxdepth)
      return true;
    CleanUp();
    m_maxdepth = maxdepth;
    m_maxnodes = GetNumNodes(m_maxdepth);
    m_firstleaf = (m_maxnodes - 1) / 4;
    try
    {
      m_matrix_to_flipped = new q_index[m_maxnodes];
      m_flipped_to_matrix = new q_index[m_maxnodes];
      BuildIndices();
    }
    catch (...)
    {
      return false;
    }
    return true;
  }

  inline void CleanUp ()
  {
    if (m_matrix_to_flipped)
    {
      delete[] m_matrix_to_flipped;
      m_matrix_to_flipped = 0;
    }
    if (m_flipped_to_matrix)
    {
      delete[] m_flipped_to_matrix;
      m_flipped_to_matrix = 0;
    }
  }

  // Inline Methods

  inline q_index ToFlippedIndex (q_index mindex) const
  {
    return m_matrix_to_flipped[mindex];
  }

  inline q_index ToMatrixIndex (q_index findex) const
  {
    return m_flipped_to_matrix[findex];
  }

  inline int GetMaxDepth () const
  {
    return m_maxdepth;
  }

private:

  // Private Methods

  inline bool IsNotLeaf (q_index i) const
  {
    return (i < m_firstleaf);
  }

  inline int GetLevelSize (int level) const
  {
    return (1 << level);
  }

  inline q_index GetNumNodes (int depth) const
  {
    return ( ((q_index)1) << (2*depth) ) / 3;
  }

  inline q_index FirstChild (q_index findex) const
  {
    if (IsNotLeaf(findex))
    {
      return (findex << 2);
    }
    else
      return -1;
  }

  void BuildIndices (q_index mindex = 0, q_index findex = 0, int level = 0);
  void PrintIndices () const;

private:

  q_index* m_matrix_to_flipped;
  q_index* m_flipped_to_matrix;
  q_index  m_maxnodes;
  q_index  m_firstleaf;
  int      m_maxdepth;

private:
  TrnQuadtreeIndexMap (const TrnQuadtreeIndexMap&);                // Do not allow copy
  TrnQuadtreeIndexMap& operator= (const TrnQuadtreeIndexMap&);     // Do not allow assignment
};

template <class TYPE>
class TERRAINAPI TrnQuadtreeLinearMulti : public TrnBaseClass
{
public:

  // Class Name

  static const char* CLASSNAME () {return "TrnQuadtreeLinearMulti";}
  virtual const char* ClassName () const {return CLASSNAME();}

  // Constructor and Destructor

  TrnQuadtreeLinearMulti ()
  : m_depth(0)
  , m_nbranches(0)
  , m_ishorizontal(true)
  , m_tree_size(0)
  , m_branch_size(0)
  , m_first_branch_leaf(0)
  , m_nodes(0)
  , m_indexmap(0)
  {
  }

  ~TrnQuadtreeLinearMulti ()
  {
    CleanUp();
  }

  inline bool Init (TrnQuadtreeIndexMap* indexmap, int depth, int nbranches = 1, bool horizontal = true)
  {
    assert(indexmap && depth <= indexmap->GetMaxDepth());
    assert(depth > 0 && depth <= QUADTREE_MAX_LEVELS && nbranches > 0);
    assert(pow(4.0,(double)depth)-1.0 < 3.0*(double)QUADTREE_MAX_NODES/nbranches);
    CleanUp();
    m_indexmap = indexmap;
    m_depth = depth;
    m_nbranches = nbranches;
    m_ishorizontal = horizontal;
    m_branch_size = GetBranchNumNodes(m_depth);
    m_tree_size = m_nbranches * m_branch_size;
    m_first_branch_leaf = (m_branch_size - 1) / 4;
    try
    {
      m_nodes = new AtomicPointer<TYPE>[m_tree_size];
    }
    catch (...)
    {
      return false;
    }
    return true;
  }

  inline void CleanUp ()
  {
    if (m_nodes)
    {
      delete[] m_nodes;
      m_nodes = 0;
    }
  }

  // Inline Methods

  inline int GetTreeDepth () const
  {
    return m_depth;
  }

  inline int GetBranchDepth () const
  {
    return m_depth;
  }

  inline int GetTreeNumBranches () const
  {
    return m_nbranches;
  }

  inline bool IsHorizontalBranching () const
  {
    return m_ishorizontal;
  }

  inline bool IsVerticalBranching () const
  {
    return !m_ishorizontal;
  }

  inline q_index GetBranchSize () const
  {
    return m_branch_size;
  }

  inline q_index GetTreeSize () const
  {
    return m_tree_size;
  }

  inline bool IsValidInBranch (q_index i) const
  {
    return (i >= 0 && i < m_branch_size);
  }

  inline bool IsValidInTree (q_index i) const
  {
    return (i >= 0 && i < m_tree_size);
  }

  inline bool IsBranchLeaf (q_index i) const
  {
    return (i >= m_first_branch_leaf);
  }

  inline bool IsTreeLeaf (q_index i) const
  {
    return IsBranchLeaf(GetBranchIndex(i));
  }

  inline bool IsNotBranchLeaf (q_index i) const
  {
    return (i < m_first_branch_leaf);
  }

  inline bool IsNotTreeLeaf (q_index i) const
  {
    return IsNotBranchLeaf(GetBranchIndex(i));
  }

  inline q_index GetBranchRoot (int branch = 0) const
  {
    return (branch*m_branch_size);
  }

  inline q_index GetParent (q_index findex) const
  {
    q_index bindex = GetBranchIndex(findex);
    if (bindex > 0)
    {
      q_index bparent = (bindex-1) >> 2;
      return findex - (bindex - bparent);
    }
    else
      return -1;
  }

  inline int GetBranch (q_index i) const
  {
    return (i/m_branch_size);
  }

  inline q_index GetBranchIndex (q_index i) const
  {
    return GetBranchIndex(i, GetBranch(i));
  }

  inline q_index GetBranchIndex (q_index i, int branch) const
  {
    return (i-GetBranchRoot(branch));
  }

  inline q_index GetTreeIndex (q_index i, int branch) const
  {
    return (i+GetBranchRoot(branch));
  }

  inline int GetLevelAtBranch (q_index i) const
  { 
    int l = 0;
    q_index tmp = i-1;
    while ( tmp >= 0 )
    {
      tmp = (tmp >> 2 ) - 1;
      ++l;
    }
    return l;
  }

  inline int GetLevelAtTree (q_index i) const
  { 
    return GetLevelAtBranch(GetBranchIndex(i));
  }

  inline int GetBranchLevelSize (int level) const
  {
    return (1 << level);
  }

  inline int GetTreeLevelSize (int level) const
  {
    return (1 << level);
  }

  inline q_index GetBranchNumNodes (int depth) const
  {
    return ( ((q_index)1) << (2*depth) ) / 3;
  }

  inline q_index GetTreeNumNodes (int depth) const
  {
    return m_nbranches * GetBranchNumNodes(depth);
  }

  inline q_index GetBranchFirstLeaf (int branch = 0) const
  {
    return GetTreeIndex(m_first_branch_leaf, branch);
  }

  inline q_index FirstChild (q_index findex) const
  {
    q_index bindex = GetBranchIndex(findex);
    if (IsNotBranchLeaf(bindex))
    {
      q_index bchild = (bindex << 2);
      return findex + (bchild - bindex);
    }
    else
      return -1;
  }

  inline q_index Child_NW (q_index findex) const
  {
    q_index bindex = GetBranchIndex(findex);
    if (IsNotBranchLeaf(bindex))
    {
      q_index bchild = (bindex << 2) + QUADTREE_NW;
      return findex + (bchild - bindex);
    }
    else
      return -1;
  }

  inline q_index Child_NE (q_index findex) const
  {
    q_index bindex = GetBranchIndex(findex);
    if (IsNotBranchLeaf(bindex))
    {
      q_index bchild = (bindex << 2) + QUADTREE_NE;
      return findex + (bchild - bindex);
    }
    else
      return -1;
  }

  inline q_index Child_SW (q_index findex) const
  {
    q_index bindex = GetBranchIndex(findex);
    if (IsNotBranchLeaf(bindex))
    {
      q_index bchild = (bindex << 2) + QUADTREE_SW;
      return findex + (bchild - bindex);
    }
    else
      return -1;
  }

  inline q_index Child_SE (q_index findex) const
  {
    q_index bindex = GetBranchIndex(findex);
    if (IsNotBranchLeaf(bindex))
    {
      q_index bchild = (bindex << 2) + QUADTREE_SE;
      return findex + (bchild - bindex);
    }
    else
      return -1;
  }

  inline void GetMatrixPos (q_index findex, int* i, int* j, int* matrixSize)
  {
    assert(i);
    assert(j);
    assert(matrixSize);
    q_index bindex = GetBranchIndex(findex);
    int level = GetLevelAtBranch(bindex);
    // Getting Matrix Childs
    // Calculating coordinates
    q_index mindex = m_indexmap->ToMatrixIndex(bindex);
    q_index nnodes = GetBranchNumNodes(level);
    int size = GetBranchLevelSize(level);
    *i = (mindex - nnodes)%size;
    *j = (mindex - nnodes)/size;
    *matrixSize = size;
  }

  inline q_index GetTileIndex (int imatrix, int jmatrix, int level, int branch = 0)
  {
    q_index mindex = GetBranchNumNodes(level) + jmatrix * GetBranchLevelSize(level) + imatrix;
    return (branch * GetBranchSize() + m_indexmap->ToFlippedIndex(mindex));
  }

  inline void SetData (q_index findex, TYPE* data)
  {
    m_nodes[findex].Set(data);
  }

  inline TYPE* GetData (q_index findex) const
  {
    return m_nodes[findex].Get();
  }

  void GetNeighbors (q_index findex, q_index *north, q_index *east, q_index *south, q_index *west) const;

private:

  int m_depth;
  int m_nbranches;     // Tree branches extending the terrain
  bool m_ishorizontal; // True if branches extend the terrain west->east, false if north->south

  q_index m_tree_size;
  q_index m_branch_size;
  q_index m_first_branch_leaf;

  AtomicPointer<TYPE>* m_nodes;
  TrnQuadtreeIndexMap* m_indexmap;

private:
  TrnQuadtreeLinearMulti (const TrnQuadtreeLinearMulti&);                // Do not allow copy
  TrnQuadtreeLinearMulti& operator= (const TrnQuadtreeLinearMulti&);     // Do not allow assignment
};

//-------------------------------------------------//
//         Template Methods Implementation         //
//-------------------------------------------------//

template <class TYPE>
void TrnQuadtreeLinearMulti<TYPE>::GetNeighbors (q_index findex, q_index *north, q_index *east, q_index *south, q_index *west) const
{
  int branch = GetBranch(findex);
  int bindex = GetBranchIndex(findex, branch);
  int level = GetLevelAtBranch(bindex);

  q_index mindex = m_indexmap->ToMatrixIndex(bindex);
  q_index num_nodes = GetBranchNumNodes(level);
  int size = GetBranchLevelSize(level);
  int lindex = mindex - num_nodes;
  int j = lindex/size;
  int i = lindex%size;

  if (north)
  {
    if (j <= 0)
    {
      if (IsHorizontalBranching() || branch <= 0)
        *north = -1;
      else
      {
        q_index t = mindex + size * (size-1);
        q_index f = m_indexmap->ToFlippedIndex(t);
        *north = findex + (f - bindex) - m_branch_size;
      }
    }
    else
    {
      q_index t = mindex - size;
      q_index f = m_indexmap->ToFlippedIndex(t);
      *north = findex + (f - bindex);
    }
  }

  if (east)
  {
    if (i >= (size-1))
    {
      if (IsVerticalBranching() || branch >= GetTreeNumBranches()-1)
        *east = -1;
      else
      {
        q_index t = mindex - (size-1);
        q_index f = m_indexmap->ToFlippedIndex(t);
        *east = findex + (f - bindex) + m_branch_size;
      }
    }
    else
    {
      q_index t = mindex + 1;
      q_index f = m_indexmap->ToFlippedIndex(t);
      *east = findex + (f - bindex);
    }
  }

  if (south)
  {
    if (j >= (size-1))
    {
      if (IsHorizontalBranching() || branch >= GetTreeNumBranches()-1)
        *south = -1;
      else
      {
        q_index t = mindex - size * (size-1);
        q_index f = m_indexmap->ToFlippedIndex(t);
        *south = findex + (f - bindex) + m_branch_size;
      }
    }
    else
    {
      q_index t = mindex + size;
      q_index f = m_indexmap->ToFlippedIndex(t);
      *south = findex + (f - bindex);
    }
  }

  if (west)
  {
    if (i <= 0)
    {
      if (IsVerticalBranching() || branch <= 0)
        *west = -1;
      else
      {
        q_index t = mindex + (size-1);
        q_index f = m_indexmap->ToFlippedIndex(t);
        *west = findex + (f - bindex) - m_branch_size;
      }
    }
    else
    {
      q_index t = mindex - 1;
      q_index f = m_indexmap->ToFlippedIndex(t);
      *west = findex + (f - bindex);
    }
  }
}

#endif // TERRAIN_QUADTREE_LINEAR_MULTI_H
