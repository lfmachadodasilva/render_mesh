// hash.h
// Hash table data structure
// celes@tecgraf.puc-rio.br
// 24 Feb 2005


#ifndef wds_hash_h
#define wds_hash_h

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include "defines.h"
#include <ds/stringkey.h>

// Hash table
// Both KEY and VALUE must be concrete types.
// The KEY type must provide a method "operator int () const" or
// a method "operator const char* () const" to be used by the hash function.
// The method "operator == (const KEY&) const" can also be defined to be used for key comparison.
template <class KEY, class VALUE>
class DSAPI DsHash
{
 struct Field {
  unsigned empty : 1;
  unsigned reusable : 1;
  unsigned next : 30;
 };
 struct Entry {
  Field field;
  KEY key;
  VALUE value;
 };
 int m_current;
 int m_freespot;
 int m_size;
 Entry* m_table;

public:
 // Creates a new hash table
 // The client may specify an initial size for the table
 DsHash (int size=2);

 // Destroys the hash table
 ~DsHash ();

 // Sets/Updates the value associated to the given key
 void  Set (const KEY& key, const VALUE& value);

 // Returns the value associated to the given key
 VALUE Get (const KEY& key) const;

 // Removes the entry associated to the given key from the table
 bool  Remove (const KEY& key);

 // Removes the entry associated to the given key from the table and
 // returns the entry's value.
 VALUE GetAndRemove (const KEY& key);

 // Checks if there is an entry in the table associated to the given key
 bool  Find (const KEY& key) const;

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

 // For debugging
 int GetNumberOfKeys ()
 {
  return CountKeys();
 }
 void Print (const char* label = 0)
 {
  if (label)
   printf("%s\n",label);
  printf("# keys/Size = %d/%d\n", CountKeys(), m_size);
  printf("Free spot = %d\n\n", m_freespot);
 }

private:
 void CreateTable ()
 {
  m_table = new Entry[m_size];
  for (int i=0; i<m_size; ++i) {
   m_table[i].field.empty = 1;
   m_table[i].field.reusable = 0;
   m_table[i].field.next = m_size;
  }
 }
 int Hash (int v) const
 {
  return Hash((unsigned int)v);
 }
 int Hash (unsigned int v) const
 {
  return v%(m_size-1);
 }
 int Hash (long int v) const
 {
   return Hash((unsigned long int)v);
 }
 int Hash (unsigned long int v) const
 {
  return v%(m_size-1);
 }
 int Hash (long long v) const
 {
   return Hash((unsigned long long)v);
 }
 int Hash (unsigned long long v) const
 {
  return v%(m_size-1);
 }
 int Hash (const void* v) const
 {
  union {
   const void* v;
   unsigned int i;
  } u;
  u.v = v;
  return u.i%(m_size-1);
 }
 int Hash (float v) const
 {
  union {
   float v;
   unsigned int i;
  } u;
  u.v = v;
  return u.i%(m_size-1);
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
  return h%(m_size-1);
 }
 int FindKey (int h, const KEY& key) const
 {
  if (m_table[h].field.empty)
   return m_size;
  while (h<m_size && !(m_table[h].key == key))
   h = m_table[h].field.next;
  return h;
 }
 void Rehash ()
 {
  int i;
  int n = CountKeys(); 
  int old_size = m_size;
  Entry* old_table = m_table;
  // choose the growing rate
  float ratio = (float)(n+1)/m_size;
  if (ratio < 0.4)
   m_size /= 2;
  else if (ratio > 0.9)
   m_size *= 2;

  CreateTable();
  for (i=0; i<old_size; ++i) {
   if (!old_table[i].field.empty && !old_table[i].field.reusable) {
    Set(old_table[i].key,old_table[i].value); 
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
  for (int i = m_freespot; i < m_size; ++i) {
   if (m_table[i].field.empty) {
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
   if (!m_table[i].field.empty && !m_table[i].field.reusable)
    n++;
  return n;
 }
};

// public methods
template <class KEY, class VALUE> inline DsHash<KEY,VALUE>::DsHash (int size)
: m_current(0), m_freespot(0), m_size(size), m_table(0)
{
 CreateTable();
}

template <class KEY, class VALUE> inline DsHash<KEY,VALUE>::~DsHash ()
{
 delete [] m_table;
}

template <class KEY, class VALUE> inline VALUE DsHash<KEY,VALUE>::Get (const KEY& key) const
{
 int h = Hash(key);
 int i = FindKey(h,key);
 return i<m_size && !m_table[i].field.reusable ? m_table[i].value : VALUE();
}

template <class KEY, class VALUE> inline bool DsHash<KEY,VALUE>::Find (const KEY& key) const
{
 int h = Hash(key);
 int i = FindKey(h,key);
 return (i < m_size && !m_table[i].field.reusable);
}

template <class KEY, class VALUE> inline void DsHash<KEY,VALUE>::Set (const KEY& key, const VALUE& value)
{
 int h2;
 int h = Hash(key);
 int i = FindKey(h,key);
 if (i < m_size) {
  m_table[i].value = value;
  m_table[i].field.reusable = 0;
 }
 else if (m_table[h].field.empty) {
  m_table[h].field.empty = 0;
  m_table[h].key = key;
  m_table[h].value = value;
 }
 else if (m_table[h].field.reusable) {
  m_table[h].field.reusable = 0;
  m_table[h].key = key;
  m_table[h].value = value;
 }
 else if ((h2 = Hash(m_table[h].key)) == h)
 {
  int f = FreeSpot();
  if (f < 0) {
   Set(key,value);
  }
  else {
   m_table[f].key = key;
   m_table[f].value = value;
   m_table[f].field.empty = 0;
   m_table[f].field.next = m_table[h].field.next;
   m_table[h].field.next = f;
  }
 }
 else { // h2 != h
  int f = FreeSpot();
  if (f < 0) {
   Set(key,value);
  }
  else {
   int prev = FindPrevious(h2,h); 
   m_table[prev].field.next = f;
   m_table[f] = m_table[h];
   m_table[h].key = key;
   m_table[h].value = value;
   m_table[h].field.next = m_size;
  }
 }
}

template <class KEY, class VALUE> inline bool DsHash<KEY,VALUE>::Remove (const KEY& key)
{
 int h = Hash(key);
 int i = FindKey(h,key);
 if (i < m_size && !m_table[i].field.reusable) {
  m_table[i].field.reusable = 1;
  return true;
 }
 return false;
}

template <class KEY, class VALUE> inline VALUE DsHash<KEY,VALUE>::GetAndRemove (const KEY& key)
{
 int h = Hash(key);
 int i = FindKey(h,key);
 if (i < m_size && !m_table[i].field.reusable) {
  m_table[i].field.reusable = 1;
  return m_table[i].value;
 }
 else
  return VALUE();
}

template <class KEY, class VALUE> inline bool DsHash<KEY,VALUE>::First (KEY* key)
{
 for (int i=0; i<m_size; ++i) {
  if (!m_table[i].field.empty && !m_table[i].field.reusable) {
   m_current = i;
   if (key) *key = m_table[i].key;
   return true;
  }
 }
 return false;
}

template <class KEY, class VALUE> inline bool DsHash<KEY,VALUE>::Next (KEY* key)
{
 int i;
 if (!m_table[m_current].field.empty && !m_table[m_current].field.reusable && m_table[m_current].key==*key)
  i = m_current;
 else
  i = FindKey(Hash(key),*key);
 
 for (++i; i<m_size; ++i) {
  if (!m_table[i].field.empty && !m_table[i].field.reusable) {
   m_current = i;
   *key = m_table[i].key;
   return true;
  }
 }
 return false;
}

template <class KEY, class VALUE> inline void DsHash<KEY,VALUE>::Clear ()
{
 for (int i=0; i<m_size; ++i) {
  m_table[i].field.empty = 1;
  m_table[i].field.reusable = 0;
  m_table[i].field.next = m_size;
 }
 m_current = m_freespot = 0;
}

#endif

