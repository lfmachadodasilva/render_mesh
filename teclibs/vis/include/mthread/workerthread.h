//* workerthread.h
// vbarata@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Aug 2010

#ifndef MTHREAD_WORKERTHREAD_H
#define MTHREAD_WORKERTHREAD_H

//-----------------------------------//
// Includes and Forward Declarations //
//-----------------------------------//

#include "thread.h"
#include "critsection.h"
#include "condvar.h"

#include <ds/array.h>

class MtlWorkerService;

//------------------//
// Class Definition //
//------------------//

// This class implements a thread that runs services only when
// requested and waits on a condition for new run requests.
//
// - Services can add and remove themselves at any time. Removing a service is
// asynchronous, it does not guarantee that the service stops immediately.
//
// - Creating an MtlWorkerThread automatically starts the worker thread,
// but it will immediately wait for new service run requests.
//
// - Destroying an MtlWorkerThread locks the current thread until the worker
// thread successfully terminates (it will still finish its current loop).

class MTHREAD_API MtlWorkerThread
{
public:

  // Constructor and Destructor

  MtlWorkerThread (const char* name = NULL);
  ~MtlWorkerThread ();

private:

  // Service Management

  void AddService (MtlWorkerService* service);
  bool RemService (MtlWorkerService* service);

  // Thread Control

  void RequestRun ();

  // Lifetime

  void Kill ();
  bool IsAlive ();

  // Forbid copy

  MtlWorkerThread (const MtlWorkerThread&) {}
  MtlWorkerThread& operator = (const MtlWorkerThread&) {return *this;}

  // Thread Main Function and Loop

  static void* ThreadMain (void* data);
  void ThreadLoop ();

private:

  friend class MtlWorkerService;

  DsArray<MtlWorkerService*> m_services;
  DsArray<MtlWorkerService*> m_servicesActive;

  MtlThread      m_thread;
  MtlCondVar     m_condition_run;
  MtlCondVar     m_condition_done;
  MtlCritSection m_cs_run;
  MtlCritSection m_cs_life;
  MtlCritSection m_cs_services;

  bool m_run;
  bool m_alive;
  bool m_servicesChanged;
  bool m_servicesRunning;

};

#endif // MTHREAD_WORKERTHREAD_H
