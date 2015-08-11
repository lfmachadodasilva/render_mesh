//* autocritsection.h
// Automatic critical section based on RAII.
// vbarata@tecgraf.puc-rio.br
// Mar 2011

#ifndef MTHREAD_AUTOMATIC_CRITICAL_SECTION_H
#define MTHREAD_AUTOMATIC_CRITICAL_SECTION_H

//-----------------------------------//
// Includes and forward declarations //
//-----------------------------------//

#include "threaddefines.h"
#include "critsection.h"

//------------------//
// Class Definition //
//------------------//

// This class enters a specified critical section when an instance is
// created and automatically leaves it when the instance is destroyed.

class MTHREAD_API MtlAutoCritSection
{
public:

  // Constructor and Destructor

  MtlAutoCritSection (MtlCritSection& cs)
  : m_cs(cs)
  {
    m_cs.Enter();
  }

  ~MtlAutoCritSection ()
  {
    m_cs.Leave();
  }

private:

  // Forbid copy

  MtlAutoCritSection (const MtlAutoCritSection&);
  MtlAutoCritSection& operator = (const MtlAutoCritSection&);

private:
  MtlCritSection& m_cs;
};

#endif // MTHREAD_AUTOMATIC_CRITICAL_SECTION_H
