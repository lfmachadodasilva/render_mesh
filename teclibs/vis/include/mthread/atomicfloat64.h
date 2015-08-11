//* atomicfloat64.h
// vbarata@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Mai 2009

#ifndef ATOMIC_FLOAT64_H
#define ATOMIC_FLOAT64_H

//-----------------------------------//
// Includes and Forward Declarations //
//-----------------------------------//

#include "atomicdefines.h"

#if defined ATOMIC_FORCE_MUTEXES
# define ATOMIC_USE_MUTEXES
#elif defined _WIN64 && WINVER >= 0x0600
#else
# pragma message ("Warning: AtomicFloat64 using mutex implementation.")
# define ATOMIC_USE_MUTEXES
#endif
#ifdef ATOMIC_USE_MUTEXES
# include <mthread/critsection.h>
#endif

//------------------//
// Class Definition //
//------------------//

class ATOMIC_API AtomicFloat64
{
public:

  // Constructor and Destructor

  AtomicFloat64 (double value = 0.0);
  ~AtomicFloat64 ();

  // Atomic Thread-safe Methods

  void Set (double new_value);
  double Get ();
  double GetAndSet (double new_value);
  bool CompareAndSet (double test_value, double new_value);

  double GetAndAdd (double operand);

  double AddAndGet (double operand);

  void Add (double operand);

private:

  // Internal value

  double m_value;

  // Platform-specific data

#ifdef ATOMIC_USE_MUTEXES
  MtlCritSection m_cs;
#elif defined _WIN32
#endif

};

#include "atomicfloat64.inl"

#undef ATOMIC_USE_MUTEXES

#endif // ATOMIC_FLOAT64_H
