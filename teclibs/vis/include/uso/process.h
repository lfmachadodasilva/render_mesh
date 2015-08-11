#ifndef USO_PROCESS_H
#define USO_PROCESS_H

#include "defines.h"
#include <stdio.h>

typedef void (*USOProgramOutputCB)(const char* line, bool is_err, bool is_new, void* data);

USO_API int uso_execute (bool wait, bool hide, int argc, char** argv, const char *starting_directory);
USO_API int USOExecuteAndMonitorOutput (const char*        command,
                                        USOProgramOutputCB outputfunc,
                                        void*              outputfuncdata=NULL);
/**
 * Returns true if the dynamic link library 'dllname'.dll is found,
 * false otherwise.
 *
 * Note: do not pass the .dll extension of the library file.
 */
USO_API bool uso_dl_found (const char* dlname);
#ifdef WIN32
/**
 * Returns 'true' if program is running on a 64 bit windows and false otherwise.
 * This function works when running from a 32 bit program.
 */
USO_API bool uso_is_64_bit_windows ();
#endif

#endif

