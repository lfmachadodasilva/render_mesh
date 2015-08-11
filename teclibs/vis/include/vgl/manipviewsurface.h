//* manipviewsurface.h
// fabraham@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Aug 2006

#ifndef VGL_MANIPVIEWSURFACE_H
#define VGL_MANIPVIEWSURFACE_H

#include "viewsurface.h"
#include "notifier.h"
#include "handler.h"

/**
 * A visualization surface with interaction support.
 *
 * Methods are provided to add/remove/clear handlers and idle functions.
 */
class VGL_API VglManipViewSurface : public VglViewSurface
{
public:
  /**
   * Handlers list type.
   */
  typedef DsPList<VglHandler> HandlerList;
  /**
   * Handlers list iterator type.
   */
  typedef HandlerList::Iterator HandlerListIterator;
  /**
   * Destructor.
   */
  virtual ~VglManipViewSurface ()
  {
  }
  /**
   * Sets the event notifier for this surface.
   */
  virtual void SetNotifier (VglNotifier* notifier)
  {
    m_notifier = notifier;
    if (notifier != NULL)
      notifier->SetViewSurface(this);
  }
  /**
   * Obtains the event notifier for this surface.
   */
  virtual VglNotifier* GetNotifier ()
  {
    return m_notifier;
  }
  /**
   * Adds a new event handler to the surface.
   * If 'at' is specified, inserts at that position in the list.
   * Else inserts at the end of the list.
   * Returns the success in registration (duplication is not allowed).
   */
  virtual bool AddHandler (VglHandler* handler);
  /**
   * Adds a new event handler to the surface.
   * This handler, along with other internal handlers, is called before
   * the handlers added via AddHandler (called user handlers).
   * Should be used with care.
   *
   * Returns the success in registration (duplication is not allowed).
   */
  virtual bool AddInternalHandler (VglHandler* handler)
  {
    if (GetNotifier())
      return GetNotifier()->AddHandlerPrivate(handler, true);
    else
      return false;
  }
  /**
   * Removes the handler from the surface.
   * Returns success in the removal.
   */
  virtual bool RemHandler (VglHandler* handler);
  /**
   * Obtains an iterator to the surface handler list.
   */
  virtual HandlerListIterator GetHandlers ()
  {
    return GetNotifier()->GetHandlers();
  }
  /**
   * Removes all handlers.
   */
  virtual void ClearHandlers ();
  /**
   * Adds a new idle function to the surface.
   * 'data' will be passed to the callback.
   * 'repeat' is the repeat policy (VGL_ONE_TIME or VGL_UNTIL_EVENT or VGL_FOREVER)
   * Returns success in the insertion.
   */
  virtual bool AddIdle (VglFunction func, void* data, int repeat);
  /**
   * Removes an idle function from the surface.
   * 'data' will be passed to the callback.
   */
  virtual bool RemIdle (VglFunction func, void* data);
  /**
   * Gets the reference to the handler given its name.
   */
  VglHandler * GetHandlerByType (const char* handlerName);
protected:
  /**
   * Constructor.
   * 'camera' is the camera associated with this view surface.
   * 'notifier' is the event notifier for this surface.
   */
  VglManipViewSurface (VglCamera* camera, VglNotifier* notifier);
  /**
   * Calls the handlers' preredraw method.
   */
  void CallHandlersPreRedraw ()
  {
    if (GetNotifier())
      GetNotifier()->HandlePreRedraw();
  }
  /**
   * Calls the handlers' endredraw method.
   */
  void CallHandlersEndRedraw ()
  {
    if (GetNotifier())
      GetNotifier()->HandleEndRedraw();
  }
  /**
   * Calls the handlers' afterredraw method.
   */
  void CallHandlersAfterRedraw ()
  {
    if (GetNotifier())
      GetNotifier()->HandleAfterRedraw();
  }
private:
  VglNotifier* m_notifier;
};

#endif
