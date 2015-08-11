//* viewsurface.h
// celes@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Feb 2003

#ifndef VGL_VIEWSURFACE_H
#define VGL_VIEWSURFACE_H

#include "defines.h"
#include <alg/matrix.h>
#include <ugl/error.h>

class VglCamera;

class VGL_API VglViewSurface
{
  VglCamera* m_camera;
  VglReshapeFunction m_reshape;
  void* m_rdata;
  VglFunction m_bredraw;
  void* m_brdata;
  VglFunction m_redraw;
  void* m_data;
  VglFunction m_eredraw;
  void *m_edata;
protected:
  /**
   * Constructor. 'camera' is the camera associated with this view surface.
   */
  VglViewSurface (VglCamera* camera) :
    m_camera(camera),
    m_reshape(NULL), m_rdata(NULL), 
    m_bredraw(NULL), m_brdata(NULL),
    m_redraw(NULL), m_data(NULL),
    m_eredraw(NULL), m_edata(NULL)
  , m_drawn_eye(VGL_EYE_MONO)
  {
  }
public:
  static void BeforeUserRedraw (const char* where, const char* callbackname)
  {
#ifdef _DEBUG
    GLenum e = glGetError();
    if (e != GL_NONE)
      printf("VGL: GL error happened before %s %s (probably a VGL error): %s\n", where, callbackname, ugl_errorstring(e));
#endif
  }
  static void AfterUserRedraw (const char* where, const char* callbackname)
  {
#ifdef _DEBUG
    GLenum e = glGetError();
    if (e != GL_NONE)
      printf("VGL: GL error happened after %s %s: %s\n", where, callbackname, ugl_errorstring(e));
#endif
  }
public:
  /**
   * Destructor.
   */
  virtual ~VglViewSurface ()
  {
  }
  /**
   * Centers the canvas cursor.
   */
  void CenterCursor()
  {
    SetCursorPos(0.5f,0.5f);
  }
  /**
   * Sets the view surface's reshape callback.
   * Callback will be called with the new width, new height and the specified 'data' pointer.
   */
  virtual void SetReshapeFunc (VglReshapeFunction func, void* data=NULL)
  {
    m_reshape = func;
    m_rdata = data;
  }
  /**
   * Gets the surface's reshape callback.
   */
  virtual VglReshapeFunction GetReshapeFunc ()
  {
    return m_reshape;
  }
  /**
   * Gets the surface's reshape callback data.
   */
  virtual void* GetReshapeData ()
  {
    return m_rdata;
  }
  /**
   * Sets the view surface's begin redraw callback.
   * Callback will be called with the specified 'data' pointer.
   */
  virtual void SetBeginRedrawFunc (VglFunction func, void* data=NULL);
  /**
   * Gets the surface's begin redraw callback.
   */
  virtual VglFunction GetBeginRedrawFunc () const
  {
    return m_bredraw;
  }
  /**
   * Gets the surface's begin redraw callback data.
   */
  virtual void* GetBeginRedrawData () const
  {
    return m_brdata;
  }
  /**
   * Sets the view surface's redraw callback.
   * Callback will be called with the specified 'data' pointer.
   */
  virtual void SetRedrawFunc (VglFunction func, void* data=NULL);
  /**
   * Gets the surface's redraw callback.
   */
  virtual VglFunction GetRedrawFunc ()
  {
    return m_redraw;
  }
  /**
   * Gets the surface's redraw callback data.
   */
  virtual void* GetRedrawData ()
  {
    return m_data;
  }
  /**
   * Sets the surface's end redraw callback.
   * 'data' will be passed to the callback.
   */
  virtual void SetEndRedrawFunc (VglFunction func, void* data=NULL)
  {
    m_eredraw = func;
    m_edata = data;
  }
  /**
   * Gets the surface's end redraw callback.
   */
  virtual VglFunction GetEndRedrawFunc ()
  {
    return m_eredraw;
  }
  /**
   * Gets the surface's end redraw callback data.
   */
  virtual void* GetEndRedrawData ()
  {
    return m_edata;
  }
  /**
   * Returns the camera associated with this view surface.
   */
  virtual VglCamera* GetCamera ()
  {
    return m_camera;
  }
  /**
   * Sets this view surface's camera.
   */
  virtual void SetCamera (VglCamera* camera)
  {
    m_camera = camera;
  }
  /**
   * Can the surface provide a viewport ?
   */
  virtual bool HasViewport ()
  {
    return false;
  }
  /**
   * obtains the surface's viewport
   */
  virtual void GetViewport (int *x, int *y, int *w, int *h)
  {
  }
  /**
   * Obtains a matrix that transforms normalized window coordinates of
   * this surface's parent (if any) to normalized coordinates for this surface.
   */
  virtual AlgMatrix GetToLocal ()
  {
    return AlgMatrix::GetIdentity();
  }
  /**
   * Obtains a matrix that transforms normalized window coordinates of
   * this surface's to normalized coordinates for this surface's parent (if any).
   */
  virtual AlgMatrix GetToGlobal ()
  {
    return AlgMatrix::GetIdentity();
  }
  /**
   * Specifies which eye is being drawn by this surface.
   * Assumes stereo is not enabled.
   * Default: VGL_EYE_MONO.
   */
  virtual void SetDrawnEye (int eye)
  {
    m_drawn_eye = eye;
  }
  /**
   * Obtains which eye is being drawn by this surface.
   * Default: VGL_EYE_MONO.
   */
  virtual int GetDrawnEye () const
  {
    return m_drawn_eye;
  }
  /**
   * Performs a redraw operation.
   */
  virtual void Redraw () = 0;
  /**
   * Requests the redraw of the surface when the process becomes idle.
   */
  virtual void PostRedraw () = 0;
  /**
   * Performs the drawing of an item (addressing issues like camera setup, viewport, stereoscopy, etc).
   */
  virtual void DrawItem (VglFunction func, void* data=NULL) = 0;
  /**
   * Sets the surface's cursor position.
   */
  virtual void SetCursorPos (float x, float y) = 0;
  /**
   * Sets if surface must draw a raster cursor or not.
   */
  virtual void SetRasterCursor (bool f) = 0;
private:
  int m_drawn_eye;
};

#endif
