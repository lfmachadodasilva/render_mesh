// Line sets
// fabraham@tecgraf.puc-rio.br
// rodesp@tecgraf.puc-rio.br
// Feb 2008
#ifndef TPV_LINE_SET_H
#define TPV_LINE_SET_H

#include <tops/model.h>
#include <topsview/defines.h>
#include <ds/array.h>
#include <stdio.h>

class UGLArray;
class TpvProperty;
class TopMultiModel;

class TPV_API TpvLineSet
{
public:
  TpvLineSet ();
  
  virtual ~TpvLineSet ();
  
  void SetModel (TopModel *m);
  void SetModel (TopMultiModel *m);

  /**
   * Sets a per-node displacement to the triangulated positions. 
   */
  void SetDisplacement (float factor, TpvProperty* disp);  

  void Reset ();
  
  void AddEdge (TopEdgeUse eu);

  const DsArray<TopEdgeUse>& GetEdges () const
  {
    return m_edges;
  }

  /**
    Gets the number of the vertices of the computed primitives.
  */
  int GetNumVertices ();

  /**
   * Gets the positions of the vertices of the computed primitives.
   */
  const float* GetVertexPositions ();

  int Size ()
  {
    if (m_pos_ts < m_update_ts) {
      UpdatePositions();
      m_pos_ts = m_update_ts;
    }
    return m_num_lines;
  }

  /**
   * Requests the immediate update of all rendering data that will be used in
   * the next 'Draw' call (positions, normals, etc).
   * Not necessary in order to call Draw (it is done internally).
   */
  void Update ();
  
  void Draw ();

protected:
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
   * Obtain the edge uses' original models.
   */
  const DsArray<TopModel*>& GetEdgesModel () const
  {
    return m_edges_model;
  }

  void AddPosition(float x0, float y0, float z0);

  virtual void ComputePositions ();
 
private:
  void TransferToGPU (UGLArray *array);
  void LoadPositions ();
  void UnloadPositions ();
  void UpdatePositions ();
private:
  TopModel* m_model;
  TopMultiModel* m_multimodel;
  DsArray<TopEdgeUse> m_edges;
  DsArray<TopModel*> m_edges_model;
  UGLArray* m_array_positions;
  int m_update_ts;
  int m_pos_ts;
  int m_num_lines;
  int m_num_pos;
  TpvProperty* m_disp;
  float m_disp_factor;
};

#endif

