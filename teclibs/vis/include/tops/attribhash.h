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

// Based on TopHash ("hash.h")

#ifndef TOP_ATTRIB_HASH_H
#define TOP_ATTRIB_HASH_H

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include "defines.h"

// Hash table
// Both KEY and VALUE must be concrete types.
// The KEY type must provide a method "operator int () const" or
// a method "operator const char* () const" to be used by the hash function.
// The method "operator == (const KEY&) const" can also be defined to be used for key comparison.
template <class KEY>
class TOPSH_API TopAttribHash
{
 struct Field {
  unsigned empty : 1;
  unsigned reusable : 1;
  unsigned next : 30;
 };
 struct KeyEntry {
  Field field;
  KEY key;
  //VALUE value;
 };
 int m_current;
 int m_freespot;
 int m_initsize;
 int m_size;
 unsigned char* m_buffer;
 unsigned char* m_table;
 bool m_error;
 int m_valuesize; 
 int m_entrysize;
 bool m_reset_size;

public:
//TODO  
  // If ok, returns 1, else 0.
//  typedef int (*NewValueFunc) (void* value);
//  typedef int (*FreeValueFunc) (void* value);

 // Creates a new hash table
 // The client may specify an initial size for the table
 TopAttribHash (int valuesize, int size = 2); 
//      NewValueFunc newfunc, FreeValueFunc freefunc);

 // Destroys the hash table
 ~TopAttribHash ();

 // Sets/Updates the value associated to the given key
 bool  Set (const KEY& key, const void* value);

 // Returns the value associated to the given key
 void* Get (const KEY& key);

 // Removes the entry associated to the given key from the table
 bool  Remove (const KEY& key);

 // Moves an entry to another key in the table
 bool  Move (const KEY& src_key, const KEY& dst_key);

 // Checks if there is an entry in the table associated to he given key
 bool  Find (const KEY& key);

 // Allows the client to traverse all entries in the table.
 // General pattern:
 //    KEY k;
 //    if (h.First(&k)) do {
 //      [VALUE v = h.Get(k);]
 //      ...
 //    } while (h.Next(&k));
 // Note: passing a null pointer to method 'First' allows the client to check if the table is not empty.
 bool  First (KEY* key=0);
 bool  Next (KEY* key);

 // Clears the hash, removing all table entries.
 void Clear ();

 // Trims the amount of allocated memory to a value
 // closer to the number of used entries
 bool TrimToSize ();

 bool GetError () const
 {
   return m_error;
 }

 // For debugging
 int GetNumberOfKeys ()
 {
  return CountKeys();
 }
 int GetAllocSize ()
 {
  return m_size;
 }
 void Print (const char* label = 0)
 {
  if (label)
   printf("%s\n",label);
  printf("# keys/Size = %d/%d\n", CountKeys(), m_size);
  printf("Free spot = %d\n\n", m_freespot);
 }

private:
 KeyEntry* KeyEntryAt (int i) const
 {
  return (KeyEntry*) &m_table[i*m_entrysize];
 }
 void* ValueAt (int i) const
 {
  return &m_table[i*m_entrysize + sizeof(KeyEntry)];
 }
 bool CreateTable ()
 {
  if (!m_buffer) {
   m_buffer = new unsigned char[m_entrysize];
   if (!m_buffer) {
    m_error = true;
    return false;
   }
  }
  m_table = new unsigned char[m_size*m_entrysize];
  if (!m_table) {
   m_error = true;
   return false;
  }
  for (int i=0; i<m_size; ++i) {
   KeyEntry* kentry = KeyEntryAt(i);
   kentry->field.empty = 1;
   kentry->field.reusable = 0;
   kentry->field.next = m_size;
  }
  return true;
 }
 int Hash (int v)
 {
  return v%(m_size-1);
 }
 int Hash (unsigned int v)
 {
  return v%(m_size-1);
 }
 int FindKey (int h, const KEY& key)
 {
  if (KeyEntryAt(h)->field.empty)
   return m_size;
  while (h<m_size && !(KeyEntryAt(h)->key == key))
   h = KeyEntryAt(h)->field.next;
  return h;
 }
 bool Rehash ()
 {
  int i;
  int n = CountKeys(); 
  int old_size = m_size;
  unsigned char* old_table = m_table;
  // choose the growing rate
  if (m_reset_size) {
    m_size = m_initsize;
    m_reset_size = false;
  }
  float ratio = (float)(n+1)/m_size;
  if (ratio < 0.4)
   m_size /= 2;
  else {
   while (ratio > 0.9) {
    m_size *= 2;
    ratio = (float)(n+1)/m_size;
   }
  }
  if (!CreateTable())
    return false;
  for (i=0; i<old_size; ++i) {
   KeyEntry* old_kentry = (KeyEntry*) &old_table[i*m_entrysize];
   if (!old_kentry->field.empty && !old_kentry->field.reusable) {
    void* old_value = &old_table[i*m_entrysize + sizeof(KeyEntry)];
    if (!SetAux(old_kentry->key, old_value))
     return false;
   }
  }
  delete [] old_table;
  m_freespot = 0;
  return true;
 }
 int FindPrevious (int h, int n)
 {
  while ((int) KeyEntryAt(h)->field.next != n) {
   h = KeyEntryAt(h)->field.next;
  }
  return h;
 }
 int FreeSpot ()
 {
  for (int i = m_freespot; i < m_size; ++i) {
   if (KeyEntryAt(i)->field.empty) {
    m_freespot = i+1;
    return i;
   }
  }
  Rehash();
  return -1;
 }
 int CountKeys ()
 {
  int n=0; 
  for (int i=0; i<m_size; ++i)
   if (!KeyEntryAt(i)->field.empty && !KeyEntryAt(i)->field.reusable)
    n++;
  return n;
 }
 bool SetAux (const KEY& key, const void* value)
 {
  int h2;
  int h = Hash(key);
  int i = FindKey(h,key);
  if (i < m_size) {
   memcpy(ValueAt(i), value, m_valuesize);
   KeyEntryAt(i)->field.reusable = 0;
  }
  else if (KeyEntryAt(h)->field.empty) {
   KeyEntryAt(h)->field.empty = 0;
   KeyEntryAt(h)->key = key;
   memcpy(ValueAt(h), value, m_valuesize);
  }
  else if (KeyEntryAt(h)->field.reusable) {
   KeyEntryAt(h)->field.reusable = 0;
   KeyEntryAt(h)->key = key;
   memcpy(ValueAt(h), value, m_valuesize);
  }
  else if ((h2 = Hash(KeyEntryAt(h)->key)) == h)
  {
   int f = FreeSpot();
   if (m_error)
     return false;
   if (f < 0) {
    if (!SetAux(key,value))
     return false;
   }
   else {
    KeyEntry* kentryf = KeyEntryAt(f);
    KeyEntry* kentryh = KeyEntryAt(h);
    kentryf->key = key;
    memcpy(ValueAt(f), value, m_valuesize);
    kentryf->field.empty = 0;
    kentryf->field.next = kentryh->field.next;
    kentryh->field.next = f;
   }
  }
  else { // h2 != h
   int f = FreeSpot();
   if (m_error)
     return false;
   if (f < 0) {
    if (!SetAux(key,value))
     return false;
   }
   else {
    int prev = FindPrevious(h2,h); 
    KeyEntry* kentryf = KeyEntryAt(f);
    KeyEntry* kentryh = KeyEntryAt(h);   
    KeyEntryAt(prev)->field.next = f;
    kentryf->field = kentryh->field;
    kentryf->key = kentryh->key;
    memcpy(ValueAt(f), ValueAt(h), m_valuesize);
    kentryh->key = key;
    memcpy(ValueAt(h), value, m_valuesize);
    kentryh->field.next = m_size;
   }
  }
  return true;
 }
};

// public methods
template <class KEY> 
inline TopAttribHash<KEY>::TopAttribHash (int valuesize, int size)
: m_current(0), m_freespot(0), m_initsize(size), m_size(size), 
  m_buffer(0), m_table(0), m_error(false), m_valuesize(valuesize),
  m_entrysize(sizeof(KeyEntry) + valuesize), m_reset_size(false)
{
 CreateTable();
}

template <class KEY> inline TopAttribHash<KEY>::~TopAttribHash ()
{
 if (m_buffer)
  delete m_buffer;
 delete [] m_table;
}

template <class KEY> inline void* TopAttribHash<KEY>::Get (const KEY& key)
{
 int h = Hash(key);
 int i = FindKey(h,key);
 return i<m_size && !KeyEntryAt(i)->field.reusable ? ValueAt(i) : NULL;
}

template <class KEY> inline bool TopAttribHash<KEY>::Find (const KEY& key)
{
 int h = Hash(key);
 int i = FindKey(h,key);
 return (i < m_size && !KeyEntryAt(i)->field.reusable);
}

template <class KEY> inline bool TopAttribHash<KEY>::Set (const KEY& key, const void* value)
{
 memcpy(m_buffer,value,m_valuesize);
 return SetAux(key,m_buffer);
}

template <class KEY> inline bool TopAttribHash<KEY>::Remove (const KEY& key)
{
 int h = Hash(key);
 int i = FindKey(h,key);
 if (i < m_size && !KeyEntryAt(i)->field.reusable) {
  KeyEntryAt(i)->field.reusable = 1;
  return true;
 }
 return false;
}

template <class KEY> inline bool TopAttribHash<KEY>::Move (const KEY& src_key, const KEY& dst_key)
{
 void* data = Get(src_key);
 if (data) {
  if (!Set(dst_key, data))
   return false;
  if (!Remove(src_key))
   return false;
 }
 return true;
}

template <class KEY> inline bool TopAttribHash<KEY>::First (KEY* key)
{
 for (int i=0; i<m_size; ++i) {
  if (!KeyEntryAt(i)->field.empty && !KeyEntryAt(i)->field.reusable) {
   m_current = i;
   if (key) *key = KeyEntryAt(i)->key;
   return true;
  }
 }
 return false;
}

template <class KEY> inline bool TopAttribHash<KEY>::Next (KEY* key)
{
 int i;
 KeyEntry* kentry = KeyEntryAt(m_current);
 if (!kentry->field.empty && !kentry->field.reusable && kentry->key==*key)
  i = m_current;
 else
  i = FindKey(Hash(key),*key);

 for (++i; i<m_size; ++i) {
  if (!KeyEntryAt(i)->field.empty && !KeyEntryAt(i)->field.reusable) {
   m_current = i;
   *key = KeyEntryAt(i)->key;
   return true;
  }
 }
 return false;
}

template <class KEY> inline void TopAttribHash<KEY>::Clear ()
{
 for (int i=0; i<m_size; ++i) {
  KeyEntry* kentry = KeyEntryAt(i);
  kentry->field.empty = 1;
  kentry->field.reusable = 0;
  kentry->field.next = m_size;
 }
 m_current = m_freespot = 0;
}

template <class KEY> inline bool TopAttribHash<KEY>::TrimToSize ()
{
 int i;
 int n = CountKeys(); 
 int new_size = (int) (1.125*(n+1));
 float ratio = (float)(n+1)/new_size;
 if (ratio >= 0.9)
   new_size *= 2;
 if (new_size < m_size) {
  // Rehash
  int old_size = m_size;
  m_size = new_size;
  unsigned char* old_table = m_table;
  if (!CreateTable())
    return false;
  for (i=0; i<old_size; ++i) {
   KeyEntry* old_kentry = (KeyEntry*) &old_table[i*m_entrysize];
   if (!old_kentry->field.empty && !old_kentry->field.reusable) {
    void* old_value = &old_table[i*m_entrysize + sizeof(KeyEntry)];
    if (!Set(old_kentry->key,old_value))
     return false;
   }
  }
  delete [] old_table;
  m_freespot = 0;
  m_reset_size = true;
 }
 return true;
}

#endif

