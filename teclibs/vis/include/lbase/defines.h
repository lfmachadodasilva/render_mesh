#ifndef LBASE_DEFINES_H
#define LBASE_DEFINES_H

#ifndef LBASE_DLL
# ifndef TEC_DLL
#  define LBASEAPI
# else
#  define LBASEAPI __declspec(dllimport)
# endif
#else
# define LBASEAPI __declspec(dllexport)
#endif

#endif
