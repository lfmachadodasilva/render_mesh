//* qterrain.inl
// vbarata@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Jun 2009

//----------//
// Includes //
//----------//

#include <assert.h>

//--------------//
// Object Links //
//--------------//

inline void TrnTerrain::SetTerrainGroup (TrnTerrainGroup* group)
{
  m_group = group;
}

inline TrnTerrainGroup* TrnTerrain::GetTerrainGroup () const
{
  return m_group;
}

inline TrnFileManager* TrnTerrain::GetFileManager () const
{
  return m_fileManager;
}

inline TrnTilerHeight* TrnTerrain::GetTilerHeight () const
{
  return m_tilerHeight;
}

inline TrnTilerTexture* TrnTerrain::GetTilerTexture () const
{
  return m_tilerTexture;
}

//-------------------------------//
// Height and Texture Tile Query //
//-------------------------------//

inline bool TrnTerrain::HasHeight () const
{
  return m_tilerHeight != NULL;
}

inline bool TrnTerrain::HasTexture () const
{
  return m_tilerTexture != NULL;
}

//----------------------------------------//
// Origin, Scale, Thickness, Bounding Box //
//----------------------------------------//

inline void TrnTerrain::SetDataOriginY (float y)
{
  m_dataOriginY = y;
  SetUpdateHgtBBoxes();
}

inline void TrnTerrain::SetTerrainOrigin (double x, double y, double z)
{
  m_trnOrigin[0] = x;
  m_trnOrigin[1] = y;
  m_trnOrigin[2] = z;
  SetUpdateHgtBBoxes();
}

inline void TrnTerrain::SetTerrainScale (float x, float y, float z)
{
  m_trnScale[0] = x;
  m_trnScale[1] = y;
  m_trnScale[2] = z;
  SetUpdateHgtBBoxes();
}

inline void TrnTerrain::SetUserOrigin (float x, float y, float z)
{
  m_userOrigin[0] = x;
  m_userOrigin[1] = y;
  m_userOrigin[2] = z;
  SetUpdateHgtBBoxes();
}

inline void TrnTerrain::SetUserScale (float x, float y, float z)
{
  m_userScale[0] = x;
  m_userScale[1] = y;
  m_userScale[2] = z;
  SetUpdateHgtBBoxes();
}

inline void TrnTerrain::SetUserThickness (float thickness)
{
  m_userThickness = thickness;
  SetUpdateHgtBBoxes();
}

inline float TrnTerrain::GetDataOriginY () const
{
  return m_dataOriginY;
}

inline const double* TrnTerrain::GetTerrainOrigin () const
{
  return m_trnOrigin;
}

inline const float* TrnTerrain::GetTerrainScale () const
{
  return m_trnScale;
}

inline const float* TrnTerrain::GetUserOrigin () const
{
  return m_userOrigin;
}

inline const float* TrnTerrain::GetUserScale () const
{
  return m_userScale;
}

inline float TrnTerrain::GetUserThickness () const
{
  return m_userThickness;
}

inline void TrnTerrain::GetBBox (float *xmin, float *ymin, float *zmin,float *xmax, float *ymax, float *zmax)
{
  AssertUpdatedBBox();
  if (xmin) *xmin = m_xmin;
  if (ymin) *ymin = m_ymin;
  if (zmin) *zmin = m_zmin;
  if (xmax) *xmax = m_xmax;
  if (ymax) *ymax = m_ymax;
  if (zmax) *zmax = m_zmax;
}

inline void TrnTerrain::GetCenter (float *xctr, float *yctr, float *zctr)
{
  AssertUpdatedBBox();
  if (xctr) *xctr = m_xctr;
  if (yctr) *yctr = m_yctr;
  if (zctr) *zctr = m_zctr;
}

inline void TrnTerrain::GetSize (float *xsize, float *ysize, float *zsize)
{
  AssertUpdatedBBox();
  if (xsize) *xsize = m_xsize;
  if (ysize) *ysize = m_ysize;
  if (zsize) *zsize = m_zsize;
}

inline void TrnTerrain::AssertUpdatedBBox ()
{
  if (m_needUpdateBBox)
  {
    UpdateBBox();
    m_needUpdateBBox = false;
  }
}

//--------------------//
// Save/Load Progress //
//--------------------//

inline void TrnTerrain::SetProgressCallback (TrnProgressCallback cb, void* data)
{
  m_progressCallback = cb;
  m_progressCallbackData = data;
}

inline void TrnTerrain::IncProgress (float increment)
{
  m_progress += m_progressMultiplier * increment;
  UpdateProgress();
}

inline void TrnTerrain::SetProgress (float progress)
{
  m_progress = progress;
  UpdateProgress();
}

inline void TrnTerrain::UpdateProgress ()
{
  if (m_progressCallback)
    m_progressCallback(m_progressCallbackData, m_progress);
}

//----------//
// Validity //
//----------//

inline bool TrnTerrain::IsCheckingValidity () const
{
  return m_checkvalidity;
}

//-----------------//
// Terrain Queries //
//-----------------//

inline bool TrnTerrain::IsOutOfCore () const
{
  return m_outofcore;
}

inline bool TrnTerrain::IsDataCompressed () const
{
  return m_compressedData;
}
