#ifndef UGL_IM_LUA
#define UGL_IM_LUA

#ifdef __cplusplus
extern "C" {
#endif
#include <lua.h>
#ifdef __cplusplus
}
#endif

#ifdef _WIN32
# ifdef UGLIMLUA_DLL
#  define UGLIMLUAAPI extern "C" __declspec(dllexport)
# else
#  define UGLIMLUAAPI extern "C"
# endif
#else
# define UGLIMLUAAPI extern "C"
#endif

#ifdef LUA_NOOBJECT  /* Lua 3 */
UGLIMLUAAPI int  uglim_open   (void);
UGLIMLUAAPI void uglim_close  (void);
#endif
#ifdef LUA_NOREF  /* Lua 4 or 5 */
UGLIMLUAAPI int  uglim_open   (lua_State* L);
UGLIMLUAAPI void uglim_close  (lua_State* L);
#endif

#endif
