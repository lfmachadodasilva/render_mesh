// 2D Active elements
// fabraham@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Jul 2006

#ifndef SCI_2D_ACTELEM_H
#define SCI_2D_ACTELEM_H

#include "actelem.h"
#include <sciutils/defines.h>

class UGLTexture;

/**
 * Sci2DActiveElement abstract class.
 *
 * This class implements basic functions for 2D active elements.
 * 
 * A mechanism is provided to re-use the rendered image of the 2D
 * element if no change to it is made.
 * Derived classes must inform the drawn area and when the image
 * must be updated.
 *
 * This class also contains a background color.
 */
class SCI_API Sci2DActiveElement : public SciActiveElement
{
public:
  virtual ~Sci2DActiveElement();
  virtual void Render();
  virtual void SetBackground(float r, float g, float b, float a = 1.0f);
  /**
   * Informs that the attributes of the element were changed
   * and its image must be regenerated in the next Render() call.
   */
  virtual void SetOutDated ();
  /**
   * Specifies if the rendered images must be reused if no change
   * to the element is made.
   */
  virtual void SetEnableOptimizations (bool f)
  {
    if (f != AreOptimizationsEnabled())
    {
      m_enable_opt = f;
      SetOutDated();
    }
  }
  /**
   * Will the rendered images be reused if no change
   * to the element is made?
   */
  bool AreOptimizationsEnabled () const
  {
    return m_enable_opt;
  }
  /**
   * Specifies the possible area for the element to be drawn.
   * x and y specify the beginning of the window,
   * width and height specify the dimension of the window.
   *
   * x,y,w and h are specified in normalized window coordinates.
   */
  virtual void SetDrawableArea (float x, float y, float width, float height) = 0;
  virtual void SetDragEnabled (bool f)
  {
    if (f == IsDragEnabled())
      return;
    SciActiveElement::SetDragEnabled(f);
    SetOutDated();
  }
protected:
  /**
   * Constructor. 'name' names the element.
   */
  Sci2DActiveElement(const char *name);
  /**
   * Is 'current' different from 'incoming' ?
   * Treats the case when either of them are NULL.
   */
  static bool Changed (const char *current, const char *incoming)
  {
    if (current)
    {
      if (incoming)
        return strcmp(current,incoming) != 0;
      else
        return false;
    }
    else
      return incoming != NULL;
  }
  virtual void Drag (float ammount_x, float ammount_y);
  virtual void SetDragged (float ammount_x, float ammount_y);
  bool IsUpdated () const
  {
    return m_updated;
  }
private:
  void UpdateTexture ();
  void CalcTextureClippingPlanes (int rw, int rh);
  void RenderTexture ();
  void SetUpdated ()
  {
    m_updated = true;
  }
  UGLTexture* GetTexture () const
  {
    return m_texture;
  }
  void SaveResolution ()
  {
    int dull;
    GetViewport(&dull,&dull,&m_res_w,&m_res_h);
  }
  bool ResolutionHasntChanged() const
  {
    int dull, vpw, vph;
    GetViewport(&dull,&dull,&vpw,&vph);
    return (vpw == m_res_w && vph == m_res_h);
  }
  UGLTexture *m_texture;
  bool m_updated;
  int m_rx, m_ry, m_rw, m_rh;
  int m_res_w, m_res_h;
  double m_clip_x[4];
  double m_clip_y[4];
  bool m_enable_opt;
  bool m_last_frame_rendered;
};

#endif
