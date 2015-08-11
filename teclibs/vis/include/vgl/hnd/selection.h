#ifndef VGL_SELECTIONHANDLER_H
#define VGL_SELECTIONHANDLER_H

#include <vgl/handler.h>
#include <vgl/defines.h>
#include <vgl/hitrecord.h>
#include <vgl/canvas.h>
#include <vgl/utils/selection.h>

#ifndef __GNUG__
# pragma warning( disable : 4355 ) // disabling 'this used in initializer list' warning
#endif

/**
 * This class provides the basic functionality for all selection handlers. 
 * It requires the setup of one callback: the selection render callback. 
 * This callback will be called in selection mode and must load/push/pop names 
 * into the name stack, names which will be returned in the selection results.
 *
 * Classes derived from this class must implement the process method, 
 * which receives a list of selection hits (see VglHitRecord for more information).
 *
 * It also defines methods to perform selection:
 * - by picking (clicking).
 * - tracing rays and obtaining the ray intersections with the geometry.
 * - obtaining all visible geometry.
 * - at any modelview/projection configuration.
 */
class VGL_API VglSelectionHandler : public VglHandler
{
public:
  /**
   * Returns the event handler class classname.
   */  
  static const char* CLASSNAME () { return "SelectionHandler"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
  /**
   * Default constructor.
   * 'surface' is the viewing surface associated with the handler.
   * 'sel_buf_size' is the size of the selection buffer used.
   * 'tolw' and 'tolh' are the picking tolerances in raster coordinates (width and height).
   */
  VglSelectionHandler (VglViewSurface* surface, int sel_buf_size = 512, double tolw = 5.0, double tolh = 5.0) :
    m_selection(surface),
    m_processor(this)
  {
    m_selection.SetSelBufferSize(sel_buf_size);
    m_selection.SetPickingTolerance(tolw,tolh);
    m_selection.SetSelectionHitsProcessor(&m_processor);
  }
  /**
   * Destructor.
   */
  virtual ~VglSelectionHandler ()
  {
  }
  void SetViewSurface (VglViewSurface *surface)
  {
    m_selection.SetViewSurface(surface);
  }
  VglViewSurface* GetSurface () const
  {
    return m_selection.GetSurface();
  }
  /**
   * Specifies a new selection buffer size.
   */
  void SetSelBufferSize (int sel_buf_size)
  {
    m_selection.SetSelBufferSize(sel_buf_size);
  }
  /**
   * Specifies a new picking tolerance (raster coordinates).
   */
  void SetPickingTolerance (double tolw, double tolh)
  {
    m_selection.SetPickingTolerance(tolw,tolh);
  }
  /**
   * Selection function data type.
   */  
  typedef void (*SelectionFunc)(void* data);
  /**
   * Sets the rendering function used for selection.
   * 'sel_render_func' is the callback that will be called to render the geometry. It is expected that it pushes/pops names into the name stack.
   * 'data' is the parameter that will be passed to the selection render callback.
   */
  virtual void SetSelectionRenderFunc (SelectionFunc f, void* data)
  {
    m_render.SetFunc(f,data);
    m_selection.SetSelectionRenderer(&m_render);
  }
  /**
   * Sets the renderer used for selection.
   * 'renderer' is an object that implements VglSelectionRenderer.
   */
  virtual void SetSelectionRenderer (VglSelectionRenderer *renderer)
  {
    m_selection.SetSelectionRenderer(renderer);
  }
  /**
   * Trace a ray and find its intersections with the geometry.
   * This is implemented by setting up a very thin orthographic viewing frustum to simulate the ray. Its dimensions are (2*tolx,2*toly,range).
   * Everything inside this viewing volume will cause a selection hit.
   * 'position' is the ray source
   * 'direction' is the ray direction.
   * 'tolx' and 'toly' are the tolerances in world coordinates.
   * 'range' is the ray range in world coordinates.
   */
  virtual void Trace (VglSelectionRenderer *renderer, AlgVector& position, AlgVector& direction, float tolx = 0.01, float toly = 0.01, float range = 1000.0)
  {
    m_selection.Trace(renderer,&m_processor,position,direction,tolx,toly,range);
  }
  /**
   * Trace a ray and find its intersections with the geometry.
   * This is implemented by setting up a very thin orthographic viewing frustum to simulate the ray. Its dimensions are (2*tolx,2*toly,range).
   * Everything inside this viewing volume will cause a selection hit.
   * 'position' is the ray source
   * 'direction' is the ray direction.
   * 'tolx' and 'toly' are the tolerances in world coordinates.
   * 'range' is the ray range in world coordinates.
   */
  virtual void Trace (AlgVector& position, AlgVector& direction, float tolx = 0.01, float toly = 0.01, float range = 1000.0)
  {
    m_selection.Trace(position,direction,tolx,toly,range);
  }
  /**
   * Performs picking at the selected region.
   * 'x' and 'y' are the normalized x and y window coordinates.
   */
  virtual void Pick (float x, float y, VglSelectionRenderer *renderer)
  {
    m_selection.Pick(renderer,&m_processor,x,y);
  }
  /**
   * Performs picking at the selected region.
   * 'x' and 'y' are the normalized x and y window coordinates.
   */
  virtual void Pick (float x, float y)
  {
    m_selection.Pick(x,y);
  }
  /**
   * Gets all visible geometry, using the viewing canvas camera information.
   */
  virtual void GetVisible (VglSelectionRenderer *renderer)
  {
    m_selection.GetVisible(renderer,&m_processor);
  }
  /**
   * Gets all visible geometry, using the viewing canvas camera information.
   */
  virtual void GetVisible ()
  {
    m_selection.GetVisible();
  }
protected:
  /**
   * Hit Process Function (called after the selection rendering function)
   * Must be implemented by subclasses.
   */
  virtual void ProcessFunction (VglSelectionHit* hits, int n) = 0;
  bool unproject(VglSelectionHit* h, double winx, double winy, double* worldx, double* worldy, double* worldz)
  {
    return m_selection.unproject(h,winx,winy,worldx,worldy,worldz);
  }
  bool unproject(double winx, double winy, double winz, double* worldx, double* worldy, double* worldz)
  {
    return m_selection.unproject(winx,winy,winz,worldx,worldy,worldz);
  }
  bool project(double worldx, double worldy, double worldz, double* winx, double* winy, double* winz)
  {
    return m_selection.project(worldx,worldy,worldz,winx,winy,winz);
  }
  /**
   * Deprecated.
   */
  void PreparePick(float x, float y, double tolw, double tolh)
  {
    m_selection.PreparePick(x,y,tolw,tolh);
  }
  /**
   * Deprecated.
   */
  void FinishPick()
  {
    m_selection.FinishPick();
  }
  /**
   * Deprecated.
   */
  double GetTolW () const
  {
    return m_selection.GetPickingToleranceW();
  }
  /**
   * Deprecated.
   */
  double GetTolH () const
  {
    return m_selection.GetPickingToleranceH();
  }
private:
  VglSelection m_selection;
  struct VGL_API Processor : public VglSelectionHitsProcessor
  {
    VglSelectionHandler *m_handler;
    Processor (VglSelectionHandler *handler) : m_handler(handler)
    {
    }
    void ProcessHits (VglSelectionHit *hits, int n)
    {
      m_handler->ProcessFunction(hits,n);
    }
  };
  VglSelectionRendererCB m_render;
  Processor m_processor;
  friend struct Processor;
};

#endif
