//* pan.h
// fabraham@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Oct 2005

#ifndef VGL_PAN_H
#define VGL_PAN_H

#include <vgl/handler.h>

class VglViewSurface;

class VGL_API VglPanHandler : public VglHandler
{
  VglViewSurface* m_surface;
  char m_constraint;
public:
  /**
   * Returns the event handler class classname.
   * \return Event handler class classname.
   */
  static const char* CLASSNAME () { return "PanHandler"; }
  virtual const char* ClassName () const { return CLASSNAME(); }

  VglPanHandler (VglViewSurface* surface);
  virtual ~VglPanHandler ();
  void SetViewSurface(VglViewSurface *surface)
  {
    m_surface = surface;
  }
  virtual int MouseMotion (int bt, float x, float y);
};

#endif
