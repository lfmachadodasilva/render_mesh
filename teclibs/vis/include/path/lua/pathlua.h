#ifndef PATH_LUA
#define PATH_LUA

#ifdef __cplusplus
extern "C" {
#endif
#include <lua.h>
#ifdef __cplusplus
}

#ifdef _WIN32
#ifdef PATHLUA_DLL
#define PATHLUAAPI extern "C" __declspec(dllexport)
#else
#define PATHLUAAPI extern "C"
#endif
#else
#define PATHLUAAPI extern "C"
#endif
#else
#define PATHLUAAPI
#endif

PATHLUAAPI int  campath_open   (lua_State* L);
PATHLUAAPI void campath_close  (lua_State* L);

#endif
