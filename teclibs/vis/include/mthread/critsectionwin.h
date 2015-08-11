//* critsectionwin.h
// Manages simple critical section mutual exclusion.
// Uses the Windows thread model.
// Note: TryEnterCriticalSection() is not supported on all Windows versions.
// vbarata@tecgraf.puc-rio.br
// Aug 2009

#ifndef MTHREAD_CRITICAL_SECTION_WINDOWS_H
#define MTHREAD_CRITICAL_SECTION_WINDOWS_H

//-----------------------------------//
// Includes and forward declarations //
//-----------------------------------//

#include "threaddefines.h"
#include <Windows.h>
#include <process.h>

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
    InitializeCriticalSection(&m_critsection);
  }

  ~MtlCritSection ()
  {
    DeleteCriticalSection(&m_critsection);
  }

  // Thread control

  void Enter ()
  {
    EnterCriticalSection(&m_critsection);
  }

  bool TryEnter ()
  {
#if(_WIN32_WINNT >= 0x0400)
    return (TryEnterCriticalSection(&m_critsection) == TRUE);
#else
    return false; // Unsupported
#endif
  }

  void Leave ()
  {
    LeaveCriticalSection(&m_critsection);
  }

private:

  // Forbid copy

  MtlCritSection (const MtlCritSection&) {}
  MtlCritSection& operator = (const MtlCritSection&) {return *this;}

private:
  friend class MtlCondVar;
  CRITICAL_SECTION m_critsection;
};

#endif // MTHREAD_CRITICAL_SECTION_WINDOWS_H
