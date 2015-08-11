#ifndef SG_SHADOW_UPDATER_H
#define SG_SHADOW_UPDATER_H

#include <sgshadow/sgshadow.h>

class SGScene;
class SGLight;
class SGShadowMap;
class SGShadowMapper;
class SGShadowCaster;
class SGShadowListener;

class SGSHADOWAPI SGShadowUpdater
{
  SGShadowMapper   *m_mapper;
  SGScene          *m_scene;
  SGShadowListener *m_listener;
  int m_mapwidth, m_mapheight, m_maptype;
//  bool m_automonitor;

public:
  static const char* CLASSNAME () { return "ShadowUpdater"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
  SGShadowUpdater (SGShadowMapper *mapper, SGScene *scene, int mapwidth=1024, int mapheight=1024, int maptype = 0/*, bool automonitor = false*/);
  virtual ~SGShadowUpdater ();
  void SetScene (SGScene *scene);
  SGShadowMap* GetShadowMap (SGLight* light);
  SGShadowMap* GetShadowMap (SGShadowCaster* caster);
  SGShadowMapper* GetShadowMapper ();
  void Monitor (SGLight *light);
  void Monitor (SGShadowCaster* caster);
  bool StopMonitoring (SGLight *light, bool destroy = false);
  bool StopMonitoring (SGShadowCaster* caster, bool destroy = false);
  bool IsMonitored (SGLight *light);
  bool IsMonitored (SGShadowCaster* caster);
  void UpdateFlagShadowMap (SGLight *light);
  void UpdateFlagShadowMap (SGShadowCaster* caster);
  void UpdateFlagAllShadowMaps ();
};

#endif
