/*
%M icanvas.c - Abstracao de Canvas do IUP para o Interact (classe basica para os
               canvas interact
%a Marcelo Medeiros Carneiro, Juli Huang
%d 03/05/96
%p Interact 
%h - Mudanca para base em cd
     Neil, 30/05/95
   - Mudanca para double coordinates
     Lula, 15/04/96
   - Mudanca de nomes de classe, separacao entre itrWorldCanvas e itrRasterCanvas
   - Introducao de busca de coordenadas a demanda
     Newton Sanches, 03/05/96

*/

#ifndef __ITR_CANVAS__
#define __ITR_CANVAS__

// Remove warnings chatos do Visual C
#ifdef WIN32
#pragma warning( disable : 4514 )
#endif
  
#include <iup.h>
#include <cd.h>
#include "interactapi.h"
#include "itask.h"
#include "itsstack.h"
#include "icursor.h"



/*
%C Abstracao de Canvas IUP para trabalhar com o interact
%x E' virtual, pois lhe falta informacao sobre como manipular coordenadas
   E' derivada por itrRasterCanvas e itrWorldCanvas que lhe conferem, de duas
   formas distintas esta habilidade
*/
class INTERACT_API itrCanvas {
private:
    Ihandle*      iupcanvas;
    cdCanvas*     cdcanvas;            
    int           mouse_near;      // indica se o mouse esta prox. do pt. 
    int           btdown;          // indica se o botao esta apertado
                                   // inicial do drag
    itrTaskStack  taskstack;       // Pilha de tarefas 
    int           mouse_x,mouse_y; // posicao originais-sem snap
    int	         mapped;          // indica se o canvas IUP ja foi mapeado
    int           oldx, oldy;      // posicao anterior do cursor
    
    char          *cb_old_button, *cb_old_motion,
                  *cb_old_enter,  *cb_old_leave,
                  *cb_old_repaint,*cb_old_resize,
                  *cb_old_kany;    // acoes do iup

    static Icallback cb_old_idle;  // antiga CB idle
    static itrCanvas* CurrCanvas;  // Canvas que vai ser pintado no prox. idle
    static itrCanvas* FirstCanvas; // Primeiro canvas da lista de canvas
    itrCanvas*    Next;

    void          AddCanvas();     // Inclui um canvas na lista de canvas
    void          DelCanvas();     // Exclui um canvas da lista de canvas
    static itrCanvas* NextRepaintable();  // Retorna o proximo canvas

    double        real_x, real_y;  // posicao original fornecida pela
                                   // pela Repaint do IUP, usada para chamar
                                   // a Repaint velha (cb_old_repaint)
	      
    // Callbacks para o IUP
    static int CanvasRepaint       (Ihandle*, float, float);
    static int CanvasResize        (Ihandle*, int, int); 	      
    static int CanvasButton        (Ihandle*, int, int, int, int, char*);
    static int CanvasMotion        (Ihandle*, int, int, char*);
    static int CanvasEnter         (Ihandle*);
    static int CanvasLeave         (Ihandle*);
    static int CanvasKAny          (Ihandle*, int);
    static int CanvasIdle          (void);

    int idle_repaint;              // indica se o repaint no idle esta habilitado
                                   // 0 -> Habilitado;  >0 -> Desabilitado
    int feedback;                  // indica se o repaint dos feedbacks esta disponivel	
                                   // 0 -> Habilitado;  >0 -> Desabilitado

    char* buttonstatus;

    void PaintTasks       ();
    void SetUpCallbacks   ();
    void RestoreCallbacks ();
    
protected:
    virtual void OnMap();
    virtual void OnEnableIdleRepaint();
    virtual void OnDisableIdleRepaint();

    itrCursorDriver curdrv;        // Familia de cursores utilizada
    //  As funcoes abaixo servem para que cada herdeiro de itrCanvas tratem
    //  situacoes que dependem do sistema de coord.

    virtual void _MoveWindow       (double, double)=0;
    virtual void _ResizeWindow     (int, int)=0;
    virtual void _PrepareCoords    (int, int, int/*dosnap*/)=0;
    virtual void _PrepareToRepaint (int xmin, int ymin, int xmax, int ymax)=0;
    virtual void _PrepareToRepaint ()=0;
 
public:
    itrCanvas   (Ihandle*, cdCanvas*);
    virtual ~itrCanvas();

    virtual void GetEventPos      (int*, int*)=0;
    virtual void GetEventPos	  (double*, double*)=0;
    virtual void GetEventUnsnapPos(int *,int *)=0;
    virtual void GetEventUnsnapPos(double*, double*)=0;
    virtual void Raster2World     (int, int, double*, double*)=0;
    virtual void World2Raster     (double, double, int*, int*)=0;

    inline char* GetEventStatus   ();
    inline Ihandle*  GetHandle    ();
    inline cdCanvas* GetCanvas    ();
    inline  void SetNear          (int on);
    inline  int  IsNear           ();
    void         PushTask         (itrTask* t);
    void         PopTask          ();
    itrTask*     GetTask          ();
    void         SetCursor        (itrCursor,int snap=0);
    itrCursor    GetCursor        ();
    virtual void GetCanvasSize    (int*, int*){};
    void         ShowCursor       ();
    void         HideCursor       ();

    void   EnableIdleRepaint      ();
    void   DisableIdleRepaint     ();
    int    IsIdleRepaintEnabled   ();
    void   EnableFeedBack         ();
    void   DisableFeedBack        ();
    int    IsFeedBackEnabled      (); 
      
   
    // Funcoes virtuais - Abstracoes de CallBacks
    virtual void Button1Pressed   (){}
    virtual void Button1Motion    (){}
    virtual void Button1Released  (){}
    virtual void Button2Pressed   (){}
    virtual void Button2Released  (){}
    virtual void Button3Pressed   (){}
    virtual void Button3Released  (){}
    virtual void MouseMove        (){}
    virtual void EnterWindow      (){}
    virtual void LeaveWindow      (){}
    virtual void Keyboard         (int){}
    virtual void Repaint          ()=0;
    virtual void IdleRepaint      (){};
    virtual void Resize           (){};

    virtual void Refresh          ();
	 virtual void PaintToCanvas    (cdCanvas* altcnv);
 	 virtual void PaintToCanvas    (cdCanvas* altcnv, int, int, int, int);

    virtual int  IsMapped         ();
   
    // Funcoes de uso primariamente interno
    inline  void Unsnap           (int *,int *);
    inline  void SetUnsnap        (int , int); 
    void         ChangeCursor     ();
};


/*
%F Pega as coordenadas originais de um evento, isto e', antes dele ter passado
   por Snap
%o (x,y) coordenadas originais
*/
inline void itrCanvas::Unsnap (int *x, int *y)
{
 *x=mouse_x; *y=mouse_y;
}

/*
%F Seta as coordenas do ponto original do evento (uso interno)
%i (x,y) coordenadas originais
*/
inline void itrCanvas::SetUnsnap (int x, int y)
{
 mouse_x = x; mouse_y = y;
}

/*
%F Set a flag Indica se o ponto esta proximo do pt. original drag ou nao
*/
inline void itrCanvas::SetNear (int on)
{
 mouse_near = on;
}

/*
%F Consulta a flag que indica se o ponto atual esta proximo do pt.original 
   drag
*/
inline int  itrCanvas::IsNear ()
{
 return mouse_near;
}

/*
%F Retorna o handle do canvas IUP associado ao itrCanvas
*/
inline Ihandle* itrCanvas::GetHandle ()
{
 return iupcanvas;
}

/*
%F Retorna o cdCanvas* do canvas cd associado ao itrCanvas
*/
inline cdCanvas* itrCanvas::GetCanvas ()
{
 return cdcanvas;
}

/*
%F Retoran o tipo de cursor atual
*/
inline itrCursor itrCanvas::GetCursor()
{
 return curdrv.GetPen();
}

/*
%F Retorna o char* de status dos botoes e teclas modificadoras
*/
inline char* itrCanvas::GetEventStatus()
{
 return buttonstatus;
}

/*
%F Retorna info se o canvas IUP ja foi mapeado
*/
inline int itrCanvas::IsMapped()
{
 return mapped;
}


#endif
