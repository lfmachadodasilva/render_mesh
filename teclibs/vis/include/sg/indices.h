// Indices classes
// fabraham@tecgraf.puc-rio.br
// Mar 2005

#ifndef SG_INDICES_H
#define SG_INDICES_H

#include <ugl/indices.h>
#include "refcount.h"

/**
 * SGIndices Classes.
 *
 * This class extends the UGLIndices classes, providing reference counting,
 * so a single index array can be shared between multiple shapes.
 */
class SG_API SGLineSet : public SGRefCount, public UGLLineSet
{
public:
  static SGLineSet* CreateCpu (int nl, unsigned int maxVerts, int accessHint=-1, int timeHint=-1)
  {
    SGLineSet* newSet = new SGLineSet(maxVerts, accessHint, timeHint);
    newSet->ResizeElementsCpu(nl, true);
    return newSet;
  }
  static SGLineSet* CreateGpu (int nl, unsigned int maxVerts, int accessHint=-1, int timeHint=-1)
  {
    SGLineSet* newSet = new SGLineSet(maxVerts, accessHint, timeHint);
    newSet->ResizeElementsGpu(nl, true);
    return newSet;
  }
  SGLineSet (unsigned int maxVerts, int accessHint=-1, int timeHint=-1) : SGRefCount(), UGLLineSet(maxVerts,accessHint,timeHint)
  {
  }
  SGLineSet (const SGLineSet *src) : SGRefCount(), UGLLineSet(src)
  {
  }
};

class SG_API SGLineStrip : public SGRefCount, public UGLLineStrip
{
public:
  static SGLineStrip* CreateCpu (int nl, unsigned int maxVerts, int accessHint=-1, int timeHint=-1)
  {
    SGLineStrip* newStrip = new SGLineStrip(maxVerts, accessHint, timeHint);
    newStrip->ResizeElementsCpu(nl, true);
    return newStrip;
  }
  static SGLineStrip* CreateGpu (int nl, unsigned int maxVerts, int accessHint=-1, int timeHint=-1)
  {
    SGLineStrip* newStrip = new SGLineStrip(maxVerts, accessHint, timeHint);
    newStrip->ResizeElementsGpu(nl, true);
    return newStrip;
  }
  SGLineStrip (unsigned int maxVerts, int accessHint=-1, int timeHint=-1) : SGRefCount(), UGLLineStrip(maxVerts,accessHint,timeHint)
  {
  }
  SGLineStrip (const UGLLineStrip *src) : SGRefCount(), UGLLineStrip(src)
  {
  }
};

class SG_API SGTriangleSet : public SGRefCount, public UGLTriangleSet
{
public:
  static SGTriangleSet* CreateCpu (int nt, unsigned int maxVerts, int accessHint=-1, int timeHint=-1)
  {
    SGTriangleSet* newSet = new SGTriangleSet(maxVerts, accessHint, timeHint);
    newSet->ResizeElementsCpu(nt, true);
    return newSet;
  }
  static SGTriangleSet* CreateGpu (int nt, unsigned int maxVerts, int accessHint=-1, int timeHint=-1)
  {
    SGTriangleSet* newSet = new SGTriangleSet(maxVerts, accessHint, timeHint);
    newSet->ResizeElementsGpu(nt, true);
    return newSet;
  }
  SGTriangleSet (unsigned int maxVerts, int accessHint=-1, int timeHint=-1) : SGRefCount(), UGLTriangleSet(maxVerts,accessHint,timeHint)
  {
  }
  SGTriangleSet (const UGLTriangleSet *src) : SGRefCount(), UGLTriangleSet(src)
  {
  }
};

class SG_API SGTriangleStrip : public SGRefCount, public UGLTriangleStrip
{
public:
  static SGTriangleStrip* CreateCpu (int nt, unsigned int maxVerts, int accessHint=-1, int timeHint=-1)
  {
    SGTriangleStrip* newStrip = new SGTriangleStrip(maxVerts, accessHint, timeHint);
    newStrip->ResizeElementsCpu(nt, true);
    return newStrip;
  }
  static SGTriangleStrip* CreateGpu (int nt, unsigned int maxVerts, int accessHint=-1, int timeHint=-1)
  {
    SGTriangleStrip* newStrip = new SGTriangleStrip(maxVerts, accessHint, timeHint);
    newStrip->ResizeElementsGpu(nt, true);
    return newStrip;
  }
  SGTriangleStrip (unsigned int maxVerts, int accessHint=-1, int timeHint=-1) : SGRefCount(), UGLTriangleStrip(maxVerts,accessHint,timeHint)
  {
  }
  SGTriangleStrip (const UGLTriangleStrip *src) : SGRefCount(), UGLTriangleStrip(src)
  {
  }
};

class SG_API SGQuadSet : public SGRefCount, public UGLQuadSet
{
public:
  static SGQuadSet* CreateCpu (int nq, unsigned int maxVerts, int accessHint=-1, int timeHint=-1)
  {
    SGQuadSet* newSet = new SGQuadSet(maxVerts, accessHint, timeHint);
    newSet->ResizeElementsCpu(nq, true);
    return newSet;
  }
  static SGQuadSet* CreateGpu (int nq, unsigned int maxVerts, int accessHint=-1, int timeHint=-1)
  {
    SGQuadSet* newSet = new SGQuadSet(maxVerts, accessHint, timeHint);
    newSet->ResizeElementsGpu(nq, true);
    return newSet;
  }
  SGQuadSet (unsigned int maxVerts, int accessHint=-1, int timeHint=-1) : SGRefCount(), UGLQuadSet(maxVerts,accessHint,timeHint)
  {
  }
  SGQuadSet (const UGLQuadSet *src) : SGRefCount(), UGLQuadSet(src)
  {
  }
};

class SG_API SGQuadStrip : public SGRefCount, public UGLQuadStrip
{
public:
  static SGQuadStrip* CreateCpu (int nq, unsigned int maxVerts, int accessHint=-1, int timeHint=-1)
  {
    SGQuadStrip* newStrip = new SGQuadStrip(maxVerts, accessHint, timeHint);
    newStrip->ResizeElementsCpu(nq, true);
    return newStrip;
  }
  static SGQuadStrip* CreateGpu (int nq, unsigned int maxVerts, int accessHint=-1, int timeHint=-1)
  {
    SGQuadStrip* newStrip = new SGQuadStrip(maxVerts, accessHint, timeHint);
    newStrip->ResizeElementsGpu(nq, true);
    return newStrip;
  }
  SGQuadStrip (unsigned int maxVerts, int accessHint=-1, int timeHint=-1) : SGRefCount(), UGLQuadStrip(maxVerts,accessHint,timeHint)
  {
  }
  SGQuadStrip (const UGLQuadStrip *src) : SGRefCount(), UGLQuadStrip(src)
  {
  }
};

class SG_API SGGridStrip : public SGTriangleStrip
{
public:
  SGGridStrip (int m, int n, int accessHint=-1, int timeHint=-1) : SGTriangleStrip(m*n, accessHint, timeHint)
  {
    ResizeCpu(1 + (m-1) + 2*(m-2) + 2*(n-1)*(m-1), true);
    UGLGridStrip::BuildGridStrip(this,m,n);
  }
};

#endif
