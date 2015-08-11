// SGMSHWriter
// fabraham@tecgraf.puc-rio.br
// Mar 2005

#ifndef SG_MSHWRITER
#define SG_MSHWRITER

#include "meshwriter.h"

class SG_API SGMSHWriter : public SGMeshWriter
{
public:
  SGMSHWriter ()
  {
  }
  virtual ~SGMSHWriter ()
  {
  }
  virtual void Write (SGMesh *mesh, UtlWriter *writer);
};

#endif
