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

#include "canvas-main.h"
#include "canvas-attach.h"

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
cCanvasMain::cCanvasMain(std::string label, int w, int h) :
  cCanvas(),
  m_canvas(NULL),
  m_zoom_handler(NULL),
  m_detail_handler(NULL),
  m_menu_function_detail(NULL),
  m_redraw_function_detail(NULL),
  m_redraw_end_function_datail(NULL)
{
  m_vec_canvas_attach[0] = NULL;
  m_vec_canvas_attach[1] = NULL;
  m_vec_canvas_attach[2] = NULL;

  // set parameters of iup canvas
  cCanvas::m_canvas_handle = IupGLCanvas(label.c_str());
  IupSetHandle(label.c_str(), cCanvas::m_canvas_handle);
  IupStoreAttribute(cCanvas::m_canvas_handle, IUP_SCROLLBAR, IUP_NO);
  IupStoreAttribute(cCanvas::m_canvas_handle, IUP_DEPTH_SIZE, "16");
  IupStoreAttribute(cCanvas::m_canvas_handle, IUP_BUFFER, IUP_DOUBLE);
  IupStoreAttribute(cCanvas::m_canvas_handle, IUP_EXPAND, IUP_YES);
  IupStoreAttribute(cCanvas::m_canvas_handle, IUP_RESIZE, IUP_YES);
  IupStoreAttribute(cCanvas::m_canvas_handle, IUP_STENCIL_SIZE, "1");

  // TODO (lfmachado, 2012-05-02) Iup functions to control opengl version. Not work
  //IupStoreAttribute(cCanvas::m_canvas_handle, "ARBCONTEXT", IUP_YES);
  //IupStoreAttribute(cCanvas::m_canvas_handle, "CONTEXTVERSION", "3.3");
  //IupStoreAttribute(cCanvas::m_canvas_handle, "CONTEXTFLAGS", "DEBUG");
  //IupStoreAttribute(cCanvas::m_canvas_handle, "CONTEXTPROFILE", "CORE");//COMPATIBILITY"); //CORE

//#ifdef _WIN32
//  IupStoreAttribute(cCanvas::m_canvas_handle, IUP_STEREO, IUP_YES);
//#endif

  char size[20];
  sprintf(size, "%dx%d", w/2, h/2);
  IupStoreAttribute(cCanvas::m_canvas_handle, IUP_SIZE, size);
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
cCanvasMain::~cCanvasMain(void)
{
  if(m_zoom_handler)
    delete m_zoom_handler;
  m_zoom_handler = NULL;
  if(m_detail_handler)
    delete m_detail_handler;
  m_detail_handler = NULL;

  if(m_vec_canvas_attach[0])
    this->delete_canvas_attach(m_vec_canvas_attach[0]);
  m_vec_canvas_attach[0] = NULL;
  if(m_vec_canvas_attach[1])
    this->delete_canvas_attach(m_vec_canvas_attach[1]);
  m_vec_canvas_attach[1] = NULL;
  if(m_vec_canvas_attach[2])
    this->delete_canvas_attach(m_vec_canvas_attach[2]);
  m_vec_canvas_attach[2] = NULL;

  if(m_camera) delete m_camera;
  m_camera = NULL;
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cCanvasMain::set_vgl( VglFunction redraw_function, 
                           VglFunction redraw_end_function, 
                           VglFunction redraw_pick_function,
                           void (*process_pick)(VglCamera *camera, bool double_click, bool ctrl, int bt, int st),
                           void *data)
{
  m_is_canvas_main = true;

  // dimensoes iniciais do volume de visualizacao
  m_bbox.min.x = -1.0;
  m_bbox.max.x =  1.0;
  m_bbox.min.y = -1.0;
  m_bbox.max.y =  1.0;
  m_bbox.min.z = -1.0;
  m_bbox.max.z =  1.0;

  // set parameters of the camera
  m_camera = new VglCamera();
  m_camera->SetAutoFit(true);
  m_camera->SetBox((float) m_bbox.min.x, 
                    (float) m_bbox.max.x, 
                    (float) m_bbox.min.y, 
                    (float) m_bbox.max.y, 
                    (float) m_bbox.min.z, 
                    (float) m_bbox.max.z);
  m_camera->SetZPlanes(s_near, s_far);
  m_camera->SetAngle(s_fovy);
  m_camera->SetTarget(s_target.x, s_target.y, s_target.z);
  m_camera->SetDOP(s_dop.x, s_dop.y, s_dop.z);
  m_camera->SetUp(s_up.x, s_up.y, s_up.z);
  m_camera->SetHeadlight(GL_LIGHT0);
  m_camera->SetOrtho(false);

  m_canvas = new VglIupCanvas(cCanvas::m_canvas_handle, m_camera);

#ifdef _DEBUG
  if(!redraw_function)
    printf("Anflex-interface - %s, %d\nPointer to redraw function is NULL.", __FILE__, __LINE__);
#endif

  m_data_render = data;

  m_canvas->SetRedrawFunc(redraw_function, m_data_render);

  if(redraw_end_function) m_canvas->SetEndRedrawFunc(redraw_end_function, m_data_render);

  m_canvas->SetStereo(false);

  m_manip_handler  = new cCanvasManipHandler(m_canvas);  
  m_navig_handler  = new cCanvasNavigHandler(m_canvas, s_max_speed, s_accel);
  m_zoom_handler   = new cCanvasZoomHandler(m_canvas);
  m_detail_handler = new cCanvasDetailHandler(m_canvas, this, data);
  m_mode_handler   = new cCanvasModeHandler(m_canvas);

  m_manip_handler->set_canvas(this);
  m_navig_handler->set_canvas(this);
  m_zoom_handler->set_canvas(this);
  m_mode_handler->set_canvas(this);
  
  m_mode_handler->AddHandler(m_manip_handler, MODE_MANIP);
  m_mode_handler->AddHandler(m_navig_handler, MODE_NAVIG);
  m_mode_handler->AddHandler(m_zoom_handler, MODE_ZOOM);
  m_mode_handler->AddHandler(m_detail_handler, MODE_DETAIL);

  m_mode_handler->ChangeHandler(MODE_MANIP);

  m_mode_handler->set_main_canvas(true);

  m_mode_handler->set_func_process_pick(process_pick);

  m_canvas->AddHandler(m_mode_handler);

  activate();
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cCanvasMain::overlay_subcanvas(bool to_overlay)
{
  for(int i = 0; i < 3; i++)
  {
    if(m_vec_canvas_attach[i])
    {
      if(to_overlay)
      {
        // put all subcanvas in overlay mode
        m_vec_canvas_attach[i]->activate_overlay();
      }
      else
      {
        // restore all subcanvas
        m_vec_canvas_attach[i]->restore_handler();
      }
    }
  }
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
bool cCanvasMain::create_canvas_attach(VglCamera* vgl_camera)
{
  float y;
  int location;
  bool can_create = false;

  for(int i = 0; i < 3; i++)
  {
    if(m_vec_canvas_attach[i] == NULL)
    {
      location = i;
      y = 0.666f - (0.333f * i);
      can_create = true;
      break;
    }
  }

  if(can_create)
    m_vec_canvas_attach[location] = new cCanvasAttach(
        0.666f, y, 0.333f, 0.333f, 
        m_canvas, vgl_camera,
        m_redraw_function_detail, m_redraw_end_function_datail,
        m_menu_function_detail,
        m_data_render);

  return can_create;
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
bool cCanvasMain::create_canvas_attach(VglCamera* vgl_camera, unsigned int i)
{
  float y;
  if(i >= 4)
    return false;
  
  if(m_vec_canvas_attach[i - 1])
  {
    delete_canvas_attach(m_vec_canvas_attach[i - 1]);
    m_vec_canvas_attach[i - 1] = NULL;
  }
  
  y = 0.666f - (0.333f * (i-1));
  m_vec_canvas_attach[i - 1] = new cCanvasAttach(
      0.666f, y, 0.333f, 0.333f, 
      m_canvas, vgl_camera,
      m_menu_function_detail, m_redraw_end_function_datail,
      m_menu_function_detail,
      m_data_render);

  return true;
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cCanvasMain::delete_canvas_attach(cCanvasAttach *canvas)
{
  for (int i = 0; i < 3; i++)
  {
    if((m_vec_canvas_attach[i] != NULL) && 
       ((canvas == NULL) || 
       (m_vec_canvas_attach[i] == canvas)))
    {
      m_canvas->RemSubCanvas(m_vec_canvas_attach[i]->get_canvas_attach());
      delete m_vec_canvas_attach[i];
      m_vec_canvas_attach[i] = NULL;
    }
  }
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cCanvasMain::clear_canvas_attach(void *data) 
{
  VglSubCanvas *subcanvas = (VglSubCanvas*) data;
  subcanvas->Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cCanvasMain::clear_color_canvas_attach(void *data, float r, float g, float b, float a) 
{
  VglSubCanvas *canvas = (VglSubCanvas*) data;
  canvas->ClearColor(r, g, b, a);
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cCanvasMain::redraw_all_canvas_attach(void)
{
  for(int i = 0; i < 3; i++)
  {
    if(m_vec_canvas_attach[i] != NULL)
      m_vec_canvas_attach[i]->repaint();
  }
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
bool cCanvasMain::create_canvas_detach(VglCamera *camera)
{ 
  int zw = m_canvas->GetWidth() / 3;
  int zh = m_canvas->GetHeight() / 3;
  
  m_detail_handler->create_canvas_detach(zw, zh, camera);

  return true;
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cCanvasMain::set_navig_att(const sBox &bbox)
{ 
  float aux = 0.0f;
  aux = std::max(aux, fabs(bbox.max.x - bbox.min.x));
  aux = std::max(aux, fabs(bbox.max.y - bbox.min.y));
  aux = std::max(aux, fabs(bbox.max.z - bbox.min.z));

  m_navig_handler->SetMaxSpeed((float)aux / 3); 
  m_navig_handler->SetAcceleration(aux); 
}


// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cCanvasMain::setStereo(bool b)
{
  if(m_canvas)
    m_canvas->SetStereo(b);
  return;
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
bool cCanvasMain::isStereoSupported(void)
{
  if(m_canvas)
    return m_canvas->IsStereoSupported();
  return false;
}