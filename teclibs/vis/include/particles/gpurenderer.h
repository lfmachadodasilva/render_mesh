/************************************************************************
  PtcGPUPointRenderer Class Header
  Implements a renderer using GPU shaders. Supports transparency and
  the particles' radius array.
  rcosta@tecgraf.puc-rio.br
  Nov 2008
*************************************************************************/

#ifndef _PARTICLES_GPU_POINT_RENDERER_H_
#define _PARTICLES_GPU_POINT_RENDERER_H_

#include "renderer.h"
#include "defines.h"
#include "positionsorter.h"

#include <shader/glslshader.h>

#include <stdio.h>

/************************************************************************
  Forward Declarations
*************************************************************************/

class PtcObstacle;
class UGLArray;
class UGLVertexArray;
class UGLTexture;
class PtcPositionSortedIndices;
class PtcVectorRenderer;

/************************************************************************
  Class Declaration
*************************************************************************/

/**
 * Renders a set of points on GPU.
 * Requirements:
 *   OpenGL >= 2.0
 */
class PARTICLES_API PtcGPUPointRenderer : public PtcPointRenderer
{
public:
  PtcGPUPointRenderer ();
  virtual ~PtcGPUPointRenderer ();

  virtual bool Init ();
  virtual void Draw ();
  virtual void SetCamera (const AlgVector & position, const AlgVector & direction);
  virtual void SetModel (PtcPointSet* model);

  void SetAlphaBlending (bool enable);
  void SetShaderPath (const char* path);

protected:
  virtual void UpdateModel ();

private:
  GLSLShader* GetCurrentShader();
  bool LoadShaders ();
  void RenderParticles ();
  void RenderVectorField ();

private:
  bool m_alphablend;
  float m_maxsize;
  PtcPositionSortedIndices* m_sorted_indexes;
  GLSLShader m_partshader;
  GLSLShader m_orthoshader;
  GLSLShader m_volshader;
  GLSLShader m_volorthoshader;
  char m_shader_path[512];
  bool m_initialized;
};

/************************************************************************
  Inline Methods
*************************************************************************/

  inline void PtcGPUPointRenderer::SetAlphaBlending (bool enable)
  {
    m_alphablend = enable;
  }

  inline GLSLShader* PtcGPUPointRenderer::GetCurrentShader ()
  {
    if (m_ortho) {
      return (m_rendermode == RENDERMODE_VOLUMETRIC) ? &m_volorthoshader : &m_orthoshader;
    } 
    else {
      return (m_rendermode == RENDERMODE_VOLUMETRIC) ? &m_volshader : &m_partshader;
    }
  }

#endif