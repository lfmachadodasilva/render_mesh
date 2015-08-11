// Point vector renderer
// rodesp@tecgraf.puc-rio.br
// Mar 2011

#ifndef TPV_SCI_POINT_VECTOR_RENDERER_H
#define TPV_SCI_POINT_VECTOR_RENDERER_H

#include <alg/vector.h>
#include <particles/vectorset.h>
#include <topsview/defines.h>
#include <topsview/renderer/renderer.h>

class PtcVectorRenderer;
class TpvGeometry;
class TpvPointSet;
class TpvPtcVectorPointSet;
class UGLTexture;

class TPV_API TpvSciPointVectorRenderer : public TpvRenderer
{
public: 
  TpvSciPointVectorRenderer ();
  
  virtual ~TpvSciPointVectorRenderer ();

  void SetGeometry (TpvGeometry* g);

  void SetGeometryChanged ();

  /**
   * Configures the use of geometry field.
   */
  void SetFieldEnabled (bool flag)
  {
    m_field_enabled = flag;
  }

  /**
   * Initialized this renderer.
   * Returns true if ok or false otherwise.
   */
  bool Init ();

  /**
   * Sets the texture used to map vector magnitudes onto colors.
   * The texture object is assumed to have a propert texture matrix set.
   * It must correctly map vector magnitudes onto the texture coordinate 
   * interval: [0, 1].
   */
  void SetColorScaleTexture (UGLTexture* texture);

  /**
   * Sets whether displayed vectors sizes will be normalized so that
   * each vector has unitary length.
   * Default: false
   */
  void SetNormalizeVectorSizesEnabled (bool enabled);

  /**
    Sets the scale applied to displayed vector sizes.
    Default: 1.0
  */
  void SetVectorSizeScale (float scale);

  /**
   * Sets the vector line width.
   */
  void SetVectorLineWidth (float width);

  /**
   * Sets the current camera position and direction.
   *
   * The parameters set by this method may be replaced when 
   * automatic determination of view parameters is enabled 
   * (see SetAutoUpdateViewParameters()).
   */
  void SetCamera (const AlgVector & position, const AlgVector & direction);

  /**
   * Sets the current camera field of view.
   *
   * The parameter set by this method may be replaced when 
   * automatic determination of view parameters is enabled 
   * (see SetAutoUpdateViewParameters()).
   */
  void SetFOV (float fov);

  /**
   * Sets whether camera view parameters (position, direction and fov) will be
   * automatically updated from the current OpenGL state.
   *
   * If enabled, the parameters set by SetCamera() and SetFOV() methods are
   * replaced by the automatic parameters computed.
   *
   * Default: true
   */
  void SetAutoUpdateViewParameters (bool enabled);

  void SetOrthoEnabled (bool enabled);

  void SetViewport (int width, int height);

  /**
   * Sets wheter volumetric rendering mode is enabled.
   * Default: false
   */
  void SetVolumetricEnabled (bool enabled);

  /**
   * Sets whether transparent rendering for points is enabled.
   * If transparency is not enabled, the alpha component of the 
   * colorscale is ignored.
   * Disabling transparency improves rendering speed, since
   * transparent points must be visibility sorted before rendering.
   * Default: true
   */
  void SetTransparencyEnabled (bool enabled);

private:
  class VectorSet : public PtcVectorSet
  {
  public:
    VectorSet ();

    virtual ~VectorSet ();

    void SetTpvPointSet (TpvPointSet* pointset);

    virtual void AddChangeListener (PtcVectorSetChangeListener* listener);

    virtual void RemoveChangeListener (PtcVectorSetChangeListener* listener);

    virtual unsigned int GetPointCount ();

    virtual int GetDimension ();

    virtual const float* GetPositions ();

    virtual const float* GetVectorField ();

    virtual void GetVectorFieldMagnitudeLimits (float* mag_min, float* mag_max);

    virtual UGLTexture* GetMaterialTexture ();

    void SetColorScaleTexture (UGLTexture* texture);

  private:
    TpvPointSet* m_pointset;
    UGLTexture* m_colorscale_texture;
  };

private:
  /**
   * Is geometry field enabled?
   */
  bool IsFieldEnabled () const
  {
    return m_field_enabled;
  }

  virtual void RenderBegin ();
  virtual void RenderEnd ();
  virtual void DoRender ();
  virtual void DoRenderSelection ();

  bool InitRenderer ();
  void Update ();
  void UpdateRenderer ();
  void UpdateCurrentRenderer ();
  void UpdateCamera ();
  void PrepareSetForRender (TpvPointSet* set);
  bool IsCameraPositionChanging (const AlgVector& new_position) const;
  bool IsCameraDirectionChanging (const AlgVector& new_direction) const;
  bool IsCameraFovChanging (float new_fov) const;

private:
  TpvGeometry* m_geometry;
  VectorSet* m_ptc_pointset;
  UGLTexture* m_colorscale_texture;
  PtcVectorRenderer* m_renderer;

  AlgVector m_camera_pos;
  AlgVector m_camera_dir;
  float m_camera_fov;
  bool m_camera_ortho_enabled;
  int m_camera_viewport_w;
  int m_camera_viewport_h;
  bool m_field_enabled;
  bool m_transparency_enabled;
  bool m_auto_update_view;
  bool m_update_camera;
  bool m_update_renderer;
  bool m_initialized;
  bool m_renderer_initialized;
};

#endif
