#ifndef ANIMATION_H
#define ANIMATION_H

#include <uso/clock.h>
#include <vgl/handler.h>
#include <vglac/vglac.h>
#include <vgl/viewsurface.h>
#include <vgl/camera.h>
#include <vglac/defines.h>
#include <vglac/modules/vglacanimation.h>

#define VGL_ANIMATION_HANDLER "VGL_ANIMATION_HANDLER"

class VGLAC_API VglAnimationHandler : public VglHandler
{
protected:
   VglACAnimation m_animation;
   VglViewSurface* m_surface;
   int m_dframe;
   int m_currframe;
   USOClock m_clock;

public:
  static const char* CLASSNAME () { return VGL_ANIMATION_HANDLER; }
  virtual const char* ClassName () const { return CLASSNAME(); }
  
  VglAnimationHandler (VglViewSurface* surface);
  virtual ~VglAnimationHandler (){};

  virtual int GetFrameInterval(){return m_dframe;};
  virtual void SetFrameInterval(int dframe){m_dframe = dframe;};

  virtual void AddControlPoint();
  virtual void Reset();
  bool Save(char* filename);
  bool Load(char* filename);
  VglACAnimation& GetACAnim() { return m_animation; }

  virtual int Keyboard (int k, int st, float x, float y);
  virtual int PostRedraw ();
};

#endif
