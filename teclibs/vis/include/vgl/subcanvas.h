//* subcanvas.h
// fabraham@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Mar 2005

#ifndef VGL_SUBCANVAS_H
#define VGL_SUBCANVAS_H

#include "canvas.h"
#include "manipviewsurface.h"
#include "camera.h"
#include "subnotifier.h"

class VglSubHandler;

class VGL_API VglSubCanvas : public VglManipViewSurface
{
public:
  /**
   * Constructs a new VglSubCanvas and associates it with a camera.
   * Its parent must also be supplied.
   */
  VglSubCanvas (VglCamera* camera, VglCanvas *parent);
  /**
   * Destroys a VglSubCanvas object.
   */
  virtual ~VglSubCanvas ();
  VglSubHandler *GetSubHandler ();

  VglSubNotifier* GetSubNotifier ()
  {
    return (VglSubNotifier*)GetNotifier();
  }
  VglCanvas *GetParent ()
  {
    return m_parent;
  }
  /**
   * Sets the subcanvas' window. 'x', 'y', 'w' and 'h' are relative to
   * the subcanvas' parent canvas window width and height and must range
   * from 0.0 to 1.0.
   */
  void SetWindow (float x, float y, float w, float h);
  /**
   * Obtains the subcanvas' window.
   */
  void GetWindow (float *x, float *y, float *w, float *h)
  {
    *x = m_x;
    *y = m_y;
    *w = m_w;
    *h = m_h;
  }
  /**
   * Specifies if the subcanvas handler must filter events to subsequent
   * handlers. [default=true]
   */
  void SetFilterEvents (bool f);
  /**
   * Obtains the subcanvas' x coord in pixels
   */
  int GetX ()
  {
    return int(m_x*GetParent()->GetWidth());
  }
  /**
   * Obtains the subcanvas' y coord in pixels
   */
  int GetY ()
  {
    return int(m_y*GetParent()->GetHeight());
  }
  /**
   * Obtains the subcanvas' width in pixels
   */
  int GetWidth ()
  {
    return int(m_w*GetParent()->GetWidth());
  }
  /**
   * Obtains the subcanvas' height in pixels
   */
  int GetHeight ()
  {
    return int(m_h*GetParent()->GetHeight());
  }
  /**
   * Enables/disables a subcanvas.
   */
  void SetEnabled (bool f);
  /**
   * Is subcanvas enabled?
   */
  bool IsEnabled ()
  {
    return m_enabled;
  }
  /**
   * Redraws the subcanvas.
   */
  void RedrawView ();
  /**
   * Specifies the subcanvas clear color.
   */
  void ClearColor (float r, float g, float b, float a)
  {
    m_cc[0] = (unsigned char)(255*r);
    m_cc[1] = (unsigned char)(255*g);
    m_cc[2] = (unsigned char)(255*b);
    m_cc[3] = (unsigned char)(255*a);
  }
  /**
   * Specifies the subcanvas clear depth value.
   */
  void ClearDepth (float d)
  {
    m_cd = d;
  }
  /**
   * Clears the desired buffers (similar to glClear).
   *
   * NOTE: It does so drawing a quad, so this might break selection algorithms.
   */
  void Clear (unsigned int mask);
  /**
   * Is this a native redraw? (to be called inside drawing callbacks)
   */
  bool IsNativeRedraw ()
  {
    return GetParent()->IsNativeRedraw();
  }
  /**
   * Sets the subcanvas' camera.
   */
  virtual void SetCamera (VglCamera *camera);
  virtual bool HasViewport ()
  {
    return true;
  }
  virtual void GetViewport (int *x, int *y, int *w, int *h)
  {
    *x = GetX();
    *y = GetY();
    *w = GetWidth();
    *h = GetHeight();
  }
  virtual void ClearHandlers ();
  /**
   * Requests the redraw of this subcanvas' parent.
   */
  virtual void Redraw ();
  /**
   * Requests the redraw of this subcanvas' parent when the process becomes idle.
   */
  virtual void PostRedraw ();
  virtual void DrawItem (VglFunction func, void* data=0);
  virtual void SetCursorPos (float x, float y);
  virtual void SetRasterCursor (bool f);
  virtual bool AddIdle (VglFunction func, void* data, int repeat)
  {
    return GetParent()->AddIdle(func,data,repeat);
  }
  virtual bool RemIdle (VglFunction func, void* data)
  {
    return GetParent()->RemIdle(func,data);
  }
  AlgMatrix GetToLocal ();
  AlgMatrix GetToGlobal ();
private:
  VglCanvas *m_parent;
  float m_x, m_y, m_w, m_h, m_winv, m_hinv;
  unsigned char m_cc[4];
  float m_cd;
  VglSubHandler *m_handler;
  bool m_enabled;
  AlgMatrix m_tolocal;
  AlgMatrix m_toglobal;
  bool m_tolocal_updated;
  bool m_toglobal_updated;
};

#endif
