#ifndef UTL_IUP_LUA
#define UTL_IUP_LUA

#ifdef __cplusplus
extern "C" {
#endif
#include <lua.h>
#ifdef __cplusplus
}
#endif

#ifdef _WIN32
# ifdef UTLIUPLUA_DLL
#  define UTLIUPLUAAPI extern "C" __declspec(dllexport)
# else
#  define UTLIUPLUAAPI extern "C"
# endif
#else
# define UTLIUPLUAAPI extern "C"
#endif

UTLIUPLUAAPI int utliup_open(lua_State* L);

#endif
