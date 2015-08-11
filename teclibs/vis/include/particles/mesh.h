/************************************************************************
  PtcMesh Class Header
  Draws a triangle mesh obstacle.
  malf@tecgraf.puc-rio.br
  Sep 2009
*************************************************************************/

#ifndef _PARTICLES_MESH_H_
#define _PARTICLES_MESH_H_

#include "obstacle.h"
#include "defines.h"

/************************************************************************
  Forward Declarations
*************************************************************************/

class UGLArray;
class UGLVertexArray;
class UGLTriangleSet;

/************************************************************************
  Class Declaration
*************************************************************************/

class PARTICLES_API PtcMesh : public PtcObstacle
{
public:
  PtcMesh(int nv, int nt, float **vs, int **ts);
  ~PtcMesh();

  void Draw ();

private:
  UGLArray* m_vertexarray;
  UGLArray* m_normalarray;
  UGLArray* m_texcoordarray;
  UGLVertexArray* m_arrays;
  UGLTriangleSet* m_triset;
};

#endif