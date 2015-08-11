//* VglLua5Handler class
// fabraham@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Feb 2004

#ifndef VGL_LUA5_HANDLER
#define VGL_LUA5_HANDLER

#include <vgl/handler.h>

extern "C" {
#include <lua.h>
}

/**
 * This class provides a mechanism to implement an event handler in lua.
 * Methods to setup the keyboard and mouse callbacks are provided.
 * To be used with Lua 5.
 */
class VglLua5Handler : public VglHandler
{
  lua_State* m_L;
  int m_keyboard_func;
  int m_mouse_button_func;
  int m_mouse_motion_func;
  int m_mouse_entry_func;
  int m_mouse_wheel_func;
  int m_begin_func;
  int m_end_func;
  int m_postredraw_func;
  int m_afterredraw_func;
public:
  /**
   * Returns the event handler class classname.
   */
  static const char* CLASSNAME () { return "Lua5Handler"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
  /**
   * Constructs a new VglLua5Handler object.
   */
  VglLua5Handler (lua_State* L);
  /**
   * Destroys a VglLua5Handler object.
   */
  virtual ~VglLua5Handler ();
  /**
   * Sets the lua keyboard callback.
   */
  void SetKeyboardFunc (int lo);
  /**
   * Sets the lua mouse button callback.
   */
  void SetMouseButtonFunc (int lo);
  /**
   * Sets the lua mouse motion callback.
   */
  void SetMouseMotionFunc (int lo);
  /**
   * Sets the lua mouse entry callback.
   */
  void SetMouseEntryFunc (int lo);
  /**
   * Sets the lua mouse wheel callback.
   */
  void SetMouseWheelFunc (int lo);
  /**
   * Sets the lua begin callback.
   */
  void SetBeginFunc (int lo);
  /**
   * Sets the lua end callback.
   */
  void SetEndFunc (int lo);
  /**
   * Sets the lua postredraw callback.
   */
  void SetPostRedrawFunc (int lo);
  /**
   * Sets the lua afterredraw callback.
   */
  void SetAfterRedrawFunc (int lo);

  virtual void Begin ();
  virtual void End ();
  virtual int Keyboard (int k, int st, float x, float y);
  virtual int MouseButton (int bt, int st, float x, float y);
  virtual int MouseMotion (int bt, float x, float y);
  virtual int MouseEntry (bool st);
  virtual int MouseWheel (float delta, float x, float y);
  virtual int PostRedraw ();
  virtual int AfterRedraw ();
};

#endif
