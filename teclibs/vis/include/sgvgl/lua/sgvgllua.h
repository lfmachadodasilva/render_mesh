#ifndef SGVGLLUA_H
#define SGVGLLUA_H

extern "C" {
#include <lua.h>
#include <lauxlib.h>
}

#ifndef SGVGLLUA_DLL
# ifndef TEC_DLL
#  define SGVGLLUAAPI
# else
#  define SGVGLLUAAPI __declspec(dllimport)
# endif
#else
# define SGVGLLUAAPI __declspec(dllexport)
#endif

SGVGLLUAAPI int sgvgl_open (lua_State* l);

#endif
