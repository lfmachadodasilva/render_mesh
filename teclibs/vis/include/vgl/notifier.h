//* notifier.h
// celes@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Jan 2003

// Event handling by notifiers (and handlers):
// 1) The application may or may not call Set*Func(), on the VglViewSurface or its VglNotifier,
//    to register a user-defined handling function
// 2) The system event handler catches the event
// 3) The system event handler calls the corresponding Notify* static method
// 4) The Notify* static method calls the corresponding Handle* method on each active registered VglNotifier
// 5) Each active registered notifier, for each event:
// 5.1) Stores any relevant information derived from the event for future use
// 5.2) Calls the event Handle* method on each active registered VglHandler, in order
// 5.2.1) Stops calling handlers if any of them filters the event
// 5.3) Calls the user-defined function associated with the event, if any
//
// Idle handling by notifiers:
// A) Adding an idle function:
// A.1) The application calls AddIdle() passing the desired idle function and repeat policy level
// A.2) If the idle is already registered, decreases its repeat policy level if necessary (never increase it) and return
// A.3) Adds the idle to the idle list
// A.4) Calls IdleAddRef(), which must be implemented by the derived system-specific VglNotifier class
// A.5) The derived system-specific VglNotifier class must:
// A.5.1) Keep a counter of active idle references
// A.5.2) If the counter is incremented above zero, start the system idle event/thread
// B) Executing idle functions:
// B.1) The system idle event/thread calls the DoIdle() static method
// B.2) The DoIdle() static method calls CallIdleFuncs() on each active registered VglNotifier
// B.3) Each active registered notifier:
// B.3.1) Calls its registered idle function
// B.3.2) Updates the idle function's repeat policy level, if needed (ONE_TIME becomes NEVER)
// B.3.3) Removes from the idle list any idle functions marked with NEVER repeat policy level
// B.3.4) Calls IddleRemRef(), which must be implemented by the derived system-specific VglNotifier class
// B.3.5) The derived system-specific VglNotifier class must:
// B.3.5.1) Keep a counter of active idle references
// B.3.5.2) If the counter is decremented back to zero, stop the system idle event/thread
// C) Removing an idle function:
// C.1) The application calls RemIdle() passing the desired idle function
// C.2) The idle function's repeat policy level is set to NEVER
// C.3) The idle function will not be effectively removed until the next system idle event/thread execution (see above)
//
// PostRedraw handling by canvases (and notifiers):
// 1) The application may or may not call SetPostRedrawFunc() to set a user-defined PostRedraw function
// 2) The application calls PostRedraw() on the VglCanvas whenever desired
// 3) The default behavior is to add Redraw() as an idle function to run ONCE at the next system idle event/thread execution
// 3.1) If a user-defined PostRedraw function was registered, it is called instead, and no idle function is added
//
// Redraw handling by canvases (and notifiers and handlers):
// 1) The application calls SetRedrawFunc(), and optionally also SetBeginRedrawFunc() and SetEndRedrawFunc()
//    on the VglCanvas, in order to register user-defined event handling functions
// 2) The system redraw event calls a method on a derived system-specific VglCanvas class
// 3) The method sets the m_nativeredraw flag and calls Redraw() on VglCanvas
// 4) The Redraw() method calls:
// 4.1) Activate()
// 4.2) CallHandlersPreRedraw()
// 4.2.1) Translated to VglNotifier::HandlePreRedraw()
// 4.2.2) The notifier calls VglHandler::PreRedraw() on each active handler
// 4.3) DrawEye() for each required eye (more than one if in stereo mode), which in turn calls:
// 4.3.1) The user-defined BeginRedraw function
// 4.3.2) The user-defined Redraw function
// 4.3.3) CallHandlersEndRedraw()
// 4.3.3.1) Translated to VglNotifier::HandleEndRedraw()
// 4.3.3.2) The notifier calls VglHandler::PostRedraw() on each active handler
// 4.3.4) Redraw() for each subcanvas
// 4.3.5) The user-defined EndRedraw function
// 4.4) CallHandlersAfterRedraw()
// 4.4.1) Translated to VglNotifier::HandleAfterRedraw()
// 4.4.2) The notifier calls VglHandler::AfterRedraw() on each active handler
// 4.5) SwapBuffers()

#ifndef VGL_NOTIFIER_H
#define VGL_NOTIFIER_H

#include "defines.h"
#include <ds/array.h>
#include <ds/list.h>

class VglCanvas;
class VglHandler;
class VglManipViewSurface;

class VGL_API VglNotifier
{
public:
  typedef DsPList<VglNotifier> NotifierList;
  typedef DsPList<VglHandler> HandlerList;
public:
  /**
   * Constructs a new event notifier.
   * \param source Notifier event source (such as a window handle).
   */
  VglNotifier (void *source);
  /**
   * Destroys a VglNotifier object.
   */
  virtual ~VglNotifier ();
  /**
   * Specifies the notifier event source (such as a window handle).
   * Must be called right after instantiation.
   */
  void SetSource (void* source)
  {
    m_source = source;
  }
  /**
   * Specifies the notifier view surface
   * Must be called right after instantiation.
   */
  void SetViewSurface (VglManipViewSurface* surface)
  {
    m_surface = surface;
  }
  /**
   * Activates the event notifier.
   */
  void Activate ();
  /**
   * Deactivates the event notifier.
   */
  void Deactivate ();
  /**
   * Is the notifier active?
   * \return Notifier active = true, false otherwise.
   */
  bool IsActive ();
  /**
   * Registers a new event handler, inserting at the end of the handler list.
   * Returns the success in registration (duplication is not allowed).
   */
  bool AddHandler (VglHandler* handler)
  {
    return AddHandlerPrivate(handler, false);
  }
  /**
   * Removes an event handler.
   * \param handler Event handler.
   * \return Success in removal.
   */
  bool RemHandler (VglHandler* handler);
  /**
   * Gets the notifier's event handlers.
   * \return An iterator to the event handler list.
   */
  HandlerList::Iterator GetHandlers ()
  {
    return GetUserHandlers();
  }
  /**
   * Removes all handlers.
   */
  void ClearHandlers ();
  /**
   * Inserts a new idle function.
   * \param func Idle function.
   * \param data Parameter to be passed to this idle function.
   * \param repeat Repeat policy. (VGL_ONE_TIME / VGL_UNTIL_EVENT / VGL_FOREVER)
   * \return Success in the insertion.
   */
  virtual bool AddIdle (VglFunction func, void* data, int repeat);
  /**
   * Removes an idle function.
   * \param func Idle function.
   * \param data Parameter to the idle function. Must be the same as in the insertion.
   * \return Success in the removal.
   */
  virtual bool RemIdle (VglFunction func, void* data);
  /**
   * Calls the idle functions.
   */
  void CallIdleFuncs ();
  /**
   * Cleans the idle function list by removing any idles set to "VGL_UNTIL_EVENT"
   */
  void CleanIdleList ();
  /**
   * Resets the idle function list by removing all idles.
   */
  void ResetIdleList ();
  /**
   * Sets all keyboard keys as unpressed.
   */
  void ResetKeys ();
  /**
   * Handles a keyboard event. Will call all event handlers and the keyboard callback.
   * \param k   Key code.
   * \param st  Key state (VGL_PRESS / VGL_RELEASE).
   * \param x   Normalized x coordinate of the mouse (-1=unknown).
   * \param y   Normalized y coordinate of the mouse (-1=unknown).
   * \param ctl Control key state (-1=unknown, 0=unpressed, 1=pressed).
   * \param sft Shift key state (-1=unknown, 0=unpressed, 1=pressed).
   */
  void HandleKeyboard (int k, int st, float x, float y, int ctl, int sft);
  /**
   * Handles a mouse click event. Will call all event handlers and the mouse click callback.
   * \param bt  Button (VGL_BUTTON_LEFT / VGL_BUTTON_MIDDLE / VGL_BUTTON_RIGHT).
   * \param st  Button state (VGL_PRESS / VGL_RELEASE).
   * \param x   Normalized x coordinate of the mouse (-1=unknown).
   * \param y   Normalized y coordinate of the mouse (-1=unknown).
   * \param ctl Control key state (-1=unknown, 0=unpressed, 1=pressed).
   * \param sft Shift key state (-1=unknown, 0=unpressed, 1=pressed).
   * \param dbl Double-click flag (-1=unknown, 0=single, 1=double).
   */
  void HandleMouseButton (int bt, int st, float x, float y, int ctl, int sft, int dbl);
  /**
   * Handles a mouse motion event. Will call all event handlers and the mouse motion callback.
   * \param x   Normalized x coordinate of the mouse (must be known).
   * \param y   Normalized y coordinate of the mouse (must be known).
   * \param ctl Control key state (-1=unknown, 0=unpressed, 1=pressed).
   * \param sft Shift key state (-1=unknown, 0=unpressed, 1=pressed).
   */
  void HandleMouseMotion (float x, float y, int ctl, int sft); 
  /**
   * Handles a mouse entry event. Will call all event handlers and the mouse entry callback.
   * \param st true if mouse entered, false if mouse left.
   */
  void HandleMouseEntry (bool st); 
  /**
   * Handles a mouse wheel event. Will call all event handlers and the mouse wheel callback.
   * \param delta Amount the wheel rotated in notches.
   * \param x     Normalized x coordinate of the mouse (-1=unknown).
   * \param y     Normalized y coordinate of the mouse (-1=unknown).
   * \param ctl   Control key state (-1=unknown, 0=unpressed, 1=pressed).
   * \param sft   Shift key state (-1=unknown, 0=unpressed, 1=pressed).
   */
  void HandleMouseWheel (float delta, float x, float y, int ctl, int sft);
  /**
   * Called before the redraw callback of the canvas.
   * Will call PreRedraw() for all event handlers.
   */
  void HandlePreRedraw (); 
  /**
   * Called after the redraw callback of the canvas.
   * Will call PostRedraw() for all event handlers.
   */
  void HandleEndRedraw (); 
  /**
   * Called after the end redraw callback of the canvas.
   * Will call AfterRedraw() for all event handlers.
   */
  void HandleAfterRedraw ();
  /**
   * Is key with code 'k' pressed?
   */
  bool GetKey (int k) const
  {
    return m_key[k];
  }
  /**
   * Is control key pressed?
   * \return true if pressed, false otherwise.
   */
  bool GetCtrl () const
  {
    return m_ctrl;
  }
  /**
   * Is shift key pressed?
   * \return true if pressed, false otherwise.
   */
  bool GetShift () const
  {
     return m_shft;
  }
  /**
   * Indicates if the current mouse button event is a double click.
   * Must only be called inside a MouseButton event.
   * Result can only be 'true' when called with state VGL_PRESS.
   */
  bool GetDoubleClick () const
  {
    return m_doubleclick;
  }
  /**
   * Indicates if the mouse cursor is over the view surface associated with
   * this notifier. Useful for derived notifiers that wish to implement a
   * specific behavior when the mouse cursor is outside their view surface.
   */
  bool GetMouseOver () const
  {
    return m_mouseover;
  }
  /**
   * Returns the x coordinate where the button was pressed.
   * \return Normalized x coordinate.
   */
  float GetX0 () const
  {
    return m_x0;
  }
  /**
   * Returns the y coordinate where the button was pressed.
   * \return Normalized y coordinate.
   */
  float GetY0 () const
  {
    return m_y0;
  }
  /**
   * Returns the last x coordinate the mouse visited.
   * \return Normalized x coordinate.
   */
  float GetLastX () const
  {
    return m_lastx;
  }
  /**
   * Returns the last y coordinate the mouse visited.
   * \return Normalized y coordinate.
   */
  float GetLastY () const
  {
    return m_lasty;
  }
  /**
   * Returns the last pressed button that remains pressed.
   * \return One of the following values:
   * VGL_NONE, VGL_BUTTON_LEFT, VGL_BUTTON_MIDDLE, VGL_BUTTON_RIGHT.
   */
  int GetButton () const
  {
    return m_button;
  }
  /**
   * Is mouse button 'bt' pressed?
   * \param bt Button (VGL_BUTTON_LEFT / VGL_BUTTON_MIDDLE / VGL_BUTTON_RIGHT).
   * \return   Whether the queried button is currently pressed or not.
   */
  bool GetButton (int bt) const
  {
    return ((m_buttons & bt) != 0);
  }
  /**
   * Sets the keyboard callback.
   * \param func Keyboard callback.
   * \param data Data that will be passed to this callback.
   */
  void SetKeyboardFunc (VglKeyboardFunction func, void* data);
  /**
   * Sets the mouse button callback.
   * \param func Mouse button callback.
   * \param data Data that will be passed to this callback.
   */
  void SetMouseButtonFunc (VglMouseButtonFunction func, void* data);
  /**
   * Sets the mouse motion callback.
   * \param func Mouse motion callback.
   * \param data Data that will be passed to this callback.
   */
  void SetMouseMotionFunc (VglMouseMotionFunction func, void* data);
  /**
   * Sets the mouse entry callback.
   * \param func Mouse entry callback.
   * \param data Data that will be passed to this callback.
   */
  void SetMouseEntryFunc (VglMouseEntryFunction func, void* data);
  /**
   * Sets the mouse wheel callback.
   * 'func' is the mouse wheel callback.
   * 'data' is the data that will be passed to this callback.
   */
  void SetMouseWheelFunc (VglMouseWheelFunction func, void* data);
  VglKeyboardFunction GetKeyboardFunc () const
  {
    return m_keyboardfunc;
  }
  VglMouseButtonFunction GetMouseButtonFunc () const
  {
    return m_buttonfunc;
  }
  VglMouseMotionFunction GetMouseMotionFunc () const
  {
    return m_motionfunc;
  }
  VglMouseEntryFunction GetMouseEntryFunc () const
  {
    return m_entryfunc;
  }
  VglMouseWheelFunction GetMouseWheelFunc () const
  {
    return m_wheelfunc;
  }
  /**
   * Sets the doubleclick maximum time in seconds
   */
  static void SetDoubleClickTime (float seconds);
  /**
   * Sets the doubleclick maximum distance in pixels
   */
  static void SetDoubleClickDist (int pixels);
  /**
   * Returns the doubleclick maximum time in seconds
   */
  static float GetDoubleClickTime ();
  /**
   * Returns the doubleclick maximum distance in pixels (default = 2 pixels)
   */
  static int GetDoubleClickDist ();
  /**
   * Notify a new keyboard event.
   * \param source Event source (to identify which notifier must be used).
   * \param k      Key code.
   * \param st     Key state (VGL_PRESS / VGL_RELEASE).
   * \param x      Normalized x coordinate of the mouse (-1=unknown).
   * \param y      Normalized y coordinate of the mouse (-1=unknown).
   * \param ctl    Control key state (-1=unknown, 0=unpressed, 1=pressed).
   * \param sft    Shift key state (-1=unknown, 0=unpressed, 1=pressed).
   */
  static void NotifyKeyboard 
    (void *source, int k, int st, float x, float y, int ctl, int sft);
  /**
   * Notifies a new mouse click event.
   * \param source Event source (to identify which notifier must be used).
   * \param bt     Button (VGL_BUTTON_LEFT / VGL_BUTTON_MIDDLE / VGL_BUTTON_RIGHT).
   * \param st     Button state (VGL_PRESS / VGL_RELEASE).
   * \param x      Normalized x coordinate of the mouse (-1=unknown).
   * \param y      Normalized y coordinate of the mouse (-1=unknown).
   * \param ctl    Control key state (-1=unknown, 0=unpressed, 1=pressed).
   * \param sft    Shift key state (-1=unknown, 0=unpressed, 1=pressed).
   * \param dbl    Double-click flag (-1=unknown, 0=single, 1=double).
   */
  static void NotifyMouseButton 
    (void *source, int bt, int st, float x, float y, int ctl, int sft, int dbl);
  /**
   * Notifies a new mouse motion event.
   * \param source Event source (to identify which notifier must be used).
   * \param x      Normalized x coordinate of the mouse (must be known).
   * \param y      Normalized y coordinate of the mouse (must be known).
   * \param ctl    Control key state (-1=unknown, 0=unpressed, 1=pressed).
   * \param sft    Shift key state (-1=unknown, 0=unpressed, 1=pressed).
   */
  static void NotifyMouseMotion (void *source, float x, float y, int ctl, int sft);
  /**
   * Notifies a new mouse entry event.
   * \param source Event source.
   * \param st     true if mouse entered, false if mouse left.
   */
  static void NotifyMouseEntry (void *source, bool st); 
  /**
   * Notifies a new mouse wheel event.
   * \param source Event source (to identify which notifier must be used).
   * \param delta  Amount the wheel rotated in notches.
   * \param x      Normalized x coordinate of the mouse (-1=unknown).
   * \param y      Normalized y coordinate of the mouse (-1=unknown).
   * \param ctl    Control key state (-1=unknown, 0=unpressed, 1=pressed).
   * \param sft    Shift key state (-1=unknown, 0=unpressed, 1=pressed).
   */
  static void NotifyMouseWheel
    (void *source, float delta, float x, float y, int ctl, int sft);
  /**
   * Calls all notifiers idle functions.
   */
  static void DoIdle ();
protected:
  /**
   * Function that will be called whenever an idle function is added.
   * Useful to setup an idle function only when needed (when there is
   * at least 1 idle function)
   */
  virtual void IdleAddRef () = 0;
  /**
   * Function that will be called whenever an idle function is removed.
   * Useful to unset an idle function if there is no idle function left.
   */
  virtual void IdleRemRef () = 0;
  /**
   * Function that will be called inside the HandleMouseButton() function.
   * /return One of the following values:
   *   - When a "mouse button released" event is received, consider that:
   *     0 = only the callback button was released
   *     1 = all buttons were released
   *     2 = mode 0 inside canvas, mode 1 outside
   */
  virtual int GetMouseButtonMode () = 0;
  /**
   * Returns the notifier's event source (such as a window handle).
   */
  void* GetSource () const
  {
    return m_source;
  }
  virtual bool IsSource (void* source)
  {
    return source == GetSource();
  }
  /**
   * Returns the notifier's view surface.
   */
  VglManipViewSurface* GetViewSurface () const
  {
    return m_surface;
  }
private:
  struct VGL_API Idle
  {
    VglFunction func;
    void* data;
    int   repeat;
    Idle () : func(0), data(0), repeat(0) { }
    Idle (VglFunction f, void* d, int r) : func(f), data(d), repeat(r) { }
    bool operator== (const Idle& oth) 
    { 
      return func==oth.func && 
        data==oth.data && 
        repeat==oth.repeat; 
    }
  };
  typedef DsList<Idle> IdleList;
private:
  void SetLastXY (float x, float y);
  bool AddHandlerPrivate (VglHandler* handler, bool is_internal);
  HandlerList::Iterator GetUserHandlers ()
  {
    return m_user_handlers.Begin();
  }
  HandlerList::Iterator GetInternalHandlers ()
  {
    return m_int_handlers.Begin();
  }
  void BuildHandlerArray (DsArray<VglHandler*>& handlers);
  void BuildIdleArray (DsArray<Idle*>& idles);
private:
  static NotifierList s_notifiers;
  void *m_source;                 // Event source (such as a canvas handle)
  VglManipViewSurface* m_surface; // View surface associated to this notifier
  bool m_ctrl;                    // Current state of control key
  bool m_shft;                    // Current state of shift key
  bool m_key[VGL_MAX_KEY];        // Currently pressed keys
  bool m_allowdouble;             // Can the next buttondown be a doubleclick?
  bool m_doubleclick;             // Is the current button event a doubleclick?
  bool m_mouseover;               // Is the mouse over the view surface?
  int m_button;                   // Last pressed button that remains pressed
  int m_buttons;                  // Currently pressed buttons
  float m_x0, m_y0;               // Last buttondown event (x,y) coordinates
  double m_t0;                    // Last buttondown event time
  int m_b0;                       // Last buttondown event button
  float m_lastx, m_lasty;         // Last visited (x,y) coordinates
  float m_setlastx, m_setlasty;
  bool m_setlastxy;
  HandlerList m_int_handlers;  // internal handlers are called before user handlers
  HandlerList m_user_handlers;
  IdleList m_idlelist;
  bool m_calling_idles;

  void (*m_keyboardfunc)(int k, int st, float x, float y, void* data);
  void (*m_buttonfunc) (int bt, int st, float x, float y, void* data);
  void (*m_motionfunc) (int bt, float x, float y, void* data);
  void (*m_entryfunc) (int st, void* data);
  void (*m_wheelfunc) (float delta, float x, float y, void* data);
  void* m_keyboardfuncdata;
  void* m_buttonfuncdata;
  void* m_motionfuncdata;
  void* m_entryfuncdata;
  void* m_wheelfuncdata;
private:
  friend class VglCanvas;
  friend class VglSubCanvas;
  friend class VglManipViewSurface;
};

#endif
