#ifndef GC_TEMPLATE_CLIST_H
#define GC_TEMPLATE_CLIST_H

#include "defines.h"

// Generic class implemented through a template
// Data structure: Circular double-chained List

// Features:
// - Each element is allocated and deallocated as needed (no pooling)
// - Sentinels to avoid null pointers

// Notes:
// - The type TYPE must be concrete

template <class TYPE> class gcCListIterator;
template <class TYPE> class gcCList;

//--------------------------//
// Double-Linked Node Class //
//--------------------------//

template <class TYPE>
class GCH_API gcDoubleNode
{
  // Internal Data

private:

  TYPE           m_data;
  gcDoubleNode* m_prev;
  gcDoubleNode* m_next;

  // Friend Classes

  friend class gcCList<TYPE>;
  friend class gcCListIterator<TYPE>;

};

//----------//
// Iterator //
//----------//

template <class TYPE>
class GCH_API gcCListIterator
{
  // Internal Data

  typedef gcDoubleNode<TYPE> Node;
  typedef gcCList<TYPE>      List;

  friend class gcCList<TYPE>;

  List* m_owner;
  Node* m_entry;
  Node* m_node;

  // Private Constructor (accessible only from gcCList<TYPE>)

  gcCListIterator (List* ownerList, Node* entryNode) :
  m_owner(ownerList),
  m_entry(entryNode),
  m_node(entryNode)
  {
  }

public:

  // Public Constructor and Destructor

  gcCListIterator  (void) : m_owner(0), m_entry(0), m_node(0) {}

  virtual ~gcCListIterator (void) {}

  // Operators

  TYPE&             operator *  (void)                          const {return m_node->m_data;}
  TYPE*             operator -> (void)                          const {return &m_node->m_data;}
  bool              operator == (const gcCListIterator& other) const {return (m_node == other.m_node && m_owner == other.m_owner);}
  bool              operator != (const gcCListIterator& other) const {return !operator == (other);}

  gcCListIterator& operator ++ (void)
  {
    if (IsValid())
    {
      m_node = m_node->m_next;
      if (!IsValid()) m_node = m_node->m_next;
    }
    return *this;
  }

  gcCListIterator& operator -- (void)
  {
    if (IsValid())
    {
      m_node = m_node->m_prev;
      if (!IsValid()) m_node = m_node->m_prev;
    }
    return *this;
  }

  gcCListIterator& operator += (unsigned int count)
  {
    if (!IsValid()) return *this;
    for (unsigned int i = 0; i < count; ++i)
    {
      m_node = m_node->m_next;
      if (!IsValid()) m_node = m_node->m_next;
    }
    return *this;
  }

  gcCListIterator& operator -= (unsigned int count)
  {
    if (!IsValid()) return *this;
    for (unsigned int i = 0; i < count; ++i)
    {
      m_node = m_node->m_prev;
      if (!IsValid()) m_node = m_node->m_prev;
    }
    return *this;
  }

  // Access functions

  TYPE& Self (void) const {return m_node->m_data;}

  bool HasNext (void) const
  {
    return (IsValid()
        &&  m_node->m_next != m_entry
        && (m_node->m_next != m_owner->m_entrySentinel || m_node->m_next->m_next != m_entry));
  }

  bool HasPrev (void) const
  {
    return (IsValid()
        &&  m_node->m_prev != m_entry
        && (m_node->m_prev != m_owner->m_entrySentinel || m_node->m_prev->m_prev != m_entry));
  }

  bool IsValid (void) const {return m_node != m_owner->m_entrySentinel;}

  // Creating more iterators

  gcCListIterator  Clone (void) const {return gcCListIterator(m_owner, m_node);}

  gcCListIterator  Next (void) const
  {
    Node* curNode = m_node;
    if (IsValid())
    {
      curNode = curNode->m_next;
      if (curNode == m_owner->m_entrySentinel) curNode = curNode->m_next;
    }
    return gcCListIterator(m_owner, curNode);
  }

  gcCListIterator  Prev (void) const
  {
    Node* curNode = m_node;
    if (IsValid())
    {
      curNode = curNode->m_prev;
      if (curNode == m_owner->m_entrySentinel) curNode = curNode->m_prev;
    }
    return gcCListIterator(m_owner, curNode);
  }

  gcCListIterator  Advance (unsigned int count) const
  {
    if (!IsValid()) return gcCListIterator(m_owner, m_node);

    Node* curNode = m_node;
    for (unsigned int i = 0; i < count; ++i)
    {
      curNode = curNode->m_next;
      if (curNode == m_owner->m_entrySentinel) curNode = curNode->m_next;
    }
    return gcCListIterator(m_owner, curNode);
  }

  gcCListIterator  Retreat (unsigned int count) const
  {
    if (!IsValid()) return gcCListIterator(m_owner, m_node);

    Node* curNode = m_node;
    for (unsigned int i = 0; i < count; ++i)
    {
      curNode = curNode->m_prev;
      if (curNode == m_owner->m_entrySentinel) curNode = curNode->m_prev;
    }
    return gcCListIterator(m_owner, curNode);
  }

};

//------//
// List //
//------//

template <class TYPE>
class GCH_API gcCList
{
  // Internal Data

  typedef gcDoubleNode<TYPE> Node;

  friend class gcCListIterator<TYPE>;

  Node*        m_entrySentinel;
  unsigned int m_size;

public:

  typedef gcCListIterator<TYPE> Iterator;

  // Constructors and Destructor

  gcCList(void);

  virtual ~gcCList(void);

  // List Access

  void	       InsertFirst    (const TYPE& newElement);
  void	       InsertLast     (const TYPE& newElement);
  void         InsertBefore   (const TYPE& newElement, const Iterator& position);
  void         InsertAfter    (const TYPE& newElement, const Iterator& position);
  TYPE	       RemoveFirst    (void);
  TYPE	       RemoveLast     (void);
  TYPE         RemoveGoNext   (Iterator& position);
  TYPE         RemoveGoPrev   (Iterator& position);
  bool         Remove         (const TYPE& element);                              // O(n)
  bool         Replace        (const TYPE& oldElement, const TYPE& newElement);   // O(n)
  TYPE	       GetFirst       (void) const;
  TYPE         GetLast        (void) const;

  bool	       IsEmpty        (void) const;
  bool	       HasElements    (void) const;
  unsigned int GetSize	    (void) const;

  void	       Clear          (void);

  bool         CopyToArray    (TYPE* allocatedCopy) const;

  // Obtaining an iterator

  Iterator     Begin          (void);
  Iterator     End            (void);
  Iterator     Find           (const TYPE& element);                             // O(n)
  Iterator     FindReverse    (const TYPE& element);                             // O(n)
  Iterator     FindAfter      (const TYPE& element, const Iterator& position);   // O(n)
  Iterator     FindBefore     (const TYPE& element, const Iterator& position);   // O(n)

  // Obtaining debug info

  void         PrintInfo      (void) const;

};

#include "clist.inl"

#endif // GC_TEMPLATE_CLIST_H
