#ifndef SG_SHADOWMAP_H
#define SG_SHADOWMAP_H

//------------------//
// Shadow Map Types //
//------------------//

#define SG_SHADOWMAP_NOSHADER  0   // Simple shadowmap using standard OpenGL functionality
#define SG_SHADOWMAP_SIMPLE    1   // Simple shadowmap using minimal shaders for improved speed and correctness
#define SG_SHADOWMAP_PCF       2   // Shadowmap with Percentage-Closer Filtering 
#define SG_SHADOWMAP_JITTER    3   // Shadowmap with Jittered PCF Grid for improved border smoothness and antialiasing
#define SG_SHADOWMAP_VARIANCE  4   // Variance Shadowmap (VSM), recommended for static light and scene (specially directional sunlight)
#define SG_SHADOWMAP_NUMTYPES  5

#define SG_SHADOWMAP_NOWARP              0 // No Warp
#define SG_SHADOWMAP_FIT_WORLD_ALIGNED   1 // Fit the map to  a bounding volume, but keep it aligned
#define SG_SHADOWMAP_FIT_VIEW_ALIGNED    2 // Fit the map to the viewing volume, allowing rotation
#define SG_SHADOWMAP_FIT_WORLD_ORIENTED  3 // Fit the map to  a bounding volume, but keep it aligned
#define SG_SHADOWMAP_FIT_VIEW_ORIENTED   4 // Fit the map to the viewing volume, allowing rotation
#define SG_SHADOWMAP_WARP_INF            5 // Apply TSM warp with n' = infinity
#define SG_SHADOWMAP_WARP_TSM            6 // Apply TSM warp with n' = n'[TSM]
#define SG_SHADOWMAP_WARP_PSM            7 // Apply TSM warp with n' = n'[PSM]      = n
#define SG_SHADOWMAP_WARP_LISPSM         8 // Apply TSM warp with n' = n'[LISPSM]   = n + sqrt(n*f)
#define SG_SHADOWMAP_WARP_GLISPSM        9 // Apply TSM warp with n' = n'[GLISMSPM]

//-----------------------------------//
// Includes and Forward Declarations //
//-----------------------------------//

#include <sgshadow/sgshadow.h>
#include <shadowmap/shadowmapinterface.h>
#include <alg/vector.h>
#include <alg/matrix.h>

class SGShadowMapper;
class SGShadowCaster;
class SGShadowMapUpdateCamera;
class SGShadowMapUpdateRenderer;
class SGShadowMapUpdateCollector;
class SGScene;
class SGLight;

//-------------------//
// Class Declaration //
//-------------------//

class SGSHADOWAPI SGShadowMap
{
public:

  // Constructors and Destructor

  SGShadowMap (SGLight* light);
  SGShadowMap (SGShadowCaster* caster);

  virtual ~SGShadowMap ();

  // Initialization and CleanUp

  bool Init (unsigned int width = 1024, unsigned int height = 1024);
  void CleanUp ();

  // Configuration Setters and Getters

  void  SetAllowShaders       (bool state);
  void  SetClipTexture        (bool state);
  void  SetLitBorders         (bool state);
  void  SetCulling            (bool state);
  void  SetCullFrontFace      (bool state);
  void  SetPolyOffset         (bool state);
  void  SetPolyOffset         (float factor, float units);
  void  SetFragOffset         (float offset);
  void  SetFragOffset         (float minBias, float maxBias);
  void  SetGaussBlurSize      (int size);
  void  SetDualDepth          (bool state);
  void  SetDualDepthClamp     (bool state);
  void  SetPCF                (bool state);
  void  SetPCFJitter          (bool state);
  void  SetPCFCircular        (bool state);
  void  SetPCFTexelSpace      (bool state);
  void  SetPCFCamMultiSample  (bool state);
  void  SetPCFCamAlignSample  (bool state);
  void  SetPCFAdaptive        (bool state);
  void  SetPCFKernelScale     (float scale);
  void  SetPCFKernelSize      (int size);
  void  SetPCFJitterSize      (int size);
  void  SetTSMFocusDistance   (float value);
  void  SetTSMFocusZDistance  (float value);
  void  SetTSMFocusPercentage (float value);
  void  SetPartitionZ         (bool state);
  void  SetForceKeepZ         (bool state);
  void  SetShadowMapWarp      (int warpType);
  void  SetVarianceMap        (bool state);
  void  SetVarianceBias       (float value);
  void  SetVarianceGround     (float value);
  void  SetFakeAttenuation    (float value);
  void  SetFakeShadowColor    (float r, float g, float b);

  int   GetWidth              (void);
  int   GetHeight             (void);
  bool  GetAllowShaders       (void);
  bool  GetClipTexture        (void);
  bool  GetLitBorders         (void);
  bool  GetCulling            (void);
  bool  GetCullFrontFace      (void);
  bool  GetPolyOffset         (void);
  void  GetPolyOffset         (float &factor, float &units);
  float GetFragOffset         (void);
  void  GetFragOffset         (float &minBias, float &maxBias);
  int   GetGaussBlurSize      (void);
  bool  GetDualDepth          (void);
  bool  GetDualDepthClamp     (void);
  bool  GetPCF                (void);
  bool  GetPCFJitter          (void);
  bool  GetPCFCircular        (void);
  bool  GetPCFTexKernel       (void);
  bool  GetPCFTexelSpace      (void);
  bool  GetPCFCamMultiSample  (void);
  bool  GetPCFCamAlignSample  (void);
  bool  GetPCFAdaptive        (void);
  float GetPCFKernelScale     (void);
  int   GetPCFKernelSize      (void);
  int   GetPCFJitterSize      (void);
  float GetTSMFocusDistance   (void);
  float GetTSMFocusZDistance  (void);
  float GetTSMFocusPercentage (void);
  bool	GetPartitionZ         (void);
  bool  GetForceKeepZ         (void);
  int   GetShadowMapWarp      (void);
  bool  GetViewDependant      (void);
  bool  GetVarianceMap        (void);
  float GetVarianceBias       (void);
  float GetVarianceGround     (void);
  float GetFakeAttenuation    (void);
  void  GetFakeShadowColor    (float &r, float &g, float &b);

  // Setters for overriding default light parameters (see "override values" below)

  void    SetLightDirection (float x, float y, float z) {m_dir = AlgVector(x,y,z); m_overrideDir      = true;}
  void    SetLightPosition  (float x, float y, float z) {m_pos = AlgVector(x,y,z); m_overridePos      = true;}
  void    SetLightFovy      (float fovy)                {m_fovy = fovy;            m_overrideFovy     = true;}
  void    SetLightProjSize  (float projsize)            {m_projsize = projsize;    m_overrideProjsize = true;}

  // Enabling, Disabling and Flagging for Update

  bool    IsEnabled          (void) {return m_enabled;}
  bool    IsFlaggedForUpdate (void) {return m_needUpdate;}

  void    SetEnabled    (bool state) {m_enabled = state;}
  void    Enable        (void)       {m_enabled = true;}
  void    Disable       (void)       {m_enabled = false;}

  void    FlagForUpdate (void)       {m_needUpdate = true;}

  // Shadow Texture update functions

  virtual void Update (SGScene* scene, SGShadowMapper *mapper);

  // Shadow Map View Functions

  void    DrawShadowMapTexture (SGShadowMapper *mapper, float left = -1.0f, float bottom = -1.0f, float right = 1.0f, float top = 1.0f, int option = 0);
  void    DrawLightFrustum     (void);

  // Internal Communication Functions

  smMap    GetMapID() {return m_mapID;} // Identification on the SM Library
  SGLight* GetLight() {return m_light;} // This shadowmap's light

protected:

  // Internal Auxiliary Functions

  AlgVector RotateVector (const AlgVector& vec, const AlgMatrix& rot);

  void ChooseClipTexture (void);

  // Associated light and shadow map ID

  SGLight        *m_light;
  SGShadowCaster *m_caster;

  bool m_hasFakeCaster;

  smMap m_mapID;

  SGShadowMapUpdateCollector *m_shadowupdatecollector;
  SGShadowMapUpdateRenderer  *m_shadowupdaterenderer;
  SGShadowMapUpdateCamera    *m_shadowupdatecamera;

  // Enabled State and Update Flag

  bool      m_enabled;
  bool      m_needUpdate;

  // Override values

  AlgVector m_dir;          // For point lights only, default = targeting sceneCenter
  float     m_fovy;         // For point lights only, default = 90 degrees
  AlgVector m_pos;          // For directional lights only, default = sceneCenter
  float     m_projsize;     // For directional lights only, default = 2*sceneRadius

  bool      m_overrideDir;
  bool      m_overrideFovy;
  bool      m_overridePos;
  bool      m_overrideProjsize;
};

#endif
