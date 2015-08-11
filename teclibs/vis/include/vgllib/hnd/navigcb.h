#ifndef VGL_NAVIG_CB_H
#define VGL_NAVIG_CB_H

#include <vgl/hnd/navig.h>
#include <vgllib/defines.h>

class VGLLIBAPI VglNavigHandlerCB : public VglNavigHandler
{
public:
  typedef bool (*PressedFunc) (int bt, float x, float y, void* data);
  typedef bool (*ReleasedFunc) (int bt, float x, float y, void* data);
  typedef bool (*MovedFunc) (int bt, float x, float y, void* data);
  static const char* CLASSNAME () { return "NavigHandlerCB"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
  /**
   * Constructs a new navig handler.
   * 'surface' is the view surface associated with this handler.
   * 'maxspeed' is the maximum navigation speed. (world units/second)
   * 'accel' is the navigation acceleration. (world units/second^2)
   */
  VglNavigHandlerCB (VglViewSurface* surface, float maxspeed=0.2f, float accel=1.0f);
  virtual ~VglNavigHandlerCB ();
  void SetKeyPressedFunc (PressedFunc func, void* data=NULL);
  void SetKeyReleasedFunc (ReleasedFunc func, void* data=NULL);
  void SetMouseButtonPressedFunc (PressedFunc func, void* data=NULL);
  void SetMouseButtonReleasedFunc (ReleasedFunc func, void* data=NULL);
  void SetMouseMotionFunc (MovedFunc func, void* data=NULL);
  void SetPostRedrawFunc (VglFunction func, void* data=NULL);
  int PostRedraw ();
protected:
  virtual bool KeyboardPressed (int k, float x, float y);
  virtual bool KeyboardReleased (int k, float x, float y);
  virtual bool MouseButtonPressed (int bt, float x, float y);
  virtual bool MouseButtonReleased (int bt, float x, float y);
  virtual bool MouseMoved (int bt, float x, float y);
private:
  PressedFunc m_key_pressed_func;
  void* m_key_pressed_data;
  ReleasedFunc m_key_released_func;
  void* m_key_released_data;
  PressedFunc m_mouse_pressed_func;
  void* m_mouse_pressed_data;
  ReleasedFunc m_mouse_released_func;
  void* m_mouse_released_data;
  MovedFunc m_mouse_motion_func;
  void* m_mouse_motion_data;
  VglFunction m_post_redraw_func;
  void* m_post_redraw_data;
};

#endif

