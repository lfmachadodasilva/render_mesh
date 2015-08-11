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

#ifndef _TOP_ITERATORS_H
#define _TOP_ITERATORS_H

#include "defines.h"

/**
  Iterates over all the elements of the model.
*/
class TOPS_API TopModel::ElemItr
{
private:  
  TopModel*  m_model;
  int        m_level, m_type, m_id;
public:
  ElemItr(TopModel* model) : 
    m_model(model)
  {
    Begin();
  }
  
  ~ElemItr() {}

  void    SetModel(TopModel* m) { m_model = m; }

  void    Begin()
  {
    m_level = m_model->GetLevel();
    m_type = 0;
    m_id  = -1;
    Next();
  }
  
  void    Next()
  {
    for (; m_type < TOP_MAX_ELEMENT_TYPES; m_type++) {
      for (m_id++; m_id < m_model->m_max_elem[m_type]; m_id++) {
        if (m_model->GetConcreteElement(m_type, m_id)->IsConcrete()) 
          return;
      }
      m_id = -1;
    }
    m_type = -1;
  }
 
  TopElement GetCurr()
  {
    return TopElement((unsigned) m_level, (unsigned) m_type, (unsigned) m_id);
  }
  
  bool     IsValid()
  {
    return (m_type >= 0);
  }
};

/**
  Iterates over all the nodes of the model.
*/
class TOPS_API TopModel::NodeItr
{
private:  
  TopModel*  m_model;
  int        m_level, m_id;
public:
  NodeItr(TopModel* model) : 
    m_model(model)
  {
    Begin();
  }
  
  ~NodeItr() {}

  void    SetModel(TopModel* m) { m_model = m; }

  void    Begin()
  {
    m_level = m_model->GetLevel();
    m_id  = -1;
    Next();
  }
  
  void    Next()
  {
    for (m_id++; m_id < m_model->m_max_node; m_id++) {
      if (m_model->GetConcreteNode(m_id)->IsConcrete())
        return;
    }
    m_id = -1;
  }
 
  TopNode GetCurr()
  {
    return TopNode(m_level, TopModel::NODE_LOCAL, m_id);
  }
  
  bool     IsValid()
  {
    return (m_id >= 0);
  }
};

#ifdef TOP_USE_NON_ORIENTED_IMPLICIT_ENTITIES  
/**
  Iterates over all facets of the model.
*/
class TOPS_API TopModel::FacetItr 
{
  TopModel*   m_model;
  ElemItr     m_elitr;
  int         m_fi;
  TopFacet    m_facet;
  
public:
  FacetItr(TopModel* model) :
    m_model(model), m_elitr(ElemItr(model))
  {
    Begin();
  }
    
  ~FacetItr() {}

  void    SetModel(TopModel* m) 
  { 
    m_model = m; 
    m_elitr.SetModel(m);
  }

  void    Begin()
  {
    m_elitr.Begin();
    m_fi   = -1;
    Next();
  }
  
  void    Next()
  {
    while (m_elitr.IsValid()) {
      TopElement el = m_elitr.GetCurr();
      for (m_fi++; m_fi < m_model->GetNFacets(el); m_fi++) {
        if (m_model->GetFacetAnchor(el, m_fi)) {
          m_facet = TopFacet(TopFacetUse(el.GetHandle(), m_fi).GetHandle());
          return;
        }
      }
      m_elitr.Next();
      m_fi   = -1;
    }
    m_fi    = -1;
    m_facet = TopFacet();
  }
 
  TopFacet& GetCurr()
  {
    return m_facet;
  }
  
  bool     IsValid()
  {
    return m_facet.IsValid();
  }
};

/**
  Iterates over all faces of the model.
*/
class TOPS_API TopModel::FaceItr 
{
  TopModel*   m_model;
  ElemItr     m_elitr;
  int         m_fi;
  TopFace    m_face;
  
public:
  FaceItr(TopModel* model) :
    m_model(model), m_elitr(ElemItr(model))
  {
    Begin();
  }
    
  ~FaceItr() {}

  void    SetModel(TopModel* m) 
  { 
    m_model = m; 
    m_elitr.SetModel(m);
  }

  void    Begin()
  {
    m_elitr.Begin();
    m_fi   = -1;
    Next();
  }
  
  void    Next()
  {
    while (m_elitr.IsValid()) {
      TopElement el = m_elitr.GetCurr();
      for (m_fi++; m_fi < m_model->GetNFaces(el); m_fi++) {
        if (m_model->GetFaceAnchor(el, m_fi)) {
          m_face = TopFace(TopFaceUse(el.GetHandle(), m_fi).GetHandle());
          return;
        }
      }
      m_elitr.Next();
      m_fi   = -1;
    }
    m_fi    = -1;
    m_face = TopFace();
  }
 
  TopFace& GetCurr()
  {
    return m_face;
  }
  
  bool     IsValid()
  {
    return m_face.IsValid();
  }
};

/**
  Iterates over all edges of the model.
*/
class TOPS_API TopModel::EdgeItr 
{
  TopModel*   m_model;
  ElemItr     m_elitr;
  int         m_ei;
  TopEdge     m_edge;
  
public:
  EdgeItr(TopModel* model) :
    m_model(model), m_elitr(ElemItr(model))
  {
    Begin();
  }
    
  ~EdgeItr() {}

  void    SetModel(TopModel* m) 
  { 
    m_model = m; 
    m_elitr.SetModel(m);
  }

  void    Begin()
  {
    m_elitr.Begin();
    m_ei   = -1;
    Next();
  }
  
  void    Next()
  {
    while (m_elitr.IsValid()) {
      TopElement el = m_elitr.GetCurr();
      for (m_ei++; m_ei < m_model->GetNEdges(el); m_ei++) {
        if (m_model->GetEdgeAnchor(el, m_ei)) {
          m_edge = TopEdge(TopEdgeUse(el.GetHandle(), m_ei).GetHandle());
          return;
        }
      }
      m_elitr.Next();
      m_ei   = -1;
    }
    m_ei    = -1;
    m_edge = TopEdge();
  }
 
  TopEdge& GetCurr()
  {
    return m_edge;
  }
  
  bool     IsValid()
  {
    return m_edge.IsValid();
  }
};

/**
  Iterates over all vertices of the model.
*/
class TOPS_API TopModel::VertexItr 
{
  TopModel*   m_model;
  ElemItr     m_elitr;
  int         m_vi;
  TopVertex   m_vertex;
  
public:
  VertexItr(TopModel* model) :
    m_model(model), m_elitr(ElemItr(model))
  {
    Begin();
  }
    
  ~VertexItr() {}

  void    SetModel(TopModel* m) 
  { 
    m_model = m; 
    m_elitr.SetModel(m);
  }

  void    Begin()
  {
    m_elitr.Begin();
    m_vi   = -1;
    Next();
  }
  
  void    Next()
  {
    while (m_elitr.IsValid()) {
      TopElement el = m_elitr.GetCurr();
      for (m_vi++; m_vi < m_model->GetNVertices(el); m_vi++) {
        if (m_model->GetVertexAnchor(el, m_vi)) {
          m_vertex = TopVertex(TopVertexUse(el.GetHandle(), m_vi).GetHandle());
          return;
        }
      }
      m_elitr.Next();
      m_vi   = -1;
    }
    m_vi    = -1;
    m_vertex = TopVertex();
  }
 
  TopVertex& GetCurr()
  {
    return m_vertex;
  }
  
  bool     IsValid()
  {
    return m_vertex.IsValid();
  }
};
#endif

/**
  Iterates over all the uses of the given edge.
*/
class TOPS_API TopModel::EdgeUseItr
{
  friend class TopModel;
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
#ifdef TOP_USE_NON_ORIENTED_IMPLICIT_ENTITIES    
  EdgeUseItr(TopModel* model, TopEdge e) : m_model(model)
  {
    m_eu_array = model->CreateEdgeUseArray();
    m_eu = model->GetEdgeUse(e);
    Begin();
  }
#endif
  
  EdgeUseItr(TopModel* model, TopEdgeUse eu) : m_model(model)
  {
    m_eu_array = model->CreateEdgeUseArray();
    m_eu = eu;
    Begin();
  }
  
  
  ~EdgeUseItr()
  {
    m_model->ReleaseEdgeUseArray(m_eu_array);
  }

  void SetModel(TopModel* m) { m_model = m; }

#ifdef TOP_USE_NON_ORIENTED_IMPLICIT_ENTITIES    
  void SetEdge(TopEdge e) { m_eu = m_model->GetEdgeUse(e); }
#endif

  void SetEdgeUse(TopEdgeUse eu) { m_eu = eu; }
  
  void Begin() 
  { 
    m_curr = 0;
    m_eu_array->Reset();
    m_model->Traverse(m_eu, TraverseCb, this, 1);
  }
  void Next() { m_curr++; }

  TopEdgeUse GetCurr() { return m_eu_array->Get(m_curr); }

  bool IsValid() { return m_curr < m_eu_array->Size(); }
};

/**
  Iterates over all the elements incident to the given edge.
*/
class TOPS_API TopModel::EdgeElemItr
{
  friend class TopModel;
  TopRawArray<TopElement>*        m_el_array;
  int                             m_curr;
  TopEdgeUse                      m_eu;
  TopModel*                       m_model;

  static bool TraverseCb(TopModel* m, TopEdgeUse eu, void* data) 
  {
    ((EdgeElemItr*) data)->m_el_array->Append(TopElement(eu.GetElemHandle())); 
    return true;
  }

 public: 
#ifdef TOP_USE_NON_ORIENTED_IMPLICIT_ENTITIES  
  EdgeElemItr(TopModel* model, TopEdge e) : m_model(model)
  {
    m_el_array = model->CreateEdgeElemArray();
    m_eu = model->GetEdgeUse(e);
    Begin();
  }
#endif

  EdgeElemItr(TopModel* model, TopEdgeUse eu) : m_model(model)
  {
    m_el_array = model->CreateEdgeElemArray();
    m_eu = eu;
    Begin();
  }
  
  
  ~EdgeElemItr()
  {
    m_model->ReleaseEdgeElemArray(m_el_array);
  }

  void SetModel(TopModel* m) { m_model = m; }

#ifdef TOP_USE_NON_ORIENTED_IMPLICIT_ENTITIES  
  void SetEdge(TopEdge e) { m_eu = m_model->GetEdgeUse(e); }
#endif

  void SetEdgeUse(TopEdgeUse eu) { m_eu = eu; }
  
  void Begin() 
  { 
    m_curr = 0;
    m_el_array->Reset();
    m_model->Traverse(m_eu, TraverseCb, this, 0);
  }

  void         Next() { m_curr++; }

  TopElement   GetCurr() { return m_el_array->Get(m_curr); }

  bool         IsValid() { return m_curr < m_el_array->Size(); }
};

#ifdef TOP_USE_NON_ORIENTED_IMPLICIT_ENTITIES  
/**
  Iterates over all the facets incident to the given edge.
*/
class TOPS_API TopModel::EdgeFacetItr
{
  friend class TopModel;
  TopRawArray<TopFacet>*           m_f_array;
  int                           m_curr;
  TopEdgeUse                    m_eu;
  TopModel*                     m_model;

  static bool TraverseCb(TopModel* m, TopEdgeUse eu, void* data) 
  {
    TopElement el = m->GetElem(eu);
    for (int i = 0; i < m->GetNFacets(eu); i++) {
      TopFacetUse fu = m->GetFacetUse(eu, i);
      if (m->GetFacetAnchor(el, fu.GetLocalId()))
        ((EdgeFacetItr*) data)->m_f_array->Append(TopFacet(fu.GetHandle()));
    }
    return true;
  }

 public: 
  EdgeFacetItr(TopModel* model, TopEdge e) : 
    m_model(model)
  {
    m_f_array = model->CreateEdgeFacetArray();
    m_eu = model->GetEdgeUse(e);
    Begin();
  }

  EdgeFacetItr(TopModel* model, TopEdgeUse eu) : 
    m_model(model)
  {
    m_f_array = model->CreateEdgeFacetArray();
    m_eu = eu;
    Begin();
  }  
  
  ~EdgeFacetItr()
  {
    m_model->ReleaseEdgeFacetArray(m_f_array);
  }

  void SetModel(TopModel* m) { m_model = m; }

  void SetEdge(TopEdge e) { m_eu = m_model->GetEdgeUse(e); }

  void SetEdgeUse(TopEdgeUse eu) { m_eu = eu; }
  
  void Begin() 
  { 
    m_curr = 0;
    m_f_array->Reset();
    m_model->Traverse(m_eu, TraverseCb, this, 1);
  }

  void         Next() { m_curr++; }

  TopFacet     GetCurr() { return m_f_array->Get(m_curr); }

  bool         IsValid() { return m_curr < m_f_array->Size(); }
};
#endif

/**
  Iterates over all the uses of the given vertex.
*/
class TOPS_API TopModel::VertexUseItr
{
  friend class TopModel;
  TopRawArray<TopVertexUse>*           m_vu_array;
  int                               m_curr;
  TopVertexUse                      m_vu;
  TopModel*                         m_model;
  bool                              m_non_manifold;

  static bool TraverseCb(TopModel* m, TopVertexUse vu, void* data) 
  {
    ((VertexUseItr*) data)->m_vu_array->Append(vu); 
    return true;
  }

 public: 
#ifdef TOP_USE_NON_ORIENTED_IMPLICIT_ENTITIES    
  VertexUseItr(TopModel* model, TopVertex v, bool non_manifold=false) : 
    m_model(model), m_non_manifold(non_manifold)
  {
    m_vu_array = model->CreateVertexUseArray();
    m_vu = model->GetVertexUse(v);
    Begin();
  }
#endif

  VertexUseItr(TopModel* model, TopVertexUse vu, bool non_manifold=false) : 
    m_model(model), m_non_manifold(non_manifold)
  {
    m_vu_array = model->CreateVertexUseArray();
    m_vu = vu;
    Begin();
  }  
  
  ~VertexUseItr()
  {
    m_model->ReleaseVertexUseArray(m_vu_array);
  }

  void SetModel(TopModel* m) { m_model = m; }

#ifdef TOP_USE_NON_ORIENTED_IMPLICIT_ENTITIES    
  void SetVertex(TopVertex v) { m_vu = m_model->GetVertexUse(v); }
#endif

  void SetVertexUse(TopVertexUse vu) { m_vu = vu; }
  
  void Begin() 
  { 
    m_curr = 0;
    m_vu_array->Reset();
    if (m_non_manifold)
      m_model->TraverseVU(m_model->GetNode(m_vu), TraverseCb, this, 1);
    else
      m_model->Traverse(m_vu, TraverseCb, this, 1);
  }

  void Next() { m_curr++; }

  TopVertexUse GetCurr() { return m_vu_array->Get(m_curr); }

  bool IsValid() { return m_curr < m_vu_array->Size(); }
};

/**
  Iterates over all the elements incident to the given vertex.
*/
class TOPS_API TopModel::VertexElemItr
{
  friend class TopModel;
  TopRawArray<TopElement>*           m_el_array;
  int                             m_curr;
  TopVertexUse                    m_vu;
  TopModel*                       m_model;
  bool                            m_non_manifold;

  static bool TraverseCb(TopModel* m, TopVertexUse vu, void* data) 
  {
    ((VertexElemItr*) data)->m_el_array->Append(TopElement(vu.GetElemHandle())); 
    return true;
  }

 public: 
#ifdef TOP_USE_NON_ORIENTED_IMPLICIT_ENTITIES  
  VertexElemItr(TopModel* model, TopVertex v, bool non_manifold=false) 
    : m_model(model), m_non_manifold(non_manifold)
  {
    m_el_array = model->CreateVertexElemArray();
    m_vu = model->GetVertexUse(v);
    Begin();
  }
#endif
  
  VertexElemItr(TopModel* model, TopVertexUse vu, bool non_manifold=false) 
    : m_model(model), m_non_manifold(non_manifold)
  {
    m_el_array = model->CreateVertexElemArray();
    m_vu = vu;
    Begin();
  }  
  
  ~VertexElemItr()
  {
    m_model->ReleaseVertexElemArray(m_el_array);
  }

  void SetModel(TopModel* m) { m_model = m; }

#ifdef TOP_USE_NON_ORIENTED_IMPLICIT_ENTITIES  
  void SetVertex(TopVertex v) { m_vu = m_model->GetVertexUse(v); }
#endif

  void SetVertexUse(TopVertexUse vu) { m_vu = vu; }
  
  void Begin() 
  { 
    m_curr = 0;
    m_el_array->Reset();
    if (m_non_manifold)
      m_model->TraverseVU(m_model->GetNode(m_vu), TraverseCb, this, 0);
    else
      m_model->Traverse(m_vu, TraverseCb, this, 0);
  }

  void Next() { m_curr++; }

  TopElement GetCurr() { return m_el_array->Get(m_curr); }

  bool IsValid() { return m_curr < m_el_array->Size(); }
};

#ifdef TOP_USE_NON_ORIENTED_IMPLICIT_ENTITIES  
/**
  Iterates over all the facets incident to the given vertex.
*/
class TOPS_API TopModel::VertexFacetItr
{
  friend class TopModel;
  TopRawArray<TopFacet>*           m_f_array;
  int                           m_curr;
  TopVertexUse                  m_vu;
  TopModel*                     m_model;
  bool                          m_non_manifold;

  static bool TraverseCb(TopModel* m, TopVertexUse vu, void* data) 
  {
    TopElement el = m->GetElem(vu);
    for (int i = 0; i < m->GetNFacets(vu); i++) {
      TopFacetUse fu = m->GetFacetUse(vu, i);
      if (m->GetFacetAnchor(el, fu.GetLocalId()))
        ((VertexFacetItr*) data)->m_f_array->Append(TopFacet(fu.GetHandle()));
    }
    return true;
  }

 public: 
  VertexFacetItr(TopModel* model, TopVertex v, bool non_manifold=false) : 
    m_model(model), m_non_manifold(non_manifold)
  {
    m_f_array = model->CreateVertexFacetArray();
    m_vu = model->GetVertexUse(v);
    Begin();
  }

  VertexFacetItr(TopModel* model, TopVertexUse vu, bool non_manifold=false) : 
    m_model(model), m_non_manifold(non_manifold)
  {
    m_f_array = model->CreateVertexFacetArray();
    m_vu = vu;
    Begin();
  }  
  
  ~VertexFacetItr()
  {
    m_model->ReleaseVertexFacetArray(m_f_array);
  }

  void SetModel(TopModel* m) { m_model = m; }

  void SetVertex(TopVertex v) { m_vu = m_model->GetVertexUse(v); }

  void SetVertexUse(TopVertexUse vu) { m_vu = vu; }
  
  void Begin() 
  { 
    m_curr = 0;
    m_f_array->Reset();
    if (m_non_manifold)
      m_model->TraverseVU(m_model->GetNode(m_vu), TraverseCb, this, 1);
    else
      m_model->Traverse(m_vu, TraverseCb, this, 1);
  }

  void         Next() { m_curr++; }

  TopFacet     GetCurr() { return m_f_array->Get(m_curr); }

  bool         IsValid() { return m_curr < m_f_array->Size(); }
};

/**
  Iterates over all the edges incident to the given vertex.
*/
class TOPS_API TopModel::VertexEdgeItr
{
  friend class TopModel;
  TopRawArray<TopEdge>*           m_e_array;
  int                          m_curr;
  TopVertexUse                 m_vu;
  TopModel*                    m_model;
  bool                         m_non_manifold;

  static bool TraverseCb(TopModel* m, TopVertexUse vu, void* data) 
  {
    TopElement el = m->GetElem(vu);
    for (int i = 0; i < m->GetNEdges(vu); i++) {
      TopEdgeUse eu = m->GetEdgeUse(vu, i);
      if (m->GetEdgeAnchor(el, eu.GetLocalId()))
        ((VertexEdgeItr*) data)->m_e_array->Append(TopEdge(eu.GetHandle()));
    }
    return true;
  }

  // Resets iterator position without recomputing elements.
  void First()
  {
    m_curr = 0;
  }
  
 public: 
  VertexEdgeItr(TopModel* model, TopVertex v, bool non_manifold=false) : 
    m_model(model), m_non_manifold(non_manifold)
  {
    m_e_array = model->CreateVertexEdgeArray();
    m_vu = model->GetVertexUse(v);
    Begin();
  }

  VertexEdgeItr(TopModel* model, TopVertexUse vu, bool non_manifold=false) : 
    m_model(model), m_non_manifold(non_manifold)
  {
    m_e_array = model->CreateVertexEdgeArray();
    m_vu = vu;
    Begin();
  }  
  
  ~VertexEdgeItr()
  {
    m_model->ReleaseVertexEdgeArray(m_e_array);
  }

  void SetModel(TopModel* m) { m_model = m; }

  void SetVertex(TopVertex v) { m_vu = m_model->GetVertexUse(v); }

  void SetVertexUse(TopVertexUse vu) { m_vu = vu; }
  
  void Begin() 
  { 
    m_curr = 0;
    m_e_array->Reset();
    if (m_non_manifold)
      m_model->TraverseVU(m_model->GetNode(m_vu), TraverseCb, this, 1);
    else
      m_model->Traverse(m_vu, TraverseCb, this, 1);
  }

  void Next() { m_curr++; }

  TopEdge GetCurr() { return m_e_array->Get(m_curr); }

  bool IsValid() { return m_curr < m_e_array->Size(); }
};
#endif

/**
  Iterates over all the elements incident to a node.

  This iterator assumes that the mesh is manifold. However, some non-manifold 
  cases are supported if "non_manifold" is true. The following constraints
  are imposed, though:
    - element adjacencies must have been properly computed, with support
    to the manifold cases that are expected to ocurr. Note that, currently,
    if TopModel::UpdateAdj() or TopModel::UpdateAdjReservoir(), for example,
    are used instead of TopModel::InsertElem(), adjacencies may not be 
    correctly computed when the mesh is not a manifold (see method documentation
    for details).
    - a node that is a vertex or a mid-edge node at one element
    must also be with respect to all the other elements;
*/

class TOPS_API TopModel::NodeElemItr
{
  friend class TopModel;
  TopRawArray<TopElement>*           m_el_array;
  int                             m_curr;
  TopNode                         m_node;
  TopVertexUse                    m_vu;
  TopEdgeUse                      m_eu;
  TopModel*                       m_model;
  bool                            m_non_manifold;

  static bool TraverseEUCb(TopModel* m, TopEdgeUse eu, void* data) 
  {
    ((NodeElemItr*) data)->m_el_array->Append(TopElement(eu.GetElemHandle())); 
    return true;
  }
  static bool TraverseVUCb(TopModel* m, TopVertexUse vu, void* data) 
  {
    ((NodeElemItr*) data)->m_el_array->Append(TopElement(vu.GetElemHandle())); 
    return true;
  }

 public: 
  NodeElemItr(TopModel* model, TopNode n, bool non_manifold = false) 
    : m_model(model), m_non_manifold(non_manifold)
  {
    m_el_array = model->CreateNodeElemArray();
    SetNode(n);
    Begin();
  }
    
  ~NodeElemItr()
  {
    m_model->ReleaseNodeElemArray(m_el_array);
  }

  void SetModel(TopModel* m) { m_model = m; }

  void SetNode(TopNode n) 
  { 
    m_node = n; 
#ifdef TOP_USE_NON_ORIENTED_IMPLICIT_ENTITIES
    m_vu = m_model->GetVertexUse(m_model->GetVertex(n));
    if (!m_vu.IsValid())
      m_eu = m_model->GetEdgeUse(m_model->GetEdge(n));
#else
    m_vu = m_model->GetVertexUse(m_model->GetElem(n), n);
    if (!m_vu.IsValid())
      m_eu = m_model->GetEdgeUse(m_model->GetElem(n), n);
#endif
  }
  
  void Begin() 
  { 
    m_curr = 0;
    m_el_array->Reset();
    if (m_vu.IsValid()) { // VertexNode
      if (m_non_manifold)
        m_model->TraverseVU(m_model->GetNode(m_vu), TraverseVUCb, this, 1);
      else
        m_model->Traverse(m_vu, TraverseVUCb, this, 0);
    } else { // EdgeNode
      if (m_non_manifold)
        m_model->TraverseEU(m_model->GetNode(m_eu, 1), TraverseEUCb, this, 1);
      else
        m_model->Traverse(m_eu, TraverseEUCb, this, 0);
    }
  }

  void Next() { m_curr++; }

  TopElement GetCurr() { return m_el_array->Get(m_curr); }

  bool IsValid() { return m_curr < m_el_array->Size(); }
};

#endif

