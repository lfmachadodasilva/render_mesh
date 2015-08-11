/// vector.h
// 3D vector of single-precision values
// celes@tecgraf.puc-rio.br
// vbarata@tecgraf.puc-rio.br
// Jul 2002 - Apr 2009

#ifndef ALG_VECTOR_H
#define ALG_VECTOR_H

#include "defines.h"

#include <math.h>
#include <stdio.h>
#include <assert.h>

class ALGH_API AlgVector
{
public:
  union {
    struct {
      float x;   // X-Coordinate 
      float y;   // Y-Coordinate
      float z;   // Z-Coordinate 
    };
    struct {
      float r; 
      float g; 
      float b;
    };
  };
public:
  /**
   * Default Constructor
   */
  AlgVector ()
  {
  }

  /**
   * Scalar Constructor
   */
  AlgVector (float scalar)
  : x(scalar)
  , y(scalar)
  , z(scalar)
  {
  }

  /**
   * Coordinate Constructor
   */
  AlgVector (float vx, float vy, float vz)
  : x(vx)
  , y(vy)
  , z(vz)
  {
  }

  /**
   * Array Constructor
   */
  AlgVector (const float v[3])
  : x(v[0])
  , y(v[1])
  , z(v[2])
  {
  }

  /**
   * Copy Constructor
   */
  AlgVector (const AlgVector& v)
  : x(v.x)
  , y(v.y)
  , z(v.z)
  {
  }

  /**
   * Destructor
   */
  ~AlgVector ()
  {
  }

  /**
   * Cast to float array
   */
  operator float* () const
  {
    return (float*) &x;
  }

  /**
   * Cast to constant float array
   */
  operator const float* () const
  {
    return (const float*) &x;
  }

  /**
   * Scalar Setter
   */
  void Set (float scalar)
  {
    x = scalar;
    y = scalar;
    z = scalar;
  }

  /**
   * Coordinate Setter
   */
  void Set (float vx, float vy, float vz)
  {
    x = vx;
    y = vy;
    z = vz;
  }

  /**
   * Array Setter
   */
  void Set (const float v[3])
  {
    x = v[0];
    y = v[1];
    z = v[2];
  }

  /**
   * Copy Setter
   */
  void Set (const AlgVector& v)
  {
    x = v.x;
    y = v.y;
    z = v.z;
  }

  /**
   * Assignment
   */
  AlgVector& operator = (const AlgVector& v)
  {
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
  }

  /**
   * Unary Positive sign
   */
  AlgVector operator + () const
  {
    return *this;
  }

  /**
   * Unary Negative Sign
   */
  AlgVector operator - () const
  {
    return AlgVector(-x, -y, -z);
  }

  /**
   * Equality
   */
  friend bool operator == (const AlgVector& v1, const AlgVector& v2)
  {
    return (v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z);
  }

  /**
   * Inequality
   */
  friend bool operator != (const AlgVector& v1, const AlgVector& v2)
  {
    return (v1.x != v2.x) || (v1.y != v2.y) || (v1.z != v2.z);
  }

  /**
   * All coordinates must satisfy the comparison.
   * Useful to check if a vertex is inside a bounding box:
   * if (v >= bbmin && bbmax >= v) { // is inside }
   */
  friend bool operator >= (const AlgVector& v1, const AlgVector& v2)
  {
    return (v1.x >= v2.x) && (v1.y >= v2.y) && (v1.z >= v2.z);
  }

  /**
   * All coordinates must satisfy the comparison.
   * Useful to check if a vertex is inside a bounding box:
   * if (bbmin <= v && v <= bbmax) { // is inside }
   */
  friend bool operator <= (const AlgVector& v1, const AlgVector& v2)
  {
    return (v1.x <= v2.x) && (v1.y <= v2.y) && (v1.z <= v2.z);
  }

  /**
   * Add another vector in place
   */
  AlgVector& operator += (const AlgVector& v2)
  {
    x += v2.x;
    y += v2.y;
    z += v2.z;
    return *this;
  }

  /**
   * Subtract another vector in place
   */
  AlgVector& operator -= (const AlgVector& v2)
  {
    x -= v2.x;
    y -= v2.y;
    z -= v2.z;
    return *this;
  }

  /**
   * Multiply another vector, component by component, in place
   */
  AlgVector& operator *= (const AlgVector& v2)
  {
    x *= v2.x;
    y *= v2.y;
    z *= v2.z;
    return *this;
  }

  /**
   * Divide by another vector, component by component, in place
   */
  AlgVector& operator /= (const AlgVector& v2)
  {
    assert(v2.x != 0.0f && v2.y != 0.0f && v2.z != 0.0f);
    x /= v2.x;
    y /= v2.y;
    z /= v2.z;
    return *this;
  }

  /**
   * Add a scalar in place
   */
  AlgVector& operator += (float scalar)
  {
    x += scalar;
    y += scalar;
    z += scalar;
    return *this;
  }

  /**
   * Subtract a scalar in place
   */
  AlgVector& operator -= (float scalar)
  {
    x -= scalar;
    y -= scalar;
    z -= scalar;
    return *this;
  }

  /**
   * Multiply a scalar in place
   */
  AlgVector& operator *= (float scalar)
  {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
  }

  /**
   * Divide by a scalar in place
   */
  AlgVector& operator /= (float scalar)
  {
    assert(scalar != 0.0f);
    float factor = 1.0f/scalar;
    x *= factor;
    y *= factor;
    z *= factor;
    return *this;
  }

  /**
   * Add two vectors
   */
  friend AlgVector operator + (const AlgVector& v1, const AlgVector& v2)
  {
    return AlgVector(v1.x+v2.x, v1.y+v2.y, v1.z+v2.z);
  }

  /**
   * Subtract two vectors
   */
  friend AlgVector operator - (const AlgVector& v1, const AlgVector& v2)
  {
    return AlgVector(v1.x-v2.x, v1.y-v2.y, v1.z-v2.z);
  }

  /**
   * Multiply two vectors component by component
   */
  friend AlgVector operator * (const AlgVector& v1, const AlgVector& v2)
  {
    return AlgVector(v1.x*v2.x, v1.y*v2.y, v1.z*v2.z);
  }

  /**
   * Divide two vectors component by component
   */
  friend AlgVector operator / (const AlgVector& v1, const AlgVector& v2)
  {
    assert(v2.x != 0.0f && v2.y != 0.0f && v2.z != 0.0f);
    return AlgVector(v1.x/v2.x, v1.y/v2.y, v1.z/v2.z);
  }

  /**
   * Add a vector and a scalar
   */
  friend AlgVector operator + (const AlgVector& v, float scalar)
  {
    return AlgVector(v.x+scalar, v.y+scalar, v.z+scalar);
  }

  /**
   * Subtract a vector by a scalar
   */
  friend AlgVector operator - (const AlgVector& v, float scalar)
  {
    return AlgVector(v.x-scalar, v.y-scalar, v.z-scalar);
  }

  /**
   * Multiply a vector by a scalar
   */
  friend AlgVector operator * (const AlgVector& v, float scalar)
  {
    return AlgVector(v.x*scalar, v.y*scalar, v.z*scalar);
  }

  /**
   * Divide a vector by a scalar
   */
  friend AlgVector operator / (const AlgVector& v, float scalar)
  {
    assert(scalar != 0.0f);
    float factor = 1.0f/scalar;
    return AlgVector(v.x*factor, v.y*factor, v.z*factor);
  }

  /**
   * Add a scalar and a vector
   */
  friend AlgVector operator + (float scalar, const AlgVector& v)
  {
    return AlgVector(scalar+v.x, scalar+v.y, scalar+v.z);
  }

  /**
   * Subtract a scalar by a vector
   */
  friend AlgVector operator - (float scalar, const AlgVector& v)
  {
    return AlgVector(scalar-v.x, scalar-v.y, scalar-v.z);
  }

  /**
   * Multiply a scalar by a vector
   */
  friend AlgVector operator * (float scalar, const AlgVector& v)
  {
    return AlgVector(scalar*v.x, scalar*v.y, scalar*v.z);
  }

  /**
   * Divide a scalar by a vector
   */
  friend AlgVector operator / (float scalar, const AlgVector& v)
  {
    assert(v.x != 0.0f && v.y != 0.0f && v.z != 0.0f);
    return AlgVector(scalar/v.x, scalar/v.y, scalar/v.z);
  }

  /**
   * Dot product
   */
  friend float operator % (const AlgVector& v1, const AlgVector& v2)
  {
    return v1.Dot(v2);
  }

  /**
   * Cross product
   */
  friend AlgVector operator ^ (const AlgVector& v1, const AlgVector& v2)
  {
    return v1.Cross(v2);
  }

  /**
   * Cross Product Operator, in-place
   */
  AlgVector& operator ^= (const AlgVector& v2)
  {
    float newX = y*v2.z - z*v2.y;
    float newY = z*v2.x - x*v2.z;
    float newZ = x*v2.y - y*v2.x;
    x = newX;
    y = newY;
    z = newZ;
    return *this;
  }

  /**
   * Length
   */
  float Length () const
  {
    return (float)sqrt(SqrLength());
  }

  /**
   * Squared Length
   */
  float SqrLength () const
  {
    return (x*x+y*y+z*z);
  }

  /**
   * Distance between two points
   */
  float Distance (const AlgVector& v2) const
  {
    return (float)sqrt(SqrDistance(v2));
  }

  /**
   * Squared distance between two points
   */
  float SqrDistance (const AlgVector& v2) const
  {
    float dx = x-v2.x;
    float dy = y-v2.y;
    float dz = z-v2.z;
    return (dx*dx+dy*dy+dz*dz);
  }

  /**
   * Normalizes the vector. Returns the previous vector length.
   * Must not be called on zero or almost-zero length vectors.
   * (This last restriction has been temporarily relaxed.)
   */
  float Normalize ()
  {
    float sqrlen = SqrLength();
    //assert(sqrlen != 0.0f && ALG_FINITE(sqrlen));
    if (sqrlen != 0.0f && ALG_FINITE(sqrlen))
    {
      float len = (float)sqrt(sqrlen);
      float factor = 1.0f/len;
      x *= factor;
      y *= factor;
      z *= factor;
      return len;
    }
    return 0.0f;
  }

  /**
   * Dot Product
   */
  float Dot (const AlgVector& v2) const
  {
    return x*v2.x + y*v2.y + z*v2.z;
  }

  /**
   * Dot Product with 'x', 'y' and 'z'.
   */
  float Dot (float v2x, float v2y, float v2z) const
  {
    return x*v2x + y*v2y + z*v2z;
  }

  /**
   * Cross Product
   */
  AlgVector Cross (const AlgVector& v2) const
  {
    return AlgVector(y*v2.z - z*v2.y,
                     z*v2.x - x*v2.z,
                     x*v2.y - y*v2.x);
  }

  /**
   * Cross Product assignment (backward compatibility - deprecated)
   */
  void Cross (const AlgVector& v1, const AlgVector& v2)
  {
    x = v1.y*v2.z - v1.z*v2.y;
    y = v1.z*v2.x - v1.x*v2.z;
    z = v1.x*v2.y - v1.y*v2.x;
  }

  /**
   * Angle in radians to another vector.
   */
  float Angle (const AlgVector& v2) const
  {
    float sqrlen1 = SqrLength();
    float sqrlen2 = v2.SqrLength();
    assert(sqrlen1 != 0.0f && ALG_FINITE(sqrlen1));
    assert(sqrlen2 != 0.0f && ALG_FINITE(sqrlen2));
    return (float)acos(Dot(v2) / (float)sqrt(sqrlen1 * sqrlen2));
  }

  /**
   * Orthogonally project on a unit vector
   */
  void Project (const AlgVector& unit_v2)
  {
    float factor = Dot(unit_v2);
    x = unit_v2.x * factor;
    y = unit_v2.y * factor;
    z = unit_v2.z * factor;
  }

  /**
   * Orthogonally project on a plane given its unit normal
   */
  void NProject (const AlgVector& unit_v2)
  {
    float factor = Dot(unit_v2);
    x -= unit_v2.x * factor;
    y -= unit_v2.y * factor;
    z -= unit_v2.z * factor;
  }

  /**
   * Reflect the vector on a plane given its unit normal
   */
  void Reflect (const AlgVector& unit_v2)
  {
    float factor = 2.0f * Dot(unit_v2);
    x -= unit_v2.x * factor;
    y -= unit_v2.y * factor;
    z -= unit_v2.z * factor;
  }

  /**
   * Refract the unit vector on a plane
   *
   * The calling vector must be normalized
   * unit_v2: Plane unit normal
   * eta: Ratio of indices of refraction (source/target medium)
   * Returns whether refraction was possible
   */
  bool Refract (const AlgVector& unit_v2, float eta)
  {
    float dot = Dot(unit_v2);
    float k = 1.0f - eta * eta * (1.0f - dot * dot);
    if (k < 0.0f)
      return false;
    float factor = eta * dot + (float)sqrt(k);
    x *= eta;
    y *= eta;
    z *= eta;
    x -= factor * unit_v2.x;
    y -= factor * unit_v2.y;
    z -= factor * unit_v2.z;
    return true;
  }

  /**
   * Rotate an angle in radians around the X-axis
   */
  void RotateX (float angle_rad)
  {
    float rot_sin = (float)sin((double)angle_rad);
    float rot_cos = (float)cos((double)angle_rad);
    float newY = y*rot_cos - z*rot_sin;
    float newZ = y*rot_sin + z*rot_cos;
    y = newY;
    z = newZ;
  }

  /**
   * Rotate an angle in radians around the X-axis through a reference point
   */
  void RotateX (float angle_rad, const AlgVector& ref_point)
  {
    x -= ref_point.x;
    y -= ref_point.y;
    z -= ref_point.z;
    RotateX(angle_rad);
    x += ref_point.x;
    y += ref_point.y;
    z += ref_point.z;
  }

  /**
   * Rotate an angle in radians around the Y-axis
   */
  void RotateY (float angle_rad)
  {
    float rot_sin = (float)sin((double)angle_rad);
    float rot_cos = (float)cos((double)angle_rad);
    float newZ = z*rot_cos - x*rot_sin;
    float newX = z*rot_sin + x*rot_cos;
    z = newZ;
    x = newX;
  }

  /**
   * Rotate an angle in radians around the Y-axis through a reference point
   */
  void RotateY (float angle_rad, const AlgVector& ref_point)
  {
    x -= ref_point.x;
    y -= ref_point.y;
    z -= ref_point.z;
    RotateY(angle_rad);
    x += ref_point.x;
    y += ref_point.y;
    z += ref_point.z;
  }

  /**
   * Rotate an angle in radians around the Z-axis
   */
  void RotateZ (float angle_rad)
  {
    float rot_sin = (float)sin((double)angle_rad);
    float rot_cos = (float)cos((double)angle_rad);
    float newX = x*rot_cos - y*rot_sin;
    float newY = x*rot_sin + y*rot_cos;
    x = newX;
    y = newY;
  }

  /**
   * Rotate an angle in radians around the Z-axis through a reference point
   */
  void RotateZ (float angle_rad, const AlgVector& ref_point)
  {
    x -= ref_point.x;
    y -= ref_point.y;
    z -= ref_point.z;
    RotateZ(angle_rad);
    x += ref_point.x;
    y += ref_point.y;
    z += ref_point.z;
  }

  /**
   * Rotate an angle in radians around a unit axis
   */
  void Rotate (const AlgVector& unit_axis, float angle_rad)
  {
    float rot_sin = (float)sin((double)angle_rad);
    float rot_cos = (float)cos((double)angle_rad);
    float rot_ncos = 1.0f - rot_cos;
    AlgVector cross = Cross(unit_axis);
    AlgVector vproj(x,y,z);
    vproj.Project(unit_axis);
    x *= rot_cos;
    y *= rot_cos;
    z *= rot_cos;
    x += vproj.x * rot_ncos;
    y += vproj.y * rot_ncos;
    z += vproj.z * rot_ncos;
    x -= cross.x * rot_sin;
    y -= cross.y * rot_sin;
    z -= cross.z * rot_sin;
  }

  /**
   * Rotate an angle in radians around a unit axis through a reference point
   */
  void Rotate (const AlgVector& unit_axis, float angle_rad, const AlgVector& ref_point)
  {
    x -= ref_point.x;
    y -= ref_point.y;
    z -= ref_point.z;
    Rotate(unit_axis, angle_rad);
    x += ref_point.x;
    y += ref_point.y;
    z += ref_point.z;
  }

  /**
   * Linearly interpolate with a given weight of another vector
   */
  AlgVector Lerp (const AlgVector& v2, float weight2) const
  {
    float weight1 = 1.0f - weight2;
    return AlgVector(weight1*x + weight2*v2.x,
                     weight1*y + weight2*v2.y,
                     weight1*z + weight2*v2.z);
  }

  // The following methods are provided as shortcuts to make code more readable.
  // However, when efficiency is important, it is faster to manually copy the
  // desired vector and call the in-place method on that copy. This prevents
  // the creation of an additional temporary object.

  /**
   * Returns the normalized vector
   */
  AlgVector Normalized () const
  {
    AlgVector vec(x,y,z);
    vec.Normalize();
    return vec;
  }

  /**
   * Orthogonal projection on a unit vector
   */
  AlgVector Projected (const AlgVector& unit_v2) const
  {
    AlgVector vec(x,y,z);
    vec.Project(unit_v2);
    return vec;
  }

  /**
   * Orthogonal projection on a plane given its unit normal
   */
  AlgVector NProjected (const AlgVector& unit_v2) const
  {
    AlgVector vec(x,y,z);
    vec.NProject(unit_v2);
    return vec;
  }

  /**
   * Vector reflection on a plane given its unit normal
   */
  AlgVector Reflected (const AlgVector& unit_v2) const
  {
    AlgVector vec(x,y,z);
    vec.Reflect(unit_v2);
    return vec;
  }

  /**
   * Unit vector refraction on a plane
   *
   * The calling vector must be normalized
   * unit_v2: Plane unit normal
   * eta: Ratio of indices of refraction (source/target medium)
   * Returns the refracted vector if possible, unchanged otherwise
   */
  AlgVector Refracted (const AlgVector& unit_v2, float eta) const
  {
    AlgVector vec(x,y,z);
    vec.Refract(unit_v2, eta);
    return vec;
  }

  /**
   * Vector rotated an angle in radians around the X-axis
   */
  AlgVector RotatedX (float angle_rad) const
  {
    AlgVector vec(x,y,z);
    vec.RotateX(angle_rad);
    return vec;
  }

  /**
   * Vector rotated an angle in radians around the X-axis through a reference point
   */
  AlgVector RotatedX (float angle_rad, const AlgVector& ref_point) const
  {
    AlgVector vec(x,y,z);
    vec.RotateX(angle_rad, ref_point);
    return vec;
  }

  /**
   * Vector rotated an angle in radians around the Y-axis
   */
  AlgVector RotatedY (float angle_rad) const
  {
    AlgVector vec(x,y,z);
    vec.RotateY(angle_rad);
    return vec;
  }

  /**
   * Vector rotated an angle in radians around the Y-axis through a reference point
   */
  AlgVector RotatedY (float angle_rad, const AlgVector& ref_point) const
  {
    AlgVector vec(x,y,z);
    vec.RotateY(angle_rad, ref_point);
    return vec;
  }

  /**
   * Vector rotated an angle in radians around the Z-axis
   */
  AlgVector RotatedZ (float angle_rad) const
  {
    AlgVector vec(x,y,z);
    vec.RotateZ(angle_rad);
    return vec;
  }

  /**
   * Vector rotated an angle in radians around the Z-axis through a reference point
   */
  AlgVector RotatedZ (float angle_rad, const AlgVector& ref_point) const
  {
    AlgVector vec(x,y,z);
    vec.RotateZ(angle_rad, ref_point);
    return vec;
  }

  /**
   * Vector rotated an angle in radians around a unit axis
   */
  AlgVector Rotated (const AlgVector& unit_axis, float angle_rad) const
  {
    AlgVector vec(x,y,z);
    vec.Rotate(unit_axis, angle_rad);
    return vec;
  }

  /**
   * Vector rotated an angle in radians around a unit axis through a reference point
   */
  AlgVector Rotated (const AlgVector& unit_axis, float angle_rad, const AlgVector& ref_point) const
  {
    AlgVector vec(x,y,z);
    vec.Rotate(unit_axis, angle_rad, ref_point);
    return vec;
  }

  /**
   * Print this vector to the console
   */
  void Print (const char* label) const
  {
    printf("%s = {%g, %g, %g}\n", label, x, y, z);
  }
};

/**
 * Receives a point and updates bounding box limits 'bbmin' and 'bbmax'.
 * Assumes bbmin.[xyz] < bbmax.[xyz].
 */
inline ALGH_API void AlgUpdateBB (float x, float y, float z, AlgVector& bbmin, AlgVector& bbmax)
{
  if      (x < bbmin.x) bbmin.x = x;
  else if (x > bbmax.x) bbmax.x = x;
  if      (y < bbmin.y) bbmin.y = y;
  else if (y > bbmax.y) bbmax.y = y;
  if      (z < bbmin.z) bbmin.z = z;
  else if (z > bbmax.z) bbmax.z = z;
}

/**
 * Receives a point and computes bounding box limits 'bbmin' and 'bbmax'.
 * 'bbmin' should be first set to  FLT_MAX,  FLT_MAX,  FLT_MAX.
 * 'bbmax' should be first set to -FLT_MAX, -FLT_MAX, -FLT_MAX.
 */
inline ALGH_API void AlgComputeBB (float x, float y, float z, AlgVector& bbmin, AlgVector& bbmax)
{
  if (x < bbmin.x) bbmin.x = x;
  if (x > bbmax.x) bbmax.x = x;
  if (y < bbmin.y) bbmin.y = y;
  if (y > bbmax.y) bbmax.y = y;
  if (z < bbmin.z) bbmin.z = z;
  if (z > bbmax.z) bbmax.z = z;
}

/**
 * Receives a point and updates bounding box limits 'bbmin' and 'bbmax'.
 * Assumes bbmin.[xyz] < bbmax.[xyz].
 */
inline ALGH_API void AlgUpdateBB (const AlgVector& v, AlgVector& bbmin, AlgVector& bbmax)
{
  AlgUpdateBB(v.x, v.y, v.z, bbmin, bbmax);
}

/**
 * Receives a point and computes bounding box limits 'bbmin' and 'bbmax'.
 * 'bbmin' should be first set to  FLT_MAX,  FLT_MAX,  FLT_MAX.
 * 'bbmax' should be first set to -FLT_MAX, -FLT_MAX, -FLT_MAX.
 */
inline ALGH_API void AlgComputeBB (const AlgVector& v, AlgVector& bbmin, AlgVector& bbmax)
{
  AlgComputeBB(v.x, v.y, v.z, bbmin, bbmax);
}

#endif

