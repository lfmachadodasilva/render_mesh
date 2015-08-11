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

#ifndef _TOP_HEAP_H
#define _TOP_HEAP_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "defines.h"
#include <io/stream.h>

// T must have the operator>() defined.
template<class T> 
class TOPSH_API TopHeap
{
  T*  m_data;
  int m_n; // 1-indexed, to ease implementation...
  int m_alloc_size;
  int m_init_alloc_size;

  int Parent(int i) { return i/2; }
  int LeftChild(int i) { return 2*i; }
  int RightChild(int i) { return 2*i+1; }

  void Heapify(int i)
  {
    while (i > 0) {
      int largest;
      int l = LeftChild(i), r = RightChild(i);
      if (l <= m_n && m_data[l] < m_data[i])
        largest = l;
      else
        largest = i;
      if (r <= m_n && m_data[r] < m_data[largest])
        largest = r;
      if (largest != i) {
        T tmp = m_data[i];
        m_data[i] = m_data[largest];
        m_data[largest] = tmp;
        i = largest;
      } else {
        i = 0;
      }
    }
  }
  
public: 
  /**
    Heap. The top element is the one with the biggest key.
  */  
  TopHeap() : m_data(NULL), m_n(0), m_init_alloc_size(8)
  {
    m_alloc_size = m_init_alloc_size;
    m_data = (T*) malloc((m_alloc_size+1)*sizeof(T));
    assert(m_data);
  }
 
  ~TopHeap()
  {
    free(m_data); 
  }

  void Reset() { m_n = 0; }

  void Empty ()
  {
    m_n = 0;
    m_alloc_size = m_init_alloc_size;
    m_data = (T*) realloc(m_data, (m_alloc_size+1)*sizeof(T));
    assert(m_data);
  }

  int  Size() const { return m_n; }

  bool IsEmpty() const { return m_n == 0; }
 
  void Insert(const T& key)
  {
    if (m_n == m_alloc_size) {
      m_alloc_size *= 2;
      m_data = (T*) realloc(m_data, (m_alloc_size+1)*sizeof(T));
      assert(m_data);
    }
    m_n++;
    int i;
    for (i = m_n; i > 1 && key < m_data[Parent(i)]; i = Parent(i)) 
      m_data[i] = m_data[Parent(i)];
    m_data[i] = key;
  }

  // Extracts the element at the top of the heap.
  T ExtractMin() 
  { 
    T max = m_data[1];
    m_data[1] = m_data[m_n];
    m_n--;
    Heapify(1);
    return max;
  }

  // Gets the element at the top of the heap.
  T& GetMin() const
  {
    return m_data[1];
  }

  // Data array is 1-indexed.
  T* GetData()
  {
    return m_data;
  }

  // Data array is 1-indexed.
  void SetData(int n, T* data)
  {
    m_n = n;
    m_alloc_size = 8;
    while (m_alloc_size <= n)
      m_alloc_size *= 2;
    m_data = (T*) realloc(m_data, (m_alloc_size+1)*sizeof(T));
    assert(m_data);
    for (int i = 1; i <= m_n; i++)
      m_data[i] = data[i];
  }

  void Print(const char* label=0) const
  {
    if (label) printf("%s\n", label);
    for (int i = 1; i <= m_n; i++) 
      printf("%d ", m_data[i]);
    printf("\n");
  }
};

// Heap test
#if 0
int main()
{
  TopHeap<int, MyCmp> h;
  int v[10] = {5, 2, 7, 3, 4, 1, 8, 9, 6, 0};
  for (int i = 0; i < 10; i++)
    h.Insert(v[i]);
  h.Print("Heap:");
  for (int i = 0; i < 10; i++) {
    printf("%d: %d\n", i, h.ExtractMax());
  }
  return 0;
}
#endif


#endif
