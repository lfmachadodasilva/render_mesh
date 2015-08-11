//* transition.h
// celes@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Jan 2003

#ifndef VGL_TRANSITION_H
#define VGL_TRANSITION_H

#include <vgl/handler.h>

/**
 * This class provides a simple mechanism to change from one handler to another
 * when a mouse button is released.\n
 */
class VGL_API VglTransitionHandler : public VglHandler
{
  VglHandler* m_from;
  VglHandler* m_to;
public:
  /**
   * Returns the event handler class classname.
   * \return Event handler class classname.
   */
  static const char* CLASSNAME () { return "TransitionHandler"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
  /**
   * Constructs a new VglTransitionHandler object.
   */
  VglTransitionHandler ();
  /**
   * Destroys a VglTransitionHandler object.
   */
  virtual ~VglTransitionHandler ();
  /**
   * Sets the transition that will happen when a mouse button is released.
   * \param from If not NULL, event handler that will be deactivated when this occurs.
   * \param to   If not NULL, event handler that will be activated when this occurs.
   */
  void SetTransition (VglHandler* from, VglHandler* to);
  /**
   * Specifies a function that will be called when the transition takes place.
   */
  void SetTransitionFunc (VglFunction func, void *data=NULL)
  {
    m_transfunc = func;
    m_transdata = data;
  }
  virtual int MouseButton (int bt, int st, float x, float y);
private:
  VglFunction m_transfunc;
  void *m_transdata;
};

#endif
