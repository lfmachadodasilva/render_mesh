//* triphase.h
// An active triphase map color scale.
// Tecgraf/PUC-Rio
// Nov 2004

#ifndef SCIUTILS_TRIPHASEMAP_H
#define SCIUTILS_TRIPHASEMAP_H

#include <sciutils/lua/sciutilsiuplua.h>
#include <sciutils/actelem2dhv.h>
#include <utl/utlstring.h>
#include <iup.h>
extern "C" {
#include <lua.h>
}

//* *SciActiveElementTriPhaseMap* Class
// Represents an active triphase map color scale.
class SCIUTILSIUPAPI SciActiveElementTriPhaseMap : public Sci2DActiveElementHV
{
public:
  SciActiveElementTriPhaseMap(const char *name);
  virtual ~SciActiveElementTriPhaseMap();
  virtual void SetDrawableAreaH (float x, float y, float w, float h);
  virtual void SetDrawableAreaV (float x, float y, float w, float h);
  /**
  * Function called when the user presses the right mouse button.
  * If no function is set, the default menu is shown.
  */
  void SetRightButtonFunc (lua_State *L, int lo);
  virtual void SetDragEnabled (bool f)
  {
    if (f == IsDragEnabled())
      return;
    Sci2DActiveElementHV::SetDragEnabled(f);
    UpdateDrawableArea();
  }
  virtual void SetHorizontal (bool v)
  {
    if (v == IsHorizontal())
      return;
    Sci2DActiveElementHV::SetHorizontal(v);
    UpdateDrawableArea();
  }
  void SetTopString(const char* s)
  {
    if (utlStringEqual(m_top_string, s))
      return;
    m_top_string = s;
    UpdateDrawableArea();
  }
  void SetLeftString(const char* s)
  {
    if (utlStringEqual(m_left_string, s))
      return;
    m_left_string = s;
    UpdateDrawableArea();
  }
  void SetRightString(const char* s)
  {
    if (utlStringEqual(m_right_string, s))
      return;
    m_right_string = s;
    UpdateDrawableArea();
  }
protected:
  virtual void Drag (float ammountx, float ammounty)
  {
    Sci2DActiveElementHV::Drag(ammountx,ammounty);
    UpdateDrawableArea();
  }
  bool Pick(float x, float y);
  void cbButton(float x, float y, int mbt, int mst, VglNotifier *ntf);
  void doRender();
private:
  void CalcDrawnAreaAndTriangleAreaH (
    float drawable_x,
    float drawable_y,
    float drawable_w,
    float drawable_h,
    float *odrawnx,
    float *odrawny,
    float *odrawnw,
    float *odrawnh,
    float *otrix,
    float *otriy,
    float *otriw,
    float *otrih) const;
  void CalcDrawnAreaAndTriangleAreaV (
    float drawable_x,
    float drawable_y,
    float drawable_w,
    float drawable_h,
    float *odrawnx,
    float *odrawny,
    float *odrawnw,
    float *odrawnh,
    float *otrix,
    float *otriy,
    float *otriw,
    float *otrih) const;
  void SaveDrawableAreaH (float x, float y, float w, float h)
  {
    m_drawable_h_x = x;
    m_drawable_h_y = y;
    m_drawable_h_w = w;
    m_drawable_h_h = h;
  }
  void SaveDrawableAreaV (float x, float y, float w, float h)
  {
    m_drawable_v_x = x;
    m_drawable_v_y = y;
    m_drawable_v_w = w;
    m_drawable_v_h = h;
  }
  void GetDrawableAreaH (float *ox, float *oy, float *ow, float *oh) const
  {
    *ox = GetDraggedX() + m_drawable_h_x;
    *oy = GetDraggedY() + m_drawable_h_y;
    *ow = m_drawable_h_w;
    *oh = m_drawable_h_h;
  }
  void GetDrawableAreaV (float *ox, float *oy, float *ow, float *oh) const
  {
    *ox = GetDraggedX() + m_drawable_v_x;
    *oy = GetDraggedY() + m_drawable_v_y;
    *ow = m_drawable_v_w;
    *oh = m_drawable_v_h;
  }
  void UpdateDrawableArea ()
  {
    if (IsHorizontal())
      UpdateDrawableAreaH();
    else
      UpdateDrawableAreaV();
  }
  void UpdateDrawableAreaH ();
  void UpdateDrawableAreaV ();
  int GetTopStringWidth () const;
  int GetTopStringHeight () const;
  int GetLeftStringWidth () const;
  int GetRightStringWidth () const;
  static int GetLeftAndRightStringsDescender();
  static int MenuItemCB (Ihandle *self);
  void MenuItem (const char *title);
  float m_drawable_h_x, m_drawable_h_y, m_drawable_h_w, m_drawable_h_h;
  float m_drawable_v_x, m_drawable_v_y, m_drawable_v_w, m_drawable_v_h;
  float m_tri_w; 
  float m_tri_h;
  float m_tri_xh, m_tri_yh; // triangle position when in horizontal mode
  float m_tri_xv, m_tri_yv; // triangle position when in vertical mode
  Ihandle *m_popupmenu;
  Ihandle *m_switch_orientation;
  lua_State *m_L;           // lua state for horizontal change cb
  int m_rightbtfunc;        // function called when right mouse button is pressed
  const char* m_top_string;
  const char* m_left_string;
  const char* m_right_string;
};

#endif
