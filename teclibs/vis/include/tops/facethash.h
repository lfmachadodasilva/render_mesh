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

#ifndef _TOP_FACETHASH_H
#define _TOP_FACETHASH_H

class TopFacetUse;

#if 1
class TopFacetHash {
  TopModel*    m_model;
  int          m_dim;
  TopFacetUse* m_hash;
  
  unsigned int Hash (const TopFacetUse& fu) const
  {
    unsigned int s = 0;
    int n = m_model->GetNNodes(fu);
    for (int i=0; i<n; i++) {
      // s += m_model->GetNode(fu,i).GetHandle() % m_dim;
      s += m_model->GetNode(fu,i).GetHandle();
    }
    return s; 
  }

public:
	TopFacetHash (TopModel* model, int nfaces);
	~TopFacetHash ();

 void  Clear();
 /**
     Look-up for a mate facet-use. If none was found, inserts the 
   given one.
 */
 const TopFacetUse& FindMate (const TopFacetUse& in) const;

 void  Set (const TopFacetUse& in) const;
 const TopFacetUse& Get (const TopFacetUse& in) const;
 const TopFacetUse& GetMate (const TopFacetUse& in) const;
private:
};
#else
#include "hash.h"

class MyFacetUse
{
  static TopModel* s_model;
  TopFacetUse m_fu;
public:  
  
  static void SetModel (TopModel* m) { s_model = m; }
  MyFacetUse() : m_fu() {}
  MyFacetUse(const TopFacetUse& fu) : m_fu(fu) {}
  
  operator int () const
  {
    int s = 0;
    int n = s_model->GetNNodes(m_fu);
    for (int i=0; i<n; i++) {
      s += s_model->GetNode(m_fu,i).GetHandle();
    }
    return s; 
  }

  bool operator== (const MyFacetUse& mfu) 
  { 
    return s_model->MatchNodes(m_fu, mfu.m_fu); 
  }
};

class TopFacetHash : public TopHash<MyFacetUse, TopFacetUse> {
  TopModel*    m_model;

public:
	TopFacetHash (TopModel* model, int nfaces);
	~TopFacetHash ();

 /**
     Look-up for a mate facet-use. If none was found, inserts the 
   given one.
 */
 TopFacetUse FindMate (const TopFacetUse& in);

 void  Set (const TopFacetUse& in);
 TopFacetUse Get (const TopFacetUse& in);
 TopFacetUse GetMate (const TopFacetUse& in);
private:
};
#endif

#endif
