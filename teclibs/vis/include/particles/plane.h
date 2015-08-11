/************************************************************************
  PtcPlane Class Header
  Draws a plane obstacle.
  rcosta@tecgraf.puc-rio.br
  Jun 2008
*************************************************************************/

#ifndef _PARTICLES_PLANE_H_
#define _PARTICLES_PLANE_H_

#include "obstacle.h"
#include "defines.h"

/************************************************************************
  Forward Declarations
*************************************************************************/

class UGLArray;
class UGLVertexArray;
class UGLTriangleStrip;

/************************************************************************
  Class Declaration
*************************************************************************/

class PARTICLES_API PtcPlane : public PtcObstacle
{
public:
  PtcPlane(float dx, float dy, int nx = 1, int ny = 1, float cx = 0, float cy = 0, float cz = 0);
  ~PtcPlane(void);

  void Draw ();

private:
  UGLArray* m_vertexarray;
  UGLArray* m_normalarray;
  UGLArray* m_texcoordarray;
  UGLVertexArray* m_arrays;
  UGLTriangleStrip* m_tristrip;
};

#endif