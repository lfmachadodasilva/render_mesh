/*
%M tasknp.h - captura uma polyline
%a Marcelo Medeiros Carneiro
   Juli Huang
%d 03.08.94

%h Modificado em 8/5/96 para atender aos novos requisitos do
   interact
*/ 
#ifndef __TASKNPOINT__
#define __TASKNPOINT__

#include "interactapi.h"
#include "itask.h"

/*
%K No. maximo de pontos no polyline
*/
#define ITR_MAXPNT  10

/*
%K Tipo do polyline gerado
*/
#define ITR_CLOSED  1
#define ITR_OPEN    0

/*
%C Tarefa de coleta de varios pontos (como na construcao de um
   polyline
*/
class INTERACT_API itrTaskNPoint : public virtual itrTask {
 protected:
  int *ipx,
      *ipy; 
  double  *px,
          *py; 
  int maxpoints;
  int n; int rubber;   // rubber-band 

  itrCursor old_cursor; 
  int style; 
  int mode;
  int initiated;

 public:
  itrTaskNPoint ();
  virtual ~itrTaskNPoint () {}

  virtual void Init ();
  virtual void Done ();

  virtual void Repaint ();
  virtual void Button1Pressed ();
  virtual void Button2Pressed ();
  virtual void Button3Pressed ();
  virtual void Button1Released();
  virtual void MouseMove      ();
  virtual void EnterWindow    () {};
  virtual void LeaveWindow    ();
  virtual void Keyboard       (int key);
  virtual void FeedBack       ();
  virtual void FeedBackAll    ();

  virtual void EndObject      (int mode) = 0;
  virtual void GetObjectData  (int* n, int* x[],    int* y[]);
  virtual void GetObjectData  (int* n, double* x[], double* y[]); 
};

#endif
