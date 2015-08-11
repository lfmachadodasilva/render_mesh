#ifndef RES_UNIT_LUA
#define RES_UNIT_LUA

#ifdef __cplusplus
extern "C" {
#endif
#include <lua.h>

#ifdef _WIN32
# ifdef RESUNIT_DLL
#  define RESUNITAPI __declspec(dllexport)
# else
#  define RESUNITAPI
# endif
#else
# define RESUNITAPI
#endif

RESUNITAPI int  resunit_open  (lua_State* L);
RESUNITAPI void resunit_close (lua_State* L);

#ifdef __cplusplus
}
#endif

#endif

