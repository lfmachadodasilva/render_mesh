#ifndef DS_MT_MONITORED_VAR
#define DS_MT_MONITORED_VAR

#include "dsmt.h"
#include "mtvar.h"
#include <mthread/condvar.h>

#define DSMTMONVAR_DECLARE_ARITHMETIC_AND_ATTRIB_OP(opsymbol, arithsymbol) \
  void operator opsymbol (TYPE var) \
  { \
    DsMTVar<TYPE>::Lock(); \
    SetConstSafe(DsMTVar<TYPE>::GetRefSafe() arithsymbol var); \
    DsMTVar<TYPE>::Unlock(); \
  }

template <class TYPE>
class DSMTAPI DsMTMonitoredVar : public DsMTVar<TYPE>
{
public:
  DsMTMonitoredVar ()
  : m_stop_waiting(false)
  , m_waiting(false)
  {
    DsMTVar<TYPE>::InitCondVar(m_wait_cond_var);
    m_waiting.InitCondVar(m_cond_ended);
  }
  DsMTMonitoredVar (const TYPE& var)
  : DsMTVar<TYPE>(var)
  , m_stop_waiting(false)
  , m_waiting(false)
  {
    DsMTVar<TYPE>::InitCondVar(m_wait_cond_var);
    m_waiting.InitCondVar(m_cond_ended);
  }
  DsMTMonitoredVar (const DsMTMonitoredVar<TYPE>& var)
  : DsMTVar<TYPE>(var)
  , m_stop_waiting(false)
  , m_waiting(false)
  {
    Set(var.Get());
    DsMTVar<TYPE>::InitCondVar(m_wait_cond_var);
    m_waiting.InitCondVar(m_cond_ended);
  }
  virtual ~DsMTMonitoredVar ()
  {
    StopWaiting(true);
  }
  void Set (TYPE& var)
  {
    DsMTVar<TYPE>::Lock();
    SetSafe(var);
    DsMTVar<TYPE>::Unlock();
  }
  void SetConst (TYPE var)
  {
    DsMTVar<TYPE>::Lock();
    SetConstSafe(var);
    DsMTVar<TYPE>::Unlock();
  }
  void SetSafe (TYPE& var)
  {
    DsMTVar<TYPE>::SetSafe(var);
    NotifyChange();
  }
  void SetConstSafe (TYPE var)
  {
    DsMTVar<TYPE>::SetConstSafe(var);
    NotifyChange();
  }
  void operator= (TYPE var)
  {
    Set(var);
  }
  DSMTMONVAR_DECLARE_ARITHMETIC_AND_ATTRIB_OP(+=, +)
  DSMTMONVAR_DECLARE_ARITHMETIC_AND_ATTRIB_OP(-=, -)
  DSMTMONVAR_DECLARE_ARITHMETIC_AND_ATTRIB_OP(*=, *)
  DSMTMONVAR_DECLARE_ARITHMETIC_AND_ATTRIB_OP(/=, /)
  DSMTMONVAR_DECLARE_ARITHMETIC_AND_ATTRIB_OP(|=, |)
  DSMTMONVAR_DECLARE_ARITHMETIC_AND_ATTRIB_OP(&=, &)
  DSMTMONVAR_DECLARE_ARITHMETIC_AND_ATTRIB_OP(^=, ^)
  bool WaitForChange (TYPE* newvalue)
  {
    bool ret = false;
    DsMTVar<TYPE>::Lock();
    TYPE oldvalue = *newvalue;
    while (true) {
      if (m_stop_waiting)
        break;
      if (DsMTVar<TYPE>::GetRefSafe() == oldvalue) {
        m_waiting = true;
        m_wait_cond_var.Wait();
        SignalEnd();
      }
      else {
        ret = true;
        *newvalue = DsMTVar<TYPE>::GetRefSafe();
        break;
      }
    }
    DsMTVar<TYPE>::Unlock();
    return ret;
  }
  /**
   * Enables the queue to wait for new data again.
   */
  void EnableWaiting ()
  {
    DsMTVar<TYPE>::Lock();
    m_stop_waiting = false;
    DsMTVar<TYPE>::Unlock();
  }
  void StopWaiting (bool wait=false)
  {
    if (m_stop_waiting)
      return;
    DsMTVar<TYPE>::Lock();
    m_stop_waiting = true;
    m_wait_cond_var.NotifyAll();
    DsMTVar<TYPE>::Unlock();
    if (wait)
      WaitUntilEnd();
  }
  bool StoppedWaiting () const
  {
    return m_stop_waiting;
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
  void NotifyChange ()
  {
    m_wait_cond_var.NotifyAll();
  }
private:
  MtlCondVar m_wait_cond_var;
  MtlCondVar m_cond_ended;
  bool m_stop_waiting;
  DsMTVar<bool> m_waiting;
};

#endif

