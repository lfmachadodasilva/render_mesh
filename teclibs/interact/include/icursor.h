#ifndef __ITR_CURSOR__
#define __ITR_CURSOR__

#include <cd.h>
#include <iup.h>
#include "interactapi.h"

#define ITR_MAX_CURSORS 30 

class itrCursorPen;
class itrRefCursorPen;
class itrCanvas;

/*
$T O tipo itrCursor e' na realidade um ponteiro para um itrCursorPen, que
   e' responsavel por desenhar o cursor
*/
typedef itrCursorPen* itrCursor;
/*
$T Ponteiro para um cursor de operacao.
*/
typedef itrRefCursorPen* itrRefCursor;

/*
%C itrCursorDriver - Classe responsavel por saber quando e porque pintar 
   o cursor.  Esta sempre utilizando um itrCursorPen, que e' quem realmente
   desenha o cursor (ou altera o cursor IUP)
*/
class INTERACT_API itrCursorDriver
{
protected:
   int shown;                    // indica se o cursor esta visivel no momento
   int losttrack;                // indica se o mouse saiu do canvas no qual 
                                 // estava o cursor.
   int cx, cy;                   // posicao do cursor
   int width, height;            // tamanho do canvas onde esta operando
   char snap;                    // determina se o cursor usara os pontos
                                 // do grid ou nao
   itrCanvas* canvas;            // canvas interact ao qual o CursorDriver esta
                                 // servindo.

   itrCursorPen* activepen;      // pena ativa no momento.  E' ela que determina
                                 // o desenho do cursor

public:
   itrCursorDriver();

   void SetPos(int x, int y, int unsnap_x, int unsnap_y);
   void Show();
   void Hide();
   void Draw();
   void LostTrack();

   void SetSnap(int s){snap = (char)s;}

   void SetCanvasSize(int h, int w);
   void GetCanvasSize(int *h, int *w);

   void SetPen(itrCursor c);
   itrCursor GetPen();

   void SetCanvas(itrCanvas* c){canvas = c;}
   itrCanvas* GetCanvas(){return canvas;}
};

/*
%C itrCursorPen - Determina o desenho de um cursor, e tambem o cursor IUP que
   o acompanhara'
*/
class INTERACT_API itrCursorPen
{
protected:
   void Prepare(itrCursorDriver* cdrv);  // Prepara o canvas para o desenho
   void Finish(itrCursorDriver* cdrv);   // Termina o desenho do canvas
public: 
   static void  InitializeDefault();
   virtual void Activate(itrCursorDriver* cdrv)=0;
   virtual void Deactivate(itrCursorDriver* cdrv)=0;
   virtual void Draw(itrCursorDriver* cdrv, int x, int y)=0;
};

/*
%C itrIupCursorPen - Modela os cursores do IUP.  Portanto nao precisa de rede
   senho.  O metodo Draw() e' vazio.
*/
class INTERACT_API itrIupCursorPen: public itrCursorPen
{
   char* cursor;
public:
   itrIupCursorPen(char* c); 
   virtual void Activate(itrCursorDriver* cdrv);
   virtual void Deactivate(itrCursorDriver* cdrv);
   virtual void Draw(itrCursorDriver* , int , int ){};
};


/*
%C itrIupAndCrossPen - Modela um cursor que, alem do cursor IUP ainda desenha
   uma CRUZ, que se extende por todo o canvas.   Se o cursor IUP especificado
   for IUP_NONE, resulta num CrossHair simples.
*/
class INTERACT_API itrIupAndCrossPen: public itrIupCursorPen
{
   char* cursor;
public:
   itrIupAndCrossPen(char* c=IUP_NONE); 
   virtual void Draw(itrCursorDriver* , int , int );
};


/* 
%K Valores para definir cursores IUP.  Sao ponteiros para itrCursorPen
*/

#ifdef __SELF__
# define EXTERN 
#else
# define EXTERN extern
#endif

INTERACT_API EXTERN itrCursor ITR_C_ARROW      ;
INTERACT_API EXTERN itrCursor ITR_C_BUSY       ;
INTERACT_API EXTERN itrCursor ITR_C_RESIZE_N   ;
INTERACT_API EXTERN itrCursor ITR_C_RESIZE_S   ;
INTERACT_API EXTERN itrCursor ITR_C_RESIZE_E   ;
INTERACT_API EXTERN itrCursor ITR_C_RESIZE_W   ;
INTERACT_API EXTERN itrCursor ITR_C_RESIZE_NE  ;
INTERACT_API EXTERN itrCursor ITR_C_RESIZE_NW  ;
INTERACT_API EXTERN itrCursor ITR_C_RESIZE_SE  ;
INTERACT_API EXTERN itrCursor ITR_C_RESIZE_SW  ;
INTERACT_API EXTERN itrCursor ITR_C_MOVE       ;
INTERACT_API EXTERN itrCursor ITR_C_HAND       ;
INTERACT_API EXTERN itrCursor ITR_C_NONE       ;
INTERACT_API EXTERN itrCursor ITR_C_IUP        ;
INTERACT_API EXTERN itrCursor ITR_C_CROSS      ;
INTERACT_API EXTERN itrCursor ITR_C_PEN        ;
INTERACT_API EXTERN itrCursor ITR_C_TEXT       ;
INTERACT_API EXTERN itrCursor ITR_C_RESIZE_C   ;
INTERACT_API EXTERN itrCursor ITR_C_OPENHAND   ;

/* 
%K Valores para cursores extendidos (Iup + desenho no canvas). 
*/
INTERACT_API EXTERN itrCursor ITR_C_CROSSHAIR  ;
INTERACT_API EXTERN itrCursor ITR_C_CROSS_BUSY ;
INTERACT_API EXTERN itrCursor ITR_C_CROSS_ARROW;
INTERACT_API EXTERN itrCursor ITR_C_CROSS_MOVE ;
INTERACT_API EXTERN itrCursor ITR_C_CROSS_HAND ;

/*
%K Valores para cursores de operacao.
*/ 
INTERACT_API EXTERN itrCursor ITR_C_NORMAL     ;
INTERACT_API EXTERN itrCursor ITR_C_OVER       ;
INTERACT_API EXTERN itrCursor ITR_C_DRAGOBJECT ;
INTERACT_API EXTERN itrCursor ITR_C_DRAGNODE   ;
INTERACT_API EXTERN itrCursor ITR_C_DRAGEDGE   ;
INTERACT_API EXTERN itrCursor ITR_C_MARK       ;
INTERACT_API EXTERN itrCursor ITR_C_FORBIDEN   ;
INTERACT_API EXTERN itrCursor ITR_C_MOVEABLE   ;
INTERACT_API EXTERN itrCursor ITR_C_SELECTABLE ;

#undef EXTERN

#endif
