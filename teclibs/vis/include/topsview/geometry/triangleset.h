// Triangle sets
// fabraham@tecgraf.puc-rio.br
// Apr 2008
#ifndef TPV_TRI_SET_H
#define TPV_TRI_SET_H

#include <ds/array.h>
#include <alg/vector.h>
#include "geomsetbase.h"

class UGLTriangleSet;
class UGLArray;

class TPV_API TpvTriangleSet : public TpvGeometrySetBase
{
public:
  TpvTriangleSet ();
  ~TpvTriangleSet ();
  /**
   * Specifies an optional set of quad indices to be used when drawing.
   */
  void SetIndices (UGLTriangleSet *indices)
  {
    m_indices = indices;
  }
  bool HasIndices () const
  {
    return m_indices != NULL;
  }
  void LoadIndices ();
protected:
  void UpdateIndicesFromSortData (DsArray<SortData>* sortdata,
                                  unsigned int* ind);
  void UpdatePerFaceNormals (UGLArray* positions, UGLArray* normals);
  void TriangulateGridTexCoords (UGLArray* texcoords1, UGLArray* texcoords2, UGLArray* texcoords3);
private:
  void ComputeNormal(
    const AlgVector &v0,
    const AlgVector &v1,
    const AlgVector &v2,
    float *x,
    float *y,
    float *z);
private:
  UGLTriangleSet* m_indices;
};

#endif

