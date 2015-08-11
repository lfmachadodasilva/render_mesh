// ------------------------------------------------------------------------------------------------- 
// Anflex Project -- Tecgraf/PUC-Rio  CENPES/Petrobras 
// www.tecgraf.puc-rio.br 
// 
// Created by lfmachado in November/2011.
// 
// $URL: $ 
// $Revision: $ 
// $Date: $ 
// 
// $LastChangedBy: $ 
// -------------------------------------------------------------------------------------------------

#ifndef ANFLEX_INTERFACE_SHADER_H
#define ANFLEX_INTERFACE_SHADER_H

#include "util.h"

class cShader
{
public:

  // matrix shader location
  GLuint m_model_view_matrix_loc, 
         m_model_view_transf_matrix_loc,
         m_normal_matrix_loc, 
         m_projection_matrix_loc;
  // end of matrix shader location

  GLuint m_color_loc;

  // light color shader location
  GLuint m_light_position_loc, 
         m_ambient_light_loc, 
         m_diffuse_light_loc, 
         m_specular_light_loc;
  // end of light color shader location

  GLuint m_render_texture_loc;

  GLuint m_has_pick_loc;

  // vertex and normal shader location
  GLuint m_in_vertex_loc, m_in_color_loc, m_in_normal_loc, m_texture_loc, m_in_texture_coord_loc;
  // end of vertex and normal shader location

  GLuint m_program_id, m_vertex_id, m_fragment_id;

  char *m_vertex_source, *m_fragment_source;

  void m_free(void);

public:
  cShader(void);
  ~cShader(void);

  bool create(void);

  void load(const sRenderAtt &render_att);
  void unload(void);
};

#endif