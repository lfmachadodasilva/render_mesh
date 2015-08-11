// Cube class
// celes@tecgraf.puc-rio.br
// Jul 2002

#ifndef SG_CUBE_H
#define SG_CUBE_H

#include <sg/shape.h>

/**
 * SGCube Class.
 * This shape will draw a parallelepiped of dimensions dx dy dz.
 */
class SG_API SGCube : public SGShape
{
  float m_dx, m_dy, m_dz;
public:
  static const char* CLASSNAME () { return "Cube"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
  /**
   * Constructor
   */
  SGCube (float dx, float dy, float dz);
  /**
   * Destructor
   */
  virtual ~SGCube ();
  virtual int GetLineCount ();
  virtual int GetTriangleCount ();
  virtual void Draw ();
  virtual void Write (UtlWriter* writer);
};

#endif
