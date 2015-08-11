// Radial grid triangulator
// fabraham@tecgraf.puc-rio.br
// Apr 2008
#ifndef TPVRES_RADIAL_TRIANGULATOR_H
#define TPVRES_RADIAL_TRIANGULATOR_H

#include "separation.h"
#include <topsviewres/defines.h>

/**
 * Radial grid triangulator class.
 * 
 * Triangulates faces converting from cylindrical coordinates to cartesian coordinates.
 * 
 * Also considers if a face is too big in the 'theta' direction, splitting it into smaller
 * faces so that curvature is visible.
 */
class TPVRES_API TpvResRadialTriangulator : public TpvResSeparationTriangulator
{
public:
  TpvResRadialTriangulator ();
  ~TpvResRadialTriangulator ();
  void SetRW (float rw)
  {
    m_rw = rw;
  }
  // virtual methods
  void TriangulatePositions (const TopFaceUse& fu, TopModel* model, UGLArray *positions);
  void TriangulateGridTexCoords (const TopFaceUse& fu, TopModel* model, UGLArray *texcoords1, UGLArray *texcoords2, UGLArray *texcoords3);
  void TriangulateField (const TopFaceUse& fu, TopModel* model, TpvProperty* property, UGLArray *texcoords);
private:
  int GetNumPartsRadial (const TopFaceUse &fu, TopModel* model);
private:
  float m_rw;
};

#endif

