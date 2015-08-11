// normalcone.h
// 3D normal cone
// fabraham@tecgraf.puc-rio.br
// Aug 2009

#ifndef ALG_NORMAL_CONE_H
#define ALG_NORMAL_CONE_H

#include "defines.h"
#include "vector.h"
#ifdef WIN32
# include <windows.h>
#endif
#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/glut.h>

class ALGH_API AlgNormalCone
{
public:
  /**
   * Constructor
   */
  AlgNormalCone ()
  {
  }
  /**
   * Builds a normal cone given 'numvertices' with positions 'positions' and
   * normals 'normals'.
   * positions[3*i], positions[3*i+1] and positions[3*i+2] are x, y, z of the
   * vertex of index 'i'. The same applies for 'normals'.
   *
   * If 'scale' is different than 1,1,1, then positions and normals are transformed
   * by a scale of sizes scale.x, scale.y and scale.z around the point
   * 'scale_center'. In this case, the transformed cone will be stored in the
   * scaled coordinate system.
   */
  void Build (int numvertices,
              const float* positions,
              const float* normals,
              const AlgVector& scale,
              const AlgVector& scale_center);
  /**
   * Decides if observer is in the backfacing region of the normal cone,
   * thus enabling the culling of all primitives associated with this
   * cone.
   * 'obspos' must be in the same coordinate system as the cone vertices
   * and normals.
   */
  bool IsInBackFacingRegion (const AlgVector& obspos) const;
  /**
   * Draws the normal cone.
   */
  void Draw () const;
  /**
   * Obtains all data associated to cone.
   * Can be used to restore a cone using SetData.
   */
  void GetData (AlgVector* n,
                AlgVector* a,
                AlgVector* b,
                AlgVector* truncbase,
                float* alpha,
                float* h,
                float* cylinder_h,
                float* cylinder_r) const;
  /**
   * Specifies all cone associated data.
   */
  void SetData (AlgVector n,
                AlgVector a,
                AlgVector b,
                AlgVector truncbase,
                float alpha,
                float h,
                float cylinder_h,
                float cylinder_r);
private:
  void FindNormalAndHalfAngle (int numvertices,
                               const float* normals);
  void TruncateConeAndFindB (int numvertices,
                             const float* positions);
  void ComputeBoundingSphere (int numvertices,
                              const float* positions,
                              AlgVector* bscenter,
                              float* bsradius);
  void ComputeDistances (int numvertices,
                         const float* positions,
                         const AlgVector& bscenter,
                         float* dmin,
                         float* dmax);
  static void DrawCone (const AlgVector& anchor,
                        const AlgVector& n,
                        float alpha,
                        float h,
                        float r,
                        float g,
                        float b,
                        float a);
  static void DrawCylinder (const AlgVector& anchor,
                            const AlgVector& n,
                            float radius,
                            float h);
private:
  AlgVector m_n;
  AlgVector m_a;
  AlgVector m_b;
  float m_alpha;
  float m_h;
  float m_90_minus_alpha;
  float m_90_minus_alpha_dot;
  AlgVector m_truncbase;
  float m_cylinder_h;
  float m_cylinder_r;
};

#endif

