#ifndef SGSHADOWLUA_H
#define SGSHADOWLUA_H

#ifndef SGSHADOWLUA_DLL
# ifndef TEC_DLL
#  define SGSHADOWLUAAPI
# else
#  define SGSHADOWLUAAPI __declspec(dllimport)
# endif
#else
# define SGSHADOWLUAAPI __declspec(dllexport)
#endif

SGSHADOWLUAAPI int sgshadow_open (lua_State* L);

#endif
