//* open_aux.h
// Exports model loading routines to LUA: receives a LUA function as the callback.
// Tecgraf/PUC-Rio
// Jan 2004

#ifndef vis_model_open_aux_h
#define vis_model_open_aux_h

extern "C" {
#include "lua.h"
}

class ResModel;

void ResModelOpenAuxOpen(lua_State* l);

bool ResModelOpenAux (const char* name,
                      int numfiles,
                      char **filenames,
                      int* o_model_count,
                      ResModel*** o_models,
                      bool buildgeometry,
                      int loadkmin,
                      int loadkmax,
                      int spf,
                      int upf);
#endif
