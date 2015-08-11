// directory.h
// Portable directory manipulator. (Win32 & POSIX)
// Tecgraf/PUC-Rio
// Nov 2005

#ifndef USO_DIRECTORY_H
#define USO_DIRECTORY_H

#include "defines.h"

#define USO_DIR_ERROR_EXISTS         1
#define USO_DIR_ERROR_PATH_NOT_FOUND 2
#define USO_DIR_ERROR_DIR_NOT_EMPTY  3
#define USO_DIR_ERROR_PERM_DENIED    4
#define USO_DIR_UNKNOWN_ERROR        5

// just for backwards compatibility
#define USO_MKDIR_ERROR_EXISTS         USO_DIR_ERROR_EXISTS
#define USO_MKDIR_ERROR_PATH_NOT_FOUND USO_DIR_ERROR_PATH_NOT_FOUND

/**
 * Tries to create directory 'dirname' (can be a path relative to the current directory).
 * Returns 0 if successful.
 * Returns the following error codes otherwise:
 *   USO_DIR_ERROR_EXISTS: Path already exists.
 *   USO_DIR_ERROR_PATH_NOT_FOUND: One or more intermediate directories do not exist.
 *   USO_DIR_UNKNOWN_ERROR: Unknown error.
 */
USO_API int uso_create_directory (const char *dirname);

/**
 * Tries to create directory 'dirname' (can be a path relative to the current
 * directory), creating all intermediate directories.
 * Returns 0 if successful.
 * Returns the following error codes otherwise:
 *   USO_DIR_ERROR_EXISTS: Path already exists.
 *   USO_DIR_ERROR_PATH_NOT_FOUND: Could not create one or more intermediate directories.
 */
USO_API int uso_create_directory_p (const char *dirname);

/**
* Tries to remove the directory 'dirname' (can be a path relative to the current directory).
* The directory must be empty.
* Returns 0 if successful.
* Returns the following error codes otherwise:
*   USO_DIR_ERROR_PATH_NOT_FOUND: One or more intermediate directories do not exist.
*   USO_DIR_ERROR_PERM_DENIED: Cannot remove directory. Permition denied.
*   USO_DIR_ERROR_DIR_NOT_EMPTY: Cannot remove directory. Directory not empty.
*/
USO_API int uso_remove_directory (const char *dirname);

#endif
