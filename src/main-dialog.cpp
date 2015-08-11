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

#define _ANFLEX_

// vrbv
#include "vrbv\node.h"
#include "vrbv\boxfactory.h"
#include "vrbv\scenedata.h"
#include "vrbv\treebuilder.h"

// Libvis library
#include "canvas\canvas-attach.h"
#include "canvas\canvas-detach.h"

#include "render\render-quad-att.h"
#include "render\render-callback.h"
#include "render\pick.h"
// End of LibVis library

#include "GL/wglew.h" // used for SetSwapInterval

// Iup library
#include <iup.h>
// End of Iup library

// Project includes
#include "obj-dialog.h"
#include "gauge.h"
#include "object.h"
#include "object-quad.h"
#include "model.h"
#include "main-dialog.h"
#include "anfvar.h"
// End of project includes

// extern from render_functions
extern void render(void *data);
extern void render_end(void *data);
extern void render_idle(void *data);
extern void render_frame(void *data);
extern void subcanvas_redraw(void *data);
extern void subcanvas_end_redraw(void *data);
extern void detail_redraw(void *data);
extern void process_pick(VglCamera *camera, bool double_click, bool ctrl, int bt, int st);
// end of extern from render_functions

static string s_filename;

static cCanvasAttach *s_current_subcanvas = NULL;
static cCanvasDetach *s_current_detail = NULL;

static cObjDialog *obj_dialog;

static void SetSwapInterval(int i);

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
cMainDialog::cMainDialog(void)
{
  m_dg = NULL;
  g_canvas_main = NULL;
  s_current_subcanvas = NULL;

  if(!m_dg)
	{
	  m_dg = create_dialog();
  
		set_callbacks();
  
		IupMap(m_dg);
  
		init_dialog();
	}
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
cMainDialog::~cMainDialog(void)
{
  delete g_canvas_main;
  delete s_current_subcanvas;

  g_model->clear();
  delete g_model;

  delete g_accel_render;
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cMainDialog::show_dialog(void)
{
  cPick::m_pick_type = cPick::PICK_BY_OBJECT;

  if(m_dg)
    IupShowXY(m_dg, IUP_CENTER, IUP_CENTER);

  m_bbox.reset();
  g_canvas_main->set_bounding_box(m_bbox);

  //srand ( time(NULL) );

  this->create_object("..\\models\\bunny_ordenado.ply");
  //this->add_object("..\\models\\bunny_ordenado.ply", 2, 0, 0, 0, 0, 0, 1, 1, 1);

  //this->create_object("..\\models\\couth\\couch_ordenado.ply");

  this->create_scene();
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cMainDialog::create_object(string filename)
{
  cAppGauge gauge;
  string s = "Loading " + get_file_name(filename) + " file...";
  gauge.set_title(s.c_str());
  gauge.show();

  s_filename = filename;

  cObject *obj = NULL;

  obj = new cObject();
  obj->create(filename, NULL);

  int v = obj->get_num_vertex(), 
      t = obj->get_num_geometries();
  
  static char att[1024];
  sprintf(att, "Libvis - %s - Vertex: %d Triangles: %d", get_file_name(filename).c_str(), v, t);
  IupStoreAttribute(m_dg, IUP_TITLE, att);

  gauge.kill();

  // calculate bouding box
  m_bbox.reset();
  m_bbox = obj->get_transform_bbox();
  g_canvas_main->set_bounding_box(m_bbox);
  // Calculate acceleration and speed using bbox
  g_canvas_main->set_navig_att(m_bbox);

  obj->create_vao_shader(g_shader);

  obj->set_id(g_model->get_size());

  g_model->add_object(obj);
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cMainDialog::add_object(string filename, 
                             float tx, float ty, float tz, 
                             float rx, float ry, float rz,
                             float sx, float sy, float sz)
{
  cAppGauge gauge;
  string s = "Loading " + get_file_name(filename) + " file...";
  gauge.set_title(s.c_str());
  gauge.show();

  cObject *obj = new cObject();
  obj->add_rotate(rx, ry, rz);
  obj->add_translate(tx, ty, tz);
  obj->add_scale(sx, sy, sz);
  obj->create(filename, NULL);

  int v = obj->get_num_vertex(), 
      t = obj->get_num_geometries();
  
  static char att[1024];
  sprintf(att, "Libvis - %s - Vertex: %d Triangles: %d", get_file_name(filename).c_str(), v, t);
  IupStoreAttribute(m_dg, IUP_TITLE, att);

  gauge.kill();
 
  // calculate bouding box
  m_bbox = obj->get_transform_bbox();
  sBox bbox = g_canvas_main->get_bounding_box();
  bbox.add(m_bbox);
  g_canvas_main->set_bounding_box(bbox);
  // Calculate acceleration and speed using bbox
  g_canvas_main->set_navig_att(m_bbox);

  obj->create_vao_shader(g_shader);
  obj->set_id(g_model->get_size());

  g_model->add_object(obj);
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cMainDialog::add_object(float tx, float ty, float tz, 
                             float rx, float ry, float rz,
                             float sx, float sy, float sz)
{
  cAppGauge gauge;

  gauge.show();

  cObjectQuad *quad_att = new cObjectQuad(0.01, 0.01, 0.01);

  int v = quad_att->get_num_vertex(), 
      t = quad_att->get_num_geometries();

  gauge.kill();
 
  // calculate bouding box
  m_bbox = quad_att->get_transform_bbox();
  sBox bbox = g_canvas_main->get_bounding_box();
  bbox.add(m_bbox);
  g_canvas_main->set_bounding_box(bbox);
  // Calculate acceleration and speed using bbox
  g_canvas_main->set_navig_att(bbox);

  quad_att->create_vao_shader(g_shader);
  quad_att->set_id(g_model->get_size());

  g_model->add_object(quad_att);
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
bool cMainDialog::create_scene(void)
{
  if(!g_accel_render)
    g_accel_render = new sAccelerationRender();

  if(!g_accel_render)
  {
    printf("bla");
    return false;
  }

  vrbv::SceneData sceneData;

  // Set bounding box type to use
  vrbv::BoxFactory::setDefaultBoxType(vrbv::BoxFactory::Type_Aabb);

  // Begin sending geometry to vdlib
  sceneData.beginScene();

  for(int i = 0; i < (int) g_model->m_vec_render_pick.size(); i++)
  {
    // Create geometry
    vrbv::Geometry* geom = new vrbv::Geometry();
    geom->setId(i);

    // Send it to scene data
    sceneData.beginGeometry(geom);

    //sceneData.addVertices(teste, 6);
    sceneData.addVertices(g_model->m_vec_render_pick[i]->get_vertex(), 
                          g_model->m_vec_render_pick[i]->get_num_vertex() * 3);
    sceneData.transformVertices(g_model->m_vec_render_pick[i]->get_transformation());

    sceneData.endGeometry();
  }

  // End current scene
  sceneData.endScene();

  // Build hierarchy
  vrbv::TreeBuilder builder;
  g_accel_render->m_scene_root = builder.createTree(sceneData);

  if(!g_accel_render->m_scene_root)
  {
    delete g_accel_render;
    g_accel_render = NULL;

    return false;
  }

  g_accel_render->m_frustum_culler.init(builder.getStatistics());

  return true;
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
Ihandle* cMainDialog::create_dialog(void)
{
  g_canvas_main = new cCanvasMain(string(CANVAS_MAIN), 800, 600);

  it_subcanvas_fit            = IupItem("Fit\tF", NULL);
  it_subcanvas_zoom_in        = IupItem("Zoom In\tI", NULL);
  it_subcanvas_zoom_out       = IupItem("Zoom Out\tO", NULL);
  it_subcanvas_projection_xy  = IupItem("XY-Plane\tZ", NULL);
  it_subcanvas_projection_xz  = IupItem("XZ-Plane\tY", NULL);
  it_subcanvas_projection_yz  = IupItem("YZ-Plane\tX", NULL);
  it_subcanvas_ortho          = IupItem("Isometric", NULL);
  it_subcanvas_manip          = IupItem("Manipulation\tM", NULL);
  it_subcanvas_navig          = IupItem("Navigation\tN", NULL);
  it_subcanvas_detach         = IupItem("Detach", NULL);
  it_subcanvas_close          = IupItem("Close", NULL);

  m_subcanvas_menu = IupSetAtt("it_subcanvas_menu",
    IupMenu(
      it_subcanvas_fit,
      IupSeparator(),
      it_subcanvas_zoom_in,
      it_subcanvas_zoom_out,
      IupSeparator(),
      it_subcanvas_projection_xy,
      it_subcanvas_projection_xz,
      it_subcanvas_projection_yz,
      IupSeparator(),
      it_subcanvas_manip,
      it_subcanvas_navig,
      IupSeparator(),
      it_subcanvas_detach,
      IupSeparator(),
      it_subcanvas_close,
    NULL),
  NULL); 

  it_detail_fit           = IupItem("Fit\tF", NULL);
  it_detail_zoom_in       = IupItem("Zoom In\tI", NULL);
  it_detail_zoom_out      = IupItem("Zoom Out\tO", NULL);
  it_detail_projection_xy = IupItem("XY-Plane\tZ", NULL);
  it_detail_projection_xz = IupItem("XZ-Plane\tY", NULL);
  it_detail_projection_yz = IupItem("YZ-Plane\tX", NULL);
  it_detail_ortho         = IupItem("Isometric", NULL);
  it_detail_manip         = IupItem("Manipulation\tM", NULL);
  it_detail_navig         = IupItem("Navigation\tN", NULL);  
  it_detail_attach        = IupItem("Attach", NULL);
  it_detail_close         = IupItem("Close", NULL);

  m_detail_menu = IupSetAtt("it_detail_menu",
    IupMenu(
      it_detail_fit,
      IupSeparator(),
      it_detail_zoom_in,
      it_detail_zoom_out,
      IupSeparator(),
      it_detail_projection_xy,
      it_detail_projection_xz,
      it_detail_projection_yz,
      IupSeparator(),
      it_detail_manip,
      it_detail_navig,
      IupSeparator(),
      it_detail_attach,
      IupSeparator(),
      it_detail_close,
    NULL),
  NULL); 

  m_bt_show = IupSetAtt(NULL, 
    IupButton(NULL, NULL), 
    IUP_TIP, "Show",
    IUP_IMAGE, "IUP_ActionOk",
  NULL);
  m_bt_zoom = IupSetAtt(NULL, 
    IupButton(NULL, NULL), 
    IUP_TIP, "Zoom",
    IUP_IMAGE, "IUP_Zoom",
  NULL);
  m_bt_zoom_in = IupSetAtt(NULL,
    IupButton(NULL, NULL),
    IUP_TIP, "Zoom In",
    IUP_IMAGE, "IUP_ZoomIn",
  NULL);
  m_bt_zoom_out = IupSetAtt(NULL,
    IupButton(NULL, NULL),
    IUP_TIP, "Zoom Out",
    IUP_IMAGE, "IUP_ZoomOut",
  NULL);
  m_bt_ortho = IupSetAtt(NULL,
    IupButton(" O ", NULL),
    IUP_TIP, "Projection Ortho",
  NULL);
  m_bt_projetion_xy = IupSetAtt(NULL,
    IupButton("XY", NULL),
    IUP_TIP, "Projection XY",
  NULL);
  m_bt_projetion_xz = IupSetAtt(NULL,
    IupButton("XZ", NULL),
    IUP_TIP, "Projection XZ",
  NULL);
  m_bt_projetion_yz = IupSetAtt(NULL,
    IupButton("YZ", NULL),
    IUP_TIP, "Projection YZ",
  NULL);
  m_bt_projetion_xyz = IupButton("XYZ", NULL);
  m_bt_detail = IupSetAtt(NULL,
    IupButton(NULL, NULL),
    IUP_TIP, "Zoom Detail",
    IUP_IMAGE, "IUP_ZoomSelection",
  NULL);
  m_bt_fit = IupSetAtt(NULL,
    IupButton(NULL, NULL),
    IUP_TIP, "Fit",
    IUP_IMAGE, "IUP_ZoomActualSize",
  NULL);
  m_bt_undo_view = IupSetAtt(NULL,
    IupButton(NULL, NULL),
    IUP_TIP, "Undo view",
    IUP_IMAGE, "IUP_EditUndo",
  NULL);
  m_bt_redo_view = IupSetAtt(NULL,
    IupButton(NULL, NULL),
    IUP_TIP, "Redo view",
    IUP_IMAGE, "IUP_EditRedo",
  NULL);
  m_bt_reset = IupSetAtt(NULL,
    IupButton("Reset Shader", NULL),
    IUP_TIP, "Reset Shader",
  NULL);
  m_tg_pick = IupSetAtt(NULL,
    IupToggle("Pick", NULL),
    IUP_TIP, "Pick",
    IUP_VALUE, IUP_OFF,
  NULL);
  m_tg_pick_disable = IupSetAtt(NULL,
    IupToggle("Disable Pick", NULL),
    IUP_TIP, "Disable Pick",
    IUP_VALUE, IUP_ON,
  NULL);
  m_tg_pick_object = IupSetAtt(NULL,
    IupToggle("Object", NULL),
    IUP_TIP, "Pick object",
    IUP_VALUE, IUP_ON,
  NULL);
  m_tg_pick_element = IupSetAtt(NULL,
    IupToggle("Element", NULL),
    IUP_TIP, "Pick Element",
    IUP_VALUE, IUP_OFF,
  NULL);
  m_tg_bbox = IupSetAtt(NULL,
    IupToggle("Bouding Box", NULL),
    IUP_TIP, "Bouding Box",
    IUP_VALUE, IUP_OFF,
  NULL);
  m_tg_fps = IupSetAtt(NULL,
    IupToggle("FPS", NULL),
    IUP_TIP, "FPS",
    IUP_VALUE, IUP_ON,
  NULL);
  m_tg_wireframe = IupSetAtt(NULL,
    IupToggle("Wireframe", NULL),
    IUP_TIP, "wireframe",
    IUP_VALUE, IUP_OFF,
  NULL);
  m_tg_vertex_mesh_quad = IupSetAtt(NULL,
    IupToggle("Vertex Mesh Quad", NULL),
    IUP_TIP, "Vertex Mesh Quad",
    IUP_VALUE, IUP_OFF,
  NULL);
  m_tg_vertex_mesh_pts = IupSetAtt(NULL,
    IupToggle("Vertex Mesh Points", NULL),
    IUP_TIP, "Vertex Mesh Points",
    IUP_VALUE, IUP_OFF,
  NULL);
  m_tg_va = IupSetAtt(NULL,
    IupToggle("VA", NULL),
    IUP_TIP, "Vertex Array",
    IUP_VALUE, IUP_OFF,
  NULL);
  m_tg_vbo = IupSetAtt(NULL,
    IupToggle("VBO", NULL),
    IUP_TIP, "Vertex Buffer Object",
    IUP_VALUE, IUP_OFF,
  NULL);
  m_tg_shader = IupSetAtt(NULL,
    IupToggle("Shader + VAO", NULL),
    IUP_TIP, "Shader + Vertex Array Object",
    IUP_VALUE, IUP_ON,
  NULL);

  Ihandle *lst_bt = IupSetAtt(NULL,
    IupVbox(
      IupFill(),
      IupHbox(
        m_bt_ortho,
        m_bt_projetion_xy,
        m_bt_projetion_xz,
        m_bt_projetion_yz,
        IupSetAtt(NULL, IupFill(), IUP_SIZE, "10", NULL),
        m_bt_fit,
        m_bt_detail,
        IupSetAtt(NULL, IupFill(), IUP_SIZE, "10", NULL),
        m_bt_zoom,
        m_bt_zoom_in,
        m_bt_zoom_out,
        IupSetAtt(NULL, IupFill(), IUP_SIZE, "10", NULL),
        m_bt_undo_view,
        m_bt_redo_view,
        IupFill(),
        m_bt_show,
        IupFill(),
      NULL),
      IupFill(),
    NULL),
    "TABTITLE", "View",
  NULL);

  Ihandle *lst_settings = IupSetAtt(NULL,
    IupHbox(
      IupVbox(
        IupFill(),
        m_tg_wireframe,
        IupFill(),
        m_tg_fps,
        IupFill(),
        m_tg_bbox,
        IupFill(),
      NULL),
      IupVbox(
        IupFill(),
        m_tg_vertex_mesh_quad,
        IupFill(),
        m_tg_vertex_mesh_pts,
        IupFill(),
      NULL),
      //IupSetAtt(NULL,
      //  IupFrame(
      //    IupRadio(
      //      IupHbox(
      //        IupVbox(
      //          IupFill(),
      //          m_tg_va,
      //          IupFill(),
      //          m_tg_vbo,
      //          IupFill(),
      //        NULL),
      //        IupVbox(
      //          IupFill(),
      //          m_tg_shader,
      //          IupFill(),
      //        NULL),
      //      NULL)
      //    )
      //  ),
      //  IUP_TITLE, "Render : ",
      //NULL),
      //IupSetAtt(NULL, IupFill(), IUP_SIZE, "10", NULL),
      //IupVbox(
      //  IupFill(),
      //  m_bt_reset,
      //  IupFill(),
      //NULL),
      //IupFill(),
    NULL),
    "TABTITLE", "Settings",
  NULL);

  Ihandle *lst_pick = IupSetAtt(NULL,
    IupHbox(
      IupSetAtt(NULL,
        IupFrame(
          IupRadio(
            IupVbox(
              IupFill(),  
              m_tg_pick_disable,
              IupFill(),
              m_tg_pick_object,
              IupFill(),
              m_tg_pick_element,
              IupFill(),
            NULL)
          )
        ),
        IUP_TITLE, "Pick",
      NULL),
      IupFill(),
    NULL),
    "TABTITLE", "Pick",
  NULL);

  Ihandle *tabs = IupSetAtt("tabs",
    IupTabs(
      lst_bt,
      lst_settings,
      lst_pick,
    NULL),
  NULL);

  Ihandle *dg = IupSetAtt("dg_main",
    IupDialog(
      IupVbox(
        tabs,
        g_canvas_main->get_iup_canvas(),
      NULL) 
    ),
    "TITLE", "Libvis",
    IUP_ICON, "IUP_Tecgraf",
    IUP_DROPFILES_CB, "cb_drop_files",
  NULL);

  return dg;
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cMainDialog::set_callbacks(void)
{
  IupSetAttribute(m_dg, "ANFLEX_OBJECT", (char*)this);
  IupSetAttribute(m_subcanvas_menu, "ANFLEX_OBJECT", (char*)this);
  IupSetAttribute(m_detail_menu, "ANFLEX_OBJECT", (char*)this);

  IupSetFunction("cb_drop_files", (Icallback)cb_drop_file);

  IupSetCallback(m_bt_zoom,     IUP_ACTION, (Icallback)cb_zoom);
  IupSetCallback(m_bt_zoom_in,  IUP_ACTION, (Icallback)cb_zoom);
  IupSetCallback(m_bt_zoom_out, IUP_ACTION, (Icallback)cb_zoom);
  IupSetCallback(m_bt_detail,   IUP_ACTION, (Icallback)cb_zoom);

  IupSetCallback(m_bt_projetion_xy,  IUP_ACTION, (Icallback)cb_projection);
  IupSetCallback(m_bt_projetion_xz,  IUP_ACTION, (Icallback)cb_projection);
  IupSetCallback(m_bt_projetion_yz,  IUP_ACTION, (Icallback)cb_projection);
  IupSetCallback(m_bt_ortho,         IUP_ACTION, (Icallback)cb_projection);
  IupSetCallback(m_bt_fit,           IUP_ACTION, (Icallback)cb_projection);

  IupSetCallback(it_subcanvas_projection_xy, IUP_ACTION, (Icallback)cb_subcanvas_menu);
  IupSetCallback(it_subcanvas_projection_xz, IUP_ACTION, (Icallback)cb_subcanvas_menu);
  IupSetCallback(it_subcanvas_projection_yz, IUP_ACTION, (Icallback)cb_subcanvas_menu);
  IupSetCallback(it_subcanvas_zoom_in,       IUP_ACTION, (Icallback)cb_subcanvas_menu);
  IupSetCallback(it_subcanvas_zoom_out,      IUP_ACTION, (Icallback)cb_subcanvas_menu);
  IupSetCallback(it_subcanvas_ortho,         IUP_ACTION, (Icallback)cb_subcanvas_menu);
  IupSetCallback(it_subcanvas_fit,           IUP_ACTION, (Icallback)cb_subcanvas_menu);
  IupSetCallback(it_subcanvas_manip,         IUP_ACTION, (Icallback)cb_subcanvas_menu);
  IupSetCallback(it_subcanvas_navig,         IUP_ACTION, (Icallback)cb_subcanvas_menu);
  IupSetCallback(it_subcanvas_detach,        IUP_ACTION, (Icallback)cb_subcanvas_menu);
  IupSetCallback(it_subcanvas_close,         IUP_ACTION, (Icallback)cb_subcanvas_menu);

  IupSetCallback(it_detail_projection_xy, IUP_ACTION, (Icallback)cb_detail_menu);
  IupSetCallback(it_detail_projection_xz, IUP_ACTION, (Icallback)cb_detail_menu);
  IupSetCallback(it_detail_projection_yz, IUP_ACTION, (Icallback)cb_detail_menu);
  IupSetCallback(it_detail_zoom_in,       IUP_ACTION, (Icallback)cb_detail_menu);
  IupSetCallback(it_detail_zoom_out,      IUP_ACTION, (Icallback)cb_detail_menu);
  IupSetCallback(it_detail_ortho,         IUP_ACTION, (Icallback)cb_detail_menu);
  IupSetCallback(it_detail_fit,           IUP_ACTION, (Icallback)cb_detail_menu);
  IupSetCallback(it_detail_manip,         IUP_ACTION, (Icallback)cb_detail_menu);
  IupSetCallback(it_detail_navig,         IUP_ACTION, (Icallback)cb_detail_menu);
  IupSetCallback(it_detail_attach,        IUP_ACTION, (Icallback)cb_detail_menu);
  IupSetCallback(it_detail_close,         IUP_ACTION, (Icallback)cb_detail_menu);

  IupSetCallback(m_tg_vertex_mesh_quad, IUP_ACTION, (Icallback)cb_main);
  IupSetCallback(m_tg_vertex_mesh_pts,  IUP_ACTION, (Icallback)cb_main);

  IupSetCallback(m_tg_pick_disable,  IUP_ACTION, (Icallback)cb_main);
  IupSetCallback(m_tg_pick_object,   IUP_ACTION, (Icallback)cb_main);
  IupSetCallback(m_tg_pick_element, IUP_ACTION, (Icallback)cb_main);
  IupSetCallback(m_tg_va,            IUP_ACTION, (Icallback)cb_main);
  IupSetCallback(m_tg_vbo,           IUP_ACTION, (Icallback)cb_main);
  IupSetCallback(m_tg_shader,        IUP_ACTION, (Icallback)cb_main);
  IupSetCallback(m_tg_pick,          IUP_ACTION, (Icallback)cb_main);
  IupSetCallback(m_tg_fps,           IUP_ACTION, (Icallback)cb_main);
  IupSetCallback(m_tg_wireframe,     IUP_ACTION, (Icallback)cb_main);
  IupSetCallback(m_tg_bbox,          IUP_ACTION, (Icallback)cb_main);
  IupSetCallback(m_bt_undo_view,     IUP_ACTION, (Icallback)cb_main);
  IupSetCallback(m_bt_redo_view,     IUP_ACTION, (Icallback)cb_main);
  IupSetCallback(m_bt_reset,         IUP_ACTION, (Icallback)cb_main);
  IupSetCallback(m_bt_show,          IUP_ACTION, (Icallback)cb_main);
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cMainDialog::init_dialog(void)
{
  // set vgl parameters
  g_canvas_main->set_vgl(render, render_end, NULL, process_pick, (void*)NULL);

  // set detach parameters
  g_canvas_main->set_detach_attribute(detail_redraw, 
                                      NULL, // redraw end
                                      NULL, // idle
                                      NULL, // data
                                      VGL_FOREVER,
                                      open_detail_menu,
                                      "IUP_Tecgraf",
                                      "Detail",
                                      "dg_main");

  // set attach parameters
  g_canvas_main->set_function_canvas_attach(subcanvas_redraw, 
                                            subcanvas_end_redraw, 
                                            open_subcanvas_menu);

  g_canvas_main->add_idle(render_idle, (void*)g_canvas_main->get_camera());
  g_fps = new cFPS();
  g_fps->restart();
  SetSwapInterval(0);

  // store first camera
  g_canvas_main->repaint();
  g_canvas_main->reset_camera_view();
  //g_canvas_main->projection(cCanvas::PLANE_XY);
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cMainDialog::open_subcanvas_menu(void *data)
{ 
  s_current_subcanvas = ((cCanvasAttach*)data);
  if(!s_current_subcanvas) return;

  IupSetAttribute(IupGetHandle("it_navig"), 
                  IUP_VALUE, 
                  s_current_subcanvas->is_activate_navig() ? IUP_ON : IUP_OFF);
  IupSetAttribute(IupGetHandle("it_manip"), 
                  IUP_VALUE, 
                  s_current_subcanvas->is_activate_manip() ? IUP_ON : IUP_OFF);

  IupPopup(IupGetHandle("it_subcanvas_menu"), IUP_MOUSEPOS, IUP_MOUSEPOS);
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cMainDialog::open_detail_menu(void *data)
{ 
  s_current_detail = ((cCanvasDetach*)data);
  if(!s_current_detail) return;

  IupSetAttribute(IupGetHandle("it_detail_navig"), 
                  IUP_VALUE, 
                  s_current_detail->is_activate_navig() ? IUP_ON : IUP_OFF);
  IupSetAttribute(IupGetHandle("it_detail_manip"), 
                  IUP_VALUE, 
                  s_current_detail->is_activate_manip() ? IUP_ON : IUP_OFF);

  IupPopup(IupGetHandle("it_detail_menu"), IUP_MOUSEPOS, IUP_MOUSEPOS);
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
int cMainDialog::cb_drop_file(Ihandle *ih, const char* filename, int num, int x, int y)
{
  cMainDialog *main_class = (cMainDialog*) IupGetAttribute(ih, "ANFLEX_OBJECT");

  main_class->create_object(filename);

  return IUP_DEFAULT;
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
int cMainDialog::cb_zoom(Ihandle* ih)
{
  cMainDialog *main_class = (cMainDialog*)IupGetAttribute(ih, "ANFLEX_OBJECT");

  if(ih == main_class->m_bt_zoom)
    g_canvas_main->activate_zoom();
  else if(ih == main_class->m_bt_zoom_in)
    g_canvas_main->zoom_in();
  else if(ih == main_class->m_bt_zoom_out)
    g_canvas_main->zoom_out();
  else if(ih == main_class->m_bt_detail)
    g_canvas_main->activate_detail();

  return IUP_DEFAULT;
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
int cMainDialog::cb_projection(Ihandle* ih)
{
  cMainDialog *main_class = (cMainDialog*)IupGetAttribute(ih, "ANFLEX_OBJECT");

  if(ih == main_class->m_bt_projetion_xy)
    g_canvas_main->projection(cCanvas::PLANE_XY);
  else if(ih == main_class->m_bt_projetion_xz)
    g_canvas_main->projection(cCanvas::PLANE_XZ);
  else if(ih == main_class->m_bt_projetion_yz)
    g_canvas_main->projection(cCanvas::PLANE_YZ);
  else if(ih == main_class->m_bt_ortho)
    g_canvas_main->orthographic(!g_canvas_main->orthographic());
  else if(ih == main_class->m_bt_fit)
    g_canvas_main->fit();

  return IUP_DEFAULT;
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
int cMainDialog::cb_main(Ihandle* ih)
{
  cMainDialog *main_class = (cMainDialog*)IupGetAttribute(ih, "ANFLEX_OBJECT");

  if(ih == main_class->m_tg_vertex_mesh_quad)
  {
    bool enable = true;
    if(IupGetAttribute(main_class->m_tg_vertex_mesh_quad, IUP_VALUE) == IUP_OFF)
      enable = false;
    
    for(int i = 0; i < (int) g_model->m_vec_render_pick.size(); i++)
    {
      int type = g_model->m_vec_render_pick[i]->get_object_type();

      if(type == cPick::OBJECT)
        ((cObject*)g_model->m_vec_render_pick[i])->add_render_att_fe_mesh_quad(enable, g_shader);
      else if(type == cPick::QUAD){}
        ((cObjectQuad*)g_model->m_vec_render_pick[i])->add_render_att_fe_mesh_quad(enable, g_shader);  
    }
  }
  else if(ih == main_class->m_tg_vertex_mesh_pts)
  {
    bool enable = true;
    if(IupGetAttribute(main_class->m_tg_vertex_mesh_pts, IUP_VALUE) == IUP_OFF)
      enable = false;

    for(int i = 0; i < (int) g_model->m_vec_render_pick.size(); i++)
    {
      int type = g_model->m_vec_render_pick[i]->get_object_type();

      if(type == cPick::OBJECT)
        ((cObject*)g_model->m_vec_render_pick[i])->add_render_att_fe_mesh_pts(enable, g_shader);
      //else if(type == cRenderPick::QUAD){}
      //  ((cObjectQuad*)g_model->m_vec_render_pick[i])->add_render_att_fe_mesh_pts(enable, g_shader);  
    }
  }
  else if(ih == main_class->m_tg_pick_disable)
  {
    if(IupGetAttribute(main_class->m_tg_pick_disable, IUP_VALUE) == IUP_ON)
    {
      cPick::m_pick_type = cPick::NO_PICK;
    }

    for(int i = 0; i < (int) g_model->m_vec_render_pick.size(); i++)
    {
      g_model->m_vec_render_pick[i]->unfocus_object();
      g_model->m_vec_render_pick[i]->unselect_object();

      g_model->m_vec_render_pick[i]->set_focus(false);
      g_model->m_vec_render_pick[i]->set_focus(-1);

      g_model->m_vec_render_pick[i]->set_selected(false);
      g_model->m_vec_render_pick[i]->remove_all_selected();
    }
  }
  else if(ih == main_class->m_tg_pick_object)
  {
    if(IupGetAttribute(main_class->m_tg_pick_object, IUP_VALUE) == IUP_ON)
      cPick::m_pick_type = cPick::PICK_BY_OBJECT;

    for(int i = 0; i < (int) g_model->m_vec_render_pick.size(); i++)
    {
      g_model->m_vec_render_pick[i]->unfocus_object();
      g_model->m_vec_render_pick[i]->unselect_object();

      g_model->m_vec_render_pick[i]->set_focus(false);
      g_model->m_vec_render_pick[i]->set_focus(-1);

      g_model->m_vec_render_pick[i]->set_selected(false);
      g_model->m_vec_render_pick[i]->remove_all_selected();
    }
  }
  else if(ih == main_class->m_tg_pick_element)
  {
    if(IupGetAttribute(main_class->m_tg_pick_element, IUP_VALUE) == IUP_ON)
      cPick::m_pick_type = cPick::PICK_BY_ELEMET;

    for(int i = 0; i < (int) g_model->m_vec_render_pick.size(); i++)
    {
      g_model->m_vec_render_pick[i]->unfocus_object();
      g_model->m_vec_render_pick[i]->unselect_object();

      g_model->m_vec_render_pick[i]->set_focus(false);
      g_model->m_vec_render_pick[i]->set_focus(-1);

      g_model->m_vec_render_pick[i]->set_selected(false);
      g_model->m_vec_render_pick[i]->remove_all_selected();
    }
  }
  else if(ih == main_class->m_tg_wireframe)
  {
    bool wireframe = true;
    if(IupGetAttribute(main_class->m_tg_wireframe, IUP_VALUE) == IUP_OFF)
      wireframe = false;

    for(int i = 0; i < (int) g_model->m_vec_render_pick.size(); i++)
      g_model->m_vec_render_pick[i]->set_render_wireframe(wireframe);
  }
  else if(ih == main_class->m_tg_fps)
  {
    if(IupGetAttribute(main_class->m_tg_fps, IUP_VALUE) == IUP_OFF)
    {
      delete g_fps;
      g_fps = NULL;

      g_canvas_main->rem_idle(render_idle, main_class);

      // Enable V-Sync for benchmarking
      // Attention! Only works under Windows
      SetSwapInterval(1);
    }
    else
    {
      g_fps = new cFPS();

      g_canvas_main->add_idle(render_idle, main_class);

      // Enable V-Sync for benchmarking
      // Attention! Only works under Windows
      SetSwapInterval(0);

      g_fps->restart();
    }
    g_canvas_main->repaint();
  }
  else if(ih == main_class->m_tg_bbox)
  {
    bool render_bbox = false;
    if(IupGetAttribute(main_class->m_tg_bbox, IUP_VALUE) == IUP_OFF)
      render_bbox = false;
    else
      render_bbox = true;
  }
  else if(ih == main_class->m_bt_undo_view)
  {
    g_canvas_main->undo_camera_view();
  }
  else if(ih == main_class->m_bt_redo_view)
  {
    g_canvas_main->redo_camera_view();
  }
  else if(ih == main_class->m_bt_reset)
  {
    // TODO refazer para vários objetos
    main_class->create_object(s_filename);
  }
  else if(ih == main_class->m_bt_show)
  {
    delete obj_dialog;
    obj_dialog = new cObjDialog();
    obj_dialog->show_dialog();
  }

  return IUP_DEFAULT;
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
int cMainDialog::cb_subcanvas_menu(Ihandle* ih)
{
  cMainDialog *main_class = (cMainDialog*)IupGetAttribute(ih, "ANFLEX_OBJECT");

  if(ih == main_class->it_subcanvas_projection_xy)
    s_current_subcanvas->projection(cCanvas::PLANE_XY);
  else if(ih == main_class->it_subcanvas_projection_xz)
    s_current_subcanvas->projection(cCanvas::PLANE_XZ);
  else if(ih == main_class->it_subcanvas_projection_yz)
    s_current_subcanvas->projection(cCanvas::PLANE_YZ);
  else if(ih == main_class->it_subcanvas_ortho)
    s_current_subcanvas->orthographic(!s_current_subcanvas->orthographic());
  else if(ih == main_class->it_subcanvas_fit)
    s_current_subcanvas->fit();
  else if(ih == main_class->it_subcanvas_zoom_in)
    s_current_subcanvas->zoom_in();
  else if(ih == main_class->it_subcanvas_zoom_out)
    s_current_subcanvas->zoom_out();
  else if(ih == main_class->it_subcanvas_manip)
    s_current_subcanvas->activate_manip();
  else if(ih == main_class->it_subcanvas_navig)
    s_current_subcanvas->activate_navig();
  else if(ih == main_class->it_subcanvas_detach)
  {
    g_canvas_main->create_canvas_detach(s_current_subcanvas->get_copy_camera());
    g_canvas_main->delete_canvas_attach(s_current_subcanvas);
    g_canvas_main->repaint();
  }
  else if(ih == main_class->it_subcanvas_close)
  {
    g_canvas_main->delete_canvas_attach(s_current_subcanvas);
    g_canvas_main->repaint();
  }

  s_current_subcanvas = NULL;
  return IUP_DEFAULT;
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
int cMainDialog::cb_detail_menu(Ihandle* ih)
{
  cMainDialog *main_class = (cMainDialog*)IupGetAttribute(ih, "ANFLEX_OBJECT");

  if(ih == main_class->it_detail_projection_xy)
    s_current_detail->projection(cCanvas::PLANE_XY);
  else if(ih == main_class->it_detail_projection_xz)
    s_current_detail->projection(cCanvas::PLANE_XZ);
  else if(ih == main_class->it_detail_projection_yz)
    s_current_detail->projection(cCanvas::PLANE_YZ);
  else if(ih == main_class->it_detail_ortho)
    s_current_detail->orthographic(!s_current_subcanvas->orthographic());
  else if(ih == main_class->it_detail_fit)
    s_current_detail->fit();
  else if(ih == main_class->it_detail_zoom_in)
    s_current_detail->zoom_in();
  else if(ih == main_class->it_detail_zoom_out)
    s_current_detail->zoom_out();
  else if(ih == main_class->it_detail_manip)
    s_current_detail->activate_manip();
  else if(ih == main_class->it_detail_navig)
    s_current_detail->activate_navig();
  else if(ih == main_class->it_detail_attach)
  {
    if(g_canvas_main->create_canvas_attach(s_current_detail->get_copy_camera()))
    {
      IupHide(s_current_detail->get_dialog());
      delete s_current_detail;
      g_canvas_main->repaint();
    }
  }
  else if(ih == main_class->it_detail_close)
  {
    IupHide(s_current_detail->get_dialog());
    delete s_current_detail;
  }

  s_current_detail = NULL;
  return IUP_DEFAULT;
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void SetSwapInterval(int i)
{
  const GLubyte *extensions = glGetString(GL_EXTENSIONS);
  if(extensions && strstr((const char*)extensions, "WGL_EXT_swap_control") != 0)
  {
    //TODO (Thyago, 2009-09-28) Find out how to do it on Linux, if it should
#ifdef _WIN32
    PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = 0;
    wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");

    if(wglSwapIntervalEXT)
      wglSwapIntervalEXT(i);
#endif
  }
}