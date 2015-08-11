//* condvarwin.h
// Manages simple condition variable thread control.
// Uses the Windows thread model.
// Note: Condition variables are only supported since Vista / Server 2008.
//       For older systems, the implementation uses LOCKLESS events instead,
//       and Notify() behaves as NotifyAll().
// vbarata@tecgraf.puc-rio.br
// Aug 2009

#ifndef MTHREAD_CONDITION_VARIABLE_WINDOWS_H
#define MTHREAD_CONDITION_VARIABLE_WINDOWS_H

//-----------------------------------//
// Includes and forward declarations //
//-----------------------------------//

#include "threaddefines.h"
#include "critsection.h"
#include <Windows.h>

#if (WINVER > 0x0600) // Windows Vista or Windows Server 2008 (or newer)
# define MTHREAD_USE_WIN_CONDVAR
#endif

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
#ifdef MTHREAD_USE_WIN_CONDVAR
#else
    CloseHandle(m_event);
#endif
  }

  void Init (MtlCritSection& critsection)
  {
#ifdef MTHREAD_USE_WIN_CONDVAR
    InitializeConditionVariable(&m_condvar);
    m_pcritsection = &critsection.m_critsection
#else
    m_event = CreateEvent(NULL, FALSE, FALSE, NULL);
#endif
  }

  // Thread control

  void Wait ()
  {
#ifdef MTHREAD_USE_WIN_CONDVAR
    SleepConditionVariableCS(&m_condvar, m_pcritsection, INFINITE);
#else
    WaitForSingleObject(m_event, INFINITE);
#endif
  }

  bool TimedWait (unsigned int miliseconds) // returns false if it times out
  {
#ifdef MTHREAD_USE_WIN_CONDVAR
    return (SleepConditionVariableCS(&m_condvar, m_pcritsection, (DWORD)miliseconds) != 0);
#else
    return (WaitForSingleObject(m_event, (DWORD)miliseconds) == 0);
#endif
  }

  void Notify ()
  {
#ifdef MTHREAD_USE_WIN_CONDVAR
    WakeConditionVariable(&m_condvar);
#else
    SetEvent(m_event);
#endif
  }

  void NotifyAll ()
  {
#ifdef MTHREAD_USE_WIN_CONDVAR
    WakeAllConditionVariable(&m_condvar);
#else
    SetEvent(m_event);
#endif
  }

private:

  // Forbid copy

  MtlCondVar (const MtlCondVar&) {}
  MtlCondVar& operator = (const MtlCondVar&) {return *this;}

private:
#ifdef MTHREAD_USE_WIN_CONDVAR
  CRITICAL_SECTION* m_pcritsection;
  CONDITION_VARIABLE m_condvar;
#else
  HANDLE m_event;
#endif
};

#endif // MTHREAD_CONDITION_VARIABLE_WINDOWS_H
