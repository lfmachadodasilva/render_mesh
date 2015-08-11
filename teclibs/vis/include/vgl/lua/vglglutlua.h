#ifndef VGL_GLUT_LUA
#define VGL_GLUT_LUA

#ifdef __cplusplus
extern "C" {
#endif
#include <lua.h>
#ifdef __cplusplus
}
#endif

#ifndef VGLGLUTLUA_DLL
# ifndef TEC_DLL
#  define VGLGLUTLUAAPI
# else
#  define VGLGLUTLUAAPI __declspec(dllimport)
# endif
#else
# define VGLGLUTLUAAPI __declspec(dllexport)
#endif

VGLGLUTLUAAPI int  vglglut_open   (lua_State* L);
VGLGLUTLUAAPI void vglglut_close  (lua_State* L);
VGLGLUTLUAAPI int  vglcglut_open  (lua_State* L);
VGLGLUTLUAAPI void vglcglut_close (lua_State* L);

#endif
