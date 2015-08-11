// PLight class
// celes@tecgraf.puc-rio.br
// Apr 2001

#ifndef SG_PLIGHT_H
#define SG_PLIGHT_H

#include <sg/light.h>

class SG_API SGPLight : public SGLight
{
  enum {
    CONSTANT=1,
    LINEAR=2,
    QUADRATIC=4
  };
  int m_att;
  float m_kc, m_kl, m_kq;
  float m_pos[4];
public:
  static const char* CLASSNAME () { return "PLight"; }
  virtual const char* ClassName () const { return CLASSNAME(); }

  SGPLight ();
  SGPLight (float x, float y, float z);
  virtual ~SGPLight ();

  void SetPosition (float x, float y, float z);
  void SetPosition (AlgVector p);
  AlgVector GetPosition ()
  {
    return AlgVector(m_pos[0],m_pos[1],m_pos[2]);
  }
  void GetPosition (float *x, float *y, float *z)
  {
    *x = m_pos[0];
    *y = m_pos[1];
    *z = m_pos[2];
  }
  void SetConstantAttenuation (float kc);
  void SetLinearAttenuation (float kl);
  void SetQuadraticAttenuation (float kq);
  int HasConstantAttenuation ()
  {
    return m_att & CONSTANT;
  }
  int HasLinearAttenuation ()
  {
    return m_att & LINEAR;
  }
  int HasQuadraticAttenuation ()
  {
    return m_att & QUADRATIC;
  }
  float GetConstantAttenuation ()
  {
    return m_kc;
  }
  float GetLinearAttenuation ()
  {
    return m_kl;
  }
  float GetQuadraticAttenuation ()
  {
    return m_kq;
  }
  virtual void Load ();
  virtual void Write (UtlWriter* writer);
  void WriteData (UtlWriter * writer);
};

#endif
