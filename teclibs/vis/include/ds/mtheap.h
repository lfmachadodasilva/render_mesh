//* mtheap.h
// Multithread-safe heap of objects.
// fabraham@tecgraf.puc-rio.br
// vbarata@tecgraf.puc-rio.br
// Aug 2008

#ifndef DS_MTHEAP_H
#define DS_MTHEAP_H

#include "dsmt.h"
#include "heap.h"
#include <mthread/critsection.h>
#include <mthread/condvar.h>

template <class TYPE, typename COMPAREFUNCTOR>
class DSMTAPI DsMTHeap : public DsHeap<TYPE, COMPAREFUNCTOR>
{
public:
  DsMTHeap (COMPAREFUNCTOR& compare)
  : DsHeap<TYPE, COMPAREFUNCTOR>(compare)
  , m_stopwaiting(false)
  {
    m_notempty.Init(m_critsection);
  }
  virtual ~DsMTHeap ()
  {
    StopWaiting();
  }
  int Root (TYPE& item)
  {
    Lock();
    int ret = DsHeap<TYPE, COMPAREFUNCTOR>::Root(item);
    Unlock();
    return ret;
  }
  /**
   * Wait till there is data available and remove the root.
   * Returns the success in getting a root. Only returns false
   * in case someone called StopWaiting().
   */
  bool GetRootWhenAvailable (TYPE& data)
  {
    int ret = 0;
    Lock();
    while (!DsHeap<TYPE, COMPAREFUNCTOR>::IsEmpty() || !m_stopwaiting) {
      if (DsHeap<TYPE, COMPAREFUNCTOR>::IsEmpty())
        m_notempty.Wait();
      else {
        ret = DsHeap<TYPE, COMPAREFUNCTOR>::Root(data);
        break;
      }
    }
    Unlock();
    return ret != 0;
  }
  void Insert (TYPE item)
  {
    Lock();
    DsHeap<TYPE, COMPAREFUNCTOR>::Insert(item);
    m_notempty.Notify();
    Unlock();
  }
  int Remove ()
  {
    Lock();
    int ret = DsHeap<TYPE, COMPAREFUNCTOR>::Remove();
    Unlock();
    return ret;
  }
  void Clear ()
  {
    Lock();
    DsHeap<TYPE, COMPAREFUNCTOR>::Clear();
    Unlock();
  }
  int Size () const
  {
    Lock();
    int ret = DsHeap<TYPE, COMPAREFUNCTOR>::Size();
    Unlock();
    return ret;
  }
  bool IsEmpty () const
  {
    Lock();
    bool ret = DsHeap<TYPE, COMPAREFUNCTOR>::IsEmpty();
    Unlock();
    return ret;
  }
  void PrioritiesChanged ()
  {
    Lock();
    DsHeap<TYPE, COMPAREFUNCTOR>::PrioritiesChanged();
    Unlock();
  }
  /**
   * Stops waiting for new data to be available.
   */
  void StopWaiting ()
  {
    Lock();
    m_stopwaiting = true;
    m_notempty.NotifyAll();
    Unlock();
  }
  /**
   * Enables the heap to wait for new data again.
   */
  void EnableWaiting ()
  {
    Lock();
    m_stopwaiting = false;
    Unlock();
  }
private:
  /**
   * Lock and Unlock
   */
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
  MtlCondVar m_notempty;
  bool m_stopwaiting;
};

#endif

