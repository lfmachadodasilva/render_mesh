//* quatern.h
// Represents quaternion.
// celes@tecgraf.puc-rio.br
// hermann@tecgraf.puc-rio.br
// Nov 2004

#ifndef VIS_QUATERN_H
#define VIS_QUATERN_H

#include "defines.h"
#include "vector.h"

class ALG_API AlgQuatern
{
private:
   float m_w;
   AlgVector m_p;

public:

   // Constructors and destructors
   AlgQuatern ()
      : m_w(1.0f),m_p(0.0f,0.0f,0.0f)
   {
   }

   AlgQuatern (float angle, float x, float y, float z)
   {
      Set(angle,x,y,z);
   }

   AlgQuatern (float angle, const AlgVector& axis)
   {
      Set(angle,axis);
   }

   AlgQuatern (const AlgVector &u, const AlgVector &v, const AlgVector &w)
   {
      Set(u, v, w);
   }

   ~AlgQuatern () 
   { 
   }

   // Set Values
   void Set (float angle, float x, float y, float z)
   {
      float a = angle*ALG_PI/180.0f/2;
      float s = (float)sin(a);
      m_w = (float)cos(a);
      m_p.Set(x,y,z);
      float sqrlen = m_p.SqrLength();
      if (sqrlen > 0.0f)
        m_p /= (float)sqrt(sqrlen);
      m_p *= s;
   }

   void Set(float angle, const AlgVector& axis)
   {
      Set(angle,axis.x,axis.y,axis.z);
   }

   void Set(const AlgVector &u, const AlgVector &v, const AlgVector &w);

   void SetRaw(float w, float x, float y, float z)
   {
      m_w = w;
      m_p.x = x;
      m_p.y = y;
      m_p.z = z;
   };

   void SetRaw(float w, const AlgVector &v)
   {
      m_w = w;
      m_p = v;
   }

   // Get Values
   float GetAngle () const
   {
      return (float)(2*acos(m_w)*180.0/ALG_PI);
   }

   void GetAxis (float* x, float* y, float* z) const
   {
      *x = m_p.x; *y = m_p.y; *z = m_p.z;
   }

   const AlgVector& GetAxis () const
   {
      return m_p;
   }

   void Get(AlgVector *u, AlgVector *v, AlgVector *w)
   {
      float s = 2/Norm();
      u->x = 1-s*(m_p.y*m_p.y+m_p.z*m_p.z); v->x =   s*(m_p.x*m_p.y-m_w*m_p.z);   w->x =   s*(m_p.x*m_p.z+m_w*m_p.y);
      u->y =   s*(m_p.x*m_p.y+m_w*m_p.z);   v->y = 1-s*(m_p.x*m_p.x+m_p.z*m_p.z); w->y =   s*(m_p.y*m_p.z-m_w*m_p.x);
      u->z =   s*(m_p.x*m_p.z-m_w*m_p.y);   v->z =   s*(m_p.y*m_p.z+m_w*m_p.x);   w->z = 1-s*(m_p.x*m_p.x+m_p.y*m_p.y);
   }

   void GetRaw(float *w, float *x, float *y, float *z) const
   {
      *w = m_w;
      *x = m_p.x;
      *y = m_p.y;
      *z = m_p.z;
   };

   void GetRaw(float *w, AlgVector *v)
   {
      *w = m_w;
      *v = m_p;
   }

   // Print
   void Print(const char *label=0)
   {
     printf("%s %g %g %g %g\n", label?label:"", m_w, m_p.x, m_p.y, m_p.z);
   }

   // Basic operations
   void Identity()
   {
      m_w = 1;
      m_p.Set(0,0,0);
   }

   void Add(const AlgQuatern& q)
   {
      m_w   += q.m_w;
      m_p.x += q.m_p.x;
      m_p.y += q.m_p.y;
      m_p.z += q.m_p.z;
   }

   void Sub(const AlgQuatern& q)
   {
      m_w   -= q.m_w;
      m_p.x -= q.m_p.x;
      m_p.y -= q.m_p.y;
      m_p.z -= q.m_p.z;
   }

   void Mult(const AlgQuatern& q);
   
   void Mult(float v)
   {
      m_w   *= v;
      m_p.x *= v;
      m_p.y *= v;
      m_p.z *= v;
   }

   void Div(float v)
   {
      Mult(1/v);
   }

   void Conjugate()
   {
      m_p.x = -m_p.x;
      m_p.y = -m_p.y;
      m_p.z = -m_p.z;
   }

   float Norm() const
   {
      return (float)sqrt(m_w*m_w + m_p.x*m_p.x + m_p.y*m_p.y + m_p.z*m_p.z);
   }

   void Normalize()
   {
      float norm = Norm();
      if (norm > 0)
        Div(norm);
   }

   void Inverse()
   {
      float t = Norm();
      if (t < 2e-5)
      {
        m_p.x = 0;
        m_p.y = 0;
        m_p.z = 0;
        m_w = 1;
      }
      else
      {
        Div(t);
        Conjugate();
      }
   }

  bool IsEqual(const AlgQuatern &q) const
  {
    if (m_w == q.m_w && m_p.x == q.m_p.x && m_p.y == q.m_p.y && m_p.z == q.m_p.z)
      return true;
    return false;
  }

   float Dot(const AlgQuatern& q) const
   {
      return m_w*q.m_w + m_p.x*q.m_p.x + m_p.y*q.m_p.y + m_p.z*q.m_p.z;
   }

   bool Log(); // Unit Quaternion operation
   
   void Exp() // Quaternion q=(0, Theta*v) operation
   {
     float t = (float)(sqrt(m_p.x*m_p.x + m_p.y*m_p.y + m_p.z*m_p.z));
     float tmp = (float)(exp(m_w)*sin(t)/t);
     m_w = (float)(cos(t)*exp(m_w));
     if (t > 2e-5)
     {
       m_p.x *= tmp;
       m_p.y *= tmp;
       m_p.z *= tmp;
     }
     else
     {
       m_p.x = m_p.y = m_p.z = 0;
     }
   }

   bool Pow(float v);

   static AlgQuatern Add(const AlgQuatern &q0, const AlgQuatern &q1)
   {
      AlgQuatern q = q0;
      q.Add(q1);
      return q;
   }

   static AlgQuatern Sub(const AlgQuatern &q0, const AlgQuatern &q1)
   {
      AlgQuatern q = q0;
      q.Sub(q1);
      return q;
   }

   static AlgQuatern Mult(const AlgQuatern &q0, const AlgQuatern &q1)
   {
      AlgQuatern q = q0;
      q.Mult(q1);
      return q;
   }

   static AlgQuatern Mult(const AlgQuatern &q0, float v)
   {
      AlgQuatern q = q0;
      q.Mult(v);
      return q;
   }

   static AlgQuatern Div(const AlgQuatern &q0, float v)
   {
      AlgQuatern q = q0;
      q.Div(v);
      return q;
   }

   static AlgQuatern Conjugate(const AlgQuatern &q)
   {
      AlgQuatern qt = q;
      qt.Conjugate();
      return qt;
   }

   static  AlgQuatern Inverse(const AlgQuatern &q)
   {
      AlgQuatern qt = q;
      qt.Inverse();
      return qt;
   }

   static AlgQuatern Normalize(const AlgQuatern &q)
   {
      AlgQuatern qt = q;
      qt.Normalize();
      return qt;
   }

   static AlgQuatern Log(const AlgQuatern &q)
   {
      AlgQuatern qt = q;
      qt.Log();
      //if(qt.Log())
      //   qt.Set(0, 0,0,0);
      return q;
   }

   static AlgQuatern Exp(const AlgQuatern &q)
   {
      AlgQuatern qt = q;
      qt.Exp();
      return qt;
   }

   static AlgQuatern Pow(const AlgQuatern &q, float v)
   {
      AlgQuatern qt = q;
      qt.Pow(v);
      return qt;
   }

   // Interpolation Functions
   // Linear
   static AlgQuatern Lerp(const AlgQuatern& q0, const AlgQuatern& q1, float h)
   {
      return AlgQuatern::Normalize(AlgQuatern::Add(AlgQuatern::Mult(q0,1-h),AlgQuatern::Mult(q1,h)));
   }

   // Spherical
   static AlgQuatern Slerp(const AlgQuatern& q0, const AlgQuatern& q1, float h);

   // Cubic
   static AlgQuatern Squad(const AlgQuatern& q0, const AlgQuatern& q1, const AlgQuatern& q2, const AlgQuatern& q3, float h);
};
#endif
