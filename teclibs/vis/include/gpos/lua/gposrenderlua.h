#ifndef GPOS_RENDER_LUA
# define GPOS_RENDER_LUA

# ifdef __cplusplus
extern "C" {
# endif
# include <lua.h>
# ifdef __cplusplus
}
# endif

int gposrender_open (lua_State* L);
void gposrender_close (lua_State *L);

#endif
