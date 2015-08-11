// FlexRender Strategy
// rodesp@tecgraf.puc-rio.br
// Aug 2003

#ifndef SG_FLEXRENDER
#define SG_FLEXRENDER

#include "render.h"
/**
 * FlexRender traversal strategy.
 * This strategy will traverse the scene graph using the SGRender strategy, allowing the user to enable/disable:
 * - light source loading.
 * - light source component-wise loading.
 * - state loading/unloading.
 * - background loading/unloading.
 * Useful for rendering techniques.
 */
class SG_API SGFlexRender : public SGRender
{
  bool m_load_lights;
  bool m_load_background;
  bool m_load_state;
  bool m_amb, m_dif, m_spe;
public:
  SGFlexRender ();
  virtual ~SGFlexRender ();

  void SetLoadLightComponent (bool ambient, bool diffuse, bool specular)
  {
    m_amb = ambient;
    m_dif = diffuse;
    m_spe = specular;
  }
  void SetLoadLights (bool f) { m_load_lights = f; }
  void SetLoadBackground (bool f) { m_load_background = f; }
  void SetLoadState (bool f) { m_load_state = f; }
  
  virtual void Load (SGState* s);
  virtual void Load (SGBackground* b);
  virtual void Unload (SGState* s);
  virtual void Unload (SGBackground* b);
  virtual int Load (SGScene* s);
  virtual int Load (SGColLight* l);
  virtual int Unload (SGColLight* l);
};

#endif
