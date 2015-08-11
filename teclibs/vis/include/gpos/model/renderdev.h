#ifndef RES_RENDER_DEV_H
#define RES_RENDER_DEV_H

#include "render.h"
#include <ds/array.h>
#include <lic/image.h>
#include <lic/licrender.h>
#include <gpos/render/lic/lic3render.h>

class TpvProperty;
class LicExtractor;
class LicGeom;

class LicController 
{
public:
  LicExtractor* vf_extractor;
  LicGeom* vf_geom;
  Lic::LicRender* vf_render;

  struct Lic3 {
  public:
    LicGeom * gasGeom;
    LicGeom * oilGeom;
    LicGeom * watGeom;
    LicGeom * satGeom;
    Lic3Render * render;
  } vf_lic3;

public:
  LicController ();
  virtual ~LicController ();
  double GetVectorFieldElapsedTime ();
  void SetVectorField (const char* propx, const char* propy, const char* propz);
  void SetVectorFieldTimestep (int step);
  void SetVectorFieldAnimated (bool f);
  void SetVectorFieldQuality (float i);
  void SetVectorFieldAnimSpeed (float i);
  void SetVectorFieldColorMode (int mode);
  void SetVectorFieldBackgroundColor (float r, float g, float b);
  void SetVectorFieldFixed(bool f)
  {
    m_vf_fixed = f;
  }
  bool GetVectorFieldColorModeChanged ()
  {
    if (m_vf_colorModeChanged) {
      m_vf_colorModeChanged = false;
      return true;
    }
    return false;
  }
  // Values on the Color Scale
  bool SetVectorFieldColorScale (float minVal, float maxVal);
  void GetVectorFieldColorScale (float* minVal, float* maxVal) const;
  // Absolute Min and Max values for magnitude/z value
  void SetVectorFieldColorScaleLimits (float minMag, float maxMag, float minZ, float maxZ);
  void GetVectorFieldColorScaleLimits (float* minVal, float* maxVal) const;
  Lic::Image* GetVectorFieldScaleTex (SciColorScale* cs);
  const char* GetVectorFieldPropertyX () const
  {
    return m_vf_prop_x;
  }
  const char* GetVectorFieldPropertyY () const
  {
    return m_vf_prop_y;
  }
  const char* GetVectorFieldPropertyZ () const
  {
    return m_vf_prop_z;
  }
  float GetVectorFieldLicL () const
  {
    return m_vf_L;
  }
  float GetVectorFieldLicB () const
  {
    return m_vf_B;
  }
  int GetVectorFieldColorMode () const
  {
	return m_vf_colorMode;
  }
  bool IsVectorFieldAnimated () const
  {
    return m_vf_animated;
  }
  bool IsVectorFieldFixed () const
  {
    return m_vf_fixed;
  }
  bool HasVectorFieldGeomChanged () const
  {
    return m_vf_rebuildGeom;
  }
  void SetVectorFieldGeomUpdated ()
  {
	  m_vf_rebuildGeom = false;
  }
  bool HasVectorFieldAnimChanged () const
  {
    return m_vf_animChanged;
  }
  void SetVectorFieldAnimUpdated ()
  {
    m_vf_animChanged = false;
  }
  // Sets which component (IJK = 012) represents the depth (Z)
  virtual void SetVectorFieldDepthComponent (int id);
  int GetVectorFieldDepthComponent()
  {
    return m_vf_depthComponent;
  }

protected:
  virtual bool DeleteRenderer();

protected:
  char* m_vf_prop_x;
  char* m_vf_prop_y;
  char* m_vf_prop_z;
  int m_vf_timestep;
  double m_vf_last_time;
  bool m_vf_animated;
  bool m_vf_fixed;
  int m_vf_colorMode;
  float m_vf_L;
  float m_vf_B;
  bool m_vf_rebuildGeom;
  bool m_vf_animChanged;
  float m_vf_scaleMin;
  float m_vf_scaleMax;
  float m_vf_magMin;
  float m_vf_magMax;
  float m_vf_zMin;
  float m_vf_zMax;
  bool m_vf_colorModeChanged;
  const float m_vf_minL;
  const float m_vf_maxL;
  const float m_vf_minB;
  const float m_vf_maxB;
  Lic::Image * m_vf_texImg;
  Lic::Image * m_vf_colorPalette;
  unsigned int m_vf_texId;
  int m_vf_depthComponent;
};

class RESRENDERAPI ResRenderData
{
public:
  TpvProperty* m_per_cell_property;
  TpvProperty* m_per_cell_colors;
  DsArray<float> m_properties;
  DsArray<float> m_colors;
  DsArray<bool> m_inside_range_cells;
  bool m_tpv_created;
  ResRenderData ()
  {
    m_tpv_created = false;
    m_per_cell_property = NULL;
    m_per_cell_colors = NULL;
  }
  ~ResRenderData ();
};

#endif

