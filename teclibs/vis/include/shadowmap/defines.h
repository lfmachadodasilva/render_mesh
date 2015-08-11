#ifndef SM_DEFINES_H
#define SM_DEFINES_H

#ifndef SHADOWMAP_DLL
# ifndef TEC_DLL
#  define SM_API
# else
#  define SM_API __declspec(dllimport)
# endif
#else
# define SM_API __declspec(dllexport)
#endif

#endif

