//* manip.h
// celes@tecgraf.puc-rio.br
// fabraham@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Jan 2003

#ifndef VGL_MANIP_H
#define VGL_MANIP_H

#include <vgl/handler.h>
#include <vgl/utils/modelrotation.h>
#include <vgl/utils/repeat.h>
#include <alg/vector.h>
#include "transformcenter.h"

class VglViewSurface;

/**
 * VGL Manipulation Handler
 *
 * This handler provides facilities for manipulating the model using the mouse.
 *
 * Mechanisms are provided for allowing the user to:
 * - rotate the model along any axis, given a rotation center (left mouse button)
 * - rotate the model along the viewing direction, given a rotation center (right mouse button)
 * - translate the model along the viewing direction (middle mouse button)
 * - scale the model along a given scale center (middle mouse button + CTRL key)
 *
 * The ammount to rotate, translate and scale is determined by the displacement
 * of the mouse cursor.
 *
 * The rotation center and scale center are actually the same and are called the
 * 'transform center'.
 *
 * Methods are available to specify the rotation center externally, or use an
 * external computation to calculate it.
 *
 * Other methods are available to constrain the rotation along the view Y axis
 * (up axis), allowing the application always to keep the up vector of their
 * models aligned with the view Y axis.
 */
class VGL_API VglManipHandler : public VglHandler, public VglTransformCenterUser
{
  VglModelRotation m_rotation;
  VglRepeatTransform m_repeat;
  char m_constraint;
  int m_feedback;
  const AlgVector* m_box;
  VglViewSurface* m_surface;
  bool m_moving;
  bool m_animated;
public:
  static const char* CLASSNAME () { return "ManipHandler"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
  /**
   * Constructor. Receives a visualization surface (mandatory).
   */
  VglManipHandler (VglViewSurface* surface);
  virtual ~VglManipHandler ();
  // public methods
  void SetViewSurface (VglViewSurface *surface)
  {
    m_surface = surface;
    m_repeat.SetViewSurface(surface);
  }
  VglViewSurface *GetSurface () const
  {
    return m_surface;
  }
  void SetFeedback (int mode);
  int GetFeedbackMode ()
  {
    return m_feedback;
  }
  void SetViewBox (const AlgVector* box);
  void SetAnimated (bool animated)
  {
    m_animated = animated;
  }
  /**
   * Specifies that the model must be rotated around its box center.
   * This invalidates previously set transform center functions.
   */
  void SetRotateAroundBoxCenter (bool f);
  void SetYRotationAxis (const AlgVector& axis)
  {
    m_rotation.SetYRotationAxis(axis);
  }
  void SetYRotationAxis (float vx, float vy, float vz)
  {
    m_rotation.SetYRotationAxis(vx,vy,vz);
  }
  void UnsetYRotationAxis ()
  {
    m_rotation.UnsetYRotationAxis();
  }
  AlgVector GetYRotationAxis () const
  {
    return m_rotation.GetYRotationAxis();
  }
  AlgVector ObtainTransformCenter() const;
  AlgVector ObtainTransformCenterEye() const;
  /**
   * Returns true in case the model/scene is moving because of this manipulator, false otherwise.
   */
  bool IsMoving ()
  {
    return m_moving;
  }
  virtual void End ();
  virtual int Keyboard (int k, int st, float x, float y);
  virtual int MouseButton (int bt, int st, float x, float y);
  virtual int MouseMotion (int bt, float x, float y);
  virtual int MouseWheel (float delta, float x, float y);
protected:
  void ApplyScale (VglCamera *camera, float dx, float dy);
};

#endif
