// -------------------------------------------------------------------------------------------------
// Anflex Project -- Tecgraf/PUC-Rio
// www.tecgraf.puc-rio.br
//
// $HeadURL: https://subversion.tecgraf.puc-rio.br/svn/anflex-interface/trunk/src/subcanvas.cpp $
// $Revision: 910 $
// $Date: 2011-10-27 16:07:55 -0200 (qui, 27 out 2011) $
//
// $Author: lfmachado $
// -------------------------------------------------------------------------------------------------

#include <vgl/vgliup.h>
#include <vgl/cnv/iupcanvas.h>
#include <vgllib/vgllibiup.h>

#include "canvas-attach.h"
#include "canvas-manip-handler.h"
#include "canvas-navig-handler.h"

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
cCanvasAttach::cCanvasAttach(float x, float y, float w, float h,
                             VglCanvas* vglParentCanvas,
                             VglCamera* srcVglCamera,
                             VglFunction redrawFunction,
                             VglFunction redrawEndFunction,
                             void(*menuPoupupFunction)(void*),
                             void *data)
{
  float xmin, xmax, ymin, ymax, zmin, zmax;

  // Get bbox
  vglParentCanvas->GetCamera()->GetBox(&xmin, &xmax, &ymin, &ymax, &zmin, &zmax);
  m_bbox.min.x = std::min(m_bbox.min.x, xmin);
  m_bbox.max.x = std::max(m_bbox.max.x, xmax);
  m_bbox.min.y = std::min(m_bbox.min.y, ymin);
  m_bbox.max.y = std::max(m_bbox.max.y, ymax);
  m_bbox.min.z = std::min(m_bbox.min.z, zmin);
  m_bbox.max.z = std::max(m_bbox.max.z, zmax);

  // calc velocity to use on navigation
  float vel = 0.0f;
  vel = std::max(vel, fabs(m_bbox.max.x - m_bbox.min.x));
  vel = std::max(vel, fabs(m_bbox.max.y - m_bbox.min.y));
  vel = std::max(vel, fabs(m_bbox.max.z - m_bbox.min.z));

  m_camera = srcVglCamera;
  m_camera->SetAutoFit(true);

  m_canvas_attach = new VglSubCanvas(srcVglCamera, vglParentCanvas);
  m_canvas_attach->SetWindow(x, y, w, h);
  m_canvas_attach->SetRedrawFunc(redrawFunction, m_canvas_attach);

  if(redrawEndFunction)
    m_canvas_attach->SetEndRedrawFunc(redrawEndFunction, m_canvas_attach);

  m_mode_handler    = new cCanvasModeHandler((VglSubCanvas*)m_canvas_attach);
  m_overlay_handler = new VglIupOverLayHandler(m_canvas_attach);
  m_manip_handler   = new cCanvasManipHandler(m_canvas_attach, false);
  m_navig_handler   = new cCanvasNavigHandler(m_canvas_attach, vel / 3, vel, false);

  m_mode_handler->set_canvas(this);
  m_manip_handler->set_canvas(this);
  m_navig_handler->set_canvas(this);

  m_manip_handler->set_menu_popup_function(menuPoupupFunction);
  m_navig_handler->set_menu_popup_function(menuPoupupFunction);

  m_mode_handler->AddHandler(m_manip_handler, MODE_MANIP);
  m_mode_handler->AddHandler(m_navig_handler, MODE_NAVIG);
  m_mode_handler->AddHandler(m_overlay_handler, MODE_OVERLAY);
  m_mode_handler->ChangeHandler(MODE_MANIP);

  m_canvas_attach->AddHandler(m_mode_handler);
 
  vglParentCanvas->AddSubCanvas(m_canvas_attach);

  postRedraw();
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
VglSubCanvas* cCanvasAttach::get_canvas_attach(void)
{
  return m_canvas_attach;
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
VglCamera* cCanvasAttach::get_camera(void)
{
  return m_camera;
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
VglCamera* cCanvasAttach::get_copy_camera(void)
{
  VglCamera* camera = new VglCamera(m_camera);
  return camera;
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cCanvasAttach::activate(void)
{
  this->activate();
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cCanvasAttach::postRedraw(void)
{
  m_canvas_attach->PostRedraw();
}
