/************************************************************************
  PtcBox Class Header
  Draws a box obstacle.
  rcosta@tecgraf.puc-rio.br
  celes@tecgraf.puc-rio.br
  Jun 2008
*************************************************************************/

#ifndef _PARTICLES_CUBE_H_
#define _PARTICLES_CUBE_H_

#include "obstacle.h"
#include "defines.h"

/************************************************************************
  Forward Declarations
*************************************************************************/

class UGLArray;
class UGLVertexArray;

/************************************************************************
  Class Declaration
*************************************************************************/

class PARTICLES_API PtcBox : public PtcObstacle
{
public:
  PtcBox (float dx, float dy, float dz, float cx = 0, float cy = 0, float cz = 0);
  ~PtcBox (void);

  void Draw ();

private:
  void RenderCube ();

private:
  UGLArray* m_vertexarray;
  UGLVertexArray* m_arrays;
};

#endif