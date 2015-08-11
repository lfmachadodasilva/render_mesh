#ifndef VGL_SPLINE_NAVIG_H
#define VGL_SPLINE_NAVIG_H

#include <vgl/hnd/navig.h>
#include <splib/splib.h>
#include <vglac/defines.h>

class VglCamera;

class VGLAC_API VglSplineNavigHandler : public VglNavigHandler
{
protected:
  Spline m_spline;
  VglCamera* m_camera;
  float m_sPos;

public:
  /**
   * Internal function. not to be called.
   */
  void CalcTranslation ();
protected:
  virtual void DoNavigThrough ();
  void Begin ();
  virtual void Translate (float velx, float vely, float velz, double dt)
  {
    // just capture dt
    m_dt = dt;
    VglNavigHandler::Translate(velx,vely,velz,dt);
  }

public:
  static const char* CLASSNAME () { return "SplineNavigHandler"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
  /**
   * Constructs a new navig handler.
   * 'surface' is the view surface associated with this handler.
   * 'maxvel' is the maximum navigation velocity. (world units/second)
   * 'accel' is the navigation acceleration. (world units/second^2)
   */
  VglSplineNavigHandler (VglViewSurface* surface, float maxvel=0.2f, float accel=1.0f);
  virtual ~VglSplineNavigHandler ();
  
  void Draw ();
  virtual bool AddPosition(float x, float y, float z);
  virtual void ResetSpline();
private:
  double m_dt;
};

#endif
