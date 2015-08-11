// SGMSHLoader
// fabraham@tecgraf.puc-rio.br
// Feb 2005

#ifndef SG_MSHLOADER
#define SG_MSHLOADER

#include <sg/defines.h>

class SGMesh;

SG_API SGMesh* sg_loadmshfile (const char* filename);
SG_API bool sg_writemshfile (SGMesh *mesh, const char* filename);

#endif

