// Selection Render Strategy
// fabraham@tecgraf.puc-rio.br
// Mar 2003

#ifndef SG_SEL_RENDER
#define SG_SEL_RENDER

#include <sg/strat/immediate.h>
#include <ds/hash.h>

/**
 * Selection Render traversal strategy.
 * This strategy will traverse the scene graph only by maintaining the correct
 * transformation matrix and rendering the objects' geometry.
 * A glLoadName((unsigned int)o) is called, so the name stored in the
 * selection buffer is the actual object pointer.
 */
class SG_API SGSelRender : public SGImmediate
{
	DsArray<SGObject*> m_list;
  DsHash<unsigned int,SGObject*> m_objtable;
  unsigned int m_nextid;
public:
  SGSelRender ();
  virtual ~SGSelRender ();
  static int GetUsedStackSize ();
	SGObject* GetObject (unsigned int id)
  {
    return m_objtable.Get(id);
  }
  virtual void Load (SGShape* s);
  virtual int Load (SGObject* o);
	virtual int Load (SGColObject* o);
  virtual int Load (SGScene* s);
  virtual int Unload (SGScene* s);
  virtual int Load (SGColScene* s);
  virtual int Unload (SGColScene* s);
};

#endif
