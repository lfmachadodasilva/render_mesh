//* critsectionposix.h
// Manages simple critical section mutual exclusion.
// Uses the Posix thread model.
// vbarata@tecgraf.puc-rio.br
// Aug 2009

#ifndef MTHREAD_CRITICAL_SECTION_POSIX_H
#define MTHREAD_CRITICAL_SECTION_POSIX_H

//-----------------------------------//
// Includes and forward declarations //
//-----------------------------------//

#include "threaddefines.h"
#include <pthread.h>

//------------------//
// Class Definition //
//------------------//

// This class guarantees thread mutual exclusion to a block of code.
// Just add 'Enter' when entering the code and 'Leave' when leaving it.

class MTHREADH_API MtlCritSection
{
public:

  // Constructor and Destructor

  MtlCritSection ()
  {
    pthread_mutex_init(&m_mutex, NULL);
  }

  ~MtlCritSection ()
  {
    pthread_mutex_destroy(&m_mutex);
  }

  // Thread control

  void Enter ()
  {
    pthread_mutex_lock(&m_mutex);
  }

  bool TryEnter ()
  {
    return (pthread_mutex_trylock(&m_mutex) == 0);
  }

  void Leave ()
  {
    pthread_mutex_unlock(&m_mutex);
  }

private:

  // Forbid copy

  MtlCritSection (const MtlCritSection&) {}
  MtlCritSection& operator = (const MtlCritSection&) {return *this;}

private:
  friend class MtlCondVar;
  pthread_mutex_t m_mutex;
};

#endif // MTHREAD_CRITICAL_SECTION_POSIX_H
