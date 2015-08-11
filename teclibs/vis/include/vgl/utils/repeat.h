// repeat.h
// fabraham@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Jun 2006

#ifndef VGL_REPEAT_H
#define VGL_REPEAT_H

#include <assert.h>
#include <vgl/handler.h>
#include <vgl/viewsurface.h>

class VGL_API VglRepeatTransform
{
public:
  /**
   * Constructor.
   * 'surface' is the visualization surface (mandatory).
   * 'handler' is the associated handler (mandatory).
   */
  VglRepeatTransform (VglViewSurface* surface, VglHandler *handler) :
    m_surface(surface),
    m_handler(handler)
  {
    assert(surface);
    assert(handler);
  }
  ~VglRepeatTransform ()
  {
  }
  /**
   * Sets a new view surface.
   */
  void SetViewSurface (VglViewSurface *surface)
  {
    m_surface = surface;
  }
  void Start () const;
  void Stop () const;
private:
  // private methods
  //  static methods
  static void DoIt (void* data);
  VglViewSurface *GetSurface ()
  {
    return m_surface;
  }
  VglNotifier *GetNotifier () const
  {
    return m_handler->GetNotifier();
  }
  // members
  VglViewSurface* m_surface;
  VglHandler *m_handler;
};

#endif
