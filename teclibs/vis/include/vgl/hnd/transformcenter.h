#ifndef VGL_TRANSFORM_CENTER_H
#define VGL_TRANSFORM_CENTER_H

#include <vgl/defines.h>
#include <ds/list.h>
#include <stdio.h>

class VglTransformCenterUser;

/**
 * Transform Center Specifier abstract class.
 * Subclasses must be able to inform the coordinates
 * of the center of rotation, translation and scaling, in model coordinates.
 */
class VGL_API VglTransformCenterSpecifier
{
public:
  /**
   * Destructor.
   */
  virtual ~VglTransformCenterSpecifier() {}
  /**
   * The transform center must be updated (some manipulation has just ended!).
   */
  virtual void UpdateTransformCenter() = 0;
  /**
   * Must return the coordinates of the center of rotation, translation and
   * scaling in pointers 'ocx', 'ocy' and 'ocz' (model coordinates).
   */
  virtual void GetTransformCenter(float *ocx, float *ocy, float *ocz) = 0;
  /**
   * A method to explicitly set the new transform center.
   * 'cx', 'cy', and 'cz' will be the new transform center (model coordinates).
   */
  virtual void SetTransformCenter(float cx, float cy, float cz) = 0;
  /**
   * Adds an user of the center specified by this object.
   */
  virtual void AddTransformCenterUser (VglTransformCenterUser *tcu);
};

class VGL_API VglTransformCenterUser
{
public:
  /**
   * Constructor.
   */
  VglTransformCenterUser();
  /**
   * Destructor.
   */
  virtual ~VglTransformCenterUser();
  /**
   * Specifies an application object for obtaining and updating the transform
   * center.
   * 
   * 'applicationmustdelete': must the application be responsible for freeing
   * 'tcs' resources ?
   *
   * See the VglTransformCenterSpecifier interface documentation for details.
   */
  void SetTransformCenterSpecifier (VglTransformCenterSpecifier *tcs, bool applicationmustdelete=true);
  /**
   * Method for clients of the transform center user to be able to specify a new
   * transform center themselves.
   */
  void SetTransformCenter (float cx, float cy, float cz)
  {
    if (HasTransformCenterSpecifier())
      m_tcs->SetTransformCenter(cx, cy, cz);
  }
protected:
  /**
   * Obtains the transform center specifier.
   */
  VglTransformCenterSpecifier *GetTransformCenterSpecifier() const
  {
    return m_tcs;
  }
  bool HasTransformCenterSpecifier () const
  {
    return m_tcs != NULL;
  }
private:
  VglTransformCenterSpecifier *m_tcs;
  bool m_free_tcs;
};

#endif
