//* handler.h
// celes@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Jan 2003

#ifndef VGL_HANDLER_H
#define VGL_HANDLER_H

#include "notifier.h"
#include <string.h>

class VglCanvas;

/**
 * This class represents an abstract event handler.
 * An event handler can define methods to handle:
 * - keyboard events
 * - mouse click events.
 * - mouse motion events.
 * - mouse entry events.
 *
 * An empty method for each kind event is provided.
 * Utility functions like query of key state, shift and control key state and
 * mouse click information are provided.
 * All event handlers must define a method to identify its classname.
 */
class VGL_API VglHandler
{
  VglNotifier* m_notifier;
  bool m_active;
  bool m_modal;
protected:
  /**
   * Constructs a new VglHandler object.
   * 'modal' indicates if the handler is modal.
   * When a modal handler is active, no idle functions are called.
   */
  VglHandler (bool modal=false);
public:
  /**
   * Returns the event handler classname.
   */
  virtual const char* ClassName () const = 0;
  /**
   * Returns true if the handler's class is named 't'.
   */
  bool IsOfType (const char *t) const
  {
    const char *it = ClassName();
    return it == t || strcmp(it,t)==0;
  }
  /**
   * Destroys a VglHandler object.
   */
  virtual ~VglHandler ();
  /**
   * Activates the event handler, making it respond to events.
   */
  void Activate ();
  /**
   * Deactivates the event handler, making it ignore new events.
   */
  void Deactivate ();
  /**
   * Returns if event handler is active or not.
   * \return true if active, false otherwise.
   */
  bool IsActive ();
  /**
   * Is the event handler modal?
   * When a modal handler is active, no idle functions are called.
   */
  bool IsModal();
  /**
   * Method called whenever the handler is activated/inserted into a notifier.
   */
  virtual void Begin ();
  /**
   * Method called whenever the handler is deactivated/removed from a notifier.
   */
  virtual void End ();
  /**
   * Handles a keyboard event.
   * \param k  Key code.
   * \param st Key state (VGL_PRESS / VGL_RELEASE)
   * \param x  Normalized x coordinate.
   * \param y  Normalized y coordinate.
   * If the function returns nonzero, the event is passed on to the next handler in the canvas list.
   * Otherwise, the event is filtered by this handler.
   */
  virtual int Keyboard (int k, int st, float x, float y);
  /**
   * Handles a mouse click event.
   * \param bt Button (VGL_BUTTON_LEFT / VGL_BUTTON_MIDDLE / VGL_BUTTON_RIGHT)
   * \param st Button state (VGL_PRESS / VGL_RELEASE)
   * \param x  Normalized x coordinate.
   * \param y  Normalized y coordinate.
   * If the function returns nonzero, the event is passed on to the next handler in the canvas list.
   * Otherwise, the event is filtered by this handler.
   */
  virtual int MouseButton (int bt, int st, float x, float y);
  /**
   * Handles a mouse motion event.
   * \param x  New normalized x coordinate.
   * \param y  New normalized y coordinate.
   * If the function returns nonzero, the event is passed on to the next handler in the canvas list.
   * Otherwise, the event is filtered by this handler.
   */
  virtual int MouseMotion (int bt, float x, float y);
  /**
   * Handles a mouse entry event.
   * \param st true if mouse entered, false if mouse left.
   * If the function returns nonzero, the event is passed on to the next handler in the canvas list.
   * Otherwise, the event is filtered by this handler.
   */
  virtual int MouseEntry (bool st);
  /**
   * Handles a mouse wheel event.
   * 'delta' is the ammount the wheel rotated in notches.
   * 'x' is the current normalized x coordinate of the mouse.
   * 'y' is the current normalized y coordinate of the mouse.
   * If the function returns nonzero, the event is passed on to the next handler in the canvas list.
   * Otherwise, the event is filtered by this handler.
   */
  virtual int MouseWheel (float delta, float x, float y);
  /**
   * Called before the canvas redraw callback
   * If the function returns nonzero, the event is passed on to the next handler in the canvas list.
   * Otherwise, the event is filtered by this handler.
   */
  virtual int PreRedraw (void);
  /**
   * Called after the canvas redraw callback
   * If the function returns nonzero, the event is passed on to the next handler in the canvas list.
   * Otherwise, the event is filtered by this handler.
   */
  virtual int PostRedraw (void);
  /**
   * Called after the canvas end redraw callback.
   * No handlers should draw anything on this callback.
   * If the function returns nonzero, the event is passed on to the next handler in the canvas list.
   * Otherwise, the event is filtered by this handler.
   */
  virtual int AfterRedraw (void);
  /**
   * Is key pressed?
   * \param k Key code.
   * \return true if pressed, false otherwise.
   */
  bool GetKey (int k) const
  {
    return m_notifier ? m_notifier->GetKey(k) : false;
  }
  /**
   * Is control key pressed?
   * \return true if pressed, false otherwise.
   */
  bool GetCtrl () const
  {
    return m_notifier ? m_notifier->GetCtrl() : false;
  }
  /**
   * Is shift key pressed?
   * \return true if pressed, false otherwise.
   */
  bool GetShift () const
  {
    return m_notifier ? m_notifier->GetShift() : false;
  }
  /**
   * Indicates if the last mouse button event was a double click.
   * Must only be called inside a MouseButton event.
   */
  bool GetDoubleClick () const
  {
    return m_notifier ? m_notifier->GetDoubleClick() : false;
  }
  /**
   * Returns the x coordinate where the button was pressed.
   * \return Normalized x coordinate.
   */
  float GetX0 () const
  {
    return m_notifier ? m_notifier->GetX0() : 0.0f;
  }
  /**
   * Returns the y coordinate where the button was pressed.
   * \return Normalized y coordinate.
   */
  float GetY0 () const
  {
    return m_notifier ? m_notifier->GetY0() : 0.0f;
  }
  /**
   * Returns the last x coordinate the mouse visited.
   * \return Normalized x coordinate.
   */
  float GetLastX () const
  {
    return m_notifier ? m_notifier->GetLastX() : 0.0f;
  }
  /**
   * Returns the last y coordinate the mouse visited.
   * \return Normalized y coordinate.
   */
  float GetLastY () const
  {
    return m_notifier ? m_notifier->GetLastY() : 0.0f;
  }
  /**
   * Returns the last pressed button that remains pressed.
   * \return One of the following values:
   * VGL_NONE, VGL_BUTTON_LEFT, VGL_BUTTON_MIDDLE, VGL_BUTTON_RIGHT.
   */
  int GetButton () const
  {
    return m_notifier ? m_notifier->GetButton() : VGL_NONE;
  }
  /**
   * Is mouse button 'bt' pressed?
   * \param bt Button (VGL_BUTTON_LEFT / VGL_BUTTON_MIDDLE / VGL_BUTTON_RIGHT).
   * \return   Whether the queried button is currently pressed or not.
   */
  bool GetButton (int bt) const
  {
    return m_notifier ? m_notifier->GetButton(bt) : false;
  }
  /**
   * Sets the event notifier that will pass events to this handler.
   * \param notifier Event notifier.
   */
  void SetNotifier (VglNotifier* notifier)
  {
    m_notifier = notifier;
  }
  /**
   * Gets the event notifier associated with this handler.
   */
  VglNotifier* GetNotifier ()
  {
    return m_notifier;
  }
};

#endif
