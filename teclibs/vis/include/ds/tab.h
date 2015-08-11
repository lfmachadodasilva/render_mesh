// tab.h
// Implements an indexable pointer tab.
// fabraham@tecgraf.puc-rio.br
// Oct 2004

#ifndef DS_TAB_H
#define DS_TAB_H

#include "array.h"

template <class TYPE>
class DSAPI DsTab
{
  DsArray<TYPE*> m_tab;
public:
  DsTab () : m_tab()
  {
  }
  int GetDimension ()
  {
    if (m_tab.Size() == 0)
      m_tab.Append(0); // id=0 is reserved for the null pointer
    return m_tab.Size(); 
  }
  TYPE* Get (int id)
  {
    return id ? m_tab.Get(id) : 0; 
  }
  int New (TYPE* t)
  {
    // TODO: reuse empty spots on the tab.
    // search for first free id
    int n = GetDimension();
    for (int i=1; i<n; ++i) {
      if (m_tab[i] == NULL) {
        m_tab[i] = t;
        return i;
      }
    }
    m_tab.Append(t);
    return n;
  }
  void Free (int id)
  {
    // TODO: reuse empty spots on the tab.
    m_tab.SetConst(id, NULL);
  }
};

#endif

