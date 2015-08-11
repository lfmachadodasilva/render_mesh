//* qterraingroup.h
// vbarata@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Oct 2009

#ifndef TRN_TERRAINGROUP_H
#define TRN_TERRAINGROUP_H

//-----------------------------------//
// Includes and Forward Declarations //
//-----------------------------------//

#include "baseclass.h"
#include "binarytree.h"

#include <ds/hash.h>
#include <alg/vector.h>

#include <float.h>
#include <limits.h>
#include <math.h>

class TrnTerrain;
class TrnRenderer;
class MtlWorkerThread;
class TrnTileManager;
class TrnPredictor;
class TrnViewSpecifier;

//------------------//
// Class Definition //
//------------------//

class TERRAINAPI TrnTerrainGroup : public TrnBaseClass
{
public:

  // Constructor and Destructor

  TrnTerrainGroup ();
  virtual ~TrnTerrainGroup ();

  bool Init (TrnViewSpecifier* viewSpecifier);
  void CleanUp ();

  // Terrain Management

  bool AddTerrain (TrnTerrain* terrain);
  void ClearTerrains (bool destroy = false);

  int GetNumTerrains () const
  {
    return (int)m_terrainTree->GetUsedLeaves();
  }

  TrnTerrain* GetTerrain (int trnIndex) const
  {
    long trnFirst = m_terrainTree->GetFirstLeaf();
    return m_terrainTree->GetDataRef(trnFirst+trnIndex).terrain;
  }

  float GetTerrainExtraOffset (int trnIndex) const
  {
    long trnFirst = m_terrainTree->GetFirstLeaf();
    return m_terrainTree->GetDataRef(trnFirst+trnIndex).hoffset;
  }

  float GetTerrainMinHeight (int trnIndex) const
  {
    long trnFirst = m_terrainTree->GetFirstLeaf();
    return m_terrainTree->GetDataRef(trnFirst+trnIndex).hmin;
  }

  int GetLowestTerrainIndex () const
  {
    return m_lowestTerrain;
  }

  // Internal Object Getters

  TrnBinaryTreeTerrain* GetTerrainTree () const
  {
    return m_terrainTree;
  }

  TrnRenderer* GetRenderer () const
  {
    return m_renderer;
  }

  MtlWorkerThread* GetWorkerThread () const
  {
    return m_workerThread;
  }

  TrnTileManager* GetTileManager () const
  {
    return m_tileManager;
  }

  TrnPredictor* GetPredictor () const
  {
    return m_predictor;
  }

  TrnViewSpecifier* GetViewSpecifier () const
  {
    return m_viewSpecifier;
  }

  // Terrain Queries

  TrnTerrain* GetActualTerrainAtPosition (float x, float z);
  TrnTerrain* GetLoadedTerrainAtPosition (float x, float z);
  TrnTerrain* GetDrawnTerrainAtPosition (float x, float z);

  bool GetActualValidAtPosition (float x, float z);
  bool GetLoadedValidAtPosition (float x, float z);
  bool GetDrawnValidAtPosition (float x, float z);

  float GetActualHeightAtPosition (float x, float z, bool transform = true);
  float GetLoadedHeightAtPosition (float x, float z, bool transform = true);
  float GetDrawnHeightAtPosition (float x, float z, bool transform = true);

  TrnObjectType GetLoadedIntersection (AlgVector rayOrigin, AlgVector rayUnitDirection, AlgVector* intersection);
  bool RayHitsBBox (AlgVector rayOrigin, AlgVector rayUnitDirection, TrnTerrainInfo& info);

  // Bounding Box

  bool IsOutdatedBBox ();

  void SetOutdatedBBox (long trnIndex);
  void SetOutdatedBBox (TrnTerrain* terrain);

  void AssertUpdatedBBox ();
  void AssertUpdatedBBox (long rawIndex);

  void GetBBox (float *xmin, float *ymin, float *zmin, float *xmax, float *ymax, float *zmax)
  {
    AssertUpdatedBBox();
    if (xmin) *xmin = m_xmin;
    if (ymin) *ymin = m_ymin;
    if (zmin) *zmin = m_zmin;
    if (xmax) *xmax = m_xmax;
    if (ymax) *ymax = m_ymax;
    if (zmax) *zmax = m_zmax;
  }

  void GetCenter (float *xctr, float *yctr, float *zctr)
  {
    AssertUpdatedBBox();
    if (xctr) *xctr = m_xctr;
    if (yctr) *yctr = m_yctr;
    if (zctr) *zctr = m_zctr;
  }

  void GetSize (float *xsize, float *ysize, float *zsize)
  {
    AssertUpdatedBBox();
    if (xsize) *xsize = m_xsize;
    if (ysize) *ysize = m_ysize;
    if (zsize) *zsize = m_zsize;
  }

private:

  DsHash<TrnTerrain*, long> m_terrainMap;
  TrnBinaryTreeTerrain* m_terrainTree;
  TrnViewSpecifier* m_viewSpecifier;
  TrnRenderer* m_renderer;
  MtlWorkerThread* m_workerThread;
  TrnTileManager* m_tileManager;
  TrnPredictor* m_predictor;

  int m_lowestTerrain;

  float m_xmin, m_ymin, m_zmin;
  float m_xmax, m_ymax, m_zmax;
  float m_xctr, m_yctr, m_zctr;
  float m_xsize, m_ysize, m_zsize;
  bool m_needUpdateBBox;

  bool m_initialized;

};

#endif // TRN_TERRAINGROUP_H
