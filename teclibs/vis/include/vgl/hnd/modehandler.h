//* modehandler.h
// fabraham@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Mar 2003

#ifndef VGL_MODE_HANDLER_H
#define VGL_MODE_HANDLER_H

#include <vgl/handler.h>
#include <vgl/defines.h>

class VglManipViewSurface;
struct Hnd_key;

/**
 * This class provides a mechanism to associate various event handlers to keys
 * and use these keys to switch between them.\n
 * This is done using the method AddHandler(handler,keycode).\n
 */
class VGL_API VglModeHandler : public VglHandler
{
  typedef DsPList<Hnd_key> HandlerList;
  VglManipViewSurface *m_manipviewsurface;
  VglHandler* m_curr;
  HandlerList m_hnd_list;
public:
  /**
   * Returns the event handler class classname.
   * \return Event handler class classname.
   */
  static const char* CLASSNAME () { return "ModeHandler"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
  /**
   * Constructs a new VglModeHandler object,
   * which will be associated with manip view surface 'manipviewsurface'.
   */
  VglModeHandler (VglManipViewSurface *manipviewsurface);
  /**
   * Destroys a VglModeHandler object.
   */
  virtual ~VglModeHandler ();
  /**
   * Activates all handlers.
   */
  virtual void Begin ();
  /**
   * Deactivates all handlers.
   */
  virtual void End ();
  /**
   * Adds a new event handler to this switch.
   * \param hnd The new event handler.
   * \param switch_key Key that will switch to this event handler.
   * \return Success in the insertion.
   */
  bool AddHandler(VglHandler* hnd, int switch_key);
  /**
   * Removes an event handler to this switch.
   * Returns the success on the removal.
   */
  bool RemHandler(VglHandler* hnd);
  /**
   * Is current handler?
   */
  bool IsCurrentHandler (VglHandler* hnd) const
  {
    return m_curr == hnd;
  }
  /**
   * Changes the current handler to the one associated with key 'k'.
   * Returns the success in changing the handler.
   */
  bool ChangeHandler(int k);
  VglHandler *GetHandler(int k) const;
  virtual int Keyboard (int k, int st, float x, float y);
};

#endif
