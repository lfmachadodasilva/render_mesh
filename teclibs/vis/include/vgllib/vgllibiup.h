#ifndef VGLLIBIUP_H
#define VGLLIBIUP_H

#ifndef VGLLIBIUP_DLL
# ifndef TEC_DLL
#  define VGLLIBIUPAPI
# else
#  define VGLLIBIUPAPI __declspec(dllimport)
# endif
#else
# define VGLLIBIUPAPI __declspec(dllexport)
#endif

#include <vgllib/hnd/iupoverlay.h>

#endif
