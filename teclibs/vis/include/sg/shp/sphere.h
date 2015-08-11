// Sphere class
// celes@tecgraf.puc-rio.br
// Jul 2002

#ifndef SG_SPHERE_H
#define SG_SPHERE_H

#include "mesh.h"

class SG_API SGSphere : public SGMesh
{
protected:
  float m_radius;
  int   m_slices, m_stacks;
public:
  static const char* CLASSNAME () { return "Sphere"; }
  virtual const char* ClassName () const { return CLASSNAME(); }

  SGSphere (float radius, int slices=16, int stacks=16);
  virtual ~SGSphere ();

  virtual void SetRadius(float r);

  virtual void Write (UtlWriter* writer);
};

#endif
