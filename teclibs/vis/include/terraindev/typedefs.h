#ifndef TERRAIN_TYPEDEFS_H
#define TERRAIN_TYPEDEFS_H

// Includes

#include "defines.h"
#include <ds/list.h>
#include <ds/stack.h>
#include <ds/heap.h>
#include <ds/hash.h>

#include <float.h>

// Forward Declarations

class TrnTile;
class TrnTileHeight;
class TrnTileTexture;
class TrnTerrain;

template <class TYPE>
class TrnQuadtreeLinearMulti;

template <class TYPE>
class TrnLinearBinaryTree;

// Structure Type Definitions

struct TrnTerrainInfo
{
  TrnTerrainInfo ()
  : terrain(NULL)
  , hmin(0.0f)
  , hoffset(0.0f)
  , xmin(FLT_MAX)
  , ymin(FLT_MAX)
  , zmin(FLT_MAX)
  , xmax(-FLT_MAX)
  , ymax(-FLT_MAX)
  , zmax(-FLT_MAX)
  , xctr(0.0f)
  , yctr(0.0f)
  , zctr(0.0f)
  , needUpdateBBox(false)
  {
  }

  TrnTerrain* terrain;
  float hmin;
  float hoffset;
  float xmin, ymin, zmin;
  float xmax, ymax, zmax;
  float xctr, yctr, zctr;
  bool needUpdateBBox;
};

struct TrnTilePair {
  TrnTileHeight* hgttile;
  TrnTileTexture* textile;
  q_index hgtindex;
  q_index texindex;
};

struct TrnTileLoadInfo {
  TrnTerrain* terrain;
  q_index tindex;
  operator int () const
  {
    return int(q_index(intptr_t(terrain)) + tindex);
  }
};

struct TrnTileUnloadInfo {
  TrnTerrain* terrain;
  q_index tindex;
  TrnTile* tile;
  long insertedFrame;
};

struct TrnTileStampInfo {
  TrnTerrain* terrain;
  q_index tindex;
  int level;
  long usedFrame;
};

struct TrnTileErrorInfo {
  TrnTerrain* terrain;
  q_index tindex;
  float error;
};

// Functor Definitions

class TrnTileErrorInfoCompare
{
public:
  DS_FORCE_INLINE int operator() (const TrnTileErrorInfo& tile1, const TrnTileErrorInfo& tile2) const
  {
    float difference = tile1.error - tile2.error;
    if (difference < -1.0E-5)
      return 1;
    else if (difference > 1.0E-5)
      return -1;
    else
      return 0;
  }
};

// Data Structure Type Definitions

typedef DsArray<TrnTilePair> TrnTilePairArray;
typedef DsHeap<TrnTileErrorInfo, TrnTileErrorInfoCompare> TrnTileHeap;
typedef TrnQuadtreeLinearMulti<TrnTileHeight> TrnQuadtreeHeight;
typedef TrnQuadtreeLinearMulti<TrnTileTexture> TrnQuadtreeTexture;
typedef DsList<q_index> TrnQIndexList;
typedef DsStack<q_index> TrnQIndexStack;

typedef TrnLinearBinaryTree<TrnTerrainInfo> TrnBinaryTreeTerrain;

#endif // TERRAIN_TYPEDEFS_H
