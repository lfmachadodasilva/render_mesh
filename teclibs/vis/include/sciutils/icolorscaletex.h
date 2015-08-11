// icolorscale.h
// 21 Jun 2007

#ifndef ITF_COLORSCALE_TEX_H
#define ITF_COLORSCALE_TEX_H

#include <vgl/defines.h>
#include <sciutils/defines.h>
#include <stdio.h>

class VglCanvas;
class SciColorScaleTex;
class ItfColorScaleHandler;

class SCI_API ItfColorScaleTex
{
public:
  ItfColorScaleTex (VglCanvas* canvas, SciColorScaleTex* cs);
  ~ItfColorScaleTex ();
  void PixelLength (float* px, float *py);
  void DrawControlPoints ();
  void DrawControlLines ();
  void SetScaleChangedFunc(VglFunction func, void *data=NULL)
  {
    m_changed_func = func;
    m_changed_data = data;
  }
  SciColorScaleTex* GetColorScaleTex ()
  {
    return m_cs;
  }
  ItfColorScaleHandler* GetHandler ()
  {
    return m_handler;
  }
  void ScaleChanged ();
  void ResetCamera ();
private:
  bool IsFirstRender () const
  {
    return m_first_render;
  }
  void SetNotFirstRender ()
  {
    m_first_render = true;
  }
  static void RedrawFunc (void*);
private:
  VglCanvas* m_canvas;
  ItfColorScaleHandler* m_handler;
  SciColorScaleTex* m_cs;
  VglFunction m_changed_func;
  void *m_changed_data;
  unsigned int m_tex_icon;
  bool m_first_render;
};

#endif
