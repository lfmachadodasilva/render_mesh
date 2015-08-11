// -------------------------------------------------------------------------------
// Anflex Project -- Tecgraf/PUC-Rio
// www.tecgraf.puc-rio.br
//
// $HeadURL: https://subversion.tecgraf.puc-rio.br/svn/anflex-interface/trunk/src/texture.h $
// $Revision: 367 $
// $Date: 2010-09-22 19:45:00 -0300 (qua, 22 set 2010) $
//
// $Author: lduarte $
// -------------------------------------------------------------------------------

#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/glew.h>
#include <string>
#include <vector>

using std::string;
using std::vector;

#define texWidth 128

struct sRGB
{
 unsigned char red, green, blue;
};


class cTexture
{
private:

 GLenum tex_format;
 GLenum tex_wrap;
 GLenum tex_filter;
 GLfloat tex_mode;

 GLenum m_s_pname;
 GLenum m_t_pname;
 
 int m_s_param;
 int m_t_param;

 int m_s_pname_eq;
 int m_t_pname_eq;

 float m_s_eq[4];
 float m_t_eq[4];

 string filename;

 unsigned int texId;

 // usada apenas para o color map do canvas
 unsigned int texCanvasId;

 unsigned char palette_texture[4*texWidth];

public:
 cTexture(GLenum texFormat, GLenum texWrap, GLenum texFilter, GLfloat texMode);
 cTexture(bool smooth, int num_levels, GLenum texFormat, GLenum texWrap, GLenum texFilter, GLfloat texMode);
 ~cTexture() { deleteTex(); }

 enum eTextureCoord{STATIC_COORD=1, AUTOMATIC_COORD};

 eTextureCoord m_tex_coord_type;
 
 void operator=(const cTexture&);

 vector<sRGB> palette_colors;

 void set_tex_coord_type(eTextureCoord t) { m_tex_coord_type = t; }
 eTextureCoord get_tex_coord_type(void) { return m_tex_coord_type; }

 void set_coordS_params(GLenum pname, int param) { m_s_pname = pname; m_s_param = param; }
 void set_coordT_params(GLenum pname, int param) { m_t_pname = pname; m_t_param = param; }

 void set_coordS_eqs(int pname_eq, float eq[4]);
 void set_coordT_eqs(int pname_eq, float eq[4]);

 void deleteTex(void);

 bool addImage(string&, string&);

 void load(bool canvasTex = false);
 void loadMatrix(float, float);

 void unloadMatrix(void);
 void unload(void);

  /// @brief Enables the usage of loaded texture.
 ///
 ///        A call to this function does not load the texture to
 ///        be used. It only enables its use in further rendering.
 void enable(void);

 /// @brief Disables the usage of loaded texture.
 ///
 ///        A call to this function does not unload the texture 
 ///        being used. It only disables its use in further rendering.
 void disable(void);
};

#endif
