//* condvar.h
// Manages simple condition variable thread control.
// vbarata@tecgraf.puc-rio.br
// Aug 2009

#ifndef MTHREAD_CONDITION_VARIABLE_H
#define MTHREAD_CONDITION_VARIABLE_H

#include "threaddefines.h"

#ifdef MTHREAD_USE_POSIX
# include "condvarposix.h"
#endif

#ifdef MTHREAD_USE_JAVA
# include "condvarjava.h"
#endif

#ifdef MTHREAD_USE_WIN
# include "condvarwin.h"
#endif

#endif // MTHREAD_CONDITION_VARIABLE_H
