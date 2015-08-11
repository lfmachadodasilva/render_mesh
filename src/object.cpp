// ------------------------------------------------------------------------------------------------- 
 // Anflex Project -- Tecgraf/PUC-Rio  CENPES/Petrobras 
 // www.tecgraf.puc-rio.br 
 // 
 // Created by lfmachado in April/2012.
 // 
 // $URL: $ 
 // $Revision: $ 
 // $Date: $ 
 // 
 // $LastChangedBy: $ 
 // ------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <map>
using namespace std;

// vrbv
#include "vrbv\node.h"
#include "vrbv\boxfactory.h"
#include "vrbv\boxrenderer.h"
#include "vrbv\scenedata.h"
#include "vrbv\treebuilder.h"

#include "alg\vector.h"

#include "render\appearance.h"
#include "render\pick.h"
#include "render\render-att.h"
#include "render\render-quad-att.h"
#include "render\render-femesh-pts.h"

#include "GL\glew.h"
#include "gli\gli.hpp"
#include "gli\gtx\gl_texture2d.hpp"

#include "texture.h"
#include "object.h"
#include "anfvar.h"
#include "rply.h"

static char* filetobuf(const char *file);	

static GLfloat s_color[3] = { 0.2f, 0.2f, 0.8f };
static void render_bbox(sBox &bbox);

#pragma region Read ply file callback functions
static int vertex_x_cb(p_ply_argument argument) 
{
  long eol;
  void *pdata;
  ply_get_argument_user_data(argument, &pdata, &eol);
  
  long index;						
	ply_get_argument_element(argument, NULL, &index);

  vector<sVertex> &v = *static_cast<vector<sVertex> *>(pdata);
  v[index].v.x = ply_get_argument_value(argument);

  return 1;
}

static int vertex_y_cb(p_ply_argument argument) 
{
  long eol;
  void *pdata;
  ply_get_argument_user_data(argument, &pdata, &eol);
  
  long index;						
	ply_get_argument_element(argument, NULL, &index);

  vector<sVertex> &v = *static_cast<vector<sVertex> *>(pdata);
  v[index].v.y = ply_get_argument_value(argument);

  return 1;
}

static int vertex_z_cb(p_ply_argument argument) 
{
  long eol;
  void *pdata;
  ply_get_argument_user_data(argument, &pdata, &eol);
  
  long index;						
	ply_get_argument_element(argument, NULL, &index);

  vector<sVertex> &v = *static_cast<vector<sVertex> *>(pdata);
  v[index].v.z = ply_get_argument_value(argument);

  return 1;
}

static int vertex_s_cb(p_ply_argument argument) 
{
  long eol;
  void *pdata;
  ply_get_argument_user_data(argument, &pdata, &eol);
  
  long index;						
	ply_get_argument_element(argument, NULL, &index);

  vector<sVertex> &v = *static_cast<vector<sVertex> *>(pdata);
  v[index].s = ply_get_argument_value(argument);

  return 1;
}

static int vertex_t_cb(p_ply_argument argument) 
{
  long eol;
  void *pdata;
  ply_get_argument_user_data(argument, &pdata, &eol);
  
  long index;						
	ply_get_argument_element(argument, NULL, &index);

  vector<sVertex> &v = *static_cast<vector<sVertex> *>(pdata);
  v[index].t = ply_get_argument_value(argument);

  return 1;
}

static int face_cb(p_ply_argument argument) 
{
  long length, value_index, eol, index;
  void *pdata;

  ply_get_argument_property(argument, NULL, &length, &value_index);
  					
	ply_get_argument_element(argument, NULL, &index);
  
  ply_get_argument_user_data(argument, &pdata, &eol);

  vector<sFace3v> &v = *static_cast<vector<sFace3v> *>(pdata);

  switch (value_index) 
  {
  case 0:
    v[index].v1 = (int) ply_get_argument_value(argument);
    break;
  case 1: 
    v[index].v2 = (int) ply_get_argument_value(argument);
    break;
  case 2:
    v[index].v3 = (int) ply_get_argument_value(argument);
    break;
  default: 
    break;
  }

  return 1;
}
#pragma endregion

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
cObject::cObject(void) : cRenderPick(cPick::OBJECT),
                         cObjectFather(),
                         m_render_bbox(false), 
                         m_pick_object(false)
{ 
  set_id(-1);
  m_index_selected = -1;

  m_transformation_matrix.Identity();
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cObject::create(string filename, cAppGauge *gauge)
{
  // read file
  read_file(filename, gauge);

  // calculate normals 
  calc_normals(gauge);

  // create array
  create_array(gauge);

  // read texture
  read_texture();

  // create scene / aabb tree
  create_scene();
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cObject::read_file(string filename, cAppGauge *gauge)
{
  // open file
  p_ply ply = ply_open(filename.c_str(), NULL, 0, NULL);
  if(!ply) 
    return;

  // read header
  if(!ply_read_header(ply))
  {
    ply_close(ply);
    return;
  }

  vecVertex.clear();
  vecTria.clear();

  // set read callback function
  m_num_vertex = ply_set_read_cb(ply, "vertex", "x", vertex_x_cb, &vecVertex, 0);
  if(!m_num_vertex)
  {
    ply_close(ply);
    return;
  }
  vecVertex.resize(m_num_vertex);
  ply_set_read_cb(ply, "vertex", "y", vertex_y_cb, &vecVertex, 0);
  ply_set_read_cb(ply, "vertex", "z", vertex_z_cb, &vecVertex, 1);

  m_render_texture = false;
  
  int n = ply_set_read_cb(ply, "vertex", "s", vertex_s_cb, &vecVertex, 0);
  m_render_texture = n ? true : false;
  ply_set_read_cb(ply, "vertex", "t", vertex_t_cb, &vecVertex, 1);

  m_num_geometries = ply_set_read_cb(ply, "face", "vertex_indices", face_cb, &vecTria, 0);
  if(!m_num_geometries)
  {
    ply_close(ply);
    return;
  }
  vecTria.resize(m_num_geometries);
  // end of set read callback functions

  if(gauge)
    gauge->set_num_steps(2 * ((2 * m_num_geometries) + m_num_vertex));

  printf("\nFile: %s\t Vertex: %ld\t Triangles: %ld\n\n", 
         get_file_name(filename).c_str(), 
         m_num_vertex, m_num_geometries);

  if (!ply_read(ply)) return;
  ply_close(ply);

  if(gauge)
    gauge->set_step((2 * m_num_geometries) + m_num_vertex);
}
 
// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cObject::calc_normals(cAppGauge *gauge)
{
  for(int i = 0; i < (int)vecVertex.size(); i++)
  {
    vecVertex[i].normal.x = 0.0f;
    vecVertex[i].normal.y = 0.0f;
    vecVertex[i].normal.z = 0.0f;
  }

  const float limit = FLT_MAX;
  float xmin =  limit;
  float xmax = -limit;
  float ymin =  limit;
  float ymax = -limit;
  float zmin =  limit;
  float zmax = -limit;

  // Calculate normals
  int v1, v2, v3;
  AlgVector vec1, vec2, normal;
  float modulo1, modulo2;
  for(int i = 0; i < m_num_geometries; i++)
  {
    v1 = vecTria[i].v1;
    v2 = vecTria[i].v2;
    v3 = vecTria[i].v3;

#pragma region calculate normal
    //normal em v1
    vec1 = vecVertex[v2].v - vecVertex[v1].v;
    vec2 = vecVertex[v3].v - vecVertex[v1].v;
    modulo1 = vec1.Length();
    modulo2 = vec2.Length();
    normal = vec1.Cross(vec2);
    vecVertex[v1].normal += (normal*(normal.Length()/(modulo1*modulo2)));

    //normal em v2
    vec1 = vecVertex[v3].v - vecVertex[v2].v;
    vec2 = vecVertex[v1].v - vecVertex[v2].v;
    modulo1 = vec1.Length();
    modulo2 = vec2.Length();
    normal = vec1.Cross(vec2);
    vecVertex[v2].normal += (normal*(normal.Length()/(modulo1*modulo2)));

    //normal em v3
    vec1 = vecVertex[v1].v - vecVertex[v3].v;
    vec2 = vecVertex[v2].v - vecVertex[v3].v;
    modulo1 = vec1.Length();
    modulo2 = vec2.Length();
    normal = vec1.Cross(vec2);
    vecVertex[v3].normal += (normal*(normal.Length()/(modulo1*modulo2)));
#pragma endregion

    // calculate bouding box
    xmin = std::min(xmin, vecVertex[v1].v.x);
    xmax = std::max(xmax, vecVertex[v1].v.x);
    ymin = std::min(ymin, vecVertex[v1].v.y);
    ymax = std::max(ymax, vecVertex[v1].v.y);
    zmin = std::min(zmin, vecVertex[v1].v.z);
    zmax = std::max(zmax, vecVertex[v1].v.z);
           
    xmin = std::min(xmin, vecVertex[v2].v.x);
    xmax = std::max(xmax, vecVertex[v2].v.x);
    ymin = std::min(ymin, vecVertex[v2].v.y);
    ymax = std::max(ymax, vecVertex[v2].v.y);
    zmin = std::min(zmin, vecVertex[v2].v.z);
    zmax = std::max(zmax, vecVertex[v2].v.z);
           
    xmin = std::min(xmin, vecVertex[v3].v.x);
    xmax = std::max(xmax, vecVertex[v3].v.x);
    ymin = std::min(ymin, vecVertex[v3].v.y);
    ymax = std::max(ymax, vecVertex[v3].v.y);
    zmin = std::min(zmin, vecVertex[v3].v.z);
    zmax = std::max(zmax, vecVertex[v3].v.z);

    if(gauge)
      gauge->update();
  }

  m_bbox = sBox(xmin, xmax, ymin, ymax, zmin, zmax);

}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cObject::create_array(cAppGauge *gauge)
{
  if(m_vertex)  delete[] m_vertex;
  if(m_color)   delete[] m_color;
  if(m_normal)  delete[] m_normal;
  if(m_index)   delete[] m_index;

  //m_num_tria = (int)vecTria.size();
  if(m_num_geometries == 0) return;

  m_vertex = new GLfloat[3 * m_num_vertex];
  m_color  = new GLfloat[3 * m_num_vertex];
  m_normal = new GLfloat[3 * m_num_vertex];

  if(m_render_texture)
    m_texture_coord = new GLfloat[2 * m_num_vertex];

  for(int i = 0, j = 0; i < m_num_vertex; i++)
  {
    j = 3 * i;
    m_vertex[j]   = (GLfloat) vecVertex[i].v.x;
    m_vertex[j+1] = (GLfloat) vecVertex[i].v.y;
    m_vertex[j+2] = (GLfloat) vecVertex[i].v.z;

    //vecVertex[i].normal *= -1;

    m_normal[j]   = (GLfloat) vecVertex[i].normal.x;
    m_normal[j+1] = (GLfloat) vecVertex[i].normal.y;
    m_normal[j+2] = (GLfloat) vecVertex[i].normal.z;

    m_color[j]    = (GLfloat) s_color[0];
    m_color[j+1]  = (GLfloat) s_color[1];
    m_color[j+2]  = (GLfloat) s_color[2];

    if(m_render_texture)
    {
      j = 2 * i;
      m_texture_coord[j]     = (GLfloat) vecVertex[i].s;
      m_texture_coord[j + 1] = (GLfloat) vecVertex[i].t;
    }

    if(gauge)
      gauge->update();
  }
  
  m_index  = new GLuint[3 * m_num_geometries];
  for(int i = 0, j = 0; i < m_num_geometries; i++)
  {
    j = 3 * i;
    m_index[j]   = vecTria[i].v1;
    m_index[j+1] = vecTria[i].v2;
    m_index[j+2] = vecTria[i].v3;

    if(gauge)
      gauge->update();
  }

  vecTria.clear();
  vecVertex.clear();
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cObject::create_scene(void)
{
  vrbv::SceneData sceneData;

  // Set bounding box type to use
  vrbv::BoxFactory::setDefaultBoxType(vrbv::BoxFactory::Type_Aabb);

  // Begin sending geometry to vdlib
  sceneData.beginScene();

  GLfloat triangle[9];

  for(int i = 0, j = 0; i < (int) m_num_geometries; i++)
  {
    // Create geometry
    vrbv::Geometry *geom = new vrbv::Geometry();
    geom->setId(i);

    // Send it to scene data
    sceneData.beginGeometry(geom);

    j = 3 * i;

    int v1 = m_index[j + 0] * 3;
    int v2 = m_index[j + 1] * 3;
    int v3 = m_index[j + 2] * 3;

    triangle[0] = m_vertex[v1 + 0];
    triangle[1] = m_vertex[v1 + 1];
    triangle[2] = m_vertex[v1 + 2];
                           
    triangle[3] = m_vertex[v2 + 0];
    triangle[4] = m_vertex[v2 + 1];
    triangle[5] = m_vertex[v2 + 2];
      
    triangle[6] = m_vertex[v3 + 0];
    triangle[7] = m_vertex[v3 + 1];
    triangle[8] = m_vertex[v3 + 2];

    sceneData.addVertices(triangle, 9);
    sceneData.transformVertices(get_transformation());

    sceneData.endGeometry();
  }

  // End current scene
  sceneData.endScene();

  // Build hierarchy
  vrbv::TreeBuilder builder;
  m_scene_root = builder.createTree(sceneData);

  if(!m_frustum_culler)
    m_frustum_culler = new vdlib::FrustumCuller();
  m_frustum_culler->init(builder.getStatistics());
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cObject::read_texture(void)
{
  if(m_render_texture)
  {
    if(cRender::m_new_render)
      m_texture_id = gli::createTexture2D("..\\models\\couth\\diffuse.tga");
    else
    {
      string mess;
      m_texture = new cTexture(GL_TEXTURE_2D, GL_REPEAT, GL_NEAREST, GL_MODULATE);
      bool ok = m_texture->addImage(string("..\\models\\couth\\diffuse.bmp"), mess);
      if(!ok)
      {
        delete m_texture; m_texture = NULL;
        IupMessage("Warning", (char*)mess.c_str());
      }
    }
  }
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
bool cObject::check_pick(const int &id, 
                         const AlgVector &ray_ori, 
                         const AlgVector &ray_dest,
                         AlgVector *point)
{
  if(m_geometry_type == TRIANGLE)
  {
    int id0 = m_index[(id * 3) + 0] * 3;
    int id1 = m_index[(id * 3) + 1] * 3;
    int id2 = m_index[(id * 3) + 2] * 3;

    AlgVector v0 = m_transformation_matrix.Transform(
      m_vertex[id0 + 0],
      m_vertex[id0 + 1],
      m_vertex[id0 + 2]);

    AlgVector v1 = m_transformation_matrix.Transform(
      m_vertex[id1 + 0],
      m_vertex[id1 + 1],
      m_vertex[id1 + 2]);

    AlgVector v2 = m_transformation_matrix.Transform(
      m_vertex[id2 + 0],
      m_vertex[id2 + 1],
      m_vertex[id2 + 2]);

    if(intersect_ray_triangle(ray_ori, ray_dest, v0, v1, v2, point) == 1)
      return true;
  }
  else if(m_geometry_type == LINE)
  {
  }

  return false;  
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cObject::change_element_pick(const bool insert, // inserting or removing
                                  const bool is_select, // is focus or select
                                  const int id) // id of element
{
  if(cRender::m_geometry_type == cRender::TRIANGLE)
  {
    set<int>::iterator it;
    set<int> set = cPick::get_selected();

    if(is_select)
    {
      if(!insert)
        set.erase(set.find(id));
      
      int i = 1;
      cPick::m_vec_selec[0] = (int)set.size();
      for(it = set.begin(); it != set.end(); it++, i++) 
        cPick::m_vec_selec[i] = (*it);
    }
    else 
      cPick::set_focus(insert ? id : -1);
  }
  else
  {
  }
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cObject::add_render_att_fe_mesh_quad(bool enable, cShader *shader)
{
  if(enable)
  {
    cRender *quad = new cRenderQuadAtt(0.0005, 0.0005, 0.0005);
    quad->create_vao_shader(shader);
    m_map_render_obj_att[cRender::FE_MESH_QUAD] = quad;
    quad->reset_transformation();
  }
  else
  {
    map<int, cRender*>::iterator it;
    it = m_map_render_obj_att.find(cRender::FE_MESH_QUAD);
    delete it->second;
    m_map_render_obj_att.erase(it);
  }
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cObject::add_render_att_fe_mesh_pts(bool enable, cShader *shader)
{
  if(enable)
  {
    cRender *femesh = new cRenderFeMeshPts(m_vertex, m_num_vertex, m_transformation_matrix);
    femesh->create_vao_shader(shader);
    m_map_render_obj_att[cRender::FE_MESH_POINT] = femesh;
  }
  else
  {
    map<int, cRender*>::iterator it;
    it = m_map_render_obj_att.find(cRender::FE_MESH_POINT);
    delete it->second;
    m_map_render_obj_att.erase(it);
  }
}


// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cObject::render(const cShader *shader, const cRenderAtt *render_att)
{
    // Object render
    cRenderPick::render(shader, render_att);

    map<int, cRender*>::iterator it;
    for(it = m_map_render_obj_att.begin(); it != m_map_render_obj_att.end(); it++)
    {
      if(it->first == cRender::FE_MESH_QUAD)
        m_render_shader_fe_mesh(it->second, shader, render_att);
      if(it->first == cRender::FE_MESH_POINT)
        it->second->render(shader, render_att);
    }
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cObject::m_render_shader_fe_mesh(cRender *att, 
                                      const cShader *shader, 
                                      const cRenderAtt *render_att)
{
  for(int i = 0, j = 0; i < m_num_vertex; i++)
  {
    j = i * 3;

    att->reset_transformation();
    att->add_translate(m_vertex[j + 0], m_vertex[j + 1], m_vertex[j + 2]);
    att->render(shader, render_att);
  }
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void render_bbox(sBox &bbox)
{
  glColor3f(0.0f, 0.0f, 0.0f);
  glBegin(GL_LINES);
  {
    // 1
    glVertex3d(bbox.min.x, bbox.min.y, bbox.min.z);
    glVertex3d(bbox.max.x, bbox.min.y, bbox.min.z);

    // 2
    glVertex3d(bbox.min.x, bbox.min.y, bbox.min.z);
    glVertex3d(bbox.min.x, bbox.min.y, bbox.max.z);

    // 3
    glVertex3d(bbox.min.x, bbox.min.y, bbox.min.z);
    glVertex3d(bbox.min.x, bbox.max.y, bbox.min.z);

    // 4
    glVertex3d(bbox.min.x, bbox.min.y, bbox.max.z);
    glVertex3d(bbox.max.x, bbox.min.y, bbox.max.z);

    // 5
    glVertex3d(bbox.min.x, bbox.min.y, bbox.max.z);
    glVertex3d(bbox.min.x, bbox.max.y, bbox.max.z);

    // 6
    glVertex3d(bbox.max.x, bbox.min.y, bbox.min.z);
    glVertex3d(bbox.max.x, bbox.min.y, bbox.max.z);

    // 7
    glVertex3d(bbox.max.x, bbox.min.y, bbox.min.z);
    glVertex3d(bbox.max.x, bbox.max.y, bbox.min.z);

    // 8
    glVertex3d(bbox.max.x, bbox.max.y, bbox.min.z);
    glVertex3d(bbox.min.x, bbox.max.y, bbox.min.z);

    // 9
    glVertex3d(bbox.max.x, bbox.max.y, bbox.max.z);
    glVertex3d(bbox.min.x, bbox.max.y, bbox.max.z);

    // 10
    glVertex3d(bbox.max.x, bbox.max.y, bbox.max.z);
    glVertex3d(bbox.max.x, bbox.min.y, bbox.max.z);

    // 11
    glVertex3d(bbox.max.x, bbox.max.y, bbox.max.z);
    glVertex3d(bbox.max.x, bbox.max.y, bbox.min.z);

    // 12
    glVertex3d(bbox.min.x, bbox.max.y, bbox.min.z);
    glVertex3d(bbox.min.x, bbox.max.y, bbox.max.z);
  }
  glEnd();
}

// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
char* filetobuf(const char *file)
{
  FILE *fptr;
  long length;
  char *buf;

  fptr = fopen(file, "rb"); /* Open file for reading */
  if (!fptr) /* Return NULL on failure */
    return NULL;
  fseek(fptr, 0, SEEK_END); /* Seek to the end of the file */
  length = ftell(fptr); /* Find out how many bytes into the file we are */
  buf = (char*)malloc(length+1); /* Allocate a buffer for the entire length of the file and a null terminator */
  fseek(fptr, 0, SEEK_SET); /* Go back to the beginning of the file */
  fread(buf, length, 1, fptr); /* Read the contents of the file in to the buffer */
  fclose(fptr); /* Close the file */
  buf[length] = 0; /* Null terminator */

  return buf; /* Return the buffer */
}