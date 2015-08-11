//* atomicpointer.h
// vbarata@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Mai 2009

#ifndef ATOMIC_POINTER_H
#define ATOMIC_POINTER_H

//-----------------------------------//
// Includes and Forward Declarations //
//-----------------------------------//

#include "atomicdefines.h"

#if defined ATOMIC_FORCE_MUTEXES
# define ATOMIC_USE_MUTEXES
#elif defined _WIN32
#else
# pragma message ("Warning: AtomicPointer using mutex implementation.")
# define ATOMIC_USE_MUTEXES
#endif
#ifdef ATOMIC_USE_MUTEXES
# include <mthread/critsection.h>
#endif

//------------------//
// Class Definition //
//------------------//

template <class TYPE>
class ATOMICH_API AtomicPointer
{
public:

  // Constructor and Destructor

  AtomicPointer (TYPE* value = NULL);
  ~AtomicPointer ();

  // Atomic Thread-safe Methods

  void Set (TYPE* new_value);
  TYPE* Get ();
  TYPE* GetAndSet (TYPE* new_value);
  bool CompareAndSet (TYPE* test_value, TYPE* new_value);

private:

  // Internal value

  TYPE* m_value;

  // Platform-specific data

#ifdef ATOMIC_USE_MUTEXES
  MtlCritSection m_cs;
#elif defined _WIN32
#endif

};

#include "atomicpointer.inl"

#undef ATOMIC_USE_MUTEXES

#endif // ATOMIC_POINTER_H
