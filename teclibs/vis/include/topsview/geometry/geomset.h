// Primitive sets for reservoirs
// fabraham@tecgraf.puc-rio.br
// Feb 2008
#ifndef TPV_GEOM_SET_H
#define TPV_GEOM_SET_H

#include <topsview/property/property.h>
#include <topsview/defines.h>
#include <tops/model.h>
#include <tops/multimodel.h>
#include <ds/array.h>
#include <alg/vector.h>
#include <stdio.h>

class UGLArray;
class TpvTriangulator;

class TPV_API TpvGeometrySet
{
public:
  enum PropType
  {
    PROP_NONE = 0,
    PROP_PER_ELEM,        
    PROP_PER_FACE,
    PROP_PER_ELEM_NODE,    
    PROP_PER_NODE,
  };
  
  enum SupportType
  {
    SUPPORT_NONE = 0,
    SUPPORT_ELEM,
    SUPPORT_FACE_USE,
    SUPPORT_EDGE_USE,
    SUPPORT_VERTEX_USE,
    SUPPORT_ELEM_ID,
    SUPPORT_NODE
  };

  virtual ~TpvGeometrySet ();
  
  virtual void SetModel (TopModel *m);
  virtual void SetModel (TopMultiModel *m);

  /**
   * Obtains the topological model.
   */
  TopModel* GetModel () const
  {
    return m_model;
  }

  /**
   * Obtains the multi-scale topological model.
   */
  TopMultiModel* GetMultiModel () const
  {
    return m_multimodel;
  }
  
  /**
   * Obtains the number of vertices per primitive.
   */
  int GetNumVertsPerPrim () const
  {
    return m_num_verts_per_prim;
  }
  
  /**
   * Sets the base id used to access arrays indexed by element ids.
   *   GetValue(id) -> array[elem_id - base_elem_id]
   * Default: 0
   * Maitained for compatibility with older geometries.
   */
  void SetBaseElemId (int id)
  {
    m_base_elem_id = id;
  }
  
  virtual void SetMustComputeNormals (bool flag)
  {
    m_has_normals = flag;
  }
  
  bool HasNormals () const
  {
    return m_has_normals;
  }
  
  /**
   * Sets the array indicating whether elements are active or not.
   * Indexed as: array[elem_id - base_elem_id]
   */
  virtual void SetActiveElements (const bool* active_elems);
  
  /**
   * Obtains the array indicating whether elements are active or not.
   * Indexed as: array[elem_id - base_elem_id]
   */
  const bool* GetActiveElements () const
  {
    return m_active_elems;
  }
  
  /**
   * Sets a triangulator for elements with the given topology type.
   * If no triangulator is set for a topology type, the default triangulator
   * will be used.
   */   
  virtual void SetTriangulator (TpvTriangulator* triangulator);
  
  TpvTriangulator* GetTriangulator () const
  {
    return m_triangulator;
  }
  
  /**
   * Resets the face list.
   * 
   * Assumptions: After Draw() or DrawSelection(), 'AddFace' can only be called
   * after a 'Reset' call.
   */
  virtual void Reset () = 0;
  
  /**
   * Adds a face to this geometry set.
   * The added face is triangulated by the triangulator set to the
   * respective element type, in order to be rendered.
   * The generated triangles will be given a support id according
   * to the support type set for this geometry set. (see SetSupportType()).
   * 
   * Assumptions: After Draw() or DrawSelection(), 'AddFace' can only be called
   * after a 'Reset' call.
   */
  virtual void AddFace (TopFaceUse fu) = 0;

  /**
   * Specifies if face sorting is enabled.
   * An index array must have been set through 'SetIndices'.
   */
  virtual void SetSortEnabled (bool flag);

  /**
   * Is face sorting enabled?
   */
  bool IsSortEnabled () const
  {
    return m_sort_enabled;
  }
  
  /**
   * Associates a scalar field to this geometry set (must have dimension equal to 1).
   */
  virtual void SetField (TpvProperty *prop);
  
  /**
   * Gets the field associated to this geometry set. 
   */
  TpvProperty* GetField () const
  {
    return m_field;
  }
  
  /**
   * Specifies per-element colors. Must have dimension equal to 3.
   */
  virtual void SetPerElemColors (TpvProperty *prop);
  
  /**
   * Obtains the per-element colors.
   */
  TpvProperty* GetPerElemColors () const
  {
    return m_per_elem_colors;
  }
  
  /**
   * Signals a change in the per-element scalar field.
   */
  virtual void SetFieldOutdated ();
  
  /**
   * Signals a change in the per-element colors.
   */
  virtual void SetPerElemColorsOutdated () = 0;
   
  TpvProperty* GetPerElemField ();

  bool HasPerElemField () const
  {
    return m_field != NULL && m_field->GetType() == TpvProperty::PROP_ELEMENT;
  }
  
  TpvProperty* GetPerElemNodeField ();

  bool HasPerElemNodeField () const
  {
    return m_field != NULL && m_field->GetType() == TpvProperty::PROP_ELEMENT_NODE;
  }
  
  bool HasPerNodeField () const
  {
    return m_per_node_field != NULL;
  }
  
  TpvProperty* GetPerNodeField ();
  
  TpvProperty* GetDisplayField ();

  /**
   * Sets the vertex attribute to which field data will be output.
   * The attributes are defined in UGLArray class. 
   * Default: UGLArray::V_TEXCOORD0
   */
  virtual void SetFieldOutput (int which);

  int GetFieldOutput () const
  {
    return m_field_output;
  }

  /**
   * Sets the vertex attributes to which grid texture will be output.
   * The attributes are defined in UGLArray class. 
   * Default: (UGLArray::V_TEXCOORD1, UGLArray::V_TEXCOORD2, UGLArray::V_TEXCOORD3)
   */
  virtual void SetGridTexOutput (int which1, int which2, int which3);

  int GetGridTexOutput (int i) const 
  {
    return m_gridtex_output[i];
  }
 
  /**
    Sets per face support type.
    Default: SUPPORT_ELEM
  */
  virtual void SetSupportType (SupportType type);
  
  SupportType GetSupportType () const 
  {
    return m_support_type;
  }

  /**
    Sets per vertex of free faces support type.
    This support is used to compute the field at the free face vertices.
    Default: SUPPORT_NONE
  */
  void SetPerVertexSupportType (SupportType type);

  SupportType GetPerVertexSupportType () const
  {
    return m_per_vertex_support_type;
  }
 
  virtual void SetNormalsType (TpvGeometrySet::PropType type);
  
  PropType GetNormalsType () const
  {
    return m_normals_type;
  }

  virtual void SetFieldType (TpvGeometrySet::PropType type);

  /**
   * Obtains the field type.
   */
  PropType GetFieldType () const
  {
    return m_field_type;
  }
   
  /**
   * Enables/disables the use of per-element colors.
   */
  virtual void SetUsePerElemColor (bool flag);

  /**
   * Should per-element vertex colors be used?
   */
  bool UsePerElemColor () const
  {
    return m_per_elem_color;
  }
  
  virtual void SetWireframe (bool flag)  
  {
    m_wireframe = flag;
  }

  /**
   * Render in wireframe mode?
   */
  bool GetWireframe () const
  {
    return m_wireframe;
  }
  
  /**
   * Specifies the use of vertex buffer objects on vertex arrays.
   */
  virtual void SetVBOEnabled (bool flag)
  {
    m_use_vbo = flag;
  }

  /**
   * Releases all associated vertex array data on CPU and VBOs.
   */
  virtual void Release () = 0;

  /**
   * Should vertex buffer objects be used?
   */
  bool IsVBOEnabled () const
  {
    return m_use_vbo;
  }

  /**
   * Specifies the observer position in the same coordinate system as the
   * geometry set.
   */
  virtual void SetObserverPosition (const AlgVector& obspos)
  {
  }

  /**
   * Specifies the scale used when rendering the geometry set. This scale
   * is specified before 'Draw'.
   */
  virtual void SetScale (float x, float y, float z)
  {
  }

  /**
   * Specifies the scale reference point used when rendering the geometry set.
   * This scale center is specified before 'Draw'.
   */
  virtual void SetScaleCenter (float x, float y, float z)
  {
  }

  /**
   * Gets the total number of primitives.
   */
  virtual int Size () = 0;

  /**
   * Gets the total number of primitives drawn in the last frame.
   */
  virtual int DrawnSize () = 0;
  
  /**
   * Requests the immediate update of all rendering data that will be used in
   * the next 'Draw' call (positions, normals, etc).
   * Not necessary in order to call Draw (it is done internally).
   */
  virtual void Update () = 0;

  /**
   * Frees geometry sets that were transferred to the GPU memory (VBO).
   */
  virtual void FreeFromCPU () = 0;

  /**
   * Draws the geometry set.
   */
  virtual void Draw () = 0;
  
  /**
   * Draws the geometry set in selection mode. The supporting element
   * identifier will be pushed onto the name stack for each primitive.
   */
  virtual void DrawSelection () = 0;
 
  /**
   * Obtains a copy of the current vertex array. It will contain 'numvertices*3' floats.
   */
  virtual DsArray<float>* GetVertexArrayCopy () = 0;
protected:
  TpvGeometrySet (int verts_per_prim);  
  
  bool IsElementActive (int index) const
  {
    return m_active_elems == NULL || m_active_elems[index - m_base_elem_id];
  }

  /**
   * Obtains an element's color.
   */
  const float* GetElemColor (int elem_id);
private:
  TopModel* m_model;
  TopMultiModel* m_multimodel;
  TpvTriangulator* m_triangulator;
  const bool* m_active_elems;
  TpvProperty* m_field;
  TpvProperty* m_per_elem_node_field;
  TpvProperty* m_per_node_field;
  TpvProperty* m_per_elem_colors;
  SupportType m_support_type;  
  SupportType m_per_vertex_support_type;  
  PropType m_normals_type;
  PropType m_field_type;
  int m_num_verts_per_prim;
  int m_base_elem_id;
  int m_field_output;
  int m_gridtex_output[3];
  bool m_has_normals;
  bool m_wireframe;
  bool m_sort_enabled;
  bool m_per_elem_color;
  bool m_use_vbo;
};

#endif

