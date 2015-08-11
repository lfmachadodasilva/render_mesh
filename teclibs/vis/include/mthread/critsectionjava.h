//* critsectionjava.h
// Manages simple critical section mutual exclusion.
// Uses the Java thread model.
// vbarata@tecgraf.puc-rio.br
// Aug 2009

#ifndef MTHREAD_CRITICAL_SECTION_JAVA_H
#define MTHREAD_CRITICAL_SECTION_JAVA_H

//-----------------------------------//
// Includes and forward declarations //
//-----------------------------------//

#include "threaddefines.h"

//------------------//
// Class Definition //
//------------------//

// This class guarantees thread mutual exclusion to a block of code.
// Just add 'Enter' when entering the code and 'Leave' when leaving it.

class MTHREAD_API MtlCritSection
{
public:

  // Constructor and Destructor

  MtlCritSection ();
  ~MtlCritSection ();

  // Thread control

  void Enter ();
  bool TryEnter ();
  void Leave ();

private:

  // Forbid copy

  MtlCritSection (const MtlCritSection&) {}
  MtlCritSection& operator = (const MtlCritSection&) {return *this;}

private:
  friend class MtlCondVar;
  int m_mutex;
};

#endif // MTHREAD_CRITICAL_SECTION_JAVA_H
