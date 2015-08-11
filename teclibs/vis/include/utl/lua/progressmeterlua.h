#ifndef PROGRESSMETER_LUA
#define PROGRESSMETER_LUA

#ifndef PROGRESSMETER_DLL
# ifndef TEC_DLL
#  define PROGRESSMETERAPI
# else
#  define PROGRESSMETERAPI  __declspec(dllimport)
# endif
#else
# define PROGRESSMETERAPI  __declspec(dllexport)
#endif

#ifdef __cplusplus
extern "C" {
#endif
#include <lua.h>

PROGRESSMETERAPI int luaopen_progressmeter (lua_State* L);

#ifdef __cplusplus
}
#endif

#endif

