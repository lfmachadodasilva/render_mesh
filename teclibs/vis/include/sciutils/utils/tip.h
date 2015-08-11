// tip.h
// An active title and subtitle.
// fabraham@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Mar 2006

#ifndef SCIUTILS_TIP_H
#define SCIUTILS_TIP_H

#include <sciutils/defines.h>
#include <ufont/fontmanagercompat.h>
#include <uso/clock.h>
#include <ds/array.h>
#include <assert.h>

class VglViewSurface;

/**
 * 'SciTip' Class
 * Draws a transparent tip on the canvas, depending on the mouse position.
 */
class SCI_API SciTip
{
public:

  SciTip (VglViewSurface *surface);
  virtual ~SciTip ()
  {
    free(m_font);
    free(m_text);
    free(m_tiptext);
  }
  void SetViewSurface (VglViewSurface *surface)
  {
    m_surface = surface;
  }
  bool SetFont (const char *font, int size, bool bold, bool italic)
  {
    if (!font)
      return false;
    if (!ufontfm_font_has_style(font,bold,italic))
      return false;
    free(m_font);
    m_font = strdup(font);
    m_fontsize = size;
    m_fontbold = bold;
    m_fontitalic = italic;
    ufontfm_set_font(m_font,m_fontsize,m_fontbold,m_fontitalic);
    m_fontascender = ufontfm_ascender();
    m_fontdescender = ufontfm_descender();
    m_fontheight = ufontfm_line_height();
    return true;
  }
  void SetBgColor (float r, float g, float b, float a)
  {
    m_bgcolor_r = r; 
    m_bgcolor_g = g; 
    m_bgcolor_b = b; 
    m_bgcolor_a = a;
  }
  void SetFgColor (float r, float g, float b)
  {
    m_fgcolor_r = r; 
    m_fgcolor_g = g; 
    m_fgcolor_b = b; 
  }
  void SetShadowColor (float r, float g, float b, float a)
  {
    m_shadowcolor_r = r; 
    m_shadowcolor_g = g; 
    m_shadowcolor_b = b; 
    m_shadowcolor_a = a;
  }
  void SetText (const char *text=NULL);
  void SetUseFontHeight (bool state)
  {
    m_usefontheight = state;
  }
  void SetXBorder (int pixels)
  {
    m_xborder = pixels;
  }
  void SetYBorder (int pixels)
  {
    m_yborder = pixels;
  }
  void SetXShadow (int pixels)
  {
    m_xshadow = pixels;
  }
  void SetYShadow (int pixels)
  {
    m_yshadow = pixels;
  }
  void SetCursorHeight(float val)
  {
    m_cursor_height = val;
  }
  void SetSpacing (float percentage)
  {
    m_spacing = percentage;
  }
  void SetPosition (float x, float y)
  {
    m_x = x;
    m_y = y;
  }
  void SetShadow (bool state)
  {
    m_shadow = state;
  }
  void SetEnabled (bool state)
  {
    m_timer.Stop();
    m_enabled = state;
  }
  bool IsEnabled () const
  {
    return m_enabled;
  }
  void DelayedEnable ()
  {
    if (!m_enabled && !m_timer.IsRunning())
      m_timer.Start();
  }
  void SetDelay (double time)
  {
    m_delay = time;
  }
  void Render ();

protected:

  VglViewSurface *GetSurface () const
  {
    return m_surface;
  }

private:

  void SetFont ()
  {
    assert(m_font);
    ufontfm_set_font(m_font,m_fontsize,m_fontbold,m_fontitalic);
  }

  void DoRender ();

  static void DoRender (void *data);

private:

  DsArray<unsigned int> m_tiplines; // First char of each line
  char *m_text;                     // Original text supplied
  char *m_tiptext;                  // Text with newlines replaced by zeroes
  char *m_font;
  int m_fontsize;
  bool m_fontbold;
  bool m_fontitalic;
  bool m_usefontheight;
  bool m_shadow;
  int m_fontheight;
  int m_fontascender;
  int m_fontdescender;
  int m_maxlinewidth;
  int m_maxlineheight;
  int m_xborder;
  int m_yborder;
  int m_xshadow;
  int m_yshadow;
  float m_spacing;
  float m_x;
  float m_y;
  float m_bgcolor_r;
  float m_bgcolor_g;
  float m_bgcolor_b;
  float m_bgcolor_a;
  float m_fgcolor_r;
  float m_fgcolor_g;
  float m_fgcolor_b;
  float m_shadowcolor_r;
  float m_shadowcolor_g;
  float m_shadowcolor_b;
  float m_shadowcolor_a;
  float m_cursor_height;
  bool m_enabled;
  VglViewSurface *m_surface;
  USOClock m_timer;
  double m_delay;
};

#endif
