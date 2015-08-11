#ifndef AUTOCAM_DEFINES_H
#define AUTOCAM_DEFINES_H

#ifndef AUTOCAM_DLL
# ifndef TEC_DLL
#  define AUTOCAM_API
#  define AUTOCAMH_API
# else
#  define AUTOCAM_API __declspec(dllimport)
#  define AUTOCAMH_API __declspec(dllexport)
# endif
#else
# define AUTOCAM_API __declspec(dllexport)
# define AUTOCAMH_API __declspec(dllexport)
#endif

#ifndef NULL
# ifdef __cplusplus
#  define NULL    0
# else
#  define NULL    ((void *)0)
# endif
#endif

#endif

