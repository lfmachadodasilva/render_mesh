// Point sets
// fabraham@tecgraf.puc-rio.br
// rodesp@tecgraf.puc-rio.br
// Feb 2008
#ifndef TPV_POINT_SET_H
#define TPV_POINT_SET_H

#include <stdio.h>

#include <tops/model.h>
#include <ds/array.h>
#include <ugl/vertexarray.h>

#include <topsview/defines.h>
#include <topsview/property/property.h>


class TpvProperty;
class TpvPointExtractor;

class TPV_API TpvPointSet
{
public:
  enum PropType
  {
    PROP_NONE = 0,
    PROP_PER_ELEM,        
    PROP_PER_FACE,
    PROP_PER_ELEM_NODE,
    PROP_PER_ELEM_POINT,
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

  TpvPointSet ();
  
  ~TpvPointSet ();
  
  void SetModel (TopModel *m);

  /**
   * Sets a per-node displacement to the triangulated positions. 
   */
  //TODO remove this method from this class.
  void SetDisplacement (float factor, TpvProperty* disp);  

  void Reset ();

  void AddNode (TopNode node);

  int GetNumNodes () const
  {
    return m_nodes.Size();
  }

  const TopNode* GetNodes ()
  {
    return m_nodes.GetArray();
  }

  void AddElement (TopElement elem);

  int GetNumElements () const
  {
    return m_elems.Size();
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
  virtual void SetPointExtractor (TpvPointExtractor* extractor);
  
  TpvPointExtractor* GetPointExtractor () const
  {
    return m_point_extractor;
  }

  /**
   * Signals a change in the geometry positions.
   */
  virtual void SetPositionsOutdated ();

  virtual void SetFieldType (TpvPointSet::PropType type);

  /**
   * Obtains the field type.
   */
  PropType GetFieldType () const
  {
    return m_field_type;
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
   * Signals a change in the per-element scalar field.
   */
  virtual void SetFieldOutdated ();

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

  bool HasPerElemField () const
  {
    return m_field != NULL && m_field->GetType() == TpvProperty::PROP_ELEMENT;
  }
  
  bool HasPerElemNodeField () const
  {
    return m_field != NULL && m_field->GetType() == TpvProperty::PROP_ELEMENT_NODE;
  }

  bool HasPerElemPointField () const
  {
    return m_field != NULL && m_field->GetType() == TpvProperty::PROP_ELEMENT_POINT;
  }
  
  bool HasPerNodeField () const
  {
    return m_per_node_field != NULL;
  }

  int Size ()
  {
    if (m_pos_ts < m_update_ts)
      UpdatePositions();
    return m_num_points;
  }

  const float* GetPositions ()
  {
    if (m_pos_ts < m_update_ts)
      UpdatePositions();
    return m_array_positions->GetArrayf();
  }

  void SetSupportType (SupportType type);
  
  SupportType GetSupportType () const 
  {
    return m_support_type;
  }

  /**
   * Requests the immediate update of all rendering data that will be used in
   * the next 'Draw' call (positions, normals, etc).
   * Not necessary in order to call Draw (it is done internally).
   */
  void Update ();

  void Draw ();

  void DrawSelection ();

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
  // TODO
  //virtual void Release () = 0;

  /**
   * Should vertex buffer objects be used?
   */
  bool IsVBOEnabled () const
  {
    return m_use_vbo;
  }

  void LoadPositions ();

  void UnloadPositions ();

  void LoadField ();

  void UnloadField ();

  /**
    Gets the number of the vertices of the computed primitives.
  */
  int GetNumVertices ();

  /**
   * Gets the positions of the vertices of the computed primitives.
   */
  const float* GetVertexPositions ();

  /**
    Gets the field values of the vertices of the computed primitives.
  */
  const float* GetVertexField ();

private:
  void TransferToGPU (UGLArray *array);
  void UpdatePositions ();
  void UpdatePositionsFromNodes ();
  void UpdatePositionsFromElements ();
  void UpdateField ();
  void UpdatePerElemField ();
  void UpdatePerElemNodeField ();
  void UpdatePerElemPointField ();
  void UpdatePerNodeField ();
  void ExtractFieldFromNodes (TpvProperty* prop, UGLArray* array_out);
  void ExtractFieldFromElements (TpvProperty* prop, UGLArray* array_out);
  UGLArray* GetUsedFieldArray ();

  TpvProperty* GetPerElemField ();

  TpvProperty* GetPerElemNodeField ();

  TpvProperty* GetPerElemPointField ();

  TpvProperty* GetPerNodeField ();

  TpvProperty* GetDisplayField ();

  bool AssertValidDisplayField ();

  bool IsElementActive (int index) const
  {
    return m_active_elems == NULL || m_active_elems[index - m_base_elem_id];
  }

private:
  TopModel* m_model;
  TpvPointExtractor* m_point_extractor;
  DsArray<TopNode> m_nodes;
  DsArray<TopElement> m_elems;
  DsArray<unsigned int> m_support;
  const bool* m_active_elems;
  TpvProperty* m_field;
  TpvProperty* m_per_elem_node_field;
  TpvProperty* m_per_elem_point_field;
  TpvProperty* m_per_node_field;
  SupportType m_support_type;  
  PropType m_field_type;
  int m_base_elem_id;
  int m_field_output;
  bool m_use_vbo;

  int m_update_ts;
  int m_pos_ts;
  int m_per_elem_field_ts;
  int m_per_elem_node_field_ts;
  int m_per_elem_point_field_ts;
  int m_per_node_field_ts;
  int m_num_points_from_nodes;
  int m_num_points_from_elems;
  int m_num_points;

  TpvProperty* m_disp;
  float m_disp_factor;

  UGLArray* m_array_positions;
  UGLArray* m_array_per_elem_field;
  UGLArray* m_array_per_elem_node_field;
  UGLArray* m_array_per_elem_point_field;
  UGLArray* m_array_per_node_field; 
};

#endif

