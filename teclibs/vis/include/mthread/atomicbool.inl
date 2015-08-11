//* atomicbool.inl
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
# pragma intrinsic(_InterlockedXor8)
# pragma intrinsic(_InterlockedOr8)
#endif
#include <assert.h>

//----------------------------//
// Atomic Thread-safe Methods //
//----------------------------//

inline void AtomicBool::Set (bool new_value)
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  m_value = new_value;
  m_cs.Leave();
#elif defined _WIN32
  if (new_value)
  {
    _InterlockedOr8((char*)&m_value, (char)0x01);
  }
  else
  {
    _InterlockedAnd8((char*)&m_value, (char)0x00);
  }
#else
  assert(false && "AtomicBool::Set() not supported on this platform");
#endif
}

inline bool AtomicBool::Get ()
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  bool old_value = m_value;
  m_cs.Leave();
  return old_value;
#elif defined _WIN32
  char old_value = _InterlockedAnd8((char*)&m_value, (char)0x01);
  return (old_value != (char)0x00);
#else
  assert(false && "AtomicBool::Get() not supported on this platform");
  return false;
#endif
}

inline bool AtomicBool::GetAndSet (bool new_value)
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  bool old_value = m_value;
  m_value = new_value;
  m_cs.Leave();
  return old_value;
#elif defined _WIN32
  if (new_value)
  {
    char old_value = _InterlockedOr8((char*)&m_value, (char)0x01);
    return (old_value != (char)0x00);
  }
  else
  {
    char old_value = _InterlockedAnd8((char*)&m_value, (char)0x00);
    return (old_value != (char)0x00);
  }
#else
  assert(false && "AtomicBool::GetAndSet() not supported on this platform");
  return false;
#endif
}

inline bool AtomicBool::CompareAndSet (bool test_value, bool new_value)
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  bool test = (m_value == test_value);
  if (test)
    m_value = new_value;
  m_cs.Leave();
  return test;
#elif defined _WIN32
  if (test_value && new_value)
  {
    char old_value = _InterlockedAnd8((char*)&m_value, (char)0x01);
    return (old_value == (char)0x01);
  }
  else if (test_value)
  {
    char old_value = _InterlockedAnd8((char*)&m_value, (char)0x00);
    return (old_value == (char)0x01);
  }
  else if (new_value)
  {
    char old_value = _InterlockedOr8((char*)&m_value, (char)0x01);
    return (old_value == (char)0x00);
  }
  else
  {
    char old_value = _InterlockedOr8((char*)&m_value, (char)0x00);
    return (old_value == (char)0x00);
  }
#else
  assert(false && "AtomicBool::CompareAndSet() not supported on this platform");
  return false;
#endif
}

inline void AtomicBool::Not ()
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  m_value = !m_value;
  m_cs.Leave();
#elif defined _WIN32
  _InterlockedXor8((char*)&m_value, (char)0x01);
#else
  assert(false && "AtomicBool::Not() not supported on this platform");
#endif
}

inline void AtomicBool::And (bool operand)
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  m_value = (m_value && operand);
  m_cs.Leave();
#elif defined _WIN32
  _InterlockedAnd8((char*)&m_value, (char)operand);
#else
  assert(false && "AtomicBool::And() not supported on this platform");
#endif
}

inline void AtomicBool::Or (bool operand)
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  m_value = (m_value || operand);
  m_cs.Leave();
#elif defined _WIN32
  _InterlockedOr8((char*)&m_value, (char)operand);
#else
  assert(false && "AtomicBool::Or() not supported on this platform");
#endif
}

inline void AtomicBool::Xor (bool operand)
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  m_value = (m_value != operand);
  m_cs.Leave();
#elif defined _WIN32
  _InterlockedXor8((char*)&m_value, (char)operand);
#else
  assert(false && "AtomicBool::Xor() not supported on this platform");
#endif
}

inline bool AtomicBool::GetAndNot ()
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  bool old_value = m_value;
  m_value = !m_value;
  m_cs.Leave();
  return old_value;
#elif defined _WIN32
  char old_value = _InterlockedXor8((char*)&m_value, (char)0x01);
  return (old_value != (char)0x00);
#else
  assert(false && "AtomicBool::GetAndNot() not supported on this platform");
  return false;
#endif
}

inline bool AtomicBool::GetAndAnd (bool operand)
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  bool old_value = m_value;
  m_value = (m_value && operand);
  m_cs.Leave();
  return old_value;
#elif defined _WIN32
  char old_value = _InterlockedAnd8((char*)&m_value, (char)operand);
  return (old_value != (char)0x00);
#else
  assert(false && "AtomicBool::GetAndAnd() not supported on this platform");
  return false;
#endif
}

inline bool AtomicBool::GetAndOr (bool operand)
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  bool old_value = m_value;
  m_value = (m_value || operand);
  m_cs.Leave();
  return old_value;
#elif defined _WIN32
  char old_value = _InterlockedOr8((char*)&m_value, (char)operand);
  return (old_value != (char)0x00);
#else
  assert(false && "AtomicBool::GetAndOr() not supported on this platform");
  return false;
#endif
}

inline bool AtomicBool::GetAndXor (bool operand)
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  bool old_value = m_value;
  m_value = (m_value != operand);
  m_cs.Leave();
  return old_value;
#elif defined _WIN32
  char old_value = _InterlockedXor8((char*)&m_value, (char)operand);
  return (old_value != (char)0x00);
#else
  assert(false && "AtomicBool::GetAndXor() not supported on this platform");
  return false;
#endif
}

inline bool AtomicBool::NotAndGet ()
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  m_value = !m_value;
  bool old_value = m_value;
  m_cs.Leave();
  return old_value;
#elif defined _WIN32
  char old_value = _InterlockedXor8((char*)&m_value, (char)0x01);
  return (old_value == (char)0x00);
#else
  assert(false && "AtomicBool::NotAndGet() not supported on this platform");
  return false;
#endif
}

inline bool AtomicBool::AndAndGet (bool operand)
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  m_value = (m_value && operand);
  bool old_value = m_value;
  m_cs.Leave();
  return old_value;
#elif defined _WIN32
  char old_value = _InterlockedAnd8((char*)&m_value, (char)operand);
  return ((old_value & (char)operand) != (char)0x00);
#else
  assert(false && "AtomicBool::AndAndGet() not supported on this platform");
  return false;
#endif
}

inline bool AtomicBool::OrAndGet (bool operand)
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  m_value = (m_value || operand);
  bool old_value = m_value;
  m_cs.Leave();
  return old_value;
#elif defined _WIN32
  char old_value = _InterlockedOr8((char*)&m_value, (char)operand);
  return ((old_value | (char)operand) != (char)0x00);
#else
  assert(false && "AtomicBool::OrAndGet() not supported on this platform");
  return false;
#endif
}

inline bool AtomicBool::XorAndGet (bool operand)
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  m_value = (m_value != operand);
  bool old_value = m_value;
  m_cs.Leave();
  return old_value;
#elif defined _WIN32
  char old_value = _InterlockedXor8((char*)&m_value, (char)operand);
  return ((old_value ^ (char)operand) != (char)0x00);
#else
  assert(false && "AtomicBool::XorAndGet() not supported on this platform");
  return false;
#endif
}
