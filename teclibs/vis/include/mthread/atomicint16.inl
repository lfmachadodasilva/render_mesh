//* atomicint16.inl
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
# pragma intrinsic(_InterlockedIncrement16)
# pragma intrinsic(_InterlockedDecrement16)
# pragma intrinsic(_InterlockedCompareExchange16)
#endif
#include <assert.h>

//----------------------------//
// Atomic Thread-safe Methods //
//----------------------------//

inline void AtomicInt16::Set (short new_value)
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  m_value = new_value;
  m_cs.Leave();
#else
  assert(false && "AtomicInt16::Set() not supported on this platform");
#endif
}

inline short AtomicInt16::Get ()
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  short old_value = m_value;
  m_cs.Leave();
  return old_value;
#elif defined _WIN32
  short old_value = _InterlockedCompareExchange16(&m_value, (short)0, (short)0);
  return old_value;
#else
  assert(false && "AtomicInt16::Get() not supported on this platform");
  return (short)0;
#endif
}

inline short AtomicInt16::GetAndSet (short new_value)
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  short old_value = m_value;
  m_value = new_value;
  m_cs.Leave();
  return old_value;
#else
  assert(false && "AtomicInt16::GetAndSet() not supported on this platform");
  return (short)0;
#endif
}

inline bool AtomicInt16::CompareAndSet (short test_value, short new_value)
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  bool test = (m_value == test_value);
  if (test)
    m_value = new_value;
  m_cs.Leave();
  return test;
#elif defined _WIN32
  short old_value = _InterlockedCompareExchange16(&m_value, new_value, test_value);
  return (old_value == test_value);
#else
  assert(false && "AtomicInt16::CompareAndSet() not supported on this platform");
  return false;
#endif
}

inline short AtomicInt16::GetAndAdd (short operand)
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  short old_value = m_value;
  m_value += operand;
  m_cs.Leave();
  return old_value;
#else
  assert(false && "AtomicInt16::GetAndAdd() not supported on this platform");
  return (short)0;
#endif
}

inline short AtomicInt16::GetAndIncrement ()
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  short old_value = m_value;
  ++m_value;
  m_cs.Leave();
  return old_value;
#elif defined _WIN32
  short new_value = _InterlockedIncrement16(&m_value);
  return (new_value-1);
#else
  assert(false && "AtomicInt16::GetAndIncrement() not supported on this platform");
  return (short)0;
#endif
}

inline short AtomicInt16::GetAndDecrement ()
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  short old_value = m_value;
  --m_value;
  m_cs.Leave();
  return old_value;
#elif defined _WIN32
  short new_value = _InterlockedDecrement16(&m_value);
  return (new_value+1);
#else
  assert(false && "AtomicInt16::GetAndDecrement() not supported on this platform");
  return (short)0;
#endif
}

inline short AtomicInt16::AddAndGet (short operand)
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  m_value += operand;
  short old_value = m_value;
  m_cs.Leave();
  return old_value;
#else
  assert(false && "AtomicInt16::AddAndGet() not supported on this platform");
  return (short)0;
#endif
}

inline short AtomicInt16::IncrementAndGet ()
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  short old_value = ++m_value;
  m_cs.Leave();
  return old_value;
#elif defined _WIN32
  short new_value = _InterlockedIncrement16(&m_value);
  return new_value;
#else
  assert(false && "AtomicInt16::IncrementAndGet() not supported on this platform");
  return (short)0;
#endif
}

inline short AtomicInt16::DecrementAndGet ()
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  short old_value = --m_value;
  m_cs.Leave();
  return old_value;
#elif defined _WIN32
  short new_value = _InterlockedDecrement16(&m_value);
  return new_value;
#else
  assert(false && "AtomicInt16::DecrementAndGet() not supported on this platform");
  return (short)0;
#endif
}

inline void AtomicInt16::Add (short operand)
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  m_value += operand;
  m_cs.Leave();
#else
  assert(false && "AtomicInt16::Add() not supported on this platform");
#endif
}

inline void AtomicInt16::Increment ()
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  ++m_value;
  m_cs.Leave();
#elif defined _WIN32
  _InterlockedIncrement16(&m_value);
#else
  assert(false && "AtomicInt16::Increment() not supported on this platform");
#endif
}

inline void AtomicInt16::Decrement ()
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  --m_value;
  m_cs.Leave();
#elif defined _WIN32
  _InterlockedDecrement16(&m_value);
#else
  assert(false && "AtomicInt16::Decrement() not supported on this platform");
#endif
}
