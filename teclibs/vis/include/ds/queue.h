// queue.h
// Implements a queue using dynamic array.
// fabraham@tecgraf.puc-rio.br
// Mar 2004

#ifndef DS_QUEUE_H
#define DS_QUEUE_H

#include "array.h"
#include "pool.h"

template <class TYPE> struct DsQueueNode
{
  DsQueueNode* next;
  TYPE data;
};

template <class TYPE> class DsQueue;

template <class TYPE> class DSAPI DsQueueIterator
{
public:
  bool Valid () const
  {
    return m_curr != NULL;
  }
  void Next ()
  {
    if (Valid())
      m_curr = m_curr->next;
  }
  TYPE& operator* () const
  {
    return m_curr->data;
  }
  TYPE* operator-> () const
  {
    return &m_curr->data;
  }
  TYPE& Self () const
  {
    return operator*();
  }
protected:
  DsQueueIterator (DsQueueNode<TYPE>* first)
  {
    m_curr = first;
  }
private:
  DsQueueNode<TYPE>* m_curr;
  friend class DsQueue<TYPE>;
};

template <class TYPE>
class DSAPI DsQueue
{
private:
	DsPool<DsQueueNode<TYPE> > m_pool; 
	DsQueueNode<TYPE>* m_first;
	DsQueueNode<TYPE>* m_last;
	int m_size;
public:
  typedef DsQueueIterator<TYPE> Iterator;
public:
	DsQueue () :
	m_first(NULL),
	m_last(NULL),
	m_size(0)
	{
	}
	~DsQueue ()
	{
		DsQueueNode<TYPE>* curr = m_first;
		DsQueueNode<TYPE>* todel;
		while(curr != NULL)
		{
			todel = curr;
			curr = curr->next;
			m_pool.Release(todel);
		}
	}
	void Enqueue (TYPE& elm)
	{
		DsQueueNode<TYPE>* newnode = m_pool.Create();
		newnode->data = elm;
		newnode->next = NULL;
		if (m_last)
		{
			m_last->next = newnode;
			m_last = newnode;
		}
		else
		{
			m_first = newnode;
			m_last = newnode;
		}
		m_size++;
	}
	void EnqueueConst (TYPE elm)
	{
		DsQueueNode<TYPE>* newnode = m_pool.Create();
		newnode->data = elm;
		newnode->next = NULL;
		if (m_last)
		{
			m_last->next = newnode;
			m_last = newnode;
		}
		else
		{
			m_first = newnode;
			m_last = newnode;
		}
		m_size++;
	}
	bool Dequeue (TYPE* data)
	{
		if (m_first)
		{
			*data = m_first->data;
			DsQueueNode<TYPE>* todel = m_first;
			m_first = m_first->next;
			if (m_first == NULL)
				m_last = NULL;
			m_pool.Release(todel);
      m_size--;
			return true;
		}
		else
			return false;
	}
	int Size () const
	{
		return m_size;
	}
  bool Empty () const
  {
    return Size()==0;
  }
  /**
   * Obtains the 'index'th item of the queue, where index=0 is the first element
   * and index=(Size()-1) is the last element on the queue.
   * Returns true if the element exists, false otherwise.
   * The result is placed at the address 'data'.
   * Warning: this method is O(n).
   */
	bool Get (int index, TYPE* data) const
	{
		int i = 0;
		DsQueueNode<TYPE>* curr = m_first;
		while (curr)
		{
			if (i==index)
			{
				*data = curr->data;
				return true;
			}
			curr = curr->next;
			i++;
		}
		return false;
	}
	void Clear ()
	{
		this->~DsQueue();
		m_first = m_last = NULL;
		m_size = 0;
	}
  Iterator Begin ()
  {
    return Iterator(m_first);
  }
protected:
  DsQueueNode<TYPE>* GetFirstNode () const
  {
    return m_first;
  }
};

#endif

