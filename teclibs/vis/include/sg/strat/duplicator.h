// Hierarchy duplicator
// fabraham@tecgraf.puc-rio.br
// Mar 2003

#ifndef SG_DUPLICATOR
#define SG_DUPLICATOR

#include <sg/strategy.h>
#include <ds/stack.h>

class SGNodeList;

class SG_API SGDuplicator : public SGStrategy
{
  DsStack<SGNodeList*> m_nodeliststack;
  DsStack<SGSpace*> m_realpointerstack;
  SGNode *m_result;
  SGObject *m_object;
  void CopyItem (SGItem *dst, SGItem *src);
  void CopyLight (SGLight *dst, SGLight *src);
  void CopySpace (SGSpace *dst, SGSpace *src);
  void CopyEntity (SGEntity *dst, SGEntity *src);
  void CopyScene (SGScene *dst, SGScene *src);
  void AttachNode (SGNode *n);
public:
  SGDuplicator ();
  virtual ~SGDuplicator ();

  SGNode* Duplicate (SGNode* node);

  virtual void Load  (SGShape* s);
  virtual int Unload (SGNode *n);
  virtual int Load   (SGLight* l);
  virtual int Unload (SGLight* l);
  virtual int Load   (SGSpace* s);
  virtual int Load   (SGScene* s);
  virtual int Load   (SGGroup* g);
  virtual int Load   (SGObject *o);
  virtual int Unload (SGObject *o);
//  virtual int Load   (SGSwitch *s);
};

#endif
