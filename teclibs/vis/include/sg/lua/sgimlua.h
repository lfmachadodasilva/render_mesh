#ifndef SGIMLUA_H
#define SGIMLUA_H

extern "C" {
#include <lua.h>
}

#ifdef SGIMLUA_DLL
# define SGIMLUAAPI extern "C" __declspec(dllexport)
#else
# define SGIMLUAAPI extern "C"
#endif

SGIMLUAAPI int sgim_open (lua_State* L);

#endif
