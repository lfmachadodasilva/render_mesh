//* atomicfloat32.inl
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

inline void AtomicFloat32::Set (float new_value)
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  m_value = new_value;
  m_cs.Leave();
#elif defined _WIN32
  InterlockedExchange((long*)&m_value, *((long*)&new_value));
#else
  assert(false && "AtomicFloat32::Set() not supported on this platform");
#endif
}

inline float AtomicFloat32::Get ()
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  float old_value = m_value;
  m_cs.Leave();
  return old_value;
#elif defined _WIN32
  long old_value = InterlockedCompareExchange((long*)&m_value, (long)0, (long)0);
  return *((float*)&old_value);
#else
  assert(false && "AtomicFloat32::Get() not supported on this platform");
  return 0.0f;
#endif
}

inline float AtomicFloat32::GetAndSet (float new_value)
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  float old_value = m_value;
  m_value = new_value;
  m_cs.Leave();
  return old_value;
#elif defined _WIN32
  long old_value = InterlockedExchange((long*)&m_value, *((long*)&new_value));
  return *((float*)&old_value);
#else
  assert(false && "AtomicFloat32::GetAndSet() not supported on this platform");
  return 0.0f;
#endif
}

inline bool AtomicFloat32::CompareAndSet (float test_value, float new_value)
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  bool test = (m_value == test_value);
  if (test)
    m_value = new_value;
  m_cs.Leave();
  return test;
#elif defined _WIN32
  long old_value = InterlockedCompareExchange((long*)&m_value, *((long*)&new_value), *((long*)&test_value));
  return (old_value == *((long*)&test_value));
#else
  assert(false && "AtomicFloat32::CompareAndSet() not supported on this platform");
  return false;
#endif
}

inline float AtomicFloat32::GetAndAdd (float operand)
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  float old_value = m_value;
  m_value += operand;
  m_cs.Leave();
  return old_value;
#else
  assert(false && "AtomicFloat32::GetAndAdd() not supported on this platform");
  return 0.0f;
#endif
}

inline float AtomicFloat32::AddAndGet (float operand)
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  m_value += operand;
  float old_value = m_value;
  m_cs.Leave();
  return old_value;
#else
  assert(false && "AtomicFloat32::AddAndGet() not supported on this platform");
  return 0.0f;
#endif
}

inline void AtomicFloat32::Add (float operand)
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  m_value += operand;
  m_cs.Leave();
#else
  assert(false && "AtomicFloat32::Add() not supported on this platform");
#endif
}
