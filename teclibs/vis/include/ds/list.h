//* List Data Structure
// Basic package project: data structure.
// TeCGraf/PUC-Rio,
// Jul 2002
// celes@tecgraf.puc-rio.br


#ifndef ds_list_h
#define ds_list_h

#ifdef TEC_UNAME_vc6
# pragma warning( disable : 4284 )
#endif

#include "defines.h"

// Class especification
 template <class TYPE> class DSAPI DsList;
// template <class TYPE> class DSAPI DsPooledList;
 template <class TYPE> class DSAPI DsListIterator;
 template <class TYPE> class DSAPI DsPList;
 template <class TYPE> class DSAPI DsPListIterator;


// Single list node
template <class TYPE>
class DSAPI dsListNode
{
 friend class DsList<TYPE>;
 //friend class DsPooledList<TYPE>;
 friend class DsListIterator<TYPE>;


 TYPE m_elm;
 dsListNode* m_next;

 dsListNode (TYPE elm)
 { 
  m_elm = elm;   // using assignment instead of copy constructor 
                 // to be compatible with the use of pooled lists
 } 
 ~dsListNode ()
 {
 }
};

//* List iterator
template <class TYPE>
class DSAPI DsListIterator
{
 friend class DsList<TYPE>;
 
 typedef dsListNode<TYPE> Node;

 Node* m_node;


public:

 DsListIterator ()
 : m_node(0) 
 { 
 }
 DsListIterator (Node* node)
 : m_node(node)
 {
 }
 ~DsListIterator () 
 {
 }
 DsListIterator& operator++ ()
 {
  m_node = m_node->m_next;
  return *this;
 }
 bool Valid () const
 {
  return m_node!=0;
 }
 TYPE& operator* () const
 {
  return m_node->m_elm;
 }
#if 1
 TYPE* operator-> () const
 {
  return &m_node->m_elm;
 }
#endif
 TYPE& Self () const
 {
  return operator*();
 }
 bool operator== (const DsListIterator& other) const
 {
  return m_node==other.m_node;
 }
 bool operator!= (const DsListIterator& other) const
 {
  return !operator==(other);
 }
 DsListIterator Next () const
 {
  return DsListIterator(m_node->m_next);
 }
};

#include <stdio.h>

//* List 
template <class TYPE>
class DSAPI DsList
{
 typedef dsListNode<TYPE> Node;
 Node* m_head;
 Node* m_tail;
  int m_size;

public:
 typedef DsListIterator<TYPE> Iterator;

 //* Creators
  //* Default creator
  // Creates an empty list.
 DsList ()
 : m_head(0), m_tail(0), m_size(0)
 {
 }
  //* Delete a list
  // It deletes all the elements in the list. 
 virtual ~DsList ()
 {
  Clear();
 }
 //* Is list empty? */
 bool IsEmpty ()
 {
   return m_head == 0;
 }
 //* Manipulators
  //* Insert
  // Inserts an element at the begining of the list.
 Iterator Insert (const TYPE& elm, int at=0)
 {
  if (at == 0)
  {
   Node* node = Create(elm); 
   node->m_next = m_head;
   m_head = node;
   if (!m_tail) 
    m_tail = m_head;
   m_size++;
   return Iterator(node);
  }
  else
  {
   Iterator it = Begin();
   for (int i=0;i<at-1; i++)
    ++it;
   return InsertAt(elm,it);
  }
 } 
  //* Append
  // Inserts an element at the end of the list.
 Iterator Append (const TYPE& elm)
 {
  Node* node = Create(elm); 
  node->m_next = 0;
  if (m_tail)
   m_tail->m_next = node;
  else
   m_head = node;
  m_tail = node;
  m_size++;
  return Iterator(node);
 } 

  //* InsertAt
  // Insert just after a given iterator
 Iterator InsertAt (const TYPE& elm, const Iterator& itr)
 {
  Node* node = Create(elm); 
  Node* ref = itr.m_node;
  m_size++;
  if (!ref)
   return Insert(elm);
  else
  {
   node->m_next = ref->m_next;
   ref->m_next = node;
   if (ref==m_tail)
    m_tail = node;
   return Iterator(node);
  }
 }

  //* Remove
  // Removes the element at the Begining of the list.
 bool Remove ()
 {
  if (m_head)
  {
   Node* node = m_head;
   m_head = node->m_next;
   if (!m_head) m_tail = 0;
   Release(node);
    m_size--;
   return true;
  }
  else
   return false;
 }

  //* Remove
  // Removes the element after the given iterator
 bool Remove (const Iterator& itr)
 {
  Node* prev = itr.m_node;
  if (!prev)
   return Remove();
  else
  {
   Node* curr = prev->m_next;
   if (curr)
   {
    if (prev)
     prev->m_next = curr->m_next;
    else
     m_head = curr->m_next;
    if (!curr->m_next)
     m_tail = prev;
    Release(curr);
        m_size--;
    return true;
   }
  }
  return false;
 }

  //* Remove
  // Removes the element (an O(n) procedure!)
 bool Remove (const TYPE& elm)
 {
  Node* prev;
  Node* curr;
  for (prev=0,curr=m_head; curr!= 0; prev=curr,curr=curr->m_next)
   if (curr->m_elm==elm)
    break;
  if (curr)
   return Remove(Iterator(prev));
  else
   return false;
 }
 //* Replace
 // Replaces element 'a' with element 'b' (an O(n) procedure!)
 bool Replace (const TYPE& a, const TYPE& b)
 {
  for (Node *curr=m_head; curr; curr=curr->m_next)
   if (curr->m_elm==a)
   {
    curr->m_elm=b;
    return true;
   }
  return false;
 }

  //* Find
  // Finds a element in the list (an O(n) procedure!)
 bool Find (const TYPE& elm)
 {
  Node* curr;
  for (curr=m_head; curr!= 0; curr=curr->m_next)
   if (curr->m_elm==elm)
    return true;
  return false;
 }

  //* Clear
  // Deletes all elements from the list.
 void Clear ()
 { 
  while (Remove())
   ;
 }

 //* Iterators

  //* Begin
  // Returns an iterator pointing to the first element 
  // in the list.
 Iterator Begin () const
 {
  return Iterator(m_head);
 }
  //* End
  // Returns an iterator pointing to the one-beyond-the-last 
  // element in the list.
 Iterator End ()
 {
  return Iterator(0);
 }
 int Size () const
 {
   return m_size;
 }

protected:
 virtual Node* Create (const TYPE& elm)
 {
  return new Node(elm);
 }

 virtual void Release (Node* node)
 {
  delete node;
 }

private:
 DsList (const DsList&);                // Do not allow copy
 DsList& operator= (const DsList&);     // Do not allow assignment

};

//* Pooled list 
/*
template <class TYPE>
class DSAPI DsPooledList : public DsList<TYPE>
{
 typedef dsListNode<TYPE> Node;
 Node* m_pool;
 
public:
 DsPooledList ()
 : m_pool(0)
 {
 }

 virtual ~DsPooledList ()
 {
 }

 void ClearAll ()
 {
  DsList<TYPE>::Clear();
  while (m_pool) {
   Node* n = m_pool->m_next;
   delete m_pool;
   m_pool = n;
  }
 }


protected:
 virtual Node* Create (const TYPE& elm)
 {
  if (m_pool) {
   Node* n = m_pool;
   m_pool = n->m_next;
   n->m_elm = elm;
   return n;
  }
  else {
   return new Node(elm);
  }
 }

 virtual void Release (Node* node)
 {
  node->m_next = m_pool;
  m_pool = node;
 }
};
*/

//* Ponter list iterator
template <class TYPE>
class DSAPI DsPListIterator
{
 friend class DsPList<TYPE>;

 typedef DsListIterator<void*> BaseItr;

 BaseItr m_itr;


public:
 DsPListIterator ()
 : m_itr() 
 { 
 }
 DsPListIterator (DsListIterator<void*>& itr)
 : m_itr(itr)
 {
 }
 ~DsPListIterator () 
 {
 }
 DsPListIterator& operator++ ()
 {
  ++m_itr;
  return *this;
 }
 bool Valid () const
 {
  return m_itr.Valid();
 }
 TYPE& operator* () const
 {
  void* p = m_itr.Self();
  return *((TYPE*)p);
 }
 TYPE* operator-> () const
 {
  void* p = m_itr.Self();
  return (TYPE*)p;
 }
 TYPE* Self () const
 {
  return operator->();
 }
 bool operator== (const DsPListIterator& other) const
 {
  return m_itr==other.m_itr;
 }
 bool operator!= (const DsPListIterator& other) const
 {
  return !operator==(other);
 }
 DsPListIterator Next () const
 {
  return DsPListIterator(m_itr.Next());
 }
};

//* PList 
// List of pointers
template <class TYPE>
class DSAPI DsPList : public DsList<void*> //DsPooledList<void*>
{
 //typedef DsPooledList<void*> Base;
 typedef DsList<void*> Base;
 typedef dsListNode<void*> Node;

public:
 typedef DsPListIterator<TYPE> Iterator;

 //* Creators
  //* Default creator
  // Creates an empty list.
 DsPList ()
 {
 }
  //* Delete a list
  // It deletes all the elements in the list. 
 virtual ~DsPList ()
 {
 }

 //* Manipulators
  //* Insert
  // Inserts an element at the begining of the list.
 Iterator Insert (const TYPE* elm, int at=0)
 {
  Base::Iterator i = Base::Insert((void*)elm,at);
  return Iterator(i);
 }
  //* Append
  // Inserts at the end of the list.
 Iterator Append (const TYPE* elm)
 {
  Base::Iterator i = Base::Append((void*)elm);
  return Iterator(i);
 }
  //* InsertAt
  // Inserts an element just after the given element.
 Iterator InsertAt (const TYPE* elm, const Iterator& itr)
 {
  Base::Iterator i((void*)itr.Self());
  i = Base::Insert((void*)elm,i);
  return Iterator(i);
 }

  //* Remove
  // Removes from Begining
 bool Remove ()
 {
  return Base::Remove();
 }

  //* Remove
  // Removes the given element. 
 bool Remove (const TYPE* elm)
 {
  return Base::Remove((void*)elm);
 }
 bool Replace (const TYPE* a, const TYPE* b)
 {
  return Base::Replace((void*)a,(void*)b);
 }
   //* Clear
  // Deletes all elements from the list.
 void Clear ()
 { 
  while (Remove())
   ;
 }

 //* Iterators

  //* Begin
  // Returns an iterator pointing to the first element 
  // in the list.
 Iterator Begin () const
 {
  Base::Iterator i = Base::Begin();
  return Iterator(i);
 }
  //* End
  // Returns an iterator pointing to the one-beyond-the-last 
  // element in the list.
 Iterator End ()
 {
  Base::Iterator i;
  return Iterator(i);
 }
};

#endif
