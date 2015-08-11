// GL and matrix stack class
// fabraham@tecgraf.puc-rio.br
// Sep 2004

#ifndef ALG_GL_MATRIX_STACK_H
#define ALG_GL_MATRIX_STACK_H

#include "glstack.h"
#include "matrixstack.h"

/**
 * This class interfaces for the OpenGL matrix stack, while maintaining a AlgMatrix stack.
 * It defines methods for:
 * - setting the base matrix (eg. the projection+view matrix), so that identity() takes to this space.
 * - accumulating/pushing/popping transformations.
 * - obtaining the stack top
 */
class ALGH_API AlgGLMatrixStack : public AlgGLStack
{
  AlgMatrixStack m_stack;
public:
  AlgGLMatrixStack () : m_stack()
  {
  }
  virtual ~AlgGLMatrixStack ()
  {
  }
  virtual AlgMatrix GetTop ()
  {
    return m_stack.GetTop();
  }
  virtual void Push ()
  {
    m_stack.Push();
    AlgGLStack::Push();
  }
  virtual void Pop ()
  {
    m_stack.Pop();
    AlgGLStack::Pop();
  }
  virtual void Identity ()
  {
    m_stack.Identity();
    AlgGLStack::Identity();
  }
  virtual void LoadMatrix (const AlgMatrix& m)
  {
    m_stack.LoadMatrix(m);
    AlgGLStack::LoadMatrix(m);
  }
  virtual void Translate (float x, float y, float z)
  {
    m_stack.Translate(x,y,z);
    AlgGLStack::Translate(x,y,z);
  }
  virtual void Translate (const AlgVector& v)
  {
    m_stack.Translate(v);
    AlgGLStack::Translate(v);
  }
  virtual void Scale (float x, float y, float z)
  {
    m_stack.Scale(x,y,z);
    AlgGLStack::Scale(x,y,z);
  }
  virtual void Scale (const AlgVector& v)
  {
    m_stack.Scale(v);
    AlgGLStack::Scale(v);
  }
  virtual void Scale (float x,float y,float z,float rx,float ry,float rz)
  {
    m_stack.Scale(x,y,z,rx,ry,rz);
    AlgGLStack::Scale(x,y,z,rx,ry,rz);
  }
  virtual void Scale (const AlgVector& v, const AlgVector& r)
  {
    m_stack.Scale(v,r);
    AlgGLStack::Scale(v,r);
  }
  virtual void Rotate (float a, float x, float y, float z)
  {
    m_stack.Rotate(a,x,y,z);
    AlgGLStack::Rotate(a,x,y,z);
  }
  virtual void Rotate (float a, const AlgVector& p)
  {
    m_stack.Rotate(a,p);
    AlgGLStack::Rotate(a,p);
  }
  virtual void Rotate (const AlgQuatern& q)
  {
    m_stack.Rotate(q);
    AlgGLStack::Rotate(q);
  }
  virtual void Rotate (float a,float x,float y,float z,float rx,float ry,float rz)
  {
    m_stack.Rotate(a,x,y,z,rx,ry,rz);
    AlgGLStack::Rotate(a,x,y,z,rx,ry,rz);
  }
  virtual void Rotate (float a, const AlgVector& p, const AlgVector& r)
  {
    m_stack.Rotate(a,p,r);
    AlgGLStack::Rotate(a,p,r);
  }
  virtual void Rotate (const AlgQuatern& q, const AlgVector& r)
  {
    m_stack.Rotate(q,r);
    AlgGLStack::Rotate(q,r);
  }
  virtual void LookAt (const AlgVector& pos, const AlgVector& target, const AlgVector& up)
  {
    m_stack.LookAt(pos,target,up);
    AlgGLStack::LookAt(pos,target,up);
  }
  virtual void Ortho (float pleft, float pright, float pbottom, float ptop, float pnear, float pfar)
  {
    m_stack.Ortho(pleft,pright,pbottom,ptop,pnear,pfar);
    AlgGLStack::Ortho(pleft,pright,pbottom,ptop,pnear,pfar);
  }
  virtual void Frustum (float pleft, float pright, float pbottom, float ptop, float pnear, float pfar)
  {
    m_stack.Frustum(pleft,pright,pbottom,ptop,pnear,pfar);
    AlgGLStack::Frustum(pleft,pright,pbottom,ptop,pnear,pfar);
  }
  virtual void Perspective (float fovy, float aspect, float znear, float zfar)
  {
    m_stack.Perspective(fovy,aspect,znear,zfar);
    AlgGLStack::Perspective(fovy,aspect,znear,zfar);
  }
  virtual void Accum (const AlgMatrix& m)
  {
    m_stack.Accum(m);
    AlgGLStack::Accum(m);
  }
  virtual void PreAccum (const AlgMatrix& m) // TODO: untested
  {
    m_stack.PreAccum(m);
    AlgGLStack::PreAccum(m);
  }
};

#endif
