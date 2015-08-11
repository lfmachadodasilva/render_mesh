//* mtarray.h
// Multithread-safe dynamic array
// fabraham@tecgraf.puc-rio.br
// vbarata@tecgraf.puc-rio.br
// Oct 2008

#ifndef DS_MTARRAY_H
#define DS_MTARRAY_H

#include "dsmt.h"
#include "array.h"
#include <mthread/critsection.h>

template <class TYPE> 
class DSMTAPI DsMTArray : private DsArray<TYPE>
{
public:
  DsMTArray (float incr=2.0F) : DsArray<TYPE>(incr)
  {
  }
  virtual ~DsMTArray()
  {
  }
  void Empty ()
  {
    Lock();
    DsArray<TYPE>::Empty();
    Unlock();
  }
  bool ValidIndex (int i)
  {
    Lock();
    bool ret = ValidIndexSafe(i);
    Unlock();
    return ret;
  }
  bool ValidIndexSafe (int i) const
  {
    return DsArray<TYPE>::ValidIndex(i);
  }
  TYPE Get (int i)
  {
    Lock();
    TYPE ret = GetSafe(i);
    Unlock();
    return ret;
  }
  TYPE GetSafe (int i)
  {
    return DsArray<TYPE>::Get(i);
  }
  void Set (int i, TYPE& t)
  {
    Lock();
    SetSafe(i, t);
    Unlock();
  }
  void SetSafe (int i, TYPE& t)
  {
    DsArray<TYPE>::Set(i, t);
  }
  void SetConst (int i,TYPE t)
  {
    Lock();
    SetConstSafe(i, t);
    Unlock();
  }
  void SetConstSafe (int i,TYPE t)
  {
    DsArray<TYPE>::SetConst(i, t);
  }
  void Append (const TYPE& t)
  {
    Lock();
    AppendSafe(t);
    Unlock();
  }
  void AppendSafe (const TYPE& t)
  {
    DsArray<TYPE>::Append(t);
  }
  void Append (int n, const TYPE* tv)
  {
    Lock();
    DsArray<TYPE>::Append(n, tv);
    Unlock();
  }
  void Insert (const TYPE& t, int pos=-1)
  {
    Lock();
    InsertSafe(t, pos);
    Unlock();
  }
  void InsertSafe (const TYPE& t, int pos=-1)
  {
    DsArray<TYPE>::Insert(t, pos);
  }
  void Remove (int i)
  {
    Lock();
    RemoveSafe(i);
    Unlock();
  }
  void RemoveSafe (int i)
  {
    DsArray<TYPE>::Remove(i);
  }
  void Invert ()
  {
    Lock();
    DsArray<TYPE>::Invert();
    Unlock();
  }
  int Size ()
  {
    Lock();
    int ret = SizeSafe();
    Unlock();
    return ret;
  }
  int SizeSafe ()
  {
    return DsArray<TYPE>::Size();
  }
  void Resize (int n)
  {
    Lock();
    DsArray<TYPE>::Resize(n);
    Unlock();
  }
  void Reserve (int n)
  {
    Lock();
    DsArray<TYPE>::Reserve(n);
    Unlock();
  }
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
