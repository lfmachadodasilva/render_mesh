#ifndef VGL_POINT_PICK_H
#define VGL_POINT_PICK_H

#include <alg/vector.h>
#include <vgl/hnd/selection.h>
#include <vgl/viewsurface.h>

class VGL_API VglPointPickHandler : public VglSelectionHandler
{
public:
  static const char* CLASSNAME () { return "PointPickhandler"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
  VglPointPickHandler (VglViewSurface* surface, int sel_buf_size = 512, double tolw = 5.0, double tolh = 5.0) : 
    VglSelectionHandler(surface, sel_buf_size, tolw, tolh)
  {
  }
  virtual ~VglPointPickHandler()
  {
  }
  bool GetClosestPoint (float x, float y, float *wx, float *wy, float *wz);
  virtual void Pick (float x, float y);
protected:
  virtual void ProcessFunction (VglSelectionHit* hits, int n);
private:
  double m_x, m_y, m_z;
  bool m_anypoint;
};

#endif

