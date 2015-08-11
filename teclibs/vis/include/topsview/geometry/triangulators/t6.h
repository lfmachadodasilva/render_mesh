// Interface for geometry triangulators
// rodesp@tecgraf.puc-rio.br
// May 2008
#ifndef TPV_ELEM_T6_TRIANGULATOR_H
#define TPV_ELEM_T6_TRIANGULATOR_H

#include "../triangulator.h"

class TPV_API TpvElemT6Triangulator : public TpvTriangulator
{
public:
  /**
   * Constructor
   */
  TpvElemT6Triangulator ();
  
  /**
   * Destructor
   */
  virtual ~TpvElemT6Triangulator ();
  
  virtual void TriangulatePositions (const TopFaceUse& fu, TopModel* model, UGLArray* positions);
  
  virtual void TriangulateField (const TopFaceUse& fu, TopModel* model, TpvProperty* property, UGLArray* texcoords);

  virtual void TriangulateColors (const TopFaceUse& fu, 
                                  TopModel* model, 
                                  TpvProperty* property, 
                                  UGLArray* colors);

  virtual void TriangulateGridTexCoords (const TopFaceUse& fu, 
    TopModel* model, UGLArray* texcoords1, UGLArray* texcoords2, UGLArray* texcoords3);
 
protected:
  
private:
  void TriangulateProperty (const TopFaceUse& fu, 
                            TopModel* m, 
                            TpvProperty* property, 
                            float* o_values);
};

#endif

