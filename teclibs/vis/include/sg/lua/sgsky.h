#ifndef SGSKY_H
#define SGSKY_H

#ifndef SGSKY_DLL
# ifndef TEC_DLL
#  define SGSKYAPI
# else
#  define SGSKYAPI __declspec(dllimport)
# endif
#else
# define SGSKYAPI __declspec(dllexport)
#endif

#endif
