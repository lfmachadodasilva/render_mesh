/**
 * @file
 * @brief Exportação da biblioteca Plot para LUA 3.2.
 * */
#ifndef __PLOTLUA_H
#define __PLOTLUA_H

#ifdef __cplusplus
extern "C" {
#endif

#include <cd.h>
#include <lua.h>
#include "plot.h"

PlotFunction* plotCreateLuaFunction(lua_State* L, int lo);

/**
 * Inicializa biblioteca plot para LUA 3.2.
 */
int  plotlua5_open (lua_State* L);

/**
 * Finaliza biblioteca plot para LUA.
 */
void plotlua5_close (lua_State* L);

#ifdef __cplusplus
}
#endif

#endif
