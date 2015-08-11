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

#ifndef _TOP_CONCRETE_TET10_H
#define _TOP_CONCRETE_TET10_H

#include "../defines.h"

/**
    Quadratic tetrahedron.

  @verbatim
  
                         v3
                         n3 
                        /  \ \
                       /    \  \
                      /      \   \ 
                     /        \    \       ^
                    /          \     \     | e5
             ^     /            \      n9
          e3 |    /              \   ^   \ 
                 n7           f1  n8 |e4   \
                /       f2         \   f0    \
               /                    \          \
              /                      \         n2 v2
             /          e2            \  .  .  /
            /          <--     .  .  . \      n5  ^
           /        .  .  n6 .          \    /   / e1
          / .  .  .              f3      \  /    
         n0---------------n4------------- n1  
         v0                               v1
                        -->
                        e0
                        
    Orientation: n0 n1 n2 n3 | n4 n5 n6 n7 n8 n9
    Edges are locally oriented from its first vertex to the last one.
    fi: opposite face to vertex vi
  @endverbatim
*/
class TOPS_API TopConcreteTET10 : public TopConcreteElement
{
private:
  static TopElementClass m_class;

  TopNode     m_nodes[10];
  TopFacetUse m_adj[4];
  
  TopConcreteTET10() {}
public:
  static TopElementClass* CLASS() { return &m_class; }
  static const char* CLASSNAME () { return "ConcreteTET10"; }
  virtual const char* ClassName () const { return CLASSNAME(); }

  static const TopElementTemplate     TEMPLATE();
  static const TopElementSizeTemplate SIZE_TEMPLATE();
  
  TopConcreteTET10(TopNode nodes[10]);
  ~TopConcreteTET10() {}

  void Init(TopNode* nodes);

  virtual bool Serialize(IOStream* io)
  {
    return TopConcreteElement::Serialize(io)       &&
           io->WriteUInts(10, (unsigned*) m_nodes) &&
           io->WriteUInts(4, (unsigned*) m_adj);
  }

  virtual bool Deserialize(IOStream* io)
  {
    return TopConcreteElement::Deserialize(io)    &&
           io->ReadUInts(10, (unsigned*) m_nodes) &&
           io->ReadUInts(4, (unsigned*) m_adj);
  }
  
  TopElementTemplate GetTemplate() { return TEMPLATE(); };
  TopElementSizeTemplate GetSizeTemplate() { return SIZE_TEMPLATE(); }

  const TopElementClass* GetClass() const { return &m_class; }
};

#endif
