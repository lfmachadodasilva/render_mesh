//* rotatenavig.h
// fabraham@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// May 2006

#ifndef VGL_ROTATE_NAVIG_H
#define VGL_ROTATE_NAVIG_H

#include <vgl/hnd/navig.h>
#include <vgl/hnd/rotation.h>
#include <vgl/hnd/selection.h>
#include <vgl/utils/modelrotation.h>
#include <vgllib/defines.h>

class VGLLIBAPI VglRotationNavigHandler : public VglNavigHandler
{
  VglModelRotation m_modelrotation;
  AlgVector m_center;
  float m_maxdisttotarget;
  float GetMaximumDistanceToTarget () const
  {
    return m_maxdisttotarget;
  }
  void SetMaximumDistanceToTarget (float f)
  {
    m_maxdisttotarget = f;
  }
  float m_lasthitzmin;
  double m_vtdt;
  double m_vtt0;
  double m_vtlastt;
  float m_vtwx;
  float m_vtwy;
  float m_usermaxspeed;
  float m_useraccel;
  bool m_ccursor_enabled;
  bool IsCenterCursorEnabled () const
  {
    return m_ccursor_enabled;
  }
  AlgVector GetObs2TargetVectorEye () const;
  AlgVector GetObs2TargetVectorWorld () const
  {
    return GetTarget() - GetObserverPosition();
  }
  AlgVector GetObserverPosition () const;
  AlgVector GetTarget () const
  {
    return m_center;
  }
  double GetViewDirTransitionTime () const
  {
    return m_vtdt;
  }
  void ObtainRotationAngles (float *anglex, float *angley);
  bool RedefineCenter(double x, double y);
  void StartViewDirTransition();
  void DoViewDirTransition ();
  void EndViewDirTransition();
  static void DoViewDirTransition (void *data)
  {
    VglRotationNavigHandler *r = (VglRotationNavigHandler*)data;
    r->DoViewDirTransition();
  }
protected:
  virtual bool IsRequestingNavigation (int direction);
  virtual void Translate (float velx, float vely, float velz, double displacement);
public:
  static const char* CLASSNAME () { return "RotationNavigHandler"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
  VglRotationNavigHandler (VglViewSurface* surface, float maxspeed=0.2f, float accel=1.0f);
  virtual ~VglRotationNavigHandler ();
  void SetViewDirTransitionTime (double dt)
  {
    m_vtdt = dt;
  }
  void EnableCenterCursor ();
  void DisableCenterCursor ();
  void ToggleCenterCursor ()
  {
    if (IsCenterCursorEnabled())
      DisableCenterCursor();
    else
      EnableCenterCursor();
  }
  void SetPercentageOfMaxSpeed (float percentage);
  virtual void Begin ();
  virtual int Keyboard (int k, int st, float x, float y);
  virtual int MouseButton (int bt, int st, float x, float y);
  virtual int MouseMotion (int bt, float x, float y);
  virtual void SetMaxSpeed (float maxspeed);
  virtual void SetAcceleration (float accel);
  virtual void IncreaseMaxSpeedAndAccel (float by);
  virtual void DecreaseMaxSpeedAndAccel (float by);
  virtual void SetYRotationAxis (const AlgVector& axis)
  {
    VglNavigHandler::SetYRotationAxis(axis);
    m_modelrotation.SetYRotationAxis(axis);
  }
  virtual void SetYRotationAxis (float vx, float vy, float vz)
  {
    VglNavigHandler::SetYRotationAxis(vx,vy,vz);
    m_modelrotation.SetYRotationAxis(vx,vy,vz);
  }
  virtual void UnsetYRotationAxis ()
  {
    VglNavigHandler::UnsetYRotationAxis();
    m_modelrotation.UnsetYRotationAxis();
  }
  void DrawCenterPoint ();
                                  int PostRedraw ()
                                  {
                                  DrawCenterPoint();
                                  return 1;
                                  }
private:
};

#endif
