/************************************************************************
  PtcCPUAlphaPointRenderer Class Header
  Implements a renderer using CPU. Supports transparency and volume
  rendering, but only a single radius value is allowed for all particles.
  rcosta@tecgraf.puc-rio.br
  Nov 2008
*************************************************************************/

#ifndef _PARTICLES_CPU_ALPHA_POINT_RENDERER_H_
#define _PARTICLES_CPU_ALPHA_POINT_RENDERER_H_

#include "renderer.h"
#include "positionsorter.h"
#include "defines.h"

#include <utl/sort.h>

/************************************************************************
  Forward Declarations
*************************************************************************/

class PtcObstacle;
class UGLArray;
class UGLVertexArray;
class UGLTexture;
class PtcVectorRenderer;
class PtcPositionSortedIndices;

/************************************************************************
  Class Declaration
*************************************************************************/
/**
 * Renders a set of points on CPU.
 * Requirements:
 *   OpenGL >= 2.0
 */
class PARTICLES_API PtcCPUAlphaPointRenderer : public PtcPointRenderer
{
public:
  PtcCPUAlphaPointRenderer ();
  virtual ~PtcCPUAlphaPointRenderer ();
  virtual bool Init ();
  virtual void Draw ();
  virtual void SetCamera (const AlgVector & position, const AlgVector & direction);
  virtual void SetModel (PtcPointSet* model);

  void SetSortDelay (unsigned int delay);

private:
  virtual void UpdateModel ();
  void RenderParticles ();

private:
  float m_maxsize;
  PtcPositionSortedIndices* m_sorted_indexes;
  bool m_initialized;
};

/************************************************************************
  Inline Methods
*************************************************************************/



#endif