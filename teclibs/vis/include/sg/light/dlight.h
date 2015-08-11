// DLight class
// celes@tecgraf.puc-rio.br
// Jul 2002

#ifndef SG_DLIGHT_H
#define SG_DLIGHT_H

#include <alg/vector.h>
#include <sg/light.h>

class SG_API SGDLight : public SGLight
{
  float m_dir[4];
public:
  static const char* CLASSNAME () { return "DLight"; }
  virtual const char* ClassName () const { return CLASSNAME(); }

  SGDLight ();
  SGDLight (float x, float y, float z);
  virtual ~SGDLight ();

  void SetDirection (float x, float y, float z);
  void SetDirection (AlgVector d);
  void GetDirection (float* x, float* y, float*z);
  AlgVector GetDirection ();

  virtual void Load ();
  virtual void Write (UtlWriter * writer);
  void WriteData (UtlWriter * writer);
};

#endif
