#ifndef VGL_GLUT_H
#define VGL_GLUT_H

#ifndef VGLGLUTAPI
# ifndef VGLGLUT_DLL
#  ifndef TEC_DLL
#   define VGLGLUTAPI
#  else
#   define VGLGLUTAPI __declspec(dllimport)
#  endif
# else
#  define VGLGLUTAPI __declspec(dllexport)
# endif
#endif

#include <vgl/vgl.h>
#include <vgl/cnv/glutcanvas.h>

#endif
