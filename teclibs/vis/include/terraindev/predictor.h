#ifndef TRN_PREDICTOR_H
#define TRN_PREDICTOR_H

//-----------------------------------//
// Includes and Forward Declarations //
//-----------------------------------//

#include "workerservice.h"
#include "viewparameters.h"
#include "typedefs.h"

#include <ds/mtarray.h>
#include <mthread/atomicint32.h>

class TrnTileManager;
class TrnViewSpecifier;
class TrnTerrain;
class TrnTerrainGroup;
class TrnTilerHeight;
class TrnTilerTexture;

//------------------//
// Class Definition //
//------------------//

class TERRAINAPI TrnPredictor : public TrnWorkerService, public TrnViewListener
{
public:

  // Class Name

  static const char* CLASSNAME () {return "TrnPredictor";}
  virtual const char* ClassName () const {return CLASSNAME();}

  // Constructor and Destructor

  TrnPredictor ();
  virtual ~TrnPredictor ();

  void Reset ();

  // Configuration

  void SetViewSpecifier (TrnViewSpecifier* viewSpecifier);
  void SetTileManager (TrnTileManager* tileManager);

  void SetTerrainGroup (TrnTerrainGroup* group);

  // Special Getters

  void GetViews (TrnViewParameters* curView, TrnViewParameters* prdView);
  void GetStatistics (long* texRequired, long* hgtRequired, long* texEnqueued, long* hgtEnqueued);
  long GetCurrentFrame ();

  // View Methods

  void HandleViewChanged ();

protected:

  // Configuration

  virtual void ApplyConfig ();

  // Internal Getters

  TrnTerrainGroup* GetCurTerrainGroup ();
  TrnViewSpecifier* GetCurViewSpecifier ();
  TrnTileManager* GetCurTileManager ();

  // View Methods

  bool UpdateView ();

  AlgQuatern GetQuatern (const TrnViewParameters& view);
  void UpdatePrediction (float vlen, const AlgVector velocity, float deltatimePos, float wVelocityAngle, const AlgVector wVelocityAxis, float deltatimeOri);

  // Requests

  void RequestPredict ();
  void RequestLoad ();

private:

  // Traversal

  void TraverseGroup (TrnTerrainGroup* group);
  void TraverseTerrain (TrnTerrain* terrain);

  void Traverse ();
  void TraverseTex (q_index n);
  void TraverseHgt (q_index n);
  bool SplitTex (q_index n);
  bool SplitHgt (q_index n);

  // Service Main (Loop) Function

  virtual void DoService ();

private:

  TrnTerrain* m_curTerrain;             // Currently Traversed
  TrnTilerHeight* m_curHgtTiler;        // Currently Traversed
  TrnTilerTexture* m_curTexTiler;       // Currently Traversed
  TrnQuadtreeHeight* m_curHgtQuadtree;  // Currently Traversed
  TrnQuadtreeTexture* m_curTexQuadtree; // Currently Traversed

  TrnTerrainGroup*   m_cfgGroup;
  TrnViewSpecifier*  m_cfgViewSpecifier; // View specifier (protected by config section)
  TrnTileManager*    m_cfgTileManager;   // Tile manager for load queuing (protected by config section)

  TrnTerrainGroup*   m_curGroup;
  TrnViewSpecifier*  m_curViewSpecifier; // View specifier (single thread)
  TrnTileManager*    m_curTileManager;   // Tile manager for load queuing (single thread)

  TrnViewParameters* m_prvViews; // Array of previous views (protected by view section)
  TrnViewParameters  m_curView;  // Current view (protected by view section)
  TrnViewParameters  m_prdView;  // Predicted view (protected by view section)

  int m_prvViewCount;  // Number of previous views remembered (protected by view section)
  int m_prvViewOldest; // Index of the oldest previous view remembered (protected by view section)
  int m_prvViewNewest; // Index of the newest previous view remembered (protected by view section)

  AtomicInt32 m_curFrame; // Frame that the current execution is based on (atomic)
  double      m_curTime;  // Used for prediction based on DeltaT (single thread)
  double*     m_prvTimes; // Used for prediction based on DeltaT (single thread)

  long m_texRequired; // Internal counter (single thread)
  long m_hgtRequired; // Internal counter (single thread)
  long m_texEnqueued; // Internal counter (single thread)
  long m_hgtEnqueued; // Internal counter (single thread)

  long m_lastTexRequired; // Statistics (protected by stats section)
  long m_lastHgtRequired; // Statistics (protected by stats section)
  long m_lastTexEnqueued; // Statistics (protected by stats section)
  long m_lastHgtEnqueued; // Statistics (protected by stats section)

  MtlCritSection m_cs_stats;
  MtlCritSection m_cs_views;

  bool m_viewFirst;   // Flags the case when there is no previous view (single thread)
  bool m_needLoad;    // Flags when a new tile manager run must be done (single thread)
  bool m_needPredict; // Flags when a new prediction must be done after the current one (single thread)

};

#endif // TRN_PREDICTOR_H
