// Bilinear contour renderer
// rodesp@tecgraf.puc-rio.br
// Apr 2010

#ifndef TPV_CONTOUR_BILINEAR_H
#define TPV_CONTOUR_BILINEAR_H

#include <topsview/defines.h>
#include "contour.h"
#include "../geometry/bilinear.h"

class CGShader;

class TPV_API TpvContourBilinearRenderer : public TpvContourRenderer
{
public: 
  TpvContourBilinearRenderer ();
  
  virtual ~TpvContourBilinearRenderer ();

  void SetShaderPath (const char* path);

  bool Init ();
  
  void SetGeometry (TpvBilinearGeometry* g);

  void SetColorScaleTexObj (int tex_obj);

  /**
    Sets whether support for transparent faces is enabled.
    Default: false
  */
  void SetTransparencyEnabled (bool flag);
  
private:
  virtual void DoRender ();
  virtual void DoRenderSelection ();
  bool InitExtensions ();
  
private:
  TpvBilinearGeometry* m_geometry;
  bool m_transp_enabled;
  bool m_initialized;
  char m_shader_path[512];
  CGShader* m_shader_q4; 
  CGShader* m_shader_q8; 
  unsigned int m_cs_tex_obj;
};

#endif

