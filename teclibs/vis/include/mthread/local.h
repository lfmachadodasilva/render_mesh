//* local.h
// Manages thread-local data (thread-specific data).
// vbarata@tecgraf.puc-rio.br
// Jan 2010

#ifndef MTHREAD_LOCAL_DATA_H
#define MTHREAD_LOCAL_DATA_H

#include "threaddefines.h"

#ifdef MTHREAD_USE_POSIX
# include "localposix.h"
#endif

#ifdef MTHREAD_USE_JAVA
# include "localjava.h"
#endif

#ifdef MTHREAD_USE_WIN
# include "localwin.h"
#endif

#endif // MTHREAD_LOCAL_DATA_H
