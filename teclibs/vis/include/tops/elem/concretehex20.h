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

#ifndef _TOP_CONCRETE_HEX20_H
#define _TOP_CONCRETE_HEX20_H

#include "../defines.h"

/**
    Quadratic hexahedron.

  @verbatim

                                   e10
                  v2               -->                v6
                  n2---------------n18----------------n6
                  /.                                  /| 
                 / .                                 / |
                /  .                                /  |
               /   .                               /   |
        e2 / n10   .         f5                   /    |
          v  /     . ^                     e6 / n14    |   ^
            /     n9 |e1                     v  /      n13 | e5
           /       .                f4         /       |
          /        .                          /        |
        n3----------------n19---------------n7         |
        v3         .      -->               v7         |
         |         .      e11                |         |
         |   f0    .              e9         |    f1   |
         |         .              -->        |         |
         |        n1 . . . . . . . n17 . . . | . . . .n5
         |       .v1                         |        v5
   e3 | n11   ^ .       f2             e7 | n15      /
      v  | e0/ .                          v  |      /
         |    n8                             |     /   ^
         |   .               f3              |    n12 / e4
         |  .                                |   /
         | .                                 |  /
         |.                                  | /
        n0----------------n16----------------n4
        v0                -->                v4
                          e8
                        
    Orientation: n0 n1 n2 n3 n4 n5 n6 n7 | n8 .. n19
    Edges are locally oriented from its first vertex to the last one.
    fi: opposite face to vertex vi
  @endverbatim
*/
class TOPS_API TopConcreteHEX20 : public TopConcreteElement
{
private:
  static TopElementClass m_class;

  TopNode       m_nodes[20];
  TopFacetUse m_adj[6];
  
  TopConcreteHEX20() {}
public:
  static TopElementClass* CLASS() { return &m_class; }
  static const char* CLASSNAME () { return "ConcreteHEX20"; }
  virtual const char* ClassName () const { return CLASSNAME(); }

  static const TopElementTemplate     TEMPLATE();
  static const TopElementSizeTemplate SIZE_TEMPLATE();
  
  TopConcreteHEX20(TopNode nodes[20]);
  ~TopConcreteHEX20() {}

  void Init(TopNode* nodes);

  virtual bool Serialize(IOStream* io)
  {
    return TopConcreteElement::Serialize(io)       &&
           io->WriteUInts(20, (unsigned*) m_nodes) &&
           io->WriteUInts(6, (unsigned*) m_adj);
  }

  virtual bool Deserialize(IOStream* io)
  {
    return TopConcreteElement::Deserialize(io)    &&
           io->ReadUInts(20, (unsigned*) m_nodes) &&
           io->ReadUInts(6, (unsigned*) m_adj);
  }

  TopElementTemplate GetTemplate() { return TEMPLATE(); };
  TopElementSizeTemplate GetSizeTemplate() { return SIZE_TEMPLATE(); }

  const TopElementClass* GetClass() const { return &m_class; }
};

#endif
