// Acceleration Strategy
// fabraham@tecgraf.puc-rio.br
// Nov 2003

#ifndef SG_ACCEL
#define SG_ACCEL

#include <sg/strategy.h>
#include <sg/light.h>
#include <sg/node.h>
#include <sg/entity.h>
#include <sg/group.h>
#include <sg/switch.h>
#include <sg/object.h>
#include <sg/scene.h>
#include <sg/colobject.h>
#include <sg/collight.h>
#include <sg/colscene.h>
#include "transfstrategy.h"
#include "interceptor.h"

/**
 * Acceleration algorithm abstract traversal strategy.
 * 
 * This strategy will intercept all the calls to a transf strategy.
 * 
 * Concrete implementations of acceleration algorithms can:
 * - skip geometry that is partially or totally invisible.
 * - select appropriate LOD levels.
 * - etc
 */
class SG_API SGAccel : public SGInterceptor
{
protected:
  /**
   * Obtains the transfstrategy's matrix stack. 
   */
  AlgStack* GetStack ()
  {
    return GetTransfStrategy()->GetStack();
  }
public:
  /**
   * Constructor. Receives the intercepted TransfStrategy.
   */
  SGAccel (SGTransfStrategy* strategy) : SGInterceptor(strategy)
  {
  }
  /**
   * Destructor.
   */
  virtual ~SGAccel ()
  {
  }
  /**
   * Obtains the intercepted TransfStrategy.
   */
  SGTransfStrategy* GetTransfStrategy () const
  {
    return (SGTransfStrategy*)SGInterceptor::GetStrategy();
  }
  virtual void SetStrategy(SGStrategy* strategy)
  {
    // TODO: check if strategy is a sgtransfstrategy
    SGInterceptor::SetStrategy(strategy);
  }
  // PreLoad/PostLoad methods: will chain calls like SGStrategy methods.
  virtual bool PreLoad(SGShape* s)
  {
    return true;
  }
  virtual bool PreLoad(SGNode* n)
  {
    return true;
  }
  virtual bool PostLoad(SGNode* n)
  {
    return true;
  }
  virtual void PostUnload(SGNode* n)
  {
  }
  virtual bool PreLoad(SGLight* l)
  {
    return PreLoad((SGNode*)l);
  }
  virtual bool PostLoad(SGLight* l)
  {
    return PostLoad((SGNode*)l);
  }
  virtual void PostUnload(SGLight* l)
  {
    PostUnload((SGNode*)l);
  }
  virtual bool PreLoad(SGSpace* s)
  {
    return PreLoad((SGNode*)s);
  }
  virtual bool PostLoad(SGSpace* s)
  {
    return PostLoad((SGNode*)s);
  }
  virtual void PostUnload(SGSpace* s)
  {
    PostUnload((SGNode*)s);
  }
  virtual bool PreLoad(SGEntity* s)
  {
    return PreLoad((SGSpace*)s);
  }
  virtual bool PostLoad(SGEntity* s)
  {
    return PostLoad((SGSpace*)s);
  }
  virtual void PostUnload(SGEntity* s)
  {
    PostUnload((SGSpace*)s);
  }
  virtual bool PreLoad(SGObject* o)
  {
    return PreLoad((SGEntity*)o);
  }
  virtual bool PostLoad(SGObject* o)
  {
    return PostLoad((SGEntity*)o);
  }
  virtual void PostUnload(SGObject* o)
  {
    PostUnload((SGEntity*)o);
  }
  virtual bool PreLoad(SGGroup* g)
  {
    return PreLoad((SGEntity*)g);
  }
  virtual bool PostLoad(SGGroup* g)
  {
    return PostLoad((SGEntity*)g);
  }
  virtual void PostUnload(SGGroup* g)
  {
    PostUnload((SGEntity*)g);
  }
  virtual bool PreLoad(SGSwitch* s)
  {
    return PreLoad((SGGroup*)s);
  }
  virtual bool PostLoad(SGSwitch* s)
  {
    return PostLoad((SGGroup*)s);
  }
  virtual void PostUnload(SGSwitch* s)
  {
    PostUnload((SGGroup*)s);
  }
  virtual bool PreLoad(SGScene* s)
  {
    return PreLoad((SGSpace*)s);
  }
  virtual bool PostLoad(SGScene* s)
  {
    return PostLoad((SGSpace*)s);
  }
  virtual void PostUnload(SGScene* s)
  {
    PostUnload((SGSpace*)s);
  }
  virtual bool PreLoad(SGCollection* c)
  {
    return PreLoad((SGNode*)c);
  }
  virtual bool PostLoad(SGCollection* c)
  {
    return PostLoad((SGNode*)c);
  }
  virtual void PostUnload(SGCollection* c)
  {
    PostUnload((SGNode*)c);
  }
  virtual bool PreLoad(SGColLight* s)
  {
    return PreLoad((SGCollection*)s);
  }
  virtual bool PostLoad(SGColLight* s)
  {
    return PostLoad((SGCollection*)s);
  }
  virtual void PostUnload(SGColLight* s)
  {
    PostUnload((SGCollection*)s);
  }
  virtual bool PreLoad(SGColObject* s)
  {
    return PreLoad((SGCollection*)s);
  }
  virtual bool PostLoad(SGColObject* s)
  {
    return PostLoad((SGCollection*)s);
  }
  virtual void PostUnload(SGColObject* s)
  {
    PostUnload((SGCollection*)s);
  }
  virtual bool PreLoad(SGColScene* s)
  {
    return PreLoad((SGCollection*)s);
  }
  virtual bool PostLoad(SGColScene* s)
  {
    return PostLoad((SGCollection*)s);
  }
  virtual void PostUnload(SGColScene* s)
  {
    PostUnload((SGCollection*)s);
  }
  virtual bool PreLoad(SGBin* b)
  {
    return PreLoad((SGCollection*)b);
  }
  virtual bool PostLoad(SGBin* b)
  {
    return PostLoad((SGCollection*)b);
  }
  virtual void PostUnload(SGBin* b)
  {
    PostUnload((SGCollection*)b);
  }
  virtual void Load (SGShape* s)
  {
    if (PreLoad(s))
      SGInterceptor::Load(s);
  }
  virtual int Load (SGNode* n)
  {
    int r = SGInterceptor::Load(n);
    if (r != CONTINUE || PostLoad(n))
      return r;
    else
    {
      SGInterceptor::Unload(n);
      return SKIP;
    }
  }
  virtual int Load (SGLight* l)
  {
    int r = SGInterceptor::Load(l);
    if (r != CONTINUE || PostLoad(l))
      return r;
    else
    {
      SGInterceptor::Unload(l);
      return SKIP;
    }
  }
  virtual int Load (SGSpace* c)
  {
    int r = SGInterceptor::Load(c);
    if (r != CONTINUE || PostLoad(c))
      return r;
    else
    {
      SGInterceptor::Unload(c);
      return SKIP;
    }
  }
  virtual int Load (SGEntity* e)
  {
    int r = SGInterceptor::Load(e);
    if (r != CONTINUE || PostLoad(e))
      return r;
    else
    {
      SGInterceptor::Unload(e);
      return SKIP;
    }
  }
  virtual int Load (SGObject* o)
  {
    int r = SGInterceptor::Load(o);
    if (r != CONTINUE || PostLoad(o))
      return r;
    else
    {
      SGInterceptor::Unload(o);
      return SKIP;
    }
  }
  virtual int Load (SGGroup* g)
  {
    int r = SGInterceptor::Load(g);
    if (r != CONTINUE || PostLoad(g))
      return r;
    else
    {
      SGInterceptor::Unload(g);
      return SKIP;
    }
  }
  virtual int Load (SGSwitch* s)
  {
    int r = SGInterceptor::Load(s);
    if (r != CONTINUE || PostLoad(s))
      return r;
    else
    {
      SGInterceptor::Unload(s);
      return SKIP;
    }
  }
  virtual int Load (SGScene* s)
  {
    int r = SGInterceptor::Load(s);
    if (r != CONTINUE || PostLoad(s))
      return r;
    else
    {
      SGInterceptor::Unload(s);
      return SKIP;
    }
  }
  virtual int Load (SGCollection* c)
  {
    int r = SGInterceptor::Load(c);
    if (r != CONTINUE || PostLoad(c))
      return r;
    else
    {
      SGInterceptor::Unload(c);
      return SKIP;
    }
  }
  virtual int Load (SGColObject* o)
  {
    int r = SGInterceptor::Load(o);
    if (r != CONTINUE || PostLoad(o))
      return r;
    else
    {
      SGInterceptor::Unload(o);
      return SKIP;
    }
  }
  virtual int Load (SGColLight* l)
  {
    int r = SGInterceptor::Load(l);
    if (r != CONTINUE || PostLoad(l))
      return r;
    else
    {
      SGInterceptor::Unload(l);
      return SKIP;
    }
  }
  virtual int Load (SGColScene* s)
  {
    int r = SGInterceptor::Load(s);
    if (r != CONTINUE || PostLoad(s))
      return r;
    else
    {
      SGInterceptor::Unload(s);
      return SKIP;
    }
  }
  virtual int Load (SGBin* b)
  {
    int r = SGInterceptor::Load(b);
    if (r != CONTINUE || PostLoad(b))
      return r;
    else
    {
      SGInterceptor::Unload(b);
      return SKIP;
    }
  }
  virtual int Unload (SGNode* n)
  {
    switch(SGInterceptor::Unload(n))
    {
    case BREAK:
      return BREAK;
    case CONTINUE:
    default:
      PostUnload(n);
      return CONTINUE;
    }
  }
  virtual int Unload (SGLight* l)
  {
    switch(SGInterceptor::Unload(l))
    {
    case BREAK:
      return BREAK;
    case CONTINUE:
    default:
      PostUnload(l);
      return CONTINUE;
    }
  }
  virtual int Unload (SGSpace* c)
  {
    switch(SGInterceptor::Unload(c))
    {
    case BREAK:
      return BREAK;
    case CONTINUE:
    default:
      PostUnload(c);
      return CONTINUE;
    }
  }
  virtual int Unload (SGEntity* e)
  {
    switch(SGInterceptor::Unload(e))
    {
    case BREAK:
      return BREAK;
    case CONTINUE:
    default:
      PostUnload(e);
      return CONTINUE;
    }
  }
  virtual int Unload (SGObject* o)
  {
    switch(SGInterceptor::Unload(o))
    {
    case BREAK:
      return BREAK;
    case CONTINUE:
    default:
      PostUnload(o);
      return CONTINUE;
    }
  }
  virtual int Unload (SGGroup* g)
  {
    switch(SGInterceptor::Unload(g))
    {
    case BREAK:
      return BREAK;
    case CONTINUE:
    default:
      PostUnload(g);
      return CONTINUE;
    }
  }
  virtual int Unload (SGSwitch* s)
  {
    switch(SGInterceptor::Unload(s))
    {
    case BREAK:
      return BREAK;
    case CONTINUE:
    default:
      PostUnload(s);
      return CONTINUE;
    }
  }
  virtual int Unload (SGScene* s)
  {
    switch(SGInterceptor::Unload(s))
    {
    case BREAK:
      return BREAK;
    case CONTINUE:
    default:
      PostUnload(s);
      return CONTINUE;
    }
  }
  virtual int Unload (SGCollection* c)
  {
    switch(SGInterceptor::Unload(c))
    {
    case BREAK:
      return BREAK;
    case CONTINUE:
    default:
      PostUnload(c);
      return CONTINUE;
    }
  }
  virtual int Unload (SGColObject* o)
  {
    switch(SGInterceptor::Unload(o))
    {
    case BREAK:
      return BREAK;
    case CONTINUE:
    default:
      PostUnload(o);
      return CONTINUE;
    }
  }
  virtual int Unload (SGColLight* l)
  {
    switch(SGInterceptor::Unload(l))
    {
    case BREAK:
      return BREAK;
    case CONTINUE:
    default:
      PostUnload(l);
      return CONTINUE;
    }
  }
  virtual int Unload (SGColScene* s)
  {
    switch(SGInterceptor::Unload(s))
    {
    case BREAK:
      return BREAK;
    case CONTINUE:
    default:
      PostUnload(s);
      return CONTINUE;
    }
  }
  virtual int Unload (SGBin* b)
  {
    switch(SGInterceptor::Unload(b))
    {
    case BREAK:
      return BREAK;
    case CONTINUE:
    default:
      PostUnload(b);
      return CONTINUE;
    }
  }
};

#endif
