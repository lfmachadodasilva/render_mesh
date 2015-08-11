#ifndef VGL_NAVIG_H
#define VGL_NAVIG_H

#include <vgl/handler.h>
#include <alg/vector.h>
#include <alg/matrix.h>
#include <uso/clock.h>
#include <vgl/utils/viewrotation.h>
#include <vgl/utils/centercursor.h>

class VglCanvas;
class VglViewSurface;

#define VGL_NAVIG_FORWARD     0
#define VGL_NAVIG_BACKWARD    1
#define VGL_NAVIG_LEFT        2
#define VGL_NAVIG_RIGHT       3
#define VGL_NAVIG_UP          4
#define VGL_NAVIG_DOWN        5
#define VGL_NAVIG_NDIRECTIONS 6

class VGL_API VglNavigHandler : public VglHandler
{
protected:
  void SetIsNavigating (int direction)
  {
    if (direction == VGL_NAVIG_FORWARD || direction == VGL_NAVIG_BACKWARD)
      m_turning = true;
    m_isnavigating[direction] = true;
    StartNavigation();
  }
  void NavigationStopped (int direction)
  {
    m_isnavigating[direction] = false;
    if (!m_isnavigating[VGL_NAVIG_FORWARD] && !m_isnavigating[VGL_NAVIG_BACKWARD])
      m_turning = false;
  }
  bool WasNavigating (int direction) const
  {
    return m_isnavigating[direction];
  }
  void StartNavigation ();
  void StopNavigation ();
  virtual bool IsRequestingNavigation (int direction)
  {
    switch(direction)
    {
      case VGL_NAVIG_FORWARD:
        return GetKey('w') || GetKey(VGL_KEY_UP)   || (IsCenteringCursor() && GetButton() == VGL_BUTTON_LEFT);
      case VGL_NAVIG_BACKWARD:
        return GetKey('s') || GetKey(VGL_KEY_DOWN) || (IsCenteringCursor() && GetButton() == VGL_BUTTON_RIGHT);
      case VGL_NAVIG_LEFT:
        return GetKey('a') || GetKey(VGL_KEY_LEFT);
      case VGL_NAVIG_RIGHT:
        return GetKey('d') || GetKey(VGL_KEY_RIGHT);
      case VGL_NAVIG_UP:
        return GetKey('r') || GetKey(VGL_KEY_PAGE_UP);
      case VGL_NAVIG_DOWN:
        return GetKey('f') || GetKey(VGL_KEY_PAGE_DOWN);
      default:
        return false;
    }
  }
  virtual void DoNavigThrough ();
  /**
   * Obtains the center cursor component of the navigation handler.
   * Allows customization of how cursor centering is used.
   */
  VglCenterCursor* GetCursorCenterer ()
  {
    return &m_centercursor;
  }
  VglViewRotation* GetViewRotation ()
  {
    return &m_rotation;
  }
  const AlgVector& GetCurrentVelocity () const
  {
    return m_vel;
  }
  /**
   * User is requesting a translation:
   * - with velocity 'velx' in the 'x' axis. ('A'/'D' or 'left/right' keys)
   * - with velocity 'vely' in the 'y' axis. ('R'/'F' or 'up/down' keys)
   * - with velocity 'velz' in the 'z' axis. ('A'/'D' or '<-'/'->' keys)
   * - has been requesting it for 'dt' seconds.
   *
   * This method is redefinable by derivating classes.
   *
   * In the VglNavigHandler context, the velocity means "translation in eye
   * space". A simple product between the velocity and the elapsed time
   * results in a translation in world units.
   */
  virtual void Translate (float velx, float vely, float velz, double dt);
public:
  static const char* CLASSNAME () { return "NavigHandler"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
  /**
   * Constructs a new navig handler.
   * 'surface' is the view surface associated with this handler.
   * 'maxspeed' is the maximum navigation speed. (world units/second)
   * 'accel' is the navigation acceleration. (world units/second^2)
   */
  VglNavigHandler (VglViewSurface* surface, float maxspeed=0.2f, float accel=1.0f);
  virtual ~VglNavigHandler ();
  virtual void SetViewSurface (VglViewSurface *surface)
  {
    m_surface = surface;
  }
  VglViewSurface* GetSurface () const
  {
    return m_surface;
  }
  void SetMaxVelocity (float maxspeed) // deprecated: wrong method name
  {
    SetMaxSpeed(maxspeed);
  }
  /**
   * Sets the maximum navigation speed. (world units/second)
   */
  virtual void SetMaxSpeed (float maxspeed)
  {
    m_maxspeed = maxspeed;
  }
  /**
   * Sets the navigation acceleration. (world units/second^2)
   */
  virtual void SetAcceleration (float accel)
  {
    m_accel = accel;
  }
  void SetRightButtonRotates (bool f)
  {
    m_rb_rotates = f;
  }
  bool GetRightButtonRotates () const
  {
    return m_rb_rotates;
  }
  virtual void IncreaseMaxSpeedAndAccel (float by)
  {
    m_maxspeed *= by; 
    m_accel  *= by;
  }
  virtual void DecreaseMaxSpeedAndAccel (float by)
  {
    m_maxspeed /= by; 
    m_accel  /= by;
  }
  /**
   * Obtains the maximum navigation speed.
   */
  float GetMaxSpeed () const
  {
    return m_maxspeed;
  }
  // deprecated: wrong name
  float GetMaxVelocity () const
  {
    return GetMaxSpeed();
  }
  float GetAcceleration () const
  {
    return m_accel;
  }
  void SetOnPlane (bool flag)
  {
    m_onplane = flag;
  }
  bool GetOnPlane () const
  {
    return m_onplane;
  }
  /**
   * Enables/disabled the drawing of a cursor in the direction of navigation.
   */
  void SetDrawCursor (bool flag)
  {
    m_drawcursor = flag;
  }
  void SetCenterCursor (bool flag)
  {
    m_centercursor.SetMustCenterCursor(flag);
  }
  bool IsCenteringCursor () const
  {
    return m_centercursor.IsCenteringCursor();
  }
  bool GetCenterCursor () const //deprecated
  {
    return IsCenteringCursor();
  }
  virtual void SetYRotationAxis (const AlgVector& axis)
  {
    m_rotation.SetYRotationAxis(axis);
  }
  virtual void SetYRotationAxis (float vx, float vy, float vz)
  {
    m_rotation.SetYRotationAxis(vx,vy,vz);
  }
  virtual void UnsetYRotationAxis ()
  {
    m_rotation.UnsetYRotationAxis();
  }
  AlgVector GetYRotationAxis () const
  {
    return m_rotation.GetYRotationAxis();
  }
  virtual void Begin ();
  virtual void End ();
  virtual int Keyboard (int k, int st, float x, float y);
  virtual int MouseButton (int bt, int st, float x, float y);
  virtual int MouseMotion (int bt, float x, float y);
  virtual int MouseEntry (bool st);
  virtual int PostRedraw ();
  // deprecated
  void SetAnimated (bool flag);
  bool GetAnimated ();
protected:
  /**
   * Keyboard pressed callback. Called when this event occurs.
   * If returns true, normal navigation event handling will occur,
   * otherwise it won't.
   */
  virtual bool KeyboardPressed (int k, float x, float y)
  {
    return true;
  }
  /**
   * Keyboard released callback. Called when this event occurs.
   * If returns true, normal navigation event handling will occur,
   * otherwise it won't.
   */
  virtual bool KeyboardReleased (int k, float x, float y)
  {
    return true;
  }
  /**
   * Mouse button pressed callback. Called when this event occurs.
   * If returns true, normal navigation event handling will occur,
   * otherwise it won't.
   */
  virtual bool MouseButtonPressed (int bt, float x, float y)
  {
    return true;
  }
  /**
   * Mouse button released callback. Called when this event occurs.
   * If returns true, normal navigation event handling will occur,
   * otherwise it won't.
   */
  virtual bool MouseButtonReleased (int bt, float x, float y)
  {
    return true;
  }
  /**
   * Mouse motion callback. Called when this event occurs.
   * If returns true, normal navigation event handling will occur,
   * otherwise it won't.
   */
  virtual bool MouseMoved (int bt, float x, float y)
  {
    return true;
  }
  static void NavigThrough (void* data);
  static void Redraw (void* data);
private:
  VglViewRotation m_rotation;
  VglCenterCursor m_centercursor;
  bool m_isnavigating[VGL_NAVIG_NDIRECTIONS];
  bool m_navigating;
  bool m_turning;
  float m_maxspeed, m_accel;
  bool m_onplane;
  bool m_drawcursor;
  bool m_rb_rotates;
  char m_constraint;
  double m_last_t;
  AlgVector m_vel;
  USOClock m_clock;
  VglViewSurface* m_surface;
};

#endif
