
#ifndef TPV_HARC_VOL_RENDERER3_H
#define TPV_HARC_VOL_RENDERER3_H

class CGShader;

#include <GL/glew.h>
#include <alg/matrix.h>
#include <topsview/geometry/array.h>
#include <topsview/geometry/tetrageometry3.h>
#include <topsview/colorscale/colorscale.h>
#include "renderer3.h"
#include <topsview/defines.h>

/**
  Volume rendering of unstructured tetrahedral meshes.
  Hardware-assisted ray casting with GPU integration of transfer function.

  This renderer draws a model in direct volume rendering mode, by using
  physically-based opacity values. The resulting image is then composed with
  the original frame buffer contents. Therefore, the opaque objects which may 
  intercept the volumetric model should be rendered before it.

  Reference:
    Espinha R, Celes W (2005) "High-Quality Hardware-Based Ray Casting Volume 
    Rendering Using Partial Pre-Integration", Brazilian Symposium on Comp. 
    Graphics and Image Processing, pp. 273-280

  OpenGL 2.0 support is required, along with the following extensions: 
    GL_ARB_texture_float
    GL_ARB_texture_rectangle
    GL_NV_fragment_program2 (NVIDIA Cg 1.5, vp40 and fp40 profiles).  
*/

MODEL_CLASS_TEMPLATE
class TPVH_API TpvHARCVolRenderer3 : public TpvRenderer3
{
public: 
  TpvHARCVolRenderer3();
  virtual ~TpvHARCVolRenderer3();

  /**
    Initializes the volume renderer.
    Returns true if it is supported.
    This method is implicitly invoked when the model is rendered.
  */
  bool Init();

  /**
    Informs the rendered whether the field extracted by the geometry set is normalized.
    Default: true (to keep compatibility)
  */
  void SetNormalizedField(bool flag);

  /**
    If true, the longest tetrahedral edge length in the model is used to 
    normalize the distance traversed by the propagating ray inside any
    single tetrahedron.
    Default: true.
  */
  void SetMaxEdgeLengthEnabled(bool flag);

  virtual void SetClippingPlane(float a, float b, float c, float d);
  virtual void SetClippingPlaneEnabled(bool flag);

  virtual void SetPolygonOffset(float factor, float units);
  virtual void SetPolygonOffsetEnabled(bool flag);

  /**
      Sets the limits of a probe box. The rendered model will be clipped
    by the given box.
  */
  virtual void SetProbeBox(float xmin, float xmax, float ymin, float ymax, float zmin, float zmax);
  virtual void SetProbeBoxEnabled(bool flag);

  /**
    Sets whether the model rendering will write to the depth buffer.
    Default: true.
  */
  void SetWriteDepthBufferEnabled(bool flag);

  /**
    Sets whether exact z values will be written to depth buffer instead 
    of model boundary face values. This is useful when a clipping plane 
    or probe box is to be used. 
    This method has no effect when depth buffer writing is disabled (see
    SetWriteDepthBufferEnabled()).
    Default: false.
  */
  void SetWriteExactZEnabled(bool flag);

  /**
      Sets the path used to look for the used shaders and 
    "PsiGammaTable.txt" file.
  */
  void SetShaderPath(const char* path);

  /**
      Sets the viewport of the window in which the model will be rendered.
    @warning In order to the algorithm to work correctly, it must be set
    whenever the window is resized.
  */
  void SetViewport(int x0, int y0, int w, int h);
  void GetViewport(int* x0, int* y0, int* w, int* h);

  /**
      Sets the background color of the model. It will be composed with
    the original frame buffer.
  */
  void SetBackground(float r, float g, float b, float a);
  
  virtual void SetNumOfSteps(int n) {}
  virtual void SetCurrentStep(int step_id) {}

  void SetGeometry (TpvTetraGeometry3<MODELCLASS>* geometry);

  void SetGeometryOutdated ();

  virtual void SetProperty(TpvProperty* property);

  virtual void SetColorScale(TpvColorScale* colorscale);

  void SetIsosurfacesEnabled(bool flag);

  /**
    Sets whether provided isosurface values will be used instead of
    colorscale values for determining isosurfaces. Isosurface colors 
    will still be retrieved from the colorscale.
    Default: false
  */
  void SetIsosurfaceValuesEnabled(bool flag);

  void SetIsosurfaceValues(int n, const float* values);

  float GetMinNormalizedIsosurfaceValueInterval();

  virtual bool Update();
  virtual void Render();

private:
  int InitExtensions ();
  bool InitTextureProxy();
  bool InitPsiGammaTable();
  bool CheckFramebufferStatus();
  bool InitFramebuffer();
  bool InitMeshAndPropertyTextures();
  bool InitTransferFuncTextures();
  bool InitShaders();

  void BuildTransferFuncTextures();
  void BuildColorScaleTexture();
  void BuildIsosurfacesTexture();
  int  BuildMeshTextures();
  void BuildPropertyTextures();
  void ComputeBdryFaces();
  void LoadTextures();
  void DrawFirstPass(
    GLint* viewport, double* projection, double* modelview, int pass);
  void DrawIntermediatePass(
    GLint* viewport, double* projection, double* modelview, 
    double frustum_near[4][3], int pass);
  void DrawFinalPass();
  void DrawFrontFacesDepths();

	bool BeginRender();
  bool EndRender();

  int GetNumIsosurfaceValues () const
  {
    if (m_isosurfaces_enabled && m_isosurface_values_enabled)
      return m_isosurface_values.Size();
    else
      return m_colorscale->GetNumberOfValues();  
  }

  float GetIsosurfaceValue (int i)
  {
    if (m_isosurfaces_enabled && m_isosurface_values_enabled)
      return m_isosurface_values[i];
    else
      return m_colorscale->GetValue(i);
  }


private:
  TpvTetraGeometry3<MODELCLASS>* m_geometry;
  TpvProperty* m_property;
  TpvColorScale* m_colorscale;

  CGShader*   m_shader1;
  CGShader*   m_shader2;
  CGShader*   m_shader3;
  CGShader*   m_shader2_isosurf;

  /** Original frame buffer contents. */
  GLuint  m_fb_color0_tex_obj;
  GLuint  m_fb_depth0_tex_obj;
  int           m_fb_width, m_fb_height;

  /** Frame buffer used for the intermediate passes of the algorithm. */
  GLuint  m_fb_obj;
  GLuint  m_fb_tex_obj;
  GLuint  m_fb_tex2_obj;
  GLuint  m_fb_depth_rb_obj;

  /** Occlusion query object for testing ray termination. */
  GLuint   m_query_obj;

  /** Mesh data structure textures (per tetrahedron). */ 
  GLuint   m_gnorm1_obj;  //< Normals of the first face.
  GLuint   m_gnorm2_obj;  //< Normals of the second face.
  GLuint   m_gnorm3_obj;  //< Normals of the third face.
  GLuint   m_gnorm4_obj;  //< Normals of the forth face.
  GLuint   m_ggrad_obj;   //< Gradient vector of the scalar field inside 
                                //< the tetrahedron.
  GLuint   m_tadj_obj;    //< Adjacent tetrahedra indexes.
  GLuint   m_tadj2_obj;    //< Adjacent tetrahedra indexes.

  /** Transfer function textures. */
  GLuint   m_tf_obj; 
  GLuint   m_isosurf_scalar_obj;
  GLuint   m_psi_table_obj;
  GLuint   m_depth_obj;

  int            m_max_w, m_max_h;
  int            m_viewport[4];
  float          m_bg_color[4];
  AlgMatrix      m_bg_mvp;

  int            m_initialized; 
  int            m_psi_initialized;

  TpvIntArray    m_bdry_elem;
  GLuint   m_bdry_disp_lst;

  char m_shader_path[256];
  char m_psi_gamma_path[256];
  int m_psi_gamma_size;

  float m_clip_plane[4];
  bool  m_clip_plane_enabled;
  float m_probe_box[6];
  bool  m_probe_box_enabled;
  float m_poly_offset_factor;
  float m_poly_offset_units;
  bool  m_poly_offset_enabled;
  bool  m_write_depth_enabled;
  bool  m_exact_z_enabled;
  bool  m_normalized_field;
  bool  m_maxedgelength_enabled;
  bool  m_isosurfaces_enabled;

  bool m_update_geometry;
  bool m_update_property;
  bool m_update_viewport;
  bool m_update_colorscale;

  bool m_isosurface_values_enabled;
  DsArray<float> m_isosurface_values;
};

#ifndef TPV_COMPILE_SHADER_FILE
TPV_API const char* TpvHARCVolRenderer3GetRTVP1 ();
TPV_API const char* TpvHARCVolRenderer3GetRTFP1 ();
TPV_API const char* TpvHARCVolRenderer3GetRTVP2 ();
TPV_API const char* TpvHARCVolRenderer3GetRT2FP2 ();
TPV_API const char* TpvHARCVolRenderer3GetRTFP4 ();
TPV_API const char* TpvHARCVolRenderer3GetIsoSurfFP ();
#endif

#include "harcvolrenderer3.inl"

#endif
