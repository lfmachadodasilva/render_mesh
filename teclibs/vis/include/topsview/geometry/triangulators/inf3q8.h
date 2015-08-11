// Interface for geometry triangulators
// rodesp@tecgraf.puc-rio.br
// May 2008
#ifndef TPV_ELEM_INF3Q8_TRIANGULATOR_H
#define TPV_ELEM_INF3Q8_TRIANGULATOR_H

#include "../triangulator.h"
#include "q4.h"
#include "q8.h"

class TPV_API TpvElemInf3Q8Triangulator : public TpvTriangulator
{
public:
  /**
   * Constructor
   */
  TpvElemInf3Q8Triangulator ();
  
  /**
   * Destructor
   */
  virtual ~TpvElemInf3Q8Triangulator ();

  virtual void SetDisplacement (float factor, TpvProperty* disp);
  
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
  void TriangulateFace4Property (const TopFaceUse& fu, 
                                 TopModel* m, 
                                 TpvProperty* property, 
                                 float* o_values);

private:
  TpvElemQ4Triangulator m_q4_triang;
  TpvElemQ8Triangulator m_q8_triang;
};

#endif

