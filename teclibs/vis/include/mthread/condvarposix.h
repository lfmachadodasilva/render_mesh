//* condvarposix.h
// Manages simple condition variable thread control.
// Uses the Posix thread model.
// vbarata@tecgraf.puc-rio.br
// Aug 2009

#ifndef MTHREAD_CONDITION_VARIABLE_POSIX_H
#define MTHREAD_CONDITION_VARIABLE_POSIX_H

//-----------------------------------//
// Includes and forward declarations //
//-----------------------------------//

#include "threaddefines.h"
#include "critsection.h"
#include <pthread.h>
#include <uso/clock.h>

//------------------//
// Class Definition //
//------------------//

// This class represents a condition variable for thread control.

class MTHREADH_API MtlCondVar
{
public:

  // Constructor and Destructor

  MtlCondVar ()
  {
  }

  ~MtlCondVar ()
  {
    pthread_cond_destroy(&m_condition);
  }

  void Init (MtlCritSection& critsection)
  {
    pthread_cond_init(&m_condition, NULL);
    m_pmutex = &critsection.m_mutex;
  }

  // Thread control

  void Wait ()
  {
    pthread_cond_wait(&m_condition, m_pmutex);
  }

  bool TimedWait (unsigned int miliseconds) // returns false if it times out
  {
    double systemtimeout = uso_gettime() + 0.001 * miliseconds;
    timespec timeout;
    timeout.tv_sec = (long)systemtimeout;
    timeout.tv_nsec = (long)(((double)1e9) * (systemtimeout - (double)timeout.tv_sec));
    return (pthread_cond_timedwait(&m_condition, m_pmutex, &timeout) == 0);
  }

  void Notify ()
  {
    pthread_cond_signal(&m_condition);
  }

  void NotifyAll ()
  {
    pthread_cond_broadcast(&m_condition);
  }

private:

  // Forbid copy

  MtlCondVar (const MtlCondVar&) {}
  MtlCondVar& operator = (const MtlCondVar&) {return *this;}

private:
  pthread_mutex_t* m_pmutex;
  pthread_cond_t m_condition;
};

#endif // MTHREAD_CONDITION_VARIABLE_POSIX_H
