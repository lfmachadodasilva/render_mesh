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

#ifndef _TOP_CONCRETE_LINE2_H
#define _TOP_CONCRETE_LINE2_H

#include "../defines.h"

/**
    Linear 1D line element.

    WARNING: This is an experimental implementation.
             Currently, adjacency information is unsupported for this type
             of element. Therefore, all the corresponding features and
             non-oriented entities (TopVertex, TopEdge, TopFace, etc.)
             cannot be accessed or used.

  @verbatim


                  fu1   
                  v1
                  n1
                 /
             ^  /
         e0 /  /
              /
             /
           n0
           v0
           fu0

  @endverbatim
*/
class TOPS_API TopConcreteLINE2 : public TopConcreteElement
{
private:
  static TopElementClass m_class;

  TopNode       m_nodes[2];
  TopFacetUse m_adj[2];

  TopConcreteLINE2() {}

public:
  static TopElementClass* CLASS() { return &m_class; }
  static const char* CLASSNAME () { return "ConcreteLINE2"; }
  virtual const char* ClassName () const { return CLASSNAME(); }

  static const TopElementTemplate     TEMPLATE();
  static const TopElementSizeTemplate SIZE_TEMPLATE();
  
  TopConcreteLINE2(TopNode nodes[2]);
  ~TopConcreteLINE2() {}

  void Init(TopNode* nodes);

  virtual bool Serialize(IOStream* io)
  {
    return TopConcreteElement::Serialize(io)      &&
           io->WriteUInts(3, (unsigned*) m_nodes) &&
           io->WriteUInts(3, (unsigned*) m_adj);
  }

  virtual bool Deserialize(IOStream* io)
  {
    return TopConcreteElement::Deserialize(io)   &&
           io->ReadUInts(3, (unsigned*) m_nodes) &&
           io->ReadUInts(3, (unsigned*) m_adj);
  }
  
  TopElementTemplate GetTemplate() { return TEMPLATE(); };
  TopElementSizeTemplate GetSizeTemplate() { return SIZE_TEMPLATE(); }

  const TopElementClass* GetClass() const { return &m_class; }
};

#endif
