// Dynamic Heap (priority queue)
// Jul 2002

#ifndef ds_heap_h
#define ds_heap_h

#include "array.h"

template <class TYPE, typename COMPAREFUNCTOR>
class DSAPI DsHeap
{
public:
  DsHeap (COMPAREFUNCTOR& compare)
  {
    m_compare = compare;
  }
  virtual ~DsHeap()
  {
  }
  /**
   * Obtains the top of the heap, stores on reference 'item'.
   * Returns true if there is such a heap top (heap is not empty), false otherwise.
   */
  bool Root (TYPE& item)
  {
    if (m_array.Size() == 0)
      return false;
    item = m_array[0];
    return true;
  }
  void Insert (TYPE item)
  {
    int at = m_array.Size();
    m_array.Append(item);
    Up(at);
  }
  int Remove ()
  {
    if (m_array.Size() == 0)
      return 0;
    int lastindex = m_array.Size()-1;
    TYPE last = m_array[lastindex];
    m_array.Resize(lastindex);
    if (m_array.Size() != 0)
    {
      m_array[0] = last;
      Down(0);
    }
    return 1;
  }
  void Clear ()
  {
    m_array.Clear();
  }
  int Size () const
  {
    return m_array.Size();
  }
  bool IsEmpty () const
  {
    return m_array.Size() == 0;
  }
  void PrioritiesChanged ()
  {
    // remove all items and store on 'oldarray'
    int n = Size();
    TYPE* oldarray = new TYPE[n];
    for (int i=0; i<n; ++i)
      oldarray[i] = m_array[i];

    Clear();
    // reinsert all items. new priorities will be considered.
    for (int i=0; i<n; ++i)
      Insert(oldarray[i]);

    delete [] oldarray;
  }
private:
  int Up (int at)
  {
    if (m_array.Size() <= 1)
      return at;
    const TYPE curr = m_array[at];
    int parent;
    while (at && m_compare(m_array[(parent = (at-1)/2)], curr) > 0) // test against parent
    {
      m_array[at] = m_array[parent]; // put parent Down
      at = parent; // put current index Up
    }
    m_array[at] = curr;
    return at;
  }
  int Down (int at)
  {
    if (m_array.Size() <= 1)
      return at;
    int last = m_array.Size() - 1;
    const TYPE curr = m_array[at];
    int child;
    while ((child = 2*at+1) <= last)
    {
      if (child < last && m_compare(m_array[child], m_array[child+1]) > 0)
        child++;
      if (m_compare(curr, m_array[child]) < 0)
        break;
      m_array[at] = m_array[child]; // put child Up
      at = child; // put current index Down
    }
    m_array[at] = curr;
    return at; // return new position
  }
private:
  DsArray<TYPE> m_array;
  COMPAREFUNCTOR m_compare;
};

#endif

