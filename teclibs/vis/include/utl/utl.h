// Generic utilities library
// Main header
// fabraham@tecgraf.puc-rio.br
// Jul 2005
#ifndef UTL_H
#define UTL_H

#include <utl/debug.h>
#include <utl/writer.h>
#include <utl/writers/luafilewriter.h>

/**
 * Formats and throws an error message.
 * Syntax works exactly like *printf.
 * Note: This function cannot be used from multiple threads.
 */
void UtlThrowError (const char* format, ...) throw(const char*);
/**
 * Converts a string to an integer. If successful, value is returned on *ret and function returns true.
 * Function returns false otherwise.
 */
bool UtlStringToInt (const char* str, int* ret);
/**
 * Converts a string to a float number. If successful, value is returned on *ret and function returns true.
 * Function returns false otherwise.
 */
bool UtlStringToFloat (const char* str, float* ret);
/**
 * Converts a string to a double number. If successful, value is returned on *ret and function returns true.
 * Function returns false otherwise.
 */
bool UtlStringToDouble (const char* str, double* ret);

#endif

