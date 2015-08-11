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

#include "appearance.h"
#include "shader.h"
#include "render-att.h"
#include "render-pick.h"
#include "texture.h"

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
cRenderPick::cRenderPick(eObjectType type) : cRender(), cPick(type)  
{
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cRenderPick::operator=(const cRenderPick &render)
{
  m_vao_id = render.m_vao_id;
  m_ibo_id = render.m_ibo_id;
  m_vbo_id = render.m_vbo_id;

  for(int i = 0, j = 0; i < m_num_vertex; i++)
  {
    j = 3 * i;

    m_vertex[j + 0] = render.m_vertex[j + 0];
    m_vertex[j + 1] = render.m_vertex[j + 1];
    m_vertex[j + 2] = render.m_vertex[j + 2];

    m_normal[j + 0] = render.m_normal[j + 0];
    m_normal[j + 1] = render.m_normal[j + 1];
    m_normal[j + 2] = render.m_normal[j + 2];

    m_color[j + 0] = render.m_color[j + 0];
    m_color[j + 1] = render.m_color[j + 1];
    m_color[j + 2] = render.m_color[j + 2];
  }

  for(int i = 0, j = 0; i < m_num_geometries; i++)
  {
    j = 3 * i;

    m_index[i + 0] = render.m_index[i + 0];
    m_index[i + 1] = render.m_index[i + 1];
    m_index[i + 2] = render.m_index[i + 2];
  }

  this->create_scene();
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cRenderPick::render(const cShader* shader, const cRenderAtt *render_att)
{
  if(cRender::m_new_render)
    cRenderPick::render_shader(shader, render_att);
  else
    cRenderPick::render_old(render_att);
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cRenderPick::render_shader(const cShader* shader, const cRenderAtt *render_att)
{
#ifdef _DEBUG
  GLenum glerror = glGetError();
  if(glerror != GL_NO_ERROR)
    printf("File: %s, Line: %d - ERROR: OpenGL error %x render_shader start.\n", __FILE__, __LINE__, glerror);
#endif

  if(!shader)
    return;

  glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT | GL_POLYGON_BIT | GL_LIGHTING_BIT);

  if(m_render_wireframe)
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  // copy model view matrix and accumulate object transformation
  AlgMatrix mvt(render_att->m_model_view_matrix);
  mvt.Accum(m_transformation_matrix); // model view matrix with transformation
  AlgMatrix mvtn (mvt);
  mvtn.PrepareScaleToTransformNormals(); // normal matrix

  // send to shader
  glUniformMatrix4fv(shader->m_model_view_transf_matrix_loc, 1, GL_FALSE, mvt.GetMatrix());
  glUniformMatrix4fv(shader->m_projection_matrix_loc, 1, GL_FALSE, render_att->m_projection_matrix.GetMatrix());
  glUniformMatrix4fv(shader->m_normal_matrix_loc, 1, GL_FALSE, mvtn.GetMatrix());

  glUniform1i(shader->m_render_texture_loc, (GLint) m_render_texture);

  if(cPick::m_pick_type == cPick::PICK_BY_OBJECT)
  {
    if(cPick::is_focus() || cPick::is_selected())
      glUniform1i(shader->m_is_selected_object, (GLint) true);
    else
      glUniform1i(shader->m_is_selected_object, (GLint) false);

    glUniform1i(shader->m_focus_id_loc, (GLint) cPick::get_focus());
  }
  else if(cPick::m_pick_type == cPick::PICK_BY_ELEMET)
  {
    glUniform1i(shader->m_is_selected_object, (GLint) false);
    glUniform1i(shader->m_focus_id_loc, (GLint) cPick::get_focus());

    glUniform1iv(shader->m_select_array_ids_loc, 50, cPick::m_vec_selec);
  }
  else
    glUniform1i(shader->m_is_selected_object, (GLint) false);

  if(m_render_texture)
  {
    glUniform1i(shader->m_texture_loc, 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture_id);
  }

  // bind vertex array object
  glBindVertexArray(m_vao_id);

  if(m_geometry_type == cRender::TRIANGLE)
    glDrawRangeElements(GL_TRIANGLES, 0, 3 * m_num_vertex, cRender::TRIANGLE * m_num_geometries, GL_UNSIGNED_INT, NULL);
  else if(m_geometry_type == cRender::LINE)
    glDrawRangeElements(GL_LINES, 0, 3 * m_num_vertex, cRender::LINE * m_num_geometries, GL_UNSIGNED_INT, NULL);
  else if(m_geometry_type == cRender::POINT)
  {
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    glDrawRangeElements(GL_POINTS, 0, 3 * m_num_vertex, m_num_geometries, GL_UNSIGNED_INT, NULL);
    glDisable(GL_VERTEX_PROGRAM_POINT_SIZE);
  }

  // remove bind for vertex array object
  glBindVertexArray(0);

  if(m_render_texture)
  {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
  }

  glPopAttrib();

#ifdef _DEBUG
  glerror = glGetError();
  if(glerror != GL_NO_ERROR)
    printf("File: %s, Line: %d - ERROR: OpenGL error %x on render_shader end. %s\n", 
    __FILE__, __LINE__, glerror, gluErrorString(glerror));
#endif
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cRenderPick::render_old(const cRenderAtt *render_att)
{
#ifdef _DEBUG
  GLenum glerror = glGetError();
  if(glerror != GL_NO_ERROR)
    printf("File: %s, Line: %d - ERROR: OpenGL error %x render_old start.\n", __FILE__, __LINE__, glerror);
#endif
 
  glPushAttrib(GL_POLYGON_BIT | GL_LIGHTING_BIT);

  if(m_render_wireframe)
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  //glMatrixMode(GL_MODELVIEW);
  //glLoadIdentity();
  //
  //glLoadMatrixf(render_att->m_model_view_matrix);

  cAppearance app;
  app.set_color(&m_color[0]);

  glEnable(GL_LIGHTING);
  glEnable(GL_NORMALIZE);

  if(m_render_texture && m_texture)
  {
    m_texture->load();
    app.load(cAppearance::TEXTURE);
  }
  else
  {
    if(cPick::m_pick_type == cPick::PICK_BY_OBJECT)
    {
      if(cPick::is_focus() || cPick::is_selected())
        app.load(cAppearance::PICK);
      else
        app.load(cAppearance::COLOR);
    }
    else
      app.load(cAppearance::COLOR);
  }

  if(m_render_texture && m_texture)
  {
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glTexCoordPointer(2, GL_FLOAT, 0, m_texture_coord);

    glNormalPointer(GL_FLOAT, 0, m_normal);
    glVertexPointer(3, GL_FLOAT, 0, m_vertex);
    glDrawElements(GL_TRIANGLES, 3 * m_num_geometries, GL_UNSIGNED_INT, m_index);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  }
  else
  {
    for(int i = 0, j = 0, k = 0; i < m_num_geometries; i++)
    {
      if(!m_render_texture && cPick::m_pick_type == cPick::PICK_BY_ELEMET)
      {
        if(cPick::is_focus() && i == cPick::get_focus())
        {
          app.load(cAppearance::PICK);
        }
        else if(cPick::is_selected())
        {
          set<int> s = cPick::get_selected();
          if(s.find(i) == s.end())
            app.load(cAppearance::COLOR);
          else
            app.load(cAppearance::PICK);
        }
        else 
          app.load(cAppearance::COLOR);
      }


      if(m_geometry_type == cRender::TRIANGLE)
      {
        j = 3 * i;

        int v1 = m_index[j + 0] * 3;
        int v2 = m_index[j + 1] * 3;
        int v3 = m_index[j + 2] * 3;

        glBegin(GL_TRIANGLES);
        {
          glNormal3fv(&m_normal[v1]);
          glVertex3fv(&m_vertex[v1]);

          glNormal3fv(&m_normal[v2]);
          glVertex3fv(&m_vertex[v2]);

          glNormal3fv(&m_normal[v3]);
          glVertex3fv(&m_vertex[v3]);
        }
        glEnd();
      }
      else
      {
        glPointSize(5);

        glBegin(GL_POINTS);
        {
          glVertex3fv(&m_vertex[i * 3]);
        }
        glEnd();
      }
    }
  }

  if(m_render_texture && m_texture) m_texture->unload();

  glPopAttrib();

#ifdef _DEBUG
  glerror = glGetError();
  if(glerror != GL_NO_ERROR)
    printf("File: %s, Line: %d - ERROR: OpenGL error %x on render_old end. %s\n", 
    __FILE__, __LINE__, glerror, gluErrorString(glerror));
#endif
}