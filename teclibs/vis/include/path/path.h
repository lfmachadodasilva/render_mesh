// path.h
// Path interpolating a set of position and rotation
// Dec 2005
// celes@tecgraf.puc-rio.br


#ifndef cam_path_h
#define cam_path_h

#include <alg/spline.h>
#include <alg/qspline.h>
#include "defines.h"

class PATH_API CamPath {
  int m_n;
  int m_size;
  double* m_time;
  double* m_arclength;
  AlgSpline m_pos;
  AlgQSpline m_rot;

public:
  CamPath ();
  ~CamPath ();
  void SetAutoKnotMethod (int autoknot);
  void SetDefaultTension (double v);
  void Begin ();
  void AddKeyFrame (double time);
  void SetPosition (double x, double y, double z);
  void SetOrientation (double angle, double ux, double uy, double uz);
  void SetMatrix (double R[3][3]);
  void SetPosKnot (double t);
  void SetRotKnot (double t);
  void SetPosTension (double v);
  void SetRotTension (double v);
  bool End ();

  bool Recompute ();

  bool ModifyTime (int i, double time);
  bool ModifyPosKnot (int i, double t);
  bool ModifyRotKnot (int i, double t);
  bool ModifyPosTension (int i, double v);
  bool ModifyRotTension (int i, double v);
  bool ModifyPosition (int i, double x, double y, double z);
  bool ModifyOrientation (int i, double angle, double ux, double uy, double uz);
  bool ModifyMatrix (int i, double R[3][3]);

  int GetNKeyFrames ();
  double GetGivenTime (int i);
  void GetGivenPosition (int i, double*x, double* y, double* z);
  void GetGivenOrientation (int i, double* angle, double* ux, double* uy, double* uz);
  double GetPosTension (int i);
  double GetRotTension (int i);
  double GetPosKnot (int i);
  double GetRotKnot (int i);
  /**
   * Obtains the arc length, in world coordinates,
   * at keyframe 'i'.
   */
  double GetArcLengthAt (int i);

  void GetPosition (double time, double* x, double* y, double* z);
  void GetOrientation (double time, double* angle, double* ux, double* uy, double* uz);
  /**
   * Obtains the position at arc length 's', where 's' is between
   * 0 and GetArcLengthAt(GetNKeyFrames()-1).
   */
  void GetPositionL (double s, double* x, double* y, double* z);
  /**
   * Obtains the position at arc length 's', where 's' is between
   * 0 and GetArcLengthAt(GetNKeyFrames()-1).
   */
  void GetOrientationL (double s, double* angle, double* ux, double* uy, double* uz);
  /**
   * Obtains, given an arc length 's' between 0 and GetArcLengthAt(GetNKeyFrames()-1),
   * the camera path time 't'.
   */
  double ConvertArcLengthToTime (double s);
  /**
   * Obtains, given a camera path time 't', the arc length 's' (between 0 and
   * GetArcLengthAt(GetNKeyFrames()-1)).
   */
  double ConvertTimeToArcLength (double t);
protected:
  double ComputeParameter (double t);
  double ComputeParameterL (double s);
  void ComputeParameter (double t, int* pi, double *pp);
  void ComputeParameterL (double s, int* pi, double *pp);
  void UpdateArcLengths ();
private:
  void Reserve (int n);
  void AdjustSize ();
};

#endif

