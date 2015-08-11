// Definitions
// celes@tecgraf.puc-rio.br
// Jul 2002

#ifndef UGL_DEFINES_H
#define UGL_DEFINES_H

#ifndef UGL_DLL
# ifndef TEC_DLL
#  define UGL_API
# else
#  define UGL_API __declspec(dllimport)
# endif
#else
# define UGL_API __declspec(dllexport)
#endif

#include <GL/glew.h>

#define UGL_MEM_TYPE_CPU          0 // no VBO
#define UGL_MEM_TYPE_VERTEX       1 // Vertex attributes buffer
#define UGL_MEM_TYPE_INDEX        2 // Vertex indices buffer
#define UGL_MEM_TYPE_PIXEL_UNPACK 3 // Pixel unpack buffer
#define UGL_MEM_TYPE_PIXEL_PACK   4 // Pixel pack buffer
#define UGL_MEM_TYPE_MAX          5

#define UGL_MEM_USAGE_STATIC      0 // GL_STATIC_*
#define UGL_MEM_USAGE_STREAM      1 // GL_STREAM_*
#define UGL_MEM_USAGE_DYNAMIC     2 // GL_DYNAMIC_*

#define UGL_MEM_USAGE_CPU_TO_GPU 0 // GL_*_DRAW
#define UGL_MEM_USAGE_GPU_TO_CPU 1 // GL_*_READ
#define UGL_MEM_USAGE_GPU_ONLY   2 // GL_*_COPY

#endif
