#ifndef VGL_OBJECTPICK_H
#define VGL_OBJECTPICK_H

#include "selection.h"
#include <vgl/defines.h>
#include <vgl/hitrecord.h>
#include <vgl/canvas.h>

/**
 * Object Pick Handler
 * This handler works as an object picking handler.
 * The picking will occur in the MouseButton event, and the closest object will be passed to a callback, which must be configured.
 */
class VGL_API VglObjectPickHandler : public VglSelectionHandler
{
public:
  /**
   * Picked object callback data type.
   */
  typedef void (*PickedObjectFunction)(unsigned int id, int bt, void* data);
private:
  PickedObjectFunction m_pickedfunc;
  void* m_pickeddata;
  int m_bt;
public:
  /**
   * Returns the event handler class classname.
   */  
  static const char* CLASSNAME () { return "ObjectPickHandler"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
  /**
   * Default constructor.
   * 'surface' is the viewing surface associated with the handler.
   * 'sel_buf_size' is the size of the selection buffer used.
   * 'tolw' and 'tolh' are the picking tolerances in raster coordinates (width and height).
   */
  VglObjectPickHandler (VglViewSurface* surface, int sel_buf_size = 512, double tolw = 5.0, double tolh = 5.0);
  /**
   * Destructor.
   */
  virtual ~VglObjectPickHandler ();
  /**
   * Sets the picked object callback.
   * The callback will be called with the 'id' of the closest selection hit, the button clicked in the 'mousebutton' event and the 'data' associated with this callback.
   */
  void SetPickedObjectFunc (PickedObjectFunction f, void * data)
  {
    m_pickedfunc = f;
    m_pickeddata = data;
  }
  virtual void ProcessFunction (VglSelectionHit* hits, int n);
  virtual int MouseButton (int bt, int st, float x, float y);
};

#endif
