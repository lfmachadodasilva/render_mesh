#ifndef GPOS_MESH_LUA
# define GPOS_MESH_LUA

# ifdef __cplusplus
extern "C" {
# endif
# include <lua.h>
# ifdef __cplusplus
}
# endif

#include <gpos/model/msh/meshio.h>

RESMESHAPI int gposmesh_open (lua_State* L);

#endif
