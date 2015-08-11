#ifndef VGL_IUP_H
#define VGL_IUP_H

#ifndef VGLIUP_DLL
# ifndef TEC_DLL
#  define VGLIUPAPI
# else
#  define VGLIUPAPI __declspec(dllimport)
# endif
#else
# define VGLIUPAPI __declspec(dllexport)
#endif

#include <vgl/vgl.h>
#include <vgl/cnv/iupcanvas.h>

#endif
