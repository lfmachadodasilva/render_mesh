//* localposix.h
// Manages thread-local data (thread-specific data).
// Uses the Posix thread model.
// vbarata@tecgraf.puc-rio.br
// Jan 2010

#ifndef MTHREAD_LOCAL_DATA_POSIX_H
#define MTHREAD_LOCAL_DATA_POSIX_H

//-----------------------------------//
// Includes and forward declarations //
//-----------------------------------//

#include "threaddefines.h"
#include <pthread.h>
#include <assert.h>

//------------------//
// Class Definition //
//------------------//

// This class manages a value stored locally on each thread.
// Values must be pointers or types not larger than pointers.
// Note: Best performance is achieved by using values aligned to the size of
// a processor cache line to avoid cache contention by multiple threads. This
// size can be queried in run time with the CPUID assembly instruction (TODO).

// Example usage:
// {
//   /* Create MtlThreadLocal */
//   MtlThreadLocal<OBJECT*>* data = new MtlThreadLocal<OBJECT*>();
//   /* Allocate and store thread-specific data (on any thread) */
//   OBJECT* objptr1 = new OBJECT();
//   data.Set(objptr1);
//   /* Use thread-specific data (on any thread) */
//   OBJECT* objptr2 = data.Get();
//   objptr2->...
//   /* Delete and reset (optional) thread-specific data (on any thread) */
//   OBJECT* objptr3 = data.Get();
//   delete objptr3;
//   data.Set(NULL);
//   /* Delete MtlThreadLocal */
//   delete data;
// }

template <class TYPE>
class MTHREADH_API MtlThreadLocal
{
public:

  // Constructor and Destructor

  MtlThreadLocal ()
  {
    int err = pthread_key_create(&m_key, NULL);
    assert(err == 0);
  }

  ~MtlThreadLocal ()
  {
    int err = pthread_key_delete(m_key);
    assert(err == 0);
  }

  // Setter and Getter. Each stored value must be manually allocated prior to
  // Set() and manually freed prior to destroying the MtlThreadLocal object.

  bool Set (const TYPE value)
  {
    return (pthread_setspecific(m_key, (const void*)value) == 0);
  }

  TYPE Get () const
  {
    return (TYPE)pthread_getspecific(m_key);
  }

private:

  // Forbid copy

  MtlThreadLocal (const MtlThreadLocal&) {}
  MtlThreadLocal& operator = (const MtlThreadLocal&) {return *this;}

private:
  pthread_key_t m_key;
};

#endif // MTHREAD_LOCAL_DATA_POSIX_H
