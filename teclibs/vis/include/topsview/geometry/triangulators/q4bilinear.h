// Q4 element triangulator for bilinear interpolation
// rodesp@tecgraf.puc-rio.br
// Apr 2010

#ifndef TPV_ELEM_Q4_BILINEAR_TRIANGULATOR_H
#define TPV_ELEM_Q4_BILINEAR_TRIANGULATOR_H

#include "../triangulator.h"

class TpvElemQ4BilinearTriangulator : public TpvTriangulator
{
public:
  TpvElemQ4BilinearTriangulator ();
 
  virtual ~TpvElemQ4BilinearTriangulator ();

  virtual void TriangulateAttrib (const TopFaceUse& fu, TopModel* model, 
      TpvProperty* property, UGLArray** outputs);
};

#endif