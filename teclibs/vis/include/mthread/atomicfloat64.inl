//* atomicfloat64.inl
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

inline void AtomicFloat64::Set (double new_value)
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  m_value = new_value;
  m_cs.Leave();
#elif defined _WIN64
  InterlockedExchange64((long long*)&m_value, *((long long*)&new_value));
#else
  assert(false && "AtomicFloat64::Set() not supported on this platform");
#endif
}

inline double AtomicFloat64::Get ()
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  double old_value = m_value;
  m_cs.Leave();
  return old_value;
#elif defined _WIN64
  long long old_value = InterlockedCompareExchange64((long long*)&m_value, (long long)0, (long long)0);
  return *((double*)&old_value);
#else
  assert(false && "AtomicFloat64::Get() not supported on this platform");
  return 0.0;
#endif
}

inline double AtomicFloat64::GetAndSet (double new_value)
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  double old_value = m_value;
  m_value = new_value;
  m_cs.Leave();
  return old_value;
#elif defined _WIN64
  long long old_value = InterlockedExchange64((long long*)&m_value, *((long long*)&new_value));
  return *((double*)&old_value);
#else
  assert(false && "AtomicFloat64::GetAndSet() not supported on this platform");
  return 0.0;
#endif
}

inline bool AtomicFloat64::CompareAndSet (double test_value, double new_value)
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  bool test = (m_value == test_value);
  if (test)
    m_value = new_value;
  m_cs.Leave();
  return test;
#elif defined _WIN64
  long long old_value = InterlockedCompareExchange64((long long*)&m_value, *((long long*)&new_value, *((long long*)&test_value);
  return (old_value == *((long long*)&test_value);
#else
  assert(false && "AtomicFloat64::CompareAndSet() not supported on this platform");
  return false;
#endif
}

inline double AtomicFloat64::GetAndAdd (double operand)
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  double old_value = m_value;
  m_value += operand;
  m_cs.Leave();
  return old_value;
#else
  assert(false && "AtomicFloat64::GetAndAdd() not supported on this platform");
  return 0.0;
#endif
}

inline double AtomicFloat64::AddAndGet (double operand)
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  m_value += operand;
  double old_value = m_value;
  m_cs.Leave();
  return old_value;
#else
  assert(false && "AtomicFloat64::AddAndGet() not supported on this platform");
  return 0.0;
#endif
}

inline void AtomicFloat64::Add (double operand)
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  m_value += operand;
  m_cs.Leave();
#else
  assert(false && "AtomicFloat64::Add() not supported on this platform");
#endif
}
