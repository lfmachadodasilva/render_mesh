//* atomicpointer.inl
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

#define ATOMICTEMPLATE template <class TYPE>
#define ATOMICPOINTER AtomicPointer<TYPE>

//----------------------------//
// Constructor and Destructor //
//----------------------------//

ATOMICTEMPLATE inline ATOMICPOINTER::AtomicPointer (TYPE* value)
: m_value(value)
{
}

ATOMICTEMPLATE inline ATOMICPOINTER::~AtomicPointer ()
{
}

//----------------------------//
// Atomic Thread-safe Methods //
//----------------------------//

ATOMICTEMPLATE inline void ATOMICPOINTER::Set (TYPE* new_value)
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  m_value = new_value;
  m_cs.Leave();
#elif defined _WIN32
  InterlockedExchangePointer((void**)&m_value, (void*)new_value);
#else
  assert(false && "AtomicPointer::Set() not supported on this platform");
#endif
}

ATOMICTEMPLATE inline TYPE* ATOMICPOINTER::Get ()
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  TYPE* old_value = m_value;
  m_cs.Leave();
  return old_value;
#elif defined _WIN32
  TYPE* old_value = (TYPE*)InterlockedCompareExchangePointer((void**)&m_value, NULL, NULL);
  return old_value;
#else
  assert(false && "AtomicPointer::Get() not supported on this platform");
  return (TYPE*)NULL;
#endif
}

ATOMICTEMPLATE inline TYPE* ATOMICPOINTER::GetAndSet (TYPE* new_value)
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  TYPE* old_value = m_value;
  m_value = new_value;
  m_cs.Leave();
  return old_value;
#elif defined _WIN32
  TYPE* old_value = (TYPE*)InterlockedExchangePointer((void**)&m_value, (void*)new_value);
  return old_value;
#else
  assert(false && "AtomicPointer::GetAndSet() not supported on this platform");
  return (TYPE*)NULL;
#endif
}

ATOMICTEMPLATE inline bool ATOMICPOINTER::CompareAndSet (TYPE* test_value, TYPE* new_value)
{
#ifdef ATOMIC_USE_MUTEXES
  m_cs.Enter();
  bool test = (m_value == test_value);
  if (test)
    m_value = new_value;
  m_cs.Leave();
  return test;
#elif defined _WIN32
  TYPE* old_value = (TYPE*)InterlockedCompareExchangePointer((void**)&m_value, (void*)new_value, (void*)test_value);
  return (old_value == test_value);
#else
  assert(false && "AtomicPointer::CompareAndSet() not supported on this platform");
  return false;
#endif
}

#undef ATOMICPOINTER
#undef ATOMICTEMPLATE
