#ifndef SG_VGL_CAMERA_H
#define SG_VGL_CAMERA_H

#include <sg/camera.h>
#include <sg/node.h>
#include <vgl/camera.h>
#include <vgl/frustum.h>
#include <utl/writer.h>
#include <assert.h>

class SGVglCamera : public SGCamera
{
  VglCamera* m_camera;
public:
  SGVglCamera(VglCamera* camera=0) : SGCamera(), m_camera(camera)
  {
  }
  virtual ~SGVglCamera()
  {
  }
  VglCamera* GetCamera()
  {
    return m_camera;
  }
  void SetCamera(VglCamera* camera)
  {
    m_camera = camera;
  }
  virtual void Write (UtlWriter* writer)
  {
    assert(m_camera!=NULL);
    writer->WriteSeparator("sgvgl.vglcamera = ");
    m_camera->Write(writer);
  }
  bool Read(FILE* file) 
  {
    assert(m_camera!=NULL);
    return m_camera->Read(file);
  }
  virtual AlgVector GetPosition()
  {
    assert(m_camera!=NULL);
    return m_camera->GetUpdatedPosition();
  }
  virtual AlgVector GetViewDir()
  {
    assert(m_camera!=NULL);
    return m_camera->GetUpdatedViewDir();
  }
  virtual AlgVector GetViewUp ()
  {
    assert(m_camera!=NULL);
    return m_camera->GetUpdatedUp();
  }
  virtual float GetZNear ()
  {
    assert(m_camera!=NULL);
    float znear,zfar;
    m_camera->GetUpdatedZPlanes(&znear,&zfar);
    return znear;
  }
  virtual float GetZFar ()
  {
    assert(m_camera!=NULL);
    float znear,zfar;
    m_camera->GetUpdatedZPlanes(&znear,&zfar);
    return zfar;
  }
  virtual float GetFovX ()
  {
    assert(m_camera);
    return m_camera->GetAngle()*m_camera->GetAspect();
  }
  virtual float GetFovY ()
  {
    assert(m_camera);
    return m_camera->GetAngle();
  }
  virtual AlgPlane GetFrustumPlane(Plane plane)
  {
    VglFrustum f;
    if (plane == SGCamera::LEFT_FRUSTUM_PLANE)   return f.GetPlane(VGL_PLANE_LEFT);
    if (plane == SGCamera::RIGHT_FRUSTUM_PLANE)  return f.GetPlane(VGL_PLANE_RIGHT);
    if (plane == SGCamera::BOTTOM_FRUSTUM_PLANE) return f.GetPlane(VGL_PLANE_BOTTOM);
    if (plane == SGCamera::TOP_FRUSTUM_PLANE)    return f.GetPlane(VGL_PLANE_TOP);
    if (plane == SGCamera::NEAR_FRUSTUM_PLANE)   return f.GetPlane(VGL_PLANE_NEAR);
    if (plane == SGCamera::FAR_FRUSTUM_PLANE)    return f.GetPlane(VGL_PLANE_FAR);
    return AlgPlane(1.0f,0.0f,0.0f,0.0f);
  }
  virtual AlgMatrix GetProjectionMatrix ()
  {
    assert(m_camera!=NULL);
    return m_camera->GetProjection();
  }
  virtual AlgMatrix GetViewMatrix ()
  {
    assert(m_camera!=NULL);
    AlgMatrix m = m_camera->GetModelview();
    if (GetAnchor())
      m.Accum(SGCamera::GetToLocal()); // accum camera model matrix
    return m;
  }
  virtual AlgMatrix GetProjection ()
  {
    return GetProjectionMatrix();
  }
  virtual AlgMatrix GetView ()
  {
    return GetViewMatrix();
  }
  virtual AlgMatrix GetProjectionInverse ()
  {
    return GetProjectionMatrix().Inverse();
  }
  virtual AlgMatrix GetViewInverse ()
  {
    return GetViewMatrix().Inverse();
  }
};

#endif
