// SGSkyAnimator class
// djavanes@tecgraf.puc-rio.br
// Jul 2002

#ifndef SG_SKYANIMATOR_H
#define SG_SKYANIMATOR_H

#include <sg/engine.h>
#include <sg/lua/sgsky.h>

class SGSky;

class SGSKYAPI SGSkyAnimator : public SGEngine
{
  float m_t0;
  SGSky* m_ref;
public:
  static const char* CLASSNAME () { return "SkyAnimator"; }
  virtual const char* ClassName () { return CLASSNAME(); }

  SGSkyAnimator (SGSky* ref);
  virtual ~SGSkyAnimator ();

  virtual void Start (float time);
  virtual void Apply (float time);
  virtual void Write (UtlWriter* writer);
};

#endif
