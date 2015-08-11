#ifndef VGL_PBUFFER_H
#define VGL_PBUFFER_H

#ifndef VGLPBUFFERAPI
# ifndef VGLPBUFFER_DLL
#  ifndef TEC_DLL
#   define VGLPBUFFERAPI
#  else
#   define VGLPBUFFERAPI __declspec(dllimport)
#  endif
# else
#  define VGLPBUFFERAPI __declspec(dllexport)
# endif
#endif

#endif

