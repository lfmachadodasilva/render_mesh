// Horizontal Plane class
// fabraham@tecgraf.puc-rio.br
// Jan 2003

#ifndef SG_HORPLANE_H
#define SG_HORPLANE_H

#include <sg/shape.h>

class SG_API SGHorizontalPlane : public SGShape
{
  float m_dx, m_dz;
public:
  static const char* CLASSNAME () { return "HorizontalPlane"; }
  virtual const char* ClassName () const { return CLASSNAME(); }

  SGHorizontalPlane (float dx, float dz);
  virtual ~SGHorizontalPlane ();

  virtual void SetSize (float dx, float dz);

  virtual int GetLineCount ();
  virtual int GetTriangleCount ();
  virtual void Draw ();
  virtual void Write (UtlWriter* writer);
};

#endif
