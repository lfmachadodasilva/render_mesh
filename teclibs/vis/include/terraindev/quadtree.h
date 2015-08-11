#ifndef TERRAIN_QUADTREE_LINEAR_H
#define TERRAIN_QUADTREE_LINEAR_H

#include "baseclass.h"
#include "quadtreedefines.h"
#include <math.h>
#include <stdlib.h>
#include <assert.h>

// ** QuadTree structure:
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
// 085 086 087 088 089 090 091 092 093 094 095 096 097 098 099 100
// 101 102 103 104 105 106 107 108 109 110 111 112 113 114 115 116
// 117 118 119 120 121 122 123 124 125 126 127 128 129 130 131 132
// 133 134 135 136 137 138 139 140 141 142 143 144 145 146 147 148
// 149 150 151 152 153 154 155 156 157 158 159 160 161 162 163 164
// 165 166 167 168 169 170 171 172 173 174 175 176 177 178 179 180
// 181 182 183 184 185 186 187 188 189 190 191 192 193 194 195 196
// 197 198 199 200 201 202 203 204 205 206 207 208 209 210 211 212
// 213 214 215 216 217 218 219 220 221 222 223 224 225 226 227 228
// 229 230 231 232 233 234 235 236 237 238 239 240 241 242 243 244
// 245 246 247 248 249 250 251 252 253 254 255 256 257 258 259 260
// 261 262 263 264 265 266 267 268 269 270 271 272 273 274 275 276
// 277 278 279 280 281 282 283 284 285 286 287 288 289 290 291 292
// 293 294 295 296 297 298 299 300 301 302 303 304 305 306 307 308
// 309 310 311 312 313 314 315 316 317 318 319 320 321 322 323 324
// 325 326 327 328 329 330 331 332 333 334 335 336 337 338 339 340
// 
// ** Size calculations
//
// level_size(level) = 2^level                  // size of each coordinate i,j in level "level"
// level_nnodes(level) = (2^level)*(2^level)    // total nodes in a tree with "level" levels
// tree_nnodes(depth) = ((4^level)-1)/3
//
// ** Indexing calculations (flipped indices)
//
// father(findex) = floor((findex-1)/4)
// children(findex) = 4*findex+i, i = 1..4
// level(findex) = floor(log4(3*findex+1))      // precision problems, calcutated iteratively in the code
//
// ** Calculating coordinates (matricial indices)
// 
// size = level_size(level)
// nnodes = tree_nnodes(level)
// lindex = mindex - nnodes    // local matricial index of the node inside its level in the quadtree
// j = lindex / size           // local j (from 0 to size-1) in level "level" for global matricial index "mindex"
// i = lindex % size           // local i (from 0 to size-1) in level "level" for global matricial index "mindex"
// 
// ** Calculating children (matricial indices)
//
// size = level_size(level+1)
// first = tree_nnodes(level+1)
// Child_NW = first + 2*(j*size + i)
// Child_NE = first + 2*(j*size + i) + 1
// Child_SW = first + 2*(j*size + i) + size
// Child_SE = first + 2*(j*size + i) + 1 + size

template <class TYPE>
class TERRAINAPI TrnQuadtreeLinear : public TrnBaseClass
{
public:

  // Class Name

  static const char* CLASSNAME () {return "TrnQuadtreeLinear";}
  virtual const char* ClassName () const {return CLASSNAME();}

  // Constants

  const static char _NW = 1;
  const static char _NE = 2;
  const static char _SW = 3;
  const static char _SE = 4;

  // Constructor and Destructor

  TrnQuadtreeLinear(int depth)
  {
    assert(depth > 0 && depth <= QUADTREE_MAX_LEVELS);
    m_depth = depth;
    m_size = NumNodes(m_depth);
    m_first_leaf = (m_size - 1) / 4;
    m_nodes = new TYPE[m_size];
    memset(m_nodes, 0, m_size * sizeof(TYPE));
    m_matrix_to_flipped = new q_index[m_size];
    m_flipped_to_matrix = new q_index[m_size];
    BuildIndices(0, 0, 0);
  }

  ~TrnQuadtreeLinear()
  {
    delete[] m_nodes;
    delete[] m_matrix_to_flipped;
    delete[] m_flipped_to_matrix;
    m_nodes = NULL;
    m_matrix_to_flipped = NULL;
    m_flipped_to_matrix = NULL;
  }

  // Inline Methods

  inline int Depth() const
  {
    return m_depth;
  }

  inline q_index Size() const
  {
    return m_size;
  }

  inline bool IsValid(q_index i) const
  {
    return (i >= 0 && i < m_size);
  }

  inline bool IsLeaf(q_index i) const
  {
    return (i >= m_first_leaf); // (i >= 0 && i < m_size && i >= m_first_leaf)
  }

  inline bool IsNotLeaf(q_index i) const
  {
    return (i < m_first_leaf); // (i >= 0 && i < m_size && i < m_first_leaf)
  }

  inline q_index Root() const
  {
    return 0;
  }

  inline q_index Parent(q_index findex) const
  {
    return (findex > 0) ? ((findex-1) >> 2) : -1;
  }

  inline int Level(q_index i) const
  { 
    int l = 0;
    q_index tmp = i-1;
    while ( tmp >= 0 )
    {
      tmp = (tmp >> 2 ) - 1;
      l++;
    }
    return l;
  }

  inline q_index FirstChild(q_index findex) const
  {
    return IsNotLeaf(findex) ? (findex << 2) : -1;
  }

  inline q_index Child_NW(q_index findex) const
  {
    return IsNotLeaf(findex) ? ((findex << 2) + _NW) : -1;
  }

  inline q_index Child_NE(q_index findex) const
  {
    return IsNotLeaf(findex) ? ((findex << 2) + _NE) : -1;
  }

  inline q_index Child_SW(q_index findex) const
  {
    return IsNotLeaf(findex) ? ((findex << 2) + _SW) : -1;
  }

  inline q_index Child_SE(q_index findex) const
  {
    return IsNotLeaf(findex) ? ((findex << 2) + _SE) : -1;
  }

  inline void GetMatrixPos(q_index findex, int* i, int* j, int* matrixSize)
  {
    assert(i);
    assert(j);
    assert(matrixSize);
    int level = Level(findex);
    // Getting Matrix Childs
    // Calculating coordinates
    q_index mindex = m_flipped_to_matrix[findex];
    q_index num_nodes = NumNodes(level);
    int size = (1 << level);
    *i = (mindex - num_nodes)%size;
    *j = (mindex - num_nodes)/size;
    *matrixSize = size;
  }

  inline void SetData(q_index findex, TYPE data)
  {
    m_nodes[findex] = data;
  }

  inline TYPE& GetData(q_index findex) const
  {
    return m_nodes[findex];
  }

  void GetNeighbors(q_index findex, q_index *north, q_index *east, q_index *south, q_index *west) const;
  void PrintIndices() const;

private:

  // Private Methods

  inline int LevelSize(int level) const
  {
    return (1 << level);
  }

  inline q_index NumNodes(int depth) const
  {
    return ( ((q_index)1) << (2*depth) ) / 3;
  }

  void BuildIndices(q_index mindex, q_index findex, int level);

protected:

  int m_depth;
  q_index m_size;
  q_index m_first_leaf;

  TYPE* m_nodes;
  q_index* m_matrix_to_flipped;
  q_index* m_flipped_to_matrix;

private:
  TrnQuadtreeLinear (const TrnQuadtreeLinear&);                // Do not allow copy
  TrnQuadtreeLinear& operator= (const TrnQuadtreeLinear&);     // Do not allow assignment
};

//-------------------------------------------------//
//         Template Methods Implementation         //
//-------------------------------------------------//

#include <stdio.h>

template <class TYPE>
void TrnQuadtreeLinear<TYPE>::GetNeighbors(q_index findex, q_index *north, q_index *east, q_index *south, q_index *west) const
{
  int level = Level(findex);

  q_index mindex = m_flipped_to_matrix[findex];
  q_index num_nodes = NumNodes(level);
  int size = LevelSize(level);
  int lindex = mindex - num_nodes;
  int j = lindex/size;
  int i = lindex%size;

  if (north)
  {
    if (j <= 0)
      *north = -1;
    else
    {
      q_index t = mindex - size;
      *north = m_matrix_to_flipped[t];
    }
  }

  if (east)
  {
    if (i >= (size-1))
      *east = -1;
    else
    {
      q_index t = mindex + 1;
      *east = m_matrix_to_flipped[t];
    }
  }

  if (south)
  {
    if (j >= (size-1))
      *south = -1;
    else
    {
      q_index t = mindex + size;
      *south = m_matrix_to_flipped[t];
    }
  }

  if (west)
  {
    if (i <= 0)
      *west = -1;
    else
    {
      q_index t = mindex - 1;
      *west = m_matrix_to_flipped[t];
    }
  }
}

template <class TYPE>
void TrnQuadtreeLinear<TYPE>::BuildIndices(q_index mindex, q_index findex, int level)
{
  m_matrix_to_flipped[mindex] = findex;
  m_flipped_to_matrix[findex] = mindex;

  if (level >= (m_depth-1))
    return;

  // Getting Matrix Children
  // Calculating coordinates
  q_index num_nodes = NumNodes(level);
  int size = LevelSize(level);
  int lindex = mindex - num_nodes;
  int j = lindex/size;
  int i = lindex%size;

  // Calculating children
  int next_level = level+1;
  int next_size = 2*size;
  q_index next_num_nodes = NumNodes(next_level);

  q_index mindex_nw = next_num_nodes + 2*(j*next_size + i);
  q_index mindex_ne = mindex_nw + 1;
  q_index mindex_sw = mindex_nw + next_size;
  q_index mindex_se = mindex_ne + next_size;

  q_index findex_child = FirstChild(findex);

  BuildIndices(mindex_nw, findex_child + _NW, next_level);
  BuildIndices(mindex_ne, findex_child + _NE, next_level);
  BuildIndices(mindex_sw, findex_child + _SW, next_level);
  BuildIndices(mindex_se, findex_child + _SE, next_level);
}

template <class TYPE>
void TrnQuadtreeLinear<TYPE>::PrintIndices() const
{
  int mindex = 0;
  for (int level = 0; level < m_depth; ++level)
  {
    int size = LevelSize(level);
    for (int j = 0; j < size; ++j)
    {
      for (int i = 0; i < size; ++i)
      {
        printf("%d ", m_matrix_to_flipped[mindex]);
        ++mindex;
      }
      printf("\n");
    }
    printf("\n");
  }
}

#endif // TERRAIN_QUADTREE_LINEAR_H
