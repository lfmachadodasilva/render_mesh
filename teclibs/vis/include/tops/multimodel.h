
#ifndef TOP_MULTI_MODEL_H
#define TOP_MULTI_MODEL_H

#include "model.h"

class TopMultiReservoirRefinement;

/**
  Represents a multiscale model.
  The multiscale model consists of a set of element refinement levels. Any 
  element at a level (i) may be refined into a number of child 
  elements which are placed at the level underneath (i+1).

  Example of a grid in which three of the four elements have each been refined 
  into four child elements.

          level 0                      level 1 
  +---------+---------+                  +----+----+ 
  |         |         |                  |    |    |
  |         |         |                  +----+----+
  |         |         |                  |    |    |
  +---------+---------+   ->   +----+----+----+----+
  |         |         |        |    |    |    |    |
  |         |         |        +----+----+----+----+
  |         |         |        |    |    |    |    |
  +---------+---------+        +----+----+----+----+

  Each level is represented by a single TopModel, which is automatically
  constructed or destructed within the multimodel. The model at the first level
  can be structured or unstructured, as currently supported by TopModel. However,
  the other levels are always represented by unstructured meshes, even if the
  first level is structured.

  Consecutive elements at level > 0 can be traversed with GetFirstChild() and GetNext()
  methods.
*/
class TOPS_API TopMultiModel
{
public:
  /**
    Creates an empty multimodel for an unstructured mesh.
    Initially, the multimodel consists of one level only.
  */
  TopMultiModel (TopModel::RealType r = TopModel::REAL_DOUBLE);

  /**
    Creates an empty multimodel for an structured mesh.
    Initially, the multimodel consists of one level only.
  */
  TopMultiModel (int nx, int ny, int nz, TopModel::RealType r = TopModel::REAL_DOUBLE, bool is_reservoir=false);

  ~TopMultiModel ();

  /**
    Gets the model corresponding to the given refinement level.
  */
  TopModel* GetModel (int level) const
  {
    return m_models.Get(level);
  }

  /**
   * Equivalent to GetModel(0).
   */
  TopModel* GetRootModel () const
  {
    return GetModel(0);
  }

  /**
    Gets the number of refinement levels of this multimodel.
  */
  int GetNLevels () const
  {
    return m_nlevels;
  }

  /**
    Gets the refinement level of the given element.
  */
  int GetLevel (TopElement elem) const
  {
    return elem.GetLevel();
  }

  /**
    Gets the refinement level of the given node.
  */
  int GetLevel (TopNode node) const
  {
    return node.GetLevel();
  }

  /**
   * Gets the model corresponding to the refinement level of the given element.
   */
  TopModel* GetElemModel (TopElement elem) const
  {
    return GetModel(GetLevel(elem));
  }

  /**
   * Gets the model corresponding to the refinement level of the given node.
   */
  TopModel* GetNodeModel (TopNode node) const
  {
    return GetModel(GetLevel(node));
  }

  /**
   * Sets the direction of the k coordinate for reservoirs.
   * The default value is TopModel::K_DIR_UP.
   */
  void SetKDir (TopModel::KDir kdir);

  /**
   * Obtains the direction of the k coordinate for reservoirs.
   */
  TopModel::KDir GetKDirReservoir () const
  {
    return m_kdir;
  }

  /**
   * Informs if reservoir elements are adjacent through switched faces,
   * considering the original element template.
   */
  void SetJDirInvertedReservoir (bool f);

  /**
   * Are reservoir elements adjacent through switched faces,
   * considering the original element template?
   */
  bool IsJDirInvertedReservoir() const
  {
    return m_j_inverted_reservoir;
  }

  /**
   * Obtains the index of the face connecting an element with coordinate 'i'
   * and the element with coordinate 'i-1'.
   */
  int IMinusFaceReservoir () const;

  /**
   * Obtains the index of the face connecting an element with coordinate 'i'
   * and the element with coordinate 'i+1'.
   */
  int IPlusFaceReservoir () const;

  /**
   * Obtains the index of the face connecting an element with coordinate 'j'
   * and the element with coordinate 'j-1'.
   */
  int JMinusFaceReservoir () const;

  /**
   * Obtains the index of the face connecting an element with coordinate 'j'
   * and the element with coordinate 'j+1'.
   */
  int JPlusFaceReservoir () const;

  /**
   * Obtains the index of the face connecting an element with coordinate 'k'
   * and the element with coordinate 'k-1'.
   */
  int KMinusFaceReservoir () const;

  /**
   * Obtains the index of the face connecting an element with coordinate 'k'
   * and the element with coordinate 'k+1'.
   */
  int KPlusFaceReservoir () const;

  /**
    Sets the parent of an element at a level i > 0. The parent element must 
    be at the level i-1.
  */
  void SetParent (TopElement elem, TopElement parent);

  /**
    Gets the parent of an element at a level i > 0. The parent element is 
    at the level i-1.
  */
  TopElement GetParent (TopElement elem);

  /**
   * Gets the root element of an element at a level i > 0. The root element is 
   * at the level 0.
   */
  TopElement GetRootElement (TopElement elem);

  /**
    Sets the first child of an element at a level i. The child element must 
    be at the level i+1.
  */
  void SetFirstChild (TopElement elem, TopElement firstchild);

  /**
    Gets the first child of an element at a level i. The child element is at
    the level i+1. 
  */
  TopElement GetFirstChild (TopElement elem);

  /**
    Sets the next sibling for an element at level > 0.
  */
  void SetNext (TopElement elem, TopElement next);

  /**
    Gets the next sibling element at the same level.
    Returns a valid element only if one was set with SetNext() method.
  */
  TopElement GetNext (TopElement elem);

  /**
    Sets the parent of a node at a level i > 0. The parent node must 
    be at the level i-1.
  */
  void SetParent (TopNode node, TopNode parent);

  /**
    Gets the parent of a node at a level i > 0. The parent node is 
    at the level i-1.
  */
  TopNode GetParent (TopNode node);

  /**
    Sets the child of a node at a level i. The child node must 
    be at the level i+1.
  */
  void SetChild (TopNode node, TopNode child);

  /**
    Gets the child of a node at a level i. The child node is at
    the level i+1. 
  */
  TopNode GetChild (TopNode node);

  /**
    Adds a new level to this multimodel. The corresponding model is returned.
  */
  TopModel* AddLevel ();

  /**
    DEPRECATED - may be removed in the future
    Inserts a new node at the given level.
  */
  TopNode InsertNode (int level, float x, float y, float z);

  /**
    DEPRECATED - may be removed in the future
    Inserts a new node at the given level and position (internal) id.
  */
  TopNode InsertNodeAtPosId (int level, unsigned pos_id, float x, float y, float z);

  /*
    DEPRECATED - may be removed in the future
    Inserts a new element at the given level. The appropriate values for:
    parent (see SetParent()), firstchild (see SetFirstChild()) and next (see SetNext())
    must be set.
    // comentario desatualizado?
  */
  TopElement InsertElem (int level, unsigned type, TopNode* nodes, bool update_adj = true);

  /**
   * DEPRECATED - may be removed in the future
   * Inserts a new element at the given level and position (internal) id.
   */
  TopElement InsertElemAtPosId (int level, unsigned type, unsigned pos_id, TopNode* nodes, bool update_adj=true);

  /**
    Refines an element of a reservoir grid into (nx x ny x nz) child elements 
    placed at the underneath level (i+1). If the parent element is at the last
    level, a new level is created.
    This method will work correctly only for reservoir grids (structured meshes
    of HE8_RESERVOIR elements).
  */
  bool RefineElemReservoir (TopElement elem, int nx, int ny, int nz);

  /**
   * Removes the elements generated by refining 'elem' (through RefineElemReservoir).
   */
  void RemoveRefinedElems (TopElement elem);

  /**
   * Obtains the 'i', 'j' and 'k' coordinates of the root element of the given
   * element 'elem'.
   */
  void GetRootElemReverseId (TopElement elem, int* i, int* j, int* k)
  {
    GetRootModel()->GetReverseId(GetRootElement(elem).GetPosId(),i,j,k);
  }

  /**
   * Obtains the 'i' coordinate of the root element of the given element 'elem'.
   */
  int GetRootElemReverseIdI (TopElement elem)
  {
    return GetRootModel()->GetReverseIdI(GetRootElement(elem).GetPosId());
  }

  /**
   * Obtains the 'j' coordinate of the root element of the given element 'elem'.
   */
  int GetRootElemReverseIdJ (TopElement elem)
  {
    return GetRootModel()->GetReverseIdJ(GetRootElement(elem).GetPosId());
  }

  /**
   * Obtains the 'k' coordinate of the root element of the given element 'elem'.
   */
  int GetRootElemReverseIdK (TopElement elem)
  {
    return GetRootModel()->GetReverseIdK(GetRootElement(elem).GetPosId());
  }
  
  /**
   * Calls 'ReleaseMemory' on all refinement levels.
   */
  void ReleaseMemory ();

  /**
   * Trims the amount of memory allocated by this model to nearly the
   * size that is actually ocuppied by the model's data. 
   * If finalize_model = true, the model cannot be edited after trimming.
   */
  bool TrimMemoryToSize (bool finalize_model = false);
  
  /**
   * Specifies a callback for monitoring the progress of heavy operations,
   * like UpdateAdj.
   */
  void SetProgressCB (TopModel::ProgressFunction func, void* funcdata = NULL)
  {
    m_progress_cb     = func;
    m_progress_cbdata = funcdata;
  }

  /**
   * Creates the adjacency information for all the elements in the model on
   * all levels.
   *
   * This method has the same requirements of TopModel::UpdateAdj.
   */
  void UpdateAdj ();

  /**
    Gets the number of children elements for each dimension of the refined element.
  */
  void GetNChildren (TopElement elem, int* nx, int* ny, int *nz);

  /**
    Utility method for getting the child of an element at the position (i, j, k), 
    relative to the refinement (nx, ny, nz) of the element.
  */
  TopElement GetChild (TopElement elem, int i, int j, int k);
  
  /**
   * Obtains the element's 'i', 'j' and 'k' positions on their parent, or on the
   * main grid if the element belongs to the main grid.
   */
  void GetPositionInGrid (TopElement elem, int *i, int *j, int *k);

  /**
    Serialized the multimodel to an output stream.
  */
  bool Serialize (IOStream* s);

  /**
    Restores a serialized multimodel from an input stream.
  */
  bool Deserialize (IOStream* s);

  /**
   * Writes memory usage to file 'fp'. label is an optional string that will
   * be printed before the data.
   */
  void PrintMemUsage (const char* label, FILE* fp);

  /**
   * Obtains the total number of elements on all levels.
   */
  int GetTotalNElem () const;

  /**
   * Obtains the total number of nodes on all levels.
   */
  int GetTotalNNodes () const;

  /**
   * Obtains the model and element with element id 'id'.
   * Assumes ids are unique among all refinement levels.
   */
  bool GetElemAtId (int id, TopModel** model, TopElement* element) const;

  /**
   * Obtains the model and node with node id 'id'.
   * Assumes ids are unique among all refinement levels.
   */
  bool GetNodeAtId (int id, TopModel** model, TopNode* node) const;

private:
  friend class TopMultiElemItr;
  friend class TopMultiReservoirRefinement;

  struct NodeData 
  {
    TopNode parent;
    TopNode child;
    int refcount;
    void Init ()
    {
      parent = TopNode();
      child  = TopNode();
      refcount = 0;
    }
  };

  struct ElemData 
  {
    TopElement parent;
    TopElement firstchild;
    TopElement next;
    int index_in_parent;
    int nx, ny, nz;
    void Init ()
    {
      parent     = TopElement();
      firstchild = TopElement();
      next       = TopElement();
      index_in_parent = -1;
      nx = ny = nz = 0;
    }
  };
private:
  void SetNChildren (TopElement elem, int nx, int ny, int nz);

  ElemData* GetElemData (TopElement elem);
  NodeData* GetNodeData (TopNode node);
  void RemoveNode (TopNode node);
  void RemoveElem (TopElement elem);
  void IncrementRefCount (TopNode node);

private:
  static void InitNodeData (void* ndv);
  static void InitElemData (void* edv);

private:
  int m_nlevels;
  TopRawArray<TopModel*> m_models;
  TopRawArray<int> m_node_attrib_ids;
  TopRawArray<int*> m_elem_attrib_ids;
  TopModel::KDir m_kdir;
  bool m_j_inverted_reservoir;
  TopModel::ProgressFunction m_progress_cb;
  void* m_progress_cbdata;
  //TODO remove refinement from TopMultiModel class
  TopMultiReservoirRefinement* m_reservoir_refinement;
};

/**
    Iterates over all the elements of the multimodel down to the level at maxlevel.
*/
class TOPS_API TopMultiElemItr
{
public:
  TopMultiElemItr (TopMultiModel* multimodel, int maxlevel = TOP_MAX_NUM_LEVELS) 
  : m_multimodel(multimodel), m_maxlevel(maxlevel)
  {
    Begin();
  }
  
  ~TopMultiElemItr () 
  {
  }

  void SetMultiModel (TopMultiModel* m) 
  { 
    m_multimodel = m; 
  }

  void Begin ()
  {
    m_level = 0;
    m_model0 = m_multimodel->GetModel(0);
    m_typeid0 = 0;
    m_posid0 = -1;
    m_elemstack[0] = TopElement();
    Next0();
  }
  
  void Next()
  {
    if (m_level == 0)
      Next0();
    else 
      Nexti();
  }
 
  TopElement GetCurr()
  {
    return m_elemstack[m_level];
  }
  
  bool IsValid()
  {
    return (m_typeid0 >= 0);
  }

private:  
  void Down ()
  {
    TopElement elem = m_multimodel->GetFirstChild(m_elemstack[m_level]);
    while (m_level < m_maxlevel && elem.IsValid()) {
      m_elemstack[++m_level] = elem;
      elem = m_multimodel->GetFirstChild(elem);
    }
  }

  void Up ()
  {
    m_level--;
  }

  void Next0 ()
  {
    assert(m_level == 0);
    for (; m_typeid0 < m_model0->GetNElemTypes(); m_typeid0++) {
      int type = m_model0->GetElemType(m_typeid0);
      for (m_posid0++; m_posid0 < (int) m_model0->GetMaxElemPosId(type); m_posid0++) {
        m_elemstack[0] = m_model0->GetElem((unsigned) type, (unsigned) m_posid0);
        if (m_elemstack[0].IsValid()) {
          Down();
          return;
        }
      }
      m_posid0 = -1;
    }
    m_typeid0 = -1;
    m_elemstack[0] = TopElement();
  }

  void Nexti ()
  {
    assert(m_level > 0);
    while (m_level > 0) {
      m_elemstack[m_level] = m_multimodel->GetNext(m_elemstack[m_level]);
      if (m_elemstack[m_level].IsValid()) {
        Down();
        return;
      }
      else
        Up();
    }
    Next0();
  }
private:
  TopMultiModel* m_multimodel;
  int m_maxlevel;
  int m_level;
  TopModel* m_model0;
  int m_typeid0, m_posid0;
  TopElement m_elemstack[TOP_MAX_NUM_LEVELS];
};

#endif

