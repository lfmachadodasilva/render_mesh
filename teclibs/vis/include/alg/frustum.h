// frustum.h
// Tecgraf/PUC-Rio
// celes@tecgraf.puc-rio.br
// Feb 2003

#ifndef ALG_FRUSTUM_H
#define ALG_FRUSTUM_H

#include "defines.h"
#include "plane.h"

class ALGH_API AlgFrustum
{
public:
  /* Creates a new AlgFrustum object
   * \param Number of canonical planes
   */
  AlgFrustum (int n)
  {
    m_pl = new AlgPlane[n];
    m_npl = n;
  }
  /* Deletes object
   */
  virtual ~AlgFrustum ()
  {
    delete [] m_pl;
  }
  /* Sets canonical plane equations
   * \param Plane ID
   * \param Plane equation coeficients
   */
  void SetCanonicalPlane (int id, float a, float b, float c, float d)
  {
    if (id>=0 && id<m_npl)
      m_pl[id].Set(a,b,c,d);
  }
  /* Sets vertex transformation matrix
   * \param The matrix represented in vector, column by column
   */
  void SetVertexMatrix (const float* m)
  {
    for (int i=0; i<16; i++)
      m_mat[i] = m[i];
  }
  /* Gets plane equation in original space
   * \param Plane ID
   */
  AlgPlane GetPlane (int id)
  {
    AlgPlane p(0.0f,0.0f,0.0f,0.0f);
    if (id>=0 && id<m_npl)
    {
      // Multiply by the transpose matrix
      p.Set (m_pl[id].a*m_mat[0]+m_pl[id].b*m_mat[1]+
          m_pl[id].c*m_mat[2]+m_pl[id].d*m_mat[3],
          m_pl[id].a*m_mat[4]+m_pl[id].b*m_mat[5]+
          m_pl[id].c*m_mat[6]+m_pl[id].d*m_mat[7],
          m_pl[id].a*m_mat[8]+m_pl[id].b*m_mat[9]+
          m_pl[id].c*m_mat[10]+m_pl[id].d*m_mat[11],
          m_pl[id].a*m_mat[12]+m_pl[id].b*m_mat[13]+
          m_pl[id].c*m_mat[14]+m_pl[id].d*m_mat[15]
          );
    }
    return p;
  }
private:
  int m_npl;
  AlgPlane* m_pl;
  float m_mat[16];
};

#endif
