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

// Lib vis
#include "vdlib\frustumculler.h"
#include "vdlib\occlusionculler.h"
#include "vrbv\boxrenderer.h"
#include "ufont\fontmanager.h"

#include "render\render-pick.h"
#include "render\render-att.h"
#include "render\render-callback.h"

#include "anfvar.h"
#include "model.h"
#include "obj-dialog.h"

#include "vr\Mat4.h"

static double fps = 0.0, ms = 0.0;
static AlgVector s_bg_color(1.0f, 1.0f, 1.0f);

static void display_fps(double fps, double ms);
static void plot_menu_subcanvas(void);
static void calc_pick_matrix(const AlgMatrix &mvp, // Model view projection matrix
                             const AlgVector raster_pos, // Raster position of mouse, use only x and y
                             AlgMatrix &pick_matrix); // pick matrix out
static void calc_world_position(const AlgVector &raster_pos, // Raster position of mouse, use onlu x and y
                                AlgVector &world_pos_near, // World position of mouse (closer to the screen)
                                AlgVector &world_pos_far); // World position of mouse (lasted render)

void init_opengl(void);

enum { FRUSTUM_CULLER, ALL };
static int s_draw_type = FRUSTUM_CULLER;

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void process_pick(VglCamera *camera, bool double_click, bool ctrl, int bt, int st)
{
  // Pick is disabled
  if(cPick::m_pick_type == cPick::NO_PICK)
    return;

  if(!g_accel_render)
    return;

  //VglCamera *camera = (VglCamera*)camera;
  g_render_att->set(camera);

  static bool first = true;
  if(first)
  {
    first = false;
  g_accel_render->m_render_callback.set_render_att(g_render_att);
  g_accel_render->m_render_callback.set_shader(g_shader);
  g_accel_render->m_render_callback.set_model(&g_model->m_vec_render_pick[0]);

  // get viewport
  g_canvas_main->get_vgl_canvas()->GetViewport(&g_render_att->m_viewport[0], 
                                               &g_render_att->m_viewport[1], 
                                               &g_render_att->m_viewport[2], 
                                               &g_render_att->m_viewport[3]);
  }

  // calculate model view projection
  AlgMatrix mvp;
  mvp = g_render_att->m_projection_matrix;  
  mvp.Accum(g_render_att->m_model_view_matrix);

  // get mouse position and transform to raster position
  AlgVector raster_mouse_pos;
  g_canvas_main->get_mouse_pos(raster_mouse_pos.x, raster_mouse_pos.y);
  raster_mouse_pos.x = g_render_att->m_viewport[0] + raster_mouse_pos.x * g_render_att->m_viewport[2];
  raster_mouse_pos.y = g_render_att->m_viewport[1] + raster_mouse_pos.y * g_render_att->m_viewport[3];

  // Calculate pick matrix with small area around the mouse
  AlgMatrix pick_matrix;
  calc_pick_matrix(mvp, raster_mouse_pos, pick_matrix);

  // First frustum culler. Used to discovery witch object is in the pick matrix
  g_accel_render->m_render_callback.set_callbalk_to_pick();
  g_accel_render->m_frustum_culler.updateFrustumPlanes(pick_matrix.GetMatrix());
  g_accel_render->m_frustum_culler.traverse(g_accel_render->m_scene_root, 
                                            &g_accel_render->m_render_callback);

  // Check if has selected object
  vector<int> vet_selected = g_accel_render->m_render_callback.get_selected();
  if(!vet_selected.empty())
  {
    std::map<float, std::pair<int, int> > map_closer;
    std::list<float> list_closer;

    for(int i = 0; i < (int)vet_selected.size(); i++)
    {
      // Selected object
      int id = vet_selected[i];
      
      vdlib::FrustumCuller *frustum_culler = g_model->m_vec_render_pick[id]->get_frustum_culler();
      vrbv::Node *scene_root = g_model->m_vec_render_pick[id]->get_scene_root();
      if(!scene_root)
        continue;
      
      // Second frustum culling. From selected object, selected triangle from pick matrix
      g_accel_render->m_render_callback.set_callbalk_to_pick();
      frustum_culler->updateFrustumPlanes(pick_matrix.GetMatrix());
      frustum_culler->traverse(scene_root, &g_accel_render->m_render_callback);

      // Check if has selected triangles
      vector<int> vet_selected_vertex = g_accel_render->m_render_callback.get_selected();
      if(!vet_selected_vertex.empty())
      { 
        // calculate world position by screen coordinate
        AlgVector world_pos_near, // coordinate closer to the screen
                  world_pos_far; // coordinate of lasted render opengl
        calc_world_position(raster_mouse_pos, world_pos_near, world_pos_far);

        AlgVector point;

        for(int j = 0; j < (int) vet_selected_vertex.size(); j++)
        {        
          // check if this element is intersect from this ray
          if(g_model->m_vec_render_pick[id]->check_pick(vet_selected_vertex[j], 
                                                         world_pos_near, 
                                                         world_pos_far, 
                                                         &point))
          {
            // store distance from screen
            float dist = world_pos_near.Distance(point);
            list_closer.push_front(dist);
            map_closer.insert(std::pair<float, std::pair<int, int> >
                              (dist, std::pair<int, int>(id, vet_selected_vertex[j])));
          } // end if
        } // end for
      } // end if
    } // end for

    if(list_closer.empty())
    {
      if(g_last_focus)
      {
        if(cPick::m_pick_type == cPick::PICK_BY_OBJECT)
          g_last_focus->unfocus_object();
        else if(cPick::m_pick_type == cPick::PICK_BY_ELEMET)
          g_last_focus->unfocus_element();
        g_last_focus = NULL;
      } // end if
    } // end if
    else
    {
      list_closer.sort();
      std::pair<int, int> select = map_closer.find(*list_closer.begin())->second;

      if(double_click)
      {
        printf("Double click - obj: %d - element: %d\n", select.first, select.second);
      }

      if(cPick::m_pick_type == cPick::PICK_BY_OBJECT)
      {
        if(double_click)
        {
          if(g_model->m_vec_render_pick[select.first]->is_selected())
            g_model->m_vec_render_pick[select.first]->unselect_object();
          else
          {
            g_last_focus->unfocus_object();
            //g_model->m_vec_render_pick[select.first]->select_object();

            cObjDialog *obj_dialog = new cObjDialog();
            obj_dialog->show_dialog();
            delete obj_dialog;
          }
        }

        if(g_last_focus != g_model->m_vec_render_pick[select.first])
        {
          if(g_last_focus)
            g_last_focus->unfocus_object();
          g_last_focus = g_model->m_vec_render_pick[select.first];
          g_last_focus->focus_object();
        }

      } // end if pick by object
      else if(cPick::m_pick_type == cPick::PICK_BY_ELEMET)
      {
        if(double_click)
        {
          if(g_model->m_vec_render_pick[select.first]->is_selected(select.second))
            g_model->m_vec_render_pick[select.first]->unselect_element(select.second);
          else
            g_model->m_vec_render_pick[select.first]->select_element(select.second);
        }

        if(g_last_focus != g_model->m_vec_render_pick[select.first])
        {
          if(g_last_focus)
            g_last_focus->unfocus_element();
          g_last_focus = g_model->m_vec_render_pick[select.first];
          g_last_focus->focus_element(select.second);
        }
        else
        {
          if(g_last_focus->get_focus() != select.second)
          {
            g_last_focus->unfocus_element();
            g_last_focus->focus_element(select.second);
          }
        }
      } // end else if pick by element

    }// end else
  } // end if has selected object
  else
  {
    // No selected object
    if(g_last_focus)
    {
      if(cPick::m_pick_type == cPick::PICK_BY_OBJECT)
        g_last_focus->unfocus_object();
      else if(cPick::m_pick_type == cPick::PICK_BY_ELEMET)
        g_last_focus->unfocus_element();
      g_last_focus = NULL;
    }
  }
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void render_frame(void *data) 
{
  if(!g_accel_render->m_scene_root)
    return;

  VglCamera *camera = (VglCamera*)data;
  g_render_att->set(camera);

  //static bool first = true;
  //if(first)
  //{
  //  first = false;
  g_accel_render->m_render_callback.set_render_att(g_render_att);
  g_accel_render->m_render_callback.set_shader(g_shader);
  g_accel_render->m_render_callback.set_model(&g_model->m_vec_render_pick[0]);

  // get viewport
  g_canvas_main->get_vgl_canvas()->GetViewport(&g_render_att->m_viewport[0], 
                                               &g_render_att->m_viewport[1], 
                                               &g_render_att->m_viewport[2], 
                                               &g_render_att->m_viewport[3]);
  //}

  // calculate model view projection
  AlgMatrix mvp;
  mvp = g_render_att->m_projection_matrix;  
  mvp.Accum(g_render_att->m_model_view_matrix);

  //process_pick(mvp);

#pragma region render
  g_accel_render->m_frustum_culler.updateFrustumPlanes(mvp.GetMatrix());
  
  g_accel_render->m_render_callback.set_callbalk_to_render();
  
  if(g_shader) 
    g_shader->load(*g_render_att);
  
  if(s_draw_type == ALL)
  {
    for(vrbv::PreOrderIterator itr(g_accel_render->m_scene_root); !itr.done(); itr.next())
      g_accel_render->m_render_callback.draw(itr.current());
  }
  else if(s_draw_type == FRUSTUM_CULLER)
  {
    g_accel_render->m_frustum_culler.traverse(g_accel_render->m_scene_root, 
                                              &g_accel_render->m_render_callback);
  }
  else
  {
  }

  if(g_shader) 
    g_shader->unload();

#pragma endregion
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void render_frame2(void *data) 
{
  if(g_model->m_vec_render_pick2.empty())
    return;
  if(!g_accel_render)
    return;
  if(!g_accel_render->m_scene_root)
    return;

  VglCamera *camera = (VglCamera*)data;
  g_render_att->set(camera);

  //static bool first = true;
  //if(first)
  //{
  //  first = false;
  g_accel_render->m_render_callback.set_render_att(g_render_att);
  g_accel_render->m_render_callback.set_shader(g_shader);
  g_accel_render->m_render_callback.set_model(&g_model->m_vec_render_pick2[0]);

  // get viewport
  g_canvas_obj->get_vgl_canvas()->GetViewport(&g_render_att->m_viewport[0], 
                                               &g_render_att->m_viewport[1], 
                                               &g_render_att->m_viewport[2], 
                                               &g_render_att->m_viewport[3]);
  //}

  // calculate model view projection
  AlgMatrix mvp;
  mvp = g_render_att->m_projection_matrix;  
  mvp.Accum(g_render_att->m_model_view_matrix);

  //process_pick(mvp);

#pragma region render
  g_accel_render->m_frustum_culler.updateFrustumPlanes(mvp.GetMatrix());
  
  g_accel_render->m_render_callback.set_callbalk_to_render();
  
  if(g_shader) 
    g_shader->load(*g_render_att);
  
  if(s_draw_type == ALL)
  {
    for(vrbv::PreOrderIterator itr(g_accel_render->m_scene_root); !itr.done(); itr.next())
      g_accel_render->m_render_callback.draw(itr.current());
  }
  else if(s_draw_type == FRUSTUM_CULLER)
  {
    g_accel_render->m_frustum_culler.traverse(g_accel_render->m_scene_root, 
                                              &g_accel_render->m_render_callback);
  }
  else
  {
  }

  if(g_shader) 
    g_shader->unload();

#pragma endregion
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void render(void *data)
{
#ifdef _DEBUG
  GLenum glerror = glGetError();
  if(glerror != GL_NO_ERROR)
    printf("File: %s, Line: %d - ERROR: OpenGL error %x on render start.\n", __FILE__, __LINE__, glerror);
#endif

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

  glClearColor(s_bg_color.x, s_bg_color.y, s_bg_color.z, 1.0);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);

  glEnable(GL_LIGHTING);

  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

  render_frame(data);

#ifdef _DEBUG
  glerror = glGetError();
  if(glerror != GL_NO_ERROR)
    printf("File: %s, Line: %d - ERROR: OpenGL error %x on render end. %s\n", __FILE__, __LINE__, glerror, gluErrorString(glerror));
#endif
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void render2(void *data)
{
#ifdef _DEBUG
  GLenum glerror = glGetError();
  if(glerror != GL_NO_ERROR)
    printf("File: %s, Line: %d - ERROR: OpenGL error %x on render start.\n", __FILE__, __LINE__, glerror);
#endif

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);

  glEnable(GL_LIGHTING);

  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

  render_frame2(data);

#ifdef _DEBUG
  glerror = glGetError();
  if(glerror != GL_NO_ERROR)
    printf("File: %s, Line: %d - ERROR: OpenGL error %x on render end. %s\n", __FILE__, __LINE__, glerror, gluErrorString(glerror));
#endif
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void render_end(void *data)
{
#ifdef _DEBUG
  GLenum glerror = glGetError();
  if(glerror != GL_NO_ERROR)
    printf("File: %s, Line: %d - ERROR: OpenGL error %x on render_end start.\n", __FILE__, __LINE__, glerror);
#endif

  if(g_fps)
  {
    g_fps->updateFPS(fps, ms);
    if(!g_model->m_vec_render_pick.empty())
      display_fps(fps, ms);
  }

#ifdef _DEBUG
  glerror = glGetError();
  if(glerror != GL_NO_ERROR)
    printf("File: %s, Line: %d - ERROR: OpenGL error %x on render_end end.\n", __FILE__, __LINE__, glerror);
#endif
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void render_idle(void *data)
{
  g_canvas_main->postRedraw();
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void detail_redraw(void *data)
{
#ifdef _DEBUG
  GLenum glerror = glGetError();
  if(glerror != GL_NO_ERROR)
    printf("File: %s, Line: %d - ERROR: OpenGL error %x on render start.\n", __FILE__, __LINE__, glerror);
#endif

  static bool first = true;
  if(first)
  {
    first = false;
    init_opengl();
  }

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

  render_frame(data);

  plot_menu_subcanvas();

#ifdef _DEBUG
  glerror = glGetError();
  if(glerror != GL_NO_ERROR)
    printf("File: %s, Line: %d - ERROR: OpenGL error %x on render_end end.\n", __FILE__, __LINE__, glerror);
#endif
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void subcanvas_redraw(void *data)
{
  g_canvas_main->clear_color_canvas_attach(data, 0.0f, 0.0f, 0.0f, 1.0f);
  g_canvas_main->clear_canvas_attach(data);

  VglSubCanvas *subcanvas = (VglSubCanvas*) data;
  render_frame((void*)subcanvas->GetCamera());

  plot_menu_subcanvas();
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void subcanvas_end_redraw(void *data)
{ 
  glPushAttrib(GL_ENABLE_BIT | 
               GL_CURRENT_BIT | 
               GL_POINT_BIT | 
               GL_DEPTH_BUFFER_BIT);
  glDisable(GL_LIGHTING);

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0.0, 1.0, 0.0, 1.0, 0.0, 1.0);

  glLineWidth(2.0);
  glColor3f(0.5, 0.5, 0.5);

  glBegin(GL_LINE_LOOP);
  glVertex2f(0.0, 0.0);
  glVertex2f(0.0, 1.0);
  glVertex2f(1.0, 1.0);
  glVertex2f(1.0, 0.0);
  glEnd();

  glPopMatrix();

  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();

  glPopAttrib();
  glLineWidth(1.0);
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void init_opengl(void)
{
  glClearColor(s_bg_color.x, s_bg_color.y, s_bg_color.z, 1.0);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);

  glEnable(GL_LIGHTING);

  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

  //glShadeModel(GL_SMOOTH);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  // init light
  {
    g_render_att->m_light_att.m_ambient_light[0] = 0.6f;
    g_render_att->m_light_att.m_ambient_light[1] = 0.6f;
    g_render_att->m_light_att.m_ambient_light[2] = 0.6f;
    g_render_att->m_light_att.m_ambient_light[3] = 1.0f;
    
    g_render_att->m_light_att.m_diffuse_light[0] = 0.3f;
    g_render_att->m_light_att.m_diffuse_light[1] = 0.3f;
    g_render_att->m_light_att.m_diffuse_light[2] = 0.3f;
    g_render_att->m_light_att.m_diffuse_light[3] = 1.0f;
    
    g_render_att->m_light_att.m_specular_light[0] = 0.3f;
    g_render_att->m_light_att.m_specular_light[1] = 0.3f;
    g_render_att->m_light_att.m_specular_light[2] = 0.3f;
    g_render_att->m_light_att.m_specular_light[3] = 1.0f;
    
    g_render_att->m_light_att.m_As[0] = 0.1f;
    g_render_att->m_light_att.m_As[1] = 0.1f;
    g_render_att->m_light_att.m_As[2] = 0.1f;
    g_render_att->m_light_att.m_As[3] = 1.0f;

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, g_render_att->m_light_att.m_As);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  g_render_att->m_light_att.m_ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  g_render_att->m_light_att.m_diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, g_render_att->m_light_att.m_specular_light);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0); // Enable only the headlight 
  }
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void display_fps(double fps, double ms)
{
  int vp[4];

  glGetIntegerv(GL_VIEWPORT, vp);
  glViewport(vp[0]+90, vp[3]-30, vp[2], vp[3]/8);

  float xmax = 10.0;
  float ymax = 10.0;

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluOrtho2D(0.0, xmax, 0.0, ymax);

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

  glDisable(GL_DEPTH_TEST);
  glDisable(GL_LIGHTING);
  glDepthMask(GL_FALSE);
  glDisable(GL_BLEND);

  float color[3];
  color[0] = s_bg_color.r;
  color[1] = s_bg_color.g;
  color[2] = s_bg_color.b;
  createNewRGB(color[0], color[1], color[2], 4);
  glColor3fv(color);

  float xoff = 0.1f;
  float yoff = 0.1f;

  char att[100];
  sprintf(att, "%.2f fps    %.2f ms", fps, ms);

  UFontGLUTMessage mess;
  mess.SetFont(GLUT_BITMAP_HELVETICA_12);
  mess.SetClippingCoords(false);

  mess.SetPosition(xoff, yoff, 0.0);
  mess.Display(att);

  glPopMatrix();

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();

  glMatrixMode(GL_MODELVIEW);

  glColor3f(1.0, 1.0, 1.0);

  glDepthMask(GL_TRUE);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_BLEND);
  glViewport(vp[0], vp[1], vp[2], vp[3]);
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void plot_menu_subcanvas(void)
{
  int vp[4];

  glGetIntegerv(GL_VIEWPORT, vp);
  glViewport(vp[0] + vp[2] - 213, (vp[1] + vp[3] - 15), 213, 15);

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluOrtho2D(0.0, 10.0, 0.0, 10.0);

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

  glDisable(GL_DEPTH_TEST);
  glDisable(GL_LIGHTING); 
  glDepthMask(GL_FALSE);
  glDisable(GL_BLEND);

  float xmin, xmax, ymin, ymax;

  xmin = 0.5;
  xmax = 1.0;
  ymin = 0.5;
  ymax = 6.0;

  glTranslatef(8.8f, 0.0f, 0.0f);

  glColor3f(0.83f, 0.83f, 0.83f);
  glBegin(GL_QUADS);
  glNormal3f(-1.0, 0.0, 0.0);

  glVertex3f((GLfloat) xmin, (GLfloat) ymin, 0.0f);
  glVertex3f((GLfloat) xmax, (GLfloat) ymin, 0.0f);
  glVertex3f((GLfloat) xmax, (GLfloat) ymax, 0.0f);
  glVertex3f((GLfloat) xmin, (GLfloat) ymax, 0.0f);
  glEnd();

  glDisable(GL_LIGHTING);
  glColor3f(0.0, 0.0, 0.0);
  glBegin(GL_LINES);
  glVertex3f((GLfloat) xmin, (GLfloat) ymin, 0.0f);
  glVertex3f((GLfloat) xmax, (GLfloat) ymin, 0.0f);
  glVertex3f((GLfloat) xmax, (GLfloat) ymin, 0.0f);
  glVertex3f((GLfloat) xmax, (GLfloat) ymax, 0.0f);
  glVertex3f((GLfloat) xmax, (GLfloat) ymax, 0.0f);
  glVertex3f((GLfloat) xmin, (GLfloat) ymax, 0.0f);
  glVertex3f((GLfloat) xmin, (GLfloat) ymin, 0.0f);
  glVertex3f((GLfloat) xmin, (GLfloat) ymax, 0.0f);
  glEnd();

  float dx, dy;

  dx = (xmax - xmin) * 0.25;
  dy = (ymax - ymin) * 0.1;

  glEnable(GL_LIGHTING);
  glColor3f(1.0, 1.0, 1.0);
  glBegin(GL_TRIANGLES);
  glNormal3f(0.0, 0.0, 1.0);
  glVertex3f( (GLfloat) (xmin + dx), (GLfloat) (ymax - 3.5*dy), 0.0f);
  glVertex3f( (GLfloat) (xmax - dx), (GLfloat) (ymax - 3.5*dy), 0.0f);
  glVertex3f( (GLfloat) (xmin + (xmax - xmin)/ 2.0), (GLfloat) (ymin + dy), 0.0f);
  glEnd();

  glPopMatrix();

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();

  glMatrixMode(GL_MODELVIEW);

  glColor3f(1.0, 1.0, 1.0);

  glDepthMask(GL_TRUE);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_BLEND);
  glViewport(vp[0], vp[1], vp[2], vp[3]);
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void calc_pick_matrix(const AlgMatrix &mvp, // Model view projection matrix
                      const AlgVector raster_pos, // Raster position of mouse, use only x and y
                      AlgMatrix &pick_matrix) // pick matrix out
{
  GLfloat tolw = 0.01, tolh = 0.01;

  // build pick matrix
  pick_matrix.Identity();
  // translate and scale the picked region to the entire window 
	GLfloat dx = (GLfloat) ((g_render_att->m_viewport[2] - 2 * 
                          (raster_pos.x - g_render_att->m_viewport[0])) / tolw);
	GLfloat dy = (GLfloat) ((g_render_att->m_viewport[3] - 2 * 
                          (raster_pos.y - g_render_att->m_viewport[1])) / tolh);
  pick_matrix.Translate(dx, dy, 0.0f);
  pick_matrix.Scale((GLfloat) (g_render_att->m_viewport[2] / tolw), 
                    (GLfloat) (g_render_att->m_viewport[3] / tolh), 
                    1.0);

  pick_matrix.Accum(mvp);
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void calc_world_position(const AlgVector &raster_pos, // Mouse raster position
                         AlgVector &world_pos_near,
                         AlgVector &world_pos_far)
{
  GLdouble world_position[3];
  GLdouble projection_double[16];
  GLdouble modelview_double[16];
  g_render_att->m_model_view_matrix.GetMatrixDouble(modelview_double);
  g_render_att->m_projection_matrix.GetMatrixDouble(projection_double);

  gluUnProject(raster_pos.x, raster_pos.y, 0.0f,
               modelview_double, 
               projection_double, 
               g_render_att->m_viewport, 
               &world_position[0],
               &world_position[1],
               &world_position[2]);

  world_pos_near.Set(world_position[0], world_position[1], world_position[2]);

  gluUnProject(raster_pos.x, raster_pos.y, 1.0f,
               modelview_double, 
               projection_double, 
               g_render_att->m_viewport,  
               &world_position[0],
               &world_position[1],
               &world_position[2]);

  world_pos_far.Set(world_position[0], world_position[1], world_position[2]);
}