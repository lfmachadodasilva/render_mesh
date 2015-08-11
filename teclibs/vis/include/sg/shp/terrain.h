// Terrain class
// djavanes@tecgraf.puc-rio.br
// Oct 2003

#ifndef SG_TERRAIN_H
#define SG_TERRAIN_H

#include <sg/shp/mesh.h>

class SG_API SGTerrain : public SGMesh
{

public:
  static const char* CLASSNAME () { return "Terrain"; }
  virtual const char* ClassName () { return CLASSNAME(); }

  SGTerrain ();
  virtual ~SGTerrain ();

  bool LoadHmap (char * filename);
  bool LoadAsc (char * filename);
  bool LoadAscBorders (char * filename, int whichborder, float floor);
  void Normalize(SGArray * pos, SGArray * nor, int width, int height, bool inverse);

  virtual void Write (UtlWriter* writer);
};

#endif
