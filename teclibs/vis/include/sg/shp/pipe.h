// Pipe class
// celes@tecgraf.puc-rio.br
// Sep 2003

#ifndef SG_PIPE_H
#define SG_PIPE_H

#include <alg/vector.h>
#include "mesh.h"

class SG_API SGPipe : public SGMesh
{
public:

  static const char* CLASSNAME () { return "Pipe"; }
  virtual const char* ClassName () const { return CLASSNAME(); }

  // slices = cylinder slices
  SGPipe (float radius, int slices=16);
  virtual ~SGPipe ();
  void SetBuildTexCoords (bool f)
  {
    m_build_tex_coords = f;
  }
  // n = number of vertices
  // v = vertices ( xyzxyzxyzxyzxyz... , size = 3*n)
  void Build (int n, float *v);
  int GetSize () const
  {
    return m_n;
  }
  const float* GetVertices () const
  {
    return m_v;
  }
  void BuildSection (
    int i,
    int point_index,
    const AlgVector& p,
    const AlgVector& dir, 
    const AlgVector& up,
    SGArray* pos, 
    SGArray* norm);

  void SetSectionTexCoord (int vertex, float s, float t);

  virtual void Draw ();
  virtual void Write (UtlWriter* writer);

protected:

  void SetTexCoordOutdated ();
  void SetTexArray (SGArray* array)
  {
    m_tex = array;
  }
  SGArray* GetTexArray ()
  {
    return m_tex;
  }
  virtual void BuildTexArray (int ncoord);
  void WriteCommon (UtlWriter* writer);

private:

  void UpdateTexCoords ();
  void UpdateSectionTexCoord (int i, int point_index);
  virtual void ComputeTexCoord (int index, int point_index, int slide_index);

private:

  int   m_slices;
  int   m_n;
  float m_radius;
  SGArray* m_tex;
  float* m_v;
  bool m_texcoord_updated;
  bool m_build_tex_coords;
};

#endif

