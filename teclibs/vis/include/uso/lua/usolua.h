#ifndef USO_LUA
#define USO_LUA

#ifdef __cplusplus
extern "C" {
#endif
#include <lua.h>

#ifdef _WIN32
# ifdef USOLUA_DLL
#  define USOLUAAPI __declspec(dllexport)
# else
#  define USOLUAAPI
# endif
#else
# define USOLUAAPI
#endif

USOLUAAPI int  luaopen_uso (lua_State* L);
USOLUAAPI void luaclose_uso (lua_State* L);

#ifdef __cplusplus
}
#endif

#endif
