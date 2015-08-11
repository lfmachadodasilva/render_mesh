#ifndef VGL_IUP_LUA
#define VGL_IUP_LUA

#ifdef __cplusplus
extern "C" {
#endif
#include <lua.h>
#ifdef __cplusplus
}
#endif

#ifndef VGLIUPLUA_DLL
# ifndef TEC_DLL
#  define VGLIUPLUAAPI
# else
#  define VGLIUPLUAAPI __declspec(dllimport)
# endif
#else
# define VGLIUPLUAAPI __declspec(dllexport)
#endif

#ifdef LUA_NOOBJECT  /* Lua 3 */
int  VGLIUPLUAAPI vgliup_open   (void);
void VGLIUPLUAAPI vgliup_close  (void);
int  VGLIUPLUAAPI vglciup_open  (void);
void VGLIUPLUAAPI vglciup_close (void);
#endif
#ifdef LUA_NOREF  /* Lua 4 or 5 */
int  VGLIUPLUAAPI vgliup_open   (lua_State* L);
void VGLIUPLUAAPI vgliup_close  (lua_State* L);
int  VGLIUPLUAAPI vglciup_open  (lua_State* L);
void VGLIUPLUAAPI vglciup_close (lua_State* L);
#endif

#endif
