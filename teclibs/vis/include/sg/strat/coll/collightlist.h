// Collected Light List class
// fabraham@tecgraf.puc-rio.br
// May 2005

#ifndef SG_COLLIGHTLIST_H
#define SG_COLLIGHTLIST_H

#include <ds/list.h>
#include <sg/collection.h>

class SGLight;

class SG_API SGColLightList : public SGCollection
{
public:
  typedef DsPList<SGLight> List;
  static const char* CLASSNAME () { return "ColLightList"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
  SGColLightList ()
  {
  }
  virtual ~SGColLightList ()
  {
  }
  void Insert (SGLight* l)
  {
    m_result.Append(l);
  }
  List::Iterator GetLights ()
  {
    return m_result.Begin();
  }
  virtual void Release ()
  {
    m_result.Clear();
  }
private:
  List m_result;
};

#endif

