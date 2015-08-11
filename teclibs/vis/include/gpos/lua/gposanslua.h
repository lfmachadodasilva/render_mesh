#ifndef GPOS_ANS_LUA
# define GPOS_ANS_LUA

# ifdef __cplusplus
extern "C" {
# endif
# include <lua.h>
# ifdef __cplusplus
}
# endif

int gposans_open (lua_State* L);

#endif
