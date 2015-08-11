/************************************************************************
  PtcSphere Class Header
  Draws a sphere obstacle.
  rcosta@tecgraf.puc-rio.br
  Jun 2008
*************************************************************************/

#ifndef _SPHERE_H_
#define _SPHERE_H_

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

class PARTICLES_API PtcSphere : public PtcObstacle
{
public:
  PtcSphere(float radius, int slices, int stacks, float cx = 0, float cy = 0, float cz = 0);
  ~PtcSphere(void);

  void Draw ();
  void SetRadius(float radius);

private:
  UGLArray* m_vertexarray;
  UGLArray* m_normalarray;
  UGLArray* m_texcoordarray;
  UGLVertexArray* m_arrays;
  UGLTriangleStrip* m_tristrip;
  float m_radius;
  float m_cx, m_cy, m_cz;
  int m_slices;
  int m_stacks;
};

#endif