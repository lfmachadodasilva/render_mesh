/**
  TopS - Topological data structure for mesh representation.
  
  TopS is a software developed by Tecgraf/PUC-Rio & UIUC.
  It is requested that the TopS users provide the appropriate
  credits and references to the work.
  
  References:
  1 -W. Celes, G.H. Paulino, R. Espinha, "A compact adjacency-based
  topological data structure for finite element mesh representation",
  IJNME, 2005 (in press)
  2 - W. Celes, G.H. Paulino, R. Espinha, "Efficient Handling of Implicit
  Entities in Reduced Mesh Representations", JCISE, Special Issue on
  Mesh-Based Geometric Data Processing, 2005 (in press)
  
  Aug 2005
*/

#ifndef TOP_REC_EDGE_BISECTION_4K
#define TOP_REC_EDGE_BISECTION_4K

#include "../defines.h"
#include "../model.h"

#ifdef TOP_USE_NON_ORIENTED_IMPLICIT_ENTITIES

class TOPS_API TopRecEdgeBisection4KListener
{
public:
  virtual ~TopRecEdgeBisection4KListener() {}

  /** Invoked after an existing element is split into two new elements. */
  virtual void SplitElem (TopModel* m, TopElement old_el, TopElement new_el[2]) {}

  /** Invoked after two elements are merged into a single one. */
  virtual void MergeElem (TopModel* m, TopElement old_el[2], TopElement new_el) {}
};

/**
  Recursive edge bisection algorithm for 4K-like triangular
  and tetrahedral meshes. Refinement data is recorded so that the mesh 
  can be coarsened back. Currently, only regular meshes composed of linear
  tetrahedra (Tet4) are supported. The mesh returned by TopGridBuilder is
  guaranteed to be consistent for being used in this refinement process.

  This class attaches itself to a model (TopModel) in order to manage 
  the refinement process. This is done by the Init() method, which must
  be invoked before refinement starts. After refinement process is done
  the Finalize() method must be called in order to release the model 
  attachment and other recorded data.

  The refinement algorithm is mainly based on the references below:

    Kossaczký I (1994) "A recursive approach to local mesh refinement
    in two and three dimensions", Journal of Computational and Applied 
    Mathematics 55, pp. 275-288.

    Bänsch E (1991) "Local Mesh Refinement in 2 and 3 Dimensions",
    Impact of Computing Science and Engineering 3, pp. 181-191.

  Usage example:
    class MyListener : public TopRecEdgeBisection4KListener
    {
    public:
      ...
      virtual void SplitElem(TopModel* m, TopElement old_el, TopElement new_el[2]) 
      {
        printf("Element has been split!\n");
      }
      virtual void MergeElem(TopModel* m, TopElement old_el[2], TopElement new_el) 
      {
        printf("Elements have been merged!\n");
      }
      ...
    };
    TopModel* mesh = TopGridBuilder(....);
    ...
    TopRecEdgeBisect* ref = new TopRecEdgeBisection4K(mesh);
    MyListener listener;
    ref->AddListener(&listener);
    if (!ref->Init())
      fprintf(stderr, "Error initializing refinement!\n");
    ...
    ref->RefineElements(nelems, elems);
    ...
    delete ref;
*/
class TOPS_API TopRecEdgeBisection4K
{
public:
  enum Triangulation {
    TRIANG_FOUR_TRIANGLES_PER_CELL = 0,
    TRIANG_SIX_TETRA_PER_CELL,
    TRIANG_SIX_PYRAMID_TETRA_PER_CELL
  };

  TopRecEdgeBisection4K (TopModel* model, Triangulation triangulation);

  ~TopRecEdgeBisection4K ();

  /**
    Initializes the refinement manager so that it can be used for
    the first time. This method allocates the necessary data for
    managing the adaptivity process.
  */
  bool Init ();

  /**
    Finalizes the utilization of the refinement manager. Although
    this method is implicitly invoked when the object is deleted,
    it can be used to explicitly free allocated resources when 
    no longer needed. After finalized, no further adaptivity 
    operation can be used.
  */
  bool Finalize ();
  
  TopModel* GetModel () const 
  { 
    return m_model; 
  }

  /**
    Register a new listener for receiving events notified by the 
    refinement manager.
  */
  void AddListener (TopRecEdgeBisection4KListener* l);

  void RemoveListener (TopRecEdgeBisection4KListener* l);

  const TopArray<TopRecEdgeBisection4KListener*>* GetListeners();

  typedef bool (*MergeCriterionCb) (TopRecEdgeBisection4K* ref, 
                                    TopElement elem1, 
                                    TopElement elem2, 
                                    void* userdata);

  /**
    Seta a criterion which constrains the merging of two adjacent elements.
    The callback must return whether the two elements meet the constraining
    criterion. The elements will be merged only if defined criterion is met.
  */ 
  void SetMergeCriterionCb (MergeCriterionCb cb, void* userdata);

  /**
    Returns whether the given edge is "compatibly divisible". An edge is
    compatibly divisible if it is the "refinement edge" of each element 
    which contains it. By convention, the refinement edge of
    an element corresponds to its first edge (e0).

    If the edge is compatibly divisible then the split operator can 
    directly perform on it. Otherwise, it will proceed recursively in order
    to make the edge compatibly divisible before splitting it.
  */
  bool IsCompatiblyDivisible (const TopEdgeUse& ref_eu)
  {
    for (EdgeUseItr it(m_model, ref_eu); it.IsValid(); it.Next()) { 
      TopEdgeUse eu = it.GetCurr();
      if (!m_model->IsCohesive(m_model->GetElem(eu)) && !IsRefinementEdge(eu))
        return false;
    }
    return true;
  }
 
  /**
    Refinement operator.
    Splits an edge into two new other ones. If the edge is not "compatibly
    divisible" (see IsCompatiblyDivisible()), the refinement procedure is 
    recursively applied to the adjacent elements in order to make 
    the edge "compatibly divisible".
    Events: SplitElem()
  */
  void SplitEdge (TopEdgeUse split_eu);

  /**
    Gets the refinement level of the given element.
  */
  int GetRefinementLevel (TopElement elem)
  {
    return GetElemData(elem)->GetLevel();
  }

  /**
    Returns whether a vertex is allowed to be collapsed.
  */    
  bool IsVertexCollapsible (TopVertexUse vu);

  /**
    Collapse a vertex by replacing the mesh surrounding it with the previous
    level of refinement, corresponding to the local mesh state before the edge 
    split that resulted in the current configuration.
    Events: MergeElem()
  */
  bool CollapseVertex (TopVertexUse vu);

  /*************************************
    Utility methods
  **************************************/
  /**
    Element-based refinement operator.
    Refines an element along its "refinement edge". Elements adjacent to
    it are recursively affected.
    Events: SplitElem()
  */  
  void RefineElement (TopElement elem)
  {
    SplitEdge(GetRefinementEdge(elem));
  }

  /**
    Element-based coarsening operator.
    Coarsens the element back to the previous refinement level. Elements 
    adjacent to it may be recursively affected. If the element are
    not allowed to be coarsened, the method returns "false". Yet, the
    adjacent element may have been coarsened, as the ability to coarsen
    the element is determined after the other elements are affected. 
    Events: MergeElem()
  */
  bool CoarsenElement (TopElement elem)
  {
    return CollapseVertex(GetNewestVertex(elem));
  }

  /**
    Refines a set of elements until the given maximum level of refinement
    is reached for all of the descendant elements.
  */
  bool RefineElements (int nelems, const TopElement* elems, int maxlevel);

  /**
    Coarsens a set of elements back until the given minimum level of 
    refinement is reached.
  */
  bool CoarsenElements (int nelems, const TopElement* elems, int minlevel);

  /**
    Refines elements inside the sphere defined by the given radius and 
    centered at (x0, y0, z0). The refinement process is repeated until 
    the maximum refinement level (maxlevel) is achieved.
  */
  void RefineInRadius (double x0, double y0, double z0, double radius, int maxlevel);

  /**
    Coarsens the mesh outside the sphere with the given radius and centered at 
    (x0, y0, z0). This method executes one step of mesh coarsening, and can
    be invoked several times in order that the desired level can be achieved.
  */
  void CoarsenOutRadius (double x0, double y0, double z0, double radius);

  /**************************************
    Node-region-based refinement
  ***************************************/
  void CreateRegion (const TopNode& node);

  void DestroyRegion (const TopNode& node);

  void DestroyRegions ();

  void SetRegion (const TopNode& node, double radius, int level);

  void RefineRegion (const TopNode& node);

  void RefineRegions ();

  void CoarsenOutsideRegions ();

  void GetElemsInRegions (TopRawArray<TopElement>* o_elems);

  void GetRegions (TopRawArray<TopNode>* o_nodes);

  /*************************
    Debug
  **************************/
  /**
    Debug method.
    Prints refinement information about an element in the mesh.
  */
  void Print (TopElement elem, const char* label);

  /**
    Debug method.
  */
  TopEdgeUse GetRefinementEdge (const TopElement& elem);

  TopVertexUse GetNewestVertex (const TopElement& elem)
  {
    return m_model->GetVertexUse(elem, m_newestvertex_lid);
  }

private:
  class EdgeUseItr
  {
    TopPool<TopRawArray<TopEdgeUse>*>* m_pool;
    TopRawArray<TopEdgeUse>*           m_eu_array;
    int                             m_curr;
    TopEdgeUse                      m_eu;
    TopModel*                       m_model;

    static bool TraverseCb(TopModel* m, TopEdgeUse eu, void* data) 
    {
      ((EdgeUseItr*) data)->m_eu_array->Append(eu); 
      return true;
    }

    // Resets iterator position without recomputing elements.
    void First()
    {
      m_curr = 0;
    }

    int Size()
    {
      return m_eu_array->Size();
    }
    
   public:   
    EdgeUseItr(TopModel* model, TopEdgeUse eu) : m_model(model)
    {
      m_pool = model->m_eu_pool;
      if (!m_pool->IsEmpty()) {
        m_eu_array = m_pool->Get();
      } else {
        m_eu_array = new TopRawArray<TopEdgeUse>();
      }
      m_eu = eu;
      Begin();
    }
    
    ~EdgeUseItr()
    {
      m_pool->Put(m_eu_array);
    }

    void SetModel(TopModel* m) { m_model = m; }

    void SetEdgeUse(TopEdgeUse eu) { m_eu = eu; }
    
    void Begin() 
    { 
      m_curr = 0;
      m_eu_array->Reset();
      m_model->TraverseThroughCohesive(m_eu, TraverseCb, this);
    }
    void Next() { m_curr++; }

    TopEdgeUse GetCurr() { return m_eu_array->Get(m_curr); }

    bool IsValid() { return m_curr < m_eu_array->Size(); }
  };

  class ElemData 
  {
  public:
    ElemData (int embedding = 0, int level = 0, int index = 0) 
    : m_embedding(embedding)
    , m_level(level)
    , m_index(index)
    {}
    int GetEmbedding () const { return m_embedding; }
    int GetLevel () const { return m_level; }
    // Type of the tetrahedron (0, 1, 2)
    int GetIndex () const { return m_index; }

  private:
    int m_embedding;
    int m_level;
    int m_index;
  };

  struct MarkIsElemInAnyRegionCbData
  {
    double xc, yc, zc;
    double radius;
    TopRecEdgeBisection4K* refinement;
  };

  struct GetElemInRegionCbData
  {
    double xc, yc, zc;
    double radius;
    TopRecEdgeBisection4K* refinement;
    TopRawArray<TopElement>* output;
  };

  struct SplitCriterionRadiusMaxLevelCbData
  {
    double xc, yc, zc;
    double radius;
    int maxlevel;
  };

  struct NodeRegion
  {
    double radius;
    int level;
    NodeRegion () : radius(0.0), level(0) {}
    NodeRegion(double radius, int level) : radius(radius), level(level) {}
  };

  class EdgeVertexNodesHashKey
  {
  public:
    EdgeVertexNodesHashKey ()
    {
    }
    EdgeVertexNodesHashKey (const TopNode& node0, const TopNode& node1)
    : m_node0(node0)
    , m_node1(node1)
    {
    }
    ~EdgeVertexNodesHashKey ()
    {
    }
    operator int () const
    {
      return (int) (m_node0.GetHandle() + m_node1.GetHandle());
    }
    bool operator == (const EdgeVertexNodesHashKey& other) const
    {
      return other.m_node0 == m_node0 && other.m_node1 == m_node1;
    }
  private:
    TopNode m_node0;
    TopNode m_node1;
  };

  class GlueElementPairItr
  {
  public:
    GlueElementPairItr (TopRecEdgeBisection4K* ref, const TopEdgeUse& coarsen_eu)
    : m_ref(ref)
    , m_elem0()
    , m_elem1()
    , m_euitr(ref->GetModel(), coarsen_eu)
    {
      UpdateGlueElementPair();
    }

    ~GlueElementPairItr ()
    {
    }

    bool IsValid ()
    {
      return m_euitr.IsValid();
    }

    void Next ()
    {
      m_euitr.Next();
      UpdateGlueElementPair();
    }

    void GetCurr (TopElement* elem0, TopElement* elem1)
    {
      *elem0 = m_elem0;
      *elem1 = m_elem1;
    }

  private:
    void UpdateGlueElementPair ()
    {
      if (IsValid()) {
        TopEdgeUse eu = m_euitr.GetCurr();
        TopElement elem = m_ref->GetModel()->GetElem(eu);
        m_ref->GetGlueElementPair(elem, &m_elem0, &m_elem1);
      }
    }

  private:
    TopRecEdgeBisection4K* m_ref;
    TopElement m_elem0;
    TopElement m_elem1;
    TopModel::EdgeUseItr m_euitr;
  };

private:
  ElemData* GetElemData (TopElement elem) 
  {
    TopElementDenseAttrib* att = m_model->GetElemDenseAttrib(m_elemtype, m_elemattid);
    return (ElemData*) att->Get(elem);
  }

  // Similarity class to which a tetrahedron belongs: 0, 1 or 2
  int GetTetrahedronClass (ElemData* data) const
  {
    return (data->GetLevel() + m_tetrahedron_class_offset) % 3;
  }

  bool IsRefinementEdge (TopEdgeUse eu)
  {    
    TopEdgeUse reu = GetRefinementEdge(m_model->GetElem(eu));
    return eu.GetLocalId() == reu.GetLocalId();
  }

  bool IsNewestVertex (const TopVertexUse& vu) const
  {
    return (int) vu.GetLocalId() == m_newestvertex_lid;
  }

  // Returns whether an element is of refinement type
  bool IsOfRefinementTopology (const TopElement& elem) const
  {
    return m_model->GetElemTypeTopology(m_model->GetType(elem)) == m_topology;
  }


  /**************************************
    Node-region-based refinement
  ***************************************/
  TopElementDenseAttrib* GetIsElemInRegionAttrib ()
  {
    return m_model->GetElemDenseAttrib(m_elemtype, 
                                       m_node_regions_elemattid);
  }

  static bool CoarsenOutsideRegionsMergeCriterionCb (TopRecEdgeBisection4K* ref, 
                                                     TopElement elem1, 
                                                     TopElement elem2, 
                                                     void* userdata);

  void GetElemsInRadius (double x0, double y0, double z0, 
                         double radius,
                         TopRawArray<TopElement>* o_elems);

  void GetElemsInRegion (const TopNode& node,
                         TopRawArray<TopElement>* o_elems);

  static int GetElemInRegionCb (TopModel* model, 
                                const TopElement& elem,
                                void* data);

  void InitIsElemInAnyRegion ();

  void FinalizeIsElemInAnyRegion ();

  void CopyIsElemInAnyRegionAttrib (const TopElement& oldelem, 
                                    const TopElement& newelem);

  void UpdateIsElemInAnyRegion ();

  void MarkIsElemInAnyRegion (const TopNode& node, 
                              double radius);

  static int MarkIsElemInAnyRegionCb (TopModel* model, 
                                      const TopElement& elem,
                                      void* data);

  bool GetIsElemInAnyRegion (const TopElement& elem);

  static bool IsElemInRadius (TopModel* model,
                              const TopElement& elem, 
                              double x0, double y0, double z0,
                              double radius);

  bool TraverseElemsDFS (TopModel* model,
                         const TopElement& root_elem,
                         unsigned int timestamp,
                         int (*cb) (TopModel* model, const TopElement& elem, void* data),
                         void* data);

  /******************************************************/

  typedef bool (*SplitCriterionCb) (TopRecEdgeBisection4K* ref, 
                                    const TopElement& elem,
                                    void* userdata);

  static bool SplitCriterionMaxLevelCb (TopRecEdgeBisection4K* ref, 
                                        const TopElement& elem,
                                        void* userdata);

  static bool SplitCriterionRadiusMaxLevelCb (TopRecEdgeBisection4K* ref, 
                                              const TopElement& elem,
                                              void* userdata);

  bool RefineElements (int nelems, 
                       const TopElement* elems,
                       SplitCriterionCb add_to_heap_cb,
                       void* add_to_heap_cb_data);

  TopEdgeUse GetCoarseningEdge (const TopVertexUse& vu);

  void GetGlueElementPair (const TopElement& elem,
                           TopElement* o_elem0,
                           TopElement* o_elem1);

  void InitElemAttribs ();

  struct SplitEdgeUseData
  {
    TopEdgeUse eu;
    int edgei;

    SplitEdgeUseData () {}

    SplitEdgeUseData (const TopEdgeUse& eu, int edgei)
    : eu(eu)
    , edgei(edgei)
    {
    }

    bool operator< (const SplitEdgeUseData& other) const
    {
      if (eu.GetElemHandle() < other.eu.GetElemHandle())
        return true;
      else if (eu.GetElemHandle() == other.eu.GetElemHandle() &&
               eu.GetLocalId() < other.eu.GetLocalId())
        return true;
      else
        return false;
    }
  };

  void MapSplitElemEdgeUses (const TopElement& oldelem,
                             const TopElement& newelem0,
                             const TopElement& newelem1);

  TopEdgeUse SplitEdgeMakeDiamond (const TopEdgeUse& split_eu);

  void CollectSplittingEdgeUses (int num_split_edges,
                                 TopEdge split_edges[], 
                                 int* o_num_split_edgeuses,
                                 SplitEdgeUseData o_split_edgeuses[],
                                 int* o_num_split_coh_edgeuses, 
                                 SplitEdgeUseData o_split_coh_edgeuses[]);

  void CollectSplittingEdges (const TopEdgeUse& split_eu,
                              int* o_num_split_edges, 
                              TopEdge o_split_edges[]);

  TopNode CreateNewestNode (const TopEdge& e)
  {
    TopEdgeUse eu = m_model->GetEdgeUse(e);
    return CreateMidNode(m_model->GetVertexNode(eu, 0),
                         m_model->GetVertexNode(eu, 1));
  }

  TopNode CreateMidNode (const TopNode& node0, const TopNode& node1)
  {
    double x0, y0, z0, x1, y1, z1;
    m_model->GetPosition(node0, &x0, &y0, &z0);
    m_model->GetPosition(node1, &x1, &y1, &z1);
    return m_model->InsertNode(0.5 * (x0 + x1), 
                               0.5 * (y0 + y1), 
                               0.5 * (z0 + z1));
  }

  void ComputeSplitElemNodes (const TopElement& elem, 
                              const TopNode& newestnode, 
                              TopHash<EdgeVertexNodesHashKey, unsigned int>& newedgenodes,
                              TopNode* nodes0, 
                              TopNode* nodes1);

  void ComputeSplitElemNodesTet4 (const TopElement& elem, 
                                  const TopNode& newestnode, 
                                  TopNode* nodes0, 
                                  TopNode* nodes1);

  void ComputeSplitCohNodes (TopEdgeUse eu, 
                             TopNode newestnode0, 
                             TopNode newestnode1, 
                             TopHash<EdgeVertexNodesHashKey, unsigned int>& newedgenodes,
                             TopNode* nodes0, 
                             TopNode* nodes1);

  void ComputeSplitElemData (ElemData* data, ElemData* newdata0, ElemData* newdata1);

  void ComputeMergedElemNodes (const TopElement& elem0,
                               const TopElement& elem1, 
                               TopNode* newnodes);

  void ComputeMergedElemNodesTet4 (const TopElement& elem0,
                                   const TopElement& elem1,
                                   TopNode* newnodes);

  void ComputeMergedElemData (TopElement newelem,
                              ElemData* data0, 
                              ElemData* data1, 
                              ElemData* newdata);

  void CollectRemovingNodesByVertexCollapse (const TopVertexUse& coarsen_vu,
                                             int* o_count,
                                             TopNode o_nodes[]);

  void CollectMergingElems (const TopEdgeUse& coarsen_eu,
                            int* o_count,
                            TopElement o_pairs[][2]);

  void MapMergedElemsVertexUses (const TopElement& oldelem0,
                                 const TopElement& oldelem1,
                                 const TopElement& newelem);

  TopVertexUse CollapseVertexMakeDiamond (const TopVertexUse& coarsen_vu);

  void GetAdjElemsOppositeRefinementEdgeVertices (const TopElement& elem,
                                                  TopElement* o_adj_elem0,
                                                  TopElement* o_adj_elem1);

  bool CheckMergeCriterion (const TopEdgeUse& coarsen_eu);

private:
  TopModel* m_model;
  Triangulation m_triangulation;
  int m_elemtype;
  int m_elemattid;
  int m_topology;
  int m_tetrahedron_class_offset;
  int m_newestvertex_lid;
  bool m_initialized;
  TopArray<TopRecEdgeBisection4KListener*> m_listeners;
  MergeCriterionCb m_merge_criterion_cb;
  void* m_merge_criterion_cb_data;
  MergeCriterionCb m_internal_merge_criterion_cb;
  void* m_internal_merge_criterion_cb_data;
  TopHash<unsigned int, NodeRegion> m_node_regions;
  int m_node_regions_elemattid;
  TopHash<unsigned int, unsigned int> m_edgeuse_map;
  TopHash<unsigned int, unsigned int> m_vertexuse_map;
};

#endif

#endif
