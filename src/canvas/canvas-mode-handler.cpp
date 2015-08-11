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

#include "canvas-mode-handler.h"
#include "canvas-main.h"

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
cCanvasModeHandler::cCanvasModeHandler(VglManipViewSurface *manipviewsurface) : 
VglModeHandler(manipviewsurface),
  m_mode_handler_type(MODE_MANIP),
  m_mode_handler_type_backup(MODE_MANIP),
  m_is_main_canvas(false),
  m_process_pick(NULL)
{
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cCanvasModeHandler::set_canvas(cCanvas* canvas)
{
	m_canvas = canvas;
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
int cCanvasModeHandler::Keyboard(int k, int st, float x, float y) 
{
  if(st == VGL_RELEASE)
  {
    if(m_is_main_canvas && m_canvas->is_activate_navig() &&
      k != MODE_MANIP && k != MODE_NAVIG && 
      k != MODE_OVERLAY && k != MODE_ZOOM && k != MODE_DETAIL &&
      (k == 'a' || k == 's' || k == 'd' || k == 'w' || k == 'f' || k == 'r'))
      m_canvas->add_camera_view();

    if(k == MODE_MANIP)
    {
      if(m_mode_handler_type != MODE_MANIP)
      {
        if((m_mode_handler_type == MODE_OVERLAY && m_mode_handler_type_backup == MODE_NAVIG) ||
          m_mode_handler_type == MODE_NAVIG)
          m_canvas->fit();

        m_mode_handler_type = MODE_MANIP;
      }
    }

    else if(k == MODE_NAVIG)
    {
      if(m_mode_handler_type != MODE_NAVIG)
      {
        if((m_mode_handler_type == MODE_OVERLAY && m_mode_handler_type_backup == MODE_MANIP) ||
           m_mode_handler_type == MODE_MANIP)
          m_canvas->fit();

        m_mode_handler_type = MODE_NAVIG;
      }
    }

    else if(m_is_main_canvas && (k == MODE_ZOOM || k == MODE_DETAIL))
    {
      if(m_mode_handler_type != k)
      {
        IupSetAttribute(m_canvas->get_iup_canvas(), IUP_CURSOR, IUP_CROSS);
        m_mode_handler_type_backup = m_mode_handler_type;
        m_mode_handler_type = k;
      }
    }

    else if(k == MODE_OVERLAY)
    {
      if(m_is_main_canvas)
        ((cCanvasMain*)m_canvas)->overlay_subcanvas(true);
      else
      {
        m_mode_handler_type_backup = m_mode_handler_type;
        m_mode_handler_type = MODE_OVERLAY;
      }
    }
  }

	return VglModeHandler::Keyboard(k, st, x, y);
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
int cCanvasModeHandler::MouseButton(int k, int st, float x, float y)
{
  //if(GetDoubleClick())
  //        printf("double click - %d\n", g);

  if(m_is_main_canvas && 
     (k == VGL_BUTTON_LEFT) || (k == VGL_BUTTON_RIGHT) || (k == VGL_BUTTON_MIDDLE))
  {
    if(st == VGL_PRESS)
    {
      // store press coordinates to compare with release coordinates
      m_old_coord.x = x;
      m_old_coord.y = y;
    }
    else if(st == VGL_RELEASE)
    {
      // check if mouse has moved
      if(m_old_coord.x != x && m_old_coord.y != y) 
        m_canvas->add_camera_view();
    }
  }

  if((k == VGL_BUTTON_LEFT) && (st == VGL_RELEASE))
  {
    m_is_right_press = false;
    m_is_motion = false;
  }
  if(st == VGL_PRESS)
  {
    m_is_right_press = true;
    m_is_motion = false;
  }
  else 
  {
    if(m_is_right_press && !m_is_motion)
    {
      //ShowViewerLeafMenu();
      return 0;
    }

    m_is_right_press = false;
    m_is_motion = false;
  }

  if(m_process_pick)
    m_process_pick(m_canvas->get_camera(), GetDoubleClick(), GetCtrl(), k, st);

  return VglModeHandler::MouseButton(k, st, x, y);
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
int cCanvasModeHandler::MouseMotion(int k, float x, float y)
{
  if(m_is_right_press)
    m_is_motion = true;

  m_mouse_x = x;
  m_mouse_y = y;

  if(m_process_pick && k == 0)
    m_process_pick(m_canvas->get_camera(), false, -1, -1, -1);

  return VglModeHandler::MouseMotion(k, x, y);
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cCanvasModeHandler::restore_handler(void)
{
  m_mode_handler_type = m_mode_handler_type_backup;
  this->ChangeHandler(m_mode_handler_type);
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cCanvasModeHandler::active_manip(bool fit)
{
  if(m_mode_handler_type != MODE_MANIP)
  {
    m_mode_handler_type_backup = m_mode_handler_type;
    m_mode_handler_type = MODE_MANIP;

    if(fit)
      m_canvas->fit();

    this->ChangeHandler(m_mode_handler_type);
  }
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cCanvasModeHandler::active_navig(bool fit)
{
  bool b;
  if(m_mode_handler_type != MODE_NAVIG)
  {
    m_mode_handler_type_backup = m_mode_handler_type;
    m_mode_handler_type = MODE_NAVIG;

    if(fit)
      m_canvas->fit();

    b = this->ChangeHandler(m_mode_handler_type);
  }
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cCanvasModeHandler::active_zoom(void)
{
  if(m_is_main_canvas && m_mode_handler_type != MODE_ZOOM)
  {
    IupSetAttribute(m_canvas->get_iup_canvas(), IUP_CURSOR, IUP_CROSS);

    m_mode_handler_type_backup = m_mode_handler_type;
    m_mode_handler_type = MODE_ZOOM;

    this->ChangeHandler(m_mode_handler_type);
  }
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cCanvasModeHandler::active_detail(void)
{
  if(m_is_main_canvas && m_mode_handler_type != MODE_DETAIL)
  {
    IupSetAttribute(m_canvas->get_iup_canvas(), IUP_CURSOR, IUP_CROSS);
    m_mode_handler_type_backup = m_mode_handler_type;
    m_mode_handler_type = MODE_DETAIL;

    this->ChangeHandler(m_mode_handler_type);
  }
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cCanvasModeHandler::active_overlay(void)
{
  if(!m_is_main_canvas && // Only active to overlay the subcanvas
      m_mode_handler_type != MODE_OVERLAY)
  {
    m_mode_handler_type_backup = m_mode_handler_type;
    m_mode_handler_type = MODE_OVERLAY;

    this->ChangeHandler(m_mode_handler_type);
  }
}
