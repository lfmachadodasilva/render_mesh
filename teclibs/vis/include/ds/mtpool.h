//* mtpool.h
// Multithread-safe pool of objects.
// fabraham@tecgraf.puc-rio.br
// vbarata@tecgraf.puc-rio.br
// Feb 2005

#ifndef DS_MTPOOL_H
#define DS_MTPOOL_H

#include "dsmt.h"
#include "pool.h"
#include <mthread/critsection.h>

template <class TYPE>
class DSMTAPI DsMTPool : public DsPool<TYPE>
{
public:
  typedef TYPE* (*CreateFunc)(void*);
  typedef void (*DestroyFunc)(TYPE*,void*);
  DsMTPool () : DsPool<TYPE> ()
  {
  }
  virtual ~DsMTPool ()
  {
    Clear();
  }
  TYPE* Create ()
  {
    Lock();
    TYPE* elm = DsPool<TYPE>::Create();
    Unlock();
    return elm;
  }
  void Release (TYPE* elm)
  {
    Lock();
    DsPool<TYPE>::Release(elm);
    Unlock();
  }
  void Clear ()
  {
    Lock();
    DsPool<TYPE>::Clear();
    Unlock();
  }
  int Size ()
  {
    Lock();
    int size = DsPool<TYPE>::Size();
    Unlock();
    return size;
  }
  void SetCreateFunc (CreateFunc func, void* data)
  {
    Lock();
    DsPool<TYPE>::SetCreateFunc(func,data);
    Unlock();
  }
  void SetDestroyFunc (DestroyFunc func, void* data)
  {
    Lock();
    DsPool<TYPE>::SetDestroyFunc(func,data);
    Unlock();
  }
  void SetMaxSize (int numitems)
  {
    Lock();
    DsPool<TYPE>::SetMaxSize(numitems);
    Unlock();
  }
private:
  void Lock ()
  {
    m_critsection.Enter();
  }
  void Unlock ()
  {
    m_critsection.Leave();
  }
private:
  MtlCritSection m_critsection;
};

#endif

