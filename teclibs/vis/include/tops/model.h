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

#ifndef _TOP_MODEL_H
#define _TOP_MODEL_H


#include <stdio.h>
#include "defines.h"
#include "clock.h"
#include "pool.h"
#include "array.h"
#include "rawarray.h"
#include "heap.h"
#include "hash.h"
#include "attribhash.h"

class TopModel;
class TopFacetHash;
class TopEdgeHash;


/** Entity handles. */
#include "handles.h"

/** ConcreteNode. */
#include "node.h"

/** ConcreteElement. */
#include "element.h"

/** TopErrorHandler, TopErrorHandlerListener. */
#include "error.h"

/** IOStream. */
class IOStream;

/** Mesh listeners (TopModelEditListener, TopModelConsistencyListener, etc.) */
#include "listeners.h"
#include "notifier.h"

/**
    Represents the behavior of an element.
*/
class TOPS_API TopElementBehavior
{
public:
  virtual ~TopElementBehavior() {}
};

/** Attributes */
#include "attributes.h"

/**
    A model is basically a container for elements and nodes, which are 
  the only explicitly represented entities. All the others (TopFacet,
  TopEdge and TopVertex) and their uses (TopFacetUse, TopEdgeUse and TopVertexUse) 
  can be indirectly retrieved from those entities.
  
    The model may represents a finite elements mesh, or other type of cell complex.

    Currently, only manifold models are supported. Although some non-manifold 
  intermediate conditions may arise during edition of the model, the final model 
  must be manifold.
*/
class TOPS_API TopModel
{
public:  
  enum ElemType {
    //For compatibility, keeps original order...
    ELEMENT_T3 = 0,
    ELEMENT_T6,
    ELEMENT_Q4,
    ELEMENT_Q8,
    ELEMENT_TET4,
    ELEMENT_TET10,
    ELEMENT_HEX8,
    ELEMENT_HEX8_RESERVOIR,
    ELEMENT_HEX20,
    ELEMENT_WEDGE15,
    ELEMENT_COH2E2,
    ELEMENT_COH2E3,
    ELEMENT_COH3T3,
    ELEMENT_COH3T6,
    ELEMENT_COH3Q4,
    ELEMENT_COH3Q8,
    //-----------------
    ELEMENT_WEDGE6,
    ELEMENT_INF2E2,
    ELEMENT_INF2E3,
    ELEMENT_INF2V2,
    ELEMENT_INF3Q4,
    ELEMENT_INF3Q8,
    ELEMENT_Q9,
    ELEMENT_POLY2D,
    ELEMENT_LINE2,
    ELEMENT_MAX
  };

  enum NodeType {
    NODE_LOCAL = 0,
    NODE_MAX
  };

  enum RealType {
    REAL_DOUBLE = 0,
    REAL_FLOAT
  };

  enum KDir {
    K_DIR_DOWN = 0,
    K_DIR_UP
  };

  /**
   * Progress function.
   * 'section' is an operation section.
   * 'progress' is an operation progress, where 0 means 0% done and 1 means
   * 100% done.
   * 'data' is an user data that will be passed to the callback.
   */
  typedef void (*ProgressFunction) (const char* section, float progress, void* data);

  /**
   * Attribute initialization function.
   *
   * Can be specified to initialize each new attrib in an attrib array.
   * (See AddElemAttribArray and AddNodeAttribArray).
   */
  typedef void (*InitAttribCB) (void* data);

private:
  friend class TopClock;
  friend class TopFacet;
  friend class TopEdge;
  friend class TopVertex;
  friend class TopRecEdgeBisection4K; //TODO remove from here!

  /** Methods for accessing element templates. */
  #include "templateaccess.h"

  struct EntityHandle {
    unsigned value;
    EntityHandle(unsigned v=TOP_INVALID_HANDLE) : value(v) {}
    unsigned GetValue() { return value; }
    bool operator==(const EntityHandle& b) const { return value == b.value; }
    bool operator==(unsigned b) const { return value == b; }
    bool IsValid() { return value != TOP_INVALID_HANDLE; }
    operator unsigned() const { return value; }
  };

  struct AttPointer {
    void* value;
    AttPointer(void* v=0) : value(v) {}
    void* GetValue() { return value; }
    bool operator==(const AttPointer& b) const { return value == b.value; }
    bool operator==(void* b) const { return value == b; }
    bool IsValid() { return value != 0; }
    operator void*() const { return value; }
  };

#ifdef TOP_USE_RESERVOIR_OPTM
  unsigned int m_reservoir_nbr_ijk[2][6];
#endif
  // Nodes
  int               m_nnodes; //<< Number of nodes.
  int               m_max_node; //<< Maximum full node id + 1.
  int               m_nnodes_alloc; //<< Number of allocated nodes.
  TopConcreteNode*  m_nodes; //<< Node array.
  unsigned char*    m_nodes_pos; //<< Node position (x,y,z) array.
  TopHeap<unsigned> m_free_nodes; //<< Free nodes heap
#ifdef TOP_USE_HASH_ENTITY_ID_MAP
  TopHash<int, EntityHandle> m_node_id_map; //<< Maps id to node handle.
#else
  TopRawArray<unsigned> m_node_id_map; //<< Maps id to node handle.
#endif

  // Elements
  TopElementClass m_elem_class_prototypes[ELEMENT_MAX];
  // Maps elem types to internal registered types.
  int                m_internal_elem_types[ELEMENT_MAX + TOP_MAX_ELEMENT_TYPES]; 
  int                m_nelem_types;  //<< Number of registered elem types.
  // Maps internal types to types in enum ElemType.
  int                m_elem_types[TOP_MAX_ELEMENT_TYPES]; 
  int                 m_elem_topologies[ELEMENT_MAX + TOP_MAX_ELEMENT_TYPES];
  TopElementClass*    m_elem_classes[ELEMENT_MAX + TOP_MAX_ELEMENT_TYPES];
  TopElementBehavior* m_elem_behaviors[ELEMENT_MAX + TOP_MAX_ELEMENT_TYPES];
  TopConcreteElement* m_elem_prototypes[TOP_MAX_ELEMENT_TYPES];
  TopElementTemplate  m_T[TOP_MAX_ELEMENT_TYPES];
  TopElementSizeTemplate m_ST[TOP_MAX_ELEMENT_TYPES];
  int                m_max_elem[TOP_MAX_ELEMENT_TYPES]; //<< Maximum full elem pos_id + 1
  int                m_nelem[TOP_MAX_ELEMENT_TYPES];
  int                m_nelem_alloc[TOP_MAX_ELEMENT_TYPES];      
  unsigned char*     m_elem[TOP_MAX_ELEMENT_TYPES]; //<< Concrete elements.
  TopHeap<unsigned>  m_free_elem[TOP_MAX_ELEMENT_TYPES];
#ifdef TOP_USE_HASH_ENTITY_ID_MAP
  TopHash<int, EntityHandle> m_elem_id_map; //<< Maps id to element handle.
#else
  TopRawArray<unsigned> m_elem_id_map; //<< Maps id to element handle.
#endif

  int               m_real_type;
  int               m_sizeof_real;
  int               m_nx, m_ny, m_nz;
  int               m_is_structured;
  bool              m_is_reservoir;
  KDir              m_kdir;
  bool              m_j_inverted_reservoir;
  int               m_level;
  int               m_dimension;
  TopErrorHandler   m_error;

#ifdef TOP_IMPLICIT_ENTITY_MANAGEMENT
  /**
      Implicit entity maps.
      When the element where the entity is anchored is removed,
    the anchor is transferred to another element, if any.
    If the entity has a lock, then a map from the old element
    to the new one is inserted into the table. 
      The last element in a chain of mappings must be CONCRETE.
    Intermediate positions in the chain may be EMPTY or VIRTUAL.
  */
  TopHash<unsigned, EntityHandle> m_frefmap_hash;
  TopHash<unsigned, EntityHandle> m_erefmap_hash;
  TopHash<unsigned, EntityHandle> m_vrefmap_hash;

  /**
      Reference counters for entity locks.
  */
  TopHash<unsigned, EntityHandle> m_frefcount_hash;
  TopHash<unsigned, EntityHandle> m_erefcount_hash;
  TopHash<unsigned, EntityHandle> m_vrefcount_hash;
#endif

  /**
      Entity attributes.
  */
  TopHash<unsigned, AttPointer> m_elatt_hash;
  TopHash<unsigned, AttPointer> m_natt_hash;
  TopHash<unsigned, AttPointer> m_fatt_hash;
  TopHash<unsigned, AttPointer> m_eatt_hash;
  TopHash<unsigned, AttPointer> m_vatt_hash;
  TopHash<unsigned, AttPointer> m_fuatt_hash;
  TopHash<unsigned, AttPointer> m_euatt_hash;
  TopHash<unsigned, AttPointer> m_vuatt_hash;
  void* m_elem_type_attribs[ELEMENT_MAX + TOP_MAX_ELEMENT_TYPES];
  void* m_node_global_attrib;

  struct AttribArray{
    size_t size;
    void* v;
    int currn;
    InitAttribCB initcb;

    AttribArray (size_t size = 0, void* v = 0, int initsize = 0, InitAttribCB initcb=NULL)
    : size(size)
    , v(v)
    , currn(initsize)
    , initcb(initcb)
    {
      Initialize(0, initsize);
    }
    bool Resize(int n)
    {
      v = realloc(v, n*size);
      if (v == NULL)
        return false;
      Initialize(currn, n);
      currn = n;
      return true;
    }
    void Release()
    {
      free(v);
      size = 0;
      v = 0;
      currn = 0;
    }
    bool IsEmpty() { return v == 0; }
  private:
    void Initialize (int oldn, int newn)
    {
      if (initcb != NULL && oldn < newn) {
        unsigned char* vuc    = (unsigned char*)v + oldn*size;
        unsigned char* vucend = (unsigned char*)v + newn*size;
        while (vuc != vucend) {
          initcb((void*)vuc);
          vuc += size;
        }
      }
    }
  };

  TopRawArray<AttribArray> m_node_attrib_arrays;
  TopRawArray<AttribArray> m_elem_attrib_arrays[TOP_MAX_ELEMENT_TYPES];

  /** Dense attributes */
  TopArray<TopDenseAttrib*> m_node_dense_attribs[NODE_MAX];
  TopArray<TopDenseAttrib*> m_elem_dense_attribs[TOP_MAX_ELEMENT_TYPES];
  /** Sparse attributes */
  TopArray<TopSparseAttrib*> m_node_sparse_attribs[NODE_MAX];
  TopArray<TopSparseAttrib*> m_elem_sparse_attribs[TOP_MAX_ELEMENT_TYPES];
  TopArray<TopSparseAttrib*> m_facet_sparse_attribs;
  TopArray<TopSparseAttrib*> m_face_sparse_attribs;
  TopArray<TopSparseAttrib*> m_edge_sparse_attribs;
  TopArray<TopSparseAttrib*> m_vertex_sparse_attribs;

  /** Edition listener. */
  TopModelNotifier m_edit_notifier;
 
  /************************
  * Elements
  *************************/
  void InitElementClasses();

  TopConcreteElement* GetConcreteElement(unsigned type, unsigned posid) const
  {
    return (TopConcreteElement*) (m_elem[type] + posid * m_ST[type].SIZE);
  }

  TopConcreteElement* GetConcreteElement(unsigned handle) const
  {
    return GetConcreteElement(
      TopElement::GetElemType(handle), TopElement::GetElemPosId(handle));
  }

  TopFacetUse* GetAdjArray(const TopElement& el) const
  {
    unsigned char* adj_array = (unsigned char*) 
        GetConcreteElement(el.GetHandle()) + m_ST[el.GetType()].ADJ_OFFSET;
#ifdef TOP_USE_DYNAMIC_ELEMENTS
    if (m_T[el.GetType()].IS_DYNAMIC)
      return *((TopFacetUse**) adj_array);
    else
#endif
      return (TopFacetUse*) adj_array;
  }

#ifdef TOP_USE_RESERVOIR_OPTM
  unsigned char* GetAdjArrayReservoir(const TopElement& el) const
  {
    return (unsigned char*) GetConcreteElement(el.GetHandle()) + 
      m_ST[el.GetType()].ADJ_OFFSET;
  }
#endif
  
  TopNode* GetNodeArray(const TopElement& el) const
  {
#ifdef TOP_USE_DYNAMIC_ELEMENTS
    if (m_T[el.GetType()].IS_DYNAMIC)
      return *((TopNode**) 
        ((unsigned char*) GetConcreteElement(el.GetHandle()) +
          m_ST[el.GetType()].NODES_OFFSET));
    else
#endif
      return (TopNode*) 
        ((unsigned char*) GetConcreteElement(el.GetHandle()) +
          m_ST[el.GetType()].NODES_OFFSET);
  }

  /************************
  * Nodes 
  *************************/
  TopConcreteNode* GetConcreteNode(unsigned handle) const
  {
    return &m_nodes[TopNode::GetNodePosId(handle)];
  }

  TopConcreteNode* GetConcreteNode(const TopNode& node) const
  {
    return GetConcreteNode(node.GetHandle());
  }

  TopConcreteElement* CreateElemPrototype(int el_type);
 
  void ResetAllTimestamps();

  static bool ResizeAttribArrays(TopRawArray<AttribArray>& att, int n);
  bool ElemArrayReserve(int type, int nelems, bool fitsize);
  bool ElemArrayTrimToSize(int type);
  bool NodeArrayReserve(int sizeof_real, int nnodes, bool fitsize);
  bool NodeArrayTrimToSize(int sizeof_real);

#ifdef TOP_USE_NON_ORIENTED_IMPLICIT_ENTITIES    
  /**********************
  * Facet anchors
  **********************/
  void SetFacetAnchor(const TopElement& el, int fi, int flag)
  {
    if (GetDimension(el) == 2)
      GetConcreteElement(el.GetHandle())->SetEdgeAnchor(fi, flag);
    else
      GetConcreteElement(el.GetHandle())->SetFaceAnchor(fi, flag);
  }

  void SetFacetExAnchor(const TopElement& el, int fi, int flag)
  {
    if (GetDimension(el) == 2)
      GetConcreteElement(el.GetHandle())->SetEdgeAnchor(fi, flag);
    else
      GetConcreteElement(el.GetHandle())->SetFaceAnchor(fi, flag);
  }

  void UpdateFaceAnchor(const TopElement& el, int fi);
  void UpdateFaceAnchors();

  /**********************
  * Face anchors
  **********************/
  void SetFaceAnchor(const TopElement& el, int fi, int flag)
  {
    assert(GetDimension(el) == 3 || fi == 0);
    return GetConcreteElement(el.GetHandle())->SetFaceAnchor(fi, flag);
  }

  void SetFaceExAnchor(const TopElement& el, int fi, int flag)
  {
    assert(GetDimension(el) == 3 || fi == 0);
    return GetConcreteElement(el.GetHandle())->SetFaceExAnchor(fi, flag);
  }

  /**********************
   * Edge anchors 
   **********************/
  void SetEdgeAnchor(const TopElement& el, int ei, int flag)
  {
    return GetConcreteElement(el.GetHandle())->SetEdgeAnchor(ei, flag);
  }

  void SetEdgeExAnchor(const TopElement& el, int ei, int flag)
  {
    return GetConcreteElement(el.GetHandle())->SetEdgeExAnchor(ei, flag);
  }
#endif

  static bool ClearEdgeAnchorCB(TopModel* m, TopEdgeUse eu, void* data);
  static bool UpdateEdgeAnchorNonLinearCB(TopModel* m, TopEdgeUse eu, void* data);
  static bool CountNonCohesiveEdgeUsesCb(TopModel* m, TopEdgeUse eu, void* data);
  void UpdateEdgeAnchor(const TopElement& el, int ei); 
  void UpdateEdgeAnchors();

  typedef bool (*LookForMateFacetUsesCB) (TopModel* m, TopVertexUse vu, void* data);
  void LookForMateFacetUses(
    const TopElement& el, TopFacetUse* fum, LookForMateFacetUsesCB cb);
  typedef bool (*LookForMateEdgeUsesCB) (TopModel* m, TopVertexUse vu, void* data);
  void LookForMateEdgeUses(
    const TopElement& el, TopEdgeUse* eum, LookForMateEdgeUsesCB cb);
  void RemDuplicatedNodeElems(
    TopConcreteNode* cn, TopConcreteNode::ElemNode* eln, unsigned ts1, unsigned ts2);
  void RemDuplicatedElem(const TopEdgeUse& eu);
  void RemDuplicatedElem(const TopVertexUse& vu);

#ifdef TOP_USE_NON_ORIENTED_IMPLICIT_ENTITIES    
  /**********************
   * Vertex anchors 
   **********************/
  void SetVertexAnchor(const TopElement& el, int vi, int flag)
  {
    return GetConcreteElement(el.GetHandle())->SetVertexAnchor(vi, flag);
  }

  void SetVertexExAnchor(const TopElement& el, int vi, int flag)
  {
    return GetConcreteElement(el.GetHandle())->SetVertexExAnchor(vi, flag);
  }

  void UpdateVertexAnchors();

  static bool GetEdgeCB(TopModel* m, TopEdgeUse eu, void* data)
  {
    if (m->GetEdgeAnchor(m->GetElem(eu), eu.GetLocalId())) {  
      *((TopEdgeUse*) data) = eu;
      return false;
    } else
      return true;
  }
#endif
 
  /**
      Gets the "shared" edge-use of ei.
      An element has a shared edge-use if:
        - there is a possible shared edge-use specified in the element 
        template for ei;
        - ei has the same vertices as its share;
        - in case of non-linear edge, the first mid-side node of ei is equal
        to the respective node in the shared edge-use (assumes that every
        mid-side node of an edge points to the same element).

    @returns The shared edge-use or an invalid edge-use.
    @see TopElementTemplate::SHARED_V
    @see TopElementTemplate::SHARED_E
  */
  TopEdgeUse GetSharedEdgeUse(const TopElement& el, int ei)
  {
    TopEdgeUse          eu = GetEdgeUse(el, ei);
    TopNode*            nodes = GetNodeArray(el);
    int sei = SHARED_E(el, ei);
    if (sei >= 0) {
      TopEdgeUse seu = GetEdgeUse(el, sei);
      if (CompareVertices(eu, seu) &&
          (NUM_E_N(el, ei) == 2 || 
           nodes[SHARED_E_N(el, ei)] == nodes[E_N(el, ei, 1)]))
        return seu;
    }
    return TopEdgeUse();
  }
  
  /**
      Gets the "shared" vertex-use of vi. 
    @returns The shared vertex-use or an invalid vertex-use.
    @see TopElementTemplate::SHARED_V
  */
  TopVertexUse GetSharedVertexUse(const TopElement& el, int vi)
  {
    TopNode* nodes = GetNodeArray(el);
    int svi = SHARED_V(el, vi);
    if (svi >= 0 && nodes[V_N(el, svi)] == nodes[V_N(el, vi)]) 
      return TopVertexUse(el.GetHandle(), svi);
    else
      return TopVertexUse();
  }
  
  typedef bool (*TraverseEUCB)(TopModel*, TopEdgeUse, void*);
  /** 
      Traverses all edge-uses of the represented vertex. This method uses 
    adjacency information stored in the data structure.
      Cohesive elements may be visited twice, as they may have two uses of
    the same edge.

    @param cb Callback function, called every time an edge-use is visited.
    @param data Optional user data passed to callback function.
    @returns The number of edge-uses visited (> 0) or -1, if callback function
    has returned "false" at any time.

    @warning During the traversal, time stamp values are used to mark visited 
    elements. Therefore, another traversal cannot be started inside the current 
    one. So, care must be taken with methods invoked in the callback function.

    @see TopModel::InsertCohesive()
  */
  int TraverseAuxEU(unsigned int ts1, unsigned int ts2, 
      TopEdgeUse eu, TopEdgeUse parent, 
      TraverseEUCB cb, void* data, bool shared);

  int Traverse(TopEdgeUse eu, TraverseEUCB cb, void* data, bool shared=true)
  {
    return TraverseAuxEU(TopClock::Advance(), TopClock::Advance(), 
        eu, TopEdgeUse(), cb, data, shared);
  }
 
  /**
      Traverses all the edge-uses of a mid-side edge node. It handles 
    non-manifold intermediate conditions in the data structure.
  */
  int TraverseEU(TopNode n, TraverseEUCB cb, void* data, bool shared=true);
  
  typedef bool (*TraverseVUCB)(TopModel*, TopVertexUse, void*);
  int TraverseAuxVU(unsigned int ts1, unsigned int ts2, 
      TopVertexUse vu, TopVertexUse parent,
      TraverseVUCB cb, void* data, bool shared);
  
  /** 
      Traverses all vertex-uses of the represented vertex. This method uses 
    adjacency information stored in the data structure.
      Cohesive elements may be visited twice, as they may have two uses of
    the same vertex.
    
    @param cb Callback function, called every time a vertex-use is visited.
    @param data Optional user data passed to callback function.
    @param shared If shared == 0, then only one vertex-use of the vertex in
    each element is visited, even for cohesive. 
    @returns The number of vertex-uses visited (> 0) or -1, if callback function
    has returned "false" at any time.

    @warning During the traversal, time stamp values are used to mark visited 
    elements. Therefore, another traversal cannot be started inside the current 
    one. So, care must be taken with methods invoked in the callback function.
    
    @see TopModel::InsertCohesive()
  */
  int Traverse(TopVertexUse vu, TraverseVUCB cb, void* data, bool shared=true)
  {
    return TraverseAuxVU(TopClock::Advance(), TopClock::Advance(), 
        vu, TopVertexUse(), cb, data, shared);
  }

  /**
      Traverses all the vertex-uses of a vertex node. It handles non-manifold
    intermediate
    conditions in the data structure.
  */
  int TraverseVU(TopNode n, TraverseVUCB cb, void* data, bool shared=true);

  int TraverseThroughCohesiveAux(unsigned int ts1, unsigned int ts2, 
    TopEdgeUse eu, TopEdgeUse& parent, TraverseEUCB cb, void* data);

  int TraverseThroughCohesive(TopEdgeUse eu, TraverseEUCB cb, void* data);

  static bool IsBoundaryCb(TopModel* m, TopEdgeUse eu, void* data) 
  {
    return (!m->IsBoundary(eu));
  } 

  int IsEdgeCollapseValidTraverseAux(unsigned int ts1, unsigned int ts2, 
    TopVertexUse vu, TopVertexUse& parent, 
    unsigned int col_ts, TopEdgeUse col_eu,
    int shared);
 
  static bool IsBoundaryCb(TopModel* m, TopVertexUse vu, void* data) 
  {
    return (!m->IsBoundary(vu));
  }

  /** 
    Replaces one of the element's nodes. 
    This method does not update anchors or adjacencies.
    Events triggered: ReplaceElemNode()
  */
  void SetNode(TopElement el, int i, TopNode n)
  {
    //TODO m_edit_notifier: Review semantics
    m_edit_notifier.NotifyReplaceElemNode(el, i, GetNode(el, i), n);
    GetNodeArray(el)[i] = n;
  }

  /** 
    Replaces one of the edge-use's nodes. 
    This method does not update anchors or adjacencies.
    Events triggered: ReplaceElemNode()
  */
  void SetNode(TopEdgeUse eu, int i, TopNode n)
  {
    TopElement el = GetElem(eu);
    SetNode(el, E_N(el, eu.GetLocalId(), i), n);
  }

  /** 
    Replaces the node associated to the vertex-use. 
    This method does not update anchors or adjacencies.
    Events triggered: ReplaceElemNode()
  */
  void SetNode(TopVertexUse vu, TopNode n)
  {
    TopElement el = GetElem(vu);
    SetNode(el, V_N(el, vu.GetLocalId()), n);
  }

  /**
    Removes all references from a node to the adjacent manifold blocks 
    of elements.
    This method does not updates anchors or adjacencies.
  */
  void ClearNodeElems(const TopNode& node)
  {
    GetConcreteNode(node)->ClearElems();
  }

  /**
  */
  void AddNodeElem(const TopNode& node, const TopElement& elem)
  {
    GetConcreteNode(node)->AddElem(elem);
  }
 
  /************************
  * Insert/Remove
  *************************/
  unsigned NewNodeHandle(int sizeof_real, unsigned pos_id);
  TopNode AddNodeAux(unsigned pos_id);
  unsigned NewElemHandle(unsigned type, unsigned pos_id);
  TopElement AddElemAux(unsigned type, unsigned pos_id, TopNode* nodes, 
    bool init_cohesive);
  void UpdateElemAdjFacetUses(const TopElement& el, TopFacetUse* fum);
  void UpdateElemAdjEdgeUses(const TopElement& el, TopEdgeUse* eum);
  void UpdateElemAdjVertexUses(const TopElement& el);
  void UpdateElemAdj(const TopElement& el);
  void UpdateCohesiveAnchors(const TopFacetUse& fu1);
  bool UpdateCohesiveAdj(const TopElement& coh,
    const TopFacetUse& fu1, const TopFacetUse& fu2);
  bool UpdateCohesiveAdjNodes(const TopElement& coh);  

  void DisconnectGiveFaceAnchors(const TopElement& el, 
    int* nfu_locked, TopFaceUse* fu_locked);
  static bool DisconnectFindSubstEUCB(TopModel* m, TopVertexUse vu, void* data);
  TopEdgeUse DisconnectFindEdgeSubstitute(
    const TopElement& el, int i, bool* same_manifold_block);
  void DisconnectGiveEdgeAnchors(const TopElement& el, 
    int* neu_locked, TopEdgeUse* eu_locked);
  TopVertexUse DisconnectFindVertexSubstitute(
    const TopElement& el, int i, bool* same_manifold_block);
  void DisconnectGiveVertexAnchors(const TopElement& el, 
    int* nvu_locked, TopVertexUse* vu_locked);
  void Disconnect(const TopElement& el, int* nfu_locked, TopFaceUse* fu_locked,
    int* neu_locked, TopEdgeUse* eu_locked, 
    int* nvu_locked, TopVertexUse* vu_locked);

  void RemElemMakeVirtual(const TopElement& el,
    int nfu_locked, TopFaceUse* fu_locked,
    int neu_locked, TopEdgeUse* eu_locked,
    int nvu_locked, TopVertexUse* vu_locked);

  void FreeElem(const TopElement& el);

  /** Splits an edge when a cohesive element is inserted. */
  static bool SplitEdgeUseCB(TopModel* m, TopEdgeUse eu, void* data);
  bool Split(TopEdgeUse eu);
  /** Splits a vertex when a cohesive element is inserted. */
  static bool SplitVertexUseCB(TopModel* m, TopVertexUse vu, void* data);
  bool Split(TopVertexUse vu);
  
  /******************
    Reference count
  *******************/
  void MapFacet(unsigned handle, unsigned handlem)
  {
    if (GetDimension(TopElement(TopElement::GetElemHandle(handle))) == 2)
      return MapEdge(handle, handlem);
    else
      return MapFace(handle, handlem);
  }
  unsigned GetFacetMap(unsigned handle) 
  {
    if (GetDimension(TopElement(TopElement::GetElemHandle(handle))) == 2)
      return GetEdgeMap(handle);
    else
      return GetFaceMap(handle);
  }
  void MapFace(unsigned handle, unsigned handlem);
  unsigned GetFaceMap(unsigned fu_hnd); 
  void MapEdge(unsigned handle, unsigned handlem);
  unsigned GetEdgeMap(unsigned eu_hnd);
  void MapVertex(unsigned handle, unsigned handlem);
  unsigned GetVertexMap(unsigned vu_hnd);
#ifdef TOP_IMPLICIT_ENTITY_MANAGEMENT
  void IncFaceRefCount(unsigned handle); 
  void DecFaceRefCount(unsigned handle); 
  void ClearFaceRefCount(unsigned handle); 
  int  GetFaceRefCount(unsigned handle);

  void IncEdgeRefCount(unsigned handle); 
  void DecEdgeRefCount(unsigned handle); 
  void ClearEdgeRefCount(unsigned handle); 
  int  GetEdgeRefCount(unsigned handle);

  void IncVertexRefCount(unsigned handle);
  void DecVertexRefCount(unsigned handle);
  void ClearVertexRefCount(unsigned handle);
  int  GetVertexRefCount(unsigned handle);

  int  AnyNodeEntityHasAnchor(TopElement& el, int nj);
  unsigned FindHandle(const TopFacet& f) { return GetFacetUse(f).GetHandle(); }
  unsigned FindHandle(const TopFace& f) { return GetFaceUse(f).GetHandle(); }
  unsigned FindHandle(const TopEdge& e) { return GetEdgeUse(e).GetHandle(); }
  unsigned FindHandle(const TopVertex& v) { return GetVertexUse(v).GetHandle(); }
#endif

  void Init(RealType r);

public:

  /**
      Creates a new empty model.  model is created, the default
    All the element types defined by ElemType enum are registered by default.
    @param r The data type used to store geometry data, like node positions.
    @see ElemType
    @see Register()
  */
  TopModel(RealType r = REAL_DOUBLE);

  /**
    Creates a structured grid model with size nx x ny x nz.
    In a structured model, elements may be directly accessed given a 
    (i,j,k) tuple. TopS assumes that the grid is filled in the 
    order: i, j, k.
    The isreservoir parameter is used to create a grid for representing
    oil reservoir models. In that case, the element HEX8_RESERVOIR should be 
    used.
  */
  TopModel(int nx, int ny, int nz, RealType r = REAL_DOUBLE, bool isreservoir = false);

  /**
      Destroys the model. 
    @warning User attributes are not freed.
  */
  virtual ~TopModel();

  /**
      Specifies a callback for monitoring the progress of heavy operations,
      like UpdateAdj.
   */
  void SetProgressCB (ProgressFunction func, void* funcdata = NULL)
  {
    m_progress_cb     = func;
    m_progress_cbdata = funcdata;
  }

  /**
      Registers an element type to be used in the model.
      Given an element topology type from enum ElemType and an associated
    behavior, a new element type is created in the model and its id
    is returned. This id must be held by the application and used in the 
    methods that require the element type id to be passed as a parameter 
    (@see GetNElemOfType()).
      The element type must be registered before any elements of this type
    is inserted into the model. Currently, element types cannot be unregistered.
    @param topology_type Id of the element topology from enum ElemType
    @param behavior Behavior associated to the element type, or NULL.
    @return Registered element type id.
  */
  int Register(int topology_type, TopElementBehavior* behavior);

  /**
      Gets the data type used to store geometry data,
    like node positions.
  */
  RealType GetRealType() const { return (RealType) m_real_type; }

  /**
      Converts the data type used to store geometry data.
    @warning This method may create a new node position array. In this
    case, the old one is deleted.
    @see GetNodePositionArray()
  */
  void ConvertRealType(RealType new_type);

  /**
      Reserves memory for at least the given number of elements and nodes.
    Parameters:
      nelems Number of requested elements (or zero) for the element types 
    in the model. All the used element types must have been previously registered
    and the size of the array must be the same as GetNElemTypes(). 
      nnodes Number of requested nodes.
      fitsize Whether the reserved memory should be allocated to fit exactly the
    requested sizes.
  */
  bool ReserveMemory(int* nelems, int nnodes, bool fitsize = false);

  /**
    Trims the amount of memory allocated by this model to nearly the
    size that is actually ocuppied by the model's data. 
    If finalize_model = true, the model cannot be edited after trimming.
  */
  bool TrimMemoryToSize(bool finalize_model = false);

  /**
      TopS does memory management to reuse dynamically allocated data. This 
    method can be called to release memory hold by the memory management mechanism,
    shared by all the models in the current process.
      This method should be called after finishing using TopS in an application, in
    order to free unused memory.
  */
  void ReleaseMemory();

  /*****************************************
  ** Support for multiscale models
  ******************************************/
  /**
    Sets the current level of the model. Should be set only once just after a new
    empty model is created.
    Default: 0.
  */
  void SetLevel(int level) 
  {
    m_level = level;
  }

  int GetLevel() const
  {
    return m_level;
  }

  /*****************************************
  ** Structured grids
  ******************************************/
  /**
    Returns whether the model is structured. 
  */
  int IsStructured() const { return m_is_structured; }

  /**
   * In case of a structured model, returns the number of elements in the 'i' direction.
   */
  int GetNi() const
  {
    return m_nx;
  }

  /**
   * In case of a structured model, returns the number of elements in the 'j' direction.
   */
  int GetNj() const
  {
    return m_ny;
  }

  /**
   * In case of a structured model, returns the number of elements in the 'k' direction.
   */
  int GetNk() const
  {
    return m_nz;
  }

  int GetId(int i, int j, int k) const
  {
	  if (i >= m_nx || i < 0 ||
		    j >= m_ny || j < 0 ||
		    k >= m_nz || k < 0)
    {
		  return -1;
    }
    return (m_ny*k + j)*m_nx + i;
  }
  
  void GetReverseId(int id, int* i, int* j, int* k) const
  {
    int nxny = m_nx*m_ny;
    assert(0 <= id && id < nxny*m_nz);
    *i = id % m_nx;
    *k = id / nxny;
    *j = (id - (nxny * (*k))) / m_nx;
  }

  int GetReverseIdI(int id) const
  {
    return id % m_nx;
  }

  int GetReverseIdJ(int id) const
  {
    int nxny = m_nx*m_ny;
    int k = id / nxny;
    return (id - (nxny*k)) / m_nx;
  }

  int GetReverseIdK(int id) const
  {
    return id / (m_ny*m_nx);
  }

  void GetDimensions(int* nx, int* ny, int* nz) const
  {
    *nx = m_nx; *ny = m_ny; *nz = m_nz;
  }

  /*****************************************
  ** Reservoir models
  ******************************************/
  /**
    Gets whether the model represents an oil reservoir grid.
  */
  bool IsReservoir() const { return m_is_reservoir; }

  /**
    Sets the direction of the k coordinate for reservoirs.
    The default value is K_DIR_UP.
  */
  void SetKDirReservoir(KDir kdir) { m_kdir = kdir; }

  KDir GetKDirReservoir() const { return m_kdir; }

  /**
   * Informs if reservoir elements are adjacent through switched faces,
   * considering the original element template.
   */
  void SetJDirInvertedReservoir(bool f) { m_j_inverted_reservoir = f; }

  /**
   * Are reservoir elements adjacent through switched faces,
   * considering the original element template?
   */
  bool IsJDirInvertedReservoir() const { return m_j_inverted_reservoir; }

  /**
    Returns the list of vertices on the face that connects an element i,j,k to
    its neighboring element i, j-1, k (in the topological grid).
    This list is ordered in parallel with the other method,
    JPlusFaceVertexReservoir, such that the returned vertex for the same 'vi'
    connects the j- face to the j+ face.
  */
  int JMinusFaceVertexReservoir (int vi) const;

  /**
    Returns the list of vertices on the face that connects an element i,j,k to
    its neighboring element i, j+1, k (in the topological grid).
    This list is ordered in parallel with the other method,
    JMinutsFaceVertexReservoir, such that the returned vertex for the same 'vi'
    connects the j+ face to the j- face.
  */
  int JPlusFaceVertexReservoir (int vi) const;

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
   * Obtains the index of the edge connecting an element with coordinate 'i, j'
   * and the element with coordinate 'i-1, j-1'.
   */
  int IMinusJMinusEdgeReservoir () const;

  /**
   * Obtains the index of the edge connecting an element with coordinate 'i, j'
   * and the element with coordinate 'i-1, j+1'.
   */
  int IMinusJPlusEdgeReservoir () const;

  /**
   * Obtains the index of the edge connecting an element with coordinate 'i, k'
   * and the element with coordinate 'i-1, k-1'.
   */
  int IMinusKMinusEdgeReservoir () const;

  /**
   * Obtains the index of the edge connecting an element with coordinate 'i, k'
   * and the element with coordinate 'i-1, k+1'.
   */
  int IMinusKPlusEdgeReservoir () const;

  /**
   * Obtains the index of the edge connecting an element with coordinate 'i, j'
   * and the element with coordinate 'i+1, j-1'.
   */
  int IPlusJMinusEdgeReservoir () const;

  /**
   * Obtains the index of the edge connecting an element with coordinate 'i, j'
   * and the element with coordinate 'i+1, j+1'.
   */
  int IPlusJPlusEdgeReservoir () const;

  /**
   * Obtains the index of the edge connecting an element with coordinate 'i, k'
   * and the element with coordinate 'i+1, k-1'.
   */
  int IPlusKMinusEdgeReservoir () const;

  /**
   * Obtains the index of the edge connecting an element with coordinate 'i, k'
   * and the element with coordinate 'i+1, k+1'.
   */
  int IPlusKPlusEdgeReservoir () const;

  /**
   * Obtains the index of the edge connecting an element with coordinate 'j, k'
   * and the element with coordinate 'j-1, k-1'.
   */
  int JMinusKMinusEdgeReservoir () const;

  /**
   * Obtains the index of the edge connecting an element with coordinate 'j, k'
   * and the element with coordinate 'j-1, k+1'.
   */
  int JMinusKPlusEdgeReservoir () const;

  /**
   * Obtains the index of the edge connecting an element with coordinate 'j, k'
   * and the element with coordinate 'j+1, k-1'.
   */
  int JPlusKMinusEdgeReservoir () const;

  /**
   * Obtains the index of the edge connecting an element with coordinate 'j, k'
   * and the element with coordinate 'j+1, k+1'.
   */
  int JPlusKPlusEdgeReservoir () const;

  /**
   * Obtains the (i,j,k) offsets of a vertex in an element.
   */
  int VertexIReservoir (int vi) const;
  int VertexJReservoir (int vi) const;
  int VertexKReservoir (int vi) const;

  /**
   * Obtains the local index of a vertex in an element with local offsets (i,j,k).
   */
  int IJKVertexReservoir (int i, int j, int k) const;

  /*****************
  ** TopNode
  ******************/
  /**
      Sets a global attribute to be used by every node.
  */
  void SetNodeGlobalAttrib(void* attrib)
  {
    m_node_global_attrib = attrib;
  }

  /**
      Gets the global node attribute.
  */
  void* GetNodeGlobalAttrib()
  {
    return m_node_global_attrib;
  }

  /**
	   Inserts a new node into the model, given its position in space. 
     Returns a handle for the node.
     Events: InsertNode()
	 */
  TopNode InsertNode(double x=0.0, double y=0.0, double z=0.0);
  TopNode InsertNode(float x=0.0, float y=0.0, float z=0.0);

  /**
    Inserts a node at the empty position with the given position (internal) id. 
    If the position is not empty, an invalid node is returned.
    Events: InsertNode()
  */
  TopNode InsertNodeAtPosId(unsigned pos_id, double x=0.0, double y=0.0, double z=0.0);
  TopNode InsertNodeAtPosId(unsigned pos_id, float x=0.0, float y=0.0, float z=0.0);

  /** Sets the user id associated to the node (id >= 0). */
  void SetId(const TopNode& n, int id);

  /**
      Gets the user id associated to the node.
    @returns id or -1.
  */
  int GetId(const TopNode& n)
  {
    return GetConcreteNode(n.GetHandle())->GetId();
  }

  /** Gets the node associated to the given user id. */
  TopNode GetNodeAtId(int id)
  {
#ifdef TOP_USE_HASH_ENTITY_ID_MAP
    return TopNode(m_node_id_map.Get(id));
#else
    if (id >= 0 && id < m_node_id_map.Size())
      return TopNode(m_node_id_map.Get(id));
    else
      return TopNode();
#endif
  }

  /** 
    Removes a node from the model. 
    If the node is used by any elements, they must all be removed
    before the node.
    Events: RemoveNode()
  */
  void RemNode(const TopNode& n);

  /** Gets the node at the given position of the internal node array. */
  TopNode GetNode(unsigned pos_id)
  {
    if (pos_id < (unsigned) m_max_node && GetConcreteNode(pos_id)->IsConcrete())
      return TopNode(m_level, NODE_LOCAL, pos_id);
    else
      return TopNode();    
  }
  
  /** Gets the number of nodes of the model. */
  int GetNNodes() const { return m_nnodes; }

  unsigned GetHandle(const TopNode& n) const { return n.GetHandle(); }

  /** Returns the position id of the node in the node array. */
  unsigned GetPosId(const TopNode& n) const { return n.GetPosId(); }
 
  /** Returns whether the node handle is valid. */
  bool IsValid(const TopNode& n) const { return n.IsValid(); }

  /**
    Returns a position id in the node array that is guaranteed to be 
    greater or equal to the maximum position occupied by a node.
  */
  unsigned GetMaxNodePosId() const { return (unsigned) m_max_node; }

  /** 
    Returns the array of node positions. 
    @warning RealType is not converted to the appropriated type.
  */
  void GetPositionArray(double** v) { *v = (double*) m_nodes_pos; }  
  void GetPositionArray(float** v) { *v = (float*) m_nodes_pos; }

  void SetPosition(const TopNode& n, double x, double y, double z=0)
  {
    unsigned i = 3*TopNode::GetNodePosId(n.GetHandle());
    if (m_real_type == REAL_FLOAT) {
      ((float*) m_nodes_pos)[i] = (float) x;
      ((float*) m_nodes_pos)[i+1] = (float) y;
      ((float*) m_nodes_pos)[i+2] = (float) z;
    } else {
      ((double*) m_nodes_pos)[i] = x;
      ((double*) m_nodes_pos)[i+1] = y;
      ((double*) m_nodes_pos)[i+2] = z;
    }
  }
  
  void SetPosition(const TopNode& n, float x, float y, float z=0)
  {
    unsigned i = 3*TopNode::GetNodePosId(n.GetHandle());
    if (m_real_type == REAL_FLOAT) {
      ((float*) m_nodes_pos)[i] = x;
      ((float*) m_nodes_pos)[i+1] = y;
      ((float*) m_nodes_pos)[i+2] = z;
    } else {
      ((double*) m_nodes_pos)[i] = (double) x;
      ((double*) m_nodes_pos)[i+1] = (double) y;
      ((double*) m_nodes_pos)[i+2] = (double) z;
    }
  }
  
  void GetPosition(const TopNode& n, double* x, double* y, double* z)
  {
    assert(z != NULL);
    unsigned i = 3*TopNode::GetNodePosId(n.GetHandle());
    if (m_real_type == REAL_FLOAT) {
      *x = (double) ((float*) m_nodes_pos)[i];
      *y = (double) ((float*) m_nodes_pos)[i+1];
      *z = (double) ((float*) m_nodes_pos)[i+2];
    } else {
      *x = ((double*) m_nodes_pos)[i];
      *y = ((double*) m_nodes_pos)[i+1];
      *z = ((double*) m_nodes_pos)[i+2];
    }
  }

  void GetPosition(const TopNode& n, double* x, double* y)
  {
    unsigned i = 3*TopNode::GetNodePosId(n.GetHandle());
    if (m_real_type == REAL_FLOAT) {
      *x = (double) ((float*) m_nodes_pos)[i];
      *y = (double) ((float*) m_nodes_pos)[i+1];
    } else {
      *x = ((double*) m_nodes_pos)[i];
      *y = ((double*) m_nodes_pos)[i+1];
    }
  }
  
  void GetPosition(const TopNode& n, float* x, float* y, float* z)
  {
    assert(z != NULL);
    unsigned i = 3*TopNode::GetNodePosId(n.GetHandle());
    if (m_real_type == REAL_FLOAT) {
      *x = ((float*) m_nodes_pos)[i];
      *y = ((float*) m_nodes_pos)[i+1];
      *z = ((float*) m_nodes_pos)[i+2];
    } else {
      *x = (float) ((double*) m_nodes_pos)[i];
      *y = (float) ((double*) m_nodes_pos)[i+1];
      *z = (float) ((double*) m_nodes_pos)[i+2];
    }
  }

  void GetPosition(const TopNode& n, float* x, float* y)
  {
    unsigned i = 3*TopNode::GetNodePosId(n.GetHandle());
    if (m_real_type == REAL_FLOAT) {
      *x = ((float*) m_nodes_pos)[i];
      *y = ((float*) m_nodes_pos)[i+1];
    } else {
      *x = (float) ((double*) m_nodes_pos)[i];
      *y = (float) ((double*) m_nodes_pos)[i+1];
    }
  }

  /**
   * Obtains node 3d coordinates.
   * Assumes the model's real type is REAL_FLOAT.
   */
  void GetPositionFloat(const TopNode& n, float* x, float* y, float* z)
  {
    unsigned i = 3*TopNode::GetNodePosId(n.GetHandle());
    assert(m_real_type == REAL_FLOAT);
    *x = ((float*) m_nodes_pos)[i];
    *y = ((float*) m_nodes_pos)[i+1];
    *z = ((float*) m_nodes_pos)[i+2];
  }
   
  /**
      Returns the first node's element. It works for manifold models.
    In non-manifold situations, nodes may have more than one associated element.
  */  
  TopElement GetElem(const TopNode& n) 
  { 
    TopConcreteNode::ElemNode* eln = GetConcreteNode(n.GetHandle())->GetElemNode();
    if (eln)
      return eln->el;
    else
      return TopElement();
  }
  
  /**
      Sets the pointer of an user-defined attribute for the node.
  */
  bool SetAttrib(const TopNode& n, void* data) 
  { 
    return m_natt_hash.Set(n.GetHandle(), data);
  }

  void* GetAttrib(const TopNode& n)
  {
    return m_natt_hash.Get(n.GetHandle());
  }

  /**
      Returns if the node is a vertex of the element that it points to.
  */
  bool IsVertex(const TopNode& n)
  {
    TopElement el = GetElem(n);
    if (!el.IsValid())
      return false;
    for (int i = 0; i < GetNVertices(el); i++) 
      if (GetVertexNode(el, i) == n) 
        return true;
    return false;
  }
 
#ifdef TOP_USE_NON_ORIENTED_IMPLICIT_ENTITIES  
  /**
      Gets the reference vertex for the node. If the node is not a vertex, 
    then returns an invalid vertex.
  */
  TopVertex GetVertex(const TopNode& n)
  {
    TopElement el = GetElem(n);
    if (!el.IsValid())
      return TopVertex();
    for (int i = 0; i < GetNVertices(el); i++) 
      if (GetVertexNode(el,i) == n) 
        return GetVertex(el, i);
    return TopVertex();
  }
#endif
  
  /**
      Gets the first vertex-use of the node in the element.
    @warning Note that cohesive elements may have more than one use
    of the same node.
  */
  TopVertexUse GetVertexUse(const TopElement& el, const TopNode& n)
  {
    for (int i = 0; i < GetNVertices(el); i++) 
      if (GetVertexNode(el, i) == n)
        return GetVertexUse(el, i);
    return TopVertexUse();
  }

  /**
      Returns if the node is a mid-side node of an edge of the element that 
    it points to.
  */
  bool IsEdge(const TopNode& n)
  {
    TopElement el = GetElem(n);
    if (!el.IsValid())
      return false;
    for (int i = 0; i < GetNNodes(el); i++) 
      if (N_E(el, i) >= 0 && GetNode(el, i) == n) 
        return true;
    return false;
  }
  
#ifdef TOP_USE_NON_ORIENTED_IMPLICIT_ENTITIES    
  /**
      If the node is a mid-side node of an edge, returns the 
    reference edge for the node. Else, an invalid edge is returned.
  */
  TopEdge GetEdge(const TopNode& n)
  {
    TopElement el = GetElem(n);
    if (!el.IsValid())
      return TopEdge();
    for (int i = 0; i < GetNNodes(el); i++) {
      int ei = N_E(el, i);
      if (ei >= 0 && GetNode(el, i) == n)
        return GetEdge(el, ei);
    }
    return TopEdge();
  }
#endif

  /**
      Gets the first edge-use of the node in the element.
    @warning Note that cohesive elements may have more than one use
    of the same node.
  */
  TopEdgeUse GetEdgeUse(const TopElement& el, const TopNode& n)
  {
    for (int i = 0; i < GetNNodes(el); i++) {
      int ei = N_E(el, i);
      if (ei >= 0 && GetNode(el, i) == n)
        return GetEdgeUse(el, ei);
    }
    return TopEdgeUse();
  }
  
  /*****************
  ** TopElement
  ******************/

  /** Gets the number of element types registered in the model. */
  int GetNElemTypes() const
  {
    return m_nelem_types;
  }

  /** Gets the ith element type registered in the model. */
  int GetElemType(int i) const
  {
    return m_elem_types[i];
  }

  /** Gets element type information. */
  const TopElementClass* GetElemClass(int type) const 
  { 
    return m_elem_classes[type]; 
  }
   
  /** 
      Gets the behavior associated to a previously registered element type. 
  */
  TopElementBehavior* GetElemTypeBehavior(int type) const 
  { 
    return m_elem_behaviors[type]; 
  }

  /** 
      Gets the topology id (from enum ElemType) associated to the 
    given registered element type. 
  */
  int GetElemTypeTopology(int type) const
  {
    return m_elem_topologies[type];
  }

  int GetTopology(const TopElement& elem) const
  {
    return m_elem_topologies[GetType(elem)];
  }

  /** 
      Sets an attribute for the given registered element type. 
  */
  void SetElemTypeAttrib(int type, void* attrib) 
  { 
    m_elem_type_attribs[type] = attrib; 
  }

  /** Gets the attribute associated to the given registered element type. */
  void* GetElemTypeAttrib(int type) const
  { 
    return m_elem_type_attribs[type]; 
  }


  /**
    Inserts a new element to the model.
    Although this method handles non-manifold intermediate conditions that 
    may arise during model edition, the final mesh must be manifold.

    For dynamic elements the array of nodes must be terminated by an invalid
    node (e.g. by calling the default constructor TopNode(), 
    so the number of nodes can be determined and proper element created.

    Parameters:
      type Element type, defined in enum ElemType.
      update_adj If true, the element adjacencies will be updated as the
        element is inserted. Otherwise, the method UpdateAdj() must be called
        after constructing the mesh in order to update the adjacencies.
        WARNING: Note that if update_adj is true (or false) for an element, 
        it also must be so for EVERY element inserted into the model.
    Events: InsertElem()

    WARNING: Currently, cohesive elements can only be inserted AFTER their
    non-cohesive neighbors.
  */  
  TopElement InsertElem(unsigned type, TopNode* nodes, bool update_adj=true);

  /**
    Inserts an element at the empty position with the given position (internal) id, 
    and updates adjacencies. If the position is not empty, an invalid element is returned.
    Cohesive elements can only be inserted after its adjacent elements are
    already in the model.
    
    WARNING: This method can only be invoked during the model construction,
    before updating adjacencies. After adding all the elements of the model, 
    every position before the maximum id must be filled. This method does not
    consider the empty elements inserted into the free element heap after an
    element removal. If it is called after an element has been removed, the heap
    will be in an inconsistent state, or it may overwrite VIRTUAL elements,
    thus making the model's anchors inconsistent.

    Parameters:
      type Element type, defined in enum ElemType.
      pos_id Position in the internal element array of the element type.
      update_adj If true, the element adjacencies will be updated as the
        element is inserted. Otherwise, the method UpdateAdj() must be called
        after constructing the mesh in order to update the adjacencies.
    Events: InsertElem()
  */
  TopElement InsertElemAtPosId(unsigned type, unsigned pos_id, 
      TopNode* nodes, bool update_adj=true);

#ifdef TOP_USE_NON_ORIENTED_IMPLICIT_ENTITIES    
  /**
      Creates and inserts a cohesive element between the two non-cohesive 
    elements incident to the given facet. A cohesive (also called "interface") 
    element is an especial element which consists of exactly two facets and may
    only be inserted between two non-cohesive elements. 
    
      When the cohesive element is inserted, some nodes in its second facet 
    may need to be duplicated (new nodes are automatically created and inserted 
    into the model). The duplicated nodes are always on the second facet of the 
    cohesive element and the user MUST explicitly set new attributes for them. This
    node duplication implies that, although the respective edges and vertices 
    of the facet do not change, their incidence does. The nodes of the first facet 
    of the cohesive element are identical to the given facet.

      The node duplications are notified by the DuplicateNode() method 
    on the model edition listener.
    
      In order to make node duplication easier, the nodes of a cohesive
    element are internally stored in a fixed order correspondence between its
    two facets. 
    
      Let's consider following example: a cohesive element has just been
    inserted. Given that node "ni"
    is a reference to node with id "i" in the model, and that elem[j] is
    a reference to the jth node of an element, then elem[0] is associated 
    to elem[6], elem[1] is associated to elem[6+1], and so on. The first 6
    nodes belongs to the first facet and the others to the second. Although
    the nodes are directly associated by an increment of 6, their local 
    facet-use orientation order is reversed (as shown by the element template ahead),
    in order to maintain consistency on the facet-use normals.
   
    @verbatim 

                    v2
                     n2 
                    /  \
                   /    \         v5
                  /      \ ^      n8
                 /        \ \e1  /  \
           e2 / /          \    /    \
             V n5          n4  /      \   normal
          normal             \/    ....\--------->
        <---------  f0       .\        n10 \
            /           e3^ .  \         \  V e4 
           /             / n11  \  f1     \
          /               .      \         \
         n0----------n3----------n1         \
         v0    -->      /        v1          \
               e0      /                      \
                      n6----------n9----------n7
                      v3         <--          v4
                                 e5

    
      Element's nodes order: n0 n1 n2 n3 n4 n5 | n6 n7 n8 n9 n10 n11 
      f0: n0, n3, n1, n4, n2, n5
      f1: n3, n11, n5, n10, n7, n9
    @endverbatim 
   
      Therefore, to find out which nodes were duplicated after a cohesive
    element insertion between two non-cohesive elements, one would write:
    
    @verbatim
     n = model->GetNNodes(coh)/2;
     for (i = 0; i < n; i++) {
        if (model->GetNode(coh, i) != model->GetNode(coh, n+i)) {
          *** coh->GetNode(n+i) is new!!!! 
          ***
          *** So, we MUST set new attributes for the node, by 
          *** allocating new space in memory for attribute data type 
          *** and initializing it. 
          
          node_data = Create new userdata...
          newnode   = model->GetNode(coh, n+i);
          model->SetAttrib(newnode, node_data);
        }
     }
   @endverbatim

   @param type Element type, defined in enum ElemType.      

      On success, it returns the cohesive element inserted. On failure, it
    returns and invalid element.

    Events: InsertElem(), InsertNode(), DuplicateNode()

    @see TopModelEditListener
  */ 
  TopElement InsertCohesive(unsigned type, const TopFacet& facet);
  TopElement InsertCohesive(unsigned type, 
                            const TopElement& el1, const TopElement& el2);
#endif

  /** Sets the user id associated to the element (id >= 0). */
  void SetId(const TopElement& el, int id);

  /**
      Gets the user id associated to the element.
  @returns id or -1.
  */
  int GetId(const TopElement& el) 
  { 
    return GetConcreteElement(el.GetHandle())->GetId(); 
  }

  /** Gets the element associated to the given user id. */
  TopElement GetElemAtId(int id)
  {
#ifdef TOP_USE_HASH_ENTITY_ID_MAP
    return TopElement(m_elem_id_map.Get(id));
#else
    if (id >= 0 && id < m_elem_id_map.Size())
      return TopElement(m_elem_id_map.Get(id));
    else
      return TopElement();
#endif
  }
 
  /**
    Removes an element from the model, updating its adjacency information. 
    Although this method handles non-manifold intermediate conditions that 
    may appear during model edition, the final mesh must be manifold.

    WARNING: At the moment, we cannot remove a non-cohesive element from a 
    model with cohesive elements, because a non-adjacent cohesive element may 
    need to be modified. This is currently not handled by TopS. As an example, 
    consider a T3 mesh with radially ordered triangles and a cohesive element. 
    If one element is removed, the cohesive will have to be modified.      

    Events: RemoveElem()
  */  
  void RemElem(const TopElement& el);

  /**
      Gets the element of the given type at the given position of the
    internal array of the type.
    @param type Element type, defined in enum ElemType.
    @param pos_id Position in the internal element array of the element type.
  */
  TopElement GetElem(unsigned type, unsigned pos_id)
  {  
    int it = m_internal_elem_types[type];
    if (it >= 0 && pos_id < (unsigned) m_max_elem[it] && 
        GetConcreteElement(it, pos_id)->IsConcrete())
      return TopElement(m_level, it, pos_id);
    else
      return TopElement();    
  }
 
  /** Gets the number of elements of a given type in the model. */
  int GetNElemOfType(unsigned type) const 
  { 
    int it = m_internal_elem_types[type];
    if (it >= 0)
      return m_nelem[it]; 
    else
      return 0;
  }

  /** Gets the total number of elements in the model. */
  int GetNElem() const
  {
    int n = 0;
    for (int i = 0; i < TOP_MAX_ELEMENT_TYPES; i++) 
      n += m_nelem[i];
    return n;
  }

  /**
    Returns a position id in the node array that is guaranteed to be 
    greater or equal to the maximum position occupied by a node.
  */
  unsigned GetMaxElemPosId(int type) const 
  { 
    return (unsigned) m_max_elem[m_internal_elem_types[type]]; 
  }

  unsigned GetHandle(const TopElement& el) const 
  { 
    return el.GetHandle(); 
  }
  
  /** Gets element type, defined in enum ElemType. */
  unsigned GetType(const TopElement& el) const 
  { 
    return (unsigned) m_elem_types[el.GetType()]; 
  }
  
  unsigned GetPosId(const TopElement& el) const 
  { 
    return el.GetPosId(); 
  }

  bool IsValid(const TopElement& el) const 
  { 
    return el.IsValid(); 
  }
  
  /** Gets element's dimension: 2 for 2D elements or 3 for 3D elements. */
  int GetDimension(const TopElement& el) const 
  {
    return m_T[el.GetType()].DIMENSION;
  }
 
  bool IsCohesive(const TopElement& el) const 
  {
    return (m_T[el.GetType()].IS_COHESIVE != 0);
  }

  bool IsInfinite(const TopElement& el) const 
  {
    return (m_T[el.GetType()].IS_INFINITE != 0);
  }

  bool IsDynamic(const TopElement& el) const
  {
    return (m_T[el.GetType()].IS_DYNAMIC != 0);
  }

  /**
      Gets the element order: 1 for linear elements, 2 for quadratic elements,
    and so on.
  */
  int GetOrder(const TopElement& el) const 
  {
    return m_T[el.GetType()].ORDER;
  }

  /** Sets the pointer of an user-defined attribute for the element. */
  bool SetAttrib(const TopElement& el, void* data) 
  { 
    return m_elatt_hash.Set(el.GetHandle(), data);
  }

  /**
      Gets the user-defined attribute set for the element.
    @returns Attribute or NULL.
  */
  void* GetAttrib(const TopElement& el) 
  { 
    return m_elatt_hash.Get(el.GetHandle());
  }

  /**
      Sets a time stamp for element traversal.
    @warning Internal use only.
  */
  void SetTimestamp(const TopElement& el, unsigned int ts) 
  { 
    GetConcreteElement(el.GetHandle())->SetTimestamp(ts); 
  }

  unsigned int GetTimestamp(const TopElement& el)
  {
    return GetConcreteElement(el.GetHandle())->GetTimestamp(); 
  }

 
  /************************
  ** TopElement - Adjacencies
  *************************/
  int GetNAdj(const TopElement& el) const
  {
    return NUM_F(el);
  }

  bool HasAdj(const TopElement& el, int fi)
  {
#ifdef TOP_USE_RESERVOIR_OPTM
    if (m_is_reservoir)
      return ((*(GetAdjArrayReservoir(el))) & ((unsigned char) 1 << fi)) != 0;
    else
#endif
    return GetAdj(el, fi).IsValid();
  }
  
  TopElement GetAdj(const TopElement& el, int fi) const
  {
#ifdef TOP_USE_RESERVOIR_OPTM
    if (m_is_reservoir) {
      if (HasAdj(el, fi))
        return GetElem(ELEMENT_HEX8_RESERVOIR,
                       (unsigned) el.GetPosId() +
                                  m_reservoir_nbr_ijk[m_kdir][fi]);
      else 
        return TopElement();
    } else {
#endif
      TopFacetUse fu = GetAdjArray(el)[fi];
      return fu.IsValid() ? GetElem(fu) : TopElement();
#ifdef TOP_USE_RESERVOIR_OPTM
    }
#endif
  }

  TopFacetUse GetAdjFacetUse(const TopElement& el, int fi) const
  {
    return GetAdjArray(el)[fi];
  }

  /*********************
  ** TopElement - Facets 
  **********************/
  int GetNFacets(const TopElement& el) const
  {
    return NUM_F(el);
  }

  TopFacetUse GetFacetUse(const TopElement& el, int i) const
  {
    return TopFacetUse(el.GetHandle(), i);
  }
#ifdef TOP_USE_NON_ORIENTED_IMPLICIT_ENTITIES  
  TopFacet GetFacet(const TopElement& el, int fi)
  {
    //assert(GetConcreteElement(el.GetHandle())->IsConcrete());
    if (GetFacetAnchor(el, fi))
      return TopFacet(GetFacetUse(el, fi).GetHandle());
    else
      return TopFacet(GetMate(GetFacetUse(el, fi)).GetHandle());
  }

  TopFacet GetFacet(const TopElement& el1, const TopElement& el2)
  {
    for (int i = 0; i < GetNFacets(el1); i++) 
      if (GetAdj(el1, i) == el2) 
        return GetFacet(el1, i);
    return TopFacet();  
  }    
#endif

#ifdef TOP_USE_NON_ORIENTED_IMPLICIT_ENTITIES    
  /** Internal use. */
  unsigned GetFacetAnchor(const TopElement& el, int fi)
  {
    if (GetDimension(el) == 2)
      return GetConcreteElement(el.GetHandle())->GetEdgeAnchor(fi);
    else
      return GetConcreteElement(el.GetHandle())->GetFaceAnchor(fi);
  }

  /** Internal use. */
  unsigned GetFacetExAnchor(const TopElement& el, int fi)
  {
    if (GetDimension(el) == 2)
      return GetConcreteElement(el.GetHandle())->GetEdgeExAnchor(fi);
    else
      return GetConcreteElement(el.GetHandle())->GetFaceExAnchor(fi);
  }
#endif
  
  /*********************
  ** TopElement - Faces 
  **********************/
  int GetNFaces(const TopElement& el) const
  {
    return NUM_FC(el);
  }

  TopFaceUse GetFaceUse(const TopElement& el, int i)
  {
    return TopFaceUse(el.GetHandle(), i);
  }

#ifdef TOP_USE_NON_ORIENTED_IMPLICIT_ENTITIES    
  TopFace GetFace(const TopElement& el, int fi)
  {
    //assert(GetConcreteElement(el.GetHandle())->IsConcrete());
    if (GetFaceAnchor(el, fi))
      return TopFace(GetFaceUse(el, fi).GetHandle());
    else
      return TopFace(GetMate(GetFaceUse(el, fi)).GetHandle());
  }
#endif

#ifdef TOP_USE_NON_ORIENTED_IMPLICIT_ENTITIES    
  /** Internal use. */
  unsigned GetFaceAnchor(const TopElement& el, int fi)
  {
    return GetConcreteElement(el.GetHandle())->GetFaceAnchor(fi);
  }
  
  /** Internal use. */
  unsigned GetFaceExAnchor(const TopElement& el, int fi)
  {
    return GetConcreteElement(el.GetHandle())->GetFaceExAnchor(fi);
  }
#endif

  /*********************
  ** TopElement - Edges 
  **********************/
  int GetNEdges(const TopElement& el) const
  {
    return NUM_E(el);
  }

  TopEdgeUse GetEdgeUse(const TopElement& el, int i)
  {
    return TopEdgeUse(el.GetHandle(), i);
  }

#ifdef TOP_USE_NON_ORIENTED_IMPLICIT_ENTITIES    
  /**
      Gets the ei'th edge incident to the element.
  */
  TopEdge GetEdge(const TopElement& el, int ei)
  {
    /**
        For linear elements, the edge's element is the one with the anchor set.
        For higher order elements, the edge's element is the one pointed by
      the mid-side nodes. These nodes MUST point to the same element, which
      also has the edge anchor set.

        @warning Unsafe to be called inside Traverse().
    */
    TopEdgeUse eu = GetEdgeUse(el, ei);
    if (NUM_E_N(el, ei) > 2) {
      TopElement nel = GetElem(GetNodeArray(el.GetHandle())[E_N(el, ei, 1)]);
      // Assumes that el is not cohesive.
      for (int i = 0; i < GetNEdges(nel); i++) 
        if (GetEdgeAnchor(nel, i) && CompareVertices(GetEdgeUse(nel, i), eu)) 
          return TopEdge(GetEdgeUse(nel, i).GetHandle());
      assert(0);
      return TopEdge();
    } else {
      if (!GetEdgeAnchor(el, ei))
        Traverse(eu, GetEdgeCB, &eu);
      assert(eu.IsValid());
      return TopEdge(eu.GetHandle());
    }
  }
#endif
 
#ifdef TOP_USE_NON_ORIENTED_IMPLICIT_ENTITIES    
  /** Internal use. */
  unsigned GetEdgeAnchor(const TopElement& el, int ei)
  {
    return GetConcreteElement(el.GetHandle())->GetEdgeAnchor(ei);
  }

  /** Internal use. */
  unsigned GetEdgeExAnchor(const TopElement& el, int ei)
  {
    return GetConcreteElement(el.GetHandle())->GetEdgeExAnchor(ei);
  }
#endif
  
  /*********************
  ** TopElement - Vertices
  **********************/
  int GetNVertices(const TopElement& el) const
  {
    return NUM_V(el);
  }

  TopVertexUse GetVertexUse(const TopElement& el, int i)
  {
    return TopVertexUse(el.GetHandle(), i);
  }

#ifdef TOP_USE_NON_ORIENTED_IMPLICIT_ENTITIES    
  TopVertex GetVertex(const TopElement& el, int vi)
  {
    // Even if the vertex owner is a cohesive element, this method is still 
    // safe, as long as vertex anchors have been correctly updated. Therefore, 
    // only the correct vertex-use in cohesive element will have the bit set. 
    TopNode     node = GetNodeArray(el)[V_N(el, vi)];
    TopElement  nel = GetElem(node);
    for (int i = 0; i < GetNVertices(nel); i++) 
      if (GetVertexAnchor(nel, i) && GetVertexNode(nel, i) == node) 
        return TopVertex(GetVertexUse(nel, i).GetHandle());
    assert(0);
    return TopVertex();
  }
#endif
 
#ifdef TOP_USE_NON_ORIENTED_IMPLICIT_ENTITIES    
  /** Internal use. */
  unsigned GetVertexAnchor(const TopElement& el, int vi)
  {
    return GetConcreteElement(el.GetHandle())->GetVertexAnchor(vi);
  }

  /** Internal use. */
  unsigned GetVertexExAnchor(const TopElement& el, int vi)
  {
    return GetConcreteElement(el.GetHandle())->GetVertexExAnchor(vi);
  }
#endif
  
  /************************
  ** TopElement - Nodes 
  *************************/
  int GetNNodes(const TopElement& el) const
  {
    return NUM_N(el);
  }
  
  TopNode   GetNode(const TopElement& el, int i)
  {
    return GetNodeArray(el)[i];
  }

  /** Gets the node of the ith vertex-use. */
  TopNode GetVertexNode(const TopElement& el, int vi)
  {
    return GetNodeArray(el)[ V_N(el, vi) ];
  }
  
  /** 
    Returns whether the element's ni'th node is associated to a vertex-use. 
    True if the node is a corner one.
  */
  bool IsVertexNode(const TopElement& el, int ni)
  {
    return N_V(el, ni) >= 0;
  }

  /** 
    Returns whether the element's ni'th node is associated to an edge-use. 
    True if the node is a mid-side one.
  */
  bool IsEdgeNode(const TopElement& el, int ni)
  {
    return N_E(el, ni) >= 0;
  }

  /** 
    Returns the vertex-use which the element's ni'th node is associated to.
    True if the node is a corner one.
  */
  TopVertexUse GetNodeVertexUse(const TopElement& el, int ni) const 
  {
    int vi = N_V(el, ni);
    return (vi >= 0) ? TopVertexUse(el.GetHandle(), vi) : TopVertexUse();
  }

  /** 
    Returns the edge-use which the element's ni'th node is associated to.
    True if the node is a mid-side one.
  */
  TopEdgeUse GetNodeEdgeUse(const TopElement& el, int ni) const
  {
    int ei = N_E(el, ni);
    return (ei >= 0) ? TopEdgeUse(el.GetHandle(), ei) : TopEdgeUse();
  }

  /***********************
  ** TopFacetUse
  ************************/
  unsigned GetHandle(const TopFacetUse& f) const 
  { 
    return f.GetHandle(); 
  }
  unsigned GetLocalId(const TopFacetUse& f) const
  { 
    return f.GetLocalId(); 
  }
  /** Gets element type, defined in enum ElemType. */
  unsigned GetElemType(const TopFacetUse& f) const 
  { 
    return (unsigned) m_elem_types[f.GetElemType()]; 
  }
  unsigned GetElemPosId(const TopFacetUse& f) const 
  { 
    return f.GetElemPosId(); 
  }
  unsigned GetElemHandle(const TopFacetUse& f) const
  { 
    return f.GetElemHandle(); 
  }
  bool IsValid(const TopFacetUse& f) const
  { 
    return f.IsValid(); 
  }
  
  bool SetAttrib(const TopFacetUse& fu, void* attrib)
  {
    if (GetDimension(GetElem(fu)) == 2)
      return m_euatt_hash.Set(fu.GetHandle(), attrib);
    else
      return m_fuatt_hash.Set(fu.GetHandle(), attrib);
  }

  void* GetAttrib(const TopFacetUse& fu)
  {
    if (GetDimension(GetElem(fu)) == 2)
      return m_euatt_hash.Get(fu.GetHandle());
    else
      return m_fuatt_hash.Get(fu.GetHandle());
  }
  
  static TopElement GetElem(const TopFacetUse& fu)
  {
    assert(fu.IsValid());
    return TopElement(fu.GetElemHandle());
  }
 
  bool IsBoundary(const TopFacetUse& fu)
  {
    return !GetAdj(fu.GetElemHandle(), fu.GetLocalId()).IsValid();
  }

  /**
      Gets the corresponding facet-use of the element adjacent to the
    fi'th facet-use of the current element. If there is no adjacent element,
    it returns an invalid facet-use. 
      This method uses adjacency information stored in the data structure 
    to determine the mate facet-use.

    @see TopModel::UpdateAdj()
  */
  TopFacetUse GetMate(const TopFacetUse& fu) const
  {
    TopElement el  = GetElem(fu);
    TopElement adj = GetAdj(el, fu.GetLocalId());
    if (!adj.IsValid())
      return TopFacetUse();
  #ifdef TOP_USE_REV_ADJ
    return GetAdjArray(el)[fu.GetLocalId()];
  #else
    for (int i = 0; i < GetNFacets(adj); i++) {
      if (GetAdj(adj, i) == el)
        return TopFacetUse(adj.GetHandle(), i);
    }
    assert(0);
    return TopFacetUse();
  #endif
  }

#ifdef TOP_USE_NON_ORIENTED_IMPLICIT_ENTITIES    
  TopFacet GetFacet(const TopFacetUse& fu)
  {
    return GetFacet(GetElem(fu), fu.GetLocalId());
  }
#endif

  int GetNEdges(const TopFacetUse& fu) const
  { 
    return NUM_F_E(GetElem(fu), fu.GetLocalId()); 
  }

  TopEdgeUse GetEdgeUse(const TopFacetUse& fu, int ei) const
  { 
    return TopEdgeUse(fu.GetElemHandle(),
        F_E(GetElem(fu), fu.GetLocalId(), ei));
  }

#ifdef TOP_USE_NON_ORIENTED_IMPLICIT_ENTITIES    
  TopEdge GetEdge(const TopFacetUse& fu, int ei)
  {
    return GetEdge(GetElem(fu), GetEdgeUse(fu, ei).GetLocalId());
  }
#endif

  int GetNVertices(const TopFacetUse& fu) const
  { 
    return NUM_F_V(GetElem(fu), fu.GetLocalId()); 
  } 

  TopVertexUse GetVertexUse(const TopFacetUse& fu, int vi) const
  {
    return TopVertexUse(fu.GetElemHandle(), 
        F_V(GetElem(fu), fu.GetLocalId(), vi));
  }
  
#ifdef TOP_USE_NON_ORIENTED_IMPLICIT_ENTITIES    
  TopVertex GetVertex(const TopFacetUse& fu, int vi)
  {
    return GetVertex(GetElem(fu), GetVertexUse(fu, vi).GetLocalId());
  }
#endif
  
  int GetNNodes(const TopFacetUse& fu) const
  { 
    return NUM_F_N(GetElem(fu), fu.GetLocalId()); 
  }

  TopNode GetNode(const TopFacetUse& fu, int ni) const
  {
    return GetNodeArray(GetElem(fu))[
      F_N(GetElem(fu), fu.GetLocalId(), ni)];
  }

  unsigned GetNodeLocalId(const TopFacetUse& fu, int ni)
  {
    return F_N(GetElem(fu), fu.GetLocalId(), ni);
  }

  TopNode GetVertexNode(const TopFacetUse& fu, int vi)
  {
    return GetNodeArray(GetElem(fu))[
      V_N(GetElem(fu), F_V(GetElem(fu), fu.GetLocalId(), vi)) ];
  }

  unsigned GetVertexNodeLocalId(const TopFacetUse& fu, int vi)
  {
    return V_N(GetElem(fu), F_V(GetElem(fu), fu.GetLocalId(), vi));
  }

  /**
      Tests for facet-use matching, i.e., fu1 and fu2 must have the same nodes 
    and opposite orientations. Notice that this is the only requisite for
    this method. 
    
    @warning This may not work correctly if there are cohesive elements,
    as one of its uses can have the same node in the same orientation as 
    another element. Therefore, there may be two matching for the facet-use.

    @see GetMate()
    @see TopElement::GetFacetUseMate()
    @see TopModel::UpdateAdj()
    @see TopModel::InsertCohesiveElem(TopElement* el1, TopElement* el2)
  */
  bool Match(const TopFacetUse& fu1, const TopFacetUse& fu2);
  
  /**
      Tests whether two facet-uses have the same nodes and the same 
    orientations. Notice that this is the only requisite for
    this method. 
    
    @warning This may not work correctly if there are cohesive elements,
    as one of its uses can have the same node in the same orientation as 
    another element. Therefore, there may be two matching for the facet-use.

    @see GetMate()
    @see TopElement::GetFacetUseMate()
    @see TopModel::UpdateAdj()
    @see TopModel::InsertCohesiveElem(TopElement* el1, TopElement* el2)
  */
  bool MatchEqual(const TopFacetUse& fu1, const TopFacetUse& fu2);
  
  /**
      Tests whether two facet-uses have the same nodes and either the same 
    or reverse orientations.

    @see Match(TopFacetUse& fu1, TopFacetUse& fu2)
    @see MatchEqual(TopFacetUse& fu1, TopFacetUse& fu2)
  */
  bool MatchNodes(const TopFacetUse& fu1, const TopFacetUse& fu2);
  
  /**
      Checks whether the other facet-use has the same vertices as the
    current one. 
  */
  bool CompareVertices(const TopFacetUse& fu1, const TopFacetUse& fu2);

  /***********************
  ** TopFaceUse
  ************************/
  unsigned GetHandle(const TopFaceUse& f) const 
  { 
    return f.GetHandle(); 
  }

  unsigned GetLocalId(const TopFaceUse& f) const
  { 
    return f.GetLocalId(); 
  }

  /** Gets element type, defined in enum ElemType. */
  unsigned GetElemType(const TopFaceUse& f) const 
  { 
    return (unsigned) m_elem_types[f.GetElemType()]; 
  }

  unsigned GetElemPosId(const TopFaceUse& f) const 
  { 
    return f.GetElemPosId(); 
  }

  unsigned GetElemHandle(const TopFaceUse& f) const
  { 
    return f.GetElemHandle(); 
  }

  bool IsValid(const TopFaceUse& f) const
  { 
    return f.IsValid(); 
  }
  
  bool SetAttrib(const TopFaceUse& fu, void* attrib)
  {
    return m_fuatt_hash.Set(fu.GetHandle(), attrib);
  }

  void* GetAttrib(const TopFaceUse& fu) 
  {
    return m_fuatt_hash.Get(fu.GetHandle());
  }
  
  static TopElement GetElem(const TopFaceUse& fu) 
  {
    return TopElement(fu.GetElemHandle());
  }
 
  bool IsBoundary(const TopFaceUse& fu)
  {
    if (GetDimension(GetElem(fu)) == 2)
      return true;
    else
      return IsBoundary(TopFacetUse(fu.GetHandle()));
  }

#ifdef TOP_USE_NON_ORIENTED_IMPLICIT_ENTITIES    
  TopFace GetFace(const TopFaceUse& fu) 
  {    
    return GetFace(GetElem(fu), fu.GetLocalId());
  }
#endif

  int GetNEdges(const TopFaceUse& fu) const
  { 
    return NUM_FC_E(GetElem(fu), fu.GetLocalId()); 
  }

  TopEdgeUse GetEdgeUse(const TopFaceUse& fu, int ei) const
  { 
    return TopEdgeUse(fu.GetElemHandle(),
        FC_E(GetElem(fu), fu.GetLocalId(), ei));
  }

#ifdef TOP_USE_NON_ORIENTED_IMPLICIT_ENTITIES    
  TopEdge GetEdge(const TopFaceUse& fu, int ei)
  {
    return GetEdge(GetElem(fu), GetEdgeUse(fu, ei).GetLocalId());
  }
#endif

  int GetNVertices(const TopFaceUse& fu) const
  { 
    return NUM_FC_V(GetElem(fu), fu.GetLocalId()); 
  } 

  TopVertexUse GetVertexUse(const TopFaceUse& fu, int vi) const
  {
    return TopVertexUse(fu.GetElemHandle(), 
        FC_V(GetElem(fu), fu.GetLocalId(), vi));
  }
 
#ifdef TOP_USE_NON_ORIENTED_IMPLICIT_ENTITIES    
  TopVertex GetVertex(const TopFaceUse& fu, int vi) 
  {
    return GetVertex(GetElem(fu), GetVertexUse(fu, vi).GetLocalId());
  }
#endif
  
  int GetNNodes(const TopFaceUse& fu) const
  { 
    return NUM_FC_N(GetElem(fu), fu.GetLocalId()); 
  }

  TopNode GetNode(const TopFaceUse& fu, int ni) const
  {
    return GetNodeArray(GetElem(fu))[
      FC_N(GetElem(fu), fu.GetLocalId(), ni)];
  }

  unsigned GetNodeLocalId(const TopFaceUse& fu, int ni)
  {
    return FC_N(GetElem(fu), fu.GetLocalId(), ni);
  }

  TopNode GetVertexNode(const TopFaceUse& fu, int vi)
  {
    return GetNodeArray(GetElem(fu))[
      V_N(GetElem(fu), FC_V(GetElem(fu), fu.GetLocalId(), vi)) ];
  }

  unsigned GetVertexNodeLocalId(const TopFaceUse& fu, int vi)
  {
    return V_N(GetElem(fu), FC_V(GetElem(fu), fu.GetLocalId(), vi));
  }

  TopFaceUse GetMate(const TopFaceUse& fu)
  {
    TopElement el = GetElem(fu);
    TopElement adj = GetAdj(el, fu.GetLocalId());
    if (GetDimension(el) <= 2 || !adj.IsValid())
      return TopFaceUse();
  #ifdef TOP_USE_REV_ADJ
    return TopFaceUse((GetAdjArray(el)[fu.GetLocalId()]).GetHandle());
  #else
    for (int i = 0; i < GetNFaces(adj); i++) {
      if (GetAdj(adj, i) == el)
        return TopFaceUse(adj.GetHandle(), i);
    }
    assert(0);
    return TopFaceUse();
  #endif
  }

  /***********************
  ** TopEdgeUse
  ************************/
  unsigned GetHandle(const TopEdgeUse& f) const
  { 
    return f.GetHandle(); 
  }
  unsigned GetLocalId(const TopEdgeUse& f) const
  { 
    return f.GetLocalId(); 
  }
  /** Gets element type, defined in enum ElemType. */
  unsigned GetElemType(const TopEdgeUse& f) const
  { 
    return (unsigned) m_elem_types[f.GetElemType()]; 
  }
  unsigned GetElemPosId(const TopEdgeUse& f) const
  { 
    return f.GetElemPosId(); 
  }
  unsigned GetElemHandle(const TopEdgeUse& f) const
  { 
    return f.GetElemHandle(); 
  }
  bool IsValid(const TopEdgeUse& f) const
  { 
    return f.IsValid(); 
  }
  
  bool SetAttrib(const TopEdgeUse& eu, void* attrib)
  {
    return m_euatt_hash.Set(eu.GetHandle(), attrib);
  }

  void* GetAttrib(const TopEdgeUse& eu)
  {
    return m_euatt_hash.Get(eu.GetHandle());
  }
  
  static TopElement GetElem(const TopEdgeUse& eu)
  {
    return TopElement(eu.GetElemHandle());
  }
  
  /**
      An edge-use is on model's boundary if at least one of the two incident 
    facet-uses of its element is on boundary.
    It does not guarantee, however, that the edge is on the model's boundary.
  */
  bool IsBoundary(const TopEdgeUse& eu)
  {
    return (IsBoundary(GetFacetUse(eu, 0)) || IsBoundary(GetFacetUse(eu, 1)));
  }
  
  /**
      Gets the number of element's facet-uses incident to the ei'th edge-use.
    In general, the number of edge-use's incident facet-uses is:
      - 2 for 3D non-cohesive elements, or
      - 1 for cohesive elements or 2D non-cohesive elements.
  */
  int GetNFacets(const TopEdgeUse& eu) const
  {
    return NUM_E_F(GetElem(eu), eu.GetLocalId()); 
  }
  
  /**
      Gets the i'th facet-use incident to the ei'th edge-use of the element. 
    By convention, we have: 0: "left" and 1: "right". The "left" one 
    corresponds to the facet-use with the same local orientation of the 
    edge-use, while the "right" one corresponds to the facet-use with opposite 
    local orientation.
  */
  TopFacetUse GetFacetUse(const TopEdgeUse& eu, int i) const
  {
    return TopFacetUse(eu.GetElemHandle(), 
        E_F(GetElem(eu), eu.GetLocalId(), i));  
  }

  int GetNFaces(const TopEdgeUse& eu) const
  {
    return NUM_E_FC(GetElem(eu), eu.GetLocalId()); 
  }

  TopFaceUse GetFaceUse(const TopEdgeUse& eu, int i)
  {
    return TopFaceUse(eu.GetElemHandle(), 
        E_FC(GetElem(eu), eu.GetLocalId(), i));  
  }

#ifdef TOP_USE_NON_ORIENTED_IMPLICIT_ENTITIES    
  TopEdge GetEdge(const TopEdgeUse& eu)
  {
    return GetEdge(GetElem(eu), eu.GetLocalId());
  }
#endif
  
  /**
      Gets the corresponding edge-use of the element adjacent to the
    i'th facet-use adjacent to the ei'th edge of the current element. If there 
    is no adjacent element, it returns an invalid edge-use. 
      This method uses adjacency information stored in the data structure 
    to determine the mate edge-use.

    @param i 0: left, 1: right.
    
    @see TopModel::UpdateAdj()
  */
  TOPS_FORCE_INLINE TopEdgeUse GetMate(const TopEdgeUse& eu, int i) const
  {
    TopElement el = GetElem(eu);
    int ei = eu.GetLocalId();
    int fi = E_F(el, ei, i);
    #ifdef TOP_USE_REV_ADJ
    TopFacetUse fum = GetAdjFacetUse(el, fi);
    #else
    TopFacetUse fum = GetMate(GetFacetUse(el, fi));
    #endif
    if (!fum.IsValid())
      return TopEdgeUse();
    for (int i = 0; i < GetNEdges(fum); i++) {
      TopEdgeUse eum = GetEdgeUse(fum, i);
      if (CompareVertices(eu, eum))
        return eum;
    }
    return TopEdgeUse();
  }

  TopVertexUse GetVertexUse(const TopEdgeUse& eu, int vi)
  {
    return TopVertexUse(eu.GetElemHandle(), 
        E_V(GetElem(eu), eu.GetLocalId(), vi));
  }

#ifdef TOP_USE_NON_ORIENTED_IMPLICIT_ENTITIES    
  TopVertex GetVertex(const TopEdgeUse& eu, int vi)
  {
    return GetVertex(GetElem(eu), GetVertexUse(eu, vi).GetLocalId());
  }
#endif
  
  int GetNNodes(const TopEdgeUse& eu) const
  { 
    return NUM_E_N(GetElem(eu), eu.GetLocalId()); 
  }

  TopNode GetNode(const TopEdgeUse& eu, int ni) const
  {
    return GetNodeArray(GetElem(eu))[
      E_N(GetElem(eu), eu.GetLocalId(), ni)]; 
  }

  unsigned GetNodeLocalId(const TopEdgeUse& eu, int ni)
  {
    return E_N(GetElem(eu), eu.GetLocalId(), ni);
  }

  TopNode GetVertexNode(const TopEdgeUse& eu, int vi) const
  {
    return GetNodeArray(GetElem(eu))[
        V_N(GetElem(eu), E_V(GetElem(eu), eu.GetLocalId(), vi))];
  }

  unsigned GetVertexNodeLocalId(const TopEdgeUse& eu, int vi)
  {
    return V_N(GetElem(eu), E_V(GetElem(eu), eu.GetLocalId(), vi));
  }

  bool MatchNodes(const TopEdgeUse& eu1, const TopEdgeUse& eu2);
  
  bool CompareVertices(const TopEdgeUse& eu1, const TopEdgeUse& eu2) const;
  
  /***********************
  ** TopVertexUse
  ************************/
  unsigned GetHandle(const TopVertexUse& f) const 
  { 
    return f.GetHandle(); 
  }
  unsigned GetLocalId(const TopVertexUse& f) const
  { 
    return f.GetLocalId(); 
  }
  unsigned GetNodeLocalId(const TopVertexUse& vu) const
  {
    return V_N(GetElem(vu), vu.GetLocalId());
  }
  /** Gets element type, defined in enum ElemType. */
  unsigned GetElemType(const TopVertexUse& f)  const
  { 
    return (unsigned) m_elem_types[f.GetElemType()]; 
  }
  unsigned GetElemPosId(const TopVertexUse& f) const 
  { 
    return f.GetElemPosId(); 
  }
  unsigned GetElemHandle(const TopVertexUse& f) const
  { 
    return f.GetElemHandle(); 
  }
  bool IsValid(const TopVertexUse& f) const 
  { 
    return f.IsValid(); 
  }
  
  bool SetAttrib(const TopVertexUse& vu, void* attrib)
  {
    return m_vuatt_hash.Set(vu.GetHandle(), attrib);
  }

  void* GetAttrib(const TopVertexUse& vu)
  {
    return m_vuatt_hash.Get(vu.GetHandle());
  }

  static TopElement GetElem(const TopVertexUse& vu)
  {
    return TopElement(vu.GetElemHandle());
  }
  
  bool IsBoundary(const TopVertexUse& vu)
  {
    for (int i = 0; i < GetNFacets(vu); i++) 
      if (IsBoundary(GetFacetUse(vu, i)))
        return true;
    return false;
  }
  
  int  GetNFacets(const TopVertexUse& vu) const
  {
    return NUM_V_F(GetElem(vu), vu.GetLocalId());
  }

  TopFacetUse GetFacetUse(const TopVertexUse& vu, int i) const
  {
    return TopFacetUse(vu.GetElemHandle(), 
        V_F(GetElem(vu), vu.GetLocalId(), i));
  }

  int  GetNFaces(const TopVertexUse& vu) const
  {
    return NUM_V_FC(GetElem(vu), vu.GetLocalId());
  }

  TopFaceUse GetFaceUse(const TopVertexUse& vu, int i) const
  {
    return TopFaceUse(vu.GetElemHandle(), 
        V_FC(GetElem(vu), vu.GetLocalId(), i));
  }

  int  GetNEdges(const TopVertexUse& vu) const
  {
    return NUM_V_E(GetElem(vu), vu.GetLocalId());
  }

  TopEdgeUse GetEdgeUse(const TopVertexUse& vu, int ei) const
  {
    return TopEdgeUse(vu.GetElemHandle(), 
        V_E(GetElem(vu), vu.GetLocalId(), ei));
  }

  /**
      Gets the corresponding vertex-use of the element adjacent to the
    i'th facet-use adjacent to the vi'th vertex of the current element. 
    If there is no adjacent element, it returns an invalid vertex-use. 
      This method uses adjacency information stored in the data structure 
    to determine the mate vertex-use.

    @see TopVertexUse
    @see TopModel::UpdateAdj()
  */
  TOPS_FORCE_INLINE TopVertexUse GetMate(const TopVertexUse& vu, int i) const
  {
    TopElement el = GetElem(vu);
    int vi = vu.GetLocalId();
    int fi = V_F(el, vi, i);
    #ifdef TOP_USE_REV_ADJ
    TopFacetUse fum = GetAdjFacetUse(el, fi);
    #else
    TopFacetUse fum = GetMate(GetFacetUse(el, fi));
    #endif
    if (!fum.IsValid())
      return TopVertexUse();
    for (int i = 0; i < GetNVertices(fum); i++) {
      TopVertexUse vum = GetVertexUse(fum, i);
      if (GetNode(vum) == GetNode(vu)) 
        return vum;
    }
    return TopVertexUse();
  }

#ifdef TOP_USE_NON_ORIENTED_IMPLICIT_ENTITIES    
  TopVertex GetVertex(const TopVertexUse& vu)
  {
    return GetVertex(GetElem(vu), vu.GetLocalId());
  }
#endif

  TopNode GetNode(const TopVertexUse& vu) const
  {
    return GetNodeArray(GetElem(vu))[
        V_N(GetElem(vu), vu.GetLocalId())];
  }

  
#ifdef TOP_USE_NON_ORIENTED_IMPLICIT_ENTITIES    
  /***********************
    TopFacet
  ************************/
  unsigned GetHandle(const TopFacet& f) 
  { 
#ifdef TOP_IMPLICIT_ENTITY_MANAGEMENT
    return FindHandle(f);
#else
    return f.GetRawHandle();
#endif
  }

  unsigned GetRawHandle(const TopFacet& f) const { return f.GetRawHandle(); }

  bool IsValid(const TopFacet& f) const { return f.IsValid(); } 

  /**
      Adds a lock for the given facet. The lock prevents the facet attribute of
    being lost after model edition.
  */
  void AddLock(const TopFacet& f)
  {
  #ifdef TOP_IMPLICIT_ENTITY_MANAGEMENT    
    if (GetDimension(GetElem(f)) == 2)
      IncEdgeRefCount(f.GetRawHandle());
    else
      IncFaceRefCount(f.GetRawHandle());
  #endif
  }

  /** Returns the lock counter of the facet. */ 
  int GetLock(const TopFacet& f)
  {
  #ifdef TOP_IMPLICIT_ENTITY_MANAGEMENT   
    if (GetDimension(GetElem(f)) == 2)
      return GetEdgeRefCount(f.GetRawHandle());
    else
      return GetFaceRefCount(f.GetRawHandle());
  #else
    return 0;
  #endif
  }

  /** Removes a lock for the given facet. */
  void RemLock(const TopFacet& f)
  {
  #ifdef TOP_IMPLICIT_ENTITY_MANAGEMENT   
    if (GetDimension(GetElem(f)) == 2)
      return DecEdgeRefCount(f.GetRawHandle());
    else
      return DecFaceRefCount(f.GetRawHandle());
  #endif
  }

  /** Clears all the locks for the given facet. */
  void ResetLock(const TopFacet& f)
  {
  #ifdef TOP_IMPLICIT_ENTITY_MANAGEMENT   
    if (GetDimension(GetElem(f)) == 2)
      return ClearEdgeRefCount(f.GetRawHandle());
    else
      return ClearFaceRefCount(f.GetRawHandle());
  #endif
  }

  TopFacetUse  GetFacetUse(const TopFacet& f, int i =0)
  {
  #ifdef TOP_IMPLICIT_ENTITY_MANAGEMENT     
    TopFacetUse fu(f.GetRawHandle());
    if (i == 1) fu = GetMate(fu);
    return TopFacetUse(GetFacetMap(fu.GetHandle()));
  #else
    TopFacetUse fu(f.GetRawHandle());
    return (i == 0) ? fu : GetMate(fu);
  #endif
  }

  bool SetAttrib(const TopFacet& f, void* attrib)
  {
    if (GetDimension(GetElem(f)) == 2)
      return m_eatt_hash.Set(GetFacetUse(f).GetHandle(), attrib);
    else
      return m_fatt_hash.Set(GetFacetUse(f).GetHandle(), attrib);
  }

  void* GetAttrib(const TopFacet& f)
  {
    if (GetDimension(GetElem(f)) == 2)
      return m_eatt_hash.Get(GetFacetUse(f).GetHandle());
    else
      return m_fatt_hash.Get(GetFacetUse(f).GetHandle());
  }

  /** Gets one of the two possible elements using the facet. */
  TopElement  GetElem(const TopFacet& f, int i =0)
  {
    if (i == 0) {
      return GetElem(GetFacetUse(f));
    } else {
      TopFacetUse fum = GetMate(GetFacetUse(f));
      if (fum.IsValid())
        return GetElem(fum);
      else
        return TopElement();
    }
  }

  /**
      Returns whether the facet is on the model's boundary or not.
    @see TopFacetUse::IsBoundary()
  */
  bool         IsBoundary(const TopFacet& f)
  {
    return IsBoundary(GetFacetUse(f)) || IsBoundary(GetMate(GetFacetUse(f)));
  }
  
  /* Edge */
  int          GetNEdges(const TopFacet& f)
  {
    return GetNEdges(GetFacetUse(f));
  }

  TopEdge      GetEdge(const TopFacet& f, int i)
  {
    return GetEdge(GetFacetUse(f), i);
  }
  
  /* Vertex */
  int          GetNVertices(const TopFacet& f)
  {
    return GetNVertices(GetFacetUse(f));
  }
  
  TopVertex    GetVertex(const TopFacet& f, int i)
  {
    return GetVertex(GetFacetUse(f), i);
  }

  /* Node */
  int          GetNNodes(const TopFacet& f)
  {
    return GetNNodes(GetFacetUse(f));
  }
  
  TopNode     GetNode(const TopFacet& f, int i)
  {
    return GetNode(GetFacetUse(f), i);
  }

  /***********************
    TopFace
  ************************/
  unsigned GetHandle(const TopFace& f) 
  { 
#ifdef TOP_IMPLICIT_ENTITY_MANAGEMENT
    return FindHandle(f);
#else
    return f.GetRawHandle();
#endif
  }
  unsigned GetRawHandle(const TopFace& f) const { return f.GetRawHandle(); }
  bool IsValid(const TopFace& f) const { return f.IsValid(); } 

  /**
      Adds a lock for the given facet. The lock prevents the facet attribute of
    being lost after model edition.
  */
  void AddLock(const TopFace& f)
  {
  #ifdef TOP_IMPLICIT_ENTITY_MANAGEMENT    
    IncFaceRefCount(f.GetRawHandle());
  #endif
  }

  /** Returns the lock counter of the facet. */ 
  int GetLock(const TopFace& f)
  {
  #ifdef TOP_IMPLICIT_ENTITY_MANAGEMENT    
    return GetFaceRefCount(f.GetRawHandle());
  #else
    return 0;
  #endif
  }

  /** Removes a lock for the given facet. */
  void RemLock(const TopFace& f)
  {
  #ifdef TOP_IMPLICIT_ENTITY_MANAGEMENT    
    DecFaceRefCount(f.GetRawHandle());
  #endif
  }

  /** Clears all the locks for the given facet. */
  void ResetLock(const TopFace& f)
  {
  #ifdef TOP_IMPLICIT_ENTITY_MANAGEMENT    
    ClearFaceRefCount(f.GetRawHandle());
  #endif
  }

  TopFaceUse  GetFaceUse(const TopFace& f, int i =0)
  {
  #ifdef TOP_IMPLICIT_ENTITY_MANAGEMENT
    TopFaceUse fu(f.GetRawHandle());
    if (i == 1) fu = GetMate(fu);
    return TopFaceUse(GetFaceMap(fu.GetHandle()));
  #else
    TopFaceUse fu(f.GetRawHandle());
    return (i == 0) ? fu : GetMate(fu);
  #endif
  }

  bool SetAttrib(const TopFace& f, void* attrib)
  {
    return m_fatt_hash.Set(GetFaceUse(f).GetHandle(), attrib);
  }

  void* GetAttrib(const TopFace& f)
  {
    return m_fatt_hash.Get(GetFaceUse(f).GetHandle());
  }

  /** Gets one of the two possible elements using the facet. */
  TopElement  GetElem(const TopFace& f, int i =0)
  {
    if (i == 0) {
      return GetElem(GetFaceUse(f));
    } else {
      TopFaceUse fum = GetMate(GetFaceUse(f));
      if (fum.IsValid())
        return GetElem(fum);
      else
        return TopElement();
    }
  }

  /**
      Returns whether the facet is on the model's boundary or not.
    @see TopFaceUse::IsBoundary()
  */
  bool         IsBoundary(const TopFace& f)
  {
    return IsBoundary(GetFaceUse(f)) || IsBoundary(GetMate(GetFaceUse(f)));
  }
  
  /* Edge */
  int          GetNEdges(const TopFace& f)
  {
    return GetNEdges(GetFaceUse(f));
  }

  TopEdge      GetEdge(const TopFace& f, int i)
  {
    return GetEdge(GetFaceUse(f), i);
  }
  
  /* Vertex */
  int          GetNVertices(const TopFace& f)
  {
    return GetNVertices(GetFaceUse(f));
  }
  
  TopVertex    GetVertex(const TopFace& f, int i)
  {
    return GetVertex(GetFaceUse(f), i);
  }

  /* Node */
  int          GetNNodes(const TopFace& f)
  {
    return GetNNodes(GetFaceUse(f));
  }
  
  TopNode     GetNode(const TopFace& f, int i)
  {
    return GetNode(GetFaceUse(f), i);
  }

  /***********************
    TopEdge
  ************************/
  unsigned GetHandle(const TopEdge& e) 
  { 
#ifdef TOP_IMPLICIT_ENTITY_MANAGEMENT
    return FindHandle(e);
#else
    return e.GetRawHandle();
#endif
  }
  unsigned GetRawHandle(const TopEdge& e) const { return e.GetRawHandle(); }
  bool IsValid(const TopEdge& e) const { return e.IsValid(); }
  
  void AddLock(const TopEdge& e)
  {
  #ifdef TOP_IMPLICIT_ENTITY_MANAGEMENT    
    IncEdgeRefCount(e.GetRawHandle());
  #endif
  }

  int GetLock(const TopEdge& e)
  {
#ifdef TOP_IMPLICIT_ENTITY_MANAGEMENT    
    return GetEdgeRefCount(e.GetRawHandle());
#else
    return 0;
#endif
  }

  void RemLock(const TopEdge& e)
  {
  #ifdef TOP_IMPLICIT_ENTITY_MANAGEMENT    
    DecEdgeRefCount(e.GetRawHandle());
  #endif
  }

  void ResetLock(const TopEdge& e)
  {
  #ifdef TOP_IMPLICIT_ENTITY_MANAGEMENT    
    ClearEdgeRefCount(e.GetRawHandle());
  #endif
  }
  
  TopEdgeUse   GetEdgeUse(const TopEdge& e)
  {
  #ifdef TOP_IMPLICIT_ENTITY_MANAGEMENT
    return TopEdgeUse(GetEdgeMap(e.GetRawHandle()));
  #else
    return TopEdgeUse(e.GetRawHandle());
  #endif
  }
  
  bool SetAttrib(const TopEdge& e, void* attrib)
  {
    return m_eatt_hash.Set(GetEdgeUse(e).GetHandle(), attrib);
  }

  void* GetAttrib(const TopEdge& e)
  {
    return m_eatt_hash.Get(GetEdgeUse(e).GetHandle());
  }
  
  TopElement  GetElem(const TopEdge& e)  
  { 
    return GetElem(GetEdgeUse(e)); 
  }
 
  /**
      An edge is on the model's boundary if one of its uses is on the boundary.
    @see TopEdgeUse::IsBoundary()
  */
  bool         IsBoundary(const TopEdge& e); 

  /* Vertex */
  TopVertex    GetVertex(const TopEdge& e, int i)
  {
    return GetVertex(GetEdgeUse(e), i);
  }
  
  /* Node */
  int      GetNNodes(const TopEdge& e)
  {
    return GetNNodes(GetEdgeUse(e));
  }

  TopNode GetNode(const TopEdge& e,int i)
  {
    return GetNode(GetEdgeUse(e), i);
  }

  /**
     Returns the a node of the oriented edge, corresponding to one of its
   two vertex. It's not necessarily a node of the element in the edge.
  */
  TopNode GetVertexNode(const TopEdge& e, int i)
  {
    return GetVertexNode(GetEdgeUse(e), i);
  }
 
  
  /***********************
    TopVertex
  ************************/
  unsigned GetHandle(const TopVertex& v) 
  { 
#ifdef TOP_IMPLICIT_ENTITY_MANAGEMENT
    return FindHandle(v);
#else
    return v.GetRawHandle();
#endif
  }
  unsigned GetRawHandle(const TopVertex& v) const { return v.GetRawHandle(); }
  bool IsValid(const TopVertex& v) const { return v.IsValid(); }
  
  void AddLock(const TopVertex& v)
  {
  #ifdef TOP_IMPLICIT_ENTITY_MANAGEMENT    
    IncVertexRefCount(v.GetRawHandle());
  #endif
  }

  int GetLock(const TopVertex& v)
  {
#ifdef TOP_IMPLICIT_ENTITY_MANAGEMENT    
    return GetVertexRefCount(v.GetRawHandle());
#else
    return 0;
#endif
  }

  void RemLock(const TopVertex& v)
  {
  #ifdef TOP_IMPLICIT_ENTITY_MANAGEMENT    
    DecVertexRefCount(v.GetRawHandle());
  #endif
  }
  
  void ResetLock(const TopVertex& v)
  {
  #ifdef TOP_IMPLICIT_ENTITY_MANAGEMENT    
    ClearVertexRefCount(v.GetRawHandle());
  #endif
  }
  
  TopVertexUse GetVertexUse(const TopVertex& v)
  {
  #ifdef TOP_IMPLICIT_ENTITY_MANAGEMENT
    return TopVertexUse(GetVertexMap(v.GetRawHandle()));
  #else
    return TopVertexUse(v.GetRawHandle());
  #endif
  }
  
  bool SetAttrib(const TopVertex& v, void* attrib)
  {
    return m_vatt_hash.Set(GetVertexUse(v).GetHandle(), attrib);
  }

  void* GetAttrib(const TopVertex& v)
  {
    return m_vatt_hash.Get(GetVertexUse(v).GetHandle());
  }
  
  TopElement GetElem(const TopVertex& v)      
  { 
    return GetElem(GetVertexUse(v)); 
  }

  /**
      A vertex is on the model's boundary if one of its uses is on the boundary.
    @see TopVertexUse::IsBoundary()
  */
  bool IsBoundary(const TopVertex& v);
  
  TopNode GetNode(const TopVertex& v) 
  { 
    return GetNode(GetVertexUse(v)); 
  }
#endif  

  /**
    Creates adjacency information for the elements in the model, after
    all the elements have been inserted using InsertElem() (or InsertElemAtPosId(), 
    as appropriate) with parameter "update_adj" set to "false" (see InsertElem()).
    The advantage of using this method is that it tends to compute adjacency 
    information faster than when elements are inserted with "update_adj" 
    equals "true".
    
    Note that EVERY element must have been inserted using InsertElem() 
    (or InsertElemAt()) with "update_adj" set to "false", and the final mesh
    MUST be manifold. Otherwhise the adjacencies are not guaranteed to 
    be computed correctly. Currently, this method can only be invoked once,
    after all the elements of the mesh have been inserted (the mesh may be 
    modified later, though, by using the provided operators).
   
    The method works as follows: the list of elements is traversed and, for each
    element in the list, check if it has facet-uses with no adjacent elements. 
    If true, search the model for matching facet-uses from other elements. 
    If a mate facet-use is found, then set the two corresponding elements to be
    mutually adjacent. Edge and vertex anchors, which are used to uniquely
    identify the corresponding entities in the model, are updated accordingly.
    
    Two facet-uses match if and only if they have the same 
    nodes but in opposite orientations. Therefore, "n10 n20 n30" would match
    "n30 n20 n10" or "n20 n10 n30", for example. This "GetMate" procedure is 
    different from GetMate(TopFacetUse), since adjacency information cannot 
    be used at this time.
  */
  void UpdateAdj ();

  /**
    Creates adjacency information for the elements in a reservoir model, after
    all the elements have been inserted using InsertElem() (or InsertElemAtPosId(), 
    as appropriate) with parameter "update_adj" set to "false" (see InsertElem()).

    This method is equivalent to UpdateAdj(), but it is optimized for 
    reservoir models. See UpdateAdj() for details.
  */
  void UpdateAdjReservoir ();

  /***********************
     Iterators 
  ************************/
  class ElemItr;
  class NodeItr;
  class FacetItr;
  class FaceItr;
  class EdgeItr;
  class VertexItr;
  class EdgeUseItr;
  class EdgeElemItr;
  class EdgeFacetItr;
  class VertexUseItr;
  class VertexElemItr;
  class VertexFacetItr;
  class VertexEdgeItr;
  class NodeElemItr;

  /*****************************************************
     Experimental (may be removed in the future)
  ******************************************************/
  /** Internal use only */
  TopConcreteElement* GetConcreteElement(const TopElement& el) const
  {
    return GetConcreteElement(el.GetType(), el.GetPosId());
  }

  /** Internal use only */
  void RemElemDisconnect(const TopElement& el);

  /** Internal use only */
  void RemElemFree(const TopElement& el);


  /**
    Converts this model into a manifold one by splitting the non-manifold
    nodes in the mesh and updating anchors of implicit entities. 
    Warning: This method does not support automatic handling of implicit
    entities. As entity anchors are recomputed, handles of implicit entities 
    and references for assigned attributes may become invalid. Hence, 
    this method should be invoked before any attribute is assigned to
    implicit entities.
  */
  void ConvertIntoManifold();

  /**
      Temporarly disconnects an element from the model.
  */
  void UnlinkElem(const TopElement& el);

  /**
      Reconnects a temporarly disconnected element to the model.
  */
  void RelinkElem(const TopElement& el);

  void ReplaceVertexNode(TopVertexUse vu, TopNode newnode);

  /**
      Collapses an edge to a new node, which can be one of the edge's nodes
    or another one given by the user.
      Elements adjacent to the collapsed edge will be removed from the model 
    and the ones incident to the edge's vertices may be modified to include the
    new given node.
      This method does not create or remove any nodes and notifies of the 
    following events just before executing the respective operations: 

    Events:
      - RemoveElem(el)
          el: element adjacent to the edge that will be removed. 
      - JoinFacet(f1, f2) 
          f1, f2: if newnode is one of the two vertex nodes of the edge, 
          f1 is the removed facet and f2 is the remaining facet, else
          both f1 and f2 are removed.
      - ReplaceElemNode(el, ni, node, newnode)
          el: element which will have a node replaced by newnode.
          ni: local id of the replaced node in the element.
          node: replaced node.
          newnode: new node.

      Currently, only T3 and TET4 meshes are supported and the following 
    assumptions must be ensured by the user:
      - resulting mesh is manifold;
      - no entities are locked, as locks are not currently supported;
      - elements cannot have two facets adjacent to the same element or
      be adjacent to themselves;
      - no zero area (or volume) elements are generated;  
      Attributes associated to the entities will not preserved.
    @see TopModelEditListener
  */
  void CollapseEdge(TopEdgeUse collapsing_eu, TopNode newnode);

  /**
    Returns whether a collapse of the given edge will result in a valid 
    (i.e., manifold) mesh.
    Currently, only T3, T6, TET4 and TET10 elements are supported.
  */
  bool IsEdgeCollapseValid(TopEdgeUse collapsing_eu);
  
  /** DEPRECATED */
  const TopArray<TopModelEditListener*>* GetEditListeners () 
  {
    return m_edit_notifier.GetEditListeners();
  }

  void AddEditListener(TopModelEditListener* l)
  {
    m_edit_notifier.AddEditListener(l);
  }

  void RemEditListener(TopModelEditListener* l)
  {
    m_edit_notifier.RemoveEditListener(l);
  }

  /**
   * Includes a node attribute array.
   * Each attribute has size 'sizeof_attrib'.
   * If desired, initial values for this array can be passed: 'count' values
   * will be copied from 'data'.
   * If desired, an attribute initialization function can be passed:
   * it will be called whenever a new node is allocated, hence requiring
   * the initialization of its associated attribute.
   *
   * Note: passing both the initialization callback and the
   * source data is not currently supported.
   */
  int AddNodeAttribArray (int sizeof_attrib,
                          int count = 0,
                          void* data = 0,
                          InitAttribCB initcb = NULL);

  void RemNodeAttribArray(int id);

  void* GetNodeAttribArray(int id) 
  { 
    return m_node_attrib_arrays.GetPtr(id)->v; 
  }

  void* GetNodeAttrib(TopNode node, int attrib_id)
  {
    AttribArray* att = m_node_attrib_arrays.GetPtr(attrib_id);
    assert(node.IsValid());
    assert(node.GetPosId() >= 0U && node.GetPosId() < (unsigned) att->currn);
    return &(((unsigned char*) att->v)[att->size * node.GetPosId()]); 
  }

  /**
   * Includes an element attribute array.
   * Each attribute has size 'sizeof_attrib'.
   * If desired, initial values for this array can be passed: 'count' values
   * will be copied from 'data'.
   * If desired, an attribute initialization function can be passed:
   * it will be called whenever a new element is allocated, hence requiring
   * the initialization of its associated attribute.
   *
   * Note: passing both the initialization callback and the
   * source data is not currently supported.
   */
  int AddElemAttribArray (int el_type,
                          int sizeof_attrib,
                          int count = 0,
                          void* data = 0,
                          InitAttribCB initcb = NULL);

  void RemElemAttribArray(int el_type, int attrib_id);

  void* GetElemAttribArray(int el_type, int attrib_id) 
  { 
    AttribArray* att = m_elem_attrib_arrays[el_type].GetPtr(attrib_id);
    return att->v; 
  }

  void* GetElemAttrib(TopElement el, int attrib_id) 
  { 
    AttribArray* att = m_elem_attrib_arrays[el.GetType()].GetPtr(attrib_id);
    return &(((unsigned char*) att->v)[att->size * el.GetPosId()]); 
  }

  /********************
    Dense attributes
  *********************/
//TODO Serialization
  int CreateNodeDenseAttrib(int sizeof_attrib, const char* name = NULL);

  void DestroyNodeDenseAttrib(int id);

  TopNodeDenseAttrib* GetNodeDenseAttrib(int id)
  {
    return m_node_dense_attribs[NODE_LOCAL].Get(id);
  }

  int CreateElemDenseAttrib(int elemtype, int sizeof_attrib, const char* name = NULL);

  void DestroyElemDenseAttrib(int elemtype, int id);

  TopElementDenseAttrib* GetElemDenseAttrib(int elemtype, int id)
  {
    return m_elem_dense_attribs[m_internal_elem_types[elemtype]].Get(id);
  }

  /********************
    Sparse attributes
  *********************/
//TODO Serialization
  int CreateNodeSparseAttrib(int sizeof_attrib, const char* name = NULL);

  void DestroyNodeSparseAttrib(int id);

  TopNodeSparseAttrib* GetNodeSparseAttrib(int id)
  {
    return m_node_sparse_attribs[NODE_LOCAL].Get(id);
  }

  int CreateElemSparseAttrib(int elemtype, int sizeof_attrib, const char* name = NULL);

  void DestroyElemSparseAttrib(int elemtype, int id);

  TopElementSparseAttrib* GetElemSparseAttrib(int elemtype, int id)
  {
    return m_elem_sparse_attribs[m_internal_elem_types[elemtype]].Get(id);
  }

  int CreateFacetSparseAttrib(int sizeof_attrib, const char* name = NULL);

  void DestroyFacetSparseAttrib(int id);

  TopFacetSparseAttrib* GetFacetSparseAttrib(int id)
  {
    return m_facet_sparse_attribs.Get(id);
  }

  int CreateFaceSparseAttrib(int sizeof_attrib, const char* name = NULL);

  void DestroyFaceSparseAttrib(int id);

  TopFaceSparseAttrib* GetFaceSparseAttrib(int id)
  {
    return m_face_sparse_attribs.Get(id);
  }

  int CreateEdgeSparseAttrib(int sizeof_attrib, const char* name = NULL);

  void DestroyEdgeSparseAttrib(int id);

  TopEdgeSparseAttrib* GetEdgeSparseAttrib(int id)
  {
    return m_edge_sparse_attribs.Get(id);
  }

  int CreateVertexSparseAttrib(int sizeof_attrib, const char* name = NULL);

  void DestroyVertexSparseAttrib(int id);

  TopVertexSparseAttrib* GetVertexSparseAttrib(int id)
  {
    return m_vertex_sparse_attribs.Get(id);
  }

  bool Serialize(IOStream* s);

  bool Deserialize(IOStream* s);

  /**
   * Obtains the current version of serialization.
   */
  static float GetSerializationVersion();

  /***********************
     Consistency checks 
  ************************/
  /** Checks whether the model is empty. */
  bool CheckEmpty();
  /** Checks whether nodes are valid. */
  bool CheckNodes();
  /** Checks whether internal facet, edge and vertex anchors are correct. */
#ifdef TOP_USE_NON_ORIENTED_IMPLICIT_ENTITIES    
  bool CheckAnchors(TopModelConsistencyListener* l = NULL);
#endif
  /** Checks whether the model is manifold. */
  bool CheckManifold(TopModelConsistencyListener* l = NULL, 
    bool allow_free_nodes = false, bool allow_free_coh_facets = false);
  /** Checks whether cohesive elements are consistent. */
  bool CheckCohesive(TopModelConsistencyListener* l = NULL, bool allow_free_facets = false);
  /** Checks whether internal element representation is correct. */
  bool CheckConcreteElems(unsigned el_type);
  bool CheckVirtualElems(unsigned el_type);
  bool CheckEmptyElems(unsigned el_type);
  bool CheckFreeElems(unsigned el_type);
  /**
      Checks whether model is consistent. Includes several other checks.
  */
  bool CheckConsistency(TopModelConsistencyListener* l = NULL, 
    bool allow_free_nodes = false, bool allow_free_coh_facets = false, 
    bool allow_non_manifold = false);

  /** Gets the error handler of this model. */
  TopErrorHandler* GetErrorHandler() { return &m_error; }

  /***********************
     Debug methods 
  ************************/
  int CountFacetAttribs();
  int CountEdgeAttribs();
  int CountVertexAttribs();
  int CountConcreteElems(unsigned el_type);
  int CountVirtualElems(unsigned el_type);
  int CountEmptyElems(unsigned el_type);
  int CountFreeElems(unsigned el_type);
  int CountTotalElems(unsigned el_type);

  void Print(TopNode node, const char* label=0);
  void Print(TopElement element, const char* label=0);
  void PrintHiddenElems(const char* label=0);
  void PrintNodes(const char* label=0);
  void PrintFreeElem(const char* label=0);
  void PrintInfo(const char* label=0);

  /**
    Prints an estimate of the minimum amount of memory required by this model.
    Only the memory that is actually used by the model's entities
    is taken into account (e.g. gaps in element and node arrays may be discarded).
    Hence, this is a lower bound on the actual memory in use by the model.
  */
  void PrintMemUsage(const char* label, FILE* fp);

  /** Internal use. */
  TopRawArray<TopEdgeUse>* CreateEdgeUseArray ()
  {
    if (!m_eu_pool->IsEmpty())
      return m_eu_pool->Get();
    else
      return new TopRawArray<TopEdgeUse>();
  }

  /** Internal use. */
  void ReleaseEdgeUseArray (TopRawArray<TopEdgeUse>* a)
  {
    m_eu_pool->Put(a);
  }

  /** Internal use. */
  TopRawArray<TopElement>* CreateEdgeElemArray ()
  {
    if (!m_ee_pool->IsEmpty())
      return m_ee_pool->Get();
    else
      return new TopRawArray<TopElement>();
  }

  /** Internal use. */
  void ReleaseEdgeElemArray (TopRawArray<TopElement>* a)
  {
    m_ee_pool->Put(a);
  }

#ifdef TOP_USE_NON_ORIENTED_IMPLICIT_ENTITIES    
  /** Internal use. */
  TopRawArray<TopFacet>* CreateEdgeFacetArray ()
  {
    if (!m_ef_pool->IsEmpty())
      return m_ef_pool->Get();
    else
      return new TopRawArray<TopFacet>();
  }

  /** Internal use. */
  void ReleaseEdgeFacetArray (TopRawArray<TopFacet>* a)
  {
    m_ef_pool->Put(a);
  }
#endif

  /** Internal use. */
  TopRawArray<TopVertexUse>* CreateVertexUseArray ()
  {
    if (!m_vu_pool->IsEmpty())
      return m_vu_pool->Get();
    else
      return new TopRawArray<TopVertexUse>();
  }

  /** Internal use. */
  void ReleaseVertexUseArray (TopRawArray<TopVertexUse>* a)
  {
    m_vu_pool->Put(a);
  }

  /** Internal use. */
  TopRawArray<TopElement>* CreateVertexElemArray ()
  {
    if (!m_ve_pool->IsEmpty())
      return m_ve_pool->Get();
    else
      return new TopRawArray<TopElement>();
  }

  /** Internal use. */
  void ReleaseVertexElemArray (TopRawArray<TopElement>* a)
  {
    m_ve_pool->Put(a);
  }

#ifdef TOP_USE_NON_ORIENTED_IMPLICIT_ENTITIES    
  /** Internal use. */
  TopRawArray<TopFacet>* CreateVertexFacetArray ()
  {
    if (!m_vf_pool->IsEmpty())
      return m_vf_pool->Get();
    else
      return new TopRawArray<TopFacet>();
  }

  /** Internal use. */
  void ReleaseVertexFacetArray (TopRawArray<TopFacet>* a)
  {
    m_vf_pool->Put(a);
  }

  /** Internal use. */
  TopRawArray<TopEdge>* CreateVertexEdgeArray ()
  {
    if (!m_vedge_pool->IsEmpty())
      return m_vedge_pool->Get();
    else
      return new TopRawArray<TopEdge>();
  }

  /** Internal use. */
  void ReleaseVertexEdgeArray (TopRawArray<TopEdge>* a)
  {
    m_vedge_pool->Put(a);
  }
#endif

  /** Internal use. */
  TopRawArray<TopElement>* CreateNodeElemArray ()
  {
    if (!m_ne_pool->IsEmpty())
      return m_ne_pool->Get();
    else
      return new TopRawArray<TopElement>();
  }

  /** Internal use. */
  void ReleaseNodeElemArray (TopRawArray<TopElement>* a)
  {
    m_ne_pool->Put(a);
  }

private:
  void UpdateProgress(const char* sectionname, float progress)
  {
    if (m_progress_cb != NULL)
      m_progress_cb(sectionname, progress, m_progress_cbdata);
  }

  void UpdateProgressEvery(const char* sectionname, int partsdone, 
                           int numparts, int frequency)
  {
    if (m_progress_cb != NULL && (partsdone%frequency) == 0)
      m_progress_cb(sectionname, float(partsdone)/numparts, m_progress_cbdata);
  }

  void SetAdj(const TopElement& el, int fi, TopElement adj);

  void SetAdj(TopElement el0, int f0, TopElement el1, int f1);

  void SetAdj(const TopFacetUse& fu0, const TopFacetUse& fu1);

  int CreateDenseAttrib(TopArray<TopDenseAttrib*>& attribs, 
    int sizeof_data, int nvalues, const char* name);
  void DestroyDenseAttrib(TopArray<TopDenseAttrib*>& attribs, int id);
  bool ResizeDenseAttribs(TopArray<TopDenseAttrib*>& attribs, int n);
  bool TrimDenseAttribsToSize(TopArray<TopDenseAttrib*>& attribs);
  int CreateSparseAttrib(TopArray<TopSparseAttrib*>& attribs, 
    int datasize, const char* name);
  void DestroySparseAttrib(TopArray<TopSparseAttrib*>& attribs, int id);
  bool TrimSparseAttribsToSize(TopArray<TopSparseAttrib*>& attribs);

  bool CheckNoDuplicateNodesInElems(TopModelConsistencyListener* l);
  bool CheckNoDuplicateManifoldBlocksInNodes();

  bool ComputeFacetAdjacencies();
  void ComputeFacetAdjacenciesReservoir();
  void ComputeNodeElementsManifold();
  void AddManifoldBlocksToNodes();
  void SplitNonManifoldNodes();
  void ComputeAnchorsManifold();
  static bool FindSmallestElemHandleCB(TopModel* m, TopVertexUse vu, void* data);
  static bool FindSmallestElemHandleCB(TopModel* m, TopEdgeUse eu, void* data);
  static bool EUCanReachElemCB(TopModel* m, TopEdgeUse eu, void* data);
  static bool VUCanReachElemCB(TopModel* m, TopVertexUse vu, void* data);

  void EdgeCollapseGetMergingFacetUses(const TopEdgeUse& collapsed_eu,
                                       TopFacetUse* o_merged_fu0,
                                       TopFacetUse* o_merged_fu1);
  bool EdgeCollapseAreMergingElemsValid(const TopEdgeUse& collapsing_edge);
  bool EdgeCollapseWillMergingElemsHaveSameNodes(
      const TopEdgeUse& collapsing_eu,
      const TopElement& merging_elem0,
      const TopElement& merging_elem1);
  bool EdgeCollapseWillMergingElemsHaveDuplicateAdjacencies(
      const TopEdgeUse& collapsing_eu,
      const TopElement& merging_elem0,
      const TopElement& merging_elem1);
  bool EdgeCollapseWillNonCollapsingElemsHaveDuplicateNodes(
      const TopEdgeUse& collapsing_eu);

private:
  TopPool<TopRawArray<TopEdgeUse>*>* m_eu_pool;
  TopPool<TopRawArray<TopElement>*>* m_ee_pool;
#ifdef TOP_USE_NON_ORIENTED_IMPLICIT_ENTITIES    
  TopPool<TopRawArray<TopFacet>*>* m_ef_pool;
#endif
  TopPool<TopRawArray<TopVertexUse>*>* m_vu_pool;
  TopPool<TopRawArray<TopElement>*>* m_ve_pool;
#ifdef TOP_USE_NON_ORIENTED_IMPLICIT_ENTITIES    
  TopPool<TopRawArray<TopFacet>*>* m_vf_pool;
  TopPool<TopRawArray<TopEdge>*>* m_vedge_pool;
#endif
  TopPool<TopRawArray<TopElement>*>* m_ne_pool;
  ProgressFunction m_progress_cb;
  void* m_progress_cbdata;
};

#include "iterators.h"
#include "attributes.inl"

#endif
