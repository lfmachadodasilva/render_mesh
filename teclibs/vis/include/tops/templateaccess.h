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

/**
  Access methods for element template data inside the TopModel class.

  Internal use only.
  This file is intended to be included within the TopModel class.
*/

//class TopModel {
// ...
int NUM_F(const TopElement& el) const 
{ 
#ifdef TOP_USE_DYNAMIC_ELEMENTS
  if (m_T[el.GetType()].IS_DYNAMIC)
    return GetConcreteElement(el.GetHandle())->NUM_F();
  else
#endif
    return m_T[el.GetType()].NUM_F; 
}
int NUM_E(const TopElement& el) const 
{ 
#ifdef TOP_USE_DYNAMIC_ELEMENTS
  if (m_T[el.GetType()].IS_DYNAMIC)
    return GetConcreteElement(el.GetHandle())->NUM_E();
  else
#endif
    return m_T[el.GetType()].NUM_E; 
}
int NUM_V(const TopElement& el) const 
{ 
#ifdef TOP_USE_DYNAMIC_ELEMENTS
  if (m_T[el.GetType()].IS_DYNAMIC)
    return GetConcreteElement(el.GetHandle())->NUM_V();
  else
#endif
    return m_T[el.GetType()].NUM_V; 
}
int NUM_N(const TopElement& el) const 
{ 
#ifdef TOP_USE_DYNAMIC_ELEMENTS
  if (m_T[el.GetType()].IS_DYNAMIC)
    return GetConcreteElement(el.GetHandle())->NUM_N();
  else
#endif
    return m_T[el.GetType()].NUM_N; 
}
int NUM_F_E(const TopElement& el, int i) const 
{ 
#ifdef TOP_USE_DYNAMIC_ELEMENTS
  if (m_T[el.GetType()].IS_DYNAMIC)
    return GetConcreteElement(el.GetHandle())->NUM_F_E(i);
  else
#endif
    return m_T[el.GetType()].NUM_F_E[i]; 
}
int NUM_F_V(const TopElement& el, int i) const 
{ 
#ifdef TOP_USE_DYNAMIC_ELEMENTS
  if (m_T[el.GetType()].IS_DYNAMIC)
    return GetConcreteElement(el.GetHandle())->NUM_F_V(i);
  else
#endif
    return m_T[el.GetType()].NUM_F_V[i]; 
}
int NUM_F_N(const TopElement& el, int i) const 
{ 
#ifdef TOP_USE_DYNAMIC_ELEMENTS
  if (m_T[el.GetType()].IS_DYNAMIC)
    return GetConcreteElement(el.GetHandle())->NUM_F_N(i);
  else
#endif
    return m_T[el.GetType()].NUM_F_N[i]; 
}
int NUM_E_F(const TopElement& el, int i) const
{ 
#ifdef TOP_USE_DYNAMIC_ELEMENTS
  if (m_T[el.GetType()].IS_DYNAMIC)
    return GetConcreteElement(el.GetHandle())->NUM_E_F(i);
  else
#endif
    return m_T[el.GetType()].NUM_E_F[i]; 
}
int NUM_E_N(const TopElement& el, int i) const
{ 
#ifdef TOP_USE_DYNAMIC_ELEMENTS
  if (m_T[el.GetType()].IS_DYNAMIC)
    return GetConcreteElement(el.GetHandle())->NUM_E_N(i);
  else
#endif
    return m_T[el.GetType()].NUM_E_N[i]; 
}
int NUM_V_F(const TopElement& el, int i) const
{ 
#ifdef TOP_USE_DYNAMIC_ELEMENTS
  if (m_T[el.GetType()].IS_DYNAMIC)
    return GetConcreteElement(el.GetHandle())->NUM_V_F(i);
  else
#endif
    return m_T[el.GetType()].NUM_V_F[i]; 
}
int NUM_V_E(const TopElement& el, int i) const
{ 
#ifdef TOP_USE_DYNAMIC_ELEMENTS
  if (m_T[el.GetType()].IS_DYNAMIC)
    return GetConcreteElement(el.GetHandle())->NUM_V_E(i);
  else
#endif
    return m_T[el.GetType()].NUM_V_E[i]; 
}
int F_E(const TopElement& el, int fi, int i) const
{ 
#ifdef TOP_USE_DYNAMIC_ELEMENTS
  if (m_T[el.GetType()].IS_DYNAMIC)
    return GetConcreteElement(el.GetHandle())->F_E(fi, i);
  else
#endif
    return m_T[el.GetType()].F_E[fi][i]; 
}
int F_V(const TopElement& el, int fi, int i) const 
{ 
#ifdef TOP_USE_DYNAMIC_ELEMENTS
  if (m_T[el.GetType()].IS_DYNAMIC)
    return GetConcreteElement(el.GetHandle())->F_V(fi, i);
  else
#endif
    return m_T[el.GetType()].F_V[fi][i]; 
}
int F_N(const TopElement& el, int fi, int i) const
{ 
#ifdef TOP_USE_DYNAMIC_ELEMENTS
  if (m_T[el.GetType()].IS_DYNAMIC)
    return GetConcreteElement(el.GetHandle())->F_N(fi, i);
  else
#endif
    return m_T[el.GetType()].F_N[fi][i]; 
}
int E_F(const TopElement& el, int ei, int i) const
{ 
#ifdef TOP_USE_DYNAMIC_ELEMENTS
  if (m_T[el.GetType()].IS_DYNAMIC)
    return GetConcreteElement(el.GetHandle())->E_F(ei, i);
  else
#endif
    return m_T[el.GetType()].E_F[ei][i]; 
}
int E_V(const TopElement& el, int ei, int i) const
{ 
#ifdef TOP_USE_DYNAMIC_ELEMENTS
  if (m_T[el.GetType()].IS_DYNAMIC)
    return GetConcreteElement(el.GetHandle())->E_V(ei, i);
  else
#endif
    return m_T[el.GetType()].E_V[ei][i]; 
}
int E_N(const TopElement& el, int ei, int i) const
{ 
#ifdef TOP_USE_DYNAMIC_ELEMENTS
  if (m_T[el.GetType()].IS_DYNAMIC)
    return GetConcreteElement(el.GetHandle())->E_N(ei, i);
  else
#endif
    return m_T[el.GetType()].E_N[ei][i]; 
}
int V_F(const TopElement& el, int vi, int i) const
{ 
#ifdef TOP_USE_DYNAMIC_ELEMENTS
  if (m_T[el.GetType()].IS_DYNAMIC)
    return GetConcreteElement(el.GetHandle())->V_F(vi, i);
  else
#endif
    return m_T[el.GetType()].V_F[vi][i]; 
}
int V_E(const TopElement& el, int vi, int i) const
{ 
#ifdef TOP_USE_DYNAMIC_ELEMENTS
  if (m_T[el.GetType()].IS_DYNAMIC)
    return GetConcreteElement(el.GetHandle())->V_E(vi, i);
  else
#endif
    return m_T[el.GetType()].V_E[vi][i]; 
}
int V_N(const TopElement& el, int vi) const
{ 
#ifdef TOP_USE_DYNAMIC_ELEMENTS
  if (m_T[el.GetType()].IS_DYNAMIC)
    return GetConcreteElement(el.GetHandle())->V_N(vi);
  else
#endif
    return m_T[el.GetType()].V_N[vi]; 
}
int N_E(const TopElement& el, int ni) const
{ 
#ifdef TOP_USE_DYNAMIC_ELEMENTS
  if (m_T[el.GetType()].IS_DYNAMIC)
    return GetConcreteElement(el.GetHandle())->N_E(ni);
  else
#endif
    return m_T[el.GetType()].N_E[ni]; 
}
int N_V(const TopElement& el, int ni) const
{ 
#ifdef TOP_USE_DYNAMIC_ELEMENTS
  if (m_T[el.GetType()].IS_DYNAMIC)
    return GetConcreteElement(el.GetHandle())->N_V(ni);
  else
#endif
    return m_T[el.GetType()].N_V[ni]; 
}
int V_F_V(const TopElement& el, int vi, int vfi) const
{ 
#ifdef TOP_USE_DYNAMIC_ELEMENTS
  if (m_T[el.GetType()].IS_DYNAMIC)
    return GetConcreteElement(el.GetHandle())->V_F_V(vi, vfi);
  else
#endif
    return m_T[el.GetType()].V_F_V[vi][vfi]; 
}
int E_F_E(const TopElement& el, int ei, int efi) const
{ 
#ifdef TOP_USE_DYNAMIC_ELEMENTS
  if (m_T[el.GetType()].IS_DYNAMIC)
    return GetConcreteElement(el.GetHandle())->E_F_E(ei, efi);
  else
#endif
    return m_T[el.GetType()].E_F_E[ei][efi]; 
}
int SHARED_V(const TopElement& el, int vi) const
{ 
#ifdef TOP_USE_DYNAMIC_ELEMENTS
  if (m_T[el.GetType()].IS_DYNAMIC)
    return GetConcreteElement(el.GetHandle())->SHARED_V(vi);
  else
#endif
    return m_T[el.GetType()].SHARED_V[vi]; 
}
int SHARED_E(const TopElement& el, int ei) const
{ 
#ifdef TOP_USE_DYNAMIC_ELEMENTS
  if (m_T[el.GetType()].IS_DYNAMIC)
    return GetConcreteElement(el.GetHandle())->SHARED_E(ei);
  else
#endif
    return m_T[el.GetType()].SHARED_E[ei]; 
}
int SHARED_E_N(const TopElement& el, int ei) const
{ 
#ifdef TOP_USE_DYNAMIC_ELEMENTS
  if (m_T[el.GetType()].IS_DYNAMIC)
    return GetConcreteElement(el.GetHandle())->SHARED_E_N(ei);
  else
#endif
    return m_T[el.GetType()].SHARED_E_N[ei]; 
}

int NUM_FC(const TopElement& el) const 
{ 
#ifdef TOP_USE_DYNAMIC_ELEMENTS
  if (m_T[el.GetType()].IS_DYNAMIC)
    return GetConcreteElement(el.GetHandle())->NUM_FC();
  else
#endif
    return m_T[el.GetType()].NUM_FC; 
}
int NUM_FC_E(const TopElement& el, int i) const 
{ 
#ifdef TOP_USE_DYNAMIC_ELEMENTS
  if (m_T[el.GetType()].IS_DYNAMIC)
    return GetConcreteElement(el.GetHandle())->NUM_FC_E(i);
  else
#endif
    return m_T[el.GetType()].NUM_FC_E[i]; 
}
int NUM_FC_V(const TopElement& el, int i) const 
{ 
#ifdef TOP_USE_DYNAMIC_ELEMENTS
  if (m_T[el.GetType()].IS_DYNAMIC)
    return GetConcreteElement(el.GetHandle())->NUM_FC_V(i);
  else
#endif
    return m_T[el.GetType()].NUM_FC_V[i]; 
}
int NUM_FC_N(const TopElement& el, int i) const 
{ 
#ifdef TOP_USE_DYNAMIC_ELEMENTS
  if (m_T[el.GetType()].IS_DYNAMIC)
    return GetConcreteElement(el.GetHandle())->NUM_FC_N(i);
  else
#endif
    return m_T[el.GetType()].NUM_FC_N[i]; 
}
int NUM_E_FC(const TopElement& el, int i) const
{ 
#ifdef TOP_USE_DYNAMIC_ELEMENTS
  if (m_T[el.GetType()].IS_DYNAMIC)
    return GetConcreteElement(el.GetHandle())->NUM_E_FC(i);
  else
#endif
    return m_T[el.GetType()].NUM_E_FC[i]; 
}
int NUM_V_FC(const TopElement& el, int i) const
{ 
#ifdef TOP_USE_DYNAMIC_ELEMENTS
  if (m_T[el.GetType()].IS_DYNAMIC)
    return GetConcreteElement(el.GetHandle())->NUM_V_FC(i);
  else
#endif
    return m_T[el.GetType()].NUM_V_FC[i]; 
}
int FC_E(const TopElement& el, int fi, int i) const
{ 
#ifdef TOP_USE_DYNAMIC_ELEMENTS
  if (m_T[el.GetType()].IS_DYNAMIC)
    return GetConcreteElement(el.GetHandle())->FC_E(fi, i);
  else
#endif
    return m_T[el.GetType()].FC_E[fi][i]; 
}
int FC_V(const TopElement& el, int fi, int i) const 
{ 
#ifdef TOP_USE_DYNAMIC_ELEMENTS
  if (m_T[el.GetType()].IS_DYNAMIC)
    return GetConcreteElement(el.GetHandle())->FC_V(fi, i);
  else
#endif
    return m_T[el.GetType()].FC_V[fi][i]; 
}
int FC_N(const TopElement& el, int fi, int i) const
{ 
#ifdef TOP_USE_DYNAMIC_ELEMENTS
  if (m_T[el.GetType()].IS_DYNAMIC)
    return GetConcreteElement(el.GetHandle())->FC_N(fi, i);
  else
#endif
    return m_T[el.GetType()].FC_N[fi][i]; 
}
int E_FC(const TopElement& el, int ei, int i) const
{ 
#ifdef TOP_USE_DYNAMIC_ELEMENTS
  if (m_T[el.GetType()].IS_DYNAMIC)
    return GetConcreteElement(el.GetHandle())->E_FC(ei, i);
  else
#endif
    return m_T[el.GetType()].E_FC[ei][i]; 
}
int V_FC(const TopElement& el, int vi, int i) const
{ 
#ifdef TOP_USE_DYNAMIC_ELEMENTS
  if (m_T[el.GetType()].IS_DYNAMIC)
    return GetConcreteElement(el.GetHandle())->V_FC(vi, i);
  else
#endif
    return m_T[el.GetType()].V_FC[vi][i]; 
}
int V_FC_V(const TopElement& el, int vi, int vfi) const
{ 
#ifdef TOP_USE_DYNAMIC_ELEMENTS
  if (m_T[el.GetType()].IS_DYNAMIC)
    return GetConcreteElement(el.GetHandle())->V_FC_V(vi, vfi);
  else
#endif
    return m_T[el.GetType()].V_FC_V[vi][vfi]; 
}
int E_FC_E(const TopElement& el, int ei, int efi) const
{ 
#ifdef TOP_USE_DYNAMIC_ELEMENTS
  if (m_T[el.GetType()].IS_DYNAMIC)
    return GetConcreteElement(el.GetHandle())->E_FC_E(ei, efi);
  else
#endif
    return m_T[el.GetType()].E_FC_E[ei][efi]; 
}

// ...
// }

