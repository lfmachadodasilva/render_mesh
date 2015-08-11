//* glutnotifier.h
// celes@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Jan 2003

#ifndef VGL_SUBNOTIFIER_H
#define VGL_SUBNOTIFIER_H

#include "notifier.h"

class VglSubCanvas;

class VGL_API VglSubNotifier : public VglNotifier
{
public:
  VglSubNotifier (VglNotifier *parent, VglSubCanvas *owner) :
    VglNotifier(owner),
    m_parent(parent)
  {
  }
  virtual ~VglSubNotifier ()
  {
  }
  virtual bool AddIdle (VglFunction func, void* data, int repeat)
  {
    return m_parent->AddIdle(func,data,repeat);
  }
  virtual bool RemIdle (VglFunction func, void* data)
  {
    return m_parent->RemIdle(func,data);
  }
protected:
  virtual void IdleAddRef ()
  {
  }
  virtual void IdleRemRef ()
  {
  }
  virtual int GetMouseButtonMode ()
  {
    return 0;
  }
private:
  VglNotifier *m_parent;
};

#endif
