//* colorscale.h
// An active color scale (with functions to save/read from Lua).
// Tecgraf/PUC-Rio
// Mar 2004

#ifndef SCI_ACOLORSCALE_LUA_H
#define SCI_ACOLORSCALE_LUA_H

#include "acolorscale.h"
#include <sciutils/defines.h>
#include <sciutils/lua/sciutilslua.h>

class SCIUTILSLUAAPI SciActiveElementColorScaleLua : public SciActiveElementColorScale
{
public:
  SciActiveElementColorScaleLua(const char *name);
  virtual ~SciActiveElementColorScaleLua();
  void SetRequestRedrawFunc (lua_State *L, int lo);
  /**
  * Function called when the user presses the right mouse button.
  * If no function is set, the default menu is shown.
  */
  void SetRightButtonFunc (lua_State *L, int lo);
  virtual void WriteToTable(lua_State *L, int t);
  virtual void ReadFromTable(lua_State *L, int t);
protected:
  virtual void cbButton(float x, float y, int mbt, int mst, VglNotifier *ntf);
  bool HasRightButtonFunc () const
  {
    return m_L != NULL && m_rightbtfunc != 0;
  }
private:
  void RequestRedraw ();
protected:
  lua_State *m_L;          // lua state for horizontal change cb
private:
  int m_rightbtfunc;       // function called when right mouse button is pressed
  int m_requestredrawfunc; // request redraw cb ref
};

#endif

