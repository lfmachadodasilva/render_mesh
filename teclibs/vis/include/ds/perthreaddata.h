// perthreaddata.h
// Collection of data that must exist individually for each thread.
// fabraham@tecgraf.puc-rio.br
// vbarata@tecgraf.puc-rio.br
// Nov 2008

#ifndef DS_MTPERTHREADDATA_H
#define DS_MTPERTHREADDATA_H

#include "dsmt.h"
#include "hash.h"
#include <mthread/critsection.h>
#include <mthread/thread.h>

/**
 * This class manages data that must exist individually for each thread.
 *
 * 'Set' sets the data for the calling thread.
 * 'Get' obtains the data of the calling thread.
 */
template <class TYPE>
class DSMTAPI DsMTPerThreadData
{
public:
  /**
   * Constructor.
   */
  DsMTPerThreadData ()
  {
    m_last_get_thread = NULL;
    m_last_get_data = NULL;
  }
  /**
   * Obtains the data of the calling thread, previously set using 'Set'.
   */
  TYPE* Get ()
  {
    MtlThread* thread_id = MtlThread::GetCurrent();
    TYPE* data;

    Lock();
    if (thread_id == m_last_get_thread)
      data = m_last_get_data;
    else {
      data = m_data.Get(thread_id);
      if (data != NULL) {
        m_last_get_thread = thread_id;
        m_last_get_data = data;
      }
    }
    Unlock();
    return data;
  }
  /**
   * Stores the data of the current thread.
   */
  void Set (TYPE* data)
  {
    MtlThread* thread_id = MtlThread::GetCurrent();
    Lock();
    m_data.Set(thread_id,data);
    m_last_get_thread = thread_id;
    m_last_get_data = data;
    Unlock();
  }
protected:
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
  DsHash<MtlThread*,TYPE*> m_data;
  MtlCritSection m_critsection;
  MtlThread m_last_get_thread;
  TYPE* m_last_get_data;
};

#endif

