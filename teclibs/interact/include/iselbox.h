/*
%M iselbox.h - Conjunto de objetos selecionados pela task select
%a Marcelo Medeiros Carneiro
   Juli Huang
%d 03.08.94
%h Separado do tasksel em 13.05.96 por Newton Sanches
%p Interact
*/

#ifndef __ITR_SELBOX__
#define __ITR_SELBOX__

#include "interactapi.h"
#include "itransf.h"
#include "iselobj.h"

/*
%C Conjunto de objetos selecionados.  Contem a lista de itrSelObj selecionados
   o bounding box do conjunto, o centro de rotacao atual, a intercessao
   das permissoes
*/
class INTERACT_API itrSelBox {
public:
  double bbx[4], bby[4],   // bounding box
         sbbx[4],sbby[4],  // bounding box inicial
         rcx, rcy;         // centro de rotacao
  itrSelObj *first, *curr; // lista dos objetos selecionados
  itrTransf  t;            // operacoes de transformacao
  int    permission;       // intercessao das permissoes de todos os selecionados
 
  itrSelBox ();
  ~itrSelBox () {};
 
  void RegisterBox (void *id, double x0, double y0,
                              double x1, double y1, int perm);
  void RemoveBox (itrSelObj *s);
  void ChangeBox (void *id, double x0, double y0, double x1, double y1);
  void ResetBoxes ();
  itrSelObj *IsSelected (void *id);
 
  void TransformBoxes ();
  void UpdateBoxes ();
  void UpdateCenter ();
  void UpdateBB ();
 
  itrSelObj *Pop ();
  void    Push (itrSelObj *s);
 
  itrSelObj *First () { return first; }
  itrSelObj *Next (itrSelObj *s) { return s->next; }
 
  void *GetFirstId ();
  void *GetNextId ();
};


#endif
