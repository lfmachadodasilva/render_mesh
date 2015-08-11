#ifndef PLYLOADERLUA_H
#define PLYLOADERLUA_H

struct lua_State;

#ifndef SGPLYLUA_DLL
# ifndef TEC_DLL
#  define SGPLYLUAAPI
# else
#  define SGPLYLUAAPI __declspec(dllimport)
# endif
#else
# define SGPLYLUAAPI __declspec(dllexport)
#endif

SGPLYLUAAPI int sgply_open (lua_State* L);

#endif

