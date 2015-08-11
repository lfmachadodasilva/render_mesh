/*
%M iselobj.c - Objeto selecionado pela task select
%a Marcelo Medeiros Carneiro
   Juli Huang
%d 03.08.94
%h Separado do tasksel em 13.05.96 por Newton Sanches
%p Interact
*/

#ifndef __SELOBJ__
#define __SELOBJ__

#include "interactapi.h"
/*
%C Objeto selecionado pela task select.  Guarda o Bounding box e o Id (void*) 
   do objeto selecionado
*/
struct INTERACT_API itrSelObj {
  double px[2], py[2],  // 0: min, 1: max
         sx[2], sy[2];  // coordenadas iniciais
 
  void *id;             // identificador o object selecionado
                        // (serve para a aplicacao poder referencia'-lo)
  int    permission;    // permissoes p/ transformar objeto
  itrSelObj *next;      // proximo na lista de permissoes
 
  itrSelObj ();
  // Pensar em tirar itrSelObj(int)
  itrSelObj (void *id, int x0, int y0, int x1, int y1, int perm);
  
  itrSelObj (void *id, double x0, double y0,
                       double x1, double y1, int perm);

  virtual ~itrSelObj () {};
};


#endif
