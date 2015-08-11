#ifndef VGL_ROTATION_H
#define VGL_ROTATION_H

#include <alg/vector.h>
#include <alg/matrix.h>
#include <vgl/defines.h>

class VglCamera;

class VGL_API VglRotation
{
  AlgVector* m_rot_yaxis;
  float m_anglex;
  float m_angley;
  bool m_hasanglex;
  bool m_hasangley;
protected:
  AlgMatrix m_current;
  VglRotation ();
  virtual void RotateX (float angle)
  {
    m_current.Rotate(angle,1.0f,0.0f,0.0f);
  }
  virtual void RotateY (float angle, const AlgVector &axis) = 0;
public:
  virtual ~VglRotation ();
  void ApplyRotationX (float angle)
  {
    m_anglex += angle;
    m_hasanglex = true;
  }
  void ApplyRotationY (float angle)
  {
    m_angley += angle;
    m_hasangley = true;
  }
  /**
   * Stores the necessary information to begin a camera rotation.
   */
  virtual void BeginRotation (VglCamera *camera)
  {
    m_current.Identity();
    m_anglex = 0.0f;
    m_angley = 0.0f;
    m_hasanglex = false;
    m_hasangley = false;
    StoreYAxisEye(camera);
  }
  /**
   * Finalizes the camera rotation.
   */
  void EndRotation (VglCamera *camera);
  /**
   * Specifies an axis for longitudinal rotation (theta in spherical
   * coordinates).
   *
   * The axis must be specified in model coordinates.
   * The axis is stored normalized.
   */
  void SetYRotationAxis (float vx, float vy, float vz);
  /**
   * Specifies an axis for longitudinal rotation (theta in spherical
   * coordinates) (vector form).
   *
   * The axis must be specified in model coordinates.
   * The axis is stored normalized.
   */
  void SetYRotationAxis (const AlgVector& axis);
  void UnsetYRotationAxis ();
  bool HasYRotationAxis () const
  {
    return m_rot_yaxis != NULL;
  }
  /**
   * Specifies the axis for longitudinal rotation (theta in spherical
   * coordinates).
   * Its is returned normalized.
   */
  AlgVector GetYRotationAxis () const
  {
    return HasYRotationAxis() ? *m_rot_yaxis : AlgVector(0.0f,1.0f,0.0f);
  }
protected:
  const AlgVector& GetYAxisEye () const
  {
    return m_y_axis_eye;
  }
private:
  void StoreYAxisEye (VglCamera* camera);
private:
  AlgVector m_y_axis_eye;};

#endif

