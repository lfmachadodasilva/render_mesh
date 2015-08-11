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
// -------------------------------------------------------------------------------------------------

#include <map>
#include <set>
using namespace std;

// vrbv
#include "vrbv\node.h"
#include "vrbv\boxfactory.h"
#include "vrbv\boxrenderer.h"
#include "vrbv\scenedata.h"
#include "vrbv\treebuilder.h"

#include "util.h"

#include "object-quad.h"

static map<int, sFace3v> map_selected;

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
cObjectQuad::cObjectQuad(void) : cRenderQuadAtt(), cObjectFather()
{ 
  this->create_array_pick();
  this->create_scene(); 
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
cObjectQuad::cObjectQuad(float height, float width, float lenght) : 
   cRenderQuadAtt(height, width, lenght),
   cObjectFather()
     
{
  this->create_array_pick();
  this->create_scene(); 
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cObjectQuad::create_array_pick(void)
{
  //m_pick = new GLfloat[2 * m_num_geometries];
  //
  //for(int i = 0, j = 0; i < m_num_vertex; i++)
  //{
  //  j = 2 * i;
  //
  //  if(i == 0)
  //  {
  //    m_pick[j]    = (GLfloat) 1.0f;
  //    m_pick[j+1]  = (GLfloat) 1.0f;
  //  }
  //  else
  //  {
  //    m_pick[j]    = (GLfloat) 0.0f;
  //    m_pick[j+1]  = (GLfloat) 0.0f;
  //  }
  //}


}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cObjectQuad::add_render_att_fe_mesh_quad(bool enable, cShader *shader)
{
  if(enable)
  {
    cRender *quad = new cRenderQuadAtt(0.0005f, 0.0005f, 0.0005f);
    quad->create_vao_shader(shader);
    m_map_render_obj_att[cObjectQuad::FE_MESH_QUAD] = quad;
    quad->reset_transformation();
  }
  else
  {
    map<int, cRender*>::iterator it;
    it = m_map_render_obj_att.find(cObjectQuad::FE_MESH_QUAD);
    delete it->second;
    m_map_render_obj_att.erase(it);
  }
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cObjectQuad::create_scene(void)
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
    vrbv::Geometry* geom = new vrbv::Geometry();
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
bool cObjectQuad::check_pick(const int &id, 
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
void cObjectQuad::change_element_pick(const bool insert, const bool is_select, const int id)
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
      cPick::m_vec_selec[0] = (int)set.size() + 1;
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