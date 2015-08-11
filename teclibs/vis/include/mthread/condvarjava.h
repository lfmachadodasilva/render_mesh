//* condvarjava.h
// Manages simple condition variable thread control.
// Uses the Java thread model.
// vbarata@tecgraf.puc-rio.br
// Aug 2009

#ifndef MTHREAD_CONDITION_VARIABLE_JAVA_H
#define MTHREAD_CONDITION_VARIABLE_JAVA_H

//-----------------------------------//
// Includes and forward declarations //
//-----------------------------------//

#include "threaddefines.h"
#include "critsection.h"

class MtlCritSection;

//------------------//
// Class Definition //
//------------------//

// This class represents a condition variable for thread control.

class MTHREAD_API MtlCondVar
{
public:

  // Constructor and Destructor

  MtlCondVar ();
  ~MtlCondVar ();

  void Init (MtlCritSection& critsection);

  // Thread control

  void Wait ();
  bool TimedWait (unsigned int miliseconds); // returns false if it times out
  void Notify ();
  void NotifyAll ();

private:

  // Forbid copy

  MtlCondVar (const MtlCondVar&) {}
  MtlCondVar& operator = (const MtlCondVar&) {return *this;}

private:
  int m_mutex;
  int m_condition;
};

#endif // MTHREAD_CONDITION_VARIABLE_JAVA_H
