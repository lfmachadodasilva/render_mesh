//* threadposix.h
// Manages threads.
// Uses the Posix thread model.
// vbarata@tecgraf.puc-rio.br
// Jan 2010

#ifndef MTHREAD_THREAD_POSIX_H
#define MTHREAD_THREAD_POSIX_H

//-----------------------------------//
// Includes and forward declarations //
//-----------------------------------//

#include "threaddefines.h"
#include <pthread.h>

//------------------//
// Class Definition //
//------------------//

// This class represents a thread

class MTHREAD_API MtlThread
{
public:

  // Static Init and CleanUp

  static bool Init ();
  static void CleanUp ();

  // Constructor and destructor

  MtlThread ();
  ~MtlThread ();

  // Main Thread Function (internal - do not call directly)

  void ThreadMain ();

  // Thread management

  bool Start (MtlThreadMain mainfunc, void* argumentptr = NULL);
  bool Detach ();
  bool Stop (); // Dangerous!!!
  bool WaitCompletion (void** returnptr = NULL);
  static MtlThread* GetCurrent ();
  static void Sleep (unsigned int miliseconds);
  static void Exit (void* returnptr = NULL);

  // Thread name

  static void SetName (const char* name);
  static const char* GetName ();

private:

  // Forbid copy

  MtlThread (const MtlThread&) {}
  MtlThread& operator = (const MtlThread&) {return *this;}

private:
  pthread_t m_thread;
  MtlThreadMain m_mainfunc;  // Thread main function
  void* m_argumentptr;       // Thread argument pointer
  void* m_returnptr;         // Thread return pointer
};

#endif // MTHREAD_THREAD_POSIX_H
