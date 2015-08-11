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
#ifndef _TOP_CONCRETE_COH3T6_H
#define _TOP_CONCRETE_COH3T6_H

#include "../defines.h"
  
/**
    Quadratic 3D triangular cohesive element.

  @verbatim
  
                     v2
                     n2 
                    /  \ 
                   /    \         v5
                  /      \ ^      n8
                 /        \ \e1  /  \
           e2 / /          \    /    \
             V n5          n4  /      \
              /              \/        \
             /      f0       .\        n10 \
            /           e3^ .  \         \  V e4 
           /             / n11  \  f1     \
          /               .      \         \
         n0----------n3----------n1         \
         v0    -->      /        v1          \
               e0      /                      \
                      n6----------n9----------n7
                      v3         <--          v4
                                 e5

    Element's nodes order: n0 n1 n2 n3 n4 n5 | n6 n7 n8 n9 n10 n11 
    f0: n0, n3, n1, n4, n2, n5
    f1: n3, n11, n5, n10, n7, n9
  @endverbatim
*/
class TOPS_API TopConcreteCOH3T6 : public TopConcreteElement
{
private:
  static TopElementClass m_class;

  TopNode      m_nodes[12];
  TopFacetUse m_adj[2];

  TopConcreteCOH3T6() {}
public:
  static TopElementClass* CLASS() { return &m_class; }
  static const char* CLASSNAME () { return "ConcreteCOH3T6"; }
  virtual const char* ClassName () const { return CLASSNAME(); }

  static const TopElementTemplate     TEMPLATE();
  static const TopElementSizeTemplate SIZE_TEMPLATE();

  TopConcreteCOH3T6(TopNode nodes[12]);
  ~TopConcreteCOH3T6() {}

  void Init(TopNode* nodes);
  void InitCohesive(TopNode* nodes);

  virtual bool Serialize(IOStream* io)
  {
    return TopConcreteElement::Serialize(io)       &&
           io->WriteUInts(12, (unsigned*) m_nodes) &&
           io->WriteUInts(2, (unsigned*) m_adj);
  }

  virtual bool Deserialize(IOStream* io)
  {
    return TopConcreteElement::Deserialize(io)    &&
           io->ReadUInts(12, (unsigned*) m_nodes) &&
           io->ReadUInts(2, (unsigned*) m_adj);
  }

  TopElementTemplate GetTemplate() { return TEMPLATE(); };
  TopElementSizeTemplate GetSizeTemplate() { return SIZE_TEMPLATE(); }

  const TopElementClass* GetClass() const { return &m_class; }
};

#endif
