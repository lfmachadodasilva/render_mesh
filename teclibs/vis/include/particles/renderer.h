/************************************************************************
  PtcPointRenderer Class Header
  Particles renderer interface.
  rcosta@tecgraf.puc-rio.br
  Nov 2008
*************************************************************************/

#ifndef _PARTICLES_POINT_RENDERER_H_
#define _PARTICLES_POINT_RENDERER_H_

#include <alg/vector.h>
#include "defines.h"

#ifdef _WIN32
# define WIN32_LEAN_AND_MEAN
# include <windows.h>
# define PARTICLES_MAX_PATH (MAX_PATH+1)
#else
# define PARTICLES_MAX_PATH (1024+1)
#endif

/************************************************************************
  Forward Declarations
*************************************************************************/

class PtcPointSet;
class UGLTexture;

/************************************************************************
  Class Declaration
*************************************************************************/

class PARTICLES_API PtcPointRenderer
{
public:
  enum RenderMode
  {
    RENDERMODE_PARTICLES,
    RENDERMODE_VOLUMETRIC,
  };

public:
  PtcPointRenderer ();

  virtual ~PtcPointRenderer ();

  virtual void Draw () = 0;

  virtual bool Init ();

  /**
   * Sets the point set model contaning the data to be rendered.
   * The renderer will register itself as a listener to the point set.
   */
  virtual void SetModel (PtcPointSet* model);

  virtual void SetCamera (const AlgVector & position, const AlgVector & direction);

  void SetFOV (float fov);
  void SetRenderMode (RenderMode mode);
  void SetOrthoEnabled (bool enable);
  void SetScale (float scale);
  void SetViewport (int width, int height);

  static void SetTexturePath (const char* path); // temp

protected:
  virtual void UpdateModel () = 0;  
  virtual bool LoadDefaultTextures ();
  PtcPointSet* GetModel () const;

protected:
  PtcPointSet* m_model;

  static UGLTexture* m_parttexture;
  static UGLTexture* m_voltexture;
  static char m_texpath[PARTICLES_MAX_PATH+1];

  RenderMode m_rendermode;
  bool m_wireframe;
  bool m_ortho;

  int m_vpwidth, m_vpheight;
  float m_fov;
  float m_scale;
  AlgVector m_campos, m_camdir;
};

/************************************************************************
  Inline Methods
*************************************************************************/

inline void PtcPointRenderer::SetCamera (const AlgVector & position, const AlgVector & direction) 
{ 
  m_campos = position;
  m_camdir = direction;
}

inline void PtcPointRenderer::SetFOV (float fov)
{ 
  m_fov = fov;
}

inline void PtcPointRenderer::SetScale (float scale)
{
  m_scale = scale;
}

inline void PtcPointRenderer::SetViewport (int width, int height)
{ 
  m_vpwidth = width; 
  m_vpheight = height;
}

inline void PtcPointRenderer::SetRenderMode (RenderMode mode)
{
  m_rendermode = mode;
}

inline void PtcPointRenderer::SetOrthoEnabled (bool enable)
{
  m_ortho = enable;
}

inline PtcPointSet* PtcPointRenderer::GetModel () const
{
  return m_model;
}

#endif
