// Quad sets
// fabraham@tecgraf.puc-rio.br
// Apr 2008
#ifndef TPV_QUAD_SET_H
#define TPV_QUAD_SET_H

#include "geomsetbase.h"

class UGLQuadSet;
class UGLArray;

class TPV_API TpvQuadSet : public TpvGeometrySetBase
{
public:
  TpvQuadSet ();
  ~TpvQuadSet ();
  /**
   * Specifies an optional set of quad indices to be used when drawing.
   */
  void SetIndices (UGLQuadSet *indices)
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
    const AlgVector &v3,
    float *x,
    float *y,
    float *z);
private:
  UGLQuadSet* m_indices;
};

#endif

