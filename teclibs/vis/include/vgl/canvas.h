//* canvas.h
// celes@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Feb 2003

#ifndef VGL_CANVAS_H
#define VGL_CANVAS_H

#include "manipviewsurface.h"
#include "camera.h"
#include <alg/matrix.h>
#include <ds/list.h>

class VglSubCanvas;
class VglHandler;
//class VglCursor;  //TODO

class VGL_API VglCanvas : public VglManipViewSurface
{
public:
  typedef DsPList<VglCanvas> CanvasList;
  typedef DsPList<VglSubCanvas> SubCanvasList;
protected:
  /**
   * Constructs a new VglCanvas and associates it with a camera and an event notifier.
   * \param camera   Canvas' camera.
   * \param notifier Canvas' event notifier.
   */
  VglCanvas (VglCamera* camera, VglNotifier* notifier);
public:
  /**
   * Destroys a VglCanvas object.
   */
  virtual ~VglCanvas ();
  void SetStereo(bool flag)
  {
    m_stereo = flag;
  }
  bool IsStereo() const
  {
    return m_stereo;
  }
  /**
   * Configures the red & cyan stereo mode.
   */
  void SetRedCyanStereoMode (bool f)
  {
    m_redcyan = f;
  }
  /**
   * Checks if red & cyan stereo mode is enabled.
   */
  bool GetRedCyanStereoMode ()
  {
    return m_redcyan;
  }
  void SetScaleBiasRed (float s, float b)
  {
    m_redcyan_rs = s;
    m_redcyan_rb = b;
  }
  void SetScaleBiasCyan (float gs, float gb, float bs, float bb)
  {
    m_redcyan_gs = gs;
    m_redcyan_gb = gb;
    m_redcyan_bs = bs;
    m_redcyan_bb = bb;
  }
  /**
   * Is this a native redraw? (to be called inside drawing callbacks)
   */
  bool IsNativeRedraw ()
  {
    return m_nativeredraw;
  }
  /**
   * Is a redraw in progress?
   */
  bool IsDrawing() const
  {
    return m_is_drawing;
  }
  /**
   * Enables or disables automatic camera aspect ratio calculation.
   * If the setting is being enabled, it updates the camera's aspect ratio.
   */
  void SetAutoAspect(bool f);
  /**
   * Called when the canvas is reshaped.
   */
  void OnReshape ();
  /**
   * Adds a new subcanvas event handler to the canvas.
   * Only to be called internally.
   */
  virtual bool AddSubHandler (VglHandler* handler);
  /**
   * Adds a new subcanvas to the canvas.
   */
  virtual void AddSubCanvas (VglSubCanvas* s);
  /**
   * Removes a subcanvas from the canvas.
   * Returns the success in the removal.
   */
  virtual bool RemSubCanvas (VglSubCanvas* s);
  /**
   * Obtains an iterator to the subcanvas list.
   */
  virtual SubCanvasList::Iterator GetSubCanvases ()
  {
    return m_subcanvases.Begin();
  }
  /**
   * Removes all subcanvases.
   */
  virtual void ClearSubCanvases ();
  /**
   * Loads a camera, updating its parameters in case mapping is used.
   */
  void LoadCamera (VglCamera *camera);
  virtual bool HasViewport ()
  {
    return true;
  }
  virtual void GetViewport (int *x, int *y, int *w, int *h)
  {
    *x = *y = 0;
    *w = GetWidth();
    *h = GetHeight();
  }
  /**
   * Sets the canvas' keyboard callback.
   * 'data' will be passed to the callback as last parameter.
   */
  virtual void SetKeyboardFunc (VglKeyboardFunction func, void *data=0); 
  /**
   * Sets the canvas' mouse button callback.
   * 'data' will be passed to the callback as last parameter.
   */
  virtual void SetMouseButtonFunc (VglMouseButtonFunction func, void *data=0); 
  /**
   * Sets the canvas' mouse motion callback.
   * 'data' will be passed to the callback as last parameter.
   */
  virtual void SetMouseMotionFunc (VglMouseMotionFunction func, void *data=0);
  /**
   * Sets the canvas' mouse entry callback.
   * 'data' will be passed to the callback as last parameter.
   */
  virtual void SetMouseEntryFunc (VglMouseEntryFunction func, void *data=0);
  /**
   * Sets the canvas' mouse wheel callback.
   * 'data' will be passed to the callback as last parameter.
   */
  virtual void SetMouseWheelFunc (VglMouseWheelFunction func, void *data=0);
  /**
   * Activates canvas.
   */
  virtual void Activate () = 0;
  /**
   * Is the canvas active?
   */
  virtual bool IsActive () = 0;
  /**
   * Gets the currently active canvas, if any.
   * \return Currently active canvas, or NULL if no canvas is active.
   */
  static VglCanvas* GetActive ();
  /**
   * Gets the canvas' width in pixels.
   * \return Canvas width in pixels.
   */
  virtual int GetWidth () = 0;
  /**
   * Gets the canvas' height in pixels.
   * \return Canvas height in pixels.
   */
  virtual int GetHeight () = 0;
  /**
   * Returns if the canvas supports SetStereo(true).
   */
  virtual bool IsStereoSupported () = 0;
  /**
   * Performs a swap buffer operation in case the view surface has more than one buffer.
   */
  virtual void SwapBuffers () = 0;
  /**
   * Performs a post redraw operation.
   */
  virtual void PostRedraw ();
  /**
   * Sets the post redraw callback.
   * 'data' will be passed to the callback as last parameter.
   * This function will be called when a PostRedraw() is issued.
   * Set as 'NULL' to recover default behaviour.
   */
  virtual void SetPostRedrawFunc (VglFunction func, void *data=NULL);
  /**
   * Obtains the surface's postredraw callback.
   */
  virtual VglFunction GetPostRedrawFunc ()
  {
    return m_postredraw_func;
  }
  /**
   * Obtains the surface's postredraw callback data.
   */
  virtual void* GetPostRedrawData ()
  {
    return m_postredraw_data;
  }
  /**
   * Performs a redraw operation.
   */
  virtual void Redraw ();
  /**
   * Performs the drawing of an item (addressing issues like camera setup, stereoscopy, etc).
   */
  virtual void DrawItem (VglFunction func, void* data=0);
  virtual void SetCursorPos (float x, float y);
  virtual void SetCamera (VglCamera* camera);
  virtual void SetAudienceDistance (float dist)
  {
    m_dist = dist;
  }
  virtual float GetAudienceDistance () const
  {
    return m_dist;
  }
  virtual void SetDimension (float width, float height)
  {
    m_width = width;
    m_height = height;
  }
  virtual void GetDimension (float *width, float *height) const
  {
    *width = m_width;
    *height = m_height;
  }
  virtual void SetShift (float shiftx, float shifty)
  {
    m_shiftx = shiftx;
    m_shifty = shifty;
  }
  virtual void GetShift (float *shiftx, float *shifty) const
  {
    *shiftx = m_shiftx;
    *shifty = m_shifty;
  }
  virtual void SetRotation (float angle, float x=0.0f, float y=1.0f, float z=0.0f)
  {
    m_rotation.Identity();
    m_rotation.Rotate(-angle,x,y,z);
  }
  virtual void SetRotation (const AlgMatrix& r)
  {
    m_rotation = r;
  }
  virtual AlgMatrix GetRotation () const
  {
    return m_rotation;
  }
  virtual void EnableMapping (float magfactor=1.0f);
  virtual void DisableMapping ();
  virtual bool IsMappingEnabled () const
  {
    return m_mapping;
  }
  virtual float GetMappingMagFactor () const
  {
    return m_magfactor;
  }
  //virtual void SetCursor (VglCursor* cursor); //TODO
protected:
  void Reshape ();
  void SetNativeRedraw (bool state)
  {
    m_nativeredraw = state;
  }
  // deprecated: maintained for compatibility:
  static void ReshapeView (void* data)
  {
    VglCanvas* cv = (VglCanvas*)data;
    cv->Reshape();
  }
  static void RedrawView (void* data);
private:
  void UpdateCameraAspect (VglCamera *camera, int w, int h);
  void UpdateCameraAspect ()
  {
    UpdateCameraAspect(GetCamera(),GetWidth(),GetHeight());
  }
  void UpdateCameraAspect (VglCamera *camera)
  {
    UpdateCameraAspect(camera,GetWidth(),GetHeight());
  }
  void UpdateCameraAspect (int w, int h)
  {
    UpdateCameraAspect(GetCamera(),w,h);
  }
  void DrawEye(int eye);
private:
  static CanvasList s_canvases;
  SubCanvasList m_subcanvases;
  //VglCursor* m_cursor;
  bool  m_mapping;
  bool  m_autoaspect;
  float m_magfactor;
  float m_dist;
  float m_width;
  float m_height;
  float m_shiftx;
  float m_shifty;
  bool m_redcyan;
  float m_redcyan_rs;
  float m_redcyan_rb;
  float m_redcyan_gs;
  float m_redcyan_gb;
  float m_redcyan_bs;
  float m_redcyan_bb;
  AlgMatrix m_rotation;
  bool m_is_drawing;
  bool m_nativeredraw;
  VglFunction m_postredraw_func;
  void *m_postredraw_data;
  bool m_stereo;
};

#endif
