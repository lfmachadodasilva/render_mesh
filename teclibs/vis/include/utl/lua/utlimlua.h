#ifndef UTL_IM_LUA
#define UTL_IM_LUA

#ifdef __cplusplus
extern "C" {
#endif
#include <lua.h>
#ifdef __cplusplus
}
#endif

#ifdef _WIN32
# ifdef UTLIMLUA_DLL
#  define UTLIMLUAAPI extern "C" __declspec(dllexport)
# else
#  define UTLIMLUAAPI extern "C"
# endif
#else
# define UTLIMLUAAPI extern "C"
#endif

#ifdef LUA_NOOBJECT  /* Lua 3 */
UTLIMLUAAPI int  utlim_open   (void);
UTLIMLUAAPI void utlim_close  (void);
#endif
#ifdef LUA_NOREF  /* Lua 4 or 5 */
UTLIMLUAAPI int  utlim_open   (lua_State* L);
UTLIMLUAAPI void utlim_close  (lua_State* L);
#endif

#endif
