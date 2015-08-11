// Hmap class
// djavanes@tecgraf.puc-rio.br
// Oct 2003

#ifndef SG_HMAP_H
#define SG_HMAP_H

#include <sg/shp/mesh.h>

class SG_API SGHmap : public SGMesh
{

public:
  static const char* CLASSNAME () { return "Hmap"; }
  virtual const char* ClassName () const { return CLASSNAME(); }

  SGHmap ();
  virtual ~SGHmap ();

  bool LoadHmap (char * filename);

  virtual void Write (UtlWriter* writer);
};

#endif
