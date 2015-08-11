/************************************************************************
  rcosta@tecgraf.puc-rio.br
  rodesp@tecgraf.puc-rio.br
  Apr 2011
*************************************************************************/

#ifndef _PARTICLES_VECTOR_RENDERER_H_
#define _PARTICLES_VECTOR_RENDERER_H_

#include <particles/defines.h>
#include <particles/positionsorter.h>
#include <particles/vectorset.h>

/************************************************************************
  Forward Declarations
*************************************************************************/

class PtcObstacle;
class UGLArray;
class UGLVertexArray;
class UGLTexture;
class PtcPositionSortedIndices;
class PtcVectorFieldLineSet;

/**
  Renders vector as lines.
*/
class PARTICLES_API PtcVectorRenderer
{
public:
  PtcVectorRenderer ();

  ~PtcVectorRenderer ();

  bool Init ();

  void Draw ();

  void SetCamera (const AlgVector & position, const AlgVector & direction);

  void SetModel (PtcVectorSet* model);

  /**
   * Sets whether color transparency will be used for rendering. If not,
   * alpha component will be ignored.
   *
   * Default: false
   */
  void SetTransparencyEnabled (bool enabled);

  /**
   * Sets whether vector magnitudes will be normalized by magnitude limits
   * obtained from PtcVectorSet. Magnitude values are used as texture coordinates
   * to the material texture that maps values onto colors. The texture is
   * obtained from PtcVectorSet. If no transformation matrix is set to 
   * the texture, or it equals identity (default), then magnitudes should be 
   * normalized so that colors are properly assigned. Otherwise, the
   * transformation matrix is responsible for mapping values to the correct
   * texture coordinates.
   * Default: true
   */
  void SetNormalizeMagnitudeTexCoordsEnabled (bool enabled);

  /**
   * Sets whether displayed vectors sizes will be normalized so that
   * each vector has unitary length.
   * Default: false
   */
  void SetNormalizeVectorSizesEnabled (bool enabled);

  /**
   * Sets the scale factor applied to displayed vector sizes. Scale is
   * applied after vector normalization (if enabled).
   * Default: 1
   */
  void SetVectorSizeScale (float factor);

  /**
   * Sets the width of vector lines.
   * Default: 1
   */
  void SetVectorLineWidth (float width);

  /**
   * Informs the renderer that vector field has changed.
   */
  void SetVectorFieldChanged ();

private:
  class VectorSetChangeListener : public PtcVectorSetChangeListener
  {
  public:
    VectorSetChangeListener (PtcVectorRenderer* renderer)
    : m_renderer(renderer)
    {
    }

    virtual ~VectorSetChangeListener ()
    {
    }

    virtual void PositionsChanged ()
    {
      m_renderer->SetVectorFieldChanged();
    }

    virtual void VectorFieldChanged ()
    {
      m_renderer->SetVectorFieldChanged();
    }

  private:
    PtcVectorRenderer* m_renderer;
  };

private:
  void UpdateVectorLines ();
  void UpdateVectorIndices ();

private:
  PtcPositionSortedIndices* m_sorted_indexes;
  PtcVectorFieldLineSet* m_vector_lines;
  UGLArray* m_vector_indexes;  
  PtcVectorSet* m_model;
  bool m_transparency_enabled;  
  bool m_vector_lines_outdated;
  VectorSetChangeListener* m_pointset_change_listener;
  bool m_normalize_vector_sizes;
  bool m_normalize_magnitude_texcoords;
  float m_vector_size_scale;
  float m_line_width;
};

#endif