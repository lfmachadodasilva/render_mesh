// SGPLYWriter
// fabraham@tecgraf.puc-rio.br
// Oct 2004

#ifndef SG_LODPLYWRITER
#define SG_LODPLYWRITER

#include "plywriter.h"

class SGPLYAPI SGLODPlyWriter : public SGPlyWriter
{
public:
  SGLODPlyWriter (bool binary, char *vertexname="vertex", char *facename="face", char *stripname="strip");
  virtual ~SGLODPlyWriter ();
  virtual void Write (SGMesh *mesh, UtlWriter *writer);
};

#endif

