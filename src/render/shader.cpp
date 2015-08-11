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

#include <string>
using std::string;

// Opengl
#include "GL\glew.h"

// Lib vis
#include "alg\matrix.h"

#include "Cg\cgGL.h"

// local
#include "shader.h"

static char* filetobuf(const char *file);

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
cShader::cShader(void)
{
  m_program_id    = 0;

  m_in_vertex_loc = 0;
  m_in_color_loc  = 0;
  m_in_normal_loc = 0;

  m_vertex_id   = 0;
  m_fragment_id = 0;

  m_vertex_source = NULL;
  m_fragment_source = NULL;
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
cShader::~cShader(void)
{
  m_free();
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cShader::m_free(void)
{
  glDisableVertexAttribArray(m_in_vertex_loc);
  glDisableVertexAttribArray(m_in_color_loc);
  glDisableVertexAttribArray(m_in_normal_loc);

  glUseProgram(0);

  //if(m_program_id > 0)
  {
    glDetachShader(m_program_id, m_vertex_id);
    glDetachShader(m_program_id, m_fragment_id);

    glDeleteShader(m_vertex_id);
    glDeleteShader(m_fragment_id);

    glDeleteProgram(m_program_id);

    if(m_vertex_source)   delete m_vertex_source;
    if(m_fragment_source) delete m_fragment_source;
  }

  m_program_id    = 0;

  m_in_vertex_loc = 0;
  m_in_color_loc  = 0;
  m_in_normal_loc = 0;

  m_vertex_id   = 0;
  m_fragment_id = 0;

  m_vertex_source = NULL;
  m_fragment_source = NULL;
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
bool cShader::create(void)
{
  int max_length;
  
  /* Vertex shader */ 
  //m_vertex_source = filetobuf(string(str + "vert").c_str());
  m_vertex_source = filetobuf("..\\models\\vertex.vert");
  m_vertex_id = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(m_vertex_id, 1, (const GLchar**)&m_vertex_source, 0);
  glCompileShader(m_vertex_id);
  {
    // check if compile
    char *shader_info_log;
    GLint is_compiled_shader;
    glGetShaderiv(m_vertex_id, GL_COMPILE_STATUS, &is_compiled_shader);
    if(!is_compiled_shader)
    {
      glGetShaderiv(m_vertex_id, GL_INFO_LOG_LENGTH, &max_length);
      shader_info_log = (char *)malloc(max_length);
      glGetShaderInfoLog(m_vertex_id, max_length, &max_length, shader_info_log);
      printf("\nShader error: %s\t%d\t%s\n", __FILE__, __LINE__, shader_info_log);
      free(shader_info_log);

      m_free();

      return false;
    }
  }
  /* End of Vertex shader */

  /* Fragment shader */ 
  //m_fragment_source = filetobuf(string(str + "frag").c_str());
  m_fragment_source = filetobuf(string("..\\models\\fragment.frag").c_str());
  m_fragment_id = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(m_fragment_id, 1, (const GLchar**)&m_fragment_source, 0);
  glCompileShader(m_fragment_id);

  {
    char *fragment_info_log;
    GLint is_compiled_fragment;
    glGetShaderiv(m_fragment_id, GL_COMPILE_STATUS, &is_compiled_fragment);
    if(!is_compiled_fragment)
    {
      glGetShaderiv(m_fragment_id, GL_INFO_LOG_LENGTH, &max_length);
      fragment_info_log = (char *)malloc(max_length);
      glGetShaderInfoLog(m_fragment_id, max_length, &max_length, fragment_info_log);
      printf("\nShader error: %s\t%d\t%s\n", __FILE__, __LINE__, fragment_info_log);
      free(fragment_info_log);
      
      m_free();

      return false;
    }
  }
  /* End of Fragment shader */ 

  m_program_id = glCreateProgram();
  glAttachShader(m_program_id, m_vertex_id);
  glAttachShader(m_program_id, m_fragment_id);

  // Need to do before glLinkProgram
  glBindAttribLocation(m_program_id, 0, "inVertex");
  glBindAttribLocation(m_program_id, 1, "inTextureCoord");
  glBindAttribLocation(m_program_id, 2, "inNormal");
  glBindAttribLocation(m_program_id, 3, "inColor");
  glBindAttribLocation(m_program_id, 4, "inPick");
  
  glLinkProgram(m_program_id);
  {
    char *program_info_log;
    GLint is_linked;
    glGetProgramiv(m_program_id, GL_LINK_STATUS, (int *)&is_linked);
    if(!is_linked)
    {
      glGetProgramiv(m_program_id, GL_INFO_LOG_LENGTH, &max_length);
      program_info_log = (char *) malloc (max_length);
      glGetProgramInfoLog(m_program_id, max_length, &max_length, program_info_log);
      printf("\nShader error: %s\t%d\t%s\n", __FILE__, __LINE__, program_info_log);
      free(program_info_log);
    
      m_free();

      return false;
    }
  }

  // shader attributes - layout(location = %d) in TYPE NAME
  m_in_vertex_loc        = glGetAttribLocation(m_program_id, "inVertex");
  m_in_normal_loc        = glGetAttribLocation(m_program_id, "inNormal");
  m_in_color_loc         = glGetAttribLocation(m_program_id, "inColor");
  m_in_texture_coord_loc = glGetAttribLocation(m_program_id, "inTextureCoord");

  m_select_array_ids_loc = glGetUniformLocation(m_program_id, "select_array_ids");
  m_focus_id_loc = glGetUniformLocation(m_program_id, "focus_id");

  m_texture_loc = glGetUniformLocation(m_program_id, "inTexture");

  m_render_texture_loc = glGetUniformLocation(m_program_id, "render_texture");

  m_model_view_matrix_loc = glGetUniformLocation(m_program_id, "model_view_matrix");
  m_model_view_transf_matrix_loc = glGetUniformLocation(m_program_id, "model_view_transf_matrix");
  m_projection_matrix_loc = glGetUniformLocation(m_program_id, "projection_matrix");
  m_normal_matrix_loc     = glGetUniformLocation(m_program_id, "normal_matrix");

  m_light_position_loc = glGetUniformLocation(m_program_id, "light_position");
  m_ambient_light_loc  = glGetUniformLocation(m_program_id, "ambient_light");
  m_diffuse_light_loc  = glGetUniformLocation(m_program_id, "diffuse_light");
  m_specular_light_loc = glGetUniformLocation(m_program_id, "specular_light");

  m_is_selected_object = glGetUniformLocation(m_program_id, "is_selected_object");

  glBindVertexArray(0);
  glUseProgram(0);

  return true;
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cShader::load(const cRenderAtt &render_att)
{
  glUseProgram(m_program_id);

  glUniform3fv(m_light_position_loc, 1, render_att.m_light_att.m_position_light);
  glUniform4fv(m_ambient_light_loc,  1, render_att.m_light_att.m_ambient_light);
  glUniform4fv(m_diffuse_light_loc,  1, render_att.m_light_att.m_diffuse_light);
  glUniform4fv(m_specular_light_loc, 1, render_att.m_light_att.m_specular_light);
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cShader::unload(void)
{
  glUseProgram(0);
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
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