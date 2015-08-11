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

#include "GL\glew.h"
#include "GL\wglew.h"

#include "canvas-detail-handler.h"
#include "canvas-detach.h"
#include "canvas-main.h"

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
cCanvasDetailHandler::cCanvasDetailHandler (VglViewSurface *surface, 
                                            cCanvasMain *canvas_main,
                                            void *data) : 
  VglZoomHandler(surface),
  m_canvas((VglCanvas*) surface),
  m_camera(m_canvas->GetCamera()),
  m_canvas_main(canvas_main),
  m_data(data),
  m_idle_function(NULL),
  m_redraw_function(NULL),
  m_redraw_end_function(NULL),
  m_menu_popup_function(NULL)
{
  m_icon.clear();
  m_title.clear();
  m_parent.clear();
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
cCanvasDetailHandler::~cCanvasDetailHandler ()
{
  this->close_detail_windows();
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cCanvasDetailHandler::create_canvas_detach(int w, int h, VglCamera* camera)
{
  cCanvasDetach *canvas;
  Ihandle *h_canvas, *dialog;
  
  h_canvas = IupGLCanvas("canvas_main");
  dialog = IupDialog(h_canvas);
  IupSetfAttribute(h_canvas, IUP_RASTERSIZE, "%dx%d", w, h);
  IupSetAttribute(h_canvas, "SHAREDCONTEXT", "canvas_main");
  
  IupSetAttribute(h_canvas, IUP_BUFFER, IUP_DOUBLE);
  IupSetAttribute(h_canvas, IUP_BORDER, IUP_NO);
  IupSetAttribute(h_canvas, IUP_DEPTH_SIZE, "16");

  if(!m_title.empty())
    IupSetAttribute(dialog, IUP_TITLE, m_title.c_str());

  if(!m_icon.empty())
    IupSetAttribute(dialog, IUP_ICON, m_icon.c_str());

  if(!m_parent.empty())
    IupSetAttribute(dialog, IUP_PARENTDIALOG, m_parent.c_str());

  IupMap(dialog);

  canvas = new cCanvasDetach(
      h_canvas, 
      m_canvas, 
      camera, 
      m_redraw_function, 
      m_redraw_end_function, 
      m_menu_popup_function, 
      (void *)m_data);

  if(isAnimating && m_idle_function)
    canvas->add_idle(m_idle_function, m_idle_data, m_idle_repeat);

  canvas->set_dialog(dialog);

  m_vec_canvas_detach.push_back(canvas);
  m_vec_dialog.push_back(dialog);

  //GetDC();
  //
  //wglCreateContextAttribsARB
  //wglCreateContext();
  //wglShareLists();
  
  IupShowXY(dialog, IUP_CENTERPARENT, IUP_CENTERPARENT);
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cCanvasDetailHandler::Zoom(float dx, float dy, float x, float y)
{   
  float factor = 1.0f/(dx>dy?dx:dy);    
  VglCamera* camera_copy = new VglCamera(m_canvas->GetCamera());
  camera_copy->Zoom(factor, x, y);

  IupSetAttribute(m_canvas_main->get_iup_canvas(), IUP_CURSOR, IUP_ARROW);
  m_canvas_main->restore_handler();

  // try to attach. if has no space, create a detach canvas
  if(m_canvas_main->create_canvas_attach(camera_copy)) 
    return;

  int zw = m_canvas->GetWidth() / 3;
  int zh = m_canvas->GetHeight() / 3;

  create_canvas_detach(zw, zh, camera_copy);
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cCanvasDetailHandler::redraw_detail_windows(void)
{
  for(int i = 0; i < (int) m_vec_canvas_detach.size(); i++)
    m_vec_canvas_detach[i]->postRedraw();
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cCanvasDetailHandler::set_detail_window_idle(VglFunction func, void* data, int repeat)
{
  assert(m_idle_function == NULL);

  m_idle_function = func;
  m_idle_data = data;
  m_idle_repeat = repeat;
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cCanvasDetailHandler::close_detail_windows(void)
{
  for(int i = 0; i < (int) m_vec_dialog.size(); i++)
    IupHide(m_vec_dialog[i]);
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cCanvasDetailHandler::set_detail_window_animation(bool is_animating)
{
  isAnimating = is_animating;
  if(m_idle_function)
  {
    if(isAnimating)
    {
      for(int i = 0; i < (int) m_vec_canvas_detach.size(); i++)
        m_vec_canvas_detach[i]->add_idle(m_idle_function, m_idle_data, m_idle_repeat);
    }
    else
    {
      for(int i = 0; i < (int) m_vec_canvas_detach.size(); i++)
        m_vec_canvas_detach[i]->rem_idle(m_idle_function, m_idle_data);
    }
  }
}
