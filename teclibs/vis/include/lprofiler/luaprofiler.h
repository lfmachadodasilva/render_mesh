#ifndef LPROFILER
#define LPROFILER

#ifndef LPROFILER_DLL
# ifndef TEC_DLL
#  define LPROFILERAPI
# else
#  define LPROFILERAPI  __declspec(dllimport)
# endif
#else
# define LPROFILERAPI  __declspec(dllexport)
#endif

#ifdef __cplusplus
extern "C" {
#endif
#include <lua.h>
LPROFILERAPI int luaopen_profiler (lua_State* L);
LPROFILERAPI void luaclose_profiler (lua_State* L);
#ifdef __cplusplus
}
#endif

#endif

