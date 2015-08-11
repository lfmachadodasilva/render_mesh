/*
%M tasksel.h - gerencia selecao e transformacao de objetos
%a Marcelo Medeiros Carneiro
   Juli Huang
%d 03.08.94
%h Modificado em 15/05/96 por Newton Sanches 
   para atender as novas especificacoes do interact
*/

#ifndef __TASKSELECT__
#define __TASKSELECT__

#include <stddef.h>
#include <stdlib.h>
#include "interactapi.h"
#include "itransf.h"
#include "itask.h"
#include "iselglob.h"
#include "iselbox.h"


/*
%C Tarefa de selecao de objetos
*/
class INTERACT_API itrTaskSelect : public virtual itrTask {
 private:

  double  evx, evy;       // ponto do ultimo evento (e fornecido `a aplicacao
                          // em GetPickPos()
  double  px[2], py[2];   // pontos inicial e final de um drag
  char    mode;           // estado da maquina de estados 
                          // 't' translacao
                          // 'r' rotacao
                          // 'f' fence (estando em modo de translacao)
                          // 'F' fence (estando em modo de rotacao)
                          // 's' selecao (estando em modo de translacao)
                          // 'S' selecao (estando em modo de rotacao)
    
  itrSelObj *picked;      // Objeto que foi pego.  
  itrSelBox  sel;         // lista dos selecionados
  int     pick_mark;      // tipo da alca na qual o mouse esta passando
                          //        6____5____4
                          //        |         |
                          //        7    9    3
                          //        |         |
                          //        8____1____2
         
  itrCursor old_cursor;   // Cursor do canvas antes da ativacao (Init) do task
  int     initialized;    // indica se o task ja esta inicializado 
  
  void TranslateBoxes ();
  void ResizeBoxes (char *r);
  void RotateBoxes (char *r);
  int PickMark (int x, int y);

 public:
   
  static int MarkSize;   // Tamanho das marcas, em pixeis  

  itrTaskSelect () : mode('t'), picked(NULL), old_cursor(ITR_C_ARROW) 
   {
    px[0]=px[1] = py[0]=py[1]=0;
    initialized = 0;
   }

  virtual ~itrTaskSelect () {}

  virtual void Init ();
  virtual void Done ();

  virtual void FeedBackTranslate ();
  virtual void FeedBackRotate    ();
  virtual void FeedBackCenter    ();
  virtual void FeedBackFence     ();
  virtual void FeedBackBoxes     ();

  virtual void Repaint ();
  virtual void Button1Pressed ();
  virtual void Button1Motion  ();
  virtual void Button1Released();
  virtual void MouseMove      ();

  void         RegisterBox (void *id, 
                            int x0, int y0, 
                            int x1, int y1, 
                            int perm=ITR_PTRANSFORM);
  void         RegisterBox (void *id, 
                            double x0, double y0, 
                            double x1, double y1, 
                            int perm=ITR_PTRANSFORM);

  void         ChangeBox   (void *id, 
                            int x0, int y0,
                            int x1, int y1);

  void         ChangeBox   (void *id, 
                            double x0, double y0,
                            double x1, double y1);
  
  inline void ResetBoxes ();
  inline void *GetFirstId ();
  inline void *GetNextId ();
 
  virtual void GetPickPos (int* x, int* y);
  virtual void GetPickPos (double* x, double* y);
  virtual void *Pick      () = 0;  // Pick usado no button pressed
  virtual int  QuickPick  () {return 0;}  // Pick usado no mouse 
                                             // move
  virtual void GetFenceArea(int* x1, int* y1, int* x2, int* y2);
  virtual void GetFenceArea(double* x1, double* y1,
                            double* x2, double* y2);
  virtual void  Fence     () = 0;
  virtual void  Transform (itrTransf t) = 0;
  virtual void  FeedBack  ();
};

//
// metodos inline
//


/*
%F "Zera" a lista de objetos selecionados
*/
inline void itrTaskSelect::ResetBoxes ()
{
 sel.ResetBoxes ();
}

/*
%F GetFirst do iterados de objetos selecionados
%o retorna o identificador do dito objeto
*/
inline void *itrTaskSelect::GetFirstId ()
{
 return sel.GetFirstId ();
}

/*
%F GetNext do iterados de objetos selecionados
%o retorna o identificador do dito objeto
*/
inline void *itrTaskSelect::GetNextId ()
{
 return sel.GetNextId ();
}

#endif


