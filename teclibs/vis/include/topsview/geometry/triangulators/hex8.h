// Interface for geometry triangulators
// rodesp@tecgraf.puc-rio.br
// May 2008
#ifndef TPV_ELEM_HEX8_TRIANGULATOR_H
#define TPV_ELEM_HEX8_TRIANGULATOR_H

#include "../triangulator.h"
#include "q4.h"

class TPV_API TpvElemHex8Triangulator : public TpvTriangulator
{
public:
  /**
   * Constructor
   */   
  TpvElemHex8Triangulator ();
  
  /**
   * Destructor
   */
  virtual ~TpvElemHex8Triangulator ();
  
  virtual void SetDisplacement (float factor, TpvProperty* disp);  

  virtual void TriangulatePositions (const TopFaceUse& fu, TopModel* model, UGLArray* positions);
  
  virtual void TriangulateField (const TopFaceUse& fu, TopModel* model, TpvProperty* property, UGLArray* texcoords);

  virtual void TriangulateColors (const TopFaceUse& fu, 
                                  TopModel* model, 
                                  TpvProperty* property, UGLArray* colors);

  virtual void TriangulateGridTexCoords (const TopFaceUse& fu, 
    TopModel* model, UGLArray* texcoords1, UGLArray* texcoords2, UGLArray* texcoords3);

protected:
  
private:
  TpvElemQ4Triangulator m_face_triang;
};

#endif

