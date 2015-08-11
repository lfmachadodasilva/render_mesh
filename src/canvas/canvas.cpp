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
#include "canvas.h"

static const double ISODOP = 1.0/sqrt(3.0);
static const double ISOVUP = 1.0/sqrt(6.0);

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
cCanvas::cCanvas() :
m_canvas_handle(NULL),
m_is_canvas_main(false),
m_camera(NULL),
m_mode_handler(NULL),
m_manip_handler(NULL)
{
  this->reset_camera_view();
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
cCanvas::~cCanvas()
{
  if(m_camera)
    delete m_camera;

  this->reset_camera_view();
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
bool cCanvas::add_camera_view(void)
{
  if(!m_camera) return false;
  
  int size = (int)m_vet_camera.size();
  
  if(size == 0) // first
    this->reset_camera_view(); // Used to initialize the structure
  
  ++m_current_camera;
  
  // check if has maximum size
  if(m_current_camera == 50)
  {
    // stay in the last positon of the vector
    m_current_camera--;
    // remove first positon of the vector
    m_vet_camera.erase(m_vet_camera.begin());
    m_vet_camera_handle.erase(m_vet_camera_handle.begin());
  }
  
  if(m_current_camera < size)
  {
    // has changed in the middle of vector. Delete forward position and resize vector
    for(int i = m_current_camera + 1; i < size; i++)
    {
      delete m_vet_camera[i];
      m_vet_camera[i] = NULL;
    }
    m_vet_camera.resize(m_current_camera);
    m_vet_camera_handle.resize(m_current_camera);
  }
  
  m_vet_camera.push_back(new VglCamera(m_camera));
  if(this->is_activate_manip())
    m_vet_camera_handle.push_back(MODE_MANIP);
  else
    m_vet_camera_handle.push_back(MODE_NAVIG);

  return true;
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
bool cCanvas::undo_camera_view(void)
{
  if(m_current_camera - 1 >= 0)
  {
    m_current_camera--;

    // get cameras
    VglCamera *cam_to = m_camera;
    VglCamera *cam_from = m_vet_camera[m_current_camera];

    // setting the current window aspect and ortho
    const bool ortho = cam_to->GetOrtho();
    const float aspect = cam_to->GetAspect();
    cam_to->SetCamera(cam_from);
    cam_to->SetAspect(aspect);
    cam_to->SetOrtho(ortho);

    // restore used handler
    if(this->is_activate_manip() && m_vet_camera_handle[m_current_camera] == MODE_NAVIG)
      this->activate_navig(false); // not necessary fit view
    else if(this->is_activate_navig() && m_vet_camera_handle[m_current_camera] == MODE_MANIP)
      this->activate_manip(false); // not necessary fit view

    pan();

    this->repaint();

    return true;
  }

  return false;
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
bool cCanvas::redo_camera_view(void)
{
  int size = (int)m_vet_camera.size();
  if(m_current_camera + 1 < size)
  {
    m_current_camera++;

    // get cameras
    VglCamera *cam_to = m_camera;
    VglCamera *cam_from = m_vet_camera[m_current_camera];

    // setting the current window aspect and ortho
    const bool ortho = cam_to->GetOrtho();
    const float aspect = cam_to->GetAspect();
    cam_to->SetCamera(cam_from);
    cam_to->SetAspect(aspect);
    cam_to->SetOrtho(ortho);

    // restore used handler
    if(this->is_activate_manip() && m_vet_camera_handle[m_current_camera] == MODE_NAVIG)
      this->activate_navig(false); // not necessary fit view
    else if(this->is_activate_navig() && m_vet_camera_handle[m_current_camera] == MODE_MANIP)
      this->activate_manip(false); // not necessary fit view

    pan();

    this->repaint();

    return true;
  }

  return false;
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cCanvas::reset_camera_view(void)
{
  // free vector of cameras
  for(int i = 0; i < (int)m_vet_camera.size(); i++)
  {
    if(m_vet_camera[i])
      delete m_vet_camera[i];
  }
  m_vet_camera.clear();
  m_vet_camera_handle.clear();

  // initialize the camera index
  m_current_camera = -1;
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cCanvas::zoom_in(double factor)
{
  m_camera->Zoom((float)factor);

  postRedraw();

  if(m_is_canvas_main)
    add_camera_view();
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cCanvas::zoom_out(double factor)
{
  m_camera->Zoom((float) (1.0 / factor));

  postRedraw();

  if(m_is_canvas_main)
    add_camera_view();
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cCanvas::fit(void)
{
  float xmin = (float) m_bbox.min.x;
  float xmax = (float) m_bbox.max.x;
  float ymin = (float) m_bbox.min.y;
  float ymax = (float) m_bbox.max.y;
  float zmin = (float) m_bbox.min.z;
  float zmax = (float) m_bbox.max.z;
  //activate();   
  m_camera->SetBox(xmin, xmax, ymin, ymax, zmin, zmax);
	m_camera->SetAngle(60.0);
  m_camera->FitView();

  // work around (gambiarra) to recalculate the rotation axes after the model fit
  this->pan();

  postRedraw();

  if(m_is_canvas_main)
    add_camera_view();
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cCanvas::pan(void)
{
  // work around (gambiarra) to recalculate the rotation axes
  if(this->is_activate_manip())
    m_manip_handler->MouseButton(VGL_BUTTON_MIDDLE, VGL_RELEASE, 0.5, 0.5);
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cCanvas::projection(int type)
{
  float xmin = (float) m_bbox.min.x;
  float xmax = (float) m_bbox.max.x;
  float ymin = (float) m_bbox.min.y;
  float ymax = (float) m_bbox.max.y;
  float zmin = (float) m_bbox.min.z;
  float zmax = (float) m_bbox.max.z;

  m_camera->SetAutoFit(true);
  //activate();
  m_camera->Reset();

  m_camera->SetBox(xmin, xmax, ymin, ymax, zmin, zmax);
	m_camera->SetAngle(60.0);
  switch(type)
  {
  case PLANE_XY:
    m_camera->SetDOP(0.0, 0.0, -1.0);
    m_camera->SetUp(0.0, 1.0, 0.0);
    break;
  case PLANE_MINUS_XY:
    m_camera->SetDOP(0.0, 0.0, 1.0);
    m_camera->SetUp(0.0, 1.0, 0.0);
    break;
  case PLANE_XZ:
    m_camera->SetDOP(0.0, -1.0, 0.0);
    m_camera->SetUp(0.0, 0.0, 1.0);
    break;
  case PLANE_MINUS_XZ:
    m_camera->SetDOP(0.0, 1.0, 0.0);
    m_camera->SetUp(0.0, 0.0, 1.0);
    break;
  case PLANE_YZ:
    m_camera->SetDOP(-1.0, 0.0, 0.0);
    m_camera->SetUp(0.0, 0.0, 1.0);
    break;
  case PLANE_MINUS_YZ:
    m_camera->SetDOP(1.0, 0.0, 0.0);
    m_camera->SetUp(0.0, 0.0, 1.0);
    break;
  case ISOMETRIC:
    m_camera->SetDOP( (float) -ISODOP, 
                          (float) -ISODOP, 
                          (float) -ISODOP);
    m_camera->SetUp((float) -ISOVUP, 
                        (float) -ISOVUP, 
                        (float) ISOVUP);
    break;
  }
  postRedraw();

  if(m_is_canvas_main)
    add_camera_view();
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cCanvas::orthographic(bool mode)
{
  m_camera->SetBox( (float) m_bbox.min.x, 
                        (float) m_bbox.max.x, 
                        (float) m_bbox.min.y, 
                        (float) m_bbox.max.y, 
                        (float) m_bbox.min.z, 
                        (float) m_bbox.max.z);
	m_camera->SetAngle(60.0);
  m_camera->SetAutoFit(true);

  //activate();
  m_camera->SetOrtho(mode);

  postRedraw();

  if(m_is_canvas_main)
    add_camera_view();
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cCanvas::set_bounding_box(const sBox &bbox)
{
  m_bbox.min.x = bbox.min.x;
  m_bbox.max.x = bbox.max.x;
  m_bbox.min.y = bbox.min.y;
  m_bbox.max.y = bbox.max.y;
  m_bbox.min.z = bbox.min.z;
  m_bbox.max.z = bbox.max.z;
  m_camera->SetBox( (float) m_bbox.min.x, 
                        (float) m_bbox.max.x, 
                        (float) m_bbox.min.y, 
                        (float) m_bbox.max.y, 
                        (float) m_bbox.min.z, 
                        (float) m_bbox.max.z);
  m_camera->SetViewVolume((float) m_bbox.min.x, 
                              (float) m_bbox.max.x, 
                              (float) m_bbox.min.y, 
                              (float) m_bbox.max.y, 
                              (float) m_bbox.min.z, 
                              (float) m_bbox.max.z);
}