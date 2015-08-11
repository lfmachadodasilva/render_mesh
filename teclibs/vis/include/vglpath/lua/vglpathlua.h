#ifndef VGLPATH_LUA
#define VGLPATH_LUA

#ifdef __cplusplus
extern "C" {
#endif
#include <lua.h>
#ifdef __cplusplus
}

#ifdef _WIN32
#ifdef VGLPATHLUA_DLL
#define VGLPATHLUAAPI extern "C" __declspec(dllexport)
#else
#define VGLPATHLUAAPI extern "C"
#endif
#else
#define VGLPATHLUAAPI extern "C"
#endif
#else
#define VGLPATHLUAAPI
#endif

VGLPATHLUAAPI int  vglpath_open   (lua_State* L);
VGLPATHLUAAPI void vglpath_close  (lua_State* L);

#endif
