#ifndef SGUTILSLUA_H
#define SGUTILSLUA_H

#ifndef SGUTILS_DLL
# ifndef TEC_DLL
#  define SGUTILSAPI
# else
#  define SGUTILSAPI __declspec(dllimport)
# endif
#else
# define SGUTILSAPI __declspec(dllexport)
#endif

SGUTILSAPI int sgutils_open (lua_State* L);

#endif

