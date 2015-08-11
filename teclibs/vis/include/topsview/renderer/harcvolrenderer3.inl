#include <GL/glew.h>

#include <tops/tops.h>

#include <alg/matrix.h>
#include <uso/clock.h>
#include <ugl/uglim.h>
#include <ugl/image.h>
#include <ugl/error.h>
#include <ugl/ugl.h>
#include <shader/cgshader.h>
#include <vgl/frustum.h>
#include "PsiGammaTable.h"
#include "harcvolrenderer3.h"

#include <Cg/cg.h>
#include <Cg/cgGL.h>

//#define VERBOSE 1

// Uncomment this line in order to avoid frame buffer resizing when the
// viewport changes.
//#define TPV_USE_FAST_VIEWPORT

// Uncomment this line in order to compile shaders on-demand.
//#define TPV_COMPILE_SHADER_FILE

// Uncomment this line to disable features unsupported by GeForce 6200 series.
//#define TPV_USE_GEFORCE_6200

/**
 * The texture size defined below works fine for most cases.
 * A too small texture size may cause isosurfaces to be rendered
 * in an offset position, thus resulting in gaps between adjacent tetrahedra.
 */
#define TRANSFER_FUNCTION_TEXTURE_SIZE 1024

/**
 * The mesh texture dimensions defined below work for most graphics cards.
 * Many cards internally use "half float" type for texture access, 
 * despite shader operations are performed using single-precision "float".
 * In that case, access to textures with any dimension larger than 2048 will 
 * suffer from precision errors.
 */
#define MAX_MESH_TEXTURE_WIDTH 2048
#define MAX_MESH_TEXTURE_HEIGHT 2048

#if 0
static bool s_save_bound_texture_image(
  const char* label, const char *filename, const char* fileformat,
  int tex_target, int tex_level, int tex_format, int tex_depth)
{
  int w, h;
  glGetTexLevelParameteriv(tex_target, tex_level, GL_TEXTURE_WIDTH, &w);
  glGetTexLevelParameteriv(tex_target, tex_level, GL_TEXTURE_HEIGHT, &h);
  unsigned char* image = NULL;
  bool r = false;
  switch (tex_format) {
    case GL_DEPTH_COMPONENT:
      // TODO
      //image = new unsigned int[w*h];
      //glGetTexImage(tex_target, tex_level, tex_format, GL_UNSIGNED_INT, image);
      //r = uglim_write_depth_image(label, filename, fileformat, w, h, (unsigned int*) image);
      //delete image;
      r = false;
      break;
    case GL_RGB:
      image = new unsigned char[3*w*h];
      glGetTexImage(tex_target, tex_level, tex_format, GL_UNSIGNED_BYTE, image);
      r = uglim_write_rgb_image(label, filename, fileformat, w, h, (unsigned char*) image);
      delete image;
      break;
    case GL_RGBA:
      image = new unsigned char[4*w*h];
      glGetTexImage(tex_target, tex_level, tex_format, GL_UNSIGNED_BYTE, image);
      r = uglim_write_rgba_image(label, filename, fileformat, w, h, (unsigned char*) image);
      delete image;
      break;
    default:
      r = false;
      break;
  }
  return r;
}
#endif

//TODO Move to AlgMatrix
inline static float Det(float* m)
{
  return
    m[0] *
      ( m[5] * (m[10]*m[15] - m[14]*m[11]) -
        m[9] * (m[6]*m[15]  - m[14]*m[7])  +
        m[13] * (m[6]*m[11]  - m[10]*m[7])   ) -
    m[4] *
      ( m[1] * (m[10]*m[15] - m[14]*m[11]) -
        m[9] * (m[2]*m[15] - m[14]*m[3])   +
        m[13] * (m[2]*m[11] - m[10]*m[3])    ) +
    m[8] *
      ( m[1] * (m[6]*m[15] - m[14]*m[7]) -
        m[5] * (m[2]*m[15] - m[14]*m[3]) +
        m[13] * (m[2]*m[7] - m[6]*m[3])      ) -
    m[12] *
      ( m[1] * (m[6]*m[11] - m[10]*m[7]) -
        m[5] * (m[2]*m[11] - m[10]*m[3]) +
        m[9] * (m[2]*m[7] - m[6]*m[3])       );
}

//TODO Move to AlgMatrix
static int Solve(float* x, float* A, float* b )
{
  double s1,s2,s3,s4,s5;

  double det = Det(A);

  if ( fabs(det) < 1e-8 )
    return 0;

  s2 =  ( A[5] * (A[10]*A[15] - A[14]*A[11]) + A[6] * (-A[9]*A[15] + A[13]*A[11]) +
          A[7] * (A[9]*A[14] - A[13]*A[10]) ) * b[0] / det;
  s3 =  - ( A[4] * (A[10]*A[15] - A[14]*A[11]) + A[6] * (-A[8]*A[15] + A[12]*A[11]) +
            A[7] * (A[8]*A[14] - A[12]*A[10]) ) * b[1] / det;
  s1 =  s2 + s3;
  s2 =  s1;
  s4 =  ( A[4] * (A[9]*A[15] - A[13]*A[11]) + A[5] * (-A[8]*A[15] + A[12]*A[11]) +
          A[7] * (A[8]*A[13] - A[12]*A[9]) ) * b[2] / det;
  s5 =  - ( A[4] * (A[9]*A[14] - A[13]*A[10]) + A[5] * (-A[8]*A[14] + A[12]*A[10]) +
            A[6] * (A[8]*A[13] - A[12]*A[9]) ) * b[3] / det;
  s3 =  s4 + s5;
  x[0] = (float) (s2 + s3);

  s2 =  - ( A[1] * (A[10]*A[15] - A[14]*A[11]) + A[2] * (-A[9]*A[15] + A[13]*A[11]) +
            A[3] * (A[9]*A[14] - A[13]*A[10]) ) * b[0] / det;
  s3 =  ( A[0] * (A[10]*A[15] - A[14]*A[11]) + A[2] * (-A[8]*A[15] + A[12]*A[11]) +
          A[3] * (A[8]*A[14] - A[12]*A[10]) ) * b[1] / det;
  s1 =  s2 + s3;
  s2 =  s1;
  s4 =  - ( A[0] * (A[9]*A[15] - A[13]*A[11]) + A[1] * (-A[8]*A[15] + A[12]*A[11]) +
            A[3] * (A[8]*A[13] - A[12]*A[9]) ) * b[2] / det;
  s5 =  ( A[0] * (A[9]*A[14] - A[13]*A[10]) + A[1] * (-A[8]*A[14] + A[12]*A[10]) +
          A[2] * (A[8]*A[13] - A[12]*A[9]) ) * b[3] / det;
  s3 =  s4 + s5;
  x[1] = (float) (s2 + s3);

  s2 =  ( A[1] * (A[6]*A[15] - A[14]*A[7]) + A[2] * (-A[5]*A[15] + A[13]*A[7]) +
          A[3] * (A[5]*A[14] - A[13]*A[6]) ) * b[0] / det;
  s3 =  - ( A[0] * (A[6]*A[15] - A[14]*A[7]) + A[2] * (-A[4]*A[15] + A[12]*A[7]) +
            A[3] * (A[4]*A[14] - A[12]*A[6]) ) * b[1] / det;
  s1 =  s2 + s3;
  s2 =  s1;
  s4 =  ( A[0] * (A[5]*A[15] - A[13]*A[7]) + A[1] * (-A[4]*A[15] + A[12]*A[7]) +
          A[3] * (A[4]*A[13] - A[12]*A[5]) ) * b[2] / det;
  s5 =  - ( A[0] * (A[5]*A[14] - A[13]*A[6]) + A[1] * (-A[4]*A[14] + A[12]*A[6]) +
            A[2] * (A[4]*A[13] - A[12]*A[5]) ) * b[3] / det;
  s3 =  s4 + s5;
  x[2] = (float) (s2 + s3);

  s2 =  - ( A[1] * (A[6]*A[11] - A[10]*A[7]) + A[2] * (-A[5]*A[11] + A[9]*A[7]) +
            A[3] * (A[5]*A[10] - A[9]*A[6]) ) * b[0] / det;
  s3 =  ( A[0] * (A[6]*A[11] - A[10]*A[7]) + A[2] * (-A[4]*A[11] + A[8]*A[7]) +
          A[3] * (A[4]*A[10] - A[8]*A[6]) ) * b[1] / det;
  s1 =   s2 + s3;
  s2 =   s1;
  s4 =  - ( A[0] * (A[5]*A[11] - A[9]*A[7]) + A[1] * (-A[4]*A[11] + A[8]*A[7]) +
            A[3] * (A[4]*A[9] - A[8]*A[5]) ) * b[2] / det;
  s5 =  ( A[0] * (A[5]*A[10] - A[9]*A[6]) + A[1] * (-A[4]*A[10] + A[8]*A[6]) +
          A[2] * (A[4]*A[9] - A[8]*A[5]) ) * b[3] / det;
  s3 =   s4 + s5;
  x[3] = (float) (s2 + s3);

  return 1;
}

static void ComputeGradient(float* p, float* s, float* gradient_out)
{
  float A[16] = {
    p[3*0+0], p[3*1+0], p[3*2+0], p[3*3+0],
    p[3*0+1], p[3*1+1], p[3*2+1], p[3*3+1],
    p[3*0+2], p[3*1+2], p[3*2+2], p[3*3+2],
    1.f, 1.f, 1.f, 1.f
  };
  float x[4];
  if (Solve(x, A, s)) {
    gradient_out[0] = x[0]; gradient_out[1] = x[1]; gradient_out[2] = x[2];
  }else {
    gradient_out[0] = gradient_out[1] = gradient_out[2] = 0.f;
  }
}

MODEL_CLASS_TEMPLATE
int TpvHARCVolRenderer3<MODELCLASS>::InitExtensions ()
{
  static bool initialized = false;
  if (initialized)
    return 1;
  if (glewInit() != GLEW_NO_ERROR)
    return 0;
  if (!glActiveTexture) return 0;
  if (!glTexImage3D) return 0;
  if (!glMultiTexCoord2f) return 0;
  if (!glMultiTexCoord3f) return 0;
  if (!glMultiTexCoord3fv) return 0;
  if (!glGenQueries) return 0;
  if (!glDeleteQueries) return 0;
  if (!glBeginQuery) return 0;
  if (!glEndQuery) return 0;
  if (!glGetQueryiv) return 0;
  if (!glGetQueryObjectiv) return 0;
  if (!glGetQueryObjectuiv) return 0;
  if (!glDeleteRenderbuffersEXT) return 0;
  if (!glGenRenderbuffersEXT) return 0;
  if (!glFramebufferRenderbufferEXT) return 0;
  if (!glGenRenderbuffersEXT) return 0;
  if (!glRenderbufferStorageEXT) return 0;
  if (!glGenFramebuffersEXT) return 0;
  if (!glDeleteFramebuffersEXT) return 0;
  if (!glCheckFramebufferStatusEXT) return 0;
  if (!glFramebufferTexture2DEXT) return 0;
  if (!glGenFramebuffersEXT) return 0;
  if (!glIsFramebufferEXT) return 0;

  // glDrawBuffers (Multiple Render Targets)
  if (!GLEW_VERSION_2_0 ||
      !GLEW_EXT_framebuffer_object ||
      !GLEW_ARB_texture_float ||
      !GLEW_ARB_texture_rectangle)
    return 0;

  initialized = true;
  return 1;
}

static void BindTextureRectangle(unsigned int obj, bool enable_texture = false,
  bool init_param = false, bool init_data = false, int w = 1, int h = 1, float* data = NULL);

static void BindTextureRectangle(unsigned int obj, bool enable_texture,
  bool init_param, bool init_data, int w, int h, float* data)
{
  glBindTexture(GL_TEXTURE_RECTANGLE_ARB, obj);
  if (init_param) {
    //Nao pode setar esse parametro!
    //glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  }
  if (init_data)
    glTexImage2D(GL_TEXTURE_RECTANGLE_ARB, 0, GL_RGBA32F_ARB,
      w, h, 0, GL_RGBA, GL_FLOAT, data);
  if (enable_texture)
    glEnable(GL_TEXTURE_RECTANGLE_ARB);
}

static void BindDepthTextureRectangle(unsigned int obj, bool enable_texture = false,
  bool init_param = false, bool init_data = false, int w = 1, int h = 1, float* data = NULL);

static void BindDepthTextureRectangle(unsigned int obj, bool enable_texture,
  bool init_param, bool init_data, int w, int h, float* data)
{
  glBindTexture(GL_TEXTURE_RECTANGLE_ARB, obj);
  if (init_param) {
    glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_DEPTH_TEXTURE_MODE, GL_LUMINANCE);
    glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_COMPARE_MODE, GL_NONE);
  }
  if (init_data)
    glTexImage2D(GL_TEXTURE_RECTANGLE_ARB, 0, GL_DEPTH_COMPONENT24,
      w, h, 0, GL_DEPTH_COMPONENT, GL_FLOAT, data);
  if (enable_texture)
    glEnable(GL_TEXTURE_RECTANGLE_ARB);
}

static void ComputeFrustumNear(
  GLint viewport[4], double modelview[16], double projection[16], double frustum_near[4][3])
{
  // frustum_near[4][3]: {bl, br, tr, tl}
  gluUnProject((double) viewport[0], (double) viewport[1], 0.0,
      modelview, projection, viewport,
      &frustum_near[0][0], &frustum_near[0][1], &frustum_near[0][2]);
  gluUnProject((double)(viewport[0]+viewport[2]), (double) viewport[1], 0.0,
      modelview, projection, viewport,
      &frustum_near[1][0], &frustum_near[1][1], &frustum_near[1][2]);
  gluUnProject((double)(viewport[0]+viewport[2]), (double)(viewport[1]+viewport[3]), 0.0,
      modelview, projection, viewport,
      &frustum_near[2][0], &frustum_near[2][1], &frustum_near[2][2]);
  gluUnProject((double) viewport[0], (double)(viewport[1]+viewport[3]), 0.0,
      modelview, projection, viewport,
      &frustum_near[3][0], &frustum_near[3][1], &frustum_near[3][2]);
}

MODEL_CLASS_TEMPLATE
bool TpvHARCVolRenderer3<MODELCLASS>::InitTextureProxy()
{
  int min_w_2d = MAX_MESH_TEXTURE_WIDTH;
  int min_h_2d = MAX_MESH_TEXTURE_HEIGHT;
  GLint size;
  glTexImage2D(GL_PROXY_TEXTURE_RECTANGLE_ARB, 0, GL_RGBA32F_ARB,
               min_w_2d, min_h_2d,
               0, GL_RGBA, GL_FLOAT, NULL);
  glGetTexLevelParameteriv(GL_PROXY_TEXTURE_RECTANGLE_ARB, 0, GL_TEXTURE_WIDTH, &size);
  if (size < min_w_2d) return false;
  glGetTexLevelParameteriv(GL_PROXY_TEXTURE_RECTANGLE_ARB, 0, GL_TEXTURE_HEIGHT, &size);
  if (size < min_h_2d) return false;
  m_max_w = min_w_2d;
  m_max_h = min_h_2d;
  return true;
}

MODEL_CLASS_TEMPLATE
bool TpvHARCVolRenderer3<MODELCLASS>::InitPsiGammaTable()
{
  if (m_psi_initialized)
    return true;

#ifdef VERBOSE
  printf("Initializing psi gamma table...\n");
#endif
  PsiGammaInitTable(m_psi_gamma_path, m_psi_gamma_size);
#ifdef VERBOSE
  printf("Psi gamma table initialized.\n");
#endif
  glPushAttrib(GL_TEXTURE_BIT);
  glActiveTexture(GL_TEXTURE11);
  glBindTexture(GL_TEXTURE_2D, m_psi_table_obj);
  //glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE_FLOAT16_ATI, PSI_GAMMA_SIZE, PSI_GAMMA_SIZE,
  glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE16F_ARB, PSI_GAMMA_SIZE, PSI_GAMMA_SIZE,
              0, GL_LUMINANCE, GL_FLOAT, PsiGammaGetTable());
  glPopAttrib();
  m_psi_initialized = 1;
  return true;
}

MODEL_CLASS_TEMPLATE
bool TpvHARCVolRenderer3<MODELCLASS>::CheckFramebufferStatus()
{
  int status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
  switch(status) {
    case GL_FRAMEBUFFER_COMPLETE_EXT:
      return true;
    case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
      //printf("Unsupported framebuffer!!!\n");
      //assert(0);
      return false;
    default:
      /* programming error; will fail on all hardware */
      //printf("Invalid framebuffer object!!!\n");
      //assert(0);
      return false;
  }
}

MODEL_CLASS_TEMPLATE
bool TpvHARCVolRenderer3<MODELCLASS>::InitFramebuffer()
{
  glPushAttrib(GL_ALL_ATTRIB_BITS);
  glGenTextures(1, &m_fb_color0_tex_obj);
  glGenTextures(1, &m_fb_depth0_tex_obj);
  glGenTextures(1, &m_fb_tex_obj);
  glGenTextures(1, &m_fb_tex2_obj);
  glGenFramebuffersEXT(1, &m_fb_obj);
  glGenRenderbuffersEXT(1, &m_fb_depth_rb_obj);

#ifdef TPV_USE_FAST_VIEWPORT
  if (m_viewport[0] + m_viewport[2] <= m_fb_width &&
      m_viewport[1] + m_viewport[3] <= m_fb_height)
  {
    glPopAttrib();
    return true;
  }
#endif

  GLint old_fb_obj;
  glGetIntegerv(GL_FRAMEBUFFER_BINDING_EXT, &old_fb_obj);

  // Initializes frame buffer object.
  glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_fb_obj);
  glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, m_fb_depth_rb_obj);
  glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24,
    m_viewport[2], m_viewport[3]);
  glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT,
    GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, m_fb_depth_rb_obj);

  // Sets textures.
  // Rendering frame buffers of the intermediate passes.
  glActiveTexture(GL_TEXTURE0);
  BindTextureRectangle(m_fb_tex_obj, false, true, true,
    m_viewport[2], m_viewport[3], NULL);
  glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT,
    GL_TEXTURE_RECTANGLE_ARB, m_fb_tex_obj, 0);
  glActiveTexture(GL_TEXTURE1);
  BindTextureRectangle(m_fb_tex2_obj, false, true, true,
    m_viewport[2], m_viewport[3], NULL);
  glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT1_EXT,
    GL_TEXTURE_RECTANGLE_ARB, m_fb_tex2_obj, 0);

  GLint maxbuffers;
  glGetIntegerv(GL_MAX_DRAW_BUFFERS, &maxbuffers);
  if (maxbuffers < 2) {
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, old_fb_obj);
    glPopAttrib();
    return false;
  }

  // Background frame buffer.
  glActiveTexture(GL_TEXTURE2);
  BindTextureRectangle(m_fb_color0_tex_obj, false, true, true,
    m_viewport[2], m_viewport[3], NULL);
  glActiveTexture(GL_TEXTURE3);
  BindDepthTextureRectangle(m_fb_depth0_tex_obj, false, true, true,
    m_viewport[2], m_viewport[3], NULL);

  // Checks status.
  bool status = CheckFramebufferStatus();
  if (status) {
    m_fb_width = m_viewport[2];
    m_fb_height = m_viewport[3];
  }
  glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, old_fb_obj);
  glPopAttrib();
  return status;
}

MODEL_CLASS_TEMPLATE
bool TpvHARCVolRenderer3<MODELCLASS>::Init()
{
  if (m_initialized)
    return true;

  if (!InitExtensions())
    return false;
  if (!InitTextureProxy())
    return false;
  if (!CGShader::Init("vp40", "fp40"))
    return false;
  if (!InitFramebuffer())
    return false;
  if (!InitMeshAndPropertyTextures())
    return false;
  if (!InitTransferFuncTextures())
    return false;
  if (!InitShaders())
    return false;
  // Occlusion query
  glGenQueries(1, &m_query_obj);
  InitPsiGammaTable();

  m_initialized = 1;
  return true;
}

MODEL_CLASS_TEMPLATE
bool TpvHARCVolRenderer3<MODELCLASS>::InitMeshAndPropertyTextures()
{
  glPushAttrib(GL_TEXTURE_BIT | GL_ENABLE_BIT);
  glGenTextures(1, &m_ggrad_obj);
  BindTextureRectangle(m_ggrad_obj, false, true);
  glGenTextures(1, &m_gnorm1_obj);
  BindTextureRectangle(m_gnorm1_obj, false, true);
  glGenTextures(1, &m_gnorm2_obj);
  BindTextureRectangle(m_gnorm2_obj, false, true);
  glGenTextures(1, &m_gnorm3_obj);
  BindTextureRectangle(m_gnorm3_obj, false, true);
  glGenTextures(1, &m_gnorm4_obj);
  BindTextureRectangle(m_gnorm4_obj, false, true);
  glGenTextures(1, &m_tadj_obj);
  BindTextureRectangle(m_tadj_obj, false, true);
  glGenTextures(1, &m_tadj2_obj);
  BindTextureRectangle(m_tadj2_obj, false, true);
  glPopAttrib();
  return true;
}

MODEL_CLASS_TEMPLATE
bool TpvHARCVolRenderer3<MODELCLASS>::InitTransferFuncTextures()
{
  glGenTextures(1, &m_tf_obj);
  glGenTextures(1, &m_isosurf_scalar_obj);
  glGenTextures(1, &m_psi_table_obj);
  glGenTextures(1, &m_depth_obj);
  return true;
}

MODEL_CLASS_TEMPLATE
bool TpvHARCVolRenderer3<MODELCLASS>::InitShaders()
{
#ifdef TPV_COMPILE_SHADER_FILE
  char filename[256];
#endif
#ifdef TPV_COMPILE_SHADER_FILE
  strcpy(filename, m_shader_path);
  strcat(filename, "/gpurt_vp1.cg");
  if (!m_shader1->CompileFile(Shader::VP, filename, "main", NULL)) {
#else
  if (!m_shader1->CompileString(Shader::VP, TpvHARCVolRenderer3GetRTVP1(), "main", NULL)) {
#endif
    return false;
  }

#ifdef TPV_COMPILE_SHADER_FILE
  strcpy(filename, m_shader_path);
  strcat(filename, "/gpurt_fp1.cg");
  if (!m_shader1->CompileFile(Shader::FP, filename, "main", NULL)) {
#else
  if (!m_shader1->CompileString(Shader::FP, TpvHARCVolRenderer3GetRTFP1(), "main", NULL)) {
#endif
    return false;
  }

  // Uniform parameters
  m_shader1->TrackMatrix(Shader::VP, "ModelViewProj",
                        Shader::MODELVIEW_PROJECTION,
                        Shader::IDENTITY);
  //m_shader1->BindTexture("FramebufferTex0", m_fb_tex_obj);
  m_shader1->BindTexture("DepthTex", m_depth_obj);

#ifdef TPV_COMPILE_SHADER_FILE
  strcpy(filename, m_shader_path);
  strcat(filename, "/gpurt_vp2.cg");
  if (!m_shader2->CompileFile(Shader::VP, filename, "main", NULL)) {
#else
  if (!m_shader2->CompileString(Shader::VP, TpvHARCVolRenderer3GetRTVP2(), "main", NULL)) {
#endif
    return false;
  }

  // Intermediate (main) pass of the GPU Ray-casting.
#ifdef TPV_COMPILE_SHADER_FILE
  strcpy(filename, m_shader_path);
  strcat(filename, "/gpurt2_fp2.cg");
  if (!m_shader2->CompileFile(Shader::FP, filename, "main", NULL)) {
#else
  if (!m_shader2->CompileString(Shader::FP, TpvHARCVolRenderer3GetRT2FP2(), "main", NULL)) {
#endif
    return false;
  }
  // Uniform parameters
  m_shader2->TrackMatrix(Shader::VP, "ModelViewProj",
                        Shader::MODELVIEW_PROJECTION,
                        Shader::IDENTITY);
  m_shader2->TrackMatrix(Shader::VP, "ModelViewProjInv",
                        Shader::MODELVIEW_PROJECTION,
                        Shader::INVERSE);
  m_shader2->TrackMatrix(Shader::FP, "ModelViewProjFP",
                        Shader::TEXTURE,
                        Shader::IDENTITY);
  m_shader2->TrackMatrix(Shader::FP, "ModelViewProjInvFP",
                        Shader::TEXTURE,
                        Shader::INVERSE);
  m_shader2->BindTexture("FramebufferTex0", m_fb_tex_obj);
  m_shader2->BindTexture("FramebufferTex1", m_fb_tex2_obj);

  m_shader2->BindTexture("GGradTex", m_ggrad_obj);
  m_shader2->BindTexture("GNorm1Tex", m_gnorm1_obj);
  m_shader2->BindTexture("GNorm2Tex", m_gnorm2_obj);
  m_shader2->BindTexture("GNorm3Tex", m_gnorm3_obj);
  m_shader2->BindTexture("GNorm4Tex", m_gnorm4_obj);
  m_shader2->BindTexture("TAdjTex", m_tadj_obj);
  m_shader2->BindTexture("TAdjTex2", m_tadj2_obj);
  m_shader2->BindTexture("TransferFuncTex", m_tf_obj);
  m_shader2->BindTexture("IsoSurfScalarTex", m_isosurf_scalar_obj);
  m_shader2->BindTexture("PsiTableTex", m_psi_table_obj);

  // Intermediate (main) pass for iso-surface rendering
#ifdef TPV_COMPILE_SHADER_FILE
  strcpy(filename, m_shader_path);
  strcat(filename, "/gpurt_vp2.cg");
  if (!m_shader2_isosurf->CompileFile(Shader::VP, filename, "main", NULL)) {
#else
  if (!m_shader2_isosurf->CompileString(Shader::VP, TpvHARCVolRenderer3GetRTVP2(), "main", NULL)) {
#endif
    return false;
  }

#ifdef TPV_COMPILE_SHADER_FILE
  strcpy(filename, m_shader_path);
  strcat(filename, "/harc_isosurf.fp.cg");
  if (!m_shader2_isosurf->CompileFile(Shader::FP, filename, "main", NULL)) {
#else
  if (!m_shader2_isosurf->CompileString(Shader::FP, TpvHARCVolRenderer3GetIsoSurfFP(), "main", NULL)) {
#endif
    return false;
  }
  // Uniform parameters
  m_shader2_isosurf->TrackMatrix(Shader::VP, "ModelViewProj",
                        Shader::MODELVIEW_PROJECTION,
                        Shader::IDENTITY);
  m_shader2_isosurf->TrackMatrix(Shader::VP, "ModelViewProjInv",
                        Shader::MODELVIEW_PROJECTION,
                        Shader::INVERSE);
  m_shader2_isosurf->TrackMatrix(Shader::FP, "ModelViewProjFP",
                        Shader::TEXTURE,
                        Shader::IDENTITY);
  m_shader2_isosurf->TrackMatrix(Shader::FP, "ModelViewProjInvFP",
                        Shader::TEXTURE,
                        Shader::INVERSE);
  m_shader2_isosurf->BindTexture("FramebufferTex0", m_fb_tex_obj);
  m_shader2_isosurf->BindTexture("FramebufferTex1", m_fb_tex2_obj);

  m_shader2_isosurf->BindTexture("GGradTex", m_ggrad_obj);
  m_shader2_isosurf->BindTexture("GNorm1Tex", m_gnorm1_obj);
  m_shader2_isosurf->BindTexture("GNorm2Tex", m_gnorm2_obj);
  m_shader2_isosurf->BindTexture("GNorm3Tex", m_gnorm3_obj);
  m_shader2_isosurf->BindTexture("GNorm4Tex", m_gnorm4_obj);
  m_shader2_isosurf->BindTexture("TAdjTex", m_tadj_obj);
  m_shader2_isosurf->BindTexture("TAdjTex2", m_tadj2_obj);
  m_shader2_isosurf->BindTexture("TransferFuncTex", m_tf_obj);
  m_shader2_isosurf->BindTexture("IsoSurfScalarTex", m_isosurf_scalar_obj);

  // Final pass of GPU Ray-casting.
  // Writes results to the frame buffer.
#ifdef TPV_COMPILE_SHADER_FILE
  strcpy(filename, m_shader_path);
  strcat(filename, "/gpurt_fp4.cg");
  if (!m_shader3->CompileFile(Shader::FP, filename, "main", NULL)) {
#else
  if (!m_shader3->CompileString(Shader::FP, TpvHARCVolRenderer3GetRTFP4(), "main", NULL)) {
#endif
    return false;
  }
  //m_shader3->BindTexture("FramebufferTex0", m_fb_tex_obj);
  return true;
}
 
/**
 * Builds the textures for mapping the scalar field associated 
 * to the tetrahedral mesh into color and opacity components.
 *
 * Two 1D textures are defined. The first one maps scalar values
 * into color and opacity values. The second texture stores
 * encoded isosurface values corresponding to the "control points"
 * of a piecewise linear transfer function. By default, control
 * points are associated to each scalar value of the user-provided
 * color scale. Points lying in an interval located between two 
 * consecutive values are linearly interpolated.
 */
MODEL_CLASS_TEMPLATE
void TpvHARCVolRenderer3<MODELCLASS>::BuildTransferFuncTextures()
{
  BuildColorScaleTexture();
  BuildIsosurfacesTexture();
}

MODEL_CLASS_TEMPLATE
void TpvHARCVolRenderer3<MODELCLASS>::BuildColorScaleTexture()
{
  int w = TRANSFER_FUNCTION_TEXTURE_SIZE;
  DsArray<float> data;
  data.Resize(4*w);
  m_colorscale->GetTexArray(w, data.GetArray());

  glPushAttrib(GL_TEXTURE_BIT);
  glActiveTexture(GL_TEXTURE8);
  glBindTexture(GL_TEXTURE_1D, m_tf_obj);
  //TODO Linear filter for RGBA32 is unsupported by current GPUs
  //glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA_FLOAT32_ATI, w,
  glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA16F_ARB, w,
               0, GL_RGBA, GL_FLOAT, data.GetArray());
  glPopAttrib();
}

MODEL_CLASS_TEMPLATE
void TpvHARCVolRenderer3<MODELCLASS>::BuildIsosurfacesTexture()
{
  int niso = GetNumIsosurfaceValues();
  float smin = m_colorscale->GetValue(0);
  float smax = m_colorscale->GetValue(m_colorscale->GetNumberOfValues() - 1);
  float ds = smax - smin;
  // Compute valid isosurface values (within color scale limits)
  DsArray<float> isovalues;
  for (int i = 0; i < niso; i++) {
    float v = GetIsosurfaceValue(i);
    if (v >= smin && v <= smax)
      isovalues.Append(v);
  }

  // Create an empty texture (no isosurfaces)
  int w = TRANSFER_FUNCTION_TEXTURE_SIZE;
  float* scalar_tex = new float[4*w];
  assert(scalar_tex);
  for (int i = 0; i < 4*w; i++)
    scalar_tex[i] = 3.0f;

  // Fill texture with isosurface values
  if (niso > 0 && ds > 0.0f && isovalues.Size() > 0) {
    //TM
    int i_tf = 0;
    for (int i = 0; i < w; ) {
      //Modified to handle precision error when drawing isosurfaces.
      //float s = (float) i/(w-1);
      float s = (float) i/w;
      float s_tf = (isovalues[i_tf] - smin)/ds;
      if (i_tf < niso-1) {
        if (s <= s_tf) {
          scalar_tex[4*i] = s_tf;
          scalar_tex[4*i+1] = (isovalues[i_tf+1] - smin)/ds;
          i++;
        } else {
          i_tf++;
        }
      } else {
        if (s <= s_tf)
          scalar_tex[4*i] = s_tf;
        i++;
      }
    }
    //Tm
    i_tf = niso-1;
    for (int i = w-1; i >= 0; ) {
      //Modified to handle precision error when drawing isosurfaces.
      //float s = (float) i/(w-1);
      float s = (float) (i+1)/(w-1);
      float s_tf = (isovalues[i_tf] - smin)/ds;
      if (i_tf > 0) {
        if (s >= s_tf) {
          scalar_tex[4*i+2] = s_tf;
          scalar_tex[4*i+3] = (isovalues[i_tf-1] - smin)/ds;
          i--;
        } else {
          i_tf--;
        }
      } else {
        if (s >= s_tf)
          scalar_tex[4*i+2] = s_tf;
        i--;
      }
    }
  }

  glPushAttrib(GL_TEXTURE_BIT);
  glActiveTexture(GL_TEXTURE10);
  glBindTexture(GL_TEXTURE_1D, m_isosurf_scalar_obj);
  glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA32F_ARB, w,
               0, GL_RGBA, GL_FLOAT, scalar_tex);
  glPopAttrib();

  delete[] scalar_tex;
}

/**
 * Builds the set of 2D textures containing the tetrahedral mesh.
 * 
 * Each texel contains data corresponding to a tetrahedron with a given
 * index in the mesh. Tetrahedral indices are mapped into two-component 
 * texture coordinates: tid -> (tid_x, tid_y), such that they
 * can be used for 2D texture access.
 *
 * Plane equations (A,B,C,D) of the four faces of each tetrahedron
 * are stored in four 2D textures, one for each face: 
 *   (tid_x, tid_y) -> (A0, B0, C0, D0)
 *   (tid_x, tid_y) -> (A1, B1, C1, D1)
 *   (tid_x, tid_y) -> (A2, B2, C2, D2)
 *   (tid_x, tid_y) -> (A3, B3, C3, D3)
 *
 * Tetrahedral adjacency information, which is used to locate the
 * following tetrahedron to which propagate a ray, is stored in two
 * textures, one for each of the two-component texture
 * coordinates associated to a tetrahedral index. Each of the four 
 * color components stored in a texel contains the component of the
 * index of the tetrahedron adjacent to the ith face of the 
 * tetrahedron corresponding to the texel location:
 *   (tid_x, tid_y) -> (r: tid_face0_x, 
 *                      g: tid_face1_x, 
 *                      b: tid_face2_x, 
 *                      a: tid_face3_x)
 *
 *   (tid_x, tid_y) -> (r: tid_face0_y, 
 *                      g: tid_face1_y, 
 *                      b: tid_face2_y, 
 *                      a: tid_face3_y)
 */
MODEL_CLASS_TEMPLATE
int TpvHARCVolRenderer3<MODELCLASS>::BuildMeshTextures()
{
  static const int F_V0[4] = {1, 2, 3, 0};

  TpvTetrahedronSet* tet = m_geometry->GetTetrahedra();
  int ntetra = tet->GetSize();
  int    w, h, data_alloc;
  float *data, *data2;

  //printf("Building mesh textures...\n");
  // Normals (plane equations of the four tetrahedral faces).
  // gnormi: (tid_x, tid_y) -> (A, B, C, D)
  w = m_max_w;
  h = (ntetra+1)/m_max_w + 1;
  assert(h <= m_max_h);
  data_alloc = 4*w*h;
  data = (float*) malloc(data_alloc*sizeof(float));
  assert(data);
  data[0] = data[1] = data[2] = data[3] = 0.0f;
  unsigned int tex_ids[4] = {GL_TEXTURE12, GL_TEXTURE13, GL_TEXTURE14, GL_TEXTURE15};
  unsigned int tex_objs[4] = {m_gnorm1_obj, m_gnorm2_obj, m_gnorm3_obj, m_gnorm4_obj};
  for (int j = 0; j < 4; j++) {
    for (int i = 0; i < ntetra; i++) {
      float* normal = tet->GetNormal(i, j);
      data[4*(i+1)]   = normal[0];
      data[4*(i+1)+1] = normal[1];
      data[4*(i+1)+2] = normal[2];
      // D = -(P0.n) (usa um nó qualquer da face).
      float* p = tet->GetPosition(i, F_V0[j]);
      data[4*(i+1)+3] = -(p[0]*normal[0] + p[1]*normal[1] + p[2]*normal[2]);
    }

    glPushAttrib(GL_TEXTURE_BIT);
    glActiveTexture(tex_ids[j]);
    glBindTexture(GL_TEXTURE_RECTANGLE_ARB, tex_objs[j]);
    glTexImage2D(GL_TEXTURE_RECTANGLE_ARB, 0, GL_RGBA32F_ARB,
                 w, h, 0, GL_RGBA, GL_FLOAT, data);
    glPopAttrib();
  }

  w = m_max_w;
  h = (ntetra+1)/m_max_w + 1;
  data_alloc = 4*w*h;
  data = (float*) realloc(data, data_alloc*sizeof(float));
  assert(data);
  data2 = (float*) malloc(data_alloc*sizeof(float));
  assert(data2);
  assert(h <= m_max_h);
  assert(sizeof(unsigned int) == sizeof(float));
  data[0] = data[1] = data[2] = data[3] = 0.0f;
  data2[0] = data2[1] = data2[2] = data2[3] = 0.0f;

  // Adjacencies.
  // (tid_x, tid_y) -> (r: a0, g: a1, b: a2, a: a3)
  for (int i = 0; i < ntetra; i++) {
    for (int j = 0; j < 4; j++) {
      int id = tet->GetAdj(i, j);
      unsigned short vi = id/m_max_w;
      unsigned short vj = id%m_max_w;
      data[4*(i+1)+j]  = vj;
      data2[4*(i+1)+j] = vi;
    }
  }

  glPushAttrib(GL_TEXTURE_BIT | GL_ENABLE_BIT);
  glActiveTexture(GL_TEXTURE6);
  BindTextureRectangle(m_tadj_obj, false, false, true, w, h, data);
  glActiveTexture(GL_TEXTURE7);
  BindTextureRectangle(m_tadj2_obj, false, false, true, w, h, data2);
  glPopAttrib();

  free(data);
  free(data2);

  //printf("Mesh textures successfully built.\n");
  return 1;
}

/**
 * Builds the texture containing the gradients of the scalar
 * field for each tetrahedron in the mesh.
 * 
 * Each texel contains data corresponding to a tetrahedron with a given
 * index in the mesh. Tetrahedral indices are mapped into two-component 
 * texture coordinates: tid -> (tid_x, tid_y), such that they
 * can be used for 2D texture access.
 */
MODEL_CLASS_TEMPLATE
void TpvHARCVolRenderer3<MODELCLASS>::BuildPropertyTextures()
{
  TpvTetrahedronSet* tet = m_geometry->GetTetrahedra();
  TpvFloatArray* tet_pos = tet->GetPositions();
  TpvFloatArray* tet_field = tet->GetField();
  int ntetra = tet->GetSize();

  // Gradients of the scalar field inside the tetrahedra.
  // ggrad: (tid_x, tid_y) -> (r: gx, g: gy, b: gz, a: gt)
  // s(X) = dot(Gt,(X-X0)) + s(X0) = dot(Gt,X) + (s(X0)-dot(Gt,X0))
  // X0 = any point in the tetrahedron.
  // gt = s(X0)-dot(Gt,X0)
  int data_alloc = 4*(ntetra+1+m_max_w);
  float* data = (float*) malloc(data_alloc*sizeof(float));
  assert(data);
  data[0] = data[1] = data[2] = data[3] = 0.0f;
  int w = m_max_w;
  int h = (ntetra+1)/m_max_w + 1;
  assert(h <= m_max_h);
  for (int i = 0; i < ntetra; i++) {
    float* p = &(tet_pos->GetArray()[12*i]);
    float* s = &(tet_field->GetArray()[4*i]);
    float gradient[4];
    ComputeGradient(p, s, gradient);
    data[4*(i+1)]   = gradient[0];
    data[4*(i+1)+1] = gradient[1];
    data[4*(i+1)+2] = gradient[2];
    data[4*(i+1)+3] = s[0] - (gradient[0]*p[0] + gradient[1]*p[1] + gradient[2]*p[2]);
  }

  glPushAttrib(GL_TEXTURE_BIT);
  glActiveTexture(GL_TEXTURE4);
  glBindTexture(GL_TEXTURE_RECTANGLE_ARB, m_ggrad_obj);
  glTexImage2D(GL_TEXTURE_RECTANGLE_ARB, 0, GL_RGBA32F_ARB,
               w, h, 0, GL_RGBA, GL_FLOAT, data);
  glPopAttrib();
}

MODEL_CLASS_TEMPLATE
void TpvHARCVolRenderer3<MODELCLASS>::ComputeBdryFaces()
{
  static const int F_N[4][3] = {{1,2,3},{2,0,3},{3,0,1},{1,0,2}};

  TpvTetrahedronSet* tet = m_geometry->GetTetrahedra();
  int ntetra = tet->GetSize();

  m_bdry_elem.Resize(0);
  for (int i = 0; i < ntetra; i++) {
    for (int j = 0; j < 4; j++) {
      if (tet->GetAdj(i, j) == 0) { // Boundary
//TODO: 1-indexed ids.
        m_bdry_elem.Append(i+1);
        break;
      }
    }
  }

  //Create display list.
#ifdef VERBOSE
  printf("Creating boundary faces display list...\n");
#endif
  glPushAttrib(GL_CURRENT_BIT);
  if (!m_bdry_disp_lst) 
    m_bdry_disp_lst = glGenLists(1);
  glNewList(m_bdry_disp_lst, GL_COMPILE);
  for (int i = 0; i < m_bdry_elem.Size(); i++) {
    int tid = m_bdry_elem[i];
    unsigned short tid_x = tid%m_max_w;
    unsigned short tid_y = tid/m_max_w;
    for (int fi = 0; fi < 4; fi++) {
      if (tet->GetAdj(tid-1, fi) == 0) { // Boundary
        // Coordenadas de textura nao sao 32 bits!!!
        glMultiTexCoord2f(GL_TEXTURE0, tid_x, tid_y); // tid
//        glNormal3fv(m_geometry->GetNormal(tetra, j));  // normal
        for (int vi = 0; vi < 3; vi++)
          glVertex3fv(tet->GetPosition(tid-1, F_N[fi][vi]));
      }
    }
  }
  glEndList();
  glPopAttrib();
#ifdef VERBOSE
  printf("Display list created.\n");
#endif
}

// Ensures that geometry and renderer are up-to-date before rendering model.
MODEL_CLASS_TEMPLATE
bool TpvHARCVolRenderer3<MODELCLASS>::Update()
{
  if (!Init())
    return false;

  if (!m_geometry)
    return true;

  if (m_geometry->GetTetrahedra()->GetSize() > m_max_w*m_max_h)
    return false;

  // Geometry
  if (m_update_geometry) {
    m_update_property = true;
  }
  if (m_update_property) {
    m_geometry->SetNormalizeField(m_normalized_field);
    m_geometry->SetField(m_property);
  }
  m_geometry->Update();

  // Renderer
  if (m_update_viewport)
    if (!InitFramebuffer())
      return false;
  if (m_update_geometry) {
    BuildMeshTextures();
    ComputeBdryFaces();
  }
  if (m_update_property)
    BuildPropertyTextures();
  if (m_update_colorscale)
    BuildTransferFuncTextures();

  m_update_geometry = false;
  m_update_property = false;
  m_update_viewport = false;
  m_update_colorscale = false;
  return true;
}



/******************
  public
*******************/
// constructor
MODEL_CLASS_TEMPLATE
TpvHARCVolRenderer3<MODELCLASS>::TpvHARCVolRenderer3()
: m_geometry(NULL)
, m_property(NULL)
, m_colorscale(NULL)
, m_shader1(new CGShader())
, m_shader2(new CGShader())
, m_shader3(new CGShader())
, m_shader2_isosurf(new CGShader())
, m_fb_color0_tex_obj(0)
, m_fb_depth0_tex_obj(0)
, m_fb_obj(0)
, m_fb_tex_obj(0)
, m_fb_tex2_obj(0)
, m_fb_depth_rb_obj(0)
, m_query_obj(0)
, m_gnorm1_obj(0)
, m_gnorm2_obj(0)
, m_gnorm3_obj(0)
, m_gnorm4_obj(0)
, m_ggrad_obj(0)
, m_tadj_obj(0)
, m_tadj2_obj(0)
, m_tf_obj(0)
, m_isosurf_scalar_obj(0)
, m_psi_table_obj(0)
, m_depth_obj(0)
, m_max_w(0)
, m_max_h(0)
, m_initialized(0)
, m_psi_initialized(0)
, m_bdry_disp_lst(0)
, m_clip_plane_enabled(false)
, m_probe_box_enabled(false)
, m_poly_offset_factor(0)
, m_poly_offset_units(0)
, m_poly_offset_enabled(false)
, m_write_depth_enabled(true)
, m_exact_z_enabled(false)
, m_normalized_field(true)
, m_maxedgelength_enabled(true)
, m_isosurfaces_enabled(false)
, m_update_geometry(true)
, m_update_property(true)
, m_update_viewport(true)
, m_update_colorscale(true)
, m_isosurface_values_enabled(false)
{
  m_fb_width = 512;
  m_fb_height = 512;
  m_viewport[0] = m_viewport[1] = m_viewport[2] = m_viewport[3] = 0;
  m_bg_color[0] = m_bg_color[1] = m_bg_color[2] = 0; m_bg_color[3] = 1;

  strcpy(m_shader_path, ".");
  strcpy(m_psi_gamma_path, ".");
  m_psi_gamma_size = 512;

  m_clip_plane[0] = 0.0f;
  m_clip_plane[1] = 0.0f;
  m_clip_plane[2] = 1.0f;
  m_clip_plane[3] = 0.0f;

  m_probe_box[0] = 0.0f; m_probe_box[1] = 1.0f;
  m_probe_box[2] = 0.0f; m_probe_box[3] = 1.0f;
  m_probe_box[4] = 0.0f; m_probe_box[5] = 1.0f;
}

// destructor
MODEL_CLASS_TEMPLATE
TpvHARCVolRenderer3<MODELCLASS>::~TpvHARCVolRenderer3()
{
  if (m_fb_color0_tex_obj) glDeleteTextures(1, &m_fb_color0_tex_obj);
  if (m_fb_depth0_tex_obj) glDeleteTextures(1, &m_fb_depth0_tex_obj);
  if (m_query_obj) glDeleteQueries(1, &m_query_obj);
  if (m_gnorm1_obj)  glDeleteTextures(1, &m_gnorm1_obj);
  if (m_gnorm2_obj)  glDeleteTextures(1, &m_gnorm2_obj);
  if (m_gnorm3_obj)  glDeleteTextures(1, &m_gnorm3_obj);
  if (m_gnorm4_obj)  glDeleteTextures(1, &m_gnorm4_obj);
  if (m_ggrad_obj)  glDeleteTextures(1, &m_ggrad_obj);
  if (m_tadj_obj)   glDeleteTextures(1, &m_tadj_obj);
  if (m_tadj2_obj)   glDeleteTextures(1, &m_tadj2_obj);
  if (m_tf_obj)     glDeleteTextures(1, &m_tf_obj);
  if (m_isosurf_scalar_obj) glDeleteTextures(1, &m_isosurf_scalar_obj);
  if (m_psi_table_obj) glDeleteTextures(1, &m_psi_table_obj);
  if (m_depth_obj) glDeleteTextures(1, &m_depth_obj);

  if (m_fb_tex_obj) glDeleteTextures(1, &m_fb_tex_obj);
  if (m_fb_tex2_obj) glDeleteTextures(1, &m_fb_tex2_obj);
  if (m_fb_obj) glDeleteFramebuffersEXT(1, &m_fb_obj);
  if (m_fb_depth_rb_obj) glDeleteRenderbuffersEXT(1, &m_fb_depth_rb_obj);

  delete m_shader1;
  delete m_shader2;
  delete m_shader3;
  delete m_shader2_isosurf;
}

MODEL_CLASS_TEMPLATE
void TpvHARCVolRenderer3<MODELCLASS>::SetNormalizedField(bool flag)
{
  m_normalized_field = flag;
  m_update_colorscale = true;
  m_update_property = true;
}

MODEL_CLASS_TEMPLATE
void TpvHARCVolRenderer3<MODELCLASS>::SetMaxEdgeLengthEnabled(bool flag)
{
  m_maxedgelength_enabled = flag;
}

MODEL_CLASS_TEMPLATE
void TpvHARCVolRenderer3<MODELCLASS>::SetClippingPlane(float a, float b, float c, float d)
{
  m_clip_plane[0] = a; m_clip_plane[1] = b; m_clip_plane[2] = c; m_clip_plane[3] = d;
  //m_update_clip_plane = true;
}

MODEL_CLASS_TEMPLATE
void TpvHARCVolRenderer3<MODELCLASS>::SetClippingPlaneEnabled(bool flag)
{
  m_clip_plane_enabled = flag;
  //m_update_clip_plane = true;
}

MODEL_CLASS_TEMPLATE
void TpvHARCVolRenderer3<MODELCLASS>::SetPolygonOffset(float factor, float units)
{
  m_poly_offset_factor = factor;
  m_poly_offset_units = units;
}

MODEL_CLASS_TEMPLATE
void TpvHARCVolRenderer3<MODELCLASS>::SetPolygonOffsetEnabled(bool flag)
{
  m_poly_offset_enabled = flag;
}

MODEL_CLASS_TEMPLATE
void TpvHARCVolRenderer3<MODELCLASS>::SetProbeBox(
  float xmin, float xmax, float ymin, float ymax, float zmin, float zmax)
{
  m_probe_box[0] = xmin;
  m_probe_box[1] = xmax;
  m_probe_box[2] = ymin;
  m_probe_box[3] = ymax;
  m_probe_box[4] = zmin;
  m_probe_box[5] = zmax;
}

MODEL_CLASS_TEMPLATE
void TpvHARCVolRenderer3<MODELCLASS>::SetProbeBoxEnabled(bool flag)
{
  m_probe_box_enabled = flag;
}

MODEL_CLASS_TEMPLATE
void TpvHARCVolRenderer3<MODELCLASS>::SetWriteDepthBufferEnabled(bool flag)
{
  m_write_depth_enabled = flag;
}

MODEL_CLASS_TEMPLATE
void TpvHARCVolRenderer3<MODELCLASS>::SetWriteExactZEnabled(bool flag)
{
  m_exact_z_enabled = flag;
}

#define CGSHADER_PATH "../../../src/topsview/renderer/cg"

MODEL_CLASS_TEMPLATE
void TpvHARCVolRenderer3<MODELCLASS>::SetShaderPath(const char* path)
{
  strncpy(m_shader_path, path, 128);
  strncpy(m_psi_gamma_path, path, 128);
  strcat(m_psi_gamma_path, "/PsiGammaTable512.txt");
  m_psi_gamma_size = 512;
}

MODEL_CLASS_TEMPLATE
void TpvHARCVolRenderer3<MODELCLASS>::SetViewport(int x0, int y0, int w, int h)
{
  if (x0 != m_viewport[0] || y0 != m_viewport[1] || 
      w != m_viewport[2] || h != m_viewport[3]) {
    m_viewport[0] = x0; m_viewport[1] = y0; m_viewport[2] = w; m_viewport[3] = h;
    m_update_viewport = true;
  }
}

MODEL_CLASS_TEMPLATE
void TpvHARCVolRenderer3<MODELCLASS>::GetViewport(int* x0, int* y0, int* w, int* h)
{
  *x0 = m_viewport[0]; *y0 = m_viewport[1]; *w = m_viewport[2]; *h = m_viewport[3];
}

MODEL_CLASS_TEMPLATE
void TpvHARCVolRenderer3<MODELCLASS>::SetBackground(float r, float g, float b, float a)
{
  m_bg_color[0] = r; m_bg_color[1] = g; m_bg_color[2] = b; m_bg_color[3] = a;
}

MODEL_CLASS_TEMPLATE
void TpvHARCVolRenderer3<MODELCLASS>::SetGeometry(TpvTetraGeometry3<MODELCLASS>* g)
{
  m_geometry = g;
  m_update_geometry = true;
}

MODEL_CLASS_TEMPLATE
void TpvHARCVolRenderer3<MODELCLASS>::SetGeometryOutdated ()
{
  m_update_geometry = true;
}

MODEL_CLASS_TEMPLATE
void TpvHARCVolRenderer3<MODELCLASS>::SetProperty(TpvProperty* property)
{
  m_property = property;
  m_update_property = true;
}

MODEL_CLASS_TEMPLATE
void TpvHARCVolRenderer3<MODELCLASS>::SetColorScale(TpvColorScale* colorscale)
{
  m_colorscale = colorscale;
  m_update_colorscale = true;
}

MODEL_CLASS_TEMPLATE
void TpvHARCVolRenderer3<MODELCLASS>::SetIsosurfacesEnabled (bool flag)
{
  m_isosurfaces_enabled = flag;
  m_update_colorscale = true;
}

MODEL_CLASS_TEMPLATE
void TpvHARCVolRenderer3<MODELCLASS>::SetIsosurfaceValuesEnabled(bool flag)
{
  m_isosurface_values_enabled = flag;
  m_update_colorscale = true;
}

MODEL_CLASS_TEMPLATE
void TpvHARCVolRenderer3<MODELCLASS>::SetIsosurfaceValues(int n, const float* values)
{
//TODO sort isosurface values
  m_isosurface_values.Clear();
  for (int i = 0; i < n; i++)
    m_isosurface_values.Append(values[i]);
  m_update_colorscale = true;
}

MODEL_CLASS_TEMPLATE
float TpvHARCVolRenderer3<MODELCLASS>::GetMinNormalizedIsosurfaceValueInterval()
{
  return (float) 2.0f / TRANSFER_FUNCTION_TEXTURE_SIZE;
}

// Bind all the textures, but the pbuffers.
MODEL_CLASS_TEMPLATE
void TpvHARCVolRenderer3<MODELCLASS>::LoadTextures()
{
  // Texture 4: gradients.
  glActiveTexture(GL_TEXTURE4);
  BindTextureRectangle(m_ggrad_obj, true);

  // Textures 6 and 7: adjacencies.
  glActiveTexture(GL_TEXTURE6);
  BindTextureRectangle(m_tadj_obj, true);
  glActiveTexture(GL_TEXTURE7);
  BindTextureRectangle(m_tadj2_obj, true);

  // Texture 8 (transfer function).
  glActiveTexture(GL_TEXTURE8);
  glBindTexture(GL_TEXTURE_1D, m_tf_obj);
  glEnable(GL_TEXTURE_1D);
#ifdef TPV_USE_GEFORCE_6200
  glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
#else
  glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
#endif
  glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

  // Texture 10 (isusurf. scalar).
  glActiveTexture(GL_TEXTURE10);
  glBindTexture(GL_TEXTURE_1D, m_isosurf_scalar_obj);
  glEnable(GL_TEXTURE_1D);
  glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  // Texture 11 (psi table).
  glActiveTexture(GL_TEXTURE11);
  glBindTexture(GL_TEXTURE_2D, m_psi_table_obj);
  glEnable(GL_TEXTURE_2D);
#ifdef TPV_USE_GEFORCE_6200
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
#else
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
#endif
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  // Otimizar texturas
  glActiveTexture(GL_TEXTURE12);
  BindTextureRectangle(m_gnorm1_obj, true);
  glActiveTexture(GL_TEXTURE13);
  BindTextureRectangle(m_gnorm2_obj, true);
  glActiveTexture(GL_TEXTURE14);
  BindTextureRectangle(m_gnorm3_obj, true);
  glActiveTexture(GL_TEXTURE15);
  BindTextureRectangle(m_gnorm4_obj, true);

  glActiveTexture(GL_TEXTURE0);
}

MODEL_CLASS_TEMPLATE
bool TpvHARCVolRenderer3<MODELCLASS>::BeginRender()
{
  glPushAttrib(GL_ALL_ATTRIB_BITS);

  if (!Update()) {
    glPopAttrib();
    return false;
  }

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();

  AlgVector eye = VglFrustum().GetEyePos();

  m_shader1->SetConstant(Shader::VP, "EyePosVP",   eye.x, eye.y, eye.z);
  m_shader1->SetConstant(Shader::FP, "EyePosFP",   eye.x, eye.y, eye.z);

//TODO improve code 
  if (m_isosurfaces_enabled) {
    m_shader2_isosurf->SetConstant(Shader::VP, "EyePosVP",   eye.x, eye.y, eye.z);
    m_shader2_isosurf->SetConstant(Shader::FP, "EyePosFP",   eye.x, eye.y, eye.z, 1.0f);
    m_shader2_isosurf->SetConstant(Shader::FP, "Viewport",
      (float) m_viewport[0], (float) m_viewport[1], (float) m_viewport[2], (float) m_viewport[3]);
    m_shader2_isosurf->SetConstant(Shader::FP, "CuttingPlaneEnabled", m_clip_plane_enabled ? 1.0f : 0.0f);
    m_shader2_isosurf->SetConstant(Shader::FP, "CuttingPlane",
      m_clip_plane[0], m_clip_plane[1], m_clip_plane[2], m_clip_plane[3]);

    if (m_colorscale && !m_normalized_field) {
      int niso = m_colorscale->GetNumberOfValues();
      assert(niso > 0);
      float smin = m_colorscale->GetValue(0);
      float smax = m_colorscale->GetValue(niso - 1);
      float ds = smax - smin;
      m_shader2_isosurf->SetConstant(Shader::FP, "ColorScaleMinMax", smin, smax, ds);
    }
    else
      m_shader2_isosurf->SetConstant(Shader::FP, "ColorScaleMinMax", 0.0f, 1.0f, 1.0f);
  }
  else {
    m_shader2->SetConstant(Shader::VP, "EyePosVP",   eye.x, eye.y, eye.z);
    m_shader2->SetConstant(Shader::FP, "EyePosFP",   eye.x, eye.y, eye.z, 1.0f);
    m_shader2->SetConstant(Shader::FP, "MaxLength",  
      m_maxedgelength_enabled ? m_geometry->GetMaxEdgeLength() : 1.0f);
    m_shader2->SetConstant(Shader::FP, "Viewport",
      (float) m_viewport[0], (float) m_viewport[1], (float) m_viewport[2], (float) m_viewport[3]);
    m_shader2->SetConstant(Shader::FP, "CuttingPlaneEnabled", m_clip_plane_enabled ? 1.0f : 0.0f);
    m_shader2->SetConstant(Shader::FP, "CuttingPlane",
      m_clip_plane[0], m_clip_plane[1], m_clip_plane[2], m_clip_plane[3]);

    if (m_colorscale && !m_normalized_field) {
      int niso = m_colorscale->GetNumberOfValues();
      assert(niso > 0);
      float smin = m_colorscale->GetValue(0);
      float smax = m_colorscale->GetValue(niso - 1);
      float ds = smax - smin;
      m_shader2->SetConstant(Shader::FP, "ColorScaleMinMax", smin, smax, ds);
    }
    else
      m_shader2->SetConstant(Shader::FP, "ColorScaleMinMax", 0.0f, 1.0f, 1.0f);
    m_shader2->SetConstant(Shader::FP, "ProbeBoxEnabled", m_probe_box_enabled ? 1.0f : 0.0f);
    bool const_interp = m_colorscale->GetInterpolationMode() != TpvColorScale::INTERP_LINEAR;
    m_shader2->SetConstant(Shader::FP, "ConstantInterpEnabled", const_interp ? 1.0f : 0.0f);
    m_shader2->SetConstant(Shader::FP, "ProbeBoxMin",
      m_probe_box[0], m_probe_box[2], m_probe_box[4]);
    m_shader2->SetConstant(Shader::FP, "ProbeBoxMax",
      m_probe_box[1], m_probe_box[3], m_probe_box[5]);
  }

  //m_shader3->SetConstant(Shader::FP, "BGColor", m_bg_color[0], m_bg_color[1], m_bg_color[2], m_bg_color[3]);
  m_shader3->SetConstant(Shader::FP, "Viewport",
    (float) m_viewport[0], (float) m_viewport[1], (float) m_viewport[2], (float) m_viewport[3]);

  LoadTextures();
  return true;
}

MODEL_CLASS_TEMPLATE
bool TpvHARCVolRenderer3<MODELCLASS>::EndRender()
{
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
  glPopAttrib();
  return true;
}

MODEL_CLASS_TEMPLATE
void TpvHARCVolRenderer3<MODELCLASS>::DrawFirstPass(
  GLint* viewport, double* projection, double* modelview, int pass)
{
  glPushAttrib(GL_TEXTURE_BIT);
  glActiveTexture(GL_TEXTURE9);

  if (pass == 0) {
    // Initializes first peel. The z-buffer is marked as if
    // the last peel had all the faces on the nearest z (z = 0).
    float depth_data[4] = {0,0,0,0};
    BindDepthTextureRectangle(m_depth_obj, true, true, true, 2, 2, depth_data);
  } else
    BindDepthTextureRectangle(m_depth_obj, true, false, false, 0, 0, NULL);

  glViewport(0, 0, viewport[2], viewport[3]);
  glMatrixMode(GL_PROJECTION);
  glLoadMatrixd(projection);
  glMatrixMode(GL_MODELVIEW);
  glLoadMatrixd(modelview);

  glDepthMask(GL_TRUE);
// Nao pode limpar o color buffer...
  //glClearColor(0.0, 0.0, 0.0, 0.0);
  //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClear(GL_DEPTH_BUFFER_BIT);
  glDepthFunc(GL_LESS);
  glEnable(GL_DEPTH_TEST);
  glFrontFace(GL_CCW);
  glCullFace(GL_BACK);
  glEnable(GL_CULL_FACE);

  m_shader1->BindTexture("FramebufferDepth0Tex", m_fb_depth0_tex_obj);
  m_shader1->BindTexture("FramebufferTex0", m_fb_tex_obj);
  m_shader1->BindTexture("FramebufferTex1", m_fb_tex2_obj);
  m_shader1->BindTexture("DepthTex", m_depth_obj);
  m_shader1->SetConstant(Shader::FP, "PassNumber", (float) pass);

#ifdef VERBOSE
  printf("Loading shader 1...\n");
#endif
  m_shader1->Load();
#ifdef VERBOSE
  printf("Shader 1 loaded.\n");
#endif
  glBegin(GL_TRIANGLES);
  if (m_bdry_disp_lst)
    glCallList(m_bdry_disp_lst);
  glEnd();
  m_shader1->Unload();

  // Copy the depth buffer to a texture.
  glActiveTexture(GL_TEXTURE9);
  glBindTexture(GL_TEXTURE_RECTANGLE_ARB, m_depth_obj);
  glCopyTexImage2D(GL_TEXTURE_RECTANGLE_ARB, 0, GL_DEPTH_COMPONENT24,
      0, 0, viewport[2], viewport[3], 0);
  glPopAttrib();

  glClear(GL_DEPTH_BUFFER_BIT);
  glDepthMask(GL_FALSE);
}

MODEL_CLASS_TEMPLATE
void TpvHARCVolRenderer3<MODELCLASS>::DrawIntermediatePass(
  GLint* viewport, double* projection, double* modelview, 
  double frustum_near[4][3], int pass)
{
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glEnable(GL_CULL_FACE);
  glViewport(0, 0, viewport[2], viewport[3]);

  AlgMatrix mvp(projection);
  mvp.Accum(AlgMatrix(modelview));

  glMatrixMode(GL_TEXTURE); // Pass ModelViewProj as texture.
  glPushMatrix();
  glLoadMatrixf(mvp.GetMatrix());

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, 1.0, 0.0, 1.0, 1.0, -1.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

//TODO improve code 
  if (m_isosurfaces_enabled) {
    m_shader2_isosurf->BindTexture("FramebufferDepth0Tex", m_fb_depth0_tex_obj);
    m_shader2_isosurf->BindTexture("FramebufferTex0", m_fb_tex_obj);
    m_shader2_isosurf->BindTexture("FramebufferTex1", m_fb_tex2_obj);
    m_shader2_isosurf->SetConstant(Shader::FP, "PassNumber", (float) pass);
  }
  else {
    m_shader2->BindTexture("FramebufferDepth0Tex", m_fb_depth0_tex_obj);
    m_shader2->BindTexture("FramebufferTex0", m_fb_tex_obj);
    m_shader2->BindTexture("FramebufferTex1", m_fb_tex2_obj);
    m_shader2->SetConstant(Shader::FP, "PassNumber", (float) pass);
  }

#ifdef VERBOSE
  printf("Loading shader 2...\n");
#endif
//TODO improve code 
  if (m_isosurfaces_enabled)
    m_shader2_isosurf->Load();
  else
    m_shader2->Load();
#ifdef VERBOSE
  printf("Shader 2 loaded.\n");
#endif
  glBegin(GL_QUADS);
    glMultiTexCoord3f(GL_TEXTURE0,
        (float) frustum_near[0][0], (float) frustum_near[0][1], (float) frustum_near[0][2]);
    glVertex3f(0.0f, 0.0f, 0.5f);
    glMultiTexCoord3f(GL_TEXTURE0,
        (float) frustum_near[1][0], (float) frustum_near[1][1], (float) frustum_near[1][2]);
    glVertex3f(1.0f, 0.0f, 0.5f);
    glMultiTexCoord3f(GL_TEXTURE0,
        (float) frustum_near[2][0], (float) frustum_near[2][1], (float) frustum_near[2][2]);
    glVertex3f(1.0f, 1.0f, 0.5f);
    glMultiTexCoord3f(GL_TEXTURE0,
        (float) frustum_near[3][0], (float) frustum_near[3][1], (float) frustum_near[3][2]);
    glVertex3f(0.0f, 1.0f, 0.5f);
  glEnd();
//TODO improve code 
  if (m_isosurfaces_enabled) 
    m_shader2_isosurf->Unload();
  else
    m_shader2->Unload();

  glMatrixMode(GL_TEXTURE);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
}

MODEL_CLASS_TEMPLATE
void TpvHARCVolRenderer3<MODELCLASS>::DrawFinalPass()
{
  if (m_write_depth_enabled && m_exact_z_enabled) {
    glDepthMask(GL_TRUE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_ALWAYS);
  }
  else {
    glDepthMask(GL_FALSE);
    glDisable(GL_DEPTH_TEST);
  }
  glEnable(GL_CULL_FACE);

  glViewport(m_viewport[0], m_viewport[1], m_viewport[2], m_viewport[3]);
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluOrtho2D(0.0, 1.0, 0.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

  m_shader3->BindTexture("FramebufferColor0Tex", m_fb_color0_tex_obj);
  m_shader3->BindTexture("FramebufferTex0", m_fb_tex_obj);
  m_shader3->BindTexture("FramebufferTex1", m_fb_tex2_obj);

#ifdef VERBOSE
  printf("Loading shader 3...\n");
#endif
  m_shader3->Load();
#ifdef VERBOSE
  printf("Shader 3 loaded.\n");
#endif
  glBegin(GL_QUADS);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(1.0f, 0.0f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(0.0f, 1.0f);
  glEnd();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
  m_shader3->Unload();
}

MODEL_CLASS_TEMPLATE
void TpvHARCVolRenderer3<MODELCLASS>::DrawFrontFacesDepths()
{
  //glClear(GL_DEPTH_BUFFER_BIT);
  if (m_write_depth_enabled) {
    if (m_clip_plane_enabled)
      glEnable(GL_CLIP_PLANE0);
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    glDepthMask(GL_TRUE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    if (m_poly_offset_enabled) {
      glPolygonOffset(m_poly_offset_factor, m_poly_offset_units);
      glEnable(GL_POLYGON_OFFSET_FILL);
    }
    glBegin(GL_TRIANGLES);
    if (m_bdry_disp_lst)
      glCallList(m_bdry_disp_lst);
    glEnd();
  }
}

// The same approach as "gpurt_renderer.cpp".
// Keeps the same context for all the intermediate passes.
// Uses dynamic loops.
MODEL_CLASS_TEMPLATE
void TpvHARCVolRenderer3<MODELCLASS>::Render()
{
  assert(glGetError() == GL_NO_ERROR);
  assert(cgGetError() == CG_NO_ERROR);

  GLint viewport[4] = {m_viewport[0], m_viewport[1], m_viewport[2], m_viewport[3]};
  double modelview[16];
  glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
  double projection[16];
  glGetDoublev(GL_PROJECTION_MATRIX, projection);

  if (!BeginRender())
    return;
  
  if (m_clip_plane_enabled)
    glDisable(GL_CLIP_PLANE0);

  // Computes the 4 vertices of the near plane (the projection plane).
  double frustum_near[4][3]; // bl, br, tr, tl
  ComputeFrustumNear(viewport, modelview, projection, frustum_near);

  // Saves background frame buffer to be used for comparison and composition.
  glActiveTexture(GL_TEXTURE2);    
  BindTextureRectangle(m_fb_color0_tex_obj, true, true, false, 0, 0, NULL);  
  glCopyTexSubImage2D(GL_TEXTURE_RECTANGLE_ARB, 0, 0, 0, 
    viewport[0], viewport[1], viewport[2], viewport[3]);

  glActiveTexture(GL_TEXTURE3);    
  BindDepthTextureRectangle(m_fb_depth0_tex_obj, true, true, false, 0, 0, NULL); 
  glCopyTexSubImage2D(GL_TEXTURE_RECTANGLE_ARB, 0, 0, 0,
      viewport[0], viewport[1], viewport[2], viewport[3]);

  GLint old_fb_obj;
  glGetIntegerv(GL_FRAMEBUFFER_BINDING_EXT, &old_fb_obj);
  glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_fb_obj);

  glPushAttrib(GL_COLOR_BUFFER_BIT);
  GLenum buffers[] = {GL_COLOR_ATTACHMENT0_EXT, GL_COLOR_ATTACHMENT1_EXT};
  glDrawBuffers(2, buffers);

  glActiveTexture(GL_TEXTURE0);
  glEnable(GL_TEXTURE_RECTANGLE_ARB);

  glDepthMask(GL_TRUE);
  glClearColor(0,0,0,0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glDepthMask(GL_FALSE);

  // Maximum number of peels = 256.
  for (int i = 0; i < 256; i++) {
    // First pass.
    // Draws front faces to find the mesh entry of the current peel.
    GLint query_count = 0; // Occlusion query flag.
    glBeginQuery(GL_SAMPLES_PASSED, m_query_obj);
      DrawFirstPass(viewport, projection, modelview, i);
    glEndQuery(GL_SAMPLES_PASSED);
    glGetQueryObjectiv(m_query_obj, GL_QUERY_RESULT, &query_count);
    if (query_count == 0)
      break;
    // Intermediate passes.
    // Traverses tetrahedra of the current peel.
    DrawIntermediatePass(viewport, projection, modelview, frustum_near, i);
  }

  glPopAttrib();

  glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, old_fb_obj);

  // Final pass.
  // Copy results to the frame buffer.
  DrawFinalPass();

  // Writes front faces to z-buffer.
  if (m_write_depth_enabled && !m_exact_z_enabled)
    DrawFrontFacesDepths();

  EndRender();
  assert(cgGetError() == CG_NO_ERROR);
  assert(glGetError() == GL_NO_ERROR);
}
