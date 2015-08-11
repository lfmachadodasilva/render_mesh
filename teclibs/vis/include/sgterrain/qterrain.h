// Quadtree Terrain class
// vbarata@tecgraf.puc-rio.br
// Apr 2008

#ifndef SGTERRAIN_TERRAIN_QUADTREE_H
#define SGTERRAIN_TERRAIN_QUADTREE_H

#include "defines.h"

#include <sg/shape.h>

class TrnViewSpecifier;
class TrnTerrainGroup;
class TrnTerrain;

class SGTERRAINAPI SGQTerrain : public SGShape
{
public:

  // Classname

  static const char* CLASSNAME ()
  {
    return "QTerrain";
  }
  virtual const char* ClassName () const
  {
    return CLASSNAME();
  }

  // Constructor and destructor

  SGQTerrain ();
  virtual ~SGQTerrain ();

  bool Init ();

  // Preprocess, load, save

  bool PreProcess (const char* hgt_filename, int hgt_tilesize,
                   const char* tex_filename, int tex_tilesize,
                   float origin_x = 0.0f, float origin_y = 0.0f, float origin_z = 0.0f,
                   float scale_x  = 1.0f, float scale_y  = 1.0f, float scale_z  = 1.0f,
                   const char* vtf_filename = 0, bool compress = false);

  bool LoadInCore (const char* hgt_filename, int hgt_tilesize,
                   const char* tex_filename, int tex_tilesize,
                   float origin_x = 0.0f, float origin_y = 0.0f, float origin_z = 0.0f,
                   float scale_x  = 1.0f, float scale_y  = 1.0f, float scale_z  = 1.0f);

  bool LoadVtf (const char* vtf_filename = 0, bool outofcore = true);
  bool SaveVtf (const char* vtf_filename = 0, bool compress = false);

  // Getters and setters

  TrnTerrainGroup* GetTerrainGroup ()
  {
    return m_terrainGroup;
  }

  TrnTerrain* GetTerrain ()
  {
    return m_terrain;
  }

  bool SetResourcePath (const char* path);
  bool SetTerrainPath (const char* path);
  void SetErrorTolerance (float tolerance);
  void SetCheckingValidity (bool state);
  void SetUpdatePosition (bool update);
  void SetWireframe (bool wireframe);
  void SetShowBBoxes (bool showbboxes);
  void SetShowStats (bool showStats);
  void SetShowViews (bool showViews);

  const char* GetResourcePath () const;
  const char* GetTerrainPath () const;
  float GetErrorTolerance () const;
  bool IsCheckingValidity () const;
  bool GetUpdatePosition () const;
  bool GetWireframe () const;
  bool GetShowBBoxes () const;
  bool GetShowStats () const;
  bool GetShowViews () const;

  const float* GetOrigin () const;
  const float* GetScale () const;
  bool IsOutOfCore () const;

  float GetActualHeightAtPosition (float x, float z);
  float GetLoadedHeightAtPosition (float x, float z);
  float GetDrawnHeightAtPosition (float x, float z);

  // SGShape virtual methods

  virtual bool HasCulling ()
  {
    return true;
  }

  virtual int GetVertexCount ()
  {
    return 0;
  }

  virtual void GetVertex (int index, float *x, float *y, float *z)
  {
  }

  virtual int GetTriangleCount()
  {
    return 0;
  }

  virtual int GetLineCount ()
  {
    return 0;
  }

  virtual void Draw ();

  virtual void Write (UtlWriter* writer);

private:

  void CleanUp ();

private:

  TrnViewSpecifier* m_viewSpecifier;
  TrnTerrainGroup* m_terrainGroup;
  TrnTerrain* m_terrain;
  char* m_hgt_filename;
  char* m_tex_filename;
  char* m_vtf_filename;
  bool m_updateposition;
  bool m_initialized;
};

#endif // SGTERRAIN_TERRAIN_QUADTREE_H
