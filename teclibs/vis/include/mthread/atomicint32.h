//* atomicint32.h
// vbarata@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Mai 2009

#ifndef ATOMIC_INT32_H
#define ATOMIC_INT32_H

//-----------------------------------//
// Includes and Forward Declarations //
//-----------------------------------//

#include "atomicdefines.h"

#if defined ATOMIC_FORCE_MUTEXES
# define ATOMIC_USE_MUTEXES
#elif defined _WIN32
#else
# pragma message ("Warning: AtomicInt32 using mutex implementation.")
# define ATOMIC_USE_MUTEXES
#endif
#ifdef ATOMIC_USE_MUTEXES
# include <mthread/critsection.h>
#endif

//------------------//
// Class Definition //
//------------------//

class ATOMIC_API AtomicInt32
{
public:

  // Constructor and Destructor

  AtomicInt32 (long value = 0);
  ~AtomicInt32 ();

  // Atomic Thread-safe Methods

  void Set (long new_value);
  long Get ();
  long GetAndSet (long new_value);
  bool CompareAndSet (long test_value, long new_value);

  long GetAndAdd (long operand);
  long GetAndIncrement ();
  long GetAndDecrement ();

  long AddAndGet (long operand);
  long IncrementAndGet ();
  long DecrementAndGet ();

  void Add (long operand);
  void Increment ();
  void Decrement ();

private:

  // Internal value

  long m_value;

  // Platform-specific data

#ifdef ATOMIC_USE_MUTEXES
  MtlCritSection m_cs;
#elif defined _WIN32
#endif

};

#include "atomicint32.inl"

#undef ATOMIC_USE_MUTEXES

#endif // ATOMIC_INT32_H
