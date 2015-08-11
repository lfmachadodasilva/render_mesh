// Material sorting collector (abstract class)

#ifndef SG_ABSTRACT_MATSORT_H
#define SG_ABSTRACT_MATSORT_H

#include <ds/stack.h>
#include <sg/strat/collector.h>
#include <sg/colscene.h>

class SGState;
class SGBin;
class SGObject;
class SGColObject;
class SGColScene;
class SGScene;

class SG_API SGAbstractMatSort : public SGCollector
{
public:
  typedef DsStack<SGState*> StateStack;
  typedef DsStack<SGBin*>   BinStack;
  SGAbstractMatSort();
  virtual ~SGAbstractMatSort();
  // collector methods
  virtual void Collect (SGScene* s);
  virtual void Collect (SGNode* n);
  virtual SGCollection* GetResult () {return m_result;}
  virtual SGColScene* GetColScene () {return m_result;}
  virtual void Release ();
  // strategy methods
  virtual void Load   (SGState* s);
  virtual void Unload (SGState* s);
  virtual int  Load   (SGLight* l);
  virtual int  Load   (SGObject* o);
  virtual int  Unload (SGObject* o);
  virtual void Load   (SGShape* s);
protected:
  virtual void CreateBins   (SGColScene* s) = 0;
  virtual void PushBin      (BinStack &bs, int slot, SGState* state);
  virtual void PopBins      () = 0;
  virtual void PushBins     (int slot, SGState* state) = 0;
  virtual void InsertObject (int slot, SGColObject* obj, SGState* state) = 0;
  StateStack*  GetStateStack(void) {return &m_statestack;}
  SGObject*    GetCurrObject(void) {return m_curr_obj;}
  int          GetStackBase (void) {return m_base;}
private:
  StateStack  m_statestack;
  SGColScene* m_result;
  SGObject*   m_curr_obj;
  int  m_base;
  bool m_first_shp;
};

#endif

