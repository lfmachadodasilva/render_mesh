/**
* Modulo de definicao da classe TpvGeometry, para ser usado como geometria extraida para a TopsView
*/

#ifndef TPV_SUPPORT_H
#define TPV_SUPPORT_H

#include "array.h"
#include <tops/tops.h>
#include <topsview/defines.h>

#include <stdio.h>
#include <math.h>

/**  
*/
struct TPV_API TpvSupport
{
  enum Type {
    ELEMENT = 0,
    ELEMENT_2D,
    FACET_USE,
    EDGE_USE,
    VERTEX_USE,
    NODE,
    NODE_LOCAL_ID
  };
  int type;
  unsigned handle;
  TpvSupport() {}
  TpvSupport(int t, unsigned h) : type(t), handle(h) {}
  TopVertexUse GetVertexUse() { return TopVertexUse(handle); }
};

typedef TpvArray<TpvSupport> TpvSupportArray;

#endif
