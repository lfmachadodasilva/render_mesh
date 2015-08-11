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

// Iup library
#include <iup.h>
// End of Iup library

#include "vrbv\node.h"
#include "vrbv\boxfactory.h"
#include "vrbv\scenedata.h"
#include "vrbv\treebuilder.h"

#include "canvas\canvas-main.h"

#include "render\pick.h"

#include "render\render-pick.h"
#include "render\render-callback.h"

#include "obj-dialog.h"
#include "anfvar.h"
#include "object.h"
// End of project includes

// extern from render_functions
extern void init_opengl(void);
extern void render2(void *data);
extern void render(void *data);
//extern void SetSwapInterval(int i);
// end of extern from render_functions

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
cObjDialog::cObjDialog(void)
{
  m_dg = NULL;
  g_canvas_obj = NULL;

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
cObjDialog::~cObjDialog(void)
{
  delete g_canvas_obj;
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cObjDialog::show_dialog(void)
{
  cPick::m_pick_type = cPick::PICK_BY_OBJECT;

  create_object("..\\models\\bunny_ordenado.ply");
  //this->create_object("..\\models\\couth\\couch_ordenado.ply");

  m_bbox.reset();
  m_bbox = g_model->m_vec_render_pick[0]->get_bbox();
  g_canvas_obj->set_bounding_box(m_bbox);

  if(m_dg)
    IupPopup(m_dg, IUP_CENTER, IUP_CENTER);
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
Ihandle* cObjDialog::create_dialog(void)
{
  g_canvas_obj = new cCanvasMain(string(CANVAS_OBJ), 200, 200);

  IupSetAttribute(g_canvas_obj->get_iup_canvas(), "SHAREDCONTEXT", "canvas_main");
    
  Ihandle *dg = IupSetAtt("obj-dialog",
    IupDialog(g_canvas_obj->get_iup_canvas()),
  NULL);

  return dg;
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cObjDialog::set_callbacks(void)
{
  IupSetAttribute(m_dg, "ANFLEX_OBJECT", (char*)this);
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cObjDialog::init_dialog(void)
{
  // set vgl parameters
  g_canvas_obj->set_vgl(render2); // TODO lfmachado funcao de desenho utilizada

  //g_canvas_obj->add_idle(render_idle, (void*)g_canvas_obj->get_camera());
  //g_fps = new cFPS();
  //g_fps->restart();
  //SetSwapInterval(0);

  // store first camera
  g_canvas_obj->repaint();
  g_canvas_obj->reset_camera_view();
  //g_canvas_main->projection(cCanvas::PLANE_XY);
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cObjDialog::create_object(string filename)
{
  IupGLSwapBuffers(g_canvas_obj->get_iup_canvas());

  cObject *obj = NULL;

  obj = (cObject*) g_model->m_vec_render_pick[0];

  // TODO lfmachado teste utilizado para fazer o popup com tudo duplicado. 
  // Recriado e realocado tudo novamente. Sem isso nao funciona o popup

  // calculate bouding box
  m_bbox.reset();
  m_bbox = obj->get_transform_bbox();
  g_canvas_obj->set_bounding_box(m_bbox);
  // Calculate acceleration and speed using bbox
  g_canvas_obj->set_navig_att(m_bbox);

  obj->create_vao_shader2(g_shader);

  obj->set_id(0);

  // end TODO

  g_model->m_vec_render_pick2.push_back((cRenderPick*)obj);
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
bool cObjDialog::create_scene(void)
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

  for(int i = 0; i < (int) g_model->m_vec_render_pick2.size(); i++)
  {
    // Create geometry
    vrbv::Geometry* geom = new vrbv::Geometry();
    geom->setId(i);

    // Send it to scene data
    sceneData.beginGeometry(geom);

    //sceneData.addVertices(teste, 6);
    sceneData.addVertices(g_model->m_vec_render_pick2[i]->get_vertex(), 
                          g_model->m_vec_render_pick2[i]->get_num_vertex() * 3);
    sceneData.transformVertices(g_model->m_vec_render_pick2[i]->get_transformation());

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