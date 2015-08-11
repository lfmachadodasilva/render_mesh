#ifndef UGL_IM_AVI_DEFINES_H
#define UGL_IM_AVI_DEFINES_H

#ifndef UGLIMAVI_DLL
# ifndef TEC_DLL
#  define UGLIMAVIAPI
# else
#  define UGLIMAVIAPI __declspec(dllimport)
# endif
#else
# define UGLIMAVIAPI __declspec(dllexport)
#endif

#endif
