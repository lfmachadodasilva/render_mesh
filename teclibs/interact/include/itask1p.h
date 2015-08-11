/*
%M task1p.h - Task de captura de 1 ponto
%a Marcelo Medeiros Carneiro
   Juli Huang
%d 03/08/94
%h Acrescentado itr ao nome da classe; Modificado comportamento para aderir
   ao novo canvas itrCanvas
   Newton C. Sanches 03/05/96
%p Interact
*/

#ifndef __TASK1POINT__
#define __TASK1POINT__

#include "interactapi.h"
#include "icanvas.h"
#include "itask.h"

/*
%C Tarefa de escolha de um ponto
%x Uma classe que derive desta sera notificada por FeedBack(),
   e EndObject() de eventos no meio e fim da escolha.  A 
   posicao corrente do GetObjectData(x,y), em versoes em 
   pixel ou coordenada do mundo.
*/
class INTERACT_API itrTask1Point : public virtual itrTask{
 private:
  int initiated;
 protected:
  
  int    ipx,  ipy;
  double px, py;
  char first;
  itrCursor old_cursor;

 public:
  itrTask1Point();
  virtual ~itrTask1Point(){}

  virtual void Init();
  virtual void Done();

  virtual void Repaint(); 
  virtual void Button1Pressed();
  virtual void Button1Released();
  virtual void Button1Motion  ();
  virtual void MouseMove      ();
  virtual void LeaveWindow    ();
  virtual void FeedBack       (){} //= 0;

  virtual void EndObject      () = 0;
  virtual void GetObjectData  (double* x, double* y);
  virtual void GetObjectData  (int* x,int* y);

};



#endif

