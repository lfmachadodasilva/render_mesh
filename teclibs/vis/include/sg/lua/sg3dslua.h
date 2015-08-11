#ifndef _3DSLOADERLUA_H
#define _3DSLOADERLUA_H

extern "C" {
#include <lua.h>
#include <lauxlib.h>
}

#ifndef SG3DSLUA_DLL
# ifndef TEC_DLL
#  define SG3DSLUAAPI
# else
#  define SG3DSLUAAPI __declspec(dllimport)
# endif
#else
# define SG3DSLUAAPI __declspec(dllexport)
#endif

SG3DSLUAAPI int sg3ds_open  (lua_State* L);

#endif
