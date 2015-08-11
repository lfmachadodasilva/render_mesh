/*
%M task2p.h - captura dois pontos
%a Marcelo Medeiros Carneiro
   Juli Huang
%d 03.08.94
%h Modificado em 7/5/96 por Newton Sanches para atender as novas especificoes
   do interact
%p Interact
*/

#ifndef __TASK2POINT__
#define __TASK2POINT__

#include "interactapi.h"
#include "itask.h"

/*
%C Classe para coleta de dois pontos num canvas interact
*/
class INTERACT_API itrTask2Point : public virtual itrTask {
 protected:
  double   px0, py0, px, py;
  int      ipx0, ipy0, ipx, ipy;
  itrCursor old_cursor;
  int initiated;
  int first;
  int pressed;

 public:
  itrTask2Point () ;
  virtual ~itrTask2Point () {};

  virtual void Repaint();

  virtual void Init ();
  virtual void Done ();

  virtual void Button1Pressed  ();
  virtual void Button1Motion   ();
  virtual void Button1Released ();
  virtual void FeedBack        (){} //= 0;
 
  virtual void EndObject       () = 0;
  virtual void GetObjectData   (int* x1,    int* y1,    int* x2,    int* y2);
  virtual void GetObjectData   (double* x1, double* y1, double* x2, double* y2);
};

#endif
