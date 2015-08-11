// Q8 element triangulator for bilinear interpolation
// rodesp@tecgraf.puc-rio.br
// Apr 2010

#ifndef TPV_ELEM_Q8_BILINEAR_TRIANGULATOR_H
#define TPV_ELEM_Q8_BILINEAR_TRIANGULATOR_H

#include "../triangulator.h"

class TpvElemQ8BilinearTriangulator : public TpvTriangulator
{
public:
  TpvElemQ8BilinearTriangulator ();
 
  virtual ~TpvElemQ8BilinearTriangulator ();

  virtual void TriangulateAttrib (const TopFaceUse& fu, TopModel* model, 
      TpvProperty* property, UGLArray** outputs);
};

#endif