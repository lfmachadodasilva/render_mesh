#ifndef UTL_LUA
#define UTL_LUA

#ifndef UTLLUA_DLL
# ifndef TEC_DLL
#  define UTLLUAAPI
# else
#  define UTLLUAAPI  __declspec(dllimport)
# endif
#else
# define UTLLUAAPI  __declspec(dllexport)
#endif

#ifdef __cplusplus
extern "C" {
#endif
#include <lua.h>

UTLLUAAPI int utl_open   (lua_State* L);
UTLLUAAPI void utl_close  (lua_State* L);

/**
 * Exports to a global table named '[name].cmdoptions' the command line arguments in
 * the following way:
 * 
 * --varname true:  [name].cmdoptions.varname will have 'true' (boolean) as value
 * --varname false: [name].cmdoptions.varname will have 'false' (boolean) as value
 * --varname:       [name].cmdoptions.varname will have 'true' (boolean) as value
 * --varname 5:     [name].cmdoptions.varname will have '5' (number) as value
 * --varname text:  [name].cmdoptions.varname will have 'text' (string) as value
 *
 * If multiple specifications are performed, the last value will be the final value of the option.
 *
 * The function removes the extracted arguments from argc/argv.
 * The function returns 0 if 'name' already exists and is not a table and 1
 * in case of success.
 */
UTLLUAAPI int utl_export_args (lua_State* L, const char* name, int *pargc, char ***pargv);
/**
 * Exports to a global table named '[name].cmdoptions' the command line arguments in
 * the following way:
 * 
 * --varname true:  [name].cmdoptions.varname will have 'true' (boolean) as value
 * --varname false: [name].cmdoptions.varname will have 'false' (boolean) as value
 * --varname:       [name].cmdoptions.varname will have 'true' (boolean) as value
 * --varname 5:     [name].cmdoptions.varname will have '5' (number) as value
 * --varname text:  [name].cmdoptions.varname will have 'text' (string) as value
 *
 * The arguments listed in [which_are_multiple_n,which_are_multiple] (array with strings),
 * if specified, accept multiple specifications and will result in a table
 * { value1, value2, value3, ... } following the rules described above.
 *
 * The function removes the extracted arguments from argc/argv.
 * The function returns 0 if 'name' already exists and is not a table and 1
 * in case of success.
 */
UTLLUAAPI int utl_export_args_multiple (lua_State* L, const char* name, int *pargc, char ***pargv, int which_are_multiple_n, const char *which_are_multiple[]);
UTLLUAAPI int utl_getboolarg (lua_State* L, const char* name, const char *optname);

#ifdef __cplusplus
}
#endif

#endif

