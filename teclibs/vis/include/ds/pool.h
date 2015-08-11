//* pool.h
// Manages pool of objects.
// celes@tecgraf.puc-rio.br
// Jul 2002

#ifndef ds_pool_h
#define ds_pool_h

#include "list.h"
#include <assert.h>
#include <stdio.h>

template <class TYPE>
class DSAPI DsPool
{
public:
  typedef DsPList<TYPE> List;
  typedef TYPE* (*CreateFunc)(void*);
  typedef void (*DestroyFunc)(TYPE*,void*);
private:
  List m_list;      // list of available objects
  CreateFunc m_createfunc;
  DestroyFunc m_destroyfunc;
  void* m_createdata;
  void* m_destroydata;
public:
  DsPool ()
  : m_list()
  , m_createfunc(NULL)
  , m_destroyfunc(NULL)
  , m_createdata(NULL)
  , m_destroydata(NULL)
  , m_max_num_items(-1)
  {
  }

  ~DsPool ()
  {
    Clear();
  }

  TYPE* Create ()
  {
    TYPE* elm;
    typename List::Iterator itr = m_list.Begin();
    if (itr.Valid())
    {
      elm = itr.Self();
      m_list.Remove();
    }
    else
    {
      elm = m_createfunc ? m_createfunc(m_createdata) : new TYPE;
    }
    return elm;
  }

  void Release (TYPE* elm)
  {
    assert(elm != NULL);
    if (m_max_num_items < 0 || Size() < m_max_num_items)
      m_list.Insert(elm);
    else {
      if (m_destroyfunc != NULL)
        m_destroyfunc(elm, m_destroydata);
      else
        delete elm;
    }
  }

  void Clear ()
  {
    if (m_destroyfunc != NULL) {
      for (typename List::Iterator i=m_list.Begin(); i.Valid(); ++i)
        m_destroyfunc(i.Self(), m_destroydata);
    }
    else {
      for (typename List::Iterator i=m_list.Begin(); i.Valid(); ++i)
        delete i.Self();
    }
    m_list.Clear();
  }

  int Size ()
  {
    return m_list.Size();
  }

  void SetCreateFunc (CreateFunc func, void* data)
  {
    m_createfunc = func;
    m_createdata = data;
  }
  void SetDestroyFunc (DestroyFunc func, void* data)
  {
    m_destroyfunc = func;
    m_destroydata = data;
  }
  /**
   * Specifies the maximum pool size in terms of number of elements.
   * If another element is released and the pool is holding 'numitems'
   * items, the element is deleted instead of stored.
   */
  void SetMaxSize (int numitems)
  {
    m_max_num_items = numitems;
  }
private:
  int m_max_num_items;
};

#endif
