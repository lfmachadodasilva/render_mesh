/**
 * @file
 * @brief Lua5 binding of TopS library.
 * */
#ifndef _TOP_TOPSLUA_H
#define _TOP_TOPSLUA_H

extern "C" { 
#include <lua.h>
}

#include "defines.h"

int TOPS_API topslua_open (lua_State* L);

#endif
