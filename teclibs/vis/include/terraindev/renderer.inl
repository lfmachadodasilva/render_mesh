//* renderer.inl
// vbarata@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Apr 2011

//----------//
// Includes //
//----------//

//--------------//
// Object Links //
//--------------//

inline void TrnRenderer::SetTerrainGroup (TrnTerrainGroup* terrainGroup)
{
  if (terrainGroup != m_terrainGroup)
  {
    m_terrainGroup = terrainGroup;
    RequestRedraw();
  }
}

inline void TrnRenderer::SetViewSpecifier (TrnViewSpecifier* viewSpecifier)
{
  if (viewSpecifier != m_viewSpecifier)
  {
    m_viewSpecifier = viewSpecifier;
    RequestRedraw();
  }
}

inline void TrnRenderer::SetPredictor (TrnPredictor* predictor)
{
  if (predictor != m_predictor)
  {
    m_predictor = predictor;
    RequestRedraw();
  }
}

inline void TrnRenderer::SetTileManager (TrnTileManager* tileManager)
{
  if (tileManager != m_tileManager)
  {
    m_tileManager = tileManager;
    RequestRedraw();
  }
}

//---------------//
// Configuration //
//---------------//

inline void TrnRenderer::SetUpdateView (bool state)
{
  if (state != m_updateView)
  {
    m_updateView = state;
    RequestRedraw();
  }
}

inline void TrnRenderer::SetWireframe (bool state)
{
  if (state != m_wireframe)
  {
    m_wireframe = state;
    RequestRedraw();
  }
}

inline void TrnRenderer::SetShowBBoxes (bool state)
{
  if (state != m_showBBoxes)
  {
    m_showBBoxes = state;
    RequestRedraw();
  }
}

inline void TrnRenderer::SetShowViews (bool state)
{
  if (state != m_showViews)
  {
    m_showViews = state;
    RequestRedraw();
  }
}

inline void TrnRenderer::SetShowStats (bool state)
{
  if (state != m_showStats)
  {
    m_showStats = state;
    RequestRedraw();
  }
}

inline void TrnRenderer::SetOpacity (float opacity)
{
  if (opacity != m_opacity)
  {
    m_opacity = opacity;
    RequestRedraw();
  }
}

inline void TrnRenderer::SetFogDensity (float density)
{
  if (density != m_fogDensity)
  {
    m_fogDensity = density;
    RequestRedraw();
  }
}

inline void TrnRenderer::SetFogColor (float r, float g, float b, float a)
{
  if (r != m_fogColor[0] || g != m_fogColor[1] || b != m_fogColor[2] || a != m_fogColor[3])
  {
    m_fogColor[0] = r;
    m_fogColor[1] = g;
    m_fogColor[2] = b;
    m_fogColor[3] = a;
    RequestRedraw();
  }
}

inline bool TrnRenderer::GetUpdateView () const
{
  return m_updateView;
}

inline bool TrnRenderer::GetWireframe () const
{
  return m_wireframe;
}

inline bool TrnRenderer::GetShowBBoxes () const
{
  return m_showBBoxes;
}

inline bool TrnRenderer::GetShowViews () const
{
  return m_showViews;
}

inline bool TrnRenderer::GetShowStats () const
{
  return m_showStats;
}

inline float TrnRenderer::GetOpacity () const
{
  return m_opacity;
}

inline float TrnRenderer::GetFogDensity () const
{
  return m_fogDensity;
}

inline void TrnRenderer::GetFogColor (float* r, float* g, float* b, float* a) const
{
  if (r) *r = m_fogColor[0];
  if (g) *g = m_fogColor[1];
  if (b) *b = m_fogColor[2];
  if (a) *a = m_fogColor[3];
}

inline float TrnRenderer::GetErrorTolerance () const
{
  return m_errorTolerance;
}

//-----------------//
// Redraw Callback //
//-----------------//

inline void TrnRenderer::SetRedrawCallback (TrnRedrawCallback cb, void* data)
{
  m_cbRedrawFunc = cb;
  m_cbRedrawData = data;
}

inline void TrnRenderer::RequestRedraw ()
{
  if (m_cbRedrawFunc)
    m_cbRedrawFunc(m_cbRedrawData);
}
