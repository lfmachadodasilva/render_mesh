// Windows Registry helper functions
// mark@tecgraf.puc-rio.br
// Mar 2000
#ifndef __REGISTRY__H_
#define __REGISTRY__H_

#include "defines.h"

/**
 * Obtains the value of regname\\regpath, record 'regvalue'.
 * regname  -> ex. HKEY_CURRENT_USER
 * regpath  -> ex. "Software\\Netscape\\Netscape Navigator\\biff"
 * regvalue -> ex. "CurrentUser"
 * Returns NULL in case no record is found.
 * The user must free the returned string.
 */
USO_API char *uso_read_registry (const char *regname, const char *regpath, const char *regvalue);
/**
 * Changes a registry. If it does not exist it creates a new one.
 * regname  -> ex. HKEY_CURRENT_USER
 * regpath  -> ex. "Software\\Netscape\\Netscape Navigator\\biff"
 * regvalue -> ex. "CurrentUser"
 * Returns true if successful.
 */
USO_API bool uso_change_registry(const char *regname, const char *regpath, const char *regvalue, const char *newvalue);
/**
 * Deletes a registry. 
 * regname  -> ex. HKEY_CURRENT_USER
 * regpath  -> ex. "Software\\Netscape\\Netscape Navigator\\biff"
 * regvalue -> ex. "SomeData"
 * Returns true if the registry was deleted or false if it did not exist or in
 * case of an error.
 */
USO_API bool uso_delete_registry(const char *regname, const char *regpath, const char *regvalue);

#endif
