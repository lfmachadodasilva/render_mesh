#ifndef SGCGLUA_H
#define SGCGLUA_H

extern "C" {
#include <lua.h>
#include <lauxlib.h>
}

#ifndef SGCG_DLL
# ifndef TEC_DLL
#  define SGCGAPI
# else
#  define SGCGAPI __declspec(dllimport)
# endif
#else
# define SGCGAPI __declspec(dllexport)
#endif

SGCGAPI int sgcg_open (lua_State* l);

#endif
