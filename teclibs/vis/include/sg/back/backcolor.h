// backcolor.h
// celes@tecgraf.puc-rio.br
// Jul 2002

#ifndef SG_BACKCOLOR_H
#define SG_BACKCOLOR_H

#include <sg/background.h>

class SG_API SGBackColor : public SGBackground 
{
  float m_red, m_green, m_blue, m_alpha;
public:
  static const char* CLASSNAME () { return "BackColor"; }
  virtual const char* ClassName () const { return CLASSNAME(); }

  SGBackColor (float red=0.0f, float green=0.0f, float blue=0.0f, float alpha=1.0f);
  virtual ~SGBackColor ();

  void SetColor(float red, float green, float blue, float alpha=1.0f);

  virtual void BeginRender ();
	virtual void EndRender ();
  virtual void Write (UtlWriter * writer);
};

#endif
