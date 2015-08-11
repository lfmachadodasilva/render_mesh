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

#ifndef _TOP_NODE_H
#define _TOP_NODE_H

#include "defines.h"
#include "pool.h"
#include "handles.h"

class TopModel;
class IOStream;

class TopConcreteNode
{
public:
  struct ElemNode {
    TopElement el;
    ElemNode*  next;
    ElemNode(TopElement e, ElemNode* n) : el(e), next(n) {}
  };
  
private:  
  friend class TopModel;

  static TopPool<ElemNode*>*   m_pool;

  unsigned char m_state; // Node state: CONCRETE, EMPTY or UNLINKED.
  ElemNode*   m_elem;
  int m_id;

  static void ReleaseMemory()
  {
    while (!m_pool->IsEmpty())
      delete m_pool->Get();
  }

  ElemNode* NewElemNode(TopElement el)
  {
    if (!m_pool->IsEmpty()) {
      ElemNode* eln = m_pool->Get();
      eln->el = el;
      eln->next = 0;
      return eln;
    } else 
      return new ElemNode(el, 0);
  }

  void CopyElemNodes(TopConcreteNode* cn)
  {
    ElemNode* prev_eln = NULL;
    for (ElemNode* eln = cn->m_elem; eln; eln = eln->next) {
      ElemNode* new_eln = NewElemNode(eln->el);
      if (m_elem == NULL)
        m_elem = new_eln;
      else if (prev_eln)
        prev_eln->next = new_eln;
      prev_eln = new_eln;
    }
  }


public:
  
  TopConcreteNode() : m_state(1), m_elem(0), m_id(-1) {}

  ~TopConcreteNode() 
  { 
    m_id = -1;
    m_state = 0; 
    while (m_elem) {
      ElemNode* eln = m_elem;
      m_elem = m_elem->next;
      delete eln;
    }
  }

  void SetId(int id) { m_id = id; }
  int GetId() { return m_id; }
  
  /**
      Adds an element to the list of elements using this node. If the list is not
    empty, the element will be inserted in the second position.      
      If element is CONCRETE, it will be the representative of a "manifold block"
    around the node, and therefore will hold anchors to the relevant entities (facets,
    edges or vertices) in which the node is contained. If the element is VIRTUAL, 
    it will represent itself. Elements marked as EMPTY are not allowed in the list.      
      If the list contains CONCRETE elements, then one of them must be the 
    head of the list. If the head element is VIRTUAL, then the node is disconnected
    from the model, but it is still being hold by an entity lock. An empty list
    means that the node is not attached to any element.
      Cohesive elements must never be in the list, since this kind of element 
    may have more than one reference to the same node, what leads to ambiguities 
    on edges. 
      If the first element is CONCRETE, the node represents the
  */
  void AddElem(TopElement el) 
  {
    // The element CANNOT be inserted at the beginning of the list, 
    // if the list is not empty, because the first element is used as a 
    // shortcut to the vertex-bit (and edge-bit, in the case of non-linear
    // elements).
    ElemNode* eln = NewElemNode(el);
    if (m_elem) {
      eln->next = m_elem->next;
      m_elem->next = eln;
    } else {
      m_elem = eln;
    }
  }

  /**
      Gets the first entry of the node's element list.
  */
  ElemNode* GetElemNode() 
  { 
    return m_elem; 
  }

  /**
      Removes element from the node's element list.
  */
  void RemElem(TopElement el)
  {
    ElemNode* prev = 0;
    for (ElemNode* eln = m_elem; eln; eln = eln->next) {
      if (eln->el == el) {
        m_pool->Put(eln);
        if (prev)
          prev->next = eln->next;
        else
          m_elem = eln->next;
      }
      prev = eln;
    }
  }

  /**
      Removes the entry after the given one in the node's element list.
    If eln == NULL, the first entry is removed.
  */
  void RemNextElemNode(ElemNode* eln =0) 
  {
    if (eln) {
      m_pool->Put(eln->next);
      eln->next = eln->next->next;
    } else { // Removes the first element
      m_pool->Put(m_elem);
      m_elem = m_elem->next;
    }
  }

  /**
      Clears the node's element list.
  */
  void ClearElems()
  {
    while (GetElemNode())
      RemNextElemNode(0);
  }

  // EMPTY = 0 is used for the initialization of nodes array of the model.
  int          IsEmpty() { return m_state == 0; }
  void         MarkAsEmpty() { m_state = 0; }
  int          IsConcrete() { return m_state == 1; }
  void         MarkAsConcrete() { m_state = 1; }
  int          IsUnlinked() { return m_state == 2; }
  void         MarkAsUnlinked() { m_state = 2; }

  bool Serialize(IOStream* io);
  bool Deserialize(IOStream* io);
};

#endif
