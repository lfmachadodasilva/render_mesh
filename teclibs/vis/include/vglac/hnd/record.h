#ifndef VGL_RECORD_H
#define VGL_RECORD_H

#include <vgl/handler.h>
#include <vglac/defines.h>

class USOClock;
class VglViewSurface;
class ACManager;
class ACTransition;

class VGLAC_API VglRecordHandler : public VglHandler
{
  VglViewSurface* m_surface;
  USOClock *m_clock;
  ACManager* m_manager;
  ACTransition *m_transition;
  void AddControlPoint ();
protected:
  VglViewSurface* GetSurface ()
  {
    return m_surface;
  }
public:
  static const char* CLASSNAME () { return "RecordHandler"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
  VglRecordHandler (VglViewSurface* surface);
  virtual ~VglRecordHandler ();
  virtual int Keyboard (int k, int st, float x, float y);
	virtual int PostRedraw ();
};

#endif
