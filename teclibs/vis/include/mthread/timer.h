//* timer.h
// vbarata@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Oct 2008

#ifndef MTHREAD_TIMER_H
#define MTHREAD_TIMER_H

//-----------------------------------//
// Includes and forward declarations //
//-----------------------------------//

#include "thread.h"
#include "critsection.h"
#include "condvar.h"

//----------//
// Typedefs //
//----------//

typedef void (*MtlTimerCallback) (void* data);

//------------------//
// Class Definition //
//------------------//

// This class implements a timer that runs a callback on its own thread
// It provides methods to:
// - Start, stop and (un)pause the timer
// - Set the delay after the timer is started and before the first callback call
// - Set the delay between two consecutive callback calls
// - Set the number of times the callback is called each time the timer is started
// - Block and unblock the timer, which prevents the callback from executing
//   without affecting the first execution delay or the execution counter
// There are no busy waits, only sleeps and waits on conditions

class MTHREAD_API MtlTimer
{
public:

  // Constructor and Destructor

  MtlTimer (const char* name = NULL);
  virtual ~MtlTimer ();

  // Setters and Getters

  virtual void SetTimerCallback (MtlTimerCallback cb, void* data);

  void SetInterval (int miliseconds);
  int GetInterval ();

  void SetStartDelay (int miliseconds);
  int GetStartDelay ();

  void SetCounterMax (int count);
  int GetCounterMax ();

  // Block Control Methods
  // (unblocking does not reset the counter or apply the start delay)

  virtual void Block ();
  virtual void Unblock ();
  virtual void SwitchBlock ();

  virtual bool IsBlocked ();
   
  // Timer Control Methods
  // (starting or unpausing resets the counter and applies the start delay)

  virtual void Start ();
  virtual void Stop ();
  virtual void Pause ();

  virtual bool IsRunning ();

protected:

  // Lifetime

  virtual void Kill ();
  virtual bool IsAlive ();

  // Timer Thread Loop

  virtual void ThreadLoop ();

private:

  // Forbid copy

  MtlTimer (const MtlTimer&) {}
  MtlTimer& operator = (const MtlTimer&) {return *this;}

  // Static Thread Main Function

  static void* ThreadMain (void* data);

private:
  
  MtlTimerCallback m_callback;
  void* m_data;

  MtlThread      m_thread;
  MtlCondVar     m_condition_run;
  MtlCritSection m_cs_run;
  MtlCritSection m_cs_config;
  MtlCritSection m_cs_life;

  int m_delay_start;
  int m_interval;
  int m_count;
  int m_count_max;
  bool m_starting;
  bool m_blocked;
  bool m_running;
  bool m_alive;

};

#endif // MTHREAD_TIMER_H
