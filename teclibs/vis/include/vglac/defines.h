#ifndef VGLAC_DEFINES_H
#define VGLAC_DEFINES_H

#ifndef VGLAC_DLL
# ifndef TEC_DLL
#  define VGLAC_API
#  define VGLACH_API
# else
#  define VGLAC_API __declspec(dllimport)
#  define VGLACH_API __declspec(dllexport)
# endif
#else
# define VGLAC_API __declspec(dllexport)
# define VGLACH_API __declspec(dllexport)
#endif

#endif
