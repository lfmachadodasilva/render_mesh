// Opaque boundary faces geometry extractor
// fabraham@tecgraf.puc-rio.br
// Oct 2008
#ifndef TPVRES_OPAQUE_BDRY_FACES_H
#define TPVRES_OPAQUE_BDRY_FACES_H

#include "bdryfaces.h"
#include <ds/array.h>
#include <geoms/intersect.h>

class TPVRES_API TpvResBdryFacesOpaqueGeometry : public TpvResBdryFacesGeometry
{
public:
  enum PrimType {
    QUADS,
    UNKNOWN,
  };
  /**
   * Enumeration of geomset types. The semantic is defined by the client,
   * but usual uses are TYPE_1 for active and TYPE_2 for inactive cells.
   */
  enum GeomSetType {
    TYPE_1,
    TYPE_2
  };
  static const int GeomSetTypeCount = 2;
public:
  TpvResBdryFacesOpaqueGeometry ();
  virtual ~TpvResBdryFacesOpaqueGeometry ();
  /**
   * Specifies the scale used when rendering the geometry. This scale
   * is specified before 'Renderer::Draw'.
   */
  virtual void SetScale (float x, float y, float z)
  {
  }
  /**
   * Specifies the scale reference point used when rendering the geometry.
   * This scale center is specified before 'Renderer::Draw'.
   */
  virtual void SetScaleCenter (float x, float y, float z)
  {
  }
  /**
   * Obtains the used primitive type.
   */
  virtual PrimType GetPrimitiveType () = 0;
  /**
   * Obtains a vertex array with all geometry vertices.
   * The array should be deleted by the caller.
   * This method should not be called at every frame.
   */
  virtual DsArray<float>* GetVertexArray (const float* separations, 
                                          GeomSetType type = TYPE_1) = 0;
  /**
   * Obtains total number of primitives in the last render call (without any culling).
   */
  virtual int Size () = 0;
  /**
   * Obtains the number of primitives used in the last render call.
   */
  virtual int DrawnSize () = 0;
  virtual void Release ();
  /**
   * Enable/disable faces extraction for a given geomset type.
   */
  void SetGeomSetTypeEnabled (GeomSetType type, bool flag);
  /**
   * Return whether a given geomset type extraction is enabled.
   */
  bool IsGeomSetTypeEnabled (GeomSetType type) const;
  /**
   * For a given geomset type, return an array of booleans with
   * true for active elements for "type", false otherwise.
   */
  const bool* GetActiveElementsArray (GeomSetType type) const;
  /**
   * Given a cell index, return whether the element is active for
   * a specific geomset type.
   */
  bool IsElementActive (int index, GeomSetType type) const;
  /**
   * Given a topelement, return whether it is active for
   * a specific geomset type.
   */
  bool IsElementActive (TopElement element, GeomSetType type) const;
  /**
   * Given a topelement and a topmodel, return whether it is active for
   * a specific geomset type.
   */
  bool IsElementActive (TopElement element, 
                        TopModel* elem_model,
                        GeomSetType type) const;

  // virtual methods
  /**
   * Return an array of booleans with true for active elements,
   * false otherwise.
   */
  const bool* GetActiveElementsArray () const;
  /**
   * Given a cell index, return whether the element is active.
   */
  bool IsElementActive (int index) const;
  /**
   * Given a topelement, return whether it is active.
   */
  bool IsElementActive (TopElement element) const;
  /**
   * Given a topelement and its corresponding topmodel,
   * return whether the element is active.
   */
  bool IsElementActive (TopElement element, TopModel* elem_model) const;
  /**
   * Preprocess geometry sets before faces extraction.
   */
  void BeforeExtractFaces ();

protected:
  bool MustDrawAdjFace (TopElement element, TopModel* elem_model, int fui);
  bool MustDrawAdjFace (TopElement element, 
                        TopModel* elem_model, 
                        int fui,
                        GeomSetType type);
  void AddElem (TopElement element,
                TpvGeometrySet *destset,
                int num_no_test_adj_fu,
                const int *no_test_adj_fu,
                int num_test_adj_fu,
                const int *test_adj_fu);
  void AddElem (TopElement element,
                TpvGeometrySet *destset,
                int num_no_test_adj_fu,
                const int *no_test_adj_fu,
                int num_test_adj_fu,
                const int *test_adj_fu,
                GeomSetType type);

private:
  bool* m_geomset_type_enabled;
  DsArray<bool>* m_elem_active;
};

#endif

