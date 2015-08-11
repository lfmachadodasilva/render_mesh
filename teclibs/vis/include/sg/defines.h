#ifndef SG_DEFINES_H
#define SG_DEFINES_H

#ifndef SG_DLL
# ifndef TEC_DLL
#  define SG_API
#  define SGH_API
# else
#  define SG_API __declspec(dllimport)
#  define SGH_API __declspec(dllexport)
# endif
#else
# define SG_API __declspec(dllexport)
# define SGH_API __declspec(dllexport)
#endif

#include <GL/glew.h>

#define SG_DEG2RAD 0.0174532f

#endif

