#ifndef GPOS_LUA
# define GPOS_LUA

# ifdef __cplusplus
extern "C" {
# endif
# include <lua.h>
# ifdef __cplusplus
}
# endif

#ifndef GPOSLUA_DLL
# ifndef TEC_DLL
#  define RESLUAAPI
# else
#  define RESLUAAPI __declspec(dllimport)
# endif
#else
# define RESLUAAPI __declspec(dllexport)
#endif

RESLUAAPI int gpos_open (lua_State* L);
RESLUAAPI void gpos_close (lua_State *L);

#endif
