#ifndef SGOBJLUA_H
#define SGOBJLUA_H

#ifndef SGOBJLUA_DLL
# ifndef TEC_DLL
#  define SGOBJLUAAPI
# else
#  define SGOBJLUAAPI __declspec(dllimport)
# endif
#else
# define SGOBJLUAAPI __declspec(dllexport)
#endif

SGOBJLUAAPI int sgobj_open (lua_State* L);

#endif
