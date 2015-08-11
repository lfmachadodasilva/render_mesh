#ifndef GC_DEFINES_H
#define GC_DEFINES_H

#ifdef _WIN32
#pragma warning(disable:4996)
#endif

#ifndef GC_DLL
# ifndef TEC_DLL
#  define GC_API
#  define GCH_API
# else
#  define GC_API __declspec(dllimport)
#  define GCH_API __declspec(dllexport)
# endif
#else
# define GC_API __declspec(dllexport)
# define GCH_API __declspec(dllexport)
#endif

#ifndef NULL
# ifdef __cplusplus
#  define NULL 0
# else
#  define NULL ((void*)0)
# endif
#endif

#endif
