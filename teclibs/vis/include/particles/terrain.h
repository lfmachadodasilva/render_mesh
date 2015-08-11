/************************************************************************
  PtcTerrain Class Header
  Draws a heightmap terrain obstacle.
  rcosta@tecgraf.puc-rio.br
  Jul 2008
*************************************************************************/

#ifndef _PARTICLES_TERRAIN_H_
#define _PARTICLES_TERRAIN_H_

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

class PARTICLES_API PtcTerrain : public PtcObstacle
{
public:
  PtcTerrain(const char* heightmap, float dx, float dz, float scale, float cx = 0, float cy = 0, float cz = 0);
  ~PtcTerrain(void);

  void Draw ();

private:
  UGLArray* m_vertexarray;
  UGLArray* m_normalarray;
  UGLArray* m_texcoordarray;
  UGLVertexArray* m_arrays;
  UGLTriangleStrip* m_tristrip;
};

#endif