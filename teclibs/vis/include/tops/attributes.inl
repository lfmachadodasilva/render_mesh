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

#ifndef TOP_ATTRIBUTES_INL
#define TOP_ATTRIBUTES_INL

inline void TopSparseAttrib::Set(const TopNode& node, void* data) 
{ 
  m_v.Set(node.GetHandle(), data);
}
inline void* TopSparseAttrib::Get(const TopNode& node) 
{
  return m_v.Get(node.GetHandle());
}
inline void TopSparseAttrib::Set(const TopElement& elem, void* data) 
{ 
  m_v.Set(elem.GetHandle(), data);
}
inline void* TopSparseAttrib::Get(const TopElement& elem) 
{
  return m_v.Get(elem.GetHandle());
}

#ifdef TOP_USE_NON_ORIENTED_IMPLICIT_ENTITIES  
inline void TopSparseAttrib::Set(const TopFacet& facet, void* data) 
{ 
  m_v.Set(m_model->GetHandle(facet), data);
}

inline void* TopSparseAttrib::Get(const TopFacet& facet) 
{
  return m_v.Get(m_model->GetHandle(facet));
}

inline void TopSparseAttrib::Set(const TopFace& face, void* data) 
{ 
  m_v.Set(m_model->GetHandle(face), data);
}

inline void* TopSparseAttrib::Get(const TopFace& face) 
{
  return m_v.Get(m_model->GetHandle(face));
}

inline void TopSparseAttrib::Set(const TopEdge& edge, void* data) 
{ 
  m_v.Set(m_model->GetHandle(edge), data);
}

inline void* TopSparseAttrib::Get(const TopEdge& edge) 
{
  return m_v.Get(m_model->GetHandle(edge));
}

inline void TopSparseAttrib::Set(const TopVertex& vertex, void* data) 
{ 
  m_v.Set(m_model->GetHandle(vertex), data);
}

inline void* TopSparseAttrib::Get(const TopVertex& vertex) 
{
  return m_v.Get(m_model->GetHandle(vertex));
}
#endif
#endif
