//* title.h
// An active title and subtitle.
// Tecgraf/PUC-Rio
// Mar 2004

#ifndef SCIUTILS_TITLE_H
#define SCIUTILS_TITLE_H

#include <GL/glew.h>
#include <sciutils/actelem2d.h>
#include <sciutils/defines.h>
#include <ufont/fontmanagercompat.h>

//* 'SciActiveElementTitle' Class
// Represents an active title/subtitle.
class SCI_API SciActiveElementTitle : public Sci2DActiveElement
{
  char *m_title;
  char *m_subtitle;
  char *m_titlefont;
  char *m_subtitlefont;
  int m_titlesize;
  int m_subtitlesize;
  bool m_titlebold;
  bool m_titleitalic;
  bool m_subtitlebold;
  bool m_subtitleitalic;

  float m_tr, m_tg, m_tb;
  float m_str, m_stg, m_stb;

  void SetTitleFont () const
  {
    assert(m_titlefont);
    ufontfm_set_font(m_titlefont,m_titlesize,m_titlebold,m_titleitalic);
  }
  void SetSubTitleFont () const
  {
    assert(m_subtitlefont);
    ufontfm_set_font(m_subtitlefont,m_subtitlesize,m_subtitlebold,m_subtitleitalic);
  }
public:
  SciActiveElementTitle(const char *name)
    : Sci2DActiveElement(name),
      m_title(NULL), m_subtitle(NULL),
      m_titlefont(NULL), m_subtitlefont(NULL),
      m_titlesize(-1),
      m_subtitlesize(-1),
      m_titlebold(false),
      m_titleitalic(false),
      m_subtitlebold(false),
      m_subtitleitalic(false),
      m_tr(0.0f), m_tg(0.0f), m_tb(0.0f),
      m_str(0.0f), m_stg(0.0f), m_stb(0.0f)
  {
    ufontfm_init();
  }
  virtual ~SciActiveElementTitle()
  {
    free(m_title);
    free(m_subtitle);
    free(m_titlefont);
    free(m_subtitlefont);
  }
  void SetTitle(const char *t)
  {
    if (!Changed(m_title,t))
      return;
    free(m_title);
    m_title = t ? strdup(t) : NULL;
    SetOutDated();
  }
  void SetTitleFont(const char *font, int size, bool bold, bool italic)
  {
    if (size == m_titlesize &&
        bold == m_titlebold &&
        italic == m_titleitalic &&
        !Changed(m_titlefont,font))
      return;
    if (!ufontfm_font_has_style(font,bold,italic))
    {
      printf(
        "SCIUTILS: Failed setting title font to '%s', style=%s\n",
        font,
        bold ?
          (italic ? "Bold&Italic" : "Bold") :
          (italic ? "Italic" : "Regular")
      );
      SetTitleFont("GLUT Helvetica",18,false,false);
      return;
    }
    free(m_titlefont);
    m_titlefont = strdup(font);
    m_titlesize = size;
    m_titlebold = bold;
    m_titleitalic = italic;
    SetOutDated();
  }
  void SetSubTitleFont(const char *font, int size, bool bold, bool italic)
  {
    if (size == m_subtitlesize &&
        bold == m_subtitlebold &&
        italic == m_subtitleitalic &&
        !Changed(m_subtitlefont,font))
      return;
    if (!ufontfm_font_has_style(font,bold,italic))
    {
      printf(
        "SCIUTILS: Failed setting title font to '%s', style=%s\n",
        font,
        bold ?
          (italic ? "Bold&Italic" : "Bold") :
          (italic ? "Italic" : "Regular")
      );
      SetSubTitleFont("GLUT Helvetica",18,false,false);
      return;
    }
    free(m_subtitlefont);
    m_subtitlefont = strdup(font);
    m_subtitlesize = size;
    m_subtitlebold = bold;
    m_subtitleitalic = italic;
    SetOutDated();
  }
  void SetSubTitle(const char *t)
  {
    if (!Changed(m_subtitle,t))
      return;
    free(m_subtitle);
    m_subtitle = t ? strdup(t) : NULL;
    SetOutDated();
  }
  void SetTitleColor(float r, float g, float b)
  {
    if (r == m_tr && g == m_tg && b == m_tb)
      return;
    m_tr = r; m_tg = g; m_tb = b;
    SetOutDated();
  }
  void SetSubTitleColor(float r, float g, float b)
  {
    if (r == m_str && g == m_stg && b == m_stb)
      return;
    m_str = r; m_stg = g; m_stb = b;
    SetOutDated();
  }
  const char * GetTitle()
  {
    return m_title;
  }
  const char * GetTitleFont()
  {
    return m_titlefont;
  }
  const char * GetSubTitle()
  {
    return m_subtitle;
  }
  const char * GetSubTitleFont()
  {
    return m_subtitlefont;
  }
  void GetTitleColor(float *r, float *g, float *b)
  {
    *r = m_tr;
    *g = m_tg;
    *b = m_tb;
  }
  void GetSubTitleColor(float *r, float *g, float *b)
  {
    *r = m_str;
    *g = m_stg;
    *b = m_stb;
  }
  virtual void SetDrawableArea (float x, float y, float w, float h);
protected:
  virtual bool Pick(float x, float y)
  {
    return false;
  }
  virtual void doRender();
  virtual void GetDrawnArea (float *ox, float *oy, float *ow, float *oh) const;
private:
  void GetTextLengths (int *titlelen, int *subtitlelen) const;
  void GetTitleQuad (const GLint *vp, int titlelen, float *oxmin, float *oxmax, float *oymin, float *oymax) const;
  void GetSubtitleQuad (const GLint *vp, int subtitlelen, float *oxmin, float *oxmax, float *oymin, float *oymax) const;
};

#endif
