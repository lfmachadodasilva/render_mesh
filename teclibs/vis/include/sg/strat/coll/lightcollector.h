// Scene Light collector
// rodesp@tecgraf.puc-rio.br
// Aug 2003

#ifndef SG_LIGHTCOLLECTOR_H
#define SG_LIGHTCOLLECTOR_H

#include <sg/strat/collector.h>
#include <sg/collight.h>
#include <sg/light.h>
#include "collightlist.h"

class SGLightCollector : public SGCollector
{
  SGColLightList m_result;
public:
  SGLightCollector()
  {
  }
  virtual ~SGLightCollector()
  {
  }
  // collector methods
  virtual SGCollection* GetResult ()
  {
    return &m_result;
  }
  SGColLightList::List::Iterator GetLights ()
  {
    return m_result.GetLights();
  }
  // strategy methods
  virtual int Load (SGLight* l)
  {
    if (l->IsEnabled())
      m_result.Insert(l);
    return CONTINUE;
  }
  virtual int Load (SGColLight* l)
  {
    if (l->IsEnabled())
      m_result.Insert(l->GetLight());
    return CONTINUE;
  }
  virtual void Release ()
  {
    m_result.Release();
  }
};

#endif
