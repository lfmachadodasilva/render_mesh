#ifndef UFONT_LUA
#define UFONT_LUA

#ifdef __cplusplus
extern "C" {
#endif
#include <lua.h>
#ifdef __cplusplus
}

#ifdef _WIN32
#ifdef UFONTLUA_DLL
#define UFONTLUAAPI extern "C" __declspec(dllexport)
#else
#define UFONTLUAAPI extern "C"
#endif
#else
#define UFONTLUAAPI extern "C"
#endif
#else
#define UFONTLUAAPI
#endif

/**
 * Exports the ufont module to lua.
 */
UFONTLUAAPI int ufont_open (lua_State* L);
/**
 * Specifies additional font directories, other than the system paths
 * (windows fonts on windows and mscorefonts on linux).
 */
UFONTLUAAPI void ufont_add_fonts_path (const char* path);
/**
 * Initializes font tables in lua.
 */
UFONTLUAAPI int ufont_init_fonts (lua_State* L);
/**
 * Closes the ufont module.
 */
UFONTLUAAPI void ufont_close (lua_State* L);

#endif
