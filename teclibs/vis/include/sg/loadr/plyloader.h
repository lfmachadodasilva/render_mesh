// SGPLYLoader
// fabraham@tecgraf.puc-rio.br
// Oct 2004

#ifndef SG_PLYLOADER
#define SG_PLYLOADER

#include <sg/sgply.h>

class SGMesh;

SGPLYAPI SGMesh* sgply_loadfile (const char* name, const char* filename, const char *vertexname="vertex", const char *facename="face", const char *stripname="strip", int lodorignvertices=-1, bool flipnormals=false, bool printerror=true);

SGPLYAPI SGMesh* sgply_loadlod (SGMesh *firstlod, const char* name, const char* filename, char *facename="face", char *stripname="strip", int lodorignvertices=-1, bool printerror=true);

#endif

