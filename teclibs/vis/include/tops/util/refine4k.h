
#ifndef TOP_REFINE_4K_H
#define TOP_REFINE_4K_H

#include <tops/tops.h>
#include "refine4koperators.h"

#ifdef TOP_USE_NON_ORIENTED_IMPLICIT_ENTITIES

// Whether refinement depth will be stored at faces
//#define TOP_REFINE_4K_USE_REFINEMENT_DEPTH

/**
  Manages refinement of 4K triangular meshes.
  It records refinement data so that the mesh can be coarsen back.
*/
//TODO optimize performance
//TODO optimize memory
//TODO allows to associate more than one attribute per entity in TopS
//TODO the attributes set by the refinement methods should not affect or
//TODO be affected by the attributes set by the application.
//TODO More efficient memory management of edge attributes
class TOPS_API TopRefinement4K
{
public:
  TopRefinement4K(TopModel* m);

  ~TopRefinement4K();

  TopModel* GetModel() const { return m_model; }

  /**
    Refinement operator.
    Splits an edge into two new others.
    (see TopModel::SplitEdge4K8)
  */
  void SplitEdge(TopEdge e);

  /**
    Coarsesing operator. 
    Undoes a previous split of an edge around the vertex. 
    The corresponding edge is determined automatically from the
    edge split history.
  */
  void SplitVertex(TopVertex v);

  /**
    Returns whether the vertex can be split. It can only be split if the surrounding 
    elements form a four-face pattern (see TopModel::CollapseEdge4K8), or a 
    two-face pattern, when the vertex is on the boundary of the mesh.
  */
  bool CanSplitVertex(TopVertex v) const;

  /**
    Gets the depth of an edge in the refinement tree.
  */
  int GetEdgeDepth(TopEdge e) const;

  int GetRefinementDepth(const TopFace& f) const
  {
    int* att = (int*) m_model->GetAttrib(f);
    return (att != NULL) ? *att : 0;
  }

  int GetRefinementDepth(const TopEdge& e) const
  {
#ifdef TOP_REFINE_4K_USE_REFINEMENT_DEPTH
    TopEdgeUse eu = m_model->GetEdgeUse(e);
    int max_depth = GetRefinementDepth(m_model->GetFace(m_model->GetElem(eu), 0));
    TopEdgeUse eum = m_model->GetMate(eu, 0);
    if (eum.IsValid()) {
      int depth = GetRefinementDepth(m_model->GetFace(m_model->GetElem(eum), 0));
      max_depth = depth > max_depth ? depth : max_depth;        
    }
    return max_depth;
#else
    TopEdgeUse eu = m_model->GetEdgeUse(e);
    if (m_model->IsCohesive(m_model->GetElem(eu)))
      eu = m_model->GetMate(eu, 0);
    int max_depth = GetCoarseningDepth(e);
    int depth = GetCoarseningDepth(m_model->GetEdge(m_model->GetElem(eu), (m_model->GetLocalId(eu) + 1) % 3));
    max_depth = depth > max_depth ? depth : max_depth;    
    depth = GetCoarseningDepth(m_model->GetEdge(m_model->GetElem(eu), (m_model->GetLocalId(eu) + 2) % 3));
    max_depth = depth > max_depth ? depth : max_depth;

    TopEdgeUse eum = m_model->GetMate(eu, 0);
    if (eum.IsValid()) {
      if (m_model->IsCohesive(m_model->GetElem(eum))) {
        eum = m_model->GetEdgeUse(m_model->GetElem(eum), (m_model->GetLocalId(eum) + 1) % 3);
        eum = m_model->GetMate(eum, 0);
      }
      int depth = GetCoarseningDepth(m_model->GetEdge(eum));
      max_depth = depth > max_depth ? depth : max_depth;        
      depth = GetCoarseningDepth(m_model->GetEdge(m_model->GetElem(eum), (m_model->GetLocalId(eum) + 1) % 3));
      max_depth = depth > max_depth ? depth : max_depth;
      depth = GetCoarseningDepth(m_model->GetEdge(m_model->GetElem(eum), (m_model->GetLocalId(eum) + 2) % 3));
      max_depth = depth > max_depth ? depth : max_depth;
    }
    return max_depth;
#endif
  }

  int GetCoarseningDepth(const TopEdge& e) const
  {
    int* att = (int*) m_model->GetAttrib(e);
    return (att != NULL) ? *att : 0;
  }

  /****************************
    Utility functions
  *****************************/
  /**
    Refines a facet around the vertex for a tolerance value.
    (see TopUtil::RefineVertexFacet())
  */
  TopFacet RefineVertexFacet(TopVertex v, TopFacet f, double tol);

  void RefineInRegion(double x0, double y0, double z0, double radius, int maxdepth);

  void CoarsenOutRegion(double x0, double y0, double z0, double radius);

private:
  class TOPS_API Refinement4KListener : public TopModelRefinement4KListener
  {
  public:
    Refinement4KListener(TopRefinement4K* r)
    {
      m_refinement = r;
    }
    virtual ~Refinement4KListener() {}
    void EdgeSplit(TopRefinement4KOperators* ref,
                   TopEdge olde[2], 
                   TopEdge newe[4], 
                   TopElement oldel[3], 
                   TopElement newel[6])
    {
      TopModel* m = ref->GetModel();
#ifdef TOP_REFINE_4K_USE_REFINEMENT_DEPTH
      TopFace oldf[2] = {
        m->GetFace(oldel[0], 0), 
        oldel[1].IsValid() ? m->GetFace(oldel[1], 0) : TopFace()
      };
      // Records refinement data.      
      int ref_depth = m_refinement->GetRefinementDepth(oldf[0]);
      assert(!oldel[1].IsValid() || m_refinement->GetRefinementDepth(oldf[1]) == ref_depth);
      // Clears attributes of the two split faces.
      int* oldatt = (int*) m->GetAttrib(oldf[0]);
      if (oldatt) {
        m_refinement->m_pool.Put(oldatt);
        m->SetAttrib(oldf[0], NULL);
      }
      if (oldf[1].IsValid()) {
        oldatt = (int*) m->GetAttrib(oldf[1]);
        if (oldatt) {
          m_refinement->m_pool.Put(oldatt);
          m->SetAttrib(oldf[1], NULL);
        }
      }
      // Sets the refinement depth of the four new faces.
      for (int i = 0; i < 4; i++) {
        if (newel[i].IsValid()) {
          int* att = NewAttrib();
          *att = ref_depth + 1;
          m->SetAttrib(m->GetFace(newel[i], 0), att);
        }
      }

      // Records coarsening data.
      int crs_depth = m_refinement->GetCoarseningDepth(olde[0]);
      int max_crs_depth = crs_depth;
      for (int i = 0; i < 4; i++) {
        if (newel[i].IsValid()) {
          TopEdge e = m->GetEdge(newel[i], 0);
          int depth = m_refinement->GetCoarseningDepth(e);
          max_crs_depth = depth > max_crs_depth ? depth : max_crs_depth;
        }
      }
      // Clears the attributes of the two split edges.
      oldatt = (int*) m->GetAttrib(olde[0]);
      if (oldatt) {
        m_refinement->m_pool.Put(oldatt);
        m->SetAttrib(olde[0], NULL);
      }
      if (olde[1].IsValid()) {
        assert(m->GetEdgeUse(olde[0]) != m->GetEdgeUse(olde[1]));
        oldatt = (int*) m->GetAttrib(olde[1]);
        if (oldatt) {
          m_refinement->m_pool.Put(oldatt);
          m->SetAttrib(olde[1], NULL);
        }
      }
      // Sets the attributes of the four new edges originated from the two split edges.
      for (int i = 0; i < 4; i++) {
        if (newe[i].IsValid()) {
          int* att = NewAttrib();
          *att = crs_depth;
          m->SetAttrib(newe[i], att);
        }
      }
      // Sets the depth of the two new edges created across the split edges.
      int* att = NewAttrib();
      *att = max_crs_depth + 1;
      m->SetAttrib(m->GetEdge(newel[0], 2), att);
      if (newel[2].IsValid()) {
        att = NewAttrib();
        *att = max_crs_depth + 1;
        m->SetAttrib(m->GetEdge(newel[2], 1), att);
      }
#else
      int* oldatt = NULL; 

      // Records coarsening data.
      int crs_depth = m_refinement->GetCoarseningDepth(olde[0]);
      int max_crs_depth = crs_depth;
      for (int i = 0; i < 4; i++) {
        if (newel[i].IsValid()) {
          TopEdge e = m->GetEdge(newel[i], 0);
          int depth = m_refinement->GetCoarseningDepth(e);
          max_crs_depth = depth > max_crs_depth ? depth : max_crs_depth;
        }
      }
      // Clears the attributes of the two split edges.
      oldatt = (int*) m->GetAttrib(olde[0]);
      if (oldatt) {
        m_refinement->m_pool.Put(oldatt);
        m->SetAttrib(olde[0], NULL);
      }
      if (olde[1].IsValid()) {
        assert(m->GetEdgeUse(olde[0]) != m->GetEdgeUse(olde[1]));
        oldatt = (int*) m->GetAttrib(olde[1]);
        if (oldatt) {
          m_refinement->m_pool.Put(oldatt);
          m->SetAttrib(olde[1], NULL);
        }
      }
      // Sets the attributes of the four new edges originated from the two split edges.
      for (int i = 0; i < 4; i++) {
        if (newe[i].IsValid()) {
          int* att = NewAttrib();
          *att = crs_depth;
          m->SetAttrib(newe[i], att);
        }
      }
      // Sets the depth of the two new edges created across the split edges.
      int* att = NewAttrib();
      *att = max_crs_depth + 1;
      m->SetAttrib(m->GetEdge(newel[0], 2), att);
      if (newel[2].IsValid()) {
        att = NewAttrib();
        *att = max_crs_depth + 1;
        m->SetAttrib(m->GetEdge(newel[2], 1), att);
      }
#endif
    }
    void EdgeSwapped(TopRefinement4KOperators* ref,
                     TopEdge olde, 
                     TopEdge newe, 
                     TopElement oldel[2], 
                     TopElement newel[2])
    {
      TopModel* m = ref->GetModel();
#ifdef TOP_REFINE_4K_USE_REFINEMENT_DEPTH
      TopFace oldf[2] = {m->GetFace(oldel[0], 0), m->GetFace(oldel[1], 0)};
      // Records refinement data.      
      int ref_depth = m_refinement->GetRefinementDepth(oldf[0]);
      assert(m_refinement->GetRefinementDepth(oldf[1]) == ref_depth);
      // Clears attributes of the two swapped faces.
      for (int i = 0; i < 2; i++) {
        int* oldatt = (int*) m->GetAttrib(oldf[i]);
        if (oldatt) {
          m_refinement->m_pool.Put(oldatt);
          m->SetAttrib(oldf[i], NULL);
        }
      }
      // Sets the refinement depth of the four new faces.
      for (int i = 0; i < 2; i++) {
        int* att = NewAttrib();
        *att = ref_depth + 1;
        m->SetAttrib(m->GetFace(newel[i], 0), att);
      }

      // Records coarsening data.
      int crs_depth = m_refinement->GetCoarseningDepth(olde);
      // Clears the attributes of the old edge.
      int* oldatt = (int*) m->GetAttrib(olde);
      if (oldatt) {
        m_refinement->m_pool.Put(oldatt);
        m->SetAttrib(olde, NULL);
      }
      // Sets the attributes of the new edge.
      int* att = NewAttrib();
      *att = crs_depth;
      m->SetAttrib(newe, att);
#else
      // Records coarsening data.
      int crs_depth = m_refinement->GetCoarseningDepth(olde);
      // Clears the attributes of the old edge.
      int* oldatt = (int*) m->GetAttrib(olde);
      if (oldatt) {
        m_refinement->m_pool.Put(oldatt);
        m->SetAttrib(olde, NULL);
      }
      // Sets the attributes of the new edge.
      int* att = NewAttrib();
      *att = crs_depth;
      m->SetAttrib(newe, att);
#endif
    }
    void EdgeCollapsed(TopRefinement4KOperators* ref,
                       TopEdge reme[2], 
                       TopEdge olde[2], 
                       TopEdge newe, 
                       TopElement oldel[4], 
                       TopElement newel[2])
    {
      TopModel* m = ref->GetModel();
#ifdef TOP_REFINE_4K_USE_REFINEMENT_DEPTH
      // Computes the depth of the split edge.
      int split_depth = m_refinement->GetCoarseningDepth(olde[0]);
      // Clears the attributes of the old edges.
      for (int i = 0; i < 2; i++) {
        int* oldatt = (int*) m->GetAttrib(olde[i]);
        if (oldatt) {
          m_refinement->m_pool.Put(oldatt);
          m->SetAttrib(olde[i], NULL);
        }
        if (reme[i].IsValid()) {
          oldatt = (int*) m->GetAttrib(reme[i]);
          if (oldatt) {
            m_refinement->m_pool.Put(oldatt);
            m->SetAttrib(reme[i], NULL);
          }
        }
      }
      // Sets the depth for the new edge.
      int* att = NewAttrib();
      *att = split_depth;
      m->SetAttrib(newe, att); 

      TopFace oldf[4] = {
        m->GetFace(oldel[0], 0), 
        m->GetFace(oldel[1], 0),
        oldel[2].IsValid() ? m->GetFace(oldel[2], 0) : TopFace(),
        oldel[3].IsValid() ? m->GetFace(oldel[3], 0) : TopFace()
      };
      // Computes the depth of the old faces.
      int ref_depth = m_refinement->GetRefinementDepth(oldf[0]);
      assert(ref_depth > 0);
      // Clears the attributes of the old edges.
      for (int i = 0; i < 4; i++) {
        if (oldel[i].IsValid()) {
          int* oldatt = (int*) m->GetAttrib(oldf[i]);
          if (oldatt) {
            m_refinement->m_pool.Put(oldatt);
            m->SetAttrib(oldf[i], NULL);
          }
        }
      }
      // Sets the depth for the new faces.
      for (int i = 0; i < 2; i++) {
        if (newel[i].IsValid()) {
          int* att = NewAttrib();
          *att = ref_depth - 1;
          m->SetAttrib(m->GetFace(newel[i], 0), att); 
        }
      }
#else
      // Computes the depth of the split edge.
      int split_depth = m_refinement->GetCoarseningDepth(olde[0]);
      // Clears the attributes of the old edges.
      for (int i = 0; i < 2; i++) {
        int* oldatt = (int*) m->GetAttrib(olde[i]);
        if (oldatt) {
          m_refinement->m_pool.Put(oldatt);
          m->SetAttrib(olde[i], NULL);
        }
        if (reme[i].IsValid()) {
          oldatt = (int*) m->GetAttrib(reme[i]);
          if (oldatt) {
            m_refinement->m_pool.Put(oldatt);
            m->SetAttrib(reme[i], NULL);
          }
        }
      }
      // Sets the depth for the new edge.
      int* att = NewAttrib();
      *att = split_depth;
      m->SetAttrib(newe, att); 
#endif
    }

#ifndef TOP_REFINE_4K_USE_REFINEMENT_DEPTH
    // Handles cohesive elements
    virtual void CohesiveInserted(TopRefinement4KOperators* ref, TopElement el)
    {
      TopModel* m = ref->GetModel();
      // Duplicates edge attributes
      assert(!m->IsCohesive(m->GetElem(m->GetEdge(el, 0))));
      assert(!m->IsCohesive(m->GetElem(m->GetEdge(el, 1))));
      int* oldatt = (int*) m->GetAttrib(m->GetEdge(el, 0));
      int lid = 1;
      if (oldatt == NULL) {
        oldatt = (int*) m->GetAttrib(m->GetEdge(el, 1));
        lid = 0;
      }
      if (oldatt != NULL) {
        int* att = NewAttrib();
        *att = *oldatt;
        m->SetAttrib(m->GetEdge(el, lid), att); 
      }
    }
#endif


  private:
    int* NewAttrib()
    {
      if (m_refinement->m_pool.IsEmpty())
        return new int[1];
      else
        return (int*) m_refinement->m_pool.Get();
    }

    TopRefinement4K* m_refinement;
  };

private:
  void Start();
  void Finish();

private:
  TopPool<int*> m_pool;
  TopModel* m_model;
  Refinement4KListener* m_edit_listener;
  TopRefinement4KOperators m_operators;
};

#endif

#endif
