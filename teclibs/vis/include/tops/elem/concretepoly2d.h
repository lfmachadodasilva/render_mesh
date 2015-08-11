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

#ifndef _TOP_CONCRETE_POLY_2D_H
#define _TOP_CONCRETE_POLY_2D_H

#include "../defines.h"

/**
TODO
*/
class TOPS_API TopConcretePOLY2D : public TopConcreteElement
{
private:
  static TopElementClass m_class;

  int m_nnodes;
  TopNode* m_nodes;
  TopFacetUse* m_adj;
  unsigned char* m_anchors;
  unsigned char* m_exanchors;

  enum {
    FACE_ANCHOR_BIT = 0,
    EDGE_ANCHOR_BIT = 1,
    VERTEX_ANCHOR_BIT = 2
  };
  
  void SetAnchorBit(int type, int i, int flag)
  {
    m_anchors[i] &= ~(1 << type);
    m_anchors[i] |= flag << type;
  }

  unsigned GetAnchorBit(int type, int i)
  {
    return m_anchors[i] & (1 << type);
  }

  void SetExAnchorBit(int type, int i, int flag)
  {
    assert(!IsConcrete());
    m_exanchors[i] &= ~(1 << type);
    m_exanchors[i] |= flag << type;
  }

  unsigned GetExAnchorBit(int type, int i)
  {
    assert(!IsConcrete());
    return m_exanchors[i] & (1 << type);
  }

  TopConcretePOLY2D();

public:
  friend class TopModel;

  static TopElementClass* CLASS() { return &m_class; }
  static const char* CLASSNAME () { return "ConcretePOLY2D"; }
  virtual const char* ClassName () const { return CLASSNAME(); }

  static const TopElementTemplate     TEMPLATE();
  static const TopElementSizeTemplate SIZE_TEMPLATE();
  
  TopConcretePOLY2D(TopNode* nodes);
  ~TopConcretePOLY2D();

  virtual void Init(TopNode* nodes);

  virtual void Finish();

  virtual bool Serialize(IOStream* io)
  {
    assert(0);
    return TopConcreteElement::Serialize(io);
    //TODO
  }

  virtual bool Deserialize(IOStream* io)
  {
    //TODO
    assert(0);
    return TopConcreteElement::Deserialize(io);
  }
  
  TopElementTemplate GetTemplate() { return TEMPLATE(); };
  TopElementSizeTemplate GetSizeTemplate() { return SIZE_TEMPLATE(); }

  const TopElementClass* GetClass() const { return &m_class; }

/////////////////////////////////////////////////////////////////////
//TODO: por enquanto, virtual para facilitar a implemetação rápida...  
/////////////////////////////////////////////////////////////////////

  /**********************
   * Face bits
   **********************/
  void SetDynFaceAnchor(int fi, int flag)
  {
    SetAnchorBit(FACE_ANCHOR_BIT, fi, flag);
  }

  unsigned GetDynFaceAnchor(int fi)
  {
    return GetAnchorBit(FACE_ANCHOR_BIT, fi);
  }
  
  void SetDynFaceExAnchor(int fi, int flag)
  {
    SetExAnchorBit(FACE_ANCHOR_BIT, fi, flag);
  }

  unsigned GetDynFaceExAnchor(int fi)
  {
    return GetExAnchorBit(FACE_ANCHOR_BIT, fi);
  }

  /**********************
   * Edge bits
   **********************/
  void SetDynEdgeAnchor(int ei, int flag)
  {
    SetAnchorBit(EDGE_ANCHOR_BIT, ei, flag);
  }

  unsigned GetDynEdgeAnchor(int ei)
  {
    return GetAnchorBit(EDGE_ANCHOR_BIT, ei);
  }
  
  void SetDynEdgeExAnchor(int ei, int flag)
  {
    SetExAnchorBit(EDGE_ANCHOR_BIT, ei, flag);
  }

  unsigned GetDynEdgeExAnchor(int ei)
  {
    return GetExAnchorBit(EDGE_ANCHOR_BIT, ei);
  } 

  /**********************
   * Vertex bits
   **********************/
  void ClearDynVertexAnchors() 
  { 
    for (int i = 0; i < NUM_V(); i++)
      m_anchors[i] &= ~(1 << VERTEX_ANCHOR_BIT);
  }
  
  void SetDynVertexAnchor(int vi, int flag)
  {
    SetAnchorBit(VERTEX_ANCHOR_BIT, vi, flag);
  }

  unsigned GetDynVertexAnchor(int vi)
  {
    return GetAnchorBit(VERTEX_ANCHOR_BIT, vi);
  }
   
  void SetDynVertexExAnchor(int vi, int flag)
  {
    SetExAnchorBit(VERTEX_ANCHOR_BIT, vi, flag);
  }

  unsigned GetDynVertexExAnchor(int vi)
  {
    return GetExAnchorBit(VERTEX_ANCHOR_BIT, vi);
  }

  int HasDynClearBits() 
  { 
    for (int i = 0; i < NUM_V(); i++)
      if (m_anchors[i] || m_exanchors[i])
        return 0;
    return 1;
  }

  void TurnDynAnchorsIntoExAnchors()
  {
    for (int i = 0; i < NUM_V(); i++) {
      m_exanchors[i] = m_anchors[i];
      m_anchors[i] = 0;
    }
  }

//private:
  virtual int NUM_F() const { return m_nnodes; }
  virtual int NUM_E() const { return m_nnodes; }
  virtual int NUM_V() const { return m_nnodes; }
  virtual int NUM_N() const { return m_nnodes; }

  virtual int NUM_F_E(int i) const { return 1; }
  virtual int NUM_F_V(int i) const { return 2; }
  virtual int NUM_F_N(int i) const { return 2; }

  virtual int NUM_E_F(int i) const { return 1; }
  virtual int NUM_E_N(int i) const { return 2; }

  virtual int NUM_V_F(int i) const { return 2; }
  virtual int NUM_V_E(int i) const { return 2; }
 
  virtual int F_E(int fi, int i) const { return fi; }
  virtual int F_V(int fi, int i) const { return (fi + i) % m_nnodes; }
  virtual int F_N(int fi, int i) const { return (fi + i) % m_nnodes; }

  virtual int E_F(int ei, int i) const { return ei; }
  virtual int E_V(int ei, int i) const { return (ei + i) % m_nnodes; }
  virtual int E_N(int ei, int i) const { return (ei + i) % m_nnodes; }

  virtual int V_F(int vi, int i) const { return (vi + i + m_nnodes - 1) % m_nnodes; }
  virtual int V_E(int vi, int i) const { return (vi + i + m_nnodes - 1) % m_nnodes; }
  virtual int V_N(int vi) const { return vi; }

  virtual int N_E(int ni) const { return -1; }
  virtual int N_V(int ni) const { return ni; }

  virtual int V_F_V(int vi, int vfi) const { return vfi == 0 ? 1 : 0; }
  virtual int E_F_E(int ei, int efi) const { return 0; }

  virtual int SHARED_V(int vi) const { return -1; }
  virtual int SHARED_E(int ei) const { return -1; }
  virtual int SHARED_E_N(int ei) const { return -1; }

  virtual int NUM_FC() const { return 1; }

  virtual int NUM_FC_E(int i) const { return m_nnodes; }
  virtual int NUM_FC_V(int i) const { return m_nnodes; }
  virtual int NUM_FC_N(int i) const { return m_nnodes; }

  virtual int NUM_E_FC(int i) const { return 1; }
  virtual int NUM_V_FC(int i) const { return 1; }
 
  virtual int FC_E(int fi, int i) const { return i; }
  virtual int FC_V(int fi, int i) const { return i; }
  virtual int FC_N(int fi, int i) const { return i; }

  virtual int E_FC(int ei, int i) const { return 0; }
  virtual int V_FC(int vi, int i) const { return 0; }

  virtual int V_FC_V(int vi, int vfi) const { return vfi; }
  virtual int E_FC_E(int ei, int efi) const { return efi; }
};

#endif
