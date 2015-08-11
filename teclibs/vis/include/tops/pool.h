/**
  TopS - Topological data structure for mesh representation.
  
  TopS is a software developed by Tecgraf/PUC-Rio & UIUC.
  It is requested that the TopS users provide the appropriate
  credits and references to the work.
  
  References:
  1 -W. Celes, G.H. Paulino, R. Espinha, "A compact adjacency-based
  topological data structure for finite element mesh representation",
  IJNME, 2005 (in press)
  2 - W. Celes, G.H. Paulino, R. Espinha, "Efficient Handling of Implicit
  Entities in Reduced Mesh Representations", JCISE, Special Issue on
  Mesh-Based Geometric Data Processing, 2005 (in press)
  
  Aug 2005
*/

#ifndef _TOP_POOL_H
#define _TOP_POOL_H

#include <stdlib.h>
#include <assert.h>
#include "defines.h"

template <class T> class TOPSH_API TopPool
{
  T*                m_data;
  int               m_n;
  int               m_size;
  
public:  
  TopPool() : 
    m_data(NULL), m_n(0), m_size(8)
  {
    m_data = (T*) calloc(m_size, sizeof(T));
    assert(m_data);
  }
  
  ~TopPool()
  {
    free(m_data); 
  }

  bool IsEmpty() { return (m_n == 0); }
    
  void Put(T d)
  {
    if (m_n == m_size) {
      m_size *= 2;
      m_data = (T*) realloc(m_data, m_size*sizeof(T));
      assert(m_data);
    }
    m_data[m_n++] = d;
  }

  T Get()
  {
    assert(m_n > 0);
    return m_data[--m_n];
  }
};

#endif
