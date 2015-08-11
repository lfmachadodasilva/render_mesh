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

#ifndef _TOP_CONCRETE_WEDGE6_H
#define _TOP_CONCRETE_WEDGE6_H

#include "../defines.h"

/**
    Quadratic wedge.

  @verbatim
  
                    e5
           v3      <--        v5
           n3-----------------n5           
           |\                 /|
           | \               / |
           |  \      f1     /  |
           |   \ \e3     ^ /   |
           |    \ v   e4/ /    |
        ^  |     \  f4   /     |  ^
      e6|  |      \     /      |  |e8
           |       \ v4/       |
           |  f2     n4    f3  |
           |         |  e2     |
           |         | <--     |
           n0. . . . |. . . . .n2
          v0\       ^|        /v2
             \    e7|| f0    /
              \      |      /
           e0| \     |     /  ^
             v  \    |    /   |e1
                 \   |   /
                  \  |  /
                   \ | /
                     n1
                     v1
                        
    Orientation: n0 n1 n2 n3 n4 n5 | n6 .. n14
    Edges are locally oriented from its first vertex to the last one.
  @endverbatim
*/
class TOPS_API TopConcreteWEDGE6 : public TopConcreteElement
{
private:
  static TopElementClass m_class;

  TopNode     m_nodes[6];
  TopFacetUse m_adj[5];
  
  TopConcreteWEDGE6() {}
public:
  static TopElementClass* CLASS() { return &m_class; }
  static const char* CLASSNAME () { return "ConcreteWEDGE6"; }
  virtual const char* ClassName () const { return CLASSNAME(); }

  static const TopElementTemplate     TEMPLATE();
  static const TopElementSizeTemplate SIZE_TEMPLATE();
  
  TopConcreteWEDGE6(TopNode nodes[6]);
  ~TopConcreteWEDGE6() {}

  void Init(TopNode* nodes);

  virtual bool Serialize(IOStream* io)
  {
    return TopConcreteElement::Serialize(io)      &&
           io->WriteUInts(6, (unsigned*) m_nodes) &&
           io->WriteUInts(5, (unsigned*) m_adj);
  }

  virtual bool Deserialize(IOStream* io)
  {
    return TopConcreteElement::Deserialize(io)   &&
           io->ReadUInts(6, (unsigned*) m_nodes) &&
           io->ReadUInts(5, (unsigned*) m_adj);
  }

  TopElementTemplate GetTemplate() { return TEMPLATE(); };
  TopElementSizeTemplate GetSizeTemplate() { return SIZE_TEMPLATE(); }

  const TopElementClass* GetClass() const { return &m_class; }
};

#endif
