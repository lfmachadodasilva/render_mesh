//* thread.h
// Manages threads.
// vbarata@tecgraf.puc-rio.br
// Jan 2010

#ifndef MTHREAD_THREAD_H
#define MTHREAD_THREAD_H

#include "threaddefines.h"

//--------------------------------//
// Main Thread Function Signature //
//--------------------------------//

typedef void* (*MtlThreadMain) (void* arg);

//----------//
// Includes //
//----------//

#ifdef MTHREAD_USE_POSIX
# include "threadposix.h"
#endif

#ifdef MTHREAD_USE_JAVA
# include "threadjava.h"
#endif

#ifdef MTHREAD_USE_WIN
# include "threadwin.h"
#endif

#endif // MTHREAD_THREAD_H
