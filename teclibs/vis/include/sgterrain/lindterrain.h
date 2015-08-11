// Lindstrom Terrain class
// gustavo@tecgraf.puc-rio.br
// Oct 2004

#ifndef SGTERRAIN_TERRAIN_LINDSTROM_H
#define SGTERRAIN_TERRAIN_LINDSTROM_H

#include <sg/shape.h>
#include "defines.h"

class Terrain;

class SGTERRAINAPI SGLindTerrain : public SGShape
{
  Terrain* m_terrain;
  char *m_heightmapfilename;
  char *m_texturefilename;
  char *m_vtffilename;
  float m_origin[3];
  float m_scale[3];
  bool m_reindex;
  bool m_outofcore;
public:
  static const char* CLASSNAME () { return "LindTerrain"; }
  virtual const char* ClassName () const { return CLASSNAME(); }

  SGLindTerrain ();
  virtual ~SGLindTerrain ();

  bool Load (char* heightMapFileName, char* textureFileName=0, bool reindex=false,
  		     const float origin_x = 0, const float origin_y = 0, const float origin_z = 0,
			 const float scale_x = 1 , const float scale_y = 1 , const float scale_z = 1);
  bool Load(char* vtfFilename, bool outOfCore=false, char* textureFileName=0);
  bool Save(const char* filename);

  Terrain* GetTerrain() { return m_terrain; }
  float SetErrorTolerance(float tolerance);
  float GetErrorTolerance();
  bool GetUpdatePosition ();
  bool SetUpdatePosition (bool update);
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
  virtual int GetTriangleCount ();
  virtual int GetLineCount ();
  virtual void Draw ();
  virtual void Write (UtlWriter* writer);
};

#endif // SGTERRAIN_TERRAIN_LINDSTROM_H
