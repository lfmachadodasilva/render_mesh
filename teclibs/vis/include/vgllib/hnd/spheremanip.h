// spheremanip.h
// fabraham@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// May 2006

#ifndef VGL_SPHERE_MANIP_H
#define VGL_SPHERE_MANIP_H

#include <vgl/hnd/navig.h>
#include <vgl/hnd/rotation.h>
#include <vgl/hnd/selection.h>
#include <vgl/hnd/transformcenter.h>
#include <vgl/utils/axis.h>
#include <vgl/utils/modelrotation.h>
#include <vgl/utils/centerfromfrustum.h>
#include <vgl/utils/repeat.h>
#include <vgllib/defines.h>

class CenteredCrossWindow;

class VGLLIBAPI VglSphereManipHandler : public VglNavigHandler, public VglTransformCenterUser
{
public:
  /**
   * NewAxisPosFunction callback type.
   */
  typedef void (*NewCenterFunction)(float x, float y, float z, void *data);
  static const char* CLASSNAME () { return "SphereManipHandler"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
  VglSphereManipHandler (VglViewSurface* surface, float maxspeed=0.2f, float accel=1.0f);
  virtual ~VglSphereManipHandler ();
  void SetViewSurface (VglViewSurface *surface);
  void SetViewDirTransitionTime (double dt)
  {
    m_vtdt = dt;
  }
  bool IsConstrainingToUpperHemisphere () const
  {
    return m_modelrotation.IsConstrainingToUpperHemisphere();
  }
  void ConstrainToUpperHemisphere ()
  {
    m_modelrotation.ConstrainToUpperHemisphere();
  }
  void SetConstrainingToUpperHemisphere (bool f)
  {
    m_modelrotation.SetConstrainingToUpperHemisphere(f);
  }
  void SetAnimated(bool flag);
  virtual void SetYRotationAxis (const AlgVector& axis);
  virtual void SetYRotationAxis (float vx, float vy, float vz);
  virtual void UnsetYRotationAxis ()
  {
    VglNavigHandler::UnsetYRotationAxis();
    m_modelrotation.UnsetYRotationAxis();
  }
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
  void DrawCenterPoint ();
  void SetNewCenterFunc (NewCenterFunction func, void *data);
  void SetRotationCenter (float x, float y, float z);
  void UnsetRotationCenter ();
  bool HasRotationCenter () const
  {
    return m_hasrcenter;
  }
  AlgVector GetRotationCenter () const;
  void GetRotationCenterv (float c[3]) const
  {
    AlgVector rcenter = GetRotationCenter();
    c[0] = rcenter.x;
    c[1] = rcenter.y;
    c[2] = rcenter.z;
  }
  void GetRotationCenter (double *x, double *y, double *z) const
  {
    AlgVector rcenter = GetRotationCenter();
    if (x)
      *x = rcenter.x;
    if (y)
      *y = rcenter.y;
    if (z)
      *z = rcenter.z;
  }
  /**
   * Specifies the selection buffer size (selection is used internally).
   */
  void SetSelBufferSize (int sel_buf_size);
  void SetThickness(float thickness)
  {
    m_render_axis.SetThickness(thickness);
  }
  float GetThickness() const
  {
    return m_render_axis.GetThickness();
  }
  void SetAxisSize(float size)
  {
    m_render_axis.SetAxisSize(size);
  }
  float GetAxisSize() const
  {
    return m_render_axis.GetAxisSize();
  }
  bool IsDrawingAxis() const
  {
    return m_draw_axis;
  }
  void SetDrawAxis (bool flag)
  {
    m_draw_axis = flag;
  }
  void SetDrawCenterPoint (bool flag)
  {
    m_draw_center_point = flag;
  }
protected:
  bool Pick (float x, float y, double wtol, double htol, AlgVector* world_point);
  // vglhandler methods
  virtual void Begin ();
  virtual void End ();
  virtual int Keyboard (int k, int st, float x, float y);
  virtual int MouseButton (int bt, int st, float x, float y);
  virtual int MouseMotion (int bt, float x, float y);
  virtual int MouseWheel (float delta, float x, float y);
  virtual int PostRedraw ();
  // vglnavighandler methods
  virtual bool IsRequestingNavigation (int direction);
  virtual void Translate (float velx, float vely, float velz, double displacement);
  // vglspheremaniphandler
  virtual void Translate (double ds);
  bool IsPanning () const
  {
    return m_ispanning;
  }
  virtual void SetPanning (bool f)
  {
    m_ispanning = f;
  }
  virtual void DoNavigThrough ()
  {
    VglNavigHandler::DoNavigThrough();
  }
private:
  float GetMaximumDistanceToTarget () const
  {
    return m_maxdisttotarget;
  }
  void SetMaximumDistanceToTarget (float f)
  {
    m_maxdisttotarget = f;
  }
  float GetLastVelocitySign () const
  {
    return m_lastvelsign;
  }
  void SetLastVelocitySign (float dy)
  {
    m_lastvelsign = dy > 0.0f ? -1.0f : +1.0f;
  }
  AlgVector GetObs2TargetVectorEye () const;
  AlgVector GetObs2TargetVectorWorld () const
  {
    return GetTarget() - GetObserverPosition();
  }
  AlgVector GetObserverPosition () const;
  AlgVector GetTarget () const
  {
    return GetRotationCenter();
  }
  double GetViewDirTransitionTime () const
  {
    return m_vtdt;
  }
  void ObtainRotationAngles (float *anglex, float *angley);
  //bool RedefineCenterWindow(double x0, double x1, double y0, double y1);
  bool RedefineCenter (float x, float y)
  {
    return RedefineCenter(x,y,2.0,2.0);
  }
  bool RedefineCenter (float x, float y, double wtol, double htol);
  void StartViewDirTransition();
  void DoViewDirTransition ();
  void EndViewDirTransition ();
  void UpdateAngularSpeeds (double curr_t);
  static void DoViewDirTransition (void *data)
  {
    VglSphereManipHandler *r = (VglSphereManipHandler*)data;
    r->DoViewDirTransition();
  }
  void InitNavigation ();
  void UpdateTransformCenter ();
  void RepeatLastRotation ();
  void StartRepeatingLastRotation ();
  void StopRepeatingLastRotation ();
  void EndedDefiningWindow (float x, float y);
  static void RepeatLastTranslation (void *data)
  {
    VglSphereManipHandler *h = (VglSphereManipHandler*)data;
    h->RepeatLastTranslation();
  }
  static void RepeatLastRotation (void *data)
  {
    VglSphereManipHandler *h = (VglSphereManipHandler*)data;
    h->RepeatLastRotation();
  }
  void SetCenteringWindow (bool f)
  {
    m_centeringwindow = f;
  }
  bool IsCenteringWindow () const
  {
    return m_centeringwindow;
  }
  void StartRepeatingLastTranslation();
  void RepeatLastTranslation ();
  void StopRepeatingLastTranslation();
  void SetLastTranslation (double ds)
  {
    m_lasttranslation = ds;
  }
  double GetLastTranslation () const
  {
    return m_lasttranslation;
  }
  void DrawWindowCross ();
  void SetDefaultMaximumDistanceToTarget ();
private:
  VglModelRotation m_modelrotation;
  CenteredCrossWindow *m_window;
  VglCenterFromFrustum m_cff;
  VglAxisRender m_render_axis;
  AlgVector* m_pcenter;
  NewCenterFunction m_newcenterfunc;
  void *m_newcenterdata;
  double m_lasttranslation;
  float m_maxdisttotarget;
  float m_lasthitzmin;
  double m_vtdt;
  double m_vtt0;
  double m_vtlastt;
  float m_lastvelsign;
  float m_vtwx;
  float m_vtwy;
  char m_constraint;
  bool m_centeringwindow;
  bool m_hasrcenter;
  bool m_ispanning;
  bool m_draw_axis;
  bool m_draw_center_point;
};

#endif
