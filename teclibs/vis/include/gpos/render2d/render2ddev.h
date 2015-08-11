#ifndef RES_RENDER_MAPSEC_DEV_H
#define RES_RENDER_MAPSEC_DEV_H

#include <gpos/model/renderdev.h>
#include <topsview/property/property.h>
#include <ds/array.h>

class TpvResMapSecGeometry;
class TpvResContourMapSecRenderer;
class ResModel;
class Lic3Render;

class Lic2DController : public LicController 
{
public:
  Lic2DController();
  virtual ~Lic2DController();
  virtual void SetVectorFieldDepthComponent (int id);
  void SetYAxisInverted(bool inverted);
  bool IsYAxisInverted () const
  {
    return m_vf_yInverted;
  }

protected:
  bool m_vf_yInverted;
};


class ResMapSecRenderData : public ResRenderData
{
public:
  TpvResMapSecGeometry *m_geometry;
  TpvResContourMapSecRenderer *m_renderer;
  Lic2DController m_vf_control;
  DsArray<bool> m_visible_cells;
  DsArray<float> m_flow_colors;
public:
  ResMapSecRenderData (ResModelNew *mdl);
  ~ResMapSecRenderData();
};

#endif

