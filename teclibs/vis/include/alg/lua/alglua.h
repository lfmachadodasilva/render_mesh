#ifndef ALG_LUA
#define ALG_LUA

#ifdef __cplusplus
extern "C" {
#endif
#include <lua.h>
#ifdef __cplusplus
}
#endif

#ifndef ALGLUA_DLL
# ifndef TEC_DLL
#  define ALGLUAAPI
# else
#  define ALGLUAAPI __declspec(dllimport)
# endif
#else
# define ALGLUAAPI __declspec(dllexport)
#endif

ALGLUAAPI int  alg_open   (lua_State* L);
ALGLUAAPI void alg_close  (lua_State* L);

#endif
