// Matrix stack interface
// fabraham@tecgraf.puc-rio.br
// Sep 2003

#ifndef ALG_STACK_H
#define ALG_STACK_H

#include "defines.h"
#include "matrix.h"
#include "vector.h"
#include "quatern.h"

class ALGH_API AlgStack
{
public:
  virtual ~AlgStack ()
  {
  }
  virtual AlgMatrix GetTop () = 0;
  virtual void Push () = 0;
  virtual void Pop () = 0;
  virtual void Identity () = 0;
  virtual void LoadMatrix (const AlgMatrix& m) = 0;
  virtual void Translate (float x, float y, float z) = 0;
  virtual void Translate (const AlgVector& v) = 0;
  virtual void Scale (float x, float y, float z) = 0;
  virtual void Scale (const AlgVector& v) = 0;
  virtual void Scale (float x,float y,float z,float rx,float ry,float rz) = 0;
  virtual void Scale (const AlgVector& v, const AlgVector& r) = 0;
  virtual void Rotate (float a, float x, float y, float z) = 0;
  virtual void Rotate (float a, const AlgVector& p) = 0;
  virtual void Rotate (const AlgQuatern& q) = 0;
  virtual void Rotate (float a,float x,float y,float z,float rx,float ry,float rz) = 0;
  virtual void Rotate (float a, const AlgVector& p, const AlgVector& r) = 0;
  virtual void Rotate (const AlgQuatern& q, const AlgVector& r) = 0;
  virtual void LookAt (const AlgVector& pos, const AlgVector& target, const AlgVector& up) = 0;
  virtual void Ortho (float pleft, float pright, float pbottom, float ptop, float pnear, float pfar) = 0;
  virtual void Frustum (float pleft, float pright, float pbottom, float ptop, float pnear, float pfar) = 0;
  virtual void Perspective (float fovy, float aspect, float znear, float zfar) = 0;
  virtual void Accum (const AlgMatrix& m) = 0;
  virtual void PreAccum (const AlgMatrix& m) = 0;
};

#endif
