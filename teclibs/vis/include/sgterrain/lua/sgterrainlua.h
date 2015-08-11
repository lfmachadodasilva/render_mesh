#ifndef SGTERRAINLUA_H
#define SGTERRAINLUA_H

#ifndef SGTERRAINLUA_DLL
# ifndef TEC_DLL
#  define SGTERRAINLUAAPI
# else
#  define SGTERRAINLUAAPI __declspec(dllimport)
# endif
#else
# define SGTERRAINLUAAPI __declspec(dllexport)
#endif

SGTERRAINLUAAPI int sgterrain_open (lua_State* L);

#endif

