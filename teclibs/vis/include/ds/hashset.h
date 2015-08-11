// hashset.h
// Set data structure using a hashtable.
// cpalomo@tecgraf.puc-rio.br
// Strongly based on hashtable implementation by celes@tecgraf.puc-rio.br,
// but more with a flavour of C++ interface.
// June 2011


#ifndef wds_hashset_h
#define wds_hashset_h

#include <cassert>
#include <iostream>
#include "defines.h"

// Hash set 
// KEY must be a concrete type.
// The KEY type must provide a method "operator int () const" or
// a method "operator const char* () const" to be used by the hash function.
// The method "operator == (const KEY&) const" can also be defined to be used for key comparison.
template <class KEY>
class DSAPI DsHashSet
{
public:
  /**< Iterator. */
  class Iterator {
  public:
    Iterator (const DsHashSet<KEY>* set = NULL, int cur_pos = -1);
    Iterator (const Iterator& rhs);
    bool Valid () const;
    Iterator& operator++ ();
    Iterator& operator++ (int i);
    KEY& operator* () const;
    bool operator== (const Iterator& rhs) const;
    bool operator!= (const Iterator& rhs) const;
  private:
    const DsHashSet<KEY>* m_set;
    int m_current;
    friend class Const_Iterator;
  };
  /**< Const iterator. */
  class Const_Iterator : public Iterator {
  public:
    Const_Iterator (const Iterator& it);
    const KEY& operator* () const;
  };

private:
  /**< Inner structures. */
  struct Field {
    unsigned empty : 1;
    unsigned reusable : 1;
    unsigned next : 30;
  };
  struct Entry {
    Field field;
    KEY key;
  };
  /**< Actual members. */
  int m_cardinality;
  int m_freespot;
  int m_table_size;
  Entry* m_table;
  static const Iterator ITERATOR_END;
public:
  friend class Iterator;

  // Create a new hashset.
  // The client may specify an initial size for the table
  DsHashSet (int size=2);

  // Destroy the hashset.
  ~DsHashSet ();

  // Insert key to set.
  void Insert (const KEY& key);

  // Check whether given key exists in set.
  bool Find (const KEY& key) const;

  // Erase given key from set.
  bool Erase (const KEY& key);

  // Erase given key from set -> ds-classes use Remove rather than Erase
  bool Remove (const KEY& key);

  // Clear the hashset, removing all set entries.
  void Clear ();

  // Return set's cardinality.
  int Size () const;

  // Return whether set is empty.
  bool Empty () const;

  // iterator
  Iterator Begin () const;
  const Iterator& End () const;

  // For debugging
  void Print (const char* label = 0) const;

private:
  bool IsPositionFree (int pos) const;
  void CreateTable ()
  {
    // instantiate hashtable
    m_table = new Entry[m_table_size];
    // initialize entries: all empty, not reusable, and next pointing to n.
    for (int i=0; i<m_table_size; ++i) {
       m_table[i].field.empty = 1;
       m_table[i].field.reusable = 0;
       m_table[i].field.next = m_table_size;
    }
  }
  int Hash (int v) const
  {
    return Hash((unsigned int)v);
  }
  int Hash (unsigned int v) const
  {
    return v%(m_table_size-1);
  }
  int Hash (long int v) const
  {
    return Hash((unsigned long int)v);
  }
  int Hash (unsigned long int v) const
  {
    return v%(m_table_size-1);
  }
  int Hash (long long v) const
  {
    return Hash((unsigned long long)v);
  }
  int Hash (unsigned long long v) const
  {
    return v%(m_table_size-1);
  }
  int Hash (const void* v) const
  {
    union {
      const void* v;
      unsigned int i;
    } u;
    u.v = v;
    return u.i%(m_table_size-1);
  }
  int Hash (float v) const
  {
    union {
      float v;
      unsigned int i;
    } u;
    u.v = v;
    return u.i%(m_table_size-1);
  }
  int Hash (double v) const
  {
    return Hash((float)v);
  }
  int Hash (const char* s) const
  {
    unsigned int h = (unsigned int)strlen(s);
    int step = (int)((h>>5)+1);
    for (int i=h; i>=step; i-=step)
      h = h ^ ((h<<5)+(h>>2)+(unsigned char)(s[i-1]));
    return h%(m_table_size-1);
  }
  int FindKey (int h, const KEY& key) const
  {
    // bucket is empty, return n to report
    if (m_table[h].field.empty)
      return m_table_size;
    //  traverse bucket to find tail
    while (h<m_table_size && !(m_table[h].key == key))
      h = m_table[h].field.next;
    return h;
  }
  void Rehash ()
  {
    int i;
    int old_size = m_table_size;
    Entry* old_table = m_table;
    // choose the growing rate
    float ratio = (float)(m_cardinality+1)/m_table_size;
    if (ratio < 0.4)
      m_table_size /= 2;
    else if (ratio > 0.9)
      m_table_size *= 2;

    CreateTable();
    m_cardinality = 0;
    for (i=0; i<old_size; ++i) {
      if (!old_table[i].field.empty && !old_table[i].field.reusable) {
        Insert(old_table[i].key); 
      }
    }
    delete [] old_table;
    m_freespot = 0;
  }

  int FindPrevious (int h, int n)
  {
    while ((int)m_table[h].field.next != n) {
      h = m_table[h].field.next;
    }
    return h;
  }
  int FreeSpot ()
  {
    // look for free spot, returning -1 when not available in current table
    // also updates current m_freespot after method call
    for (int i = m_freespot; i < m_table_size; ++i) {
      if (m_table[i].field.empty) {
        m_freespot = i+1;
        return i;
      }
    }
    // rehash when no freespot available (will allocate more space)
    Rehash();
    // return -1 to inform there was no free spot
    return -1;
  }
  int CountKeys ()
  {
    int n=0; 
    for (int i=0; i<m_table_size; ++i)
      if (!IsPositionFree(i))
        n++;
    return n;
  }
};

// public methods
template <class KEY> inline DsHashSet<KEY>::DsHashSet (int size)
: m_cardinality(0), m_freespot(0), m_table_size(size), m_table(0)
{
  CreateTable();
}

template <class KEY> inline DsHashSet<KEY>::~DsHashSet ()
{
  delete [] m_table;
}

template <class KEY> inline void DsHashSet<KEY>::Insert (const KEY& key)
{
  int h2;
  int h = Hash(key);
  int i = FindKey(h,key);
  if (i < m_table_size) {
    // TODO update cardinality correctly

    // key found inside table:
    // set as not reusable and increase cardinality
    if (m_table[i].field.empty || m_table[i].field.reusable)
      m_cardinality++;

    m_table[i].field.reusable = 0;
  }
  else if (m_table[h].field.empty) {
    // key not found, and bucket is empty:
    // store, set as not empty and increase cardinality
    m_table[h].field.empty = 0;
    m_table[h].key = key;
    m_cardinality++;
  }
  else if (m_table[h].field.reusable) {
    // key not found, and bucket is empty
    // set as not reusable and increase cardinality
    m_table[h].field.reusable = 0;
    m_table[h].key = key;
    m_cardinality++;
  }
  else if ((h2 = Hash(m_table[h].key)) == h) {
    int f = FreeSpot();
    if (f < 0) {
      // there was no free spot: call Insert again for newly allocated table
      Insert(key);
    }
    else {
      // found free spot: occupy it
      m_table[f].key = key;
      m_table[f].field.empty = 0;
      m_table[f].field.next = m_table[h].field.next;
      m_table[h].field.next = f;
      m_cardinality++;
    }
  }
  else { // h2 != h
    // bucket collision
    
    int f = FreeSpot();
    if (f < 0) {
      // there was no free spot: call Insert again for newly allocated table
      Insert(key);
    }
    else {
      // found free spot: occupy it
      int prev = FindPrevious(h2,h); 
      m_table[prev].field.next = f;
      m_table[f] = m_table[h];
      m_table[h].key = key;
      m_table[h].field.next = m_table_size;
      m_cardinality++;
    }
  }
}

template <class KEY>
const typename DsHashSet<KEY>::Iterator DsHashSet<KEY>::ITERATOR_END;

template <class KEY> inline bool DsHashSet<KEY>::Find (const KEY& key) const
{
  int h = Hash(key);
  int i = FindKey(h,key);
  return (i < m_table_size && !m_table[i].field.reusable);
}

template <class KEY> inline bool DsHashSet<KEY>::Erase (const KEY& key)
{
  int h = Hash(key);
  int i = FindKey(h,key);
  if (i < m_table_size && !m_table[i].field.reusable) {
    m_table[i].field.reusable = 1;
    m_cardinality--;
    return true;
  }
  return false;
}

template <class KEY> inline bool DsHashSet<KEY>::Remove (const KEY& key)
{
  return Erase(key);
}

template <class KEY> inline void DsHashSet<KEY>::Clear ()
{
  for (int i=0; i<m_table_size; ++i) {
    m_table[i].field.empty = 1;
    m_table[i].field.reusable = 0;
    m_table[i].field.next = m_table_size;
  }
  m_freespot = m_cardinality = 0;
}

template <class KEY> inline int DsHashSet<KEY>::Size () const
{
  return m_cardinality;
}

template <class KEY> inline bool DsHashSet<KEY>::Empty () const
{
  return Size() == 0;
}

template <class KEY>
typename DsHashSet<KEY>::Iterator DsHashSet<KEY>::Begin () const
{
  Iterator it(this, -1);
  it++;
  return it;
}

template <class KEY>
const typename DsHashSet<KEY>::Iterator& DsHashSet<KEY>::End () const
{
  return ITERATOR_END;
}

template <class KEY>
bool DsHashSet<KEY>::IsPositionFree (int pos) const
{
  assert(pos >=0 && pos < m_table_size);
  return m_table[pos].field.empty || m_table[pos].field.reusable;
}

template <class KEY>
inline void DsHashSet<KEY>::Print (const char* label) const
{
  if (label)
    std::cout << label << std::endl;

  std::cout << "# keys/Size = " << m_cardinality << "/" << m_table_size << std::endl;
  std::cout << "Free spot = " << m_freespot << std::endl;

  for (Const_Iterator it = Begin(); it != End(); it++)
    std::cout << *it << " ";
  std::cout << std::endl;
}

// Iterator implementation
template <class KEY>
DsHashSet<KEY>::Iterator::Iterator (const DsHashSet<KEY>* set, int cur_pos)
: m_set(set), m_current(cur_pos)
{
}

template <class KEY>
DsHashSet<KEY>::Iterator::Iterator (const Iterator& rhs)
: m_set(rhs.m_set), m_current(rhs.m_current)
{
}

template <class KEY>
bool DsHashSet<KEY>::Iterator::Valid () const
{
  return *this != m_set->End();
}

template <class KEY>
typename DsHashSet<KEY>::Iterator& DsHashSet<KEY>::Iterator::operator++ ()
{
  if (m_set) {
    for (int i = m_current+1; i < m_set->m_table_size; i++) {
      if (!m_set->IsPositionFree(i)) {
        m_current = i;
        return *this;
      }
    }
  }
  // reached end, or set is null
  m_current = -1;

  return *this;
}

template <class KEY>
typename DsHashSet<KEY>::Iterator& DsHashSet<KEY>::Iterator::operator++ (int i)
{
  return this->operator++();
}

template <class KEY>
KEY& DsHashSet<KEY>::Iterator::operator* () const
{
  // TODO should validate whether reached End or not
  return m_set->m_table[m_current].key;
}

template <class KEY>
bool DsHashSet<KEY>::Iterator::operator== (const Iterator& rhs) const
{
  return this->m_current == rhs.m_current;
}

template <class KEY>
bool DsHashSet<KEY>::Iterator::operator!= (const Iterator& rhs) const
{
  return !(*this == rhs);
}

template <class KEY>
DsHashSet<KEY>::Const_Iterator::Const_Iterator (const Iterator& it)
{
  this->m_set = it.m_set;
  this->m_current = it.m_current;
}

template <class KEY>
const KEY& DsHashSet<KEY>::Const_Iterator::operator* () const
{
  return this->m_set->m_table[this->m_current].key;
}

#endif
