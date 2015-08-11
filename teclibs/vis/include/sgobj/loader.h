#ifndef SG_OBJ_LOADER_H
#define SG_OBJ_LOADER_H

#include "defines.h"

class SGNode;

SGOBJAPI SGNode* SGLoadOBJFile (const char* name, const char* filename, bool replicate_texcoords=false);

#endif

