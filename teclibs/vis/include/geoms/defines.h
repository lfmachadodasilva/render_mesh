
#ifndef GEOMS_DEFINES_H
#define GEOMS_DEFINES_H

#ifndef GEOMS_DLL
# ifndef TEC_DLL
#  define GEOMS_API
# else
#  define GEOMS_API __declspec(dllimport)
# endif
#else
# define GEOMS_API __declspec(dllexport)
#endif

#endif
