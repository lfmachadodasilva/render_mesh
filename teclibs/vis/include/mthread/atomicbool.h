//* atomicbool.h
// vbarata@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Mai 2009

#ifndef ATOMIC_BOOL_H
#define ATOMIC_BOOL_H

//-----------------------------------//
// Includes and Forward Declarations //
//-----------------------------------//

#include "atomicdefines.h"

#if defined ATOMIC_FORCE_MUTEXES
# define ATOMIC_USE_MUTEXES
#elif defined _WIN32
#else
# pragma message ("Warning: AtomicBool using mutex implementation.")
# define ATOMIC_USE_MUTEXES
#endif
#ifdef ATOMIC_USE_MUTEXES
# include <mthread/critsection.h>
#endif

//------------------//
// Class Definition //
//------------------//

class ATOMIC_API AtomicBool
{
public:

  // Constructor and Destructor

  AtomicBool (bool value = false);
  ~AtomicBool ();

  // Atomic Thread-safe Methods

  void Set (bool new_value);
  bool Get ();
  bool GetAndSet (bool new_value);
  bool CompareAndSet (bool test_value, bool new_value);

  void Not ();
  void And (bool operand);
  void Or (bool operand);
  void Xor (bool operand);

  bool GetAndNot ();
  bool GetAndAnd (bool operand);
  bool GetAndOr (bool operand);
  bool GetAndXor (bool operand);

  bool NotAndGet ();
  bool AndAndGet (bool operand);
  bool OrAndGet (bool operand);
  bool XorAndGet (bool operand);

private:

  // Internal value

  bool m_value;

  // Platform-specific data

#ifdef ATOMIC_USE_MUTEXES
  MtlCritSection m_cs;
#elif defined _WIN32
#endif

};

#include "atomicbool.inl"

#undef ATOMIC_USE_MUTEXES

#endif // ATOMIC_BOOL_H
