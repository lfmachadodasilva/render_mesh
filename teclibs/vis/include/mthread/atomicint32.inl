//* atomicint32.inl
// vbarata@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Mai 2009

//----------//
// Includes //
//----------//

#ifdef ATOMIC_USE_MUTEXES
#elif defined _WIN32
# include <Windows.h>
#endif
#include <assert.h>

//----------------------------//
// Atomic Thread-safe Methods //
//----------------------------//

inline void AtomicInt32::Set (long new_value)
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  m_value = new_value;
  m_cs.Leave();
#elif defined _WIN32
  InterlockedExchange(&m_value, new_value);
#else
  assert(false && "AtomicInt32::Set() not supported on this platform");
#endif
}

inline long AtomicInt32::Get ()
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  long old_value = m_value;
  m_cs.Leave();
  return old_value;
#elif defined _WIN32
  long old_value = InterlockedCompareExchange(&m_value, (long)0, (long)0);
  return old_value;
#else
  assert(false && "AtomicInt32::Get() not supported on this platform");
  return (long)0;
#endif
}

inline long AtomicInt32::GetAndSet (long new_value)
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  long old_value = m_value;
  m_value = new_value;
  m_cs.Leave();
  return old_value;
#elif defined _WIN32
  long old_value = InterlockedExchange(&m_value, new_value);
  return old_value;
#else
  assert(false && "AtomicInt32::GetAndSet() not supported on this platform");
  return (long)0;
#endif
}

inline bool AtomicInt32::CompareAndSet (long test_value, long new_value)
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  bool test = (m_value == test_value);
  if (test)
    m_value = new_value;
  m_cs.Leave();
  return test;
#elif defined _WIN32
  long old_value = InterlockedCompareExchange(&m_value, new_value, test_value);
  return (old_value == test_value);
#else
  assert(false && "AtomicInt32::CompareAndSet() not supported on this platform");
  return false;
#endif
}

inline long AtomicInt32::GetAndAdd (long operand)
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  long old_value = m_value;
  m_value += operand;
  m_cs.Leave();
  return old_value;
#elif defined _WIN32
  long old_value = InterlockedExchangeAdd(&m_value, operand);
  return old_value;
#else
  assert(false && "AtomicInt32::GetAndAdd() not supported on this platform");
  return (long)0;
#endif
}

inline long AtomicInt32::GetAndIncrement ()
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  long old_value = m_value;
  ++m_value;
  m_cs.Leave();
  return old_value;
#elif defined _WIN32
  long new_value = InterlockedIncrement(&m_value);
  return (new_value-1);
#else
  assert(false && "AtomicInt32::GetAndIncrement() not supported on this platform");
  return (long)0;
#endif
}

inline long AtomicInt32::GetAndDecrement ()
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  long old_value = m_value;
  --m_value;
  m_cs.Leave();
  return old_value;
#elif defined _WIN32
  long new_value = InterlockedDecrement(&m_value);
  return (new_value+1);
#else
  assert(false && "AtomicInt32::GetAndDecrement() not supported on this platform");
  return (long)0;
#endif
}

inline long AtomicInt32::AddAndGet (long operand)
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  m_value += operand;
  long old_value = m_value;
  m_cs.Leave();
  return old_value;
#elif defined _WIN32
  long old_value = InterlockedExchangeAdd(&m_value, operand);
  return (old_value+operand);
#else
  assert(false && "AtomicInt32::AddAndGet() not supported on this platform");
  return (long)0;
#endif
}

inline long AtomicInt32::IncrementAndGet ()
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  long old_value = ++m_value;
  m_cs.Leave();
  return old_value;
#elif defined _WIN32
  long new_value = InterlockedIncrement(&m_value);
  return new_value;
#else
  assert(false && "AtomicInt32::IncrementAndGet() not supported on this platform");
  return (long)0;
#endif
}

inline long AtomicInt32::DecrementAndGet ()
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  long old_value = --m_value;
  m_cs.Leave();
  return old_value;
#elif defined _WIN32
  long new_value = InterlockedDecrement(&m_value);
  return new_value;
#else
  assert(false && "AtomicInt32::DecrementAndGet() not supported on this platform");
  return (long)0;
#endif
}

inline void AtomicInt32::Add (long operand)
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  m_value += operand;
  m_cs.Leave();
#elif defined _WIN32
  InterlockedExchangeAdd(&m_value, operand);
#else
  assert(false && "AtomicInt32::Add() not supported on this platform");
#endif
}

inline void AtomicInt32::Increment ()
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  ++m_value;
  m_cs.Leave();
#elif defined _WIN32
  InterlockedIncrement(&m_value);
#else
  assert(false && "AtomicInt32::Increment() not supported on this platform");
#endif
}

inline void AtomicInt32::Decrement ()
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  --m_value;
  m_cs.Leave();
#elif defined _WIN32
  InterlockedDecrement(&m_value);
#else
  assert(false && "AtomicInt32::Decrement() not supported on this platform");
#endif
}
