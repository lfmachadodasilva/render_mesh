/**
* Modulo de definicao da classe TpvArray, 
  para ser usado como geometria extraida para a TopsView
*/

#ifndef TPV_ARRAY_H
#define TPV_ARRAY_H

#include <ds/array.h>
#include <tops/tops.h>
#include <topsview/defines.h>

#include <stdio.h>
#include <math.h>

/**
  Defines a reference counted array.
*/
template <class TYPE> 
class TPV_API TpvArray : public DsArray<TYPE>
{
protected:
  int m_refcount;

public:
  TpvArray(int size, const TYPE* v) 
    : m_refcount(0)
  {
    Append(size, v);
  }
  TpvArray() : m_refcount(0) 
  {
  }  
  virtual ~TpvArray() 
  {
  }
  void Release() 
  { 
    if (--m_refcount <= 0) delete this; 
  }
  void AddRef() 
  { 
    m_refcount++; 
  }
};

typedef TpvArray<TopElement> TpvElementArray;
typedef TpvArray<TopFacetUse> TpvFacetUseArray;
typedef TpvArray<TopEdgeUse> TpvEdgeUseArray;
typedef TpvArray<TopVertexUse> TpvVertexUseArray;
typedef TpvArray<TopNode> TpvNodeArray;
typedef TpvArray<int> TpvIntArray; 
typedef TpvArray<float> TpvFloatArray; 

#endif
