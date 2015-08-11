/**
 * file      fbo.h
 * @author   vbarata@tecgraf.puc-rio.br
 * @date     Mar 2009
 */

/**
 * Usage instructions:
 *
 * UGLRenderBuffer (not needed in automatic mode)
 * ---------------
 * 1. New
 * 2. Call Init() to specify data format, dimensions and multisampling
 * 2.1. Call Init() again whenever parameters need to be changed
 * 3. Attach to UGLFrameBuffer
 * 4. Use to render/write/read data
 * 5. Delete
 *
 * UGLFrameBuffer (automatic mode)
 * --------------
 * 1. New
 * 2. Call SetSize() and SetMultiSampling() to specify dimensions and multisampling
 * 3. Call SetupRenderToTexture() with the desired textures (or the UGL_RENDERBUFFER constant)
 * 4. Call Activate(true)
 * 5. Use to render/write/read data
 * 6. Call Deactivate()
 * 7. Use any written textures normally
 * 8. Return to step 2 or 4 if needed
 * 9. Delete
 *
 * UGLFrameBuffer (semi-automatic mode)
 * --------------
 * 1. New
 * 2. Call SetSize() and SetMultiSampling() to specify dimensions and multisampling
 * 3. Call Attach*() as many times as needed
 * 4. Call Activate(true)
 * 5. Use to render/write/read data
 * 6. Call Deactivate()
 * 7. Use any written textures normally
 * 8. Return to step 2 or 4 if needed
 * 9. Delete
 *
 * UGLFrameBuffer (manual OpenGL-wrapper mode)
 * --------------
 * 1. Create
 * 2. Call SetSize() and SetMultiSampling() to specify dimensions and multisampling
 * 3. Call Activate(false)
 * 4. Call Attach*() and Detach() as needed, or SetupRenderToTexture() once
 * 5. Call ConfigBuffers()
 * 6. Call CheckCompleteness() once per unique FBO attachment configuration
 * 7. Use to render/write/read data
 * 8. Call PerformAntialiasing() if needed
 * 9. Call GenerateMipmaps() if needed
 * 10. Call Deactivate() (or return to step 4 or 7)
 * 11. Use any written textures normally
 * 12. Return to step 2 or 3 if needed
 * 13. Delete
 */

#ifndef UGL_FBO_H
#define UGL_FBO_H

/**
 * Includes and Forward Declarations
 */

#include "defines.h"

#include <ds/array.h>

class UGLTexture;
class UGLFBOAttachInfo;

#define UGL_RENDERBUFFER ((UGLTexture*)0x1)

/**
 * UGLRenderBuffer class
 * Allows for OpenGL RenderBuffer usage
 * (requires EXT_framebuffer_object)
 */
class UGL_API UGLRenderBuffer
{
public:
  /**
   * Constructor
   */
  UGLRenderBuffer ();

  /**
   * Destructor
   */
  virtual ~UGLRenderBuffer ();

  /**
   * Initialization
   * Can be called again to change the renderbuffer parameters (expensive)
   * (multisampling requires EXT_framebuffer_multisample)
   */
  bool Init (unsigned int format, int width, int height, int nsamples = 1);

  /**
   * Data format
   */
  GLenum GetFormat ()
  {
    return m_format;
  }

  /**
   * Width in pixels
   */
  GLsizei GetWidth ()
  {
    return m_width;
  }

  /**
   * Height in pixels
   */
  GLsizei GetHeight ()
  {
    return m_height;
  }

  /**
   * OpenGL Id Getter
   */
  GLuint GetId ()
  {
    return m_rb;
  }

private:
  /**
   * OpenGL ID assigned to this RenderBuffer
   */
  GLuint m_rb;
  /**
   * Internal format
   */
  GLenum m_format;
  /**
   * Width in pixels
   */
  GLsizei m_width;
  /**
   * Height in pixels
   */
  GLsizei m_height;
  /**
   * Number of samples per pixel
   */
  GLsizei m_nsamples;
};

/**
 * UGLFrameBuffer class
 * Allows for OpenGL FrameBuffer Object (FBO) usage
 * (requires EXT_framebuffer_object)
 */
class UGL_API UGLFrameBuffer
{
public:
  /**
   * Constructor
   */
  UGLFrameBuffer ();

  /**
   * Destructor
   */
  virtual ~UGLFrameBuffer ();

  /**
   * Set the framebuffer size
   * Detaches any previously attached render targets
   */
  bool SetSize (int width, int height = 1);

  /**
   * Get the framebuffer size
   */
  void GetSize (int* width, int* height);

  /**
   * Set the framebuffer number of samples
   * Deactivates the framebuffer if activated
   * Detaches any previously attached render targets
   * Multisampling requires EXT_framebuffer_multisample
   */
  bool SetMultiSampling (int nsamples, bool multicolor = true, bool multidepth = true, bool multistencil = true);

  /**
   * Attach 1D texture target
   */
  bool AttachTexture1D (unsigned int attachment, UGLTexture* texture1d, int basemipmap = 0, int lastmipmap = 0);
  bool AttachTexture1D (unsigned int attachment, unsigned int texture1d, int basemipmap = 0, int lastmipmap = 0);

  /**
   * Attach one layer of a 1D texture array target
   * (requires EXT_texture_array)
   */
  bool AttachArrayTexture1DLayer (unsigned int attachment, UGLTexture* arraytex1d, int layer, int basemipmap = 0, int lastmipmap = 0);
  bool AttachArrayTexture1DLayer (unsigned int attachment, unsigned int arraytex1d, int layer, int basemipmap = 0, int lastmipmap = 0);

  /**
   * Attach an entire 1D texture array target as a multi-layered attachment
   * (requires EXT_texture_array and EXT_geometry_shader4)
   */
  bool AttachArrayTexture1D (unsigned int attachment, UGLTexture* arraytex1d, int basemipmap = 0, int lastmipmap = 0);
  bool AttachArrayTexture1D (unsigned int attachment, unsigned int arraytex1d, int basemipmap = 0, int lastmipmap = 0);

  /**
   * Attach 2D texture target
   */
  bool AttachTexture2D (unsigned int attachment, UGLTexture* texture2d, int basemipmap = 0, int lastmipmap = 0);
  bool AttachTexture2D (unsigned int attachment, unsigned int texture2d, int basemipmap = 0, int lastmipmap = 0);

  /**
   * Attach one layer of a 2D texture array target
   * (requires EXT_texture_array)
   */
  bool AttachArrayTexture2DLayer (unsigned int attachment, UGLTexture* arraytex2d, int layer, int basemipmap = 0, int lastmipmap = 0);
  bool AttachArrayTexture2DLayer (unsigned int attachment, unsigned int arraytex2d, int layer, int basemipmap = 0, int lastmipmap = 0);

  /**
   * Attach an entire 2D texture array target as a multi-layered attachment
   * (requires EXT_texture_array and EXT_geometry_shader4)
   */
  bool AttachArrayTexture2D (unsigned int attachment, UGLTexture* arraytex2d, int basemipmap = 0, int lastmipmap = 0);
  bool AttachArrayTexture2D (unsigned int attachment, unsigned int arraytex2d, int basemipmap = 0, int lastmipmap = 0);

  /**
   * Attach one plane of a 3D texture target
   */
  bool AttachTexture3DPlane (unsigned int attachment, UGLTexture* texture3d, int zplane, int basemipmap = 0, int lastmipmap = 0);
  bool AttachTexture3DPlane (unsigned int attachment, unsigned int texture3d, int zplane, int basemipmap = 0, int lastmipmap = 0);

  /**
   * Attach an entire 3D texture target as a layered attachment
   * (requires EXT_geometry_shader4)
   */
  bool AttachTexture3D (unsigned int attachment, UGLTexture* texture3d, int basemipmap = 0, int lastmipmap = 0);
  bool AttachTexture3D (unsigned int attachment, unsigned int texture3d, int basemipmap = 0, int lastmipmap = 0);

  /**
   * Attach rectangle texture target (prefer a 2D texture in OpenGL 2.0 or greater)
   */
  bool AttachTextureRectangle (unsigned int attachment, UGLTexture* texturerect);
  bool AttachTextureRectangle (unsigned int attachment, unsigned int texturerect);

  /**
   * Attach one face of a cube texture target
   */
  bool AttachTextureCubeFace (unsigned int attachment, UGLTexture* texturecube, int face, int basemipmap = 0, int lastmipmap = 0);
  bool AttachTextureCubeFace (unsigned int attachment, unsigned int texturecube, int face, int basemipmap = 0, int lastmipmap = 0);

  /**
   * Attach an entire cube texture target as a layered attachment
   * (requires EXT_geometry_shader4)
   */
  bool AttachTextureCube (unsigned int attachment, UGLTexture* texturecube, int basemipmap = 0, int lastmipmap = 0);
  bool AttachTextureCube (unsigned int attachment, unsigned int texturecube, int basemipmap = 0, int lastmipmap = 0);

  /**
   * Attach renderbuffer target
   */
  bool AttachRenderBuffer (unsigned int attachment, UGLRenderBuffer* renderbuffer);
  bool AttachRenderBuffer (unsigned int attachment, unsigned int renderbuffer);

  /**
   * Detach target
   */
  bool Detach (unsigned int attachment);

  /**
   * Automatically setup this FBO for render-to-texture
   * Pass in UGL_RENDERBUFFER to use an internal renderbuffer
   */
  bool SetupRenderToTexture (UGLTexture* color);
  bool SetupRenderToTexture (UGLTexture* color, UGLTexture* depth);
  bool SetupRenderToTexture (UGLTexture* color, UGLTexture* depth, UGLTexture* stencil);
  bool SetupRenderToTexture (int ncolors, UGLTexture** colors);
  bool SetupRenderToTexture (int ncolors, UGLTexture** colors, UGLTexture* depth);
  bool SetupRenderToTexture (int ncolors, UGLTexture** colors, UGLTexture* depth, UGLTexture* stencil);

  /**
   * Check if the FBO is active for rendering
   * Do not pass true to "antialiased", it is to be used only internally
   */
  bool IsActive (bool antialiased = false) const;

  /**
   * Activate the FBO for rendering
   * @param autoupdate Indicates whether this FBO's attachments have already
   *                   been setup or if the FBO should simply be bound before
   *                   the application sets up the attachments manually. If
   *                   true, automatically calls ConfigBuffers() and
   *                   CheckCompleteness() if necessary
   */
  bool Activate (bool autoupdate = true);

  /**
   * Deactivate the FBO for rendering
   * @param autoantialias If true, automatically calls PerformAntialiasing()
   * @param automipmap If true, automatically calls GenerateMipmaps()
   */
  void Deactivate (bool autoantialias = true, bool automipmap = true);

  /**
   * Configure OpenGL Read and Draw buffers
   * Useful when an fbo is changed while active
   * @param readbuffer If zero, uses the first attached color buffer, if any
   */
  void ConfigBuffers (unsigned int readbuffer = 0);

  /**
   * Check for FBO completeness errors
   * Useful when an fbo is changed while active
   * Do not pass true to "antialiased", it is to be used only internally
   * @return true if no errors.
   */
  bool CheckCompleteness (bool antialiased = false) const;

  /**
   * Downsample a multisampled FBO to perform antialiasing
   * Useful when an fbo is changed while active
   * (requires EXT_framebuffer_multisample)
   */
  void PerformAntialiasing ();

  /**
   * Generate attachment mipmaps
   * Useful when an fbo is changed while active
   */
  void GenerateMipmaps ();

  /**
   * Generate attachment mipmaps
   * Useful when an fbo is changed while active
   */
  void GenerateMipmaps (unsigned int attachment);

protected:

  bool CheckDimensions (int ncolors, UGLTexture** colors, UGLTexture* depth, UGLTexture* stencil);
  void ListAttachments () const;
  void PrintAttachInfo (UGLFBOAttachInfo* attachinfo) const;

  bool CreateFBO ();
  bool CreateMSFBO ();

  void Update ();
  void UpdateAntialiased ();

  bool AttachAutoRenderBuffer (unsigned int attachment);
  UGLFBOAttachInfo* GetAttachInfo (unsigned int attachment);

  void RequestAttach (unsigned int attachment, UGLTexture* texture);
  void DoAttach (unsigned int attachment, UGLFBOAttachInfo* attachinfo, bool multisampled);
  void DetachAll ();

private:
  // blocking copy constructor (to avoid copying issues: copy must be made explicitly)
  UGLFrameBuffer& UGLFrameBuffer::operator= (const UGLFrameBuffer &o) 
  {
    return *this;
  }

  // blocking assignment operator (to avoid copying issues: copy must be made explicitly)
  UGLFrameBuffer (const UGLFrameBuffer& o) 
  {
  }

private:
  /**
   * OpenGL ID assigned to this FBO
   */
  GLuint m_fbo;
  /**
   * OpenGL ID assigned to the multi-sampled FBO
   */
  GLuint m_msfbo;
  /**
   * Saves the ID of the last FBO bound before this
   */
  GLuint m_lastfbo;
  /**
   * Color attachments
   */
  DsArray<UGLFBOAttachInfo*> m_color;
  /**
   * Depth attachment
   */
  UGLFBOAttachInfo* m_depth;
  /**
   * Stencil attachment
   */
  UGLFBOAttachInfo* m_stencil;
  /**
   * Width in pixels
   */
  GLsizei m_width;
  /**
   * Height in pixels
   */
  GLsizei m_height;
  /**
   * Number of samples per pixel
   */
  GLsizei m_nsamples;
  /**
   * Stores if color buffers are multisampled
   */
  bool m_multicolor;
  /**
   * Stores if the depth buffer is multisampled
   */
  bool m_multidepth;
  /**
   * Stores if the stencil buffer is multisampled
   */
  bool m_multistencil;
  /**
   * Stores if this FBO been activated and not yet deactivated
   */
  bool m_activated;
  /**
   * Stores if this FBO needs an update on its next activation
   */
  bool m_needUpdate;
  /**
   * Stores if the antialiased FBO needs an update on the next AA operation
   */
  bool m_needAAUpdate;
};

#endif /* UGL_FBO_H */

