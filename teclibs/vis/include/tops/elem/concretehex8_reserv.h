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

#ifndef _TOP_CONCRETE_HEX8_RESERV_H
#define _TOP_CONCRETE_HEX8_RESERV_H

#include "../defines.h"

/**
    Linear hexahedron used as reservoir cell.

  @verbatim
      
                                   e2
                  v2              <--                 v3
                  n2----------------------------------n3
                  /.                                  /| 
                 / .                                 / |
                /  .                                /  |
               /   .                               /   |
        e3 /  /    .         f0                ^  /    |
          v  /     .                       e1 /  /     |    
            /      . |e10                       /      |   | e9
           /       . v              f5         /       |   v
          /        .                          /        |
        n0----------------------------------n1         |
        v0         .      -->               v1         |
         |         .      e0                 |         |
         |   f3    .              e6         |    f2   |
         |         . /           <--         |         |
         |        n6 . . . . . . . . . . . . | . . . .n7
         |       .v6                         |        v7
   e11|  |      .       f4             e8 |  |       /
      v  | e7/ .                          v  |      /
         |  v .                              |     /   ^
         |   .               f1              |    /   /e5 
         |  .                                |   /
         | .                                 |  /
         |.                                  | /
        n4-----------------------------------n5
        v4                -->                v5
                          e4
    z ^ 
      |  ^ J = y
      | /
      |/    
      * ----->  
      |      I = x 
      | 
      v K

  @endverbatim
*/
class TOPS_API TopConcreteHEX8Reservoir : public TopConcreteElement
{
private:
  static TopElementClass m_class;

  TopNode       m_nodes[8];
  TopFacetUse m_adj[6];
  
  TopConcreteHEX8Reservoir() {}
public:
  static TopElementClass* CLASS() { return &m_class; }
  static const char* CLASSNAME () { return "ConcreteHEX8Reservoir"; }
  virtual const char* ClassName () const { return CLASSNAME(); }

  static const TopElementTemplate     TEMPLATE();
  static const TopElementSizeTemplate SIZE_TEMPLATE();
  
  TopConcreteHEX8Reservoir(TopNode nodes[8]);
  ~TopConcreteHEX8Reservoir() {}

  void Init(TopNode* nodes);

  static int TopFaceVertex (int vi);
  static int BottomFaceVertex (int vi);
  static int IMinusFaceVertex (int vi);
  static int IPlusFaceVertex (int vi);
  static int JMinusFaceVertex (int vi, bool j_inverted);
  static int JPlusFaceVertex (int vi, bool j_inverted);
  static int IMinusFace ();
  static int IPlusFace ();
  static int JMinusFace (bool j_inverted);
  static int JPlusFace (bool j_inverted);
  static int KMinusFace (bool is_kdir_up);
  static int KPlusFace (bool is_kdir_up);

  static int IMinusJMinusEdge (bool j_inverted);
  static int IMinusJPlusEdge (bool j_inverted);
  static int IMinusKMinusEdge (bool is_kdir_up);
  static int IMinusKPlusEdge (bool is_kdir_up);
  static int IPlusJMinusEdge (bool j_inverted);
  static int IPlusJPlusEdge (bool j_inverted);
  static int IPlusKMinusEdge (bool is_kdir_up);
  static int IPlusKPlusEdge (bool is_kdir_up);
  static int JMinusKMinusEdge (bool j_inverted, bool is_kdir_up);
  static int JMinusKPlusEdge (bool j_inverted, bool is_kdir_up);
  static int JPlusKMinusEdge (bool j_inverted, bool is_kdir_up);
  static int JPlusKPlusEdge (bool j_inverted, bool is_kdir_up);

  static int VertexI (int vi);
  static int VertexJ (int vi, bool j_inverted);
  static int VertexK (int vi, bool is_kdir_up);
  static int IJKVertex (int i, int j, int k, bool j_inverted, bool is_kdir_up);

  virtual bool Serialize(IOStream* io)
  {
    return TopConcreteElement::Serialize(io)      &&
           io->WriteUInts(8, (unsigned*) m_nodes) &&
           io->WriteUInts(6, (unsigned*) m_adj);
  }

  virtual bool Deserialize(IOStream* io)
  {
    return TopConcreteElement::Deserialize(io)   &&
           io->ReadUInts(8, (unsigned*) m_nodes) &&
           io->ReadUInts(6, (unsigned*) m_adj);
  }
  
  TopElementTemplate GetTemplate() { return TEMPLATE(); };
  TopElementSizeTemplate GetSizeTemplate() { return SIZE_TEMPLATE(); }

  const TopElementClass* GetClass() const { return &m_class; }
};

#endif
