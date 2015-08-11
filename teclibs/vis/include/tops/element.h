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

#ifndef _TOP_ELEMENT_H
#define _TOP_ELEMENT_H

#include <assert.h>
#include "defines.h"
#include <io/stream.h>

class TopModel;

/**
    Defines the topological properties of an element type, such as, for
  instance, the number of facets and their node incidence. Every element
  has a pointer to a template, which is constant for all elements of the
  same type.
*/
struct TOPS_API TopElementTemplate
{
  int IS_DYNAMIC;
  int DIMENSION;      ///< Element dimension: 2 (2D), 3 (3D)
  int ORDER;          ///< 1: Linear, 2: quadratic, 3: cubic, ....
  int IS_COHESIVE;    ///< Flag indicating if element is cohesive (1 or 0)
  int IS_INFINITE;    ///< Flag indicating if element is infinite (1 or 0)
  
  int NUM_F;          ///< Number of element's facets
  int NUM_E;          ///< Number of element's edges
  int NUM_V;          ///< Number of element's vertices
  int NUM_N;          ///< Number of element's nodes

  /**
      Arrays containing the number of entities of a given type in relation to
    another. For instance, NUM_F_E[fi] is the number of edge-uses of the fi'th
    facet-use of the element. 
  */
  int NUM_F_E[TOP_MAX_NUM_F]; 
  int NUM_F_V[TOP_MAX_NUM_F]; 
  int NUM_F_N[TOP_MAX_NUM_F];

  int NUM_E_F[TOP_MAX_NUM_E];
  int NUM_E_N[TOP_MAX_NUM_E];

  int NUM_V_F[TOP_MAX_NUM_V];
  int NUM_V_E[TOP_MAX_NUM_V];

  
  /**
      Array containing local entity incidences inside an element. For 
    instance, F_E[fi][ei] is the local id of the ei'th edge-use of the
    the fi's facet-use of the element.
  */ 
  int  F_E[TOP_MAX_NUM_F][TOP_MAX_NUM_F_E];
  int  F_V[TOP_MAX_NUM_F][TOP_MAX_NUM_F_V];
  int  F_N[TOP_MAX_NUM_F][TOP_MAX_NUM_F_N];

  int  E_F[TOP_MAX_NUM_E][2];
  int  E_V[TOP_MAX_NUM_E][2];
  int  E_N[TOP_MAX_NUM_E][TOP_MAX_NUM_E_N];

  int  V_F[TOP_MAX_NUM_V][TOP_MAX_NUM_V_F];
  int  V_E[TOP_MAX_NUM_V][TOP_MAX_NUM_V_E];
  int  V_N[TOP_MAX_NUM_V];

  /**
      N_E[ni] is the local id of the edge-use of which the ni'th node 
    of the element is a mid-side node. If the node is not a mid-side node
    of an edge, then N_E[ni] < 0.
  */
  int  N_E[TOP_MAX_NUM_N];
  
  /**
      N_V[ni] is the local id of the vertex-use relative to the ni'th node 
    of the element. If the node is not a vertex, then N_V[ni] < 0.
  */
  int  N_V[TOP_MAX_NUM_N]; 
 
  /**
      Local position of the vi'th vertex-use of the element in the i'th 
    facet-use incident to the vertex-use.
      Suppose that V_F_V[vi][0] is 1. Then the vertex-use "vi" is the second 
    vertex-use of the first facet-use incident to "vi", according to
    facet-use local orientation.
  */
  int  V_F_V[TOP_MAX_NUM_V][TOP_MAX_NUM_V_F];
  int  E_F_E[TOP_MAX_NUM_E][2];

  /**
      SHARED_V[vi] is the local id of the "shared" vertex-use for the
    vi'th vertex-use of the element. If there is no "shared" vertex-use,
    SHARED_V[vi] is < 0.
    
      It represents the "other possible use" of a vertex in the element. 
    Non-cohesive element have only one use of each vertex, while cohesive
    elements mey have two. In these elements, if the vertex (or the nodes)
    of the shared vertex-use is the same as vi's, then there are two uses
    of the vertex, else there is one use of the vertex.
  */
  int  SHARED_V[TOP_MAX_NUM_V];
  int  SHARED_E[TOP_MAX_NUM_E];
  /* Local node id of the 1st mid-side node of the edge on the shared edge.
    Only if NUM_E_N[ei] > 2.
   */
  int  SHARED_E_N[TOP_MAX_NUM_E];

  //TOPFACE
  int NUM_FC;          ///< Number of element's facets

  int NUM_FC_E[TOP_MAX_NUM_F]; 
  int NUM_FC_V[TOP_MAX_NUM_F]; 
  int NUM_FC_N[TOP_MAX_NUM_F];

  int NUM_E_FC[TOP_MAX_NUM_E];

  int NUM_V_FC[TOP_MAX_NUM_V];

  int  FC_E[TOP_MAX_NUM_F][TOP_MAX_NUM_F_E];
  int  FC_V[TOP_MAX_NUM_F][TOP_MAX_NUM_F_V];
  int  FC_N[TOP_MAX_NUM_F][TOP_MAX_NUM_F_N];

  int  E_FC[TOP_MAX_NUM_E][2];

  int  V_FC[TOP_MAX_NUM_V][TOP_MAX_NUM_V_F];
 
  int  V_FC_V[TOP_MAX_NUM_V][TOP_MAX_NUM_V_F];
  int  E_FC_E[TOP_MAX_NUM_E][2];
};

/**
  Element sizes and offsets template.
  Offsets are positive values relative to the element address.
*/ 
struct TOPS_API TopElementSizeTemplate
{
  int SIZE; // Total size of the concrete element
  int NODES_OFFSET;
  int ADJ_OFFSET;
};

class TopNode;


class TOPS_API TopElementClass
{
public:
  TopElementClass(TopElementTemplate t) { m_T = t; }

  int GetDimension() const { return m_T.DIMENSION; }
  int GetOrder() const { return m_T.ORDER; }
  bool IsCohesive() const { return m_T.IS_COHESIVE != 0; }
  bool IsInfinite() const { return m_T.IS_INFINITE != 0; }
  bool IsDynamic() const { return m_T.IS_DYNAMIC != 0; }

  /********************************************
    For static elements only!
  *********************************************/
  int GetNFacets() const { return m_T.NUM_F; }
  int GetNEdges() const { return m_T.NUM_E; }
  int GetNVertices() const { return m_T.NUM_V; }
  int GetNNodes() const { return m_T.NUM_N; } 
  bool IsVertexNode(int ni) const { return m_T.N_V[ni] >= 0; }
  bool IsEdgeNode(int ni) const { return m_T.N_E[ni] >= 0; }
  int GetEdgeUseNNodes(int eui) const { return m_T.NUM_E_N[eui]; }
  int GetEdgeUseNodeLocalId(int eui, int ni) const { return m_T.E_N[eui][ni]; }

private:
  friend class TopModel;
  TopElementTemplate m_T;
  TopElementClass() {}
};

/**
    Defines the element behavior. This is what makes an element different
  to another.

  @see TopElementTemplate
  @see TopElement
*/
class TOPS_API TopConcreteElement
{
  friend class TopModel;

  /**
      Bits used for vertex/edge/facet identification. The entity's element is 
    the only one with the bit set, for the corresponding entity-use.
    Entity anchors (32 bits): { 
      3: not used, 
      1: dynamic flag,
      2: state (enum State),
      TOP_MAX_NUM_F: facet anchors, 
      TOP_MAX_NUM_E: edge anchors,
      TOP_MAX_NUM_V: vertex anchors 
    }       
      For every element type, m_anchors represent the anchors actually held 
    by the element. For a virtual or empty element, m_ts keeps the anchors that
    element used to hold ("ex-anchors").
      A normal element has only anchors.
      An empty element has only ex-anchors.
      A virtual element may have both anchors (for the locked entities) and 
    ex-anchors (like the empty elements).
  */
  unsigned int m_anchors;
  unsigned int m_ts;  ///< Timestamp. Used for traversals.
  int m_id;  ///< Element id.

  void SetAnchorBit(int i, int flag)
  {
    m_anchors &= ~(1 << i);
    m_anchors |= flag << i;
  }

  unsigned GetAnchorBit(int i)
  {
    return m_anchors & (1 << i);
  }

  void SetExAnchorBit(int i, int flag)
  {
    assert(!IsConcrete());
    m_ts &= ~(1 << i);
    m_ts |= flag << i;
  }

  unsigned GetExAnchorBit(int i)
  {
    assert(!IsConcrete());
    return m_ts & (1 << i);
  }

  void SetState(int state)
  {
    m_anchors &= ~(3 << TOP_ELEMENT_STATE_OFFSET);
    m_anchors |= state << TOP_ELEMENT_STATE_OFFSET;
  }

  unsigned GetState()
  {
    return (m_anchors & TOP_ELEMENT_STATE_PAT) >> TOP_ELEMENT_STATE_OFFSET;
  }

protected:
  /** 
    Creation only attribute. Must be set during element's initialization if
    it is dynamic.
  */
  void SetDynamic() 
  { 
    m_anchors &= ~(1 << TOP_ELEMENT_DYNAMIC_OFFSET);
    m_anchors |= 1 << TOP_ELEMENT_DYNAMIC_OFFSET;
  }

  unsigned IsDynamic() 
  {
    return m_anchors & TOP_ELEMENT_DYNAMIC_PAT;
  }

  virtual void SetDynFaceAnchor(int fi, int flag) {}
  virtual unsigned GetDynFaceAnchor(int fi) { return 0; }
  virtual void SetDynFaceExAnchor(int fi, int flag) {}
  virtual unsigned GetDynFaceExAnchor(int fi) { return 0; }
  virtual void SetDynEdgeAnchor(int ei, int flag) {}
  virtual unsigned GetDynEdgeAnchor(int ei) { return 0; }
  virtual void SetDynEdgeExAnchor(int ei, int flag) {}
  virtual unsigned GetDynEdgeExAnchor(int ei) { return 0; }
  virtual void ClearDynVertexAnchors() {} 
  virtual void SetDynVertexAnchor(int vi, int flag) {}
  virtual unsigned GetDynVertexAnchor(int vi) { return 0; }
  virtual void SetDynVertexExAnchor(int vi, int flag) {}
  virtual unsigned GetDynVertexExAnchor(int vi) { return 0; }
  virtual int HasDynClearBits() { return 0; }
  virtual void TurnDynAnchorsIntoExAnchors() {}

public: 

  enum State {
    STATE_EMPTY = 0,
    STATE_CONCRETE = 1,
    STATE_VIRTUAL = 2,
    STATE_UNLINKED = 3
  };
  
  static const char* CLASSNAME () { return "ConcreteElement"; }
  virtual const char* ClassName () const { return CLASSNAME(); }

  TopConcreteElement() : 
    m_ts(TopClock::GetInitTime()), m_id(-1)
  {
    m_anchors = 0;
    MarkAsConcrete();
  }

  virtual ~TopConcreteElement() {}
  
  /**
     Initializes element with the given nodes.
   */
  virtual void Init(TopNode* nodes) 
  {    
    m_anchors = 0;
    m_id = -1;
    MarkAsConcrete();
  }
  
  virtual void InitCohesive(TopNode* nodes) 
  {
    m_anchors = 0;
    MarkAsConcrete();
  }

  /**
    Finishes element usage.
  */
  virtual void Finish() 
  {
    MarkAsEmpty();
  }

  virtual bool Serialize(IOStream* io)
  {
    return io->WriteUInts(1, &m_anchors) &&
           io->WriteUInts(1, &m_ts)      &&
           io->WriteInts(1, &m_id);
  }

  virtual bool Deserialize(IOStream* io)
  {
    return io->ReadUInts(1, &m_anchors) &&
           io->ReadUInts(1, &m_ts)      &&
           io->ReadInts(1, &m_id);
  }

  virtual TopElementTemplate GetTemplate() =0;

  virtual TopElementSizeTemplate GetSizeTemplate() =0;

  virtual const TopElementClass* GetClass() const =0;
  
  unsigned int GetTimestamp()                { return m_ts; }
  void         SetTimestamp(unsigned int ts) { m_ts = ts; }

  unsigned int GetId() { return m_id; }
  void SetId(unsigned int id) { m_id = id; }

  /**********************
   * Face anchors 
   **********************/
  /** Bit must be 0 or 1 */
  void SetFaceAnchor(int fi, int flag)
  {
#ifdef TOP_USE_DYNAMIC_ELEMENTS
    if (IsDynamic())
      SetDynFaceAnchor(fi, flag);
    else
#endif
      SetAnchorBit(fi + TOP_ELEMENT_FANCHOR_OFFSET, flag);
  }

  /**
      Returns if the facet bit is set for the fi'th facet-use of the element,
    that is, if the element is the corresponding facet's element.
  */
  unsigned GetFaceAnchor(int fi)
  {
#ifdef TOP_USE_DYNAMIC_ELEMENTS
    if (IsDynamic())
      return GetDynFaceAnchor(fi);
    else
#endif
      return GetAnchorBit(fi + TOP_ELEMENT_FANCHOR_OFFSET);
  }
  
  /** Bit must be 0 or 1 */
  void SetFaceExAnchor(int fi, int flag)
  {
#ifdef TOP_USE_DYNAMIC_ELEMENTS
    if (IsDynamic())
      SetDynFaceExAnchor(fi, flag);
    else
#endif
      SetExAnchorBit(fi + TOP_ELEMENT_FANCHOR_OFFSET, flag);
  }

  /**
      Returns if the facet bit is set for the fi'th facet-use of the element,
    that is, if the element is the corresponding facet's element.
  */
  unsigned GetFaceExAnchor(int fi)
  {
#ifdef TOP_USE_DYNAMIC_ELEMENTS
    if (IsDynamic())
      return GetDynFaceExAnchor(fi);
    else
#endif
      return GetExAnchorBit(fi + TOP_ELEMENT_FANCHOR_OFFSET);
  }

  /**********************
   * Edge bits
   **********************/
  /** Bit must be 0 or 1 */
  void SetEdgeAnchor(int ei, int flag)
  {
#ifdef TOP_USE_DYNAMIC_ELEMENTS
    if (IsDynamic())
      SetDynEdgeAnchor(ei, flag);
    else
#endif
      SetAnchorBit(ei + TOP_ELEMENT_EANCHOR_OFFSET, flag);
  }

  /**
      Returns if the edge bit is set for the ei'th edge-use of the element,
    that is, if the element is the corresponding edge's element.
  */
  unsigned GetEdgeAnchor(int ei)
  {
#ifdef TOP_USE_DYNAMIC_ELEMENTS
    if (IsDynamic())
      return GetDynEdgeAnchor(ei);
    else
#endif
      return GetAnchorBit(ei + TOP_ELEMENT_EANCHOR_OFFSET);
  }
  
  /** Bit must be 0 or 1 */
  void SetEdgeExAnchor(int ei, int flag)
  {
#ifdef TOP_USE_DYNAMIC_ELEMENTS
    if (IsDynamic())
      SetDynEdgeExAnchor(ei, flag);
    else
#endif
      SetExAnchorBit(ei + TOP_ELEMENT_EANCHOR_OFFSET, flag);
  }

  /**
      Returns if the edge bit is set for the ei'th edge-use of the element,
    that is, if the element is the corresponding edge's element.
  */
  unsigned GetEdgeExAnchor(int ei)
  {
#ifdef TOP_USE_DYNAMIC_ELEMENTS
    if (IsDynamic())
      return GetDynEdgeExAnchor(ei);
    else
#endif
      return GetExAnchorBit(ei + TOP_ELEMENT_EANCHOR_OFFSET);
  }  

  /**********************
   * Vertex bits
   **********************/
  void ClearVertexAnchors() 
  { 
#ifdef TOP_USE_DYNAMIC_ELEMENTS
    if (IsDynamic())
      ClearDynVertexAnchors();
    else
#endif
      m_anchors &= ~TOP_ELEMENT_VANCHOR_PAT;
  }
  
  /** Bit must be 0 or 1 */
  void SetVertexAnchor(int vi, int flag)
  {
#ifdef TOP_USE_DYNAMIC_ELEMENTS
    if (IsDynamic())
      SetDynVertexAnchor(vi, flag);
    else
#endif
      SetAnchorBit(vi + TOP_ELEMENT_VANCHOR_OFFSET, flag);
  }

  /**
      Returns if the vertex bit is set for the vi'th vertex-use of the element,
    that is, if the element is the corresponding vertex's element.
  */
  unsigned GetVertexAnchor(int vi)
  {
#ifdef TOP_USE_DYNAMIC_ELEMENTS
    if (IsDynamic())
      return GetDynVertexAnchor(vi);
    else
#endif
      return GetAnchorBit(vi + TOP_ELEMENT_VANCHOR_OFFSET);
  }
   
  /** Bit must be 0 or 1 */
  void SetVertexExAnchor(int vi, int flag)
  {
#ifdef TOP_USE_DYNAMIC_ELEMENTS
    if (IsDynamic())
      SetDynVertexExAnchor(vi, flag);
    else
#endif
      SetExAnchorBit(vi + TOP_ELEMENT_VANCHOR_OFFSET, flag);
  }

  /**
      Returns if the vertex bit is set for the vi'th vertex-use of the element,
    that is, if the element is the corresponding vertex's element.
  */
  unsigned GetVertexExAnchor(int vi)
  {
#ifdef TOP_USE_DYNAMIC_ELEMENTS
    if (IsDynamic())
      return GetDynVertexExAnchor(vi);
    else
#endif
      return GetExAnchorBit(vi + TOP_ELEMENT_VANCHOR_OFFSET);
  }

  int HasClearBits() 
  { 
#ifdef TOP_USE_DYNAMIC_ELEMENTS
    if (IsDynamic())
      return HasDynClearBits();
    else
#endif
      return !((m_anchors&TOP_ELEMENT_ANCHOR_PAT) || m_ts); 
  }

  void TurnAnchorsIntoExAnchors()
  {
#ifdef TOP_USE_DYNAMIC_ELEMENTS
    if (IsDynamic()) {
      TurnDynAnchorsIntoExAnchors();
    } else {
#endif
      m_ts = m_anchors & TOP_ELEMENT_ANCHOR_PAT;
      m_anchors &= ~TOP_ELEMENT_ANCHOR_PAT;
#ifdef TOP_USE_DYNAMIC_ELEMENTS
    }
#endif
  }
    
  /***********************************
   * Element state
   ************************************/
  int IsEmpty()
  {
    return GetState() == STATE_EMPTY;
  }
  
  void MarkAsEmpty() 
  {
    SetState(STATE_EMPTY);
  }

  int IsVirtual() 
  { 
    return GetState() == STATE_VIRTUAL;
  }
  
  /**
     Marks an element as virtual. For efficiency reasons, this method only 
   turns all the anchors into ex-anchors, as is done by MarkAsEmpty() method. 
   To keep consistency, it is necessary to explicitly turn anchors into
   ex-anchors and set the anchors again for entities that are both locked 
   and anchored in the virtual element.
  */
  void MarkAsVirtual() 
  {
    SetState(STATE_VIRTUAL);
  }
  
  int IsUnlinked() 
  { 
    return GetState() == STATE_UNLINKED;
  }
  
  /**
     Marks an element as unlinked. For efficiency reasons, this method only 
   turns all the anchors into ex-anchors, as is done by MarkAsEmpty() method. 
  */
  void MarkAsUnlinked() 
  { 
    SetState(STATE_UNLINKED);
  }
  
  /**
    Returns whether the element is not empty or virtual.
  */
  int IsConcrete() 
  { 
    return GetState() == STATE_CONCRETE;
  }
  
  void MarkAsConcrete() 
  { 
    SetState(STATE_CONCRETE);
    SetTimestamp(TopClock::GetInitTime());
  }

  /***************************************
   * Template data
   ****************************************/
  virtual int NUM_F() const { return -1; }
  virtual int NUM_E() const { return -1; }
  virtual int NUM_V() const { return -1; }
  virtual int NUM_N() const { return -1; }

  virtual int NUM_F_E(int i) const { return -1; }
  virtual int NUM_F_V(int i) const { return -1; }
  virtual int NUM_F_N(int i) const { return -1; }

  virtual int NUM_E_F(int i) const { return -1; }
  virtual int NUM_E_N(int i) const { return -1; }

  virtual int NUM_V_F(int i) const { return -1; }
  virtual int NUM_V_E(int i) const { return -1; }
 
  virtual int F_E(int fi, int i) const { return -1; }
  virtual int F_V(int fi, int i) const { return -1; }
  virtual int F_N(int fi, int i) const { return -1; }

  virtual int E_F(int ei, int i) const { return -1; }
  virtual int E_V(int ei, int i) const { return -1; }
  virtual int E_N(int ei, int i) const { return -1; }

  virtual int V_F(int vi, int i) const { return -1; }
  virtual int V_E(int vi, int i) const { return -1; }
  virtual int V_N(int vi) const { return -1; }

  virtual int N_E(int ni) const { return -1; }
  virtual int N_V(int ni) const { return -1; }

  virtual int V_F_V(int vi, int vfi) const { return -1; }
  virtual int E_F_E(int ei, int efi) const { return -1; }

  virtual int SHARED_V(int vi) const { return -1; }
  virtual int SHARED_E(int ei) const { return -1; }
  virtual int SHARED_E_N(int ei) const { return -1; }

  virtual int NUM_FC() const { return -1; }

  virtual int NUM_FC_E(int i) const { return -1; }
  virtual int NUM_FC_V(int i) const { return -1; }
  virtual int NUM_FC_N(int i) const { return -1; }

  virtual int NUM_E_FC(int i) const { return -1; }
  virtual int NUM_V_FC(int i) const { return -1; }
 
  virtual int FC_E(int fi, int i) const { return -1; }
  virtual int FC_V(int fi, int i) const { return -1; }
  virtual int FC_N(int fi, int i) const { return -1; }

  virtual int E_FC(int ei, int i) const { return -1; }
  virtual int V_FC(int vi, int i) const { return -1; }

  virtual int V_FC_V(int vi, int vfi) const { return -1; }
  virtual int E_FC_E(int ei, int efi) const { return -1; }
};

#endif
