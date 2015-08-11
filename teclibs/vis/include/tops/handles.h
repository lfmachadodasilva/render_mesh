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

#ifndef _TOP_HANDLES_H
#define _TOP_HANDLES_H

#include "defines.h"

class TopModel;

/**
    Node handle (32bits): {
      TOP_ENTITY_LEVEL_BITS:level |
      TOP_NODE_TYPE_BITS:node_type | 
      TOP_NODE_POS_ID_BITS:node_posid
    }

    Nodes are the lowest order entities represented in a model. When attached to
  an element, a node can be a corner or mid-side node, and always holds a reference
  to at least one of the elements which contains it. (For a manifold model, which 
  is the case of this data structure, only one element pointer is actually required).
*/
class TOPSH_API TopNode
{
private:  
  unsigned m_handle;
public:
  static unsigned CreateHandle(unsigned level, unsigned type, unsigned posid) 
  {
    return (((level << TOP_NODE_TYPE_BITS) | type) << TOP_NODE_POS_ID_BITS) | posid;
  }
  static unsigned CreateHandle(unsigned type, unsigned posid) 
  {
    return (type << TOP_NODE_POS_ID_BITS) | posid;
  }
  // Extracts a node handle from a generic entity handle
  // Extracts an element handle from a generic entity handle
  static unsigned GetNodeHandle(unsigned handle)
  {
    return handle & TOP_NODE_HANDLE_PAT;
  }  
  static unsigned GetNodePosId(unsigned handle)
  {
    return handle & TOP_NODE_POS_ID_PAT;
  }
  static unsigned GetNodeType(unsigned handle)
  {
    return (handle & TOP_NODE_TYPE_PAT) >> TOP_NODE_TYPE_OFFSET;
  }

  TopNode(unsigned handle = TOP_INVALID_HANDLE) 
    : m_handle(handle) {}

  TopNode(unsigned type, unsigned posid) 
    : m_handle(CreateHandle(type, posid)) {}

  TopNode(unsigned level, unsigned type, unsigned posid) 
    : m_handle(CreateHandle(level, type, posid)) {}

  bool     IsValid() const { return m_handle != TOP_INVALID_HANDLE; }

  unsigned GetHandle() const { return m_handle; }

  /**
    Internal use.
    Returns internal node level.
  */
  unsigned GetLevel() const 
  { 
#if (TOP_ENTITY_LEVEL_BITS > 0)
    return (m_handle & TOP_NODE_LEVEL_PAT) >> TOP_NODE_LEVEL_OFFSET;
#else
    return 0;
#endif
  }
  /**
    Internal use.
    Returns internal node type.
  */
  unsigned GetType() const 
  { 
    return (m_handle & TOP_NODE_TYPE_PAT) >> TOP_NODE_TYPE_OFFSET;
  }
  /**
    Internal use.
    Returns internal node position.
  */
  unsigned GetPosId() const 
  { 
    return m_handle & TOP_NODE_POS_ID_PAT; 
  }
  
  bool IsEqual(const TopNode& n) const { return m_handle == n.m_handle; }
  bool operator==(const TopNode& n) const { return m_handle == n.m_handle; }
  bool operator!=(const TopNode& n) const { return m_handle != n.m_handle; }
  bool operator<(const TopNode& n) const { return m_handle < n.m_handle; }
};

/**
    Element handle: { 
      TOP_ENTITY_LOCAL_ID_BITS: 0 | 
      TOP_ENTITY_LEVEL_BITS:level |
      TOP_ELEMENT_TYPE_BITS:el_type | 
      TOP_ELEMENT_POS_ID_BITS:el_id 
    }

    Elements are the highest order entities represented in a model. Along
  with nodes, they are explicitly represented and are the "building blocks"
  of a finite element model. There are, basically, two types of 
  elements: cohesive and non-cohesive.
  
    In current implementation, the following constraints are assumed for
  an element:
    - its boundary is manifold;
    - normals of facet-uses must point away from the element;
    - element's entities are locally oriented;
    - it has at most: 
      * TOP_MAX_NUM_F facet-uses,
      * TOP_MAX_NUM_E edge-uses,
      * TOP_MAX_NUM_V vertex-uses;
    - if it's not cohesive, then it's a closed polyhedron and it has no more 
    than a single reference to each of its nodes. Non-cohesive elements
    can have at most one use of a facet, edge or vertex. Cohesive elements can 
    have up to two uses of an edge or vertex (in this case, the element has
    what is called either a "shared" edge-use or vertex-use).
    
  @see TopElementTemplate::SHARED_V
  @see TopElementTemplate::SHARED_E
*/    
class TOPS_API TopElement
{
private:  
  unsigned m_handle;
public:
  static unsigned CreateHandle(unsigned level, unsigned type, unsigned posid) 
  {
    return (((level << TOP_ELEMENT_TYPE_BITS) | type) << TOP_ELEMENT_POS_ID_BITS) | posid;
  }
  static unsigned CreateHandle(unsigned type, unsigned posid) 
  {
    return (type << TOP_ELEMENT_POS_ID_BITS) | posid;
  }
  // Extracts an element handle from a generic entity handle
  static unsigned GetElemHandle(unsigned handle)
  {
    return handle & TOP_ELEMENT_HANDLE_PAT;
  }  
  static unsigned GetElemPosId(unsigned handle)
  {
    return handle & TOP_ELEMENT_POS_ID_PAT;
  }
  static unsigned GetElemType(unsigned handle)
  {
    return (handle & TOP_ELEMENT_TYPE_PAT) >> TOP_ELEMENT_TYPE_OFFSET;
  }

  TopElement(unsigned handle = TOP_INVALID_HANDLE) 
    : m_handle(handle) {}

  TopElement(unsigned type, unsigned posid) 
    : m_handle(CreateHandle(type, posid)) {}

  TopElement(unsigned level, unsigned type, unsigned posid) 
    : m_handle(CreateHandle(level, type, posid)) {}

  bool  IsValid() const { return m_handle != TOP_INVALID_HANDLE; }

  unsigned GetHandle() const { return m_handle; }

  /**
    Internal use.
    Returns internal element level.
  */
  unsigned GetLevel() const 
  { 
#if (TOP_ENTITY_LEVEL_BITS > 0)
    return (m_handle & TOP_ELEMENT_LEVEL_PAT) >> TOP_ELEMENT_LEVEL_OFFSET;
#else
    return 0;
#endif
    
  }
  /**
    Internal use.
    Returns internal element type.
  */
  unsigned GetType() const 
  { 
    return (m_handle & TOP_ELEMENT_TYPE_PAT) >> TOP_ELEMENT_TYPE_OFFSET;
  }
  /**
    Internal use.
    Returns internal element position.
  */
  unsigned GetPosId() const 
  { 
    return m_handle & TOP_ELEMENT_POS_ID_PAT; 
  }
  
  bool IsEqual(const TopElement& el) const { return m_handle == el.m_handle; }
  bool operator==(const TopElement& el) const { return m_handle == el.m_handle; }
  bool operator!=(const TopElement& el) const { return m_handle != el.m_handle; }
  bool operator<(const TopElement& n) const { return m_handle < n.m_handle; }
};

/**
    FacetUse handle: { 
      TOP_ENTITY_LOCAL_ID_BITS:lid | 
      TOP_ENTITY_LEVEL_BITS:level |
      TOP_ELEMENT_TYPE_BITS:el_type | 
      TOP_ELEMENT_POS_ID_BITS:el_id 
    }
    Represents the use of a facet by an element.
    @see TopFacet
*/ 
class TOPS_API TopFacetUse
{
private:  
  unsigned m_handle;
public:
  TopFacetUse(unsigned handle=TOP_INVALID_HANDLE) : m_handle(handle) {}
  TopFacetUse(unsigned el_handle, int lid) 
    : m_handle(el_handle | (lid << TOP_ELEMENT_HANDLE_BITS)) {}
  bool IsValid() const { return m_handle != TOP_INVALID_HANDLE; }
  unsigned   GetHandle() const { return m_handle; }
  unsigned   GetLocalId() const { return m_handle >> TOP_ELEMENT_HANDLE_BITS; }
  // Returns internal element type.
  unsigned   GetElemType() const 
  { 
    return (m_handle & TOP_ELEMENT_TYPE_PAT) >> TOP_ELEMENT_TYPE_OFFSET; 
  }
  // Returns internal element position.
  unsigned   GetElemPosId() const 
  { 
    return m_handle & TOP_ELEMENT_POS_ID_PAT; 
  }
  unsigned   GetElemHandle() const 
  { 
    return m_handle & TOP_ELEMENT_HANDLE_PAT; 
  }
  
  bool IsEqual(const TopFacetUse& fu) const { return m_handle == fu.m_handle; }
  bool operator==(const TopFacetUse& fu) const { return m_handle == fu.m_handle; }
  bool operator!=(const TopFacetUse& fu) const { return m_handle != fu.m_handle; }
};

/**
    FaceUse handle: { 
      TOP_ENTITY_LOCAL_ID_BITS:lid | 
      TOP_ENTITY_LEVEL_BITS:level |
      TOP_ELEMENT_TYPE_BITS:el_type | 
      TOP_ELEMENT_POS_ID_BITS:el_id 
    }
    Represents the use of a face by an element.
    @see TopFace
*/ 
class TOPS_API TopFaceUse
{
private:  
  unsigned m_handle;
public:
  TopFaceUse(unsigned handle=TOP_INVALID_HANDLE) : m_handle(handle) {}
  TopFaceUse(unsigned el_id, int lid) 
    : m_handle(el_id | (lid<<TOP_ELEMENT_HANDLE_BITS)) {}
  bool IsValid() const { return m_handle != TOP_INVALID_HANDLE; }
  unsigned   GetHandle() const { return m_handle; }
  unsigned   GetLocalId() const 
  { 
    return m_handle >> TOP_ELEMENT_HANDLE_BITS; 
  }
  // Returns internal element type.
  unsigned   GetElemType() const 
  { 
    return (m_handle & TOP_ELEMENT_TYPE_PAT) >> TOP_ELEMENT_TYPE_OFFSET; 
  }
  // Returns internal element position.
  unsigned   GetElemPosId() const 
  { 
    return m_handle & TOP_ELEMENT_POS_ID_PAT; 
  }
  unsigned   GetElemHandle() const 
  { 
    return m_handle & TOP_ELEMENT_HANDLE_PAT; 
  }
  
  bool IsEqual(const TopFaceUse& fu) const { return m_handle == fu.m_handle; }
  bool operator==(const TopFaceUse& fu) const { return m_handle == fu.m_handle; }
  bool operator!=(const TopFaceUse& fu) const { return m_handle != fu.m_handle; }
};

/**
    EdgeUse handle: { 
      TOP_ENTITY_LOCAL_ID_BITS:lid | 
      TOP_ENTITY_LEVEL_BITS:level |
      TOP_ELEMENT_TYPE_BITS:el_type | 
      TOP_ELEMENT_POS_ID_BITS:el_id 
    }    
    Represents the use of a edge by an element.
    @see TopEdge
*/
class TOPS_API TopEdgeUse
{
private:  
  unsigned m_handle;
public:
  TopEdgeUse(unsigned handle=TOP_INVALID_HANDLE) : m_handle(handle) {}
  TopEdgeUse(unsigned el_id, int lid) 
    : m_handle(el_id | (lid<<TOP_ELEMENT_HANDLE_BITS)) {}
  bool IsValid() const { return m_handle != TOP_INVALID_HANDLE; }
  unsigned   GetHandle() const { return m_handle; }
  unsigned   GetLocalId() const { return m_handle >> TOP_ELEMENT_HANDLE_BITS; }
  // Returns internal element type.
  unsigned   GetElemType() const 
  { 
    return (m_handle & TOP_ELEMENT_TYPE_PAT) >> TOP_ELEMENT_TYPE_OFFSET; 
  }
  // Returns internal element position.
  unsigned   GetElemPosId() const 
  { 
    return m_handle & TOP_ELEMENT_POS_ID_PAT; 
  }
  unsigned   GetElemHandle() const 
  { 
    return m_handle & TOP_ELEMENT_HANDLE_PAT; 
  }
  
  bool IsEqual(const TopEdgeUse& eu) const { return m_handle == eu.m_handle; }
  bool operator==(const TopEdgeUse& eu) const { return m_handle == eu.m_handle; }
  bool operator!=(const TopEdgeUse& eu) const { return m_handle != eu.m_handle; }
};

/**
    VertexUse handle: { 
      TOP_ENTITY_LOCAL_ID_BITS:lid | 
      TOP_ENTITY_LEVEL_BITS:level |
      TOP_ELEMENT_TYPE_BITS:el_type | 
      TOP_ELEMENT_POS_ID_BITS:el_id 
    }    
    Represents the use of a vertex by an element.
    @see TopVertex
*/
class TOPS_API TopVertexUse
{
private:  
  unsigned m_handle;
public:
  TopVertexUse(unsigned handle=TOP_INVALID_HANDLE) : m_handle(handle) {}
  TopVertexUse(unsigned el_id, int lid) : m_handle(el_id | (lid<<TOP_ELEMENT_HANDLE_BITS)) {}
  bool IsValid() const { return m_handle != TOP_INVALID_HANDLE; }
  unsigned   GetHandle() const { return m_handle; }
  unsigned   GetLocalId() const { return m_handle >> TOP_ELEMENT_HANDLE_BITS; }
  // Returns internal element type.
  unsigned   GetElemType() const 
  { 
    return (m_handle & TOP_ELEMENT_TYPE_PAT) >> TOP_ELEMENT_TYPE_OFFSET; 
  }
  // Returns internal element position.
  unsigned   GetElemPosId() const 
  { 
    return m_handle & TOP_ELEMENT_POS_ID_PAT; 
  }
  unsigned   GetElemHandle() const 
  { 
    return m_handle & TOP_ELEMENT_HANDLE_PAT; 
  }

  bool IsEqual(const TopVertexUse& vu) const { return m_handle == vu.m_handle; }
  bool operator==(const TopVertexUse& vu) const { return m_handle == vu.m_handle; }
  bool operator!=(const TopVertexUse& vu) const { return m_handle != vu.m_handle; }
};


#ifdef TOP_USE_NON_ORIENTED_IMPLICIT_ENTITIES  
/**
    Facet handle.

    For a d-dimensional element, a facet is the (d-1)-dimensional non-oriented entity
  which defines the element's boundary and is bounded by a set of edges. In a 
  manifold model, facets can be "used" by one element (boundary facets) or two 
  adjacent elements (interior facets), and
  are uniquely defined by one of the two possible facet-uses. The facet-use which
  defines the facet is the one of the only element holding the "anchor" bit for the
  facet.
*/
class TOPS_API TopFacet
{
private:
  friend class TopModel;
  unsigned  m_handle;
public:
  TopFacet() : m_handle(TOP_INVALID_HANDLE) {}
  TopFacet(unsigned handle) : m_handle(handle) {} 
  bool IsValid() const { return m_handle != TOP_INVALID_HANDLE; }
  unsigned GetRawHandle() const { return m_handle; }
};

/**
    Face handle.

    For a d-dimensional element, a facet is the (d-1)-dimensional non-oriented entity
  which defines the element's boundary and is bounded by a set of edges. In a 
  manifold model, facets can be "used" by one element (boundary facets) or two 
  adjacent elements (interior facets), and
  are uniquely defined by one of the two possible facet-uses. The facet-use which
  defines the facet is the one of the only element holding the "anchor" bit for the
  facet.
*/
class TOPS_API TopFace
{
private:
  friend class TopModel;
  unsigned  m_handle;
public:
  TopFace() : m_handle(TOP_INVALID_HANDLE) {}
  TopFace(unsigned handle) : m_handle(handle) {} 
  bool IsValid() const { return m_handle != TOP_INVALID_HANDLE; }
  unsigned GetRawHandle() const { return m_handle; }
};

/**
    Edge handle.
  
    An edge is the 1-dimensional entity which is bounded by two vertices. Non-linear 
  edges can also have mid-side nodes, besides the corner nodes.
  It may be radialy "used" by several elements and is uniquely defined by one
  of its edge-uses. The edge-use which defines the edge is the one of the only 
  element holding the "anchor" bit for the edge. The edge is considered a boundary 
  edge if one of its uses is on the model's boundary.
  
    For an element, an edge-use is locally incident to two facet-uses.
  If the element is cohesive, then these two facet-uses are the same. A non-cohsive 
  element can have at most one use of a given edge, while a cohesive one can have 
  up to two uses of the edge.

    Non-linear edges can contain one or more mid-side nodes, in addition to the
  corner nodes related to the vertices which bound the edge.
*/
class TOPS_API TopEdge
{
private:
  friend class TopModel;
  unsigned  m_handle;
public:
  TopEdge() : m_handle(TOP_INVALID_HANDLE) {}
  TopEdge(unsigned handle) : m_handle(handle) {} 
  bool IsValid() const { return m_handle != TOP_INVALID_HANDLE; }
  unsigned GetRawHandle() const { return m_handle; }
};


/**
    Vertex handle.
  
    A vertex is the 0-dimensional entity which bounds an edge. It may be unorderly
  "uses" by several elements and is uniquely defined by one of its vertex-uses. The 
  vertex-use which defines the vertex is the one of the only element holding the 
  "anchor" bit for the vertex. The vertex is considered a boundary vertex if one of 
  its uses is on the model's boundary.
*/
class TOPS_API TopVertex
{
private:
  friend class TopModel;
  unsigned  m_handle;
public:
  TopVertex() : m_handle(TOP_INVALID_HANDLE) {}
  TopVertex(unsigned handle) : m_handle(handle) {} 
  bool IsValid() const { return m_handle != TOP_INVALID_HANDLE; }
  unsigned GetRawHandle() const { return m_handle; }
};
#endif
#endif
