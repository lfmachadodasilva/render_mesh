// Interface for geometry triangulators
// rodesp@tecgraf.puc-rio.br
// May 2008
#ifndef TPV_FEM_TRIANGULATOR_H
#define TPV_FEM_TRIANGULATOR_H

#include "../triangulator.h"
#include "t3.h"
#include "t6.h"
#include "q4.h"
#include "q8.h"
#include "inf2e2.h"
#include "inf2e3.h"
#include "inf2v2.h"
#include "inf3q4.h"
#include "inf3q8.h"

class TPV_API TpvFemTriangulator : public TpvTriangulator
{
public:
  /**
   * Constructor
   */   
  TpvFemTriangulator ();
  
  /**
   * Destructor
   */
  virtual ~TpvFemTriangulator ();
  
  virtual void SetDisplacement (float factor, TpvProperty* disp);  

  virtual void TriangulatePositions (const TopFaceUse& fu, TopModel* model, UGLArray* positions);
 
  virtual void TriangulateField (const TopFaceUse& fu, TopModel* model, TpvProperty* property, UGLArray* texcoords);

  virtual void TriangulateColors (const TopFaceUse& fu, 
                                  TopModel* model, 
                                  TpvProperty* property, 
                                  UGLArray* colors);

  virtual void TriangulateGridTexCoords (const TopFaceUse& fu, 
    TopModel* model, UGLArray* texcoords1, UGLArray* texcoords2, UGLArray* texcoords3);
 
  virtual void TriangulatePositions(
    const AlgVector* vertices, int numvertices, UGLArray* positions);

  virtual void TriangulateField (
    int numvertices, float* pervertexfield, UGLArray* texcoords);

  virtual void TriangulateColors (int numvertices, 
                                  float* pervertexcolors, 
                                  UGLArray* colors);

  virtual void TriangulateGridTexCoords (
    int numvertices, UGLArray* texcoords1, UGLArray* texcoords2, UGLArray* texcoords3);

private:
  TpvElemT3Triangulator m_t3_triang;
  TpvElemT6Triangulator m_t6_triang;
  TpvElemQ4Triangulator m_q4_triang;
  TpvElemQ8Triangulator m_q8_triang;
  TpvElemInf2E2Triangulator m_inf2e2_triang;
  TpvElemInf2E3Triangulator m_inf2e3_triang;
  TpvElemInf2V2Triangulator m_inf2v2_triang;
  TpvElemInf3Q4Triangulator m_inf3q4_triang;
  TpvElemInf3Q8Triangulator m_inf3q8_triang;
};

#endif

