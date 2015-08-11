// Boundary faces geometry extractor (with layer separation)
// fabraham@tecgraf.puc-rio.br
// Feb 2008
#ifndef TPVRES_BDRY_FACES_SEP_H
#define TPVRES_BDRY_FACES_SEP_H

#include "bdryfacesopaque.h"
#include <alg/vector.h>
#include <geoms/intersect.h>
#include <topsviewres/defines.h>

namespace topsgeoms {
  class PolyhedraModelRes;
};
class TpvResGeometrySetOcclusion;
class TpvResQuadSetSplitHex;
class TpvResRadialTriangulator;

class TPVRES_API TpvResBdryFacesSepGeometry : public TpvResBdryFacesOpaqueGeometry
{
public:
  TpvResBdryFacesSepGeometry (int num_layers, bool use_culling=true);
  ~TpvResBdryFacesSepGeometry ();
  /**
   * Set elements hierarchy for a given layer 'k'.
   */
  void SetHierarchy (geoms::Hierarchy* hierarchy, 
                     topsgeoms::PolyhedraModelRes* poly_model, 
                     int k);
  int GetNumLayers () const
  {
    return m_num_layers;
  }
  TpvGeometrySet* GetGeomSet (int index, 
                              GeomSetType type = TYPE_1);
  float GetGeomSetAverageZ (int index, GeomSetType type = TYPE_1);
  /**
   * Specifies the observer position in the reservoir coordinate system
   * (after scale, but before separation).
   *
   * Separations for each layer are specified as separations[l] for layer 'l'.
   * If 'separations' is NULL, no separation is assumed.
   */
  void SetObserverPosition (const AlgVector& obspos, const float* separations);
  virtual void SetModel (TopMultiModel* m, bool is_radial, float radial_rw);
  virtual bool SetActiveElements (const bool* active_elems);
  virtual void SetPerElemField (TpvProperty* p);
  virtual void SetPerElemColors (TpvProperty* p);
  virtual void SetFieldOutdated ();
  virtual void SetPerElemColorsOutdated ();
  virtual void SetVBOEnabled (bool flag);
  virtual void Release ();
  virtual void SetScale (float x, float y, float z);
  virtual void SetScaleCenter (float x, float y, float z);
  virtual PrimType GetPrimitiveType ();
  virtual DsArray<float>* GetVertexArray (const float* separations, 
                                          GeomSetType type = TYPE_1);
  virtual int Size ();
  virtual int DrawnSize ();
protected:
  virtual TpvGeometrySet* GetGeomSetInt (int index, GeomSetType type = TYPE_1);
private:
  // virtual methods
  void ExtractFaces ();
private:
  TpvGeometrySet*** m_geomset;
  TpvResGeometrySetOcclusion*** m_geomsetocc;
  TpvResQuadSetSplitHex*** m_geomsetsplithex;
  TpvResRadialTriangulator* m_radial_triangulator;
  int m_num_layers;
};

#endif

