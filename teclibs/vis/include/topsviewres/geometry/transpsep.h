// Boundary faces geometry extractor (with transparency and separation)
// fabraham@tecgraf.puc-rio.br
// Feb 2008
#ifndef TPVRES_TRANSP_SEP_H
#define TPVRES_TRANSP_SEP_H

#include "transp.h"
#include <topsviewres/defines.h>

class TpvResRadialTriangulator;
class TpvResSeparationTriangulator;

class TPVRES_API TpvResTranspSepGeometry : public TpvResTranspGeometry
{
public:
  TpvResTranspSepGeometry (int num_layers);
  virtual ~TpvResTranspSepGeometry ();
  int GetNumLayers () const
  {
    return m_num_layers;
  }
  virtual void SetModel (TopMultiModel* m, bool is_radial, float radial_rw);
  virtual bool SetActiveElements (const bool* active_elems);
  virtual void SetPerElemField (TpvProperty* p);
  virtual void SetPerElemColors (TpvProperty* p);
  virtual void SetFieldOutdated ();
  virtual void SetPerElemColorsOutdated ();
  virtual void SetVBOEnabled (bool flag);
  void SetSeparations (const float* separations);
  const float* GetSeparations () const;
  TpvQuadSet* GetQuadSetOpaque (int index);
protected:
  void CollectElement (TopElement element, int el_id);
  TpvQuadSet* GetQuadSetOpaqueInt (int index)
  {
    assert(0 <= index && index < m_num_layers);
    return m_geom_set_opaque[index];
  }
private:
  virtual void ExtractOpaqueFaces ();
  virtual void ExtractTranspFaces ();
  // virtual methods
  virtual void CollectModelElements();
  virtual void ComputeCentroids();
  virtual void ExtractFaces ();
private:
  TpvQuadSet** m_geom_set_opaque;
  TpvResRadialTriangulator* m_radial_triangulator;
  TpvResRadialTriangulator* m_radial_triangulator_transp;
  TpvResSeparationTriangulator* m_sep_triangulator_transp;
  int m_num_layers;
};

#endif

