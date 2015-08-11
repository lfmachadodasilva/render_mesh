// Interface for geometry triangulators
// rodesp@tecgraf.puc-rio.br
// May 2008
#ifndef TPV_ELEM_T3_TRIANGULATOR_H
#define TPV_ELEM_T3_TRIANGULATOR_H

#include "../triangulator.h"

class TPV_API TpvElemT3Triangulator : public TpvTriangulator
{
public:
  /**
   * Constructor
   */
  TpvElemT3Triangulator ();
  
  /**
   * Destructor
   */
  virtual ~TpvElemT3Triangulator ();
  
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
};

#endif

