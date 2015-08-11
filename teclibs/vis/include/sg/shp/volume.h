// Volume class
// rodesp@tecgraf.puc-rio.br
// fabraham@tecgraf.puc-rio.br
// Aug 2003

#ifndef SG_VOLUME_H
#define SG_VOLUME_H

#include <sg/shape.h>
#include <alg/vector.h>

class SG_API SGVolume : public SGShape
{
  AlgVector m_vertices[8];
  float m_sizex, m_sizey, m_sizez;
  int m_num_planes;
public:
  static const char* CLASSNAME () { return "Volume"; }
  virtual const char* ClassName () const { return CLASSNAME(); }

  SGVolume(float sizex, float sizey, float sizez, int num_planes=64);
  virtual ~SGVolume();

  void SetNumPlanes(int num_planes);

  virtual int GetTriangleCount ();
  virtual int GetLineCount ();
  virtual int GetVertexCount ();
  virtual void GetVertex (int index, float *x, float *y, float *z);
  virtual void Draw ();
  virtual void Write (UtlWriter* writer);
};

#endif
