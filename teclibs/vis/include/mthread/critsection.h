//* critsection.h
// Manages simple critical section mutual exclusion.
// vbarata@tecgraf.puc-rio.br
// Aug 2009

#ifndef MTHREAD_CRITICAL_SECTION_H
#define MTHREAD_CRITICAL_SECTION_H

#include "threaddefines.h"

#ifdef MTHREAD_USE_POSIX
# include "critsectionposix.h"
#endif

#ifdef MTHREAD_USE_JAVA
# include "critsectionjava.h"
#endif

#ifdef MTHREAD_USE_WIN
# include "critsectionwin.h"
#endif

#endif // MTHREAD_CRITICAL_SECTION_H
