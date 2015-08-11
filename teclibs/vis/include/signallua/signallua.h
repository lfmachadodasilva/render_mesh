#ifndef SIGNAL_LUA
#define SIGNAL_LUA

#ifdef __cplusplus
extern "C" {
#endif
#include <lua.h>
#ifdef __cplusplus
}
# ifdef _WIN32
#  ifdef SIGNALLUADLL
#   define SIGNALLUAAPI __declspec(dllexport)
#  else
#   define SIGNALLUAAPI extern "C"
#  endif
# else
#  define SIGNALLUAAPI extern "C"
# endif
#else
# define SIGNALLUAAPI
#endif

#ifdef LUA_NOOBJECT  /* Lua 3 */
SIGNALLUAAPI int signal_open (void);
#endif
#ifdef LUA_NOREF  /* Lua 4 or 5 */
SIGNALLUAAPI int signal_open (lua_State* L);
#endif

#endif
