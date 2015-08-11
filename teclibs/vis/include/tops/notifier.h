
#ifndef TOP_NOTIFIER_H
#define TOP_NOTIFIER_H

#include "array.h"

class TOPS_API TopModelNotifier
{
public:
  TopModelNotifier()
    : m_model(NULL), m_enabled(true)
  {
  }
  ~TopModelNotifier()
  {
  }
  void SetModel(TopModel* m)
  {
    m_model = m;
  }
  void SetEnabled(bool flag)
  {
    m_enabled = flag;
  }
  bool IsEnabled()
  {
    return m_enabled;
  }
  void AddEditListener(TopModelEditListener* l)
  {
    m_edit_listeners.Append(l);
  }
  const TopArray<TopModelEditListener*>* GetEditListeners()
  {
    return &m_edit_listeners;
  }
  void RemoveEditListener(TopModelEditListener* l)
  {
    for (int i = 0; i < m_edit_listeners.Size(); i++)
      if (m_edit_listeners.Get(i) == l)
        m_edit_listeners.Remove(i);
  }
  void ClearEditListeners()
  {
    m_edit_listeners.Reset();
  }

  void NotifyInsertNode(TopNode n)
  {
    if (m_enabled)
      for (int i = 0; i < m_edit_listeners.Size(); i++)
        m_edit_listeners.Get(i)->InsertNode(m_model, n);
  }
  void NotifyRemoveNode(TopNode n)
  {
    if (m_enabled)
      for (int i = 0; i < m_edit_listeners.Size(); i++)
        m_edit_listeners.Get(i)->RemoveNode(m_model, n);
  }
  void NotifyInsertElem(TopElement el) 
  {
    if (m_enabled)
      for (int i = 0; i < m_edit_listeners.Size(); i++)
        m_edit_listeners.Get(i)->InsertElem(m_model, el);
  }
  void NotifyRemoveElem(TopElement el) 
  {
    if (m_enabled)
      for (int i = 0; i < m_edit_listeners.Size(); i++)
        m_edit_listeners.Get(i)->RemoveElem(m_model, el);
  }
  void NotifyDuplicateNode(TopNode old_n, TopNode new_n)
  {
    if (m_enabled)
      for (int i = 0; i < m_edit_listeners.Size(); i++)
        m_edit_listeners.Get(i)->DuplicateNode(m_model, old_n, new_n);
  }
  void NotifyReplaceElemNode(TopElement el, int i, TopNode old_n, TopNode new_n)
  {
    if (m_enabled)
      for (int i = 0; i < m_edit_listeners.Size(); i++)
        m_edit_listeners.Get(i)->ReplaceElemNode(m_model, el, i, old_n, new_n);
  }

  /**
    Mesh adaptivity
  */
  void NotifySplitElem(TopElement old_el, TopElement new_el[2])
  {
    if (m_enabled)
      for (int i = 0; i < m_edit_listeners.Size(); i++)
        m_edit_listeners.Get(i)->SplitElem(m_model, old_el, new_el);
  }
  void NotifySwapElem(TopElement old_el[2], TopElement new_el[2])
  {
    if (m_enabled)
      for (int i = 0; i < m_edit_listeners.Size(); i++)
        m_edit_listeners.Get(i)->SwapElem(m_model, old_el, new_el);
  }
  void NotifyMergeElem(TopElement old_el[2], TopElement new_el)
  {
    if (m_enabled)
      for (int i = 0; i < m_edit_listeners.Size(); i++)
        m_edit_listeners.Get(i)->MergeElem(m_model, old_el, new_el);
  }
  /**
    Experimental (may change in the future!)
  */
  void NotifyJoinFacet(TopFacetUse f1, TopFacetUse f2)
  {
    if (m_enabled)
      for (int i = 0; i < m_edit_listeners.Size(); i++)
        m_edit_listeners.Get(i)->JoinFacet(m_model, f1, f2);
  }

private:
  TopModel* m_model;
  TopArray<TopModelEditListener*> m_edit_listeners;
  bool m_enabled;
};

#endif
