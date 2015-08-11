/************************************************************************
  PtcCylinder Class Header
  Draws a cylinder obstacle.
  rcosta@tecgraf.puc-rio.br
  Jun 2008
*************************************************************************/

#ifndef _PARTICLES_CYLINDER_H_
#define _PARTICLES_CYLINDER_H_

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

class PARTICLES_API PtcCylinder : public PtcObstacle
{
public:
  PtcCylinder(float top_radius, float bottom_radius, float height, unsigned int slices, 
    unsigned int stacks, float cx = 0, float cy = 0, float cz = 0);
  ~PtcCylinder(void);

  void Draw ();
  void SetRadius (float top_radius, float bottom_radius);

private:
  float m_topradius;
  float m_bottomradius;
  float m_height;
  float m_cx, m_cy, m_cz;
  unsigned int m_slices;
  unsigned int m_stacks;
  UGLArray* m_vertexarray;
  UGLArray* m_normalarray;
  UGLArray* m_texcoordarray;
  UGLArray* m_top_vertexarray;
  UGLArray* m_top_normalarray;
  UGLArray* m_top_texcoordarray;
  UGLArray* m_bottom_vertexarray;
  UGLArray* m_bottom_normalarray;
  UGLArray* m_bottom_texcoordarray;
  UGLVertexArray* m_arrays;
  UGLVertexArray* m_top_arrays;
  UGLVertexArray* m_bottom_arrays;
  UGLTriangleStrip* m_tristrip;
};

#endif