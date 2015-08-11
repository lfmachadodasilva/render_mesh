//--------------------------------------------------------------------------------------------------
// Anflex Project -- Tecgraf/PUC-Rio CENPES/Petrobras
// www.tecgraf.puc-rio.br
//
// Created by lduarte in September/2010.
//
// $URL: $
// $Revision: $
// $Date: $
//
// $LastChangedBy:  $
//--------------------------------------------------------------------------------------------------

#include <math.h>

#include "appearance.h"
//#include "util.h"

static const float color_white [] = { 1.0f, 1.0f, 1.0f, 1.0f };
static const float color_black [] = { 0.0f, 0.0f, 0.0f, 0.4f };
#define TOL_ZERO  1.0e-08

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
cAppearance::cAppearance()
{
  m_face = GL_FRONT_AND_BACK;

  int i;
  for(i = 0; i < 3; ++i)
  {
    m_color[i] = 0.0f;
    m_ambient[i] = 0.0f;
    m_pick_ambient[i] = 1.0f;

    m_diffuse[i] = 0.0f;
    m_pick_diffuse[i] = 1.0f;

    m_specular[i] = 0.0f;
    m_pick_specular[i] = 1.0f;
  }

  m_color[3] = 1.0f;
  m_ambient[3] = 1.0f;
  m_diffuse[3] = 1.0f;
  m_specular[3] = 1.0f;

  m_pick_ambient[3] = 1.0f;
  m_pick_diffuse[3] = 1.0f;
  m_pick_specular[3] = 1.0f;

  m_shininess = 20.0f;
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
cAppearance::cAppearance(GLenum face, GLfloat *color)
{
  m_face = face;

  int i;
  for(i = 0; i < 3; ++i)
  {
    m_color[i] = color[i];
    m_ambient[i] = 0.6f * color[i];
    m_pick_ambient[i] = 0.6f * color[i];

    m_diffuse[i] = 0.9f * color[i];
    m_pick_diffuse[i] = 0.9f * color[i];

    m_specular[i] = 0.7f * color[i];
    m_pick_specular[i] = 0.7f * color[i];
  }

  m_color[3] = color[3];
  m_ambient[3] = color[3];
  m_diffuse[3] = color[3];
  m_specular[3] = color[3];

  m_pick_ambient[3] = color[3];
  m_pick_diffuse[3] = color[3];
  m_pick_specular[3] = color[3];

  m_shininess = 20.0f;

  //generate_select_color(m_pick_ambient[0], m_pick_ambient[1], m_pick_ambient[2]);
  //generate_select_color(m_pick_diffuse[0], m_pick_diffuse[1], m_pick_diffuse[2]);
  //generate_select_color(m_pick_specular[0], m_pick_specular[1], m_pick_specular[2]);
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void cAppearance::operator=(const cAppearance &obj)
{
  m_face = obj.m_face;

  for(int i = 0; i < 4; ++i)
  {
    m_color[i] = obj.m_color[i];

    m_ambient[i] = obj.m_ambient[i];
    m_diffuse[i] = obj.m_diffuse[i];
    m_specular[i] = obj.m_specular[i];

    m_pick_ambient[i] = obj.m_pick_ambient[i];
    m_pick_diffuse[i] = obj.m_pick_diffuse[i];
    m_pick_specular[i] = obj.m_pick_specular[i];
  }
  
  m_shininess = obj.m_shininess;
  m_pick_shininess = obj.m_pick_shininess;
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
bool cAppearance::operator==(const cAppearance &obj) const
{
  if(m_face != obj.m_face)
    return false;

  for(int i = 0; i < 4; ++i)
  {
    if(fabs(m_color[i] - obj.m_color[i]) > TOL_ZERO)
      return false;

    if(fabs(m_ambient[i] - obj.m_ambient[i]) > TOL_ZERO)
      return false;
    if(fabs(m_diffuse[i] - obj.m_diffuse[i]) > TOL_ZERO)
      return false;
    if(fabs(m_specular[i] - obj.m_specular[i]) > TOL_ZERO)
      return false;

    if(fabs(m_pick_ambient[i] - obj.m_pick_ambient[i]) > TOL_ZERO)
      return false;
    if(fabs(m_pick_diffuse[i] - obj.m_pick_diffuse[i]) > TOL_ZERO)
      return false;
    if(fabs(m_pick_specular[i] - obj.m_pick_specular[i]) > TOL_ZERO)
      return false;
  }
  
  if(fabs(m_shininess - obj.m_shininess) > TOL_ZERO)
    return false;
  if(fabs(m_pick_shininess - obj.m_pick_shininess) > TOL_ZERO)
    return false;

  return true;
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
bool cAppearance::operator!=(const cAppearance &obj) const
{
  if(this->operator==(obj))
    return false;
  return true;
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void cAppearance::set_color(GLfloat *color)
{
  int i;
  for(i = 0; i < 3; ++i)
  {
    m_color[i] = color[i];
    m_ambient[i] = 0.6f * color[i];
    m_pick_ambient[i] = 0.6f * color[i];

    m_diffuse[i] = 0.9f * color[i];
    m_pick_diffuse[i] = 0.9f * color[i];

    m_specular[i] = 0.7f * color[i];
    m_pick_specular[i] = 0.7f * color[i];
  }

 /* m_color[3] = color[3];
  m_ambient[3] = color[3];
  m_diffuse[3] = color[3];
  m_specular[3] = color[3];*/

  m_pick_ambient[0]  = 1.0f;
  m_pick_ambient[1]  = 1.0f;
  m_pick_ambient[2]  = 1.0f;

  m_pick_diffuse[0]  = 1.0f;
  m_pick_diffuse[1]  = 1.0f;
  m_pick_diffuse[2]  = 1.0f;

  m_pick_specular[0] = 1.0f;
  m_pick_specular[1] = 1.0f;
  m_pick_specular[2] = 1.0f;

  //generate_select_color(m_pick_ambient[0], m_pick_ambient[1], m_pick_ambient[2]);
  //generate_select_color(m_pick_diffuse[0], m_pick_diffuse[1], m_pick_diffuse[2]);
  //generate_select_color(m_pick_specular[0], m_pick_specular[1], m_pick_specular[2]);
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void cAppearance::set_alpha(GLfloat alpha)
{
	m_color[3]		= alpha;
	m_ambient[3]	= alpha;
	m_diffuse[3]	= alpha;
	m_specular[3] = alpha;

	m_pick_ambient[3]		= alpha;
  m_pick_diffuse[3]		= alpha;
  m_pick_specular[3]	= alpha;
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void cAppearance::load_color(eAppearanceColorType type, float alpha) const
{
  if(type == COLOR)
    glColor4f(m_color[0], m_color[1], m_color[2], alpha);
  else if(type == PICK)
  {
    // TODO (lfmachado, 15-02-2011) decide color to use 
    //glColor3fv(&m_pick_diffuse[0]);
    glColor4f(color_white[0], color_white[1], color_white[2], alpha);
  }
  else if(type == TEXTURE)
    glColor4f(color_white[0], color_white[1], color_white[2], alpha);
  else if(type == SHADOW)
    glColor4f(color_black[0], color_black[1], color_black[2], alpha);
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void cAppearance::load_color(eAppearanceColorType type) const
{
  if(type == COLOR)
    glColor3fv(m_color);
  else if(type == PICK)
  {
    // TODO (lfmachado, 15-02-2011) decide color to use 
    //glColor3fv(&m_pick_diffuse[0]);
    glColor3fv(color_white);
  }
  else if(type == TEXTURE)
    glColor3fv(color_white);
  else if(type == SHADOW)
    glColor4fv(color_black);
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void cAppearance::load(eAppearanceColorType type, float alpha) const
{
  if(type == COLOR)
  {
    // Front face
		GLfloat ambient_mat_front[] = { m_ambient[0], 
                                    m_ambient[1], 
                                    m_ambient[2], 
                                    alpha};
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_mat_front);

		GLfloat diffuse_mat_front[] = { m_diffuse[0], 
                                    m_diffuse[1], 
                                    m_diffuse[2], 
                                    alpha};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_mat_front);

		GLfloat specular_mat_front[] = {m_specular[0], 
                                    m_specular[1], 
                                    m_specular[2], 
                                    alpha};
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_mat_front);
    // End of front face

    // Back face
    GLfloat ambient_mat_back[] = {0.4f * m_ambient[0], 
                                  0.4f * m_ambient[1], 
                                  0.4f * m_ambient[2], 
                                  alpha};
    glMaterialfv(GL_BACK, GL_AMBIENT, ambient_mat_back);

		GLfloat diffuse_mat_back[] = {m_diffuse[0], 
                                  m_diffuse[1], 
                                  m_diffuse[2], 
                                  alpha};
    glMaterialfv(GL_BACK, GL_DIFFUSE, diffuse_mat_back);

		GLfloat specular_mat_back[] = { 0.8f * m_specular[0], 
                                    0.8f * m_specular[1], 
                                    0.8f * m_specular[2], 
                                    alpha};
    glMaterialfv(GL_BACK, GL_SPECULAR, specular_mat_back);
    // End of back face
  }
  else if(type == PICK)
  {
    // Front face 
		GLfloat ambient_pick_mat[] = {m_pick_ambient[0], 
																	m_pick_ambient[1], 
																	m_pick_ambient[2], 
																	alpha};
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_pick_mat);

		GLfloat diffuse_pick_mat[] = {m_pick_diffuse[0], 
																	m_pick_diffuse[1], 
																	m_pick_diffuse[2], 
																	alpha};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_pick_mat);

		GLfloat specular_pick_mat[] = { m_pick_specular[0], 
																	  m_pick_specular[1], 
																		m_pick_specular[2], 
																		alpha};
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_pick_mat);
    // End of front face

    // Back face
    GLfloat ambient_pick_mat_back[] = { 0.4f * m_pick_ambient[0], 
																	      0.4f * m_pick_ambient[1], 
																	      0.4f * m_pick_ambient[2], 
																	      alpha};
    glMaterialfv(GL_BACK, GL_AMBIENT, ambient_pick_mat_back);

		GLfloat diffuse_pick_mat_back[] = { m_pick_diffuse[0], 
																	      m_pick_diffuse[1], 
																	      m_pick_diffuse[2], 
																	      alpha};
    glMaterialfv(GL_BACK, GL_DIFFUSE, diffuse_pick_mat_back);

		GLfloat specular_pick_mat_back[] = {0.8f *	m_pick_specular[0], 
																	      0.8f *	m_pick_specular[1], 
																		    0.8f *	m_pick_specular[2], 
																		    alpha};
    glMaterialfv(GL_BACK, GL_SPECULAR, specular_pick_mat_back);
    // End of back face
  }
  else if(type == TEXTURE)
  {
    GLfloat ambient_mat[] = {0.4f, 0.4f, 0.4f, alpha};
    glMaterialfv(m_face, GL_AMBIENT, ambient_mat);

    GLfloat diffuse_mat[] = {0.8f, 0.8f, 0.8f, alpha};
    glMaterialfv(m_face, GL_DIFFUSE, diffuse_mat);

    GLfloat specular_mat[] = {0.6f, 0.6f, 0.6f, alpha};  
    glMaterialfv(m_face, GL_SPECULAR, specular_mat);
  }

  glMaterialf(m_face, GL_SHININESS, m_shininess);
}
