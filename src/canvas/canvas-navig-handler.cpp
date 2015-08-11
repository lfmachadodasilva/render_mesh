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

#include "canvas.h"
#include "canvas-navig-handler.h"

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
cCanvasNavigHandler::cCanvasNavigHandler( VglViewSurface *surface, 
                                          double maxspeed, 
                                          double accel, 
                                          bool is_main_canvas) : 
                                          VglNavigHandler(surface, (float) maxspeed, (float) accel),
                                          m_canvas(NULL),
                                          poupup_menu_function(NULL)
{
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cCanvasNavigHandler::set_menu_popup_function(void(*func)(void*))
{
	poupup_menu_function = func;
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cCanvasNavigHandler::set_canvas(cCanvas* canvas)
{
	m_canvas = canvas;
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
int cCanvasNavigHandler::MouseButton(int bt, int st, float x, float y)
{
  if(st == VGL_RELEASE && bt == VGL_BUTTON_LEFT)
  {
    if (y > 0.90 && x > 0.92)
    {
      if (poupup_menu_function != NULL)
        poupup_menu_function((void*)m_canvas);

      // (lfmachado, 2011-12-06) need to return 0 to ignore when navig callback
      return 0;
    }
  }

  return VglNavigHandler::MouseButton(bt, st, x, y);
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
int cCanvasNavigHandler::MouseMotion(int bt, float x, float y)
{
  return VglNavigHandler::MouseMotion(bt, x, y);
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
int cCanvasNavigHandler::Keyboard(int k, int st, float x, float y) 
{
	return VglNavigHandler::Keyboard(k, st, x, y);
}
