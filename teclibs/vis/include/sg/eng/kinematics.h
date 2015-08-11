// kinematics class
// celes@tecgraf.puc-rio.br
// Jul 2002

#ifndef SG_KINEMATICS_H
#define SG_KINEMATICS_H

#include <sg/engine.h>
#include <alg/vector.h>

class SGEntity;

class SG_API SGKinematics : public SGEngine
{
  float m_t0;
  float m_wlen;
  AlgVector m_v;
  AlgVector m_w;
  SGEntity* m_ref;
  int m_flag;
public:
  static const char* CLASSNAME () { return "Kinematics"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
  SGKinematics (SGEntity* ref);
  virtual ~SGKinematics ();

  void SetEntity(SGEntity* ref);

  void SetLinearVelocity (float vx, float vy, float vz);
  void SetLinearVelocity (const AlgVector& v);
  void SetAngularVelocity (float wx, float wy, float wz);
  void SetAngularVelocity (const AlgVector& w);

  virtual void Start (float time);
  virtual void Apply (float time);
  virtual void Write (UtlWriter* writer);
};

#endif
