// smoothpath.h
// Smooth path interpolating a set of fov, position, target, and view up.
// Aug 2006


#ifndef cam_smoothpath_h
#define cam_smoothpath_h

#include "ds/array.h"
#include "alg/spline.h"
#include "splineapprox.h"
#include "kinematics.h"
#include "defines.h"

class PATH_API CamSmoothPath {
  float m_aspect;
	float m_ttime;
	DsArray<int> m_ind;
	DsArray<float> m_fov;
	DsArray<float> m_pzero;
	DsArray<float> m_stoptime;
  AlgSpline m_pos;
  AlgSpline m_target;
  AlgSpline m_up;
	CamSplineApprox m_posx;
	CamSplineApprox m_targetx;
	CamKinematics* m_fkin;
	CamKinematics* m_zkin;
	CamKinematics* m_pkin;
	CamKinematics* m_tkin;

public:
  CamSmoothPath ();
  ~CamSmoothPath ();
  void Begin (float tension=0.0f);
  void AddKeyFrame (float fovy, 
                    float x, float y, float z,
                    float tx, float ty, float tz,
                    float ux, float uy, float uz,
                    float stoptime=0.0f,
                    float pzero=0.0f);
  void End ();
	void SetTotalTime (float t);
  void SetAspect (float a);
	void Compute (float accel_factor=0.15);

  int GetNKeyFrames ();
	float GetTotalTime ();
  float GetKeyFrameTime (int i);

  float GetFovy (float time);
  float GetPzero (float time);
  void GetPosition (float time, float* x, float* y, float* z);
  void GetTarget (float time, float* x, float* y, float* z);
  void GetUp (float time, float* x, float* y, float* z);

private:
  float ComputeMaxDisplacement (int i);
};

#endif

