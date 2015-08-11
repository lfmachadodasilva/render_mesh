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

#ifndef _TOP_CONCRETE_INF2E3_H
#define _TOP_CONCRETE_INF2E3_H

#include "../defines.h"

/**
    Quadratic 2D infinite element.

  @verbatim
                 f2  
         v3   <- e2       v2
         n3. . . . . . . .n2
          |               |
          |               | ^
  f3 e3 | |               | |
        v |               | e1 f1
          |               |
          |               |
         n0------n4-------n1
         v0    e0 ->      v1
               f0
  
    Orientation: n0 n1 n2 n3 n4
    Edges are locally oriented from its first vertex to the last one.
  @endverbatim
*/
class TOPS_API TopConcreteINF2E3 : public TopConcreteElement
{
private:
  static TopElementClass m_class;

  TopNode       m_nodes[5];
  TopFacetUse m_adj[4];
  
  TopConcreteINF2E3() {}

public:
  static TopElementClass* CLASS() { return &m_class; }
  static const char* CLASSNAME () { return "ConcreteINF2E3"; }
  virtual const char* ClassName () const { return CLASSNAME(); }

  static const TopElementTemplate     TEMPLATE();
  static const TopElementSizeTemplate SIZE_TEMPLATE();

  TopConcreteINF2E3(TopNode nodes[5]);
  ~TopConcreteINF2E3() {}

  void Init(TopNode* nodes);

  virtual bool Serialize(IOStream* io)
  {
    return TopConcreteElement::Serialize(io)      &&
           io->WriteUInts(5, (unsigned*) m_nodes) &&
           io->WriteUInts(4, (unsigned*) m_adj);
  }

  virtual bool Deserialize(IOStream* io)
  {
    return TopConcreteElement::Deserialize(io)   &&
           io->ReadUInts(5, (unsigned*) m_nodes) &&
           io->ReadUInts(4, (unsigned*) m_adj);
  }
  
  TopElementTemplate GetTemplate() { return TEMPLATE(); };
  TopElementSizeTemplate GetSizeTemplate() { return SIZE_TEMPLATE(); }  

  const TopElementClass* GetClass() const { return &m_class; }
};

#endif
