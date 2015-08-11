//* window.h
// fabraham@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Jun 2006

#ifndef VGL_WINDOW_H
#define VGL_WINDOW_H

#include <vgl/handler.h>
#include <vgl/viewsurface.h>

class VGL_API VglWindow
{
public:
  VglWindow (VglViewSurface *surface, VglHandler *handler);
  virtual ~VglWindow ();
  virtual void SetAnimated (bool flag)
  {
    printf("VGL: VglWindow::SetAnimated was deprecated (%s:%d).\n", __FILE__, __LINE__);
  }
  VglViewSurface* GetSurface ()
  {
    return m_surface;
  }
  void SetViewSurface (VglViewSurface *surface)
  {
    m_surface = surface;
  }
  virtual void BeginFeedback (bool centered, float x, float y);
  virtual void EndFeedback (float x, float y);
  virtual void GetFinalWindow (float x, float y, float *ox0, float *ox1, float *oy0, float *oy1);
  virtual void ContinueFeedback (float x, float y);
  virtual void OnEndRedraw ();
  bool MustEndRedraw () const
  {
    return MustDrawWindow();
  }
protected:
  void DrawWindow (float, float, float, float);
  VglNotifier *GetNotifier () const
  {
    return m_handler->GetNotifier();
  }
  float GetX0 ()
  {
    return GetNotifier() ? GetNotifier()->GetX0() : 0.0f;
  }
  float GetY0 ()
  {
    return GetNotifier() ? GetNotifier()->GetY0() : 0.0f;
  }
  float GetLastX ()
  {
    return GetNotifier() ? GetNotifier()->GetLastX() : 0.0f;
  }
  float GetLastY ()
  {
    return GetNotifier() ? GetNotifier()->GetLastY() : 0.0f;
  }
  bool MustDrawWindow () const
  {
    return m_drawwindow;
  }
  bool IsCentered () const
  {
    return m_centeredwindow;
  }
private:
  void SetCentered (bool f)
  {
    m_centeredwindow = f;
  }
  VglViewSurface* m_surface;
  VglHandler *m_handler;
  float m_x0, m_x1, m_y0, m_y1;
  bool m_drawwindow;
  bool m_centeredwindow;
};

#endif
