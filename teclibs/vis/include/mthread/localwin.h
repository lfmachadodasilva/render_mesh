//* localwin.h
// Manages thread-local data (thread-specific data).
// Uses the Windows thread model.
// vbarata@tecgraf.puc-rio.br
// Jan 2010

#ifndef MTHREAD_LOCAL_DATA_WINDOWS_H
#define MTHREAD_LOCAL_DATA_WINDOWS_H

//-----------------------------------//
// Includes and forward declarations //
//-----------------------------------//

#include "threaddefines.h"
#include <Windows.h>
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
    m_key = TlsAlloc();
    assert(m_key != TLS_OUT_OF_INDEXES);
  }

  ~MtlThreadLocal ()
  {
    BOOL success = TlsFree(m_key);
    assert(success == TRUE);
  }

  // Setter and Getter. Each stored value must be manually allocated prior to
  // Set() and manually freed prior to destroying the MtlThreadLocal object.

  bool Set (const TYPE value)
  {
    return (TlsSetValue(m_key, (LPVOID)value) == TRUE);
  }

  TYPE Get () const
  {
    TYPE value = (TYPE)TlsGetValue(m_key);
    assert(GetLastError() == ERROR_SUCCESS);
    return value;
  }

private:

  // Forbid copy

  MtlThreadLocal (const MtlThreadLocal&) {}
  MtlThreadLocal& operator = (const MtlThreadLocal&) {return *this;}

private:
  DWORD m_key;
};

#endif // MTHREAD_LOCAL_DATA_WINDOWS_H
