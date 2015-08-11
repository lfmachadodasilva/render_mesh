//* handlermanip.h
// vbarata@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Fev 2009

#ifndef TRN_HANDLER_MANIP_H
#define TRN_HANDLER_MANIP_H

//-----------------------------------//
// Includes and Forward Declarations //
//-----------------------------------//

#include "baseclass.h"
#include "handler.h"
#include <ds/array.h>
#include <alg/vector.h>
#include <vgl/handler.h>
#include <vgl/hnd/transformcenter.h>
#include <vgl/utils/modelrotation.h>
#include <vgl/utils/centercursor.h>
#include <vgl/utils/repeat.h>

class TrnTerrain;
class USOClock;

//-----------------------//
// TrnHandlerManip Class //
//-----------------------//

// This class implements a manipulation handler suitable for flat-world terrains

class TERRAINAPI TrnHandlerManip : public VglHandler, public VglTransformCenterUser, public TrnHandler
{
private:

  typedef enum _action
  {
    TRN_HANDLER_MANIP_NONE     = 0,
    TRN_HANDLER_MANIP_ROTATE_X = 1,
    TRN_HANDLER_MANIP_ROTATE_Y = 2,
    TRN_HANDLER_MANIP_ORBIT_X  = 3,
    TRN_HANDLER_MANIP_ORBIT_Y  = 4,
    TRN_HANDLER_MANIP_FLOAT    = 5,
    TRN_HANDLER_MANIP_WALK     = 6,
    TRN_HANDLER_MANIP_PAN      = 7,
  } TrnHandlerManipAction;

  typedef struct _function
  {
    TrnHandlerManipAction action;
    AlgVector vector;
    float delta;
    double time;
  } TrnHandlerManipFunction;

public:

  // Class Name

  static const char* CLASSNAME () { return "TrnHandlerManip"; }
  virtual const char* ClassName () const { return CLASSNAME(); }

  // Constructor and Destructor

  TrnHandlerManip (VglViewSurface* surface, TrnViewSpecifier* viewSpecifier);
  virtual ~TrnHandlerManip ();

  // Setters and Getters

  float GetXClick () const
  {
    return m_xclick;
  }

  float GetYClick () const
  {
    return m_yclick;
  }

  void SetConstrainAngle (float upnegangle, float downposangle);
  void SetConstrainHeight (float minheight, float maxheight);

  // Transform Center

  AlgVector ObtainTransformCenter () const;
  AlgVector ObtainTransformCenterEye () const;

  // VglHandler Initializer and De-initializer

  virtual void Begin ();
  virtual void End ();

  // Event Handlers

  virtual int MouseButton (int bt, int st, float x, float y);
  virtual int MouseMotion (int bt, float x, float y);
  virtual int MouseWheel (float delta, float x, float y);
  virtual int MouseEntry (bool st);

  bool IsAnimating ()
  {
    return m_animating;
  }

  bool IsDragging ()
  {
    return m_dragging;
  }

  void Stop ()
  {
    StopTransformRepeat();
  }

protected:

  // Information

  float GetCurrentTiltAngle (const TrnViewParameters& view);
  void GetAllowedBox (float* xmin, float* ymin, float* zmin, float* xmax, float* ymax, float* zmax);

  // Transform Center

  bool SetCenterWindow (const TrnViewParameters& view, float x, float y); // [0..1] from bottom left
  bool SetCenterModel (const TrnViewParameters& view);
  bool SetCenterView (const TrnViewParameters& view);
  bool SetCenterBox (const TrnViewParameters& view);
  bool SetCenter (float xworld, float yworld, float zworld);

  // Preparations

  void PreparePan (TrnViewParameters& view, float& xclick, float& yclick);
  float GetPanMaxY (TrnViewParameters& view);
  AlgVector GetPanWrlStep (TrnViewParameters& view, float x);
  AlgVector GetPanWrlMove (TrnViewParameters& view, float x, float y);

  // Transforms

  int DoRotatePan (TrnViewParameters& view, float angledeg, bool isrepeating = false);
  int DoRotateTilt (TrnViewParameters& view, float angledeg, bool isrepeating = false);
  int DoRotateCenter (TrnViewParameters& view, bool isrepeating = false);
  int DoOrbitAzimuth (TrnViewParameters& view, float angledeg, bool isrepeating = false);
  int DoOrbitElevation (TrnViewParameters& view, float angledeg, bool isrepeating = false);
  int DoFloat (TrnViewParameters& view, float delta, bool isrepeating = false);
  int DoWalk (TrnViewParameters& view, float delta, bool isrepeating = false);
  int DoPan (TrnViewParameters& view, float x, float y, bool isrepeating = false);
  int DoTranslate (TrnViewParameters& view, AlgVector wrlMove, bool isrepeating = false);

  // Transform Repeating

  static void RepeatTransform (void* data);

  bool StartTransformRepeat ();
  void DoTransformRepeat ();
  bool StopTransformRepeat ();

  // Flags

  void SetDragging (bool state)
  {
    if (m_dragging != state)
    {
      m_dragging = state;
      if (state)
        NotifyStartDragging();
      else
        NotifyStopDragging();
    }
  }

  // Notifications

  virtual void NotifyMove (bool changedtarget) {}
  virtual void NotifyStartDragging () {}
  virtual void NotifyStopDragging () {}
  virtual void NotifyStartAnimating () {}
  virtual void NotifyStopAnimating () {}
  virtual void NotifyPan () {}
  virtual void NotifyRotate () {}
  virtual void NotifyOrbit () {}
  virtual void NotifyFloat () {}
  virtual void NotifyWalk () {}

private:

  DsArray<TrnHandlerManipFunction> m_lastActions;
  DsArray<TrnHandlerManipFunction> m_repeatActions;

  VglModelRotation m_rotation;
  VglCenterCursor m_centercursor;

  USOClock* m_clock;
  double m_time_lastmotion;
  float m_xclick;
  float m_yclick;
  float m_ypanmax;
  AlgVector m_ypanstep;
  char m_constraint;
  bool m_didmove;
  bool m_dragging;
  bool m_animating;

};

#endif // TRN_HANDLER_MANIP_H
