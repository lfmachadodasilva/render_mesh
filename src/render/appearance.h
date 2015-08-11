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

#ifndef ANFLEX_INTERFACE_APPEARANCE_H_
#define ANFLEX_INTERFACE_APPEARANCE_H_

#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/glew.h>

class cAppearance
{
private:
  GLenum m_face;

  GLfloat m_color[4];

  GLfloat m_ambient[4];
  GLfloat m_diffuse[4];
  GLfloat m_specular[4];
  GLfloat m_shininess;

  GLfloat m_pick_ambient[4];
  GLfloat m_pick_diffuse[4];
  GLfloat m_pick_specular[4];
  GLfloat m_pick_shininess;

public:
 cAppearance();
 cAppearance(GLenum face, GLfloat *color);
 ~cAppearance() { }

 void operator=(const cAppearance &obj);
 bool operator==(const cAppearance &obj) const;
 bool operator!=(const cAppearance &obj) const;

 enum eAppearanceColorType{COLOR=1, PICK, TEXTURE, SHADOW};

 void set_face(GLenum face) { m_face = face; }

 void set_color(GLfloat *color);

 void set_alpha(GLfloat alpha);

 const GLfloat* get_color(void) const { return &m_color[0]; }
 const GLfloat* get_color_pick(void) const { return &m_pick_diffuse[0]; }
 
 void load(eAppearanceColorType type = COLOR, float alpha = 1.0f) const;
 void load_color(eAppearanceColorType type = COLOR) const;
 void load_color(eAppearanceColorType type, float alpha) const;
};

#endif // ANFLEX_INTERFACE_APPEARANCE_H_
