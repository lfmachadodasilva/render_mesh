#ifndef TERRAIN_TERRAIN_H
#define TERRAIN_TERRAIN_H

//-----------------------------------//
// Includes and Forward Declarations //
//-----------------------------------//

#include "baseclass.h"
#include "quadtreeterrain.h"
#include <ds/mtqueue.h>

class TrnFileManager;
class TrnTilerHeight;
class TrnTilerTexture;
class TrnDataLoader;
class TrnTerrainGroup;

//------------------//
// TrnTerrain Class //
//------------------//

class TERRAINAPI TrnTerrain : public TrnBaseClass
{
public:

  // Class Name

  static const char* CLASSNAME () {return "TrnTerrain";}
  virtual const char* ClassName () const {return CLASSNAME();}

  // Typedefs

  typedef void (*TrnProgressCallback) (void* data, float progress);

  // Constructor and Destructor

  TrnTerrain ();
  virtual ~TrnTerrain ();

  // Object Links

  void SetTerrainGroup (TrnTerrainGroup* group);

  TrnTerrainGroup* GetTerrainGroup () const;
  TrnFileManager* GetFileManager () const;
  TrnTilerHeight* GetTilerHeight () const;
  TrnTilerTexture* GetTilerTexture () const;

  // Preprocessing, Loading and Saving
  // When loading from source, specify a vtf filename to preprocess the terrain

  int LoadFromSource (TrnDataLoader* hgtdata, int hgt_tilesize, TrnTileHeightType hgt_tiletype,
                      TrnDataLoader* texdata, int tex_tilesize,
                      const char* wrl_filename,
                      const char* vtf_filename, bool compress);
  int LoadFromSource (TrnDataLoader* hgtdata, int hgt_tilesize, TrnTileHeightType hgt_tiletype,
                      TrnDataLoader* texdata, int tex_tilesize,
                      const char* vtf_filename, bool compress);
  int LoadFromVtf (const char* vtf_filename, const bool outofcore);
  int Save (const char* vtf_filename, bool compress);

  // Height and Texture Tile Query

  void SetHgtBoundingShape (TrnTileHeightBounding shape);

  bool GetHgtBBox (q_index tileindex, float *x_min, float *y_min, float *z_min,
                                      float *x_max, float *y_max, float *z_max) const;

  bool IsHgtVisible (q_index tileindex, const TrnViewParameters& view) const;
  bool EvalHgtVisible (q_index tileindex, const TrnViewParameters& view) const;

  q_index GetMatchingHgtIndex (q_index texindex);
  q_index GetMatchingTexIndex (q_index hgtindex);

  q_index GetTileIndexAtPosition (float x, float z, int level);

  bool GetActualValidAtPosition (float x, float z);
  bool GetLoadedValidAtPosition (float x, float z);
  bool GetDrawnValidAtPosition (float x, float z);

  float GetActualHeightAtPosition (float x, float z, bool transform = true);
  float GetLoadedHeightAtPosition (float x, float z, bool transform = true);
  float GetDrawnHeightAtPosition (float x, float z, bool transform = true);

  TrnObjectType GetLoadedIntersection (AlgVector rayOrigin, AlgVector rayUnitDirection, AlgVector* intersection);

  bool HasHeight () const;
  bool HasTexture () const;

  // Origin, Scale, Thickness, Bounding Box

  void SetDataOriginY (float y);
  void SetTerrainOrigin (double x, double y, double z);
  void SetTerrainScale (float x, float y, float z);
  void SetUserOrigin (float x, float y, float z);
  void SetUserScale (float x, float y, float z);
  void SetUserThickness (float thickness);

  float GetDataOriginY () const;
  const double* GetTerrainOrigin () const;
  const float* GetTerrainScale () const;
  const float* GetUserOrigin () const;
  const float* GetUserScale () const;
  float GetUserThickness () const;

  void GetBBox (float *xmin, float *ymin, float *zmin,float *xmax, float *ymax, float *zmax);
  void GetCenter (float *xctr, float *yctr, float *zctr);
  void GetSize (float *xsize, float *ysize, float *zsize);

  void SetUpdateHgtBBoxes ();

  // Save/Load Progress

  void SetProgressCallback (TrnProgressCallback cb, void* data);

  void IncProgress (float increment);
  void SetProgress (float progress);
  void UpdateProgress ();

  // Validity 

  void SetCheckingValidity (bool state);
  bool IsCheckingValidity () const;

  // Terrain Queries

  bool IsOutOfCore () const;
  bool IsDataCompressed () const;

private:

  TrnTilerHeight* CreateTilerHeight (TrnTileHeightType tiletype);
  TrnTilerTexture* CreateTilerTexture ();

  bool CheckQuadtreeConsistency ();

  int SaveVTFFile (const char* vtf_filename);
  int LoadVTFFile (const char* vtf_filename);

  void AssertUpdatedBBox ();
  void UpdateBBox ();

private:

  TrnTerrainGroup*    m_group;
  TrnFileManager*     m_fileManager;

  float               m_progress;
  float               m_progressMultiplier;
  TrnProgressCallback m_progressCallback;
  void*               m_progressCallbackData;

  TrnTilerHeight*     m_tilerHeight;
  TrnTilerTexture*    m_tilerTexture;

  float               m_dataOriginY;   // Adjusts height data stored in disk and internal arrays
  double              m_trnOrigin[3];  // Adjusts terrain to its real position
  float               m_trnScale[3];   // Adjusts terrain to its real dimensions
  float               m_userOrigin[3]; // User translation for rendering
  float               m_userScale[3];  // User scale for rendering
  float               m_userThickness; // User thickness for rendering

  bool                m_compressedData;
  bool                m_outofcore;
  bool                m_checkvalidity;

  float               m_xmin, m_ymin, m_zmin;
  float               m_xmax, m_ymax, m_zmax;
  float               m_xctr, m_yctr, m_zctr;
  float               m_xsize, m_ysize, m_zsize;
  bool                m_needUpdateBBox;
};

#include "qterrain.inl"

#endif // TERRAIN_TERRAIN_H
