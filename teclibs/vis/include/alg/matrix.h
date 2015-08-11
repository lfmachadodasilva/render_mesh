//* matrix.h
// Implements a 4x4 matrix to support graphics operation.
// celes@tecgraf.puc-rio.br
// fabraham@tecgraf.puc-rio.br
// Jun 2002

#ifndef ALG_MATRIX_H
#define ALG_MATRIX_H

#include "defines.h"
#include "vector.h"
#include "quatern.h"
#include "plane.h"
#include <ds/stack.h>
#include <string.h>

class ALG_API AlgMatrix
{
  float m_v[16];
public:
  static const AlgMatrix& GetIdentity ();
  AlgMatrix()
  {
  }
  /**
   * Copy constructor
   */
  AlgMatrix (const AlgMatrix& m)
  {
    memcpy(m_v,m.m_v,16*sizeof(float));
  }
  AlgMatrix (const float *v)
  {
    memcpy(m_v,v,16*sizeof(float));
  }
  AlgMatrix (const double *v)
  {
    for(int i=0; i<16; i++)
      m_v[i] = (float)v[i];
  }
	AlgMatrix(const AlgVector& x, const AlgVector& y, const AlgVector& z);
  AlgMatrix(const AlgVector& x, const AlgVector& y, const AlgVector& z, const AlgVector& w);
  void operator = (const AlgMatrix&m)
  {
    operator=(m.m_v);
  }
	void operator = (const float* m)
  {
    memcpy(m_v, m, 16*sizeof(float));
  }
  void Identity ();
  void Translate (float x, float y, float z);
  void Translate (const AlgVector& v);
  void Scale (float x, float y, float z);
  void Scale (const AlgVector& v)
  {
    Scale(v.x,v.y,v.z);
  }
  void Scale (float x, float y, float z, float rx, float ry, float rz);
  void Scale (const AlgVector& v, const AlgVector& r);
  void Scale (float s);
  void Rotate (float a, float x, float y, float z);
  void Rotate (float a, const AlgVector& p);
  void Rotate (const AlgQuatern& q);
  void Rotate (float a, float x, float y, float z, float rx, float ry, float rz);
  void Rotate (float a, const AlgVector& p, const AlgVector& r);
  void Rotate (const AlgQuatern& q, const AlgVector& r);
  /**
   * Simplest form of 'Rotate' around an axis: 'c' is the cosine of the
   * angle, 's' is the sine and 'n' is the normalized axis of rotation.
   */
  void Rotate (float c, float s, const AlgVector& n);
  /**
   * Positions at 'p' and matches 'n' with '0,0,1'. Ideal for
   * drawing shapes that are oriented with '0,0,1', like
   * glut*Sphere, glu*Cone, gluCylinder, etc.
   */
  void NewBase (const AlgVector& p, const AlgVector& n);
  void LookAt      (const AlgVector& pos, const AlgVector& target, const AlgVector& up);
  void Ortho       (float pleft, float pright, float pbottom, float ptop, float pnear, float pfar);
  void Frustum     (float pleft, float pright, float pbottom, float ptop, float pnear, float pfar);
  void Perspective (float fovy, float aspect, float znear, float zfar);

  void ProjectFromOrigin (const AlgPlane& plane);
  void ProjectFromPoint (const AlgVector& porigin, const AlgPlane& plane);
  void ProjectInDirection (const AlgVector& direction, const AlgPlane& plane);

  void Accum (const AlgMatrix& m);
  void PreAccum(const AlgMatrix& m);
  void SetMatrix (const float* v);
  void SetMatrix (const double* v);
  void Transpose ();
  bool IsIdentity () const;
  /**
   * Inverts the matrix.
   * Returns 'true' if inversion was possible,
   * 'false' otherwise.
   */
  bool Invert ();
  /**
   * Takes a scale matrix and prepares it to transform normal vectors.
   * This is done by computing the transpose of the inverse of the scale matrix.
   */
  void PrepareScaleToTransformNormals ()
  {
    Invert();
    Transpose();
  }
  AlgMatrix Inverse () const;
  AlgVector Transform(float x, float y, float z) const;
  void Transform (float*x, float*y, float*z) const;
  void Transform (float*x, float*y, float*z, float*w) const;
  void Transform (int n, int nelem, float *v) const
  {
    Transform(n, nelem, v, v);
  }
  /**
   * General batch transform.
   * Takes an array of points at 'src', where vertex 'i' has coordinates
   * x = src[nelem*i], y = src[nelem*i+1], z = src[nelem*i+2] (if nelem>2)
   * and w = src[nelem*i+3] (if nelem==4).
   *
   * Transformed coordinates will be held at the same positions in the
   * destination array 'dst'.
   */
  void Transform (int n, int nelem, float *dst, const float* src) const;
  AlgVector Transform(const AlgVector& p) const;
  AlgVector TransformNormal(float nx, float ny, float nz) const;
  AlgVector TransformNormal(const AlgVector& n) const;
  void      TransformNormals(int n, float *v) const;
  /**
   * Batch transform by 3x3 matrix.
   *
   * Takes an array of points at 'src', where vertex 'i' has coordinates
   * x = src[3*i], y = src[3*i+1] and  z = src[3*i+2].
   *
   * Transformed coordinates will be held at the same positions in the
   * destination array 'dst'.
   */
  void Transform3x3 (int n, float* dst, const float *src) const;
  AlgPlane  TransformPlane(float a, float b, float c, float d) const;
  AlgPlane  TransformPlane(const AlgPlane& p) const;
  AlgVector TransformVector(float vx, float vy, float vz) const;
  AlgVector TransformVector(const AlgVector& v) const;

  /**
   * Finds a basis of the 3D vector space centered on a plane.
   * The i (right) and j (up) directions lie on the plane, while k 
   * is the normal direction.
   * The plane translation is given by the 4th row of the matrix.
   * The returned matrix transforms a point defined in the corresponding
   * plane coordinate system to the canonical basis (ei,ej,ek).
   */
  void PlaneBasis (const AlgPlane& plane);

  /**
   * Finds a basis of the 3D vector space centered at the given point on 
   * the plane (see PlaneBasis()).
   */
  void PlaneBasis (const AlgPlane& plane, const AlgVector& center);

  /**
   * Gets the matrix that transforms a point defined in the 
   * canonical basis (ei,ej,ek) to a coordinate system defined on the
   * plane (see PlaneBasis()). This matrix is the inverse of the
   * a plane basis matrix.
   */
  void InversePlaneBasis (const AlgPlane& plane);

  /**
   * Returns the inverse of the given plane base matrix 
   * (see InversePlaneBasis()).
   */
  void InversePlaneBasis (const AlgPlane& plane, const AlgVector& center);

  /** Sets the value at the position of line i and column j. */
  void Set (int i, int j, float v)
  {   
    m_v[4*j + i] = v;
  }
  const float* GetMatrix () const
  {
    return m_v;
  }
  void GetMatrixDouble (double* v) const
  {
    int i;
    for (i=0; i<16; i++)
      v[i] = m_v[i];
  }
  void Print (const char* label=0) const;
  /**
   * Comparison operator.
   */
  bool operator == (const AlgMatrix& m) const
  {
    return memcmp(m_v, m.m_v, sizeof(m_v)) == 0;
  }
  /**
   * Comparison operator.
   */
  bool operator != (const AlgMatrix& m) const
  {
    return memcmp(m_v, m.m_v, sizeof(m_v)) != 0;
  }
  /**
   * Automatic cast to const float* operator.
   */
  operator const float* () const
  {
    return m_v;
  }
private:
  void InvertPlaneBasis ();
};

class ALG_API AlgStackMatrix : public DsStack<AlgMatrix>
{
public:
  AlgStackMatrix ()
    : DsStack<AlgMatrix>()
  {
    Init();
  }
	void Clear ()
  {
    DsStack<AlgMatrix>::Clear();
    Init();
  }
private:
  void Init ()
  {
    AlgMatrix m;
    m.Identity();
    Push(m);
  }
};

#endif
