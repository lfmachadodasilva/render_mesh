// Fog class
// celes@tecgraf.puc-rio.br
// Jul 2002

#ifndef SG_FOG_H
#define SG_FOG_H

#include <sg/state.h>

class SG_API SGFog : public SGState
{
  enum {
    NONE=0,
    LINEAR,
    EXP,
    EXP2
  };
  int m_mode;
  float m_start, m_end;
  float m_density;
  float m_color[4];
public:
  static const char* CLASSNAME () { return "Fog"; }
  virtual const char* ClassName () const { return CLASSNAME(); }

  SGFog ();
  virtual ~SGFog ();

  void SetLinearMode (float start, float end);
  void SetExpMode (float density);
  void SetExp2Mode (float density);
  void SetColor (float red, float green, float blue, float alpha=1.0f);

  virtual void Load ();
  virtual void Unload ();
  virtual bool IsOpaque () const;
  virtual void Write (UtlWriter* writer);
};

#endif
