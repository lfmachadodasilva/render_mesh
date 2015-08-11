// Triangle class
// djavanes@tecgraf.puc-rio.br
// Jan 2008

#ifndef SG_TRIANGLE_H
#define SG_TRIANGLE_H

#include <sg/shape.h>

class SG_API SGTriangle : public SGShape
{
  float m_nx, m_ny, m_nz, m_x0, m_y0, m_z0, m_x1, m_y1, m_z1, m_x2, m_y2, m_z2;
public:
  static const char* CLASSNAME () { return "Triangle"; }
  virtual const char* ClassName () const { return CLASSNAME(); }

  SGTriangle (float x0, float y0, float z0, float x1, float y1, float z1, float x2, float y2, float z2);
  virtual ~SGTriangle ();

  virtual int GetLineCount ();
  virtual int GetTriangleCount ();
  virtual void Draw ();
  virtual void Write (UtlWriter* writer);
};

#endif
