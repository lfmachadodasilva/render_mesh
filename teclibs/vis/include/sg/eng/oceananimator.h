// SGOceanAnimator class
// fabraham@tecgraf.puc-rio.br
// Jun 2003

#ifndef SG_OCEANANIMATOR_H
#define SG_OCEANANIMATOR_H

#include <sg/engine.h>

class SGOcean;

class SGOceanAnimator : public SGEngine
{
  float m_t0;
  SGOcean* m_ref;
public:
  static const char* CLASSNAME () { return "OceanAnimator"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
  SGOceanAnimator (SGOcean* ref);
  virtual ~SGOceanAnimator ();

  virtual void Start (float time);
  virtual void Apply (float time);
  virtual void Write (UtlWriter* writer);
};

#endif
