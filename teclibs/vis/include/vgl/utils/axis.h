#ifndef VGL_AXIS_H
#define VGL_AXIS_H

#include <vgl/defines.h>
#include <alg/vector.h>

class VglViewSurface;

class VGL_API VglAxisRender
{
public:
  VglAxisRender (VglViewSurface* surface) :
    m_surface(surface),
    m_axis(0.0f,1.0f,0.0f),
    m_thickness(1.0f),
    m_axis_size(100.0f),
    m_posset(false)
  {
  }
  void SetViewSurface (VglViewSurface *surface)
  {
    m_surface = surface;
  }
  void SetAxis (const AlgVector &axis)
  {
    m_axis = axis;
  }
  void SetAxisSize (float size)
  {
    m_axis_size = size;
  }
  float GetAxisSize () const
  {
    return m_axis_size;
  }
  void SetThickness (float thickness)
  {
    m_thickness = thickness;
  }
  float GetThickness () const
  {
    return m_thickness;
  }
  void SetAxisPosition (const AlgVector &pos)
  {
    m_pos = pos;
    m_posset = true;
  }
  void UnsetAxisPosition ()
  {
    m_posset = false;
  }
  void RenderAxis();
private:
  VglViewSurface *m_surface;
  AlgVector m_axis;
  AlgVector m_pos;
  float m_thickness;
  float m_axis_size;
  bool m_posset;
};

#endif
