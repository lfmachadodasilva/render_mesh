// StateGroup class
// celes@tecgraf.puc-rio.br
// Jul 2002

#ifndef SG_STATEGROUP_H
#define SG_STATEGROUP_H

#include <sg/state.h>
#include <ds/list.h>

class SG_API SGStateGroup : public SGState
{
public:
  typedef DsPList<SGState> List;
  typedef List::Iterator ListIterator;

  static const char* CLASSNAME () { return "StateGroup"; }
  virtual const char* ClassName () const { return CLASSNAME(); }

  SGStateGroup ();
  virtual ~SGStateGroup ();

  void Insert (SGState* s);
  void Remove (SGState* s);

  ListIterator GetStateIterator() const;

  virtual void Load ();
  virtual void Unload ();
  virtual bool IsOpaque () const;
  virtual void Write (UtlWriter* writer);
private:
  List m_list; 
};

#endif
