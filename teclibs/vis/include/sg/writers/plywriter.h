// SGPLYWriter
// fabraham@tecgraf.puc-rio.br
// Oct 2004

#ifndef SG_PLYWRITER
#define SG_PLYWRITER

#include "meshwriter.h"
#include <sg/sgply.h>

SGPLYAPI bool sgply_writefile (const SGMesh *mesh, const char* filename, bool binary=false, char *vertexname="vertex", char *facename="face", char *stripname="strip");

class SGPLYAPI SGPlyWriter : public SGMeshWriter
{
protected:
  bool m_binary;
  char *m_vertexname;
  char *m_facename;
  char *m_stripname;
public:
  SGPlyWriter (bool binary, char *vertexname="vertex", char *facename="face", char *stripname="strip");
  virtual ~SGPlyWriter ();
  virtual void Write (SGMesh *mesh, UtlWriter *writer);
};

#endif

