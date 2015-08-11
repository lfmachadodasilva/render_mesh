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

#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/glew.h>
#include <GL/glut.h>

#include <iup.h>
#include <iupgl.h>

#include "main-dialog.h"
#include "obj-dialog.h"

#include "anfvar.h"
#include "render\pick.h"
#include "render\render.h"

extern void init_opengl(void);
cPick::ePickType cPick::m_pick_type = cPick::NO_PICK;
bool cRender::m_new_render = false;

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void _glfwParseGLVersion( int *major, int *minor, int *rev )
{
  GLuint _major, _minor = 0, _rev = 0;
  const GLubyte *version;
  const GLubyte *ptr;

  // Get OpenGL version string
  version = glGetString( GL_VERSION );
  if( !version )
  {
    return;
  }

  // Parse string
  ptr = version;
  for( _major = 0; *ptr >= '0' && *ptr <= '9'; ptr ++ )
  {
    _major = 10*_major + (*ptr - '0');
  }
  if( *ptr == '.' )
  {
    ptr ++;
    for( _minor = 0; *ptr >= '0' && *ptr <= '9'; ptr ++ )
    {
      _minor = 10*_minor + (*ptr - '0');
    }
    if( *ptr == '.' )
    {
      ptr ++;
      for( _rev = 0; *ptr >= '0' && *ptr <= '9'; ptr ++ )
      {
        _rev = 10*_rev + (*ptr - '0');
      }
    }
  }

  // Return parsed values
  *major = _major;
  *minor = _minor;
  *rev = _rev;
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
int main (int argc, char** argv)
{
  // Init
  //glutInit(&argc, argv);
  IupOpen(&argc, &argv);
  IupGLCanvasOpen();
  IupImageLibOpen();

  // Create dialog
  cMainDialog *main_dialog = new cMainDialog();

  //glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if(GLEW_OK != err) 
  {
    fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
    return EXIT_FAILURE;
  }

  printf("Glew Version: %s\n", glewGetString(GLEW_VERSION));
  printf("GL Vendor: %s\n", glGetString(GL_VENDOR));
  printf("GL Renderer: %s\n", glGetString(GL_RENDERER));
  printf("\nGL Version: %s\n", glGetString(GL_VERSION));
  
  //This is the new way for getting the GL version.
	//It returns integers. Much better than the old glGetString(GL_VERSION).
  int OpenGLVersion[2];
  glGetIntegerv(GL_MAJOR_VERSION, &OpenGLVersion[0]);
  glGetIntegerv(GL_MINOR_VERSION, &OpenGLVersion[1]);
  printf("OpenGL major version = %d\n", OpenGLVersion[0]);
  printf("OpenGL minor version = %d\n", OpenGLVersion[1]);
  
  // For all versions of OpenGL 3.3 and above, 
  // the corresponding GLSL version matches the OpenGL version. 
  // So GL 4.1 uses GLSL 4.10.
  printf("Shader Version: %s\n\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
  
  int major, minor, rev; 
  _glfwParseGLVersion(&major, &minor, &rev);

  cRender::m_new_render = major <= 2 ? false: true;

  g_model = new cModel();

  if(!g_render_att)
    g_render_att = new cRenderAtt();

  if(cRender::m_new_render)
  {
    if(!g_shader)
    {
      g_shader = new cShader();
      if(!g_shader->create())
      {
        delete g_shader;
        g_shader = NULL;
      }
    }

    if(!g_shader2)
    {
      g_shader2 = new cShader();
      if(!g_shader2->create())
      {
        delete g_shader2;
        g_shader2 = NULL;
      }
    }
  }

  init_opengl();

  main_dialog->show_dialog();

  IupMainLoop();
  IupClose();

  delete main_dialog;
  //delete obj_dialog;

  return EXIT_SUCCESS;
}

