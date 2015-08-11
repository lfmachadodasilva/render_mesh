/************************************************************************
  PtcViewer Class Header
  Manages the particles renderer.
  rcosta@tecgraf.puc-rio.br
  Dec 2008
*************************************************************************/

#ifndef PARTICLES_VIEWER_H_
#define PARTICLES_VIEWER_H_

#include <alg/vector.h>
#include "renderer.h"
#include "defines.h"

/************************************************************************
  Forward Declarations
*************************************************************************/

class PtcModel;
class PtcPointRenderer;
class PtcCPUPointRenderer;
class PtcCPUAlphaPointRenderer;
class PtcGPUPointRenderer;
class PtcVectorRenderer;
class PtcObstacleRenderer;

/************************************************************************
  Class Declaration
*************************************************************************/

class PARTICLES_API PtcViewer
{
public:
  enum Renderer {
    RENDERER_AUTO,
    RENDERER_CPU,
    RENDERER_GPU
  };

  enum RenderMode
  {
    RENDERMODE_PARTICLES,
    RENDERMODE_VOLUMETRIC,
    RENDERMODE_VECTORFIELD,
    RENDERMODE_VECTORFIELD_PARTICLES
  };

  PtcViewer (const char* texpath = NULL);
  ~PtcViewer ();

  void Draw ();
  bool Init (Renderer mode = RENDERER_AUTO);

  void SetCamera (const AlgVector & position, const AlgVector & direction);
  void SetFOV (float fov);
  void SetModel (PtcModel* model);
  void SetViewport (int width, int height);

  void SetObstaclesEnabled (bool enable);
  void SetOrthoEnabled (bool enable);
  void SetRenderMode (RenderMode mode);
  void SetShaderPath (const char* path);
  void SetTransparencyEnabled (bool enable);
  void SetWireframeEnabled (bool enable);

private:
  bool InitParticleRenderer (Renderer type);

private:
  PtcPointRenderer* m_renderer;
  PtcCPUPointRenderer* m_cpurenderer;
  PtcCPUAlphaPointRenderer* m_cpualpharenderer;
  PtcGPUPointRenderer* m_gpurenderer;
  PtcVectorRenderer* m_vectorrenderer;
  
  Renderer m_renderertype;
  RenderMode m_rendermode;

  bool m_transparency;
 
  int m_vpwidth, m_vpheight;
  float m_fov;
  float m_scale;
  AlgVector m_campos, m_camdir;
  bool m_updatecam;

  PtcObstacleRenderer* m_obstacle_renderer;
  bool m_obstacles_enabled;
};

/************************************************************************
  Inline Methods
*************************************************************************/

inline void PtcViewer::SetCamera (const AlgVector & position, const AlgVector & direction) 
{ 
  m_campos = position;
  m_camdir = direction;
  m_updatecam = true;
}

inline void PtcViewer::SetFOV (float fov)
{ 
  m_fov = fov;
  m_updatecam = true;
}

inline void PtcViewer::SetViewport (int width, int height)
{ 
  m_vpwidth = width; 
  m_vpheight = height;
  m_updatecam = true;
}

#endif

