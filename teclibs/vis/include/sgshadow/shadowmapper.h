#ifndef SG_SHADOWMAPPER_H
#define SG_SHADOWMAPPER_H

//-----------------------------------//
// Includes and Forward Declarations //
//-----------------------------------//

#include <sgshadow/sgshadow.h>
#include <sg/strat/render/render.h>
#include <shadowmap/shadowmapinterface.h>

class SGShadowMapFakeCollector;
class SGFlexRender;
class SGAbstractMatSort;
class SGTranspMatSort;
class SGShadowMap;
class SGColScene;
class SGObject;
class SGGroup;

//-----------------------------------//
// Shadow Map Casting Enable/Disable //
//-----------------------------------//

// Default state = Enabled
// Disabling a group makes every object not cast shadows
// Enabling a group makes each object be checked individually

SGSHADOWAPI void DisableShadowCasting (SGObject *o);
SGSHADOWAPI void DisableShadowCasting (SGGroup  *g);
SGSHADOWAPI void DisableShadowCasting (SGScene  *s);
SGSHADOWAPI void EnableShadowCasting  (SGObject *o);
SGSHADOWAPI void EnableShadowCasting  (SGGroup  *g);
SGSHADOWAPI void EnableShadowCasting  (SGScene  *s);
SGSHADOWAPI bool IsShadowCaster       (SGObject *o);
SGSHADOWAPI bool IsShadowCaster       (SGGroup  *g);
SGSHADOWAPI bool IsShadowCaster       (SGScene  *s);

//-------------------------------------//
// Fake Shadow Receiver Enable/Disable //
//-------------------------------------//

// Default state = Disabled
// Enabling a group makes every object a receiver
// Disabling a group makes each object be checked individually

SGSHADOWAPI void DisableFakeShadowReceiver (SGObject *o);
SGSHADOWAPI void DisableFakeShadowReceiver (SGGroup  *g);
SGSHADOWAPI void DisableFakeShadowReceiver (SGScene  *s);
SGSHADOWAPI void EnableFakeShadowReceiver  (SGObject *o);
SGSHADOWAPI void EnableFakeShadowReceiver  (SGGroup  *g);
SGSHADOWAPI void EnableFakeShadowReceiver  (SGScene  *s);
SGSHADOWAPI bool IsFakeShadowReceiver      (SGObject *o);
SGSHADOWAPI bool IsFakeShadowReceiver      (SGGroup  *g);
SGSHADOWAPI bool IsFakeShadowReceiver      (SGScene  *s);

//-------------------//
// Class Declaration //
//-------------------//

class SGSHADOWAPI SGShadowMapper : public SGRender
{
public:

  // Constructors and Destructor

  SGShadowMapper ();
  SGShadowMapper (SGFlexRender* renderer, SGTranspMatSort* collector);

  virtual ~SGShadowMapper (void);

  // Initialization and CleanUp

  bool Init ();
  void CleanUp ();

  // Setters and Getters

  void    SetUseCombiner  (bool state);
  void    SetFakeShadows  (bool state);
  void    SetFake4Mode    (bool state);
  bool    SetWindowSize   (unsigned int width, unsigned int height);
  void    FlagSceneUpdate (void);
  
  void    SetTextureUnitColor  (unsigned int unit);
  void    SetTextureUnitShadow (unsigned int unit);
  void    SetTextureUnitClip   (unsigned int unit);
  void    SetTextureUnitJitter (unsigned int unit);

  void    SetWorldBBox (unsigned int vertexCount, float* vertices);
  void    SetUpdateSceneRoot (SGNode *node);
  SGNode* GetUpdateSceneRoot (void);

  bool    GetFakeShadows (void);
  bool    GetFake4Mode   (void);

  // Managing Shadow Maps

  void    AddShadowMap        (SGShadowMap* shadowmap);
  void    RemoveShadowMap     (SGShadowMap* shadowmap);
  bool    HasShadowMap        (SGShadowMap* shadowmap);

  void    UpdateShadowMap     (SGScene* scene, SGShadowMap* shadowmap);
  void    UpdateAllShadowMaps (SGScene* scene);

  void    FlagAllShadowMaps ();
  void    UpdateFlaggedShadowMaps (SGScene* scene);

  // Shadow Map View Functions

  void    UpdateAndDrawShadowMapTexture (SGLight*     light,     SGScene* scene, float left = -1.0f, float bottom = -1.0f, float right = 1.0f, float top = 1.0f, int option = 0);
  void    UpdateAndDrawShadowMapTexture (SGShadowMap* shadowmap, SGScene* scene, float left = -1.0f, float bottom = -1.0f, float right = 1.0f, float top = 1.0f, int option = 0);

  // Internal Communication Functions

  smMapper     GetMapperID  (void);             // Identification on the SM Library
  SGShadowMap* GetShadowMap (SGLight*  light);  // Getting a given light's shadowmap
  virtual void SetCamera    (SGCamera* camera); // Setting the camera

  // Overloaded "load" strategy functions

  virtual int Load (SGScene*    scene);

  // Enable debugging options

  void  SetDebugMode (int mode);

protected:

  // Rendering the scene

  virtual void Render            (SGScene* scene);
  virtual void RenderAmbientPass (bool isTransparentPass);
  virtual void RenderLightPasses (bool isTransparentPass);

private:

  // Associated shadow mapper ID

  smMapper m_mapperID;

  // Option to use the ShadowMap Combiner
  // (must be used unless shadowmaps are all of type NOSHADER, in which case it must not be used)

  bool m_useCombiner;

  // Hash map to find the shadow map for a given light

  DsHash<SGLight*,SGShadowMap*> m_shadowmaps;

  // Scene root used for Shadow Map update (and world bounding box calculation)

  SGNode *m_updateSceneRoot;

  // SGStrategies to collect lights and render the scene on each pass 

  bool m_transparency;
  bool m_ownrenderer;
  bool m_owncollector;

  int m_debugmode;

  SGFlexRender* m_renderer;
  SGAbstractMatSort* m_scenecollector;
  SGShadowMapFakeCollector* m_fakeCollector;

  SGColScene* m_collectedScene;
  SGColScene* m_collectedFakeScene;
};

#endif
