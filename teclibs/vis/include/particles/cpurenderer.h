/************************************************************************
  PtcCPUPointRenderer Class Header
  Implements a renderer using CPU. Does NOT support transparency nor
  volume rendering, but supports different radius for each particle.
  rcosta@tecgraf.puc-rio.br
  Nov 2008
*************************************************************************/

#ifndef _PARTICLES_CPU_POINT_RENDERER_H_
#define _PARTICLES_CPU_POINT_RENDERER_H_

#include "renderer.h"
#include "radiussorter.h"
#include "defines.h"
#include "pointset.h"

/************************************************************************
  Forward Declarations
*************************************************************************/

class UGLArray;
class UGLVertexArray;
class UGLTexture;

/************************************************************************
  Class Declaration
*************************************************************************/

/**
 * Renders a set of points on CPU.
 * Requirements:
 *   OpenGL >= 2.0
 */
class PARTICLES_API PtcCPUPointRenderer : public PtcPointRenderer
{
public:
  PtcCPUPointRenderer ();
  virtual ~PtcCPUPointRenderer ();
  virtual bool Init ();
  virtual void Draw ();
  virtual void SetModel (PtcPointSet* model);

  void SetRadiusPrecision (float precision);

  /**
   * Informs the renderer that the point radius array has changed.
   */
  void SetRadiusArrayChanged ();

protected:
  virtual void UpdateModel ();

private:
  class PointSetChangeListener : public PtcPointSetChangeListener
  {
  public:
    PointSetChangeListener (PtcCPUPointRenderer* renderer)
    : m_renderer(renderer)
    {
    }

    virtual ~PointSetChangeListener ()
    {
    }

    virtual void RadiusChanged () 
    { 
      m_renderer->SetRadiusArrayChanged();
    }
  private:
    PtcCPUPointRenderer* m_renderer;
  };

private:
  void RenderParticles ();
  void SetSortedIndicesOutdated ();

private:
  float m_maxsize;
  float m_radiusdiff;
  UGLArray* m_sorted_indexes;
  PtcRadiusSorter m_sorter;
  bool m_sorted_indices_outdated;
  PointSetChangeListener* m_pointset_change_listener;
  bool m_initialized;
};

/************************************************************************
  Inline Methods
*************************************************************************/



#endif