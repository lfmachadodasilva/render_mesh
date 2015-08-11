#ifndef SCIUTILS_IUP_LUA
# define SCIUTILS_IUP_LUA

# ifdef __cplusplus
extern "C" {
# endif
# include <lua.h>

#include <sciutils/defines.h>

#ifndef SCIUTILSIUP_DLL
# ifndef TEC_DLL
#  define SCIUTILSIUPAPI
# else
#  define SCIUTILSIUPAPI __declspec(dllimport)
# endif
#else
# define SCIUTILSIUPAPI __declspec(dllexport)
#endif

SCIUTILSIUPAPI int sciutilsiup_open (lua_State* L);

# ifdef __cplusplus
}
# endif

#endif
