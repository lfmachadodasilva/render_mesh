#ifndef LBASE_LUA
#define LBASE_LUA

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif
#include <lua.h>
#include <tolua.h>

#include "defines.h"

typedef struct
{
  lua_State* L;
  int self_ref;
  void *self;
  const char *selftype;
  int func_ref;
  int data_ref;
  int uniqueperobj;
} Func;

LBASEAPI int lbase_open (lua_State* L);
LBASEAPI void lbase_close (lua_State* L);
LBASEAPI void lbase_seterrorfuncc (lua_State *L, lua_CFunction func);
LBASEAPI int lbase_seterrorfunclua (lua_State *L, int stackpos);
LBASEAPI int lbase_call (lua_State *L, int nargs, int nresults);
LBASEAPI int lbase_printtraceback (lua_State *L);
LBASEAPI const char* lbase_getloext ();

/**
 * Checks the Lua stack for the parameters of a callback setting function
 * of the following type:
 * obj:[SetCallback](function,data)
 * Checks the type of 'obj' in stack position 1 (must be 'objtype').
 * Checks if function is a function in stack position 2.
 * Checks if 'data' is a table or nil or noobj.
 */
LBASEAPI int lbase_checksetfuncparams (
  lua_State *L,
  const char *objtype,
  tolua_Error *tolua_err
);
/**
 * Creates a Lua Func structure for callback setting functions of the
 * following type:
 * obj:[SetCallback](function,data)
 * Assumes that 'obj'  is in stack position 1.
 * Assumes that 'func' is in stack position 2.
 * Assumes that 'data' is in stack position 3 and is a table or nil or noobj.
 *
 * If 'uniqueperobj', the callback is assumed to be unique per object,
 * otherwise it is assumed that one object can have many callbacks.
 * If 'self' is specified, then it will be the first parameter
 * to the callback, pushed with type 'selftype'.
 *
 * Returns a newly created lua callback structure.
 * Returns NULL in case uniqueperobj=0 and the callback was already found.
 */
#ifdef __cplusplus
LBASEAPI Func *lbase_createfunc (lua_State *L,
                                 int uniqueperobj=NULL,
                                 void *self=NULL,
                                 const char *selftype=NULL);
#else
LBASEAPI Func *lbase_createfunc (lua_State *L,
                                 int uniqueperobj,
                                 void *self,
                                 const char *selftype);
#endif
/**
 * Pushes the lua function referenced by 'data'
 * (which was created with lbase_createfunc or lbase_createcb)
 * and the object reference if it was specified in
 * lbase_createfunc.
 */
LBASEAPI Func* lbase_pushcb (void *data);
/**
 * Pushes the 'data' parameter of the obj:[SetCallback](function,data).
 */
LBASEAPI void lbase_pushdata (void *data);
/**
 * Informs whether the 'self' parameter of the obj:[SetCallback](function,data)
 * is going to be passed to the callback.
 */
LBASEAPI int lbase_hasself (void *data);
/**
 * Informs whether the 'data' parameter of the obj:[SetCallback](function,data)
 * exists.
 */
LBASEAPI int lbase_hasdata (void *data);
/**
 * Creates a Lua Func structure for callback setting functions of the
 * following type:
 * obj:[SetCallback](function,data)
 * Assumes that 'obj'  is in stack position 1.
 * Assumes that 'func' is in stack position 2.
 * Assumes that 'data' is in stack position 3 and is a table or nil or noobj.
 * Assumes that the callback is unique (see lbase_createfunc).
 * If 'passselftofunc' is 1, 'obj' is passed as the first parameter
 * of the callback, pushed with type 'objtype'.
 *
 * In case of errors, this function calls tolua_error with the appropriate
 * message (setfuncname is used in the message).
 *
 * Returns the newly created lua callback structure.
 */
LBASEAPI Func* lbase_createcb (
  lua_State* L,
  const char *objtype,
  const char *setfuncname,
  int passselftofunc
);
/**
 * Removes and returns a non-unique callback that is assumed to be
 * at stack position 2.
 */
LBASEAPI Func* lbase_remove_nonunique_callback (lua_State *L);
/**
 * This macro defines a callback setting function,
 * to be used with tolua_function.
 *
 * 'func' is the function name.
 * 'classname' is the object class name (without ").
 * 'setfuncname' is the object class method for setting callbacks (without ").
 * 'passselftofunc' must be 1 if 'obj' must be passed as first callback
 * parameter.
 */
#define LBASE_DEFINE_SET_UNIQUE_CB(func,classname,setfuncname,funcname,passselftofunc) \
  static int func(lua_State *L) \
  { \
    Func* f = lbase_createcb(L,#classname,#setfuncname,passselftofunc); \
    classname* self = (classname*) tolua_tousertype(L,1,0); \
    self->setfuncname(funcname,f); \
    return 0; \
  }

#ifdef __cplusplus
}
#endif

#endif
