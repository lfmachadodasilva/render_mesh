#ifndef SG_CAMERA_H
#define SG_CAMERA_H

#include <alg/matrix.h>
#include <alg/vector.h>
#include <alg/plane.h>
#include "refcount.h"

class SGNode;
/**
 * SGCamera Class.
 * 
 * This is the base class for all camera management classes to provide compatibility with the scene graph.
 *
 * It provides methods to:
 * - anchor the camera with a scene graph node's coordinate system.
 * - obtain the matrices that transform a point:
 *    - from the global coordinate system to the anchor node's coordinate system.
 *    - from the anchor node's coordinate system to the global coordinate system.
 *
 * It provides an interface for concrete classes to obtain the camera's:
 * - position
 * - orientation
 * - near and far plane distances
 * - field of view angles
 * - view frustum planes
 * - view and projection matrices and their inverses
 */
class SG_API SGCamera : public SGRefCount
{
  SGNode* m_anchor;
public:
  /**
   * Frustum plane ids.
   */
  typedef enum 
  {
    LEFT_FRUSTUM_PLANE=0,
    RIGHT_FRUSTUM_PLANE,
    BOTTOM_FRUSTUM_PLANE,
    TOP_FRUSTUM_PLANE,
    NEAR_FRUSTUM_PLANE,
    FAR_FRUSTUM_PLANE
  } Plane;
  static const char* CLASSNAME () { return "Camera"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
  /**
   * Constructor
   */
  SGCamera ();
  /**
   * Destructor
   */
  virtual ~SGCamera ();
  /**
   * Anchors the camera with a scene graph node. 
   * The camera's coordinates will be relative to the node's local coordinate system. 
   * A NULL anchor node means the camera's coordinates are relative to the world's coordinate system.
   */
  void SetAnchor(SGNode* anchor)
  {
    m_anchor = anchor;
  }
  /**
   * Obtains the camera's anchor node, NULL is no anchor node is set.
   */
  SGNode* GetAnchor () const
  {
    return m_anchor; 
  }
  /**
   * Obtains the matrix that describes the transformation from 
   * the global coordinate system to the anchor node's coordinate system.
   */
  AlgMatrix GetToLocal ();
  /**
   * Obtains the matrix that describes the transformation from 
   * the anchor node's coordinate system to the global coordinate system.
   */
  AlgMatrix GetToGlobal ();
  /**
   * Obtains the camera's position in its anchor's coordinate system.
   */
  virtual AlgVector GetPosition() = 0;
  /**
   * Obtains the camera's view direction in its anchor's coordinate system.
   */
  virtual AlgVector GetViewDir() = 0;
  /**
   * Obtains the camera's up vector in its anchor's coordinate system.
   */
  virtual AlgVector GetViewUp () = 0;
  /**
   * Obtains the camera's near plane distance.
   */
  virtual float GetZNear () = 0;
  /**
   * Obtains the camera's far plane distance.
   */
  virtual float GetZFar () = 0;
  /**
   * Obtains the current angle of the field of view in the y-z plane.
   */
  virtual float GetFovX () = 0;
  /**
   * Obtains the current angle of the field of view in the x-z plane.
   */
  virtual float GetFovY () = 0;
  /**
   * Obtains the frustum plane in the camera anchor's coordinate system.
   */
  virtual AlgPlane GetFrustumPlane(Plane id) = 0;
  /**
   * Obtains the current view matrix.
   */
  virtual AlgMatrix GetView () = 0;
  /**
   * Obtains the current projection matrix.
   */
  virtual AlgMatrix GetProjection () = 0;
  /**
   * Obtains the inverse of the current view matrix.
   * Implementations can cache the inverse, not calculating it by demand.
   */
  virtual AlgMatrix GetViewInverse () = 0;
  /**
   * Obtains the inverse of the current projection matrix.
   * Implementations can cache the inverse, not calculating it by demand.
   */
  virtual AlgMatrix GetProjectionInverse () = 0;
};

#endif

