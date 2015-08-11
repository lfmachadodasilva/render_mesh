// Pbuffercanvas class
// fabraham@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Sep 2003

#ifndef VGL_PBUFFERCANVAS_H
#define VGL_PBUFFERCANVAS_H

#include <ugl/rpbuffer.h>
#include <vgl/canvas.h>
#include <vgl/vglpbuffer.h>
#include <ds/list.h>

/**
 * This class implements a Pbuffer canvas.\n
 */
class VGLPBUFFERAPI VglPBufferCanvas : public VglCanvas
{
  UGLReshapablePBuffer m_pbuffer;
  bool m_terminate;
public:
	/**
	 * Constructor
	 */
	VglPBufferCanvas (VglCamera* camera, bool usePBuffer = false);
  /**
   * Specifies the GPU on which the GL context will be created,
   * where 0 stands for the first GPU, 1 for the second, and so on.
   * Default: 0.
   *
   * Warning: X11 only.
   */
  void SetGPU (int gpu_index)
  {
    m_pbuffer.SetGPU(gpu_index);
  }
  /**
   * Specifies the level of anti-aliasing sampling. Default=1.
   *
   * Warning: FBO mode only.
   */
  void SetAntiAliasingNumSamples (int nsamples)
  {
    m_pbuffer.SetAntiAliasingNumSamples(nsamples);
  }
  /**
   * Obtains the level of anti-aliasing sampling. Default=1.
   */
  int GetAntiAliasingNumSamples () const
  {
    return m_pbuffer.GetAntiAliasingNumSamples();
  }
  /**
   * Initializes the pbuffer's rendering context.
   * 'mode' should be a bitwise OR between:
   * PBuffer::INDEX,
   * PBuffer::ALPHA, 
   * PBuffer::DOUBLE, 
   * PBuffer::SINGLE,
   * PBuffer::DEPTH,
   * PBuffer::STENCIL,
   * PBuffer::ACCUM.
   * 'sharecontext' specifies if this canvas' pbuffer should use the same GL context as the currently active GL context. Otherwise, a new GL context is created.
   * 'sharelists' specifies if this canvas' pbuffer should share texture objects and display lists with the currently active GL context. If 'sharecontext', this is automatically done.
   * Note that the default values for 'sharecontext' and 'sharelists' differ from the ones in UGLPBuffer.
	 * Returns success on initializing the pbuffer.
   */
  bool Initialize (int width, int height, int mode, bool sharecontext=false, bool sharelists=false);
  /**
   * Destroys a VglPBufferCanvas object.
   */
  virtual ~VglPBufferCanvas ();
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
  virtual void SetCursorPos (float x, float y);
  virtual void Activate ();
  virtual void Redraw ();
  virtual bool IsActive ();
  virtual bool IsStereoSupported ()
  {
    return false;
  }
  virtual void SwapBuffers ();
  virtual int  GetWidth ();
  virtual int  GetHeight ();
  virtual void SetRasterCursor (bool on);
private:
  static void RedrawCB (void* data);
  bool m_use_pbuffer;
};

#endif

