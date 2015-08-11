// arch.h
// File architeture manipulator. (Win32 & POSIX)
// Tecgraf/PUC-Rio
// earp@tecgraf.puc-rio.br
// Feb 2010

#ifndef USO_ARCH_H
#define USO_ARCH_H

#include "defines.h"

/*
 * Changes byte order
 */
USO_API void uso_ByteSwapD (unsigned char * b);

#define uso_ByteSwapDouble(x) uso_ByteSwapD((unsigned char*)(x))

#endif

