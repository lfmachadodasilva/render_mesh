// StateSequence class
// celes@tecgraf.puc-rio.br
// Jul 2002

#ifndef SG_STATESEQUENCE_H
#define SG_STATESEQUENCE_H

#include <sg/engine.h>

class SGStateSwitch;

class SG_API SGStateSequence : public SGEngine
{
  float m_t0;
  float m_delay;
  SGStateSwitch* m_ref;

public:
  static const char* CLASSNAME () { return "StateSequence"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
  SGStateSequence (SGStateSwitch* stateswitch);
  virtual ~SGStateSequence ();

  void SetDelay (float delay);

  virtual void Start (float time);
  virtual void Apply (float time);
  virtual void Write (UtlWriter* writer);
};

#endif
