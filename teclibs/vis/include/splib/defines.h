#ifndef SPLIB_DEFINES_H
#define SPLIB_DEFINES_H

#ifndef SPLIB_DLL
# ifndef TEC_DLL
#  define SPLIB_API
#  define SPLIBH_API
# else
#  define SPLIB_API __declspec(dllimport)
#  define SPLIBH_API __declspec(dllexport)
# endif
#else
# define SPLIB_API __declspec(dllexport)
# define SPLIBH_API __declspec(dllexport)
#endif

#ifndef NULL
# ifdef __cplusplus
#  define NULL    0
# else
#  define NULL    ((void *)0)
# endif
#endif

#endif

