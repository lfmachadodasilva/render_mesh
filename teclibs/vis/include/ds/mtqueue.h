//* mtqueue.h
// Multithread-safe queue of objects.
// fabraham@tecgraf.puc-rio.br
// vbarata@tecgraf.puc-rio.br
// Feb 2005

#ifndef DS_MTQUEUE_H
#define DS_MTQUEUE_H

#include "dsmt.h"
#include "mtvar.h"
#include "queue.h"
#include <mthread/critsection.h>
#include <mthread/condvar.h>

template <class TYPE>
class DsMTQueue;

template <class TYPE>
class DSMTAPI DsMTQueueIterator : public DsQueueIterator<TYPE>
{
public:
  ~DsMTQueueIterator ()
  {
    m_queue->Unlock();
  }
private:
  DsMTQueueIterator (DsQueueNode<TYPE>* first,
                     DsMTQueue<TYPE>* queue)
  : DsQueueIterator<TYPE>(first)
  {
    m_queue = queue;
    m_queue->Lock();
  }
private:
  DsMTQueue<TYPE>* m_queue;
private:
  friend class DsMTQueue<TYPE>;
};

template <class TYPE>
class DSMTAPI DsMTQueue : public DsQueue<TYPE>
{
public:
  typedef DsMTQueueIterator<TYPE> Iterator;
public:
  DsMTQueue()
  : DsQueue<TYPE>()
  , m_stop_waiting(false)
  , m_waiting(false)
  {
    m_cond_notempty.Init(m_critsection);
    m_waiting.InitCondVar(m_cond_ended);
  }
  virtual ~DsMTQueue()
  {
    StopWaiting(true);
  }
  void Enqueue (TYPE& elm)
  {
    Lock();
    EnqueueSafe(elm);
    Unlock();
  }
  void EnqueueSafe (TYPE& elm)
  {
    DsQueue<TYPE>::Enqueue(elm);
    m_cond_notempty.NotifyAll();
  }
  void EnqueueConst (TYPE elm)
  {
    Lock();
    DsQueue<TYPE>::EnqueueConst(elm);
    m_cond_notempty.NotifyAll();
    Unlock();
  }
  bool Dequeue (TYPE* data)
  {
    Lock();
    bool ret = DequeueSafe(data);
    Unlock();
    return ret;
  }
  /**
   * Same as 'Dequeue', but assumes the queue is already locked.
   */
  bool DequeueSafe (TYPE* data)
  {
    return DsQueue<TYPE>::Dequeue(data);
  }
  int Size ()
  {
    Lock();
    int ret = DsQueue<TYPE>::Size();
    Unlock();
    return ret;
  }
  bool Empty ()
  {
    Lock();
    bool ret = DsQueue<TYPE>::Empty();
    Unlock();
    return ret;
  }
  bool Get (int index, TYPE* data)
  {
    Lock();
    bool ret = DsQueue<TYPE>::Get(index,data);
    Unlock();
    return ret;
  }
  void Clear ()
  {
    Lock();
    ClearSafe();
    Unlock();
  }
  /**
   * Same as 'Clear', but assumes the queue is already locked.
   */
  void ClearSafe ()
  {
    DsQueue<TYPE>::Clear();
  }
  /**
   * Wait till there is data available and dequeue it.
   * Returns the success in dequeuing. Only returns false
   * in case someone called StopWaiting().
   */
  bool DequeueWait (TYPE* data)
  {
    Lock();
    if (!WaitForItemsOrTermination(false)) {
      Unlock();
      return false;
    }
    bool ret = DequeueSafe(data);
    Unlock();
    return ret;
  }
  /**
   * Wait till there is data available.
   * Returns true when there are items on the queue or false
   * in case someone called StopWaiting().
   */
  bool WaitForItemsOrTermination ()
  {
    return WaitForItemsOrTermination(true);
  }
  /**
   * Wait till there is new data available.
   * Returns true if there is a new item or false
   * in case someone called StopWaiting().
   */
  bool WaitForNewItemsOrTermination ()
  {
    return WaitForNewItemsOrTermination(true);
  }
  /**
   * Stops waiting for new data to be available in the queue.
   * If 'wait' is true, the method will only return when the 'DequeueWait'
   * method finishes.
   */
  void StopWaiting (bool wait=false)
  {
    if (m_stop_waiting)
      return;
    Lock();
    m_stop_waiting = true;
    m_cond_notempty.NotifyAll();
    Unlock();
    if (wait)
      WaitUntilEnd();
  }
  /**
   * Enables the queue to wait for new data again.
   */
  void EnableWaiting ()
  {
    Lock();
    m_stop_waiting = false;
    Unlock();
  }
  bool StoppedWaiting ()
  {
    bool ret;
    Lock();
    ret = m_stop_waiting;
    Unlock();
    return ret;
  }
  /**
   * Deprecated name. Use 'DequeueWait'.
   */
  bool DequeueTillAvailable (TYPE* data)
  {
    return DequeueWait(data);
  }
  /**
   * Begins iteration on queue.
   * Typical usage:
   *
   * for (DsMTQueue<item_type_name>::Iterator it = queue.Begin();
   *      it.Valid();
   *      it.Next())
   * {
   *   item_type_name item = it.Self();
   *   ...
   * }
   */
  Iterator Begin ()
  {
    return Iterator(DsQueue<TYPE>::GetFirstNode(),this);
  }
private:
  void SignalEnd ()
  {
    m_waiting.Lock();
    m_waiting.SetConstSafe(false);
    m_cond_ended.NotifyAll();
    m_waiting.Unlock();
  }
  void WaitUntilEnd ()
  {
    m_waiting.Lock();
    while (m_waiting.GetSafe())
      m_cond_ended.Wait();
    m_waiting.Unlock();
  }
  bool WaitForItemsOrTermination (bool lock)
  {
    bool ret = false;
    if (lock)
      Lock();
    while (!DsQueue<TYPE>::Empty() || !m_stop_waiting)
    {
      if (DsQueue<TYPE>::Empty())
        (void)WaitForNewItemsOrTermination(false);
      else {
        ret = true;
        break;
      }
    }
    if (lock)
      Unlock();
    return ret;
  }
  bool WaitForNewItemsOrTermination (bool lock)
  {
    if (lock)
      Lock();

    // sleep until someone signals 'notempty'
    m_waiting = true;
    m_cond_notempty.Wait();
    SignalEnd();
    
    bool ret = !m_stop_waiting;

    if (lock)
      Unlock();

    return ret;
  }
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
  friend class DsMTQueueIterator<TYPE>;
  MtlCritSection m_critsection;
  MtlCondVar m_cond_notempty;
  MtlCondVar m_cond_ended;
  bool m_stop_waiting;
  DsMTVar<bool> m_waiting;
};

#endif

