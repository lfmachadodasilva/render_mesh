#ifndef TPV_TETRAHEDRON_SET_H
#define TPV_TETRAHEDRON_SET_H

#include "array.h"
#include "support.h"
#include <topsview/defines.h>

#include <stdio.h>
#include <math.h>

/**
    Represents tetrahedral data.
*/
class TPV_API TpvTetrahedronSet
{
private:
  int m_size;
  TpvIntArray   m_adj;
  TpvFloatArray m_pos;
  TpvFloatArray m_normals;
  TpvSupportArray m_supports;
  TpvSupportArray m_point_supports;
  TpvFloatArray m_params;
  TpvFloatArray m_field;
  TpvFloatArray m_vertex_positions;
  TpvIntArray m_vertex_incidences;

public:
  TpvTetrahedronSet() : m_size(0) {}
  ~TpvTetrahedronSet() {}

  void SetSize(int size) { m_size = size; }
  int GetSize() { return m_size; }

  TpvIntArray* GetAdjacencies() { return &m_adj; }

  //TODO: 1-indexed (0:invalid).
  int GetAdj(int ti, int fi)
  { 
    return m_adj.Get(4*ti+fi); 
  }

  TpvFloatArray* GetPositions() { return &m_pos; }

  float* GetPosition(int ti, int vi)
  { 
    return &(m_pos.GetArray()[12*ti + 3*vi]); 
  }

  TpvFloatArray* GetNormals() { return &m_normals; }

  float* GetNormal(int ti, int fi)
  { 
    return &(m_normals.GetArray()[12*ti + 3*fi]); 
  }

  /** Preferred support order: FACET_USE/ELEMENT2D, ELEMENT. */
  TpvSupportArray* GetSupports() { return &m_supports; }

  TpvSupportArray* GetPointSupports() { return &m_point_supports; }

  // optional
  TpvFloatArray* GetParams() { return &m_params; }

  // optional
  TpvFloatArray* GetField() { return &m_field; }

  float GetField(int ti, int vi)
  { 
    return m_field.Get(4*ti+vi); 
  }

  // Optional
  TpvFloatArray* GetVertexPositions() 
  { 
    return &m_vertex_positions; 
  }

  // Optional
  TpvIntArray* GetVertexIncidences() 
  { 
    return &m_vertex_incidences; 
  }

  void Clear();

  /**
   * Reorders tetrahedrons according to order defined by 'order':
   * order[ti] = tetrahedron 'order[ti]' should be moved to position 'ti'.
   */
  void Reorder (const int* order);

  void Print();
};

#endif
