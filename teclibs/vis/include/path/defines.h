#ifndef PATH_DEFINES_H
#define PATH_DEFINES_H

#ifndef PATH_DLL
# ifndef TEC_DLL
#  define PATH_API
# else
#  define PATH_API __declspec(dllimport)
# endif
#else
# define PATH_API __declspec(dllexport)
#endif

#endif

