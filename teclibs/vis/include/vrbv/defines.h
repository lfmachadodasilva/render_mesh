#ifndef VRBV_DEFINES_H
#define VRBV_DEFINES_H

#ifndef VRBV_DLL
# ifndef TEC_DLL
#  define VRBV_API
# else
#  define VRBV_API __declspec(dllimport)
# endif
#else
# define VRBV_API __declspec(dllexport)
#endif

#endif