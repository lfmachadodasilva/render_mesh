// SLight class
// celes@tecgraf.puc-rio.br
// Jul 2002

#ifndef SG_SLIGHT_H
#define SG_SLIGHT_H

#include "plight.h"

class SG_API SGSLight : public SGPLight
{
  float m_dir[3];
  float m_cutoff;
  float m_expo;
public:
  static const char* CLASSNAME () { return "SLight"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
	
  SGSLight();
  SGSLight(float px, float py, float pz);
	virtual ~SGSLight ();

  void SetDirection (float x, float y, float z);
  void SetDirection (AlgVector d);
  AlgVector GetDirection ()
  {
    return AlgVector(m_dir[0],m_dir[1],m_dir[2]);
  }
  void SetCutoff (float angle);
  float GetCutoff ()
  {
    return m_cutoff;
  }
  void SetExponent (float value);
  float GetExponent ()
  {
    return m_expo;
  }
  virtual void Load ();
  virtual void Write (UtlWriter * writer);
  void WriteData (UtlWriter * writer);
};

#endif
