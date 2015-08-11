// mtvar.h
// Multithread-safe variable
// fabraham@tecgraf.puc-rio.br
// vbarata@tecgraf.puc-rio.br
// Sep 2008

#ifndef DS_MTVAR_H
#define DS_MTVAR_H

#include "dsmt.h"
#include <mthread/critsection.h>
#include <mthread/condvar.h>

#define DSMT_DECLARE_LOGICAL_OP(symbol) \
  bool operator symbol (TYPE var) \
  { \
    Lock(); \
    bool ret = m_var symbol var; \
    Unlock(); \
    return ret; \
  }

#define DSMT_DECLARE_ARITHMETIC_OP(symbol) \
  TYPE operator symbol (TYPE var) \
  { \
    Lock(); \
    TYPE ret = m_var symbol var; \
    Unlock(); \
    return ret; \
  }

#define DSMT_DECLARE_UNARY_OP(symbol) \
  TYPE operator symbol () \
  { \
    Lock(); \
    TYPE ret = symbol m_var; \
    Unlock(); \
    return ret; \
  }

#define DSMT_DECLARE_ARITHMETIC_AND_ATTRIB_OP(opsymbol, arithsymbol) \
  void operator opsymbol (TYPE var) \
  { \
    Lock(); \
    SetConstSafe(m_var arithsymbol var); \
    Unlock(); \
  }

template <class TYPE>
class DSMTAPI DsMTVar
{
public:
  DsMTVar ()
  {
  }
  DsMTVar (const TYPE& var)
  : m_var(var)
  {
  }
  DsMTVar (const DsMTVar<TYPE>& var)
  {
    m_var = var.Get();
  }
  virtual ~DsMTVar ()
  {
  }
  void Set (TYPE& var)
  {
    Lock();
    SetSafe(var);
    Unlock();
  }
  void SetConst (TYPE var)
  {
    Lock();
    SetConstSafe(var);
    Unlock();
  }
  void SetSafe (TYPE& var)
  {
    m_var = var;
  }
  void SetConstSafe (TYPE var)
  {
    m_var = var;
  }
  void operator= (TYPE var)
  {
    Set(var);
  }
  DSMT_DECLARE_LOGICAL_OP(>=)
  DSMT_DECLARE_LOGICAL_OP(<=)
  DSMT_DECLARE_LOGICAL_OP(>)
  DSMT_DECLARE_LOGICAL_OP(<)
  DSMT_DECLARE_LOGICAL_OP(==)
  DSMT_DECLARE_LOGICAL_OP(!=)
  DSMT_DECLARE_LOGICAL_OP(||)
  DSMT_DECLARE_LOGICAL_OP(&&)
  DSMT_DECLARE_ARITHMETIC_OP(+)
  DSMT_DECLARE_ARITHMETIC_OP(-)
  DSMT_DECLARE_ARITHMETIC_OP(*)
  DSMT_DECLARE_ARITHMETIC_OP(/)
  DSMT_DECLARE_ARITHMETIC_OP(|)
  DSMT_DECLARE_ARITHMETIC_OP(&)
  DSMT_DECLARE_ARITHMETIC_OP(^)
  DSMT_DECLARE_UNARY_OP(-)
  DSMT_DECLARE_UNARY_OP(!)
  DSMT_DECLARE_UNARY_OP(~)
  DSMT_DECLARE_ARITHMETIC_AND_ATTRIB_OP(+=, +)
  DSMT_DECLARE_ARITHMETIC_AND_ATTRIB_OP(-=, -)
  DSMT_DECLARE_ARITHMETIC_AND_ATTRIB_OP(*=, *)
  DSMT_DECLARE_ARITHMETIC_AND_ATTRIB_OP(/=, /)
  DSMT_DECLARE_ARITHMETIC_AND_ATTRIB_OP(|=, |)
  DSMT_DECLARE_ARITHMETIC_AND_ATTRIB_OP(&=, &)
  DSMT_DECLARE_ARITHMETIC_AND_ATTRIB_OP(^=, ^)
  /**
   * Get a copy of the variable.
   */
  TYPE Get ()
  {
    Lock();
    TYPE ret = GetSafe();
    Unlock();
    return ret;
  }
  TYPE GetSafe ()
  {
    return m_var;
  }
  /**
   * Get a reference to the variable.
   * The reference must be freed with FreeRef() when done using it.
   */
  TYPE& GetRef ()
  {
    Lock();
    return GetRefSafe();
  }
  TYPE& GetRefSafe ()
  {
    return m_var;
  }
  void FreeRef ()
  {
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
  /**
   * Allows the initialization of a condition variable
   * associated with this variable's critical section.
   */
  void InitCondVar (MtlCondVar& var)
  {
    var.Init(m_critsection);
  }
private:
  TYPE m_var;
  MtlCritSection m_critsection;
};

#endif

