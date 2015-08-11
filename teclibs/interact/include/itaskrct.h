/*
M% taskrect.c - captura dois pontos, com feedback de retangulo
a% Marcelo Medeiros Carneiro
   Juli Huang
%d 03.08.94

%h Neil : mudanca para CD, este modulo em 29/11/95
   Newton : mudanca para atender ao novo canvas interact em 8/5/95
*/

#ifndef __TASKRECT__
#define __TASKRECT__

#include "interactapi.h"
#include "itask2p.h"

/*
%C Tarefa de coleta de dois pontos, com feedback predefinido de retangulo
*/
class INTERACT_API itrTaskRect : public virtual itrTask2Point
{
 public:
  itrTaskRect () : itrTask2Point () {};
  virtual ~itrTaskRect () {};
  virtual void FeedBack ();
};

#endif
