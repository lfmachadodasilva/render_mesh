#ifndef SGLODLUA_H
#define SGLODLUA_H

#ifndef SGLODLUA_DLL
# ifndef TEC_DLL
#  define SGLODLUAAPI
# else
#  define SGLODLUAAPI __declspec(dllimport)
# endif
#else
# define SGLODLUAAPI __declspec(dllexport)
#endif

SGLODLUAAPI int sglod_open (lua_State* L);

#endif
