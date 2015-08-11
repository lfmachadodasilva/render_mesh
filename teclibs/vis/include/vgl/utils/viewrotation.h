#ifndef VGL_VIEWROTATION_H
#define VGL_VIEWROTATION_H

#include "rotation.h"

class VGL_API VglViewRotation : public VglRotation
{
  void RotateY (float angle, const AlgVector &axis)
  {
    m_current.Rotate(angle,axis.x,axis.y,axis.z);
  }
public:
  VglViewRotation ()
  {
  }
  ~VglViewRotation ()
  {
  }
};

#endif

