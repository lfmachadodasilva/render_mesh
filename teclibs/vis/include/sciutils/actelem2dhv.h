// actelem2dhv.h
// 2D Active Element with Horizontal/Vertical orientations
// fabraham@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Aug 2006

#ifndef SCIUTILS_ACTELEM2DHV_H
#define SCIUTILS_ACTELEM2DHV_H

#include "actelem2d.h"
#include <sciutils/defines.h>

class SCI_API Sci2DActiveElementHV : public Sci2DActiveElement
{
public:
  virtual void SetHorizontal (bool v);
  bool IsHorizontal () const
  {
    return m_horiz;
  }
  void SetDrawableArea (float x, float y, float w, float h)
  {
    if (IsHorizontal())
      SetDrawableAreaH(x,y,w,h);
    else
      SetDrawableAreaV(x,y,w,h);
  }
  virtual void SetDrawableAreaH (float x, float y, float w, float h) = 0;
  virtual void SetDrawableAreaV (float x, float y, float w, float h) = 0;
protected:
  Sci2DActiveElementHV (const char *name);
  virtual float GetDrawnX () const;
  virtual float GetDrawnY () const;
  float GetDrawnXH () const
  {
    return GetDrawnX();
  }
  float GetDrawnYH () const
  {
    return GetDrawnY();
  }
  float GetDrawnXV () const
  {
    return m_drawn_v_x;
  }
  float GetDrawnYV () const
  {
    return m_drawn_v_y;
  }
  float GetDrawnWidthV () const
  {
    return m_drawn_v_w;
  }
  float GetDrawnHeightV () const
  {
    return m_drawn_v_h;
  }
  virtual void Drag (float ammount_x, float ammount_y);
  virtual void SetDraggedH (float ammount_x, float ammount_y);
  virtual void SetDraggedV (float ammount_x, float ammount_y);
  virtual float GetDraggedX () const;
  virtual float GetDraggedY () const;
  virtual float GetDraggedXH () const;
  virtual float GetDraggedYH () const;
  virtual float GetDraggedXV () const;
  virtual float GetDraggedYV () const;
  virtual void SetDrawnAreaH (float x, float y, float w, float h);
  virtual void SetDrawnAreaV (float x, float y, float w, float h);
  virtual void GetDrawnArea (float *ox, float *oy, float *ow, float *oh) const;
  virtual void SetDraggedXH (float ammount_x);
  virtual void SetDraggedYH (float ammount_y);
  virtual void SetDraggedXV (float ammount_x);
  virtual void SetDraggedYV (float ammount_y);
private:
  float m_drawn_v_x;
  float m_drawn_v_y;
  float m_drawn_v_w;
  float m_drawn_v_h;
  float m_dragged_v_x;
  float m_dragged_v_y;
  bool m_horiz;
};

#endif
