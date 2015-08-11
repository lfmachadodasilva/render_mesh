/*
%M itask.h - classe base dos tasks
%a Marcelo Medeiros Carneiro
   Juli Huang
%d 03/08/94
%h Acrescentado itr ao nome da classe; Modificado comportamento para aderir
   ao novo canvas itrCanvas
   Newton C. Sanches 03/05/96
%p Interact
*/

#ifndef __TASK__
#define __TASK__


// Remove warnings chatos do Visual C
#ifdef WIN32
#pragma warning( disable : 4514 )
#endif


#include "interactapi.h"
#include "ienv.h"

#define ITR_TASK_COLOR (itrEnvironment::FeedBackColor)

#define ITR_CALL_FB(_fb)   if(canvas->IsFeedBackEnabled())_fb()
#define ITR_CALL_EO(_eo)   _eo

class itrCanvas;

/*
%C Classe basica para as Tasks.  
*/
class INTERACT_API itrTask
{
 protected:
  itrCanvas* canvas;

 public:
  itrTask () {}
  virtual ~itrTask () {}

  virtual void Init () {}
  virtual void Done () {}

  virtual void Repaint        () {} 
  virtual void Button1Pressed (){}
  virtual void Button1Motion  (){}
  virtual void Button1Released(){}
  virtual void Button2Pressed (){}
  virtual void Button3Pressed (){}
  virtual void Button3Released(){}
  virtual void MouseMove      (){}
  virtual void EnterWindow    () {}
  virtual void LeaveWindow    () {}
  virtual void Keyboard       (int ) {}
  virtual void FeedBack       (void) = 0;
  virtual void DrawCursor     (int , int ) {}

  inline itrCanvas *GetCanvas ();
  inline  void SetCanvas      (itrCanvas *c);
  virtual void GetEventPos    (int* x, int* y);
  virtual void GetEventPos    (double* x, double* y);
  virtual char* GetEventStatus();
};


/*
%F Retorna o Canvas associado ao task
%o - ptr. para o Canvas
*/
inline itrCanvas* itrTask::GetCanvas()
{
  return canvas;
}

/*
%F Associa o Task a um canvas
%i c - o canvas a ser associado
*/
inline void itrTask::SetCanvas(itrCanvas* c)
{
  canvas = c;
}

#endif

