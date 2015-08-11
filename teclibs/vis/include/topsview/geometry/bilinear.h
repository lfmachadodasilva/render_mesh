// Bilinear shader geometry
// rodesp@tecgraf.puc-rio.br
// Apr 2010

#ifndef TPV_BILINEAR_H
#define TPV_BILINEAR_H

#include <tops/tops.h>
#include <topsview/defines.h>

#include "geometry.h"

#include <stdio.h>
#include <math.h>

class TpvTriangleSet;

/**  
*/
class TPV_API TpvBilinearGeometry : public TpvGeometry
{
public:
  TpvBilinearGeometry () {}
  
  virtual ~TpvBilinearGeometry () {}

  virtual TpvTriangleSet* GetTriangleSetQ4 ()
  {
    return NULL;
  }

  virtual TpvTriangleSet* GetTriangleSetQ8 ()
  {
    return NULL;
  }
};

#endif