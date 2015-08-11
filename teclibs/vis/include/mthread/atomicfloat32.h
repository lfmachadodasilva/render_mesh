//* atomicfloat32.h
// vbarata@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Mai 2009

#ifndef ATOMIC_FLOAT32_H
#define ATOMIC_FLOAT32_H

//-----------------------------------//
// Includes and Forward Declarations //
//-----------------------------------//

#include "atomicdefines.h"

#if defined ATOMIC_FORCE_MUTEXES
# define ATOMIC_USE_MUTEXES
#elif defined _WIN32
#else
# pragma message ("Warning: AtomicFloat32 using mutex implementation.")
# define ATOMIC_USE_MUTEXES
#endif
#ifdef ATOMIC_USE_MUTEXES
# include <mthread/critsection.h>
#endif

//------------------//
// Class Definition //
//------------------//

class ATOMIC_API AtomicFloat32
{
public:

  // Constructor and Destructor

  AtomicFloat32 (float value = 0.0f);
  ~AtomicFloat32 ();

  // Atomic Thread-safe Methods

  void Set (float new_value);
  float Get ();
  float GetAndSet (float new_value);
  bool CompareAndSet (float test_value, float new_value);

  float GetAndAdd (float operand);

  float AddAndGet (float operand);

  void Add (float operand);

private:

  // Internal value

  float m_value;

  // Platform-specific data

#ifdef ATOMIC_USE_MUTEXES
  MtlCritSection m_cs;
#elif defined _WIN32
#endif

};

#include "atomicfloat32.inl"

#undef ATOMIC_USE_MUTEXES

#endif // ATOMIC_FLOAT32_H
