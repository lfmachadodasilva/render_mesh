#ifndef SGVGL_DEFINES_H
#define SGVGL_DEFINES_H

#ifndef SGVGL_DLL
# ifndef TEC_DLL
#  define SGVGLAPI
# else
#  define SGVGLAPI __declspec(dllimport)
# endif
#else
# define SGVGLAPI __declspec(dllexport)
#endif

#endif

