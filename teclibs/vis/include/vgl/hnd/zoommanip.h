// fabraham@tecgraf.puc-rio.br
// celes@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// May 2006
#ifndef VGL_ZOOMMANIP_H
#define VGL_ZOOMMANIP_H

#include <vgl/hnd/zoom.h>
#include <vgl/hnd/manip.h>
#include <vgl/utils/centerfromfrustum.h>
#include "transformcenter.h"

/**
 * ZoomManipHandler
 *
 * This is a special zoom handler, that works just like the default
 * zoom handler, but redefines the transform center of a manipulation handler.
 *
 * This transform center is found by trying to identify the scene's center of
 * interest, given the current zoom window.
 */
class VGL_API VglZoomManipHandler : public VglZoomHandler, public VglTransformCenterSpecifier
{
public:
  /**
   * Returns the event handler class classname.
   */
  static const char* CLASSNAME () { return "ZoomManipHandler"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
  /**
   * Constructs a new VglZoomManipHandler object.
   * The manipulation's center of rotation will be defined in the
   * manipulation handler 'manip'.
   */
  VglZoomManipHandler (VglViewSurface *surface);
  VglZoomManipHandler (VglViewSurface *surface, VglManipHandler *manip);
  virtual ~VglZoomManipHandler ();
  void SetViewSurface(VglViewSurface *surface)
  {
    VglZoomHandler::SetViewSurface(surface);
    m_cff.SetViewSurface(surface);
  }
  void DrawDebugPoints ();
  /**
   * Specifies a selection rendering callback.
   * If unspecified, the algorithm will use the surface's redraw callback to
   * render the scene.
   */
  virtual void SetSelectionRenderFunc (VglSelectionFunction f, void* data)
  {
    m_cff.SetSelectionRenderFunc(f,data);
  }
  VglSelectionFunction GetSelectionRenderFunc () const
  {
    return m_cff.GetSelectionRenderFunc();
  }
  void* GetSelectionRenderData () const
  {
    return m_cff.GetSelectionRenderData();
  }
  // vglhandler methods
  virtual int MouseButton (int bt, int st, float x, float y);
  virtual void UpdateTransformCenter();
  // vglzoomhandler methods
  virtual int UndoZoom ();
  virtual int RedoZoom ();
protected:
  // vgltransformcenterspecifier methods
  virtual void GetTransformCenter (float *ocx, float *ocy, float *ocz);
  virtual void SetTransformCenter(float cx, float cy, float cz);
private:
  VglCenterFromFrustum m_cff;
  float m_wcx, m_wcy, m_wcz;
  bool m_center_set;
};

#endif
