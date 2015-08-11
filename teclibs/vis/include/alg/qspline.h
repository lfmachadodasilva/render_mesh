// qspline.h
// v-Quaternion spline interpolation
// Ref. "v-Quaternion Splines for the Smooth Interpolation of Orientations"
// G.M. Nielson, IEEE Trans. on Vis. and C.G., 10(2), 2004.
// Dec 2005
// celes@tecgraf.puc-rio.br


#ifndef utl_qspline_h
#define utl_qspline_h

#include <assert.h>
#include <stdio.h>
#include "defines.h"

class ALG_API AlgQSpline
{
  struct Quat {
    double x, y, z, w;
    Quat () {}
    Quat (double angle, double ux, double uy, double uz);
  };

  int m_n;       // number of given Orientations (in fact, n+1 Orientations are given)
  int m_size;    // allocated size of vectors 
  int*  m_ind;   // orientation indirection (to deal with duplicate orientations)
  Quat* m_Q;     // interpolation Orientations
  Quat* m_R;     // right control Orientations
  Quat* m_L;     // left control Orientations
  double* m_t;    // knot values
  double* m_v;    // tension values

  double* m_a;    // temporary A-vector of tridiagonal system
  double* m_b;    // temporary B-vector of tridiagonal system
  double* m_c;    // temporary C-vector of tridiagonal system
  Quat* m_d0;    // temporary C-vector of tridiagonal system
  Quat* m_d;     // temporary C-vector of tridiagonal system

  int   m_auto_knot; // automatic knot value generation (0=NONE, 1=UNIFORM, 2=NONUNIFORM)
  double m_def_v;     // current tension value 

public:
  AlgQSpline ();
  ~AlgQSpline ();

    // Set the default tension value
  void SetDefaultTension (double v);
  // Set the auto knot value generation method (0=NONE, 1=UNIFORM, 2=NONUNIFORM)
  // This value is used when computing the spline.
  void SetAutoKnotMethod (int autoknot);
  // Begin interpolation Quat
  // It resets all existing data. 
  void Begin ();
  // Add an interpolation orientation, giving the angle and direction of rotation.
  void AddOrientation (double angle, double ux, double uy, double uz);
  // Add an interpolation orientation, giving the rotation matrix.
  void AddMatrix (double R[3][3]);
  // Set tension value of last added ratation
  void SetTension (double v);
  // Set knot value of last added ratation
  void SetKnot (double t);
  // Signilize the end of interpolation Quat.
  // It computes the quaternion spline, returning 'true' on success.
  bool End ();

  // Re-set an interpolation orientation
  bool ModifyOrientation (int i, double angle, double ux, double uy, double uz);
  // Re-set an interpolation orientation
  bool ModifyMatrix (int i, double R[3][3]);
  // Re-set a knot value
  bool ModifyKnot (int i, double t);
  // Re-set a tension value
  bool ModifyTension (int i, double v);
  // Re-compute the qspline
  // It returns 'true' on success.
  bool Recompute ();

  // Return the corresponding Orientation
  // If the value of t is out of range, it is clamped to the initial or final value.
  void GetOrientation (double t, double* angle, double* ux, double* uy, double* uz);

  // Return number of rotations
  int GetNOrientations ();
    // Return the corresponding given rotation
  void GetGivenOrientation (int i, double* angle, double* ux, double* uy, double* uz);
  // Return the corresponding knot value
  double GetKnot (int i);
  // Return the corresponding tension value
  double GetTension (int i);



private:
  double Ti (int i) {
    assert(i>=0 && i<=m_n);
    return m_t[i];
  }
  double Ni (int i) {
    assert(i>=0 && i<=m_n);
    return m_v[i];
  }
  double Hi (int i) {
    return (i==0 || i==m_n+1) ? 0.0f : Ti(i) - Ti(i-1);
  }
  double Gi (int i) {
    return 2*(Hi(i) + Hi(i+1)) / (Ni(i)*Hi(i)*Hi(i+1) + 2*(Hi(i)+Hi(i+1)));
  }
  double Mi (int i) {
    return (Gi(i)*Hi(i)) / (Gi(i)*Hi(i) + Hi(i+1) + Gi(i+1)*Hi(i+2));
  }
  double Li (int i) {
    return (Gi(i-1)*Hi(i-1) + Hi(i)) / (Gi(i-1)*Hi(i-1) + Hi(i) + Gi(i)*Hi(i+1));
  }
  double Di (int i) {
    return Hi(i) / (Hi(i)+Hi(i+1));
  }

  const Quat& MatrixToQuat (double R[3][3]);
  const Quat& CorrectDirection (const Quat&q);
  void QuatToOrientation (const Quat& q, double* angle, double* ux, double* uy, double* uz);
  void GenerateKnot ();
  void EliminateDuplications ();
  double Angle (const Quat& q0, const Quat& q1); 
  const Quat& Geodesic (double t, const Quat& q0, const Quat& q1);

  void FillA ();
  void FillB ();
  void FillC ();
  bool Solve4DSpline ();
  void Normalize (Quat* d);
  void SolveQSpline ();
  double EvalMaxError (Quat* d, Quat* d0);
  void FillRL ();

  void Reserve ();
  void AdjustSize ();
  void AllocAux();
  void FreeAux();
  void AllocTemp ();
  void FreeTemp ();



public:
  void Debug ();
};


#endif

