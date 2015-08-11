//* atomicint16.h
// vbarata@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Mai 2009

#ifndef ATOMIC_INT16_H
#define ATOMIC_INT16_H

//-----------------------------------//
// Includes and Forward Declarations //
//-----------------------------------//

#include "atomicdefines.h"

#if defined ATOMIC_FORCE_MUTEXES
# define ATOMIC_USE_MUTEXES
#elif defined _WIN32
#else
# pragma message ("Warning: AtomicInt16 using mutex implementation.")
# define ATOMIC_USE_MUTEXES
#endif
#ifdef ATOMIC_USE_MUTEXES
# include <mthread/critsection.h>
#endif

//------------------//
// Class Definition //
//------------------//

class ATOMIC_API AtomicInt16
{
public:

  // Constructor and Destructor

  AtomicInt16 (short value = 0);
  ~AtomicInt16 ();

  // Atomic Thread-safe Methods

  void Set (short new_value);
  short Get ();
  short GetAndSet (short new_value);
  bool CompareAndSet (short test_value, short new_value);

  short GetAndAdd (short operand);
  short GetAndIncrement ();
  short GetAndDecrement ();

  short AddAndGet (short operand);
  short IncrementAndGet ();
  short DecrementAndGet ();

  void Add (short operand);
  void Increment ();
  void Decrement ();

private:

  // Internal value

  short m_value;

  // Platform-specific data

#ifdef ATOMIC_USE_MUTEXES
  MtlCritSection m_cs;
#elif defined _WIN32
#endif

};

#include "atomicint16.inl"

#undef ATOMIC_USE_MUTEXES

#endif // ATOMIC_INT16_H
