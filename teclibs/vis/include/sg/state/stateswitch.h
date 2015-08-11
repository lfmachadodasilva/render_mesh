// StateSwitch class
// celes@tecgraf.puc-rio.br
// Jul 2002

#ifndef SG_STATESWITCH
#define SG_STATESWITCH

#include <sg/state.h>

class SG_API SGStateSwitch : public SGState
{
  int m_active;
  int m_nstates;
  SGState** m_vstates;
public:
  static const char* CLASSNAME () { return "StateSwitch"; }
  virtual const char* ClassName () const { return CLASSNAME(); }

  SGStateSwitch (int nstates);
  virtual ~SGStateSwitch ();

  int AttribState (int id, SGState* s);

  void SetActive (int id);

  SGState* GetActiveState () const { return m_vstates[m_active]; }
  int GetActive () const { return m_active; }
  int GetDimension () const { return m_nstates; }

  virtual void Load ();
  virtual void Unload ();
  virtual bool IsOpaque () const;
  virtual void Write (UtlWriter* writer);
};

#endif
