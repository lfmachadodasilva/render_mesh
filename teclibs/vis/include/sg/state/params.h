// State Parameters class
// fabraham@tecgraf.puc-rio.br
// Oct 2004

#ifndef SG_STATE_PARAMS_H
#define SG_STATE_PARAMS_H

#include <sg/state.h>
#include <ds/hash.h>
#include <ds/list.h>

class SG_API SGStateParams : public SGState
{
  DsHash<GLenum,bool> m_enables;
  DsList<GLenum> m_enablelist;
  bool m_pop;
  void SetEnable (GLenum e, bool f);
public:
  static const char* CLASSNAME () { return "StateParams"; }
  virtual const char* ClassName () const { return CLASSNAME(); }

  SGStateParams ();
  virtual ~SGStateParams ();

  void SetColorMaterial (bool f);

  virtual void Load ();
  virtual void Unload ();
  virtual bool IsOpaque () const;
  virtual void Write (UtlWriter* writer);
};

#endif
