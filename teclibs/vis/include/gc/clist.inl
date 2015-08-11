#include <exception>
#include <stdio.h>

#define CLISTTEMPLATE template <class TYPE>
#define CLISTCLASS    gcCList <TYPE>

//-----------------------------//
// Constructors and Destructor //
//-----------------------------//

CLISTTEMPLATE CLISTCLASS::gcCList (void) :
m_size(0)
{
  m_entrySentinel = new Node;
  m_entrySentinel->m_data = TYPE();
  m_entrySentinel->m_next = m_entrySentinel;
  m_entrySentinel->m_prev = m_entrySentinel;
}


CLISTTEMPLATE CLISTCLASS::~gcCList (void)
{
  Clear();
  delete m_entrySentinel;
}

//--------------//
// List access //
//--------------//

CLISTTEMPLATE void CLISTCLASS::InsertFirst (const TYPE& newElement)
{
  Node* newNode = new Node;
  newNode->m_data = newElement;
  newNode->m_next = m_entrySentinel->m_next;
  newNode->m_prev = m_entrySentinel;
  m_entrySentinel->m_next->m_prev = newNode;
  m_entrySentinel->m_next = newNode;
  ++m_size;
}

CLISTTEMPLATE void CLISTCLASS::InsertLast (const TYPE& newElement)
{
  Node* newNode = new Node;
  newNode->m_data = newElement;
  newNode->m_next = m_entrySentinel;
  newNode->m_prev = m_entrySentinel->m_prev;
  m_entrySentinel->m_prev->m_next = newNode;
  m_entrySentinel->m_prev = newNode;
  ++m_size;
}

CLISTTEMPLATE void CLISTCLASS::InsertBefore (const TYPE& newElement, const Iterator& position)
{
  if (position.m_owner != this || position.m_node == m_entrySentinel) return;
  Node* baseNode = position.m_node;
  Node* newNode  = new Node;
  newNode->m_data = newElement;
  newNode->m_prev = baseNode->m_prev;
  newNode->m_next = baseNode;
  baseNode->m_prev->m_next = newNode;
  baseNode->m_prev = newNode;
  ++m_size;
}

CLISTTEMPLATE void CLISTCLASS::InsertAfter (const TYPE& newElement, const Iterator& position)
{
  if (position.m_owner != this || position.m_node == m_entrySentinel) return;
  Node* baseNode = position.m_node;
  Node* newNode  = new Node;
  newNode->m_data = newElement;
  newNode->m_next = baseNode->m_next;
  newNode->m_prev = baseNode;
  baseNode->m_next->m_prev = newNode;
  baseNode->m_next = newNode;
  ++m_size;
}

CLISTTEMPLATE TYPE CLISTCLASS::RemoveFirst (void)
{
  if (m_size == 0) {return TYPE();}
  Node* TempNode = m_entrySentinel->m_next;
  TYPE FirstData = TempNode->m_data;
  m_entrySentinel->m_next = TempNode->m_next;
  TempNode->m_next->m_prev = m_entrySentinel;
  delete TempNode;
  --m_size;
  return FirstData;
}

CLISTTEMPLATE TYPE CLISTCLASS::RemoveLast (void)
{
  if (m_size == 0) {return TYPE();}
  Node* TempNode = m_entrySentinel->m_prev;
  TYPE LastData = TempNode->m_data;
  m_entrySentinel->m_prev = TempNode->m_prev;
  TempNode->m_prev->m_next = m_entrySentinel;
  delete TempNode;
  --m_size;
  return LastData;
}

CLISTTEMPLATE TYPE CLISTCLASS::RemoveGoNext (Iterator& position)
{
  if (position.m_owner != this || position.m_node == m_entrySentinel) return TYPE();
  Node* BaseNode = position.m_node;
  TYPE  BaseData = BaseNode->m_data;
  BaseNode->m_prev->m_next = BaseNode->m_next;
  BaseNode->m_next->m_prev = BaseNode->m_prev;
  if (BaseNode == position.m_entry)
  {
    position.m_entry = position.m_entry->m_next;
    if (position.m_entry == m_entrySentinel) position.m_entry = position.m_entry->m_next;
  }
  position.m_node = position.m_node->m_next;
  if (position.m_node == m_entrySentinel) position.m_node = position.m_node->m_next;
  delete BaseNode;
  --m_size;
  return BaseData;
}

CLISTTEMPLATE TYPE CLISTCLASS::RemoveGoPrev (Iterator& position)
{
  if (position.m_owner != this || position.m_node == m_entrySentinel) return TYPE();
  Node* BaseNode = position.m_node;
  TYPE  BaseData = BaseNode->m_data;
  BaseNode->m_prev->m_next = BaseNode->m_next;
  BaseNode->m_next->m_prev = BaseNode->m_prev;
  if (BaseNode == position.m_entry)
  {
    position.m_entry = position.m_entry->m_prev;
    if (position.m_entry == m_entrySentinel) position.m_entry = position.m_entry->m_prev;
  }
  position.m_node = position.m_node->m_prev;
  if (position.m_node == m_entrySentinel) position.m_node = position.m_node->m_prev;
  delete BaseNode;
  --m_size;
  return BaseData;
}

CLISTTEMPLATE bool CLISTCLASS::Remove (const TYPE& element)
{
  if (m_size == 0) return false;

  Iterator position = Find(element);
  if (!position.IsValid()) return false;
  RemoveGoNext(position);
  return true;
}

CLISTTEMPLATE bool CLISTCLASS::Replace (const TYPE& oldElement, const TYPE& newElement)
{
  if (m_size == 0) return false;

  Iterator position = Find(oldElement);
  if (!position.IsValid()) return false;
  position.m_node->m_data = newElement;
  return true;
}

CLISTTEMPLATE TYPE CLISTCLASS::GetFirst (void) const
{
  return (m_entrySentinel->m_next->m_data);
}

CLISTTEMPLATE TYPE CLISTCLASS::GetLast (void) const
{
  return (m_entrySentinel->m_prev->m_data);
}

CLISTTEMPLATE bool CLISTCLASS::IsEmpty (void) const
{
  return (m_size == 0);
}

CLISTTEMPLATE bool CLISTCLASS::HasElements (void) const
{
  return (m_size > 0);
}

CLISTTEMPLATE unsigned int CLISTCLASS::GetSize (void) const
{
  return m_size;
}

CLISTTEMPLATE void CLISTCLASS::Clear (void)
{
  Node* CurrentNode = m_entrySentinel->m_next;

  while (CurrentNode != m_entrySentinel)
  {
    Node* TempNode = CurrentNode;
    CurrentNode = CurrentNode->m_next;
    delete TempNode;
  }
  m_entrySentinel->m_next = m_entrySentinel;
  m_entrySentinel->m_prev = m_entrySentinel;
  m_size = 0;
}

CLISTTEMPLATE bool CLISTCLASS::CopyToArray (TYPE* allocatedCopy) const
{
  if (!allocatedCopy) return false;

  try
  {
    Node* CurrentNode = m_entrySentinel->m_next;
    for (unsigned int i = 0; i < m_size; ++i)
    {
      allocatedCopy[i] = CurrentNode->m_data;
      CurrentNode      = CurrentNode->m_next;
    }
  }
  catch (...)
  {
    return false;
  }

  return true;
}

//-----------------------//
// Obtaining an iterator //
//-----------------------//

CLISTTEMPLATE gcCListIterator<TYPE> CLISTCLASS::Begin (void)
{
  return Iterator(this, m_entrySentinel->m_next);
}

CLISTTEMPLATE gcCListIterator<TYPE> CLISTCLASS::End (void)
{
  return Iterator(this, m_entrySentinel->m_prev);
}

CLISTTEMPLATE gcCListIterator<TYPE> CLISTCLASS::Find (const TYPE& element)
{
  Node* CurrentNode = m_entrySentinel->m_next;

  while (CurrentNode != m_entrySentinel && !(CurrentNode->m_data == element))
  {
    CurrentNode = CurrentNode->m_next;
  }

  return Iterator(this, CurrentNode);
}

CLISTTEMPLATE gcCListIterator<TYPE> CLISTCLASS::FindReverse (const TYPE& element)
{
  Node* CurrentNode = m_entrySentinel->m_prev;

  while (CurrentNode != m_entrySentinel && !(CurrentNode->m_data == element))
  {
    CurrentNode = CurrentNode->m_prev;
  }

  return Iterator(this, CurrentNode);
}

CLISTTEMPLATE gcCListIterator<TYPE> CLISTCLASS::FindAfter (const TYPE& element, const Iterator& position)
{
  if (position.m_owner != this || position.m_node == m_entrySentinel) return Iterator(this, m_entrySentinel);

  Node* CurrentNode = position.m_node;

  do
  {
    CurrentNode = CurrentNode->m_next;
    if (CurrentNode == m_entrySentinel) CurrentNode = CurrentNode->m_next;
    if (CurrentNode->m_data == element && CurrentNode != position.m_entry) return Iterator(this,CurrentNode);
  }
  while (CurrentNode != position.m_entry);

  return Iterator(this, m_entrySentinel);
}

CLISTTEMPLATE gcCListIterator<TYPE> CLISTCLASS::FindBefore (const TYPE& element, const Iterator& position)
{
  if (position.m_owner != this || position.m_node == m_entrySentinel) return Iterator(this, m_entrySentinel);

  Node* CurrentNode = position.m_node;

  do
  {
    CurrentNode = CurrentNode->m_prev;
    if (CurrentNode == m_entrySentinel) CurrentNode = CurrentNode->m_prev;
    if (CurrentNode->m_data == element && CurrentNode != position.m_entry) return Iterator(this,CurrentNode);
  }
  while (CurrentNode != position.m_entry);

  return Iterator(this, m_entrySentinel);
}

//----------------------//
// Obtaining debug info //
//----------------------//

CLISTTEMPLATE void CLISTCLASS::PrintInfo (void) const
{
  printf("<Circular List Information>\n");
  printf("List size: %u\n", GetSize());
}

#undef CLISTCLASS
#undef CLISTTEMPLATE
