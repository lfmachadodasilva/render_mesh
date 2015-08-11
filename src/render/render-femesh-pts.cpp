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

#include "render-femesh-pts.h"

static GLfloat s_color[3] = { 0.2f, 0.2f, 0.8f };

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
cRenderFeMeshPts::cRenderFeMeshPts(GLfloat *vertex, int &size, AlgMatrix &transf_matrix) : 
   cRenderPick(cRenderPick::NONE)
{
  m_geometry_type = cRender::POINT;
  m_transformation_matrix = transf_matrix;
  v_cpy = vertex;
  m_num_vertex = size;
  m_num_geometries = size;

  this->create();

  this->calc_normals(NULL);

  this->create_array(NULL);
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cRenderFeMeshPts::create(void)
{
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cRenderFeMeshPts::calc_normals(cAppGauge *gauge)
{
 
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cRenderFeMeshPts::create_array(cAppGauge *gauge)
{
  if(m_vertex)  delete[] m_vertex;
  if(m_color)   delete[] m_color;
  if(m_normal)  delete[] m_normal;
  if(m_index)   delete[] m_index;

  m_vertex = new GLfloat[3 * m_num_vertex];
  m_normal = new GLfloat[3 * m_num_vertex];
  m_color  = new GLfloat[3 * m_num_vertex];
  m_index  = new GLuint[m_num_vertex];
  for(int i = 0, j = 0; i < m_num_vertex; i++)
  {
    j = 3 * i;

    m_vertex[j + 0] = v_cpy[j + 0];
    m_vertex[j + 1] = v_cpy[j + 1];
    m_vertex[j + 2] = v_cpy[j + 2];

    m_normal[j + 0] = 1.0f;//v_cpy[j];
    m_normal[j + 1] = 1.0f;//v_cpy[j];
    m_normal[j + 2] = 1.0f;//v_cpy[j];

    m_color[j + 0] = 0.0f;//v_cpy[j];
    m_color[j + 1] = 0.0f;//v_cpy[j];
    m_color[j + 2] = 0.0f;//v_cpy[j];

    m_index[i] = i;
  }

  v_cpy = NULL;
}