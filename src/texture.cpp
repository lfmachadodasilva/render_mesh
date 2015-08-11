// -------------------------------------------------------------------------------
// Anflex Project -- Tecgraf/PUC-Rio
// www.tecgraf.puc-rio.br
//
// $HeadURL: https://subversion.tecgraf.puc-rio.br/svn/anflex-interface/trunk/src/texture.cpp $
// $Revision: 1149 $
// $Date: 2012-04-10 16:02:13 -0300 (ter, 10 abr 2012) $
//
// $Author: thyago $
// -------------------------------------------------------------------------------

#include <assert.h>

#include "texture.h"
//#include "util.h"
#include "bmp.h"
//#include "anfvar.h"

// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
cTexture::cTexture(GLenum texFormat, GLenum texWrap, GLenum texFilter, GLfloat texMode)
{
 filename = "";

 texId = 0;
 texCanvasId = 0;

 tex_format = texFormat;
 tex_wrap = texWrap;
 tex_filter = texFilter;
 tex_mode = texMode;

 m_tex_coord_type = STATIC_COORD;
 
 m_s_param = -1;
 m_t_param = -1;

 m_s_pname_eq = -1;
 m_t_pname_eq = -1;

 m_s_eq[0] = 0.0;
 m_s_eq[1] = 0.0;
 m_s_eq[2] = 0.0;
 m_s_eq[3] = 0.0;
 
 m_t_eq[0] = 0.0;
 m_t_eq[1] = 0.0;
 m_t_eq[2] = 0.0;
 m_t_eq[3] = 0.0;
}

// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
cTexture::cTexture(bool smooth, int num_levels, GLenum texFormat, GLenum texWrap, GLenum texFilter, GLfloat texMode)
{
 filename = "";

 texId = 0;
 texCanvasId = 0;

 tex_format = texFormat;
 tex_wrap = texWrap;
 tex_filter = texFilter;
 tex_mode = texMode;

 m_tex_coord_type = STATIC_COORD;

 m_s_param = -1;
 m_t_param = -1;

 m_s_pname_eq = -1;
 m_t_pname_eq = -1;

 m_s_eq[0] = 0.0;
 m_s_eq[1] = 0.0;
 m_s_eq[2] = 0.0;
 m_s_eq[3] = 0.0;

 m_t_eq[0] = 0.0;
 m_t_eq[1] = 0.0;
 m_t_eq[2] = 0.0;
 m_t_eq[3] = 0.0;
}

// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
void cTexture::operator=(const cTexture& obj)
{
 filename = obj.filename;

 texId = obj.texId;
 texCanvasId = obj.texCanvasId;

 tex_format = obj.tex_format;
 tex_wrap = obj.tex_wrap;
 tex_filter = obj.tex_filter;
 tex_mode = obj.tex_mode;
}

// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
void cTexture::deleteTex(void)
{
#ifndef _EXPANF_DLL_
 glDeleteTextures(1, &texId);

 if(texCanvasId)
  glDeleteTextures(1, &texCanvasId);
#endif
}

// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
bool cTexture::addImage(string& fname, string& mess)
{
	filename = fname;

	unsigned char *image = NULL;
	unsigned int nbits = 0, rowsize = 0, width = 0, height = 0;
	image = bmpRead((char*)filename.c_str(), &width, &height, &nbits, &rowsize);
	if((!image) || (nbits != 24) && (rowsize != (3 * width)))
	{
		image = NULL;
		mess = "Could not open texture file " + filename + ".";
		return false;
	}

	if(image)
	{
		glPushAttrib(GL_ENABLE_BIT | GL_TEXTURE_BIT);
		glEnable(tex_format);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		glGenTextures(1, &texId);
		glBindTexture(tex_format, texId);
		glTexImage2D(tex_format, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

		glPopAttrib();

		free(image);

		return true;
	}

  return false;
}

// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
void cTexture::load(bool canvasTex)
{
#ifndef _EXPANF_DLL_
	if(!texId)
		return;

	glPushAttrib(/*GL_ENABLE_BIT | GL_CURRENT_BIT | GL_LIGHTING_BIT | */GL_TEXTURE_BIT); 

	glEnable(tex_format);

	if(canvasTex)
		glBindTexture(tex_format, texCanvasId);
	else
		glBindTexture(tex_format, texId);

	glTexParameteri(tex_format, GL_TEXTURE_WRAP_S, tex_wrap);
	glTexParameteri(tex_format, GL_TEXTURE_WRAP_T, tex_wrap);
	glTexParameteri(tex_format, GL_TEXTURE_MAG_FILTER, tex_filter);
	glTexParameteri(tex_format, GL_TEXTURE_MIN_FILTER, tex_filter);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, tex_mode);

	if(m_tex_coord_type == AUTOMATIC_COORD)
	{
		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);

		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);

		glTexGenfv(GL_S, GL_OBJECT_PLANE, m_s_eq);
		glTexGenfv(GL_T, GL_OBJECT_PLANE, m_t_eq);
	}
#endif
}


// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
void cTexture::loadMatrix(float min_value, float max_value)
{
#ifndef _EXPANF_DLL_
 if(!texId)
  return;

 float diff = max_value - min_value;
 float disp = -min_value / diff;
 glMatrixMode(GL_TEXTURE);
 glPushMatrix();
 glLoadIdentity();
 glTranslatef(disp, 0.0f, 0.0f);
 glScalef(1.0f/diff, 1.0f, 1.0f);
#endif
}

// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
void cTexture::unloadMatrix(void)
{
#ifndef _EXPANF_DLL_
 glMatrixMode(GL_TEXTURE);
 glPopMatrix();
 glMatrixMode(GL_MODELVIEW);
#endif
}

// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
void cTexture::unload(void)
{
#ifndef _EXPANF_DLL_
 glPopAttrib();
#endif
}


// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
void cTexture :: enable(void)
{
#ifndef _EXPANF_DLL_
 glEnable( tex_format );
#endif
}


// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
void cTexture :: disable(void)
{
#ifndef _EXPANF_DLL_
 glDisable( tex_format );
#endif
}

// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
void cTexture :: set_coordS_eqs(int pname_eq, float eq[4])
{
  m_s_pname_eq = pname_eq;
  
  m_s_eq[0] = eq[0];
  m_s_eq[1] = eq[1];
  m_s_eq[2] = eq[2];
  m_s_eq[3] = eq[3];

  float norma = 0.0;
  for(int i = 0; i < 4; ++i)
    norma += (m_s_eq[i] * m_s_eq[i]);
  norma = sqrt(norma);
  
  for(int i = 0; i < 4; ++i)
    m_s_eq[i] /= norma;
}

// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
void cTexture :: set_coordT_eqs(int pname_eq, float eq[4])
{
  m_t_pname_eq = pname_eq;
  
  m_t_eq[0] = eq[0];
  m_t_eq[1] = eq[1];
  m_t_eq[2] = eq[2];
  m_t_eq[3] = eq[3];

  float norma = 0.0;
  for(int i = 0; i < 4; ++i)
    norma += (m_t_eq[i] * m_t_eq[i]);
  norma = sqrt(norma);
  
  for(int i = 0; i < 4; ++i)
    m_t_eq[i] /= norma;
}
