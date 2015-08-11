#ifndef TRN_RENDERER_H
#define TRN_RENDERER_H

//-----------------------------------//
// Includes and Forward Declarations //
//-----------------------------------//

#include "baseclass.h"
#include "typedefs.h"
#include "viewparameters.h"

#include <mthread/atomicint32.h>

class TrnTerrain;
class TrnTerrainGroup;
class TrnTilerHeight;
class TrnTilerTexture;
class TrnPredictor;
class TrnTileManager;
class TrnViewSpecifier;
class UFontManager;

//-------------------//
// TrnRenderer Class //
//-------------------//

class TERRAINAPI TrnRenderer : public TrnBaseClass
{
public:

  // Typedefs

  typedef void (*TrnRedrawCallback) (void* data);

public:

  // Class Name

  static const char* CLASSNAME () {return "TrnRenderer";}
  virtual const char* ClassName () const {return CLASSNAME();}

  // Constructor and Destructor

  TrnRenderer ();
  virtual ~TrnRenderer ();

  // Object Links

  void SetTerrainGroup (TrnTerrainGroup* terrainGroup);
  void SetViewSpecifier (TrnViewSpecifier* viewSpecifier);
  void SetPredictor (TrnPredictor* predictor);
  void SetTileManager (TrnTileManager* tileManager);

  // Configuration

  void SetUpdateView (bool state);
  void SetWireframe (bool state);
  void SetShowBBoxes (bool state);
  void SetShowViews (bool state);
  void SetShowStats (bool state);
  void SetOpacity (float opacity);
  void SetFogDensity (float density);
  void SetFogColor (float r, float g, float b, float a);
  void SetErrorTolerance (float pixels);

  bool GetUpdateView () const;
  bool GetWireframe () const;
  bool GetShowBBoxes () const;
  bool GetShowViews () const;
  bool GetShowStats () const;
  float GetOpacity () const;
  float GetFogDensity () const;
  void GetFogColor (float* r, float* g, float* b, float* a) const;
  float GetErrorTolerance () const;

  // Special Getters

  long GetCurrentFrame ();

  // Redraw Callback

  void SetRedrawCallback (TrnRedrawCallback cb, void* data);
  void RequestRedraw ();

  // Visibility

  bool IsVisible (TrnTerrainInfo& info, const TrnViewParameters& view);

  // Render

  void Render ();
  void RenderDebug ();

protected:

  // Update

  void UpdateView ();

  // Render

  void RenderBegin();
  void RenderEnd();

  void RenderGroup (TrnTerrainGroup* group);
  void RenderTerrain (TrnTerrain* terrain);

  void CollectTiles ();
  void RenderSurface ();
  void RenderBorder ();
  void RenderBBoxes ();
  void RenderRecent ();
  void RenderViews ();
  void RenderStats ();

  // Traversal

  void Traverse ();
  void TraverseTex (q_index n);
  void TraverseHgt (q_index n);
  bool SplitTex (q_index n);
  bool SplitHgt (q_index n);

  // Traversal (with budget limit)

  // (...)

  // Traversal (with occlusion culling)

  // (...)

private:

  // Internal Objects

  UFontManager* m_fontManager;

  // Linked Objects

  TrnViewSpecifier* m_viewSpecifier;
  TrnPredictor* m_predictor;
  TrnTileManager* m_tileManager;
  TrnTerrainGroup* m_terrainGroup;

  // Currently Rendered Objects

  TrnTerrain* m_curTerrain;
  TrnTilerHeight* m_curHgtTiler;
  TrnTilerTexture* m_curTexTiler;
  TrnQuadtreeHeight* m_curHgtQuadtree;
  TrnQuadtreeTexture* m_curTexQuadtree;

  // Configuration

  bool m_updateView;
  bool m_wireframe;
  bool m_showBBoxes;
  bool m_showViews;
  bool m_showStats;
  float m_opacity;
  float m_fogDensity;
  float m_fogColor[4];
  float m_errorTolerance;

  // Redraw Callback

  TrnRedrawCallback m_cbRedrawFunc;
  void* m_cbRedrawData;

  // Internal Counters

  long m_texRequired;
  long m_hgtRequired;
  long m_texDrawn;
  long m_hgtDrawn;
  long m_texTotal;
  long m_hgtTotal;

  // General information

  TrnViewParameters m_curView;
  AtomicInt32 m_curFrame;
  TrnTilePairArray m_drawCollection;
};

#include "renderer.inl"

#endif // TRN_RENDERER_H
