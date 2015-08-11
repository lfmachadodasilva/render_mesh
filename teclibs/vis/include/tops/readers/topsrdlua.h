/**
 * @file
 * @brief Lua5 binding of TopS library.
 * */
#ifndef _TOP_TOPSRDLUA_H
#define _TOP_TOPSRDLUA_H

extern "C" { 
#include <lua.h>
}

int  topsrdlua_open (lua_State* L);

#endif
