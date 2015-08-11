// Acceleration Strategies Chain
// fabraham@tecgraf.puc-rio.br
// Apr 2005

#ifndef SG_CHAIN
#define SG_CHAIN

#include <sg/strat/accel.h>
#include <ds/list.h>

class SGH_API SGAccelChain : public SGAccel
{
  DsPList<SGAccel> m_chain;
public:
  /**
   * Constructor. Receives the intercepted TransfStrategy.
   */
  SGAccelChain (SGTransfStrategy* strategy) : SGAccel(strategy)
  {
  }
  /**
   * Destructor.
   */
  virtual ~SGAccelChain ()
  {
  }
  /**
   * Inserts an acceleration strategy in the chain.
   * The last strategies will be the last to intercept the calls.
   */
  void Insert (SGAccel *a)
  {
    m_chain.Append(a);
    a->SetStrategy(GetStrategy());
  }
  /**
   * Removes an acceleration strategy from the chain.
   * Returns if the strategy was found.
   */
  bool Remove (SGAccel *a)
  {
    return m_chain.Remove(a);
  }
  virtual void SetStrategy(SGStrategy* strategy)
  {
    SGAccel::SetStrategy(strategy);
    for (DsPList<SGAccel>::Iterator i=m_chain.Begin(); i.Valid(); ++i)
      i->SetStrategy(strategy);
  }
  // PreLoad/PostLoad methods: will call all strategies in the chain.
  virtual bool PreLoad(SGShape* s)
  {
    for (DsPList<SGAccel>::Iterator i=m_chain.Begin(); i.Valid(); ++i)
      if (!i->PreLoad(s))
        return false;
    return true;
  }
  virtual bool PreLoad(SGNode* n)
  {
    for (DsPList<SGAccel>::Iterator i=m_chain.Begin(); i.Valid(); ++i)
      if (!i->PreLoad(n))
        return false;
    return true;
  }
  virtual bool PostLoad(SGNode* n)
  {
    for (DsPList<SGAccel>::Iterator i=m_chain.Begin(); i.Valid(); ++i)
      if (!i->PostLoad(n))
        return false;
    return true;
  }
  virtual void PostUnload(SGNode* n)
  {
    for (DsPList<SGAccel>::Iterator i=m_chain.Begin(); i.Valid(); ++i) // TODO: think: must reverse order?
      i->PostUnload(n);
  }
  virtual bool PreLoad(SGLight* s)
  {
    for (DsPList<SGAccel>::Iterator i=m_chain.Begin(); i.Valid(); ++i)
      if (!i->PreLoad(s))
        return false;
    return true;
  }
  virtual bool PostLoad(SGLight* s)
  {
    for (DsPList<SGAccel>::Iterator i=m_chain.Begin(); i.Valid(); ++i)
      if (!i->PostLoad(s))
        return false;
    return true;
  }
  virtual void PostUnload(SGLight* s)
  {
    for (DsPList<SGAccel>::Iterator i=m_chain.Begin(); i.Valid(); ++i) // TODO: think: must reverse order?
      i->PostUnload(s);
  }
  virtual bool PreLoad(SGSpace* s)
  {
    for (DsPList<SGAccel>::Iterator i=m_chain.Begin(); i.Valid(); ++i)
      if (!i->PreLoad(s))
        return false;
    return true;
  }
  virtual bool PostLoad(SGSpace* s)
  {
    for (DsPList<SGAccel>::Iterator i=m_chain.Begin(); i.Valid(); ++i)
      if (!i->PostLoad(s))
        return false;
    return true;
  }
  virtual void PostUnload(SGSpace* s)
  {
    for (DsPList<SGAccel>::Iterator i=m_chain.Begin(); i.Valid(); ++i) // TODO: think: must reverse order?
      i->PostUnload(s);
  }
  virtual bool PreLoad(SGEntity* s)
  {
    for (DsPList<SGAccel>::Iterator i=m_chain.Begin(); i.Valid(); ++i)
      if (!i->PreLoad(s))
        return false;
    return true;
  }
  virtual bool PostLoad(SGEntity* s)
  {
    for (DsPList<SGAccel>::Iterator i=m_chain.Begin(); i.Valid(); ++i)
      if (!i->PostLoad(s))
        return false;
    return true;
  }
  virtual void PostUnload(SGEntity* s)
  {
    for (DsPList<SGAccel>::Iterator i=m_chain.Begin(); i.Valid(); ++i) // TODO: think: must reverse order?
      i->PostUnload(s);
  }
  virtual bool PreLoad(SGObject* s)
  {
    for (DsPList<SGAccel>::Iterator i=m_chain.Begin(); i.Valid(); ++i)
      if (!i->PreLoad(s))
        return false;
    return true;
  }
  virtual bool PostLoad(SGObject* s)
  {
    for (DsPList<SGAccel>::Iterator i=m_chain.Begin(); i.Valid(); ++i)
      if (!i->PostLoad(s))
        return false;
    return true;
  }
  virtual void PostUnload(SGObject* s)
  {
    for (DsPList<SGAccel>::Iterator i=m_chain.Begin(); i.Valid(); ++i) // TODO: think: must reverse order?
      i->PostUnload(s);
  }
  virtual bool PreLoad(SGGroup* s)
  {
    for (DsPList<SGAccel>::Iterator i=m_chain.Begin(); i.Valid(); ++i)
      if (!i->PreLoad(s))
        return false;
    return true;
  }
  virtual bool PostLoad(SGGroup* s)
  {
    for (DsPList<SGAccel>::Iterator i=m_chain.Begin(); i.Valid(); ++i)
      if (!i->PostLoad(s))
        return false;
    return true;
  }
  virtual void PostUnload(SGGroup* s)
  {
    for (DsPList<SGAccel>::Iterator i=m_chain.Begin(); i.Valid(); ++i) // TODO: think: must reverse order?
      i->PostUnload(s);
  }
  virtual bool PreLoad(SGSwitch* s)
  {
    for (DsPList<SGAccel>::Iterator i=m_chain.Begin(); i.Valid(); ++i)
      if (!i->PreLoad(s))
        return false;
    return true;
  }
  virtual bool PostLoad(SGSwitch* s)
  {
    for (DsPList<SGAccel>::Iterator i=m_chain.Begin(); i.Valid(); ++i)
      if (!i->PostLoad(s))
        return false;
    return true;
  }
  virtual void PostUnload(SGSwitch* s)
  {
    for (DsPList<SGAccel>::Iterator i=m_chain.Begin(); i.Valid(); ++i) // TODO: think: must reverse order?
      i->PostUnload(s);
  }
  virtual bool PreLoad(SGScene* s)
  {
    for (DsPList<SGAccel>::Iterator i=m_chain.Begin(); i.Valid(); ++i)
      if (!i->PreLoad(s))
        return false;
    return true;
  }
  virtual bool PostLoad(SGScene* s)
  {
    for (DsPList<SGAccel>::Iterator i=m_chain.Begin(); i.Valid(); ++i)
      if (!i->PostLoad(s))
        return false;
    return true;
  }
  virtual void PostUnload(SGScene* s)
  {
    for (DsPList<SGAccel>::Iterator i=m_chain.Begin(); i.Valid(); ++i) // TODO: think: must reverse order?
      i->PostUnload(s);
  }
  virtual bool PreLoad(SGCollection* s)
  {
    for (DsPList<SGAccel>::Iterator i=m_chain.Begin(); i.Valid(); ++i)
      if (!i->PreLoad(s))
        return false;
    return true;
  }
  virtual bool PostLoad(SGCollection* s)
  {
    for (DsPList<SGAccel>::Iterator i=m_chain.Begin(); i.Valid(); ++i)
      if (!i->PostLoad(s))
        return false;
    return true;
  }
  virtual void PostUnload(SGCollection* s)
  {
    for (DsPList<SGAccel>::Iterator i=m_chain.Begin(); i.Valid(); ++i) // TODO: think: must reverse order?
      i->PostUnload(s);
  }
  virtual bool PreLoad(SGColLight* s)
  {
    for (DsPList<SGAccel>::Iterator i=m_chain.Begin(); i.Valid(); ++i)
      if (!i->PreLoad(s))
        return false;
    return true;
  }
  virtual bool PostLoad(SGColLight* s)
  {
    for (DsPList<SGAccel>::Iterator i=m_chain.Begin(); i.Valid(); ++i)
      if (!i->PostLoad(s))
        return false;
    return true;
  }
  virtual void PostUnload(SGColLight* s)
  {
    for (DsPList<SGAccel>::Iterator i=m_chain.Begin(); i.Valid(); ++i) // TODO: think: must reverse order?
      i->PostUnload(s);
  }
  virtual bool PreLoad(SGColObject* s)
  {
    for (DsPList<SGAccel>::Iterator i=m_chain.Begin(); i.Valid(); ++i)
      if (!i->PreLoad(s))
        return false;
    return true;
  }
  virtual bool PostLoad(SGColObject* s)
  {
    for (DsPList<SGAccel>::Iterator i=m_chain.Begin(); i.Valid(); ++i)
      if (!i->PostLoad(s))
        return false;
    return true;
  }
  virtual void PostUnload(SGColObject* s)
  {
    for (DsPList<SGAccel>::Iterator i=m_chain.Begin(); i.Valid(); ++i) // TODO: think: must reverse order?
      i->PostUnload(s);
  }
  virtual bool PreLoad(SGColScene* s)
  {
    for (DsPList<SGAccel>::Iterator i=m_chain.Begin(); i.Valid(); ++i)
      if (!i->PreLoad(s))
        return false;
    return true;
  }
  virtual bool PostLoad(SGColScene* s)
  {
    for (DsPList<SGAccel>::Iterator i=m_chain.Begin(); i.Valid(); ++i)
      if (!i->PostLoad(s))
        return false;
    return true;
  }
  virtual void PostUnload(SGColScene* s)
  {
    for (DsPList<SGAccel>::Iterator i=m_chain.Begin(); i.Valid(); ++i) // TODO: think: must reverse order?
      i->PostUnload(s);
  }
  virtual bool PreLoad(SGBin* s)
  {
    for (DsPList<SGAccel>::Iterator i=m_chain.Begin(); i.Valid(); ++i)
      if (!i->PreLoad(s))
        return false;
    return true;
  }
  virtual bool PostLoad(SGBin* s)
  {
    for (DsPList<SGAccel>::Iterator i=m_chain.Begin(); i.Valid(); ++i)
      if (!i->PostLoad(s))
        return false;
    return true;
  }
  virtual void PostUnload(SGBin* s)
  {
    for (DsPList<SGAccel>::Iterator i=m_chain.Begin(); i.Valid(); ++i) // TODO: think: must reverse order?
      i->PostUnload(s);
  }
};

#endif
