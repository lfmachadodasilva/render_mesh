//* atomicint8.h
// vbarata@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Mai 2009

#ifndef ATOMIC_INT8_H
#define ATOMIC_INT8_H

//-----------------------------------//
// Includes and Forward Declarations //
//-----------------------------------//

#include "atomicdefines.h"

#if defined ATOMIC_FORCE_MUTEXES
# define ATOMIC_USE_MUTEXES
#elif 0//defined _WIN32
#else
# pragma message ("Warning: AtomicInt8 using mutex implementation.")
# define ATOMIC_USE_MUTEXES
#endif
#ifdef ATOMIC_USE_MUTEXES
# include <mthread/critsection.h>
#endif

//------------------//
// Class Definition //
//------------------//

class ATOMIC_API AtomicInt8
{
public:

  // Constructor and Destructor

  AtomicInt8 (char value = 0);
  ~AtomicInt8 ();

  // Atomic Thread-safe Methods

  void Set (char new_value);
  char Get ();
  char GetAndSet (char new_value);
  bool CompareAndSet (char test_value, char new_value);

  char GetAndAdd (char operand);
  char GetAndIncrement ();
  char GetAndDecrement ();

  char AddAndGet (char operand);
  char IncrementAndGet ();
  char DecrementAndGet ();

  void Add (char operand);
  void Increment ();
  void Decrement ();

private:

  // Internal value

  char m_value;

  // Platform-specific data

#ifdef ATOMIC_USE_MUTEXES
  MtlCritSection m_cs;
#elif defined _WIN32
#endif

};

#include "atomicint8.inl"

#undef ATOMIC_USE_MUTEXES

#endif // ATOMIC_INT8_H
