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
// Extracted from "ds/array.h"

#ifndef _TOP_ARRAY_H
#define _TOP_ARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defines.h"

template <class TYPE> 
class TOPSH_API TopArray
{
protected:
  int    d_nmax;
  int    d_n;
  float  d_incr;
  TYPE*  d_v;
  char*  d_name;

public:
  TopArray (float incr=2.0F) 
    : d_nmax(0), d_n(0), d_incr(incr), d_v(0)
  {
    d_name = 0;
  }
  virtual ~TopArray()
  {
    if (d_v)
      delete [] d_v;
    free(d_name);
  }
  void Reset() 
  { 
    d_n = 0; 
  }
  void Empty ()
  {
    d_n = d_nmax = 0;
    if (d_v)
      delete [] d_v;
    d_v = 0;
  }
  bool SetName (const char* name)
  {
    if (d_name) {
      free(d_name);
      d_name = NULL;
    }
    if (name) {
      d_name = (char*)malloc(strlen(name)+1);
      if (!d_name)
        return false;
      strcpy(d_name,name);
    }
    return true;
  }
  /*
  TYPE& operator[] (int i)
  {
    Reserve(i+1);
    return d_v[i];
  }
  */
  /*
  const TYPE& operator[] (int i) const
  {
    return d_v[i];
  }
  */
  TYPE Get (int i) const
  {
    return d_v[i];
  }
  TYPE* GetAddress (int i) const
  {
    return d_v+i;
  }
  void Set (int i,TYPE& t)
  {
    d_v[i] = t;
  }
  void SetConst (int i,TYPE t)
  {
    d_v[i] = t;
  }
  bool Append (const TYPE& t)
  {
    if (!Resize(d_n+1))
      return false;
    d_v[d_n-1] = t;
    return true;
  }
  // Appends n elements of TYPE.
  bool Append (int n, const TYPE* tv)
  {
    if (!Resize(d_n+n))
      return false;
    TYPE* v = d_v+d_n-n;
    for (int i=0; i<n; i++)
      *v++ = tv[i];
    return true;
  }
  /**
   * Inserts element 't' at position 'pos'.
   * If 'pos' is negative, inserts at the end of the list.
   */
  bool Insert (const TYPE& t, int pos=-1)
  {
    if (!Resize(d_n+1))
      return false;
    if (pos < 0 || pos >= d_n-1)
      d_v[d_n-1] = t;
    else
    {
      for (int i=d_n-2; i>=pos; i--)
        d_v[i+1] = d_v[i];
      d_v[pos] = t;
    }
    return true;
  }
  // Removes entry at the given index. 
  void Remove (int i)
  {
    d_n--;
    if (i < d_n)
      memmove(d_v+i, d_v+i+1, (d_n-i)*sizeof(TYPE));
  }
  void Invert ()
  {
    for (int i=0, j=d_n-1; i<j; i++, j--)
    {
      TYPE t = d_v[i];
      d_v[i] = d_v[j];
      d_v[j] = t;
    }
  }
  TYPE* GetArray ()
  {
    return d_v;
  }
  const TYPE* GetArrayConst () const
  {
    return d_v;
  }
  int Size (void) const
  { 
    return d_n; 
  }
  /**
   * Returns 'true' if 'i' is a valid index
   * for 'Get'. (i between 0 and size-1).
   */
  bool ValidIndex (int i) const
  {
    return 0 <= i && i < Size();
  }
  bool Resize (int n)
  {
    if (!Reserve(n))
      return false;
    d_n = n;
    return true;
  }
  bool Reserve (int n)
  {
    if (n>d_nmax)
    {
      do
      {
        d_nmax = d_nmax ? (int)(d_incr*d_nmax) : 2;
      } while (n>d_nmax);
      TYPE* v = new TYPE[d_nmax];
      if (!v)
        return false;
      for (int i=0; i<d_n; ++i)
        v[i] = d_v[i];
      delete [] d_v;
			d_v = v;
    }
    if (n>d_n) d_n = n;
    return true;
  } 
};


#endif
