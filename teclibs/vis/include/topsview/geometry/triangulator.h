// Interface for geometry triangulators
// fabraham@tecgraf.puc-rio.br
// Apr 2008
#ifndef TPV_TRIANGULATOR_H
#define TPV_TRIANGULATOR_H

#include "support.h"
#include <topsview/defines.h>
#include <stdio.h>

class AlgVector;
class UGLArray;
class TpvProperty;
class TopMultiModel;

class TPV_API TpvTriangulator
{
  /////////////////////////// start of old implementation
private:
  static int m_edge_num_lin[TopModel::ELEMENT_MAX][TOP_MAX_NUM_E];

  /**************************************************************************
    Edge
  ***************************************************************************/
  static void InitEdgeNumOfLines();

public:
  static void Init();

  /************************************************************
    Edge
  *************************************************************/
  static int GetEdgeNumOfLines(int el_type, int eu_id);
  static void TriangulateEdgeGeometry(TopModel* m, const TopEdgeUse& eu, 
      float* pos, float* pos_out);
  static void TriangulateEdgeField(TopModel* m, const TopEdgeUse& eu, 
      float* s, float* s_out);

  /////////////////////////// end of old implementation
  /////////////////////////// start of new implementation
  /**
   * Constructor
   */
  TpvTriangulator ();
  /**
   * Destructor
   */
  virtual ~TpvTriangulator ();
  /**
   * Sets a per-node displacement to the triangulated positions. 
   */
  virtual void SetDisplacement (float factor, TpvProperty* disp);  
  /**
   * Triangulates the positions of a face-use.
   * 'model' is the model that owns the facet-use.
   * Coordinates must be added to the 'positions' array using AddValue().
   */
  virtual void TriangulatePositions (const TopFaceUse& fu, TopModel* model, UGLArray* positions)
  {
  }  
  /**
   * Triangulates the gridtex coordinates of a facet use.
   * 'model' is the model that owns the facet-use.
   * Texture coordinates must be added to the 'texcoords1', 'texcoords2' arrays
   * using AddValue().
   * If drawing triangles, 'texcoords3' must also be filled.
   */
  virtual void TriangulateGridTexCoords (const TopFaceUse& fu, TopModel* model, UGLArray* texcoords1, UGLArray* texcoords2, UGLArray* texcoords3)
  {
  }   
  /**
   * Triangulates the scalar field 'property' of a facet use.
   * 'model' is the model that owns the facet-use.
   * Scalar values must be added to the 'texcoords' array using AddValue().
   */
  virtual void TriangulateField (const TopFaceUse& fu, TopModel* model, TpvProperty* property, UGLArray* texcoords)
  {
  }
  /**
   * Triangulates the color 'property' of a facet use.
   * 'model' is the model that owns the facet-use.
   * Color values must be added to the 'colors' array using AddValue().
   */
  virtual void TriangulateColors (const TopFaceUse& fu, 
                                  TopModel* model, 
                                  TpvProperty* property, 
                                  UGLArray* texcoords)
  {
  }
  /**
   * Triangulates a generic attribute of a facet use, and writes the results 
   * to the output vertex arrays.
   * Parameters:
   *   fu: facet use
   *   model: model that owns the facet use
   *   property: attribute to be triangulated
   *   outputs: array of pointer to the output vertex arrays
   *     Triangulated attribute values must be added to the 
   *     the outputs[i] array using AddValue().
   */
  virtual void TriangulateAttrib (const TopFaceUse& fu, TopModel* model, 
      TpvProperty* property, UGLArray** outputs)
  {
  }
  /**
   * Triangulates the positions of a polygon with 'numvertices' vertices with
   * coordinates 'vertices'.
   * Coordinates must be added to the 'positions' array using AddValue().
   */
  virtual void TriangulatePositions (const AlgVector* vertices, int numvertices, UGLArray* positions)
  {
  }
  /**
   * Triangulates the scalar field 'property' of a polygon witn 'numvertices'
   * vertices.
   * The pervertexfield parameter is the array of scalar values per polygon vertex.
   * Scalar values must be added to the 'texcoords' array using AddValue().
   */
  virtual void TriangulateField (int numvertices, float* pervertexfield, UGLArray* texcoords)
  {
  }
  /**
   * Triangulates the color 'property' of a polygon witn 'numvertices'
   * vertices.
   * The pervertexcolors parameter is the array of color values per polygon vertex.
   * Color values must be added to the 'colors' array using AddValue().
   */
  virtual void TriangulateColors (int numvertices, float* pervertexcolors, UGLArray* colors)
  {
  }
  /**
   * Triangulates a generic attribute of polygon with 'numvertices', 
   * and writes the results to the output vertex arrays.
   * Parameters:
   *   numvertices: number of vertices of the polygon
   *   model: model which owns the polygon
   *   support: support topological entity of the polygon
   *   vsupports: per-vertex support topological entities
   *   vparams: parametric (natural) coordinates of the
   *     polygon vertices with respect to the per-vertex
   *     supports
   *   property: attribute to be triangulated.
   *   outputs: array of pointer to the output vertex arrays
   *     Triangulated attribute values must be added to the 
   *     the outputs[i] array using AddValue().
   */
  virtual void TriangulateAttrib (int numvertices, TopModel* model, 
      unsigned int support, unsigned int* vsupports, float* vparams,
      TpvProperty* property, UGLArray** outputs)
  {
  }
  /**
   * Triangulates the gridtex coordinates of a polygon with 'numvertices'
   * vertices.
   * Texture coordinates must be added to the 'texcoords1', 'texcoords2' arrays
   * using AddValue().
   * If drawing triangles, 'texcoords3' must also be filled.
   */
  virtual void TriangulateGridTexCoords (int numvertices, UGLArray* texcoords1, UGLArray* texcoords2, UGLArray* texcoords3)
  {
  }
protected:
  float GetDisplacementFactor() const
  {
    return m_disp_factor;    
  }
  TpvProperty* GetDisplacement() const
  {
    return m_disp;
  }
private:
  float m_disp_factor;
  TpvProperty* m_disp;
};

#endif

