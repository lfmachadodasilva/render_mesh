// Color class
// celes@tecgraf.puc-rio.br
// Jul 2002 

#ifndef SG_COLOR_H
#define SG_COLOR_H

#include <sg/state.h>
#include <utl/defines.h>

class SG_API SGColor : public SGState
{
  uchar m_red, m_green, m_blue, m_alpha;
public:
  static const char* CLASSNAME () { return "Color"; }
  virtual const char* ClassName () const { return CLASSNAME(); }

  SGColor () : m_red(255), m_green(255), m_blue(255), m_alpha(255) {}
  SGColor (float red, float green, float blue, float alpha=1.0f);
  virtual ~SGColor ();

  void SetColor(float red, float green, float blue, float alpha=1.0f);
  virtual void Load ();
  virtual void Unload ();
  virtual bool IsOpaque () const;
  virtual void Write (UtlWriter* writer);
};

#endif
