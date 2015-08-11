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

#ifndef _TOP_CONCRETE_T6_H
#define _TOP_CONCRETE_T6_H

#include "../defines.h"

/**
    Quadratic 2D triangular element.

  @verbatim

                  v2
                  n2
                 /  \      ^
                /    \     |
     | f2 e2   n5     n4   e1 f1
     v        /        \
             /          \
           n0-----n3--- n1  
           v0           v1 
                  e0 ->
                  f0
  
    Orientation: n0 n1 n2 | n3 n4 n5      
    Edges are locally oriented from its first vertex to the last one.
    e0: n0, n3, n1
    f0: n0, n3, n1
  @endverbatim
*/
class TOPS_API TopConcreteT6 : public TopConcreteElement
{
private:
  static TopElementClass m_class;

  TopNode       m_nodes[6];
  TopFacetUse m_adj[3];
 
  TopConcreteT6() {}
public:
  static TopElementClass* CLASS() { return &m_class; }
  static const char* CLASSNAME () { return "ConcreteT6"; }
  virtual const char* ClassName () const { return CLASSNAME(); }

  static const TopElementTemplate     TEMPLATE();
  static const TopElementSizeTemplate SIZE_TEMPLATE();
  
  TopConcreteT6(TopNode nodes[6]);
  ~TopConcreteT6() {}

  void Init(TopNode* nodes);

  virtual bool Serialize(IOStream* io)
  {
    return TopConcreteElement::Serialize(io)      &&
           io->WriteUInts(6, (unsigned*) m_nodes) &&
           io->WriteUInts(3, (unsigned*) m_adj);
  }

  virtual bool Deserialize(IOStream* io)
  {
    return TopConcreteElement::Deserialize(io)   &&
           io->ReadUInts(6, (unsigned*) m_nodes) &&
           io->ReadUInts(3, (unsigned*) m_adj);
  }
  
  TopElementTemplate GetTemplate() { return TEMPLATE(); };
  TopElementSizeTemplate GetSizeTemplate() { return SIZE_TEMPLATE(); }

  const TopElementClass* GetClass() const { return &m_class; }
};

#endif
