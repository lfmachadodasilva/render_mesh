// Reshapable pbuffer class
// fabraham@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Sep 2003

#ifndef UGL_RPBUFFER_H
#define UGL_RPBUFFER_H

#ifndef __APPLE__
# define RPBUFFER_USE_X11_ON_GLX
#endif

#ifndef UGLRPBUFFER_DLL
# ifndef TEC_DLL
#  define UGLRPBUFFER_API
# else
#  define UGLRPBUFFER_API __declspec(dllimport)
# endif
#else
# define UGLRPBUFFER_API __declspec(dllexport)
#endif

#include "pbuffer.h"
#if (!defined(WIN32) && defined(RPBUFFER_USE_X11_ON_GLX))
# include <GL/glxew.h>
#endif
#include <stdio.h>

/**
 * This class implements a Reshapable Pbuffer canvas.
 */
class UGLRPBUFFER_API UGLReshapablePBuffer
{
public:
	/**
	 * Constructor
	 */
	UGLReshapablePBuffer (bool use_pbuffer = false);
  /**
   * Specifies the GPU on which the GL context will be created,
   * where 0 stands for the first GPU, 1 for the second, and so on.
   * Default: 0.
   *
   * Warning: X11 only, FBO mode only.
   */
  void SetGPU (int gpu_index)
  {
#if (defined(WIN32) || !defined(RPBUFFER_USE_X11_ON_GLX))
    printf("UGL: SetGPU() not supported in windows (%s:%d).\n",__FILE__,__LINE__);
#else
    if (m_use_pbuffers)
      printf("UGL: SetGPU() not supported with pbuffer implementation (%s:%d).\n",__FILE__,__LINE__);
    else
      m_gpu_index = gpu_index;
#endif
  }
  /**
   * Specifies the level of anti-aliasing sampling. Default=1.
   *
   * Warning: FBO mode only.
   */
  void SetAntiAliasingNumSamples (int nsamples)
  {
    m_antialiasing_num_samples = nsamples;
  }
  /**
   * Obtains the level of anti-aliasing sampling. Default=1.
   */
  int GetAntiAliasingNumSamples () const
  {
    return m_antialiasing_num_samples;
  }
  /**
   * Initializes the pbuffer's rendering context.
   * 'mode' should be a bitwise OR between:
   * PBuffer::ALPHA, 
   * PBuffer::DOUBLE, 
   * PBuffer::SINGLE,
   * PBuffer::DEPTH,
   * PBuffer::STENCIL.
	 * Returns success on initializing the pbuffer.
   */
  bool Initialize (int width, int height, int mode, bool sharecontext=false, bool sharelists=false);
  void SetRedrawFunc (void (*func)(void*), void* data=0)
  {
    m_redraw = func;
    m_data = data;
  }
  /**
   * Destructor
   */
  virtual ~UGLReshapablePBuffer ();
	/**
	 * Resizes the pbuffer if a new dimension is passed.
	 * It is going to recreate the resizable pbuffer while keeping the main pbuffer intact.
	 */
	bool Reshape (int width, int height);
  /**
   * Ends the main loop.
   */
  void Terminate ();
  /**
   * Starts the rendering mainloop. Analog to glutMainLoop/IupMainLoop.
   * The function returns after Terminate() is called.
   */
  void MainLoop ();
  /**
   * Deactivates the canvas pbuffers.
   */
  void Deactivate ();
  /**
   * Is the pbuffer initialized?
   */
  bool IsInitialized ();
  void Activate ();
  bool IsActive ();
  int  GetWidth ();
  int  GetHeight ();
  
  void SwapBuffers(void);
  /**
   * Finalizes redraw in case anti-aliasing was requested.
   */
  void FinishAntialiasedRedraw ();
private:
  void Close ();
private:
  void (*m_redraw)(void*);
  void* m_data;
  bool m_terminate;
#if (defined(WIN32) || !defined(RPBUFFER_USE_X11_ON_GLX))
  int m_glut_window;
#else
  int m_gpu_index;
  Display *m_display;
  Window m_win;
  GLXContext m_glcontext;
  bool m_win_created;
#endif
  GLuint m_fbo;
  GLuint m_color_buffer;
  GLuint m_depth_stencil_buffer;
  GLuint m_depth_buffer;
  GLuint m_stencil_buffer;
  GLuint m_fbo_ms;
  GLuint m_color_buffer_ms;
  GLuint m_depth_stencil_buffer_ms;
  GLuint m_depth_buffer_ms;
  GLuint m_stencil_buffer_ms;
  int m_mode;
  int m_width;
  int m_height;
  bool m_initialized;
  bool m_active;
  bool m_use_pbuffers;
  UGLPBuffer* m_mainpbuffer;
  UGLPBuffer* m_pbuffer;

  bool InitializePBuffers(int width, int height, int mode, bool sharecontext, bool sharelists);
  bool ReshapePBuffers(int width, int height);
  void ActivatePBuffers(void);
  void DeactivatePBuffers(void);
  void SwapBuffersPBuffers(void);
private:
  int m_antialiasing_num_samples;
  bool m_share_context;  
};

#endif

