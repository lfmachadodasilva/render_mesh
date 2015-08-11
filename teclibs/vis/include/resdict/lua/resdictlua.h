#ifndef RES_DICT_LUA
#define RES_DICT_LUA

#ifdef __cplusplus
extern "C" {
#endif
#include <lua.h>
#ifdef __cplusplus
}
#endif

#ifndef RESDICTLUA_DLL
# ifndef TEC_DLL
#  define RESDICTLUAAPI
#  define RESDICTLUACAPI extern "C"
# else
#  define RESDICTLUAAPI __declspec(dllimport)
#  define RESDICTLUACAPI extern "C" __declspec(dllimport)
# endif
#else
# define RESDICTLUAAPI __declspec(dllexport)
# define RESDICTLUACAPI extern "C" __declspec(dllexport)
#endif

RESDICTLUAAPI int luaopen_resdict (lua_State* L);

#endif

