//* atomicint64.inl
// vbarata@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Mai 2009

//----------//
// Includes //
//----------//

#ifdef ATOMIC_USE_MUTEXES
#elif defined _WIN64
# include <Windows.h>
#endif
#include <assert.h>

//----------------------------//
// Atomic Thread-safe Methods //
//----------------------------//

inline void AtomicInt64::Set (long long new_value)
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  m_value = new_value;
  m_cs.Leave();
#elif defined _WIN64
  InterlockedExchange64(&m_value, new_value);
#else
  assert(false && "AtomicInt64::Set() not supported on this platform");
#endif
}

inline long long AtomicInt64::Get ()
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  long long old_value = m_value;
  m_cs.Leave();
  return old_value;
#elif defined _WIN64
  long long old_value = InterlockedCompareExchange64(&m_value, (long long)0, (long long)0);
  return old_value;
#else
  assert(false && "AtomicInt64::Get() not supported on this platform");
  return (long long)0;
#endif
}

inline long long AtomicInt64::GetAndSet (long long new_value)
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  long long old_value = m_value;
  m_value = new_value;
  m_cs.Leave();
  return old_value;
#elif defined _WIN64
  long long old_value = InterlockedExchange64(&m_value, new_value);
  return old_value;
#else
  assert(false && "AtomicInt64::GetAndSet() not supported on this platform");
  return (long long)0;
#endif
}

inline bool AtomicInt64::CompareAndSet (long long test_value, long long new_value)
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  bool test = (m_value == test_value);
  if (test)
    m_value = new_value;
  m_cs.Leave();
  return test;
#elif defined _WIN64
  long long old_value = InterlockedCompareExchange(&m_value, new_value, test_value);
  return (old_value == test_value);
#else
  assert(false && "AtomicInt64::CompareAndSet() not supported on this platform");
  return false;
#endif
}

inline long long AtomicInt64::GetAndAdd (long long operand)
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  long long old_value = m_value;
  m_value += operand;
  m_cs.Leave();
  return old_value;
#elif defined _WIN64
  long long old_value = InterlockedExchangeAdd64(&m_value, operand);
  return old_value;
#else
  assert(false && "AtomicInt64::GetAndAdd() not supported on this platform");
  return (long long)0;
#endif
}

inline long long AtomicInt64::GetAndIncrement ()
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  long long old_value = m_value;
  ++m_value;
  m_cs.Leave();
  return old_value;
#elif defined _WIN64
  long long new_value = InterlockedIncrement64(&m_value);
  return (new_value-1);
#else
  assert(false && "AtomicInt64::GetAndIncrement() not supported on this platform");
  return (long long)0;
#endif
}

inline long long AtomicInt64::GetAndDecrement ()
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  long long old_value = m_value;
  --m_value;
  m_cs.Leave();
  return old_value;
#elif defined _WIN64
  long long new_value = InterlockedDecrement64(&m_value);
  return (new_value+1);
#else
  assert(false && "AtomicInt64::GetAndDecrement() not supported on this platform");
  return (long long)0;
#endif
}

inline long long AtomicInt64::AddAndGet (long long operand)
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  m_value += operand;
  long long old_value = m_value;
  m_cs.Leave();
  return old_value;
#elif defined _WIN64
  long long old_value = InterlockedExchangeAdd64(&m_value, operand);
  return (old_value+operand);
#else
  assert(false && "AtomicInt64::AddAndGet() not supported on this platform");
  return (long long)0;
#endif
}

inline long long AtomicInt64::IncrementAndGet ()
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  long long old_value = ++m_value;
  m_cs.Leave();
  return old_value;
#elif defined _WIN64
  long long new_value = InterlockedIncrement64(&m_value);
  return new_value;
#else
  assert(false && "AtomicInt64::IncrementAndGet() not supported on this platform");
  return (long long)0;
#endif
}

inline long long AtomicInt64::DecrementAndGet ()
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  long long old_value = --m_value;
  m_cs.Leave();
  return old_value;
#elif defined _WIN64
  long long new_value = InterlockedDecrement64(&m_value);
  return new_value;
#else
  assert(false && "AtomicInt64::DecrementAndGet() not supported on this platform");
  return (long long)0;
#endif
}

inline void AtomicInt64::Add (long long operand)
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  m_value += operand;
  m_cs.Leave();
#elif defined _WIN64
  InterlockedExchangeAdd64(&m_value, operand);
#else
  assert(false && "AtomicInt64::Add() not supported on this platform");
#endif
}

inline void AtomicInt64::Increment ()
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  ++m_value;
  m_cs.Leave();
#elif defined _WIN64
  InterlockedIncrement64(&m_value);
#else
  assert(false && "AtomicInt64::Increment() not supported on this platform");
#endif
}

inline void AtomicInt64::Decrement ()
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  --m_value;
  m_cs.Leave();
#elif defined _WIN64
  InterlockedDecrement64(&m_value);
#else
  assert(false && "AtomicInt64::Decrement() not supported on this platform");
#endif
}
