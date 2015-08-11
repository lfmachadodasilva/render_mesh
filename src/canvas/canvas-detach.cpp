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

#include <iup.h>
#include <iupgl.h>
#include <stdlib.h>
#include <algorithm>

#include "canvas-detach.h"

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
cCanvasDetach::cCanvasDetach(Ihandle *iup_canvas,
                             VglCanvas* parent_canvas,
                             VglCamera* camera,
                             VglFunction redraw_function,
                             VglFunction redraw_end_function,
                             void(*menu_poupup_function)(void*),
                             void *data)
{
  float xmin, xmax, ymin, ymax, zmin, zmax;

  // get boox
  parent_canvas->GetCamera()->GetBox(&xmin, &xmax, &ymin, &ymax, &zmin, &zmax);
  m_bbox.min.x = std::min(m_bbox.min.x, xmin);
  m_bbox.max.x = std::max(m_bbox.max.x, xmax);
  m_bbox.min.y = std::min(m_bbox.min.y, ymin);
  m_bbox.max.y = std::max(m_bbox.max.y, ymax);
  m_bbox.min.z = std::min(m_bbox.min.z, zmin);
  m_bbox.max.z = std::max(m_bbox.max.z, zmax);

  // calc velocity
  float vel = 0.0f;
  vel = std::max(vel, fabs(m_bbox.max.x - m_bbox.min.x));
  vel = std::max(vel, fabs(m_bbox.max.y - m_bbox.min.y));
  vel = std::max(vel, fabs(m_bbox.max.z - m_bbox.min.z));

  m_camera = camera;
  m_camera->SetAutoFit(true);

  m_canvas_detach = new VglIupCanvas(iup_canvas, m_camera);
  m_canvas_detach->SetRedrawFunc(redraw_function, m_camera);
  if(redraw_end_function)
    m_canvas_detach->SetEndRedrawFunc(redraw_end_function, m_canvas_detach);

  m_mode_handler  = new cCanvasModeHandler(m_canvas_detach);
  m_manip_handler = new cCanvasManipHandler(m_canvas_detach, false);
  m_navig_handler = new cCanvasNavigHandler(m_canvas_detach, vel / 3, vel, false);

  m_mode_handler->set_canvas(this);
  m_manip_handler->set_canvas(this);
  m_navig_handler->set_canvas(this);

  m_manip_handler->set_menu_popup_function(menu_poupup_function);
  m_navig_handler->set_menu_popup_function(menu_poupup_function);

  m_mode_handler->AddHandler(m_manip_handler, MODE_MANIP);
  m_mode_handler->AddHandler(m_navig_handler, MODE_NAVIG);
  m_mode_handler->ChangeHandler(MODE_MANIP);

  m_canvas_detach->AddHandler(m_mode_handler);
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cCanvasDetach::zoom(float factor, float x, float y)
{
  m_canvas_detach->GetCamera()->Zoom(factor, x, y);
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cCanvasDetach::add_idle(VglFunction idleFunction, void* idleData, int idleRepeat)
{
  m_canvas_detach->AddIdle(idleFunction, idleData, idleRepeat);
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cCanvasDetach::rem_idle(VglFunction idleFunction, void* idleData)
{
  m_canvas_detach->RemIdle(idleFunction, idleData);
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
VglCamera* cCanvasDetach::get_copy_camera(void)
{
  VglCamera* camera = new VglCamera(m_camera);
  return camera;
}
