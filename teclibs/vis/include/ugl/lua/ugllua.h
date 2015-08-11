#ifndef UGL_LUA
#define UGL_LUA

#ifdef __cplusplus
extern "C" {
#endif
#include <lua.h>
#ifdef __cplusplus
}
#endif

#ifdef _WIN32
# ifdef UGLLUA_DLL
#  define UGLLUAAPI extern "C" __declspec(dllexport)
# else
#  define UGLLUAAPI extern "C"
# endif
#else
# define UGLLUAAPI extern "C"
#endif

#ifdef LUA_NOOBJECT  /* Lua 3 */
UGLLUAAPI int  ugl_open   (void);
UGLLUAAPI void ugl_close  (void);
#endif
#ifdef LUA_NOREF  /* Lua 4 or 5 */
UGLLUAAPI int  ugl_open   (lua_State* L);
UGLLUAAPI void ugl_close  (lua_State* L);
#endif

#endif
