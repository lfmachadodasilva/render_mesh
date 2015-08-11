#ifndef VGL_LUA
#define VGL_LUA

#include <lbase/lbase.h>

#ifdef __cplusplus
extern "C" {
#endif
#include <lua.h>
#ifdef __cplusplus
}
#endif

#ifndef VGLLUA_DLL
# ifndef TEC_DLL
#  define VGLLUAAPI
#  define VGLLUACAPI extern "C"
# else
#  define VGLLUAAPI __declspec(dllimport)
#  define VGLLUACAPI extern "C" __declspec(dllimport)
# endif
#else
# define VGLLUAAPI __declspec(dllexport)
# define VGLLUACAPI extern "C" __declspec(dllexport)
#endif

VGLLUAAPI int  vgl_open   (lua_State* L);
VGLLUAAPI void vgl_close  (lua_State* L);
VGLLUACAPI int  vglc_open  (lua_State* L);
VGLLUACAPI void vglc_close (lua_State* L);

#endif
