#ifndef VGL_CENTERCURSOR_H
#define VGL_CENTERCURSOR_H

#include <vgl/viewsurface.h>

class VGL_API VglCenterCursor
{
public:
  VglCenterCursor (VglViewSurface *surface);
  void Activate ();
  void Deactivate ();
  void SetReturnPosition (float x, float y);
  void SetMustCenterCursor (bool flag);
  bool IsCenteringCursor () const
  {
    return m_centering_cursor;
  }
  void ToggleMustCenterCursor ()
  {
    SetMustCenterCursor(!IsCenteringCursor());
  }
  bool IsMotionEventUsable (float lastx, float lasty);
  void MouseEnteredSurface ();
  void MouseLeftSurface ();
private:
  bool IsActive () const
  {
    return m_active;
  }
  void SetCursorCentered (bool f)
  {
    m_cursor_centered = f;
  }
  bool IsCursorCentered () const
  {
    return m_cursor_centered;
  }
private:
  VglViewSurface *m_surface;
  float m_xreturn;
  float m_yreturn;
  bool m_active;
  bool m_centering_cursor;
  bool m_cursor_centered;
  bool m_return_when_done;
};

#endif

