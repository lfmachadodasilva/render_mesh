// GL stack class
// fabraham@tecgraf.puc-rio.br
// Sep 2003

#ifndef ALG_GL_STACK_H
#define ALG_GL_STACK_H

#include "matrixstack.h"

#include <GL/glew.h>

/**
 * This class interfaces for the OpenGL matrix stack.
 * It defines methods for:
 * - setting the base matrix (eg. the projection+view matrix), so that identity() takes to this space.
 * - accumulating/pushing/popping transformations.
 * - obtaining the stack top
 */
class ALGH_API AlgGLStack : public AlgStack
{
public:
  AlgGLStack () 
  : m_which_stack(GL_MODELVIEW)
  , m_cpu_mode(false)
  {
    Init();
  }
  AlgGLStack (int whichstack, bool cpumode = false) 
  : m_which_stack(whichstack)
  , m_cpu_mode(cpumode)
  {
    Init();
  }
  virtual ~AlgGLStack ()
  {
    if (m_identity)
      delete m_identity;
  }
  void SetIdentity (AlgMatrix* m)
  {
    if (m != NULL)
    {
      if (m_identity != NULL)
        *m_identity = *m;
      else
        m_identity = new AlgMatrix(*m);
    }
    else if (m_identity != NULL)
    {
      delete m_identity;
      m_identity = 0;
    }
  }
  void SetIdentity (AlgMatrix m)
  {
    SetIdentity(&m);
  }
  void SetIdentity (float* m)
  {
    if (m != NULL)
    {
      if (m_identity != NULL)
        *m_identity = m;
      else
        m_identity = new AlgMatrix(m);
    }
    else if (m_identity != NULL)
    {
      delete m_identity;
      m_identity = 0;
    }
  }
  AlgMatrix* GetIdentity() const
  {
    return m_identity;
  }
  virtual AlgMatrix GetTop ()
  {
    if (m_gl_push_count < 0)
      InitPushCount();
    float m[16];
    glGetFloatv(m_which_stack_get,m);
    return AlgMatrix(m);
  }
  virtual void Push ()
  {
    if (m_gl_push_count < 0)
      InitPushCount();
#ifdef _DEBUG
    if (!m_cpu_mode
        && m_gl_real_push_limit != m_gl_push_limit 
        && m_gl_push_count == 0)
    {
      for (int i=0; i<m_gl_real_push_limit-m_gl_push_limit; i++)
        glPushMatrix();
    }
#endif
    if (m_gl_push_count >= m_gl_push_limit)
    {
      // a new stack push would overflow: pushing in an own stack
      float m[16];
      glGetFloatv(m_which_stack_get,m);
      m_matrix_stack.LoadMatrix(AlgMatrix(m));
      m_matrix_stack.Push();
    }
    else
    {
      glPushMatrix();
      ++m_gl_push_count;
    }
  }
  virtual void Pop ()
  {
    if (m_matrix_stack.Size() > 1)
    {
      m_matrix_stack.Pop();
      glLoadMatrixf(m_matrix_stack.GetTop());
    }
    else
    {
      glPopMatrix();
      --m_gl_push_count;
    }
#ifdef _DEBUG
    if (!m_cpu_mode
        && m_gl_real_push_limit != m_gl_push_limit 
        && m_gl_push_count == 0)
    {
      for (int i=0; i<m_gl_real_push_limit-m_gl_push_limit; i++)
        glPopMatrix();
    }
#endif
  }
  virtual void Identity ()
  {
    if (GetIdentity())
      glLoadMatrixf(GetIdentity()->GetMatrix());
    else
      glLoadIdentity();
  }
  virtual void LoadMatrix (const AlgMatrix& m)
  {
    if (GetIdentity())
    {
      glLoadMatrixf(GetIdentity()->GetMatrix());
      glMultMatrixf(m);
    }
    else
      glLoadMatrixf(m);
  }
  virtual void Translate (float x, float y, float z)
  {
    glTranslatef(x,y,z);
  }
  virtual void Translate (const AlgVector& v)
  {
    glTranslatef(v.x,v.y,v.z);
  }
  virtual void Scale (float x, float y, float z)
  {
    glScalef(x,y,z);
  }
  virtual void Scale (const AlgVector& v)
  {
    glScalef(v.x,v.y,v.z);
  }
  virtual void Scale (float x,float y,float z,float rx,float ry,float rz)
  {
    glTranslatef(rx,ry,rz);
    glScalef(x,y,z);
    glTranslatef(-rx,-ry,-rz);
  }
  virtual void Scale (const AlgVector& v, const AlgVector& r)
  {
    glTranslatef(r.x,r.y,r.z);
    glScalef(v.x,v.y,v.z);
    glTranslatef(-r.x,-r.y,-r.z);
  }
  virtual void Rotate (float a, float x, float y, float z)
  {
    glRotatef(a,x,y,z);
  }
  virtual void Rotate (float a, const AlgVector& p)
  {
    glRotatef(a,p.x,p.y,p.z);
  }
  virtual void Rotate (const AlgQuatern& q)
  {
    float x,y,z;
    q.GetAxis(&x,&y,&z);
    glRotatef(q.GetAngle(),x,y,z);
  }
  virtual void Rotate (float a,float x,float y,float z,float rx,float ry,float rz)
  {
    glTranslatef(rx,ry,rz);
    glRotatef(a,x,y,z);
    glTranslatef(-rx,-ry,-rz);
  }
  virtual void Rotate (float a, const AlgVector& p, const AlgVector& r)
  {
    glTranslatef(r.x,r.y,r.z);
    glRotatef(a,p.x,p.y,p.z);
    glTranslatef(-r.x,-r.y,-r.z);
  }
  virtual void Rotate (const AlgQuatern& q, const AlgVector& r)
  {
    float x,y,z;
    q.GetAxis(&x,&y,&z);
    glTranslatef(r.x,r.y,r.z);
    glRotatef(q.GetAngle(),x,y,z);
    glTranslatef(-r.x,-r.y,-r.z);
  }
  virtual void LookAt (const AlgVector& pos, const AlgVector& target, const AlgVector& up)
  {
    gluLookAt(pos.x,pos.y,pos.z,target.x,target.y,target.z,up.x,up.y,up.z);
  }
  virtual void Ortho (float pleft, float pright, float pbottom, float ptop, float pnear, float pfar)
  {
    glOrtho(pleft,pright,pbottom,ptop,pnear,pfar);
  }
  virtual void Frustum (float pleft, float pright, float pbottom, float ptop, float pnear, float pfar)
  {
    glFrustum(pleft,pright,pbottom,ptop,pnear,pfar);
  }
  virtual void Perspective (float fovy, float aspect, float znear, float zfar)
  {
    gluPerspective(fovy,aspect,znear,zfar);
  }
  virtual void Accum (const AlgMatrix& m)
  {
    glMultMatrixf(m);
  }
  virtual void PreAccum (const AlgMatrix& m) // TODO: untested
  {
    AlgMatrix top = GetTop();
    top.PreAccum(m);
    LoadMatrix(top);
  }
private:
  void Init ()
  {
    m_identity = NULL;
    m_gl_push_count = -1;
  }
  void InitPushCount()
  {
    m_gl_push_count = 0;
    switch(m_which_stack) {
      case GL_MODELVIEW:  glGetIntegerv(GL_MAX_MODELVIEW_STACK_DEPTH, &m_gl_push_limit); m_which_stack_get = GL_MODELVIEW_MATRIX;  break;
      case GL_PROJECTION: glGetIntegerv(GL_MAX_PROJECTION_STACK_DEPTH,&m_gl_push_limit); m_which_stack_get = GL_PROJECTION_MATRIX; break;
      case GL_TEXTURE:    glGetIntegerv(GL_MAX_TEXTURE_STACK_DEPTH,   &m_gl_push_limit); m_which_stack_get = GL_TEXTURE_MATRIX;    break;
    }
    m_gl_push_limit--;
    if (m_cpu_mode)
      m_gl_real_push_limit = m_gl_push_limit = 0;
    else {
      m_gl_real_push_limit = m_gl_push_limit;
#ifdef _DEBUG
      // reverting to the lowest common denominator of currently used video cards:
      switch (m_which_stack) {
        case GL_PROJECTION: m_gl_push_limit = 1;  break;
        case GL_MODELVIEW:  m_gl_push_limit = 31; break;
        // TODO: add GL_TEXTURE limit
      }
#endif
    }
  }
  AlgMatrix* m_identity;
  AlgMatrixStack m_matrix_stack;
  int m_which_stack;
  int m_which_stack_get;
  GLint m_gl_push_limit;
  GLint m_gl_real_push_limit;
  GLint m_gl_push_count;
  bool m_cpu_mode;
};

#endif
