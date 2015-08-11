/************************************************************************
rodesp@tecgraf.puc-rio.br
Apr 2011
*************************************************************************/

#ifndef _PARTICLES_VECTOR_FIELD_LINE_SET_H_
#define _PARTICLES_VECTOR_FIELD_LINE_SET_H_

#include <ds/array.h>
#include <ugl/vertexarray.h>
#include "defines.h"
#include "pointset.h"

/**
 * Represents a set of OpenGL lines from a vector field.
 */
class PtcVectorFieldLineSet
{
public:
  PtcVectorFieldLineSet (int dimension);

  ~PtcVectorFieldLineSet ();

  /**
   * Sets the vector field from which vector lines will be
   * extracted.
   * Parameters:
   *   count: Number of vectors
   *   positions: Vector positions 2D: (x, y), 3D: (x, y, z)
   *   vectors: Vectors 2D: (x, y), 3D: (x, y, z)
   *   magnitude_min: Minimum vector magnitude (used for normalization)
   *   magnitude_max: Maximum vector magnitude (used for normalization)
   *   normalize_magnitudes: Whether vector magnitudes will be normalized ([0, 1])
   *   normalize_vector: Whether vectors will be transformed into unitary vectors
   *   vector_size_scale: Scale factor applied to displayed vector sizes.
   */
  void SetVectorField (int count, 
                       const float* positions, 
                       const float* vectors,
                       float magnitude_min,
                       float magnitude_max,
                       bool normalize_magnitudes = true,
                       bool normalize_vectors = false,
                       float vector_size_scale = 1.0f);

  /**
   * Load vector positions (start and end points of each vector).
   * Default: UGLArray::V_POSITION
   */
  void LoadPositions ();

  void UnloadPositions ();

  /**
   * Default: UGLArray::V_COLOR (r,g,b,a)
   */
  void LoadColors ();

  void UnloadColors ();

  /**
   * Default: UGLArray::V_TEXCOORD0
   */
  void SetMagnitudesVextexAttrib (int ugl_array_which);

  void LoadMagnitudes ();

  void UnloadMagnitudes ();

private:
  int m_dimension;
  unsigned int m_count;
  UGLArray* m_vectorarray;
  UGLArray* m_veccolorssarray;
  UGLArray* m_vectexcoordsarray;
};

#endif
