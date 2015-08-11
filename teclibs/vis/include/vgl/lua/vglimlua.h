#ifndef VGLIM_LUA
#define VGLIM_LUA

#ifdef __cplusplus
extern "C" {
#endif
#include <lua.h>
#ifdef __cplusplus
}
#endif

#ifndef VGLIMLUA_DLL
# ifndef TEC_DLL
#  define VGLIMLUAAPI
# else
#  define VGLIMLUAAPI __declspec(dllimport)
# endif
#else
# define VGLIMLUAAPI __declspec(dllexport)
#endif

VGLIMLUAAPI int  vglim_open   (lua_State* L);
VGLIMLUAAPI void vglim_close  (lua_State* L);

#endif
