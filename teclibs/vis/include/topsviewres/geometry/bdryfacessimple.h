// Boundary faces geometry extractor, simple version
// fabraham@tecgraf.puc-rio.br
// Feb 2008
#ifndef TPVRES_BDRY_FACES_SIMPLE_H
#define TPVRES_BDRY_FACES_SIMPLE_H

#include "bdryfacesopaque.h"
#include <alg/vector.h>
#include <geoms/intersect.h>
#include <topsviewres/defines.h>

namespace topsgeoms {
  class PolyhedraModelRes;
};
class TpvGeometrySet;
class TpvResQuadSetOcclusion;
class TpvResQuadSetSplitHex;
class TpvResRadialTriangulator;

class TPVRES_API TpvResBdryFacesSimpleGeometry : public TpvResBdryFacesOpaqueGeometry
{
public:
  TpvResBdryFacesSimpleGeometry (bool use_culling=true);
  virtual ~TpvResBdryFacesSimpleGeometry ();
  /**
   * Set elements hierarchy.
   */
  void SetHierarchy (geoms::Hierarchy* hierarchy, 
                     topsgeoms::PolyhedraModelRes* poly_model);
  TpvGeometrySet* GetQuadSet (GeomSetType type = TYPE_1);
  /**
   * Specifies the observer position in the reservoir coordinate system
   * (after scale).
   */
  void SetObserverPosition (const AlgVector& obspos);
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
  TpvGeometrySet* GetGeomSetInt (int type) const
  {
    return m_geomset[type];
  }
private:
  virtual void ExtractFaces ();
private:
  TpvGeometrySet** m_geomset;
  TpvResQuadSetOcclusion** m_geomsetocc;
  TpvResQuadSetSplitHex** m_geomsetsplithex;
  TpvResRadialTriangulator* m_radial_triangulator;
};

#endif

