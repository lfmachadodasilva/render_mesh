// Layer separation triangulator
// fabraham@tecgraf.puc-rio.br
// Apr 2008
#ifndef TPVRES_SEPARATION_TRIANGULATOR_H
#define TPVRES_SEPARATION_TRIANGULATOR_H

#include <topsview/geometry/triangulator.h>
#include <topsviewres/defines.h>

class TopMultiModel;

/**
 * Layer separation triangulator.
 *
 * Applies a 'z' displacement according to layer separation values.
 * Does not divide faces into smaller faces.
 */
class TPVRES_API TpvResSeparationTriangulator : public TpvTriangulator
{
public:
  TpvResSeparationTriangulator ();
  ~TpvResSeparationTriangulator ();
  /**
   * Specifies the multi-scale model that owns the facet uses to be triangulated.
   */
  void SetModel (TopMultiModel* m)
  {
    m_multimodel = m;
  }
  /**
   * Set optional layer separations.
   * If specified, separations[k] will be added to the z coordinate
   * of a cell with layer index 'k'.
   * Returns true if separations have changed and false otherwise.
   */
  bool SetSeparations (const float* separations);
  /**
   * Obtains the optional layer separations.
   * If specified, separations[k] will be added to the z coordinate
   * of a cell with layer index 'k'.
   */
  const float* GetSeparations () const
  {
    return m_separations;
  }
  // virtual methods
  void TriangulatePositions (const TopFaceUse& fu, TopModel* model, UGLArray *positions);
  void TriangulateGridTexCoords (const TopFaceUse& fu, TopModel* model, UGLArray *texcoords1, UGLArray *texcoords2, UGLArray *texcoords3);
  void TriangulateField (const TopFaceUse& fu, TopModel* model, TpvProperty* property, UGLArray *texcoords);
protected:
  TopMultiModel* GetModel () const
  {
    return m_multimodel;
  }
private:
  TopMultiModel* m_multimodel;
  float* m_separations;
};

#endif

