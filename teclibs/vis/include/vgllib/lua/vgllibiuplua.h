#ifndef VGLLIBIUP_LUA
#define VGLLIBIUP_LUA

#ifdef __cplusplus
extern "C" {
#endif
#include <lua.h>
#ifdef __cplusplus
}
#endif

#ifndef VGLLIBIUPLUA_DLL
# ifndef TEC_DLL
#  define VGLLIBIUPLUAAPI
# else
#  define VGLLIBIUPLUAAPI __declspec(dllimport)
# endif
#else
# define VGLLIBIUPLUAAPI __declspec(dllexport)
#endif

VGLLIBIUPLUAAPI int vgllibiup_open (lua_State* L);

#endif
