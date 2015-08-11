#ifndef VGL_DISTANCE_PICK_H
#define VGL_DISTANCE_PICK_H

#include <alg/vector.h>
#include <vgl/hnd/pointpick.h>
#include <vgl/viewsurface.h>

class VGL_API VglDistancePickHandler : public VglPointPickHandler
{
public:
  typedef void (*DistanceCb)(const AlgVector* p0, const AlgVector* p1, void* data);
  typedef void (*PostRedrawCb)(void* data);

  static const char* CLASSNAME () { return "DistancePickHandler"; }
  virtual const char* ClassName () const { return CLASSNAME(); }

  VglDistancePickHandler(VglViewSurface* surface);  
  virtual ~VglDistancePickHandler();
  void ResetLine()
  {
    m_hasline = false;
    m_first_move = true;
  }
  /**
    Sets the function called when distance events are delivered.
    If one of the two points are invalid, then the parameter will be NULL.
  */
  void SetDistanceFunc(DistanceCb cb, void* data);
  /**
    Sets a function to called when the final line is drawn.
  */
  void SetPostRedrawFunc(PostRedrawCb cb, void* data)
  {
    m_prcb = cb;
    m_prcb_data = data;
  }
  /**
    Enables/disables calling of DistanceCb during mouse motion events.
    If disabled, the event will be called after picking the to necessary points
    to compute distance.
  */
  void SetMotionEventEnabled(bool flag);
  /**
    Enables/disables line persistence after picking the two distance points.
  */
  void SetPersistentLineEnabled(bool flag);
  virtual void Begin();
  virtual void End();
  virtual int MouseMotion(int bt, float x, float y);
  virtual int MouseButton(int bt, int st, float x, float y);   
  virtual int PostRedraw (void);

protected:
  virtual void ProcessFunction (VglSelectionHit* hits, int n);

private:                           
  DistanceCb m_cb;
  PostRedrawCb m_prcb;
  void* m_cb_data;
  void* m_prcb_data;
  bool m_ispicking;
  bool m_haspickedpoint;
  bool m_persistentline;
  bool m_hasline;
  bool m_first_move;
  bool m_motioncb;

  float m_x0, m_y0;
  float m_x1, m_y1; 
  float m_x, m_y;
  AlgVector m_wp, m_wp0, m_wp1;

  void BeginLine(float x, float y);
  void MoveLine(float x, float y);
  void FinishLine();
};

#endif

