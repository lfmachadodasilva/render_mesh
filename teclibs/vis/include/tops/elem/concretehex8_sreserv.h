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

#ifndef _TOP_CONCRETE_HEX8_SRESERV_H
#define _TOP_CONCRETE_HEX8_SRESERV_H

#include "../defines.h"

/**
  Linear hexahedron used as a reservoir cell memory-optimized for 
  structured meshes.
  The topology is the same as 
*/
class TOPS_API TopConcreteHEX8SReservoir : public TopConcreteElement
{
private:
  static TopElementClass m_class;

  TopNode       m_nodes[8];
  unsigned char m_adj;
  
  TopConcreteHEX8SReservoir() {}
public:
  static TopElementClass* CLASS() { return &m_class; }
  static const char* CLASSNAME () { return "ConcreteHEX8SReservoir"; }
  virtual const char* ClassName () const { return CLASSNAME(); }

  static const TopElementTemplate     TEMPLATE();
  static const TopElementSizeTemplate SIZE_TEMPLATE();
  
  TopConcreteHEX8SReservoir(TopNode nodes[8]);
  ~TopConcreteHEX8SReservoir() {}

  void Init(TopNode* nodes);

  virtual bool Serialize(IOStream* io)
  {
    return TopConcreteElement::Serialize(io)      &&
           io->WriteUInts(8, (unsigned*) m_nodes) &&
           io->WriteUChars(1, &m_adj);
  }

  virtual bool Deserialize(IOStream* io)
  {
    return TopConcreteElement::Deserialize(io)   &&
           io->ReadUInts(8, (unsigned*) m_nodes) &&
           io->ReadUChars(1, &m_adj);
  }
  
  TopElementTemplate GetTemplate() { return TEMPLATE(); };
  TopElementSizeTemplate GetSizeTemplate() { return SIZE_TEMPLATE(); }

  const TopElementClass* GetClass() const { return &m_class; }
};

#endif
