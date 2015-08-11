// Matrix stack class
// fabraham@tecgraf.puc-rio.br
// Sep 2003

#ifndef ALG_MATRIX_STACK_H
#define ALG_MATRIX_STACK_H

#include "stack.h"
#include <ds/stack.h>

/**
 * This class implements a matrix stack on the CPU, just like the OpenGL matrix stacks.
 * It defines methods for:
 * - accumulating/pushing/popping transformations.
 * - obtaining the stack top
 */
class ALGH_API AlgMatrixStack : public AlgStack, private DsStack<AlgMatrix>
{
public:
  AlgMatrixStack () : DsStack<AlgMatrix>()
  {
    Clear();
  }
  virtual ~AlgMatrixStack () {}
  int Size () const
  {
    return DsStack<AlgMatrix>::Size();
  }
  virtual AlgMatrix GetTop ()
  {
    return Top();
  }
  void Clear ()
  {
    DsStack<AlgMatrix>::Clear();
    PushConst(AlgMatrix::GetIdentity());
  }
  virtual void Push ()
  {
    Duplicate();
  }
  virtual void Pop ()
  {
    DsStack<AlgMatrix>::Pop();
  }
  virtual void Identity ()
  {
    Top().Identity();
  }
  virtual void LoadMatrix (const AlgMatrix& m)
  {
    Top() = m;
  }
  virtual void Translate (float x, float y, float z)
  {
    Top().Translate(x,y,z);
  }
  virtual void Translate (const AlgVector& v)
  {
    Top().Translate(v);
  }
  virtual void Scale (float x, float y, float z)
  {
    Top().Scale(x,y,z);
  }
  virtual void Scale (const AlgVector& v)
  {
    Top().Scale(v);
  }
  virtual void Scale (float x, float y, float z, float rx, float ry, float rz)
  {
    Top().Scale(x,y,z,rx,ry,rz);
  }
  virtual void Scale (const AlgVector& v, const AlgVector& r)
  {
    Top().Scale(v,r);
  }
  virtual void Rotate (float a, float x, float y, float z)
  {
    Top().Rotate(a,x,y,z);
  }
  virtual void Rotate (float a, const AlgVector& p)
  {
    Top().Rotate(a,p);
  }
  virtual void Rotate (const AlgQuatern& q)
  {
    Top().Rotate(q);
  }
  virtual void Rotate (float a, float x, float y, float z, float rx, float ry, float rz)
  {
    Top().Rotate(a,x,y,z,rx,ry,rz);
  }
  virtual void Rotate (float a, const AlgVector& p, const AlgVector& r)
  {
    Top().Rotate(a,p,r);
  }
  virtual void Rotate (const AlgQuatern& q, const AlgVector& r)
  {
    Top().Rotate(q,r);
  }
  virtual void LookAt (const AlgVector& pos, const AlgVector& target, const AlgVector& up)
  {
    Top().LookAt(pos,target,up);
  }
  virtual void Ortho (float pleft, float pright, float pbottom, float ptop, float pnear, float pfar)
  {
    Top().Ortho(pleft,pright,pbottom,ptop,pnear,pfar);
  }
  virtual void Frustum (float pleft, float pright, float pbottom, float ptop, float pnear, float pfar)
  {
    Top().Frustum(pleft,pright,pbottom,ptop,pnear,pfar);
  }
  virtual void Perspective (float fovy, float aspect, float znear, float zfar)
  {
    Top().Perspective(fovy,aspect,znear,zfar);
  }
  virtual void Accum (const AlgMatrix& m)
  {
    Top().Accum(m);
  }
  virtual void PreAccum (const AlgMatrix& m)
  {
    Top().PreAccum(m);
  }
};

#endif
