
#ifndef TOPS_UTIL_REFINE4KOPERATORS_H
#define TOPS_UTIL_REFINE4KOPERATORS_H

#include <tops/tops.h>

#ifdef TOP_USE_NON_ORIENTED_IMPLICIT_ENTITIES

class TopRefinement4KOperators;

/**
	Listener for refinement operations of 4K meshes.
*/
class TOPS_API TopModelRefinement4KListener
{
public:
	virtual ~TopModelRefinement4KListener() {}

  virtual void EdgeSplit (TopRefinement4KOperators* m,
                          TopElement oldel[3], 
                          TopElement newel[6]) 
  {
  }

  virtual void EdgeSwapped(TopRefinement4KOperators* m,
                           TopElement oldel[2], 
                           TopElement newel[2]) 
  {
  }

  virtual void EdgeCollapsed(TopRefinement4KOperators* m,
                             TopElement oldel[4], 
                             TopElement newel[2]) 
  {
  }

  virtual void CohesiveInserted(TopRefinement4KOperators* m, TopElement el) 
  {
  }
};

class TOPS_API TopRefinement4KOperators
{
public:
  TopRefinement4KOperators (TopModel* model);

  ~TopRefinement4KOperators ();

  TopModel* GetModel ()
  {
    return m_model;
  }

  /** @deprecated */
  void SplitFacet(TopFacet f, TopElement el_out[6]);

  /** @deprecated */
  void SwapFacet(TopFacet f, TopElement el_out[6]);

  void SetRefinement4KListener(TopModelRefinement4KListener* l)
  {
    m_refinement4k_listener = l;
  }

  TopModelRefinement4KListener* GetRefinement4KListener()
  {
    return m_refinement4k_listener;
  }

  /**  
      Splits an edge of a 4-8 mesh (T3 or T6 elements) and notifies edition listener of 
    the changes.
      When one of the edge-use local ids of the split edge is different from zero,
    the algorithm will proceed recursively.
      During the split process, some new entities (nodes, vertices, edges, elements)
    may be inserted into the model.
      The split modifications are notified by the methods: SplitElem(), SplitEdge(),
    InsertNode(), InsertVertex(), InsertEdge(), on the model edition listener.
      When SplitElem() and SplitEdge() are called, the old element is 
    already disconnect from the model. Thus, only the local entities of this 
    element (facet-use, edge-use and vertex-use) can be retrieved. Facets, edges 
    and vertices are not guaranteed. However, in SplitEdge(), retrieving the
    facet associated to the edge is allowed. 
      The main uses for the above callbacks are to move attributes from the old 
    entities to the new ones.
    
      Split node order:
    @verbatim
                  2                                        2 
                /   \                                    / | \
              /       \                                /   |   \
            5    El0'   4                            5     8     4
          /               \                        /  El0  |  El1  \
        /                   \                    /         |         \
       0----------3----------1                  0----6-----3----7-----1
       .......................---> e            .......................---> e
       *----------*----------*                  *----*----* *---*-----*
                El2'                 ====>         El4         El5
       *----------*----------*                  *----*----* *---*-----*
                                               
       10---------12---------9                  10---16----12---15----9
        \                   /                    \         |         /
          \               /                        \  El2  |  El3  /
           13    El1'   14                           13    17    14
              \        /                               \   |    /
                \    /                                   \ |  /
                  11                                       11 
    @endverbatim 
    @see TopModelEditListener
  */
  void SplitEdge4K8(TopEdge e);
  
  /**
      Swaps an edge of a 4-8 mesh (T3 or T6 elements) and notifies edition listener of 
    the changes. 
      When one of the edge-use local ids of the swap edge is different from zero,
    the algorithm will split other edges recursively, by calling SplitEdge4K8().
    Swaps are only allowed in internal edges shared by two non-cohesive elements.
      The swap modifications are notified by the methods: SwapElem(), SwapEdge(), on
    the model edition listener.
      When SwapElem() and SwapEdge() are called, the old element is 
    already disconnect from the model. Thus, only the local entities of this 
    element (facet-use, edge-use and vertex-use) can be retrieved. Facets, edges 
    and vertices are not guaranteed. However, in SwapEdge(), retrieving the
    facet associated to the edge is allowed. 
      The main uses for the above callbacks are to move attributes from the old 
    entities to the new ones.
    
      Swap node order:
    @verbatim
                   2                                    2           
                 /   \                                / | \         
               /       \                            /   |   \       
             6    El0'   5                        6     |     5
           /               \                    /       |       \   
         /                   \                /         |         \ 
        0----------4----------1    ====>     0    El0   4   El1    1
         \                   /                \         |         / 
           \               /                    \       |       /   
            7     El1'   8                       7      |     8     
              \        /                           \    |   /       
                \    /                               \  | /         
                  3                                     3            
    @endverbatim 
    @see TopModelEditListener    
  */
  void SwapEdge4K8(TopEdge e);

  /**
      Collapses an edge incident to a vertex at the center of a 4-facet (or 
    2-face, if the vertex is on the boundary of the mesh) pattern of a 
    4K triangle mesh.
      This method can be used to undo a split edge operation (see SplitEdge4K8), while
    edge swapping should be reversed by swaping back the resulting edge (see SwapEdge4K8).    
      Cohesive elements along the edges to collapse are not supported. No consistency
    checks are performed by this method.
      The mesh modifications are notified by the methods of TopModelEditListener: 
    RemoveEdge(), RemoveVertex(), RemoveNode(), MergeEdge(), and MergeElem().

                  *                                        * 
                /   \                                    / | \
              /       \                                /   |   \
            *    El0'   *                            *     *     *
          /               \                        /  El0  |  El1  \
        /                   \                    /         |         \
       *----------*----------*    <========     *----*-----X----*-----*
        \                   /                    \         |         /
          \               /                        \  El2  |  El3  /
            *    El1'   *                            *     *      *
              \        /                               \   |    /
                \    /                                   \ |  /
                  *                                        *  
                                  
       X = colv
       Either of the two vertical edges (in this example) = cole
  */
  void CollapseEdge4K8(TopEdge cole, TopVertex colv);

private:
  class TOPS_API ModelEditListener : public TopModelEditListener
  {
  public:
    ModelEditListener ()
    {
    }

    void SetRefinement4KOperators (TopRefinement4KOperators* ref)
    {
      m_ref = ref;
    }

    virtual ~ModelEditListener() 
    {
    }

    virtual void InsertElem(TopModel* m, TopElement el) 
    {
      if (m->IsCohesive(el)&& m_ref->m_refinement4k_listener)
          m_ref->m_refinement4k_listener->CohesiveInserted(m_ref, el);
    }

  private:
    TopRefinement4KOperators* m_ref;
  };

private:
  void SplitFacetGetFacetUses(const TopFacet& f, TopFacetUse* fu_out, TopFacetUse* fum_out);
  void MakeDiamondFacetUse(const TopFacetUse& fu, TopFacetUse* fu_out);
  void MakeDiamond(const TopFacet& f, TopFacetUse* fu_out, TopFacetUse* fum_out);

  void SplitFacetSaveNodes(TopElement el, TopElement elm, TopElement coh, TopNode sn[18]);
  void SplitFacetSaveAttribs(TopElement el, TopElement elm, 
    void* fatt[4], void* eatt[4], void* vatt[6]);
  void SplitFacetRestoreAttribs(TopElement sel[6],
    void* fatt[4], void* eatt[4], void* vatt[6]);
  void SwapFacetSaveAttribs(TopElement el, TopElement elm, 
    void* fatt[4], void* eatt[4], void* vatt[6]);
  void SwapFacetRestoreAttribs(TopElement sel[6],
    void* fatt[4], void* eatt[4], void* vatt[6]);
  void SplitFacetNotifySplitElem(
    TopElement el, TopElement elm, TopElement coh, TopElement sel[6]);
  void SplitFacetSaveAdjCoh(TopElement el, TopElement elm, TopElement adj_coh[4]);
  void SwapFacetNotifySwapElem(TopElement el, TopElement elm, TopElement sel[6]);

  void CollapseEdge4K8SaveAttribs(TopElement elems[4],
    void* fatt[4], void* eatt[4], void* vatt[6]);
  void CollapseEdge4K8RestoreAttribs(TopElement elems[2],
    void* fatt[4], void* eatt[4], void* vatt[6]);
  void CollapseEdge4K8SaveNodes(TopElement colelems[4], TopNode sn[4][6]);
  void CollapseEdge4K8SaveAdjCoh(TopElement colelems[4], TopElement adj_coh[4]);
  void CollapseEdge4K8NotifyMergeElem(
    TopElement oldelems[4], TopElement newelems[2]);

private:
  TopModel* m_model;  
  TopModelRefinement4KListener* m_refinement4k_listener;
  ModelEditListener m_model_edit_listener;
};

#endif

#endif