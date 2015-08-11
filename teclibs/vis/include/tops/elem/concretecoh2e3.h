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

#ifndef _TOP_CONCRETE_COH2E3_H
#define _TOP_CONCRETE_COH2E3_H

#include "../defines.h"

/**
    Quadratic 2D edge cohesive element.
 
  @verbatim   

                   v3        v1
                   n4        n1
           |      /         /      ^ 
           V     /         /       |
          f1    n5        n2      f0
          e1   /         /        e0
              /         /
            n3        n0
            v2        v0
            
    Element's nodes order: n0 n1 n2 | n3 n4 n5                      
    f0: n0, n2, n1        
    f1: n4, n5, n3 
  @endverbatim
*/
class TOPS_API TopConcreteCOH2E3 : public TopConcreteElement
{
private:
  static TopElementClass m_class;

  TopNode      m_nodes[6];
  TopFacetUse m_adj[2];

  TopConcreteCOH2E3() {}
public:
  static TopElementClass* CLASS() { return &m_class; }
  static const char* CLASSNAME () { return "ConcreteCOH2E3"; }
  virtual const char* ClassName () const { return CLASSNAME(); }

  static const TopElementTemplate     TEMPLATE();
  static const TopElementSizeTemplate SIZE_TEMPLATE();

  TopConcreteCOH2E3(TopNode nodes[6]);
  ~TopConcreteCOH2E3() {}

  void Init(TopNode* nodes);
  void InitCohesive(TopNode* nodes);

  virtual bool Serialize(IOStream* io)
  {
    return TopConcreteElement::Serialize(io)      &&
           io->WriteUInts(6, (unsigned*) m_nodes) &&
           io->WriteUInts(2, (unsigned*) m_adj);
  }

  virtual bool Deserialize(IOStream* io)
  {
    return TopConcreteElement::Deserialize(io)   &&
           io->ReadUInts(6, (unsigned*) m_nodes) &&
           io->ReadUInts(2, (unsigned*) m_adj);
  }

  TopElementTemplate GetTemplate() { return TEMPLATE(); };
  TopElementSizeTemplate GetSizeTemplate() { return SIZE_TEMPLATE(); }

  const TopElementClass* GetClass() const { return &m_class; }
};

#endif
