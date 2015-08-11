#ifndef SGBVTREELUA_H
#define SGBVTREELUA_H

#ifndef SGBVTREELUA_DLL
# ifndef TEC_DLL
#  define SGBVTREELUAAPI
# else
#  define SGBVTREELUAAPI __declspec(dllimport)
# endif
#else
# define SGBVTREELUAAPI __declspec(dllexport)
#endif

SGBVTREELUAAPI int sgbvtree_open (lua_State* L);

#endif
