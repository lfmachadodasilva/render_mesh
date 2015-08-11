
#ifndef TOP_LISTENERS_H
#define TOP_LISTENERS_H

class TopModel;

/**
  Mesh modification event listener. 

  When the mesh is modified, the corresponding method of a listener 
  registered at the model is invoked in order to notify of a model changes.
*/
class TOPS_API TopModelEditListener
{
public:
  virtual ~TopModelEditListener() {}

  /** Invoked after a new node is inserted into the model. */
  virtual void InsertNode(TopModel* m, TopNode n) {}
  /** Invoked before an existing is removed from the model. */
  virtual void RemoveNode(TopModel* m, TopNode n) {}
  /** Invoked after a new node is inserted into the model. */
  virtual void InsertElem(TopModel* m, TopElement el) {}
  /** Invoked before an existing element is removed from the model. */
  virtual void RemoveElem(TopModel* m, TopElement el) {}
  /** Invoked after an existing node is duplicated. */
  virtual void DuplicateNode(TopModel* m, TopNode old_n, TopNode new_n) {}

  /**
    Mesh adaptivity
  */
  /** Invoked after an existing element is split into two new elements. */
  virtual void SplitElem(TopModel* m, TopElement old_el, TopElement new_el[2]) {}
  /** Invoked after two elements are replaced with two other elements. */
  virtual void SwapElem(TopModel* m, TopElement old_el[2], TopElement new_el[2]) {}
  /** Invoked after two elements are merged into a single one. */
  virtual void MergeElem(TopModel* m, TopElement old_el[2], TopElement new_el) {}
  /**
    Experimental (may change in the future!)
  */
  virtual void JoinFacet(TopModel* m, TopFacetUse f1, TopFacetUse f2) {}

  /** Invoked when a node of an existing element is replaced by another. */
//TODO Correct semantics: sometimes it is called before the replacement and after at others.
  virtual void ReplaceElemNode(TopModel* m, TopElement el, int i, 
                               TopNode old_n, TopNode new_n) {}
};

/**
    Mesh consistency check listener.
*/
class TOPS_API TopModelConsistencyListener
{
public:
  virtual ~TopModelConsistencyListener() {}
  virtual bool ManifoldFailed(TopModel* m, TopNode n) { return false; }
  virtual bool CohesiveFailed(TopModel* m, TopElement coh) { return false; }
#ifdef TOP_USE_NON_ORIENTED_IMPLICIT_ENTITIES    
  virtual bool FacetAnchorFailed(TopModel* m, TopFacetUse fu) { return false; }
  virtual bool EdgeAnchorFailed(TopModel* m, TopEdgeUse eu) { return false; }
  virtual bool VertexAnchorFailed(TopModel* m, TopVertexUse vu) { return false; }
#endif
};

#endif
