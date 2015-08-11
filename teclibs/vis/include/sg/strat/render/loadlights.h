// Load Lights Strategy
// fabraham@tecgraf.puc-rio.br
// Apr 2003

#ifndef SG_LOAD_LIGHTS
#define SG_LOAD_LIGHTS

#include <sg/strat/immediate.h>

/**
 * Load lights strategy.
 * This strategy will traverse the scene graph and will load all light sources, with
 * the right coordinate transformations.
 */
class SG_API SGLoadLights : public SGImmediate
{
  bool m_are_there_lights;
  bool m_enabled, m_ambe, m_dife, m_spee;
public:
  SGLoadLights ();
  virtual ~SGLoadLights ();

  void SetAmbientEnabled (bool f) { m_ambe = f; }
  void SetDiffuseEnabled (bool f) { m_dife = f; }
  void SetSpecularEnabled (bool f) { m_spee = f; }
  void SetEnabled (bool f) { m_enabled = f; }

  virtual int Load (SGLight* l);
  virtual int Load (SGScene* s);
  virtual int Load (SGObject *o);
  virtual int Unload (SGObject *o);
  virtual int Unload (SGLight* l);
  virtual int Unload (SGScene* s);
};

#endif
