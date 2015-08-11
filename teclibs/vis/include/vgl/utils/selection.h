#ifndef VGL_SELECTION_H
#define VGL_SELECTION_H

#include <GL/glew.h>
#include <vgl/handler.h>
#include <vgl/defines.h>
#include <vgl/hitrecord.h>
#include <vgl/canvas.h>

class VGL_API VglSelectionRenderer
{
public:
  virtual ~VglSelectionRenderer ()
  {
  }
  /**
   * Called to render the scene geometry in selection mode.
   * It is expected that this function pushes/pops names into the name stack.
   */
  virtual void SelectionRender () = 0;
};

class VGL_API VglSelectionRendererCB : public VglSelectionRenderer
{
public:
  VglSelectionRendererCB () : m_func(NULL), m_data(NULL)
  {
  }
  virtual ~VglSelectionRendererCB ()
  {
  }
  void SetFunc (VglSelectionFunction func, void *data=NULL)
  {
    m_func = func;
    m_data = data;
  }
  VglSelectionFunction GetFunc () const
  {
    return m_func;
  }
  void* GetFuncData () const
  {
    return m_data;
  }
private:
  virtual void SelectionRender ()
  {
    if (m_func)
      m_func(m_data);
  }
  VglSelectionFunction m_func;
  void *m_data;
};

class VGL_API VglSelectionHitsProcessor
{
public:
  virtual ~VglSelectionHitsProcessor ()
  {
  }
  virtual void ProcessHits (VglSelectionHit *hits, int n) = 0;
};

class VGL_API VglSelectionHitsProcessorCB : public VglSelectionHitsProcessor
{
public:
  VglSelectionHitsProcessorCB () : m_func(NULL), m_data(NULL)
  {
  }
  void SetFunc (VglProcessFunction func, void *data)
  {
    m_func = func;
    m_data = data;
  }
private:
  virtual void ProcessHits (VglSelectionHit *hits, int n)
  {
    if (m_func)
      m_func(hits,n,m_data);
  }
  VglProcessFunction m_func;
  void *m_data;
};

class VGL_API VglClosestHitProcessor : public VglSelectionHitsProcessor
{
public:
  VglClosestHitProcessor ();
  bool FoundHit () const
  {
    return m_pclosesthit != NULL;
  }
  /**
   * Gets the minimum Z of all primitives hit (ranges from 0 to 1).
   */
  float GetClosestHitZmin () const
  {
    if (FoundHit())
      return m_closesthit.GetZMinFloat();
    else
      return -5.0f;
  }
  /**
   * Gets the name stack depth of the closest hit.
   * Returns 0 in case there was no hit at all.
   */
  int GetNameStackDepth () const
  {
    if (FoundHit())
      return m_closesthit.GetNameStackDepth();
    else
      return 0;
  }
  /**
   * Gets the name stack of the hit (GetNameStackDepth values).
   * Returns NULL in case there was no hit at all.
   */
  const GLuint* GetNameStack () const
  {
    if (FoundHit())
      return m_closesthit.GetNameStack();
    else
      return NULL;
  }
  /**
   * Gets the value of the hit name stack at index 'index'.
   */
  unsigned int GetNameStackValue (int index) const
  {
    if (FoundHit())
      return m_closesthit.GetNameStack()[index];
    else
      return 0xFFFFFFFF;
  }
  virtual void ProcessHits (VglSelectionHit *hits, int n);
private:
  VglSelectionHit m_closesthit;
  VglSelectionHit *m_pclosesthit;
};

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
class VGL_API VglSelection
{
public:
  /**
   * Constructor.
   * 'surface' is the viewing surface associated with the handler (optional).
   */
  VglSelection (VglViewSurface* surface);
  /**
   * Destructor.
   */
  virtual ~VglSelection ();
  /**
   * Specifies a new seletion buffer size (default=space for 512 'names').
   */
  void SetSelBufferSize (int sel_buf_size);
  /**
   * Obtains the current selection buffer size.
   */
  int GetSelBufferSize () const
  {
    return m_buffersize;
  }
  /**
   * Specifies a new picking tolerance (raster coordinates) (default=5x5 pixels).
   */
  void SetPickingTolerance (double tolw, double tolh)
  {
    m_tolw = tolw;
    m_tolh = tolh;
  }
  double GetPickingToleranceW() const
  {
    return m_tolw;
  }
  double GetPickingToleranceH() const
  {
    return m_tolh;
  }
  void SetSelectionRenderer (VglSelectionRenderer *renderer)
  {
    m_renderer = renderer;
  }
  void SetSelectionHitsProcessor (VglSelectionHitsProcessor *processor)
  {
    m_processor = processor;
  }
  VglSelectionRenderer* GetSelectionRenderer () const
  {
    return m_renderer;
  }
  VglSelectionHitsProcessor* GetSelectionHitsProcessor () const
  {
    return m_processor;
  }
  /**
   * Performs picking at the selected region.
   * 'renderer' renders the geometry in selection mode.
   * 'processor' processes the selection hits.
   * 'x' and 'y' are the normalized x and y window coordinates.
   */
  void Pick (VglSelectionRenderer *renderer, VglSelectionHitsProcessor *processor, float x, float y) const;
  /**
   * Performs picking at the selected region.
   * 'x' and 'y' are the normalized x and y window coordinates.
   * Uses the default renderer/processor.
   */
  void Pick (float x, float y) const
  {
    Pick(m_renderer,m_processor,x,y);
  }
  /**
   * Trace a ray and find its intersections with the geometry.
   * This is implemented by setting up a very thin orthographic viewing
   * frustum to simulate the ray. Its dimensions are (2*wtolx,2*wtoly,wrange).
   *
   * Everything inside this viewing volume will cause a selection hit.
   * 'renderer' renders the geometry in selection mode.
   * 'processor' processes the selection hits.
   * 'wposition' is the ray source
   * 'wdirection' is the ray direction.
   * 'wtolx' and 'wtoly' are the tolerances in world coordinates.
   * 'wrange' is the ray range in world coordinates.
   */
  void Trace (VglSelectionRenderer *renderer, VglSelectionHitsProcessor *processor, const AlgVector& wposition, const AlgVector& wdirection, float wtolx = 0.01, float wtoly = 0.01, float wrange = 1000.0) const;
  /**
   * Trace a ray and find its intersections with the geometry.
   * This is implemented by setting up a very thin orthographic viewing
   * frustum to simulate the ray. Its dimensions are (2*wtolx,2*wtoly,wrange).
   *
   * Everything inside this viewing volume will cause a selection hit.
   * 'wposition' is the ray source
   * 'wdirection' is the ray direction.
   * 'wtolx' and 'wtoly' are the tolerances in world coordinates.
   * 'wrange' is the ray range in world coordinates.
   * Uses the default renderer/processor.
   */
  void Trace (const AlgVector& wposition, const AlgVector& wdirection, float wtolx = 0.01, float wtoly = 0.01, float wrange = 1000.0) const
  {
    Trace(m_renderer,m_processor,wposition,wdirection,wtolx,wtoly,wrange);
  }
  /**
   * Gets all visible geometry, using the viewing canvas camera configuration.
   * 'renderer' renders the geometry in selection mode.
   * 'processor' processes the selection hits.
   */
  void GetVisible (VglSelectionRenderer *renderer, VglSelectionHitsProcessor *processor) const;
  /**
   * Gets all visible geometry, using the viewing canvas camera configuration.
   * 'renderer' renders the geometry in selection mode.
   * Uses the default renderer/processor.
   */
  void GetVisible () const
  {
    GetVisible(m_renderer,m_processor);
  }
  void SetViewSurface (VglViewSurface *surface)
  {
    m_surface = surface;
  }
  VglViewSurface* GetSurface () const
  {
    return m_surface;
  }
  bool unproject(VglSelectionHit* h, double winx, double winy, double* worldx, double* worldy, double* worldz);
  bool unproject(double winx, double winy, double winz, double* worldx, double* worldy, double* worldz);
  bool project(double worldx, double worldy, double worldz, double* winx, double* winy, double* winz);
private:
  void PreparePick(float x, float y, double tolw, double tolh) const;
  void PrepareSelection() const;
  void FinishSelection(VglSelectionHitsProcessor *processor) const;
  void FinishPick(VglSelectionHitsProcessor *processor) const;
  void FinishPick() const
  {
    FinishPick(m_processor);
  }
  void GetModelviewProjectionAndViewPort (double modelMatrix[16], double projMatrix[16], GLint viewport[4]);
private:
  // members
  VglViewSurface* m_surface;
  VglSelectionRenderer *m_renderer;
  VglSelectionHitsProcessor *m_processor;
  double m_tolw, m_tolh;
  int m_buffersize;
  GLuint* m_selectionbuffer;
  friend class VglSelectionHandler;
};

#endif

