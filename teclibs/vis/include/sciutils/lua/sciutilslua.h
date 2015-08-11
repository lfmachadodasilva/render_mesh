#ifndef SCIUTILS_LUA
# define SCIUTILS_LUA

# ifdef __cplusplus
extern "C" {
# endif
# include <lua.h>

#include <sciutils/defines.h>

#ifndef SCIUTILSLUA_DLL
# ifndef TEC_DLL
#  define SCIUTILSLUAAPI
# else
#  define SCIUTILSLUAAPI __declspec(dllimport)
# endif
#else
# define SCIUTILSLUAAPI __declspec(dllexport)
#endif

SCIUTILSLUAAPI int sciutils_open (lua_State* L);

# ifdef __cplusplus
}
# endif

#endif

