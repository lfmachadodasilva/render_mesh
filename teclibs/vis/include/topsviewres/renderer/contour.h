// Iso-contour renderer
// fabraham@tecgraf.puc-rio.br
// Feb 2008
#ifndef TPVRES_CONTOUR_RENDERER_H
#define TPVRES_CONTOUR_RENDERER_H

#include <topsviewres/defines.h>
#include <topsviewres/geometry/bdryfacesopaque.h>
#include <topsview/renderer/contour.h>

class TPVRES_API TpvResContourRenderer : public TpvContourRenderer
{
public: 
  TpvResContourRenderer ();
  virtual ~TpvResContourRenderer ();

  /**
   * Enables/disables wireframe mode.
   */
  void SetWireframe (bool flag);
  /**
   * Returns whether wireframe mode is on.
   */
  bool GetWireframe () const;
  /**
   * Enables/disables wireframe mode for a given geomset type.
   */
  void SetWireframe (TpvResBdryFacesOpaqueGeometry::GeomSetType type, 
                     bool flag);
  /**
   * Returns whether wireframe mode is on for a given geomset type.
   */
  bool GetWireframe (TpvResBdryFacesOpaqueGeometry::GeomSetType type) const;

  /**
   * Enables grid lines drawing.
   */
  void SetGridLinesEnabled (bool flag);
  /**
   * Returns whether grid lines drawing is enabled.
   */
  bool GetGridLinesEnabled () const;
  /**
   * Enables grid lines drawing for a given geomset type.
   */
  void SetGridLinesEnabled (TpvResBdryFacesOpaqueGeometry::GeomSetType type, 
                         bool flag);
  /**
   * Returns whether grid lines drawing is enabled for a given geomset type.
   */
  bool 
  GetGridLinesEnabled (TpvResBdryFacesOpaqueGeometry::GeomSetType type) const;

  /**
   * Specifies a color to be used as material color (diffuse component).
   * Ideally, when the reservoir is rendered with a color scale,
   * this is set to the default value (1, 1, 1, 1 (white)).
   */
  void SetLightingColor (float r, float g, float b, float a=1.0f)
  {
    m_color[0] = r;
    m_color[1] = g;
    m_color[2] = b;
    m_color[3] = a;
  }
  /**
   * Reverts to the default lighting color (white).
   */
  void SetDefaultLightingColor ()
  {
    SetLightingColor(1.0f,1.0f,1.0f,1.0f);
  }
protected:
  virtual void RenderBegin ();
  virtual void RenderEnd ();
private:
  float m_color[4];
  bool* m_wireframe_per_type;
  bool* m_draw_grid_per_type;
};

#endif

