// ------------------------------------------------------------------------------------------------- 
// Anflex Project -- Tecgraf/PUC-Rio  CENPES/Petrobras 
// www.tecgraf.puc-rio.br 
// 
// Created by lfmachado in April/2011.
// 
// $URL: $ 
// $Revision: $ 
// $Date: $ 
// 
// $LastChangedBy: $ 
// -------------------------------------------------------------------------------------------------

#include "iup.h"

#include "canvas-zoom-handler.h"
#include "canvas.h"

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
cCanvasZoomHandler::cCanvasZoomHandler (VglViewSurface* surface) : VglZoomHandler(surface){
   m_canvas = (cCanvas*)surface;   
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
cCanvasZoomHandler::~cCanvasZoomHandler () {}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cCanvasZoomHandler::set_canvas(cCanvas* canvas)
{
	m_canvas = canvas;
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
int cCanvasZoomHandler::MouseButton (int bt, int st, float x, float y) 
{
  if (bt == VGL_BUTTON_LEFT) 
  {
    if (st == VGL_PRESS) 
    { 
      VglZoomHandler::MouseButton(bt, st, x, y);
      return 0; // filtrando os eventos ate o release do botao
    }
    else if (st == VGL_RELEASE) 
    { 
      IupSetAttribute(m_canvas->get_iup_canvas(), IUP_CURSOR, IUP_ARROW);
      int ret = VglZoomHandler::MouseButton(bt, st, x, y);
      m_canvas->restore_handler();
      return ret;
    }
  }

  return VglZoomHandler::MouseButton(bt, st, x, y);
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
int cCanvasZoomHandler::MouseMotion (int bt, float x, float y) 
{
  if(bt == VGL_BUTTON_LEFT) 
  {
    VglZoomHandler::MouseMotion(bt, x, y);
    return 0;
  }

  return VglZoomHandler::MouseMotion(bt, x, y);
}