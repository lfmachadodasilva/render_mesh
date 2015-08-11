#ifndef UTEST_LUA_H
#define UTEST_LUA_H

#ifdef __cplusplus
extern "C" {
#endif
#include <lua.h>
#ifdef __cplusplus
}
#endif

#ifdef _WIN32
# ifdef UTESTLUA_DLL
#  define UTESTLUAAPI extern "C" __declspec(dllexport)
# else
#  define UTESTLUAAPI extern "C"
# endif
#else
# define UTESTLUAAPI extern "C"
#endif

UTESTLUAAPI int  utest_open  (lua_State* L);
UTESTLUAAPI void utest_close (lua_State* L);

#endif
