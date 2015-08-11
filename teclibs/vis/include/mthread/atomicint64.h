//* atomicint64.h
// vbarata@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Mai 2009

#ifndef ATOMIC_INT64_H
#define ATOMIC_INT64_H

//-----------------------------------//
// Includes and Forward Declarations //
//-----------------------------------//

#include "atomicdefines.h"

#if defined ATOMIC_FORCE_MUTEXES
# define ATOMIC_USE_MUTEXES
#elif defined _WIN64 && WINVER >= 0x0600
#else
# pragma message ("Warning: AtomicInt64 using mutex implementation.")
# define ATOMIC_USE_MUTEXES
#endif
#ifdef ATOMIC_USE_MUTEXES
# include <mthread/critsection.h>
#endif

//------------------//
// Class Definition //
//------------------//

class ATOMIC_API AtomicInt64
{
public:

  // Constructor and Destructor

  AtomicInt64 (long long value = 0);
  ~AtomicInt64 ();

  // Atomic Thread-safe Methods

  void Set (long long new_value);
  long long Get ();
  long long GetAndSet (long long new_value);
  bool CompareAndSet (long long test_value, long long new_value);

  long long GetAndAdd (long long operand);
  long long GetAndIncrement ();
  long long GetAndDecrement ();

  long long AddAndGet (long long operand);
  long long IncrementAndGet ();
  long long DecrementAndGet ();

  void Add (long long operand);
  void Increment ();
  void Decrement ();

private:

  // Internal value

  long long m_value;

  // Platform-specific data

#ifdef ATOMIC_USE_MUTEXES
  MtlCritSection m_cs;
#elif defined _WIN32
#endif

};

#include "atomicint64.inl"

#undef ATOMIC_USE_MUTEXES

#endif // ATOMIC_INT64_H
