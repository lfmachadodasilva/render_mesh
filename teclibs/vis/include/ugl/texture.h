// Texture class
// celes@tecgraf.puc-rio.br
// fabraham@tecgraf.puc-rio.br
// Jul 2002

#ifndef UGL_TEXTURE_H
#define UGL_TEXTURE_H

#include <GL/glew.h>
#include "defines.h"
#include <alg/matrix.h>

class UGLWriter;

class UGL_API UGLTexture
{
public:
  UGLTexture ();
  virtual ~UGLTexture();
  /**
  * Sets 1D texture data.
  * Allowed formats: GL_RGB, GL_RGBA, GL_LUMINANCE, GL_ALPHA, GL_LUMINANCE_ALPHA.
  * Allowed types: GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, GL_UNSIGNED_INT, GL_FLOAT.
  * Data sizes must be:
  *   GL_RGB:             3*width*sizeof(type)
  *   GL_RGBA:            4*width*sizeof(type)
  *   GL_LUMINANCE:       1*width*sizeof(type)
  *   GL_ALPHA:           1*width*sizeof(type)
  *   GL_LUMINANCE_ALPHA: 2*width*sizeof(type)
  *   GL_DEPTH_COMPONENT: 1*width*sizeof(type)
   * Internal format is set to be the same as 'format'.
  * 'takeownership' specifies if the data pointer can be used directly. if true, memory must have been allocated with m/calloc.
  */
  bool SetData1D (int width,
                  unsigned int format,
                  unsigned int type,
                  void* data,
                  bool takeownership = false,
                  bool border = false,
                  bool isopaque = true)
  {
    return SetData1D(width,
                     format,
                     format,
                     type,
                     data,
                     takeownership,
                     border,
                     isopaque);
  }
  /**
  * Sets 1D texture data.
  * Allowed formats: GL_RGB, GL_RGBA, GL_LUMINANCE, GL_ALPHA, GL_LUMINANCE_ALPHA.
  * Allowed types: GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, GL_UNSIGNED_INT, GL_FLOAT.
  * Data sizes must be:
  *   GL_RGB:             3*width*sizeof(type)
  *   GL_RGBA:            4*width*sizeof(type)
  *   GL_LUMINANCE:       1*width*sizeof(type)
  *   GL_ALPHA:           1*width*sizeof(type)
  *   GL_LUMINANCE_ALPHA: 2*width*sizeof(type)
  *   GL_DEPTH_COMPONENT: 1*width*sizeof(type)
   * 'iformat' is the internal texture format and can be one of the following constants:
   * GL_ALPHA, GL_ALPHA4, GL_ALPHA8, GL_ALPHA12, GL_ALPHA16, GL_COMPRESSED_ALPHA,
   * GL_COMPRESSED_LUMINANCE, GL_COMPRESSED_LUMINANCE_ALPHA, GL_COMPRESSED_INTENSITY,
   * GL_COMPRESSED_RGB, GL_COMPRESSED_RGBA, GL_LUMINANCE, GL_LUMINANCE4, GL_LUMINANCE8,
   * GL_LUMINANCE12, GL_LUMINANCE16, GL_LUMINANCE_ALPHA, GL_LUMINANCE4_ALPHA4,
   * GL_LUMINANCE6_ALPHA2, GL_LUMINANCE8_ALPHA8, GL_LUMINANCE12_ALPHA4,
   * GL_LUMINANCE12_ALPHA12, GL_LUMINANCE16_ALPHA16, GL_INTENSITY, GL_INTENSITY4,
   * GL_INTENSITY8, GL_INTENSITY12, GL_INTENSITY16, GL_R3_G3_B2, GL_RGB, GL_RGB4,
   * GL_RGB5, GL_RGB8, GL_RGB10, GL_RGB12, GL_RGB16, GL_RGBA, GL_RGBA2, GL_RGBA4,
   * GL_RGB5_A1, GL_RGBA8, GL_RGB10_A2, GL_RGBA12, GL_RGBA16, GL_SLUMINANCE,
   * GL_SLUMINANCE8, GL_SLUMINANCE_ALPHA, GL_SLUMINANCE8_ALPHA8, GL_SRGB, GL_SRGB8,
   * GL_SRGB_ALPHA, or GL_SRGB8_ALPHA8.
  * 'takeownership' specifies if the data pointer can be used directly. if true, memory must have been allocated with m/calloc.
  */
  bool SetData1D (int width,
                  unsigned int format,
                  unsigned int iformat,
                  unsigned int type,
                  void* data,
                  bool takeownership = false,
                  bool border = false,
                  bool isopaque = true);
  /**
   * Sets 2D texture data.
   * Allowed formats: GL_RGB, GL_RGBA, GL_LUMINANCE, GL_ALPHA, GL_LUMINANCE_ALPHA, GL_DEPTH_COMPONENT.
   * Allowed types: GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, GL_UNSIGNED_INT, GL_FLOAT.
   * Data sizes must be:
   *   GL_RGB:             3*width*height*sizeof(type)
   *   GL_RGBA:            4*width*height*sizeof(type)
   *   GL_LUMINANCE:       1*width*height*sizeof(type)
   *   GL_ALPHA:           1*width*height*sizeof(type)
   *   GL_LUMINANCE_ALPHA: 2*width*height*sizeof(type)
   *   GL_DEPTH_COMPONENT: 1*width*height*sizeof(type)
   * 'takeownership' specifies if the data pointer can be used directly. if true, memory must have been allocated with m/calloc.
   * Internal format is set to be the same as 'format'.
   */
  bool SetData2D (int width,
                  int height,
                  unsigned int format,
                  unsigned int type,
                  void* data,
                  bool takeownership = false,
                  bool border = false,
                  bool isopaque = true)
  {
    return SetData2D(width,
                     height,
                     format,
                     format,
                     type,
                     data,
                     takeownership,
                     border,
                     isopaque);
  }
  /**
   * Sets 2D texture data.
   * Allowed formats: GL_RGB, GL_RGBA, GL_LUMINANCE, GL_ALPHA, GL_LUMINANCE_ALPHA, GL_DEPTH_COMPONENT
   * Allowed types: GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, GL_UNSIGNED_INT, GL_FLOAT
   * Data sizes must be:
   *   GL_RGB:             3*width*height*sizeof(type)
   *   GL_RGBA:            4*width*height*sizeof(type)
   *   GL_LUMINANCE:       1*width*height*sizeof(type)
   *   GL_ALPHA:           1*width*height*sizeof(type)
   *   GL_LUMINANCE_ALPHA: 2*width*height*sizeof(type)
   *   GL_DEPTH_COMPONENT: 1*width*height*sizeof(type)
   * 'iformat' is the internal texture format and can be one of the following constants:
   * GL_ALPHA, GL_ALPHA4, GL_ALPHA8, GL_ALPHA12, GL_ALPHA16, GL_COMPRESSED_ALPHA,
   * GL_COMPRESSED_LUMINANCE, GL_COMPRESSED_LUMINANCE_ALPHA, GL_COMPRESSED_INTENSITY,
   * GL_COMPRESSED_RGB, GL_COMPRESSED_RGBA, GL_LUMINANCE, GL_LUMINANCE4, GL_LUMINANCE8,
   * GL_LUMINANCE12, GL_LUMINANCE16, GL_LUMINANCE_ALPHA, GL_LUMINANCE4_ALPHA4,
   * GL_LUMINANCE6_ALPHA2, GL_LUMINANCE8_ALPHA8, GL_LUMINANCE12_ALPHA4,
   * GL_LUMINANCE12_ALPHA12, GL_LUMINANCE16_ALPHA16, GL_INTENSITY, GL_INTENSITY4,
   * GL_INTENSITY8, GL_INTENSITY12, GL_INTENSITY16, GL_R3_G3_B2, GL_RGB, GL_RGB4,
   * GL_RGB5, GL_RGB8, GL_RGB10, GL_RGB12, GL_RGB16, GL_RGBA, GL_RGBA2, GL_RGBA4,
   * GL_RGB5_A1, GL_RGBA8, GL_RGB10_A2, GL_RGBA12, GL_RGBA16, GL_SLUMINANCE,
   * GL_SLUMINANCE8, GL_SLUMINANCE_ALPHA, GL_SLUMINANCE8_ALPHA8, GL_SRGB, GL_SRGB8,
   * GL_SRGB_ALPHA, or GL_SRGB8_ALPHA8.
   * 'takeownership' specifies if the data pointer can be used directly. if true, memory must have been allocated with m/calloc.
   */
  bool SetData2D (int width,
                  int height,
                  unsigned int format,
                  unsigned int iformat,
                  unsigned int type,
                  void* data,
                  bool takeownership = false,
                  bool border = false,
                  bool isopaque = true);
  /**
   * Replaces part or all of a 2D texture data.
   * Allowed formats: GL_RGB, GL_RGBA, GL_LUMINANCE, GL_LUMINANCE_ALPHA.
   * Allowed types: GL_UNSIGNED_BYTE, GL_FLOAT.
   * Data sizes must be:
   *   GL_RGB:             3*width*height*sizeof(type)
   *   GL_RGBA:            4*width*height*sizeof(type)
   *   GL_LUMINANCE:       width*height*sizeof(type)
   *   GL_LUMINANCE_ALPHA: 2*width*height*sizeof(type)
   *   GL_DEPTH_COMPONENT: 1*width*height*sizeof(type)
   * 'takeownership' specifies if the data pointer can be used directly. if true, memory must have been allocated with m/calloc.
   */
  bool SetSubData2D (int xoffset, int yoffset, int width, int height, unsigned int format, unsigned int type, const void *data);
  /**
   * Sets 3D texture data.
   * Allowed formats: GL_RGB, GL_RGBA, GL_LUMINANCE, GL_ALPHA, GL_LUMINANCE_ALPHA, GL_DEPTH_COMPONENT.
   * Allowed types: GL_UNSIGNED_BYTE, GL_FLOAT.
   * Data sizes must be:
   *   GL_RGB:             3*width*height*depth*sizeof(type)
   *   GL_RGBA:            4*width*height*depth*sizeof(type)
   *   GL_LUMINANCE:       1*width*height*depth*sizeof(type)
   *   GL_ALPHA:           1*width*height*depth*sizeof(type)
   *   GL_LUMINANCE_ALPHA: 2*width*height*depth*sizeof(type)
   * 'takeownership' specifies if the data pointer can be used directly. if true, memory must have been allocated with m/calloc.
   * Internal format is set to be the same as 'format'.
   */
  bool SetData3D (int width,
                  int height,
                  int depth,
                  unsigned int format,
                  unsigned int type,
                  void* data,
                  bool takeownership = false,
                  bool border = false,
                  bool isopaque = true)
  {
    return SetData3D(width,
                     height,
                     depth,
                     format,
                     format,
                     type,
                     data,
                     takeownership,
                     border,
                     isopaque);
  }
  /**
   * Sets 3D texture data.
   * Allowed formats: GL_RGB, GL_RGBA, GL_LUMINANCE, GL_ALPHA, GL_LUMINANCE_ALPHA, GL_DEPTH_COMPONENT.
   * Allowed types: GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, GL_UNSIGNED INT, GL_FLOAT.
   * Data sizes must be:
   *   GL_RGB:             3*width*height*depth*sizeof(type)
   *   GL_RGBA:            4*width*height*depth*sizeof(type)
   *   GL_LUMINANCE:       1*width*height*depth*sizeof(type)
   *   GL_ALPHA:           1*width*height*depth*sizeof(type)
   *   GL_LUMINANCE_ALPHA: 2*width*height*depth*sizeof(type)
   * 'iformat' is the internal texture format and can be one of the following constants:
   * GL_ALPHA, GL_ALPHA4, GL_ALPHA8, GL_ALPHA12, GL_ALPHA16, GL_COMPRESSED_ALPHA,
   * GL_COMPRESSED_LUMINANCE, GL_COMPRESSED_LUMINANCE_ALPHA, GL_COMPRESSED_INTENSITY,
   * GL_COMPRESSED_RGB, GL_COMPRESSED_RGBA, GL_LUMINANCE, GL_LUMINANCE4, GL_LUMINANCE8,
   * GL_LUMINANCE12, GL_LUMINANCE16, GL_LUMINANCE_ALPHA, GL_LUMINANCE4_ALPHA4,
   * GL_LUMINANCE6_ALPHA2, GL_LUMINANCE8_ALPHA8, GL_LUMINANCE12_ALPHA4,
   * GL_LUMINANCE12_ALPHA12, GL_LUMINANCE16_ALPHA16, GL_INTENSITY, GL_INTENSITY4,
   * GL_INTENSITY8, GL_INTENSITY12, GL_INTENSITY16, GL_R3_G3_B2, GL_RGB, GL_RGB4,
   * GL_RGB5, GL_RGB8, GL_RGB10, GL_RGB12, GL_RGB16, GL_RGBA, GL_RGBA2, GL_RGBA4,
   * GL_RGB5_A1, GL_RGBA8, GL_RGB10_A2, GL_RGBA12, GL_RGBA16, GL_SLUMINANCE,
   * GL_SLUMINANCE8, GL_SLUMINANCE_ALPHA, GL_SLUMINANCE8_ALPHA8, GL_SRGB, GL_SRGB8,
   * GL_SRGB_ALPHA, or GL_SRGB8_ALPHA8.
   * 'takeownership' specifies if the data pointer can be used directly. if true, memory must have been allocated with m/calloc.
   */
  bool SetData3D (int width,
                  int height,
                  int depth,
                  unsigned int format,
                  unsigned int iformat,
                  unsigned int type,
                  void* data,
                  bool takeownership = false,
                  bool border = false,
                  bool isopaque = true);
  /**
   * Uses glCopyTexImage2D to fill a 2D texture.
   * 'dim' specifies the texture mode. The usual is GL_TEXTURE_2D.
   * Allowed formats: GL_RGB, GL_RGBA.
   * 'x', 'y', 'w' and 'h' specifies the image region.
   * 'read_buffer' specifies which read buffer to use. The default value is to use the currently bound read buffer.
   */
  void CopyImage (int dim, unsigned int format, int x, int y, int w, int h, GLenum read_buffer = -1);
  const void* GetData ();
  /**
   * Obtains the texture object's name (id).
   * In case the texture was not previously setup, sets its parameters.
   * - requires the GL state in which the texture was set be loaded.
   */
  unsigned int GetTextureId ();
  /**
   * Manually sets the texture unit into which this texture will be loaded.
   *
   * If done, this texture will not participate in automatic texture unit setup.
   * It is not recommended to use textures with automatic unit setup along with textures
   * with manual unit setup.
   */
  void SetUnit (int unit)
  {
    m_userunit = unit;
  }
  /**
   * Gets the texture unit manually set with SetUnit()
   */
  int GetUnit ()
  {
    return m_userunit;
  }
  /**
   * Gets the texture unit where the texture is currently loaded
   * (either manually specified or automatically determined).
   * Result is undefined if the texture is not currently loaded.
   */
  int GetLoadedUnit ()
  {
    return m_loadedunit;
  }
  void SetWidth (int w, int origwidth=-1)
  {
    m_width = w;
    if (origwidth >= 0)
      m_origwidth = origwidth;
    else
      m_origwidth = w;
  }
  int GetWidth () const
  {
    return m_width;
  }
  int GetOriginalWidth () const
  {
    return m_origwidth;
  }
  void SetHeight (int h, int origheight=-1)
  {
    m_height = h;
    if (origheight >= 0)
      m_origheight = origheight;
    else
      m_origheight = h;
  }
  int GetHeight () const
  {
    return m_height;
  }
  int GetOriginalHeight () const
  {
    return m_origheight;
  }
  void SetDepth (int d)
  {
    m_depth = d;
  }
  int GetDepth () const
  {
    return m_depth;
  }
  void SetBorder (bool b)
  {
    m_border = (b) ? 1 : 0;
  }
  int GetBorder () const
  {
    return m_border;
  }
  void SetFormat (int f)
  {
    m_format = f;
  }
  int GetFormat () const
  {
    return m_format;
  }
  void SetInternalFormat (int f)
  {
    m_iformat = f;
  }
  void SetTextureCompression (bool compress)
  {
    m_compress = compress;
  }
  void SetWrap (int s, int t, int r=GL_REPEAT, bool clampMeansEdge = true);
  void GetWrap (int*s, int*t, int*r) const
  {
    *s = m_swrap;
    *t = m_twrap;
    *r = m_rwrap;
  }
  /**
   * Specifies the minification and magnification filters
   * and if mipmapping should be enabled.
   * Possible values for 'min' are:
   * - GL_NEAREST
   * - GL_LINEAR
   * Possible values for 'mag' are:
   * - GL_NEAREST
   * - GL_LINEAR
   * - GL_NEAREST_MIPMAP_NEAREST
   * - GL_NEAREST_MIPMAP_LINEAR
   * - GL_LINEAR_MIPMAP_NEAREST
   * - GL_LINEAR_MIPMAP_LINEAR
   */
  void SetFilter (int min, int mag, bool mipmap=false)
  {
    m_minfilter = min;
    m_magfilter = mag;
    m_mipmap    = mipmap;
    m_updated   = false;
  }
  void GetFilter (int*min, int*mag, bool*mipmap) const
  {
    *min = m_minfilter;
    *mag = m_magfilter;
    *mipmap = m_mipmap;
  }
  int GetTarget () const
  {
    return m_dim;
  }
  void SetEnvMode (int mode)
  {
    m_envmode = mode;
  }
  int GetEnvMode () const
  {
    return m_envmode;
  }
  void SetEnvColor (float red, float green, float blue, float alpha=1.0f)
  {
    m_envcolor[0] = red;
    m_envcolor[1] = green;
    m_envcolor[2] = blue;
    m_envcolor[3] = alpha;
  }
  void GetEnvColor (float*red, float*green, float*blue, float*alpha) const
  {
    *red = m_envcolor[0];
    *green = m_envcolor[1];
    *blue = m_envcolor[2];
    *alpha = m_envcolor[3];
  }
  void SetDepthParams (int depthtexmode);
  void SetShadow (int comparemode, int comparefunc);
  void SetGenTexS (int mode, float a=0, float b=0, float c=0, float d=0);
  void SetGenTexT (int mode, float a=0, float b=0, float c=0, float d=0);
  void SetGenTexR (int mode, float a=0, float b=0, float c=0, float d=0);
  void SetGenTexQ (int mode, float a=0, float b=0, float c=0, float d=0);
  int GetGenTexModeS () const
  {
    return m_sgenmode;
  }
  int GetGenTexModeT () const
  {
    return m_tgenmode;
  }
  int GetGenTexModeR () const
  {
    return m_rgenmode;
  }
  int GetGenTexModeQ () const
  {
    return m_qgenmode;
  }
  const float* GetGenTexPlaneS () const
  {
    return m_sgenplane;
  }
  const float* GetGenTexPlaneT () const
  {
    return m_tgenplane;
  }
  const float* GetGenTexPlaneR () const
  {
    return m_rgenplane;
  }
  const float* GetGenTexPlaneQ () const
  {
    return m_qgenplane;
  }
  void DisableGenTexS ()
  {
    SetGenTexS(0);
  }
  void DisableGenTexT ()
  {
    SetGenTexT(0);
  }
  void DisableGenTexR ()
  {
    SetGenTexR(0);
  }
  void DisableGenTexQ ()
  {
    SetGenTexQ(0);
  }
  /**
   * Resets the texture coordinates transformation.
   */
  void LoadIdentity ();
  /**
   * Accumulates a translation into the texture coordinates transformation.
   */
  void Translate (float x, float y, float z);
  /**
   * Accumulates a translation into the texture coordinates transformation.
   */
  void Translate (const AlgVector& v);
  /**
   * Accumulates a rotation into the texture coordinates transformation.
   */
  void Rotate (float angle, float x, float y, float z);
  /**
   * Accumulates a rotation into the texture coordinates transformation.
   */
  void Rotate (AlgQuatern& q);
  /**
   * Accumulates a scale into the texture coordinates transformation.
   */
  void Scale (float x, float y, float z);
  /**
   * Accumulates a scale into the texture coordinates transformation.
   */
  void Scale (AlgVector& s);
  /**
   * Accumulates an uniform scale into the texture coordinates transformation.
   */
  void Scale (float s);
  /**
   * Sets the texture coordinates transformation.
   */
  void SetTransform (const AlgMatrix& matrix);
  /**
   * Accumulates an arbitrary matrix into the texture coordinates transformation.
   */
  void Transform (const AlgMatrix& matrix);
  /**
   * Checks whether there is a texture coordinates transformation.
   */
  bool HasTransform () const;
  /**
   * Obtains the texture coordinates transformation matrix.
   */
  const AlgMatrix GetTransform () const;
  static float GetMaxAnisotropy ();
  void SetAnisotropy (float anisotropy);
  float GetAnisotropy () const
  {
    return m_anisotropy;
  }
  /**
   * Force the update of the texture object state.
   * Useful when computation and transfers must be done before an user interface pops up.
   */
  void Update ();
  /**
   * Binds the texture object with the active GL state.
   * It will be bound into the next available texture unit if all textures are bound with this utility.
   * - requires the OpenGL state in which the texture was created, and it must be active.
   */
  void Load ();
  /**
   * Unbinds the Load'ed texture, restoring the GL state prior to loading.
   */
  void Unload ();
  /**
   * Is this texture opaque or translucent?
   */
  bool IsOpaque () const;
  /**
   * Set texture opacity status.
   */
  void SetOpaque (bool isopaque)
  {
    m_isopaque = isopaque;
  }
  /**
   * Sets texture as opaque, although it contains texels with alphas different
   * than 0 or 1.
   * Alpha blending will be enabled when the texture is loaded.
   */
  void SetConsiderOpaque ()
  {
    SetOpaque(true);
    m_consider_opaque = true;
  }
  /**
   * Is considering texture as opaque, although it contains texels with alphas
   * different than 0 or 1 ?
   */
  bool IsConsiderOpaque () const
  {
    return m_consider_opaque;
  }
  /**
   * Reserves and frees texture units for use by external texture objects.
   * Must be used as "push" and "pop" methods around texture-loading functions.
   */
  static void ReserveTextureUnits (int quantity);
  static void FreeTextureUnits    (int quantity);

protected:
  void AssertMatrix ();
  virtual void SetParameters ();
  void Cleanup ();

private:
  GLuint m_id;
  int m_userunit;
  int m_loadedunit;
  int m_source;
  int m_dim;
  bool m_isopaque;
  bool m_updated;
  bool m_mipmap;
  bool m_compress;
  int m_width;
  int m_height;
  int m_depth;
  int m_border;
  int m_format;
  int m_iformat;
  int m_swrap;
  int m_twrap;
  int m_rwrap;
  int m_magfilter;
  int m_minfilter;
  int m_envmode;
  int m_sgenmode;
  int m_tgenmode;
  int m_rgenmode;
  int m_qgenmode;
  int m_palsize;
  float m_sgenplane[4];
  float m_tgenplane[4];
  float m_rgenplane[4];
  float m_qgenplane[4];
  float m_envcolor[4];
  int m_depthtexmode;
  int m_shadowcompmode, m_shadowcompfunc;
  float m_anisotropy;
  void* m_data;
  unsigned int m_type;
  unsigned char* m_palette;
  AlgMatrix* m_matrix;
  int m_origwidth;
  int m_origheight;
  bool m_consider_opaque;
};

#endif
