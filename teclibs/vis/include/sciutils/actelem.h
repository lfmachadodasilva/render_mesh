// Active elements on a VGL Canvas. 
// calomeni@tecgraf.puc-rio.br
// fabraham@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Mar 2004

#ifndef vis_actelem_h
#define vis_actelem_h

#include <vgl/vgl.h>
#include <vgl/handler.h>
#include <ds/array.h>
#include <sciutils/defines.h>
#include <alg/glstack.h>
#include "colorscale.h"

#define SCI_FLOOR_NORM_COORD(v,vpv) (float(floor((v)*(vpv)))/(vpv))
#define SCI_CEIL_NORM_COORD(v,vpv)  (float(ceil ((v)*(vpv)))/(vpv))

struct lua_State;

//* *SciActiveElement* Class
// Represents an active element on a VGL canvas
class SCI_API SciActiveElement
{
public:
  virtual ~SciActiveElement()
  {
    free(m_name);
  }
  /**
   * Renders the element, if it is visible.
   */
  virtual void Render()
  {
    if (GetVisible())
      doRender();
  }

  const char * GetName()
  {
    return m_name;
  }

  virtual void SetVisible(bool vis)
  {
    m_visible = vis;
  }

  bool GetVisible()
  {
    return m_visible;
  }

  virtual void SetCanvas(VglCanvas *cnv)
  {
    m_canvas = cnv;
  }

  VglCanvas * GetCanvas() const
  {
    return m_canvas;
  }

  virtual void SetSubCanvas(VglSubCanvas *cnv)
  {
    m_subcanvas = cnv;
  }

  VglSubCanvas * GetSubCanvas() const
  {
    return m_subcanvas;
  }
  /**
   * Specifies the background color for the element.
   * 'r', 'g' and 'b' are specified between 0 and 1.
   */
  virtual void SetBackground(float r, float g, float b, float a = 1.0f)
  {
    m_br = r; m_bg = g; m_bb = b; m_ba = a;
  }
  void GetBackground(float *r, float *g, float *b, float *a) const
  {
    *r = m_br; *g = m_bg; *b = m_bb; *a = m_ba;
  }
  bool IsBackground (float r, float g, float b, float a) const
  {
    return r == m_br && g == m_bg && b == m_bb && a == m_ba;
  }
  /**
   * Saves current settings to a Lua table.
   */
  virtual void WriteToTable(lua_State *L, int t) {}
  /**
   * Reads settings from a Lua table.
   */
  virtual void ReadFromTable(lua_State *L, int t) {}
  /**
   * Specifies if the element can be dragged with the middle mouse button.
   */
  virtual void SetDragEnabled (bool f)
  {
    m_drag_enabled = f;
  }
  /**
   * Is the element draggable with the middle mouse button?
   */
  bool IsDragEnabled () const
  {
    return m_drag_enabled;
  }
  /**
   * Informs if the next render is going to be a native redraw.
   * Not necessary if the element has an associated VglCanvas or VglSubCanvas.
   */
  void SetNativeRedraw (bool f)
  {
    m_is_native_redraw = f;
  }
  /**
   * Obtains the element's drawn area in normalized coordinates (0<->1).
   * 'ox', 'oy', 'ow' and 'oh' can be NULL (not going to be assigned to)
   */
  virtual void GetDrawnArea (float *ox, float *oy, float *ow, float *oh) const
  {
    if (ox)
      *ox = GetDrawnX();
    if (oy)
      *oy = GetDrawnY();
    if (ow)
      *ow = GetDrawnWidth();
    if (oh)
      *oh = GetDrawnHeight();
  }
  void SetProjectionStack (AlgGLStack* pstack)
  {
    m_pstack = pstack;
  }
protected:
  /**
   * Constructor. 'name' names the element.
   */
  SciActiveElement(const char *name) :
    m_canvas(NULL),
    m_subcanvas(NULL),
    m_br(0.0f),
    m_bg(0.0f),
    m_bb(0.0f),
    m_ba(1.0f),
    m_dragged_x(0.0f),
    m_dragged_y(0.0f),
    m_visible(true),
    m_drag_enabled(true),
    m_is_native_redraw(true),
    m_pstack(NULL)
  {
    m_name = name ? strdup(name) : NULL;
  }
  /**
   * Stores the element's drawn area in normalized coordinates (0<->1).
   */
  virtual void SetDrawnArea (float x, float y, float w, float h)
  {
    m_drawn_x = x;
    m_drawn_y = y;
    m_drawn_w = w;
    m_drawn_h = h;
  }
  /**
   * Obtains the elements's drawn area's initial x coordinate (normalized
   * window coordinates) (0<->1).
   */
  virtual float GetDrawnX () const
  {
    return m_drawn_x;
  }
  /**
   * Obtains the elements's drawn area's initial y coordinate (normalized
   * window coordinates) (0<->1).
   */
  virtual float GetDrawnY () const
  {
    return m_drawn_y;
  }
  /**
   * Obtains the elements's drawn area's width (normalized window
   * coordinates) (0<->1).
   */
  float GetDrawnWidth () const
  {
    return m_drawn_w;
  }
  /**
   * Obtains the elements's drawn area's height (normalized window
   * coordinates) (0<->1).
   */
  float GetDrawnHeight () const
  {
    return m_drawn_h;
  }
  /**
   * Obtains the element's drawn area, converted to pixels (based on viewing
   * surface's dimensions).
   */
  void GetDrawnAreaPixels (int *ox, int *oy, int *ow, int *oh) const;
  /**
   * Obtains the viewing surface's viewport, in pixels.
   */
  void GetViewport (int *cx, int *cy, int *cw, int *ch) const;
  /**
   * Obtains the viewing surface's event notifier.
   */
  VglNotifier* GetNotifier () const
  {
    if (GetSubCanvas())
      return GetSubCanvas()->GetSubNotifier();
    else if (GetCanvas())
      return GetCanvas()->GetNotifier();
    else
      return NULL;
  }
  bool IsNativeRedraw () const
  {
    if (GetSubCanvas())
      return GetSubCanvas()->IsNativeRedraw();
    else if (GetCanvas())
      return GetCanvas()->IsNativeRedraw();
    else
      return m_is_native_redraw;
  }
  /**
   * Requests the redrawing of the viewing surface.
   */
  void RequestRedraw () const
  {
    if (GetSubCanvas())
      GetSubCanvas()->PostRedraw();
    else if (GetCanvas())
      GetCanvas()->PostRedraw();
  }
  /**
   * Drags the element by 'ammountx' and 'ammounty' (increments dragged ammount).
   */
  virtual void Drag (float ammount_x, float ammount_y);
  /**
   * Specifies the total dragged ammount for the element.
   */
  virtual void SetDragged (float ammount_x, float ammount_y);
  /**
   * Resets the dragged ammount.
   */
  virtual void ResetDragged ()
  {
    m_dragged_x = 0.0f;
    m_dragged_y = 0.0f;
  }
  /**
   * Constrains the dragging ammounts in 'x' and 'y' to the screen boundaries.
   */
  void ConstrainToScreenLimits (float &ammount_x, float &ammount_y) const;
  /**
   * Obtains the displacement between the x coordinates of the
   * original position and the dragged position.
   */
  virtual float GetDraggedX () const
  {
    return m_dragged_x;
  }
  /**
   * Obtains the displacement between the y coordinates of the
   * original position and the dragged position.
   */
  virtual float GetDraggedY () const
  {
    return m_dragged_y;
  }
  /**
   * Calls glColor(backgroundcolor).
   */
  void SetBackgroundColor() const;
  /**
   * Obtains a good color for fonts, given the current background color.
   */
  void GetFontColor (int *outr, int *outg, int *outb) const;
  /**
   * Callback functions
   * A notifier is given to provide additional information.
   */
  virtual void cbButton(float x, float y, int mbt, int mst, VglNotifier *ntf);
  virtual void cbButtonOutside(VglNotifier *ntf) {};
  virtual void cbMove(float x, float y, int mbt, VglNotifier *ntf) {};
  virtual bool cbDrag(float x, float y, int mbt, VglNotifier *ntf);
  virtual void cbKey(float x, float y, int k, int kst, VglNotifier *ntf) {};
  friend class SciActiveElementGroup;
  /**
   * Method that does the actual render of the element.
   * Must be defined in all derived classes.
   */
  virtual void doRender() = 0;
  /**
   * Pick method.
   * Returns true if given normalized coordinate lies inside the element,
   * false otherwise.
   */
  virtual bool Pick(float x, float y) = 0;
protected:
  AlgGLStack* GetProjectionStack () const
  {
    return m_pstack;
  }
private:
  /**
   * Viewing surface's handlers iterator type.
   */
  typedef DsPList<VglHandler>::Iterator HandlersIterator;
  /**
   * Obtains the viewing surface's event handlers.
   */
  HandlersIterator GetHandlers () const
  {
    if (GetSubCanvas())
      return GetSubCanvas()->GetHandlers();
    else
      return GetCanvas()->GetHandlers();
  }
  DsArray<VglHandler*> m_prev_active_handlers;
  char *m_name;
  VglCanvas *m_canvas;
  VglSubCanvas* m_subcanvas;
  float m_br, m_bg, m_bb, m_ba;
  float m_stx, m_sty;
  float m_drawn_x;
  float m_drawn_y;
  float m_drawn_w;
  float m_drawn_h;
  float m_dragged_x;
  float m_dragged_y;
  bool m_visible;
  bool m_drag_enabled;
  bool m_is_native_redraw;
  AlgGLStack* m_pstack;
};

//* *SciActiveElementGroup* Class
// Represents a group of active elements on a VGL Canvas
// Receives a canvas event and dispatches events accordingly to its members
class SCI_API SciActiveElementGroup : public SciActiveElement
{
public:
  SciActiveElementGroup(const char *name) :
    SciActiveElement(name),
    m_current(NULL),
    m_kfocus(false)
  {
  }
  virtual ~SciActiveElementGroup()
  {
  }
  /**
   * Specifies if the child elements can be dragged with the
   * middle mouse button.
   */
  virtual void SetDragEnabled (bool f);
    //* Canvas adjust
    // This setting is propagated among current children
  virtual void SetCanvas(VglCanvas *cnv);

  virtual void SetSubCanvas(VglSubCanvas *cnv);

    //* Visibility adjust
    // This setting is propagated among current children
  virtual void SetVisible(bool vis);

  virtual void Add(SciActiveElement *elem)
  {
    m_elements.Append(elem);
    if (GetSubCanvas())
      elem->SetSubCanvas(GetSubCanvas());
    if (GetCanvas())
      elem->SetCanvas(GetCanvas());
  }

  SciActiveElement* Get(int elem)
  {
    return (elem >= 0 && elem < m_elements.Size()) ? m_elements[elem] : NULL;
  }

  SciActiveElement* GetByName(const char *name);

  /**
   * Removes the first element with name 'name'.
   * Returns true if an element was found and removed, false otherwise.
   */
  virtual bool RemoveByName(const char *name);
  virtual bool Remove(int elem)
  {
    if (elem < 0 || elem >= m_elements.Size())
      return false;
    int newsize = m_elements.Size()-1;
    for (int i=elem; i<newsize; i++)
      m_elements[i] = m_elements[i+1];
    m_elements.Resize(newsize);
    return true;
  }
  virtual void SetKeyOnFocusOnly(bool v)
  {
    m_kfocus = v;
  }
    //* VglHandler
  static const char * CLASSNAME() { return "SciActiveElementGroup"; }
  virtual const char * ClassName() const { return CLASSNAME(); }
    //* VglHandler-compatible event methods
  virtual int MouseButton (int bt, int st, float x, float y);
  virtual int MouseMotion (int bt, float x, float y);
  virtual int MouseEntry (bool st);
  virtual int Keyboard (int k, int st, float x, float y);
    //* SciActiveElement
    //* Background adjust
    // Propagates setting to children
  virtual void SetBackground(float r, float g, float b, float a = 1.0f);
protected:
  virtual void cbButton(float x, float y, int mbt, int mst, VglNotifier *ntf);
  virtual void cbButtonOutside(VglNotifier *ntf);
  virtual void cbMove(float x, float y, int mbt, VglNotifier *ntf);
  virtual bool cbDrag(float x, float y, int mbt, VglNotifier *ntf);
  virtual void cbKey(float x, float y, int k, int kst, VglNotifier *ntf);
  virtual bool Pick(float x, float y);
  virtual void doRender();
private:
  int handle_button(int bt, int st, float x, float y);
  int handle_motion(int bt, float x, float y);
  DsArray<SciActiveElement*> m_elements;  // list of elements that belong to this group
  SciActiveElement *m_current;  // the group element currently in focus
  bool m_kfocus; // toggles dispatching of keyboard event to all elements of the group (false) or
                 // just to the element in focus (true)
};

//* *SciActiveElementGroupHandler* Class
// A Vgl handler to dispatch events to a given group
class SciActiveElementGroupHandler : public VglHandler
{
  SciActiveElementGroup *m_grp;

public:
  SciActiveElementGroupHandler(SciActiveElementGroup *grp)
    : m_grp(grp)
  {
  }
  virtual ~SciActiveElementGroupHandler()
  {
  }
  SciActiveElementGroup* GetGroup()
  {
    return m_grp;
  }

  static const char * CLASSNAME() { return "SciActiveElementGroupHandler"; }
  virtual const char * ClassName() const { return CLASSNAME(); }

  virtual int MouseButton (int bt, int st, float x, float y)
  {
    return m_grp->MouseButton(bt, st, x, y);
  }

  virtual int MouseMotion (int bt, float x, float y)
  {
    return m_grp->MouseMotion(bt, x, y);
  }

  virtual int MouseEntry (bool st)
  {
    return m_grp->MouseEntry(st);
  }

  virtual int Keyboard (int k, int st, float x, float y)
  {
    return m_grp->Keyboard(k, st, x, y);
  }
};


#endif
