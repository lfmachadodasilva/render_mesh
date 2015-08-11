// date.h
// Date and time utilities.
// fabraham@tecgraf.puc-rio.br
// vbarata@tecgraf.puc-rio.br
// May 2011
#ifndef UTL_DATE_H
#define UTL_DATE_H

#include "defines.h"

/**
 * Formats 'dt' in a readable way: if its a number of milliseconds,
 * formats 'X ms'. if a number of seconds, shows in seconds. also deals
 * with minutes and hours.
 */
UTL_API void utlFormatTime (char* out, double dt);

#endif

