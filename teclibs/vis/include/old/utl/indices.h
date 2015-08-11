#ifndef UTL_INDICES_H_OLD
#define UTL_INDICES_H_OLD

#include <ugl/indices.h>
#include <utl/defines.h>

class UTL_API UtlLineSet : public UGLLineSet
{
public:
  UtlLineSet (int ns,int nv) : UGLLineSet(ns,nv)
  {
  }
};

class UTL_API UtlLineStrip : public UGLLineStrip
{
public:
  UtlLineStrip (int ns,int nv) : UGLLineStrip(ns,nv)
  {
  }
  UtlLineStrip (const UtlLineStrip *src) : UGLLineStrip(src)
  {
  }
};

class UTL_API UtlTriangleSet : public UGLTriangleSet
{
public:
  UtlTriangleSet (int nt,int nv) : UGLTriangleSet(nt,nv)
  {
  }
  UtlTriangleSet (const UtlTriangleSet *src) : UGLTriangleSet(src)
  {
  }
};

class UTL_API UtlTriangleStrip : public UGLTriangleStrip
{
public:
  UtlTriangleStrip (int nt, int nv) : UGLTriangleStrip(nt,nv)
  {
  }
  UtlTriangleStrip (const UtlTriangleStrip *src) : UGLTriangleStrip(src)
  {
  }
};

class UTL_API UtlQuadSet : public UGLQuadSet
{
public:
  UtlQuadSet (int nq,int nv) : UGLQuadSet(nq,nv)
  {
  }
  UtlQuadSet (const UtlQuadSet *src) : UGLQuadSet(src)
  {
  }
};

class UTL_API UtlGridStrip : public UGLGridStrip
{
public:
  UtlGridStrip (int m, int n) : UGLGridStrip(m,n)
  {
  }
};

#endif
