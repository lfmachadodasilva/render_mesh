// viewrcenter.h
// Tecgraf/PUC-Rio
// fabraham@tecgraf.puc-rio.br
// Jun 2006
#ifndef VGL_CENTER_FROM_FRUSTUM_H
#define VGL_CENTER_FROM_FRUSTUM_H

#include <vgl/utils/selection.h>
#include <GL/glew.h>
#include <assert.h>

/**
 * VglCenterFromFrustum
 * Obtains the transform center given a view frustum (defined by a vglcamera).
 */
class VGL_API VglCenterFromFrustum : public VglSelectionRenderer, public VglClosestHitProcessor
{
public:
  /**
   * Constructor.
   * 'surface' is the surface from which the camera is obtained.
   * 'sel_buf_size', if specified, defines the size of the selection buffer
   * used internally.
   */
  VglCenterFromFrustum (VglViewSurface* surface, int sel_buf_size = 512) :
    m_surface(surface),
    m_selection(surface),
    m_frustum(),
    m_selfunc(NULL),
    m_seldata(NULL),
    m_debugging(false)
  {
    m_selection.SetSelectionRenderer(this);
    m_selection.SetSelectionHitsProcessor(this);
    SetSelBufferSize(sel_buf_size);
  }
  virtual ~VglCenterFromFrustum ()
  {
  }
  void SetViewSurface (VglViewSurface *surface)
  {
    m_surface = surface;
    m_selection.SetViewSurface(surface);
  }
  /**
   * Specifies a selection rendering callback.
   * If unspecified, the algorithm will use the surface's redraw callback to
   * render the scene.
   */
  virtual void SetSelectionRenderFunc (VglSelectionFunction f, void* data=NULL)
  {
    m_selfunc = f;
    m_seldata = data;
  }
  VglSelectionFunction GetSelectionRenderFunc () const
  {
    if (m_selfunc != NULL)
      return m_selfunc;
    else
      return GetSurface()->GetRedrawFunc();
  }
  void* GetSelectionRenderData () const
  {
    if (m_selfunc != NULL)
      return m_seldata;
    else
      return GetSurface()->GetRedrawData();
  }
  /**
   * Obtains the transform center given the view surface camera configuration.
   * Will only write to variables 'cx', 'cy' and 'cz' if any transform center
   * was found.
   * Returns true if a transform center was found, false otherwise.
   */
  virtual bool ObtainTransformCenter (float *owcx, float *owcy, float *owcz)
  {
    m_debugpoints.Resize(0);
    m_debugcolors.Resize(0);
    if (TryCenterOfFrustum(0.05) || TryCenterOfFrustum(0.3) || TryWholeFrustum())
    {
      AlgVector owc = CalcTransformCenter(2*GetClosestHitZmin()-1);
      *owcx = owc.x;
      *owcy = owc.y;
      *owcz = owc.z;
      return true;
    }
    else
      return false;
  }
  void SetSelBufferSize (int sel_buf_size)
  {
    m_selection.SetSelBufferSize(sel_buf_size);
  }
  int GetSelBufferSize () const
  {
    return m_selection.GetSelBufferSize();
  }
  /**
   * Enables/disables the debugging of the algorithm.
   */
  virtual void SetDebugging (bool f)
  {
    m_debugging = f;
  }
  DsArray<AlgVector>& GetDebugPoints ()
  {
    return m_debugpoints;
  }
  DsArray<AlgVector>& GetDebugColors ()
  {
    return m_debugcolors;
  }
  /**
   * Draws debugging info for the algorithm.
   */
  void DrawDebug ()
  {
    m_frustum.Draw();
  }
protected:
  virtual bool TryCenterOfFrustum (double sizearoundcenter)
  {
    int x, y, w, h;
    GetSurface()->GetViewport(&x,&y,&w,&h);
    // preparing a pick matrix centered at the middle of the screen,
    // sized 'sizearoundcenter' times the screen size:
    m_selection.SetPickingTolerance(w*sizearoundcenter,h*sizearoundcenter);
    m_selection.Pick(0.5f,0.5f);
    return FoundHit();
  }
  virtual bool TryWholeFrustum ()
  {
    m_selection.GetVisible();
    return FoundHit();
  }
  virtual void SelectionRender () // vglselectionrenderer
  {
    if (DebuggingEnabled())
      m_frustum.Update();
    if (GetSelectionRenderFunc())
      GetSelectionRenderFunc()(GetSelectionRenderData());
    else
    {
      VglFunction redraw = GetSurface()->GetRedrawFunc();
      if (redraw)
      {
        glInitNames();
        glPushName(0);
        redraw(GetSurface()->GetRedrawData());
        glPopName();
      }
    }
  }
  VglViewSurface* GetSurface () const
  {
    return m_surface;
  }
  bool DebuggingEnabled () const
  {
    return m_debugging;
  }
private:
  AlgVector CalcTransformCenter(float zmin)
  {
    VglCamera *camera = GetSurface()->GetCamera();
    AlgMatrix pvinv = camera->GetProjectionMatrix();
    pvinv.Accum(camera->GetViewMatrix());
    pvinv.Invert(); // projectionview inverse: takes from clipping space to world space
    // obtain a point at the center of the frustum with the closest Z from the selection
    AlgVector zmincenter  = pvinv.Transform(0.0f,0.0f,zmin);
    AlgVector znearcenter = pvinv.Transform(0.0f,0.0f,-1.0f);
    // obtain viewing direction
    AlgVector viewdir = zmincenter - znearcenter;
    viewdir.Normalize();
    // obtain the length of the intersection between the frustum and the
    // plane z=zmin (worldspace)
    AlgVector topleft     = pvinv.Transform(-1.0f, 1.0f,zmin);
    AlgVector bottomleft  = pvinv.Transform(-1.0f,-1.0f,zmin);
    AlgVector bottomright = pvinv.Transform( 1.0f,-1.0f,zmin);
    float averagelen = ((bottomleft-bottomright).Length() + (topleft-bottomleft).Length()) * 0.50f;
    AlgVector result = (zmincenter + viewdir*averagelen*0.5f);
    if (DebuggingEnabled())
    {
      m_debugpoints.Append(pvinv.Transform(0.0f,0.0f,1.0f));   m_debugcolors.Append(AlgVector(1,0,1));
      m_debugpoints.Append(topleft);                           m_debugcolors.Append(AlgVector(0,1,1));
      m_debugpoints.Append(bottomright);                       m_debugcolors.Append(AlgVector(0,1,1));
      m_debugpoints.Append(bottomleft);                        m_debugcolors.Append(AlgVector(0,1,1));
      m_debugpoints.Append(pvinv.Transform( 1.0f, 1.0f,zmin)); m_debugcolors.Append(AlgVector(0,1,1));
      m_debugpoints.Append(zmincenter);                        m_debugcolors.Append(AlgVector(0,0,1));
      m_debugpoints.Append(result);                            m_debugcolors.Append(AlgVector(1,0,0));
    }
    return result;
  }
  // private members
  VglViewSurface *m_surface;
  VglSelection m_selection;
  VglFrustum m_frustum;
  DsArray<AlgVector> m_debugpoints;
  DsArray<AlgVector> m_debugcolors;
  VglSelectionFunction m_selfunc;
  void *m_seldata;
  bool m_debugging;
};

#endif
