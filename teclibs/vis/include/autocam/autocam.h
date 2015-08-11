#ifndef _AUTOCAM_AUTOCAM_H
#define _AUTOCAM_AUTOCAM_H

#include <stdio.h>
#include <alg/vector.h>
#include <alg/quatern.h>
#include <utl/writers/lua3filewriter.h>
#include <ds/array.h>
#include <splib/splib.h>

#include "defines.h"
#include "actransition.h"
#include "framemng.h"
#include "timemng.h"

#define AUTOCAM_CONTROLPOINT "AUTOCAM_CONTROLPOINT"
#define AUTOCAM_MANAGER "AUTOCAM_MANAGER"

class AUTOCAM_API ACControlPoint
{
private:
   static int m_nextid;
   int m_id;
   double m_time;
   int m_frame;

   float m_fovx, m_fovy;

   int m_splinepos;
   int m_qsplinepos;

   char *m_commentary;
   AlgVector m_pos;
   AlgQuatern m_ori;
   ACTransition *m_postransition;
   ACTransition *m_oritransition;

   Spline *m_spline;
   QSpline *m_qspline;

public:
   ACControlPoint();
   virtual ~ACControlPoint(){delete m_commentary;};

   virtual const char *ClassName(){return AUTOCAM_CONTROLPOINT;};

   int GetId(){return m_id;};

   ACTransition *GetPosTransition(){return m_postransition;};
   void SetPosTransition(ACTransition *transition){m_postransition = transition;};

   ACTransition *GetOriTransition(){return m_oritransition;};
   void SetOriTransition(ACTransition *transition){m_oritransition = transition;};

   const char *GetCommentary(){return m_commentary;};
   void SetCommentary(const char *commentary);

   double GetTime(){return m_time;};
   void SetTime(double time){m_time = time;};

   int GetFrame(){return m_frame;};
   void SetFrame(int frame){m_frame = frame;};

   AlgVector GetPosition(){return m_pos;};
   void SetPosition(const AlgVector &position){m_pos = position;};

   AlgQuatern GetOrientation(){return m_ori;};
   void SetOrientation(const AlgQuatern &orientation){m_ori = orientation;};
   void SetOrientation(const AlgVector &dir, const AlgVector &up);
   void SetOrientation(const AlgVector &u, const AlgVector &v, const AlgVector &w){m_ori.Set(u, v, w);};

   float GetFovx(){return m_fovx;};
   void SetFovx(float fovx){m_fovx = fovx;};

   float GetFovy(){return m_fovy;};
   void SetFovy(float fovy){m_fovy = fovy;};

   int GetSplinePos(){return m_splinepos;};
   void SetSplinePos(int splinepos){m_splinepos = splinepos;};

   int GetQSplinePos(){return m_qsplinepos;};
   void SetQSplinePos(int qsplinepos){m_qsplinepos = qsplinepos;};

   Spline *GetSpline(){return m_spline;};
   void SetSpline(Spline *spline){m_spline = spline;};

   QSpline *GetQSpline(){return m_qspline;};
   void SetQSpline(QSpline *qspline){m_qspline = qspline;};

   void Save(UtlWriter *writer);
   bool Save(FILE *fp);
   bool Load(FILE *fp);
};

typedef DsArray<ACControlPoint*> ACControlPointArray;
typedef DsArray<Spline*> SplineArray;
typedef DsArray<QSpline*> QSplineArray;

class AUTOCAM_API ACManager
{
private:
   bool m_byframe;
   ACControlPointArray m_controlpoints;
   SplineArray m_splines;
   QSplineArray m_qsplines;

   ACFrameManager m_framemng;
   TimeManager m_timemng;

   void RemoveSpline(Spline *spline);

public:
   ACManager();
   virtual ~ACManager();

   virtual const char *ClassName(){return AUTOCAM_MANAGER;};

   // Time/Frame Control Methods
   void SetByFrame(bool byframe){m_byframe = byframe;};
   bool IsByFrame(){return m_byframe;};

   // RECORD MODE
   int AddControlPoint(double time, int frame, const AlgVector &pos, const AlgQuatern &ori, ACTransition *postransition, ACTransition *oritransition);
   int AddControlPoint(double time, int frame, const AlgVector &pos, const AlgVector &u, const AlgVector &v, const AlgVector &w, ACTransition *postransition, ACTransition *oritransition);
   int AddControlPoint(double time, int frame, const AlgVector &pos, const AlgVector &dir, const AlgVector &up, ACTransition *postransition, ACTransition *oritransition);

   int AddControlPoint(double time, int frame, const AlgVector &pos, const AlgQuatern &ori, ACTransition *postransition, ACTransition *oritransition, float fovy, float fovx = -1);
   int AddControlPoint(double time, int frame, const AlgVector &pos, const AlgVector &u, const AlgVector &v, const AlgVector &w, ACTransition *postransition, ACTransition *oritransition, float fovy, float fovx = -1);
   int AddControlPoint(double time, int frame, const AlgVector &pos, const AlgVector &dir, const AlgVector &up, ACTransition *postransition, ACTransition *oritransition, float fovy, float fovx = 1);

   int RemoveControlPoint(int id);
   bool RemoveAllControlPoints();

   //ACControlPoint *GetControlPoint(int id);
   //ACControlPoint *GetControlPointInArray(int posarray);
   int GetId(int posarray);
   bool GetIdFrame(int id, int *frame);
   bool GetIdTime(int id, double *time);
   bool GetIdPosition(int id, AlgVector *pos);
   bool GetIdOrientation(int id, AlgQuatern *ori);
   bool GetIdOrientation(int id, AlgVector *dir, AlgVector *up);
   bool GetIdOrientation(int id, AlgVector *u, AlgVector *v, AlgVector *w);
   bool GetIdFovx(int id, float *fovx);
   bool GetIdFovy(int id, float *fovy);
   bool GetIdPosTransition(int id, ACTransition **postransition);
   bool GetIdOriTransition(int id, ACTransition **oritransition);
   bool GetIdCommentary(int id, const char **commentary);

   bool SetControlPoint(int id, double time, int frame, const AlgVector &pos, const AlgQuatern &ori, ACTransition *postransition, ACTransition *oritransition, const char *commentary);
   bool SetControlPoint(int id, double time, int frame, const AlgVector &pos, const AlgVector &u, const AlgVector &v, const AlgVector &w, ACTransition *postransition, ACTransition *oritransition, const char *commentary);
   bool SetControlPoint(int id, double time, int frame, const AlgVector &pos, const AlgVector &dir, const AlgVector &up, ACTransition *postransition, ACTransition *oritransition, const char *commentary);

   bool SetControlPointFrame(int id, int frame);
   bool SetControlPointTime(int id, double time);
   bool SetControlPointPosition(int id, const AlgVector &pos);
   bool SetControlPointOrientation(int id, const AlgQuatern &ori);
   bool SetControlPointOrientation(int id, const AlgVector  &dir, const AlgVector  &up);
   bool SetControlPointOrientation(int id, const AlgVector  &u, const AlgVector  &v, const AlgVector  &w);
   bool SetControlPointFovx(int id, float fovx);
   bool SetControlPointFovy(int id, float fovy);
   bool SetControlPointPosTransition(int id, ACTransition *postransition);
   bool SetControlPointOriTransition(int id, ACTransition *oritransition);
   bool SetControlPointCommentary(int id, const char *commentary);
   void CutTake();

   // EXBITION MODE

   // Update
   void Update(){m_framemng.Update();};

   void SetTime(double time);
   double GetTime(){return m_timemng.GetTime();};

   void SetFrame(int frame);
   int GetFrame(){return m_framemng.GetFrame();};

   void Play(double ref);
   void Play();
   void Stop();
   void Pause();
   void Speed(double speed);
   double GetSpeed(){return m_framemng.GetSpeed();};

   bool GetPosition(AlgVector *pos);
   bool GetPosition(int frame, AlgVector *pos);
   bool GetPosition(double time, AlgVector *pos);
   
   bool GetOrientation(AlgQuatern *ori);
   bool GetOrientation(AlgVector *dir, AlgVector *up);
   bool GetOrientation(AlgVector *u, AlgVector *v, AlgVector *w);
   bool GetOrientation(int frame, AlgQuatern *ori);
   bool GetOrientation(double time, AlgQuatern *ori);

   bool GetFovx(float *fovx);
   bool GetFovx(int frame, float *fovx);
   bool GetFovx(double time, float *fovx);

   bool GetFovy(float *fovy);
   bool GetFovy(int frame, float *fovy);
   bool GetFovy(double time, float *fovy);

   bool IsPlaying(){return m_framemng.IsRunning();};
   bool IsPaused(){return m_framemng.IsPaused();};

   int GetControlPointsPositions(float *posarray);
   int GetPathPointsPositions(int np, float *posarray);

   // ALL MODES
   int GetSize(){return m_controlpoints.Size();}

   // Callbacks Methods

   // Save/Load Methods
   void Save(UtlWriter *writer);
   bool Save(FILE *fp);
   bool Load(FILE *fp);
};

#endif
