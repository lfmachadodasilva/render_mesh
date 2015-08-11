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

#include "canvas-main.h"
#include "canvas-manip-handler.h"

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
cCanvasManipHandler::cCanvasManipHandler (VglViewSurface *surface, bool is_main_canvas) : 
    VglManipHandler(surface),
    m_canvas(NULL),
    poupup_menu_function(NULL)
{
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cCanvasManipHandler::set_menu_popup_function(void(*func)(void*))
{
	poupup_menu_function = func;
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cCanvasManipHandler::set_canvas(cCanvas* canvas)
{
	m_canvas = canvas;
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
int cCanvasManipHandler::MouseButton(int bt, int st, float x, float y)
{ 
  if(st == VGL_RELEASE && bt == VGL_BUTTON_LEFT)
  {
    if(y > 0.90 && x > 0.92)
    {
      if(poupup_menu_function != NULL)
        poupup_menu_function((void*)m_canvas);

      // (lfmachado, 2011-12-06) need to return 0 to ignore when manip callback
      return 0;
    }
  }

  return VglManipHandler::MouseButton(bt, st, x, y);
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
int cCanvasManipHandler::MouseMotion(int bt, float x, float y)
{
  return VglManipHandler::MouseMotion(bt, x, y);
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
int cCanvasManipHandler::MouseWheel (float delta, float x, float y)
{
  if(m_canvas && !this->IsMoving())
	{
		float factor = 1.0f + 0.05f * fabs(delta);
		if(delta > 0)
			m_canvas->zoom_in(factor);
		else
			m_canvas->zoom_out(factor);
	}
	return 1;
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
int cCanvasManipHandler::Keyboard (int k, int st, float x, float y) 
{
  VglCamera *camera = NULL;

  if(st == VGL_RELEASE && !this->IsMoving())
  {
    switch(k)
    {
    case 'z':
      m_canvas->projection(cCanvas::PLANE_XY);
      break;
    case 'Z':
      m_canvas->projection(cCanvas::PLANE_MINUS_XY);
      break;
    case 'x':
      m_canvas->projection(cCanvas::PLANE_YZ);
      break;
    case 'X':
      m_canvas->projection(cCanvas::PLANE_MINUS_YZ);
      break;
    case 'y':
      m_canvas->projection(cCanvas::PLANE_XZ);
      break;
    case 'Y':
      m_canvas->projection(cCanvas::PLANE_MINUS_XZ);
      break;
    case 'i': case 'I':
      m_canvas->zoom_in();
      break;
    case 'o': case 'O':
      m_canvas->zoom_out();
      break;
    case 'u': case 'U':
      camera = m_canvas->get_camera();
      camera->UndoZoom();
      m_canvas->repaint();
      break;
    case 'r': case 'R':
      camera = m_canvas->get_camera();
      camera->RedoZoom();
      m_canvas->repaint();
      break;
    case 'f': case 'F':
      m_canvas->reset_bounding_box_to_original();
      m_canvas->fit();
      break;
    case 'p': case 'P':
      m_canvas->orthographic(!m_canvas->orthographic());
      break;
    }
  }

  return VglManipHandler::Keyboard(k, st, x, y);
}
