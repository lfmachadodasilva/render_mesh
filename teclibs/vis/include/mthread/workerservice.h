//* workerservice.h
// vbarata@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Aug 2010

#ifndef MTHREAD_WORKERSERVICE_H
#define MTHREAD_WORKERSERVICE_H

//-----------------------------------//
// Includes and Forward Declarations //
//-----------------------------------//

#include "critsection.h"
#include "condvar.h"

class MtlWorkerThread;

//------------------//
// Class Definition //
//------------------//

// This class implements a service that runs
// on a worker thread, only when requested.
//
// - Anyone can request that a service be run anytime.
//
// - Multiple requests are coalesced into a single one.
//
// - Destroying an MtlWorkerService locks the current thread until the
// service successfully terminates (it will still finish its current loop
// and remove itself from the worker thread).

class MTHREAD_API MtlWorkerService
{
public:

  // Constructor and Destructor

  MtlWorkerService ();
  virtual ~MtlWorkerService ();

  // Thread

  void SetThread (MtlWorkerThread* thread);

  // Service Control

  virtual void RequestRun ();
  virtual void Finalize ();

protected:

  // Thread

  MtlWorkerThread* GetThread ();  // To be called inside ServiceLoop() only

private:

  // Forbid copy

  MtlWorkerService (const MtlWorkerService&) {}
  MtlWorkerService& operator = (const MtlWorkerService&) {return *this;}

  // Service Control

  void RunService ();
  bool MustRun ();
  void DoneRun ();

  // Lifetime

  void ThreadKilled ();

  // Service Main (Loop) Function

  virtual void ServiceLoop () = 0; // Implement the service here

private:

  friend class MtlWorkerThread;

  MtlWorkerThread* m_curthread;
  MtlWorkerThread* m_nextthread;
  MtlCondVar     m_condition_done;
  MtlCritSection m_cs_thread;
  MtlCritSection m_cs_run;
  bool m_mustrun;
  bool m_running;

};

#endif // MTHREAD_WORKERSERVICE_H
