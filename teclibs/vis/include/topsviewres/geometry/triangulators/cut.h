// Cutting plane triangulator
// fabraham@tecgraf.puc-rio.br
// Apr 2008
#ifndef TPVRES_CUT_TRIANGULATOR_H
#define TPVRES_CUT_TRIANGULATOR_H

#include <topsview/geometry/triangulator.h>
#include <topsviewres/defines.h>

/**
 * Cutting plane triangulator.
 *
 * Divides the cutting plane polygons into triangles.
 *
 * To be used with a TpvTriangleSet geometry set.
 */
class TPVRES_API TpvResCutTriangulator : public TpvTriangulator
{
public:
  /**
   * Constructor.
   */
  TpvResCutTriangulator ();
  /**
   * Destructor.
   */
  virtual ~TpvResCutTriangulator ();
  // virtual methods
  void TriangulatePositions(const AlgVector* vertices, int numvertices, UGLArray* positions);
  void TriangulateField (int numvertices, float* pervertexfield, UGLArray* texcoords);
  void TriangulateGridTexCoords (int numvertices, UGLArray* texcoords1, UGLArray* texcoords2, UGLArray *texcoords3);
  void TriangulateColors (int numvertices, float* pervertexcolors, UGLArray* colors);
private:
};

#endif

