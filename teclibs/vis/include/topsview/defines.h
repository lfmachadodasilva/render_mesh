#ifndef TPV_DEFINES_H
#define TPV_DEFINES_H

#ifndef TOPSVIEW_DLL
# ifndef TEC_DLL
#  define TPV_API
#  define TPVH_API
# else
#  define TPV_API __declspec(dllimport)
#  define TPVH_API __declspec(dllexport)
# endif
#else
# define TPV_API __declspec(dllexport)
# define TPVH_API __declspec(dllexport)
#endif

#endif
