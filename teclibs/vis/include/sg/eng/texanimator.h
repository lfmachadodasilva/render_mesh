// TexAnimator class
// celes@tecgraf.puc-rio.br
// Jul 2002

#ifndef SG_TEXANIMATOR_H
#define SG_TEXANIMATOR_H

#include <sg/engine.h>

class SGTexture;

class SG_API SGTexAnimator : public SGEngine
{
  float m_t0;
  float m_vx, m_vy, m_vz;
  SGTexture* m_ref;
public:
  static const char* CLASSNAME () { return "TexAnimator"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
  SGTexAnimator (SGTexture* ref);
  virtual ~SGTexAnimator ();

  void SetVelocity (float vx, float vy=0.0f, float vz=0.0f);

  virtual void Start (float time);
  virtual void Apply (float time);
  virtual void Write (UtlWriter* writer);
};

#endif
