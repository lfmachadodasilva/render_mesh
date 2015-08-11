// Dynamic Heap (priority queue)
// Object-like elements version
// Oct 2009

#ifndef DS_HEAP_2_H
#define DS_HEAP_2_H

#include "array.h"

/**
 * Min-heap template.
 * TYPE must be a pointer to an object which implements the following methods:
 *
 * - void SetHeapPosition (int pos): informs the object its current heap
 *                                   position, -1 if not on heap.
 * - int GetHeapPosition () const: obtains the object's current heap position,
 *                                 -1 if not on heap.
 * - bool operator> (TYPE e) const: compares the object with another object.
 *                                  must return true if the object is 'bigger',
 *                                  in other words, if it has a lower priority
 *                                  than 'c'.
 * - bool operator< (TYPE e) const: compares the object with another object.
 *                                  must return true if the object is 'smaller',
 *                                  in other words, if it has a higher priority
 *                                  than 'c'.
 *
 * This is only necessary if objects can change their priority while using the heap.
 * This way, given an object, it is possible to inform of priority changes via the
 * PriorityChanged (TYPE item) method.
 * It also enables the user to remove an item which is not the root from the heap.
 */
template <class TYPE>
class DSAPI DsHeap2
{
public:
  /**
   * Constructor.
   */
  DsHeap2 ()
  {
  }
  /**
   * Destructor.
   */
  virtual ~DsHeap2 ()
  {
  }
  /**
   * Obtains the root item (item with higher priority) and stores on variable 'item'.
   * Returns 'true' if successful, 'false' otherwise.
   */
  bool Root (TYPE& item)
  {
    if (m_array.Size() == 0)
      return false;
    item = m_array[0];
    return true;
  }
  /**
   * Inserts an item on the heap.
   */
  void Insert (TYPE item)
  {
    m_array.Append(item);
    int at = m_array.Size() - 1;
    item->SetHeapPosition(at);
    Up(at);
  }
  /**
   * Removes the root item from the heap, preparing the heap
   * for a new query on the root item.
   * Returns 'false' if the method was called on a empty heap,
   * 'true' otherwise.
   */
  bool Remove ()
  {
    if (m_array.Size() == 0)
      return false;
    m_array[0]->SetHeapPosition(-1);
    int lastindex = m_array.Size()-1;
    TYPE last = m_array[lastindex];
    m_array.Resize(lastindex);
    if (m_array.Size() != 0) {
      SetNewElem(0, last);
      Down(0);
    }
    return true;
  }
  /**
   * Removes all items from the heap.
   */
  void Clear ()
  {
    m_array.Empty();
  }
  /**
   * Returns the number of items on the heap.
   */
  int Size () const
  {
    return m_array.Size();
  }
  TYPE Get (int i) const
  {
    return m_array.Get(i);
  }
  /**
   * Informs if the heap is empty.
   */
  bool IsEmpty () const
  {
    return m_array.Size() == 0;
  }
  /**
   * Informs a change in the priority of item 'item'.
   */
  void PriorityChanged (TYPE item)
  {
    int currpos = item->GetHeapPosition();
    assert(0 <= currpos && currpos < m_array.Size());
    int at = Up(currpos);
    if (at == currpos) // if item went up, it won't go down
      Down(at);
  }
  /**
   * Removes an item from the heap. It can be any item
   * still on the heap.
   */
  void RemoveElement (TYPE item)
  {
    int olditempos = item->GetHeapPosition();
    assert(olditempos >= 0);
    int lastindex = m_array.Size()-1;
    TYPE last = m_array[lastindex];
    m_array.Resize(lastindex);
    if (m_array.Size() != 0 && olditempos != lastindex) {
      SetNewElem(olditempos, last);
      PriorityChanged(last);
    }
    item->SetHeapPosition(-1);
  }
private:
  int Up (int at)
  {
    if (m_array.Size() <= 1)
      return at;
    const TYPE curr = m_array[at];
    int parent;
    while (at && (*m_array[(parent = (at-1)/2)]) > curr) // test against parent
    {
      SetNewElem(at, m_array[parent]); // put parent down
      at = parent; // put current index up
    }
    SetNewElem(at, curr);
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
      if (child < last && (*m_array[child]) > m_array[child+1])
        child++;
      if (*curr < m_array[child])
        break;
      SetNewElem(at, m_array[child]); // put child up
      at = child; // put current index down
    }
    SetNewElem(at, curr);
    return at; // return new position
  }
  void SetNewElem (int pos, TYPE item)
  {
    assert(pos < m_array.Size());
    m_array[pos] = item;
    item->SetHeapPosition(pos);
  }
private:
  DsArray<TYPE> m_array;
};

#endif

