//* vglglut.h
// celes@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Feb 2003

#ifndef VGL_C_GLUT_H
#define VGL_C_GLUT_H

#include <vgl/vglc/vglc.h>

#ifdef __cplusplus
extern "C" {
#endif

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

VGLGLUTAPI VglCanvas* vglGlutCanvas (int win);
VGLGLUTAPI int vglGetGlutWindow (VglCanvas* vgl);

#ifdef __cplusplus
}
#endif

#endif
