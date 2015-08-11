/*
%M iwcanvas.h - Abstracao de Canvas do IUP, usando sistema de coordenadas 
                do mundo.
%a Newton Sanches (Baseado em Juli Huang, MMC, Neil e Lula)
%d 03/05/96
%p Interact 
*/

#ifndef __ITR_WORLD_CANVAS__
#define __ITR_WORLD_CANVAS__

#include "interactapi.h"
#include "icanvas.h"

/*
%T Retangulo
*/
struct INTERACT_API itrArea
{
    double xmin,
           ymin,
           xmax,
           ymax;
};

/*
%K Comportamento num resize 
*/
typedef enum
{
   ITR_SCALE,
   ITR_KEEPORIGIN_UL,
   ITR_KEEPORIGIN_UR,
   ITR_KEEPORIGIN_LL,
   ITR_KEEPORIGIN_LR,
   ITR_KEEPORIGIN_CENTER
} itrResizeBehaviour;

/*
%C Exetensao de itrCanvas.
   Abstracao de um canvas no qual usa-se coordenadas do mundo
*/
class INTERACT_API itrWorldCanvas:public itrCanvas
{
private:

    int keepaspect;                // flag p/ manter a relacao de aspecto
    itrResizeBehaviour resizebehaviour; // flag p/ saber o que saber no resize
    int realheight, realwidth;             // Tamanho da janela (pixels)
    int pos_x, pos_y;              // posicao do evento de mouse (pixels)
    double wpos_x, wpos_y;         // posicao do evento de mouse (world coord.)
    itrArea world;                 // limites do mundo
    itrArea model;                 // limites 
    itrArea window;                
    itrArea bound;
    double factor_x, factor_y;
   
    double ua_xmin, ua_xmax, ua_ymin, ua_ymax;

    // uso interno
    void _SetWindow                (double, double, double, double);
    void FixRatio                  ();

    // Funcoes para adapatacao ao sistema de coordenadas
    virtual void ResizeScale       (int , int);
    virtual void ResizeKeepOrigin  (int , int, double, double);
    virtual void _MoveWindow       (double, double);
    virtual void _ResizeWindow     (int, int);
    virtual void _PrepareCoords    (int, int, int/*dosnap*/);
    virtual void _PrepareToRepaint ();
    virtual void _PrepareToRepaint (int xmin, int ymin, int xmax, int ymax);

    char sxmin[30], sxmax[30],
         symin[30], symax[30], 
         sdx  [30], sdy  [30],
         sposx[30], sposy[30];

    virtual void OnMap              ();
  
public:  
    itrWorldCanvas(Ihandle*, cdCanvas*);
    virtual ~itrWorldCanvas(){};
              
    virtual void Snap		   (double*, double*){}
    virtual void GetEventPos       (int*, int*);
    virtual void GetEventPos       (double*, double*);
    virtual void GetEventUnsnapPos (int*, int*);
    virtual void GetEventUnsnapPos (double*, double*);
    virtual void Raster2World      (int, int, double*, double*);
    virtual void World2Raster      (double, double, int*, int*);  
 
    void GetCanvasSize             (int*, int*);

    virtual void PaintWindowToCanvas(cdCanvas* altcnv, int, int, int, int,
                                               double, double, double, double);

    void SetWorld                  (double, double, double, double);
    void SetWindow                 (double, double, double, double);
    void SetLimits                 (double, double, double, double);
    void Fit                       ();
    void SetUsedArea               (double, double, double, double);
    void GetUsedArea               (double*, double*, double*, double*);

    void GetWorld                  (double*, double*, double*, double*);
    void GetWindow                 (double*, double*, double*, double*);
    void GetLimits                 (double*, double*, double*, double*);

    int  SetKeepAspect             (int);
    void SetResizeBehaviour        (itrResizeBehaviour bh);
    void Zoom                      (double, double, double);
    void Zoom                      (double);
    void UpdateScrollBar           ();
};

#endif
