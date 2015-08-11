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

#ifndef _TOP_EDGEHASH_H
#define _TOP_EDGEHASH_H

class TopEdgeUse;

class TopEdgeHash {
  TopModel*    m_model;
  int          m_dim;
  TopEdgeUse*  m_hash;
  
public:
  TopEdgeHash(TopModel* model, int nedges);
  ~TopEdgeHash();

  void  Clear();
  const TopEdgeUse& Find(const TopEdgeUse& in) const;

  void  Set (const TopEdgeUse& in) const;
  const TopEdgeUse& Get (const TopEdgeUse& in) const;
private:
  unsigned int Hash (const TopEdgeUse& e) const;
};

#endif
