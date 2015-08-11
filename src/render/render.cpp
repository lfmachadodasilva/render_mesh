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

#include "shader.h"
#include "render.h"

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
cRender::cRender(void) : 
  m_geometry_type(TRIANGLE), 
  m_frustum_culler(NULL), m_scene_root(NULL),
  m_vertex(NULL), m_index(NULL), m_normal(NULL), m_color(NULL),
  m_vao_id(0), m_ibo_id(0), m_vbo_id(0),
  m_render_texture(false), m_render_wireframe(false),
  m_texture(NULL) 
{
  
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
cRender::~cRender(void)
{
  m_free_buffer();
  m_free_mesh();
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cRender::m_free_mesh(void)
{
  if(m_vertex) 
    delete[] m_vertex;
  if(m_index) 
    delete[] m_index;
  if(m_normal) 
    delete[] m_normal;
  if(m_color) 
    delete[] m_color;

  m_vertex = NULL;
  m_index = NULL;
  m_normal = NULL;
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cRender::m_free_buffer(void)
{
	if(cRender::m_new_render)
	{
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		if(m_vao_id > 0)
			glDeleteVertexArrays(1, &m_vao_id);
		if(m_ibo_id > 0)
			glDeleteBuffers(1, &m_ibo_id);
		if(m_vbo_id > 0)
			glDeleteBuffers(1, &m_vbo_id);
	}

  m_vao_id = 0;
  m_ibo_id = 0;
  m_vbo_id = 0;
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
bool cRender::create_vao_shader(const cShader *shader)
{
  if(!cRender::m_new_render)
    return false;

  if(!shader || !m_vertex || !m_normal || !m_color)
    return false;

  int size = 0, size_tex = 0;

  // index buffer index
  size = m_geometry_type * m_num_geometries * sizeof(GLuint);
  glGenBuffers(1, &m_ibo_id);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo_id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, m_index, GL_DYNAMIC_DRAW);
  // end of index buffer index

  GLenum error = glGetError();
  if(error != GL_NO_ERROR)
    printf("Error %s - %d\n" __FILE__, __LINE__);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  // vertex buffer object
  size = 3 * m_num_vertex * sizeof(GLfloat);
  glGenBuffers(1, &m_vbo_id);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id);
  glBufferData(GL_ARRAY_BUFFER, (4 * size) + size_tex, 0, GL_DYNAMIC_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER, 0, size, m_vertex);
  glBufferSubData(GL_ARRAY_BUFFER, size, size, m_normal);
  // to render with texture is not necessary add color data
  if(m_render_texture)
  {
    size_tex = 2 * m_num_vertex * sizeof(GLfloat);
    glBufferSubData(GL_ARRAY_BUFFER, 2 * size, size_tex, m_texture_coord);
  }
  else
  {
    glBufferSubData(GL_ARRAY_BUFFER, 2 * size, size, m_color);
  }
  // end of vertex buffer object

  error = glGetError();
  if(error != GL_NO_ERROR)
    printf("Error %s - %d\n" __FILE__, __LINE__);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // vertex array object
  glGenVertexArrays(1, &m_vao_id);

  m_vec_vao_id.push_back(m_vao_id);

  glBindVertexArray(m_vao_id);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id);
  glVertexAttribPointer(shader->m_in_vertex_loc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glVertexAttribPointer(shader->m_in_normal_loc, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid *) (size));
  // to render with texture is not necessary add color data
  if(m_render_texture)
    glVertexAttribPointer(shader->m_in_texture_coord_loc, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid *) (2 * size));
  else
    glVertexAttribPointer(shader->m_in_color_loc, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid *) (2 * size));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo_id);

  error = glGetError();
  if(error != GL_NO_ERROR)
    printf("Error %s - %d\n" __FILE__, __LINE__);

  // Enable attributes
  glEnableVertexAttribArray(shader->m_in_vertex_loc);
  glEnableVertexAttribArray(shader->m_in_normal_loc);
  if(m_render_texture)
    glEnableVertexAttribArray(shader->m_in_texture_coord_loc);
  else 
  {
    glEnableVertexAttribArray(shader->m_in_color_loc);
  }
  // end of vertex array object

  // disable
  glBindVertexArray(0);
  glDisableVertexAttribArray(shader->m_in_vertex_loc);
  glDisableVertexAttribArray(shader->m_in_normal_loc);
  glDisableVertexAttribArray(shader->m_in_color_loc);
  glDisableVertexAttribArray(shader->m_in_texture_coord_loc);
  //glDisableVertexAttribArray(shader->m_in_pick_loc);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  return true;
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
bool cRender::create_vao_shader2(const cShader *shader)
{
  if(!cRender::m_new_render)
    return false;

  if(!shader || !m_vertex || !m_normal || !m_color)
    return false;

  int size = 0, size_tex = 0;

  //// index buffer index
  size = m_geometry_type * m_num_geometries * sizeof(GLuint);
  //glGenBuffers(1, &m_ibo_id);
  //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo_id);
  //glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, m_index, GL_DYNAMIC_DRAW);
  //// end of index buffer index
  //
  //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  //
  //// vertex buffer object
  size = 3 * m_num_vertex * sizeof(GLfloat);
  //glGenBuffers(1, &m_vbo_id);
  //glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id);
  //glBufferData(GL_ARRAY_BUFFER, (4 * size) + size_tex, 0, GL_DYNAMIC_DRAW);
  //glBufferSubData(GL_ARRAY_BUFFER, 0, size, m_vertex);
  //glBufferSubData(GL_ARRAY_BUFFER, size, size, m_normal);
  //// to render with texture is not necessary add color data
  //if(m_render_texture)
  //{
  //  size_tex = 2 * m_num_vertex * sizeof(GLfloat);
  //  glBufferSubData(GL_ARRAY_BUFFER, 2 * size, size_tex, m_texture_coord);
  //}
  //else
  //{
  //  glBufferSubData(GL_ARRAY_BUFFER, 2 * size, size, m_color);
  //}
  //// end of vertex buffer object

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // vertex array object
  glGenVertexArrays(1, &m_vao_id);

  m_vec_vao_id.push_back(m_vao_id);

  glBindVertexArray(m_vao_id);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id);
  glVertexAttribPointer(shader->m_in_vertex_loc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glVertexAttribPointer(shader->m_in_normal_loc, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid *) (size));
  // to render with texture is not necessary add color data
  if(m_render_texture)
    glVertexAttribPointer(shader->m_in_texture_coord_loc, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid *) (2 * size));
  else
  {
    glVertexAttribPointer(shader->m_in_color_loc, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid *) (2 * size));
  }

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo_id);

  // Enable attributes
  glEnableVertexAttribArray(shader->m_in_vertex_loc);
  glEnableVertexAttribArray(shader->m_in_normal_loc);
  if(m_render_texture)
    glEnableVertexAttribArray(shader->m_in_texture_coord_loc);
  else 
  {
    glEnableVertexAttribArray(shader->m_in_color_loc);
  }
  // end of vertex array object

  // disable
  glBindVertexArray(0);
  glDisableVertexAttribArray(shader->m_in_vertex_loc);
  glDisableVertexAttribArray(shader->m_in_normal_loc);
  glDisableVertexAttribArray(shader->m_in_color_loc);
  glDisableVertexAttribArray(shader->m_in_texture_coord_loc);
  //glDisableVertexAttribArray(shader->m_in_pick_loc);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  return true;
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
sBox cRender::get_transform_bbox(void)
{
  sBox bbox;
  bbox.reset();

  AlgVector p;

  p = m_transformation_matrix.Transform(m_bbox.min.x, m_bbox.min.y, m_bbox.min.z);
  bbox.min.x = std::min(bbox.min.x, p.x);
  bbox.min.y = std::min(bbox.min.y, p.y);
  bbox.min.z = std::min(bbox.min.z, p.z);

  p = m_transformation_matrix.Transform(m_bbox.max.x, m_bbox.max.y, m_bbox.max.z);
  bbox.max.x = std::max(bbox.max.x, p.x);
  bbox.max.y = std::max(bbox.max.y, p.y);
  bbox.max.z = std::max(bbox.max.z, p.z);

  //for(int i = 0; i < m_num_vertex; i++)
  //{
  //  j = 3 * i;
  //
  //   p = m_transformation_matrix.Transform(m_vertex[j], m_vertex[j+1], m_vertex[j+2]);
  //
  //   bbox.min.x = std::min(bbox.min.x, p.x);
  //   bbox.min.y = std::min(bbox.min.y, p.y);
  //   bbox.min.z = std::min(bbox.min.z, p.z);
  //
  //   bbox.max.x = std::max(bbox.max.x, p.x);
  //   bbox.max.y = std::max(bbox.max.y, p.y);
  //   bbox.max.z = std::max(bbox.max.z, p.z);
  //}

  return bbox;
}