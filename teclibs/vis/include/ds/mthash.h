//* mthash.h
// Multithread-safe hash table
// vbarata@tecgraf.puc-rio.br
// Aug 2009

#ifndef DS_MTHASH_H
#define DS_MTHASH_H

#include "dsmt.h"
#include "hash.h"
#include <mthread/critsection.h>

template <class KEY, class VALUE>
class DSMTAPI DsMTHash : private DsHash<KEY, VALUE>
{
public:
  DsMTHash (int size=2) : DsHash<KEY, VALUE>(size)
  {
  }
  virtual ~DsMTHash ()
  {
  }
  void Set (const KEY& key, const VALUE& value)
  {
    Lock();
    SetSafe(key, value);
    Unlock();
  }
  void SetSafe (const KEY& key, const VALUE& value)
  {
    DsHash<KEY, VALUE>::Set(key, value);
  }
  VALUE Get (const KEY& key)
  {
    Lock();
    VALUE ret = GetSafe(key);
    Unlock();
    return ret;
  }
  VALUE GetSafe (const KEY& key)
  {
    return DsHash<KEY, VALUE>::Get(key);
  }
  bool Remove (const KEY& key)
  {
    Lock();
    bool success = RemoveSafe(key);
    Unlock();
    return success;
  }
  bool RemoveSafe (const KEY& key)
  {
    return DsHash<KEY, VALUE>::Remove(key);
  }
  VALUE GetAndRemove (const KEY& key)
  {
    Lock();
    VALUE ret = GetAndRemoveSafe(key);
    Unlock();
    return ret;
  }
  VALUE GetAndRemoveSafe (const KEY& key)
  {
    return DsHash<KEY, VALUE>::GetAndRemove(key);
  }
  bool Find (const KEY& key)
  {
    Lock();
    bool ret = FindSafe(key);
    Unlock();
    return ret;
  }
  bool FindSafe (const KEY& key)
  {
    return DsHash<KEY, VALUE>::Find(key);
  }
  bool First (KEY* key=0)
  {
    Lock();
    bool ret = FirstSafe(key);
    Unlock();
    return ret;
  }
  bool FirstSafe (KEY* key=0)
  {
    return DsHash<KEY, VALUE>::First(key);
  }
  bool Next (KEY* key)
  {
    Lock();
    bool ret = NextSafe(key);
    Unlock();
    return ret;
  }
  bool NextSafe (KEY* key)
  {
    return DsHash<KEY, VALUE>::Next(key);
  }
  void Clear ()
  {
    Lock();
    DsHash<KEY, VALUE>::Clear();
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
