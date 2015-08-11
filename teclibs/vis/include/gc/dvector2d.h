#ifndef GC_DVECTOR2D_H
#define GC_DVECTOR2D_H

#include "defines.h"

// 2-dimensional vector of double-precision floating point values
// Intended to be used as a basic type, not an object as such

class GC_API gcDVector2D
{
public:

  // Public Internal Data

  double x;
  double y;

  // Constructors and Destructor

  gcDVector2D (void)                       : x(0.0),       y(0.0)       {}
  gcDVector2D (double newAll)              : x(newAll),    y(newAll)    {}
  gcDVector2D (double newX, double   newY) : x(newX),      y(newY)      {}
  gcDVector2D (const double       *vec2dv) : x(vec2dv[0]), y(vec2dv[1]) {}
  gcDVector2D (const gcDVector2D  &vec2D)  : x(vec2D.x),   y(vec2D.y)   {}

  virtual ~gcDVector2D (void) {}

  // Cast to double*

  operator       double* (void) const {return (      double*) &x;}
  operator const double* (void) const {return (const double*) &x;}

  // Auxiliary Setters (getters are not needed since members are public)

  void Set (const double *new2dv)     {x=new2dv[0]; y=new2dv[1];}
  void Set (double newX, double newY) {x=newX;      y=newY;}

  // Unary operators

  gcDVector2D operator - (void) const {return gcDVector2D(-x, -y);}
  gcDVector2D operator + (void) const {return (*this);}

  // Assignment

  gcDVector2D& operator = (const gcDVector2D& vec2D) {x = vec2D.x; y = vec2D.y; return *this;}

  // Comparison

  bool operator == (const gcDVector2D &v2) const {return (x==v2.x && y==v2.y);}
  bool operator != (const gcDVector2D &v2) const {return (x!=v2.x || y!=v2.y);}

  // Basic vector dot operations and scalar multiplication and division

  gcDVector2D operator + (const gcDVector2D &v2) const {return gcDVector2D(x+v2.x, y+v2.y);}
  gcDVector2D operator - (const gcDVector2D &v2) const {return gcDVector2D(x-v2.x, y-v2.y);}
  gcDVector2D operator * (const gcDVector2D &v2) const {return gcDVector2D(x*v2.x, y*v2.y);}
  gcDVector2D operator / (const gcDVector2D &v2) const
  {
    if (v2.x == 0.0 || v2.y == 0.0) return gcDVector2D(x, y);
    else                            return gcDVector2D(x/v2.x, y/v2.y);
  }

  friend gcDVector2D operator * (double Sc, const gcDVector2D &v2) {return v2*Sc;}

  gcDVector2D operator * (double Sc) const {return gcDVector2D(x*Sc, y*Sc);}
  gcDVector2D operator / (double Sc) const
  {
    if (Sc == 0.0 || Sc == 1.0) return gcDVector2D(x, y);
    else  {double ISc = 1.0/Sc; return gcDVector2D(x*ISc, y*ISc);}
  }

  // Basic self-assignment vector dot operations

  void operator += (const gcDVector2D &v2)   {x+=v2.x; y+=v2.y;}
  void operator -= (const gcDVector2D &v2)   {x-=v2.x; y-=v2.y;}
  void operator *= (const gcDVector2D &v2)   {x*=v2.x; y*=v2.y;}
  void operator /= (const gcDVector2D &v2)
  {
    if (v2.x == 0.0 || v2.y == 0.0) return;
    else {x/=v2.x; y/=v2.y;}
  }

  void operator *= (double Sc) {x*=Sc; y*=Sc;}
  void operator /= (double Sc)
  {
    if (Sc == 0.0 || Sc == 1.0) return;
    else {double ISc = 1.0/Sc; x*=ISc; y*=ISc;}
  }

  // Vector Product Operators

  double operator ^ (const gcDVector2D &v2) const {return Dot(v2);}
  double operator % (const gcDVector2D &v2) const {return Cross(v2);}

  // Vector methods
  // - vector parameters whose name begin with "unit" must be normalized
  // - all angles are in radians

  double       Norm       (void) const;
  double       SqrNorm    (void) const;

  void         Normalize  (void);
  gcDVector2D  Normalized (void) const;

  double       Dot        (const gcDVector2D &v2) const;
  double       Cross      (const gcDVector2D &v2) const; // z coordinate of cross product

  double       Angle      (const gcDVector2D &v2) const;

  void         Project    (const gcDVector2D &unitV2);
  gcDVector2D  Projected  (const gcDVector2D &unitV2) const;

  void         OProject   (const gcDVector2D &unitV2);
  gcDVector2D  OProjected (const gcDVector2D &unitV2) const;

  void         Reflect    (const gcDVector2D &unitV2);
  gcDVector2D  Reflected  (const gcDVector2D &unitV2) const;

  void         RotateZ    (double angleRad);
  gcDVector2D  RotatedZ   (double angleRad) const;

  void         RotateZ    (double angleRad, const gcDVector2D &refPoint);
  gcDVector2D  RotatedZ   (double angleRad, const gcDVector2D &refPoint) const;

  gcDVector2D  Lerp       (const gcDVector2D &v2, double weight2) const; // Linear Interpolation

};

#endif // GC_DVECTOR2D_H
