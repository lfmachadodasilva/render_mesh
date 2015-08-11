#ifndef VGLLIB_LUA
#define VGLLIB_LUA

#ifdef __cplusplus
extern "C" {
#endif
#include <lua.h>
#ifdef __cplusplus
}
#endif

#ifndef VGLLIBLUA_DLL
# ifndef TEC_DLL
#  define VGLLIBLUAAPI
# else
#  define VGLLIBLUAAPI __declspec(dllimport)
# endif
#else
# define VGLLIBLUAAPI __declspec(dllexport)
#endif

VGLLIBLUAAPI int vgllib_open (lua_State* L);

#endif
