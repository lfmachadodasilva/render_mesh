#ifndef VGLLIB_DEFINES_H
#define VGLLIB_DEFINES_H

#ifndef VGLLIB_DLL
# ifndef TEC_DLL
#  define VGLLIBAPI
# else
#  define VGLLIBAPI __declspec(dllimport)
# endif
#else
# define VGLLIBAPI __declspec(dllexport)
#endif

#include <GL/glew.h>

#endif

