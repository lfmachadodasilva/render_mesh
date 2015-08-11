//* planenavig.h
// fabraham@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Apr 2005

#ifndef VGL_PLANE_NAVIG_H
#define VGL_PLANE_NAVIG_H

#include "navig.h"

class VglViewSurface;
class VglCamera;

// TODO: enable navigation plane configuration. currently, using a=0,b=1,c=0,d=0
class VGL_API VglPlaneNavigHandler : public VglNavigHandler
{
  float m_mindistance;
  bool m_constraindistance;
protected:
  virtual void Translate (float velx, float vely, float velz, double displacement);
public:
  static const char* CLASSNAME () { return "PlaneNavigHandler"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
  VglPlaneNavigHandler (VglViewSurface* surface, float maxvel=0.2f, float accel=1.0f);
  virtual ~VglPlaneNavigHandler ();
  void SetMinDistance (float d)
  {
    m_mindistance = d;
    m_constraindistance = true;
  }
  void UnsetMinDistance ()
  {
    m_constraindistance = false;
  }
};

#endif
