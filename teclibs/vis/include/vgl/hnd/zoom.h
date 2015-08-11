//* zoom.h
// celes@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Jan 2003

#ifndef VGL_ZOOM_H
#define VGL_ZOOM_H

#include <vgl/handler.h>
#include <vgl/utils/window.h>
#include <ds/defines.h>

class VglViewSurface;

class VGL_API VglZoomHandler : public VglHandler
{
  VglViewSurface* m_surface;
  VglWindow m_window;
  char m_constraint;
  void DrawWindow (bool, float, float, float, float);
protected:
  virtual void Zoom (float dx, float dy, float x, float y);
  virtual void TranslateZoom (float x, float y);
  virtual void ScaleZoom (float s);
public:
  /**
   * Returns the event handler class classname.
   * \return Event handler class classname.
   */
  static const char* CLASSNAME () { return "ZoomHandler"; }
  virtual const char* ClassName () const { return CLASSNAME(); }

  VglZoomHandler (VglViewSurface *surface);
  virtual ~VglZoomHandler ();
  virtual void SetViewSurface(VglViewSurface *surface)
  {
    m_surface = surface;
    m_window.SetViewSurface(surface);
  }
  DS_DEPRECATED void SetAnimated(bool flag)
  {
    printf("VGL: VglZoomHandler::SetAnimated was deprecated (%s:%d).\n", __FILE__, __LINE__);
  }
  VglViewSurface* GetSurface ()
  {
    return m_surface;
  }
  virtual int MouseButton (int bt, int st, float x, float y);
  virtual int MouseMotion (int bt, float x, float y);
  virtual int PostRedraw ();
  virtual int UndoZoom ();
  virtual int RedoZoom ();
  virtual bool CanUndoZoom ();
  virtual bool CanRedoZoom ();
  virtual bool HasZoom ();
};

#endif
