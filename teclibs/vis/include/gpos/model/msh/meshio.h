// meshio.h
// Tecgraf/PUC-Rio
// fabraham@tecgraf.puc-rio.br
// Jul 2006

#ifndef MESHIO_H
#define MESHIO_H

#ifndef GPOSMESH_DLL
# ifndef TEC_DLL
#  define RESMESHAPI
# else
#  define RESMESHAPI __declspec(dllimport)
# endif
#else
# define RESMESHAPI __declspec(dllexport)
#endif

struct lua_State;

/**
 * Initializes the MESH reservoir model file format opener.
 *
 * Parameters:
 *  L - the lua state into which the model will be loaded. If NULL,
 *      an internal lua state will be created.
 */
RESMESHAPI void gposmesh_init (lua_State *L);

#endif
