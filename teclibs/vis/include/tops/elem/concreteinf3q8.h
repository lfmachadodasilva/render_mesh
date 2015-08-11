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

#ifndef _TOP_CONCRETE_INF3Q8_H
#define _TOP_CONCRETE_INF3Q8_H

#include "../defines.h"

/**
    Infinite 3D quadratic quadrilateral.

  @verbatim

                                   e9 
                  v7               -->                 v6
                  n11. . . . . . . . . . . . . . . . . n10
                  /.                                  /. 
                 / .                                 / .
                /  .                                /  .
            ^  /   .                               /   .
        e7 /  /    .         f4                ^  /    .
             /     . ^                     e6 /  /     .    
            /      . |e8                        /      .   | e10
           /       .                f5         /       .   v
          /        .                          /        .
        n3----------------n6----------------n2         .
        v3         .     <--                v2         .
         |         .      e2                 |         .
         |   f1    .              e11        |    f3   .
         |         .             <--         |         .
         |        n8 . . . . . . . . . . . . | . . . .n9
         |       /v4                      ^  |        v5
   e3 | n7    ^ /       f0             e1 | n5       /
      v  | e4/ /                             |      /
         |    /                              |     /   ^
         |   /               f2              |    /   / e5
         |  /                                |   /
         | /                                 |  /
         |/                                  | /
        n0----------------n4-----------------n1
        v0                -->                v1
                          e0
                        
    Orientation: n0 n1 n2 ... n11
    Edges are locally oriented from its first vertex to the last one.
  @endverbatim
*/

class TOPS_API TopConcreteINF3Q8: public TopConcreteElement
{
private:
  static TopElementClass m_class;

  TopNode       m_nodes[12];
  TopFacetUse m_adj[6];
  
  TopConcreteINF3Q8() {}
public:
  static TopElementClass* CLASS() { return &m_class; }
  static const char* CLASSNAME () { return "ConcreteINF3Q8"; }
  virtual const char* ClassName () const { return CLASSNAME(); }

  static const TopElementTemplate     TEMPLATE();
  static const TopElementSizeTemplate SIZE_TEMPLATE();
  
  TopConcreteINF3Q8(TopNode nodes[12]);
  ~TopConcreteINF3Q8() {}

  void Init(TopNode* nodes);

  virtual bool Serialize(IOStream* io)
  {
    return TopConcreteElement::Serialize(io)       &&
           io->WriteUInts(12, (unsigned*) m_nodes) &&
           io->WriteUInts(6, (unsigned*) m_adj);
  }

  virtual bool Deserialize(IOStream* io)
  {
    return TopConcreteElement::Deserialize(io)    &&
           io->ReadUInts(12, (unsigned*) m_nodes) &&
           io->ReadUInts(6, (unsigned*) m_adj);
  }

  TopElementTemplate GetTemplate() { return TEMPLATE(); };
  TopElementSizeTemplate GetSizeTemplate() { return SIZE_TEMPLATE(); }

  const TopElementClass* GetClass() const { return &m_class; }
};

#endif
