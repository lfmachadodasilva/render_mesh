#ifndef UTESTGL_LUA_H
#define UTESTGL_LUA_H

#ifdef __cplusplus
extern "C" {
#endif
#include <lua.h>
#ifdef __cplusplus
}
#endif

#ifdef _WIN32
# ifdef UTESTGLLUA_DLL
#  define UTESTGLLUAAPI extern "C" __declspec(dllexport)
# else
#  define UTESTGLLUAAPI extern "C"
# endif
#else
# define UTESTGLLUAAPI extern "C"
#endif

UTESTGLLUAAPI int luaopen_utestgl (lua_State* L);
UTESTGLLUAAPI void luaclose_utestgl (lua_State* L);

#endif
