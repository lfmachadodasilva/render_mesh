// LOD selection Strategy
// fabraham@tecgraf.puc-rio.br
// Oct 2004

#ifndef SG_LOD
#define SG_LOD

#include <sg/strat/interceptor.h>
#include <sg/strat/immediate.h>
#include <sg/camera.h>
#include <sg/modules/sglod.h>

class SGObject;
/**
 * LOD selection traversal strategy.
 * This strategy will intercept the calls to a strategy performing
 * LOD selection on objects.
 */
class SGLODAPI SGLOD : public SGInterceptor
{
  SGObject *m_obj;
  SGImmediate *m_tstrategy;
  AlgStack *m_stack;
  float m_minfovsin;
  void InitFrame ();
  void Select (SGObject *o);
public:
  SGLOD (SGStrategy* strategy, SGImmediate *t) : SGInterceptor(strategy), m_tstrategy(t)
  {
  }
  virtual ~SGLOD ()
  {
  }
  void SetImmediate (SGImmediate *t)
  {
    m_tstrategy = t;
  }
  virtual int Load (SGColScene *s);
  virtual int Load (SGColObject *o);
};

#endif
