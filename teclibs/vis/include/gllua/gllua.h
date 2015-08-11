#ifndef GL_LUA
#define GL_LUA

extern "C" {
#include <lua.h>
}

#ifndef GLLUA_DLL
# ifndef TEC_DLL
#  define GLLUAAPI
# else
#  define GLLUAAPI __declspec(dllimport)
# endif
#else
# define GLLUAAPI __declspec(dllexport)
#endif

GLLUAAPI int gl_open (lua_State* L);
GLLUAAPI void gl_close (lua_State* L);

#endif
