#ifndef RES_RENDER_3D_DEV_H
#define RES_RENDER_3D_DEV_H

#include <ds/array.h>
#include <topsviewres/geometry/tetrageometry.h>
#include <topsview/property/property.h>
#include <topsview/geometry/bdryedges2.h>
#include <topsview/renderer/harcvolrenderer3.h>
#include <topsview/geometry/edgetoline.h>
#include <topsview/renderer/polywireframe3.h>
#include <gpos/model/renderdev.h>
#include <gpos/render3d/lic/slicextractor.h>
#include <gpos/render3d/lic/slicgeom.h>
#include <lic/licrender.h>
#if (defined WIN32 && defined RES_ENABLE_CUDA_VV)
# include <cudarc/cudarc.h>
#endif

class TpvColorScale;
class TpvResBdryFacesSimpleGeometry;
class TpvResBdryFacesSepGeometry;
class TpvResBdryFacesSectionGeometry;
class TpvResBdryFacesSubGridGeometry;
class TpvResTranspGeometry;
class TpvResTranspSepGeometry;
class TpvResTranspSectionGeometry;
class TpvResCutSimpleGeometry;
class TpvResCutSepGeometry;
class TpvResSecGeometry;
class TpvResTransparency;
class TpvResContourSimpleRenderer;
class TpvResContourSepRenderer;
class TpvResContourTranspRenderer;
class TpvResContourTranspSepRenderer;
class TpvResContourCutSimpleRenderer;
class TpvResContourCutSepRenderer;
class TpvProperty;
class TpvVflVectorIntegrator;
class TpvVflAdvector;
class TpvVflVectorField;
class VflFieldLineRenderer;
class VflFieldLineList;

class SLicController : public LicController 
{
public:
  SLicController();
  virtual ~SLicController();

  SLicExtractor * GetExtractor() { return static_cast<SLicExtractor*> (vf_extractor); }
  SLicGeom * GetGeometry() { return static_cast<SLicGeom*> (vf_geom); }

  Image * Get2DPallete() { return m_palette; }

protected:
  virtual bool DeleteRenderer();

private:
  Image * m_palette;

};

class Res3DRenderData : public ResRenderData
{
public:
  TpvResBdryFacesSimpleGeometry *m_geometry;
  TpvResBdryFacesSepGeometry *m_geometrysep;
  TpvResBdryFacesSectionGeometry *m_geometrysec;
  TpvResBdryFacesSubGridGeometry* m_geometrysubgrid;
  TpvResTranspGeometry *m_geometrytransp;
  TpvResTranspSepGeometry *m_geometrytranspsep;
  TpvResTranspSectionGeometry *m_geometrytranspsec;
  TpvResCutSimpleGeometry *m_geometrycut;
  TpvResCutSepGeometry *m_geometrycut_sep;
  TpvResContourSimpleRenderer *m_renderer;
  TpvResContourSepRenderer *m_renderersep;
  TpvResContourTranspRenderer *m_renderertransp;
  TpvResContourTranspSepRenderer *m_renderertranspsep;
  TpvResContourCutSimpleRenderer *m_renderercut;
  TpvResContourCutSepRenderer *m_renderercut_sep;

  TpvProperty* m_vv_prop;
  TpvColorScale* m_vv_colorscale;
  TpvResTetraGeometry* m_vv_geom;
  TpvHARCVolRenderer3<TpvResGeometryModel>* m_vv_rnd;
#if (defined WIN32 && defined RES_ENABLE_CUDA_VV)
  CudaRC* m_vv_cuda_rnd;
#endif
  TpvBdryEdgesGeometry2<TpvResGeometryModel>* m_vv_bdry_edges_geom;
  TpvEdgeToLineGeometry<TpvResGeometryModel>* m_vv_bdry_lines_geom;
  TpvPolyWireframeRenderer3<TpvResGeometryModel>* m_vv_grid_rnd;
  bool m_vv_tpv_created;

  SLicController m_vf_control;

  TpvVflVectorIntegrator* m_fieldline_integrator;
  TpvVflAdvector* m_fieldline_advector;
  TpvVflVectorField *m_fieldline_field;
  VflFieldLineRenderer* m_fieldline_renderer;
  TpvColorScale* m_fieldline_colorscale;
  VflFieldLineList*** m_fieldline_list; // ptr: [well][timestep]
  int m_fieldline_curproperty;
  DsArray<int> m_fieldline_curwells;
  DsArray<int> m_fieldline_backupwells;
  float m_fieldline_minValue;
  float m_fieldline_maxValue;
//int m_fieldline_curstep;

  Res3DRenderData (ResModelNew *mdl)
  : m_mdl(mdl)
  {
    m_geometry = NULL;
    m_geometrysep = NULL;
    m_geometrysec = NULL;
    m_geometrysubgrid = NULL;
    m_geometrycut = NULL;
    m_geometrycut_sep = NULL;
    m_geometrytransp = NULL;
    m_geometrytranspsep = NULL;
    m_geometrytranspsec = NULL;
    m_renderer = NULL;
    m_renderersep = NULL;
    m_renderercut = NULL;
    m_renderercut_sep = NULL;
    m_renderertransp = NULL;
    m_renderertranspsep = NULL;

    m_vv_tpv_created = false;
    m_vv_prop = 0;
    m_vv_colorscale = 0;
    m_vv_geom = 0;
    m_vv_rnd = 0;
#if (defined WIN32 && defined RES_ENABLE_CUDA_VV)
    m_vv_cuda_rnd = NULL;
#endif
    m_vv_bdry_edges_geom = 0;
    m_vv_bdry_lines_geom = 0;
    m_vv_grid_rnd = 0;

    m_fieldline_integrator = 0;
    m_fieldline_advector = 0;
    m_fieldline_field = 0;
    m_fieldline_renderer = 0;
    m_fieldline_colorscale = 0;
    //for (int i = 0; i < 12; ++i) m_fieldline_list[i] = 0;
    m_fieldline_list = 0;
    m_fieldline_curproperty = -1;
    //m_fieldline_curstep = -1;
    m_fieldline_minValue = 0.0f;
    m_fieldline_maxValue = 1.0f;
  }
  ~Res3DRenderData();
  void ClearFieldLineData();
private:
  ResModelNew* m_mdl;
};

#endif

