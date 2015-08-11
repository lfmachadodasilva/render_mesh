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
#ifndef _TOP_RAW_ARRAY_H
#define _TOP_RAW_ARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "defines.h"

/**
  @warning When array is reallocated, destructors are not called!!!
*/
template <class TYPE> 
class TOPSH_API TopRawArray
{
protected:
  int    d_nmax;
  int    d_n;
  float  d_incr;
  TYPE*  d_v;
  char*  d_name;
  bool   d_reset_nmax;
public:
  TopRawArray (float incr=TOP_ARRAY_RESIZE_FACTOR) 
    : d_nmax(0), d_n(0), d_incr(incr), d_v(0), d_reset_nmax(false)
  {
    d_name = 0;
  }
  virtual ~TopRawArray()
  {
    free(d_v);
    free(d_name);
  }
  void Reset() 
  { 
    d_n = 0; 
  }
  void Empty ()
  {
    d_n = d_nmax = 0;
    free(d_v);
    d_v = 0;
  }
  bool TrimToSize ()
  {
    if (d_nmax == d_n)
      return true;
    else if (d_n == 0) {
      Empty();
      d_reset_nmax = true;
      return true;
    }
    else {
      d_v = (TYPE*) realloc(d_v,d_n*sizeof(TYPE));
      d_nmax = 0; // to force recomputation of d_nmax proportionally to d_incr
      d_reset_nmax = true;
      return (d_v != NULL);
    }
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
  const char* GetName () const
  {
    return d_name;
  }
/*
  TYPE& operator[] (int i)
  {
    Reserve(i+1);
    return d_v[i];
  }
*/
  const TYPE& operator[] (int i) const
  {
    assert(i >= 0 && i < d_n);
    return d_v[i];
  }
  TYPE Get (int i) const
  {
    assert(i >= 0 && i < d_n);
    return d_v[i];
  }
  //DEPRECATED
  TYPE* GetPtr (int i) const
  {
    return GetAddress(i);
  }
  TYPE* GetAddress (int i) const
  {
    assert(i >= 0 && i < d_n);
    return &d_v[i];
  }
  void Set (int i, TYPE t)
  {
    assert(i >= 0 && i < d_n);
    d_v[i] = t;
  }
  bool Append (const TYPE& t)
  {
    if (!Resize(d_n+1)) 
      return false;
    d_v[d_n-1] = t;
    return true;
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
  int GetMaxSize (void) const
  {
    return d_nmax;
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
      //if (d_name)
      //  printf("DS: realloc(%s,%d->",d_name,d_nmax);
      if (d_reset_nmax) {
        d_nmax = 0;
        d_reset_nmax = false;
      }
      do
      {
        d_nmax = d_nmax ? (int)(d_incr*d_nmax) : TOP_ARRAY_INIT_SIZE;
      } while (n>d_nmax);
      //if (d_name)
      //  printf("%d)\n",d_nmax);
      d_v = (TYPE*) realloc(d_v,d_nmax*sizeof(TYPE));
      if (!d_v)
        return false;
    }
    if (n>d_n) d_n = n;
    return true;
  } 
};


#endif
