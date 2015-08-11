// ShpSwitcher class
// djavanes@tecgraf.puc-rio.br
// Ago 2004

#ifndef SG_SHPSWITCHER_H
#define SG_SHPSWITCHER_H

#include <sg/engine.h>
#include <ds/list.h>
#include <sg/shape.h>
#include <sg/utils.h>

class SGObject;

class SG_API SGShpSwitcher : public SGEngine
{
protected:
  typedef DsPList<SGShape> List;
  List m_list;
  List::Iterator m_listi;
  
  float m_t0;
  float m_tt;
  int m_it;
  
  SGObject* m_ref;
  SGShape* dest_shape;
public:
  static const char* CLASSNAME () { return "ShpSwitcher"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
  SGShpSwitcher (SGObject* ref);
  virtual ~SGShpSwitcher ();

  void SetTransitionTime (float transtime);
  void SetInterpolateType (int i_type);
  void AddShape (SGShape* shape);

  virtual void Start (float time);
  virtual void Apply (float time);
  virtual void Write (UtlWriter* writer);
};

#endif
