//* eventdebugger.h
// celes@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Jan 2003

#ifndef VGL_EVENTDEBUGGER_H
#define VGL_EVENTDEBUGGER_H

#include <vgl/handler.h>
#include <stdio.h>

/**
 * This class prints all received event information.
 * It is useful for your application debugging.
 */
class VGL_API VglEventDebugger : public VglHandler
{
  char *m_label;
public:
  /**
   * Returns the event handler class classname.
   * \return Event handler class classname.
   */
  static const char* CLASSNAME () { return "EventDebugger"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
  VglEventDebugger (const char *label=0)
  {
    m_label = label ? strdup(label) : 0;
  }
  virtual ~VglEventDebugger ()
  {
    free(m_label);
  }
  virtual int Keyboard (int k, int st, float x, float y)
  {
    printf("%s%skey: %d  %d @ %f %f\n",m_label?m_label:"",m_label?": ":"",k,st,x,y);
		return 1;
  }
  virtual int MouseButton (int bt, int st, float x, float y)
  {
    printf("%s%sbt: %d %d @ %f %f c=%d s=%d\n",m_label?m_label:"",m_label?": ":"",bt,st,x,y,GetCtrl(),GetShift());
		return 1;
  }
  virtual int MouseMotion (int bt, float x, float y)
  {
    printf("%s%sbt: %d dist: %f %f\n",m_label?m_label:"",m_label?": ":"",bt,x-GetLastX(),y-GetLastY());
		return 1;
  }
  virtual int MouseEntry (bool st)
  {
    printf("%s%sst: %d\n",m_label?m_label:"",m_label?": ":"",st);
		return 1;
  }
};

#endif
