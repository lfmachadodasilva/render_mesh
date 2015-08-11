#ifndef TRN_TILEMANAGER_H
#define TRN_TILEMANAGER_H

//-----------------------------------//
// Includes and Forward Declarations //
//-----------------------------------//

#include "workerservice.h"

#include <mthread/atomicint32.h>
#include <ds/mtqueue.h>
#include <ds/mthash.h>
#include <ds/heap.h>

class TrnPredictor;
class TrnViewSpecifier;
class UGLArray;
class UGLIndices;
class UGLTexture;

//---------------------------------//
// TrnTileStampInfoCompare Functor //
//---------------------------------//

class TrnTileStampInfoCompare
{
public:
  DS_FORCE_INLINE int operator() (const TrnTileStampInfo& tile1, const TrnTileStampInfo& tile2) const
  {
    int i1 = tile1.usedFrame - 100*tile1.level;
    int i2 = tile2.usedFrame - 100*tile2.level;
    if (i1 < i2)
      return -1;
    else if (i1 > i2)
      return 1;
    else
      return 0;
  }
};

//----------------------//
// TrnTileManager Class //
//----------------------//

class TERRAINAPI TrnTileManager : public TrnWorkerService
{
public:

  // Class Name

  static const char* CLASSNAME () {return "TrnTileManager";}
  virtual const char* ClassName () const {return CLASSNAME();}

  // Constructor and Destructor

  TrnTileManager ();
  virtual ~TrnTileManager ();

  void Reset ();

  // Configuration

  void SetMaxTilesTex (long maxTilesTex);
  void SetMaxTilesHgt (long maxTilesHgt);

  void SetViewSpecifier (TrnViewSpecifier* viewSpecifier);
  void SetPredictor (TrnPredictor* predictor);

  // Special Getters

  q_index GetNumLoadedTex ();
  q_index GetNumLoadedHgt ();
  q_index GetMaxTilesTex ();
  q_index GetMaxTilesHgt ();
  q_index GetNumTexToLoad ();
  q_index GetNumHgtToLoad ();
  q_index GetNumTexToUnload ();
  q_index GetNumHgtToUnload ();

  void GetStatistics (long* texBytes, long* hgtBytes);

  // Tile Management

  TrnTileTexture* LoadAndGetTexTile (TrnTerrain* terrain, q_index tile_index);
  TrnTileHeight* LoadAndGetHgtTile (TrnTerrain* terrain, q_index tile_index);

  void RequestLoadTex (TrnTerrain* terrain, q_index tile_index);
  void RequestLoadHgt (TrnTerrain* terrain, q_index tile_index);
  bool EnqueueLoadTex (TrnTerrain* terrain, q_index tile_index);
  bool EnqueueLoadHgt (TrnTerrain* terrain, q_index tile_index);

  // Feedback Data Structure Access

  DsMTQueue<TrnTileStampInfo>* GetRecentlyLoadedTexQueue();
  DsMTQueue<TrnTileStampInfo>* GetRecentlyLoadedHgtQueue();
  void ForgetRecent (long curFrame);

  // Object Destruction

  void EnqueueToDestroy (UGLTexture* utex);
  void EnqueueToDestroy (UGLArray* uarray);
  void EnqueueToDestroy (UGLIndices* uind);

  void DestroyQueuedObjects (); // Must be called in the render thread

protected:

  // Configuration

  virtual void ApplyConfig ();

  // Internal Getters

  TrnViewSpecifier* GetCurViewSpecifier ();
  TrnPredictor* GetCurPredictor ();

  // Requests

  void RequestPredict ();
  void RequestLoad ();

  // Tile Management

  bool AddTex (TrnTileLoadInfo tinfo);
  bool AddHgt (TrnTileLoadInfo tinfo);

  bool RemoveTex ();
  bool RemoveHgt ();

  // Thread Control

  void SignalLoaded ();

private:

  // Service Main (Loop) Function

  void DoService ();

private:

  long m_cfgMaxTilesTex; // Maximum number of texture tiles that may be in memory at any given time (protected by config section)
  long m_cfgMaxTilesHgt; // Maximum number of height tiles that may be in memory at any given time (protected by config section)

  long m_curMaxTilesTex; // Maximum number of texture tiles that may be in memory at any given time (single thread)
  long m_curMaxTilesHgt; // Maximum number of height tiles that may be in memory at any given time (single thread)

  TrnViewSpecifier*  m_cfgViewSpecifier; // View specifier for current frame query (protected by config section)
  TrnPredictor*      m_cfgPredictor;     // View predictor to notify about loaded tiles (protected by config section)

  TrnViewSpecifier*  m_curViewSpecifier; // View specifier for current frame query (single thread)
  TrnPredictor*      m_curPredictor;     // View predictor to notify about loaded tiles (single thread)

  AtomicInt32 m_curFrame; // Frame that the current execution is based on (atomic)

  TrnTileStampInfoCompare m_cmpfunctor;
  DsHeap<TrnTileStampInfo, TrnTileStampInfoCompare>* m_tex_heapPriority; // Priority queue to decide when to unload tiles
  DsHeap<TrnTileStampInfo, TrnTileStampInfoCompare>* m_hgt_heapPriority; // Priority queue to decide when to unload tiles

  DsMTQueue<TrnTileLoadInfo>* m_tex_queueLoad;      // Queue for tiles waiting to be loaded
  DsMTQueue<TrnTileLoadInfo>* m_hgt_queueLoad;      // Queue for tiles waiting to be loaded
  DsMTHash<TrnTileLoadInfo, bool>* m_tex_tableLoad; // Table for tiles waiting to be loaded
  DsMTHash<TrnTileLoadInfo, bool>* m_hgt_tableLoad; // Table for tiles waiting to be loaded

  DsMTQueue<TrnTileUnloadInfo>* m_tex_queueUnload; // Queue for tiles waiting to be unloaded
  DsMTQueue<TrnTileUnloadInfo>* m_hgt_queueUnload; // Queue for tiles waiting to be unloaded

  DsMTQueue<TrnTileStampInfo>* m_tex_recentlyLoaded; // Queue of recently loaded tiles
  DsMTQueue<TrnTileStampInfo>* m_hgt_recentlyLoaded; // Queue of recently loaded tiles

  DsMTQueue<UGLArray*>*   m_todestroy_array; // Queue for vertex arrays waiting to be destroyed in the render thread
  DsMTQueue<UGLIndices*>* m_todestroy_index; // Queue for index arrays waiting to be destroyed in the render thread
  DsMTQueue<UGLTexture*>* m_todestroy_tex;   // Queue for textures waiting to be destroyed in the render thread

  long m_texBytes; // Internal counter (single thread)
  long m_hgtBytes; // Internal counter (single thread)

  long m_statTexBytes; // Statistics (protected by stats section)
  long m_statHgtBytes; // Statistics (protected by stats section)

  MtlCritSection m_cs_stats;
  MtlCritSection m_cs_loaded;
  MtlCondVar m_condition_loaded;
  bool m_abortwait;

};

#endif // TRN_TILEMANAGER_H
