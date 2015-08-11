/*
%M ircanvas.h - Abstracao de Canvas do IUP, usando sistema de coordenadas 
                inteiras em pixels do canvas os canvas.
%a Newton Sanches (Baseado em Juli Huang, MMC, Neil e Lula)
%d 03/05/96
%p Interact 
*/

#ifndef __ITR_RASTER_CANVAS__
#define __ITR_RASTER_CANVAS__

#include "interactapi.h"
#include "icanvas.h"

/*
%C Extenaso de itrCanvas.
   Abstracao de um canvas no qual as coordenas estao todas em coordenadas
   da tela
%x - Nao sao ofereciadas funcoes de World e Window
   - O ScrollBar e' ignorado
   - A consulta GetEventPos(double*,double*) retorna o (x,y) do pixel do evento
     convertido para double.  Essa funcao existe para manter compatibilidade com
     as Tasks
*/
class INTERACT_API itrRasterCanvas:public itrCanvas {
private:
    int realheight, realwidth;     // tamanho do canvas
    int pos_x, pos_y;              // posicao do evento de mouse
    double ua_xmin, ua_xmax,
           ua_ymin, ua_ymax;       // Area util do canvas

    // Funcoes para adapatacao ao sistema de coordenadas
    virtual void _MoveWindow       (double, double);
    virtual void _ResizeWindow     (int, int);
    virtual void _PrepareCoords    (int, int, int/*dosnap*/);
    virtual void _PrepareToRepaint ();
    virtual void _PrepareToRepaint (int xmin,int ymin,int xmax,int ymax);

    virtual void OnMap             ();
  
public:  
    itrRasterCanvas(Ihandle* h, cdCanvas* cc);
    virtual ~itrRasterCanvas(){};
              
    virtual void Snap		   (int*, int*){}
    virtual void GetEventPos       (int*, int*);
    virtual void GetEventPos       (double*, double*);
    virtual void GetEventUnsnapPos (int*, int*);
    virtual void GetEventUnsnapPos (double*, double*);
    virtual void Raster2World     (int, int, double*, double*);
    virtual void World2Raster     (double, double, int*, int*);
 
    void SetUsedArea              (double, double, double, double);   
    void GetUsedArea              (double*, double*, double*, double*);
    void GetUsedSize              (int*, int*);
    void GetCanvasSize            (int*, int*);
};

#endif
