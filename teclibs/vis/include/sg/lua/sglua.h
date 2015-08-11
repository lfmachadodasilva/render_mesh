#ifndef SGLUA_H
#define SGLUA_H

extern "C" {
#include <lua.h>
#include <lauxlib.h>
}

#ifndef SGLUA_DLL
# ifndef TEC_DLL
#  define SGLUAAPI
# else
#  define SGLUAAPI __declspec(dllimport)
# endif
#else
# define SGLUAAPI __declspec(dllexport)
#endif

SGLUAAPI int sg_open (lua_State* l);

#endif
