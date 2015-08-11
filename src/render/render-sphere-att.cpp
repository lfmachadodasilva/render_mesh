//// ------------------------------------------------------------------------------------------------- 
//// Anflex Project -- Tecgraf/PUC-Rio  CENPES/Petrobras 
//// www.tecgraf.puc-rio.br 
//// 
//// Created by lfmachado in April/2012.
//// 
//// $URL: $ 
//// $Revision: $ 
//// $Date: $ 
//// 
//// $LastChangedBy: $ 
//// -------------------------------------------------------------------------------------------------
//
//#include "render-sphere-att.h"
//
//static GLfloat s_color[3] = { 0.2f, 0.2f, 0.8f };
//
//// -------------------------------------------------------------------------------------------------
//// -------------------------------------------------------------------------------------------------
//cRenderSphereAtt::cRenderSphereAtt(void) : 
//   cRenderObjectAtt(cRenderObjectAtt::SPHERE),
//   m_radius(1.0), 
//   m_slices(1.0), 
//   m_stacks(1.0)
//{
//  m_transformation_matrix.Identity();
//
//  m_num_geometries = 6 /*squares*/ * 2 /*triangles per square*/;
//  m_num_vertex = 8;
//
//  this->create();
//
//  this->calc_normals(NULL);
//
//  this->create_array(NULL);
//}
//
//// -------------------------------------------------------------------------------------------------
//// -------------------------------------------------------------------------------------------------
//cRenderSphereAtt::cRenderSphereAtt(float radius, float slices, float stacks) : 
//  cRenderObjectAtt(cRenderObjectAtt::SPHERE),
//  m_radius(radius), 
//  m_slices(slices), 
//  m_stacks(stacks)
//{
//  m_transformation_matrix.Identity();
//
//  m_num_geometries = 6 /*squares*/ * 2 /*triangles per square*/;
//  m_num_vertex = 8;   
//
//  this->create();
//
//  this->calc_normals(NULL);
//
//  this->create_array(NULL);
//}
//
//// -------------------------------------------------------------------------------------------------
//// -------------------------------------------------------------------------------------------------
//void cRenderSphereAtt::create(void)
//{
//  /*float const R = 1./(float)(m_slices - 1);
//  float const S = 1./(float)(m_stacks - 1);
//  int r, s;
//
//  vecVertex.resize(m_slices * m_stacks * 3);
// 
//  std::vector<sVertex>::iterator v = vecVertex.begin();
//
//  for(r = 0; r < m_slices; r++) 
//  {
//    for(s = 0; s < m_stacks; s++) 
//    {
//      float const y = sin( -M_PI_2 + M_PI * r * R );
//      float const x = cos(2*M_PI * s * S) * sin( M_PI * r * R );
//      float const z = sin(2*M_PI * s * S) * sin( M_PI * r * R );
//    }
//  }
//
//  vecTria.resize(m_slices * m_stacks * 4);
//  std:vector<sFace3v>::iterator i = vecTria.begin();
//  for(r = 0; r < m_slices; r++) 
//  {
//    for(s = 0; s < m_stacks; s++) 
//    {
//      *i++ = r * (int)m_stacks + s;
//      *i++ = r * (int)m_stacks + (s+1);
//      *i++ = (r+1) * m_stacks + (s+1);
//      *i++ = (r+1) * m_stacks + s;
//    }
//  }*/
//}
//
//// -------------------------------------------------------------------------------------------------
//// -------------------------------------------------------------------------------------------------
//void cRenderSphereAtt::calc_normals(cAppGauge *gauge)
//{
//  for(int i = 0; i < (int)vecVertex.size(); i++)
//    vecVertex[i].normal = AlgVector(0.0f, 0.0f, 0.0f);
//
//  if(m_geometry_type == cRenderObjectAtt::LINE)
//    return;
//
//  const float limit = FLT_MAX;
//  float xmin =  limit;
//  float xmax = -limit;
//  float ymin =  limit;
//  float ymax = -limit;
//  float zmin =  limit;
//  float zmax = -limit;
//
//  // Calculate normals
//  int v1, v2, v3;
//  AlgVector vec1, vec2, normal;
//  float modulo1, modulo2;
//  for(int i = 0; i < m_num_geometries; i++)
//  {
//    v1 = vecTria[i].v1;
//    v2 = vecTria[i].v2;
//    v3 = vecTria[i].v3;
//
//#pragma region calculate normal
//    //normal em v1
//    vec1 = vecVertex[v2].v - vecVertex[v1].v;
//    vec2 = vecVertex[v3].v - vecVertex[v1].v;
//    modulo1 = vec1.Length();
//    modulo2 = vec2.Length();
//    normal = vec1.Cross(vec2);
//    vecVertex[v1].normal += (normal*(normal.Length()/(modulo1*modulo2)));
//
//    //normal em v2
//    vec1 = vecVertex[v3].v - vecVertex[v2].v;
//    vec2 = vecVertex[v1].v - vecVertex[v2].v;
//    modulo1 = vec1.Length();
//    modulo2 = vec2.Length();
//    normal = vec1.Cross(vec2);
//    vecVertex[v2].normal += (normal*(normal.Length()/(modulo1*modulo2)));
//
//    //normal em v3
//    vec1 = vecVertex[v1].v - vecVertex[v3].v;
//    vec2 = vecVertex[v2].v - vecVertex[v3].v;
//    modulo1 = vec1.Length();
//    modulo2 = vec2.Length();
//    normal = vec1.Cross(vec2);
//    vecVertex[v3].normal += (normal*(normal.Length()/(modulo1*modulo2)));
//#pragma endregion
//
//    // calculate bouding box
//    xmin = std::min(xmin, vecVertex[v1].v.x);
//    xmax = std::max(xmax, vecVertex[v1].v.x);
//    ymin = std::min(ymin, vecVertex[v1].v.y);
//    ymax = std::max(ymax, vecVertex[v1].v.y);
//    zmin = std::min(zmin, vecVertex[v1].v.z);
//    zmax = std::max(zmax, vecVertex[v1].v.z);
//           
//    xmin = std::min(xmin, vecVertex[v2].v.x);
//    xmax = std::max(xmax, vecVertex[v2].v.x);
//    ymin = std::min(ymin, vecVertex[v2].v.y);
//    ymax = std::max(ymax, vecVertex[v2].v.y);
//    zmin = std::min(zmin, vecVertex[v2].v.z);
//    zmax = std::max(zmax, vecVertex[v2].v.z);
//           
//    xmin = std::min(xmin, vecVertex[v3].v.x);
//    xmax = std::max(xmax, vecVertex[v3].v.x);
//    ymin = std::min(ymin, vecVertex[v3].v.y);
//    ymax = std::max(ymax, vecVertex[v3].v.y);
//    zmin = std::min(zmin, vecVertex[v3].v.z);
//    zmax = std::max(zmax, vecVertex[v3].v.z);
//
//    //if(gauge)
//    //  gauge->update();
//  }
//
//  m_bbox = sBox(xmin, xmax, ymin, ymax, zmin, zmax);
//}
//
//// -------------------------------------------------------------------------------------------------
//// -------------------------------------------------------------------------------------------------
//void cRenderSphereAtt::create_array(cAppGauge *gauge)
//{
//  if(m_vertex)  delete[] m_vertex;
//  if(m_color)   delete[] m_color;
//  if(m_normal)  delete[] m_normal;
//  if(m_index)   delete[] m_index;
//
//  m_pick = NULL;
//
//  m_vertex = new GLfloat[3 * m_num_vertex];
//  m_color  = new GLfloat[3 * m_num_vertex];
//  m_normal = new GLfloat[3 * m_num_vertex];
//
//  for(int i = 0, j = 0; i < m_num_vertex; i++)
//  {
//    j = 3 * i;
//    m_vertex[j]   = (GLfloat) vecVertex[i].v.x;
//    m_vertex[j+1] = (GLfloat) vecVertex[i].v.y;
//    m_vertex[j+2] = (GLfloat) vecVertex[i].v.z;
//
//    m_normal[j]   = (GLfloat) vecVertex[i].normal.x;
//    m_normal[j+1] = (GLfloat) vecVertex[i].normal.y;
//    m_normal[j+2] = (GLfloat) vecVertex[i].normal.z;
//
//    m_color[j]    = (GLfloat) s_color[0];
//    m_color[j+1]  = (GLfloat) s_color[1];
//    m_color[j+2]  = (GLfloat) s_color[2];
//
//    //if(gauge)
//    //  gauge->update();
//  }
//
//  m_index  = new GLuint[3 * m_num_geometries];
//  for(int i = 0, j = 0; i < m_num_geometries; i++)
//  {
//    j = 3 * i;
//    m_index[j]   = vecTria[i].v1;
//    m_index[j+1] = vecTria[i].v2;
//    m_index[j+2] = vecTria[i].v3;
//
//    //if(gauge)
//    //  gauge->update();
//  }
//
//  //vecTria.clear();
//  //vecVertex.clear();
//}
//
//// -------------------------------------------------------------------------------------------------
//// -------------------------------------------------------------------------------------------------
//bool cRenderSphereAtt::check_pick(const int &id, 
//                                const AlgVector &ray_ori, 
//                                const AlgVector &ray_dest, 
//                                AlgVector *point)
//{
//  return false;
//}