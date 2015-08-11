// Primitive sets for reservoirs, base class for concrete geometry sets
// fabraham@tecgraf.puc-rio.br
// Feb 2008
#ifndef TPV_GEOM_SET_BASE_H
#define TPV_GEOM_SET_BASE_H

#include "geomset.h"

#include <utl/sort.h>

class TpvGeometrySetAttrib;

class TPV_API TpvGeometrySetBase : public TpvGeometrySet
{
public:
  virtual ~TpvGeometrySetBase ();
  virtual void SetActiveElements (const bool* active_elems);
  // tpvgeometryset
  void Reset ();
  
  /**
   * Adds a face to this geometry set.
   * The added face is triangulated by the triangulator set to the
   * respective element type, in order to be rendered.
   * The generated triangles will be given a support id according
   * to the support type set for this geometry set. (see SetSupportType()).
   */
  void AddFace (TopFaceUse fu);

  /**
   * Adds a free face (defined by a set of vertices, rather than an
   * entity from TopS) to this geometry set.
   * The added face is triangulated by the triangulator set to the
   * respective element type, in order to be rendered.
   * Parameters:
   *   vertices: positions of each face vertex.
   *   support: support for the face.
   *   vertsupport: (optional) supports for each face vertex. If support
   *     is given for one face, it must be also given for the others.
   *   vertparam: (optional) parametric coordinates used for 
   *     interpolating field within the face vertex's support. 
   *     For one-dimensional support (e.g. edge-use), one natcoord
   *     per vertex must be provided. For two-dimensional support (e.g.
   *     face-use), two natcoords per vertex are required. It must be
   *     given for all or no faces.
   */
  virtual void AddFace (DsArray<AlgVector>* vertices, unsigned int support,
    DsArray<unsigned int>* vertsupport = NULL, DsArray<float>* vertparam = NULL);

  int GetNumFacesTops () const
  {
    return m_tops_faces.Size();
  }

  const TopFaceUse* GetFacesTops () const
  {
    return m_tops_faces.GetArrayConst();
  }
  
  /**
    Gets the number of the vertices of the computed primitives.
  */
  int GetNumVertices ();

  /**
   * Gets the positions of the vertices of the computed primitives.
   */
  const float* GetVertexPositions ();

  /**
   * Gets the normals of the vertices of the computed primitives.
   */
  const float* GetVertexNormals ();

  /**
    Gets the field values of the vertices of the computed primitives.
  */
  const float* GetVertexField ();

  /**
    Gets the number of computed primitives.
  */
  int Size ()
  {
    if (m_pos_ts < m_update_ts) {
      UpdatePositions();
      m_pos_ts = m_update_ts;
    }
    return m_num_faces_tops + m_num_faces_free;
  }

  int DrawnSize ()
  {
    return Size();
  }

  /**
   * Gets the supports of the computed primitives.
   */
  const unsigned int* GetSupports ();
  
  virtual bool HasIndices () const = 0;
  
  /**
   * Specifies if face sorting is enabled.
   * An index array must have been set through 'SetIndices'.
   */
  void SetSortEnabled (bool flag);
  
  /**
   * Sorts the face array according to observer position 'ex', 'ey' and 'ez'.
   */
  void Sort (float ex, float ey, float ez);
  
  /**
   * Specifies a per-element scalar field. Must have dimension equal to 1.
   */
  void SetField (TpvProperty *prop);
  
  /**
   * Specifies per-element colors. Must have dimension equal to 3.
   */
  void SetPerElemColors (TpvProperty *prop);

  /**
   * Adds a new attribute to this geometry set. Attributes
   * are triangulated and drawn as OpenGL vertex parameters of
   * output primitives.
   * 
   * Parameters:
   *   data: user data associated to the attribute.
   *   triangulator: triangulator used to transform user data into
   *     OpenGL vertex parameters. Triangulator writes data
   *     to a number of output vertex arrays. The method 
   *     TpvTriangulator::TriangulateAttrib() is used
   *     to this end.
   *   noutputs: number of vertex arrays to which triangulated data
   *     will be written.
   *   nvalues: number of values per vertex of each output vertex array.
   *   targets: targets of the output vertex array. Correspond to "which"
   *     parameter defined in UGLArray class.
   *
   * For example, if the attribute will be output as three-dimensional texture
   * coordinates to UGLArray::V_TEXCOORD1 target and four-dimensional texture 
   * coordinates at UGLArray::V_TEXCOORD2, then noutputs = 2, nvalues = {3, 4} and
   * targets = {UGLArray::V_TEXCOORD1, UGLArray::V_TEXCOORD2}
   *
   * Returns: ?
   *     
   */
  int AddAttrib (TpvProperty* data, TpvTriangulator* triangulator, 
      int noutputs, int* nvalues, int* targets);

  /**
   * Sets the user data associated to an attribute.
   */
  void SetAttribData (int id, TpvProperty* data);

  /**
   * Signals a change in an geometry set attribute.
   */
  void SetAttribOutdated (int id);
 
  /**
   * Signals a change in the geometry positions.
   */
  void SetPositionsOutdated ();
  
  void SetFieldOutdated ();
  
  /**
   * Signals a change in the per-element colors.
   */
  void SetPerElemColorsOutdated ();

  /**
   * Is any user data outdated ? (Will next Update/Draw* recompute this data?)
   * 'user_update_ts' is updated in case the user data is outdated.
   */
  bool IsUserDataOutdated (int& user_update_ts)
  {
    if (m_update_ts == user_update_ts)
      return false;
    user_update_ts = m_update_ts;
    return true;
  }

  void SetFieldOutput (int which);

  void SetGridTexOutput (int which1, int which2, int which3);

  /**
   * Requests the immediate update of all rendering data that will be used in
   * the next 'Draw' call (positions, normals, etc).
   * Not necessary in order to call Draw (it is done internally).
   */
  void Update ();
   
  /**
   * Loads the specified indices.
   * A previous SetIndices call must have been issued.
   */
  virtual void LoadIndices () = 0;
  
  /**
   * Draws the geometry set.
   */
  void Draw ();
  
  /**
   * Draws the geometry set in selection mode. The supporting element
   * identifier will be pushed onto the name stack for each primitive.
   */
  void DrawSelection ();
 
  // virtual methods:
  DsArray<float>* GetVertexArrayCopy ();
  void FreeFromCPU ();
  void Release ();
protected:
  struct TPV_API SortData {
    int face;
    float cx, cy, cz;
    double dist; 
  };
  class TPV_API CompareFunctor 
  {
  public:
    UTL_FORCE_INLINE int operator() (const unsigned int i1, const unsigned int i2) const
    {
      if (m_sortData[i1].dist < m_sortData[i2].dist)
        return 1;
      else if (m_sortData[i1].dist > m_sortData[i2].dist)
        return -1;
      else
        return 0;
    }
    UTL_FORCE_INLINE void SetSortData (const SortData* data)
    { 
      m_sortData = data;
    }
  private:
    const SortData* m_sortData;
  };
protected:
  TpvGeometrySetBase (int verts_per_prim);  
  virtual void UpdateIndicesFromSortData (DsArray<SortData>* sortdata,
                                          unsigned int* ind) = 0;
  virtual void UpdatePerFaceNormals (UGLArray* positions, UGLArray* normals) = 0;
  virtual void TriangulateGridTexCoords (UGLArray* texcoords1, UGLArray* texcoords2, UGLArray* texcoords3) = 0;
private:
  void TransferToGPU (UGLArray *array);
  void LoadPositions ();
  void LoadNormals ();
  void LoadColors ();
  void LoadField ();
  void LoadAttrib (int id);
  void UnloadAttrib (int id);
  void UnloadPositions ();
  void UnloadNormals ();
  void UnloadColors ();
  void UnloadField ();
  void UpdatePositions ();
  void UpdatePositionsTops ();
  void UpdatePositionsFree ();
  void UpdateNormals ();
  void UpdatePerFaceNormals ();
  void UpdateColors ();
  void UpdatePerFaceColors ();
  void UpdatePerFaceColorsTops ();
  void UpdatePerFaceColorsFree ();
  void UpdatePerFaceGridTexCoords ();
  void UpdatePerFaceGridTexCoordsTops ();
  void UpdatePerFaceGridTexCoordsFree ();
  void UpdateField ();
  void UpdatePerElemField ();
  void UpdatePerElemNodeField ();
  void UpdatePerNodeField ();
  void UpdateAttrib (int id);
  void BuildSortData (int f);
  TopModel* GetModelFromSupport (unsigned int support);
  int GetIdFromSupport (TopModel* model, unsigned int support);
  void PrintArrayMemUsage ();
  UGLArray* GetUsedFieldArray ();
private:
  struct FreeFaceData {
    int numvertices;
    unsigned int support;
    TopModel* model;
  };
  DsArray<TopFaceUse> m_tops_faces;
  DsArray<TopModel*> m_tops_faces_model;
  DsArray<AlgVector> m_free_faces_coords; // free faces (not tops related)
  DsArray<FreeFaceData> m_free_faces_data;
  DsArray<unsigned int> m_free_faces_per_vertex_support;
  DsArray<float> m_free_faces_per_vertex_param;
  DsArray<unsigned int> m_support;
  DsArray<TpvGeometrySetAttrib*> m_attribs;
  DsArray<int> m_attribs_ts;
  UGLArray* m_array_per_face_positions;
  UGLArray* m_array_per_face_normals;
  UGLArray* m_array_per_elem_field;
  UGLArray* m_array_per_elem_node_field;
  UGLArray* m_array_per_node_shared_field;
  UGLArray* m_array_per_node_nonshared_field;  
  UGLArray* m_array_per_elem_colors;
  UGLArray* m_array_per_face_grid_tex_coords_1;
  UGLArray* m_array_per_face_grid_tex_coords_2;
  UGLArray* m_array_per_face_grid_tex_coords_3;
  DsArray<SortData> m_sort_data;
  int m_update_ts;
  int m_pos_ts;
  int m_per_face_grid_tex_coords_ts;
  int m_per_face_normals_ts;
  int m_per_node_normals_ts;
  int m_per_elem_field_ts;
  int m_per_elem_node_field_ts; 
  int m_per_node_nonshared_field_ts;
  int m_per_elem_colors_ts;
  int m_num_faces_tops;
  int m_num_faces_free;
  // array indices: sorting this array instead of SortData*:
  // this is faster since sizeof(SortData) > sizeof(unsigned int).
  DsArray<unsigned int> m_sort_indices;
  CompareFunctor m_comparefunctor;
  UtlSort<unsigned int, CompareFunctor, UtlSortPivotMiddle<unsigned int> > m_sort;
};

#endif

