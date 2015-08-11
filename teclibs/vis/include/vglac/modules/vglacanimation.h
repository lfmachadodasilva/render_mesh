#ifndef _VGLAC_VGLACANIMATION_H
#define _VGLAC_VGLACANIMATION_H

#include <stdio.h>
#include <vgl/camera.h>
#include <utl/writers/lua3filewriter.h>

#include <autocam/autocam.h>
#include <autocam/actransition.h>
#include <autocam/framemng.h>
#include <autocam/timemng.h>
#include <vglac/defines.h>

#define VLGAC_ANIMATION "VLGAC_ANIMATION"

class VGLAC_API VglACAnimation
{
public:
   typedef void (*UserDataWriteFunc) (UtlWriter *writer, void *data);
   typedef bool (*UserDataReadFunc) (FILE *fp, void *data);
private:
   ACManager m_manager;
   ACTransitionCut m_transitioncut;
   ACTransitionLinear m_transitionlinear;
   ACTransitionCubic m_transitioncubic;
   VglCamera *m_camera;
   UserDataWriteFunc m_userdatawritefunc;
   UserDataReadFunc m_userdatareadfunc;
   void *m_userdatawritedata;
   void *m_userdatareaddata;
public:
   VglACAnimation() :
     m_camera(NULL),
     m_userdatawritefunc(NULL),
     m_userdatareadfunc(NULL),
     m_userdatawritedata(NULL),
     m_userdatareaddata(NULL)
   {
   }
   virtual ~VglACAnimation(){};

   virtual const char *ClassName(){return VLGAC_ANIMATION;};

   void SetCamera(VglCamera *cam){m_camera = cam;};
   VglCamera *GetCamera(){return m_camera;};

   bool IsByFrame(){return m_manager.IsByFrame();};
   void SetByFrame(bool byframe){m_manager.SetByFrame(byframe);};

   int GetSize(){return m_manager.GetSize();};

   // RECORD MODE
   int AddControlPoint(double time, int frame, int postransition, int oritransition);
   int AddControlPoint(double time, int frame, AlgVector &pos, AlgQuatern &ori, int postransition, int oritransition);
   int AddControlPoint(double time, int frame, AlgVector &pos, AlgQuatern &ori, int postransition, int oritransition, float fovy, float fovx=-1);
   int RemoveControlPoint(int id){return m_manager.RemoveControlPoint(id);};
   bool RemoveAllControlPoints(){return m_manager.RemoveAllControlPoints();};
   //const ACControlPoint *GetControlPoint(int id){return m_manager.GetControlPoint(id);};
   //const ACControlPoint *GetControlPointInArray(int posarray){return m_manager.GetControlPointInArray(posarray);};
   void CutTake(){m_manager.CutTake();};

   int GetId(int posarray){return m_manager.GetId(posarray);};
   bool GetIdFrame(int id, int *frame){return m_manager.GetIdFrame(id, frame);};
   bool GetIdTime(int id, double *time){return m_manager.GetIdTime(id, time);};
   bool GetIdPosition(int id, AlgVector *pos){return m_manager.GetIdPosition(id, pos);};
   bool GetIdOrientation(int id, AlgQuatern *ori){return m_manager.GetIdOrientation(id, ori);};
   bool GetIdOrientation(int id, AlgVector *dir, AlgVector *up){return m_manager.GetIdOrientation(id, dir, up);};
   bool GetIdOrientation(int id, AlgVector *u, AlgVector *v, AlgVector *w){return m_manager.GetIdOrientation(id, u, v, w);};
   bool GetIdFovx(int id, float *fovx){return m_manager.GetIdFovx(id, fovx);};
   bool GetIdFovy(int id, float *fovy){return m_manager.GetIdFovy(id, fovy);};
   bool GetIdPosTransition(int id, int *postransition);
   bool GetIdOriTransition(int id, int *oritransition);
   bool GetIdCommentary(int id, const char **commentary){return m_manager.GetIdCommentary(id, commentary);};

   bool GetPosition(int frame, AlgVector *pos){return m_manager.GetPosition(frame, pos);};
   bool GetPosition(double time, AlgVector *pos){return m_manager.GetPosition(time, pos);};
   bool GetOrientation(int frame, AlgQuatern *ori){return m_manager.GetOrientation(frame, ori);};
   bool GetOrientation(double time, AlgQuatern *ori){return m_manager.GetOrientation(time, ori);};;
   bool GetFovx(int frame, float *fovx){return m_manager.GetFovx(frame, fovx);};
   bool GetFovx(double time, float *fovx){return m_manager.GetFovx(time, fovx);};
   bool GetFovy(int frame, float *fovy){return m_manager.GetFovy(frame, fovy);};
   bool GetFovy(double time, float *fovy){return m_manager.GetFovy(time, fovy);};

   bool SetIdFrame(int id, int frame){return m_manager.SetControlPointFrame(id, frame);};
   bool SetControlPointTime(int id, double time){return m_manager.SetControlPointTime(id, time);};
   bool SetControlPointPosition(int id, const AlgVector &pos){return m_manager.SetControlPointPosition(id, pos);};
   bool SetControlPointOrientation(int id, const AlgQuatern &ori){return m_manager.SetControlPointOrientation(id, ori);};
   bool SetControlPointOrientation(int id, const AlgVector  &dir, const AlgVector  &up){return m_manager.SetControlPointOrientation(id, dir, up);};
   bool SetControlPointOrientation(int id, const AlgVector  &u, const AlgVector  &v, const AlgVector  &w){return m_manager.SetControlPointOrientation(id, u, v, w);};
   bool SetControlPointFovx(int id, float fovx){return m_manager.SetControlPointFovx(id, fovx);};
   bool SetControlPointFovy(int id, float fovy){return m_manager.SetControlPointFovy(id, fovy);};
   bool SetControlPointPosTransition(int id, int postransition);
   bool SetControlPointOriTransition(int id, int oritransition);
   bool SetControlPointCommentary(int id, const char *commentary){return m_manager.SetControlPointCommentary(id, commentary);};
   bool SetControlPoint(int id, VglCamera *camera);

   // EXHIBITION MODE
   void Update(){m_manager.Update();};
   void UpdateCamera();
   void SetTime(double time){m_manager.SetTime(time);};
   double GetTime(){return m_manager.GetTime();};

   void SetFrame(int frame){m_manager.SetTime(frame);};
   int GetFrame(){return m_manager.GetFrame();};

   void Play(double ref){m_manager.Play(ref);};
   void Play(){m_manager.Play();};
   void Stop(){m_manager.Stop();};
   void Pause(){m_manager.Pause();};
   void Speed(double speed){m_manager.Speed(speed);};
   double GetSpeed(){return m_manager.GetSpeed();};

   bool IsPlaying(){return m_manager.IsPlaying();};
   bool IsPaused(){return m_manager.IsPaused();};

   int GetControlPointsPositions(float *posarray){return m_manager.GetControlPointsPositions(posarray);};
   int GetPathPointsPositions(int np, float *posarray){return m_manager.GetPathPointsPositions(np, posarray);};

   // Save/Load
   void Save(UtlWriter *writer);
   bool Save(FILE *fp);
   void SetUserDataWriteFunc (UserDataWriteFunc f, void *data)
   {
     m_userdatawritefunc = f;
     m_userdatawritedata = data;
   }
   bool Load(FILE *fp);
   bool Load(const char *filename);
   void SetUserDataReadFunc (UserDataReadFunc f, void *data)
   {
     m_userdatareadfunc = f;
     m_userdatareaddata = data;
   }
};

#endif
