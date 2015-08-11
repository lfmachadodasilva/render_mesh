#ifndef VGLAC_LUA
#define VGLAC_LUA

#ifdef __cplusplus
extern "C" {
#endif
#include <lua.h>
#ifdef __cplusplus
}
#endif

#ifdef _WIN32
#ifdef VGLACLUADLL
#define VGLACLUAAPI __declspec(dllexport)
#else
#define VGLACLUAAPI extern "C"
#endif
#else
#define VGLACLUAAPI extern "C"
#endif

VGLACLUAAPI int  vglac_open (lua_State* L);
VGLACLUAAPI void vglac_close (lua_State* L);

#endif
