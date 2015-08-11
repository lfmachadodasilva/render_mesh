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

#include "render-quad-att.h"

static GLfloat s_color[3] = { 0.2f, 0.2f, 0.8f };

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
cRenderQuadAtt::cRenderQuadAtt(void) : 
   cRenderPick(cRenderPick::QUAD),
   m_height(1.0), 
   m_width(1.0), 
   m_lenght(1.0)
{
  m_transformation_matrix.Identity();

  m_num_geometries = 6 /*squares*/ * 2 /*triangles per square*/;
  m_num_vertex = 8;

  this->create();

  this->calc_normals(NULL);

  this->create_array(NULL);
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
cRenderQuadAtt::cRenderQuadAtt(float height, float width, float lenght) : 
  cRenderPick(cRenderPick::QUAD),
  m_height(height), 
  m_width(width), 
  m_lenght(lenght)
{
  m_transformation_matrix.Identity();

  m_num_geometries = 6 /*squares*/ * 2 /*triangles per square*/;
  m_num_vertex = 8;   

  this->create();

  this->calc_normals(NULL);

  this->create_array(NULL);
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cRenderQuadAtt::create(void)
{
  sVertex vertex;

  // 0
  vertex.v.x = m_lenght / 2;
  vertex.v.y = -m_width / 2;
  vertex.v.z = -m_height / 2;
  vecVertex.push_back(vertex);

  // 1
  vertex.v.x = m_lenght / 2;
  vertex.v.y = m_width / 2;
  vertex.v.z = -m_height / 2;
  vecVertex.push_back(vertex);

  // 2
  vertex.v.x = m_lenght / 2;
  vertex.v.y = m_width / 2;
  vertex.v.z = m_height / 2;
  vecVertex.push_back(vertex);

  // 3
  vertex.v.x = m_lenght / 2;
  vertex.v.y = -m_width / 2;
  vertex.v.z = m_height / 2;
  vecVertex.push_back(vertex);

  // 4
  vertex.v.x = -m_lenght / 2;
  vertex.v.y = -m_width / 2;
  vertex.v.z = -m_height / 2;
  vecVertex.push_back(vertex);

  // 5
  vertex.v.x = -m_lenght / 2;
  vertex.v.y = m_width / 2;
  vertex.v.z = -m_height / 2;
  vecVertex.push_back(vertex);

  // 6
  vertex.v.x = -m_lenght / 2;
  vertex.v.y = m_width / 2;
  vertex.v.z = m_height / 2;
  vecVertex.push_back(vertex);

  // 3
  vertex.v.x = -m_lenght / 2;
  vertex.v.y = -m_width / 2;
  vertex.v.z = m_height / 2;
  vecVertex.push_back(vertex);

  sFace3v tri;

  // 0
  tri.v1 = 0;
  tri.v2 = 1;
  tri.v3 = 2;
  vecTria.push_back(tri);
  tri.v1 = 2;
  tri.v2 = 3;
  tri.v3 = 0;
  vecTria.push_back(tri);

  // 1
  tri.v1 = 1;
  tri.v2 = 5;
  tri.v3 = 6;
  vecTria.push_back(tri);
  tri.v1 = 6;
  tri.v2 = 2;
  tri.v3 = 1;
  vecTria.push_back(tri);

  // 2
  tri.v1 = 5;
  tri.v2 = 4;
  tri.v3 = 7;
  vecTria.push_back(tri);
  tri.v1 = 7;
  tri.v2 = 6;
  tri.v3 = 5;
  vecTria.push_back(tri);

  // 3
  tri.v1 = 4;
  tri.v2 = 0;
  tri.v3 = 3;
  vecTria.push_back(tri);
  tri.v1 = 3;
  tri.v2 = 7;
  tri.v3 = 4;
  vecTria.push_back(tri);

  // 4
  tri.v1 = 3;
  tri.v2 = 2;
  tri.v3 = 6;
  vecTria.push_back(tri);
  tri.v1 = 6;
  tri.v2 = 7;
  tri.v3 = 3;
  vecTria.push_back(tri);

  // 5
  tri.v1 = 1;
  tri.v2 = 0;
  tri.v3 = 4;
  vecTria.push_back(tri);
  tri.v1 = 4;
  tri.v2 = 5;
  tri.v3 = 1;
  vecTria.push_back(tri);
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cRenderQuadAtt::calc_normals(cAppGauge *gauge)
{
  for(int i = 0; i < (int)vecVertex.size(); i++)
    vecVertex[i].normal = AlgVector(0.0f, 0.0f, 0.0f);

  if(m_geometry_type == cRenderPick::LINE)
    return;

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

    //if(gauge)
    //  gauge->update();
  }

  m_bbox = sBox(xmin, xmax, ymin, ymax, zmin, zmax);
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cRenderQuadAtt::create_array(cAppGauge *gauge)
{
  if(m_vertex)  delete[] m_vertex;
  if(m_color)   delete[] m_color;
  if(m_normal)  delete[] m_normal;
  if(m_index)   delete[] m_index;

  m_vertex = new GLfloat[3 * m_num_vertex];
  m_color  = new GLfloat[3 * m_num_vertex];
  m_normal = new GLfloat[3 * m_num_vertex];

  for(int i = 0, j = 0; i < m_num_vertex; i++)
  {
    j = 3 * i;
    m_vertex[j]   = (GLfloat) vecVertex[i].v.x;
    m_vertex[j+1] = (GLfloat) vecVertex[i].v.y;
    m_vertex[j+2] = (GLfloat) vecVertex[i].v.z;

    m_normal[j]   = (GLfloat) vecVertex[i].normal.x;
    m_normal[j+1] = (GLfloat) vecVertex[i].normal.y;
    m_normal[j+2] = (GLfloat) vecVertex[i].normal.z;

    m_color[j]    = (GLfloat) s_color[0];
    m_color[j+1]  = (GLfloat) s_color[1];
    m_color[j+2]  = (GLfloat) s_color[2];

    //if(gauge)
    //  gauge->update();
  }

  m_index  = new GLuint[3 * m_num_geometries];
  for(int i = 0, j = 0; i < m_num_geometries; i++)
  {
    j = 3 * i;
    m_index[j]   = vecTria[i].v1;
    m_index[j+1] = vecTria[i].v2;
    m_index[j+2] = vecTria[i].v3;

    //if(gauge)
    //  gauge->update();
  }

  vecTria.clear();
  vecVertex.clear();
}