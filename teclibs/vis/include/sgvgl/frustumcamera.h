#ifndef SG_FRUSTUM_CAMERA_H
#define SG_FRUSTUM_CAMERA_H

#include <sg/camera.h>
#include <vgl/frustum.h>
#include <vgl/util.h>

class SGVglFrustumCamera : public SGCamera
{
  VglFrustum m_frustum;
	AlgMatrix m_projection, m_modelview;
public:
  SGVglFrustumCamera() : m_frustum()
  {
  }
  virtual ~SGVglFrustumCamera()
  {
  }
	void Update ()
	{
		m_modelview = VglUtil::GetModelview();
		m_projection = VglUtil::GetProjection();
		m_frustum.Update(m_modelview.GetMatrix(),m_projection.GetMatrix());
	}
  AlgMatrix& GetModelview()
  {
    return m_modelview;
  }
  virtual AlgVector GetPosition()
  {
    return m_frustum.GetEyePos();
  }
  virtual AlgVector GetViewDir()
  {
    return m_frustum.GetViewDir();
  }
  virtual AlgVector GetViewUp ()
  {
    return m_frustum.GetViewUp();
  }
  virtual float GetZNear ()
  {
    return m_frustum.GetNearDist();
  }
  virtual float GetZFar ()
  {
    return m_frustum.GetFarDist();
  }
  virtual float GetFovX ()
  {
    return m_frustum.GetFovx();
  }
  virtual float GetFovY ()
  {
    return m_frustum.GetFovy();
  }
  virtual AlgPlane GetFrustumPlane(Plane plane)
  {
    if (plane == SGCamera::LEFT_FRUSTUM_PLANE)   return m_frustum.GetPlane(VGL_PLANE_LEFT);
    if (plane == SGCamera::RIGHT_FRUSTUM_PLANE)  return m_frustum.GetPlane(VGL_PLANE_RIGHT);
    if (plane == SGCamera::BOTTOM_FRUSTUM_PLANE) return m_frustum.GetPlane(VGL_PLANE_BOTTOM);
    if (plane == SGCamera::TOP_FRUSTUM_PLANE)    return m_frustum.GetPlane(VGL_PLANE_TOP);
    if (plane == SGCamera::NEAR_FRUSTUM_PLANE)   return m_frustum.GetPlane(VGL_PLANE_NEAR);
    if (plane == SGCamera::FAR_FRUSTUM_PLANE)    return m_frustum.GetPlane(VGL_PLANE_FAR);
    return AlgPlane(1.0f,0.0f,0.0f,0.0f);
  }
	virtual AlgMatrix GetProjection ()
	{
		return m_projection;
	}
	virtual AlgMatrix GetView ()
	{
		AlgMatrix m = GetModelview();
		m.Accum(SGCamera::GetToGlobal()); // accum camera model matrix
		return m;
	}
	virtual AlgMatrix GetProjectionInverse ()
	{
		return GetProjection().Inverse();
	}
	virtual AlgMatrix GetViewInverse ()
	{
		return GetView().Inverse();
	}
};

#endif
