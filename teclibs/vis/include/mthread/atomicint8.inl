//* atomicint8.inl
// vbarata@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Mai 2009

//----------//
// Includes //
//----------//

#ifdef ATOMIC_USE_MUTEXES
#elif defined _WIN32
# define _interlockedbittestandset workaround_ms_header_conflict_ibittestandset
# define _interlockedbittestandreset workaround_ms_header_conflict_ibittestandreset
# include <intrin.h>
# undef _interlockedbittestandset
# undef _interlockedbittestandreset
# pragma intrinsic(_InterlockedAnd8)
#endif
#include <assert.h>

//----------------------------//
// Atomic Thread-safe Methods //
//----------------------------//

inline void AtomicInt8::Set (char new_value)
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  m_value = new_value;
  m_cs.Leave();
#else
  assert(false && "AtomicInt8::Set() not supported on this platform");
#endif
}

inline char AtomicInt8::Get ()
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  char old_value = m_value;
  m_cs.Leave();
  return old_value;
#elif defined _WIN32
  char old_value = _InterlockedAnd8(&m_value, (char)0x01);
  return old_value;
#else
  assert(false && "AtomicInt8::Get() not supported on this platform");
  return (char)0;
#endif
}

inline char AtomicInt8::GetAndSet (char new_value)
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  char old_value = m_value;
  m_value = new_value;
  m_cs.Leave();
  return old_value;
#else
  assert(false && "AtomicInt8::GetAndSet() not supported on this platform");
  return (char)0;
#endif
}

inline bool AtomicInt8::CompareAndSet (char test_value, char new_value)
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  bool test = (m_value == test_value);
  if (test)
    m_value = new_value;
  m_cs.Leave();
  return test;
#else
  assert(false && "AtomicInt8::CompareAndSet() not supported on this platform");
  return false;
#endif
}

inline char AtomicInt8::GetAndAdd (char operand)
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  char old_value = m_value;
  m_value += operand;
  m_cs.Leave();
  return old_value;
#else
  assert(false && "AtomicInt8::GetAndAdd() not supported on this platform");
  return (char)0;
#endif
}

inline char AtomicInt8::GetAndIncrement ()
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  char old_value = m_value;
  ++m_value;
  m_cs.Leave();
  return old_value;
#else
  assert(false && "AtomicInt8::GetAndIncrement() not supported on this platform");
  return (char)0;
#endif
}

inline char AtomicInt8::GetAndDecrement ()
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  char old_value = m_value;
  --m_value;
  m_cs.Leave();
  return old_value;
#else
  assert(false && "AtomicInt8::GetAndDecrement() not supported on this platform");
  return (char)0;
#endif
}

inline char AtomicInt8::AddAndGet (char operand)
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  m_value += operand;
  char old_value = m_value;
  m_cs.Leave();
  return old_value;
#else
  assert(false && "AtomicInt8::AddAndGet() not supported on this platform");
  return (char)0;
#endif
}

inline char AtomicInt8::IncrementAndGet ()
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  char old_value = ++m_value;
  m_cs.Leave();
  return old_value;
#else
  assert(false && "AtomicInt8::IncrementAndGet() not supported on this platform");
  return (char)0;
#endif
}

inline char AtomicInt8::DecrementAndGet ()
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  char old_value = --m_value;
  m_cs.Leave();
  return old_value;
#else
  assert(false && "AtomicInt8::DecrementAndGet() not supported on this platform");
  return (char)0;
#endif
}

inline void AtomicInt8::Add (char operand)
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  m_value += operand;
  m_cs.Leave();
#else
  assert(false && "AtomicInt8::Add() not supported on this platform");
#endif
}

inline void AtomicInt8::Increment ()
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  ++m_value;
  m_cs.Leave();
#else
  assert(false && "AtomicInt8::Increment() not supported on this platform");
#endif
}

inline void AtomicInt8::Decrement ()
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  --m_value;
  m_cs.Leave();
#else
  assert(false && "AtomicInt8::Decrement() not supported on this platform");
#endif
}
