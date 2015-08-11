/**
 * @file
 * @brief Exportação da biblioteca Plot para LUA 3.2.
 * */
#ifndef __GLPLOTLUA_H
#define __GLPLOTLUA_H

#include <cd.h>
extern "C" {
#include <lua.h>
}
#include "plot.h"

#ifndef GLPLOTLUA_DLL
# ifndef TEC_DLL
#  define PLOTLUAAPI
# else
#  define PLOTLUAAPI __declspec(dllimport)
# endif
#else
# define PLOTLUAAPI __declspec(dllexport)
#endif

PLOTLUAAPI PlotFunction* plotCreateLuaFunction(lua_State* L, int lo);

/**
 * Inicializa biblioteca plot para LUA 3.2.
 */
PLOTLUAAPI int plotlua_open (lua_State* L);

/**
 * Finaliza biblioteca plot para LUA.
 */
PLOTLUAAPI void plotlua_close (lua_State* L);

#endif
