// frustum.h
// Tecgraf/PUC-Rio
// celes@tecgraf.puc-rio.br
// Feb 2003

#ifndef VGL_FRUSTUM_H
#define VGL_FRUSTUM_H

#include <alg/plane.h>
#include <alg/frustum.h>
#include <alg/matrix.h>
#include "defines.h"

class VGL_API VglFrustum : public AlgFrustum
{
public:
  /**
   * Constructs a new VglFrustum object.
   * Mmv = Modelview matrix, Mp = projection matrix.
   */
  VglFrustum (const float* Mmv, const float* Mp);
  /**
   * Constructs a new VglFrustum object.
   * Mmv = Modelview matrix, Mp = projection matrix.
   */
  VglFrustum (const AlgMatrix &Mmv, const AlgMatrix &Mp);
  /**
   * Constructs a new VglFrustum object.
   * Mmvp is the Modelview-projection matrix.
   */
  VglFrustum (const float* Mmvp);
  /**
   * Constructs a new VglFrustum object.
   * Mmvp is the Modelview-projection matrix.
   */
  VglFrustum (const AlgMatrix &Mmvp);
  /**
   * Constructs a new VglFrustum object.
   * Both modelview and projection matrices are obtained by glGet.
   */
  VglFrustum ();
  /**
   * Virtual destructor
   */
  virtual ~VglFrustum () {}
  /**
   * Updates matrices. Mmv = Modelview matrix, Mp = projection matrix
   */
  void Update (const float* Mmv, const float* Mp);
  /**
   * Updates matrices. Mmvp = Modelview-projection matrix
   */
  void Update (const float* Mmvp);
  /**
   * Updates matrices
   * Both modelview and projection matrices are obtained by glGet.
   */
  void Update ();
  /**
   * Draws the frustum.
   * lr, lg, lb     = line color
   * qr, qg, qb, qa = transparent quad color
   */
  void Draw (float lr=1.0f, float lg=1.0f, float lb=1.0f, float qr=1.0f, float qg=1.0f, float qb=0.0f, float qa=0.3f);
  /**
   * Draws the frustum.
   * lr, lg, lb     = line color
   * leftr, leftg, leftb, lefta = transparent left quad color
   * rightr, rightg, rightb, righta = transparent right quad color
   * bottomr, bottomg, bottomb, bottoma = transparent bottom quad color
   * topr, topg, topb, topa = transparent top quad color
   * nearr, nearg, nearb, neara = transparent near quad color
   * farr, farg, farb, fara = transparent far quad color
   */
  void CustomDraw (float lr=1.0f, float lg=1.0f, float lb=1.0f,
                   float leftr=1.0f, float leftg=1.0f, float leftb=0.0f, float lefta=0.8f,
                   float rightr=1.0f, float rightg=1.0f, float rightb=0.0f, float righta=0.8f,
                   float bottomr=1.0f, float bottomg=1.0f, float bottomb=0.0f, float bottoma=0.8f,
                   float topr=1.0f, float topg=1.0f, float topb=0.0f, float topa=0.8f,
                   float nearr=1.0f, float nearg=1.0f, float nearb=0.0f, float neara=0.8f,
                   float farr=1.0f, float farg=1.0f, float farb=0.0f, float fara=0.8f);
  /**
   * Gets frustum plane in object space, one of the following values:
   *           VGL_PLANE_LEFT
   *           VGL_PLANE_RIGHT
   *           VGL_PLANE_BOTTOM
   *           VGL_PLANE_TOP
   *           VGL_PLANE_NEAR
   *           VGL_PLANE_FAR
   */
  AlgPlane GetPlane (int id);
  /**
   * Gets the current eye position in object coordinates. (current modelview&projection)
   */
  AlgVector GetEyePos ();
  /**
   * Gets the current view direction. (current modelview&projection)
   */
  AlgVector GetViewDir ();
  /**
   * Gets the current view up direction. (current modelview&projection)
   */
  AlgVector GetViewUp ();
  /**
   * Gets the current near plane distance. (current modelview&projection)
   */
  float GetNearDist ();
  /**
   * Gets the current far plane distance. (current modelview&projection)
   */
  float GetFarDist ();
  /**
   * Gets the current angle of the field of view in the x-z plane. (current modelview&projection)
   */
  float GetFovy ();
  /**
   * Gets the current angle of the field of view in the y-z plane. (current modelview&projection)
   */
  float GetFovx ();
  /**
   * Obtains the 8 frustum vertices.
   */
  void GetVertices (AlgVector* v);
private:
  void InitCanonicalPlanes ();
};

#endif
