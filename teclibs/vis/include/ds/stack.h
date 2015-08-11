// stack.h
// Implements a stack using dynamic array.
// celes@tecgraf.puc-rio.br
// Jul 2002

#ifndef DS_STACK_H
#define DS_STACK_H

#include "array.h"
#include <assert.h>

template <class TYPE>
class DSAPI DsStack
{
public:
  DsStack () : m_v()
  {
  }
  ~DsStack ()
  {
  }
  void Push (TYPE& elm)
  {
    m_v.Append(elm);
  }
  void PushConst (TYPE elm)
  {
    m_v.Append(elm);
  }
  TYPE& Top ()
  {
    return m_v[m_v.Size()-1];
  }
  void Pop ()
  {
    assert(m_v.Size());
    m_v.Resize(m_v.Size()-1);
  }
  void Duplicate ()
  {
    TYPE m = Top();
    Push(m);
  }
  int Size () const
  {
    return m_v.Size();
  }
  bool IsEmpty () const
  {
    return Size() == 0;
  }
  TYPE& GetAt (int depth)
  {
    assert(m_v.ValidIndex(depth));
    return m_v[m_v.Size()-depth-1];
  }
  void Clear ()
  {
    m_v.Clear();
  }
private:
  // blocking copy constructor (to avoid copying issues: copy must be made explicitly)
  DsStack (const DsStack& o) 
  {
  }
  // blocking assignment operator (to avoid copying issues: copy must be made explicitly)
  DsStack& operator= (const DsStack& o) 
  {
    return *this;
  }
private:
  DsArray<TYPE> m_v;
};

#endif
