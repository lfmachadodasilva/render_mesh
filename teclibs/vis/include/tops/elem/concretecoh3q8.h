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

#ifndef _TOP_CONCRETE_COH3Q8_H
#define _TOP_CONCRETE_COH3Q8_H

#include "../defines.h"
  
/**
    Quadratic 3D quadrangular cohesive element.

  @verbatim   
                 e2
         v3     <--               v2
         n3--------n6-------------n2  e5
          |            v7         |   -->      v6
          |            n11........|-n14--------n10
          |             .         |            |
          |             .         | ^          |
     e3 | n7      f0    .        n5 |e1        |
        v |           ^ .         |            |
          |         e4| n15       |   f1      n13 | e6
          |             .         |            |  v
          |             .         |            |
         n0--------n4-------------n1           |
         v0     -->     |         v1           |
                e0     n8-----------n12--------n9
                       v4         <--          v5
                                   e7

    Element's nodes order: n0 n1 n2 n3 | n4 n5 n6 n7                   
    f0: n0, n1, n2, n3    
    f1: n4, n7, n6, n5
  @endverbatim
*/
class TOPS_API TopConcreteCOH3Q8 : public TopConcreteElement
{
private:
  static TopElementClass m_class;

  TopNode       m_nodes[16];
  TopFacetUse m_adj[2];

  TopConcreteCOH3Q8() {}
public:
  static TopElementClass* CLASS() { return &m_class; }
  static const char* CLASSNAME () { return "ConcreteCOH3Q8"; }
  virtual const char* ClassName () const { return CLASSNAME(); }

  static const TopElementTemplate     TEMPLATE();
  static const TopElementSizeTemplate SIZE_TEMPLATE();

  TopConcreteCOH3Q8(TopNode nodes[16]);
  ~TopConcreteCOH3Q8() {}

  void Init(TopNode* nodes);
  void InitCohesive(TopNode* nodes);

  virtual bool Serialize(IOStream* io)
  {
    return TopConcreteElement::Serialize(io)       &&
           io->WriteUInts(16, (unsigned*) m_nodes) &&
           io->WriteUInts(2, (unsigned*) m_adj);
  }

  virtual bool Deserialize(IOStream* io)
  {
    return TopConcreteElement::Deserialize(io)    &&
           io->ReadUInts(16, (unsigned*) m_nodes) &&
           io->ReadUInts(2, (unsigned*) m_adj);
  }

  TopElementTemplate GetTemplate() { return TEMPLATE(); };
  TopElementSizeTemplate GetSizeTemplate() { return SIZE_TEMPLATE(); }

  const TopElementClass* GetClass() const { return &m_class; }
};

#endif
