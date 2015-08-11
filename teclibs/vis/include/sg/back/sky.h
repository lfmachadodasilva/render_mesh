// Sky.h
// djavanes@tecgraf.puc-rio.br
// Jul 2002

#ifndef SG_SKY_H
#define SG_SKY_H

#include <sg/background.h>
#include <sg/lua/sgsky.h>

class SkyEnvironment;

class SGSKYAPI SGSky : public SGBackground 
{
  bool  m_factory_type_defined;
  int   m_factory_type;
  float m_factory_radius;
  SkyEnvironment * m_env;
  static char* s_path;
public:
  static const char* CLASSNAME () { return "Sky"; }
  virtual const char* ClassName () const { return CLASSNAME(); }

  static void SetTexturesPath (const char* path);
  static void ResetTexturesPath();  

  SGSky (SkyEnvironment* env);
  SGSky (SkyEnvironment* env, int factory_type, float radius=0.0f);
  virtual ~SGSky ();

  SkyEnvironment * GetEnvironment ()
  {
    return m_env;
  }
  void UpdateVtime (double time);

  virtual void BeginRender ();
  virtual void EndRender ();
  virtual void Write (UtlWriter * writer);
};

#endif
