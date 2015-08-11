// spline.h
// v-Spline interpolation
// Ref. "v-Quaternion Splines for the Smooth Interpolation of Orientations"
// G.M. Nielson, IEEE Trans. on Vis. and C.G., 10(2), 2004.
// Dec 2005
// celes@tecgraf.puc-rio.br


#ifndef utl_spline_h
#define utl_spline_h

#include <utl/defines.h>

#include <assert.h>

class UTL_API UtlSpline
{
  struct Point {
    double x, y, z;
  };
  int m_n;       // number of given Positions (in fact, n+1 Positions are given)
  int m_size;    // allocated size of vectors 
  int* m_ind;    // point indirection (to deal with duplicate points)
  Point* m_P;    // interpolation Positions
  Point* m_R;    // right control Positions
  Point* m_L;    // left control Positions
  double* m_t;    // knot values
  double* m_v;    // tension values

  double* m_a;    // temporary A-vector of tridiagonal system
  double* m_b;    // temporary B-vector of tridiagonal system
  double* m_c;    // temporary C-vector of tridiagonal system
  Point* m_d;    // temporary C-vector of tridiagonal system

  int   m_auto_knot; // automatic knot value generation (0=NONE, 1=UNIFORM, 2=NONUNIFORM)
  double m_def_v;     // default tension value 

public:
  UtlSpline ();
  ~UtlSpline ();

  // Set the default tension value
  void SetDefaultTension (double v);
  // Set the auto knot value generation method (0=NONE, 1=UNIFORM, 2=NONUNIFORM)
  // This value is used when computing the spline.
  void SetAutoKnotMethod (int autoknot);
  // Begin interpolation Point
  // It resets all existing data. 
  void Begin ();
  // Add an interpolation Point.
  void AddPosition (double x, double y, double z);
  // Set tension value of last added position
  void SetTension (double v);
  // Set knot value of last added position
  void SetKnot (double t);
  // Signilize the end of interpolation Point.
  // It computes the spline, returning 'true' on success.
  bool End ();

  // Re-set an interpolation Point
  bool ModifyPosition (int i, double x, double y, double z);
  // Re-set a knot value
  bool ModifyKnot (int i, double t);
  // Re-set a tension value
  bool ModifyTension (int i, double v);
  // Re-compute the spline
  // It returns 'true' on success.
  bool Recompute ();

  // Return the corresponding Point coordinate
  // If the value of t is out of range, it is clamped to the initial or final value.
  void GetPosition (double t, double* x, double* y, double* z);

  // Return number of positions
  int GetNPositions ();
  // Return the corresponding given position
  void GetGivenPosition (int i, double* x, double* y, double* z);
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

  void GenerateKnot ();
  void EliminateDuplications ();
  double Distance (const Point& p0, const Point& p1);
  const Point& Linear (double t, const Point& p0, const Point& p1);

  void FillA ();
  void FillB ();
  void FillC ();
  bool SolveD ();
  void FillR ();
  void FillL ();

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

